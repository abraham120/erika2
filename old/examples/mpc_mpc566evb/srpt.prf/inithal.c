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
 * CVS: $Id: inithal.c,v 1.3 2006/01/05 14:39:07 pj Exp $
 */

#include "erika.h"
#include "code.h"
#include "cfg_e7t.h"

const ERIKA_ADDR ERIKA_arm7_thread_body[THREAD_MAX] = {
    (ERIKA_ADDR)thread0,
    (ERIKA_ADDR)thread1,
    (ERIKA_ADDR)thread2,
    (ERIKA_ADDR)thread3
};


#ifdef __MULTI__

struct ERIKA_TOS ERIKA_arm7_system_tos[THREAD_MAX+1] =
{
    {(ERIKA_ADDR)(__SYS_STACK_ADDRESS        ), (ERIKA_ADDR)(__IRQ_STACK_ADDRESS        )}, /* main. MANDATORY! */
    {(ERIKA_ADDR)(__SYS_STACK_ADDRESS-512 -32), (ERIKA_ADDR)(__IRQ_STACK_ADDRESS-512 -32)}, /* thread0 */
    {(ERIKA_ADDR)(__SYS_STACK_ADDRESS-1024-32), (ERIKA_ADDR)(__IRQ_STACK_ADDRESS-1024-32)}, /* thread1 */
    {(ERIKA_ADDR)(__SYS_STACK_ADDRESS-1536-32), (ERIKA_ADDR)(__IRQ_STACK_ADDRESS-1536-32)}, /* thread2 */
    {(ERIKA_ADDR)(__SYS_STACK_ADDRESS-2048-32), (ERIKA_ADDR)(__IRQ_STACK_ADDRESS-2048-32)} /* thread3 */
};


/* stack used only by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
struct ERIKA_TOS ERIKA_arm7_IRQ_tos = {
  (ERIKA_ADDR)(__SYS_STACK_ADDRESS-2560-32), (ERIKA_ADDR)(__IRQ_STACK_ADDRESS-2560-32)
};
#endif


ERIKA_UREG ERIKA_arm7_thread_tos[THREAD_MAX+1] =
{
    0,				/* main */
    1,				/* thread0 */
    2,				/* thread1 */
    3,				/* thread2 */
    4				/* thread3 */
};


ERIKA_UREG ERIKA_arm7_active_tos = 0; /* main */

#endif /* __MULTI__ */


/* IRQ handlers installation */
#ifdef __EXT0_USED__
ERIKA_ADDR ERIKA_ext0_handler_addr = 0;
#endif

#ifdef __TIMER_0_USED__
ERIKA_ADDR ERIKA_timer0_handler_addr = 0;
#endif

#ifdef __TIMER_1_USED__
ERIKA_ADDR ERIKA_timer1_handler_addr = 0;
#endif
