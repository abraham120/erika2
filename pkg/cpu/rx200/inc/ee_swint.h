/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
	
	@file ee_swint.h
	@brief Swint ISR
	@author Gianluca Franchino
	@date 2013
*/ 

#ifndef __INCLUDE_RX200_SWINT_H__
#define __INCLUDE_RX200_SWINT_H__

#ifdef __CCRX__
#include "cpu/common/inc/ee_compiler_ccrx.h"
#else
#error Unsupported compiler
#endif

#ifdef	__USE_SWINT__

__INLINE__ void __ALWAYS_INLINE__  EE_enable_swint(EE_UINT8 pri_lev)
{
	/*Set SWINT interrupt priority level */
	if (pri_lev > 15)
	/*Set SWINT interrupt priority level */
		ICU.IPR[IPR_ICU_SWINT].BIT.IPR = 15;
	else 
		ICU.IPR[IPR_ICU_SWINT].BIT.IPR = pri_lev;
	
	/*Enable SWINT interrupt in ICU*/
	ICU.IER[IER_ICU_SWINT].BIT.IEN_ICU_SWINT = 1;
	
}

/*Trigger SW interrupt*/
__INLINE__ void __ALWAYS_INLINE__  EE_swint()
{
	ICU.SWINTR.BIT.SWINT = 1;
}

#endif /*__USE_SWINT__*/

#endif /* __INCLUDE_RX200_SWINT_H__ */
