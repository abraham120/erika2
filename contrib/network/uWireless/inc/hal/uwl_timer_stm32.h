/** 
* @file uwl_timer_stm32.h
* @brief Timer Implementation for STM32
* @author Gianluca Franchino
* @version 0.1
* @date 2013-10-07
*/
#ifndef __uwl_timer_stm32_h__
#define __uwl_timer_stm32_h__

#include <hal/uwl_timer.h>
#include "stm32f4xx.h"

#ifndef UWL_HAL_TIMER_ID
#define UWL_HAL_TIMER_ID 2
#endif

#if (UWL_HAL_TIMER_ID == 2)

#define UWL_TIMx	TIM2
#define UWL_RCC_APBxPeriph_TMR RCC_APB1Periph_TIM2

#else

#error "UWL_HAL ERROR: invalid timer hw interface specified"

#endif


int8_t uwl_timer_init(uint32_t period, uint32_t fcy);

void uwl_timer_set_isr_callback(void (*func)(void));


COMPILER_INLINE void uwl_timer_start(void)
{
	TIM_ClearITPendingBit(UWL_TIMx, TIM_IT_Update);
	/* UWL_TIMER_ID Interrupts enable */
	TIM_ITConfig(UWL_TIMx, TIM_IT_Update, ENABLE);
	/* UWL_TIMER_ID enable counter */
	TIM_Cmd(UWL_TIMx, ENABLE);
}

COMPILER_INLINE void uwl_timer_stop(void)
{
	/* UWL_TIMER_ID Interrupts enable */
	TIM_ITConfig(UWL_TIMx, TIM_IT_Update, DISABLE);
	/* UWL_TIMER_ID enable counter */
	TIM_Cmd(UWL_TIMx, DISABLE);
	TIM_ClearITPendingBit(UWL_TIMx, TIM_IT_Update);
}


#endif /* Header Protection */
