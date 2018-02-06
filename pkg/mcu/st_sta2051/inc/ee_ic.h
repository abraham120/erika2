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
 * Author: 2004-2006 Paolo Gai
 * CVS: $Id: ee_ic.h,v 1.1 2006/10/19 09:51:44 pj Exp $
 */

#include "mcu/st_sta2051/inc/ee_mcuregs.h"

#ifndef __INCLUDE_ST_STA2051_IC_H__
#define __INCLUDE_ST_STA2051_IC_H__



/*
 * Interrupt sources (channels)
 */

/* Priorities */
#define IRQ_T0          0      /* Timer 0 */
#define IRQ_FLASH       1      /* Flash */
#define IRQ_RCCU        2      /* RCCU */
#define IRQ_RTC         3      /* Real Time Clock */
#define IRQ_WDG         4      /* WatchDog */
#define IRQ_WUIMU       5      /* WIU wake-up */
#define IRQ_USBHI       6      /* USB High priority */
#define IRQ_I2C0ERR     7      /* I2C Error */
#define IRQ_I2C1ERR     8      /* I2C error */
#define IRQ_UART0       9      /* UART0 */
#define IRQ_UART1      10      /* UART1 */
#define IRQ_UART2      11      /* UART2 */
#define IRQ_UART3      12      /* UART3 */
#define IRQ_SPI0       13      /* BSPI 0 */
#define IRQ_SPI1       14      /* BSPI 1 */
#define IRQ_I2C0       15      /* I2C 0 tx/rx */
#define IRQ_I2C1       16      /* I2C 1 tx/rx */
#define IRQ_CAN        17      /* CAN */
#define IRQ_ADC        18      /* ADC */
#define IRQ_T1         19      /* Timer 1 */
#define IRQ_T2         20      /* Timer 2 */
#define IRQ_T3         21      /* Timer 3 */
/* 22-24 are reserved */
#define IRQ_HDLC       25      /* HDLC */
#define IRQ_USBLO      26      /* USB Low priority */
#define IRQ_GPS        27      /* GPS Data ready */
/* 28  is reserved*/
#define IRQ_T0OV       29      /* Timer 0 overflow */
#define IRQ_T0OC1      30      /* Timer 0 output Compare 0 */
#define IRQ_T0OC2      31      /* Timer 0 output Compare 1 */
/* FIQ */
#define FIQ_T0          0      /* Timer 0 */
#define FIQ_WDG         1      /* Watchdog timer */



/* Masks */
#define IRQ_T0_MASK         (1<< 0)     /* Timer 0 */
#define IRQ_FLASH_MASK      (1<< 1)     /* Flash */
#define IRQ_RCCU_MASK       (1<< 2)     /* RCCU */
#define IRQ_RTC_MASK        (1<< 3)     /* Real Time Clock */
#define IRQ_WDG_MASK        (1<< 4)     /* WatchDog */
#define IRQ_WUIMU_MASK      (1<< 5)     /* WIU wake-up */
#define IRQ_USBHI_MASK      (1<< 6)     /* USB High priority */
#define IRQ_I2C0ERR_MASK    (1<< 7)     /* I2C Error */
#define IRQ_I2C1ERR_MASK    (1<< 8)     /* I2C error */
#define IRQ_UART0_MASK      (1<< 9)     /* UART0 */
#define IRQ_UART1_MASK      (1<<10)     /* UART1 */
#define IRQ_UART2_MASK      (1<<11)     /* UART2 */
#define IRQ_UART3_MASK      (1<<12)     /* UART3 */
#define IRQ_SPI0_MASK       (1<<13)     /* BSPI 0 */
#define IRQ_SPI1_MASK       (1<<14)     /* BSPI 1 */
#define IRQ_I2C0_MASK       (1<<15)     /* I2C 0 tx/rx */
#define IRQ_I2C1_MASK       (1<<16)     /* I2C 1 tx/rx */
#define IRQ_CAN_MASK        (1<<17)     /* CAN */
#define IRQ_ADC_MASK        (1<<18)     /* ADC */
#define IRQ_T1_MASK         (1<<19)     /* Timer 1 */
#define IRQ_T2_MASK         (1<<20)     /* Timer 2 */
#define IRQ_T3_MASK         (1<<21)     /* Timer 3 */
/* 22-24 are reserved */
#define IRQ_HDLC_MASK       (1<<25)     /* HDLC */
#define IRQ_USBLO_MASK      (1<<26)     /* USB Low priority */
#define IRQ_GPS_MASK        (1<<27)     /* GPS Data ready */
/* 28  is reserved*/
#define IRQ_T0OV_MASK       (1<<29)     /* Timer 0 overflow */
#define IRQ_T0OC1_MASK      (1<<30)     /* Timer 0 output Compare 0 */
#define IRQ_T0OC2_MASK      (1<<31)     /* Timer 0 output Compare 1 */
/* FIQ */
#define FIQ_T0_MASK         (1<< 0)     /* Timer 0 */
#define FIQ_WDG_MASK        (1<< 1)     /* Watchdog timer */



/* 
 * Types
 */

/* a number between 0 and 21 */
typedef EE_UINT32 EE_TYPEIRQ;

/* a bitmask from 0x0 to 0x001FFFFF */
typedef EE_UINT32 EE_TYPEIRQMASK;



/*
 * Functions
 */


/* FIR, IER and IPR setting */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_FIQ_enable_EIC(void)
{ *ICR |= 0x2; }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_FIQ_disable_EIC(void)
{ *ICR &= ~0x2; }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_enable_EIC(void)
{ *ICR |= 0x1; }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_disable_EIC(void)
{ *ICR &= ~0x1; }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_and_FIQ_enable_EIC(void)
{ *ICR |= 0x3; }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_and_FIQ_disable_EIC(void)
{ *ICR &= ~0x3; }

__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_FIQ_enable_channel(EE_TYPEIRQ ch)
{ *FIR |= (1 << ch); }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_FIQ_disable_channel(EE_TYPEIRQ ch)
{ *FIR &= ~(1 << ch); }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_FIQ_clear_channel(EE_TYPEIRQ ch)
{
  /* pending bits are 2,3 => shift of 4 instead of 1
     It is a read/clear register!
     THAT IS WRONG: *((volatile EE_ADDR)FIR) |= (8 << ch);
  */
  *FIR = (4 << ch);
}
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_enable_channel(EE_TYPEIRQ ch)
{ *IER |= (1 << ch); }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_disable_channel(EE_TYPEIRQ ch)
{ *IER &= ~(1 << ch); }
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_clear_channel(EE_TYPEIRQ ch)
{
  *IPR = (1 << ch); /* writing 1 force to 0 */
}

__INLINE__ void __ALWAYS_INLINE__ 
EE_sta2051_IRQ_set_handler(EE_TYPEIRQ ch, 
			   EE_ADDR ad,
			   const int priority)
{
    /*
     * NOTE: SIR contains only the 16 less significant bits of the
     * handler address. The bitwise and between "ad" and
     * 0x0000FFFF is useless because you have to do a shift...
     */
    /* write address in SIR[31:16] */
    SIR[ch] = ((EE_UINT32)ad << 16) | priority;
}



/* EIC initial settings */
__INLINE__ void __ALWAYS_INLINE__ EE_sta2051_IRQ_init(void) 
{
  *ICR = 0;          /* IRQ and FIQ disabled */
  *IVR = 0;          /* IVR value is 0, we suppose all interruptv
			handlers allocated first */
  *CIPR = 0;         /* current priority = 0 */
  *IER = 0;          /* all interrupts disabled */
  *IPR = 0xffffffff; /* no pending interrupts */
  *FIR = 0xC;        /* all FIQ disabled, no FIQ pending interrupts */
}

#endif
