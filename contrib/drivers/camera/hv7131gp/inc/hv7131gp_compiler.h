/** 
* @file hv7131gp_compiler.h
* @brief HV7131GP Abstract Compiler
* 
* This file is the definition of the abstract compiler used by all the module
* of the HV7131GP library. 
*
*/
#ifndef __hv7131gp_compiler_h__
#define __hv7131gp_compiler_h__

/**
* Start Compiler Selection section
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include "hv7131gp_compiler_ee.h"

#else			/* No compiler */
#error HV7131GP_HAL ERROR: compiler type not specified

#endif	/* End Compiler Selection */

#endif /* Header Protection */
