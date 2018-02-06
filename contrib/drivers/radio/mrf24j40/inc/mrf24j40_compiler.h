/** 
* @file mrf24j40_compiler.h
* @brief MRF24J40 Abstract Compiler
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the abstract compiler used by all the module
* of the MRF24J40 library. 
*
* \todo Write something about the supporte compiler.
*/
#ifndef __mrf24j40_compiler_h__
#define __mrf24j40_compiler_h__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include <mrf24j40_compiler_ee.h>

#elif defined __C30__ 	/* Microchip C30 */
#include <mrf24j40_compiler_c30.h>

#else			/* No compiler */
#error "MRF24J40_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
