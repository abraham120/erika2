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

/** 
	@file ee_timer_pic32like_api.h
	@brief Timer adapted functions for compatibility with pic32 projects. 
	@author Dario Di Stefano
	@date 2010
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER_PIC32LIKE_H__
#define __INCLUDE_EEMCUMICO32_TIMER_PIC32LIKE_H__

/* ------------------------------------------------ */
/* Macros for compatibility with pic32 timer driver */
/* ------------------------------------------------ */

#define EE_TIMER_DEFAULT_SETTINGS (MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK)
#ifdef __USE_TIMER_IRQ__
#define EE_mchp_timer_set_callback(lc, cbk) EE_hal_timer_set_callback(& EE_ST_NAME(lc), cbk)
#define EE_mchp_timer_init(uc, lc, period, prescale) EE_hal_timer_init(& EE_ST_NAME(lc), period, EE_TIMER_DEFAULT_SETTINGS)
#else
#define EE_mchp_timer_init(uc, lc, period, prescale) EE_hal_timer_init((MicoTimer_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc), period, MICO32_TIMER_CONTROL_CONT_BIT_MASK | MICO32_TIMER_CONTROL_START_BIT_MASK)
#endif // #ifdef __USE_TIMER_IRQ__
#define EE_mchp_timer_start(uc) EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc))
#define EE_mchp_timer_stop(uc) EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc))
#define EE_mchp_timer_get_val(uc, va) EE_hal_timer_get_val((MicoTimer_t*)EE_BASE_ADD(uc), va)

/*
	This function is used to initialize a Timer. 
        Arguments:
            - EE_UINT8 id: id number of the timer
            - EE_UINT16 period: desired period
            - EE_UINT8 prescale: pre-scaler
        Actions: 
            - Initialize the timer
        Return values:
            - the function return the result: 	EE_TIMER_OK if no errors found, 
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_hard_init(EE_UINT8 id, EE_UINT16 period, EE_UINT8 prescale)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period, prescale);
	else 
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period, prescale);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period, prescale);
		#else	
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period, prescale);
		#endif
	#endif
	
	return ret;
}

/*
	This function is used to initialize a Timer. 
        Arguments:
            - EE_UINT8 id: id number of the timer
            - EE_UINT16 period: desired period
            - EE_UINT8 prescale: pre-scaler
        Actions: 
            - Initialize the timer
        Return values:
            - the function return the result: 	EE_TIMER_OK if no errors found, 
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_soft_init(EE_UINT8 id, EE_UINT32 period_us, EE_UINT32 f_tick)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period_us, f_tick);
	else 
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period_us, f_tick);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_init(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC, period_us, f_tick);
		#else	
		ret = EE_mchp_timer_init(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC, period_us, f_tick);
		#endif
	#endif
	
	return ret;
}

#ifdef __USE_TIMER_IRQ__
/*
	This function is used to set ISR callback.
        Arguments:
            - EE_UINT8 id: id number of the timer
            - void (*f)(void): callback to be called inside the interrupt handler.
        Actions: 
            - Set ISR callback
        Return values:
            - the function return the result: 	EE_TIMER_OK if no errors found, 
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_set_callback(EE_UINT8 id, void (*f)(void))
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_set_callback(EE_TIMER1_NAME_LC, f);
	else 
		ret = EE_mchp_timer_set_callback(EE_TIMER2_NAME_LC, f);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_set_callback(EE_TIMER1_NAME_LC, f);
		#else	
		ret = EE_mchp_timer_set_callback(EE_TIMER2_NAME_LC, f);
		#endif
	#endif
	
	return ret;
}
#endif // #ifdef __USE_TIMER_IRQ__

/*
	This function is used to start a timer.
        Arguments:
            - EE_UINT8 id: id number of the timer
        Actions: 
            - Start a timer
        Return values:
            - the function return the result: 	EE_TIMER_OK if no errors found, 
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_start(EE_UINT8 id)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_start(EE_TIMER1_NAME_UC);
	else 
		ret = EE_mchp_timer_start(EE_TIMER2_NAME_UC);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_start(EE_TIMER1_NAME_UC);
		#else	
		ret = EE_mchp_timer_start(EE_TIMER2_NAME_UC);
		#endif
	#endif
	
	return ret;
}

/*
	This function is used to stop a timer.
        Arguments:
            - EE_UINT8 id: id number of the timer
        Actions: 
            - Stop a timer
        Return values:
            - the function return the result: 	EE_TIMER_OK if no errors found, 
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_stop(EE_UINT8 id)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_stop(EE_TIMER1_NAME_UC);
	else 
		ret = EE_mchp_timer_stop(EE_TIMER2_NAME_UC);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_stop(EE_TIMER1_NAME_UC);
		#else	
		ret = EE_mchp_timer_stop(EE_TIMER2_NAME_UC);
		#endif
	#endif
	
	return ret;
}

/*
	This function is used to get timer counter value
        Arguments:
            - EE_UINT8 id: id number of the timer
			- EE_UINT16 *v: pointer to a variable
        Actions: 
            - Get timer counter value
        Return values:
            - the function return the result: 	EE_TIMER_OK if no errors found, 
												a negative number in case of errors.
*/
__INLINE__ EE_INT8 __ALWAYS_INLINE__ EE_timer_get_val(EE_UINT8 id, EE_UINT16 *v)
{
	EE_INT8 ret;
	
	#if defined(EE_TIMER1_NAME_LC) && defined(EE_TIMER2_NAME_LC)
	if(id==1)
		ret = EE_mchp_timer_get_val(EE_TIMER1_NAME_UC, (unsigned int *) v);
	else 
		ret = EE_mchp_timer_get_val(EE_TIMER2_NAME_UC, (unsigned int *) v);
	#else
		#if defined(EE_UART1_NAME_LC)
		ret = EE_mchp_timer_get_val(EE_TIMER1_NAME_UC, (unsigned int *) v);
		#else	
		ret = EE_mchp_timer_get_val(EE_TIMER2_NAME_UC, (unsigned int *) v);
		#endif
	#endif
	
	return ret;
}

#endif // __INCLUDE_EEMCUMICO32_TIMER_PIC32LIKE_H__
