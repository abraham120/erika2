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
	@file ee_irq_types.h
	@brief IRQ-related stuff for Lattice Mico32; types and common definitions 
	(used by both ee_irq_internal.h and ee_irq.h)
	@author Bernardo  Dal Seno
	@date 2009 - 2010
*/

#ifndef __INCLUDE_MICO32_IRQ_TYPES_H__
#define __INCLUDE_MICO32_IRQ_TYPES_H__

#include <MicoInterrupts.h>

/* Type for ISR handlers: they get called with the IRQ level as argument */
typedef void (*EE_mico32_ISR_handler)(int level);


/* Qualifiers for the interrupt handler table */
#ifdef __STATIC_ISR_TABLE__
#define MICO32_ISR_TABLE_QUALIFIER const
#else
#define MICO32_ISR_TABLE_QUALIFIER
#endif


/* Length of the ISR table */
#define MICO32_ISR_TABLE_LEN  (MAX_MICO32_ISR_LEVEL + 1)


/* Used to declare static handlers in eecfg.c */
#define DECLARE_MICO32_ISR_HANDLER(h)  void h(int)


#endif /* __INCLUDE_MICO32_IRQ_TYPES_H__ */
