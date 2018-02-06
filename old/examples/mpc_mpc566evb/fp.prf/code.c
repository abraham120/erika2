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
 * Author: 2004 Antonio Fiaschi
 * CVS: $Id: code.c,v 1.4 2006/01/05 14:39:07 pj Exp $
 */

#include "code.h"



ERIKA_UREG profiling_overhead_time = 0;

ERIKA_UREG thread1_activate_first_time = 0;
ERIKA_UREG thread1_activate_second_time = 0;
ERIKA_UREG thread2_activate_first_time = 0;
ERIKA_UREG thread3_activate_first_time = 0;
ERIKA_UREG thread4_activate_first_time = 0;
ERIKA_UREG thread1_activate_ready_time = 0;
ERIKA_UREG thread1_activate_stacked_time = 0;
ERIKA_UREG context_switch_time = 0;
ERIKA_UREG scheduler_ready_time = 0;
ERIKA_UREG scheduler_stacked_time = 0;
ERIKA_UREG end_instance_ready_time = 0;
ERIKA_UREG end_instance_stacked_time = 0;
ERIKA_UREG mutex_lock_time = 0;
ERIKA_UREG mutex_unlock_ready_time = 0;
ERIKA_UREG mutex_unlock_stacked_time = 0;
ERIKA_UREG start_timer_latency_time = 0;
ERIKA_UREG end_timer_ready_time = 0;
ERIKA_UREG IRQ_handler_latency_time = 0;



void start_profiling(void)
{
    ERIKA_timer_0_set(0xffffffff);
    ERIKA_timer_0_start();
}

void end_profiling(ERIKA_UREG *variable)
{
    *variable = ERIKA_timer_0_get();
    ERIKA_timer_0_stop();
    *variable = 0xffffffff - *variable;

    if (variable != &profiling_overhead_time) {
	/* subtract {start,end}_profiling() overhead  */
	*variable -= profiling_overhead_time;

	/* convert in nsec */
	*variable *= 20;
    }
}



#define TIMER_DELAY 1000000

HANDLER timer_1_handler_ready(void)
{
    start_timer_latency_time = ERIKA_timer_1_get();
    start_timer_latency_time = TIMER_DELAY - start_timer_latency_time;
    start_timer_latency_time *= 20;
    ERIKA_timer_1_stop();

    /* end_timer_ready_time */
    ERIKA_thread_activate(TID_thread4);
    start_profiling();
}



HANDLER timer_1_handler_stacked(void)
{
    ERIKA_timer_1_stop();
}



void thread0(void)
{
    int tmp;
    
    /* ... */
    end_profiling(&scheduler_ready_time);

    /* mutex_lock_time */
    start_profiling();	
    ERIKA_mutex_lock(MUTEX_sync);
    end_profiling(&mutex_lock_time);
    
    /* scheduler_stacked_time */
    ERIKA_thread_activate(TID_thread1);
    start_profiling();	
    ERIKA_sys_scheduler();
    end_profiling(&scheduler_stacked_time);

    /* mutex_unlock_ready_time */
    start_profiling();
    ERIKA_mutex_unlock(MUTEX_sync);

    /* IRQ_handler_latency_time */
    ERIKA_timer1_handler_addr = (ERIKA_ADDR)timer_1_handler_stacked;
    ERIKA_timer_1_set(TIMER_DELAY);

    start_profiling();
    ERIKA_timer_1_start();
    for (tmp=0; tmp<2*TIMER_DELAY; tmp++) {}
    end_profiling(&IRQ_handler_latency_time);

    start_profiling();
    ERIKA_timer_1_start();
    ERIKA_timer_1_stop();
    for (tmp=0; tmp<2*TIMER_DELAY; tmp++) {}
    end_profiling(&tmp);
    IRQ_handler_latency_time -= tmp;

    /* end_timer_ready_time */
    ERIKA_timer1_handler_addr = (ERIKA_ADDR)timer_1_handler_ready;
    ERIKA_timer_1_set(TIMER_DELAY);
    ERIKA_timer_1_start();
    for (tmp=0; tmp<2*TIMER_DELAY; tmp++) {}
    
    /* end of profiling */
    ERIKA_led_1_on();
    for (;;) {}
}



void thread1(void)
{
    /* ... */
    end_profiling(&mutex_unlock_ready_time);

    /* thread1_activate_ready_time */
    start_profiling();	
    ERIKA_thread_activate(TID_thread2);

    /* ... */
    end_profiling(&end_instance_stacked_time);

    /* end_instance_ready_time */
    ERIKA_thread_activate(TID_thread3);
    start_profiling();	
}



void thread2(void)
{
    /* ... */
    end_profiling(&thread1_activate_ready_time);

    /* context_switch_time */
    context_switch_time = thread1_activate_ready_time - thread1_activate_first_time;
	
    /* thread1_activate_stacked_time */
    start_profiling();	
    ERIKA_thread_activate(TID_thread5);
    end_profiling(&thread1_activate_stacked_time);

    /* mutex_unlock_stacked_time */
    ERIKA_mutex_lock(MUTEX_sync);
    start_profiling();
    ERIKA_mutex_unlock(MUTEX_sync);
    end_profiling(&mutex_unlock_stacked_time);

    /* end_instance_stacked_time */
    start_profiling();
}



void thread3(void)
{
    /* ... */
    end_profiling(&end_instance_ready_time);
}


void thread4(void)
{
    /* ... */
    end_profiling(&end_timer_ready_time);
}


void thread5(void)
{
}


void thread6(void)
{
}



void main(void)
{
    /* peripherals initialization */
    init_drivers();

    /* profiling_overhead_time */
    start_profiling();
    end_profiling(&profiling_overhead_time);

    /* thread1_activate_first_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread3);
    end_profiling(&thread1_activate_first_time);

    /* thread1_activate_second_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread3);
    end_profiling(&thread1_activate_second_time);

    /* thread2_activate_first_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread4);
    end_profiling(&thread2_activate_first_time);
    
    /* thread3_activate_first_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread5);
    end_profiling(&thread3_activate_first_time);
    
    /* thread4_activate_first_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread6);
    end_profiling(&thread4_activate_first_time);
    
    /* clear pending activations of thread{3,4,5,6} */
    ERIKA_sys_scheduler();

    /* scheduler_ready_time */
    ERIKA_thread_activate(TID_thread0);
    start_profiling();	
    ERIKA_sys_scheduler();

    /* never return */
}

