/** 
* @file iedf_timer_pic32.h
* @brief Timer Implementation for PIC32
* @author Christian Nastasi
* @author Daniele Alessandrelli
* @author Gianluca Franchino  
* @version 0.1
* @date 2010-02-08
*/
#ifndef __iedf_timer_pic32_h__
#define __iedf_timer_pic32_h__

#include <hal/iedf_timer.h>

#define IEDF_HAL_BUS_FREQ (EE_get_peripheral_clock() / 1000)


#ifndef IEDF_HAL_TIMER_ID
#define IEDF_HAL_TIMER_ID 5
#endif

#if (IEDF_HAL_TIMER_ID == 5)
        #define IEDF_TIMER_REG_CONbits T5CONbits
        #define IEDF_TIMER_REG_TMR TMR5
        #define IEDF_TIMER_REG_PERIOD PR5
        #define IEDF_TIMER_INTERRUPT_NAME _TIMER_5_VECTOR
        #define IEDF_TIMER_REG_CON_CLEAR() T5CONCLR = 0xFFFFFFFF
        #define IEDF_TIMER_MODULE_ON() T5CONbits.ON = 1
        #define IEDF_TIMER_MODULE_OFF() T5CONbits.ON = 0
        #define IEDF_TIMER_INTERRUPT_PRIORITY IPC5bits.T5IP
        #define IEDF_TIMER_INTERRUPT_SUBPRIORITY IPC5bits.T5IS
        #define IEDF_TIMER_INTERRUPT_FLAG_CLEAR() IFS0CLR = _IFS0_T5IF_MASK
        #define IEDF_TIMER_INTERRUPT_ENABLE() IEC0SET = _IEC0_T5IE_MASK
        #define IEDF_TIMER_INTERRUPT_DISABLE() IEC0CLR = _IEC0_T5IE_MASK
        #define IEDF_TIMER_INTERRUPT_VECTOR _TIMER_5_VECTOR
#else /* TODO: implement other timer */
        #error "IEDF_HAL ERROR: invalid timer hw interface specified""
#endif


int8_t iedf_timer_init(uint32_t period, uint32_t fcy);

void iedf_timer_set_isr_callback(void (*func)(void));

COMPILER_INLINE void iedf_timer_start(void)
{
        IEDF_TIMER_INTERRUPT_FLAG_CLEAR();
        IEDF_TIMER_INTERRUPT_ENABLE();
        IEDF_TIMER_MODULE_ON();
}

COMPILER_INLINE void iedf_timer_stop(void)
{
        IEDF_TIMER_INTERRUPT_DISABLE();
        IEDF_TIMER_MODULE_OFF();
        IEDF_TIMER_INTERRUPT_FLAG_CLEAR();
}

#endif /* Header Protection */
