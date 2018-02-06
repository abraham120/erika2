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
 * A minimal EE demo that demonstrates how to work with the MULTISTACK mode and
 * semaphores.
 * In this demo is shown that a task can be interrupted with a call to
 * ready2stacked (with an activation of a high priority task) and resumed with a
 * call to stkchange (if the high priority task is blocked on a shared
 * resource).
 * Author: 2011  Gianluca Franchino
 *               Giuseppe Serano
 * Based on examples/s12xs/porting_examples/multistack/EEtest6
 */


#include "ee.h"
#include "kernel/sem/inc/ee_sem.h"
#include "lpc12xx_libcfg_default.h"
#include "test/assert/inc/ee_assert.h"

#define TRUE 1

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_TASK2_FIRED,
  EE_ASSERT_TASK1_POST,
  EE_ASSERT_TASK2_ENDED,
  EE_ASSERT_TASK1_ENDED,
  EE_ASSERT_TASKS_ENDED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* This semaphore is initialized automatically */
SemType P = STATICSEM(1);

/* This semaphore is initialized inside the Background Task */
SemType V;

volatile int taskp_counter = 0;
volatile int taskc_counter = 0;
volatile int taskp_ended = 0;
volatile int taskc_ended = 0;

/*
 * LED INITIALIZATION
 */
void led_init(void) 
{
  IOCON_PIO_CFG_Type PIO_mode;
  
  IOCON_StructInit(&PIO_mode);
  
  PIO_mode.type = IOCON_PIO_0_7;
  IOCON_SetFunc(&PIO_mode);
  GPIO_SetDir(LPC_GPIO0, 7, 1);
//GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
}


/*
 * TASK 1
 */
TASK(Task1)
{
  taskp_counter++;
  EE_assert(EE_ASSERT_TASK1_FIRED, taskp_counter == 1, EE_ASSERT_INIT);
  ActivateTask(Task2);
  
  GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
  
  EE_assert(EE_ASSERT_TASK1_POST, taskp_counter == 1, EE_ASSERT_TASK2_FIRED);
  PostSem(&V); 
  EE_assert(EE_ASSERT_TASK1_ENDED, taskp_counter == 1, EE_ASSERT_TASK2_ENDED);
  taskp_ended++;
}

/*
 * TASK 2
 */
TASK(Task2)
{
  taskc_counter++;
  EE_assert(EE_ASSERT_TASK2_FIRED, taskc_counter == 1, EE_ASSERT_TASK1_FIRED);
  WaitSem(&V);
  GPIO_SetLowLevel(LPC_GPIO0, 7, 1);
  EE_assert(EE_ASSERT_TASK2_ENDED, taskc_counter == 1, EE_ASSERT_TASK1_POST);
  taskc_ended++;
}

/*
 * MAIN TASK
 */
int main(void)
{

  /*Setup the microcontroller system:
    -System Clock Setup;
    -PLL setup
    -Whatchdog setup (Default Watchdog = disabled)
    
    The system (core) clock frequency (CF):  CF= Fin * M / (2P);
    For Fin<15 P=4 and M=2
    If your board mounts a 12MHz cristal oscillator, i.e. Fin=12MHz,
    then the default system clock frequency is CF = 12 MHz * M / (2P)= 6MHZ.

    See "system_LPC12xx.c" in <lpc12cc_cmsis_driver_library> 
    for further informations.
    To modify the system setup, use functions provided by 
    "lpc12xx_sysctrl.c" in <lpc12cc_cmsis_driver_library>
  */
  SystemInit();

  /*Initializes Erika related stuffs*/
  EE_system_init(); 
  
  led_init();
  
  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);
  
  /* Initialization of the second semaphore of the example; the first
   * semaphore is initialized inside the definition */
  InitSem(V,0);

  ActivateTask(Task1);
  //ActivateTask(Task2);
  
  EE_assert(
    EE_ASSERT_TASKS_ENDED, taskp_ended && taskc_ended, EE_ASSERT_TASK1_ENDED
  );
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_TASKS_ENDED);
  result = EE_assert_last();
  
  /* Forever loop: background activities (if any) should go here... */
  for (;;)
  {
    ;
  }

}
