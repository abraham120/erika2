/* Memory map for Freescale MPC5668 CPU 1 in multicore setup */

MEMORY
{
	boot:	org = 0x00000000, len = 0x00020000
	iflash:	org = 0x00030000, len = 0x001c0000

    /* Dummy memory areas. Used only bu MPC5643L with Codewarrior */
    calibrations_ram:	org = 0x00040000, len = 0x1
    calibrations_flash:	org = 0x00060000, len = 0x1

/* Use only 256 kB of RAM, as per MMU setting from the BAM */
	isram:	org = 0x40020000, len = 0x00020000
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);
