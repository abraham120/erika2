/** 
* @file uwl_timer_pic32.c
* @brief Timer Implementation for PIC32
* @author Christian Nastasi
* @author Daniele Alessandrelli
* @version 0.1
* @date 2010-02-09
*/
#include <hal/uwl_timer_mico32.h>

static void (* volatile isr_callback)(void) = NULL;

int8_t uwl_timer_init(uint32_t period, uint32_t fcy) 
{

	uwl_hal_timer_init(MICROSECONDS_TO_TICKS(period), 	MICO32_TIMER_CONTROL_INT_BIT_MASK | 
														MICO32_TIMER_CONTROL_CONT_BIT_MASK | 
														MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	return 1;
}

void uwl_timer_set_isr_callback(void (*func)(void))
{
	isr_callback = func;
	uwl_hal_timer_set_isr_callback(UWL_TIMER_INTERRUPT_NAME);
} 

COMPILER_ISR(UWL_TIMER_INTERRUPT_NAME)
{
    UWL_TIMER_INTERRUPT_FLAG_CLEAR();
	if (isr_callback != NULL)
		isr_callback();
}

