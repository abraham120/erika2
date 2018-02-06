/** 
* @file iedf_compiler.h
* @brief RI-EDF Abstract Compiler
* @author Gianluca Franchino 2012
* @author Christian Nastasi 2009
*
* This file is the definition of the abstract compiler used by all the module
* of the RI_EDF library. 
*
*/
#ifndef __iedf_compiler_h__
#define __iedf_compiler_h__

/**
* Start Compiler Selection section
*/
#ifdef __ERIKA__	/* Erika Abstract Compiler */
#include <ee.h>
#include <hal/iedf_compiler_ee.h>

#elif defined __C30__ 	/* Microchip C30 */
#include <hal/iedf_compiler_c30.h>

#else			/* No compiler */
#error "IEDF_HAL ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
