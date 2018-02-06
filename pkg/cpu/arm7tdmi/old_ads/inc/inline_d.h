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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: inline_d.h,v 1.2 2006/04/08 21:05:47 pj Exp $
 */

#ifndef __INCLUDE_ARM7ADS_INLINE_D_H__
#define __INCLUDE_ARM7ADS_INLINE_D_H__

#include "arm7ads/drivers.h"


/*
 * Generic interrupts controlling
 */

__INLINE__ void __ALWAYS_INLINE__ EE_enable_external_IRQ(EE_TYPEIRQ i)
{
    *INTMSK &= ~(IRQ_GLOBAL_MASK | i);
}

__INLINE__ void __ALWAYS_INLINE__ EE_disable_external_IRQ(EE_TYPEIRQ i)
{
    *INTMSK |= (i);
}

__INLINE__ void __ALWAYS_INLINE__ EE_accept_external_IRQ(EE_TYPEIRQ i)
{
    *INTPND |= (i);
}

__INLINE__ void __ALWAYS_INLINE__ EE_clear_pending_IRQ(void)
{
    *INTPND = 0x00000000;
}



/*
 * External IRQ #0 controlling
 */

#ifdef __EXT0_USED__

/* Initialize the EXT0 source interrupt (button)  */
__INLINE__ void __ALWAYS_INLINE__ EE_ext0_init(void)
{
    *IOPCON |= IO_ENABLE_EXT0;
    *IOPCON |= IO_ACTIVE_HIGH_EXT0;
    *IOPCON |= IO_RISING_EDGE_EXT0;
}

#endif /* __EXT0_USED__ */



/*
 * LEDs controlling
 */

#ifdef __LEDS_USED__

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void) {*IOPDATA = *IOPDATA | 16;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void) {*IOPDATA = *IOPDATA | 32;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void) {*IOPDATA = *IOPDATA | 64;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void) {*IOPDATA = *IOPDATA | 128;}

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void) {*IOPDATA = *IOPDATA ^ 16;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void) {*IOPDATA = *IOPDATA ^ 32;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void) {*IOPDATA = *IOPDATA ^ 64;}
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void) {*IOPDATA = *IOPDATA ^ 128;}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) {EE_led_1_off();}

#endif /* __LEDS_USED__ */



/*
 * LCD controlling
 */

#ifdef __LCD_USED__

/* Display LCD number. NOTE: Do not check whether number is in the
 * range of 0x0 and 0xf (if so then it cannot set the segment display
 * correctly!) */
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_display(EE_UREG num)
{
    *IOPDATA &= ~LCD_MASK;
    *IOPDATA |= EE_LCD_numeric_display[num];	
}

/* Initialize the 7 segment display.  */
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_init(void)
{
    *IOPMOD |= LCD_MASK;
    *IOPDATA |= LCD_MASK;
}

#endif /* __LCD_USED__ */



/*
 * Timers controlling
 */

#ifdef __TIMER_USED__

__INLINE__ void __ALWAYS_INLINE__ EE_timer_init(void)
{
    /* disable timer */
    *TMOD = 0;
}

#endif /* __TIMER_USED__ */



#ifdef __TIMER_0_USED__
__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_start(void)
{
//    *TMOD |= (1<<1);		/* toggle mode */
//    *TMOD &= ~(1<<2);		/* initial TOUT = 0 */
    *TMOD |= (1<<0);		/* enable timer */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_stop(void)
{
    *TMOD &= ~(1<<0);		/* disable timer */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_set(EE_UREG count_down)
{
    *TDATA0 = count_down;
}

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_0_get(void)
{
    return *TCNT0;
}

#endif /* __TIMER_0_USED__ */



#ifdef __TIMER_1_USED__
__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_start(void)
{
//    *TMOD |= (1<<(1+3));	/* toggle mode */
//    *TMOD &= ~(1<<(2+3));	/* initial TOUT = 0 */
    *TMOD |= (1<<(0+3));	/* enable timer */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_stop(void)
{
    *TMOD &= ~(1<<(0+3));		/* disable timer */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_set(EE_UREG count_down)
{
    *TDATA1 = count_down;
}

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_1_get(void)
{
    return *TCNT1;
}

#endif /* __TIMER_0_USED__ */



/*
 * DIP switch controlling
 */

#ifdef __DIP_SWITCH_USED__

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_dip_switch_get(void)
{
    return DIP_SWITCH_MASK & *IOPDATA;
}

#endif /* __DIP_SWITCH_USED__ */


#endif /* __INCLUDE_ARM7ADS_INLINE_D_H__ */
