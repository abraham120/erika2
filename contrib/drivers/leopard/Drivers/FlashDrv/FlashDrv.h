/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef EE_MCU_MPC5643L_FLASH_H
#define EE_MCU_MPC5643L_FLASH_H

#include "eecfg.h"

#include <cpu/common/inc/ee_stdint.h>
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>

#include "ssd_types.h"
#include "ssd_c90fl.h"
#include "BswCommon.h"

/******************************************************************************
*	MPC-dependent configuration
******************************************************************************/
#define C90FL_REG_BASE                  0xC3F88000  ///< Flash reg. base addr.
#define MAIN_ARRAY_BASE                 0x00000000  ///< Main array base addr.
#define SHADOW_ROW_BASE                 0x00F00000  ///< Shadow base addr.
#define SHADOW_ROW_SIZE                 0x00004000  ///< Shadow size

#define C90FL_PAGE_SIZE                 0x10        ///< Flash page size

/* Low space blocks */
#define OFFSET_LOW_BLOCK0               0x00000000U ///< Offset of low block 0
#define LOW_BLOCK0_SIZE                 0x4000U     ///< 16KB block size
#define OFFSET_LOW_BLOCK1               0x00004000U ///< Offset of low block 1
#define LOW_BLOCK1_SIZE                 0xC000U     ///< 48KB block size
#define OFFSET_LOW_BLOCK2               0x00010000U ///< Offset of low block 2
#define LOW_BLOCK2_SIZE                 0xC000U     ///< 48KB block size
#define OFFSET_LOW_BLOCK3               0x0001C000U ///< Offset of low block 3
#define LOW_BLOCK3_SIZE                 0x4000U     ///< 16KB block size
#define OFFSET_LOW_BLOCK4               0x00020000U ///< Offset of low block 4
#define LOW_BLOCK4_SIZE                 0x10000U    ///< 64KB block size
#define OFFSET_LOW_BLOCK5               0x00030000U ///< Offset of low block 5
#define LOW_BLOCK5_SIZE                 0x10000U    ///< 64KB block size

/* Mid space blocks */
#define OFFSET_MID_BLOCK0               0x00040000U ///< Offset of mid block 0
#define MID_BLOCK0_SIZE                 0x20000U    ///< 128KB block size
#define OFFSET_MID_BLOCK1               0x00060000U ///< Offset of mid block 1
#define MID_BLOCK1_SIZE                 0x20000U    ///< 128KB block size

/* High space blocks */
#define OFFSET_HIGH_BLOCK0              0x00080000U ///< Offset of high block 0
#define HIGH_BLOCK0_SIZE                0x40000U    ///< 256KB block size
#define OFFSET_HIGH_BLOCK1              0x000C0000U ///< Offset of high block 1
#define HIGH_BLOCK1_SIZE                0x40000U    ///< 256KB block size

/* Flash Memory Lower/Upper Bound */
#define FLASH_MEMORY_LOWER_BOUND    (OFFSET_LOW_BLOCK0) ///< Flash lower bound
#define FLASH_MEMORY_UPPER_BOUND    (OFFSET_HIGH_BLOCK1 + HIGH_BLOCK1_SIZE) ///< Flash upper bound

/* Low/Mid address lock enabled password */
#define FLASH_LMLR_PASSWORD             0xA1A11111U ///< Flash primary low/mid password

/* High address lock enabled password */
#define FLASH_HLR_PASSWORD              0xB2B22222U ///< Flash high password

/* Secondary low and middle address lock enabled password */
#define FLASH_SLMLR_PASSWORD            0xC3C33333  ///< Flash secondary low/mid password

/******************************************************************************
*	Abstraction of SSD functions 
******************************************************************************/
#if !defined(__E200ZX_EXECUTE_FROM_RAM__) && defined (EE_SSD_DRIVER_IN_RAM)

#pragma push // save current pragma context
#pragma section const_type "SSD_Driver" "SSD_Driver" data_mode=far_abs
__declspec(section "SSD_Driver")
extern const uint32 FlashProgram_C[];
extern const uint32 BlankCheck_C[];
extern const uint32 FlashInit_C[];
extern const uint32 FlashErase_C[];
extern const uint32 ProgramVerify_C[];
extern const uint32 GetLock_C[];
extern const uint32 SetLock_C[];
extern const uint32 FlashDepletionRecover_C[];

extern const uint8 *FlashMemorySpace[];
#pragma pop

#else

extern const uint8  *FlashMemorySpace[];

extern const uint32 FlashInit_C[];
extern const uint32 FlashErase_C[];
extern const uint32 BlankCheck_C[];
extern const uint32 ProgramVerify_C[];
extern const uint32 GetLock_C[];
extern const uint32 SetLock_C[];
extern const uint32 FlashDepletionRecover_C[];

extern const uint32 FlashProgram_C[];

#endif  /* !__E200ZX_EXECUTE_FROM_RAM__ && EE_SSD_DRIVER_IN_RAM */


#define pFlashInit					((pFLASHINIT)FlashInit_C)
#define pFlashErase 				((pFLASHERASE)FlashErase_C)
#define pBlankCheck					((pBLANKCHECK)BlankCheck_C)
#define pFlashProgram  				((pFLASHPROGRAM)FlashProgram_C)
#define pProgramVerify 				((pPROGRAMVERIFY) ProgramVerify_C)
#define pGetLock       				((pGETLOCK)GetLock_C)
#define pSetLock        	 		((pSETLOCK)SetLock_C)
#define pCheckSum					((pCHECKSUM)CheckSum_C)
#define pFlashDepletionRecover		((pFLASHDEPLETIONRECOVER)FlashDepletionRecover_C)

#ifdef UNIT_TEST
    #undef pFlashInit					
    #undef pFlashErase 				
    #undef pBlankCheck					
    #undef pFlashProgram  				
    #undef pProgramVerify 				
    #undef pGetLock       				
    #undef pSetLock        	 		
    #undef pCheckSum					
    #undef pFlashDepletionRecover		
#endif

#define BLOCK_NOT_WRITABLE  0x0U
#define WRITABLE_BLOCK      0x1U

/* 
 * Start Address of n-th Block
 * n = 0: low space - block 0;
 * n = 1: low space - block 1;
 * n = 2: low space - block 2;
 * n = 3: low space - block 3;
 * n = 4: low space - block 4;
 * n = 5: low space - block 5;
 * n = 6: mid space - block 0;
 * n = 7: mid space - block 1;
 * n = 8: high space - block 0;
 * n = 9: high space - block 1.
 */
#define FLASH_BLOCK_START_ADDR(n)   (FlashMemorySpace[(n)])

#if !defined(__E200ZX_EXECUTE_FROM_RAM__) && defined (EE_SSD_DRIVER_IN_RAM)
#if defined(__VLE__)
 
#pragma push // save current pragma context
#pragma section code_type "SSD_Driver_code_vle" code_mode=far_abs

__declspec(section "SSD_Driver_code_vle")

StdReturnType FlashDrvInit(void);
StdReturnType FlashDrvDeinit(void);
StdReturnType FlashDrvInitCheck(void);
StdReturnType FlashWriteData(const uint8 * dest, const uint8 * source, const uint16 length);
StdReturnType FlashEraseBlocks(const uint8 * addr, const uint32 length);
StdReturnType FlashBlankCheck(const uint8 * addr, const uint32 length);
StdReturnType FlashDepletionRecovery(void);

#pragma pop //restore original pragma context
 
#else

#pragma push // save current pragma context
#pragma section code_type "SSD_Driver_code" code_mode=far_abs

__declspec(section "SSD_Driver_code")

StdReturnType FlashDrvInit(void) __attribute__((force_export));
StdReturnType FlashDrvDeinit(void) __attribute__((force_export));
StdReturnType FlashDrvInitCheck(void) __attribute__((force_export));
StdReturnType FlashWriteData(const uint8 * dest, const uint8 * source, const uint16 length) __attribute__((force_export));
StdReturnType FlashEraseBlocks(const uint8 * addr, const uint32 length) __attribute__((force_export));
StdReturnType FlashBlankCheck(const uint8 * addr, const uint32 length) __attribute__((force_export));
StdReturnType FlashDepletionRecovery(void);

#pragma pop //restore original pragma context

#endif	/* defined(__VLE__) */

#else   /* !__E200ZX_EXECUTE_FROM_RAM__ && EE_SSD_DRIVER_IN_RAM */

StdReturnType FlashDrvInit(void);
StdReturnType FlashDrvDeinit(void);
StdReturnType FlashDrvInitCheck(void);
StdReturnType FlashWriteData(const uint8 * dest, const uint8 * source, const uint16 length);
StdReturnType FlashEraseBlocks(const uint8 * addr, const uint32 length);
StdReturnType FlashBlankCheck(const uint8 * addr, const uint32 length);
StdReturnType FlashDepletionRecovery(void);

#endif  /* !__E200ZX_EXECUTE_FROM_RAM__ && EE_SSD_DRIVER_IN_RAM */

#endif  /* EE_MCU_MPC5643L_FLASH_H */

