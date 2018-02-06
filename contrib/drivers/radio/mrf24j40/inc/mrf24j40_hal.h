/** 
* @file mrf24j40_hal.h
* @brief MRF24J40 Hw Abstraction Layer
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the MRF24J40 library. 
*
* \todo Write something about the hal support.
*/
#ifndef __mrf24j40_hal_h__
#define __mrf24j40_hal_h__

#include <mrf24j40_compiler.h>


/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

//#include <ee.h>

#if defined 	__MICROCHIP_DSPIC30__
#include <mrf24j40_hal_ee_dspic.h>
#elif defined	__MICROCHIP_PIC32__
#include <mrf24j40_hal_ee_pic32.h>
#elif defined __LM32__
#include <mrf24j40_hal_ee_mico32.h>
#elif defined __STM32__
#include <mrf24j40_hal_ee_stm32.h>
#else		/* NO Architecture */
#error "MRF24J40_HAL: Architecture not supported"
#endif

#else			/* No OS */

#error "MRF24J40_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
