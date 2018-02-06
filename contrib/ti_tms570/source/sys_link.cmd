/*----------------------------------------------------------------------------*/
/* sys_link.cmd                                                               */
/*                                                                            */
/* (c) Texas Instruments 2009-2013, All rights reserved.                      */
/*                                                                            */


/* USER CODE BEGIN (0) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Linker Settings                                                            */

--retain="*(.intvecs)"

/* USER CODE BEGIN (1) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/
/* Memory Map                                                                 */

MEMORY
{
    VECTORS (X)  : origin=0x00000000 length=0x00000020
    FLASH0  (RX) : origin=0x00000020 length=0x0007FFE0
    FLASH1  (RX) : origin=0x00080000 length=0x00080000
    FLASH2  (RX) : origin=0x00100000 length=0x00080000
    FLASH3  (RX) : origin=0x00180000 length=0x00080000
    STACKS  (RW) : origin=0x08000000 length=0x00006000
    RAM     (RW) : origin=0x08006000 length=0x00022000

/* USER CODE BEGIN (2) */

/* USER CODE END */
}

/* USER CODE BEGIN (3) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Section Configuration                                                      */

SECTIONS
{
    .intvecs : {} > VECTORS
    .text    : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .const   : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .cinit   : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .pinit   : {} > FLASH0 | FLASH1 | FLASH2 | FLASH3
    .bss     : {} > RAM
    .data    : {} > RAM

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/*----------------------------------------------------------------------------*/
/* Misc                                                                       */

/* USER CODE BEGIN (6) */
/* USER CODE END */

/*----------------------------------------------------------------------------*/

