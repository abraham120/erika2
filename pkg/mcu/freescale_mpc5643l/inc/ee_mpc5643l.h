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
 * MPC5643L register map
 *         2012 Francesco Esposito
 */

#ifndef EE_MCU_MPC5643L_H
#define EE_MCU_MPC5643L_H

/* ISO int types used by MPC5643L.h */
#define STDINT_SKIP_64BIT
#include <cpu/common/inc/ee_stdint.h>

#include "MPC5643L.h"

#define EE_E200ZX_MAX_EXT_IRQ 256U

#if (! defined EE_CURRENTCPU) || (EE_CURRENTCPU == 0)
/* INTC Base */
#define INTC_BASE 0xFFF48000

/* INTC_PSR Base */
#define INTC_PSR_BASE (INTC_BASE+0x40)

/* For duplicated registers, pick the Z4 instance */
#define INTC_CPR (INTC.CPR_PRC0)
#define INTC_IACKR (INTC.IACKR_PRC0)
#define INTC_EOIR (INTC.EOIR_PRC0)
/* This value is ignored in MPC5643L,
 * it is provided just to guarantee backward compatibility */
#define EE_E200ZX_INTC_CURRPROC 0x0U

#define SET_INT_PRIO(level, pri) \
			(*(volatile char *) (INTC_PSR_BASE+(level-16)))=pri

#else /* if EE_CURRENTCPU != 0 */
/* INTC Base */
#define INTC_BASE 0x8FF48000

/* INTC_PSR Base */
#define INTC_PSR_BASE (INTC_BASE+0x40)

/* For duplicated registers, pick the Z4 instance */
#define INTC_CPR (INTC_1.CPR_PRC0)
#define INTC_IACKR (INTC_1.IACKR_PRC0)
#define INTC_EOIR (INTC_1.EOIR_PRC0)
/* This value is ignored in MPC5643L,
 * it is provided just to guarantee backward compatibility */
#define EE_E200ZX_INTC_CURRPROC 0x0U

#define SET_INT_PRIO(level, pri) \
			(*(volatile char *) (INTC_PSR_BASE+(level-16)))=pri

#endif /* EE_CURRENTCPU */

#ifndef EE_ISR_DYNAMIC_TABLE
void EE_mpc5643_initialize_external_IRQ_priorities(void);
#endif /* __STATIC_ISR_TABLE__ */

__INLINE__ unsigned int EE_mpc5643l_lsm_or_dpm(void)
{
	/* return only the 9-th bit of UOPT, bit number 22 (32-9-1=22) */
	return (SSCM.UOPS.B.UOPT & 0x400000UL);
}

#define SEMA4_NUM   (16)  /* Number of semaphores available in SEMA4 */
#define SEMA4_1_NUM (16)  /* Number of semaphores available in SEMA4_1 */
#define SEM_NUM     (SEMA4_NUM + SEMA4_1_NUM)

__asm void EE_mpc5643l_initMMU(void);

#endif /* EE_MCU_MPC5643L_H */
