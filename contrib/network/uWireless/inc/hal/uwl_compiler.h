/** 
* @file uwl_compiler.h
* @brief uWireless Abstract Compiler
* @author Christian Nastasi
* @version 0.1
* @date 2009-03-22
*
* This file is the definition of the abstract compiler used by all the module
* of the uWireless library. 
*
* \todo Write something about the supported compiler.
*/
#ifndef __uwl_compiler_h__
#define __uwl_compiler_h__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__	/* Erika Abstract Compiler */
#include <ee.h>
#include <hal/uwl_compiler_ee.h>

#elif defined __C30__ 	/* Microchip C30 */
#include <hal/uwl_compiler_c30.h>

#else			/* No compiler */
#error "UWL_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
