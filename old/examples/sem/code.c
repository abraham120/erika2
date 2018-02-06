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
 * Author: 2002 Paolo Gai
 * CVS: $Id: code.c,v 1.4 2006/01/05 14:38:25 pj Exp $
 */

#include "ee.h"
#include "code.h"
#include "sem/sem.h"

/* Simple Semaphore test:
   - The first semaphore is initialized using the static initializer
   - The second semaphore is initialized through a macro

  The test is composed by four threads:
  - A "noise" thread that is activated at every timer interrupt
  - Three threads that implements a (1)producer/(2)consumer protocol

  Depending on the presence of a #define CASE2 the threads have a
  different behavior:

  In particular, thread1 blocks on semP only when thread2 has been
  enqueued on it, to test the case in which the post operation of
  thread1 wakes up a thread with priority less than the system
  ceiling.

  A typical trace of case 2 is: (priority of th1 > th2 > th3)
  th1:W(P), P(P), W(B) (th1 blocks), 
  th2:W(V), P(P), W(V) (th2 blocks),
  th3:P(B) (th1 woken up),
  th1:W(P), P(P) (th2 woken up), W(B) (th1 blocks, switch to th2!)
*/

#define CASE2


EE_SEM semP = {1,EE_NIL,EE_NIL};
EE_SEM semV;

#ifdef CASE2
EE_SEM semB = {0,EE_NIL,EE_NIL};
#endif

int items     = 0;
int produced1 = 0;
int consumed1 = 0;
int consumed2 = 0;

/* Noise task */
void thread0(void)
{
  int i;
  for (i=0; i<1000; i++);

#ifdef __LCD_USED__
  EE_LCD_display(0); 
#endif
}

/* Producer */
void thread1(void)
{
  for (;;) {
	  EE_sem_wait(&semP);
	  items++;
	  produced1++;
	  EE_sem_post(&semV);

#ifdef CASE2
	  EE_sem_wait(&semB);
#endif
#ifdef __LCD_USED__
	  EE_LCD_display(1);
#endif	  
  }
}

/* Consumer 1 */
void thread2(void)
{
  for (;;) {

	  EE_sem_wait(&semV);
	  items--;
	  consumed1++;
	  EE_sem_post(&semP);
#ifdef __LCD_USED__
	  EE_LCD_display(2);
#endif
  }
}

/* Consumer 2 */
void thread3(void)
{
  for (;;) {

#ifdef CASE2
	  EE_sem_post(&semB);
#else
	  EE_sem_wait(&semV);
	  items--;
	  consumed2++;
	  EE_sem_post(&semP);
#endif

#ifdef __LCD_USED__
	  EE_lcd_write_num(3);
#endif
  }
}

void my_init(void);

void main(void)
{
  EE_sem_init(semV,0);
  
  my_init();
  
  EE_thread_activate(1);
  EE_thread_activate(2);
  EE_thread_activate(3);
  
  for (;;) {}
}

