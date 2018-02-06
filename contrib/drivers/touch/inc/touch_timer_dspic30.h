#ifndef __touch_timer_dspic30_h__
#define __touch_timer_dspic30_h__

#include "touch_timer.h"

#ifndef TOUCH_TIMER_REG_CON
#define TOUCH_TIMER_REG_CON		T4CON
#endif

#ifndef TOUCH_TIMER_REG_CONbits
#define TOUCH_TIMER_REG_CONbits		T4CONbits
#endif

#ifndef TOUCH_TIMER_REG_TMR
#define TOUCH_TIMER_REG_TMR		TMR4
#endif

#ifndef TOUCH_TIMER_REG_PERIOD
#define TOUCH_TIMER_REG_PERIOD		PR4
#endif

#ifndef TOUCH_TIMER_INTERRUPT_NAME
#define TOUCH_TIMER_INTERRUPT_NAME	_T4Interrupt
#endif

#ifndef TOUCH_TIMER_INTERRUPT_FLAG	
#define TOUCH_TIMER_INTERRUPT_FLAG	IFS1bits.T4IF	
#endif

#ifndef TOUCH_TIMER_INTERRUPT_ENABLE
#define TOUCH_TIMER_INTERRUPT_ENABLE 	IEC1bits.T4IE
#endif

#ifndef TOUCH_TIMER_INTERRUPT_PRIORITY
#define TOUCH_TIMER_INTERRUPT_PRIORITY 	IPC6bits.T4IP
#endif

int8_t touch_timer_init(uint32_t period, uint32_t fcy);

void touch_timer_set_isr_callback(void (*func)(void));

COMPILER_INLINE void touch_timer_start(void)
{
	TOUCH_TIMER_INTERRUPT_FLAG = 0;
	TOUCH_TIMER_INTERRUPT_ENABLE = 1;
	TOUCH_TIMER_REG_CONbits.TON = 1;
}

COMPILER_INLINE void touch_timer_stop(void)
{
	TOUCH_TIMER_INTERRUPT_ENABLE = 0;
	TOUCH_TIMER_REG_CONbits.TON = 0;
	TOUCH_TIMER_INTERRUPT_FLAG = 0;
}

#endif /* Header Protection */
