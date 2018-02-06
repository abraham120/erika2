

#ifndef __touch_timer_h__
#define __touch_timer_h__

#ifndef TOUCH_HAL_EXTERNAL_TIMER		/* Check if no external HAL timer */

#include <touch_compiler.h>

#if defined __MICROCHIP_DSPIC30__

#include <touch_timer_dspic30.h>

#else			/* No timer */
#error "UWL_HAL ERROR: timer hw interface not specified"

#endif	/* End Selection */

#endif /* TOUCH_HAL_EXTERNAL_TIMER */

#endif /* Header Protection */
