/**
* @file touch_compiler_c30.h
* @brief Microchip C30 support for Touch.
* @author Francesco Prosperi
* @date 2009-03-24
*/
#ifndef __TOUCH_COMPILER_C30_H__
#define __TOUCH_COMPILER_C30_H__

#ifdef __dsPIC30F__
	#include <p30fxxxx.h>
#elifdef __dsPIC33F__
	#include <p33Fxxxx.h>
#elifdef __PIC24H__
	#include <p24Hxxxx.h>
#endif

/**
* @name Basic type representations.
* @{ */
#ifndef FALSE
#define FALSE 0x00
#endif

#ifndef TRUE
#define TRUE 0x01
#endif

#ifndef UINT8_T
#define UINT8_T
typedef unsigned char uint8_t;		/**< Unsigned 8 bit intgerer. */
#endif

#ifndef UINT16_T
#define UINT16_T
typedef unsigned short int uint16_t;	/**< Unsigned 16 bit intgerer. */
#endif

#ifndef UINT32_T
#define UINT32_T
typedef unsigned long int uint32_t;	/**< Unsigned 32 bit intgerer. */
#endif

#ifndef INT8_T
#define INT8_T
typedef signed char int8_t;		/**< Unsigned 8 bit intgerer. */
#endif

#ifndef INT16_T
#define INT16_T
typedef signed short int int16_t;	/**< Unsigned 16 bit intgerer. */
#endif

#ifndef INT32_T
#define INT32_T
typedef signed long int int32_t;	/**< Unsigned 32 bit intgerer. */
#endif
/**  @} */

#ifndef COMPILER_INLINE
#define COMPILER_INLINE static inline
#endif

#ifndef COMPILER_ISR
#error "compiler_c30: ISR not defined!"
#endif

#endif /* Header Protection */
