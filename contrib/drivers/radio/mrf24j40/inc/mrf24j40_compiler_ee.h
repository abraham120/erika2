/** 
* @file mrf24j40_compiler_ee.h
* @brief Erika Enterprise Compiler support for MRF24J40.
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef __mrf24j40_compiler_ee_h__
#define __mrf24j40_compiler_ee_h__

#include <ee.h>

#include "../../../../misc/inc/ee_stdint.h"

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

#endif /* Header Protection */
