/** 
* @file cc2420_hal.h
* @brief CC2420 Hw Abstraction Layer
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the CC2420 library. 
*
* \todo Write something about the hal support.
*/
#ifndef __cc2420_hal_h__
#define __cc2420_hal_h__

#include <cc2420_compiler.h>


/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>
#include <cc2420_hal_ee.h>

#else			/* No OS */

#error "CC2420_HAL ERROR: OS not specified"

#endif	/* End OS Selection */

#endif /* Header Protection */
