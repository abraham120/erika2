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
 * Author: 2003 Paolo Gai
 * CVS: $Id: e7t_hal.c,v 1.4 2006/01/17 13:18:22 pj Exp $
 */

#include "ee.h"
#include "cfg_e7t.h"

void thread0(void);
void thread1(void);
void thread2(void);
void thread3(void);
/* NOTE: if a thread is compiled in thumb mode with ADS, its address
   will have the less significant bit equal to 1. Instead, with GNU
   gcc each thumb thread has a prologue that is in ARM-mode. */
const EE_ADDR EE_hal_thread_body[THREAD_MAX] = {
    (EE_ADDR)thread0,
    (EE_ADDR)thread1,
    (EE_ADDR)thread2,
    (EE_ADDR)thread3
};



#ifdef __TIMER_1_USED__
void timer1_handler(void);
#define TIMER1_HANDLER timer1_handler
#else
#define TIMER1_HANDLER forever_loop
#endif

void forever_loop(void)
{ 
  for (;;);
}

const EE_ADDR EE_IC_EXTIRQ_vector[22] = {
  (EE_ADDR)forever_loop, /* Ext 0 */
  (EE_ADDR)forever_loop, /* Ext 1 */
  (EE_ADDR)forever_loop, /* Ext 2 */
  (EE_ADDR)forever_loop, /* Ext 3 */
  (EE_ADDR)forever_loop, /* UART0 Tx */
  (EE_ADDR)forever_loop, /* UART0 Rx & error*/
  (EE_ADDR)forever_loop, /* UART1 Tx */
  (EE_ADDR)forever_loop, /* UART1 Rx & error*/
  (EE_ADDR)forever_loop, /* GDMA ch. 0 */
  (EE_ADDR)forever_loop, /* GDMA ch. 1 */
  (EE_ADDR)forever_loop, /* Timer 0 */
  (EE_ADDR)TIMER1_HANDLER, /* Timer 1 */
  (EE_ADDR)forever_loop, /* HDLC A Tx */
  (EE_ADDR)forever_loop, /* HDLC A Rx */
  (EE_ADDR)forever_loop, /* HDLC B Tx */
  (EE_ADDR)forever_loop, /* HDLC B Rx */
  (EE_ADDR)forever_loop, /* Ethernet BDMA Tx */
  (EE_ADDR)forever_loop, /* Ethernet BDMA Rx */
  (EE_ADDR)forever_loop, /* Ethernet MAC Tx */
  (EE_ADDR)forever_loop, /* Ethernet MAC Rx */
  (EE_ADDR)forever_loop, /* I2C-bus */
  (EE_ADDR)forever_loop /* No Pending Interrupt */
};




/* Interrupt handling */

#define COUNTDOWN ((1 * 1000 * 1000 * 1000) / 20) /* 1 sec */

void mytimer_start(void)
{
  EE_clear_pending_IRQ();
  EE_enable_external_IRQ(IRQ_TIMER1_MASK);
  EE_timer_1_set(COUNTDOWN);
  EE_timer_1_start();
}

void timer1_handler(void)
{
  /* activate thread */
  EE_thread_activate(0);
