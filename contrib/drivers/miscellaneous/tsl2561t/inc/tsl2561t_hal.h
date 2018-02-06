/** 
* @file tsl2561t.h
* @brief TSL2561T Light Sensor Driver
* @author Matteo Petracca
* @author Marco Ghibaudi 
* @date 2010-04-22
*
* This file is the definition of the hardware abstraction layer used by the 
* tsl2561t light sensor 
*
* \todo Write something about the supported compilers.
*/

#ifndef __tsl2561t_hal_h__
#define __tsl2561t_hal_h__

#include <tsl2561t_compiler.h>


/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>

#if defined	__MICROCHIP_PIC32__
#include <tsl2561t_hal_ee_pic32.h>
#else
	#if defined __LM32__
	#include <tsl2561t_hal_ee_mico32.h>
	#else /* NO Architecture */		
	#error "TSL2561T_HAL: Architecture not supported"
	#endif
#endif

#else			/* No OS */

#error "TSL2561T_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
