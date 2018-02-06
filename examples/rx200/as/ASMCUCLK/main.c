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
 * Simple project to test the Mcu_InitClock() service.
 * Author: 2012  Gianluca Franchino
 */

#include "Mcu.h"
#include "test/assert/inc/ee_assert.h"

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/*
 * TASK 1
 */
TASK(Task1)
{
  /* Nothing to do... */
}

/*
 * MAIN TASK
 */
int main(void)
{

	counter = 0;

	Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	EE_rskrx210_leds_init(0xF);
	
#define CLK_SETTING 10	

#if	CLK_SETTING == 0
	Mcu_InitClock(MCU_CLK_MODE_LOCO_I1_B1);
#elif 	CLK_SETTING == 1
	Mcu_InitClock(MCU_CLK_MODE_HOCO32_I1_B1);
#elif	CLK_SETTING == 2
	Mcu_InitClock(MCU_CLK_MODE_HOCO36_I1_B1);
#elif 	CLK_SETTING == 3
	Mcu_InitClock(MCU_CLK_MODE_HOCO40_I1_B2);
#elif	CLK_SETTING == 4
	Mcu_InitClock(MCU_CLK_MODE_HOCO50_I1_B2);
#elif 	CLK_SETTING == 5
	Mcu_InitClock(MCU_CLK_MODE_MOSC20_PLL40_I2_B2);
#elif	CLK_SETTING == 6
	Mcu_InitClock(MCU_CLK_MODE_MOSC20_PLL50_I2_B2);
#elif 	CLK_SETTING == 7
	Mcu_InitClock(MCU_CLK_MODE_MOSC20_PLL60_I2_B2);
#elif	CLK_SETTING == 8
	Mcu_InitClock(MCU_CLK_MODE_MOSC20_PLL80_I2_B4);
#elif	CLK_SETTING == 9
	Mcu_InitClock(MCU_CLK_MODE_MOSC20_PLL100_I2_B4);
#else
#error "CLK_SETTING is not correctly set."
#endif


	EE_assert_range(EE_ASSERT_FIN, TRUE, EE_ASSERT_INIT);
	result = EE_assert_last();

	/* Forever loop: background activities (if any) should go here */
	for (;result == 1;) {
		while (counter % 100000) counter++;

		EE_rskrx210_leds_toggle();

		counter++;
	}

}
