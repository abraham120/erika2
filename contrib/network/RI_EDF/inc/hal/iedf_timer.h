/** 
* @file iedf_timer.h
* @brief Abstract Timer Interface
* @author Christian Nastasi
* @author Gianluca Franchino 
* @version 0.1
* @date 2009-06-22
*/
#ifndef __iedf_timer_h__
#define __iedf_timer_h__

#ifndef UWL_HAL_EXTERNAL_TIMER		/* Check if no external HAL timer */

#include <hal/iedf_compiler.h>

#if defined __MICROCHIP_DSPIC30__

#include <hal/iedf_timer_dspic30.h>

#elif defined __AVR5__
/* TODO*/

#elif defined __MICROCHIP_PIC32__

#include <hal/iedf_timer_pic32.h>

#elif defined __LM32__

#include <hal/iedf_timer_mico32.h>


#else			/* No timer */
#error "IEDF_HAL ERROR: timer hw interface not specified"

#endif	/* End Selection */

#endif /* IEDF_HAL_EXTERNAL_TIMER */

#endif /* Header Protection */
