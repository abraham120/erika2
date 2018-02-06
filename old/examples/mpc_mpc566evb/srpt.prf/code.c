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


ERIKA_TIME profiling_overhead_time = 0;
ERIKA_TIME tmp_profiling_time = 0;

ERIKA_TIME first_thread_activate_time = 0;
ERIKA_TIME second_thread_activate_time = 0;
ERIKA_TIME thread_activate_ready_time = 0;
ERIKA_TIME thread_activate_stacked_time = 0;
ERIKA_TIME scheduler_ready_time = 0;
ERIKA_TIME scheduler_stacked_time = 0;
ERIKA_TIME end_instance_ready_time = 0;
ERIKA_TIME end_instance_stacked_time = 0;
ERIKA_TIME mutex_lock_time = 0;
ERIKA_TIME mutex_unlock_stacked_time = 0;


__INLINE__ void start_profiling()
{
  tmp_profiling_time = ERIKA_sys_gettime();
}

__INLINE__ void end_profiling(ERIKA_TIME *variable)
{
    *variable = ERIKA_sys_gettime();
    if ((unsigned)tmp_profiling_time < (unsigned)(*variable)) {
	*variable -= (unsigned)tmp_profiling_time;
    } else {
	*variable -= (signed)tmp_profiling_time;
    }

    if (variable != &profiling_overhead_time) {
	/* subtract {start,end}_profiling() overhead  */
	*variable -= profiling_overhead_time;

	/* convert in nsec */
	*variable *= 20;
    }
}


void thread0(void)
{
}



void thread1(void)
{
    /* ... */
    end_profiling(&thread_activate_ready_time);
    
    /* thread_activate_stacked_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread0);
    end_profiling(&thread_activate_stacked_time);

    /* scheduler_ready_time */
    ERIKA_thread_activate(TID_thread2);
    start_profiling();
    ERIKA_sys_scheduler();

    /* ... */
    end_profiling(&end_instance_stacked_time);

    /* end_instance_ready_time */
    ERIKA_thread_activate(TID_thread3);
    start_profiling();
}



void thread2(void)
{
    /* ... */
    end_profiling(&scheduler_ready_time);
    
    /* scheduler_stacked_time  */
    ERIKA_thread_activate(TID_thread0);
    start_profiling();
    ERIKA_sys_scheduler();
    end_profiling(&scheduler_stacked_time);

    /* end_instance_stacked_time */
    start_profiling();
}



void thread3(void)
{
    /* ... */
    end_profiling(&end_instance_ready_time);

    /* mutex_lock_time */
    start_profiling();
    ERIKA_mutex_lock(MUTEX_sync);
    end_profiling(&mutex_lock_time);

    /* mutex_unlock_stacked_time */
    start_profiling();
    ERIKA_mutex_unlock(MUTEX_sync);
    end_profiling(&mutex_unlock_stacked_time);
}


void main(void)
{
    /* peripherals initialization */
    init_drivers();

    /* begin profiling */
    ERIKA_led_1_off();
    
    /* profiling_overhead_time */
    start_profiling();
    end_profiling(&profiling_overhead_time);

    /* first_thread_activate_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread0);
    end_profiling(&first_thread_activate_time);
    
    /* second_thread_activate_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread0);
    end_profiling(&second_thread_activate_time);

    ERIKA_sys_scheduler();
    
    /* thread_activate_ready_time */
    start_profiling();
    ERIKA_thread_activate(TID_thread1);

    /* end profiling */
    ERIKA_led_1_on();
    
    for (;;);
}

