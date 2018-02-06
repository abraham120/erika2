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
 * CVS: $Id: code.c,v 1.3 2006/01/05 14:35:53 pj Exp $
 */

/* Test Description:
   This test has 4 tasks with priority th1<th2<th3<th4

   This test uses:
   - (BCC1 or BCC2) + Multistack
   - StartOS
   - ActivateTask into StartupHook (no preemption)
   - TerminateTask on the base level
   - ChainTask on the base and on a nested level
   - Schedule with no preemption
*/

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

/* 0-10: the assertion tested by threads
   11-: assertions used by PreTaskHook and PostTaskHook
*/

EE_TYPEASSERTVALUE EE_assertions[20];

#define TRUE 1

#if defined(__ARM7GNU__)
#if defined(__TRISCENDA7S__)
void init_drivers(void);		//definito in initdrvs.c
#endif
#endif

#if defined(__JANUS__)
EE_UINT16 fiq_arm0_handler(EE_UINT16 etu0_fir)
{
  return etu0_fir;
}

/* this  was used to program the EIC controller... */
void user_handler1(void)
{
}
#endif

/*
 * Display a number during a short pause 
 */
//#define LOOP_LENGHT 100000
//#define LOOP_LENGHT 10000
#define LOOP_LENGHT 1000
//#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1
void pause_and_display(int disp)
{
  int i=0;
    
#ifdef __PLAY_NOTE_SUPPORT__
  EE_play_note(_DO1, 15);
#endif
  
#if defined(__TRISCENDA7S__) && defined(__LED_USED__)
	 for (i=0; i<LOOP_LENGHT; i++)    EE_LED_display(disp);
#else
  int j=0;
	 for (i=0; i<LOOP_LENGHT; i++) {
#ifdef __LCD_USED__        
    	EE_lcd_display(disp);
#endif
    	for(j=0; j<10; j++) {
      	/* do nothing */
    }
  }
#endif
}

#ifdef __OO_HAS_PRETASKHOOK__
//Pretaskhook uses assertions 11, 13, 15, 17, ...

volatile int pretaskcount = 0;
TaskType pretask;

void PreTaskHook(void)
{
  pretaskcount++;

  GetTaskID(&pretask);

  EE_assert(9+pretaskcount*2, TRUE, (pretaskcount==1)? 1:8+pretaskcount*2);
    
}
#endif

#ifdef __OO_HAS_POSTTASKHOOK__
volatile int posttaskcount = 0;
TaskType posttask;

void PostTaskHook(void)
{
  posttaskcount++;

  GetTaskID(&posttask);

  EE_assert(10+posttaskcount*2, posttask==pretask, 9+posttaskcount*2);    
}
#endif

#ifdef __OO_HAS_ERRORHOOK__
volatile int errorhookcount = 0;
void ErrorHook(StatusType Error)
{
  errorhookcount++;
}
#endif

void StartupHook(void)
{
  EE_assert(2, TRUE, 1);
  ActivateTask(0);
  EE_assert(3, TRUE, 2);
  ActivateTask(1);
  EE_assert(4, TRUE, 3);
}

void main(void)
{
  EE_assert(1, TRUE, EE_ASSERT_NIL);

#ifdef __H8__
    EE_init();
#else
#ifdef __LEDS_USED__
    EE_leds_init();
#endif
#ifdef __LCD_USED__
    EE_lcd_init();
#endif
#endif
#ifdef __TRISCENDA7S__
	 init_drivers();
#endif

  StartOS(OSDEFAULTAPPMODE);

  EE_assert_last();
}
