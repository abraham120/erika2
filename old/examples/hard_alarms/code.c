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
 * Author: 2003 Bertozzi Francesco
 */


#include "ee.h"
#include "hard_alarms/hard_alarms.h"

#include "code.h"

#define LOOP 10000

volatile int activations = 0;
volatile int callbacks = 0;

void mycallback(void)
{
  callbacks++;
}

void thread0(void)
{
  EE_TYPETICK t;
  EE_UINT16 x;
  

  EE_alarm_setabs(alarm0, 1300, 1300);
  EE_alarm_setrel(alarm1, 400, 400);
  EE_alarm_setrel(alarm2, 500, 500);

  EE_alarm_get(alarm0, &t);
  
  for (x=0; x<LOOP; x++)
  { /* Idle loop */  }
  
  EE_alarm_cancel(alarm0);
  EE_alarm_cancel(alarm2);
  EE_alarm_cancel(alarm1);

  EE_alarm_setrel(alarm0, 300, 300);
  EE_alarm_setrel(alarm1, 310, 310);

}


void thread1(void)
{
  activations++;
}

void main(void)
{
  start_timer0();
  EE_thread_activate(0,1);
  EE_sys_scheduler();
  
  for (;;) {}
}



