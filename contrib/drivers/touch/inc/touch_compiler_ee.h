/**
* @file touch_compiler_ee.h
* @brief Erika Enterprise Compiler support for Touch.
* @author Francesco Prosperi
* @date 2009-06-07
*
* Using the Erika Enterprise abstraction for the compiler.
*/

#ifndef __TOUCH_COMPILER_EE_H__
#define __TOUCH_COMPILER_EE_H__

#include <ee.h>
#include <ee_irq.h>

/**
* @name Basic type representations.
* @{ */
#ifndef UINT8_T
#define UINT8_T
typedef EE_UINT8 uint8_t;	/**< Unsigned 8 bit intgerer. */
#endif

#ifndef UINT16_T
#define UINT16_T
typedef EE_UINT16 uint16_t;	/**< Unsigned 16 bit intgerer. */
#endif

#ifndef UINT32_T
#define UINT32_T
typedef EE_UINT32 uint32_t;	/**< Unsigned 32 bit intgerer. */
#endif

#ifndef INT8_T
#define INT8_T
typedef EE_INT8 int8_t;		/**< Unsigned 8 bit intgerer. */
#endif

#ifndef INT16_T
#define INT16_T
typedef EE_INT16 int16_t;	/**< Unsigned 16 bit intgerer. */
#endif

#ifndef INT32_T
#define INT32_T
typedef EE_INT32 int32_t;	/**< Unsigned 32 bit intgerer. */
#endif
/**  @} */

#ifndef COMPILER_INLINE
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#ifdef __PIC30__
#define COMPILER_ISR(func) ISR2(func)
#elif defined __AVR5__
#define COMPILER_ISR(func) void func(void)
#endif
#endif

#endif /* Header Protection */
