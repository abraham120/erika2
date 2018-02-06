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

#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifdef __EVALUATOR7T__
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"
#endif

#ifdef __PIC30__
#include "mcu/microchip_dspic/inc/ee_timer.h"
#endif

#ifdef __CORTEX_M0__
#include "lpc12xx_libcfg_default.h"
#endif

#ifdef EE_PPCE200Z225
#include "mcu/st_spc574k/inc/ee_spc574k_stm.h"
#endif

#define TRUE 1

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[20];

DeclareTask(Task1);
DeclareTask(Task2);

volatile int ISR2_fired;

#if defined(__NIOS2__)
#include "sys/alt_alarm.h"
static void myISR2(void);
alt_u32 mycallback (void* arg)
{
  myISR2();
  return 0;
}
#endif

#if defined(__ARM7GNU__) && defined(__JANUS__)
#include "arm7gnu/janus/stub.h"
_ISR2(myISR2)
#else
	#if defined(__HCS12XS__) || defined(__MC9S12__)
		#include "cpu/hs12xs/inc/ee_irqstub.h"
		#include "ee_s12regs.h" 
		#include "mcu/hs12xs/inc/ee_timer.h"
		#define myISR2 CPU12TimerCh0ISR
		ISR2(myISR2)
	#else
		#if defined(__CORTEX_MX__)
		ISR2(SysTick_Handler)
		#else
			#if defined (__RX200__)
			ISR2(cmia0_handler)
			#else
				#if defined (EE_TRICORE__)
				ISR2(STM_handler)
				#else
				static void myISR2(void)
				#endif
			#endif
		#endif
	#endif
#endif
{
  StatusType s;

  EE_assert(8, TRUE, 7);
  s = ClearEvent(Event1);
  EE_assert(9, (s==E_OS_CALLEVEL), 8);
  s = WaitEvent(Event1);
  EE_assert(10, (s==E_OS_CALLEVEL), 9);
  
  ISR2_fired=1;

#if defined(__ARM7GNU__) && defined(__JANUS__)
  // Reset the interrupt pending bit on the EIC
  *OCCDEFINT &= ~INTF0B;
#endif

#if defined(__HCS12XS__) || defined(__MC9S12__)
	EE_timer_clear_ISRflag(EE_TIMER_0); 
	EE_timer_disable_ISR(EE_TIMER_0);
	EE_timer_stop();
#endif

/* K2 (SPC574K) specific interrupt handling */
#if defined (EE_PPCE200Z225)
	spc574k_STM_clear_int();	/* Clear isr */
	spc574k_STM_set_counter(0);	/* Reset initial counter value to 0 */
#endif
}

TASK(Task1)
{
  StatusType s;
  EventMaskType EventMask;

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  EnableAllInterrupts();
  EE_assert(2, TRUE, 1);

  s = SetEvent(INVALID_TASK, Event1);
  EE_assert(3, (s==E_OS_ID), 2);

  s = SetEvent(Task1, Event1);
  EE_assert(4, (s==E_OS_ACCESS), 3);

  s = SetEvent(Task2, Event1);
  EE_assert(5, (s==E_OS_STATE), 4);

  s = ClearEvent(Event1);
  EE_assert(6, (s==E_OS_ACCESS), 5);

  // Trigger interrupt
#if defined(__ARM7GNU__) && defined(__EVALUATOR7T__)
  EE_timer_0_start();
#endif

#if defined(__ARM7GNU__) && defined(__JANUS__)
  *OCEN |= ENF0;
  *OCCDEFIE |= IEF0B;
#endif

  EE_assert(7, TRUE, 6);

  while(!ISR2_fired);

  EE_assert(11, TRUE, 10);

  s = GetEvent(INVALID_TASK, &EventMask);
  EE_assert(12, (s==E_OS_ID), 11);

  s = GetEvent(Task1, &EventMask);
  EE_assert(13, (s==E_OS_ACCESS), 12);

  s = GetEvent(Task2, &EventMask);
  EE_assert(14, (s==E_OS_STATE), 13);

  s = WaitEvent(Event1);
  EE_assert(15, (s==E_OS_ACCESS), 14);

  ChainTask(Task2);
}

TASK(Task2)
{
  StatusType s;

  EE_assert(16, TRUE, 15);

  s = GetResource(Resource1);
  EE_assert(17, (s==E_OK), 16);

  s = WaitEvent(Event1);
  EE_assert(18, (s==E_OS_RESOURCE), 17);
  
  s = ReleaseResource(Resource1);
  EE_assert(19, (s==E_OK), 18);

  TerminateTask();
}

#ifndef __OO_AUTOSTART_TASK__
void StartupHook(void)
{
  ActivateTask(Task1);
}
#endif

int main(int argc, char **argv)
{
#if defined(__ARM7GNU__) && defined(__EVALUATOR7T__)

#define COUNTDOWN ((1 * 1000 * 1000 * 1000) / 20) /* 1 sec */

  EE_IC_clear_pending_IRQ();
  EE_IC_enable_external_IRQ(IRQ_TIMER0_MASK);
  EE_timer_0_set(((1 * 1000 * 1000 * 1000) / 20)/10); /* 100 msec */

#endif

#if defined(__ARM7GNU__) && defined(__JANUS__)

  EE_janus_IRQ_enable_channel(IRQ_ETUOCFB);
  EE_janus_IRQ_set_priority(IRQ_ETUOCFB, 1);
  EE_janus_IRQ_set_handler(IRQ_ETUOCFB, (EE_ADDR)myISR2);
  EE_janus_IRQ_enable_EIC();
  *OCREGF0B = 0x4FFF;

#endif

#if defined(__NIOS2__)
  {
    alt_alarm myalarm;
    alt_alarm_start(&myalarm, 100, mycallback, NULL);
  }

#endif

#if defined(__HCS12XS__) || defined(__MC9S12__)

  EE_set_peripheral_frequency_mhz(8);
  EE_timer_init_ms(EE_TIMER_0, 10, EE_TIMER_ISR_ON);
  EE_timer_start();

#endif

#if defined(__PPCE200Z7__) || defined(EE_PPCE200Z4)
  EE_e200z7_register_ISR(10, myISR2, 0);
  EE_e200z7_setup_decrementer(3000000);
#elif defined (EE_PPCE200Z225) /* K2 does not have decrementers */
  /* K2 (SPC574K) specific interrupt handling. STM_2 is mapped to isr 44 */
  EE_e200z7_register_ISR(16 + 44, myISR2, 1);	/* Register ISR */
  /* STM_2 initialization */
  spc574k_STM_set_prescaler(1);	/* Set prescaler to 0 */
  spc574k_STM_cmp(3000000);		/* Set timer match value to 3000000 */
  spc574k_STM_set_counter(0); 	/* Reset initial counter value to 0 */
  spc574k_STM_enable();			/* Enable STM_2 and start counting */
#endif

#if defined(__PIC30__)
  EE_timer_soft_init(EE_TIMER_1, 3000000);
  EE_timer_set_callback(EE_TIMER_1, (EE_ISR_callback)myISR2);
  EE_timer_start(EE_TIMER_1);
#endif

#if defined(__CORTEX_MX__)
  /*Initializes Erika related stuffs*/
  EE_system_init();
#endif

#if defined(__CORTEX_M0__)
  /* Generate systemtick interrupt */
  SysTick_Config(3000000); 
  /* Priority SysTick = 00*/
  NVIC_SetPriority(SysTick_IRQn, 0);
#endif

#if defined(__CORTEX_M4__)
  EE_systick_set_period(3000000);
  EE_systick_enable_int();
  EE_systick_start();
#endif

#if defined (__RX200__)
	EE_systick_start();
	EE_systick_start();
	EE_systick_set_period(0x0C, 0x9C);
	EE_systick_enable_int();
#endif

#if defined(EE_TRICORE__)
  EE_tc2Yx_stm_set_clockpersec();
  EE_tc2Yx_stm_set_sr0(1000000U, EE_ISR2_ID_STM_handler);
#endif
  StartOS(OSDEFAULTAPPMODE);

  EE_assert_range(0,1,19);
  EE_assert_last();

  return 0;
}

#ifdef __JANUS__
EE_UINT16 fiq_arm0_handler(EE_UINT16 etu0_fir)
{
  return etu0_fir;
}
#endif
