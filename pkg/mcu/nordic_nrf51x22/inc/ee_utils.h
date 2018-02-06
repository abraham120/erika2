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
            
    @author Alessandro Biondi
    @date   2013

**/

#ifndef __INCLUDE_NORDIC_NRF51X22_EE_UTILS_H__
#define __INCLUDE_NORDIC_NRF51X22_EE_UTILS_H__

#include "mcu/nordic_nrf51x22/inc/ee_mcu.h"
#include "nrf.h"

/** Utility Macro that convert an amount of ms in number of ticks of a given
    frequency **/
#define MILLISECONDS_TO_TICKS(X_MS, REF_FREQ_HZ)                            \
    ((X_MS) * ((REF_FREQ_HZ) / 1000UL))

/** Utility Macro that convert an amount of us in number of ticks of a given
    frequency **/
#define MICROSECONDS_TO_TICKS(X_MICROSECS, REF_FREQ_HZ)                     \
    (((X_MICROSECS) / 1000UL)?                                              \
        (MILLISECONDS_TO_TICKS(((X_MICROSECS) / 1000UL), (REF_FREQ_HZ))):   \
        (MILLISECONDS_TO_TICKS((X_MICROSECS), (REF_FREQ_HZ)) / 1000UL))


/** error codes
    @{
**/
#define EE_UTILS_ERR_BAD_FREQ      0
/** @} **/

/**
    @brief get system clock frequency (Hz) - HFCLK (High Freq. Clock).

    @return actual system frequency
**/
EE_UINT32 EE_get_system_clock(void);


#endif  /* __INCLUDE_NORDIC_NRF51X22_EE_UTILS_H__ */
