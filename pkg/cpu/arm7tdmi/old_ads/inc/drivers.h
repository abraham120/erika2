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
 * Author 2001-2002 Alessandro Colantonio
 * CVS: $Id: drivers.h,v 1.2 2006/04/08 21:05:47 pj Exp $
 */

#ifndef __INCLUDE_ARM7ADS_DRIVERS_H__
#define __INCLUDE_ARM7ADS_DRIVERS_H__

#include "eecfg.h"
#include "erikahal.h"



/*
 * Interrupts handling
 */

#define IRQ_EXT0_MASK (1<<0)	/* Ext 0 */
//#define IRQ_EXT1_MASK (1<<1)	/* Ext 1 */
//#define IRQ_EXT2_MASK (1<<2)	/* Ext 2 */
//#define IRQ_EXT3_MASK (1<<3)	/* Ext 3 */
//#define IRQ_UART0TX_MASK (1<<4)	/* UART0 Tx */
//#define IRQ_UART0RX_MASK (1<<5)	/* UART0 Rx & error*/
//#define IRQ_UART1TX_MASK (1<<6)	/* UART1 Tx */
//#define IRQ_UART1RX_MASK (1<<7)	/* UART1 Rx & error*/
//#define IRQ_GDMA0_MASK (1<<8)	/* GDMA ch. 0 */
//#define IRQ_GDMA1_MASK (1<<9)	/* GDMA ch. 1 */
#define IRQ_TIMER0_MASK (1<<10)	/* Timer 0 */
#define IRQ_TIMER1_MASK (1<<11)	/* Timer 1 */
//#define IRQ_HDLCATX_MASK (1<<12) /* HDLC A Tx */
//#define IRQ_HDLCARX_MASK (1<<13) /* HDLC A Rx */
//#define IRQ_HDLCBTX_MASK (1<<14) /* HDLC B Tx */
//#define IRQ_HDLCBRX_MASK (1<<15) /* HDLC B Rx */
//#define IRQ_ETHBDMATX_MASK (1<<16) /* Ethernet BDMA Tx */
//#define IRQ_ETHBDMARX_MASK (1<<17) /* Ethernet BDMA Rx */
//#define IRQ_ETHMACTX_MASK (1<<18) /* Ethernet MAC Tx */
//#define IRQ_ETHMACRX_MASK (1<<19) /* Ethernet MAC Rx */
//#define IRQ_I2C_MASK (1<<20)	/* I2C-bus */

#define IRQ_GLOBAL_MASK (1<<21)

__INLINE__ void __ALWAYS_INLINE__ EE_enable_external_IRQ(EE_TYPEIRQ);
__INLINE__ void __ALWAYS_INLINE__ EE_disable_external_IRQ(EE_TYPEIRQ);
__INLINE__ void __ALWAYS_INLINE__ EE_accept_external_IRQ(EE_TYPEIRQ);
__INLINE__ void __ALWAYS_INLINE__ EE_clear_pending_IRQ(void);



/*
 * Memory mapped I/O ports
 */

/* base I/O address */
#define SYSCFG    0x03FF0000	

/* Leds and LCD */
#define IOPMOD ((volatile EE_ADDR)(SYSCFG + 0x5000)) /* I/O port mode */
#define IOPCON ((volatile EE_ADDR)(SYSCFG + 0x5004)) /* I/O port control */
#define IOPDATA ((volatile EE_ADDR)(SYSCFG + 0x5008)) /* input port data */

/* Interrupt controller */
#define INTMOD ((volatile EE_ADDR)(SYSCFG + 0x4000)) /* IRQ mode */
#define INTPND ((volatile EE_ADDR)(SYSCFG + 0x4004)) /* IRQ pending req. */
#define INTMSK ((volatile EE_ADDR)(SYSCFG + 0x4008)) /* IRQ mask */

/* Timers */
#define TMOD ((volatile EE_ADDR)(SYSCFG + 0x6000))	/* timer mode */
#define TDATA0 ((volatile EE_ADDR)(SYSCFG + 0x6004)) /* timer 0 data */
#define TDATA1 ((volatile EE_ADDR)(SYSCFG + 0x6008)) /* timer 1 data */
#define TCNT0 ((volatile EE_ADDR)(SYSCFG + 0x600C)) /* timer 0 count */
#define TCNT1 ((volatile EE_ADDR)(SYSCFG + 0x6010)) /* timer 1 count */



/*
 * External IRQ #0 controlling
 */
#ifdef __EXT0_USED__

extern EE_ADDR EE_ext0_handler_addr;

#define IO_ENABLE_EXT0 (1<<4)	/* bit 4 of IOPMOD = 1 ==> enable */
#define IO_ACTIVE_HIGH_EXT0 (1<<3) /* bit 3 of IOPMOD = 1 ==> active high */
#define IO_RISING_EDGE_EXT0 (1<<0) /* bit 1+0 of IOPMOD = 01 ==>
				    * rising edge detection */

/* Initialize the EXT0 interrupt source (button)  */
__INLINE__ void __ALWAYS_INLINE__ EE_ext0_init(void);

#endif /* __EXT0_USED__ */



/*
 * LEDs controlling
 */

#ifdef __LEDS_USED__

/* On Evaluator7T, the LEDs are connected through IO Port 
 * LED1 is Green, LED2 is Red, LED3 is Yellow, LED4 is Green */

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void);

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_on(void);
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_on(void);
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_on(void);
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_on(void);

__INLINE__ void __ALWAYS_INLINE__ EE_led_4_off(void);
__INLINE__ void __ALWAYS_INLINE__ EE_led_3_off(void);
__INLINE__ void __ALWAYS_INLINE__ EE_led_2_off(void);
__INLINE__ void __ALWAYS_INLINE__ EE_led_1_off(void);

#endif /* __LEDS_USED__ */



/*
 * LCD display controlling
 */

#ifdef __LCD_USED__

/* On Evaluator7T, the LEDs are connected through IO Port */

/* the bits taken up by the display in IODATA register */
#define LCD_MASK (0x1fc00)

/* define segments in terms of I/O lines */
#define LCD_SEG_A (1<<10)
#define LCD_SEG_B (1<<11)
#define LCD_SEG_C (1<<12)
#define LCD_SEG_D (1<<13)
#define LCD_SEG_E (1<<14)
#define LCD_SEG_F (1<<16)
#define LCD_SEG_G (1<<15)

#define	LCD_DISP_0 (LCD_SEG_A|LCD_SEG_B|LCD_SEG_C|LCD_SEG_D|LCD_SEG_E|LCD_SEG_F)
#define	LCD_DISP_1 (LCD_SEG_B|LCD_SEG_C)
#define	LCD_DISP_2 (LCD_SEG_A|LCD_SEG_B|LCD_SEG_D|LCD_SEG_E|LCD_SEG_G)
#define	LCD_DISP_3 (LCD_SEG_A|LCD_SEG_B|LCD_SEG_C|LCD_SEG_D|LCD_SEG_G)
#define	LCD_DISP_4 (LCD_SEG_B|LCD_SEG_C|LCD_SEG_F|LCD_SEG_G)
#define	LCD_DISP_5 (LCD_SEG_A|LCD_SEG_C|LCD_SEG_D|LCD_SEG_F|LCD_SEG_G)
#define	LCD_DISP_6 (LCD_SEG_A|LCD_SEG_C|LCD_SEG_D|LCD_SEG_E|LCD_SEG_F|LCD_SEG_G)
#define	LCD_DISP_7 (LCD_SEG_A|LCD_SEG_B|LCD_SEG_C)
#define	LCD_DISP_8 (LCD_SEG_A|LCD_SEG_B|LCD_SEG_C|LCD_SEG_D|LCD_SEG_E|LCD_SEG_F|LCD_SEG_G)
#define	LCD_DISP_9 (LCD_SEG_A|LCD_SEG_B|LCD_SEG_C|LCD_SEG_D|LCD_SEG_F|LCD_SEG_G)

#define	LCD_DISP_A (LCD_SEG_A|LCD_SEG_B|LCD_SEG_C|LCD_SEG_E|LCD_SEG_F|LCD_SEG_G)
#define	LCD_DISP_B (LCD_SEG_C|LCD_SEG_D|LCD_SEG_E|LCD_SEG_F|LCD_SEG_G)
#define	LCD_DISP_C (LCD_SEG_A|LCD_SEG_D|LCD_SEG_E|LCD_SEG_F)
#define	LCD_DISP_D (LCD_SEG_B|LCD_SEG_C|LCD_SEG_D|LCD_SEG_E|LCD_SEG_G)
#define	LCD_DISP_E (LCD_SEG_A|LCD_SEG_D|LCD_SEG_E|LCD_SEG_F|LCD_SEG_G)
#define	LCD_DISP_F (LCD_SEG_A|LCD_SEG_E|LCD_SEG_F|LCD_SEG_G)

/* Association number <-> segments */
extern EE_UREG EE_LCD_numeric_display[16];

/* Initialize the 7 segment display.  */
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_init(void);

/* Display LCD number. NOTE: Do not check whether number is in the
 * range of 0x0 and 0xf (if so then it cannot set the segment display
 * correctly!) */
__INLINE__ void __ALWAYS_INLINE__ EE_LCD_display(EE_UREG num);

#endif /* __LCD_USED__ */



/*
 * Timers controlling
 */

#ifdef __TIMER_0_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

extern EE_ADDR EE_timer0_handler_addr;

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_start(void);
__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_stop(void);
__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_set(EE_UREG count_down);
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_0_get(void);
#endif /* __TIMER_0_USED__ */


#ifdef __TIMER_1_USED__

#ifndef __TIMER_USED__
#define __TIMER_USED__
#endif

extern EE_ADDR EE_timer1_handler_addr;

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_start(void);
__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_stop(void);
__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_set(EE_UREG count_down);
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_timer_1_get(void);
#endif /* __TIMER_1_USED__ */


#ifdef __TIMER_USED__
__INLINE__ void __ALWAYS_INLINE__ EE_timer_init(void);
#endif /* __TIMER_USED__ */



/*
 * DIP switch controlling
 */

#ifdef __DIP_SWITCH_USED__

#define DIP_SWITCH_MASK 0xf

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_dip_switch_get(void);

#endif /* __DIP_SWITCH_USED__ */

#endif /* __INCLUDE_ARM7ADS_DRIVERS_H__ */
