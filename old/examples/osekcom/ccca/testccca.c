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
 * Author: 2003 Francesco Bertozzi
 * CVS: $Id: testccca.c,v 1.4 2006/01/05 14:38:25 pj Exp $
 */

#include "ee.h"
#include "com/com.h"

/* In this test thread0 sends every 100mS an internal message to
 * thread1 thread2 and thread3 that sum received data to ABS_Data - it
 * sounds like a per 4 multiply 
 */
#ifdef __ST10__
extern start_timer1(void);
#endif

EE_UINT32 ABS_Data = 1;

void COMErrorHook (StatusType error_id)
{
  EE_osekcom_COMErrorGetServiceId();
}

void thread0(void)
{  
  SendMessage(ABS, (EE_UINT8 *)&ABS_Data);
}

void thread1(void)
{
  EE_UINT32 dato1;
  
  ReceiveMessage( RECEIVER1, (EE_UINT8 *)&dato1);
  ABS_Data += dato1;
}

void thread2(void)
{
  EE_UINT32 dato2;
  
  ReceiveMessage( RECEIVER2, (EE_UINT8 *)&dato2);
  ABS_Data += dato2;
}
void thread3(void)
{
  EE_UINT32 dato3;

  ReceiveMessage( RECEIVER2, (EE_UINT8 *)&dato3);
  ABS_Data += dato3;
}

void callback(void)
{
  EE_thread_activate(2);
  EE_thread_activate(3);
}

void mytimer_start();

void main(void)
{  /* Initialize OsekCOM */
  if (StartCOM(EE_OSEKCOM_MODE_A) == E_OK) {
#ifdef __ST10__
    start_timer1();
#endif

#ifdef __ARM7GNU__
#ifdef __EVALUATOR7T__
    mytimer_start();
#endif
#endif
  }

  for (;;) {}
}

