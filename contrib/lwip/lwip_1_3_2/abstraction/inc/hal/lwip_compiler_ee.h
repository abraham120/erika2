/*
  Name: lwip_compiler_ee.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: 	EE compiler abstraction for LWIP. 
*/

#ifndef __lwip_compiler_ee_h__
#define __lwip_compiler_ee_h__

#include <ee.h>

/** 
* @name Basic type representations.
* @{ */
#ifndef U8_T
#define U8_T
typedef EE_UINT8 u8_t;	/**< Unsigned 8 bit intgerer. */
#endif

#ifndef U16_T
#define U16_T
typedef EE_UINT16 u16_t;	/**< Unsigned 16 bit intgerer. */
#endif

#ifndef U32_T
#define U32_T
typedef EE_UINT32 u32_t;	/**< Unsigned 32 bit intgerer. */
#endif

#ifndef S8_T
#define S8_T
typedef EE_INT8 s8_t;		/**< Unsigned 8 bit intgerer. */
#endif

#ifndef S16_T
#define S16_T
typedef EE_INT16 s16_t;	/**< Unsigned 16 bit intgerer. */
#endif

#ifndef S32_T
#define S32_T
typedef EE_INT32 s32_t;	/**< Unsigned 32 bit intgerer. */
#endif

#ifndef MEM_PTR_T
#define MEM_PTR_T
typedef u32_t               mem_ptr_t;
#endif

/* printf formatters for data types */
#ifndef U16_F
#define U16_F	"u"
#endif

#ifndef S16_F
#define S16_F	"d"
#endif

#ifndef X16_F
#define X16_F	"x"
#endif

#ifndef U32_F
#define U32_F	"u"
#endif

#ifndef S32_F
#define S32_F	"d"
#endif

#ifndef X32_F
#define X32_F	"x"
#endif

#ifndef SZT_F
#define SZT_F	"zu"
#endif

/**  @} */

#endif /* Header Protection */
