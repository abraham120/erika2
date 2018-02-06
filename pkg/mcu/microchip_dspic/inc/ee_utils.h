/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
    @file   ee_utils.h
    
    @brief  Utility API to set the mcu's behaviour.

    This file contain Utility API to set the mcu's behaviour. In particular contains API
    to interact with oscillator to set desired clock frequency and to get his value.
    Here there are some utility to read FOSC and FOSCSEL configuration registers of dsPIC
    architecture too.
    
    Actually the APIs are fully implemented only for dsPIC architecture. For PIC24 there 
    are get mocks implementation that rely on User (re)definition of EE_SYS_CLOCK with
    configured value of peripheral clock (the name and meaning of the define is chosen 
    for backward compatibility with miniflex board code).
            
    @author Errico Guidieri
    @date   2011

**/

#ifndef __INCLUDE_MICROCHIP_DSPIC_EE_UTILS_H__
#define __INCLUDE_MICROCHIP_DSPIC_EE_UTILS_H__

#include "mcu/microchip_dspic/inc/ee_mcu.h"

#if defined(__dsPIC33F__) 

#ifndef EE_PIC30_FRC_OSC_FREQ
/** Nominal Fast RC primary oscillator frequency **/
#define EE_PIC30_FRC_OSC_FREQ 7370000UL
#endif /* EE_PIC30_FRC_OSC_FREQ */

#ifndef EE_PIC30_PRI_OSC_FREQ
/** External Clock Source, redefine in the application if differs from this value **/
#define EE_PIC30_PRI_OSC_FREQ 4000000UL
#endif /* EE_PIC30_PRI_OSC_FREQ */

/** error codes
    @{
**/
#define EE_UTILS_ERR_NO_CLOCK_SWITCH      -1
#define EE_UTILS_ERR_UNKNOWN_CLOCK_SOURCE -2
/** @} **/

/**
    @brief set desired system clock frequency (Hz).
    
    @param fosc (EE_UINT32): desidered system frequency (Hz)

    @return frequency set or an appropriate error values
**/
EE_INT16 EE_set_system_clock(EE_UINT32 fosc);

/**
    @brief get system clock frequency (Hz).

    @return actual system frequency or an 
        appropriate error values
**/
EE_UINT32 EE_get_system_clock(void);

/**
    @brief get periphereal clock frequency (Hz).

    @return actual periphereal frequency or an 
        appropriate error values
**/
EE_UINT32 EE_get_peripheral_clock(void);

/**
    @brief get cpu instruction per seconds (MIPS).

    @return actual cpu MIPS or an 
        appropriate error values
**/
EE_UINT32 EE_get_cpu_mips(void);

/**
    @brief read FOSCSEL configuartion read-only flash register
    
    @return value of the register.
**/
__INLINE__ EE_UINT16 EE_read_foscsel(void){
    EE_UINT8 prevTblPag = TBLPAG;
    EE_UINT16 offset, data;
    TBLPAG = __builtin_tblpage(&_FOSCSEL);
    offset = __builtin_tbloffset(&_FOSCSEL);
    /* Table read */
    asm volatile ("tblrdl [%1],%0" : "=r"(data) : "r"(offset));
    TBLPAG = prevTblPag;
    return data;
}

/**
    @brief read FOSC configuartion read-only flash register
    
    @return value of the register.
**/
__INLINE__ EE_UINT16 EE_read_fosc(void){
    EE_UINT8 prevTblPag = TBLPAG;
    EE_UINT16 offset, data;
    TBLPAG = __builtin_tblpage(&_FOSC);
    offset = __builtin_tbloffset(&_FOSC);
    /* Table read */
    asm volatile ("tblrdl [%1],%0" : "=r"(data) : "r"(offset));
    TBLPAG = prevTblPag;
    return data;
}
#endif /* __dsPIC33F__ */

/* Support for __PIC24__ in not yet implementated. 
   There just a mock to make some driver compile 
*/
#if defined(__PIC24F__)

#ifndef EE_SYS_CLOCK
/** clock frequency define. Override this define to desired value **/
#define EE_SYS_CLOCK  16000000UL
#endif /* EE_SYS_CLOCK */

/**
    @brief mock function that return system clock value.
    
    mock function that return system clock value, 
    evaluated rely on User redefinition of EE_SYS_CLOCK (that must contains 
    the value of peripheral clock, half of the value returned by this method).
    
    @return system clock value, twice of peripheral clock (defined with EE_SYS_CLOCK).
 **/
__INLINE__ EE_UINT32 EE_get_system_clock(void){
    return EE_SYS_CLOCK * 2;
}

/**
    @brief mock function that return peripheral clock value.
    
    mock function that return peripheral clock value, 
    evaluated rely on User redefinition of EE_SYS_CLOCK (that must contains 
    the value of peripheral clock, the value returned by this method).
    
    @return peripheral clock value (defined with EE_SYS_CLOCK).
 **/
__INLINE__ EE_UINT32 EE_get_peripheral_clock(void){
    return EE_SYS_CLOCK;
}

/**
    @brief mock function that return instruction per seconds (MIPS).
    
    mock function that return MIPS clock value, 
    evaluated rely on User redefinition of EE_SYS_CLOCK (that must contains 
    the value of peripheral clock) and supposing doze factor = 1.
    
    @return cpu MIPS (supposing doze factor = 1).
**/
__INLINE__ EE_UINT32 EE_get_cpu_mips(void){
    return EE_SYS_CLOCK / 1000000UL;
}
#endif /* __PIC24F__ */

#endif  /* __INCLUDE_MICROCHIP_DSPIC_EE_UTILS_H__ */
