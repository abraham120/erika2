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
 * CVS: $Id: code.c,v 1.1 2006/07/11 09:16:42 pj Exp $
 */

#include "ee.h"
#include "cpu/pic30/inc/ee_irqstub.h"

volatile int j;

// in T1.S
void T1_program(void);
void T1_clear(void);


ISR2(_T1Interrupt)
{
  // clear the interrupt source
  T1_clear();

  j++;
  /* activate thread */
  ActivateTask(Task0);
}



void __attribute__((__interrupt__)) _T3Interrupt(void)
{
  j++;
}

void __attribute__((__interrupt__)) _DefaultInterrupt(void)
{
  j++;
}

TASK(Task0)
{
  GetResource(MUTEX_sync);

  ActivateTask(Task1);
    
  ReleaseResource(MUTEX_sync);
  //  TerminateTask();
}



TASK(Task1)
{
  ActivateTask(Task2);
  //  TerminateTask();
}



TASK(Task2)
{
  //  GetResource(RES_SCHEDULER);

  ActivateTask(Task3);

  //  ReleaseResource(RES_SCHEDULER);
  //  TerminateTask();
}


volatile int task3_times;
TASK(Task3)
{
  task3_times++;
  //  TerminateTask();
}

void StartupHook(void)
{
}

void main(void)
{
  /* Program T1 */
  T1_program();

  //  StartOS(OSDEFAULTAPPMODE);

  /* activate the first thread */
  ActivateTask(Task0);

  for (;;);
}
