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
 * Author: 2001-2002 Paolo Gai
 * CVS: $Id: initarm7.c,v 1.3 2006/01/17 13:18:22 pj Exp $
 */

#include "ee.h"
#include "code.h"

#include "cfg_e7t.h"

/* NOTE: if a thread is compiled in thumb mode with ADS, its address
   will have the less significant bit equal to 1. Instead, with GNU
   gcc each thumb thread has a prologue that is in ARM-mode. */
const EE_ADDR EE_hal_thread_body[THREAD_MAX] = {
    (EE_ADDR)thread0,
    (EE_ADDR)thread1,
    (EE_ADDR)thread2,
    (EE_ADDR)thread3
};

#ifdef __MULTI__

struct EE_TOS EE_arm7_system_tos[THREAD_MAX+1] =
{
    {(EE_ADDR)(__SYS_STACK_ADDRESS        ), (EE_ADDR)(__IRQ_STACK_ADDRESS        )}, /* main. MANDATORY! */
    {(EE_ADDR)(__SYS_STACK_ADDRESS-512-32 ), (EE_ADDR)(__IRQ_STACK_ADDRESS-512-32 )}, /* thread0 */
    {(EE_ADDR)(__SYS_STACK_ADDRESS-1024-32), (EE_ADDR)(__IRQ_STACK_ADDRESS-1024-32)}, /* thread1 */
    {(EE_ADDR)(__SYS_STACK_ADDRESS-1536-32), (EE_ADDR)(__IRQ_STACK_ADDRESS-1536-32)}, /* thread2 */
    {(EE_ADDR)(__SYS_STACK_ADDRESS-2048-32), (EE_ADDR)(__IRQ_STACK_ADDRESS-2048-32)}  /* thread3 */
};


/* stack used only by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
struct EE_TOS EE_arm7_IRQ_tos = {
  (EE_ADDR)(__SYS_STACK_ADDRESS-2560), (EE_ADDR)(__IRQ_STACK_ADDRESS-2560)
};
#endif


EE_UREG EE_arm7_thread_tos[THREAD_MAX+1] =
{
    0,				/* main */
    1,				/* thread0 */
    2,				/* thread1 */
    3,				/* thread2 */
    4				/* thread3 */
};


EE_UREG EE_arm7_active_tos = 0; /* main */

#endif /* __MULTI__ */


/* IRQ handlers installation */
#ifdef __TIMER_1_USED__
void my_timer_handler(void);
EE_ADDR EE_timer1_handler_addr = (EE_ADDR)my_timer_handler;
#endif


/* ---------------------------------------------------------*/

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

void my_init()
{
    EE_clear_pending_IRQ();

    EE_timer_init();

    EE_timer_1_set(COUNTDOWN);
    EE_enable_external_IRQ(IRQ_TIMER1_MASK);
    EE_timer_1_start();
}






