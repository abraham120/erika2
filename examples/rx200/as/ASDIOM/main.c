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
 * Simple project to to estimate the DIO driver MINIMAL services.
 * 
 * Author: 2012  Gianluca Franchino
 */

#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "test/assert/inc/ee_assert.h"

/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,
	EE_ASSERT_INIT,
	EE_ASSERT_DIO_INIT,
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

}

/*
 * MAIN TASK
 */
int main(void)
{
	Dio_PortLevelType	lvl;
	
	Mcu_Init(MCU_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);
	
	Port_Init(PORT_CONFIG_DEFAULT_PTR);
	
	Dio_Init(DIO_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_DIO_INIT, TRUE, EE_ASSERT_INIT);
	
	EE_assert_range(EE_ASSERT_FIN, TRUE, EE_ASSERT_DIO_INIT);
	result = EE_assert_last();

	/* Forever loop: background activities (if any) should go here */
	for (;result == 1;) {
	    while (counter % 5000) counter++;
	    lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED_0);

	    if (lvl & 0x00000001)
	    	Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000000);
	    else
	    	Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000001);

	    counter++;
	}

}