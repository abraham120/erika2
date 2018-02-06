/** 
* @file iedf_timer_dspic30.h
* @brief Timer Implementation for dsPIC33
* @author Christian Nastasi
* @author Gianluca Franchino  
* @version 0.1
* @date 2009-06-22
*/
#ifndef __iedf_timer_dspic30_h__
#define __iedf_timer_dspic30_h__

#include <hal/iedf_timer.h>

#ifndef IEDF_TIMER_REG_CON
#define IEDF_TIMER_REG_CON		T5CON
#endif

#ifndef IEDF_TIMER_REG_CONbits
#define IEDF_TIMER_REG_CONbits		T5CONbits
#endif

#ifndef IEDF_TIMER_REG_TMR
#define IEDF_TIMER_REG_TMR		TMR5
#endif

#ifndef IEDF_TIMER_REG_PERIOD
#define IEDF_TIMER_REG_PERIOD		PR5
#endif

#ifndef IEDF_TIMER_INTERRUPT_NAME
#define IEDF_TIMER_INTERRUPT_NAME	_T5Interrupt
#endif

#ifndef IEDF_TIMER_INTERRUPT_FLAG	
#define IEDF_TIMER_INTERRUPT_FLAG	IFS1bits.T5IF	
#endif

#ifndef IEDF_TIMER_INTERRUPT_ENABLE
#define IEDF_TIMER_INTERRUPT_ENABLE 	IEC1bits.T5IE
#endif

#ifndef IEDF_TIMER_INTERRUPT_PRIORITY
#define IEDF_TIMER_INTERRUPT_PRIORITY 	IPC7bits.T5IP
#endif

int8_t iedf_timer_init(uint32_t period, uint32_t fcy);

void iedf_timer_set_isr_callback(void (*func)(void));

COMPILER_INLINE void iedf_timer_start(void)
{
	IEDF_TIMER_INTERRUPT_FLAG = 0;
	IEDF_TIMER_INTERRUPT_ENABLE = 1;
	IEDF_TIMER_REG_CONbits.TON = 1;
}

COMPILER_INLINE void iedf_timer_stop(void)
{
	IEDF_TIMER_INTERRUPT_ENABLE = 0;
	IEDF_TIMER_REG_CONbits.TON = 0;
	IEDF_TIMER_INTERRUPT_FLAG = 0;
}

#endif /* Header Protection */
