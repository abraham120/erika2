/** 
* @file uwl_timer_pic32.h
* @brief Timer Implementation for PIC32
* @author Christian Nastasi
* @author Daniele Alessandrelli
* @version 0.1
* @date 2010-02-08
*/
#ifndef __uwl_timer_pic32_h__
#define __uwl_timer_pic32_h__

#include <hal/uwl_timer.h>

#define UWL_HAL_BUS_FREQ (EE_get_peripheral_clock() / 1000)


#ifndef UWL_HAL_TIMER_ID
#define UWL_HAL_TIMER_ID 5
#endif

#if (UWL_HAL_TIMER_ID == 5)
        #define UWL_TIMER_REG_CONbits T5CONbits
        #define UWL_TIMER_REG_TMR TMR5
        #define UWL_TIMER_REG_PERIOD PR5
        #define UWL_TIMER_INTERRUPT_NAME _TIMER_5_VECTOR
        #define UWL_TIMER_REG_CON_CLEAR() T5CONCLR = 0xFFFFFFFF
        #define UWL_TIMER_MODULE_ON() T5CONbits.ON = 1
        #define UWL_TIMER_MODULE_OFF() T5CONbits.ON = 0
        #define UWL_TIMER_INTERRUPT_PRIORITY IPC5bits.T5IP
        #define UWL_TIMER_INTERRUPT_SUBPRIORITY IPC5bits.T5IS
        #define UWL_TIMER_INTERRUPT_FLAG_CLEAR() IFS0CLR = _IFS0_T5IF_MASK
        #define UWL_TIMER_INTERRUPT_ENABLE() IEC0SET = _IEC0_T5IE_MASK
        #define UWL_TIMER_INTERRUPT_DISABLE() IEC0CLR = _IEC0_T5IE_MASK
        #define UWL_TIMER_INTERRUPT_VECTOR _TIMER_5_VECTOR
#else /* TODO: implement other timer */
        #error "UWL_HAL ERROR: invalid timer hw interface specified"
#endif


int8_t uwl_timer_init(uint32_t period, uint32_t fcy);

void uwl_timer_set_isr_callback(void (*func)(void));

COMPILER_INLINE void uwl_timer_start(void)
{
        UWL_TIMER_INTERRUPT_FLAG_CLEAR();
        UWL_TIMER_INTERRUPT_ENABLE();
        UWL_TIMER_MODULE_ON();
}

COMPILER_INLINE void uwl_timer_stop(void)
{
        UWL_TIMER_INTERRUPT_DISABLE();
        UWL_TIMER_MODULE_OFF();
        UWL_TIMER_INTERRUPT_FLAG_CLEAR();
}

#endif /* Header Protection */
