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

/**
    @file     ee_timer.c
    @brief    TIMER library source file for Nordic NRF51x22.\n
    @author   Alessandro Biondi
    @date     2013
    @example

*/

#include <ee_irq.h>
#include "mcu/nordic_nrf51x22/inc/ee_timer.h"

/* Following API make sense only if alarms are defined */
#if defined(__ALARMS__) || ( ( defined(__OO_BCC1__) || defined( __OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__) ) && !defined(__OO_NO_ALARMS__) )

#ifndef __NORDIC_S110_BLE__ 
static void EE_timer0_set_callback(EE_ISR_callback func);
#endif
static void EE_timer1_set_callback(EE_ISR_callback func);
static void EE_timer2_set_callback(EE_ISR_callback func);

static volatile CounterType counter_timer0 = 0;
static volatile CounterType counter_timer1 = 0;
static volatile CounterType counter_timer2 = 0;

/*
 * Callback of Timer0. Used to increment OSEK counter "counter_timer0";
 */
static void EE_timer0_tick_routine(void)
{
    IncrementCounter(counter_timer0);
}

/*
 * Callback of Timer1. Used to increment OSEK counter "counter_timer1";
 */
static void EE_timer1_tick_routine(void)
{
    IncrementCounter(counter_timer1);
}

/*
 * Callback of Timer2. Used to increment OSEK counter "counter_timer2";
 */
static void EE_timer2_tick_routine(void)
{
    IncrementCounter(counter_timer2);
}

static volatile EE_ISR_callback t0_cbk = EE_timer0_tick_routine;
static volatile EE_ISR_callback t1_cbk = EE_timer1_tick_routine;
static volatile EE_ISR_callback t2_cbk = EE_timer2_tick_routine;

EE_INT8 EE_timer_set_counter(EE_TimerId id, CounterType counterId)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id){
        case EE_TIMER_0:
			#ifndef __NORDIC_S110_BLE__
            EE_timer0_set_callback(EE_timer0_tick_routine);
            counter_timer0 = counterId;
			#else
			error = EE_TIMER_ERR_BAD_ARGS;
			#endif
        break;
        case EE_TIMER_1:
            EE_timer1_set_callback(EE_timer1_tick_routine);
            counter_timer1 = counterId;
        break;
        case EE_TIMER_2:
            EE_timer2_set_callback(EE_timer2_tick_routine);
            counter_timer2 = counterId;
        break;
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}
#else
#define EE_timer0_tick_routine NULL
#define EE_timer1_tick_routine NULL
#define EE_timer2_tick_routine NULL

static volatile EE_ISR_callback t0_cbk;
static volatile EE_ISR_callback t1_cbk;
static volatile EE_ISR_callback t2_cbk;
#endif /* defined(__ALARMS__) || ( defined(__OO_BCC1__) || defined( __OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__) && !defined(__OO_NO_ALARMS__) ) */

//------------------------------------------------------------------

#ifndef __NORDIC_S110_BLE__
static void EE_timer0_set_callback(EE_ISR_callback func)
{
    t0_cbk = func;
}
#endif

static void EE_timer1_set_callback(EE_ISR_callback func)
{
    t1_cbk = func;
}

static void EE_timer2_set_callback(EE_ISR_callback func)
{
    t2_cbk = func;
}

//------------------------------------------------------------------

ISR2 (EE_Timer0_IRQHandler)
{
    /* Clear Interrupt */
	NRF_TIMER0->EVENTS_COMPARE[EE_DEFAULT_CC_REG] = 0;            
    if(t1_cbk != 0)
        t1_cbk();
}

ISR2 (EE_Timer1_IRQHandler)
{
    /* Clear Interrupt */
	NRF_TIMER1->EVENTS_COMPARE[EE_DEFAULT_CC_REG] = 0;            
    if(t1_cbk != 0)
        t1_cbk();
}

ISR2(EE_Timer2_IRQHandler)
{
    /* Clear Interrupt */
	NRF_TIMER2->EVENTS_COMPARE[EE_DEFAULT_CC_REG] = 0;            
    if(t2_cbk != 0)
        t2_cbk();
}

//------------------------------------------------------------------

EE_INT8 EE_timer_hard_init(EE_TimerId id, EE_UINT32 period, EE_TimerPrescaleFactor ps, EE_TimerBitMode bitmode){

    EE_INT8 error = EE_TIMER_NO_ERRORS;
	volatile NRF_TIMER_Type * p_timer = 0;
	volatile IRQn_Type IRQn;
	
    switch(id)
	{
		case EE_TIMER_0:
            p_timer = NRF_TIMER0;
			IRQn	= TIMER0_IRQn;
			if(bitmode>EE_TIMER_BITMODE_32)
				/* Timer 0 has 32-bit as maximum bitmode */
				error = EE_TIMER_ERR_BAD_ARGS;
        break;
        case EE_TIMER_1:
            p_timer = NRF_TIMER1;
			IRQn	= TIMER1_IRQn;
			if(bitmode>EE_TIMER_BITMODE_16) 
				error = EE_TIMER_ERR_BAD_ARGS;
        break;
        case EE_TIMER_2:
            p_timer = NRF_TIMER2;
			IRQn	= TIMER2_IRQn;
			if(bitmode>EE_TIMER_BITMODE_16) 
				error = EE_TIMER_ERR_BAD_ARGS;
        break;
   
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
	
	if(ps>EE_MAX_PRESCALE_FACTOR) 
		error = EE_TIMER_ERR_BAD_ARGS;
	
	if(!error)
	{
		p_timer->MODE 			= TIMER_MODE_MODE_Timer; 		/* Set the timer in Timer Mode */
		p_timer->PRESCALER		= ps;							/* Set prescale factor */
		p_timer->BITMODE 		= bitmode;						/* Set timer bitmode */
		p_timer->TASKS_CLEAR 	= 1;         			        /* Clear the task first to be usable for later */
		p_timer->CC[EE_DEFAULT_CC_REG] = period;				/* Set period */
		p_timer->INTENSET 			   = (EE_DEFAULT_CC_ENABLE << EE_DEFAULT_CC_POS);
	
		NVIC_ClearPendingIRQ(IRQn);
		NVIC_EnableIRQ(IRQn);
	}
	
    return error;
}

//------------------------------------------------------------------

EE_INT8 EE_timer_soft_init(EE_TimerId id, EE_UINT32 period_us)
{
    EE_INT8   error    	= EE_TIMER_NO_ERRORS;
    EE_UINT32 baseFreq 	= EE_get_system_clock();
    EE_UINT32 ticks		= MICROSECONDS_TO_TICKS(period_us, baseFreq);

    
    EE_UINT16 prd; /* Period */
    EE_TimerPrescaleFactor  psc; /* Prescale */
	
	/* Timer 1-2 has 16-bit as maximum bitmode */
	EE_TimerBitMode bitmode = EE_TIMER_BITMODE_16; 
	EE_UINT32 max_period = 0xffffUL; 
	
	/* In soft init we use the maximum bitmode */
	if(id==EE_TIMER_0) { 
		/* Timer 0 has 32-bit as maximum bitmode */
		max_period = 0xffffffffUL; 
		bitmode = EE_TIMER_BITMODE_32;
	}
		
    if (ticks < max_period) {
        prd = ticks;
        psc = EE_TIMER_PS1;
    } else if (ticks / 2 < max_period) {
        prd = ticks / 2;
        psc = EE_TIMER_PS2;
    } else if (ticks / 4 < max_period) {
        prd = ticks / 4;
        psc = EE_TIMER_PS4;
    } else if (ticks / 8 < max_period) {
        prd = ticks / 8;
        psc = EE_TIMER_PS8;
    } else if (ticks / 16 < max_period) {
        prd = ticks / 16;
        psc = EE_TIMER_PS16;
    } else if (ticks / 16 < max_period) {
        prd = ticks / 16;
        psc = EE_TIMER_PS32;
    } else if (ticks / 32 < max_period) {
        prd = ticks / 32;
        psc = EE_TIMER_PS32;
    } else if (ticks / 64 < max_period) {
        prd = ticks / 64;
        psc = EE_TIMER_PS64;
    } else if (ticks / 128 < max_period) {
        prd = ticks / 128;
        psc = EE_TIMER_PS128;
	} else if (ticks / 256 < max_period) {
        prd = ticks / 256;
        psc = EE_TIMER_PS256;	
    } else if (ticks / 512 < max_period) {
        prd = ticks / 512;
        psc = EE_TIMER_PS512;
    } 
	else {
        error = EE_TIMER_ERR_BAD_ARGS;
    }
    if(!error) {
		
		error = EE_timer_hard_init(id, prd, psc, bitmode);
	}
    return error;
}

//------------------------------------------------------------------

EE_INT8 EE_timer_set_callback(EE_TimerId id, EE_ISR_callback func)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id)
	{
        case EE_TIMER_0:
		    #ifndef __NORDIC_S110_BLE__
            if(func == NULL)
                EE_timer0_set_callback(EE_timer0_tick_routine);
            else
                EE_timer0_set_callback(func);
			#else
			error = EE_TIMER_ERR_BAD_ARGS;
			#endif
        break;
		case EE_TIMER_1:
            if(func == NULL)
                EE_timer1_set_callback(EE_timer1_tick_routine);
            else
                EE_timer1_set_callback(func);
        break;
        case EE_TIMER_2:
            if(func == NULL)
                EE_timer2_set_callback(EE_timer2_tick_routine);
            else
                EE_timer2_set_callback(func);
        break;
        
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}

//------------------------------------------------------------------

EE_INT8 EE_timer_start(EE_TimerId id)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id)
	{
        case EE_TIMER_0:
            NRF_TIMER0->TASKS_START = 1;
        break;
		case EE_TIMER_1:
            NRF_TIMER1->TASKS_START = 1;
        break;
        case EE_TIMER_2:
            NRF_TIMER2->TASKS_START = 1;
        break;
        
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}

//------------------------------------------------------------------

EE_INT8 EE_timer_stop(EE_TimerId id)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id)
	{
        case EE_TIMER_0:
            NRF_TIMER0->TASKS_STOP = 1;
        break;
		case EE_TIMER_1:
            NRF_TIMER1->TASKS_STOP = 1;
        break;
        case EE_TIMER_2:
            NRF_TIMER2->TASKS_STOP = 1;
        break;
		
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}
