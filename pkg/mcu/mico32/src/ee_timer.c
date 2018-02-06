/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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

/** 
	@file ee_timer.c
	@brief Timer library source file. 
	@author Dario Di Stefano
	@date 2010
*/
#include <ee_irq.h>
#include "mcu/mico32/inc/ee_timer.h"

/******************************************************************************/
/*                              Global Functions                              */
/******************************************************************************/
#ifdef __USE_TIMER_IRQ__
/* Vectors and uart structures definitions */
#ifdef EE_TIMER1_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC)
#endif

#ifdef EE_TIMER2_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC)
#endif

#ifdef EE_TIMER3_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER3_NAME_UC, EE_TIMER3_NAME_LC)
#endif

#ifdef EE_TIMER4_NAME_UC
DEFINE_STRUCT_TIMER(EE_TIMER4_NAME_UC, EE_TIMER4_NAME_LC)
#endif
#endif /* #ifdef __USE_TIMER_IRQ__ */

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#ifdef __USE_TIMER_IRQ__

/* Timer driver common handler */
void EE_timer_common_handler(int level)
{
    EE_timer_st *tstp = EE_get_timer_st_from_level(level);
    MicoTimer_t *timerc = tstp->base;
    
	/* acknowledge the interrupt */
	timerc->Status = 0;
	
	/* body of the ISR callback... */
	if(tstp->cbk != EE_NULL_CBK)
        tstp->cbk();

	// All done!!!
	return;	
}
#endif /* #ifdef __USE_TIMER_IRQ__ */

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

#ifdef __USE_TIMER_IRQ__

/* This function initializes the timer */
int EE_hal_timer_init(EE_timer_st* tst, int period, int settings)
{
	MicoTimer_t *timerc = tst->base;
	
	/* Stop the timer */
	timerc->Control = MICO32_TIMER_CONTROL_STOP_BIT_MASK;
	
	/* acknowledge the interrupt */
	timerc->Status = 0;
	
	/* Register the handler */
	EE_hal_timer_handler_setup(tst);
	if(EE_timer_need_enable_int(settings))
		mico32_enable_irq(tst->irqf);
	else
		mico32_disable_irq(tst->irqf);
	
	/* Set the period */
	timerc->Period = period;	// timer period
	
	/* Set the control register */
	timerc->Control = settings;
	
	/* ISR management */
	return EE_TIMER_OK;

}

#else

/* This function initializes the timer */
int EE_hal_timer_init(MicoTimer_t* timerc, int irqf, int period, int settings)
{
	/* Stop the timer */
	timerc->Control = MICO32_TIMER_CONTROL_STOP_BIT_MASK;
	
	/* acknowledge the interrupt */
	timerc->Status = 0;
	
	mico32_disable_irq(irqf);
	
	/* Set the period */
	timerc->Period = period;	// timer period
	
	/* Set the control register */
	timerc->Control = settings;
	
	/* ISR management */
	return EE_TIMER_OK;

}

#endif /* #ifdef __USE_TIMER_IRQ__ */
