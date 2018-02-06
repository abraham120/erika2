/* Memory map for Freescale MPC5644A */

MEMORY
{
    /* First 16 KB for boot sector */
	boot:	org = 0x00000000, len = 0x00004000

    /* 512 KB of Flash memory */
	iflash:	org = 0x00080000, len = 0x00080000

    /* 64 kB of RAM */
	isram:	org = 0x40000000, len = 0x00010000
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);

