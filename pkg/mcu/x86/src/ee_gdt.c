#include "mcu/x86/inc/ee_gdt.h"


#define	KERNEL_CODE_SEGMENT  0x8
#define	KERNEL_DATA_SEGMENT  0x10
#define	USER_CODE_SEGMENT  0x18
#define	USER_DATA_SEGMENT  0x20
#define	TSS_SEGMENT  0x28


/* Defines a GDT entry. We say packed, because it prevents the
 * compiler from doing things that it thinks is best, i.e.
 * optimization, etc. */
struct gdt_entry
{
    EE_UINT16 limit_low;
    EE_UINT16 base_low;
    EE_UINT8 base_middle;
    EE_UINT8 access;
    EE_UINT8 granularity;
    EE_UINT8 base_high;
} __attribute__((packed));

/* Special pointer which includes the limit: The max bytes
 * taken up by the GDT, minus 1. Again, this NEEDS to be
 * packed */
struct gdt_ptr
{
    EE_UINT16  limit;
    EE_UINT32 base;
} __attribute__((packed));

/* Our GDT, with 6 entries, and finally our special GDT pointer */
static struct gdt_entry gdt[6];
static struct gdt_ptr _gp;




/* Setup a descriptor in the Global Descriptor Table */
static void gdt_set_gate(int num, EE_UINT32 base, EE_UINT32 limit, EE_UINT8 access,
EE_UINT8 gran)
{
    /* Setup the descriptor base access */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}


void EE_gdt_init(void) {
    // load static GDT
    _gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
    _gp.base  = (EE_UINT32)&gdt;

    /* Our NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* The second entry is our Code Segment. The base address
     * is 0, the limit is 4 gigabytes, it uses 4 kilobyte
     * granularity, uses 32-bit opcodes, and is a Code Segment
     * descriptor.
     */
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /* The third entry is our Data Segment. It's exactly the
     * same as our code segment, but the descriptor type in
     * this entry's access byte says it's a Data Segment
     */
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    /* Install the user mode segments into the GDT */
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    ///* Install the TSS into the GDT */
    //tss_install(5, 0x10, 0x0);

    /* Flush our the old GDT / TSS and install the new changes! */

	// load GDT
	asm volatile("lgdt (%0)" :: "m"(_gp) : "memory");

	// setup data segments
	asm volatile("mov %0, %%ds; mov %0, %%gs; mov %0, %%es; mov %0, %%fs; mov %0, %%ss"
		:: "r"(KERNEL_DATA_SEGMENT) : "memory");

	// setup code segment
	asm volatile("jmp %0, $1f; 1:" :: "i"(KERNEL_CODE_SEGMENT) : "memory");

}
