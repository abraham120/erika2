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
 * Author: Antonio Fiaschi
 * CVS: $Id: ee_primitivestubs.S,v 1.2 2004/12/21 14:52:29 fiaschi Exp $
 */

#include "ee_libapi.h"

#include "cpu/mpc5protected/inc/ee_macro.h"

#ifdef __FP__
#define EE_API_ID_EE_THREAD_END_INSTANCE EE_API_ID_EE_FP_THREAD_END_INSTANCE
#endif

	.global EE_hal_protected_stub
	.global EE_hal_protected_stub_r
	.global EE_hal_protected_stub_1p
	.global EE_hal_protected_stub_r_1p
	.global EE_hal_protected_stub_2p
	.global EE_hal_protected_stub_r_2p
	.global EE_hal_protected_stub_3p
	.global EE_hal_protected_stub_r_3p

	.global EE_hal_stub_end_instance
	.global	EE_hal_stub_IRQ_epilogue
	
	.text

	.type	EE_hal_stub_IRQ_epilogue, @function
EE_hal_stub_IRQ_epilogue:

	// Call the selected handler
	blrl

	// Call IRQ_epilogue primitive
	li	r11, EE_API_ID_EE_IRQ_EPILOGUE
	sc
	.size	EE_hal_stub_IRQ_epilogue, . - EE_hal_stub_IRQ_epilogue

        .type   EE_hal_stub_end_instance, @function
EE_hal_stub_end_instance:
                                                                                
        // Branch to the thread
        blrl
                                                                                
        // Call thread_end_instance primitve
        li      r11, EE_API_ID_EE_THREAD_END_INSTANCE
        sc
        .size   EE_hal_stub_end_instance, . - EE_hal_stub_end_instance
                                                                                
// void EE_hal_protected_stub(EE_UREG primitive)
	.type	EE_hal_protected_stub, @function
EE_hal_protected_stub:
	mr	r11, r3
	sc
	blr
	.size	EE_hal_protected_stub, . - EE_hal_protected_stub

// EE_UREG EE_hal_protected_stub_r(EE_UREG primitive)
	.type	EE_hal_protected_stub_r, @function
EE_hal_protected_stub_r:
        mr      r11, r3
        sc
        blr
	.size	EE_hal_protected_stub_r, . - EE_hal_protected_stub_r

// void EE_hal_protected_stub_1p(EE_UREG par1, EE_UREG primitive)
	.type	EE_hal_protected_stub_1p, @function
EE_hal_protected_stub_1p:
	mr      r11, r4
	sc	
	blr
	.size	EE_hal_protected_stub_1p, . - EE_hal_protected_stub_1p

// EE_UREG EE_hal_protected_stub_r_1p(EE_UREG par1, EE_UREG primitive)
	.type	EE_hal_protected_stub_r_1p, @function
EE_hal_protected_stub_r_1p:
	mr	r11, r4
	sc
	blr
	.size	EE_hal_protected_stub_r_1p, . - EE_hal_protected_stub_r_1p

// void EE_hal_protected_stub_2p(EE_UREG par1, EE_UREG par2, EE_UREG primitve)
	.type	EE_hal_protected_stub_2p, @function
EE_hal_protected_stub_2p:
        mr      r11, r5
        sc
        blr
	.size	EE_hal_protected_stub_2p, . - EE_hal_protected_stub_

// EE_UREG EE_hal_protected_stub_r_2p(EE_UREG par1, EE_UREG par2, EE_UREG primitive)
	.type	EE_hal_protected_stub_r_2p, @function
EE_hal_protected_stub_r_2p:
	mr	r11, r5
	sc
	blr
	.size	EE_hal_protected_stub_r_2p, . - EE_hal_protected_stub_r_2p

// void EE_hal_protected_stub_3p(EE_UREG par1, EE_UREG par2, EE_UREG par3, EE_UREG primitive)
	.type	EE_hal_protected_stub_3p, @function
EE_hal_protected_stub_3p:
	mr	r11, r6
	sc
	blr
	.size	EE_hal_protected_stub_3p, . - EE_hal_protected_stub_3p

// EE_UREG EE_hal_protected_stub_r_3p(EE_UREG par1, EE_UREG par2, EE_UREG par3, EE_UREG primitive)
        .type   EE_hal_protected_stub_r_3p, @function
EE_hal_protected_stub_r_3p:
        mr      r11, r6
        sc
        blr
        .size   EE_hal_protected_stub_r_3p, . - EE_hal_protected_stub_r_3p


