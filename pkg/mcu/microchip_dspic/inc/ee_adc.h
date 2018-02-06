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
    @file   ee_adc.h
    @brief  This header contains a simple ADC driver. 
            Those API let you get a sample (right now only in uint16 format), 
            every time yoi invoke EE_adc_get_ch_uint. 
            The sample and conversion are executed inside the funtion call.
            Right now is not support buffer acquisition with DMA, neither 
            asynchronous acquisition with in ISR callback.
            Multiple channels sampling in 10 bits resolution is not 
            yet implemented.
    @author Errico Guidieri
    @date   2011
*/
 
#ifndef __INCLUDE_INCLUDE_MICROCHIP_DSPIC_ADC_H__
#define __INCLUDE_INCLUDE_MICROCHIP_DSPIC_ADC_H__

/******************************* 
Include device header
********************************/
#include "mcu/microchip_dspic/inc/ee_mcu.h"

#ifdef __USE_ADC__

/** Resolution levels for 12 bits ADC  **/
#define EE_ADC_RES_MIN  1024UL
/** Resolution levels for 12 bits ADC  **/
#define EE_ADC_RES_MAX  4096UL

#ifndef EE_ADC_VDD_mV
/** Internal voltage positive reference value **/
#define EE_ADC_VDD_mV  3300UL
#endif /* EE_ADC_VDD_mV */

#ifdef EE_ADC_VREF
/** External voltage positive reference value **/
#define EE_ADC_VREF    EE_ADC_VDD_mV
#endif /* EE_ADC_VREF */

/** 
    define for ADC analog input pins (_PCFGX)
    @{
**/  
#define EE_ADC_PIN0   0
#define EE_ADC_PIN1   1
#define EE_ADC_PIN2   2
#define EE_ADC_PIN3   3
#define EE_ADC_PIN4   4
#define EE_ADC_PIN5   5
#define EE_ADC_PIN6   6
#define EE_ADC_PIN7   7
#define EE_ADC_PIN8   8
#define EE_ADC_PIN9   9
#define EE_ADC_PIN10 10
#define EE_ADC_PIN11 11
#define EE_ADC_PIN12 12
#define EE_ADC_PIN13 13
#define EE_ADC_PIN14 14
#define EE_ADC_PIN15 15
#define EE_ADC_PIN16 16
#define EE_ADC_PIN17 17
#define EE_ADC_PIN18 18
#define EE_ADC_PIN19 19
#define EE_ADC_PIN20 20
#define EE_ADC_PIN21 21
#define EE_ADC_PIN22 22
#define EE_ADC_PIN23 23

/** 
    define for ADC channel's IDs and map it on default pins 
    (if are not defined yet. As should done in ee_board.h header)
    
    @{
**/

#ifndef EE_ADC_AN0
#define EE_ADC_AN0   EE_ADC_PIN0
#endif /* EE_ADC_AN0 */

#ifndef EE_ADC_AN1
#define EE_ADC_AN1   EE_ADC_PIN1
#endif /* EE_ADC_AN1 */

#ifndef EE_ADC_AN2
#define EE_ADC_AN2   EE_ADC_PIN2
#endif /* EE_ADC_AN2 */

#ifndef EE_ADC_AN3
#define EE_ADC_AN3   EE_ADC_PIN3
#endif /* EE_ADC_AN3 */

#ifndef EE_ADC_AN4
#define EE_ADC_AN4   EE_ADC_PIN4
#endif /* EE_ADC_AN4 */

#ifndef EE_ADC_AN5
#define EE_ADC_AN5   EE_ADC_PIN5
#endif /* EE_ADC_AN5 */

#ifndef EE_ADC_AN6
#define EE_ADC_AN6   EE_ADC_PIN6
#endif /* EE_ADC_AN6 */

#ifndef EE_ADC_AN7
#define EE_ADC_AN7   EE_ADC_PIN7
#endif /* EE_ADC_AN7 */

#ifndef EE_ADC_AN8
#define EE_ADC_AN8   EE_ADC_PIN8
#endif /* EE_ADC_AN8 */

#ifndef EE_ADC_AN9
#define EE_ADC_AN9   EE_ADC_PIN9
#endif /* EE_ADC_AN9 */

#ifndef EE_ADC_AN10
#define EE_ADC_AN10   EE_ADC_PIN10
#endif /* EE_ADC_AN10 */

#ifndef EE_ADC_AN11
#define EE_ADC_AN11   EE_ADC_PIN11
#endif /* EE_ADC_AN11 */

#ifndef EE_ADC_AN12
#define EE_ADC_AN12   EE_ADC_PIN12
#endif /* EE_ADC_AN12 */

#ifndef EE_ADC_AN13
#define EE_ADC_AN13   EE_ADC_PIN13
#endif /* EE_ADC_AN13 */

#ifndef EE_ADC_AN14
#define EE_ADC_AN14   EE_ADC_PIN14
#endif /* EE_ADC_AN14 */

#ifndef EE_ADC_AN15
#define EE_ADC_AN15   EE_ADC_PIN15
#endif /* EE_ADC_AN15 */

#ifndef EE_ADC_AN16
#define EE_ADC_AN16   EE_ADC_PIN16
#endif /* EE_ADC_AN16 */

#ifndef EE_ADC_AN17
#define EE_ADC_AN17   EE_ADC_PIN17
#endif /* EE_ADC_AN17 */

#ifndef EE_ADC_AN18
#define EE_ADC_AN18   EE_ADC_PIN18
#endif /* EE_ADC_AN18 */

#ifndef EE_ADC_AN19
#define EE_ADC_AN19   EE_ADC_PIN19
#endif /* EE_ADC_AN19 */

#ifndef EE_ADC_AN20
#define EE_ADC_AN20   EE_ADC_PIN20
#endif /* EE_ADC_AN20 */

#ifndef EE_ADC_AN21
#define EE_ADC_AN21   EE_ADC_PIN21
#endif /* EE_ADC_AN21 */

#ifndef EE_ADC_AN22
#define EE_ADC_AN22   EE_ADC_PIN22
#endif /* EE_ADC_AN22 */

#ifndef EE_ADC_AN23
#define EE_ADC_AN23   EE_ADC_PIN23
#endif /* EE_ADC_AN23 */

/** Error codes. 
    @{
**/
/** No errors happened **/
#define EE_ADC_ERR_NO             0 
/** Driver Unitialized **/
#define EE_ADC_ERR_DRIVER_UNINT  -1
/** Channel ID is invalid **/
#define EE_ADC_ERR_CHID_INVALID  -2
/** @} **/

/** Type for return errors value **/
typedef EE_INT16  EE_AdcErr;
/** Channel's ID type **/
typedef EE_UINT8  EE_AdcChId;

/** Enum for ADC converters **/
typedef enum EE_Adc_Coverter_Id_TAG {
    EE_ADC_1,
    EE_ADC_2,
} EE_Adc_Coverter_Id;

/**  
   Enum that configure reference for 
   AD conversion First name is positive reference second name 
   is negative reference).
   
   Vdd: Positive internal reference = dspic supply
   Vss: Negative internal reference = gnd
   VRefh: Positive external reference
   VRefl: Negative external reference
 **/
typedef enum EE_Adc_VoltageRef_TAG {
    EE_ADC_VDD_VSS     = 0x0,
    EE_ADC_VREFh_VSS   = 0x1,
    EE_ADC_VDD_VREFl   = 0x02,
    EE_ADC_VREFh_VREFl = 0x7
} EE_Adc_VoltageRef;

/** Enum for bit resolution **/
typedef enum EE_Adc_BitResolution_TAG {
    EE_ADC_10_BIT = 0,
    EE_ADC_12_BIT = 1
} EE_Adc_BitResolution;

/** @brief Initialize ADC driver.
    
    @param adc_id (EE_Adc_Coverter_Id): converter's ID
    @param adc_ch_id (EE_AdcChId): channel's ID to initialize
    @param volt_ref (EE_Adc_VoltageRef): a voltage reference pair enum values
    @param bit_res (EE_Adc_BitResolution): desired ADc bit resolution
    
    @return EE_ADC_ERR_NO if no errors happend. 
        Otherwise appropriate error value.
**/
EE_AdcErr EE_adc_init_ch(EE_Adc_Coverter_Id adc_id, EE_AdcChId adc_ch_id);

/**
    @brief Get channel value as uint 
    
    @param adc_id (EE_Adc_Coverter_Id): converter's ID
    @param adc_ch_id (EE_AdcChId): channel's ID to acquire.
    @param value  (EE_UINT16 *): return value pointer.
    
    @return EE_ADC_ERR_NO if no errors happend. 
        Otherwise appropriate error value.
**/
EE_AdcErr EE_adc_get_ch_uint(EE_Adc_Coverter_Id adc_id, EE_AdcChId adc_ch_id, EE_UINT16 * value );

/** 
    @brief Start ADC sampling 
    
    @param adc_id (EE_Adc_Coverter_Id): converter's ID to start
    
    @return EE_ADC_ERR_NO if no errors happend. 
        Otherwise appropriate error value.

 **/
EE_AdcErr EE_adc_start ( EE_Adc_Coverter_Id adc_id, EE_Adc_VoltageRef volt_ref, EE_Adc_BitResolution bit_res );

/** 
    @brief Stop ADC sampling 
    
    @param adc_id (EE_Adc_Coverter_Id): converter's ID to stop
    
    @return EE_ADC_ERR_NO if no errors happend. 
        Otherwise appropriate error value.

 **/
EE_AdcErr EE_adc_stop ( EE_Adc_Coverter_Id adc_id);

/** 
    @brief Set ADC behaviour for MCU idle state
    
    @param adc_id (EE_Adc_Coverter_Id): converter's ID to set idle behaviour to
    @param on (EE_UINT8): on flag
    
    @return EE_ADC_ERR_NO if no errors happend. 
        Otherwise appropriate error value.
**/
__INLINE__ EE_AdcErr EE_adc_set_idle_behaviour (EE_Adc_Coverter_Id adc_id, EE_UINT8 on ) {
    EE_AdcErr error = EE_ADC_ERR_NO ;
    switch ( adc_id ){
        case EE_ADC_1:
            /* 1 => Discontinue module operation when device enters Idle mode */
            _ADSIDL = (on) ? 0 : 1;
        break;
        case EE_ADC_2:
            /* TODO: implement this case */
        break;
        default:
            error = EE_ADC_ERR_CHID_INVALID;
    }
    return error;
}

#endif //__USE_ADC__

#endif //__INCLUDE_INCLUDE_MICROCHIP_DSPIC_ADC_H__
