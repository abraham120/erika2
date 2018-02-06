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
 * Author: 2002 Paolo Gai
 * CVS: $Id: threads.c,v 1.1 2005/07/17 13:10:52 pj Exp $
 */

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1

void pause_and_display(int disp);

TASK(thread0)
{
#ifdef __LEDS_USED__
    EE_led_1_on();
#endif    
        
    pause_and_display(0x0);

#ifdef __LEDS_USED__
    EE_led_1_off();
#endif

    // check if the last pretaskhook is set AND its posttaskhook has
    // not been called (the number of preemptions in the system is
    // fixed!!!
    EE_assert(18, !EE_assertions[18], 17);
    
    // and here we should check if both pre/post task hooks and
    // preemptions went ok
    EE_assert_and(19, 18, 10);

    EE_assert_range(0,1,19);

    TerminateTask();
}



TASK(thread1)
{
    EE_assert(5, TRUE, 4);

#ifdef __LEDS_USED__
    EE_led_2_on();
#endif

    pause_and_display(0x1);

#ifdef __LEDS_USED__
    EE_led_2_off();
#endif

    ChainTask(thread2);
}



TASK(thread2)
{
    EE_assert(6, TRUE, 5);

#ifdef __LEDS_USED__
    EE_led_3_on();
#endif
    
    pause_and_display(0x2);

#ifdef __LEDS_USED__
    EE_led_3_off();
#endif

    ChainTask(thread3);
}

void myfunc2(void)
{
    EE_assert(10, TRUE, 9);

#ifdef __LEDS_USED__
    EE_led_4_off();
#endif

    TerminateTask();
}

void myfunc1(void)
{
    EE_assert(9, TRUE, 8);

    pause_and_display(0x3);

    myfunc2();
}

TASK(thread3)
{
    EE_assert(7, TRUE, 6);

#ifdef __LEDS_USED__
    EE_led_4_on();
#endif
    
    Schedule();

    EE_assert(8, TRUE, 7);

    myfunc1();
}
