/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2011 Steve Langstaff
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
 * Header file for system clock setting functions.
 * Author: 2011, Steve Langstaff
 */


#ifndef __INCLUDE_MSP430_MCU_SYSCLK_H__
#define __INCLUDE_MSP430_MCU_SYSCLK_H__

/*
 * We specify the clock rate in the function name so that we can check that
 * the rate is supported at compile-time rather than run-time.
 * The conditional compilation means that this function is only defined if
 * the header file for the specific device variant has the relevant flash
 * offsets defined.
 *
 * TODO: It seems that The ValueLine parts like those supplied with the
 * LaunchPad development tool are calibrated for 1MHz operation but not
 * other speeds - perhaps we should chop out the unsupported speeds somehow?
 */
#if (defined(CALBC1_1MHZ_) && defined(CALDCO_1MHZ_))
__INLINE__ void __ALWAYS_INLINE__ EE_sysclk_init_1MHz(void)
{
    BCSCTL1 = CALBC1_1MHZ;
    DCOCTL = CALDCO_1MHZ;
}
#endif

#if (defined(CALBC1_8MHZ_) && defined(CALDCO_8MHZ_))
__INLINE__ void __ALWAYS_INLINE__ EE_sysclk_init_8MHz(void)
{
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;
}
#endif

#if (defined(CALBC1_12MHZ_) && defined(CALDCO_12MHZ_))
__INLINE__ void __ALWAYS_INLINE__ EE_sysclk_init_12MHz(void)
{
    BCSCTL1 = CALBC1_12MHZ;
    DCOCTL = CALDCO_12MHZ;
}
#endif

#if (defined(CALBC1_16MHZ_) && defined(CALDCO_16MHZ_))
__INLINE__ void __ALWAYS_INLINE__ EE_sysclk_init_16MHz(void)
{
    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL = CALDCO_16MHZ;
}
#endif

#endif
