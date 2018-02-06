/**
* @file touch_hal.h
* @brief Touch Hw Abstraction Layer
* @author
* @date 2009-06-07
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the touch library.
*
* \todo Write something about the hal support.
*/

#ifndef __TOUCH_HAL_H__
#define __TOUCH_HAL_H__

#include <touch_compiler.h>

/**
* Start HAL Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika OS */

#include <ee.h>
#include <touch_hal_ee.h>

#else			/* No OS */

#error "CC2420_HAL ERROR: OS not specified"

#endif	/* End OS Selection */


#endif // __TOUCH_HAL_H__
