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
 
#include "ee.h"
#include "mcu/microchip_dspic/inc/ee_adc.h"

/* WARNING: ADC2 driver is not implemented! only ADC1 is supported. */

enum EE_Adc_SampleFormats {
    EE_ADC_UINT  = 0x0,
    EE_ADC_INT   = 0x1,
    EE_ADC_UFRAC = 0x2,
    EE_ADC_FRAC  = 0x3
};

static void EE_adc_set_sample_format(enum EE_Adc_SampleFormats format)
{
    _FORM = format;
}

static EE_INT16 EE_adc1_init_ch_internal ( EE_AdcChId adc_ch_id )
{
    /* turn off ADC module */
    _ADON = 0;
    EE_INT16 error = EE_ADC_ERR_NO;
    switch( adc_ch_id ) {
#ifdef _PCFG0
        case EE_ADC_PIN0:
            _PCFG0 = 0;
        break;
#endif
#ifdef _PCFG1
        case EE_ADC_PIN1:
            _PCFG1 = 0;
        break;
#endif
#ifdef _PCFG2
        case EE_ADC_PIN2:
            _PCFG2 = 0;
        break;
#endif
#ifdef _PCFG3
        case EE_ADC_PIN3:
            _PCFG3 = 0;
        break;
#endif
#ifdef _PCFG4
        case EE_ADC_PIN4:
            _PCFG4 = 0;
        break;
#endif
#ifdef _PCFG5
        case EE_ADC_PIN5:
            _PCFG5 = 0;
        break;
#endif
#ifdef _PCFG6
        case EE_ADC_PIN6:
            _PCFG6 = 0;
        break;
#endif
#ifdef _PCFG7
        case EE_ADC_PIN7:
            _PCFG7 = 0;
        break;
#endif
#ifdef _PCFG8
        case EE_ADC_PIN8:
            _PCFG8 = 0;
        break;
#endif
#ifdef _PCFG9
        case EE_ADC_PIN9:
            _PCFG9 = 0;
        break;
#endif
#ifdef _PCFG10
        case EE_ADC_PIN10:
            _PCFG10 = 0;
        break;
#endif
#ifdef _PCFG11
        case EE_ADC_PIN11:
            _PCFG11 = 0;
        break;
#endif
#ifdef _PCFG12
        case EE_ADC_PIN12:
            _PCFG12 = 0;
        break;
#endif
#ifdef _PCFG13
        case EE_ADC_PIN13:
            _PCFG13 = 0;
        break;
#endif
#ifdef _PCFG14
        case EE_ADC_PIN14:
            _PCFG14 = 0;
        break;
#endif
#ifdef _PCFG15
        case EE_ADC_PIN15:
            _PCFG15 = 0;
        break;
#endif
#ifdef _PCFG16
        case EE_ADC_PIN16:
            _PCFG16 = 0;
        break;
#endif
#ifdef _PCFG17
        case EE_ADC_PIN17:
            _PCFG17 = 0;
        break;
#endif
#ifdef _PCFG18
        case EE_ADC_PIN18:
            _PCFG18 = 0;
        break;
#endif
#ifdef _PCFG19
        case EE_ADC_PIN19:
            _PCFG19 = 0;
        break;
#endif
#ifdef _PCFG20
        case EE_ADC_PIN20:
            _PCFG20 = 0;
        break;
#endif
#ifdef _PCFG21
        case EE_ADC_PIN21:
            _PCFG21 = 0;
        break;
#endif
#ifdef _PCFG22
        case EE_ADC_PIN22:
            _PCFG22 = 0;
        break;
#endif
#ifdef _PCFG23
        case EE_ADC_PIN23:
            _PCFG23 = 0;
        break;
#endif
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

static EE_INT16 EE_adc2_init_ch_internal ( EE_AdcChId adc_ch_id )
{
    /* To Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_init_ch( EE_Adc_Coverter_Id adc_id, EE_AdcChId adc_ch_id )
{
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_init_ch_internal( adc_ch_id );
        break;
        case EE_ADC_2:
            error = EE_adc2_init_ch_internal( adc_ch_id );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

static EE_AdcErr EE_adc1_start_internal ( EE_Adc_VoltageRef volt_ref, EE_Adc_BitResolution bit_res )
{
    EE_INT16 error = EE_ADC_ERR_NO;
    if(_ADON == 0){
            /* Set control register 2 */
            /* Vref = AVcc/AVdd, Scan Inputs */
            _VCFG = volt_ref;
            /* Set bit resolution for ADC (10 or 12 bits) */
            _AD12B = bit_res;
            /*  Sample Clock Source Select bits 
                111 => Internal counter ends sampling and starts conversion (autosampling)
                Other configuration not supported because they depends on other periphereal
                (GP Timers, PWM, external pins)
            */
            _SSRC = 0x7;
            /* Input scan not supported by default */
            _CSCNA = 0; /* Input scan enable bit */
            AD1CSSL = 0x0000;  /* Channel selection register for input scan [none]*/
            #ifdef _CSS16
            AD1CSSH = 0x0000;
            #endif
            /*  1 => Sampling begins immediately after last conversion. SAMP bit is auto-set
                0 => Sampling begins when SAMP bit is set 
                We want trigger convertion with a function call so we put this at 0.
            */
            _ASAM = 0; /* ADC Sample Auto-Start bit */
            /* 
              1 => ADC internal RC clock
              0 => Clock derived from system clock */
            _ADRC = 0; /* ADC Conversion Clock Source bit */
            /* AST = value (e.g. 31) * Tad Tad: ADC clock period [if ARDC = 0 
               then periphereal clock]) used only if SSRC if autosampling is choose */
            _SAMC = 31; /* Auto Sample Time (AST) bits */
            /* 0011 1111 => TAD = (ADCS<7:0> + 1) · TCY = 64 · TCY 
               Not used if ADRC were = 1 */
            _ADCS = 0x003F; /* ADC Conversion Clock Select bits */
            /* reset ADC interrupt flag */
            _AD1IF = 0;
            /* disable ADC interrupts */
            _AD1IE = 0;
            /* turn on ADC module */
            _ADON = 1;
    }
    return error;
}

static EE_AdcErr EE_adc2_start_internal( EE_Adc_VoltageRef volt_ref, EE_Adc_BitResolution bit_res )
{
    /* To Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_start( EE_Adc_Coverter_Id adc_id, EE_Adc_VoltageRef volt_ref, EE_Adc_BitResolution bit_res ){
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_start_internal( volt_ref, bit_res);
        break;
        case EE_ADC_2:
            error = EE_adc2_start_internal( volt_ref, bit_res );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

static EE_AdcErr EE_adc1_stop_internal( void )
{
    /* turn off ADC module */
    _ADON = 0;
    return EE_ADC_ERR_NO;
}

static EE_AdcErr EE_adc2_stop_internal( void )
{
    /* To Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_stop( EE_Adc_Coverter_Id adc_id ){
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_stop_internal( );
        break;
        case EE_ADC_2:
            error = EE_adc2_stop_internal( );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

#define _adc_check_set(pcfgX, pinX) \
                if(pcfgX){\
                    error = EE_ADC_ERR_CHID_INVALID;\
                    break;\
                }\
                _CH0SA = pinX

static EE_AdcErr EE_adc1_get_ch_uint_internal( EE_AdcChId adc_ch_id, EE_UINT16 * value)
{
    EE_AdcErr error = EE_ADC_ERR_NO;
    if(_ADON == 0) {
        error = EE_ADC_ERR_DRIVER_UNINT; 
    } else {
        /* Set the data format to acquire as UINT (10 -12 bit) */
        EE_adc_set_sample_format(EE_ADC_UINT);
        /* Select channel to acquire */
        switch (adc_ch_id) {
#ifdef _PCFG0
            case EE_ADC_PIN0:
              _adc_check_set(_PCFG0, EE_ADC_PIN0);
            break;
#endif
#ifdef _PCFG1
            case EE_ADC_PIN1:
              _adc_check_set(_PCFG1, EE_ADC_PIN1);
            break;
#endif
#ifdef _PCFG2
            case EE_ADC_PIN2:
              _adc_check_set(_PCFG2, EE_ADC_PIN2);
            break;
#endif
#ifdef _PCFG3
            case EE_ADC_PIN3:
              _adc_check_set(_PCFG3, EE_ADC_PIN3);
            break;
#endif
#ifdef _PCFG4
            case EE_ADC_PIN4:
              _adc_check_set(_PCFG4, EE_ADC_PIN4);
            break;
#endif
#ifdef _PCFG5
            case EE_ADC_PIN5:
              _adc_check_set(_PCFG5, EE_ADC_PIN5);
            break;
#endif
#ifdef _PCFG6
            case EE_ADC_PIN6:
              _adc_check_set(_PCFG6, EE_ADC_PIN6);
            break;
#endif
#ifdef _PCFG7
            case EE_ADC_PIN7:
              _adc_check_set(_PCFG7, EE_ADC_PIN7);
            break;
#endif
#ifdef _PCFG8
            case EE_ADC_PIN8:
              _adc_check_set(_PCFG8, EE_ADC_PIN8);
            break;
#endif
#ifdef _PCFG9
            case EE_ADC_PIN9:
              _adc_check_set(_PCFG9, EE_ADC_PIN9);
            break;
#endif
#ifdef _PCFG10
            case EE_ADC_PIN10:
              _adc_check_set(_PCFG10, EE_ADC_PIN10);
            break;
#endif
#ifdef _PCFG11
            case EE_ADC_PIN11:
              _adc_check_set(_PCFG11, EE_ADC_PIN11);
            break;
#endif
#ifdef _PCFG12
            case EE_ADC_PIN12:
              _adc_check_set(_PCFG12, EE_ADC_PIN12);
            break;
#endif
#ifdef _PCFG13
            case EE_ADC_PIN13:
              _adc_check_set(_PCFG13, EE_ADC_PIN13);
            break;
#endif
#ifdef _PCFG14
            case EE_ADC_PIN14:
              _adc_check_set(_PCFG14, EE_ADC_PIN14);
            break;
#endif
#ifdef _PCFG15
            case EE_ADC_PIN15:
              _adc_check_set(_PCFG15, EE_ADC_PIN15);
            break;
#endif
#ifdef _PCFG16
            case EE_ADC_PIN16:
              _adc_check_set(_PCFG16, EE_ADC_PIN16);
            break;
#endif
#ifdef _PCFG17
            case EE_ADC_PIN17:
              _adc_check_set(_PCFG17, EE_ADC_PIN17);
            break;
#endif
#ifdef _PCFG18
            case EE_ADC_PIN18:
              _adc_check_set(_PCFG18, EE_ADC_PIN18);
            break;
#endif
#ifdef _PCFG19
            case EE_ADC_PIN19:
              _adc_check_set(_PCFG19, EE_ADC_PIN19);
            break;
#endif
#ifdef _PCFG20
            case EE_ADC_PIN20:
              _adc_check_set(_PCFG20, EE_ADC_PIN20);
            break;
#endif
#ifdef _PCFG21
            case EE_ADC_PIN21:
              _adc_check_set(_PCFG21, EE_ADC_PIN21);
            break;
#endif
#ifdef _PCFG22
            case EE_ADC_PIN22:
              _adc_check_set(_PCFG22, EE_ADC_PIN22);
            break;
#endif
#ifdef _PCFG23
            case EE_ADC_PIN23:
              _adc_check_set(_PCFG23, EE_ADC_PIN23);
            break;
#endif
            default:
              error = EE_ADC_ERR_CHID_INVALID;
        }
        if(error==EE_ADC_ERR_NO){
            /* Start sampling and conversion (auto-convert) */
            _DONE = 0; /* cleared by software */
            _SAMP = 1; /* start sampling, (cleared by ADC controller) */
            while(!_DONE){
                /* Wait till the EOC */
            }
            /* Acquire data */
            *value =  ADC1BUF0;
        }
    }
    return error;
}

static EE_AdcErr EE_adc2_get_ch_uint_internal( EE_AdcChId adc_ch_id, EE_UINT16 * value ){
    /* TO Be implemented */
    return EE_ADC_ERR_CHID_INVALID;
}

EE_AdcErr EE_adc_get_ch_uint( EE_Adc_Coverter_Id adc_id, EE_AdcChId adc_ch_id, EE_UINT16 * value ){
    EE_AdcErr error;
    switch( adc_id ){
        case EE_ADC_1:
            error = EE_adc1_get_ch_uint_internal( adc_ch_id, value );
        break;
        case EE_ADC_2:
            error = EE_adc2_get_ch_uint_internal( adc_ch_id, value );
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}



