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

#include "cache.h"
#include "mcu/freescale_mpc5643l/inc/ee_mmu_mpc5643l.h"

#define MODULE_ID   (17)

extern unsigned int asmReadL1CSR1(void);
extern void asmWriteL1CSR1(unsigned int);

void CACHE_Enable2way(void)
{
	unsigned int u32Dummy = 0;

	//cache invalidation
	asmWriteL1CSR1(0x2);

	//wait the end of the invalidation process
	do {
	u32Dummy = asmReadL1CSR1();

	} while ( (u32Dummy & 0x2) == 1);

	//cache enable
	asmWriteL1CSR1(0x1);

	asm("isync");
}

void CACHE_Enable4way(void)
{
	unsigned int u32Dummy = 0;

	//cache invalidation
	asmWriteL1CSR1(0x2);

	//wait the end of the invalidation process
	do {
		u32Dummy = asmReadL1CSR1();
	} while ( (u32Dummy & 0x2) == 1);

	//cache enable
	asmWriteL1CSR1(0x11);

	asm("isync");
}

void CACHE_Disable(void)
{
	asmWriteL1CSR1(0x0);
	asm("isync");
}

asm void InitICache(void)
{
    nofralloc
    
/**************************************************************************
# FUNCTION     : cfg_CACHE                                                *
# PURPOSE      : This function initializes the CACHE, using L1CSR1        *
#                register.                                                *
#                SEQUENCE:                                                *
#                - Start Cache Invalidate                                 *
#                - Wait for invalidation to complete, check for Abort     *
#                  operation and restart invalidation if detected         *
#                - Enable Cache by setting CE bit                         *
#**************************************************************************/
cfg_CACHE:

    /*--------------------------------------------#
    # Invalidate - Set CINV                      #
    # bit in L1CSR1 Register                     #
    #--------------------------------------------*/
    lis   r5, 0x0000
    ori   r5, r5, 0x0002
    msync
    isync
    mtspr 0x3f3,r5

    /*-------------------------------------------#
    # Mask out CINV and CABT to see if           #
    # invalidation is complete (i.e. CINV=0,     #
    # CABT=0)                                    #
    #-------------------------------------------*/
label_CINV_check:
    /*-------------------------------------------#
    # Load Registers with Masks:                 #
    # Load CINV mask into R8                     #
    # Load CABT mask into R7                     #
    # Load CABT clear mask into R11              #
    #-------------------------------------------*/
    lis   r8, 0x0000
    ori   r8, r8, 0x0002
    lis   r7, 0x0000
    ori   r7, r7, 0x0004
    lis   r11, 0xFFFF
    ori   r11, r11, 0xFFFB
CHECK_CINV:

    /*-------------------------------------------#
    # Read SPR_L1CSR1 register, store in r9      #
    #-------------------------------------------*/
    mfspr r9, 0x3f3
    /*-------------------------------------------#
    # check for an ABORT of the cache invalidate #
    # operation                                  #
    #-------------------------------------------*/
    and.  r10, r7, r9
    beq   NO_ABORT
    /*-------------------------------------------#
    # If abort detected, clear CABT bit and      #
    # re-run invalidation                        #
    #-------------------------------------------*/
    and.  r10, r11, r9
    msync
    isync
    mtspr 0x3f3, r10
    b     cfg_CACHE

NO_ABORT:
    /*-------------------------------------------#
    # Check that invalidation has completed -    #
    # (CINV=0). Branch if invalidation not       #
    # complete.                                  #
    #-------------------------------------------*/
    and.  r10, r8, r9
    bne CHECK_CINV

    /*-------------------------------------------#
    # Enable cache by performing a               #
    # read/modify/write of the CE bit in the     #
    # SPR_L1CSR1 register                            #
    #-------------------------------------------*/
    mfspr r5, 0x3f3
    oris  r5, r5, 0x0000
    ori   r5, r5, 0x0001    /* Store SPR_L1CSR1 value to R5 (CE=1) */
    msync
    isync
    mtspr 0x3f3, r5        /* Write R5 to SPR_L1CSR1 register */

    blr
/**************************************************************************
# END OF cfg_CACHE                                                        *
#**************************************************************************/
}

asm void set_SRAM_as_cachable(void)
{
    fralloc

	/*
     * Notice that is much more prudent initialize a MMU entry
     * for SRAM area as first operation otherwise it has to be PROPERLY
     * initialized by the debugger if the application has to be executed
     * directly from SRAM
     */
    lis r3,TLB2_MAS0@h      /* SRAM area of core 0 */
    ori r3,r3,TLB2_MAS0@l
    lis r4,TLB2_MAS1@h
    ori r4,r4,TLB2_MAS1@l
    lis r5,(TLB2_MAS2 & ~0x00000008)@h
    ori r5,r5,(TLB2_MAS2 & ~0x00000008)@l
    lis r6,TLB2_MAS3@h
    ori r6,r6,TLB2_MAS3@l

    /* Write MMU Assist Register 0 (MAS0); SPR 624 */
    mtspr   624, r3
    /* Write MMU Assist Register 1 (MAS1); SPR 625 */
    mtspr   625, r4
    /* Write MMU Assist Register 2 (MAS2); SPR 626 */
    mtspr   626, r5
    /* Write MMU Assist Register 3 (MAS3); SPR 627 */
    mtspr   627, r6
    /* Write the table entry */
    tlbwe

#if !defined (LOCK_STEP)
    lis r3,TLB3_MAS0@h      /* SRAM area of core 1 */
    ori r3,r3,TLB3_MAS0@l
    lis r4,TLB3_MAS1@h
    ori r4,r4,TLB3_MAS1@l
    lis r5,(TLB3_MAS2 & ~0x00000008)@h
    ori r5,r5,(TLB3_MAS2 & ~0x00000008)@l
    lis r6,TLB3_MAS3@h
    ori r6,r6,TLB3_MAS3@l

    /* Write MMU Assist Register 0 (MAS0); SPR 624 */
    mtspr   624, r3
    /* Write MMU Assist Register 1 (MAS1); SPR 625 */
    mtspr   625, r4
    /* Write MMU Assist Register 2 (MAS2); SPR 626 */
    mtspr   626, r5
    /* Write MMU Assist Register 3 (MAS3); SPR 627 */
    mtspr   627, r6
    /* Write the table entry */
    tlbwe
#endif

    blr
}

asm void set_FLASH_as_cachable(void)
{
    lis r3,TLB0_MAS0@h      /* SRAM area of core 0 */
    ori r3,r3,TLB0_MAS0@l
    lis r4,TLB0_MAS1@h
    ori r4,r4,TLB0_MAS1@l
    lis r5,(TLB0_MAS2 & ~0x00000008)@h
    ori r5,r5,(TLB0_MAS2 & ~0x00000008)@l
    lis r6,TLB0_MAS3@h
    ori r6,r6,TLB0_MAS3@l

    /* Write MMU Assist Register 0 (MAS0); SPR 624 */
    mtspr   624, r3
    /* Write MMU Assist Register 1 (MAS1); SPR 625 */
    mtspr   625, r4
    /* Write MMU Assist Register 2 (MAS2); SPR 626 */
    mtspr   626, r5
    /* Write MMU Assist Register 3 (MAS3); SPR 627 */
    mtspr   627, r6
    /* Write the table entry */
    tlbwe

	blr
}

asm void set_SRAM_as_NOT_cachable(void)
{
    fralloc

	/*
     * Notice that is much more prudent initialize a MMU entry
     * for SRAM area as first operation otherwise it has to be PROPERLY
     * initialized by the debugger if the application has to be executed
     * directly from SRAM
     */
    lis r3,TLB2_MAS0@h      /* SRAM area of core 0 */
    ori r3,r3,TLB2_MAS0@l
    lis r4,TLB2_MAS1@h
    ori r4,r4,TLB2_MAS1@l
    lis r5,(TLB2_MAS2 | 0x00000008)@h
    ori r5,r5,(TLB2_MAS2 | 0x00000008)@l
    lis r6,TLB2_MAS3@h
    ori r6,r6,TLB2_MAS3@l

    /* Write MMU Assist Register 0 (MAS0); SPR 624 */
    mtspr   624, r3
    /* Write MMU Assist Register 1 (MAS1); SPR 625 */
    mtspr   625, r4
    /* Write MMU Assist Register 2 (MAS2); SPR 626 */
    mtspr   626, r5
    /* Write MMU Assist Register 3 (MAS3); SPR 627 */
    mtspr   627, r6
    /* Write the table entry */
    tlbwe

#if !defined (LOCK_STEP)
    lis r3,TLB3_MAS0@h      /* SRAM area of core 1 */
    ori r3,r3,TLB3_MAS0@l
    lis r4,TLB3_MAS1@h
    ori r4,r4,TLB3_MAS1@l
    lis r5,(TLB3_MAS2 | 0x00000008)@h
    ori r5,r5,(TLB3_MAS2 | 0x00000008)@l
    lis r6,TLB3_MAS3@h
    ori r6,r6,TLB3_MAS3@l

    /* Write MMU Assist Register 0 (MAS0); SPR 624 */
    mtspr   624, r3
    /* Write MMU Assist Register 1 (MAS1); SPR 625 */
    mtspr   625, r4
    /* Write MMU Assist Register 2 (MAS2); SPR 626 */
    mtspr   626, r5
    /* Write MMU Assist Register 3 (MAS3); SPR 627 */
    mtspr   627, r6
    /* Write the table entry */
    tlbwe
#endif

    blr
}

asm void set_FLASH_as_NOT_cachable(void)
{
    lis r3,TLB0_MAS0@h      /* SRAM area of core 0 */
    ori r3,r3,TLB0_MAS0@l
    lis r4,TLB0_MAS1@h
    ori r4,r4,TLB0_MAS1@l
    lis r5,(TLB0_MAS2 | 0x00000008)@h
    ori r5,r5,(TLB0_MAS2 | 0x00000008)@l
    lis r6,TLB0_MAS3@h
    ori r6,r6,TLB0_MAS3@l

    /* Write MMU Assist Register 0 (MAS0); SPR 624 */
    mtspr   624, r3
    /* Write MMU Assist Register 1 (MAS1); SPR 625 */
    mtspr   625, r4
    /* Write MMU Assist Register 2 (MAS2); SPR 626 */
    mtspr   626, r5
    /* Write MMU Assist Register 3 (MAS3); SPR 627 */
    mtspr   627, r6
    /* Write the table entry */
    tlbwe

	blr
}

