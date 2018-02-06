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
 * CVS: $Id: code.c,v 1.5 2006/05/14 18:00:59 pj Exp $
 */

#include "code.h"



/*
 * timer #1 reset value (1 sec)
 *
 * 1 sec = 1000 * 1000 * 1000 nsec
 * timer tick = 50 MHz = 20 nsec
 */
#define COUNTDOWN ((5 * 1000 * 1000 * 1000) / 20) /* 5 sec */
//#define COUNTDOWN ((1 * 1000 * 1000 * 1000) / 20) /* 1 sec */
//#define COUNTDOWN ((100 * 1000 * 1000) / 20) /* 100 msec */
//#define COUNTDOWN ((10 * 1000 * 1000) / 20) /* 10 msec */
//#define COUNTDOWN ((1 * 1000 * 1000) / 20) /* 1 msec */
//#define COUNTDOWN ((100 * 1000) / 20) /* 100 usec */
//#define COUNTDOWN ((10 * 1000) / 20) /* 10 usec, too small! */

#define ALARM 500

/*
 * Display a number during a short pause 
 */
//#define LOOP_LENGHT 100000
#define LOOP_LENGHT 10000
//#define LOOP_LENGHT 1000
//#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1

void pause_and_display(int disp)
{
//    int i=0;
//    int j=0;
    
//    for (i=0; i<LOOP_LENGHT; i++) {
//        EE_LCD_display(disp);
//        for(j=0; j<10; j++) {
            /* do nothing */
//        }
//    }
}


#ifdef __PIT_USED__
void pit_handler(void)
{
	/* activate thread */
	EE_pit_exception_reset();
	EE_thread_activate(TID_thread3);
}
#endif

#ifdef __RT_CLOCK_USED__
void rt_clock_handler(void)
{
	EE_rt_clock_alarm_exception_reset();
	EE_rt_clock_reset();
	EE_clear_pending_IRQ();
	pause_and_display(0xd);
	EE_thread_activate(TID_thread2);
}
#endif

void handler_not_defined(void){
	for(;;){}
}

void thread0(void) 
{
	pause_and_display(0xd);
	EE_thread_activate(TID_thread1);
}

void thread1(void)
{
        pause_and_display(0xd);
	//EE_thread_activate(TID_thread2);
}

void thread2(void)
{
//        pause_and_display(0xd);
//        EE_thread_activate(TID_thread3);
}

void thread3(void)
{
//        pause_and_display(0xd);
}

void main(void)
{
    /* peripherals initialization */
    init_drivers();

    /* periodic timer start */
#ifdef __PIT_USED__
    EE_pit_set(COUNTDOWN);
    EE_pit_freeze();
    EE_pit_start();
    EE_pit_enable();
    EE_pit_resume();
#endif
#ifdef __RT_CLOCK_USED__
    EE_rt_clock_reset();
    EE_rt_clock_alarm_set(ALARM);
    EE_rt_clock_freeze();
    EE_rt_clock_start();
    EE_rt_clock_alarm_enable();
    EE_rt_clock_sec_disable();
    EE_rt_clock_resume();
#endif
    /* activate the first thread */
    EE_thread_activate(TID_thread0);

    /* if there are no thread to execute, the main thread will go
     * into an infinite loop */
    for (;;) {
	/* LCD idle indication */
	pause_and_display(0xd);
	
	/* background activities, none in this test */
    }
}

