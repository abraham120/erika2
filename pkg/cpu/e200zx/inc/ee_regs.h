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
/*
 * e200zX register mappings.
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 *         2012 Francesco Esposito
 */

#ifndef __EE_CPU_E200ZX_REGS_H__
#define __EE_CPU_E200ZX_REGS_H__

#ifdef __DCC__
#define ASM_REORDER_OFF .set noreorder
#define ASM_REORDER_ON .set reorder
#else
#define ASM_REORDER_OFF
#define ASM_REORDER_ON
#endif

#ifdef __MWERKS__
/* CodeWarrior Assembly uses the deprecated macro __MWERKS__ */
#ifdef __VLE__
#define text_section(name)	.section name,.text_vle
#else /* __VLE__ */
#define text_section(name)	.section name,.text
#endif /* __VLE__ */
#else /* __MWERKS */
#define text_section(name)	.section name, , c
#endif /* __MWERKS */


#if defined(__VLE__)
/* Diab doesn't map the bctr instruction to its VLE equivalent */
#define bctr se_bctr
#endif /* __VLE__ */


#ifdef __MWERKS__ /* CodeWarrior Assembly uses this deprecated macro */
/* CodeWarrior doesn't recognize lower-case "sp" */
#define sp r1
#endif

#define SPRG_XER	1
#define SPRG_LR		8
#define SPRG_CTR	9
#define SPRG_SRR0	26
#define SPRG_SRR1	27

#define SPRG_IVOR_BASE	400
#define SPRG_IVPR	63

#define SPRG_DEC	22
#define SPRG_DECAR	54
#define SPRG_TBL_W	284
#define SPRG_TBH_W	285
#define SPRG_TCR	340
#define SPRG_TSR	336

#define SPRG_HID0	1008


/* IRQ vector  */

#ifdef __PPCE200Z0__
#define E200ZX_IRQ_VECTOR_BASE_ALIGN	4096
/* Z0 has fixed IVORs, at 16-byte intervals */
#define E200ZX_IRQ_ENTRY_ALIGN	16

#elif defined __PPCE200Z6__ || defined __PPCE200Z7__ || defined EE_PPCE200Z4
#define E200ZX_IRQ_VECTOR_BASE_ALIGN	E200ZX_IRQ_ENTRY_ALIGN
#define E200ZX_IRQ_ENTRY_ALIGN	16

#else
#error "Unknown CPU"
#endif


#ifdef __PPCE200Z0__
/* Z0 doesn't have any internal timer */
#define E200ZX_CPU_HAS_TB	0
#else
#define E200ZX_CPU_HAS_TB	1
#endif

#endif /* __EE_CPU_E200ZX_REGS_H__ */
