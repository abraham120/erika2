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
 * Simple project to test Mcu_GetResetReason() and Mcu_InitClock() services.
 *
 * Author: 2011  Giuseppe Serano
 */

#include "Mcu.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"

#ifndef	TRUE
#define	TRUE	1
#endif

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_ISR_FIRED,
  EE_ASSERT_TASK1_FIRED,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
  counter++;
  if (counter == 1) {
    EE_assert(EE_ASSERT_ISR_FIRED, counter == 1, EE_ASSERT_INIT);
  }
  ActivateTask(Task1);
}

/*
 * TASK 1
 */
TASK(Task1)
{
  if (counter == 1) {
    EE_assert(EE_ASSERT_TASK1_FIRED, counter == 1, EE_ASSERT_ISR_FIRED);
  }
  EE_user_led_toggle();
}

/*
 * MAIN TASK
 */
int main(void)
{

  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  EE_user_led_init();

  if (Mcu_GetResetReason() == MCU_POWER_ON_RESET)
    Mcu_InitClock(MCU_CLOCK_MODE_NORMAL);
  else
    Mcu_InitClock(MCU_CLOCK_MODE_PRIOSC_10_NO_PLL);

  EE_systick_set_period(NVIC_ST_RELOAD_M);
  EE_systick_enable_int();
  EE_systick_start();

  while(!counter);

  EE_assert_range(EE_ASSERT_FIN, TRUE, EE_ASSERT_TASK1_FIRED);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {
    ;
  }

}
