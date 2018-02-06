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
 * CVS: $Id: code.c,v 1.4 2006/10/25 14:31:01 pj Exp $
 */

/* Test Description:
   This test has 4 tasks with 
   - ready priority= dispatch priority r1<r2<r3<r4

   This test uses:
   - MonoStack
   - StartOS
   - ActivateTask into StartupHook (no preemption)
   - TerminateTask on the base level
   - ActivateTask into an ISR2
   - GetResource & ReleaseResource

   threads are identified by numbers... T is the timer, D is the main

   1: starts
   1: lock
   1: timer programming
   1: active wait
   T: Activate 2 (no preemption) (1 ends active wait)
   1: unlock
   2: prempts + terminate
   1: resume
   1: lock
   1: timer programming
   1: active wait
   T: activate 0,3
   3: preempts + terminate (1 ends active wait)
   1: resume
   1: unlock
   1: terminate
   0: starts+terminate
   D: main cycle

*/

#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#ifdef __EVALUATOR7T__
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"
#endif

/* 0-10: the assertion tested by threads
   11-: assertions used by PreTaskHook and PostTaskHook
*/

EE_TYPEASSERTVALUE EE_assertions[22];

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

#ifdef __TRISCENDA7S__
#define COUNTDOWN (10 * 1000)
#else
/*
 * timer #1 reset value (1 sec)
 *
 * 1 sec = 1000 * 1000 * 1000 nsec
 * timer tick = 50 MHz = 20 nsec
 */
//#define COUNTDOWN ((5 * 1000 * 1000 * 1000) / 20) /* 5 sec */
#define COUNTDOWN ((1 * 1000 * 1000 * 1000) / 20) /* 1 sec */
//#define COUNTDOWN ((100 * 1000 * 1000) / 20) /* 100 msec */
//#define COUNTDOWN ((10 * 1000 * 1000) / 20) /* 10 msec */
//#define COUNTDOWN ((1 * 1000 * 1000) / 20) /* 1 msec */
//#define COUNTDOWN ((100 * 1000) / 20) /* 100 usec */
//#define COUNTDOWN ((10 * 1000) / 20) /* 10 usec, too small! */
#endif

/*
 * Display a number during a short pause 
 */
//#define LOOP_LENGHT 100000
//#define LOOP_LENGHT 10000
//#define LOOP_LENGHT 1000
#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1
void pause_and_display(int disp)
{
  int i=0;

#ifdef __PLAY_NOTE_SUPPORT__
  EE_play_note(_DO0, 15);
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

volatile int cycle;

void timer_and_button_handler(void)
{
  static int xxx=0;

  // the timer is stopped and reprogrammed everytime to allow debugging
  // the code without problems...
#if defined(__ARM7GNU__) || defined(__ARM7ADS__)
  EE_timer_1_stop();
#endif

#ifdef __ST10__
  /* stop the timer */
  #pragma asm
 	BCLR T6R
  #pragma endasm
#endif

#ifdef __H8__
  /* stop timerA match interrupt */
  static EE_UINT8 cont=10;
  cont--;
  if (!cont)
  {
    EE_disable_irq(OCIA_IRQ);
    cont=10;
  }
  else
    return;
#endif

  cycle = 0;
  
  if (xxx==0) {
    // first time
    EE_assert(8, 1, 7);
    xxx++;
    ActivateTask(thread2);
    EE_assert(9, 1, 8);
  } else {
    EE_assert(16, 1, 15);
    // second time
    ActivateTask(thread3);
    EE_assert(17, 1, 16);
    ActivateTask(thread0);
    EE_assert(18, 1, 17);
  }
}


#ifdef __OO_HAS_PRETASKHOOK__
volatile int pretaskcount = 0;
void PreTaskHook(void)
{
  pretaskcount++;
}
#endif

#ifdef __OO_HAS_POSTTASKHOOK__
volatile int posttaskcount = 0;
void PostTaskHook(void)
{
  posttaskcount++;
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
  EE_assert(2, 1, 1);
  ActivateTask(1);
  EE_assert(3, 1, 2);
}

int mytimer_start_count=1;
void mytimer_start(void)
{
  if (mytimer_start_count) {
    EE_assert(6, 1, 5);
    mytimer_start_count = 0;
  }
  else
    EE_assert(14, 1, 13);

#if defined(__ARM7GNU__) || defined(__ARM7ADS__)
  EE_timer_1_set(COUNTDOWN);
  EE_timer_1_start();
#endif

#ifdef __ST10__
  /* start the timer */
  #pragma asm
 	BSET T6R
  #pragma endasm
#endif

#ifdef __H8__
  /* start timerA match interrupt */
  EE_t16_reset_ocra_match_flag();
  EE_enable_irq(OCIA_IRQ);
#endif
}

void main(void)
{
  EE_assert(1, 1, EE_ASSERT_NIL);

#if defined(__ARM7GNU__) || defined(__ARM7ADS__)
#ifdef __EVALUATOR7T__

#ifdef __LEDS_USED__
  EE_leds_init();
#endif

#ifdef __LCD_USED__
  EE_lcd_init();
#endif

  EE_IC_clear_pending_IRQ();

#ifdef __TIMER_USED__		/* defined through __TIMER_?_USED__ */
    EE_timer_init();
#endif

#ifdef __TIMER_1_USED__
    EE_IC_enable_external_IRQ(IRQ_TIMER1_MASK);
#endif

#endif /*__EVALUATOR7T__*/
#endif /* ARM7 */

#ifdef __ST10__
  /* program the timer */
  #pragma asm
 	MOV T6IC,ZEROS
 	MOV T6CON,ZEROS
 	MOV T6,ZEROS
	MOV T6IC, #00044h
  #pragma endasm

#endif

#if defined(__TRISCENDA7S__)
  init_drivers();
#endif

#ifdef __H8__
    EE_init();
    
#endif

  StartOS(OSDEFAULTAPPMODE);
}
