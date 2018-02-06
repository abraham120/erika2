/** 
* @file uwl_timer.h
* @brief Abstract Timer Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_timer_h__
#define __uwl_timer_h__

#ifndef UWL_HAL_EXTERNAL_TIMER		/* Check if no external HAL timer */

#include <hal/uwl_compiler.h>

#if defined __MICROCHIP_DSPIC30__

#include <hal/uwl_timer_dspic30.h>

#elif defined __AVR5__
/* TODO*/

#elif defined __MICROCHIP_PIC32__

#include <hal/uwl_timer_pic32.h>

#elif defined __LM32__

#include <hal/uwl_timer_mico32.h>

#elif defined __STM32__

#include <hal/uwl_timer_stm32.h>

#else			/* No timer */
#error "UWL_HAL ERROR: timer hw interface not specified"

#endif	/* End Selection */

#endif /* UWL_HAL_EXTERNAL_TIMER */

#endif /* Header Protection */
