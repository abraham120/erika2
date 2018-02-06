/** 
* @file fm25h20_compiler.h
* @brief FM25H20 Abstract Compiler
* @author Christian Nastasi
* @author Marco Ghibaudi 
* @date 2010-01-25
*
* This file is the definition of the abstract compiler used by all the module
* of the FM25H20 library. 
*
* \todo Write something about the supported compilers.
*/
#ifndef __fm25h20_compiler_h__
#define __fm25h20_compiler_h__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include <fm25h20_compiler_ee.h>

#else			/* No compiler */
#error "FM25H20_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
