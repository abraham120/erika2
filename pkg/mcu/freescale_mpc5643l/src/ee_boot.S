/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Boot code for the MPC5643L board.
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#include <eecfg.h>
#include <cpu/e200zx/inc/ee_regs.h>
#include <mcu/freescale_mpc5643l/inc/ee_regs_asm.h>
#include <cpu/e200zx/inc/ee_cpu_asm.h>

#define FLASH_REG CFLASH.PFCR0.R
#define FLASH_DATA 0x18C7EDED

	.extern	ee_load_ram, ee_sdata, ee_sbss, ee_ebss, sram_setup, main
	.extern EE_e200zx_mmu_entries, EE_e200zx_mmu_num_entries
	.extern ee_ssbss2, ee_esbss2

#ifndef EE_ISR_DYNAMIC_TABLE
	.extern EE_mpc5643_initialize_external_IRQ_priorities
#endif /* !EE_ISR_DYNAMIC_TABLE */

#ifdef __ASM_CONVERTED_TO_C__
int main(void);
void ee_start(void);
#if defined(MPC5643L_STD_SW_MMU_CONFIG)
void WriteMMUEntry(void);
void mmu_init_mpc5643l(void);
#include "mcu/freescale_mpc5643l/inc/ee_mmu_mpc5643l.h"
#endif /* defined(MPC5643L_STD_SW_MMU_CONFIG) */
#ifndef EE_ISR_DYNAMIC_TABLE
void EE_mpc5643l_initialize_external_IRQ_priorities(void);
#endif /* !EE_ISR_DYNAMIC_TABLE */
#endif

#if ! defined(__E200ZX_EXECUTE_FROM_RAM__) && ! defined(__SLAVE_CPU__)
#ifdef __VLE__
#define BAM_RCHW 0x15a0000
#else
#define BAM_RCHW 0x05a0000
#endif

#if !defined (EE_APP_NOT_BOOTABLE)
	/* CW-VAR-DEFINITION:
	#pragma section R ".boot_data"
	const struct { EE_UINT32 rchw; void (*start)(void); }
		EE_COMPILER_SECTION(".boot_data") bam_data =
		{ BAM_RCHW, ee_start };
	*/

	.section .boot_data
	.global	_bam_data
	.type	_bam_data, @object
_bam_data:
	.long	BAM_RCHW		/* BAM data */
	.long	__start
	.size	_bam_data, .-_bam_data
#endif /* !EE_APP_NOT_BOOTABLE */

#endif /* ! __E200ZX_EXECUTE_FROM_RAM__ && ! __SLAVE_CPU__ */


	.extern	EE_e200zx_sys_stack
#define _stack0	(EE_e200zx_sys_stack + EE_SYS_STACK_SIZE - 16)

	/* CW-FUNC-DEFINITION: void ee_start(void) */
	.global	__start
	.type	__start, @function
__start:
    bl  init_regs
#if defined(MPC5643L_STD_SW_MMU_CONFIG)
    /* To use standard MPC5643L MMU initialization */
    bl	mmu_init_mpc5643l
#endif  /* MPC5643L_STD_SW_MMU_CONFIG */

#ifndef __SLAVE_CPU__
	bl	sram_setup
	/* bl	pll_setup */
#endif /* __SLAVE_CPU__ */

	addis	r8, 0, _stack0@ha	/* setup the stack pointer */
	addi	sp, r8, _stack0@l

	addis	r8, 0, ee_load_ram@ha	/* load _load_ram into r8 */
	addi	r8, r8, ee_load_ram@l
	addis	r9, 0, ee_sbss@ha		/* load _sbss into r9 */
	addi	r9, r9, ee_sbss@l
	addis	r10, 0, ee_sdata@ha	/* load _sdata into r10 */
	addi	r10, r10, ee_sdata@l

	cmplw	cr0, r8, r10		/* check if we have to move data */
	beq	2f

	/* NOTE: the loops below assume that .data and .bss are not empty */
1:
	lwz	r11, 0(r8)		/* copy .data where it belongs */
	addi	r8, r8, 4
	stw	r11, 0(r10)
	addi	r10, r10, 4
	cmplw	cr0, r10, r9
	blt	1b
	msync							/* Grant that all the copies are consistently in ram. This
											 ensure consistency if some code has been moved in RAM */

2:
	addis	r8, 0, ee_ebss@ha		/* load _ebss into r8 (r9 is _sbss) */
	addi	r8, r8, ee_ebss@l
	li	r11, 0			/* load 0 in r11 */

1:
	stw	r11, 0(r9)		/* zero out the BSS */
	addi	r9, r9, 4
	cmplw	cr0, r9, r8
	blt	1b

	addis	r8, 0, ee_estack@ha	/* load _estack into r8 */
	addi	r8, r8, ee_estack@l
	addis	r9, 0, ee_sstack@ha	/* load _sstack into r9 */
	addi	r9, r9, ee_sstack@l
	addis	r11, 0, 0xa5a5a5a5@ha	/* load the fill pattern in r11 */
	addi	r11, r11, 0xa5a5a5a5@l

1:
	stw	r11, 0(r9)		/* fill the stacks */
	addi	r9, r9, 4
	cmplw	cr0, r9, r8
	blt	1b

#ifdef __E200ZX_EXECUTE_FROM_RAM__
	addis	r8, 0, ee_esbss2@ha	/* load ee_esbss2 into r8 */
	addi	r8, r8, ee_esbss2@l
	addis	r9, 0, ee_ssbss2@ha	/* load ee_ssbss2 into r9 */
	addi	r9, r9, ee_ssbss2@l
	li	r11, 0x0		/* load zero into r11 */
	cmplw	cr0, r8, r9 /* check if we have to zero out sbss2 */
	beq	2f

1:
	stw	r11, 0(r9)		/* fill sbss2 with zero */
	addi	r9, r9, 4
	cmplw	cr0, r9, r8
	blt	1b
2:
#endif

	addis	r13, 0, _SDA_BASE_@ha	/* load .sdata base into r13 */
	addi	r13, r13, _SDA_BASE_@l
	addis	r2, 0, _SDA2_BASE_@ha	/* load .sdata2 base into r2 */
	addi	r2, r2, _SDA2_BASE_@l

#if defined(__EE_CRT0_INIT_MMU__) && ! defined(__SLAVE_CPU__)
	/* mmu initialization */
	addis	r3, 0, EE_e200zx_mmu_entries@ha
	addi	r3, r3, EE_e200zx_mmu_entries@l
	addis	r4, 0, EE_e200zx_mmu_num_entries@ha
	addi	r4, r4, EE_e200zx_mmu_num_entries@l
	lwz	r4, 0(r4)
	bl	EE_e200zx_mmu_setup
#endif /* __EE_CRT0_INIT_MMU__ && ! __SLAVE_CPU__ */
	bl	cpu_setup		/* cpu-specific initialization */
#ifndef EE_ISR_EXTERNAL_TABLE /* the ISR table is implemented externally */
	bl	intc_setup		/* interrupt controller */
#ifndef EE_ISR_DYNAMIC_TABLE
	bl	EE_mpc5643_initialize_external_IRQ_priorities /* Init ext. irq prio */
#endif /* !EE_ISR_DYNAMIC_TABLE */
#endif /* !EE_ISR_EXTERNAL_TABLE */

#if !defined(__E200ZX_EXECUTE_FROM_RAM__)
    bl  FlashConfig
#endif
	bl	main			/* jump to application code */

	wrteei	0
1:
	b	1b
	.size	__start, .-__start


/*
 * external interrupt handlers (the first 16 entries are for cpu vectors)
 * to use the full hw support we should let the INTC handle the multiplexing,
 * since we have a common entry point, by now use it.
 */
/* #define VTBA		(16 * 4 + EE_e200z7_ISR_table) */
/* VTBA = 0 -> Only offsets are read from INTC_IACKR_PRC */
#define VTBA	0

	/* CW-FUNC-DEFINITION: static void intc_setup(void) */
	.type	intc_setup, @function
intc_setup:
	/* BCR = 0: VTES=0 (4 byte entries) HVEN=0 (SW vector mode) */
	li	r0, 0
	addis	r3, 0, INTC_BCR_ADDR@ha
#ifndef __SLAVE_CPU__
	stw	r0, INTC_BCR_ADDR@l(r3)
#endif

	/* init current priority */
	stw	r0, INTC_CPR_ADDR@l(r3)

	/* init vector table base address */
	addis	r4, 0, VTBA@ha
	addi	r4, r4, VTBA@l
	stw	r4, INTC_IACKR_ADDR@l(r3)

	blr
	.size	intc_setup, .-intc_setup

#if defined(MPC5643L_STD_SW_MMU_CONFIG)
    /* CW-FUNC-DEFINITION: static void mmu_init_mpc5643l(void) */
	.type	mmu_init_mpc5643l, @function
mmu_init_mpc5643l:

    mflr     r27

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
    lis r5,TLB2_MAS2@h
    ori r5,r5,TLB2_MAS2@l
    lis r6,TLB2_MAS3@h
    ori r6,r6,TLB2_MAS3@l
    bl WriteMMUEntry

#if !defined (LOCK_STEP)
    lis r3,TLB3_MAS0@h      /* SRAM area of core 1 */
    ori r3,r3,TLB3_MAS0@l
    lis r4,TLB3_MAS1@h
    ori r4,r4,TLB3_MAS1@l
    lis r5,TLB3_MAS2@h
    ori r5,r5,TLB3_MAS2@l
    lis r6,TLB3_MAS3@h
    ori r6,r6,TLB3_MAS3@l
    bl WriteMMUEntry
#endif

	lis r3,TLB0_MAS0@h
    ori r3,r3,TLB0_MAS0@l
    lis r4,TLB0_MAS1@h
    ori r4,r4,TLB0_MAS1@l
    lis r5,TLB0_MAS2@h
    ori r5,r5,TLB0_MAS2@l
    lis r6,TLB0_MAS3@h
    ori r6,r6,TLB0_MAS3@l
    bl WriteMMUEntry

    lis r3,TLB1_MAS0@h
    ori r3,r3,TLB1_MAS0@l
    lis r4,TLB1_MAS1@h
    ori r4,r4,TLB1_MAS1@l
    lis r5,TLB1_MAS2@h
    ori r5,r5,TLB1_MAS2@l
    lis r6,TLB1_MAS3@h
    ori r6,r6,TLB1_MAS3@l
    bl WriteMMUEntry

    lis r3,TLB4_MAS0@h
    ori r3,r3,TLB4_MAS0@l
    lis r4,TLB4_MAS1@h
    ori r4,r4,TLB4_MAS1@l
    lis r5,TLB4_MAS2@h
    ori r5,r5,TLB4_MAS2@l
    lis r6,TLB4_MAS3@h
    ori r6,r6,TLB4_MAS3@l
    bl WriteMMUEntry

    lis r3,TLB5_MAS0@h
    ori r3,r3,TLB5_MAS0@l
    lis r4,TLB5_MAS1@h
    ori r4,r4,TLB5_MAS1@l
    lis r5,TLB5_MAS2@h
    ori r5,r5,TLB5_MAS2@l
    lis r6,TLB5_MAS3@h
    ori r6,r6,TLB5_MAS3@l
    bl WriteMMUEntry

    lis r3,TLB6_MAS0@h
    ori r3,r3,TLB6_MAS0@l
    lis r4,TLB6_MAS1@h
    ori r4,r4,TLB6_MAS1@l
    lis r5,TLB6_MAS2@h
    ori r5,r5,TLB6_MAS2@l
    lis r6,TLB6_MAS3@h
    ori r6,r6,TLB6_MAS3@l
    bl WriteMMUEntry

    lis r3,TLB7_MAS0@h
    ori r3,r3,TLB7_MAS0@l
    lis r4,TLB7_MAS1@h
    ori r4,r4,TLB7_MAS1@l
    lis r5,TLB7_MAS2@h
    ori r5,r5,TLB7_MAS2@l
    lis r6,TLB7_MAS3@h
    ori r6,r6,TLB7_MAS3@l
    bl WriteMMUEntry

    lis r3,TLB8_MAS0@h
    ori r3,r3,TLB8_MAS0@l
    lis r4,TLB8_MAS1@h
    ori r4,r4,TLB8_MAS1@l
    lis r5,TLB8_MAS2@h
    ori r5,r5,TLB8_MAS2@l
    lis r6,TLB8_MAS3@h
    ori r6,r6,TLB8_MAS3@l
    bl WriteMMUEntry

    lis r3,TLB9_MAS0@h
    ori r3,r3,TLB9_MAS0@l
    lis r4,TLB9_MAS1@h
    ori r4,r4,TLB9_MAS1@l
    lis r5,TLB9_MAS2@h
    ori r5,r5,TLB9_MAS2@l
    lis r6,TLB9_MAS3@h
    ori r6,r6,TLB9_MAS3@l
    bl WriteMMUEntry

    mtlr r27

	blr

	.size	mmu_init_mpc5643l, .-mmu_init_mpc5643l

    /* CW-FUNC-DEFINITION: static void WriteMMUEntry(void) */
	.type	WriteMMUEntry, @function
WriteMMUEntry:
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
	.size	WriteMMUEntry, .-WriteMMUEntry
#endif /* defined(MPC5643L_STD_SW_MMU_CONFIG) */

/* CW-FUNC-DEFINITION: static void init_regs(void) */
	.type	init_regs, @function
init_regs:

    lis r6,0x200
	ori r6,r6,0x0
	mtmsr r6
	isync

	xor  r0, r0, r0
	evmergelo r0,r0,r0

	evmergelo r1,r0,r1 //used by runtime - should preserve lower 32bits
	evmergelo r2,r0,r2 //used by runtime - should preserve lower 32bits
	evmergelo r3,r0,r3 //used by runtime - should preserve lower 32bits
	
	evmergelo r4,r0,r0
	evmergelo r5,r0,r0
	evmergelo r6,r0,r0
	evmergelo r7,r0,r0
	evmergelo r8,r0,r0
	evmergelo r9,r0,r0
	evmergelo r10,r0,r0
	evmergelo r11,r0,r0
	evmergelo r12,r0,r0
	
	evmergelo r13,r0,r13 //used by runtime - should preserve lower 32bits

	evmergelo r14,r0,r0
	evmergelo r15,r0,r0
	evmergelo r16,r0,r0
	evmergelo r17,r0,r0
	evmergelo r18,r0,r0
	evmergelo r19,r0,r0
	evmergelo r20,r0,r0
	evmergelo r21,r0,r0
	evmergelo r22,r0,r0
	evmergelo r23,r0,r0
	evmergelo r24,r0,r0
	evmergelo r25,r0,r0
	evmergelo r26,r0,r0
	evmergelo r27,r0,r0
	evmergelo r28,r0,r0
	evmergelo r29,r0,r0
	
	evmergelo r30,r0,r30 //used by runtime - should preserve lower 32bits
	evmergelo r31,r0,r31 //used by runtime - should preserve lower 32bits

	// 2.  32-bit DEAR (spr 61)
	mtspr 61,r0         //DEAR

	//3.  32-bit SPRG0-9 (spr 272-279, 604 & 605)

	mtspr 272,r0        //SPRG0-7
	mtspr 273,r0
	mtspr 274,r0
	mtspr 275,r0
	mtspr 276,r0
	mtspr 277,r0
	mtspr 278,r0
	mtspr 279,r0

	mtspr 604,r0         //SPRG8-9
	mtspr 605,r0

	//4.  32-bit USPRG0 (spr 256)

	mtspr 256,r0         //USPRG0

	//5.  32-bit SRR0 (spr 26), SRR1 (spr 27), CSRR0 (spr58), CSRR1 (spr59),
	//		DSRR0 (spr 574), DSRR1 (spr 575), MCSRR0 (spr570), MCSRR1 (spr571)

	mtspr 26,r0          //SRR0-1
	mtspr 27,r0
	mtspr 58,r0          //CSRR0-1
	mtspr 59,r0
	mtspr 570,r0         //MCSRR0-1
	mtspr 571,r0 
	mtspr 574,r0         //DSRR0-1 
	mtspr 575,r0      
    
	//6.  32-bit IVPR (spr 63)

	mtspr 63,r0          //IVPR
	mtspr 62,r0          //ESR
	mtspr 340,r0         //TCR
	mtspr 512,r0         //SPEFSCR
	mtspr 1,r0           //XER
	mtspr 256,r0         //USPRG0 
 

	//32-bit IVOR0-15 (spr 400 - 415), IVOR 32-35 (spr 528 - 531)

	mtspr 400,r0         //IVOR0-15
	mtspr 401,r0
	mtspr 402,r0
	mtspr 403,r0   
	mtspr 404,r0
	mtspr 405,r0
	mtspr 406,r0
	mtspr 407,r0
	mtspr 408,r0
	mtspr 409,r0
	mtspr 410,r0
	mtspr 411,r0
	mtspr 412,r0
	mtspr 413,r0
	mtspr 414,r0
	mtspr 415,r0

	mtspr 528,r0         //IVOR32-34 (IVOR35 not in Leopard)
	mtspr 529,r0
	mtspr 530,r0
	
	//mtspr 531,r0		 //IVOR35 KOMODO ONLY

	//8.  32-bit MCAR (spr 573)

	mtspr 573,r0         //MCAR
 
	//9. 32-bit TBL, TBU (spr 284, 285)

	mtspr 284,r0         //TBL
	mtspr 285,r0         //TBU
 
	//10. 32-bit DEC, DECAR (spr 22, 54)

	mtspr 22,r0          //DEC
	mtspr 54,r0          //DECAR

	//11. 64-bit DVC1, DVC2 (spr 318, 319)
	//Note most debug registers are reset by POR so initialization is not required.

	mtspr 318,r0         //DVC1
	mtspr 319,r0         //DVC2

	//12. 32-bit DBCNT (spr 562)

	mtspr 562,r0         //DBCNT
	
	// initialize MAS0 - MAS6; actual TLB configuration done later
	mtmas0 r0
	mtmas1 r0
	mtmas2 r0
	mtmas3 r0
	mtmas4 r0
	// no MAS5
	mtmas6 r0
	
	// init ACC
	evmra r0, r4
	evmra r0, r4
	
	mtcrf 0xFF,r0 // CFR
	mtspr 9,r0 // COUNT

    blr

.size	init_regs, .-init_regs

