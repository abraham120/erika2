/** 
* @file cc2420_compiler.h
* @brief CC2420 Abstract Compiler
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the abstract compiler used by all the module
* of the CC2420 library. 
*
* \todo Write something about the supporte compiler.
*/
#ifndef __cc2420_compiler_h__
#define __cc2420_compiler_h__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include <cc2420_compiler_ee.h>
#ifdef __C30__ 
#ifndef COMPILER_ATTRIBUTE_NEAR 
#define COMPILER_ATTRIBUTE_NEAR __attribute__((near))
#endif
#endif

#elif defined __C30__ 	/* Microchip C30 */
#include <cc2420_compiler_c30.h>
#ifdef __C30__ 
#ifndef COMPILER_ATTRIBUTE_NEAR 
#define COMPILER_ATTRIBUTE_NEAR __attribute__((near))
#endif
#endif

#else			/* No compiler */
#error "CC2420_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
