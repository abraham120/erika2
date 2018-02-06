/** 
* @file tsl2561t.h
* @brief TSL2561T Light Sensor Driver
* @author Matteo Petracca
* @author Marco Ghibaudi 
* @date 2010-04-22
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef __tsl2561t_compiler_ee_h__
#define __tsl2561t_compiler_ee_h__

#include <ee.h>
#include "../../../../misc/inc/ee_stdint.h"

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

#endif /* Header Protection */
