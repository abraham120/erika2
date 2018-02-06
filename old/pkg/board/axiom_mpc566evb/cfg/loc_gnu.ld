/* Default linker script, for normal executables */
OUTPUT_FORMAT("elf32-powerpc", "elf32-powerpc",
	      "elf32-powerpc")
OUTPUT_ARCH(powerpc:common)
ENTRY(_start)
/*SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib");*/
/* Do we need any of these for elf?
   __DYNAMIC = 0;    */

MEMORY {
	boot (rx) : ORIGIN = 0xFFF00000 , LENGTH = 16K 
	rom (rx)  : ORIGIN = 0xFFF04000 , LENGTH = 40K
	ram (!rx) : ORIGIN = 0xFFF0E000 , LENGTH = 52K
}

SECTIONS {
	myboot : {
		out/ee_irqvect.o
	} > boot

	mytext : {
		*(.text)
		*(.rodata)
		__DATA_ROM = . ;
	} > rom

	mydata : AT (ADDR(mytext) + SIZEOF(mytext)) {
		__DATA_RAM = . ;
		*(.data)
		*(.sdata)
		__DATA_END = . ;
	} > ram

	.bss : {
		__BSS_START = . ;
		*(.bss)
		*(.dynbss)
		*(.sbssx .sbss.* .gnu.linkonce.sb.*)
		*(.scommon)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(.sbss)
		*(.comment)
		__BSS_END = . ;
		__HEAP_START = . ;
	} > ram
}

__HEAP_END = . ;

INCLUDE out/loc_mpc566evb.ld

