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
 * Author: 2005-2006 Antonio Romano
 * CVS: $Id: inithal.c,v 1.1 2006/07/11 09:16:42 pj Exp $
 */

#include "ee.h"
#include "mcu/atmega128/inc/ee_ic.h"






void thread0(void);
void thread1(void);
void thread2(void);
void thread3(void);



const EE_ADDR EE_avr5_thread_body[THREAD_MAX] = {
    (EE_ADDR)thread0,
    (EE_ADDR)thread1,
    (EE_ADDR)thread2,
    (EE_ADDR)thread3
};



#ifdef __MULTI__

const EE_ADDR EE_avr5_system_tos[THREAD_MAX+1] =
{
    (_STACK_ADDRESS - 19    ), /* main. MANDATORY! */
    (_STACK_ADDRESS - 50 - 19), /* thread0 */
    (_STACK_ADDRESS - 100 - 19), /* thread1 */
    (_STACK_ADDRESS - 150 - 19), /* thread2 */
    (_STACK_ADDRESS - 200 - 19) /* thread3 */
};


/* stack used only by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__

EE_ADDR EE_avr5_IRQ_tos = {_STACK_ADDRESS - 300- 19};

#endif


EE_UREG EE_avr5_thread_tos[THREAD_MAX+1] =
{
    0,				/* main */
    1,				/* thread0 */
    2,				/* thread1 */
    3,				/* thread2 */
    4				/* thread3 */
};


EE_UREG EE_avr5_active_tos = 0;


#endif /* __MULTI__ */



