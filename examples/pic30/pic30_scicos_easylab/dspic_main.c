/*
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

 * Author: 2011 Errico Guidieri
 * Patriot bugfix by Simone Mannori (1 Ottobre 2011)
 */

#define XNAME(x,y)  x##y
#define NAME(x,y)   XNAME(x,y)

#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_utils.h"
#include "mcu/microchip_dspic/inc/ee_timer.h"

/* Oscillator selectione register set on internal Fast RC oscillator. */
_FOSCSEL(FNOSC_FRC);
/* Oscillator configuration register set with clock switch enabled & clock monitoring disabled (FCKSM_CSECMD),
 * OSC2 pin as GPIO (OSCIOFNC_ON) and
 * primary oscillator disabled (not external oscillator/clock source in the board) */
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
/* Watchdog Timer disabled */
_FWDT(FWDTEN_OFF);
/* Disable Code Protection */
_FGS(GCP_OFF);

/* Period Ts specified in Scicos top diagram by clock block */
static double       scicos_period;
/* as above, expressed in (int) milliseconds */
static EE_UINT16    dspic_period;  
static EE_UINT16    dspic_delay;

/* simple time */
static double actTime; /* current run time (sec) */
static EE_UINT32    dspic_tick; /* current tick (+1 at each isr) */

/* CPU load analyzer */
static float CPU_load = 0.0;
volatile EE_UINT8 easylab_CPUload_gpout_mask = 0;
void (*CPU_load_test_gpout_func) (EE_UINT8, float);

static EE_UINT16 start_time_ticks; /* based on tmr1, range [0,40000], initialized over the range */
static EE_UINT16 start_time_ms;    /* based on sciCounter, not initialized */

void CPU_load_test_start(void) {
	if( CPU_load_test_gpout_func != NULL )
		CPU_load_test_gpout_func(easylab_CPUload_gpout_mask, 1.0);
	start_time_ticks = TMR1;
	start_time_ms = EE_counter_RAM[sciCounter].value;
}

void CPU_load_test_end(void) {
	if( CPU_load_test_gpout_func != NULL )
		CPU_load_test_gpout_func(easylab_CPUload_gpout_mask, 0.0);
	EE_UINT16 end_time_ticks = TMR1;
	EE_UINT16 end_time_ms = EE_counter_RAM[sciCounter].value;
	float us = (float)(end_time_ticks - start_time_ticks)/40.0;
	float ms = end_time_ms - start_time_ms;
	CPU_load = ms/1e3 + us/1e6;
}

float CPU_load_get(void)
{
	return CPU_load;
}

extern int    NAME(MODELNAME,_init)(void);
extern double NAME(MODELNAME,_get_tsamp)(void);
extern double NAME(MODELNAME,_get_tsamp_delay)(void);
extern int    NAME(MODELNAME,_isr)(double);
extern int    NAME(MODELNAME,_end)(void);

double get_scicos_time()
{
    return(actTime);
}

double get_scicos_period()
{
    return(scicos_period);
}

EE_UINT16   get_dspic_period()
{
    return(dspic_period);
}

EE_UINT32   get_dspic_tick()
{
    return(dspic_tick);
}

TASK(rt_sci)
{
    CPU_load_test_start();
    NAME(MODELNAME,_isr)(actTime);
    actTime += scicos_period;
    dspic_tick++;
    CPU_load_test_end();
}

int main(void)
{
    /* Set the system clock frequency to 80 Mhz (means microcontroller instructions frequency 40 MIPS) */
    EE_set_system_clock(80000000UL);
    
    /* Tie timer1 to sciCounter each interrupt correspond to a tick */
    EE_timer_set_counter(EE_TIMER_1, sciCounter);

    /* reset the timer and put tic period at 1 ms */
    EE_timer_soft_init(EE_TIMER_1, 1000U);
    EE_timer_start(EE_TIMER_1);
    
    /* simulation time */
    actTime = 0.0; dspic_tick = 0; 

    /* recover the cycle period Ts */
    scicos_period = NAME(MODELNAME,_get_tsamp)();
    dspic_period = (EE_UINT16) (1000U * scicos_period);
    dspic_delay = (int) (1000 * NAME(MODELNAME,_get_tsamp_delay)()) ;

    /* Blocks initialization */
    NAME(MODELNAME,_init)();
    
    /* Set the isr period */
    SetRelAlarm(AlarmSci, dspic_period + dspic_delay, dspic_period);

    /* Forever loop: background activities (if any) should go here */
    while(1)
    {
      /* put your code here :-) */
    }
    
    return 0;
}
