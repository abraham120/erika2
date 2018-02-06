/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * Author: 2012 Errico Guidieri
 */
#ifndef INCLUDE_E200ZX_IRQ_MEM_PROT_H__
#define INCLUDE_E200ZX_IRQ_MEM_PROT_H__

#ifdef __EE_MEMORY_PROTECTION__

#include "ee_irq.h"

/*
 * With memory protection ISR2 are somehow tricky: we need to execute them in
 * trusted/ untrusted mode according to the OS application they belong to, and
 * we must be able to terminate them if necessary. We use one ISR2 stack
 * per application and we maintain a stack of ISR2 descriptors to track
 * the active ISR2s. A complete implementation would use two stacks per
 * application: one for trusted and one for untrusted mode.
 */

/*
 * Pseudocode:
 * void ISR2_N_handler(void)
 * {
 *	EE_as_Application_RAM_type *from, *to;
 *	EE_as_ISR_RAM_type *tos;
 *	ApplicationType toid = N, fromid;
 *	EE_ADDR sp = get_sp();
 *
 *	fromid = EE_e200zx_get_application();
 *	to = &EE_as_Application_RAM[ISR_N_appid];
 *
 *	tos = &EE_as_ISR_stack[EE_IRQ_nesting_level++];
 *	tos->ISR = N;
 *
 *	if (EE_IRQ_nesting_level == 1) {
 *		EE_e200zx_ISR_stksave.sp = sp;
 *		EE_e200zx_ISR_stksave.appl = fromid;
 *		load_sp(to->ISRTOS);
 *	} else if (fromid != ISR2_N_appid) {
 *		from = &EE_as_Application_RAM[fromid];
 *		from->ISRTOS = sp;
 *		load_sp(to->ISRTOS);
 *	}
 *
 *	tos->TerminationTOS = sp;
 *
 *	EE_std_enableIRQ_nested();
 *	load_appid(ISR2_N_appid);
 *	load_mode(ISR2_N_appmode);
 *	call_handler();
 *	TerminateISR2();
 * }
 */

__asm void EE_ISR2_PROT_prestub(int toid, int isrid)
{

% reg toid, isrid; lab l1, l2
! "r6", "r7", "r8", "r9", "r10", "r11"

	.set noreorder
	addis	r6, 0, EE_as_Application_RAM@ha
	ori	r6, r6, EE_as_Application_RAM@l	# r6 <= EE_as_Application_RAM
	mr	r7, toid
	slwi	r7, r7, 4
	add	r8, r6, r7			# r8 <= to

	addis	r9, 0, EE_IRQ_nesting_level@ha
	ori	r9, r9, EE_IRQ_nesting_level@l
	lwz	r7, 0(r9)
	mr	r10, r7				# r10 <= EE_IRQ_nesting_level
	addi	r7, r7, 1
	stw	r7, 0(r9)

	addis	r11, 0, EE_as_ISR_stack@ha
	ori	r11, r11, EE_as_ISR_stack@l
	slwi	r7, r10, 3			# r7 <= r10 << 3
	add	r9, r11, r7			# r9 <= tos

	stw	isrid, 4(r9)			# tos->ISR_Terminated = 0 | ID

	mfpid0	r7				# r7 <= fromid

	cmpli	cr0, 0, r10, 0
	bne	l1

	addis	r11, 0, EE_e200zx_ISR_stksave@ha
	ori	r11, r11, EE_e200zx_ISR_stksave@l
	stw	sp, 0(r11)
	stw	r7, 4(r11)

	lwz	sp, 0(r8)			# sp <= to->ISRTOS
	b	l2
l1:
	cmpl	cr0, r7, toid
	beq	l2

	slwi	r7, r7, 4
	stwx	sp, r6, r7			# from->ISRTOS <= sp

	lwz	sp, 0(r8)			# sp <= to->ISRTOS
l2:
#if 0 /* Arbitrary TerminateIsr() not supported */
	stw	sp, (r9)			# tos->TerminationTOS <= sp
#endif
	/* `isync' is needed for pid0 update */
	isync
	mtpid0	toid				# switch app

	lwz	r0, 4(r8)			# r0 <= to->Mode
	mtmsr	r0				# switch appmode
	/* `isync' is needed for both pid0 and msr updates */
	isync
	.set reorder
}

__asm void EE_ISR2_PROT_poststub(void)
{
! "r0"
	li	r0, EE_ID_TerminateISR2
	sc
}

#ifdef EE_ISR_DYNAMIC_TABLE

#define ISR2(f)                                                 \
static void EE_PREPROC_JOIN(ISR2_,f)(void);                     \
void f(void)                                                    \
{                                                               \
  EE_ISR2_PROT_prestub(EE_PREPROC_JOIN(ISR2_APP_,f),            \
    EE_PREPROC_JOIN(ISR2_ID_,f));                               \
  EE_PREPROC_JOIN(ISR2_,f)();                                   \
  EE_ISR2_PROT_poststub();                                      \
}                                                               \
static void EE_PREPROC_JOIN(ISR2_,f)(void)

#else /* EE_ISR_DYNAMIC_TABLE */

#define ISR2(f)                                                       \
void EE_PREPROC_JOIN(ISR2_,f)(void);                                  \
void f(void)                                                          \
{                                                                     \
  /* keep the old ORTI */                                             \
  EE_ORTI_runningisr2_type ortiold;                                   \
  /* handle ORTI ID */                                                \
  ortiold = EE_ISR2_prestub(f);                                       \
  /* These handle stack change and nesting */                         \
  EE_ISR2_PROT_prestub(EE_PREPROC_JOIN(ISR2_APP_,f),                  \
    EE_PREPROC_JOIN(ISR2_ID_,f));                                     \
  EE_PREPROC_JOIN(ISR2_,f)();                                         \
  EE_ISR2_PROT_poststub();                                            \
  /* poststub do clean-up and scheduling and INTC PRIO pop */         \
  EE_ISR2_poststub(ortiold);                                          \
}                                                                     \
void EE_PREPROC_JOIN(ISR2_,f)(void)

#define ISR2_INT(f)                                                   \
void EE_PREPROC_JOIN(ISR2_INT_,f)(void);                              \
void f(void)                                                          \
{                                                                     \
  /* keep the old ORTI */                                             \
  EE_ORTI_runningisr2_type ortiold;                                   \
  /* Save the old ORTI ID */                                          \
  ortiold = EE_ISR2_prestub(f);                                       \
  /* These handle stack change and nesting */                         \
  EE_ISR2_PROT_prestub(EE_PREPROC_JOIN(ISR2_APP_,f),                  \
    EE_PREPROC_JOIN(ISR2_ID_,f));                                     \
  EE_PREPROC_JOIN(ISR2_INT_,f)();                                     \
  EE_ISR2_PROT_poststub();                                            \
  /* post-stub internal do clean-up and scheduling */                 \
  EE_ISR2_INT_poststub(ortiold);                                      \
}                                                                     \
void EE_PREPROC_JOIN(ISR2_INT_,f)(void)

/* TODO: Add support for ISR1 in static ISR table */
#endif /* EE_ISR_DYNAMIC_TABLE */

#endif /* __EE_MEMORY_PROTECTION__ */
#endif /* INCLUDE_E200ZX_IRQ_MEM_PROT_H__ */
