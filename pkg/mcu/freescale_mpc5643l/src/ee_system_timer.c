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
 * Author: 2013  Francesco Esposito
 */

#include <ee_internal.h>
#include <ee_api.h>
#include <ee_irq.h>

/* This file is needed only if System Timer is defined with a device */
#if defined(ENABLE_SYSTEM_TIMER) && defined(EE_SYSTEM_TIMER_DEVICE)

/* STM identifier */
#define EE_MPC5643L_STM 1
/* Add here additional identifiers if a system timer other
then STM is required */

#if defined (__MSRP__) && defined (__SLAVE_CPU__)
/* In multicore case remap to the second STM device */
#define GENERIC_STM STM_1
#else
#define GENERIC_STM STM
#endif

/* Used for compiler error */
#define PREPROC(s) s

/* Handler Declaration */
void EE_mpc5643l_system_timer_handler(void);

#ifdef EE_ISR_DYNAMIC_TABLE
void EE_mpc5643l_system_timer_handler(void)
#else
ISR2(EE_mpc5643l_system_timer_handler)
#endif
{
    /* Reset initial value */
    GENERIC_STM.CNT.R = 0U;

    /* Clear ISR */
    GENERIC_STM.CIR0.B.CIF = 1U;

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || \
    defined(__OO_ECC2__) || defined(__AS_SC4__)
    IncrementCounterHardware(EE_SYSTEM_TIMER);
#else
    CounterTick(EE_SYSTEM_TIMER);
#endif
}

/* System Timer Initialization */
void EE_initialize_system_timer(void)
{
#if defined (DEBUG)
    /* Enable freeze mode during debug */
    GENERIC_STM.CR.B.FRZ = 1U;
#endif

    /* Set prescaler */
    GENERIC_STM.CR.B.CPS = 0U;

    /* Enable channel 0 */
    GENERIC_STM.CCR0.B.CEN = 1U;

    /* Set initial vaue */
    GENERIC_STM.CNT.R = 0U;

#ifdef EE_ISR_DYNAMIC_TABLE
    /* STM channel 0 isr is the 46-th isr source. Lowest priority == 1 */
    EE_e200z7_register_ISR(46, EE_mpc5643l_system_timer_handler, 1);
#endif /* EE_ISR_DYNAMIC_TABLE */

#if (EE_SYSTEM_TIMER_DEVICE == EE_MPC5643L_STM)
    /* OSTICKDURATION is defined as nanoseconds macro */
    GENERIC_STM.CMP0.R = ((EE_CPU_CLOCK + (OSTICKDURATION / 2000U)) /
        (OSTICKDURATION / 1000U)); /* Set match value for channel 0 */
#else
#error Unsupported Device: PREPROC(EE_SYSTEM_TIMER_DEVICE) as\
    System Timer!
#endif

    /* Start Timer */
    GENERIC_STM.CR.B.TEN = 1U;
}

#endif /* ENABLE_SYSTEM_TIMER && EE_SYSTEM_TIMER_DEVICE */

