/** 
* @file uwl_timer_stm32.c
* @brief Timer Implementation for STM32
* @author Gianluca Franchino
* @version 0.1
* @date 2013-10-09
*/
#include <hal/uwl_timer_stm32.h>

static void (* volatile isr_callback)(void) = NULL;

int8_t uwl_timer_init(uint32_t period, uint32_t fcy) 
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	uint16_t PrescalerValue;
	
	/* Timer clock enable */
	RCC_APB1PeriphClockCmd(UWL_RCC_APBxPeriph_TMR, ENABLE);

	
	/* Compute the prescaler value, this set the timer tick to 1us, i.e. 
	 * counter freq: 1 MHz.
	 * Note, the base counter clock is APB2, which is set to work at 
	 * SystemCoreClock / 2.
	 */
	PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 1e6) - 1;
	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = period;
	TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(UWL_TIMx, &TIM_TimeBaseStructure);
	
	/*TODO: delete the following instruc., it should be unuseful.*/
	/* Prescaler configuration */
	//TIM_PrescalerConfig(UWL_TIMx, PrescalerValue, TIM_PSCReloadMode_Immediate);
	
	
	return 1;
}

void uwl_timer_set_isr_callback(void (*func)(void))
{
	isr_callback = func;
} 

COMPILER_ISR(UWL_TIMER_INTERRUPT_NAME) 
{
	TIM_ClearITPendingBit(UWL_TIMx, TIM_IT_Update);
	if (isr_callback != NULL) 
		isr_callback();
}

