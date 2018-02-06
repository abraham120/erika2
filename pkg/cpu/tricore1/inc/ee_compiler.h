/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, TU Dortmund University, Faculty of Computer Science 12
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

/* Author: Jan C. Kleinsorge, TU Dortmund University, 2010-
 *
 */

#ifndef __INCLUDE_TRICORE1_EE_COMPILER_H__
#define __INCLUDE_TRICORE1_EE_COMPILER_H__

#ifndef __EECFG_THIS_IS_ASSEMBLER__

#ifdef __NO_INLINE__
#define __INLINE__ static
#else
#define __INLINE__ static inline
#endif

/* GCC-specific language extensions */
#ifdef __GNUC__

#define __ALWAYS_INLINE__ __attribute__((always_inline))

#define __NEVER_INLINE__ __attribute__((noinline))

#define __UNUSED__ __attribute__((unused))

#define __INTERRUPT__ __attribute__((interrupt))

#define __INTERRUPT_HANDLER__ __attribute__((interrupt_handler))

#define __ALIGNED__(b) __attribute__((aligned(b)))

#define NORETURN  __attribute__ ((noreturn))

/* Predefine types. Mapped to HAL types in ee_cpu.h  */ 
typedef signed int __attribute__((mode(QI))) int8; 
typedef signed int __attribute__((mode(HI))) int16; 
typedef signed int __attribute__((mode(SI))) int32; 
typedef signed int __attribute__((mode(DI))) int64; 

typedef unsigned int __attribute__((mode(QI))) uint8; 
typedef unsigned int __attribute__((mode(HI))) uint16; 
typedef unsigned int __attribute__((mode(SI))) uint32; 
typedef unsigned int __attribute__((mode(DI))) uint64; 

/* Software barrier */
#define EE_barrier(...) \
    do { asm volatile("" : : : "memory"); } while(0)

#else

#error Compiler unsupported.

#endif /* __GNUC__ */

#endif /* __EECFG_THIS_IS_ASSEMBLER__ */

#endif  /* __INCLUDE_TRICORE1_EE_COMPILER_H__ */
