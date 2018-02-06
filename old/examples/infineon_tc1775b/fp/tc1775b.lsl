#include "tc1v1_2.lsl"

processor spe
{
	derivative = tc1775b;
}

derivative tc1775b
{
	core tc
	{
		architecture = TC1V1.2;
	}

	bus fpi_bus
	{
		mau = 8;
		width = 32;
		map (dest=bus:tc:fpi_bus, dest_offset=0, size=4G);
	}

	memory brom
	{
		mau = 8;
		size = 8k;
		type = reserved rom;
		map (dest=bus:tc:fpi_bus, dest_offset=0xBFFFE000, size=8k);
	}
	memory spram
	{
		mau = 8;
		size = 8k;
		type = reserved rom;
		map (dest=bus:tc:fpi_bus, dest_offset=0xC0000000, size=8k);
	}
	memory sram
	{
		mau = 8;
		size = 32k;
		type = ram;
		map (dest=bus:tc:fpi_bus, dest_offset=0xD0000000, size=32k);
	}
	memory sbsram
	{
		mau = 8;
		size = 8k;
		type = reserved ram;
		map (dest=bus:tc:fpi_bus, dest_offset=0xD0008000, size=8k);
	}
	memory pram
	{
		mau = 8;
		size = 4k;
		type = reserved ram;
		map (dest=bus:tc:pcp_data_bus, size=4k);
		map (dest=bus:tc:fpi_bus, dest_offset=0xF0010000, size=4k);
	}
	memory pcode
	{
		mau = 8;
		size = 16k;
		type = reserved ram;
		map (dest=bus:tc:pcp_code_bus, size=16k);
		map (dest=bus:tc:fpi_bus, dest_offset=0xF0020000, size=16k);
	}
}
