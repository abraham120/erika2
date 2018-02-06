/** 
* @file ov9650_compiler_ee.h
* @brief Erika Enterprise Compiler support for OV9650.
* @author Salvatore Marrapese, Marco Ghibaudi
* @date 2012-06-22
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef _OV9650_COMPILER_EE_H_
#define _OV9650_COMPILER_EE_H_

#include <ee.h>

#include "../../../../pkg/cpu/common/inc/ee_stdint.h"

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

#endif /* Header Protection */
