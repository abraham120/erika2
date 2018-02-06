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
#include "ee_irq.h"

#ifdef __CORTEX_M0__
#include "lpc12xx_libcfg_default.h"
#endif

#ifdef EE_PPCE200Z225
#include "mcu/st_spc574k/inc/ee_spc574k_stm.h"
#endif

/* Assertions */
#include "test/assert/inc/ee_assert.h"
#define TRUE 1

/* assertion data */
EE_TYPEASSERTVALUE EE_assertions[21];

volatile int irqStatus=0;
volatile int BasTask_cancontinue=0;
volatile int BasTaskLow_cancontinue=0;

SemType mySem;

DeclareTask(ExtTask);
DeclareTask(BasTask);
DeclareTask(BasTaskLow);
DeclareTask(ExtTaskLow);

TASK(ExtTask)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  
  EE_assert(3, TRUE, 2);

  /* WaitSem chiamata con contatore a 0 --> mi blocco ed eseguo un task preemptato */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(8, (s==E_OK), 7);
#else
  WaitSem(&mySem);
  EE_assert(8, TRUE, 7);
#endif

  TerminateTask();
}

TASK(BasTask)
{
  int v;
  
  EE_assert(2, TRUE, 1);
  ActivateTask(ExtTask);
  EE_assert(4, TRUE, 3);
 
  v = GetValueSem(&mySem);
 
  EE_assert(5, (v == -1), 4);

  /* the IRQ can now do the Post... */
  irqStatus = 1;
  while (!BasTask_cancontinue);

  EE_assert(9, TRUE, 8);

  TerminateTask();
}


TASK(BasTaskLow)
{
  EE_assert(16, TRUE, 15);

  /* we wait for the Interrupt. the interrupt will execute a sempost waking up 
   * ExtTaskLow which will not preempt BasTaskLow */
  irqStatus = 2;
  while (!BasTaskLow_cancontinue);

  EE_assert(19, TRUE, 18);
 
  TerminateTask();
}

TASK(ExtTaskLow)
{
#ifdef __OO_EXTENDED_STATUS__
  StatusType s;
#endif
  
  EE_assert(12, TRUE, 11);

  /* WaitSem chiamata con contatore a 0 --> mi blocco e torno al main */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(14, (s==E_OK), 13);
#else
  WaitSem(&mySem);
  EE_assert(14, TRUE, 13);
#endif

  /* WaitSem chiamata con contatore a 0 --> mi blocco e torno al main */
#ifdef __OO_EXTENDED_STATUS__
  s = WaitSem(&mySem);
  EE_assert(20, (s==E_OK), 19);
#else
  WaitSem(&mySem);
  EE_assert(20, TRUE, 19);
#endif


  TerminateTask();
}



int myErrorCounter;
void ErrorHook(StatusType Error)
{
  myErrorCounter++;
}

#if defined(__NIOS2__)
/* call the ERIKA Enterprise tick function for the Counter1 counter! */
static void handle_timer_interrupt(void* context, alt_u32 id)
{
  StatusType s;
  /* clear the interrupt */
  IOWR_ALTERA_AVALON_TIMER_STATUS (HIGH_RES_TIMER_BASE, 0);
  
  if (irqStatus==1) {
    /* SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * preemption alla fine dell'ISR */
    EE_assert(6, TRUE, 5);
    s = PostSem(&mySem);
    EE_assert(7, (s==E_OK), 6);
    BasTask_cancontinue = 1;
    irqStatus = 0;
  }
  
  if (irqStatus==2) {
    /*  SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * no preemption alla fine dell'ISR */
    EE_assert(17, TRUE, 16);
    s = PostSem(&mySem);
    EE_assert(18, (s==E_OK), 17);
    BasTaskLow_cancontinue = 1;
    irqStatus = 0;
  }
  
}
#endif

#if defined(__HCS12XS__) || defined(__MC9S12__)
	#include "ee_s12regs.h" 
	#include "mcu/hs12xs/inc/ee_timer.h"
	#define myISR2 CPU12TimerCh0ISR
	ISR2(myISR2) {
		StatusType s;
		EE_timer_clear_ISRflag(EE_TIMER_0); 
		
	  if (irqStatus==1) {
	    /* SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
	     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
	     * preemption alla fine dell'ISR */
	    EE_assert(6, TRUE, 5);
	    s = PostSem(&mySem);
	    EE_assert(7, (s==E_OK), 6);
	    BasTask_cancontinue = 1;
	    irqStatus = 0;
	  }
  
	  if (irqStatus==2) {
	    /*  SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
	     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
	     * no preemption alla fine dell'ISR */
	    EE_assert(17, TRUE, 16);
	    s = PostSem(&mySem);
	    EE_assert(18, (s==E_OK), 17);
	    BasTaskLow_cancontinue = 1;
	    irqStatus = 0;
	  }
	}
#endif

#if defined(__PPCE200Z7__) || defined(EE_PPCE200Z4) || defined (EE_PPCE200Z225)
static void handle_timer_interrupt(void)
{
  StatusType s;

  if (irqStatus==1) {
    /* SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * preemption alla fine dell'ISR */
    EE_assert(6, TRUE, 5);
    s = PostSem(&mySem);
    EE_assert(7, (s==E_OK), 6);
    BasTask_cancontinue = 1;
    irqStatus = 0;
  }
  
  if (irqStatus==2) {
    /*  SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * no preemption alla fine dell'ISR */
    EE_assert(17, TRUE, 16);
    s = PostSem(&mySem);
    EE_assert(18, (s==E_OK), 17);
    BasTaskLow_cancontinue = 1;
    irqStatus = 0;
  }

/* K2 (SPC574K) specific interrupt handling */
#if defined (EE_PPCE200Z225)
	spc574k_STM_clear_int();	/* Clear isr */
	spc574k_STM_set_counter(0);	/* Reset initial counter value to 0 */
#endif
}
#endif

#if defined(__CORTEX_MX__) || defined(EE_TRICORE__)
#ifdef __CORTEX_MX__
ISR2(SysTick_Handler)
#elif defined(EE_TRICORE__)
ISR2(STM_handler)
#endif
{
  StatusType s;

  if (irqStatus==1) {
    /* SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * preemption alla fine dell'ISR */
    EE_assert(6, TRUE, 5);
    s = PostSem(&mySem);
    EE_assert(7, (s==E_OK), 6);
    BasTask_cancontinue = 1;
    irqStatus = 0;
  }
  
  if (irqStatus==2) {
    /*  SemPost chiamato in un IRQ con contatore =0 e qualcuno bloccato 
     * --> sblocco un task e il task sbloccato va in coda ready, no preemption, 
     * no preemption alla fine dell'ISR */
    EE_assert(17, TRUE, 16);
    s = PostSem(&mySem);
    EE_assert(18, (s==E_OK), 17);
    BasTaskLow_cancontinue = 1;
    irqStatus = 0;
  }
  
}
#endif /* defined(__CORTEX_MX__) || defined(EE_TRICORE__) */

void StartupHook(void)
{
	#if defined(__NIOS2__)
  	/* set to free running mode */
  	IOWR_ALTERA_AVALON_TIMER_CONTROL (HIGH_RES_TIMER_BASE, 
            ALTERA_AVALON_TIMER_CONTROL_ITO_MSK  |
            ALTERA_AVALON_TIMER_CONTROL_CONT_MSK |
            ALTERA_AVALON_TIMER_CONTROL_START_MSK);

  	/* register the interrupt handler, and enable the interrupt */
  	alt_irq_register (HIGH_RES_TIMER_IRQ, NULL, handle_timer_interrupt);    
  	#endif
  	#if defined(__HCS12XS__) || defined(__MC9S12__)
		EE_set_peripheral_frequency_mhz(8);
		EE_timer_init_ms(EE_TIMER_0, 10, EE_TIMER_ISR_ON);
		EE_timer_start();
	#endif
	#if defined(__PPCE200Z7__) || defined(EE_PPCE200Z4)
		EE_e200z7_register_ISR(10, handle_timer_interrupt, 0);
		EE_e200z7_setup_decrementer(2000000);
	#elif defined (EE_PPCE200Z225) /* K2 does not have decrementers */
		/* K2 (SPC574K) specific interrupt handling.STM_2 is mapped to isr 44 */
		/* Register ISR */
		EE_e200z7_register_ISR(16 + 44, handle_timer_interrupt, 1);
		/* STM_2 initialization */
		spc574k_STM_set_prescaler(1);	/* Set prescaler to 0 */
		spc574k_STM_cmp(2000000);		/* Set timer match value to 3000000 */
		spc574k_STM_set_counter(0); 	/* Reset initial counter value to 0 */
		spc574k_STM_enable();			/* Enable STM_2 and start counting */
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
#if defined(EE_TRICORE__)
  EE_tc2Yx_stm_set_clockpersec();
  EE_tc2Yx_stm_set_sr0(1000000U, EE_ISR2_ID_STM_handler);
#endif
}



int main(void)
{
  StatusType s;
  unsigned int v;

#if defined(__CORTEX_MX__)
  /*Initializes Erika related stuffs*/
  EE_system_init();
#endif

	#if defined(__PPCE200Z7__) || defined(EE_PPCE200Z4)
	EnableAllInterrupts();
	#endif

  EE_assert(1, TRUE, EE_ASSERT_NIL);

  InitSem(&mySem, 0);
  
  StartOS(OSDEFAULTAPPMODE);

  EE_assert(10, TRUE, 9);
  
  v = GetValueSem(&mySem);
 
  EE_assert(11, (v == 0), 10);
  
  /* activate the ExtTasklow */
  s = ActivateTask(ExtTaskLow);

  EE_assert(13, (s==E_OK), 12);

  /* SemPost chiamato nel main con contatore =0 e qualcuno bloccato 
   * --> sblocco un task e parte il task sbloccato */
  s = PostSem(&mySem);
  EE_assert(15, (s==E_OK), 14);
  
  /* activate BasTaskLow, which has higher priority than ExtTasklow */
  s = ActivateTask(BasTaskLow);

  EE_assert(21, (s==E_OK), 20);

  EE_assert_range(0,1,21);
  EE_assert_last();
  
  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
}
