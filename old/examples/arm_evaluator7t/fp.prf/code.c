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
 * CVS: $Id: code.c,v 1.6 2006/10/25 14:37:33 pj Exp $
 */

#include "ee.h"
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"


EE_UREG profiling_overhead_time = 0;

EE_UREG thread1_activate_first_time = 0;
EE_UREG thread1_activate_second_time = 0;
EE_UREG thread2_activate_first_time = 0;
EE_UREG thread3_activate_first_time = 0;
EE_UREG thread4_activate_first_time = 0;
EE_UREG thread1_activate_ready_time = 0;
EE_UREG thread1_activate_stacked_time = 0;
EE_UREG context_switch_time = 0;
EE_UREG scheduler_ready_time = 0;
EE_UREG scheduler_stacked_time = 0;
EE_UREG end_instance_ready_time = 0;
EE_UREG end_instance_stacked_time = 0;
EE_UREG mutex_lock_time = 0;
EE_UREG mutex_unlock_ready_time = 0;
EE_UREG mutex_unlock_stacked_time = 0;
EE_UREG start_timer_latency_time = 0;
EE_UREG end_timer_ready_time = 0;
EE_UREG IRQ_handler_latency_time = 0;



void start_profiling(void)
{
    EE_timer_0_set(0xffffffff);
    EE_timer_0_start();
}

void end_profiling(EE_UREG *variable)
{
    *variable = EE_timer_0_get();
    EE_timer_0_stop();
    *variable = 0xffffffff - *variable;

    if (variable != &profiling_overhead_time) {
	/* subtract {start,end}_profiling() overhead  */
	*variable -= profiling_overhead_time;

	/* convert in nsec */
	*variable *= 20;
    }
}



#define TIMER_DELAY 1000000

void timer_1_handler_ready(void)
{
    start_timer_latency_time = EE_timer_1_get();
    start_timer_latency_time = TIMER_DELAY - start_timer_latency_time;
    start_timer_latency_time *= 20;
    EE_timer_1_stop();

    /* end_timer_ready_time */
    ActivateTask(thread4);
    start_profiling();
}



void timer_1_handler_stacked(void)
{
    EE_timer_1_stop();
}



TASK(thread0)
{
    int tmp;
    
    /* ... */
    end_profiling(&scheduler_ready_time);

    /* mutex_lock_time */
    start_profiling();	
    GetResource(MUTEX_sync);
    end_profiling(&mutex_lock_time);
    
    /* scheduler_stacked_time */
    ActivateTask(thread1);
    start_profiling();	
    Schedule();
    end_profiling(&scheduler_stacked_time);

    /* mutex_unlock_ready_time */
    start_profiling();
    ReleaseResource(MUTEX_sync);

    /* IRQ_handler_latency_time */
    EE_IC_EXTIRQ_vector[IRQ_TIMER1] = (EE_ADDR)timer_1_handler_stacked;
    EE_timer_1_set(TIMER_DELAY);

    start_profiling();
    EE_timer_1_start();
    for (tmp=0; tmp<2*TIMER_DELAY; tmp++) {}
    end_profiling(&IRQ_handler_latency_time);

    start_profiling();
    EE_timer_1_start();
    EE_timer_1_stop();
    for (tmp=0; tmp<2*TIMER_DELAY; tmp++) {}
    end_profiling(&tmp);
    IRQ_handler_latency_time -= tmp;

    /* end_timer_ready_time */
    EE_IC_EXTIRQ_vector[IRQ_TIMER1] = (EE_ADDR)timer_1_handler_ready;
    EE_timer_1_set(TIMER_DELAY);
    EE_timer_1_start();
    for (tmp=0; tmp<2*TIMER_DELAY; tmp++) {}
    
    /* end of profiling */
    EE_led_1_on();
    for (;;) {}
}



TASK(thread1)
{
    /* ... */
    end_profiling(&mutex_unlock_ready_time);

    /* thread1_activate_ready_time */
    start_profiling();	
    ActivateTask(thread2);

    /* ... */
    end_profiling(&end_instance_stacked_time);

    /* end_instance_ready_time */
    ActivateTask(thread3);
    start_profiling();	
}



TASK(thread2)
{
    /* ... */
    end_profiling(&thread1_activate_ready_time);

    /* context_switch_time */
    context_switch_time = thread1_activate_ready_time - thread1_activate_first_time;
	
    /* thread1_activate_stacked_time */
    start_profiling();	
    ActivateTask(thread5);
    end_profiling(&thread1_activate_stacked_time);

    /* mutex_unlock_stacked_time */
    GetResource(MUTEX_sync);
    start_profiling();
    ReleaseResource(MUTEX_sync);
    end_profiling(&mutex_unlock_stacked_time);

    /* end_instance_stacked_time */
    start_profiling();
}



TASK(thread3)
{
    /* ... */
    end_profiling(&end_instance_ready_time);
}


TASK(thread4)
{
    /* ... */
    end_profiling(&end_timer_ready_time);
}


TASK(thread5)
{
}


TASK(thread6)
{
}

void init_drivers(void)
{
    EE_IC_clear_pending_IRQ();

#ifdef __BUTTON_USED__
    EE_IC_enable_external_IRQ(IRQ_EXT0_MASK);	/* button */
    EE_button_init();
#endif
    
#ifdef __LEDS_USED__
    EE_leds_init();
#endif

#ifdef __LCD_USED__
    EE_lcd_init();
#endif

#ifdef __TIMER_USED__		/* defined through __TIMER_?_USED__ */
    EE_timer_init();
#endif

#ifdef __TIMER_0_USED__
    EE_IC_enable_external_IRQ(IRQ_TIMER0_MASK);
#endif

#ifdef __TIMER_1_USED__
    EE_IC_enable_external_IRQ(IRQ_TIMER1_MASK);
#endif

#ifdef __DIP_SWITCH_USED__
    /* do nothing */
#endif
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
    ActivateTask(thread3);
    end_profiling(&thread1_activate_first_time);

    /* thread1_activate_second_time */
    start_profiling();
    ActivateTask(thread3);
    end_profiling(&thread1_activate_second_time);

    /* thread2_activate_first_time */
    start_profiling();
    ActivateTask(thread4);
    end_profiling(&thread2_activate_first_time);
    
    /* thread3_activate_first_time */
    start_profiling();
    ActivateTask(thread5);
    end_profiling(&thread3_activate_first_time);
    
    /* thread4_activate_first_time */
    start_profiling();
    ActivateTask(thread6);
    end_profiling(&thread4_activate_first_time);
    
    /* clear pending activations of thread{3,4,5,6} */
    Schedule();

    /* scheduler_ready_time */
    ActivateTask(thread0);
    start_profiling();	
    Schedule();

    /* never return */
}

