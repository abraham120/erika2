/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Simple test for spinlocks, shared memory, leds and buttons
 * Author: 2012 Francesco Esposito
 */

#include "support.h"
#include <ee.h>
#include <cpu/e200zx/inc/ee_irq.h>
#include "board/freescale_xpc564xl/inc/ee_board.h"

/* My shared data */
#ifdef __MSRP__

#ifdef USE_PRAGMAS
#pragma section EE_SHARED_NOTINIT_BEGIN
#pragma section EE_SHARED_FAST_NOTINIT_BEGIN
volatile int shared_data[SHARED_LONG_LEN];
#pragma section EE_SHARED_END
#pragma section EE_SHARED_FAST_OR_SLOW_END
#else
volatile int EE_SHARED_UDATA shared_data[SHARED_LONG_LEN];
#endif
#else
volatile int shared_data[SHARED_LONG_LEN];
#endif

/* Shared variable */
int shared_data_local[SHARED_LONG_LEN];

DeclareTask(TaskZ6_1);
DeclareTask(TaskZ6_2);
DeclareTask(TaskZ6_3);
DeclareTask(TaskZ6_4);

/* First task */
TASK(TaskZ6_1)
{
	delay(MEDIUM_DELAY);
	/* Write shared_data_local */
	set_shared_value(1,shared_data_local);

	ActivateTask(TaskZ6_2);
	TerminateTask();
}
int pippo;
/* Second task */
TASK(TaskZ6_2)
{
	int check_res;
	delay(SMALL_DELAY);

	/* Check shared_data_local */
	check_res = check_shared_value(1,shared_data_local);

	pippo = check_res;

	/* Exec concurrently with disturbing task */
	lock_var();
	delay(LARGE_DELAY);
	set_shared_value(2,shared_data);
	unlock_var();

	delay(MEDIUM_DELAY);

	/* If previous check is ok activate TaskZ6_3 */
	if (check_res == 1)
		ActivateTask(TaskZ6_3);
	/* If check is not ok the task activation chain terminates here */

	TerminateTask();
}

/* Third Task */
TASK(TaskZ6_3)
{
	int check_res;
	delay(LARGE_DELAY);
	/* 
	* Check shared_data. This is a syncronous read so
	* spinlock or resource use is unnecessary,
	* the variable is always checked after it is written
	*/
	check_res = check_shared_value(2,shared_data);
	
	ActivateTask(TaskZ6_1);
	TerminateTask();
}

/* Third Task */
TASK(TaskZ6_4)
{
	/* Activate disturbing task */
	/* It may reside in Z0 or Z6 according with OIL definition */
	delay(MEDIUM_DELAY);
	ActivateTask(disturbing_task);
}

/*
 * Interrupt handler for the decrementer timer
 */
static void timer_interrupt(void)
{
	ActivateTask(TaskZ6_4);
}

static void init_decrementer_timer(void)
{
	EE_e200z7_register_ISR(10, timer_interrupt, 1);
	EE_e200z7_setup_decrementer(26000000);
}


static void Buttons_Interrupt0(void)
{
   static EE_UINT8 recall = 0;

   if (recall == (EE_UINT8)0U) {
      EE_led_set(0, 0);
      recall = (EE_UINT8)1U;
   }
   else {
      EE_led_set(0, 1);
      recall = (EE_UINT8)0U;
   }

   EE_buttons_clear_ISRflag(BUTTON_0);
}

static void Buttons_Interrupt1(void)
{
   static EE_UINT8 recall = 0;

   if (recall == (EE_UINT8)0U) {
      EE_led_set(1, 0);
      recall = (EE_UINT8)1U;
   }
   else {
      EE_led_set(1, 1);
      recall = (EE_UINT8)0U;
   }

   EE_buttons_clear_ISRflag(BUTTON_1);
}

static void Buttons_Interrupt2(void)
{
   static EE_UINT8 recall = 0;

   if (recall == (EE_UINT8)0U) {
      EE_led_set(2, 0);
      recall = (EE_UINT8)1U;
   }
   else {
      EE_led_set(2, 1);
      recall = (EE_UINT8)0U;
   }

   EE_buttons_clear_ISRflag(BUTTON_2);
}

/* Led 4 not working: PD7 pin of the microcontroller bugged */
static void Buttons_Interrupt3(void)
{
   static EE_UINT8 recall = 0;

   if (recall == (EE_UINT8)0U) {
      EE_led_set(3, 0);
      recall = (EE_UINT8)1U;
   }
   else {
      EE_led_set(3, 1);
      recall = (EE_UINT8)0U;
   }

   EE_buttons_clear_ISRflag(BUTTON_3);
}

/*
 * MAIN TASK
 */
int main(void)
{

	unsigned int current_status;

	EE_buttons_init();
	EE_e200z7_register_ISR(41 + 16, Buttons_Interrupt0, 4); /* 41=eirq0 */
	EE_e200z7_register_ISR(42 + 16, Buttons_Interrupt1, 3); /* 42=eirq1 */
	EE_e200z7_register_ISR(43 + 16, Buttons_Interrupt2, 2); /* 43=eirq2 */
	EE_e200z7_register_ISR(44 + 16, Buttons_Interrupt3, 1); /* 44=eirq3 */
	EE_e200z7_enableIRQ();
	EE_leds_init();

	/* 
	 * If button 0 is pressed at start time, the application enters
	 * into end-less loop...
	 * ...just to test button 0.
	 */
	if(EE_button_get_B0())
		while(1);

	/* 
	 * if the application does not enter into end-less loop,
	 * further button0 pressions turn leds on/off.
	 */

	/* System start-up: start slave core in VLE/PPC mode */
#ifdef __MSRP__
	sys_start_up(VLE_MODE);
#endif

	/*current_status = EE_mpc5643l_lsm_or_dpm();*/

	/* Init decrementer */
	init_decrementer_timer();

	/* Start Operating System */
	StartOS(OSDEFAULTAPPMODE);

	while(1)
	;

	return 0;
}
