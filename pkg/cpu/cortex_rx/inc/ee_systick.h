/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
    @file	ee_systick.h
    @brief	SysTick system timer driver header file.
    @author	Giuseppe Serano
    @date	2012
    @author Christoph Kreuzberger
    @date 2014

**/

#ifndef	__INCLUDE_CORTEX_RX_SYSTICK_H__
#define	__INCLUDE_CORTEX_RX_SYSTICK_H__



#ifdef	__USE_SYSTICK__

#include "../contrib/ti_tms570/include/rti.h"
// Halcogen Variables
#define systick_handler rtiCompare2Interrupt
#define RTI_COUNTER_BLOCK rtiCOUNTER_BLOCK1
#define RTI_NOTIFICATION_COMPARE rtiNOTIFICATION_COMPARE2
#define RTI_COMPARE rtiCOMPARE2
#define EE_systick_clr_int_flg(f) rtiREG1->INTFLAG=4U;


/** error value. No errors happened **/
#define	EE_SYSTICK_NO_ERRORS	0
/** error value. Wrong funtion arguments values **/
#define	EE_SYSTICK_ERR_BAD_ARGS	1

#define RELOAD_M        0xFFFFFFFF
#define RELOAD_S        0


/**
    @brief Start SysTick.

    This will start the SysTick counter.  If an ISR has been defined, it is
    called when the SysTick counter rolls over.

    @note Calling this function will cause the SysTick counter to (re)commence
    counting from its current value.  The counter is not automatically reloaded
    with the period as specified in a previous call to EE_systick_set_period().
    If an immediate reload is required, the \b NVIC_ST_CURRENT register must be
    written to force this.  Any write to this register clears the SysTick
    counter to 0 and will cause a reload with the supplied period on the next
    clock.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_systick_start(void)
{
  //NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_ENABLE;
  rtiStartCounter(RTI_COUNTER_BLOCK);
}

/**
    @brief Stop SysTick.

    This will stop the SysTick counter.  If an ISR has been defined, it will
    no longer be called until SysTick is restarted.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_systick_stop(void)
{
  //NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);
  rtiStopCounter(RTI_COUNTER_BLOCK);
}

/**
    @brief Enables the SysTick interrupt.

    This function will enable the SysTick interrupt, allowing it to be
    reflected to the processor.

    @note The SysTick ISR does not need to clear the SysTick interrupt source as
    this is done automatically by NVIC when the interrupt ISR is called.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_systick_enable_int()
{
  //NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;
  rtiEnableNotification(RTI_NOTIFICATION_COMPARE);
}

/**
    @brief Disables the SysTick interrupt.

    This function will disable the SysTick interrupt, preventing it from being
    reflected to the processor.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_systick_disable_int()
{
  //NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_INTEN);
  rtiDisableNotification(RTI_NOTIFICATION_COMPARE);
}

/**
    @brief Sets the period of the SysTick counter.

    @param period is the number of clock ticks in each period of the SysTick
    counter; must be between 1 and 16,777,216, inclusive. If the \e period is
    out of range the function returns \b EE_SYSTICK_ERR_BAD_ARGS, else it will
    returns \b EE_SYSTICK_NO_ERRORS.

    This function sets the rate at which the SysTick counter wraps; this
    equates to the number of processor clocks between interrupts.

    @note Calling this function does not cause the SysTick counter to reload
    immediately.  If an immediate reload is required, the \b NVIC_ST_CURRENT
    register must be written.  Any write to this register clears the SysTick
    counter to 0 and will cause a reload with the \e period supplied here on
    the next clock after the SysTick is enabled.
 */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_systick_set_period(EE_UREG period)
{
  if ((period == RELOAD_S) || (period > RELOAD_M))
    return EE_SYSTICK_ERR_BAD_ARGS;

  //NVIC_ST_RELOAD_R = period - 1;
  rtiSetPeriod(RTI_COMPARE, period);

  return EE_SYSTICK_NO_ERRORS;
}

/**
    @brief Gets the period of the SysTick counter.

    This function returns the rate at which the SysTick counter wraps; this
    equates to the number of processor clocks between interrupts.

    @return Returns the period of the SysTick counter.
 */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_systick_get_period()
{
  //return NVIC_ST_RELOAD_R + 1;
  return rtiGetPeriod(RTI_COMPARE);
}

/**
    @brief Gets the current value of the SysTick counter.

    This function returns the current value of the SysTick counter; this will
    be a value between the period - 1 and zero, inclusive.

    @return Returns the current value of the SysTick counter.
 */
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_systick_get_value()
{
  //
  // Return the current value of the SysTick counter.
  //
  //return NVIC_ST_CURRENT_R;
  return rtiGetCurrentTick(RTI_COMPARE);
}

/** Default Clock Frequency */
#define	EE_DEFAULT_RTI_CLOCK	10000000

/**
    @brief Delay with SysTick .

    @param usDelay Number of us to Delay.

    This function delays the program execution by <tt>usDelay</tt> microseconds.
 */
__INLINE__ void __ALWAYS_INLINE__ EE_systick_delay_us(EE_UREG usDelay){
    EE_UREG	const start = EE_systick_get_value();
	EE_UREG ticks = MICROSECONDS_TO_TICKS(usDelay, EE_DEFAULT_RTI_CLOCK);

	/* Bound the delay to max one whole run */
	if ((ticks == RELOAD_S) || (ticks > RELOAD_M))
		ticks = RELOAD_M - 1;
	
	while (((EE_systick_get_value() - start) % RELOAD_M)  < ticks){
		; /* wait */
	}
}

#endif	/* __USE_SYSTICK__ */

#endif	/* __INCLUDE_CORTEX_RX_SYSTICK_H__ */
