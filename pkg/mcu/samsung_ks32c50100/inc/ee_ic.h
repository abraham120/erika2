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

/*
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_ic.h,v 1.4 2006/04/08 21:10:43 pj Exp $
 */

#include "mcu/samsung_ks32c50100/inc/ee_mcuregs.h"

#ifndef __INCLUDE_SAMSUNG_KS32C50100_IC_H__
#define __INCLUDE_SAMSUNG_KS32C50100_IC_H__

/*************************************************************************
 Interrupts handling
 *************************************************************************/

/* this is the source code for the support of the KS32C50100 Interrupt
   controller. This file declares a set of functions for handling the
   various registers of the peripheral, and a set of function that
   helps the initializations of some table used during the interrupt
   handling routines. 

   The following defines work only when __ALLOW_NESTED_IRQ__ is present:
   __IRQ_PRIORITY_MASKS__ is used to specify if some additional
   software should be used to appropriately set up the IRQ masks.

   __IRQ_PRIORITY_MASKS_NOCONST__ is used to specify that the mask
   vector used is not const. That can be useful if the masks changes
   during the application life. masks can be recalculated using the
   provided function EE_IC_compute_masks.

   __IRQ_VECTOR_NOCONST__ is used to specify that the IRQ vector can
   be changed at runtime. That feauture can be useful if you want to
   change the irq handlers during the life of the application
*/


/*
 * Constants 
 */

/* Masks */
#define IRQ_EXT0_MASK      (1<< 0) /* Ext 0 */
#define IRQ_EXT1_MASK      (1<< 1) /* Ext 1 */
#define IRQ_EXT2_MASK      (1<< 2) /* Ext 2 */
#define IRQ_EXT3_MASK      (1<< 3) /* Ext 3 */
#define IRQ_UART0TX_MASK   (1<< 4) /* UART0 Tx */
#define IRQ_UART0RX_MASK   (1<< 5) /* UART0 Rx & error*/
#define IRQ_UART1TX_MASK   (1<< 6) /* UART1 Tx */
#define IRQ_UART1RX_MASK   (1<< 7) /* UART1 Rx & error*/
#define IRQ_GDMA0_MASK     (1<< 8) /* GDMA ch. 0 */
#define IRQ_GDMA1_MASK     (1<< 9) /* GDMA ch. 1 */
#define IRQ_TIMER0_MASK    (1<<10) /* Timer 0 */
#define IRQ_TIMER1_MASK    (1<<11) /* Timer 1 */
#define IRQ_HDLCATX_MASK   (1<<12) /* HDLC A Tx */
#define IRQ_HDLCARX_MASK   (1<<13) /* HDLC A Rx */
#define IRQ_HDLCBTX_MASK   (1<<14) /* HDLC B Tx */
#define IRQ_HDLCBRX_MASK   (1<<15) /* HDLC B Rx */
#define IRQ_ETHBDMATX_MASK (1<<16) /* Ethernet BDMA Tx */
#define IRQ_ETHBDMARX_MASK (1<<17) /* Ethernet BDMA Rx */
#define IRQ_ETHMACTX_MASK  (1<<18) /* Ethernet MAC Tx */
#define IRQ_ETHMACRX_MASK  (1<<19) /* Ethernet MAC Rx */
#define IRQ_I2C_MASK       (1<<20) /* I2C-bus */
#define IRQ_GLOBAL_MASK    (1<<21)

/* Priorities */
#define IRQ_EXT0            0      /* Ext 0 */
#define IRQ_EXT1            1      /* Ext 1 */
#define IRQ_EXT2            2      /* Ext 2 */
#define IRQ_EXT3            3      /* Ext 3 */
#define IRQ_UART0TX         4      /* UART0 Tx */
#define IRQ_UART0RX         5      /* UART0 Rx & error*/
#define IRQ_UART1TX         6      /* UART1 Tx */
#define IRQ_UART1RX         7      /* UART1 Rx & error*/
#define IRQ_GDMA0           8      /* GDMA ch. 0 */
#define IRQ_GDMA1           9      /* GDMA ch. 1 */
#define IRQ_TIMER0         10      /* Timer 0 */
#define IRQ_TIMER1         11      /* Timer 1 */
#define IRQ_HDLCATX        12      /* HDLC A Tx */
#define IRQ_HDLCARX        13      /* HDLC A Rx */
#define IRQ_HDLCBTX        14      /* HDLC B Tx */
#define IRQ_HDLCBRX        15      /* HDLC B Rx */
#define IRQ_ETHBDMATX      16      /* Ethernet BDMA Tx */
#define IRQ_ETHBDMARX      17      /* Ethernet BDMA Rx */
#define IRQ_ETHMACTX       18      /* Ethernet MAC Tx */
#define IRQ_ETHMACRX       19      /* Ethernet MAC Rx */
#define IRQ_I2C            20      /* I2C-bus */



/* 
 * Types
 */

/* a number between 0 and 21 */
typedef EE_UINT32 EE_TYPEIRQ;

/* a bitmask from 0x0 to 0x001FFFFF */
typedef EE_UINT32 EE_TYPEIRQMASK;



/* 
 * Variables
 */


#ifdef __IRQ_VECTOR_NOCONST__
#define EE_IRQVECTOR_CONST
#else
#define EE_IRQVECTOR_CONST const
#endif

/* This is the external interrupt vector, that contains a function
   pointer for each external interrupt in the system. */
extern EE_IRQVECTOR_CONST EE_ADDR EE_IC_EXTIRQ_vector[22];

#if defined(__IRQ_PRIORITY_MASKS__) && defined(__ALLOW_NESTED_IRQ__)
/* the set of masks that can be used to mask the INTMSK register to
   implement a priority nesting */

#ifdef __IRQ_PRIORITY_MASKS_NOCONST__
#define EE_EXTIRQMASK_CONST
#else
#define EE_EXTIRQMASK_CONST const
#endif

extern EE_EXTIRQMASK_CONST EE_TYPEIRQMASK EE_IC_EXTIRQ_masks[21];
#endif




/* 
 * Functions
 */

/* parameters are a bit mask obtained using IRQ_*_MASK */

/* This function enables the external IRQ mask given as parameter.
   Inthis case, the global mask is enabled by default
 */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_enable_external_IRQ(EE_TYPEIRQMASK i)
{ *INTMSK &= ~(IRQ_GLOBAL_MASK | i); }

/* This function disables the external IRQs passed as parameters.
   The global mask in this case is not modified if not explicitly stated */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_disable_external_IRQ(EE_TYPEIRQMASK i)
{ *INTMSK |= (i); }

/* signal to the interrupt controller that the interrupts i have been
   serviced. it is typically not used, because the IRQ/FIQ handlers
   take care of it */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_accept_external_IRQ(EE_TYPEIRQMASK i)
{ *INTPND |= (i); }

/* clears ALL the pending interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_clear_pending_IRQ(void)
{ *INTPND = 0x000FFFFF; }

/* the specified interrupts are set as FIQ, the others as IRQ */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_interrupt_all_as_FIQ(EE_TYPEIRQMASK i)
{ *INTMOD = (i); }

/* the specified interrupts are set as FIQ, the others remains unaltered */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_interrupt_as_FIQ(EE_TYPEIRQMASK i)
{ *INTMOD |= (i); }

/* the specified interrupts are set as IRQ, the others remains unaltered */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_interrupt_as_IRQ(EE_TYPEIRQMASK i)
{ *INTMOD &= ~(i); }

/* set interrupt priorities 0-3 (0 the lowest) */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_0_3(EE_TYPEIRQ p0, EE_TYPEIRQ p1,
					  EE_TYPEIRQ p2, EE_TYPEIRQ p3)
{ *INTPRI0 = p0 + (p1<<8) + (p2<<16) + (p3<<24); }

/* set interrupt priorities 4-7 (4 the lowest) */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_4_7(EE_TYPEIRQ p4, EE_TYPEIRQ p5,
					  EE_TYPEIRQ p6, EE_TYPEIRQ p7)
{ *INTPRI1 = p4 + (p5<<8) + (p6<<16) + (p7<<24); }

/* set interrupt priorities 8-11 (8 the lowest) */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_8_11(EE_TYPEIRQ p8, EE_TYPEIRQ p9,
					    EE_TYPEIRQ p10, EE_TYPEIRQ p11)
{ *INTPRI2 = p8 + (p9<<8) + (p10<<16) + (p11<<24); }

/* set interrupt priorities 12-15 (12 the lowest) */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_12_15(EE_TYPEIRQ p12, EE_TYPEIRQ p13,
					     EE_TYPEIRQ p14, EE_TYPEIRQ p15)
{ *INTPRI3 = p12 + (p13<<8) + (p14<<16) + (p15<<24); }

/* set interrupt priorities 16-19 (16 the lowest) */
__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_16_19(EE_TYPEIRQ p16, EE_TYPEIRQ p17,
					     EE_TYPEIRQ p18, EE_TYPEIRQ p19)
{ *INTPRI4 = p16 + (p17<<8) + (p18<<16) + (p19<<24); }


/* set interrupt priority 0 to 20: 0 the lowest, 20 the highest */
/* Note: is it better to use + or | ??? */

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_0(EE_TYPEIRQ p)
{ *INTPRI0 = (*INTPRI0 && 0xFFFFFF00) + p; }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_1(EE_TYPEIRQ p)
{ *INTPRI0 = (*INTPRI0 && 0xFFFF00FF) + (p << 8); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_2(EE_TYPEIRQ p)
{ *INTPRI0 = (*INTPRI0 && 0xFF00FFFF) + (p << 16); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_3(EE_TYPEIRQ p)
{ *INTPRI0 = (*INTPRI0 && 0x00FFFFFF) + (p << 24); }


__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_4(EE_TYPEIRQ p)
{ *INTPRI1 = (*INTPRI1 && 0xFFFFFF00) + p; }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_5(EE_TYPEIRQ p)
{ *INTPRI1 = (*INTPRI1 && 0xFFFF00FF) + (p << 8); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_6(EE_TYPEIRQ p)
{ *INTPRI1 = (*INTPRI1 && 0xFF00FFFF) + (p << 16); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_7(EE_TYPEIRQ p)
{ *INTPRI1 = (*INTPRI1 && 0x00FFFFFF) + (p << 24); }


__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_8(EE_TYPEIRQ p)
{ *INTPRI2 = (*INTPRI2 && 0xFFFFFF00) + p; }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_9(EE_TYPEIRQ p)
{ *INTPRI2 = (*INTPRI2 && 0xFFFF00FF) + (p << 8); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_10(EE_TYPEIRQ p)
{ *INTPRI2 = (*INTPRI2 && 0xFF00FFFF) + (p << 16); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_11(EE_TYPEIRQ p)
{ *INTPRI2 = (*INTPRI2 && 0x00FFFFFF) + (p << 24); }


__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_12(EE_TYPEIRQ p)
{ *INTPRI3 = (*INTPRI3 && 0xFFFFFF00) + p; }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_13(EE_TYPEIRQ p)
{ *INTPRI3 = (*INTPRI3 && 0xFFFF00FF) + (p << 8); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_14(EE_TYPEIRQ p)
{ *INTPRI3 = (*INTPRI3 && 0xFF00FFFF) + (p << 16); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_15(EE_TYPEIRQ p)
{ *INTPRI3 = (*INTPRI3 && 0x00FFFFFF) + (p << 24); }


__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_16(EE_TYPEIRQ p)
{ *INTPRI4 = (*INTPRI4 && 0xFFFFFF00) + p; }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_17(EE_TYPEIRQ p)
{ *INTPRI4 = (*INTPRI4 && 0xFFFF00FF) + (p << 8); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_18(EE_TYPEIRQ p)
{ *INTPRI4 = (*INTPRI4 && 0xFF00FFFF) + (p << 16); }

__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_19(EE_TYPEIRQ p)
{ *INTPRI4 = (*INTPRI4 && 0x00FFFFFF) + (p << 24); }


__INLINE__ void __ALWAYS_INLINE__ EE_IC_set_IRQ_priority_20(EE_TYPEIRQ p)
{ *INTPRI5 = p; }


/* This function computes the masks to be used as values for
   EE_IC_EXTIRQ_masks. Usage: set the INTPRI* registers as wanted,
   then call this function. It will fill up a vector of 20 words
   containing the values for the INTMSK vector. 

   result must be a vector of at least 21 words.

   masked is the set of interrupts that are always masked (e.g.,
   because their interrupt must never be raised.
*/
void EE_IC_compute_masks(EE_TYPEIRQMASK *result, EE_TYPEIRQMASK masked);


#endif
