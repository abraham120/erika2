/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * A minimal EE demo for BCC2 mode testing. Task1 is a non-preemptive task
 * and Task2 can have pending activations.
 * Author: 2013  Giuseppe Serano
 * Based on examples/s12xs/porting_examples/monostack/EEtest7
 */


#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#include <avr/io.h>

#ifndef	F_CPU
/*! \brief Define default CPU frequency, if this is not already defined. */
#define	F_CPU	2000000UL
#endif

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TIMER_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_ACTIVATIONS,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* Counters */
volatile int timer_fired = 0;
volatile int timer_divisor = 0;
volatile int task1_fired = 0;
volatile int task2_fired = 0;
volatile int task1_ended = 0;
volatile int task2_ended = 0;
volatile int isr1_fired = 0;
volatile int counter = 0;

/* Stack Pointers */
volatile EE_UINT16 task2_sp = 0x0000U;
volatile EE_UINT16 task1_sp = 0x0000U;
volatile EE_UINT16 main_sp = 0x0000U;

EE_UINT16 EE_currentSP( void ) {
  __asm__ __volatile__(
    /* r24:r25 = SP */
    "in	r24, 0x3D\n"	/* SPL -> r24 */
    "in	r25, 0x3E\n"	/* SPH -> r25 */
    ::
  );
}

/*
 * Access a global symbol.
 */
#define	EE_AVR8_REQUEST_SYM(symbol)				\
	__asm__ __volatile__(					\
		".global " EE_PREPROC_STRING(symbol)		\
		"\n ldi r30, lo8(" EE_PREPROC_STRING(symbol)	\
		")\n" ::					\
	)

/*
 * Request IRQ Entry global symbol.
 */
#define	EE_AVR8_REQUEST_IRQ_ENTRY(entry)	\
	EE_AVR8_REQUEST_SYM(EE_PREPROC_JOIN(tag_,entry))

__INLINE__ void __ALWAYS_INLINE__ EE_pmic_init(void)
{
  EE_AVR8_REQUEST_IRQ_ENTRY(OSC_XOSCF_vect);
  PMIC.CTRL |= ( PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm );
}

void EE_timer_init()
{
	/* Set up Timer/Counter 0 with three Compare Match interrupts. */
	TCC0.CTRLB = TC_WGMODE_NORMAL_gc;
#ifdef	EE_AVR8_TCC0_OVF_ISR_PRI
	TCC0.INTCTRLA = (EE_UREG) TC_OVFINTLVL_HI_gc;
#else
	TCC0.INTCTRLA = (EE_UREG) TC_OVFINTLVL_OFF_gc;
#endif
	TCC0.PER = 0x00ff; /* Period: 0x00ff */
}

void EE_timer_start()
{
	TCC0.CTRLA = TC_CLKSEL_DIV1_gc; /* Run at maximum speed. */
}

void EE_timer_stop()
{
	TCC0.CTRLA = TC_CLKSEL_OFF_gc;
}

/*
 * Timer ISR2
 */
ISR2(EE_AVR8_TCC0_OVF_ISR)
{

  isr1_fired++;

  timer_divisor++;
  if (timer_divisor == 2000)
  {

    timer_divisor = 0;
    timer_fired++;
    if (timer_fired == 1) {
      EE_assert(EE_ASSERT_TIMER_FIRED, timer_fired == 1, EE_ASSERT_TASK2_FIRED);
    }

    ActivateTask(Task1);

    EE_timer_stop();

  }

}

/*
 * TASK 1
 */
TASK(Task1)
{

  EE_UINT16	curr_sp;

  curr_sp = EE_currentSP();
  if (curr_sp != task1_sp) {
    task1_sp = curr_sp;
  }

  task1_fired++;
  if (task1_fired == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, task1_fired == 1, EE_ASSERT_TIMER_FIRED);
  }

  ActivateTask(Task2);

#if	0	/* Forgetfulness Test!!! */
  TerminateTask();
  task1_ended++;
#endif	/* 0 */

}

/*
 * TASK 2
 */
TASK(Task2)
{

  EE_UINT16	curr_sp;

  curr_sp = EE_currentSP();
  if (curr_sp != task2_sp) {
    task2_sp = curr_sp;
  }

  task2_fired++;
  if ((task2_fired % 5) == 1) {

    if (task2_fired == 1) {
      EE_assert(EE_ASSERT_TASK2_FIRED, task2_fired == 1, EE_ASSERT_INIT);
    }
    EE_timer_start();
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);
    ActivateTask(Task2);

  }

  TerminateTask();

  task2_ended++;

}

/*
 * MAIN TASK
 */
int main(void)
{

  EE_UINT16	curr_sp;

  EE_pmic_init();

  /* EE_hal_enableIRQ(); */	/* Done by StartOS() */

  EE_timer_init();

  EE_assert(EE_ASSERT_INIT, EE_TRUE, EE_ASSERT_NIL);

  StartOS(OSDEFAULTAPPMODE);

  ActivateTask(Task2);

  while(task2_fired < 5);

  EE_assert(
    EE_ASSERT_TASK2_ACTIVATIONS, task2_fired == 5, EE_ASSERT_TASK1_FIRED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASK2_ACTIVATIONS);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    curr_sp = EE_currentSP();
    if (curr_sp != main_sp) {
      main_sp = curr_sp;
    }

    while (counter % 10000) counter++;
    ActivateTask(Task2);
    counter++;

  }

}
