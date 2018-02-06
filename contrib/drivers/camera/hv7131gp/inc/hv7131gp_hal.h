/** 
* @file hv7131gp_hal.h
* @brief HV7131GP Hw Abstraction Layer
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the HV7131GP library. 
*
* \todo Write something about the hal support.
*/
#ifndef __hv7131gp_hal_h__
#define __hv7131gp_hal_h__

#include "hv7131gp_compiler.h"


/**
* Start HAL Selection section
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>

#if defined 	__MICROCHIP_DSPIC30__
#include "hv7131gp_hal_ee_dspic30.h"
#elif defined	__MICROCHIP_PIC32__
#include "hv7131gp_hal_ee_pic32.h"
#elif defined __LM32__
#include "hv7131gp_hal_ee_mico32.h"
#else		/* NO Architecture */
#error "HV7131GP_HAL: Architecture not supported"
#endif

#else			/* No OS */

#error "HV7131GP_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
