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
 * Dual-core interfacing code for MPC5643L
 * Author: 2011 Bernardo  Dal Seno
 *         2012 Francesco Esposito
 */

#ifndef EE_MCU_MPC5643L_DUAL_H
#define EE_MCU_MPC5643L_DUAL_H

#include "ee_mpc5643l.h"

#define VLE_MODE 0x2U
#define PPC_MODE 0x0U

/* First software IRQ used for interprocessor communication  */
#define EE_MPC5643L_INTER_IRQ_BASE 7
/* Position in VBA of the first interprocessor IRQ */
#define EE_MPC5643L_INTER_IRQ_VBA_BASE EE_MPC5643L_INTER_IRQ_BASE
/* Interprocessor IRQ vector number, from CPU id */
#define EE_MPC5643L_INTER_IRQ_LEVEL(cpu) \
	((EE_SREG)(cpu) + EE_MPC5643L_INTER_IRQ_VBA_BASE + 16)

/* Setup the intercore IRQs used by ERIKA for multicore support */
__INLINE__ void EE_mpc5643l_setup_inter_irqs(void)
{
	/*
	 * set INTC on master to receive interrupts from
	 * SW source interrupt number 7 (prio=1)
	 */
	INTC.PSR[EE_MPC5643L_INTER_IRQ_BASE].R = 0x1U;

	/*
	 * set INTC on slave to receive interrupts from
	 * SW source interrupt number 7 (prio=1)
	 */
	INTC_1.PSR[EE_MPC5643L_INTER_IRQ_BASE].R = 0x1U;
}

/* Signal the core `cpu' (0/1) by sending an IIRQ */
__INLINE__ void EE_mpc5643l_signal_cpu(EE_UINT8 cpu)
{
	if (cpu == 0) {
		INTC.SSCIR[EE_MPC5643L_INTER_IRQ_BASE].R = 2U;
	}
	else if (cpu == 1) {
		INTC_1.SSCIR[EE_MPC5643L_INTER_IRQ_BASE].R = 2U;
	}
    else {
        /* Ignore signal */
    }
}

/* Acknowledge the signal riceved by the core `cpu' (0/1) */
__INLINE__ void EE_mpc5643l_ack_signal(EE_UINT8 cpu)
{
	if (cpu == 0) {
		INTC.SSCIR[EE_MPC5643L_INTER_IRQ_BASE].R = 1U;
	}
	else if (cpu == 1) {
		INTC_1.SSCIR[EE_MPC5643L_INTER_IRQ_BASE].R = 1U;
	}
    else {
        /* Ignore ack */
    }
}

/* Acquire the spin lock `spin_id' */
__INLINE__ void EE_mpc5643l_spin_in(EE_TYPESPIN spin_id)
{
    volatile SEMA4_tag* SEM4_X = NULL;
    uint8_t index = spin_id;

	/* The same value as EE_CURRENTCPU can be obtained at run-time by
	 * reading from special register PIR (286) */
	uint8_t locked_val = (uint8_t)EE_CURRENTCPU;
	locked_val += (uint8_t)1U;

    if (SEM_NUM <= spin_id) {
        /* Not supported sempahore ID */
        return;
    }

    /* Decode Semaphore ID */
    if (SEMA4_NUM > spin_id) {
        SEM4_X = &SEMA4;
    }
    else {
        index = index - SEMA4_1_NUM;
        SEM4_X = &SEMA4_1;
    }

	do {
		SEM4_X->GATE[index].R = locked_val;
	} while (SEM4_X->GATE[index].R != locked_val);
}

/* Release the spin lock `spin_id' */
__INLINE__ void EE_mpc5643l_spin_out(EE_TYPESPIN spin_id)
{
    volatile SEMA4_tag* SEM4_X = NULL;
    uint8_t index = spin_id;

    if (SEM_NUM <= spin_id) {
        /* Not supported sempahore ID */
        return;
    }

    /* Decode Semaphore ID */
    if (SEMA4_NUM > spin_id) {
        SEM4_X = &SEMA4;
    }
    else {
        index = index - SEMA4_1_NUM;
        SEM4_X = &SEMA4_1;
    }

	SEM4_X->GATE[index].R = 0U;
}

/* Start slave core */
__INLINE__ void EE_mpc5643l_start_slave(volatile unsigned int start, unsigned int mode)
{
	/* Write the reset vector into DPMBOOT[P2BOOT] */
	SSCM.DPMBOOT.R = start;

	/* Set DPMBOOT[DVLE] to enable/disable VLE */
    if (mode == VLE_MODE) {
	    SSCM.DPMBOOT.R = SSCM.DPMBOOT.R | VLE_MODE;
    }

    /* Check if input mode is valid, otherwise skip starting slave core */
    if (mode != VLE_MODE || mode != PPC_MODE) {
	    SSCM.DPMKEY.R = 0x5AF0UL; /* First write */
	    SSCM.DPMKEY.R = 0xA50FUL; /* Second write */
    }

	/* Immediately after the second write slave core starts */
}

#endif /* EE_MCU_MPC5643L_DUAL_H */
