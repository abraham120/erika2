
/* This load file is used when __NO_ROM_DATA__ is defined */

OUTPUT_FORMAT(srec)
OUTPUT_ARCH(h8300)
ENTRY(__start)

MEMORY
{
    mem : o = 0x8000, l = 0x6f00
}

SECTIONS
{
    .text : {
	*(.init)
        *(.text)
        *(.rodata)
	*(.vectors)
    } > mem


    .data : {
        __DATA_RAM_START = . ;	
        *(.data)
	*(.tiny)
	__DATA_RAM_END = . ;
    } > mem
    
    
    .bss : {
        __BSS_START = . ;
        *(.bss)
        *(COMMON)
        __BSS_END = . ;
    } > mem
}
