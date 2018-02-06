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

#ifndef __INCLUDE_TRICORE1_EE_CPU_H__
#define __INCLUDE_TRICORE1_EE_CPU_H__

#include "cpu/tricore1/inc/ee_compiler.h"
#include "cpu/tricore1/inc/ee_hal.h"

/* Inclusions at the bottom to break dependency cycle */

/*************************************************************************
 CPU dependent data types
*************************************************************************/

#if defined(__TC13__) || defined(__TC131__)

/* Previous Context Information Register */
typedef union {
    struct {
        EE_UINT32 PCXO   :16; /* Previous Context Pointer Offset Address  */
        EE_UINT32 PCXS   :4;  /* Previous Context Pointer Segment Address */
        EE_UINT32 _bit20 :1;  /* Reserved */
        EE_UINT32 _bit21 :1;  /* Reserved */
        EE_UINT32 UL     :1;  /* Upper or Lower Context Tag */
        EE_UINT32 PIE    :1;  /* Previous Interrupt Enable */
        EE_UINT32 PCPN   :8;  /* Previous CPU Priority Number */ 
    } bits;
    EE_UINT32 reg;
} __ALIGNED__(4) EE_PCXI;


/* Context Save Area Link Word (only PCXS and PCXO are valid)*/
typedef EE_PCXI EE_CSA_LINK;


/* Context Save Area (16 words, upper or lower context) */
typedef struct {
    EE_CSA_LINK next;
    union {
        struct {
            EE_UREG PSW;
            EE_UREG A10;
            EE_UREG A11;
            EE_UREG D8;
            EE_UREG D9;
            EE_UREG D10;
            EE_UREG D11;
            EE_UREG A12;
            EE_UREG A13;
            EE_UREG A14;
            EE_UREG A15;
            EE_UREG D12;
            EE_UREG D13;
            EE_UREG D14;
            EE_UREG D15;
        } ucx;
        struct {
            EE_UREG A11;
            EE_UREG A2;
            EE_UREG A3;
            EE_UREG D0;
            EE_UREG D1;
            EE_UREG D2;
            EE_UREG D3;
            EE_UREG A4;
            EE_UREG A5;
            EE_UREG A6;
            EE_UREG A7;
            EE_UREG D4;
            EE_UREG D5;
            EE_UREG D6;
            EE_UREG D7;
        } lcx;
    };
} __ALIGNED__(64) EE_CSA;


/* Interrupt control register */
typedef union {
    struct {
        EE_UREG CCPN    :8; /* Current CPU Priority Number */
        EE_UREG IE      :1; /* Interrupt Enable */
        EE_UREG _bit9   :1;
        EE_UREG _bit10  :1;
        EE_UREG _bit11  :1;
        EE_UREG _bit12  :1;
        EE_UREG _bit13  :1;
        EE_UREG _bit14  :1;
        EE_UREG _bit15  :1;
        EE_UREG PIPN    :8; /* Pending Interrupt Priority Number */
        EE_UREG CARBCYC :2; /* Number of Arbitration Cycles */
        EE_UREG CONECYC :1; /* No. of Clks per Arb. Cycle Control */
        EE_UREG _bit27  :1;
        EE_UREG _bit28  :1;
        EE_UREG _bit29  :1;
        EE_UREG _bit30  :1;
        EE_UREG _bit31  :1;
    } bits;
    EE_UREG reg;
} __ALIGNED__(4) EE_ICR;



/*************************************************************************
 Application dependent data types
*************************************************************************/

#ifdef __HAS_TYPES_H__
#include "types.h"
#endif


/*************************************************************************
 Execution barriers
*************************************************************************/

/* Data barrier */
#define EE_tc1_dsync(...) \
    asm volatile("dsync")

/* Instruction barrier */
#define EE_tc1_isync(...) \
    asm volatile("isync")


/*********************************************************************
 TRICORE1 information
*********************************************************************/

__INLINE__ unsigned int __ALWAYS_INLINE__ EE_tc1_cpu_model(void)
{
    EE_UREG r;
    asm ("mfcr %0, $cpu_id" : "=d"(r));
    return (r >> 0x10);
}


__INLINE__ unsigned int __ALWAYS_INLINE__ EE_tc1_cpu_revision(void)
{
    EE_UREG r;
    asm ("mfcr %0, $cpu_id": "=d"(r));
    return (r & 0xff);
}


#ifdef __TC131__
/* Reads the CPU Clock Cycle Counter (includes overflow bit) */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_tc1_get_CCTN(void)
{
    EE_UREG r;
    asm ("mfcr %0, $cctn": "=d"(r));
    return r;
}
#endif


/*********************************************************************
 TRICORE1 interrupt support 
*********************************************************************/

#ifdef __GNUC__

/* Enable interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_enableIRQ(void)
{
    asm volatile ("enable");
}

/* Disable interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_disableIRQ(void)
{
    asm volatile ("disable");
}


/* Returns the first CSA in the Previous Context List */
__INLINE__ EE_ICR  __ALWAYS_INLINE__ EE_tc1_get_ICR()
{
    EE_ICR icr; 
    asm volatile ("mfcr %0, $icr" : "=d"(icr.reg));
    return icr;
}


/* Set the first CSA in the Previous Context List */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_set_ICR(EE_ICR icr)
{
    asm volatile ("mtcr $icr, %0" : : "d"(icr));
}


/* Return ICR.IE. */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_tc1_interrupts_enabled(void)
{
    EE_ICR icr;
    asm volatile ("mfcr %0, $icr" : "=D"(icr.reg));
    return icr.bits.IE;    
}


#else 

#error Compiler not supported.

#endif


/*********************************************************************
 TRICORE1 context handling
*********************************************************************/


#ifdef __GNUC__


__INLINE__ void __ALWAYS_INLINE__ EE_tc1_jump(EE_THREAD_PTR t)
{
    asm volatile ("ji %0" : : "a"(t));
}


__INLINE__ void __ALWAYS_INLINE__ EE_tc1_jump_and_link(EE_THREAD_PTR t)
{
    asm volatile ("jli %0" : : "a"(t));
}


__INLINE__ EE_ADDR __ALWAYS_INLINE__ EE_tc1_get_RA(void)
{
    EE_ADDR reg;
    asm volatile ("mov.d %0, %%a11" : "=d"(reg));
    return reg;
}


__INLINE__ void __ALWAYS_INLINE__ EE_tc1_set_RA(EE_ADDR reg)
{
    asm volatile ("mov.a %%a11, %0" : : "d"(reg));
}


__INLINE__ EE_ADDR __ALWAYS_INLINE__ EE_tc1_get_SP(void)
{
    EE_ADDR reg;
    asm volatile ("mov.d %0, %%a10" : "=d"(reg));
    return reg;
}


__INLINE__ void __ALWAYS_INLINE__ EE_tc1_set_SP(EE_ADDR reg)
{
    asm volatile ("mov.a %%a10, %0" : : "d"(reg));
}

#else 

#error Compiler not supported.

#endif 


/*********************************************************************
 TRICORE1 CSA handling
*********************************************************************/

#ifdef __GNUC__


/* Makes a CSA pointer from a CSA link word */
__INLINE__ EE_CSA* __ALWAYS_INLINE__ EE_tc1_csa_make_addr(EE_CSA_LINK link)
{
    return (EE_CSA*)((link.bits.PCXS << 28) | (link.bits.PCXO << 6));
}


/* Returns the first CSA in the Free Context List */
__INLINE__ EE_CSA_LINK __ALWAYS_INLINE__ EE_tc1_csa_get_fcx()
{
    EE_CSA_LINK head;
    asm volatile ("mfcr %0, $fcx" : "=d"(head));
    return head;
}


/* Set the first CSA in the Free Context List */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_csa_set_fcx(EE_CSA_LINK link)
{
    asm volatile ("mtcr $fcx, %0" : : "d"(link));
}


/* Returns the first CSA in the Previous Context List */
__INLINE__ EE_CSA_LINK __ALWAYS_INLINE__ EE_tc1_csa_get_pcxi()
{
    EE_CSA_LINK head;
    asm volatile ("mfcr %0, $pcxi" : "=d"(head));
    return head;
}


/* Set the first CSA in the Previous Context List */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_csa_set_pcxi(EE_CSA_LINK link)
{
    asm volatile("mtcr $pcxi, %0" : : "d"(link));
}

#else 

#error Compiler not supported.

#endif 


/* 
 * Note: 
 * CSAs must be located in one and the same segment for this implementation.
 */


/* Returns the link work of a given CSA */
__INLINE__ EE_CSA_LINK __ALWAYS_INLINE__ EE_tc1_csa_get_next(EE_CSA_LINK link)
{
    extern EE_CSA __CSA_BEGIN; /* FIXME: Proper wrapping */
    return (&__CSA_BEGIN)[link.bits.PCXO].next;
}


/* Sets the link word of a given CSA 'at' to 'link* */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_csa_set_next(EE_CSA_LINK at,
                                                      EE_CSA_LINK link)
{
    extern EE_CSA __CSA_BEGIN; /* FIXME: Proper wrapping */
    (&__CSA_BEGIN)[at.bits.PCXO].next = link; 
}


/* Places item after a given CSA into the Previous Context List. 
 * For head-insertion, use EE_tc1_csa_push().
 */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_csa_insert(EE_CSA_LINK at, 
                                                    EE_CSA_LINK link)
{
    EE_CSA_LINK next = EE_tc1_csa_get_next(at);
    EE_tc1_csa_set_next(link, next); 
    EE_tc1_csa_set_next(at, link); 
}


/* Removes the successor of a given CSA from the Previous Context List. 
 * Returns a link to the removed CSA. 
 */ 
__INLINE__ EE_CSA_LINK __ALWAYS_INLINE__ EE_tc1_csa_remove_next(EE_CSA_LINK at)
{
    EE_CSA_LINK next = EE_tc1_csa_get_next(at);
    EE_tc1_csa_set_next(at, EE_tc1_csa_get_next(next));
    return next;
}


/* Insert CSA as the head of the Previous Context List. */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_csa_push(EE_CSA_LINK link)
{
    EE_CSA_LINK head = EE_tc1_csa_get_pcxi();
    EE_tc1_csa_set_next(link, head);
    EE_tc1_csa_set_pcxi(link);
}


/* Removes and resets the head of the Previous Context List 
 * Returns the old head.
 */
__INLINE__ EE_CSA_LINK __ALWAYS_INLINE__ EE_tc1_csa_pop(void)
{
    EE_CSA_LINK head = EE_tc1_csa_get_pcxi();
    EE_CSA_LINK next = EE_tc1_csa_get_next(head);
    EE_tc1_csa_set_pcxi(next);
    return head;
}


/* Removes a CSA from the Free Context List */
__INLINE__ EE_CSA_LINK __ALWAYS_INLINE__ EE_tc1_csa_alloc(void)
{
    EE_CSA_LINK head = EE_tc1_csa_get_fcx();
    EE_CSA_LINK next = EE_tc1_csa_get_next(head);
    EE_tc1_csa_set_fcx(next);
    return head;
}


/* Inserts CSA into the Free Context List. */
__INLINE__ void __ALWAYS_INLINE__ EE_tc1_csa_free(EE_CSA_LINK link)
{
    EE_CSA_LINK head = EE_tc1_csa_get_fcx();
    EE_tc1_csa_set_next(link, head);
    EE_tc1_csa_set_fcx(link);
}


/*************************************************************************
 HAL Interrupt handling
*************************************************************************/


/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    EE_tc1_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_tc1_disableIRQ();
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

#else 

#error CPU not supported

#endif /* __TC13__ || __TC131__ */


#endif /* __INCLUDE_TRICORE1_EE_CPU_H__ */
