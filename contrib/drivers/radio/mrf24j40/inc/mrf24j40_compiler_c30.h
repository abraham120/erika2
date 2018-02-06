/** 
* @file mrf24j40_compiler_c30.h
* @brief Microchip C30 support for MRF24J40.
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*/
#ifndef __mrf24j40_compiler_c30_h__
#define __mrf24j40_compiler_c30_h__

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

#ifndef UINT64_T
#define UINT64_T
typedef unsigned long long uint64_t;	/**< Unsigned 64 bit intgerer. */
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

#ifndef INT64_T
#define INT64_T
typedef signed long long int64_t;	/**< Unsigned 64 bit intgerer. */
#endif
/**  @} */

#ifndef HAL_INLINE 
#define HAL_INLINE static inline
#endif

#endif /* Header Protection */
