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
 * Simple project to demonstrate that the PCLK WDG driver services using callback
 * and standard watchdog NM interrupt without system reset.
 *
 * Author: 2013,  Gianluca Franchino
 */

#include "Dio.h"
#include "Mcu.h"
#include "Port.h"
#include "Wdg_PCLK.h"
#include "test/assert/inc/ee_assert.h"


/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,
	EE_ASSERT_INIT,
	EE_ASSERT_VERSION,
	EE_ASSERT_CLOCK_INIT,
	EE_ASSERT_PLL_LOCKED,
	EE_ASSERT_WDG_INIT,
	EE_ASSERT_WDG_FAST_MODE,
	EE_ASSERT_WDG_FAST_NOTIF,
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
void Wdg_PCLK_Notification_Fast(void)
{
	if ( counter == 0 ) {

		EE_assert(EE_ASSERT_WDG_FAST_NOTIF, TRUE,  EE_ASSERT_WDG_FAST_MODE);
	}

	Dio_FlipChannel(DIO_CHANNEL_USER_LED_1);

	counter++;
	
	Wdg_PCLK_SetTriggerCondition(0);
	
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
/*
 * Since the Watch Dog System can only be configured once, and this is done
 * through Wdg_PCLK_Init(WDG_PCLK_CONFIG_DEFAULT_PTR), 
 * Wdg_PCLK_SetMode(WDGIF_FAST_MODE) has not effect and returns E_OK.  
 */
	EE_assert(EE_ASSERT_WDG_FAST_MODE, 
			( Wdg_PCLK_SetMode(WDGIF_FAST_MODE) == E_OK ), 
			EE_ASSERT_WDG_INIT);

	/* Forever loop: background activities (if any) should go here */
	for(;;) {

		if (wdgfeed == TRUE) {

			Wdg_PCLK_SetTriggerCondition(0);
			
			if (Dio_ReadChannel(DIO_CHANNEL_USER_SWITCH_1) == FALSE)
				wdgfeed = FALSE;			
			
			Dio_FlipChannel(DIO_CHANNEL_USER_LED_0);
		}

		if (counter == 1) {

			EE_assert_range(EE_ASSERT_FIN, TRUE, EE_ASSERT_WDG_FAST_NOTIF);
			result = EE_assert_last();
			counter++;
		}

	}

	TerminateTask();
}


/*
 * MAIN TASK
 */
int main(void)
{

	Std_VersionInfoType	version;

	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	Wdg_PCLK_GetVersionInfo(&version);

	EE_assert(EE_ASSERT_VERSION,(
								(version.vendorID == 0) &&
								(version.moduleID == 102) &&
								(version.sw_major_version == 1) &&
								(version.sw_minor_version == 0) &&
								(version.sw_patch_version == 0)
								), EE_ASSERT_INIT);

	Mcu_Init(MCU_CONFIG_DEFAULT_PTR);
	
	if ( Mcu_InitClock(MCU_CLK_MODE_MOSC20_PLL100_I2_B4) == E_NOT_OK ) {

		Mcu_PerformReset();
	}

	EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);

	//while (Mcu_GetPllStatus() != MCU_PLL_LOCKED);

	EE_assert(EE_ASSERT_PLL_LOCKED, 
				Mcu_GetPllStatus() == MCU_PLL_LOCKED, 
				EE_ASSERT_CLOCK_INIT);

	counter = 0;

	Port_Init(PORT_CONFIG_DEFAULT_PTR);
	Dio_Init(DIO_CONFIG_DEFAULT_PTR);

	Wdg_PCLK_Init(WDG_PCLK_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_WDG_INIT, TRUE, EE_ASSERT_PLL_LOCKED);

	/* Start ERIKA ENTERPRISE */
	StartOS(OSDEFAULTAPPMODE);

}
