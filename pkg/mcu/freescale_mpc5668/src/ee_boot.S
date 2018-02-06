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
 * Boot code for the MPC5668 board.
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */

#include <eecfg.h>
#include <cpu/e200zx/inc/ee_regs.h>
#include <mcu/freescale_mpc5668/inc/ee_regs_asm.h>
#include <cpu/e200zx/inc/ee_cpu_asm.h>

	.extern	ee_load_ram, ee_sdata, ee_sbss, ee_ebss, sram_setup, main
	.extern EE_e200zx_mmu_entries, EE_e200zx_mmu_num_entries
	.extern ee_ssbss2, ee_esbss2
#ifndef EE_ISR_DYNAMIC_TABLE
	.extern EE_mpc5668_initialize_external_IRQ_priorities
#endif /* !EE_ISR_DYNAMIC_TABLE */

#ifdef __ASM_CONVERTED_TO_C__
int main(void);
void ee_start(void);
#ifndef EE_ISR_DYNAMIC_TABLE
void EE_mpc5668_initialize_external_IRQ_priorities(void);
#endif /* !EE_ISR_DYNAMIC_TABLE */
#endif /* __ASM_CONVERTED_TO_C__ */

#if ! defined(__E200ZX_EXECUTE_FROM_RAM__) && ! defined(__SLAVE_CPU__)
#ifdef __VLE__
#define BAM_RCHW 0x15a0000
#else
#define BAM_RCHW 0x05a0000
#endif
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
#endif /* ! __E200ZX_EXECUTE_FROM_RAM__ && ! __SLAVE_CPU__ */


	.extern	EE_e200zx_sys_stack
#define _stack0	(EE_e200zx_sys_stack + EE_SYS_STACK_SIZE - 16)

	.section .boot, , c

	/* CW-FUNC-DEFINITION: void ee_start(void) */
	.global	__start
	.type	__start, @function
__start:
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
	bl	EE_mpc5668_initialize_external_IRQ_priorities /* Init ext. irq prio */
#endif /* !EE_ISR_DYNAMIC_TABLE */
#endif /* !EE_ISR_EXTERNAL_TABLE */

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
	/* MCR = 0: VTES=0 (4 byte entries) HVEN=0 (SW vector mode) */
	li	r0, 0
	addis	r3, 0, INTC_MCR_ADDR@ha
#ifndef __SLAVE_CPU__
	stw	r0, INTC_MCR_ADDR@l(r3)
#endif

	/* init current priority */
	stw	r0, INTC_CPR_ADDR@l(r3)

	/* init vector table base address */
	addis	r4, 0, VTBA@ha
	addi	r4, r4, VTBA@l
	stw	r4, INTC_IACKR_ADDR@l(r3)

	blr
	.size	intc_setup, .-intc_setup
