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

 /**
    @file   ee_board.h
    @brief  stellaris board header file.

    Header file taht contains board's API declaration, and defines
    for remap mcu drivers on board layout.

    @author Giuseppe Serano
    @date   2011
  */

#ifndef __INCLUDE_STELLARIS_LM4F232XXXX_BOARD_H__
#define __INCLUDE_STELLARIS_LM4F232XXXX_BOARD_H__

#include "mcu/ti_stellaris_lm4f232xxxx/inc/ee_mcu.h"

/*
 * User Led
 */
#ifdef __USE_USER_LED__

#define	USER_LED_MASK	0x04

/** @brief User led initialization **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_init(void)
{

    //
    // Enable the GPIO port G (R6) that is used for the on-board LED.
    //
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R6;

    //
    // Enable the GPIO pin for the LED (PG2).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIO_PORTG_DIR_R |= USER_LED_MASK;
    GPIO_PORTG_DEN_R |= USER_LED_MASK;

}

/** @brief User led on **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_on(void)
{
    GPIO_PORTG_DATA_R |= USER_LED_MASK;
}

/** @brief User_led_off **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_off(void)
{
    GPIO_PORTG_DATA_R &= ~(USER_LED_MASK);
}

/** @brief User led toggle **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_led_toggle(void)
{
    GPIO_PORTG_DATA_R ^= USER_LED_MASK;
}

#endif /* __USE_USER_LED__ */

/*
 * User Buttons
 */
#ifdef __USE_USER_BUTTONS__

#define	NUM_BUTTONS	5
#define	UP_BUTTON	0x00000001
#define	DOWN_BUTTON	0x00000002
#define	LEFT_BUTTON	0x00000004
#define	RIGHT_BUTTON	0x00000008
#define	SELECT_BUTTON	0x00000010

#define	ALL_BUTTONS	( \
  LEFT_BUTTON | RIGHT_BUTTON | UP_BUTTON | DOWN_BUTTON | SELECT_BUTTON \
)

/** @brief User buttons initialization **/
__INLINE__ void __ALWAYS_INLINE__ EE_user_buttons_init(void)
{

    //
    // Enable the GPIO port M (R11) that is used for the on-board buttons.
    //
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R11;

    //
    // Enable the GPIO pin for the on-board buttons.
    // Set the direction as input, weak pull-up and enable the GPIO pin for 
    // digital function.
    //
    GPIO_PORTM_DIR_R &= ~ALL_BUTTONS;
    GPIO_PORTM_PUR_R |= ALL_BUTTONS;
    GPIO_PORTM_DEN_R |= ALL_BUTTONS;

}

/** @brief Enables the User Buttons interrupt. */
__INLINE__ void __ALWAYS_INLINE__ EE_user_buttons_enable_int(void)
{

  register EE_UREG tmp;

  tmp = GPIO_PORTM_IM_R;

  /* Disables PORT M Interrupts */
  GPIO_PORTM_IM_R = 0x00000000;

  /* Edge Triggered Interrupt */
  GPIO_PORTM_IS_R &= ~ALL_BUTTONS;

  /* Single Edge Triggered Interrupts */
  GPIO_PORTM_IBE_R &= ~ALL_BUTTONS;

  /* Falling Edge Triggered Interrupts */
  GPIO_PORTM_IEV_R &= ~ALL_BUTTONS;

  /* Enables User Buttons Interrupts */
  GPIO_PORTM_IM_R = (tmp | ALL_BUTTONS);

}

/** @brief Disables the User Buttons interrupt. */
__INLINE__ void __ALWAYS_INLINE__ EE_user_buttons_disable_int(void)
{

  /* Disables User Buttons Interrupts */
  GPIO_PORTM_IM_R &= ~ALL_BUTTONS;

}

/** @brief Clear the User Buttons interrupt sources. */
__INLINE__ void __ALWAYS_INLINE__ EE_user_buttons_clear_int(void)
{

  /* Clear User Buttons Interrupt Source */
  GPIO_PORTM_ICR_R |= ALL_BUTTONS;

}

/** @brief User Buttons Status Retrieval */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_user_buttons_get_status(void)
{
  return GPIO_PORTM_DATA_R & ALL_BUTTONS;
}

#endif /* __USE_USER_BUTTONS__ */

/*
 * OLED Display
 */
#ifdef __USE_OLED_DISPLAY__

#define	OLED_DISPLAY_LEDS_NUM	8
#define	OLED_DISPLAY_LED_0	0x01
#define	OLED_DISPLAY_LED_1	0x02
#define	OLED_DISPLAY_LED_2	0x04
#define	OLED_DISPLAY_LED_3	0x08
#define	OLED_DISPLAY_LED_4	0x10
#define	OLED_DISPLAY_LED_5	0x20
#define	OLED_DISPLAY_LED_6	0x40
#define	OLED_DISPLAY_LED_7	0x80

#define	OLED_DISPLAY_LEDS_OFF	0x00
#define	OLED_DISPLAY_LEDS_ON	( \
  OLED_DISPLAY_LED_0 | OLED_DISPLAY_LED_1 | \
  OLED_DISPLAY_LED_2 | OLED_DISPLAY_LED_3 | \
  OLED_DISPLAY_LED_4 | OLED_DISPLAY_LED_5 | \
  OLED_DISPLAY_LED_6 | OLED_DISPLAY_LED_7   \
)

#define	OLED_DISPLAY_LINE_SIZE	0x10

/** @brief OLED Display Initialization. */
void EE_oled_display_init(void);

/** @brief OLED Display Clear display. */
void EE_oled_display_clear(void);

/** @brief OLED Display User Leds display. */
void EE_oled_display_leds(EE_UINT8 leds_mask);

/** @brief OLED Display User Message Line 1 display. */
void EE_oled_display_line1(const char *s);

/** @brief OLED Display User Message Line 2 display. */
void EE_oled_display_line2(const char *s);

#endif /* __USE_OLED_DISPLAY__ */

#endif /*__INCLUDE_STELLARIS_LM4F232XXXX_BOARD_H__ */
