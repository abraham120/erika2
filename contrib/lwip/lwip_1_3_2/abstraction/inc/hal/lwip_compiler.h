/*
  Name: lwip_compiler.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: 	This file is the definition of the abstract compiler 
				used by all the module of the LWIP library. 
*/

#ifndef __lwip_compiler_h__
#define __lwip_compiler_h__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__	/* Erika Abstract Compiler */
#include <ee.h>
#include <hal/lwip_compiler_ee.h>
#elif defined __C30__ 	/* Microchip C30 */
#include <hal/lwip_compiler_c30.h>
#else			/* No compiler */
#error "LWIP_HAL ERROR: compiler type not specified"
#endif	/* End Compiler Selection */

#endif /* Header Protection */
