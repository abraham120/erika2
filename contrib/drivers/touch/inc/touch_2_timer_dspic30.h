#ifndef __touch_2_timer_dspic30_h__
#define __touch_2_timer_dspic30_h__

#include "touch_2_timer.h"

#ifndef TOUCH_2_TIMER_REG_CON
#define TOUCH_2_TIMER_REG_CON		T6CON
#endif

#ifndef TOUCH_2_TIMER_REG_CONbits
#define TOUCH_2_TIMER_REG_CONbits	T6CONbits
#endif

#ifndef TOUCH_2_TIMER_REG_TMR
#define TOUCH_2_TIMER_REG_TMR		TMR6
#endif

#ifndef TOUCH_2_TIMER_REG_PERIOD
#define TOUCH_2_TIMER_REG_PERIOD		PR6
#endif

#ifndef TOUCH_2_TIMER_INTERRUPT_NAME
#define TOUCH_2_TIMER_INTERRUPT_NAME	_T6Interrupt
#endif

#ifndef TOUCH_2_TIMER_INTERRUPT_FLAG
#define TOUCH_2_TIMER_INTERRUPT_FLAG	IFS2bits.T6IF
#endif

#ifndef TOUCH_2_TIMER_INTERRUPT_ENABLE
#define TOUCH_2_TIMER_INTERRUPT_ENABLE 	IEC2bits.T6IE
#endif

#ifndef TOUCH_2_TIMER_INTERRUPT_PRIORITY
#define TOUCH_2_TIMER_INTERRUPT_PRIORITY 	IPC11bits.T6IP
#endif

int8_t touch_2_timer_init(uint32_t period, uint32_t fcy);

void touch_2_timer_set_isr_callback(void (*func)(void));

COMPILER_INLINE void touch_2_timer_start(void)
{
	TOUCH_2_TIMER_INTERRUPT_FLAG = 0;
	TOUCH_2_TIMER_INTERRUPT_ENABLE = 1;
	TOUCH_2_TIMER_REG_CONbits.TON = 1;
}

COMPILER_INLINE void touch_2_timer_stop(void)
{
	TOUCH_2_TIMER_INTERRUPT_ENABLE = 0;
	TOUCH_2_TIMER_REG_CONbits.TON = 0;
	TOUCH_2_TIMER_INTERRUPT_FLAG = 0;
}

#endif /* Header Protection */
