/** 
* @file uwl_timer_dspic30.h
* @brief Timer Implementation for dsPIC33
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_timer_dspic30_h__
#define __uwl_timer_dspic30_h__

#include <hal/uwl_timer.h>

#ifndef UWL_TIMER_REG_CON
#define UWL_TIMER_REG_CON		T5CON
#endif

#ifndef UWL_TIMER_REG_CONbits
#define UWL_TIMER_REG_CONbits		T5CONbits
#endif

#ifndef UWL_TIMER_REG_TMR
#define UWL_TIMER_REG_TMR		TMR5
#endif

#ifndef UWL_TIMER_REG_PERIOD
#define UWL_TIMER_REG_PERIOD		PR5
#endif

#ifndef UWL_TIMER_INTERRUPT_NAME
#define UWL_TIMER_INTERRUPT_NAME	_T5Interrupt
#endif

#ifndef UWL_TIMER_INTERRUPT_FLAG	
#define UWL_TIMER_INTERRUPT_FLAG	IFS1bits.T5IF	
#endif

#ifndef UWL_TIMER_INTERRUPT_ENABLE
#define UWL_TIMER_INTERRUPT_ENABLE 	IEC1bits.T5IE
#endif

#ifndef UWL_TIMER_INTERRUPT_PRIORITY
#define UWL_TIMER_INTERRUPT_PRIORITY 	IPC7bits.T5IP
#endif

int8_t uwl_timer_init(uint32_t period, uint32_t fcy);

void uwl_timer_set_isr_callback(void (*func)(void));

COMPILER_INLINE void uwl_timer_start(void)
{
	UWL_TIMER_INTERRUPT_FLAG = 0;
	UWL_TIMER_INTERRUPT_ENABLE = 1;
	UWL_TIMER_REG_CONbits.TON = 1;
}

COMPILER_INLINE void uwl_timer_stop(void)
{
	UWL_TIMER_INTERRUPT_ENABLE = 0;
	UWL_TIMER_REG_CONbits.TON = 0;
	UWL_TIMER_INTERRUPT_FLAG = 0;
}

#endif /* Header Protection */
