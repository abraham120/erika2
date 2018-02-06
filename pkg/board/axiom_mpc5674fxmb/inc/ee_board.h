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
/*
 * MPC5674FXMB register mappings
 * Author: 2010 Fabio Checconi
 */

#ifndef AXIOM_MPC5674FXMB_BOARD_H
#define AXIOM_MPC5674FXMB_BOARD_H

#define SIU_BASE	0xc3f90000U

#define SIU_PCRS	((volatile EE_UINT16 *)SIU_BASE)

/* Leds */
#define SIU_PCR147	SIU_PCRS[179U]
#define SIU_PCR148	SIU_PCRS[180U]
#define SIU_PCR149	SIU_PCRS[181U]
#define SIU_PCR150	SIU_PCRS[182U]
#define SIU_PCR151	SIU_PCRS[183U]
#define SIU_PCR152	SIU_PCRS[184U]
#define SIU_PCR153	SIU_PCRS[185U]
#define SIU_PCR154	SIU_PCRS[186U]
/* Button */
#define SIU_PCR450	SIU_PCRS[482U]

#define SIU_GPIO	((volatile EE_UINT8 *)(SIU_BASE + 0x0600U))

#define SIU_IREER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0028U))
#define SIU_IFEER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x002cU))

#define SIU_EISR	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0014U))

#define SIU_DIRER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0018U))

#define SIU_DIRSR	(*(volatile EE_UINT32 *)(SIU_BASE + 0x001cU))

#define SIU_EIISR	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0904U))

#ifdef __USE_LEDS__

#define LED_0	1U
#define LED_1	2U
#define LED_2	4U
#define LED_3	8U
#define LED_4	16U
#define LED_5	32U
#define LED_6	64U
#define LED_7	128U

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void)
{
	SIU_PCR147 = 0x200U;
	SIU_PCR148 = 0x200U;
	SIU_PCR149 = 0x200U;
	SIU_PCR150 = 0x200U;
        SIU_PCR151 = 0x200U;
        SIU_PCR152 = 0x200U;
        SIU_PCR153 = 0x200U;
        SIU_PCR154 = 0x200U;
	SIU_GPIO[147] = 1U;
	SIU_GPIO[148] = 1U;
	SIU_GPIO[149] = 1U;
	SIU_GPIO[150] = 1U;
        SIU_GPIO[151] = 1U;
	SIU_GPIO[152] = 1U;
	SIU_GPIO[153] = 1U;
	SIU_GPIO[154] = 1U;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds(EE_UREG led)
{
        SIU_GPIO[147] =  (EE_UINT8)led & 1U;
	SIU_GPIO[148] = ((EE_UINT8)led >> 1U) & 1U;
	SIU_GPIO[149] = ((EE_UINT8)led >> 2U) & 1U;
	SIU_GPIO[150] = ((EE_UINT8)led >> 3U) & 1U;
        SIU_GPIO[151] = ((EE_UINT8)led >> 4U) & 1U;
        SIU_GPIO[152] = ((EE_UINT8)led >> 5U) & 1U;
        SIU_GPIO[153] = ((EE_UINT8)led >> 6U) & 1U;
        SIU_GPIO[154] = ((EE_UINT8)led >> 7U) & 1U;
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_set(EE_UREG idx, EE_UREG val)
{
  SIU_GPIO[147U + idx] = (EE_UINT8)val;
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_0_on(void)  { EE_led_set(0U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_0_off(void) { EE_led_set(0U, 0U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void)  { EE_led_set(1U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void) { EE_led_set(1U, 0U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void)  { EE_led_set(2U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void) { EE_led_set(2U, 0U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void)  { EE_led_set(3U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void) { EE_led_set(3U, 0U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void)  { EE_led_set(4U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void) { EE_led_set(4U, 0U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_5_on(void)  { EE_led_set(5U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_5_off(void) { EE_led_set(5U, 0U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_6_on(void)  { EE_led_set(6U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_6_off(void) { EE_led_set(6U, 0U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_7_on(void)  { EE_led_set(7U, 1U); }
__INLINE__ void __ALWAYS_INLINE__ EE_led_7_off(void) { EE_led_set(7U, 0U); }

#endif

#ifdef __USE_BUTTONS__

#define BUTTON_0	1U

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_disable_interrupts(EE_UREG btn)
{
	EE_UINT32 val;

	val = SIU_DIRER;
	SIU_DIRER = val & ~1U;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_enable_interrupts(EE_UREG btn)
{
	EE_UINT32 val;

	val = SIU_DIRER;
	SIU_DIRER = val | 1U;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_clear_ISRflag(EE_UREG btn)
{
	SIU_EISR = 1U;
}

__INLINE__ EE_TYPEBOOL __ALWAYS_INLINE__ EE_button_get_B0(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0FC0U))&0x100U);
}

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init(EE_UREG btn, int n)
{
	EE_UINT32 val;

	SIU_PCR450 = 0x900U;
	val = SIU_EIISR;
	SIU_EIISR = val & ~3U;
	val = SIU_IFEER;
	SIU_IREER = val | 1U;
	val = SIU_DIRER;
	SIU_DIRER = val | 1U;
	SIU_DIRSR = 0U;
}

#endif

#endif
