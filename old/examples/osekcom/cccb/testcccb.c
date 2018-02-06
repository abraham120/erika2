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
 * CVS: $Id: testcccb.c,v 1.3 2006/01/05 14:38:25 pj Exp $
 */

/* 
 * In this example thread0 periodically (1.5 times faster than thread
 * 1) sends an internal message to:
 * - thread1 (that manage a queued internal message) and to 
 * - thread2 (that manage an unqueued internal message).  
 * thread1 is activated periodically 
 * thread2 is activated after a message arrival.
 *
 * Every thread add the content of his message to the value of the
 * sending message
 */

#include "ee.h"
#include "com/com.h"

EE_OSEKCOM_DECLARE_FLAG(data_in);


EE_UINT32 ABS_Data         = 1;
EE_UINT8  data_send        = 0;
EE_UINT8  data_rx_queued   = 0;
EE_UINT8  data_rx_unqueued = 0;

void thread0(void)
{	
  SendMessage(ABS, (EE_UINT8 *)&ABS_Data);
  data_send++;
}

void thread1(void)
{
  EE_UINT32 data1;

  if (ReadFlag_data_in() == COM_TRUE)
    while (ReceiveMessage( CENTRALINA2, (EE_UINT8 *)&data1) != E_COM_NOMSG)
      {
	ABS_Data += data1;
	data_rx_queued ++;
      }
}

void thread2(void)
{      
  EE_UINT32 data2;

  ReceiveMessage( CENTRALINA1, (EE_UINT8 *)&data2);
  ABS_Data += data2;
  data_rx_unqueued++;
}

void mytimer_start();

void main(void)
{
  /* Initialize OsekCOM */
  if (StartCOM(2) == E_OK) {
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

