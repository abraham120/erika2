/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
	@file mcu\mico32\inc\ee_internal.h
	@brief ee_internal.h for mcu.
	@author Dario Di Stefano
	@date 2010
*/
 
#ifndef __INCLUDE_MCUMICO32_INTERNAL_H__
#define __INCLUDE_MCUMICO32_INTERNAL_H__

 /*
 * FRSH
 */

#if defined(__FRSH__)
/* This function set the capacity timer to raise in t ticks. */
void EE_hal_set_budget_timer(EE_STIME t);

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_budget_timer(void)
{
  // TODO!!!
}
#endif  /* __FRSH__ */

/* Macros used by drivers */
#define cat3_ind(a,b,c) cat3(a,b,c)
#define cat3(a, b, c)  a ## b ## c
#define cat2(a, b) a ## b
#define EE_BASE_ADD(uc) cat2(uc, _BASE_ADDRESS)
#define EE_NULL_CBK ((EE_ISR_callback)0)
/* Macro for the structure name generation */
#define EE_ST_NAME(lc) cat3(ee_, lc, _st)
/* Macro for vectors (buffers) name generation */
#define EE_VETRX_NAME(lc) cat3(ee_, lc, _isr_rxvet)
#define EE_VETTX_NAME(lc) cat3(ee_, lc, _isr_txvet)
#define EE_IRQ_NAME(uc) cat2(uc, _IRQ)


#endif /* __INCLUDE_MCUMICO32_INTERNAL_H__ */
