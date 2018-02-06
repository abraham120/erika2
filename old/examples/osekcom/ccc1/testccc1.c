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
 * CVS: $Id: testccc1.c,v 1.3 2006/01/05 14:38:25 pj Exp $
 */

#include "ee.h"
#include "com/com.h"

/* In this test there are two timer: one timer increment every 51.2 uSec used 
 * by capcom function and one other timer used to check randomly if a thread
 * should send a message.
 * Using IPDU callout the ipdu is send only if all messages are transmitted,
 * state check by test_var variable.
 */
#ifdef __ST10__
extern start_timer1(void);
#endif

EE_UINT16 test_var = 0,
             timer_mod = 0;
             
EE_UINT8 data_send = 0;
             
EE_UINT16 wake_mod[THREAD_MAX] = {0,6,2,7,1};

void COMErrorHook (StatusType error_id)
{
  EE_osekcom_COMErrorGetServiceId();
}

void thread0(void)
{  
  data_send++;
  SendMessage (REVERSE,&data_send);
  SendMessage (DC_CURRENT_CTRL,&data_send);
  test_var |= 0xC000; 
}

void thread1(void)
{  
  data_send++;
  SendMessage (V12_POWER,&data_send);
  SendMessage (BRAKE_SOL,&data_send);
  test_var |= 0x3000; 
}

void thread2(void)
{  
  data_send++;
  SendMessage (BACKUP_ALARM,&data_send);
  SendMessage (WARN_LIGHT,&data_send);
  test_var |= 0x0C00; 
}

void thread3(void)
{  
  data_send++;
  SendMessage (KEY_SWITCH,&data_send);
  SendMessage (FWD_REV,&data_send);
  test_var |= 0x0300; 
}

void thread4(void)
{  
  data_send++;
  SendMessage (SHIFT_PROGRESS,&data_send);
  SendMessage (MAIN_ACK,&data_send);
  test_var |= 0x00C0; 
}

void thread5(void)
{  
  data_send++;
  SendMessage (IDLE,&data_send);
}

StatusType ipdu_callout (void)
{
  if (test_var == 0xFFC0)
  {
    test_var = 0;
    return EE_COM_TRUE;
  }
  else
    return EE_COM_FALSE;
}

void callback_txok (void)
{
}

void callback_txer (void)
{
}

void callback_rxok (void)
{
}

void callback_rxer (void)
{
}

void main(void)
{  /* Initialize OsekCOM */
  if (StartCOM(EE_OSEKCOM_MODE_A) == E_OK) {
#ifdef __ST10__
    start_timer1();
#endif

  }

  for (;;) {}
}

