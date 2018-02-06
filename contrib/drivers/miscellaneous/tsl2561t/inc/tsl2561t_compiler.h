/** 
* @file tsl2561t.h
* @brief TSL2561T Light Sensor Driver
* @author Matteo Petracca
* @author Marco Ghibaudi 
* @date 2010-04-22
*
* This file is the definition of the abstract compiler used by all the module
* of the TSL2561T library. 
*
* \todo Write something about the supported compiler.
*/
#ifndef __TSL2561T_COMPILER_H__
#define __TSL2561T_COMPILER_H__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include "tsl2561t_compiler_ee.h"

#else			/* No compiler */
#error "TSL2561T_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
