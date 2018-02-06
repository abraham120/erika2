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
#include "ee_pic30regs.h"
#include "mcu/microchip_dspic/inc/ee_internal.h"
#include "mcu/microchip_dspic/inc/ee_mcu.h"

#define EE_DSPIC_PIN_OUT 0
#define EE_DSPIC_PIN_IN  1

/* Formal define to make code more readable */
#define EE_DSPIC_NO_SIGNAL  -1

#ifdef _RP0R0 /* Register Programmable Pin 0 (chosen to as proof of programmable I/O) */

#ifdef _RC0 /* port C defined. Extended Riprogrammable pins */
static EE_INT8 EE_conf_dspic_pin_extended(EE_UINT8 pin, EE_UINT8 signal, EE_UINT8 pinDir)
{
    switch (pin) {
        case EE_PIN_RP16:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP16R = signal;
            _TRISC0 = pinDir;
        break;
        case EE_PIN_RP17:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP17R = signal;
            _TRISC1 = pinDir;
        break;
        case EE_PIN_RP18:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP18R = signal;
            _TRISC2 = pinDir;
        break;
        case EE_PIN_RP19:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP19R = signal;
            _TRISC3 = pinDir;
        break;
        case EE_PIN_RP20:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP20R = signal;
            _TRISC4 = pinDir;
        break;
        case EE_PIN_RP21:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP21R = signal;
            _TRISC5 = pinDir;
        break;
        case EE_PIN_RP22:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP22R = signal;
            _TRISC6 = pinDir;
        break;
        case EE_PIN_RP23:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP23R = signal;
            _TRISC7 = pinDir;
        break;
        case EE_PIN_RP24:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP24R = signal;
            _TRISC8 = pinDir;
        break;
        case EE_PIN_RP25:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP25R = signal;
            _TRISC9 = pinDir;
        break;
        default:
            return EE_INTERNAL_ERR_INVALID_PIN;
    }
    return 0;
}
#else
static EE_INT8 EE_conf_dspic_pin_extended(EE_UINT8 pin, EE_UINT8 signal, EE_UINT8 pinDir)
{
    return EE_INTERNAL_ERR_INVALID_PIN;
}
#endif /* _RC0 */

static EE_INT8 EE_conf_dspic_pin(EE_UINT8 pin, EE_UINT8 signal, EE_UINT8 pinDir)
{
    switch (pin) {
        case EE_PIN_RP0:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP0R = signal;
            _TRISB0 = pinDir;
        break;
        case EE_PIN_RP1:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP1R = signal;
            _TRISB1 = pinDir;
        break;
        case EE_PIN_RP2:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP2R = signal;
            _TRISB2 = pinDir;
        break;
        case EE_PIN_RP3:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP3R = signal;
            _TRISB3 = pinDir;
        break;
        case EE_PIN_RP4:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP4R = signal;
            _TRISB4 = pinDir;
        break;
        case EE_PIN_RP5:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP5R = signal;
            _TRISB5 = pinDir;
        break;
        case EE_PIN_RP6:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP6R = signal;
            _TRISB6 = pinDir;
        break;
        case EE_PIN_RP7:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP7R = signal;
            _TRISB7 = pinDir;
        break;
        case EE_PIN_RP8:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP8R = signal;
            _TRISB8 = pinDir;
        break;
        case EE_PIN_RP9:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP9R = signal;
            _TRISB9 = pinDir;
        break;
        case EE_PIN_RP10:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP10R = signal;
            _TRISB10 = pinDir;
        break;
        case EE_PIN_RP11:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP11R = signal;
            _TRISB11 = pinDir;
        break;
        case EE_PIN_RP12:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP12R = signal;
            _TRISB12 = pinDir;
        break;
        case EE_PIN_RP13:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP13R = signal;
            _TRISB13 = pinDir;
        break;
        case EE_PIN_RP14:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP14R = signal;
            _TRISB14 = pinDir;
        break;
        case EE_PIN_RP15:
            if(pinDir == EE_DSPIC_PIN_OUT)
                _RP15R = signal;
            _TRISB15 = pinDir;
        break;
        default:
            return EE_conf_dspic_pin_extended(pin, signal, pinDir);
    }
    return 0;
}

EE_INT8 EE_conf_dspic_pin_out(EE_UINT8 pin, EE_UINT8 signal)
{
    return EE_conf_dspic_pin(pin, signal, EE_DSPIC_PIN_OUT);
}

EE_INT8 EE_conf_dspic_pin_in(EE_UINT8 pin, EE_UINT8 signal)
{
    /* Conf right pin as an Input */
    EE_INT8 error;
    error = EE_conf_dspic_pin(pin, EE_DSPIC_NO_SIGNAL, EE_DSPIC_PIN_IN);
    if (error >= 0) {
        switch (signal) {
            case U1RX_SIGNAL:
                _U1RXR = pin;
            break;
            case U1CTS_SIGNAL:
                _U1CTSR = pin;
            break;
            case U2RX_SIGNAL:
                _U2RXR = pin;
            break;
            case U2CTS_SIGNAL:
                _U2CTSR = pin;
            break;
            /* TODO: add all possible configurable INs */
            default:
                error = EE_INTERNAL_ERR_INVALID_SIGNAL;
        }
    }
    return error;
}
#endif /* _RP0R0 Register Programmable Pin 0 (chosen to as proof of programmable I/O) */
