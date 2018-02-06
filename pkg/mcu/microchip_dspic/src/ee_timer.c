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
    @brief     TIMER library source file.\n
    @author Errico Guidieri
    @date     2011
    @example

*/

#include "ee.h"
#include "ee_irq.h"
#include "mcu/microchip_dspic/inc/ee_timer.h"
#include "mcu/microchip_dspic/inc/ee_utils.h"


/* Following API make sense only if alarms are defined */
#if defined(__ALARMS__) || ( ( defined(__OO_BCC1__) || defined( __OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__) ) && !defined(__OO_NO_ALARMS__) )

static void EE_timer1_set_callback(EE_ISR_callback func);
static void EE_timer2_set_callback(EE_ISR_callback func);

static volatile CounterType counter_timer1 = 0;
static volatile CounterType counter_timer2 = 0;
/*
 * Callback of Timer1. Used to increment OSEK counter "counter_timer1";
 */
static void EE_timer1_tick_routine(void)
{
    IncrementCounter(counter_timer1);
}

/*
 * Callback of Timer1. Used to increment OSEK counter "counter_timer2";
 */
static void EE_timer2_tick_routine(void)
{
    IncrementCounter(counter_timer2);
}

static volatile EE_ISR_callback t1_cbk = EE_timer1_tick_routine;
static volatile EE_ISR_callback t2_cbk = EE_timer2_tick_routine;

EE_INT8 EE_timer_set_counter(EE_TimerId id, CounterType counterId)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id){
        case EE_TIMER_1:
            EE_timer1_set_callback(EE_timer1_tick_routine);
            counter_timer1 = counterId;
        break;
        case EE_TIMER_2:
            EE_timer2_set_callback(EE_timer2_tick_routine);
            counter_timer2 = counterId;
        break;
        case EE_TIMER_3:
        case EE_TIMER_23:
            /* TODO implement those timers at least */
            error = EE_TIMER_ERR_UNIMPLEMENTED;
        break;
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}
#else
#define EE_timer1_tick_routine NULL
#define EE_timer2_tick_routine NULL

static volatile EE_ISR_callback t1_cbk;
static volatile EE_ISR_callback t2_cbk;
#endif /* defined(__ALARMS__) || ( defined(__OO_BCC1__) || defined( __OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__) && !defined(__OO_NO_ALARMS__) ) */

static void EE_timer1_init(EE_UINT16 t1_period, EE_TimerPrescaleFactor ps)
{
    T1CON = 0;                      /* ensure Timer 1 is in reset state */
    IFS0bits.T1IF = 0;              /* reset Timer 1 interrupt flag */
    IPC0bits.T1IP = 5;              /* set Timer1 interrupt priority level to 5 */
    IEC0bits.T1IE = 1;              /* enable Timer 1 interrupt */
    T1CONbits.TCS = 0;              /* select external timer clock */
    T1CONbits.TGATE = 0;            /* Gated time accumulation disabled */
    TMR1 = 0x00;                    /* Clear timer register */
    PR1 = t1_period;                /* set Timer 1 period register */
    T1CONbits.TCKPS = ps;           /* select Timer1 Input Clock Prescale */
}

static void EE_timer1_start()
{
    IFS0bits.T1IF = 0;              /* reset Timer 1 interrupt flag */
    T1CONbits.TON = 1;              /* enable Timer 1 and start the count */
}

void EE_timer1_stop( void )
{
    T1CONbits.TON = 0;              /* enable Timer 1 and start the count */
    IEC0bits.T1IE = 0;              /* disable Timer 1 interrupt */
}

static void EE_timer1_set_callback(EE_ISR_callback func)
{
    t1_cbk = func;
}

ISR2 (_T1Interrupt)
{
    IFS0bits.T1IF = 0;                /* reset timer interrupt flag    */
    if(t1_cbk != 0)
        t1_cbk();
}

static void EE_timer2_init(EE_UINT16 t2_period, EE_TimerPrescaleFactor ps)
{
    T2CON = 0;                        /* ensure Timer 2 is in reset state */
    IFS0bits.T2IF = 0;                /* reset Timer 2 interrupt flag */
    IPC1bits.T2IP = 5;                /* set Timer 2 interrupt priority level to 5 */
    IEC0bits.T2IE = 1;                /* enable Timer 2 interrupt */
    T2CONbits.T32 = 0;                /* select 16-bit timer */
    T2CONbits.TCS = 0;                /* select external timer clock */
    T2CONbits.TGATE = 0;              /* Gated time accumulation disabled */
    TMR2 = 0x00;                      /* Clear timer register */
    PR2 = t2_period;                  /* set Timer 2 period register */
    T2CONbits.TCKPS = ps;             /* select Timer 2 Input Clock Prescale */
    T2CONbits.TON = 1;                /* enable Timer 2 and start the count */
}

static void EE_timer2_start()
{
    IFS0bits.T2IF = 0;                /* reset Timer 2 interrupt flag */
    T2CONbits.TON = 1;                /* enable Timer 2 and start the count */
}

static void EE_timer2_stop( void )
{
    T2CONbits.TON = 0;                /* enable Timer 2 and start the count */
    IEC0bits.T2IE = 0;                /* disable Timer 2 interrupt */
}

static void EE_timer2_set_callback(EE_ISR_callback func)
{
    t2_cbk = func;
}

ISR2(_T2Interrupt)
{
    IFS0bits.T2IF = 0;                /* reset timer interrupt flag    */
    if(t2_cbk != 0)
        t2_cbk();
}

EE_INT8 EE_timer_hard_init(EE_TimerId id, EE_UINT32 period, EE_TimerPrescaleFactor ps){
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id){
        case EE_TIMER_1:
            EE_timer1_init(period, ps);
        break;
        case EE_TIMER_2:
            EE_timer2_init(period, ps);
        break;
        case EE_TIMER_3:
        case EE_TIMER_23:
            /* TODO implement those timers at least */
            error = EE_TIMER_ERR_UNIMPLEMENTED;
        break;
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}

EE_INT8 EE_timer_soft_init(EE_TimerId id, EE_UINT32 period_us)
{
    EE_INT8   error    = EE_TIMER_NO_ERRORS;
    EE_UINT32 baseFreq = EE_get_peripheral_clock();
    EE_UINT32 ticks = MICROSECONDS_TO_TICKS(period_us, baseFreq);

    EE_UINT32 const max_period  = 0xffffUL;
    EE_UINT16 prd; /* Period */
    EE_UINT8  psc; /* Prescale */
    if (ticks < max_period) {
        prd = ticks;
        psc = EE_TIMER_PS1;
    } else if (ticks / 8 < max_period) {
        prd = ticks / 8;
        psc = EE_TIMER_PS8;
    } else if (ticks / 64 < max_period) {
        prd = ticks / 64;
        psc = EE_TIMER_PS64;
    } else if (ticks / 256 < max_period) {
        prd = ticks / 256;
        psc = EE_TIMER_PS256;
    } else {
        error = EE_TIMER_ERR_BAD_ARGS;
    }
    if(!error)
        error = EE_timer_hard_init(id, prd, psc);
    return error;
}

EE_INT8 EE_timer_set_callback(EE_TimerId id, EE_ISR_callback func)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id){
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
        case EE_TIMER_3:
        case EE_TIMER_23:
            /* TODO implement those timers at least */
            error = EE_TIMER_ERR_UNIMPLEMENTED;
        break;
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}

EE_INT8 EE_timer_start(EE_TimerId id)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id){
        case EE_TIMER_1:
            EE_timer1_start();
        break;
        case EE_TIMER_2:
            EE_timer2_start();
        break;
        case EE_TIMER_3:
        case EE_TIMER_23:
            /* TODO implement those timers at least */
            error = EE_TIMER_ERR_UNIMPLEMENTED;
        break;
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}

EE_INT8 EE_timer_stop(EE_TimerId id)
{
    EE_INT8 error = EE_TIMER_NO_ERRORS;
    switch(id){
        case EE_TIMER_1:
            EE_timer1_stop();
        break;
        case EE_TIMER_2:
            EE_timer2_stop();
        break;
        case EE_TIMER_3:
        case EE_TIMER_23:
            /* TODO implement those timers at least */
            error = EE_TIMER_ERR_UNIMPLEMENTED;
        break;
        default:
            error = EE_TIMER_ERR_BAD_ARGS;
    }
    return error;
}
