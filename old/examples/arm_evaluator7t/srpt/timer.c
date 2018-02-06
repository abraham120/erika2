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

/*
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: timer.c,v 1.2 2004/11/30 14:51:44 pj Exp $
 */

#include "code.h"


/* thread activation accepted error */ 
#define TIMER_TOLERANCE 0x00000100

/* number of timer ticks necessary to reach the period */

extern const EE_TYPERELDLINE th_period[];
static EE_TIME time_countdown[THREAD_MAX];

/* elapsed time since last ticks handler activation */
static EE_TIME last_handler_activation;


/* ticks counter initialization */
/* This function is called into a thread!!! */
void tick_start(void) 
{
    int i;
    EE_TIME min_dline;
    
    /* timer activation */
    last_handler_activation = EE_timer_0_get();


    min_dline = th_period[0];
    
    
    /* the threads start at the same time */
    for (i=0; i < PERIODIC_THREAD_MAX; i++) {
	time_countdown[i] = th_period[i];
	EE_thread_activate(i);
	if (th_period[i] < min_dline){
	    min_dline = time_countdown[i];
	}
    }

    EE_timer_1_set(min_dline);
    EE_timer_1_start();
    
    EE_sys_scheduler();
}



/* periodic thread activation */
void tick_handler(void)
{
    int i = 0;

    EE_TIME min_dline;
    EE_TIME this_handler_activation;
    EE_TIME elapsed_time;
    
    /* calculate the last activation time */
    this_handler_activation = EE_timer_0_get();
    if ((last_handler_activation - this_handler_activation) > 0) {
	elapsed_time = last_handler_activation - this_handler_activation;
    } else {
	elapsed_time = (signed)last_handler_activation - (signed)this_handler_activation;
    }
    last_handler_activation = this_handler_activation;

    /* initialize the minimum with a value of the table, in order to
     * do not risk to take a value smaller than each other */
    min_dline = th_period[0];


    /* if the thread has reached its period of activation, then it is
     * activated */
    for (i=0; i < PERIODIC_THREAD_MAX; i++) {
	/* for each thread, update the elapsed time */
	time_countdown[i] -= elapsed_time;

	/* If the tick size is very large, the thread can be activated
	 * several times */
	while ((signed)time_countdown[i] <= (signed)TIMER_TOLERANCE) {
	    time_countdown[i] += th_period[i];
	    EE_thread_activate(i);
	}

	/* test if the remaining time is the smaller */
	if (time_countdown[i] < min_dline){
	    min_dline = time_countdown[i];
	}
    }

    
    /* Predispose the next thread activation. Reload the timer with
     * the new value, in ticks (consider the time elapsed since the
     * handler activation) */
    /* NOTE: since the timer restarts after the interrupt request, its
     * current value indicates the timer handler latency. */
    
    /* write a new value (the nearest deadline) */
    EE_timer_1_set(min_dline);
    
    /* end of handler */
}
