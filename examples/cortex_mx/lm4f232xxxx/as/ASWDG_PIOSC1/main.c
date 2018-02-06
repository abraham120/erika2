/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * Simple project to test the Precision Internal Oscillator WDG driver services
 * using callback and standard watchdog interrupt without system reset.
 *
 * Author: 2012,  Giuseppe Serano
 */

#include "ee.h"
#include "Dio.h"
#include "Mcu.h"
#include "Port.h"
#include "Sci.h"
#include "WdgPIOsc.h"
#include "test/assert/inc/ee_assert.h"

#define	PLL_LOCK_MAX_ATTEMPTS	0x0000000A

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_VERSION,
  EE_ASSERT_CLOCK_INIT,
  EE_ASSERT_PLL_LOCKED,
  EE_ASSERT_WDG_INIT,
  EE_ASSERT_WDG_SLOW_MODE,
  EE_ASSERT_WDG_SLOW_NOTIF,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

volatile boolean wdgfeed = TRUE;

/*
 * Watchdog Slow Mode Notification Callback.
 */
void Wdg_PIOsc_Notification_Slow(
  void
)
{
  if ( counter == 0 ) {

    EE_assert(EE_ASSERT_WDG_SLOW_NOTIF, TRUE,  EE_ASSERT_WDG_SLOW_MODE);

  }

  Dio_FlipChannel(DIO_CHANNEL_USER_LED);

  counter++;

  Wdg_PIOsc_SetTriggerCondition(1000 * counter);

  if ( counter == 10 ) {

    counter = 2;
    wdgfeed = TRUE;

  }

}

/*
 * TASK BackgroundTask
 */
TASK(BackgroundTask)
{

  EE_assert(
    EE_ASSERT_WDG_SLOW_MODE,
    ( Wdg_PIOsc_SetMode(WDGIF_SLOW_MODE) == E_OK ),
    EE_ASSERT_WDG_INIT
  );

  /* Forever loop: background activities (if any) should go here */
  while(TRUE)
  {

    if (wdgfeed) {

      Wdg_PIOsc_SetTriggerCondition(1000);	/* 1s */

      wdgfeed = Dio_ReadChannel(DIO_CHANNEL_USER_SWITCH_SELECT_WAKE);

      Dio_FlipChannel(DIO_CHANNEL_USER_LED);

    }

    if (counter == 1) {

      EE_assert_range(EE_ASSERT_FIN, TRUE, EE_ASSERT_WDG_SLOW_NOTIF);
      result = EE_assert_last();
      counter++;

    }

  }

  /* 
   *  NOTE: 	TerminateTask() statement commented preventing compiler
   * 		warning #111-D: statement is unreachable.
   */
  /* TerminateTask(); */
}

/*
 * MAIN TASK
 */
int main(void)
{

  Std_VersionInfoType version;

  EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

  Wdg_PIOsc_GetVersionInfo(&version);

  EE_assert(
    EE_ASSERT_VERSION,
    (
      (version.vendorID == 0) &&
      (version.moduleID == 102) &&
      (version.sw_major_version == 1) &&
      (version.sw_minor_version == 0) &&
      (version.sw_patch_version == 0)
    ),
    EE_ASSERT_INIT
  );

  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  if ( Mcu_InitClock(MCU_CLOCK_MODE_MOSC_4_PLL) == E_NOT_OK ) {

    Mcu_PerformReset();

  }

  EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);

  for (
    counter = 0;
    ( 
      ( counter <  PLL_LOCK_MAX_ATTEMPTS ) &&
      ( Mcu_GetPllStatus() != MCU_PLL_LOCKED )
    );
    counter++
  ) {

    ;

  }

  EE_assert(
    EE_ASSERT_PLL_LOCKED,
    ( counter <  PLL_LOCK_MAX_ATTEMPTS ),
    EE_ASSERT_CLOCK_INIT
  );

  Mcu_DistributePllClock();

  counter = 0;

  Port_Init(PORT_CONFIG_DEFAULT_PTR);

  Dio_Init(DIO_CONFIG_DEFAULT_PTR);

  Sci_Init(SCI_CONFIG_WDG_PIOSC_TESTS_PTR);

  Wdg_PIOsc_Init(WDG_PIOSC_CONFIG_DEFAULT_PTR);

  EE_assert(EE_ASSERT_WDG_INIT, TRUE, EE_ASSERT_PLL_LOCKED);

  /* Start ERIKA ENTERPRISE */
  StartOS(OSDEFAULTAPPMODE);

  return 0;

}
