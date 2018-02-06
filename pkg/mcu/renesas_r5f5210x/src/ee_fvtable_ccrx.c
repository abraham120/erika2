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
	@file ee_vtable_ccrx.c
	@brief Fixed Interrupt Vector Table for use with Renesas HEW.
	@author Gianluca Franchino
	@date 2012
	@author Giuseppe Serano
	@date 2013
 */

#include "ee.h"
#include "mcu/renesas_r5f5210x/inc/ee_nmi.h"

/* Dummy Trap */
#pragma interrupt (EE_dummy_trap)
void EE_dummy_trap(void)
{
    /* Go into an infinite loop.*/
    while(1)
    {
    }
}

/* NMI Trap */
#ifndef	EE_RX200_NMI_TRAP
#define	EE_RX200_NMI_TRAP	EE_rx200_nmi_trap
#pragma interrupt (EE_RX200_NMI_TRAP)
void EE_RX200_NMI_TRAP(void)
{
    /* Go into an infinite loop.*/
    while(1)
    {
    }
}
#else
extern void EE_RX200_NMI_TRAP(void);
#endif

/* Supervisor Instruction Trap */
#ifndef	EE_RX200_SVI_TRAP
#define	EE_RX200_SVI_TRAP	EE_rx200_svi_trap
#pragma interrupt (EE_RX200_SVI_TRAP)
void EE_RX200_SVI_TRAP(void)
{ 
    /* Go into an infinite loop.*/
    while(1)
    {
    }
}
#else
extern void EE_RX200_SVI_TRAP(void);
#endif

/* Undefined Instruction Trap */
#ifndef	EE_RX200_UI_TRAP
#define	EE_RX200_UI_TRAP	EE_rx200_ui_trap
#pragma interrupt (EE_RX200_UI_TRAP)
void EE_RX200_UI_TRAP(void)
{
    /* Go into an infinite loop.*/
    while(1)
    {
    }
}
#else
extern void EE_RX200_UI_TRAP(void);
#endif

/* Floating Point Trap */
#ifndef	EE_RX200_FP_TRAP
#define	EE_RX200_FP_TRAP	EE_rx200_fp_trap
#pragma interrupt (EE_RX200_FP_TRAP)
void EE_RX200_FP_TRAP(void)
{
    /* Go into an infinite loop.*/
    while(1)
    {
    }
}
#else
extern void EE_RX200_FP_TRAP(void);
#endif

/* Reset Trap */
#ifndef	EE_RX200_RESET_TRAP
#define	EE_RX200_RESET_TRAP	EE_rx200_reset_trap
#endif
extern void EE_RX200_RESET_TRAP(void);

#pragma section C FIXEDVECT

void (*const Fixed_Vectors[])(void) = {
/* ;0xffffffd0  Exception (Supervisor Instruction) */
	EE_RX200_SVI_TRAP,
/* ;0xffffffd4  Reserved */
	EE_dummy_trap,
/* ;0xffffffd8  Reserved */
	EE_dummy_trap,
/* ;0xffffffdc  Exception (Undefined Instruction) */
	EE_RX200_UI_TRAP,
/* ;0xffffffe0  Reserved */
	EE_dummy_trap,
/* ;0xffffffe4  Exception (Floating Point) */
	EE_RX200_FP_TRAP,
/* ;0xffffffe8  Reserved */
	EE_dummy_trap,
/* ;0xffffffec  Reserved */
	EE_dummy_trap,
/* ;0xfffffff0  Reserved */
	EE_dummy_trap,
/* ;0xfffffff4  Reserved */
	EE_dummy_trap,
/* ;0xfffffff8  NMI */
	EE_RX200_NMI_TRAP,
/* ;0xfffffffc  RESET
 * ;<<VECTOR DATA START (POWER ON RESET)>>
 * ;Power On Reset PC */
	EE_RX200_RESET_TRAP                                                                                                                            
/* ;<<VECTOR DATA END (POWER ON RESET)>> */
};

#pragma address _MDEreg=0xffffff80	/* MDE register (Single Chip Mode) */
#ifdef __BIG
const unsigned long _MDEreg = 0xfffffff8;	/* big endian */
#else
const unsigned long _MDEreg = 0xffffffff;	/* little endian */
#endif
