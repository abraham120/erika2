/** @file	ee_atmel_stk600_led.h
 *
 *  @brief	Erika Enterprise - LED Driver - Atmel STK600 Header File.
 *
 *  <!--
 *    ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 *    Copyright (C) 2002-2013  Evidence Srl
 *
 *    This file is part of ERIKA Enterprise.
 *
 *    ERIKA Enterprise is free software; you can redistribute it
 *    and/or modify it under the terms of the GNU General Public License
 *    version 2 as published by the Free Software Foundation, 
 *    (with a special exception described below).
 *
 *    Linking this code statically or dynamically with other modules is
 *    making a combined work based on this code.  Thus, the terms and
 *    conditions of the GNU General Public License cover the whole
 *    combination.
 *
 *    As a special exception, the copyright holders of this library give you
 *    permission to link this code with independent modules to produce an
 *    executable, regardless of the license terms of these independent
 *    modules, and to copy and distribute the resulting executable under
 *    terms of your choice, provided that you also meet, for each linked
 *    independent module, the terms and conditions of the license of that
 *    module.  An independent module is a module which is not derived from
 *    or based on this library.  If you modify this code, you may extend
 *    this exception to your version of the code, but you are not
 *    obligated to do so.  If you do not wish to do so, delete this
 *    exception statement from your version.
 *
 *    ERIKA Enterprise is distributed in the hope that it will be
 *    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License version 2 for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    version 2 along with ERIKA Enterprise; if not, write to the
 *    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *    Boston, MA 02110-1301 USA.
 *  -->
 *
 *  The LED driver provides General Porpose Times(s) services.
 *
 *  The LED driver is part of the microcontroller abstraction layer (MCAL). It
 *  initializes and controls the internal General Purpose Timer(s) (LED) of the
 *  microcontroller.
 *
 *  The LED driver provides services and configuration parameters for
 *  - Starting and stopping hardware timers
 *  - Getting timer values
 *  - Controlling time triggered interrupt notifications
 *
 *  The tick duration of a timer channel depends on channel specific settings
 *  (part of LED driver) as well as on system clock and settings of the clock
 *  tree controlled by the MCU module. The tick duration is not limited by this
 *  specification.
 *
 *  Not all hardware timers must be controlled by the LED module. Some timers
 *  may be controlled by Operating System (OS) or Other Drivers directly.
 *
 *  The number of timer channels controlled by the LED driver depends on
 *  hardware, implementation and system configuration.
 *
 *  The LED driver only generates time bases, and does not serve as an event
 *  counter. This functionality is provided by another driver module
 *  (ICU driver).
 * 
 *  @author	Riccardo Schiavi
 *  @author	Giuseppe Serano
 *  @version	0.1
 */

#ifndef	__INCLUDE_ATMEL_STK600_LED_H__
#define	__INCLUDE_ATMEL_STK600_LED_H__

/* 
 * LED Definition
 */

/* ATXMEGA MCUs */
#ifdef	__ATXMEGA__

/* PORT A */
#ifdef	__LED_PORT_A__
#define	EE_LED_0	EE_GPIO_CHANNEL_A_0	/**< PORT B - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_A_1	/**< PORT B - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_A_2	/**< PORT B - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_A_3	/**< PORT B - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_A_4	/**< PORT B - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_A_5	/**< PORT B - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_A_6	/**< PORT B - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_A_7	/**< PORT B - PIN 7 */
#endif

/* PORT B */
#ifdef	__LED_PORT_B__
#define	EE_LED_0	EE_GPIO_CHANNEL_B_0	/**< PORT B - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_B_1	/**< PORT B - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_B_2	/**< PORT B - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_B_3	/**< PORT B - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_B_4	/**< PORT B - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_B_5	/**< PORT B - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_B_6	/**< PORT B - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_B_7	/**< PORT B - PIN 7 */
#endif

/* PORT C */
#ifdef	__LED_PORT_C__
#define	EE_LED_0	EE_GPIO_CHANNEL_C_0	/**< PORT C - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_C_1	/**< PORT C - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_C_2	/**< PORT C - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_C_3	/**< PORT C - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_C_4	/**< PORT C - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_C_5	/**< PORT C - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_C_6	/**< PORT C - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_C_7	/**< PORT C - PIN 7 */
#endif

/* PORT D */
#ifdef	__LED_PORT_D__
#define	EE_LED_0	EE_GPIO_CHANNEL_D_0	/**< PORT D - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_D_1	/**< PORT D - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_D_2	/**< PORT D - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_D_3	/**< PORT D - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_D_4	/**< PORT D - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_D_5	/**< PORT D - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_D_6	/**< PORT D - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_D_7	/**< PORT D - PIN 7 */
#endif

/* PORT E */
#ifdef	__LED_PORT_E__
#define	EE_LED_0	EE_GPIO_CHANNEL_E_0	/**< PORT E - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_E_1	/**< PORT E - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_E_2	/**< PORT E - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_E_3	/**< PORT E - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_E_4	/**< PORT E - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_E_5	/**< PORT E - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_E_6	/**< PORT E - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_E_7	/**< PORT E - PIN 7 */
#endif

/* PORT F */
#ifdef	__LED_PORT_F__
#define	EE_LED_0	EE_GPIO_CHANNEL_F_0	/**< PORT F - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_F_1	/**< PORT F - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_F_2	/**< PORT F - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_F_3	/**< PORT F - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_F_4	/**< PORT F - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_F_5	/**< PORT F - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_F_6	/**< PORT F - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_F_7	/**< PORT F - PIN 7 */
#endif

/* PORT G */
#ifdef	__LED_PORT_G__
#define	EE_LED_0	EE_GPIO_CHANNEL_G_0	/**< PORT G - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_G_1	/**< PORT G - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_G_2	/**< PORT G - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_G_3	/**< PORT G - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_G_4	/**< PORT G - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_G_5	/**< PORT G - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_G_6	/**< PORT G - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_G_7	/**< PORT G - PIN 7 */
#endif

/* PORT H */
#ifdef	__LED_PORT_H__
#define	EE_LED_0	EE_GPIO_CHANNEL_H_0	/**< PORT H - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_H_1	/**< PORT H - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_H_2	/**< PORT H - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_H_3	/**< PORT H - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_H_4	/**< PORT H - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_H_5	/**< PORT H - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_H_6	/**< PORT H - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_H_7	/**< PORT H - PIN 7 */
#endif

/* PORT J */
#ifdef	__LED_PORT_J__
#define	EE_LED_0	EE_GPIO_CHANNEL_J_0	/**< PORT J - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_J_1	/**< PORT J - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_J_2	/**< PORT J - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_J_3	/**< PORT J - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_J_4	/**< PORT J - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_J_5	/**< PORT J - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_J_6	/**< PORT J - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_J_7	/**< PORT J - PIN 7 */
#endif

/* PORT K */
#ifdef	__LED_PORT_K__
#define	EE_LED_0	EE_GPIO_CHANNEL_K_0	/**< PORT K - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_K_1	/**< PORT K - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_K_2	/**< PORT K - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_K_3	/**< PORT K - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_K_4	/**< PORT K - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_K_5	/**< PORT K - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_K_6	/**< PORT K - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_K_7	/**< PORT K - PIN 7 */
#endif

/* PORT L */
#ifdef	__LED_PORT_L__
#define	EE_LED_0	EE_GPIO_CHANNEL_L_0	/**< PORT L - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_L_1	/**< PORT L - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_L_2	/**< PORT L - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_L_3	/**< PORT L - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_L_4	/**< PORT L - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_L_5	/**< PORT L - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_L_6	/**< PORT L - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_L_7	/**< PORT L - PIN 7 */
#endif

/* PORT M */
#ifdef	__LED_PORT_M__
#define	EE_LED_0	EE_GPIO_CHANNEL_M_0	/**< PORT M - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_M_1	/**< PORT M - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_M_2	/**< PORT M - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_M_3	/**< PORT M - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_M_4	/**< PORT M - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_M_5	/**< PORT M - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_M_6	/**< PORT M - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_M_7	/**< PORT M - PIN 7 */
#endif

/* PORT N */
#ifdef	__LED_PORT_N__
#define	EE_LED_0	EE_GPIO_CHANNEL_N_0	/**< PORT N - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_N_1	/**< PORT N - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_N_2	/**< PORT N - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_N_3	/**< PORT N - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_N_4	/**< PORT N - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_N_5	/**< PORT N - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_N_6	/**< PORT N - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_N_7	/**< PORT N - PIN 7 */
#endif

/* PORT P */
#ifdef	__LED_PORT_P__
#define	EE_LED_0	EE_GPIO_CHANNEL_P_0	/**< PORT P - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_P_1	/**< PORT P - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_P_2	/**< PORT P - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_P_3	/**< PORT P - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_P_4	/**< PORT P - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_P_5	/**< PORT P - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_P_6	/**< PORT P - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_P_7	/**< PORT P - PIN 7 */
#endif

/* PORT Q */
#ifdef	__LED_PORT_Q__
#define	EE_LED_0	EE_GPIO_CHANNEL_Q_0	/**< PORT Q - PIN 0 */
#define	EE_LED_1	EE_GPIO_CHANNEL_Q_1	/**< PORT Q - PIN 1 */
#define	EE_LED_2	EE_GPIO_CHANNEL_Q_2	/**< PORT Q - PIN 2 */
#define	EE_LED_3	EE_GPIO_CHANNEL_Q_3	/**< PORT Q - PIN 3 */
#define	EE_LED_4	EE_GPIO_CHANNEL_Q_4	/**< PORT Q - PIN 4 */
#define	EE_LED_5	EE_GPIO_CHANNEL_Q_5	/**< PORT Q - PIN 5 */
#define	EE_LED_6	EE_GPIO_CHANNEL_Q_6	/**< PORT Q - PIN 6 */
#define	EE_LED_7	EE_GPIO_CHANNEL_Q_7	/**< PORT Q - PIN 7 */
#endif

#include "board/common/inc/ee_board_common_led.h"

#endif	/* __ATXMEGA__ */

#endif	/* __INCLUDE_ATMEL_STK600_LED_H__ */

