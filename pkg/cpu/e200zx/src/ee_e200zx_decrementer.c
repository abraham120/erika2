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
 * Author: 2011  Bernardo  Dal Seno
 *         2010  Fabio Checconi
 */

#include <ee_internal.h>

#ifndef __PPCE200Z0__
/* e200z0 has no internal timer, so the functions below are not defined */

void EE_e200zx_setup_fixed_intv(EE_UREG bitpos)
{
	EE_UREG tcr;
	tcr = EE_e200zx_get_tcr();
	tcr |= ((EE_UREG)1 << TCR_FIE);
	tcr &= ~(EE_UREG)TCR_FPALL_MASK;
	tcr |= ((bitpos & (EE_UREG)0x3) << TCR_FP)
		| (((bitpos >> 2) & (EE_UREG)0xf) << TCR_FPEXT);
	EE_e200zx_set_tcr(tcr);
}

void EE_e200zx_stop_fixed_intv(void)
{
	EE_UREG tcr;
	tcr = EE_e200zx_get_tcr();
	tcr &= ~((EE_UREG)1 << TCR_FIE);
	EE_e200zx_set_tcr(tcr);
}

void EE_e200z7_setup_decrementer(EE_UINT32 dec_value)
{
	EE_UREG tcr;
	EE_e200zx_set_decar(dec_value);
	EE_e200zx_set_dec(dec_value);
	tcr = EE_e200zx_get_tcr();
	tcr |= ((EE_UREG)1 << TCR_DIE) | ((EE_UREG)1 << TCR_ARE);
	EE_e200zx_set_tcr(tcr);
}

void EE_e200z7_setup_decrementer_oneshot(EE_UINT32 oneshotvalue)
{
	EE_UREG tcr;
	EE_e200zx_set_dec(oneshotvalue);
	tcr = EE_e200zx_get_tcr();
	tcr |= ((EE_UREG)1 << TCR_DIE);
	tcr &= ~((EE_UREG)1 << TCR_ARE);
	EE_e200zx_set_tcr(tcr);
}

void EE_e200z7_stop_decrementer(void)
{
	EE_UREG tcr;
	tcr = EE_e200zx_get_tcr();
	tcr &= ~((EE_UREG)1 << TCR_ARE);
	EE_e200zx_set_tcr(tcr);
	EE_e200zx_set_dec(0U);
	EE_e200zx_set_decar(0U);
	tcr = EE_e200zx_get_tcr();
	tcr &= ~((EE_UREG)1 << TCR_DIE);
	EE_e200zx_set_tcr(tcr);
	EE_e200zx_set_tsr((EE_UREG)1 << TSR_DIS);
}

void EE_e200zx_delay(EE_UINT32 ticks)
{
	EE_UINT32 start;
	start = EE_e200zx_get_tbl();
	/* (EE_e200zx_get_tbl() - start) is always the number of ticks from the
	 * beginning, even if a wrap-around has occurred. */
	while ((EE_e200zx_get_tbl() - start) < ticks) {
		/* Wait */
	}
}

#endif /* ! __PPCE200Z0__ */
