/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 
/** 
* @file 	enc28j60_compiler_ee.h
* @brief 	ENC28J60 driver - EE abstraction, and types definition.
* @author 	Dario Di Stefano
* @date 	2010
*/ 

#ifndef __enc28j60_compiler_ee_h__
#define __enc28j60_compiler_ee_h__

#include <ee.h>

#ifdef __AUTOSAR_R4_0__
#include "Std_Types.h"
#define BOOL boolean
#define DEF_BOOL_TYPE
#else
#include "../../../../misc/inc/ee_stdint.h"
#endif /* __AUTOSAR_R4_0__ */

#ifndef COMPILER_INLINE 
#define COMPILER_INLINE __INLINE__
#endif

#ifndef COMPILER_ISR
#define COMPILER_ISR(func) ISR2(func)
#endif

/** T Y P E S   D E F I N I T I O N S **************************************/
// #include "GenericTypeDefs.h", not allowed...

/* BOOL, BYTE, WORD, DWORD */
#ifndef DEF_BOOL_TYPE
#define DEF_BOOL_TYPE
/* chris: FIXME: do we really need this!? */
typedef enum {
	TRUE 		= 0x01,	/**< True */
	FALSE		= 0x00, /**< False */
} BOOL;
typedef BOOL Boolean;
#endif /* DEF_BOOL_TYPE */
typedef uint8_t		BYTE;						// 8-bit unsigned
typedef uint16_t	WORD;						// 16-bit unsigned
typedef uint32_t	DWORD;						// 32-bit unsigned

/* BYTE_VAL */
#ifdef __BIG_ENDIAN__
typedef union _BYTE_VAL
{
    BYTE Val;
    struct
    {
        unsigned char b7:1;
        unsigned char b6:1;
        unsigned char b5:1;
        unsigned char b4:1;
        unsigned char b3:1;
        unsigned char b2:1;
        unsigned char b1:1;
        unsigned char b0:1;
    } bits;
} BYTE_VAL;
#else
typedef union _BYTE_VAL
{
    BYTE Val;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;
#endif

/* WORD_VAL */
#ifdef __BIG_ENDIAN__
typedef union _WORD_VAL
{
    WORD Val;
    BYTE v[2];
    struct
    {
        BYTE HB;
        BYTE LB;
    } byte;
    struct
    {
        unsigned char b15:1;
        unsigned char b14:1;
        unsigned char b13:1;
        unsigned char b12:1;
        unsigned char b11:1;
        unsigned char b10:1;
        unsigned char b9:1;
        unsigned char b8:1;
        unsigned char b7:1;
        unsigned char b6:1;
        unsigned char b5:1;
        unsigned char b4:1;
        unsigned char b3:1;
        unsigned char b2:1;
        unsigned char b1:1;
        unsigned char b0:1;
    } bits;
} WORD_VAL;
#else
typedef union __attribute__((packed)) _WORD_VAL
{
    WORD Val;
    BYTE v[2];
    struct __attribute__((packed))
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct __attribute__((packed))
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
    } bits;
} WORD_VAL, WORD_BITS;
#endif

/* DWORD_VAL */
#ifdef __BIG_ENDIAN__
typedef union _DWORD_VAL
{
    DWORD Val;
	WORD w[2];
    BYTE v[4];
    struct
    {
        WORD HW;
        WORD LW;
    } word;
    struct
    {
		BYTE MB;
		BYTE UB;
		BYTE HB;
		BYTE LB;
    } byte;
    struct
    {
        WORD_VAL high;
        WORD_VAL low;
    }wordUnion;
    struct
    {
        unsigned char b31:1;
        unsigned char b30:1;
        unsigned char b29:1;
        unsigned char b28:1;
        unsigned char b27:1;
        unsigned char b26:1;
        unsigned char b25:1;
        unsigned char b24:1;
        unsigned char b23:1;
        unsigned char b22:1;
        unsigned char b21:1;
        unsigned char b20:1;
        unsigned char b19:1;
        unsigned char b18:1;
        unsigned char b17:1;
        unsigned char b16:1;
        unsigned char b15:1;
        unsigned char b14:1;
        unsigned char b13:1;
        unsigned char b12:1;
        unsigned char b11:1;
        unsigned char b10:1;
        unsigned char b9:1;
        unsigned char b8:1;
        unsigned char b7:1;
        unsigned char b6:1;
        unsigned char b5:1;
        unsigned char b4:1;
        unsigned char b3:1;
        unsigned char b2:1;
        unsigned char b1:1;
        unsigned char b0:1;
    } bits;
} DWORD_VAL;
#else
typedef union _DWORD_VAL
{
    DWORD Val;
	WORD w[2];
    BYTE v[4];
    struct
    {
        WORD LW;
        WORD HW;
    } word;
    struct
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
        unsigned char b8:1;
        unsigned char b9:1;
        unsigned char b10:1;
        unsigned char b11:1;
        unsigned char b12:1;
        unsigned char b13:1;
        unsigned char b14:1;
        unsigned char b15:1;
        unsigned char b16:1;
        unsigned char b17:1;
        unsigned char b18:1;
        unsigned char b19:1;
        unsigned char b20:1;
        unsigned char b21:1;
        unsigned char b22:1;
        unsigned char b23:1;
        unsigned char b24:1;
        unsigned char b25:1;
        unsigned char b26:1;
        unsigned char b27:1;
        unsigned char b28:1;
        unsigned char b29:1;
        unsigned char b30:1;
        unsigned char b31:1;
    } bits;
} DWORD_VAL;
#endif

#endif /* Header Protection */
