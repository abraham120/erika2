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

/*
 * Author: Gianluca Franchino 2012
 */
 
#ifndef __BM_CORTEX_M4__CONFIG_H__
#define __BM_CORTEX_M4__CONFIG_H__

#ifdef __LM4F232xxxx__


#ifdef __BM_ERIKA__

#define bm_clear_isr1() NVIC_INT_CLR_PENDING(EE_CORTEX_MX_GPIO_A_INT_NUM)
#define bm_clear_isr2() NVIC_INT_CLR_PENDING(EE_CORTEX_MX_GPIO_B_INT_NUM)
#define bm_clear_isr2_act_task()\
	NVIC_INT_CLR_PENDING(EE_CORTEX_MX_GPIO_C_INT_NUM)

#define	bm_raise_isr1() NVIC_INT_SET_PENDING(EE_CORTEX_MX_GPIO_A_INT_NUM)
#define	bm_raise_isr2() NVIC_INT_SET_PENDING(EE_CORTEX_MX_GPIO_B_INT_NUM)
#define	bm_raise_isr2_act_task()\
	NVIC_INT_SET_PENDING(EE_CORTEX_MX_GPIO_C_INT_NUM)

#else

#error "__BM_ERIKA__ not defined!" 

#endif /*__BM_ERIKA__*/

#ifndef EE_CPU_CLOCK
#define EE_CPU_CLOCK      16000000U
#endif

#define get_time_stamp() (NVIC_ST_RELOAD_M - EE_systick_get_value()) 
#define ticks_to_us(x) (1000 * x / MICROSECONDS_TO_TICKS(1,EE_CPU_CLOCK))


/*Initialize SysTick. Note that, SysTick is a 24 bits countdown timer */
__INLINE__ void bm_time_stamp_init(void) 
{
	EE_systick_set_period(NVIC_ST_RELOAD_M);
	EE_systick_start();
}

__INLINE__ void bm_interrupt_init(void) 
{
	NVIC_SET_PRI(EE_CORTEX_MX_GPIO_A_INT_NUM, 0);	
	NVIC_INT_ENABLE(EE_CORTEX_MX_GPIO_A_INT_NUM);

	NVIC_SET_PRI(EE_CORTEX_MX_GPIO_B_INT_NUM, 0);	
	NVIC_INT_ENABLE(EE_CORTEX_MX_GPIO_B_INT_NUM);
	
	NVIC_SET_PRI(EE_CORTEX_MX_GPIO_C_INT_NUM, 0);
	NVIC_INT_ENABLE(EE_CORTEX_MX_GPIO_C_INT_NUM);	
}


__INLINE__ void bm_hw_init(void) 
{
	EE_system_init(); 
	
	/*Init ISR1 and ISR2 interrupts */
	bm_interrupt_init();
	
	/*Initialize the 24 bits timer for timestamping*/
	bm_time_stamp_init();
	
	/*Initialize the UART communication*/
	//bm_uart_init();
	
}

#else
#error "NO MCU defined!!!"
#endif /*__LM4F232xxxx__*/

#endif /*__BM_CORTEX_M4__CONFIG_H__*/
