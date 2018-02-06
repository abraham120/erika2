/* Kernel entry function */
ENTRY(_start)

OUTPUT_FORMAT(elf32-i386)

SECTIONS {
	/* Memory-mapped CGA buffer */
	_scga = 0xB8000;
	cga_buffer = 0xB8000;
	_ecga = 0xB8FFF;

    /* Set kernel start address */
    . = 0x100000;

    /* Code and readonly data */
    .text : {
        /* fill gaps with int3 opcode to detect invalid jumps */
        /*FILL(0xcc)*/

        /* multiboot header */
        multiboot_header = .;
        KEEP (*(".rodata.multiboot"))

        /* fixed address for IRQ handlers */
        . = 0x1000;

        /* common text (always accessible) */
        _stext_common = .;

        /* start of FAIL* allowed code region */
        _stext_fail = .;

        /* IRQ Handlers */
        KEEP (*(".text.irqhandlers*")) /* ASM */
        *(".text.irq_handler*") /* C */
        *(".text.isrs*") /* C */
        *(".text.isr_*") /* C */
        KEEP (*(".text.idt")) /* ASM */
        . += 16; /* padding after data, workaround for import-trace */

        /* constructors */
        . = ALIGN(8);
        PROVIDE(__CTORS_START = .);
        KEEP (*(.ctors*))
        KEEP (*(.init_array*))
        PROVIDE(__CTORS_END = .);

        /* constructor code */
        _stext_constructors = .;
        KEEP (*(".text.startup"))
        _etext_constructors = .;

        /* common symbols */
        _stext_common_syms = .;
        *("_GLOBAL__I_a")
        _etext_common_syms = .;

        . += 16; /* padding after data, workaround for import-trace */

        /* compiler code (arithmetic routines...) */
        "*libgcc*.a:" ( ".text" )

        /* anonymous read only data (probably strings) */
        /* cannot be separated by source, so put it here */
        _srodata_an = .;
        *(".rodata..L*")
        _erodata_an = .;

        . += 16; /* padding after data, workaround for import-trace */

        . = ALIGN(0x1000);
        _stext = .;
        *(".text*")
        _etext = .;

        /* remaining rodata */
        _srodata = .;
        *(".rodata*")
        _erodata = .;

        _etext_fail_allowed = .;
    }

    /* Data and Stacks */
    . = 0x200000;
    .data : {
        _sstack = .; /* to include TSS in FAIL tests, TODO: better placing*/

        /* TSS at known address */
        _stss = .;
        tss = .;
        . += 104;
        _etss = .;

        /* Stacks */
        . = ALIGN(4096);
        /*_sstack = .;*/

        _sstack_os = .;
        *(".startup_stack")
        _estack_os = .;

        . = ALIGN(4096);
        _sstack = .;

        _sstack_os = .;
        *(".kernel_stack")
        _estack_os = .;

        _estack = .;

        /* Data */
        . = ALIGN(4096);
        _sdata = .;
        *(".data*")
        *(COMMON);
        _edata = .;
    }

    /* Memory-mapped I/O APIC */
    _sioapic = 0xFEC00000;
    ioapic = 0xFEC00000;
    _eioapic = 0xFEC00FFF;

    /* Memory-mapped Local APIC */
    _slapic = 0xFEE00000;
    lapic = 0xFEE00000;
    _elapic = 0xFEE00FFF;

    /* Get rid of unnecessary GCC bits */
    /DISCARD/ : {
        *(.comment)
        *(.eh_frame)
        *(.note.gnu.build-id)
    }
}
