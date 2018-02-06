#ifndef __touch_1_kal_h__
#define __touch_1_kal_h__

#include <touch_compiler.h>

#define TOUCH_KAL_ERR_TIMER_INIT	10

/* Start OS selection */
#ifdef __ERIKA__
#include <touch_1_kal_erika.h>	/* Erika Enterprise */

#else					/* No KAL */
#error "TOUCH_KAL ERROR: OS or equivalent abstraction not specified"
#endif

#endif /* Header Protection */
