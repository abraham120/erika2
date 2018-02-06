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

/** 
* \file ee_timer.h
* \brief Timer driver, Erika HCS12 mcu.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/

#ifdef __USE_TIMER__
 
#ifndef __INCLUDE_MC9S12_TIMER_H__
#define __INCLUDE_MC9S12_TIMER_H__

/* Include a file with the registers of the s12 micro-controller */ 
#include "mcu/hs12xs/inc/ee_mcuregs.h"

#define EE_TIMER_ISR_ON  1
#define EE_TIMER_ISR_OFF 0

#define EE_TIMER_PRESCALE_FACTOR_128 	7
#define EE_TIMER_PRESCALE_FACTOR_64 	6
#define EE_TIMER_PRESCALE_FACTOR_32 	5
#define EE_TIMER_PRESCALE_FACTOR_16 	4
#define EE_TIMER_PRESCALE_FACTOR_8 		3
#define EE_TIMER_PRESCALE_FACTOR_4 		2
#define EE_TIMER_PRESCALE_FACTOR_2 		1
#define EE_TIMER_PRESCALE_FACTOR_1 		0

#define EE_TIMER_0 0
#define EE_TIMER_1 1
#define EE_TIMER_2 2
#define EE_TIMER_3 3
#define EE_TIMER_4 4
#define EE_TIMER_5 5

#define EE_S12_TIMER_SET_SYSCTRL_REG1(var8) TSCR1=var8
#define EE_S12_TIMER_GET_SYSCTRL_REG1()    TSCR1

#define EE_S12_TIMER_SET_SYSCTRL_REG2(var8) TSCR2=var8
#define EE_S12_TIMER_GET_SYSCTRL_REG2()    TSCR2

#define EE_S12_TIMER_SET_ISR_FLAG1(var8)    TFLG1=var8
#define EE_S12_TIMER_GET_ISR_FLAG1()       TFLG1

#define EE_S12_TIMER_SET_ISR_FLAG2(var8)    TFLG2=var8
#define EE_S12_TIMER_GET_ISR_FLAG2()       TFLG2

#define EE_S12_TIMER_SET_CNT_REG(var8)      TCNT=var8
#define EE_S12_TIMER_GET_CNT_REG()         TCNT

#define EE_S12_TIMER_SET_ICOC_SEL(var8)     TIOS=var8
#define EE_S12_TIMER_GET_ICOC_SEL()        TIOS

#define EE_S12_TIMER_SET_CTRL_REG1(var8)    TCTL1=var8
#define EE_S12_TIMER_GET_CTRL_REG1()       TCTL1

#define EE_S12_TIMER_SET_CTRL_REG2(var8)    TCTL2=var8
#define EE_S12_TIMER_GET_CTRL_REG2()       TCTL2

#define EE_S12_TIMER_SET_CTRL_REG3(var8)    TCTL3=var8
#define EE_S12_TIMER_GET_CTRL_REG3()       TCTL3

#define EE_S12_TIMER_SET_CTRL_REG4(var8)    TCTL4=var8
#define EE_S12_TIMER_GET_CTRL_REG4()       TCTL4

#define EE_S12_TIMER_SET_OC_CTRL(var16)     *((EE_UINT16*)(&TCTL1))=var16
#define EE_S12_TIMER_GET_OC_CTRL()         *((EE_UINT16*)(&TCTL1))

#define EE_S12_TIMER_SET_IC_CTRL(var16)     *((EE_UINT16*)(&TCTL3))=var16
#define EE_S12_TIMER_GET_IC_CTRL()         *((EE_UINT16*)(&TCTL3))

#define EE_S12_TIMER_SET_IE_REG(var8)       TIE=var8
#define EE_S12_TIMER_GET_IE_REG()          TIE

#define EE_S12_TIMER_SET_OC_DIS_REG(var8)   OCPD=var8
#define EE_S12_TIMER_GET_OC_DIS_REG()      OCPD

#define EE_S12_TIMER_SET_TC0_REG(var8)      TC0=var8
#define EE_S12_TIMER_GET_TC0_REG()         TC0

#define EE_S12_TIMER_SET_TC1_REG(var8)      TC1=var8
#define EE_S12_TIMER_GET_TC1_REG()         TC1

#define EE_S12_TIMER_SET_TC2_REG(var8)      TC2=var8
#define EE_S12_TIMER_GET_TC2_REG()         TC2

#define EE_S12_TIMER_SET_TC3_REG(var8)      TC3=var8
#define EE_S12_TIMER_GET_TC3_REG()         TC3

#define EE_S12_TIMER_SET_TC4_REG(var8)      TC4=var8
#define EE_S12_TIMER_GET_TC4_REG()         TC4

#define EE_S12_TIMER_SET_TC5_REG(var8)      TC5=var8
#define EE_S12_TIMER_GET_TC5_REG()         TC5

#define EE_S12_TIMER_SET_PERIOD(id, per)  *(&(EE_S12_TIMER_GET_TC0_REG()) + id) = per
#define EE_S12_TIMER_GET_PERIOD(id)       *(&(EE_S12_TIMER_GET_TC0_REG()) + id)
#define EE_S12_TIMER_SET_PRESCALER(ps)    EE_S12_TIMER_SET_SYSCTRL_REG2(ps)

#if defined (__MC9S12G128__) || defined (__MC9S12XS128__)

#define EE_TIMER_6 6
#define EE_TIMER_7 7
#define EE_TIMER_ID_MAX EE_TIMER_7

#define EE_S12_TIMER_SET_TC6_REG(var8)      TC6=var8
#define EE_S12_TIMER_GET_TC6_REG()         TC6

#define EE_S12_TIMER_SET_TC7_REG(var8)      TC7=var8
#define EE_S12_TIMER_GET_TC7_REG()         TC7

#define EE_S12_TIMER_SET_OC_MASK_REG(var8)  OC7M=var8
#define EE_S12_TIMER_GET_OC_MASK_REG()     OC7M

#define EE_S12_TIMER_SET_OC_DATA_REG(var8)  OC7D=var8
#define EE_S12_TIMER_GET_OC_DATA_REG()     OC7D

#elif defined (__MC9S12GN16__) || defined (__MC9S12GN32__) || defined (__MC9S12G48__) || defined (__MC9S12GN48__)

#define EE_TIMER_ID_MAX EE_TIMER_5

#define EE_S12_TIMER_SET_OC_MASK_REG(var8)  do{} while(0)
#define EE_S12_TIMER_GET_OC_MASK_REG()     0

#define EE_S12_TIMER_SET_OC_DATA_REG(var8)  do{} while(0)
#define EE_S12_TIMER_GET_OC_DATA_REG()     0

#endif

#if defined (__MC9S12G96__) || defined (__MC9S12G128__) || defined (__MC9S12GN16__)\
            || defined (__MC9S12GN32__) || defined (__MC9S12G48__) || defined (__MC9S12GN48__)

#define EE_S12_TIMER_SET_PRIORITY(prio) do{} while(0)

#endif /* __MC9S12G96__ || __MC9S12G128__ || __MC9S12GN16__ || __MC9S12GN32__ */

#if defined (__MC9S12XS64__) || defined (__MC9S12XS128__) || defined (__MC9S12XS256__)

#define EE_TIMER_ISR_ON_PRIO1  1
#define EE_TIMER_ISR_ON_PRIO2  2
#define EE_TIMER_ISR_ON_PRIO3  3
#define EE_TIMER_ISR_ON_PRIO4  4
#define EE_TIMER_ISR_ON_PRIO5  5
#define EE_TIMER_ISR_ON_PRIO6  6
#define EE_TIMER_ISR_ON_PRIO7  7

/* Set base address and set ISR priority */
#define EE_S12_TIMER_SET_PRIORITY(prio) do {\
                                        INT_CFADDR = 0xE0;\
                                        INT_CFDATA7 = prio; } while(0)

#endif /* __MC9S12XS64__ || __MC9S12XS128__ || __MC9S12XS256__ */

/**
 * Periods used for timer channels initialization.
*/
extern volatile unsigned int ee_timer_periods[];
#define EE_S12_TIMER_GET_INIT_PERIOD(tid)         ee_timer_periods[tid]
#define EE_S12_TIMER_SET_INIT_PERIOD(tid, var16)  ee_timer_periods[tid] = var16

/**
 * \brief				This function is used to initialize a timer.
                        Requires: EE_set_peripheral_frequency_mhz(mhz) should already be called to
                        save the peripheral frequency. 
 * \param tim_id		Number of the Timer to be used.
 * \param period_us	Period in micro-seconds.
 * \param isr_mode		Flag to select the operating mode, Polling or ISR.
                        Use EE_TIMER_ISR_ON, EE_TIMER_ISR_OFF for S12G.
                        For S12XS this parameter can be used to set the ISR priority
                        with EE_TIMER_ISR_ON_PRIOx (see the code for further info).
 * \return				True if the timer has been properly initialized.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_timer_init_us(EE_UINT16 tim_id, EE_UINT32 period_us, EE_UINT8 isr_mode) {
	
	EE_UINT32 max_period, ticks, prd;
	EE_UINT8 psc;
	
	if( EE_get_peripheral_frequency_mhz()==0 )
		return -1; /* Please set peripheral frequency before timer initialization... */
	
	if(tim_id > EE_TIMER_ID_MAX)
		return -2; /* Timer id wrong or timer not supported */
	
	/* Reset timer module */
	EE_S12_TIMER_SET_SYSCTRL_REG1(0);	/* turn off Timer module */
	EE_S12_TIMER_SET_SYSCTRL_REG2(0);	/* clear Timer sys_reg 2 */
	EE_S12_TIMER_SET_CNT_REG(0);		/* clear Timer counter */
	EE_S12_TIMER_SET_ISR_FLAG1(0);		/* clear isr flags */
	EE_S12_TIMER_SET_OC_MASK_REG(0);	/* Output compare mask cleared */
	EE_S12_TIMER_SET_OC_DATA_REG(0);	/* Output compare data cleared */
	
	EE_S12_TIMER_SET_ICOC_SEL( EE_S12_TIMER_GET_ICOC_SEL() | (0x01 << tim_id) );			/* output compare mode */
	EE_S12_TIMER_SET_OC_CTRL( EE_S12_TIMER_GET_OC_CTRL() & (~(0x0003 << (tim_id << 1))) );	/* do not use timer pins */
	EE_S12_TIMER_SET_IC_CTRL( EE_S12_TIMER_GET_IC_CTRL() & (~(0x0003 << (tim_id << 1))) );	/* do not use input capture */
	EE_S12_TIMER_SET_OC_DIS_REG( EE_S12_TIMER_GET_OC_DIS_REG() | (0x01 << tim_id) );		/* disable output compare pin */
	
	/* Timer ID dependent feature */
	max_period  = 0xffff;
	ticks = period_us * EE_get_peripheral_frequency_mhz();
	if (ticks < max_period) {
		prd = ticks;
		psc = EE_TIMER_PRESCALE_FACTOR_1;
	} else if (ticks / 8 < max_period) {
		prd = ticks / 8;
		psc = EE_TIMER_PRESCALE_FACTOR_8;
	} else if (ticks / 64 < max_period) {
		prd = ticks / 64;
		psc = EE_TIMER_PRESCALE_FACTOR_64;
	} else if (ticks / 128 < max_period) {
		prd = ticks / 128;
		psc = EE_TIMER_PRESCALE_FACTOR_128;
	} else {
		/* Please, the desired period is too big! */
		return -2;
	}

	EE_S12_TIMER_SET_PERIOD( tim_id, (EE_UINT16)prd );  /* Write the period in the register */
	EE_S12_TIMER_SET_PRESCALER(psc);                    /* Prescaler should be the same for all the timers */
	EE_S12_TIMER_SET_INIT_PERIOD( tim_id, EE_S12_TIMER_GET_PERIOD(tim_id) );     /* Save the period in the array */

	if( isr_mode ) {
		EE_S12_TIMER_SET_IE_REG( EE_S12_TIMER_GET_IE_REG() | (0x01 << tim_id) );	/* enable interrupt */
		EE_S12_TIMER_SET_PRIORITY(isr_mode);
	}
	else {
		EE_S12_TIMER_SET_IE_REG( EE_S12_TIMER_GET_IE_REG() & (~(0x01 << tim_id)) );	/* disable interrupt */
	}
	
	return 1; /* all is ok! */
}

/**
 * \brief				This function is used to initialize a timer.
                        Requires: EE_set_peripheral_frequency_mhz(mhz) should already be called to
                        save the peripheral frequency. 
 * \param tim_id		Number of the Timer to be used.
 * \param period_us	Period in milli-seconds.
 * \param isr_mode		Flag to select the operating mode, Polling or ISR.
                        Use EE_TIMER_ISR_ON, EE_TIMER_ISR_OFF for S12G.
                        For S12XS this parameter can be used to set the ISR priority
                        with EE_TIMER_ISR_ON_PRIOx (see the code for further info).
 * \return				True if the timer has been properly initialized.
*/
__INLINE__ int __ALWAYS_INLINE__ EE_timer_init_ms(EE_UINT16 tim_id, EE_UINT16 period_ms, EE_UINT8 isr_mode) {
	return EE_timer_init_us(tim_id, (EE_UINT32)period_ms*1000ul,isr_mode);
}

/**
 * \brief				This function is used to start the Timer peripheral.
                        Requires: Timer should already be initialized.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_start( void ) {
	EE_S12_TIMER_SET_SYSCTRL_REG1(0x80);	/* turn on Timer module */
}

/**
 * \brief				This function is used to stop the Timer peripheral.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_stop( void ) {
	EE_S12_TIMER_SET_SYSCTRL_REG1(0);	/* turn off Timer module */
}

/**
 * \brief				This function is used to reset the Timer peripheral.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_reset( void ) {
	EE_S12_TIMER_SET_CNT_REG(0);		/* clear Timer counter */
}

/**
 * \brief				This function is used to clear the Timer Interrupt flag.
 * \param tim_id		Number of the timer to be used.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_clear_ISRflag( EE_UINT16 tim_id ) {
	EE_S12_TIMER_SET_ISR_FLAG1(0x01 << tim_id);		/* clear isr flag */
}

/**
 * \brief				This function is used to read the Timer counter.
 * \return				Timer counter value.
*/
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_timer_get_counter( void ) {
	return EE_S12_TIMER_GET_CNT_REG();
}

/**
 * \brief				This function is used to enable Timer IRQ.
 * \param tim_id		Number of the timer to be used.
 * \param isr_mode		Interrupt priority for S12XS, EE_TIMER_ISR_ON for S12G. 
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_enable_ISR( EE_UINT16 tim_id, EE_UINT8 isr_mode ) {
	EE_S12_TIMER_SET_IE_REG( EE_S12_TIMER_GET_IE_REG() | (0x01 << tim_id) );	/* enable interrupt */
	EE_S12_TIMER_SET_PRIORITY(isr_mode);
}

/**
 * \brief				This function is used to disable Timer IRQ.
 * \param tim_id		Number of the timer to be used.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_disable_ISR( EE_UINT16 tim_id ) {
	EE_S12_TIMER_SET_IE_REG( EE_S12_TIMER_GET_IE_REG() & (~(0x01 << tim_id)) );	/* disable interrupt */
}

/**
 * \brief				This function is used to enable Timer counter reset.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_counter_reset_enable( void ) {
	EE_S12_TIMER_SET_SYSCTRL_REG2( EE_S12_TIMER_GET_SYSCTRL_REG2() | 0x08 );
}

/**
 * \brief				This function is used to disable Timer counter reset.
 * \return				nothing.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_timer_counter_reset_disable( void ) {
	EE_S12_TIMER_SET_SYSCTRL_REG2( EE_S12_TIMER_GET_SYSCTRL_REG2() & ~(0x08) );
}


#endif /* __INCLUDE_MC9S12_TIMER_H__ */

#endif /* __USE_TIMER__ */
