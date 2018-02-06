/** 
* @file uwl_kal.h
* @brief Abstract KAL interface 
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_kal_h__
#define __uwl_kal_h__

#include <hal/uwl_compiler.h>

#define UWL_KAL_ERR_TIMER_INIT	10

/* chris: is it necesary to have this include in here? maybe the 
	  implementation details specific of the particular kal can be 
	  hidden in the uwl_kal_erika.c? 
	  If we need some particular macros (or inline) specific for the
	  particular kal then we need to use something like this!
*/
/* Start OS selection */
#ifdef __ERIKA__
#include <kal/uwl_kal_erika.h>	/* Erika Enterprise */

#else					/* No KAL */
#error "UWL_KAL ERROR: OS or equivalent abstraction not specified"
#endif

#endif /* Header Protection */
