
MEMORY
{
	/* First 16KB reserved for vectors */
	vectors (rx): org = 0x00000000, len = 0x00004000
	/* External SDRAM 32MB-16KB  */
	sdram :  org = 0x00004000, len = 0x01ffc000
	/* Internal SRAM 16KB  */
	sram :	org = 0xd1030000, len = 0x00004000
}
SECTIONS
{
	/* DWARF 1 */
	.debug          0 : { *(.debug) }
	.line           0 : { *(.line) }

	/* GNU DWARF 1 extensions */
	.debug_srcinfo  0 : { *(.debug_srcinfo) }
	.debug_sfnames  0 : { *(.debug_sfnames) }

	/* DWARF 1.1 and DWARF 2 */
	.debug_aranges  0 : { *(.debug_aranges) }
	.debug_pubnames 0 : { *(.debug_pubnames) }

	/* DWARF 2 */
	.debug_info     0 : { *(.debug_info) }
	.debug_abbrev   0 : { *(.debug_abbrev) }
	.debug_line     0 : { *(.debug_line) }
	.debug_frame    0 : { *(.debug_frame) }
	.debug_str      0 : { *(.debug_str) }
	.debug_loc      0 : { *(.debug_loc) }
	.debug_macinfo  0 : { *(.debug_macinfo) }

	/* SGI/MIPS DWARF 2 extensions */
	.debug_weaknames 0 : { *(.debug_weaknames) }
	.debug_funcnames 0 : { *(.debug_funcnames) }
	.debug_typenames 0 : { *(.debug_typenames) }
	.debug_varnames  0 : { *(.debug_varnames) }

	.vectors : {
		*(.vectors)
		__vectors_end = . ;
		} > vectors

	.text : {
		*(.text)
		*(.rdata)
		*(.rodata)
		*(.frame_info)
		*(.j_class_table)
		*(.init)
		*(.fini)
		*(.glue_7t)
		*(.glue_7)
		*(.eh_frame)
	} > sdram

	.sdata2 : {} > sdram

	__DATA_RAM	= .;
	__DATA_ROM 	= . ;
	.data  : {
		*(.data)
	} > sdram

	.sdata : {
		*(.sdata)
	} > sdram

	__DATA_END	= .;

	__BSS_START	= .;
	.sbss : {}
	.bss  : {
		*(.bss)
	} > sdram
	__BSS_END	= .;
	end		= .;
	_end		= .;
	__HEAP_START	= .;
}


INCLUDE out/loc_triscend.ld

__PHYSICAL_EXEC_ADDRESS = 0xd0000000 ;	/* useless */
__PSEUDO_EXEC_ADDRESS   = 0xc0000000 ;
__ALIAS_SETTING         = 0x08 ;


__EH_FRAME_BEGIN__ = 0 ;
