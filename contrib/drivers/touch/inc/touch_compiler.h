/**
* @file touch_compiler.h
* @brief Touch Abstract Compiler
* @author Francesco Prosperi
* @date 2009-06-07
*
* This file is the definition of the abstract compiler used by all the module
* of the Touch library.
*
* \todo Write something about the support compiler.
*/
#ifndef __TOUCH_COMPILER_H__
#define __TOUCH_COMPILER_H__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include "touch_compiler_ee.h"
#ifdef __C30__
#ifndef COMPILER_ATTRIBUTE_NEAR
#define COMPILER_ATTRIBUTE_NEAR __attribute__((near))
#endif
#endif

#elif defined __C30__ 	/* Microchip C30 */
#include "touch_compiler_c30.h"
#ifdef __C30__
#ifndef COMPILER_ATTRIBUTE_NEAR
#define COMPILER_ATTRIBUTE_NEAR __attribute__((near))
#endif
#endif

#else			/* No compiler */
#error "TOUCH_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
