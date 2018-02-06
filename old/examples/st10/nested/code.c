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
 * CVS: $Id: code.c,v 1.4 2007/06/01 09:02:28 pj Exp $
 */

/*
 * ST10 Nested Interrupt Test
 *
 * This demo uses the EDF Kernel and 3 CAPCOMs ro raise interrupts.
 *
 * Each interrupt basically activates a thread and wait on an infinite 
 * loop that a variable called spin is set to 1.
 *
 * Finally, spin is set to 1 by a high frequency interrupt.
 *
 * A tipical scenario is the following one (it repeats every 200 T8 units)
 *
 * 40  -> Capcom 24 -> Interrupt -> spin lock
 * 80  -> Capcom 25 -> the interrupt preempts the previous one -> spin lock
 * 100 -> Capcom 26 -> spin = 1 -> Interrupt from capcom 25 exit from the interrupt
 * 200 -> Capcom 26 -> spin = 1 -> Interrupt from capcom 24 exit from the interrupt
 * Then, the threads executes in the following order:
 * thread1 (2 times), thread2, thread3
 */




#include "ee.h"

volatile int th1, th2, th3;


void thread1(void)
{
  th1++;
}

void thread2(void)
{
  th2++;
}

void thread3(void)
{
  th3++;
}

// initializes the CAPCOMS
void my_irq_init(void);

void main(void)
{
  my_irq_init();

  for (;;) {}
}

