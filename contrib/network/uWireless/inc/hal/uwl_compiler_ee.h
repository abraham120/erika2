/** 
* @file uwl_compiler_ee.h
* @brief Erika Enterprise Compiler support for uWireless.
* @author Christian Nastasi
* @version 0.1
* @date 2009-03-22
*
* Using the Erika Enterprise abstraction for the compiler.
*/
#ifndef __uwl_compiler_ee_h__
#define __uwl_compiler_ee_h__

#include <ee.h>
#include <ee_irq.h>

#include "../../../../misc/inc/ee_stdint.h"

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ATTRIBUTE_FAR
#if (defined(__PIC30__))
#define COMPILER_ATTRIBUTE_FAR __attribute__((far))
#else
#define COMPILER_ATTRIBUTE_FAR
#endif
#endif

#ifndef COMPILER_ISR
#if (defined(__PIC30__) || defined(__PIC32__) || defined(__LM32__) \
|| defined(__STM32__))
#define COMPILER_ISR(func) ISR2(func)
#elif defined __AVR5__
#define COMPILER_ISR(func) void func(void)
#endif
#endif

#endif /* Header Protection */
