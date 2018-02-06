/* Memory map for Freescale MPC5643L CPU 1 in multicore setup */

MEMORY
{
    /* First 16 KB for boot sector */
	boot:	org = 0x00000000, len = 0x00004000
	iflash:	org = 0x000C0000, len = 0x00040000
    /* Use only 64 kB of RAM for Slave core, (the second RAM block) */
	isram:	org = 0x50000000, len = 0x00010000
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);
