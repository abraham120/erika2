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
 * Support for Infineon Application Kit TC2X5 board.
 * Author: 2014, Christoph Kreuzberger
 *
 */

#ifndef INCLUDE_EE_APPKIT_TC2X5_EE_BOARD_H__
#define INCLUDE_EE_APPKIT_TC2X5_EE_BOARD_H__

/* Appkit 2x5 default clock frequency (20MHz) */
#define EE_APPKIT_2X5_FOSC    	20000000U
/* Interface Board Oscillator Frequency Define */
#define EE_TC2YX_BOARD_FOSC     EE_APPKIT_2X5_FOSC
/* Interface Board Oscillator Frequency Define */
#define EE_TC27X_BOARD_FOSC     EE_APPKIT_2X5_FOSC

#ifdef EE_USE_DISPLAY
#include "graph.h"
#endif

#ifdef EE_USE_LEDS
#include "ee_led.h"
#endif

#ifdef EE_USE_BUTTONS
#include "ee_button.h"
#endif


#endif /* INCLUDE_EE_APPKIT_TC2X5_EE_BOARD_H__ */
