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
    @file	ee_timer.h
    @brief	Timer Driver header file.
    @author	Giuseppe Serano
    @date	2012

**/

#ifndef	__INCLUDE_STELLARIS_LM4F232XXXX_TIMER_H__
#define	__INCLUDE_STELLARIS_LM4F232XXXX_TIMER_H__

#ifdef	__USE_TIMER__

/* Timer Module IDs Macros */
#define	EE_TIMER_0	0x00000000	/**< Timer Module 0 */
#define	EE_TIMER_1	0x00000001	/**< Timer Module 1 */
#define	EE_TIMER_2	0x00000002	/**< Timer Module 2 */
#define	EE_TIMER_3	0x00000003	/**< Timer Module 3 */
#define	EE_TIMER_4	0x00000004	/**< Timer Module 4 */
#define	EE_TIMER_5	0x00000005	/**< Timer Module 5 */

#define	EE_TIMER_WIDE	0x00000010	/**< Timer Wide Module */

#define	EE_TIMER_A	0x00FF0000	/**< Timer Unit A */
#define	EE_TIMER_B	0xFF000000	/**< Timer Unit B */
#define	EE_TIMER_BOTH	( EE_TIMER_A | EE_TIMER_B )	/**< Timer Both Units */

typedef	EE_UREG	EE_TimerId;	/**< Timer Identifier */

/** Timer Configuration Macros **/
#define	EE_TIMER_CFG_RTC	0x00000001	/**< RTC Configuration	      */
#define	EE_TIMER_CFG_SPLITTED	0x00000004	/**< Splitted Configuration   */

#define	EE_TIMER_CFG_ONE_SHOT	0x00210000	/**< Joined On-Shot	      */
#define	EE_TIMER_CFG_PERIODIC	0x00220000	/**< Joined Periodic	      */
#define	EE_TIMER_CFG_COUNT_UP	0x00100000	/**< Joined Count Up	      */

#define	EE_TIMER_CFG_A_ONE_SHOT	EE_TIMER_CFG_ONE_SHOT	/**< Unit A One-Shot  */
#define	EE_TIMER_CFG_A_PERIODIC	EE_TIMER_CFG_PERIODIC	/**< Unit A Priodic   */
#define	EE_TIMER_CFG_A_COUNT_UP	EE_TIMER_CFG_COUNT_UP	/**< Unit A Count Up  */

#define	EE_TIMER_CFG_B_ONE_SHOT	0x21000000		/**< Unit B One-Shot  */
#define	EE_TIMER_CFG_B_PERIODIC	0x22000000		/**< Unit B Periodic  */
#define	EE_TIMER_CFG_B_COUNT_UP	0x10000000		/**< Unit B Count Up  */

typedef	EE_UREG	EE_TimerCfg;	/**< Timer Configuration */

/* Timer Errors Macros */
#define	EE_TIMER_ERR_NONE	0x00000000	/**< No Error.		      */
#define	EE_TIMER_ERR_INIT	0x00000001	/**< Module Not Initialized.  */
#define	EE_TIMER_ERR_ID		0x00000002	/**< Wrong Identifier	      */

typedef	EE_UREG	EE_TimerErr;	/**< Timer Errors */

/** @brief	Timer Initialization.
 *  @param	id	Timer Identifier.
 *  @param	cfg	Timer Configuration.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *
 *  This function initializes a timer module and configures the operating mode
 *  of the timer(s).
 *
 *  The timer(s) is(are) stopped before being configured, and is(are) left in
 *  the stopped state.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 *
 *  The configuration is specified in <em>cfg</em> as one of the following
 *  values:
 *  - <tt>TIMER_CFG_RTC</tt>:		Full-width RTC.
 *  - <tt>TIMER_CFG_ONE_SHOT</tt>:	Full-width one-shot.
 *  - <tt>TIMER_CFG_PERIODIC</tt>:	Full-width periodic.
 *  - <tt>TIMER_CFG_COUNT_UP</tt>:	Full-width counts up instead of down.
 *  - <tt>TIMER_CFG_SPLITTED</tt>:	Two half-width timers.
 *
 *  When configured for a pair of half-width timers, each timer is separately
 *  configured.  The first timer is configured by setting <em>cfg</em> to the
 *  result of a logical OR operation between one of the following values and
 *  <em>cfg</em>:
 *
 *  - <tt>TIMER_CFG_A_ONE_SHOT</tt>:	Half-width one-shot timer A.
 *  - <tt>TIMER_CFG_A_PERIODIC</tt>:	Half-width periodic timer A.
 *  - <tt>TIMER_CFG_A_COUNT_UP</tt>:	Half-width timer A that counts up
 *  					instead of down.
 *
 *  Similarly, the second timer is configured by setting <em>cfg</em> to the
 *  result of a logical OR operation between one of the corresponding
 *  <tt>TIMER_CFG_B_*</tt> values and <em>cfg</em>.
 */
EE_TimerErr EE_timer_init(EE_TimerId id, EE_TimerCfg cfg);

/** @brief	Timer De-Initialization.
 *  @param	id	Timer Identifier.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  This function de-initializes a timer module.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 */
EE_TimerErr EE_timer_deinit(EE_TimerId id);

/** @brief	Timer Start.
 *  @param	id	Timer Identifier.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  This function will start the Timer(s) counter(s).
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 *
 *  @note	If an ISR has been defined, it is called when the Timer counter
 *  		rolls over.
 *
 *  @note	Calling this function will cause the Timer(s) counter(s) to
 *  		(re)commence counting from its current value.  The counter is
 *  		not automatically reloaded with the period as specified in a
 *  		previous call to EE_timer_set_period().
 */
EE_TimerErr EE_timer_start(EE_TimerId id);

/** @brief	Timer Stop.
 *  @param	id	Timer Identifier.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  This function will stop the Timer(s) counter(s).
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 *
 *  @note	If an ISR has been defined, it will no longer be called until
 *  		Timer(s) is(are) restarted.
 */
EE_TimerErr EE_timer_stop(EE_TimerId id);

/** @brief	Enables Timer Interrupt.
 *  @param	id	Timer Identifier.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  This function will enable the Timer(s) interrupt(s), allowing it to be
 *  reflected to the processor.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 *
 *  @note	The Timer(s) ISR need to clear the Timer interrupt source by
 *  		calling <tt>EE_timer_clear_int()</tt>.
 */
EE_TimerErr EE_timer_enable_int(EE_TimerId id);

/** @brief	Disables the Timer interrupt.
 *  @param	id	Timer Identifier.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  This function will disable the Timer(s) interrupt(s), preventing it from
 *  being reflected to the processor.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 */
EE_TimerErr EE_timer_disable_int(EE_TimerId id);

/** @brief	Clear the Timer interrupt.
 *  @param	id	Timer Identifier.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  The specified timer(s) interrupt(s) sources are cleared, so that they no
 *  longer assert.  This function must be called in the interrupt handler to
 *  keep the interrupt from being triggered again immediately upon exit.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 */
EE_TimerErr EE_timer_clear_int(EE_TimerId id);

/** @brief	Sets the period of the Timer counter.
 *  @param	id	Timer Identifier.
 *  @param	period	Timer Counter Current Value to read.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  This function sets the timer period; if the timer is running then the period
 *  is immediately loaded into the timer.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 *
 *  @note	This function can be used for both full- and half-width modes of
 *  		16/32-bit timers, and for half-width modes of 32/64-bit timers.
 *  		Use EE_timer_set_period_64() for full-width modes of 32/64-bit
 *  		timers.
 */
EE_TimerErr EE_timer_set_period(EE_TimerId id, EE_UREG period);

/** @brief	Gets the period of the Timer counter.
 *
 *  This function gets the currently programmed period for the specified timer.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 *
 *  @note	This function can be used for both full- and half-width modes of
 *  		16/32-bit timers, and for half-width modes of 32/64-bit timers.
 *  		Use EE_timer_get_period_64() for full-width modes of 32/64-bit
 *  		timers.
 */
EE_TimerErr EE_timer_get_period(EE_TimerId id, EE_UREG *period);

/** @brief	Gets the current value of the Timer counter.
 *  @param	id	Timer Identifier.
 *  @param	value	Timer Counter Current Value to read.
 *  @return	Error Code:
 *  		- <tt>EE_TIMER_ERR_NONE</tt>:	Operation successful.
 *  		- <tt>EE_TIMER_ERR_ID</tt>:	Wrong Timer Identifier.
 *  		- <tt>EE_TIMER_ERR_INIT</tt>:	Timer Module Not Initialized.
 *
 *  This function reads the current value of the specified timer.
 *
 *  The identifier of a timer is specified in <em>id</em> as one of the
 *  following timer module values:
 *  - <tt>EE_TIMER_0</tt>:	Timer Module 0.
 *  - <tt>EE_TIMER_1</tt>:	Timer Module 1.
 *  - <tt>EE_TIMER_2</tt>:	Timer Module 2.
 *  - <tt>EE_TIMER_3</tt>:	Timer Module 3.
 *  - <tt>EE_TIMER_4</tt>:	Timer Module 4.
 *  - <tt>EE_TIMER_5</tt>:	Timer Module 5.
 *
 *  There are two types of timer models; a 16/32-bit variety and a 32/64-bit
 *  variety. To type of timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  value:
 *  - <tt>EE_TIMER_WIDE</tt>:	32/64-bit Timer Module Type.
 *
 *  The 16/32-bit variety is comprised of two 16-bit timers that can operate
 *  independently or be concatenated to form a 32-bit timer.
 *  Similarly, the 32/64-bit variety is comprised of two 32-bit timers that can
 *  operate independently or be concatenated to form a 64-bit timer.
 *
 *  The timer in a timer module is selected by setting <em>id</em> to the
 *  result of a logical OR operation between <em>id</em> and the following
 *  values:
 *  - <tt>EE_TIMER_A</tt>:	Timer Unit A.
 *  - <tt>EE_TIMER_B</tt>:	Timer Unit B.
 *  - <tt>EE_TIMER_BOTH</tt>:	Both Timer Units.
 *
 *  @note	This function can be used for both full- and half-width modes of
 *  		16/32-bit timers, and for half-width modes of 32/64-bit timers.
 *  		Use EE_timer_get_value_64() for full-width modes of 32/64-bit
 *  		timers.
 */
EE_TimerErr EE_timer_get_value(EE_TimerId id, EE_UREG *value);

#endif	/* __USE_TIMER__ */

#endif	/* __INCLUDE_STELLARIS_LM4F232XXXX_TIMER_H__ */
