/** 
* @file iedf_kal.h
* @brief Abstract KAL interface 
* @author Christian Nastasi
* @author Gianluca Franchino  
* @version 0.1
* @date 2009-06-22
*/
#ifndef __iedf_kal_h__
#define __iedf_kal_h__

#include <hal/iedf_compiler.h>

#define IEDF_KAL_ERR_TIMER_INIT	10

/* chris: is it necesary to have this include in here? maybe the 
	  implementation details specific of the particular kal can be 
	  hidden in the iedf_kal_erika.c? 
	  If we need some particular macros (or inline) specific for the
	  particular kal then we need to use something like this!
*/
/* Start OS selection */
#ifdef __ERIKA__
#include <kal/iedf_kal_erika.h>	/* Erika Enterprise */

#else					/* No KAL */
#error "IEDF_KAL ERROR: OS or equivalent abstraction not specified"
#endif

#endif /* Header Protection */
