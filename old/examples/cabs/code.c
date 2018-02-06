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
 * Author: 2000-2002 Paolo Gai
 * CVS: $Id: code.c,v 1.3 2006/01/05 14:38:25 pj Exp $
 */


#include "ee.h"
#include "cabs/cabs.h"

EE_EXTERN_CAB(cab1);
EE_EXTERN_CAB(cab2);

EE_UREG tick=1;
EE_UREG result=0;

void thread1(void)
{
  void *msg;
  EE_CAB_INDEX num;

  EE_UREG tick_cab1;
  EE_UREG tick_cab2;
  
  EE_cab_getmes(&cab1, &msg, &num);
  tick_cab1 = *((EE_UREG *)msg);
  EE_cab_unget(&cab1, num);

  EE_cab_getmes(&cab2, &msg, &num);
  tick_cab2 = *((EE_UREG *)msg);
  EE_cab_unget(&cab2, num);

  result = tick_cab1 - tick_cab2;

#ifdef __LCD_USED__
  EE_LCD_display(1);
#endif
}

void thread2(void)
{
  void *msg;
  EE_CAB_INDEX num;
  EE_UREG mytick;
  
  EE_cab_getmes(&cab1, &msg, &num);
  mytick = *((EE_UREG *)msg);
  EE_cab_unget(&cab1, num);

  EE_cab_reserve(&cab2, &msg, &num);
  *((EE_UREG *)msg) = mytick*2;
  EE_cab_putmes(&cab2, num);

#ifdef __LCD_USED__
  EE_LCD_display(2);
#endif
}

void thread3(void)
{
  void *msg;
  EE_CAB_INDEX num;

  EE_cab_reserve(&cab1, &msg, &num);
  *((EE_UREG *)msg) = tick++;
  EE_cab_putmes(&cab1, num);

#ifdef __LCD_USED__
  EE_LCD_display(3);
#endif
}

#ifdef __ST10__
// initializes the CAPCOMS
void st10_irq_init(void);
#endif

#ifdef __ARM7GNU__
// initializes the CAPCOMS
void arm7gnu_irq_init(void);
#endif

void EE_main(void)
{
  /* Initialize cabs */
  EE_cab_init(&cab1);
  EE_cab_init(&cab2);

#ifdef __ST10__
  st10_irq_init();
#endif

#ifdef __ARM7GNU__
  arm7gnu_irq_init();
#endif

#ifdef __H8__
  EE_init();
#endif
  
  for (;;) {}
}

