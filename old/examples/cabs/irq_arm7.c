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
 * CVS: $Id: irq_arm7.c,v 1.2 2004/11/30 14:52:54 pj Exp $
 */


#include "ee.h"
#include "cabs/cabs.h"

/*
 * timer #1 reset value (1 sec)
 *
 * 1 sec = 1000 * 1000 * 1000 nsec
 * timer tick = 50 MHz = 20 nsec
 */
//#define COUNTDOWN ((5 * 1000 * 1000 * 1000) / 20) /* 5 sec */
#define COUNTDOWN ((1 * 1000 * 1000 * 1000) / 20) /* 1 sec */
//#define COUNTDOWN ((100 * 1000 * 1000) / 20) /* 100 msec */
//#define COUNTDOWN ((10 * 1000 * 1000) / 20) /* 10 msec */
//#define COUNTDOWN ((1 * 1000 * 1000) / 20) /* 1 msec */
//#define COUNTDOWN ((100 * 1000) / 20) /* 100 usec */
//#define COUNTDOWN ((10 * 1000) / 20) /* 10 usec, too small! */


void arm7gnu_irq_init(void)
{
    EE_clear_pending_IRQ();

    EE_timer_init();
    EE_timer_0_set(0xFFFFFFFF);
    EE_enable_external_IRQ(IRQ_TIMER0_MASK);
    EE_timer_0_start();

    EE_timer_1_set(COUNTDOWN);
    EE_enable_external_IRQ(IRQ_TIMER1_MASK);
    EE_timer_1_start();

    EE_leds_init();


}

int th1_counter = 0;
int th2_counter = 0;


void timer_handler(void)
{
    /* activate thread */
    EE_thread_activate(0);

    if (th1_counter == 2) {
      EE_thread_activate(1);
      th1_counter = 0;
    }
    else
      th1_counter++;

    if (th2_counter == 4) {
      EE_thread_activate(2);
      th2_counter = 0;
    }
    else
      th2_counter++;
    
    /* end of handler */
}



