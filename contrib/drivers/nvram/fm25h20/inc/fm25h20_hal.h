/** 
* @file fm25h20_hal.h
* @brief FM25H20 Hw Abstraction Layer
* @author Christian Nastasi
* @author Marco Ghibaudi 
* @date 2010-01-25
*
* This file is the definition of the hardware abstraction layer used by 
* all the module of the FM25H20 library. 
*
* \todo Write something about the hal support.
*/
#ifndef __fm25h20_hal_h__
#define __fm25h20_hal_h__

#include <fm25h20_compiler.h>

/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>

#if defined	__MICROCHIP_PIC32__
#include <fm25h20_hal_ee_pic32.h>
#else		/* NO Architecture */
#error "FM25H20_HAL: Architecture not supported"
#endif

#else			/* No OS */

#error "FM25H20_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
