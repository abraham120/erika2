/** 
* @file iedf_timer_mico32.h
* @brief Timer Implementation for mico32
* @author Christian Nastasi
* @author Daniele Alessandrelli
* @author Gianluca Franchino  
* @version 0.1
* @date 2010-02-08
*/
#ifndef __iedf_timer_mico32_h__
#define __iedf_timer_mico32_h__

#include <hal/iedf_timer.h>
#include "mcu/mico32/inc/ee_timer.h"
#include <MicoMacros.h>

#ifndef ISR2
#define ISR2(func) void func(void)
#endif

#define IEDF_TIMER_INTERRUPT_NAME 			iedf_timer_ISR_cbk
#define IEDF_TIMER_INTERRUPT_FLAG_CLEAR()

#define DECLARE_FUNC_IEDF_TIMER(uc, lc) \
COMPILER_INLINE int iedf_hal_timer_start(void) { \
	return cat3(EE_, lc, _on)(); } \
COMPILER_INLINE int iedf_hal_timer_stop(void) { \
	return cat3(EE_, lc, _off)(); } \
COMPILER_INLINE int iedf_hal_timer_set_isr_callback(void (*func)(void)) { \
	return cat3(EE_, lc, _set_ISR_callback)(func); } \
COMPILER_INLINE int iedf_hal_timer_init(int per, int set) { \
	return cat3(EE_, lc, _init)(per, set); }
DECLARE_FUNC_IEDF_TIMER(TIMER_IEDF, timer_iedf)
		
int8_t iedf_timer_init(uint32_t period, uint32_t fcy);
void iedf_timer_set_isr_callback(void (*func)(void));
COMPILER_ISR(IEDF_TIMER_INTERRUPT_NAME);

COMPILER_INLINE void iedf_timer_start(void)
{
	iedf_hal_timer_start();
}

COMPILER_INLINE void iedf_timer_stop(void)
{
	iedf_hal_timer_stop();
}



#endif /* Header Protection */
