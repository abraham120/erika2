#include "ee.h"
#include "cpu/x86/inc/ee_irqstub.h"
#include "mcu/x86/inc/ee_lapic.h"

#ifdef DEBUG
#include "mcu/x86/inc/ee_printf.h"
#endif

#define IDT_ENTRY_COUNT 256

ISR2(unhandled) {
#ifdef DEBUG
    printf("Unhandled Exception: #%d\n", vector);

    EE_hal_shutdown_system();
#endif
    // send end-of-interrupt (unless exception)
    if(vector > 31) {
        EE_lapic_send_eoi();
    }
}


struct idt_descriptor {
    /* First 16 bits of the offset to procedure entry point in the segment. */
    EE_UINT16 isr_offset_15_0;

    /* Segment selector for destination code segment. */
    EE_UINT16 cs;
    EE_UINT8 zero;

    /* Gate type
       0x5 for a task gate
       0xe for an interrupt gate
       0xf for a call gate */
    EE_UINT8 type:5;

    /* Lowest privilege level this gate can be accessed from.
       See Intel Developer's Manual Volume 3 - section 5.10.1.1 */
    EE_UINT8 dpl:2;

    /* Present bit */
    EE_UINT8 p:1;

    /* Bits 31-16 of the offset to procedure entry point in the segment. */
    EE_UINT16 isr_offset_31_16;

} __attribute__((__packed__));

/* The descriptor table */
extern struct idt_descriptor theidt[IDT_ENTRY_COUNT];

void EE_idt_init(void)
{
    struct idt_desc {
        /* Size of the IDT structure - 1 */
        EE_UINT16 size;
        /* 32-bit linear address of the IDT. */
        EE_UINT32 addr;
    } __attribute__((__packed__)) idtdesc;

    /* Commit the IDT */
    idtdesc.size = sizeof(theidt) - 1;
    idtdesc.addr = (EE_UINT32) &theidt[0];
    asm volatile("lidt %0" : : "m" (idtdesc) : "memory");
}


#ifdef	__MULTI__
#ifdef	__IRQ_STACK_NEEDED__
EE_UREG EE_x86_tmp_tos = 0U;
#endif
#endif


