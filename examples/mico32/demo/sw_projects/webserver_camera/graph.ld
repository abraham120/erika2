SECTIONS
{
	.graph (NOLOAD) : 
	{
		. = ALIGN(16);
		_fgraph = .;
		*(.graph)
		. = ALIGN(16);
		.egraph = .;
	} > sdram
}
