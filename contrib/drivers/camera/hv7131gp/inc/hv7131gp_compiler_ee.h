/** 
* @file hv7131gp_compiler_ee.h
* @brief Erika Enterprise Compiler support for HV7131GP.
* @author Marco Ghibaudi
* @date 2010-03-19
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef __hv7131gp_compiler_ee_h__
#define __hv7131gp_compiler_ee_h__

#include <ee.h>

#include "../../../../misc/inc/ee_stdint.h"

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

/* chris: TODO: move this in the HAL, see MRF24J40 solution! */
#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

#endif /* Header Protection */
