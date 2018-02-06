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

#if defined(__NIOS2__)
/* Altera Includes */ 
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "altera_avalon_timer_regs.h"
#endif

/* EE includes */
#include "ee.h"

/* Assertions */
#include "test/assert/inc/ee_assert.h"
#define TRUE 1
/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[12];

SemType mySem = STATICSEM(1);

DeclareTask(ExtTask);
DeclareTask(ExtTask2);
DeclareTask(BasTask);

TASK(ExtTask)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  
  EE_assert(2, TRUE, 1);

  /* WaitSem chiamata con semaforo con contatore > 1 --> decrementa e ritorna */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(3, (s==E_OK), 2);
#else
  WaitSem(&mySem);
  EE_assert(3, TRUE, 2);
#endif

  /* WaitSem chiamata con contatore a 0 e coda sem vuota --> mi blocco ed il task è accodato come primo 
   * WaitSem chiamata con contatore a 0 --> mi blocco ed eseguo un nuovo task che attendeva di partire */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(7, (s==E_OK), 6);
#else
  WaitSem(&mySem);
  EE_assert(7, TRUE, 6);
#endif
  TerminateTask();
}

TASK(ExtTask2)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  
  EE_assert(4, TRUE, 3);

  /* WaitSem chiamata con contatore a 0 e coda sem non vuota --> mi blocco ed il task è accodato come ultimo */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(10, (s==E_OK), 9);
#else
  WaitSem(&mySem);
  EE_assert(10, TRUE, 9);
#endif

  TerminateTask();
}


TASK(BasTask)
{
  StatusType s;
  
  EE_assert(6, TRUE, 5);
  
  /* SemPost chiamato in un task con contatore =0 e qualcuno bloccato --> sblocco un task e parte il task sbloccato */
  s = PostSem(&mySem);
  EE_assert(8, (s==E_OK), 7);

  /* SemPost chiamato in un task con contatore =0 e qualcuno bloccato --> sblocco un task e il task sbloccato va in coda ready */
  s = PostSem(&mySem);
  EE_assert(9, (s==E_OK), 8);
  
  TerminateTask();
}


int myErrorCounter;
void ErrorHook(StatusType Error)
{
  myErrorCounter++;
}

int main(void)
{

#if defined(__CORTEX_MX__)
  /*Initializes Erika related stuffs*/
  EE_system_init();
#endif

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  StartOS(OSDEFAULTAPPMODE);

  EE_assert(5, TRUE, 4);

  ActivateTask(BasTask);

  EE_assert(11, TRUE, 10);
  
  EE_assert_range(0,1,11);
  EE_assert_last();
  
  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}
