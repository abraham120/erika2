/* Memory map for Freescale MPC5643L in DPM mode */

MEMORY
{
    /* First 16 KB for boot sector */
	boot:	org = 0x00000000, len = 0x00004000

    /* 512 KB of Flash memory available in single core configuration */
	iflash:	org = 0x00080000, len = 0x00080000

    /* Use only 64 kB of RAM as in DPM mode.
    /* This value can be equal to 128 in case of LSM...
     * keep in mind in case of big application
     */
	isram:	org = 0x40000000, len = 0x00010000
}

isram_base = ADDR(isram);
isram_len = SIZEOF(isram);

