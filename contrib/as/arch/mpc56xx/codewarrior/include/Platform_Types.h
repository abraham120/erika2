/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/** @file   Platform_Types.h
 *  @brief  AUTOSAR Platform Types Header File.
 *
 *  This files contains all types and symbols for Freescale Leopard (MPC5643L)
 *  and Codewarrior compiler. Those types must be abstracted in order to
 *  become platform and compiler independend.
 *
 *  @author Errico Guidieri
 *  @date 2012
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*
 * PLATFORM057: The platform type files for all platforms shall contain the
 *    following symbols:
 */
#define CPU_TYPE_8  8   /**< Indicating a  8 bit processor. */
#define CPU_TYPE_16 16  /**< Indicating a 16 bit processor. */
#define CPU_TYPE_32 32  /**< Indicating a 32 bit processor. */

/** The most significant bit is the first bit of the bit sequence. **/
#define MSB_FIRST 0
/** The least significant bit is the first bit of the bit sequence. **/
#define LSB_FIRST 1

/** Within a uint16, the high byte is located before the low byte. */
#define HIGH_BYTE_FIRST 0
/** Within uint16, the low byte is located before the high byte. */
#define LOW_BYTE_FIRST  1

/** @brief  CPU Type.
 *
 *  <b>PLATFORM044:</b> For each platform the register width of the CPU used
 *  shall be indicated by defining <tt>CPU_TYPE</tt>.
 *
 *  <b>PLATFORM045:</b> According to the register width of the CPU used,
 *  <tt>CPU_TYPE</tt> shall be assigned to one of the symbols
 *  <tt>CPU_TYPE_8</tt>, <tt>CPU_TYPE_16</tt> or <tt>CPU_TYPE_32</tt>.
 *
 *  <tt>CPU_TYPE_32</tt>: 32 bit processor.
 */
#define CPU_TYPE  CPU_TYPE_32

/** @brief  CPU bit order.
 * 
 *  <b>PLATFORM043:</b> For each platform the appropriate bit order on register
 *  level shall be indicated in the platform types header file using the symbol
 *  <tt>CPU_BIT_ORDER</tt>.
 *
 *  <b>PLATFORM048:</b> In case of big endian bit ordering
 *  <tt>CPU_BIT_ORDER</tt> shall be assigned to <tt>MSB_FIRST</tt> in the
 *  platform types header file.
 *
 *  <b>PLATFORM049:</b> In case of little endian bit ordering
 *  <tt>CPU_BIT_ORDER</tt> shall be assigned to <tt>LSB_FIRST</tt> in the
 *  platform types header file.
 *
 * <tt>MSB_FIRST</tt>: Big Endian.
 */
#define CPU_BIT_ORDER MSB_FIRST

/** @brief  CPU byte order.
 *
 *  <b>PLATFORM046:</b> For each platform the appropriate byte order on memory
 *  level shall be indicated in the platform types header file using the symbol
 *  <tt>CPU_BYTE_ORDER</tt>.
 *
 *  <b>PLATFORM050:</b> In case of big endian byte ordering
 *  <tt>CPU_BYTE_ORDER</tt> shall be assigned to <tt>HIGH_BYTE_FIRST</tt> in the
 *  platform types header file.
 *
 *  <b>PLATFORM051:</b> In case of little endian byte ordering
 *  <tt>CPU_BYTE_ORDER</tt> shall be assigned to <tt>LOW_BYTE_FIRST</tt> in the
 *  platform types header file.
 *
 *  <tt>HIGH_BYTE_FIRST</tt>: Big Endian.
 */
#define CPU_BYTE_ORDER  HIGH_BYTE_FIRST

/* Include Erika version of standard int */
#include <cpu/common/inc/ee_stdint.h>

#if 0 /* Standar Types Definitions */
typedef signed char int8_t;
typedef short int   int16_t;
typedef long int    int32_t;
typedef long long   int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned long int   uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char         int_fast8_t;
typedef short int           int_fast16_t;
typedef long int            int_fast32_t;

typedef unsigned char       uint_fast8_t;
typedef unsigned short int  uint_fast16_t;
typedef unsigned long int   uint_fast32_t;
#endif

/** @brief  Boolean.
 *
 *  <b>PLATFORM027</b>: The standard AUTOSAR type <tt>boolean</tt> shall be
 *  implemented as an unsigned integer with a bit length that is the shortest
 *  one natively supported by the platform (in general 8 bits).
 */
typedef unsigned char boolean;

/*
 * PLATFORM054: In case of in-built compiler support of the symbols,
 *    redefinitions shall be avoided using a conditional check.
 *
 * PLATFORM55:  These symbols shall only be used in conjunction with the
 *    boolean type defined in Platform_Types.h.
 *
 * PLATFORM056: The symbols TRUE and FALSE shall be defined as follows:
 */
#ifndef FALSE
#define FALSE 0U /**< Boolean value FALSE. */
#endif
#ifndef TRUE
#define TRUE  1U /**< Boolean value TRUE. */
#endif

/** @brief  8 bit unsigned integer.
 *
 *  <b>PLATFORM013:</b> This standard AUTOSAR type shall be of 8 bit unsigned.
 */
typedef uint8_t   uint8;

/** @brief  16 bit unsigned integer.
 *
 *  <b>PLATFORM014:</b> This standard AUTOSAR type shall be of 16 bit unsigned.
 */
typedef uint16_t  uint16;

/** @brief  32 bit unsigned integer.
 *
 *  <b>PLATFORM015:</b> This standard AUTOSAR type shall be of 32 bit unsigned.
 */
typedef uint32_t  uint32;

/** @brief  64 bit unsigned integer.
 *
 *  This NOT-standard AUTOSAR type shall be of 64 bit unsigned.
 */
typedef uint64_t  uint64;

/** @brief  8 bit signed integer.
 *
 *  <b>PLATFORM016:</b> This standard AUTOSAR type shall be of 8 bit signed.
 */
typedef int8_t    sint8;

/** @brief  16 bit signed integer.
 *
 *  <b>PLATFORM017:</b> This standard AUTOSAR type shall be of 16 bit signed.
 */
typedef int16_t   sint16;

/** @brief  32 bit signed integer.
 *
 *  <b>PLATFORM018:</b> This standard AUTOSAR type shall be of 32 bit signed.
 */
typedef int32_t   sint32;

/** @brief  64 bit signed integer.
 *
 *  This NOT-standard AUTOSAR type shall be of 64 bit signed.
 */
typedef int64_t   sint64;

/** @brief  At least 8 bit unsigned integer.
 *
 *  <b>PLATFORM020:</b> This optimized AUTOSAR type shall be at least of 8 bit
 *  unsigned.
 */
typedef uint_fast8_t  uint8_least;

/** @brief  At least 16 bit unsigned integer.
 *
 *  <b>PLATFORM021:</b> This optimized AUTOSAR type shall be at least of 16 bit
 *  unsigned.
 */
typedef uint_fast16_t uint16_least;

/** @brief  At least 32 bit unsigned integer.
 *
 *  <b>PLATFORM022:</b> This optimized AUTOSAR type shall be at least of 32 bit
 *  unsigned.
 */
typedef uint_fast32_t uint32_least;

/** @brief  At least 8 bit signed integer.
 *
 *  <b>PLATFORM023:</b> This optimized AUTOSAR type shall be at least of 8 bit
 *  signed.
 */
typedef int_fast8_t sint8_least;

/** @brief  At least 16 bit signed integer.
 *
 *  <b>PLATFORM024:</b> This optimized AUTOSAR type shall be at least of 16 bit
 *  signed.
 */
typedef int_fast16_t  sint16_least;

/** @brief  At least 32 bit signed integer.
 *
 *  <b>PLATFORM025:</b> This optimized AUTOSAR type shall be at least of 32 bit
 *  signed.
 */
typedef int_fast32_t  sint32_least;

/** @brief  Float.
 *
 *  <b>FLATFORM041</b>
 */
typedef float   float32;

/** @brief  Double.
 *
 *  <b>PLATFORM042</b>
 */
typedef double    float64;  

#endif  /* PLATFORM_TYPES_H */
