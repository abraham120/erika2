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
    @file   ee_internal.h
    @brief  This header contains internal API for drivers.
            The API here collected should not be directly called by users.
            Right now you can find here some implementation for
            fresh scheduler (FRSH) and some API for configurable pins.
    @author Errico Guidieri
    @date   2011
*/

#ifndef __INCLUDE_MICROCHIP_DSPIC_INTERNAL_H__
#define __INCLUDE_MICROCHIP_DSPIC_INTERNAL_H__

#include "mcu/microchip_dspic/inc/ee_mcu.h"

/*************************************************************************
 Configurable signals
**************************************************************************/

/* Output Signals */
#define U1TX_SIGNAL  0x03
#define U1RTS_SIGNAL 0x04 /* UART 1. Ready to send */
#define U2TX_SIGNAL  0x05
#define U2RTS_SIGNAL 0x06

/* Input Signals */
#define U1RX_SIGNAL  0
#define U1CTS_SIGNAL 1 /* UART 1. Clear to send */
#define U2RX_SIGNAL  2
#define U2CTS_SIGNAL 3

#define EE_INTERNAL_ERR_INVALID_PIN    -1
#define EE_INTERNAL_ERR_INVALID_SIGNAL -2

#if defined(_RP0R0) || defined(_RPOR0_RP20R_MASK) /* Register Programmable Pin 0 (chosen to as proof of programmable I/O) */
EE_INT8 EE_conf_dspic_pin_in(EE_UINT8 pin, EE_UINT8 signal);
EE_INT8 EE_conf_dspic_pin_out(EE_UINT8 pin, EE_UINT8 signal);
#else
__INLINE__ EE_INT8 EE_conf_dspic_pin_in(EE_UINT8 pin, EE_UINT8 signal);
__INLINE__ EE_INT8 EE_conf_dspic_pin_out(EE_UINT8 pin, EE_UINT8 signal);
#endif /* Programmable I/O */
/*************************************************************************
 Timers
 *************************************************************************/

/*
 * FRSH
 */

#if defined(__DSPIC_FRSH__) && defined(__FRSH__)
/* This function set the capacity timer to raise in t ticks. */
void EE_hal_set_budget_timer(EE_STIME t);

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_budget_timer(void)
{
  IFS1bits.T5IF = 0;
  T4CONbits.TON = 0;
}
#elif defined(__FRSH__)

/* This function set the capacity timer to raise in t ticks. */
void EE_hal_set_budget_timer(EE_STIME t);

__INLINE__ void __ALWAYS_INLINE__ EE_hal_stop_budget_timer(void)
{
  IFS3bits.T7IF = 0;
  T6CONbits.TON = 0;
}

#endif /* __FRSH__ */

#if !defined(_RP0R0) && !defined(_RPOR0_RP20R_MASK) /* Implementation for model that don't have riconfigurable pins */
#if defined(__dsPIC33F__)  || defined(__PIC24H__) \
    || defined(__dsPIC30F1010__) || defined(__dsPIC30F2020__) || defined(__dsPIC30F2023__)

__INLINE__ EE_INT8 EE_conf_dspic_pin_in(EE_UINT8 pin, EE_UINT8 signal){
    switch (signal) {
        case U1RX_SIGNAL:
            TRISFbits.TRISF2 = 1;     /* Set UART1 In RX Pin */
        break;
        case U1CTS_SIGNAL:
            #ifdef _TRISD14
            TRISDbits.TRISD14 = 1;    /* Set UART1 In CTS Pin */
            #else
            TRISDbits.TRISD9 = 1;    /* Set UART1 In CTS Pin */
            #endif
        break;
        case U2RX_SIGNAL:
            TRISFbits.TRISF4 = 1;     /* Set UART2 In RX Pin */
        break;
        case U2CTS_SIGNAL:
            #ifdef _TRISF12
            TRISFbits.TRISF12 = 1;    /* Set UART2 In CTS Pin */
            #else
            TRISBbits.TRISB8 = 1;    /* Set UART2 In CTS Pin */
            #endif
        break;
        /* TODO: add all possible configurable INs */
        default:
            return EE_INTERNAL_ERR_INVALID_SIGNAL;
    }
    return 0;
}
__INLINE__ EE_INT8 EE_conf_dspic_pin_out(EE_UINT8 pin, EE_UINT8 signal){
    switch (signal) {
        case U1TX_SIGNAL:
            TRISFbits.TRISF3 = 0;        /* Set UART1 Out TX Pin */
        break;
        case U1RTS_SIGNAL:
            #ifdef _TRISD15
            TRISDbits.TRISD15 = 0;       /* Set UART1 Out RTS Pin */
            #else
            TRISFbits.TRISF6 = 0;       /* Set UART1 Out RTS Pin */
            #endif
        break;
        case U2TX_SIGNAL:
            TRISFbits.TRISF5 = 0;        /* Set UART2 Out TX Pin */
        case U2RTS_SIGNAL:
            #ifdef _TRISF13
            TRISFbits.TRISF13 = 0;       /* Set UART2 Out RTS Pin */
            #else
            TRISBbits.TRISB14 = 0;       /* Set UART2 Out RTS Pin */
            #endif
        break;
        /* TODO: add all possible configurable OUTs */
        default:
            return EE_INTERNAL_ERR_INVALID_SIGNAL;
    }
    return 0;
}
#elif defined(__dsPIC30F__)
__INLINE__ EE_INT8 EE_conf_dspic_pin_in(EE_UINT8 pin, EE_UINT8 signal){
    switch (signal) {
        case U1RX_SIGNAL:
            TRISFbits.TRISF2 = 1;     /* Set UART1 In RX Pin */
        break;
        case U2RX_SIGNAL:
            TRISFbits.TRISF4 = 1;     /* Set UART2 In RX Pin */
        break;
        /* TODO: add all possible configurable INs */
        default:
            return EE_INTERNAL_ERR_INVALID_SIGNAL;
    }
    return 0;
}
__INLINE__ EE_INT8 EE_conf_dspic_pin_out(EE_UINT8 pin, EE_UINT8 signal){
    switch (signal) {
        case U1TX_SIGNAL:
            TRISFbits.TRISF3 = 0;        /* Set UART1 Out TX Pin */
        break;
        case U2TX_SIGNAL:
            TRISFbits.TRISF5 = 0;        /* Set UART2 Out TX Pin */
        /* TODO: add all possible configurable OUTs */
        default:
            return EE_INTERNAL_ERR_INVALID_SIGNAL;
    }
    return 0;
}
#endif /* __dsPIC30F__ ... */

#endif /* _RP0R0 */
#endif /* __INCLUDE_MICROCHIP_DSPIC_INTERNAL_H__ */
