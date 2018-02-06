/** @file reg_esm.h
*   @brief ESM Register Layer Header File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the ESM driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __REG_ESM_H__
#define __REG_ESM_H__

#include "sys_common.h"



/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Esm Register Frame Definition */
/** @struct esmBase
*   @brief Esm Register Frame Definition
*
*   This type is used to access the Esm Registers.
*/
/** @typedef esmBASE_t
*   @brief Esm Register Frame Type Definition
*
*   This type is used to access the Esm Registers.
*/
typedef volatile struct esmBase
{
    uint32 EPENASET1;              /* 0x0000                 */
    uint32 EPENACLR1;              /* 0x0004                 */
    uint32 INTENASET1;             /* 0x0008                 */
    uint32 INTENACLR1;             /* 0x000C                 */
    uint32 INTLVLSET1;             /* 0x0010                 */
    uint32 INTLVLCLR1;             /* 0x0014                 */
    uint32 ESTATUS1[3U];           /* 0x0018, 0x001C, 0x0020 */
    uint32 EPSTATUS;               /* 0x0024                 */
    uint32 INTOFFH;                /* 0x0028                 */
    uint32 INTOFFL;                /* 0x002C                 */
    uint32 LTC;                    /* 0x0030                 */
    uint32 LTCPRELOAD;             /* 0x0034                 */
    uint32 KEY;                    /* 0x0038                 */
    uint32 ESTATUS2EMU;            /* 0x003C                 */
} esmBASE_t;

/** @def esmREG
*   @brief Esm Register Frame Pointer
*
*   This pointer is used by the Esm driver to access the Esm registers.
*/
#define esmREG ((esmBASE_t *)0xFFFFF500U)

/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
