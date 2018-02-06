/** 
* @file uwl_rand.h
* @brief Random number generator
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_rand_h__
#define __uwl_rand_h__

#include <hal/uwl_compiler.h>

#ifdef __ERIKA__	/* Erika */
#include <ee.h>
/* TODO: this is FAKE!!!, what can we do in future??? */
#include <stdlib.h>
COMPILER_INLINE void uwl_rand_init(void) 
{
}

COMPILER_INLINE uint8_t uwl_rand_8bit(void)
{
	return (rand() % 0xFF);
}

#elif defined __C30__ 	/* Microchip C30 */
#include <stdlib.h>
COMPILER_INLINE void uwl_rand_init(void) 
{
}

COMPILER_INLINE uint8_t uwl_rand_8bit(void)
{
	return (rand() % 0xFF);
}

#else			/* No random generator */
#error "UWL_HAL ERROR: random number generator not specified"

#endif	/* End Random Generator Selection */

#endif /* Header Protection */
