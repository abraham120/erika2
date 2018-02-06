/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/** 
	@file 	ee_timer.h
	@brief 	TIMER library header file.\n
			TIMER API explanation:\n
			API is generated with DECLARE_FUNC_TIMER(uc, lc) and only if the macros
			EE_TIMER1_NAME_UC, EE_TIMER2_NAME_UC, EE_TIMER3_NAME_UC, EE_TIMER4_NAME_UC
			are defined in "eecfg.h". 
	@author Dario Di Stefano
	@date 	2010
	@example
			The name of the TIMER module specified inside the platform and
			inside the conf.oil file is "User_Timer".
			
			The macros generated in "eecfg.h" are:\n
			\#define EE_TIMER1_NAME_LC user_timer\n
			\#define EE_TIMER1_NAME_UC USER_TIMER\n
			
			The user must use the lower case form of the name, "user_timer", 
			to call the functions of the TIMER API as shown in the following example list.
				
			Name: 				int EE_user_timer_init(int period, int settings);\n
			Action:				This function configures Timer controller (to change default parameters);\n
			Parameter period:	Timer desired period [ticks];\n
			Parameter settings: binary OR of flags for special settings (see macros in ee_timer.h);\n
			Return:				EE_TIMER_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_timer_on(void);\n
			Action:				This function starts timer internal counter;\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_timer_off(void);\n
			Action:				This function stops timer internal counter;\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_timer_set_ISR_callback(EE_ISR_callback cbk);\n
			Action:				This function sets the Timer ISR callback (interrupt mode only);\n
			Parameter cbk:		Pointer to the callback;\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_timer_get_value(EE_UINT32 *val);\n
			Action:				This function reads timer counter;\n
			Parameter val:		address of the variable to copy to;\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_timer_enable_IRQ(void);\n
			Action:				This function enables timer IRQ (interrupt mode only);\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
			
			Name: 				int EE_user_timer_disable_IRQ(void);\n
			Action:				This function disables timer IRQ (interrupt mode only);\n
			Return:				EE_SPI_OK if no errors found, a negative number in case of errors.\n
*/

#ifndef __INCLUDE_EEMCUMICO32_TIMER_H__
#define __INCLUDE_EEMCUMICO32_TIMER_H__

//#include "cpu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_internal.h"
#include "mcu/mico32/inc/ee_buffer.h"
//#include <cpu/mico32/inc/ee_irq.h>
#include <MicoTimer.h>                  // to use LATTICE data structures.
 
/* mico-timer register structure (defined in MicoTimer.h)
 typedef struct st_MicoTimer{
     volatile unsigned int Status;
     volatile unsigned int Control;
     volatile unsigned int Period;
     volatile unsigned int Snapshot;
}MicoTimer_t; */
 
/* Symbols and macros */
#define EE_TIMER_OK         (0x00)
#define EE_timer_need_enable_int(mode)  ( (mode) & MICO32_TIMER_CONTROL_INT_BIT_MASK )

/**
	@brief			This function starts the timer counter.
    @param base		pointer to the Timer registers structure
    @return			EE_TIMER_OK if no errors found, else an error code (see macros in ee_timer.h).
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_start(MicoTimer_t* base)
{
    base->Control |= MICO32_TIMER_CONTROL_START_BIT_MASK; 
    return EE_TIMER_OK;
}

/**
	@brief			This function stops the timer counter.
    @param base		pointer to the Timer registers structure
    @return			EE_TIMER_OK if no errors found, else an error code (see macros in ee_timer.h).
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_stop(MicoTimer_t* base)
{
    base->Control |= MICO32_TIMER_CONTROL_STOP_BIT_MASK; 
    base->Status = 0;
    return EE_TIMER_OK;
}

/**
	@brief			This function reads the timer counter.
    @param base		pointer to the Timer registers structure
	@param val		pointer to a variable to copy to.
    @return			EE_TIMER_OK
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_get_val(MicoTimer_t* base, EE_UINT32 *val)
{
    *val = base->Snapshot;
    return EE_TIMER_OK;
}

/**
	@brief			This function enables timer IRQ.
    @param base		pointer to the Timer registers structure
    @return			EE_TIMER_OK
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_enable_IRQ(MicoTimer_t* base)
{
    base->Control |= MICO32_TIMER_CONTROL_INT_BIT_MASK;
    return EE_TIMER_OK;
}

/**
	@brief			This function disables timer IRQ.
    @param base		pointer to the Timer registers structure
	@return			EE_TIMER_OK
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_disable_IRQ(MicoTimer_t* base)
{
    base->Control &= ~MICO32_TIMER_CONTROL_INT_BIT_MASK;
    return EE_TIMER_OK;
}

#ifdef __USE_TIMER_IRQ__

/* Macro for Structure declaration */
#define DECLARE_STRUCT_TIMER(uc, lc) \
    extern EE_timer_st EE_ST_NAME(lc);
/* Macro for structure definition */
#define DEFINE_STRUCT_TIMER(uc, lc) \
EE_timer_st cat3(ee_, lc, _st) = { \
    .base= (MicoTimer_t*)cat2(uc, _BASE_ADDRESS),\
    .irqf= cat2(uc, _IRQ),\
    .cbk= EE_NULL_CBK };
    
/* Timer structure */
typedef struct {
    MicoTimer_t* base;
    int irqf;                           // irq flag to register the handler
    EE_ISR_callback cbk;
} EE_timer_st;

/**
	@brief			This function initializes the timer.
	@param tst		pointer to the Timer driver structure
	@param period 	timer period [ticks]
	@param settings Binary OR of flags.  Possible flag values are 
	@return			EE_TIMER_OK if no errors found, else an error code (see macros in ee_timer.h).
*/
int EE_hal_timer_init(EE_timer_st* tst, int period, int settings);

/**
	@brief			This function sets the timer ISR callback.
    @param tst		pointer to the Timer driver structure
	@param cbk		pointer to the callback
	@return			EE_TIMER_OK
*/
__INLINE__ int __ALWAYS_INLINE__  EE_hal_timer_set_callback(EE_timer_st* tst, EE_ISR_callback cbk)
{
    tst->cbk = cbk;
    return EE_TIMER_OK;
}

/**
	@brief			This function is the Timer IRQ handler.
    @param level	IRQ level
*/
void EE_timer_common_handler(int level);

#ifndef __STATIC_ISR_TABLE__
/**
	@brief 			This function sets the interrupt handler
	@param tst 		pointer to the Timer driver structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_timer_handler_setup(EE_timer_st* tst)
{
    /* Register IRQ handler */
    EE_mico32_register_ISR(tst->irqf, EE_timer_common_handler); 
}
#else /* __STATIC_ISR_TABLE__ */
#define EE_hal_timer_handler_setup(tst)
#endif

/* Interrupt mode API */
#define DECLARE_FUNC_TIMER(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _init)(int period, int settings){ \
    return EE_hal_timer_init(& EE_ST_NAME(lc), period, settings); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _on)(void){ \
    return EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _off)(void){ \
    return EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _set_ISR_callback)(EE_ISR_callback cbk){ \
    return EE_hal_timer_set_callback(& EE_ST_NAME(lc), cbk); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _get_value)(EE_UINT32 *val){ \
    return EE_hal_timer_get_val((MicoTimer_t*)EE_BASE_ADD(uc), val); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _enable_IRQ)(void){ \
    return EE_hal_timer_enable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _disable_IRQ)(void){ \
    return EE_hal_timer_disable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); }
    
#ifdef EE_TIMER1_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC)
#endif

#ifdef EE_TIMER2_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC)
#endif
    
#ifdef EE_TIMER3_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER3_NAME_UC, EE_TIMER3_NAME_LC)
#endif
    
#ifdef EE_TIMER4_NAME_UC
DECLARE_STRUCT_TIMER(EE_TIMER4_NAME_UC, EE_TIMER4_NAME_LC)
#endif
    
/* Return the Timer structure for the componente associated with the given IRQ
 * level */
__DECLARE_INLINE__ EE_timer_st *EE_get_timer_st_from_level(int level);

/**
	@brief 			This function is used inside the handler to get TIMER structure pointer
	@param level 	IRQ level
    @return 		the pointer of the structure associated to the IRQ number passed as argument
*/
__INLINE__ EE_timer_st * __ALWAYS_INLINE__ EE_get_timer_st_from_level(int level)
{
    #ifdef EE_TIMER1_NAME_UC
    if (level == EE_IRQ_NAME(EE_TIMER1_NAME_UC))
        return & EE_ST_NAME(EE_TIMER1_NAME_LC);
    #endif
    #ifdef EE_TIMER2_NAME_UC
    if (level == EE_IRQ_NAME(EE_TIMER2_NAME_UC))
        return & EE_ST_NAME(EE_TIMER2_NAME_LC);
    #endif
    #ifdef EE_TIMER3_NAME_UC
    if (level == EE_IRQ_NAME(EE_TIMER3_NAME_UC))
        return & EE_ST_NAME(EE_TIMER3_NAME_LC);
    #endif
    #ifdef EE_TIMER4_NAME_UC
    if (level == EE_IRQ_NAME(EE_TIMER4_NAME_UC))
        return & EE_ST_NAME(EE_TIMER4_NAME_LC);
    #endif
    return (EE_timer_st *)0;
}

#else /* #ifdef __USE_TIMER_IRQ__ */

/**
	@brief 			This function initializes the timer (polling mode).
    @param timerc	pointer to the Timer registers structure
	@param irqf		Timer IRQ numner
	@param period	timer period [ticks]
	@param settings	Binary OR of flags.  Possible flag values are 
					MICO32_TIMER_CONTROL_INT_BIT_MASK, MICO32_TIMER_CONTROL_CONT_BIT_MASK
	@return			EE_TIMER_OK if no errors found, else an error code (see macros in ee_timer.h).
*/
int EE_hal_timer_init(MicoTimer_t* timerc, int irqf, int period, int settings);

/* Polling mode API */
#define DECLARE_FUNC_TIMER(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _init)(int period, int settings){ \
    return EE_hal_timer_init((MicoTimer_t*)EE_BASE_ADD(uc), (int)EE_IRQ_NAME(uc), period, settings); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _on)(void){ \
    return EE_hal_timer_start((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _off)(void){ \
    return EE_hal_timer_stop((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _get_value)(EE_UINT32 *val){ \
    return EE_hal_timer_get_val((MicoTimer_t*)EE_BASE_ADD(uc), val); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _enable_IRQ)(void){ \
    return EE_hal_timer_enable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); } \
__INLINE__ int __ALWAYS_INLINE__  cat3(EE_, lc, _disable_IRQ)(void){ \
    return EE_hal_timer_disable_IRQ((MicoTimer_t*)EE_BASE_ADD(uc)); }

#endif  /* #ifdef __USE_TIMER_IRQ__ */

/* User functions (API) declaration: */  
#ifdef EE_TIMER1_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER1_NAME_UC, EE_TIMER1_NAME_LC)
#endif

#ifdef EE_TIMER2_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER2_NAME_UC, EE_TIMER2_NAME_LC)
#endif

#ifdef EE_TIMER3_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER3_NAME_UC, EE_TIMER3_NAME_LC)
#endif

#ifdef EE_TIMER4_NAME_UC
DECLARE_FUNC_TIMER(EE_TIMER4_NAME_UC, EE_TIMER4_NAME_LC)
#endif

#ifdef __USE_MICO_PIC32LIKE_API__
#include "mcu/mico32/inc/ee_timer_pic32like_api.h"
#endif

#endif /* __INCLUDE_EEMCUMICO32_TIMER_H__ */

