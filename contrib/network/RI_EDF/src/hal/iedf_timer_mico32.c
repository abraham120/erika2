/** 
* @file iedf_timer_pic32.c
* @brief Timer Implementation for PIC32
* @author Christian Nastasi
* @author Daniele Alessandrelli
* @author Gianluca Franchino 
* @version 0.1
* @date 2010-02-09
*/
#include <hal/iedf_timer_mico32.h>

static void (* volatile isr_callback)(void) = NULL;

int8_t iedf_timer_init(uint32_t period, uint32_t fcy) 
{

	iedf_hal_timer_init(MICROSECONDS_TO_TICKS(period), 	MICO32_TIMER_CONTROL_INT_BIT_MASK | 
														MICO32_TIMER_CONTROL_CONT_BIT_MASK | 
														MICO32_TIMER_CONTROL_STOP_BIT_MASK);
	
	return 1;
}

void iedf_timer_set_isr_callback(void (*func)(void))
{
	isr_callback = func;
	iedf_hal_timer_set_isr_callback(IEDF_TIMER_INTERRUPT_NAME);
} 

COMPILER_ISR(IEDF_TIMER_INTERRUPT_NAME)
{
    IEDF_TIMER_INTERRUPT_FLAG_CLEAR();
	if (isr_callback != NULL)
		isr_callback();
}

