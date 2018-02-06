/**
 * \file IfxVadc_regdef.h
 * \brief
 * \copyright Copyright (c) 2012 Infineon Technologies AG. All rights reserved.
 *
 *
 * $Revision: 1585 $
 * $Date: 2013-09-03 13:30:24 +0200 (Di, 03 Sep 2013) $
 *
 *                                 IMPORTANT NOTICE
 *
 *
 * Infineon Technologies AG (Infineon) is supplying this file for use
 * exclusively with Infineon's microcontroller products. This file can be freely
 * distributed within development tools that are supporting such microcontroller
 * products.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * \defgroup IfxLld_Vadc Vadc
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Vadc_Bitfields Bitfields
 * \ingroup IfxLld_Vadc
 * 
 * \defgroup IfxLld_Vadc_union Union
 * \ingroup IfxLld_Vadc
 * 
 * \defgroup IfxLld_Vadc_struct Struct
 * \ingroup IfxLld_Vadc
 * 
 */
#ifndef IFXVADC_REGDEF_H
#define IFXVADC_REGDEF_H
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Vadc_Bitfields
 * \{  */

/** \\brief  Access Enable Register 0 */
typedef struct _Ifx_VADC_ACCEN0_Bits
{
    unsigned int EN0:1;                     /**< \brief [0:0] Access Enable for Master TAG ID x (rw) */
    unsigned int EN1:1;                     /**< \brief [1:1] Access Enable for Master TAG ID x (rw) */
    unsigned int EN2:1;                     /**< \brief [2:2] Access Enable for Master TAG ID x (rw) */
    unsigned int EN3:1;                     /**< \brief [3:3] Access Enable for Master TAG ID x (rw) */
    unsigned int EN4:1;                     /**< \brief [4:4] Access Enable for Master TAG ID x (rw) */
    unsigned int EN5:1;                     /**< \brief [5:5] Access Enable for Master TAG ID x (rw) */
    unsigned int EN6:1;                     /**< \brief [6:6] Access Enable for Master TAG ID x (rw) */
    unsigned int EN7:1;                     /**< \brief [7:7] Access Enable for Master TAG ID x (rw) */
    unsigned int EN8:1;                     /**< \brief [8:8] Access Enable for Master TAG ID x (rw) */
    unsigned int EN9:1;                     /**< \brief [9:9] Access Enable for Master TAG ID x (rw) */
    unsigned int EN10:1;                    /**< \brief [10:10] Access Enable for Master TAG ID x (rw) */
    unsigned int EN11:1;                    /**< \brief [11:11] Access Enable for Master TAG ID x (rw) */
    unsigned int EN12:1;                    /**< \brief [12:12] Access Enable for Master TAG ID x (rw) */
    unsigned int EN13:1;                    /**< \brief [13:13] Access Enable for Master TAG ID x (rw) */
    unsigned int EN14:1;                    /**< \brief [14:14] Access Enable for Master TAG ID x (rw) */
    unsigned int EN15:1;                    /**< \brief [15:15] Access Enable for Master TAG ID x (rw) */
    unsigned int EN16:1;                    /**< \brief [16:16] Access Enable for Master TAG ID x (rw) */
    unsigned int EN17:1;                    /**< \brief [17:17] Access Enable for Master TAG ID x (rw) */
    unsigned int EN18:1;                    /**< \brief [18:18] Access Enable for Master TAG ID x (rw) */
    unsigned int EN19:1;                    /**< \brief [19:19] Access Enable for Master TAG ID x (rw) */
    unsigned int EN20:1;                    /**< \brief [20:20] Access Enable for Master TAG ID x (rw) */
    unsigned int EN21:1;                    /**< \brief [21:21] Access Enable for Master TAG ID x (rw) */
    unsigned int EN22:1;                    /**< \brief [22:22] Access Enable for Master TAG ID x (rw) */
    unsigned int EN23:1;                    /**< \brief [23:23] Access Enable for Master TAG ID x (rw) */
    unsigned int EN24:1;                    /**< \brief [24:24] Access Enable for Master TAG ID x (rw) */
    unsigned int EN25:1;                    /**< \brief [25:25] Access Enable for Master TAG ID x (rw) */
    unsigned int EN26:1;                    /**< \brief [26:26] Access Enable for Master TAG ID x (rw) */
    unsigned int EN27:1;                    /**< \brief [27:27] Access Enable for Master TAG ID x (rw) */
    unsigned int EN28:1;                    /**< \brief [28:28] Access Enable for Master TAG ID x (rw) */
    unsigned int EN29:1;                    /**< \brief [29:29] Access Enable for Master TAG ID x (rw) */
    unsigned int EN30:1;                    /**< \brief [30:30] Access Enable for Master TAG ID x (rw) */
    unsigned int EN31:1;                    /**< \brief [31:31] Access Enable for Master TAG ID x (rw) */
} Ifx_VADC_ACCEN0_Bits;

/** \\brief  Access Protection Register */
typedef struct _Ifx_VADC_ACCPROT0_Bits
{
    unsigned int APC0:1;                    /**< \brief [0:0] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC1:1;                    /**< \brief [1:1] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC2:1;                    /**< \brief [2:2] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC3:1;                    /**< \brief [3:3] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC4:1;                    /**< \brief [4:4] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC5:1;                    /**< \brief [5:5] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC6:1;                    /**< \brief [6:6] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC7:1;                    /**< \brief [7:7] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC8:1;                    /**< \brief [8:8] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC9:1;                    /**< \brief [9:9] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC10:1;                   /**< \brief [10:10] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC11:1;                   /**< \brief [11:11] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC12:1;                   /**< \brief [12:12] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC13:1;                   /**< \brief [13:13] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APC14:1;                   /**< \brief [14:14] Access Protection Channel Control, Group 0 - 14 (rw) */
    unsigned int APEM:1;                    /**< \brief [15:15] Access Protection External Multiplexer (rw) */
    unsigned int API0:1;                    /**< \brief [16:16] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API1:1;                    /**< \brief [17:17] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API2:1;                    /**< \brief [18:18] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API3:1;                    /**< \brief [19:19] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API4:1;                    /**< \brief [20:20] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API5:1;                    /**< \brief [21:21] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API6:1;                    /**< \brief [22:22] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API7:1;                    /**< \brief [23:23] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API8:1;                    /**< \brief [24:24] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API9:1;                    /**< \brief [25:25] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API10:1;                   /**< \brief [26:26] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API11:1;                   /**< \brief [27:27] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API12:1;                   /**< \brief [28:28] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API13:1;                   /**< \brief [29:29] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int API14:1;                   /**< \brief [30:30] Access Protection Initialization, Group 0 - 14 (rw) */
    unsigned int APGC:1;                    /**< \brief [31:31] Access Protection Global Configuration (rw) */
} Ifx_VADC_ACCPROT0_Bits;

/** \\brief  Access Protection Register */
typedef struct _Ifx_VADC_ACCPROT1_Bits
{
    unsigned int APS0:1;                    /**< \brief [0:0] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS1:1;                    /**< \brief [1:1] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS2:1;                    /**< \brief [2:2] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS3:1;                    /**< \brief [3:3] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS4:1;                    /**< \brief [4:4] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS5:1;                    /**< \brief [5:5] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS6:1;                    /**< \brief [6:6] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS7:1;                    /**< \brief [7:7] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS8:1;                    /**< \brief [8:8] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS9:1;                    /**< \brief [9:9] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS10:1;                   /**< \brief [10:10] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS11:1;                   /**< \brief [11:11] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS12:1;                   /**< \brief [12:12] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS13:1;                   /**< \brief [13:13] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APS14:1;                   /**< \brief [14:14] Access Protection Service Request, Group 0 - 14 (rw) */
    unsigned int APTF:1;                    /**< \brief [15:15] Access Protection Test Function (rw) */
    unsigned int APR0:1;                    /**< \brief [16:16] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR1:1;                    /**< \brief [17:17] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR2:1;                    /**< \brief [18:18] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR3:1;                    /**< \brief [19:19] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR4:1;                    /**< \brief [20:20] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR5:1;                    /**< \brief [21:21] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR6:1;                    /**< \brief [22:22] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR7:1;                    /**< \brief [23:23] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR8:1;                    /**< \brief [24:24] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR9:1;                    /**< \brief [25:25] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR10:1;                   /**< \brief [26:26] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR11:1;                   /**< \brief [27:27] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR12:1;                   /**< \brief [28:28] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR13:1;                   /**< \brief [29:29] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int APR14:1;                   /**< \brief [30:30] Access Protection Result Registers, Group 0 - 14 (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_VADC_ACCPROT1_Bits;

/** \\brief  Background Request Source Control Register */
typedef struct _Ifx_VADC_BRSCTRL_Bits
{
    unsigned int SRCRESREG:4;               /**< \brief [3:0] Source-specific Result Register (rw) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int XTSEL:4;                   /**< \brief [11:8] External Trigger Input Selection (rw) */
    unsigned int XTLVL:1;                   /**< \brief [12:12] External Trigger Level (rh) */
    unsigned int XTMODE:2;                  /**< \brief [14:13] Trigger Operating Mode (rw) */
    unsigned int XTWC:1;                    /**< \brief [15:15] Write Control for Trigger Configuration (w) */
    unsigned int GTSEL:4;                   /**< \brief [19:16] Gate Input Selection (rw) */
    unsigned int GTLVL:1;                   /**< \brief [20:20] Gate Input Level (rh) */
    unsigned int reserved_21:2;             /**< \brief \internal Reserved */
    unsigned int GTWC:1;                    /**< \brief [23:23] Write Control for Gate Configuration (w) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_VADC_BRSCTRL_Bits;

/** \\brief  Background Request Source Mode Register */
typedef struct _Ifx_VADC_BRSMR_Bits
{
    unsigned int ENGT:2;                    /**< \brief [1:0] Enable Gate (rw) */
    unsigned int ENTR:1;                    /**< \brief [2:2] Enable External Trigger (rw) */
    unsigned int ENSI:1;                    /**< \brief [3:3] Enable Source Interrupt (rw) */
    unsigned int SCAN:1;                    /**< \brief [4:4] Autoscan Enable (rw) */
    unsigned int LDM:1;                     /**< \brief [5:5] Autoscan Source Load Event Mode (rw) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int REQGT:1;                   /**< \brief [7:7] Request Gate Level (rh) */
    unsigned int CLRPND:1;                  /**< \brief [8:8] Clear Pending Bits (w) */
    unsigned int LDEV:1;                    /**< \brief [9:9] Generate Load Event (w) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int RPTDIS:1;                  /**< \brief [16:16] Repeat Disable (rw) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_VADC_BRSMR_Bits;

/** \\brief  Background Request Source Pending Register, Group */
typedef struct _Ifx_VADC_BRSPND_Bits
{
    unsigned int CHPNDGy:32;                /**< \brief [31:0] Channels Pending Group x (rw) */
} Ifx_VADC_BRSPND_Bits;

/** \\brief  Background Request Source Channel Select Register, Group */
typedef struct _Ifx_VADC_BRSSEL_Bits
{
    unsigned int CHSELGy:32;                /**< \brief [31:0] Channel Selection Group x (rw) */
} Ifx_VADC_BRSSEL_Bits;

/** \\brief  Group, Channel Ctrl. Reg. */
typedef struct _Ifx_VADC_CHCTR_Bits
{
    unsigned int ICLSEL:2;                  /**< \brief [1:0] Input Class Select (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int BNDSELL:2;                 /**< \brief [5:4] Lower Boundary SelectWhile BNDSELX ≠ 0000, bitfields BNDSELU and BNDSELL are concatenated and select the corresponding result register as lower boundary. (rw) */
    unsigned int BNDSELU:2;                 /**< \brief [7:6] Upper Boundary Select (rw) */
    unsigned int CHEVMODE:2;                /**< \brief [9:8] Channel Event Mode (rw) */
    unsigned int SYNC:1;                    /**< \brief [10:10] Synchronization Request (rw) */
    unsigned int REFSEL:1;                  /**< \brief [11:11] Reference Input Selection (rw) */
    unsigned int BNDSELX:4;                 /**< \brief [15:12] BoundaryExtension (rw) */
    unsigned int RESREG:4;                  /**< \brief [19:16] Result Register (rw) */
    unsigned int RESTBS:1;                  /**< \brief [20:20] Result Target for Background Source (rw) */
    unsigned int RESPOS:1;                  /**< \brief [21:21] Result Position (rw) */
    unsigned int reserved_22:6;             /**< \brief \internal Reserved */
    unsigned int BWDCH:2;                   /**< \brief [29:28] Broken Wire Detection Channel (rw) */
    unsigned int BWDEN:1;                   /**< \brief [30:30] Broken Wire Detection Enable (rw) */
    unsigned int reserved_31:1;             /**< \brief \internal Reserved */
} Ifx_VADC_CHCTR_Bits;

/** \\brief  Clock Control Register */
typedef struct _Ifx_VADC_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module Disable Status Bit (r) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int EDIS:1;                    /**< \brief [3:3] Sleep Mode Enable Control (rw) */
    unsigned int reserved_4:28;             /**< \brief \internal Reserved */
} Ifx_VADC_CLC_Bits;

/** \\brief  External Multiplexer Select Register */
typedef struct _Ifx_VADC_EMUXSEL_Bits
{
    unsigned int EMUXGRP0:4;                /**< \brief [3:0] External Multiplexer Group for Interface x (rw) */
    unsigned int EMUXGRP1:4;                /**< \brief [7:4] External Multiplexer Group for Interface x (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_VADC_EMUXSEL_Bits;

/** \\brief  Alias Register, Group */
typedef struct _Ifx_VADC_G_ALIAS_Bits
{
    unsigned int ALIAS0:5;                  /**< \brief [4:0] Alias Value for CH0 Conversion Requests (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int ALIAS1:5;                  /**< \brief [12:8] Alias Value for CH1 Conversion Requests (rw) */
    unsigned int reserved_13:19;            /**< \brief \internal Reserved */
} Ifx_VADC_G_ALIAS_Bits;

/** \\brief  Arbitration Configuration Register, Group */
typedef struct _Ifx_VADC_G_ARBCFG_Bits
{
    unsigned int ANONC:2;                   /**< \brief [1:0] Analog Converter Control (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int ARBRND:2;                  /**< \brief [5:4] Arbitration Round Length (rw) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int ARBM:1;                    /**< \brief [7:7] Arbitration Mode (rw) */
    unsigned int reserved_8:8;              /**< \brief \internal Reserved */
    unsigned int ANONS:2;                   /**< \brief [17:16] Analog Converter Control Status (rh) */
    unsigned int CSRC:2;                    /**< \brief [19:18] Currently Converted Request Source (rh) */
    unsigned int CHNR:5;                    /**< \brief [24:20] Channel Number (rh) */
    unsigned int SYNRUN:1;                  /**< \brief [25:25] Synchronous Conversion Running (rh) */
    unsigned int reserved_26:2;             /**< \brief \internal Reserved */
    unsigned int CAL:1;                     /**< \brief [28:28] Start-Up Calibration Active Indication (rh) */
    unsigned int CALS:1;                    /**< \brief [29:29] Start-Up Calibration Started (rh) */
    unsigned int BUSY:1;                    /**< \brief [30:30] Converter Busy Flag (rh) */
    unsigned int SAMPLE:1;                  /**< \brief [31:31] Sample Phase Flag (rh) */
} Ifx_VADC_G_ARBCFG_Bits;

/** \\brief  Arbitration Priority Register, Group */
typedef struct _Ifx_VADC_G_ARBPR_Bits
{
    unsigned int PRIO0:2;                   /**< \brief [1:0] Priority of Request Source x (rw) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int CSM0:1;                    /**< \brief [3:3] Conversion Start Mode of Request Source x (rw) */
    unsigned int PRIO1:2;                   /**< \brief [5:4] Priority of Request Source x (rw) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int CSM1:1;                    /**< \brief [7:7] Conversion Start Mode of Request Source x (rw) */
    unsigned int PRIO2:2;                   /**< \brief [9:8] Priority of Request Source x (rw) */
    unsigned int reserved_10:1;             /**< \brief \internal Reserved */
    unsigned int CSM2:1;                    /**< \brief [11:11] Conversion Start Mode of Request Source x (rw) */
    unsigned int reserved_12:12;            /**< \brief \internal Reserved */
    unsigned int ASEN0:1;                   /**< \brief [24:24] Arbitration Slot y Enable (rw) */
    unsigned int ASEN1:1;                   /**< \brief [25:25] Arbitration Slot y Enable (rw) */
    unsigned int ASEN2:1;                   /**< \brief [26:26] Arbitration Slot y Enable (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_VADC_G_ARBPR_Bits;

/** \\brief  Autoscan Source Control Register, Group */
typedef struct _Ifx_VADC_G_ASCTRL_Bits
{
    unsigned int SRCRESREG:4;               /**< \brief [3:0] Source-specific Result Register (rw) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int XTSEL:4;                   /**< \brief [11:8] External Trigger Input Selection (rw) */
    unsigned int XTLVL:1;                   /**< \brief [12:12] External Trigger Level (rh) */
    unsigned int XTMODE:2;                  /**< \brief [14:13] Trigger Operating Mode (rw) */
    unsigned int XTWC:1;                    /**< \brief [15:15] Write Control for Trigger Configuration (w) */
    unsigned int GTSEL:4;                   /**< \brief [19:16] Gate Input Selection (rw) */
    unsigned int GTLVL:1;                   /**< \brief [20:20] Gate Input Level (rh) */
    unsigned int reserved_21:2;             /**< \brief \internal Reserved */
    unsigned int GTWC:1;                    /**< \brief [23:23] Write Control for Gate Configuration (w) */
    unsigned int reserved_24:4;             /**< \brief \internal Reserved */
    unsigned int TMEN:1;                    /**< \brief [28:28] Timer Mode Enable (rw) */
    unsigned int reserved_29:2;             /**< \brief \internal Reserved */
    unsigned int TMWC:1;                    /**< \brief [31:31] Write Control for Timer Mode (w) */
} Ifx_VADC_G_ASCTRL_Bits;

/** \\brief  Autoscan Source Mode Register, Group */
typedef struct _Ifx_VADC_G_ASMR_Bits
{
    unsigned int ENGT:2;                    /**< \brief [1:0] Enable Gate (rw) */
    unsigned int ENTR:1;                    /**< \brief [2:2] Enable External Trigger (rw) */
    unsigned int ENSI:1;                    /**< \brief [3:3] Enable Source Interrupt (rw) */
    unsigned int SCAN:1;                    /**< \brief [4:4] Autoscan Enable (rw) */
    unsigned int LDM:1;                     /**< \brief [5:5] Autoscan Source Load Event Mode (rw) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int REQGT:1;                   /**< \brief [7:7] Request Gate Level (rh) */
    unsigned int CLRPND:1;                  /**< \brief [8:8] Clear Pending Bits (w) */
    unsigned int LDEV:1;                    /**< \brief [9:9] Generate Load Event (w) */
    unsigned int reserved_10:6;             /**< \brief \internal Reserved */
    unsigned int RPTDIS:1;                  /**< \brief [16:16] Repeat Disable (rw) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_VADC_G_ASMR_Bits;

/** \\brief  Autoscan Source Pending Register, Group */
typedef struct _Ifx_VADC_G_ASPND_Bits
{
    unsigned int CHPND:32;                  /**< \brief [31:0] Channels Pending (rw) */
} Ifx_VADC_G_ASPND_Bits;

/** \\brief  Autoscan Source Channel Select Register, Group */
typedef struct _Ifx_VADC_G_ASSEL_Bits
{
    unsigned int CHSEL:32;                  /**< \brief [31:0] Channel Selection (rw) */
} Ifx_VADC_G_ASSEL_Bits;

/** \\brief  Boundary Flag Register, Group */
typedef struct _Ifx_VADC_G_BFL_Bits
{
    unsigned int BFL0:1;                    /**< \brief [0:0] Boundary Flag y (rh) */
    unsigned int BFL1:1;                    /**< \brief [1:1] Boundary Flag y (rh) */
    unsigned int BFL2:1;                    /**< \brief [2:2] Boundary Flag y (rh) */
    unsigned int BFL3:1;                    /**< \brief [3:3] Boundary Flag y (rh) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int BFA0:1;                    /**< \brief [8:8] Boundary Flag y Activation Select (rw) */
    unsigned int BFA1:1;                    /**< \brief [9:9] Boundary Flag y Activation Select (rw) */
    unsigned int BFA2:1;                    /**< \brief [10:10] Boundary Flag y Activation Select (rw) */
    unsigned int BFA3:1;                    /**< \brief [11:11] Boundary Flag y Activation Select (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int BFI0:1;                    /**< \brief [16:16] Boundary Flag y Inversion Control (rw) */
    unsigned int BFI1:1;                    /**< \brief [17:17] Boundary Flag y Inversion Control (rw) */
    unsigned int BFI2:1;                    /**< \brief [18:18] Boundary Flag y Inversion Control (rw) */
    unsigned int BFI3:1;                    /**< \brief [19:19] Boundary Flag y Inversion Control (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_VADC_G_BFL_Bits;

/** \\brief  Boundary Flag Control Register, Group */
typedef struct _Ifx_VADC_G_BFLC_Bits
{
    unsigned int BFM0:4;                    /**< \brief [3:0] Boundary Flag y Mode Control (rw) */
    unsigned int BFM1:4;                    /**< \brief [7:4] Boundary Flag y Mode Control (rw) */
    unsigned int BFM2:4;                    /**< \brief [11:8] Boundary Flag y Mode Control (rw) */
    unsigned int BFM3:4;                    /**< \brief [15:12] Boundary Flag y Mode Control (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_BFLC_Bits;

/** \\brief  Boundary Flag Node Pointer Register, Group */
typedef struct _Ifx_VADC_G_BFLNP_Bits
{
    unsigned int BFL0NP:4;                  /**< \brief [3:0] Boundary Flag y Node Pointer (rw) */
    unsigned int BFL1NP:4;                  /**< \brief [7:4] Boundary Flag y Node Pointer (rw) */
    unsigned int BFL2NP:4;                  /**< \brief [11:8] Boundary Flag y Node Pointer (rw) */
    unsigned int BFL3NP:4;                  /**< \brief [15:12] Boundary Flag y Node Pointer (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_BFLNP_Bits;

/** \\brief  Boundary Flag Software Register, Group */
typedef struct _Ifx_VADC_G_BFLS_Bits
{
    unsigned int BFC0:1;                    /**< \brief [0:0] Boundary Flag y Clear (w) */
    unsigned int BFC1:1;                    /**< \brief [1:1] Boundary Flag y Clear (w) */
    unsigned int BFC2:1;                    /**< \brief [2:2] Boundary Flag y Clear (w) */
    unsigned int BFC3:1;                    /**< \brief [3:3] Boundary Flag y Clear (w) */
    unsigned int reserved_4:12;             /**< \brief \internal Reserved */
    unsigned int BFS0:1;                    /**< \brief [16:16] Boundary Flag y Set (w) */
    unsigned int BFS1:1;                    /**< \brief [17:17] Boundary Flag y Set (w) */
    unsigned int BFS2:1;                    /**< \brief [18:18] Boundary Flag y Set (w) */
    unsigned int BFS3:1;                    /**< \brief [19:19] Boundary Flag y Set (w) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_VADC_G_BFLS_Bits;

/** \\brief  Boundary Select Register, Group */
typedef struct _Ifx_VADC_G_BOUND_Bits
{
    unsigned int BOUNDARY0:12;              /**< \brief [11:0] Boundary Value 0 for Limit Checking (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int BOUNDARY1:12;              /**< \brief [27:16] Boundary Value 1 for Limit Checking (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_VADC_G_BOUND_Bits;

/** \\brief  Channel Event Flag Clear Register, Group */
typedef struct _Ifx_VADC_G_CEFCLR_Bits
{
    unsigned int CEV0:1;                    /**< \brief [0:0] Clear Channel Event for Channel y (w) */
    unsigned int CEV1:1;                    /**< \brief [1:1] Clear Channel Event for Channel y (w) */
    unsigned int CEV2:1;                    /**< \brief [2:2] Clear Channel Event for Channel y (w) */
    unsigned int CEV3:1;                    /**< \brief [3:3] Clear Channel Event for Channel y (w) */
    unsigned int CEV4:1;                    /**< \brief [4:4] Clear Channel Event for Channel y (w) */
    unsigned int CEV5:1;                    /**< \brief [5:5] Clear Channel Event for Channel y (w) */
    unsigned int CEV6:1;                    /**< \brief [6:6] Clear Channel Event for Channel y (w) */
    unsigned int CEV7:1;                    /**< \brief [7:7] Clear Channel Event for Channel y (w) */
    unsigned int CEV8:1;                    /**< \brief [8:8] Clear Channel Event for Channel y (w) */
    unsigned int CEV9:1;                    /**< \brief [9:9] Clear Channel Event for Channel y (w) */
    unsigned int CEV10:1;                   /**< \brief [10:10] Clear Channel Event for Channel y (w) */
    unsigned int CEV11:1;                   /**< \brief [11:11] Clear Channel Event for Channel y (w) */
    unsigned int CEV12:1;                   /**< \brief [12:12] Clear Channel Event for Channel y (w) */
    unsigned int CEV13:1;                   /**< \brief [13:13] Clear Channel Event for Channel y (w) */
    unsigned int CEV14:1;                   /**< \brief [14:14] Clear Channel Event for Channel y (w) */
    unsigned int CEV15:1;                   /**< \brief [15:15] Clear Channel Event for Channel y (w) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_CEFCLR_Bits;

/** \\brief  Channel Event Flag Register, Group */
typedef struct _Ifx_VADC_G_CEFLAG_Bits
{
    unsigned int CEV0:1;                    /**< \brief [0:0] Channel Event for Channel y (rwh) */
    unsigned int CEV1:1;                    /**< \brief [1:1] Channel Event for Channel y (rwh) */
    unsigned int CEV2:1;                    /**< \brief [2:2] Channel Event for Channel y (rwh) */
    unsigned int CEV3:1;                    /**< \brief [3:3] Channel Event for Channel y (rwh) */
    unsigned int CEV4:1;                    /**< \brief [4:4] Channel Event for Channel y (rwh) */
    unsigned int CEV5:1;                    /**< \brief [5:5] Channel Event for Channel y (rwh) */
    unsigned int CEV6:1;                    /**< \brief [6:6] Channel Event for Channel y (rwh) */
    unsigned int CEV7:1;                    /**< \brief [7:7] Channel Event for Channel y (rwh) */
    unsigned int CEV8:1;                    /**< \brief [8:8] Channel Event for Channel y (rwh) */
    unsigned int CEV9:1;                    /**< \brief [9:9] Channel Event for Channel y (rwh) */
    unsigned int CEV10:1;                   /**< \brief [10:10] Channel Event for Channel y (rwh) */
    unsigned int CEV11:1;                   /**< \brief [11:11] Channel Event for Channel y (rwh) */
    unsigned int CEV12:1;                   /**< \brief [12:12] Channel Event for Channel y (rwh) */
    unsigned int CEV13:1;                   /**< \brief [13:13] Channel Event for Channel y (rwh) */
    unsigned int CEV14:1;                   /**< \brief [14:14] Channel Event for Channel y (rwh) */
    unsigned int CEV15:1;                   /**< \brief [15:15] Channel Event for Channel y (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_CEFLAG_Bits;

/** \\brief  Channel Event Node Pointer Register 0, Group */
typedef struct _Ifx_VADC_G_CEVNP0_Bits
{
    unsigned int CEV0NP:4;                  /**< \brief [3:0] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV1NP:4;                  /**< \brief [7:4] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV2NP:4;                  /**< \brief [11:8] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV3NP:4;                  /**< \brief [15:12] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV4NP:4;                  /**< \brief [19:16] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV5NP:4;                  /**< \brief [23:20] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV6NP:4;                  /**< \brief [27:24] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV7NP:4;                  /**< \brief [31:28] Service Request Node Pointer Channel Event i (rw) */
} Ifx_VADC_G_CEVNP0_Bits;

/** \\brief  Channel Event Node Pointer Register 1, Group */
typedef struct _Ifx_VADC_G_CEVNP1_Bits
{
    unsigned int CEV8NP:4;                  /**< \brief [3:0] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV9NP:4;                  /**< \brief [7:4] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV10NP:4;                 /**< \brief [11:8] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV11NP:4;                 /**< \brief [15:12] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV12NP:4;                 /**< \brief [19:16] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV13NP:4;                 /**< \brief [23:20] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV14NP:4;                 /**< \brief [27:24] Service Request Node Pointer Channel Event i (rw) */
    unsigned int CEV15NP:4;                 /**< \brief [31:28] Service Request Node Pointer Channel Event i (rw) */
} Ifx_VADC_G_CEVNP1_Bits;

/** \\brief  Channel Assignment Register, Group */
typedef struct _Ifx_VADC_G_CHASS_Bits
{
    unsigned int ASSCH0:1;                  /**< \brief [0:0] Assignment for Channel y (rw) */
    unsigned int ASSCH1:1;                  /**< \brief [1:1] Assignment for Channel y (rw) */
    unsigned int ASSCH2:1;                  /**< \brief [2:2] Assignment for Channel y (rw) */
    unsigned int ASSCH3:1;                  /**< \brief [3:3] Assignment for Channel y (rw) */
    unsigned int ASSCH4:1;                  /**< \brief [4:4] Assignment for Channel y (rw) */
    unsigned int ASSCH5:1;                  /**< \brief [5:5] Assignment for Channel y (rw) */
    unsigned int ASSCH6:1;                  /**< \brief [6:6] Assignment for Channel y (rw) */
    unsigned int ASSCH7:1;                  /**< \brief [7:7] Assignment for Channel y (rw) */
    unsigned int ASSCH8:1;                  /**< \brief [8:8] Assignment for Channel y (rw) */
    unsigned int ASSCH9:1;                  /**< \brief [9:9] Assignment for Channel y (rw) */
    unsigned int ASSCH10:1;                 /**< \brief [10:10] Assignment for Channel y (rw) */
    unsigned int ASSCH11:1;                 /**< \brief [11:11] Assignment for Channel y (rw) */
    unsigned int ASSCH12:1;                 /**< \brief [12:12] Assignment for Channel y (rw) */
    unsigned int ASSCH13:1;                 /**< \brief [13:13] Assignment for Channel y (rw) */
    unsigned int ASSCH14:1;                 /**< \brief [14:14] Assignment for Channel y (rw) */
    unsigned int ASSCH15:1;                 /**< \brief [15:15] Assignment for Channel y (rw) */
    unsigned int ASSCH16:1;                 /**< \brief [16:16] Assignment for Channel y (rw) */
    unsigned int ASSCH17:1;                 /**< \brief [17:17] Assignment for Channel y (rw) */
    unsigned int ASSCH18:1;                 /**< \brief [18:18] Assignment for Channel y (rw) */
    unsigned int ASSCH19:1;                 /**< \brief [19:19] Assignment for Channel y (rw) */
    unsigned int ASSCH20:1;                 /**< \brief [20:20] Assignment for Channel y (rw) */
    unsigned int ASSCH21:1;                 /**< \brief [21:21] Assignment for Channel y (rw) */
    unsigned int ASSCH22:1;                 /**< \brief [22:22] Assignment for Channel y (rw) */
    unsigned int ASSCH23:1;                 /**< \brief [23:23] Assignment for Channel y (rw) */
    unsigned int ASSCH24:1;                 /**< \brief [24:24] Assignment for Channel y (rw) */
    unsigned int ASSCH25:1;                 /**< \brief [25:25] Assignment for Channel y (rw) */
    unsigned int ASSCH26:1;                 /**< \brief [26:26] Assignment for Channel y (rw) */
    unsigned int ASSCH27:1;                 /**< \brief [27:27] Assignment for Channel y (rw) */
    unsigned int ASSCH28:1;                 /**< \brief [28:28] Assignment for Channel y (rw) */
    unsigned int ASSCH29:1;                 /**< \brief [29:29] Assignment for Channel y (rw) */
    unsigned int ASSCH30:1;                 /**< \brief [30:30] Assignment for Channel y (rw) */
    unsigned int ASSCH31:1;                 /**< \brief [31:31] Assignment for Channel y (rw) */
} Ifx_VADC_G_CHASS_Bits;

/** \\brief  External Multiplexer Control Register, Group x */
typedef struct _Ifx_VADC_G_EMUXCTR_Bits
{
    unsigned int EMUXSET:3;                 /**< \brief [2:0] External Multiplexer Start SelectionFor single-step mode and sequence mode: Select the start value before selecting the respective mode. (rw) */
    unsigned int reserved_3:5;              /**< \brief \internal Reserved */
    unsigned int EMUXACT:3;                 /**< \brief [10:8] External Multiplexer Actual Selection (rh) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int EMUXCH:10;                 /**< \brief [25:16] External Multiplexer Channel Select (rw) */
    unsigned int EMUXMODE:2;                /**< \brief [27:26] External Multiplexer Mode (rw) */
    unsigned int EMXCOD:1;                  /**< \brief [28:28] External Multiplexer Coding Scheme (rw) */
    unsigned int EMXST:1;                   /**< \brief [29:29] External Multiplexer Sample Time Control (rw) */
    unsigned int EMXCSS:1;                  /**< \brief [30:30] External Multiplexer Channel Selection Style (r) */
    unsigned int EMXWC:1;                   /**< \brief [31:31] Write Control for EMUX Configuration (w) */
} Ifx_VADC_G_EMUXCTR_Bits;

/** \\brief  Queue 0 Register 0, Group */
typedef struct _Ifx_VADC_G_Q0R0_Bits
{
    unsigned int REQCHNR:5;                 /**< \brief [4:0] Request Channel Number (rh) */
    unsigned int RF:1;                      /**< \brief [5:5] Refill (rh) */
    unsigned int ENSI:1;                    /**< \brief [6:6] Enable Source Interrupt (rh) */
    unsigned int EXTR:1;                    /**< \brief [7:7] External Trigger (rh) */
    unsigned int V:1;                       /**< \brief [8:8] Request Channel Number Valid (rh) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_VADC_G_Q0R0_Bits;

/** \\brief  Queue 0 Backup Register, Group */
typedef struct _Ifx_VADC_G_QBUR_QINR0_QBUR0_Bits
{
    unsigned int REQCHNR:5;                 /**< \brief [4:0] Request Channel Number (rh) */
    unsigned int RF:1;                      /**< \brief [5:5] Refill (rh) */
    unsigned int ENSI:1;                    /**< \brief [6:6] Enable Source Interrupt (rh) */
    unsigned int EXTR:1;                    /**< \brief [7:7] External Trigger (rh) */
    unsigned int V:1;                       /**< \brief [8:8] Request Channel Number Valid (rh) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_VADC_G_QBUR_QINR0_QBUR0_Bits;

/** \\brief  Queue 0 Input Register, Group */
typedef struct _Ifx_VADC_G_QBUR_QINR0_QINR0_Bits
{
    unsigned int REQCHNR:5;                 /**< \brief [4:0] Request Channel Number (w) */
    unsigned int RF:1;                      /**< \brief [5:5] Refill (w) */
    unsigned int ENSI:1;                    /**< \brief [6:6] Enable Source Interrupt (w) */
    unsigned int EXTR:1;                    /**< \brief [7:7] External Trigger (w) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_VADC_G_QBUR_QINR0_QINR0_Bits;

/** \\brief  Queue 0 Source Control Register, Group */
typedef struct _Ifx_VADC_G_QCTRL0_Bits
{
    unsigned int SRCRESREG:4;               /**< \brief [3:0] Source-specific Result Register (rw) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int XTSEL:4;                   /**< \brief [11:8] External Trigger Input Selection (rw) */
    unsigned int XTLVL:1;                   /**< \brief [12:12] External Trigger Level (rh) */
    unsigned int XTMODE:2;                  /**< \brief [14:13] Trigger Operating Mode (rw) */
    unsigned int XTWC:1;                    /**< \brief [15:15] Write Control for Trigger Configuration (w) */
    unsigned int GTSEL:4;                   /**< \brief [19:16] Gate Input Selection (rw) */
    unsigned int GTLVL:1;                   /**< \brief [20:20] Gate Input Level (rh) */
    unsigned int reserved_21:2;             /**< \brief \internal Reserved */
    unsigned int GTWC:1;                    /**< \brief [23:23] Write Control for Gate Configuration (w) */
    unsigned int reserved_24:4;             /**< \brief \internal Reserved */
    unsigned int TMEN:1;                    /**< \brief [28:28] Timer Mode Enable (rw) */
    unsigned int reserved_29:2;             /**< \brief \internal Reserved */
    unsigned int TMWC:1;                    /**< \brief [31:31] Write Control for Timer Mode (w) */
} Ifx_VADC_G_QCTRL0_Bits;

/** \\brief  Queue 0 Mode Register, Group */
typedef struct _Ifx_VADC_G_QMR0_Bits
{
    unsigned int ENGT:2;                    /**< \brief [1:0] Enable Gate (rw) */
    unsigned int ENTR:1;                    /**< \brief [2:2] Enable External Trigger (rw) */
    unsigned int reserved_3:5;              /**< \brief \internal Reserved */
    unsigned int CLRV:1;                    /**< \brief [8:8] Clear Valid Bit (w) */
    unsigned int TREV:1;                    /**< \brief [9:9] Trigger Event (w) */
    unsigned int FLUSH:1;                   /**< \brief [10:10] Flush Queue (w) */
    unsigned int CEV:1;                     /**< \brief [11:11] Clear Event Flag (w) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int RPTDIS:1;                  /**< \brief [16:16] Repeat Disable (rw) */
    unsigned int reserved_17:15;            /**< \brief \internal Reserved */
} Ifx_VADC_G_QMR0_Bits;

/** \\brief  Queue 0 Status Register, Group */
typedef struct _Ifx_VADC_G_QSR0_Bits
{
    unsigned int FILL:4;                    /**< \brief [3:0] Filling Level for Queue (rh) */
    unsigned int reserved_4:1;              /**< \brief \internal Reserved */
    unsigned int EMPTY:1;                   /**< \brief [5:5] Queue Empty (rh) */
    unsigned int reserved_6:1;              /**< \brief \internal Reserved */
    unsigned int REQGT:1;                   /**< \brief [7:7] Request Gate Level (rh) */
    unsigned int EV:1;                      /**< \brief [8:8] Event Detected (rh) */
    unsigned int reserved_9:23;             /**< \brief \internal Reserved */
} Ifx_VADC_G_QSR0_Bits;

/** \\brief  Result Event Flag Clear Register, Group */
typedef struct _Ifx_VADC_G_REFCLR_Bits
{
    unsigned int REV0:1;                    /**< \brief [0:0] Clear Result Event for Result Register y (w) */
    unsigned int REV1:1;                    /**< \brief [1:1] Clear Result Event for Result Register y (w) */
    unsigned int REV2:1;                    /**< \brief [2:2] Clear Result Event for Result Register y (w) */
    unsigned int REV3:1;                    /**< \brief [3:3] Clear Result Event for Result Register y (w) */
    unsigned int REV4:1;                    /**< \brief [4:4] Clear Result Event for Result Register y (w) */
    unsigned int REV5:1;                    /**< \brief [5:5] Clear Result Event for Result Register y (w) */
    unsigned int REV6:1;                    /**< \brief [6:6] Clear Result Event for Result Register y (w) */
    unsigned int REV7:1;                    /**< \brief [7:7] Clear Result Event for Result Register y (w) */
    unsigned int REV8:1;                    /**< \brief [8:8] Clear Result Event for Result Register y (w) */
    unsigned int REV9:1;                    /**< \brief [9:9] Clear Result Event for Result Register y (w) */
    unsigned int REV10:1;                   /**< \brief [10:10] Clear Result Event for Result Register y (w) */
    unsigned int REV11:1;                   /**< \brief [11:11] Clear Result Event for Result Register y (w) */
    unsigned int REV12:1;                   /**< \brief [12:12] Clear Result Event for Result Register y (w) */
    unsigned int REV13:1;                   /**< \brief [13:13] Clear Result Event for Result Register y (w) */
    unsigned int REV14:1;                   /**< \brief [14:14] Clear Result Event for Result Register y (w) */
    unsigned int REV15:1;                   /**< \brief [15:15] Clear Result Event for Result Register y (w) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_REFCLR_Bits;

/** \\brief  Result Event Flag Register, Group */
typedef struct _Ifx_VADC_G_REFLAG_Bits
{
    unsigned int REV0:1;                    /**< \brief [0:0] Result Event for Result Register y (rwh) */
    unsigned int REV1:1;                    /**< \brief [1:1] Result Event for Result Register y (rwh) */
    unsigned int REV2:1;                    /**< \brief [2:2] Result Event for Result Register y (rwh) */
    unsigned int REV3:1;                    /**< \brief [3:3] Result Event for Result Register y (rwh) */
    unsigned int REV4:1;                    /**< \brief [4:4] Result Event for Result Register y (rwh) */
    unsigned int REV5:1;                    /**< \brief [5:5] Result Event for Result Register y (rwh) */
    unsigned int REV6:1;                    /**< \brief [6:6] Result Event for Result Register y (rwh) */
    unsigned int REV7:1;                    /**< \brief [7:7] Result Event for Result Register y (rwh) */
    unsigned int REV8:1;                    /**< \brief [8:8] Result Event for Result Register y (rwh) */
    unsigned int REV9:1;                    /**< \brief [9:9] Result Event for Result Register y (rwh) */
    unsigned int REV10:1;                   /**< \brief [10:10] Result Event for Result Register y (rwh) */
    unsigned int REV11:1;                   /**< \brief [11:11] Result Event for Result Register y (rwh) */
    unsigned int REV12:1;                   /**< \brief [12:12] Result Event for Result Register y (rwh) */
    unsigned int REV13:1;                   /**< \brief [13:13] Result Event for Result Register y (rwh) */
    unsigned int REV14:1;                   /**< \brief [14:14] Result Event for Result Register y (rwh) */
    unsigned int REV15:1;                   /**< \brief [15:15] Result Event for Result Register y (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_REFLAG_Bits;

/** \\brief  Result Event Node Pointer Register 0, Group */
typedef struct _Ifx_VADC_G_REVNP0_Bits
{
    unsigned int REV0NP:4;                  /**< \brief [3:0] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV1NP:4;                  /**< \brief [7:4] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV2NP:4;                  /**< \brief [11:8] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV3NP:4;                  /**< \brief [15:12] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV4NP:4;                  /**< \brief [19:16] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV5NP:4;                  /**< \brief [23:20] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV6NP:4;                  /**< \brief [27:24] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV7NP:4;                  /**< \brief [31:28] Service Request Node Pointer Result Event i (rw) */
} Ifx_VADC_G_REVNP0_Bits;

/** \\brief  Result Event Node Pointer Register 1, Group */
typedef struct _Ifx_VADC_G_REVNP1_Bits
{
    unsigned int REV8NP:4;                  /**< \brief [3:0] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV9NP:4;                  /**< \brief [7:4] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV10NP:4;                 /**< \brief [11:8] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV11NP:4;                 /**< \brief [15:12] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV12NP:4;                 /**< \brief [19:16] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV13NP:4;                 /**< \brief [23:20] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV14NP:4;                 /**< \brief [27:24] Service Request Node Pointer Result Event i (rw) */
    unsigned int REV15NP:4;                 /**< \brief [31:28] Service Request Node Pointer Result Event i (rw) */
} Ifx_VADC_G_REVNP1_Bits;

/** \\brief  Result Assignment Register, Group */
typedef struct _Ifx_VADC_G_RRASS_Bits
{
    unsigned int ASSRR0:1;                  /**< \brief [0:0] Assignment for Result Register y (rw) */
    unsigned int ASSRR1:1;                  /**< \brief [1:1] Assignment for Result Register y (rw) */
    unsigned int ASSRR2:1;                  /**< \brief [2:2] Assignment for Result Register y (rw) */
    unsigned int ASSRR3:1;                  /**< \brief [3:3] Assignment for Result Register y (rw) */
    unsigned int ASSRR4:1;                  /**< \brief [4:4] Assignment for Result Register y (rw) */
    unsigned int ASSRR5:1;                  /**< \brief [5:5] Assignment for Result Register y (rw) */
    unsigned int ASSRR6:1;                  /**< \brief [6:6] Assignment for Result Register y (rw) */
    unsigned int ASSRR7:1;                  /**< \brief [7:7] Assignment for Result Register y (rw) */
    unsigned int ASSRR8:1;                  /**< \brief [8:8] Assignment for Result Register y (rw) */
    unsigned int ASSRR9:1;                  /**< \brief [9:9] Assignment for Result Register y (rw) */
    unsigned int ASSRR10:1;                 /**< \brief [10:10] Assignment for Result Register y (rw) */
    unsigned int ASSRR11:1;                 /**< \brief [11:11] Assignment for Result Register y (rw) */
    unsigned int ASSRR12:1;                 /**< \brief [12:12] Assignment for Result Register y (rw) */
    unsigned int ASSRR13:1;                 /**< \brief [13:13] Assignment for Result Register y (rw) */
    unsigned int ASSRR14:1;                 /**< \brief [14:14] Assignment for Result Register y (rw) */
    unsigned int ASSRR15:1;                 /**< \brief [15:15] Assignment for Result Register y (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_RRASS_Bits;

/** \\brief  Source Event Flag Clear Register, Group */
typedef struct _Ifx_VADC_G_SEFCLR_Bits
{
    unsigned int SEV0:1;                    /**< \brief [0:0] Clear Source Event 0/1 (w) */
    unsigned int SEV1:1;                    /**< \brief [1:1] Clear Source Event 0/1 (w) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_VADC_G_SEFCLR_Bits;

/** \\brief  Source Event Flag Register, Group */
typedef struct _Ifx_VADC_G_SEFLAG_Bits
{
    unsigned int SEV0:1;                    /**< \brief [0:0] Source Event 0/1 (rwh) */
    unsigned int SEV1:1;                    /**< \brief [1:1] Source Event 0/1 (rwh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_VADC_G_SEFLAG_Bits;

/** \\brief  Source Event Node Pointer Register, Group */
typedef struct _Ifx_VADC_G_SEVNP_Bits
{
    unsigned int SEV0NP:4;                  /**< \brief [3:0] Service Request Node Pointer Source Event i (rw) */
    unsigned int SEV1NP:4;                  /**< \brief [7:4] Service Request Node Pointer Source Event i (rw) */
    unsigned int reserved_8:24;             /**< \brief \internal Reserved */
} Ifx_VADC_G_SEVNP_Bits;

/** \\brief  Service Request Software Activation Trigger, Group */
typedef struct _Ifx_VADC_G_SRACT_Bits
{
    unsigned int AGSR0:1;                   /**< \brief [0:0] Activate Group Service Request Node y (w) */
    unsigned int AGSR1:1;                   /**< \brief [1:1] Activate Group Service Request Node y (w) */
    unsigned int AGSR2:1;                   /**< \brief [2:2] Activate Group Service Request Node y (w) */
    unsigned int AGSR3:1;                   /**< \brief [3:3] Activate Group Service Request Node y (w) */
    unsigned int reserved_4:4;              /**< \brief \internal Reserved */
    unsigned int ASSR0:1;                   /**< \brief [8:8] Activate Shared Service Request Node y (w) */
    unsigned int ASSR1:1;                   /**< \brief [9:9] Activate Shared Service Request Node y (w) */
    unsigned int ASSR2:1;                   /**< \brief [10:10] Activate Shared Service Request Node y (w) */
    unsigned int ASSR3:1;                   /**< \brief [11:11] Activate Shared Service Request Node y (w) */
    unsigned int reserved_12:20;            /**< \brief \internal Reserved */
} Ifx_VADC_G_SRACT_Bits;

/** \\brief  Synchronization Control Register, Group */
typedef struct _Ifx_VADC_G_SYNCTR_Bits
{
    unsigned int STSEL:2;                   /**< \brief [1:0] Start Selection (rw) */
    unsigned int reserved_2:2;              /**< \brief \internal Reserved */
    unsigned int EVALR1:1;                  /**< \brief [4:4] Evaluate Ready Input Rx (rw) */
    unsigned int EVALR2:1;                  /**< \brief [5:5] Evaluate Ready Input Rx (rw) */
    unsigned int EVALR3:1;                  /**< \brief [6:6] Evaluate Ready Input Rx (rw) */
    unsigned int reserved_7:25;             /**< \brief \internal Reserved */
} Ifx_VADC_G_SYNCTR_Bits;

/** \\brief  Valid Flag Register, Group */
typedef struct _Ifx_VADC_G_VFR_Bits
{
    unsigned int VF0:1;                     /**< \brief [0:0] Valid Flag of Result Register x (rwh) */
    unsigned int VF1:1;                     /**< \brief [1:1] Valid Flag of Result Register x (rwh) */
    unsigned int VF2:1;                     /**< \brief [2:2] Valid Flag of Result Register x (rwh) */
    unsigned int VF3:1;                     /**< \brief [3:3] Valid Flag of Result Register x (rwh) */
    unsigned int VF4:1;                     /**< \brief [4:4] Valid Flag of Result Register x (rwh) */
    unsigned int VF5:1;                     /**< \brief [5:5] Valid Flag of Result Register x (rwh) */
    unsigned int VF6:1;                     /**< \brief [6:6] Valid Flag of Result Register x (rwh) */
    unsigned int VF7:1;                     /**< \brief [7:7] Valid Flag of Result Register x (rwh) */
    unsigned int VF8:1;                     /**< \brief [8:8] Valid Flag of Result Register x (rwh) */
    unsigned int VF9:1;                     /**< \brief [9:9] Valid Flag of Result Register x (rwh) */
    unsigned int VF10:1;                    /**< \brief [10:10] Valid Flag of Result Register x (rwh) */
    unsigned int VF11:1;                    /**< \brief [11:11] Valid Flag of Result Register x (rwh) */
    unsigned int VF12:1;                    /**< \brief [12:12] Valid Flag of Result Register x (rwh) */
    unsigned int VF13:1;                    /**< \brief [13:13] Valid Flag of Result Register x (rwh) */
    unsigned int VF14:1;                    /**< \brief [14:14] Valid Flag of Result Register x (rwh) */
    unsigned int VF15:1;                    /**< \brief [15:15] Valid Flag of Result Register x (rwh) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_VADC_G_VFR_Bits;

/** \\brief  Global Boundary Select Register */
typedef struct _Ifx_VADC_GLOBBOUND_Bits
{
    unsigned int BOUNDARY0:12;              /**< \brief [11:0] Boundary Value 0 for Limit Checking (rw) */
    unsigned int reserved_12:4;             /**< \brief \internal Reserved */
    unsigned int BOUNDARY1:12;              /**< \brief [27:16] Boundary Value 1 for Limit Checking (rw) */
    unsigned int reserved_28:4;             /**< \brief \internal Reserved */
} Ifx_VADC_GLOBBOUND_Bits;

/** \\brief  Global Configuration Register */
typedef struct _Ifx_VADC_GLOBCFG_Bits
{
    unsigned int DIVA:5;                    /**< \brief [4:0] Divider Factor for the Analog Internal Clock (rw) */
    unsigned int reserved_5:2;              /**< \brief \internal Reserved */
    unsigned int DCMSB:1;                   /**< \brief [7:7] Double Clock for the MSB Conversion (rw) */
    unsigned int DIVD:2;                    /**< \brief [9:8] Divider Factor for the Arbiter Clock (rw) */
    unsigned int reserved_10:5;             /**< \brief \internal Reserved */
    unsigned int DIVWC:1;                   /**< \brief [15:15] Write Control for Divider Parameters (w) */
    unsigned int DPCAL0:1;                  /**< \brief [16:16] Disable Post-Calibration (rw) */
    unsigned int DPCAL1:1;                  /**< \brief [17:17] Disable Post-Calibration (rw) */
    unsigned int DPCAL2:1;                  /**< \brief [18:18] Disable Post-Calibration (rw) */
    unsigned int reserved_19:12;            /**< \brief \internal Reserved */
    unsigned int SUCAL:1;                   /**< \brief [31:31] Start-Up Calibration (w) */
} Ifx_VADC_GLOBCFG_Bits;

/** \\brief  Global Event Flag Register */
typedef struct _Ifx_VADC_GLOBEFLAG_Bits
{
    unsigned int SEVGLB:1;                  /**< \brief [0:0] Source Event (Background) (rwh) */
    unsigned int reserved_1:7;              /**< \brief \internal Reserved */
    unsigned int REVGLB:1;                  /**< \brief [8:8] Global Result Event (rwh) */
    unsigned int reserved_9:7;              /**< \brief \internal Reserved */
    unsigned int SEVGLBCLR:1;               /**< \brief [16:16] Clear Source Event (Background) (w) */
    unsigned int reserved_17:7;             /**< \brief \internal Reserved */
    unsigned int REVGLBCLR:1;               /**< \brief [24:24] Clear Global Result Event (w) */
    unsigned int reserved_25:7;             /**< \brief \internal Reserved */
} Ifx_VADC_GLOBEFLAG_Bits;

/** \\brief  Global Event Node Pointer Register */
typedef struct _Ifx_VADC_GLOBEVNP_Bits
{
    unsigned int SEV0NP:4;                  /**< \brief [3:0] Service Request Node Pointer Backgr. Source (rw) */
    unsigned int reserved_4:12;             /**< \brief \internal Reserved */
    unsigned int REV0NP:4;                  /**< \brief [19:16] Service Request Node Pointer Backgr. Result (rw) */
    unsigned int reserved_20:12;            /**< \brief \internal Reserved */
} Ifx_VADC_GLOBEVNP_Bits;

/** \\brief  Global Result Control Register */
typedef struct _Ifx_VADC_GLOBRCR_Bits
{
    unsigned int reserved_0:16;             /**< \brief \internal Reserved */
    unsigned int DRCTR:4;                   /**< \brief [19:16] Data Reduction Control (rw) */
    unsigned int reserved_20:4;             /**< \brief \internal Reserved */
    unsigned int WFR:1;                     /**< \brief [24:24] Wait-for-Read Mode Enable (rw) */
    unsigned int reserved_25:6;             /**< \brief \internal Reserved */
    unsigned int SRGEN:1;                   /**< \brief [31:31] Service Request Generation Enable (rw) */
} Ifx_VADC_GLOBRCR_Bits;

/** \\brief  Global Result Register */
typedef struct _Ifx_VADC_GLOBRES_Bits
{
    unsigned int RESULT:16;                 /**< \brief [15:0] Result of most recent conversion (rwh) */
    unsigned int GNR:4;                     /**< \brief [19:16] Group Number (rh) */
    unsigned int CHNR:5;                    /**< \brief [24:20] Channel Number (rh) */
    unsigned int EMUX:3;                    /**< \brief [27:25] External Multiplexer Setting (rh) */
    unsigned int CRS:2;                     /**< \brief [29:28] Converted Request Source (rh) */
    unsigned int FCR:1;                     /**< \brief [30:30] Fast Compare Result (rh) */
    unsigned int VF:1;                      /**< \brief [31:31] Valid Flag (rwh) */
} Ifx_VADC_GLOBRES_Bits;

/** \\brief  Global Result Register, Debug */
typedef struct _Ifx_VADC_GLOBRESD_Bits
{
    unsigned int RESULT:16;                 /**< \brief [15:0] Result of most recent conversion (rwh) */
    unsigned int GNR:4;                     /**< \brief [19:16] Group Number (rh) */
    unsigned int CHNR:5;                    /**< \brief [24:20] Channel Number (rh) */
    unsigned int EMUX:3;                    /**< \brief [27:25] External Multiplexer Setting (rh) */
    unsigned int CRS:2;                     /**< \brief [29:28] Converted Request Source (rh) */
    unsigned int FCR:1;                     /**< \brief [30:30] Fast Compare Result (rh) */
    unsigned int VF:1;                      /**< \brief [31:31] Valid Flag (rwh) */
} Ifx_VADC_GLOBRESD_Bits;

/** \\brief  Global Test Functions Register */
typedef struct _Ifx_VADC_GLOBTF_Bits
{
    unsigned int CDCH:4;                    /**< \brief [3:0] Conversion Diagnostics Channel (rw) */
    unsigned int CDGR:4;                    /**< \brief [7:4] Conversion Diagnostics Group (rw) */
    unsigned int CDEN:1;                    /**< \brief [8:8] Converter Diagnostics Enable (rw) */
    unsigned int CDSEL:2;                   /**< \brief [10:9] Converter Diagnostics Pull-Devices Select (rw) */
    unsigned int reserved_11:4;             /**< \brief \internal Reserved */
    unsigned int CDWC:1;                    /**< \brief [15:15] Write Control for Conversion Diagnostics (w) */
    unsigned int PDD:1;                     /**< \brief [16:16] Pull-Down Diagnostics Enable (rw) */
    unsigned int MDPD:1;                    /**< \brief [17:17] Multiplexer Diagnostics Pull-Devices Enable (rw) */
    unsigned int MDPU:1;                    /**< \brief [18:18] Multiplexer Diagnostics Pull-Devices Enable (rw) */
    unsigned int reserved_19:4;             /**< \brief \internal Reserved */
    unsigned int MDWC:1;                    /**< \brief [23:23] Write Control for Multiplexer Diagnostics (w) */
    unsigned int reserved_24:8;             /**< \brief \internal Reserved */
} Ifx_VADC_GLOBTF_Bits;

/** \\brief  Input Class Register */
typedef struct _Ifx_VADC_ICLASS_Bits
{
    unsigned int STCS:5;                    /**< \brief [4:0] Sample Time Control for Standard Conversions (rw) */
    unsigned int reserved_5:3;              /**< \brief \internal Reserved */
    unsigned int CMS:3;                     /**< \brief [10:8] Conversion Mode for Standard Conversions (rw) */
    unsigned int reserved_11:5;             /**< \brief \internal Reserved */
    unsigned int STCE:5;                    /**< \brief [20:16] Sample Time Control for EMUX Conversions (rw) */
    unsigned int reserved_21:3;             /**< \brief \internal Reserved */
    unsigned int CME:3;                     /**< \brief [26:24] Conversion Mode for EMUX Conversions (rw) */
    unsigned int reserved_27:5;             /**< \brief \internal Reserved */
} Ifx_VADC_ICLASS_Bits;

/** \\brief  Module Identification Register */
typedef struct _Ifx_VADC_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_VADC_ID_Bits;

/** \\brief  Kernel Reset Register 0 */
typedef struct _Ifx_VADC_KRST0_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int RSTSTAT:1;                 /**< \brief [1:1] Kernel Reset Status (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_VADC_KRST0_Bits;

/** \\brief  Kernel Reset Register 1 */
typedef struct _Ifx_VADC_KRST1_Bits
{
    unsigned int RST:1;                     /**< \brief [0:0] Kernel Reset (rwh) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_VADC_KRST1_Bits;

/** \\brief  Kernel Reset Status Clear Register */
typedef struct _Ifx_VADC_KRSTCLR_Bits
{
    unsigned int CLR:1;                     /**< \brief [0:0] Kernel Reset Status Clear (w) */
    unsigned int reserved_1:31;             /**< \brief \internal Reserved */
} Ifx_VADC_KRSTCLR_Bits;

/** \\brief  OCDS Control and Status Register */
typedef struct _Ifx_VADC_OCS_Bits
{
    unsigned int TGS:2;                     /**< \brief [1:0] Trigger Set for OTGB0/1 (rw) */
    unsigned int TGB:1;                     /**< \brief [2:2] OTGB0/1 Bus Select (rw) */
    unsigned int TG_P:1;                    /**< \brief [3:3] TGS, TGB Write Protection (w) */
    unsigned int reserved_4:20;             /**< \brief \internal Reserved */
    unsigned int SUS:4;                     /**< \brief [27:24] OCDS Suspend Control (rw) */
    unsigned int SUS_P:1;                   /**< \brief [28:28] SUS Write Protection (w) */
    unsigned int SUSSTA:1;                  /**< \brief [29:29] Suspend State (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_VADC_OCS_Bits;

/** \\brief  Group Result Control Reg. */
typedef struct _Ifx_VADC_RCR_Bits
{
    unsigned int reserved_0:16;             /**< \brief \internal Reserved */
    unsigned int DRCTR:4;                   /**< \brief [19:16] Data Reduction Control (rw) */
    unsigned int DMM:2;                     /**< \brief [21:20] Data Modification Mode (rw) */
    unsigned int reserved_22:2;             /**< \brief \internal Reserved */
    unsigned int WFR:1;                     /**< \brief [24:24] Wait-for-Read Mode Enable (rw) */
    unsigned int FEN:2;                     /**< \brief [26:25] FIFO Mode Enable (rw) */
    unsigned int reserved_27:4;             /**< \brief \internal Reserved */
    unsigned int SRGEN:1;                   /**< \brief [31:31] Service Request Generation Enable (rw) */
} Ifx_VADC_RCR_Bits;

/** \\brief  Group Result Register */
typedef struct _Ifx_VADC_RES_Bits
{
    unsigned int RESULT:16;                 /**< \brief [15:0] Result of Most Recent Conversion (rwh) */
    unsigned int DRC:4;                     /**< \brief [19:16] Data Reduction Counter (rh) */
    unsigned int CHNR:5;                    /**< \brief [24:20] Channel Number (rh) */
    unsigned int EMUX:3;                    /**< \brief [27:25] External Multiplexer Setting (rh) */
    unsigned int CRS:2;                     /**< \brief [29:28] Converted Request Source (rh) */
    unsigned int FCR:1;                     /**< \brief [30:30] Fast Compare Result (rh) */
    unsigned int VF:1;                      /**< \brief [31:31] Valid Flag (rh) */
} Ifx_VADC_RES_Bits;

/** \\brief  Group Result Reg., Debug */
typedef struct _Ifx_VADC_RESD_Bits
{
    unsigned int RESULT:16;                 /**< \brief [15:0] Result of Most Recent Conversion (rh) */
    unsigned int DRC:4;                     /**< \brief [19:16] Data Reduction Counter (rh) */
    unsigned int CHNR:5;                    /**< \brief [24:20] Channel Number (rh) */
    unsigned int EMUX:3;                    /**< \brief [27:25] External Multiplexer Setting (rh) */
    unsigned int CRS:2;                     /**< \brief [29:28] Converted Request Source (rh) */
    unsigned int FCR:1;                     /**< \brief [30:30] Fast Compare Result (rh) */
    unsigned int VF:1;                      /**< \brief [31:31] Valid Flag (rh) */
} Ifx_VADC_RESD_Bits;

/** \\brief  Calibration Control Register */
typedef struct _Ifx_VADC_SHS_CALCTR_Bits
{
    unsigned int CALORD:1;                  /**< \brief [0:0] Calibration Order (rw) */
    unsigned int reserved_1:2;              /**< \brief \internal Reserved */
    unsigned int ARCH:1;                    /**< \brief [3:3] Alternate Reference Channel (rw) */
    unsigned int AREFDEF:3;                 /**< \brief [6:4] Alternate Reference Definition (rw) */
    unsigned int ARM:1;                     /**< \brief [7:7] Alternate Reference Mode (rw) */
    unsigned int CALGNSTC:6;                /**< \brief [13:8] Gain Calibration Sample Time Control (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int SUCALVAL:7;                /**< \brief [22:16] Startup Calibration Cycles (rw) */
    unsigned int reserved_23:1;             /**< \brief \internal Reserved */
    unsigned int CALMAX:6;                  /**< \brief [29:24] Calibration Maximum Timing (rw) */
    unsigned int reserved_30:1;             /**< \brief \internal Reserved */
    unsigned int SUCAL:1;                   /**< \brief [31:31] Start-Up Calibration (w) */
} Ifx_VADC_SHS_CALCTR_Bits;

/** \\brief  Gain Calibration Control $2 */
typedef struct _Ifx_VADC_SHS_CALGC_Bits
{
    unsigned int CALGNVALS:14;              /**< \brief [13:0] Gain Calibration Value, Standard Reference (rwh) */
    unsigned int reserved_14:1;             /**< \brief \internal Reserved */
    unsigned int GNSWC:1;                   /**< \brief [15:15] Gain Calibration Write Control, Standard (w) */
    unsigned int CALGNVALA:14;              /**< \brief [29:16] Gain Calibration Value, Alternate Reference (rwh) */
    unsigned int reserved_30:1;             /**< \brief \internal Reserved */
    unsigned int GNAWC:1;                   /**< \brief [31:31] Gain Calibration Write Control, Alternate (w) */
} Ifx_VADC_SHS_CALGC_Bits;

/** \\brief  Module Identification Register */
typedef struct _Ifx_VADC_SHS_ID_Bits
{
    unsigned int MODREV:8;                  /**< \brief [7:0] Module Revision Number (r) */
    unsigned int MODTYPE:8;                 /**< \brief [15:8] Module Type (r) */
    unsigned int MODNUMBER:16;              /**< \brief [31:16] Module Number Value (r) */
} Ifx_VADC_SHS_ID_Bits;

/** \\brief  SHS Configuration Register */
typedef struct _Ifx_VADC_SHS_SHSCFG_Bits
{
    unsigned int DIVS:4;                    /**< \brief [3:0] Divider Factor for the SHS Clock (rw) */
    unsigned int reserved_4:6;              /**< \brief \internal Reserved */
    unsigned int AREF:2;                    /**< \brief [11:10] Analog Reference Voltage Selection (rw) */
    unsigned int ANOFF:1;                   /**< \brief [12:12] Analog Converter Power Down ForceSee also . (rw) */
    unsigned int reserved_13:1;             /**< \brief \internal Reserved */
    unsigned int ANRDY:1;                   /**< \brief [14:14] Analog Converter Ready (rh) */
    unsigned int SCWC:1;                    /**< \brief [15:15] Write Control for SHS Configuration (w) */
    unsigned int SP0:1;                     /**< \brief [16:16] Sample Pending on S&H Unit x (rh) */
    unsigned int SP1:1;                     /**< \brief [17:17] Sample Pending on S&H Unit x (rh) */
    unsigned int reserved_18:6;             /**< \brief \internal Reserved */
    unsigned int TC:4;                      /**< \brief [27:24] Test Control (rw) */
    unsigned int STATE:4;                   /**< \brief [31:28] Current State of Sequencer (rh) */
} Ifx_VADC_SHS_SHSCFG_Bits;

/** \\brief  Stepper Configuration Register */
typedef struct _Ifx_VADC_SHS_STEPCFG_Bits
{
    unsigned int KSEL0:3;                   /**< \brief [2:0] Kernel Select (rw) */
    unsigned int SEN0:1;                    /**< \brief [3:3] Step x Enable (rw) */
    unsigned int KSEL1:3;                   /**< \brief [6:4] Kernel Select (rw) */
    unsigned int SEN1:1;                    /**< \brief [7:7] Step x Enable (rw) */
    unsigned int KSEL2:3;                   /**< \brief [10:8] Kernel Select (rw) */
    unsigned int SEN2:1;                    /**< \brief [11:11] Step x Enable (rw) */
    unsigned int KSEL3:3;                   /**< \brief [14:12] Kernel Select (rw) */
    unsigned int SEN3:1;                    /**< \brief [15:15] Step x Enable (rw) */
    unsigned int KSEL4:3;                   /**< \brief [18:16] Kernel Select (rw) */
    unsigned int SEN4:1;                    /**< \brief [19:19] Step x Enable (rw) */
    unsigned int KSEL5:3;                   /**< \brief [22:20] Kernel Select (rw) */
    unsigned int SEN5:1;                    /**< \brief [23:23] Step x Enable (rw) */
    unsigned int KSEL6:3;                   /**< \brief [26:24] Kernel Select (rw) */
    unsigned int SEN6:1;                    /**< \brief [27:27] Step x Enable (rw) */
    unsigned int KSEL7:3;                   /**< \brief [30:28] Kernel Select (rw) */
    unsigned int SEN7:1;                    /**< \brief [31:31] Step x Enable (rw) */
} Ifx_VADC_SHS_STEPCFG_Bits;

/** \\brief  Timing Configuration $2 */
typedef struct _Ifx_VADC_SHS_TIMCFG_Bits
{
    unsigned int AT:1;                      /**< \brief [0:0] Accelerated Timing (rw) */
    unsigned int reserved_1:3;              /**< \brief \internal Reserved */
    unsigned int FCRT:4;                    /**< \brief [7:4] Fast Compare Mode Response Time (rw) */
    unsigned int SST:6;                     /**< \brief [13:8] Short Sample Time (rw) */
    unsigned int reserved_14:2;             /**< \brief \internal Reserved */
    unsigned int TGEN:14;                   /**< \brief [29:16] Timing Generator (rh) */
    unsigned int reserved_30:2;             /**< \brief \internal Reserved */
} Ifx_VADC_SHS_TIMCFG_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Vadc_union
 * \{  */

/** \\brief  Access Enable Register 0 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_ACCEN0_Bits B;
} Ifx_VADC_ACCEN0;

/** \\brief  Access Protection Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_ACCPROT0_Bits B;
} Ifx_VADC_ACCPROT0;

/** \\brief  Access Protection Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_ACCPROT1_Bits B;
} Ifx_VADC_ACCPROT1;

/** \\brief  Background Request Source Control Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_BRSCTRL_Bits B;
} Ifx_VADC_BRSCTRL;

/** \\brief  Background Request Source Mode Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_BRSMR_Bits B;
} Ifx_VADC_BRSMR;

/** \\brief  Background Request Source Pending Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_BRSPND_Bits B;
} Ifx_VADC_BRSPND;

/** \\brief  Background Request Source Channel Select Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_BRSSEL_Bits B;
} Ifx_VADC_BRSSEL;

/** \\brief  Group, Channel Ctrl. Reg. */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_CHCTR_Bits B;
} Ifx_VADC_CHCTR;

/** \\brief  Clock Control Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_CLC_Bits B;
} Ifx_VADC_CLC;

/** \\brief  External Multiplexer Select Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_EMUXSEL_Bits B;
} Ifx_VADC_EMUXSEL;

/** \\brief  Alias Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_ALIAS_Bits B;
} Ifx_VADC_G_ALIAS;

/** \\brief  Arbitration Configuration Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_ARBCFG_Bits B;
} Ifx_VADC_G_ARBCFG;

/** \\brief  Arbitration Priority Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_ARBPR_Bits B;
} Ifx_VADC_G_ARBPR;

/** \\brief  Autoscan Source Control Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_ASCTRL_Bits B;
} Ifx_VADC_G_ASCTRL;

/** \\brief  Autoscan Source Mode Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_ASMR_Bits B;
} Ifx_VADC_G_ASMR;

/** \\brief  Autoscan Source Pending Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_ASPND_Bits B;
} Ifx_VADC_G_ASPND;

/** \\brief  Autoscan Source Channel Select Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_ASSEL_Bits B;
} Ifx_VADC_G_ASSEL;

/** \\brief  Boundary Flag Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_BFL_Bits B;
} Ifx_VADC_G_BFL;

/** \\brief  Boundary Flag Control Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_BFLC_Bits B;
} Ifx_VADC_G_BFLC;

/** \\brief  Boundary Flag Node Pointer Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_BFLNP_Bits B;
} Ifx_VADC_G_BFLNP;

/** \\brief  Boundary Flag Software Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_BFLS_Bits B;
} Ifx_VADC_G_BFLS;

/** \\brief  Boundary Select Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_BOUND_Bits B;
} Ifx_VADC_G_BOUND;

/** \\brief  Channel Event Flag Clear Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_CEFCLR_Bits B;
} Ifx_VADC_G_CEFCLR;

/** \\brief  Channel Event Flag Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_CEFLAG_Bits B;
} Ifx_VADC_G_CEFLAG;

/** \\brief  Channel Event Node Pointer Register 0, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_CEVNP0_Bits B;
} Ifx_VADC_G_CEVNP0;

/** \\brief  Channel Event Node Pointer Register 1, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_CEVNP1_Bits B;
} Ifx_VADC_G_CEVNP1;

/** \\brief  Channel Assignment Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_CHASS_Bits B;
} Ifx_VADC_G_CHASS;

/** \\brief  External Multiplexer Control Register, Group x */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_EMUXCTR_Bits B;
} Ifx_VADC_G_EMUXCTR;

/** \\brief  Queue 0 Register 0, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_Q0R0_Bits B;
} Ifx_VADC_G_Q0R0;

/** \\brief  Queue 0 Backup Register, Group
 * Queue 0 Input Register, Group
 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access: Queue 0 Backup Register, Group  */
    Ifx_VADC_G_QBUR_QINR0_QBUR0_Bits B_QBUR0;
    /** \brief Bitfield access: Queue 0 Input Register, Group  */
    Ifx_VADC_G_QBUR_QINR0_QINR0_Bits B_QINR0;
} Ifx_VADC_G_QBUR_QINR0;

/** \\brief  Queue 0 Source Control Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_QCTRL0_Bits B;
} Ifx_VADC_G_QCTRL0;

/** \\brief  Queue 0 Mode Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_QMR0_Bits B;
} Ifx_VADC_G_QMR0;

/** \\brief  Queue 0 Status Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_QSR0_Bits B;
} Ifx_VADC_G_QSR0;

/** \\brief  Result Event Flag Clear Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_REFCLR_Bits B;
} Ifx_VADC_G_REFCLR;

/** \\brief  Result Event Flag Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_REFLAG_Bits B;
} Ifx_VADC_G_REFLAG;

/** \\brief  Result Event Node Pointer Register 0, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_REVNP0_Bits B;
} Ifx_VADC_G_REVNP0;

/** \\brief  Result Event Node Pointer Register 1, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_REVNP1_Bits B;
} Ifx_VADC_G_REVNP1;

/** \\brief  Result Assignment Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_RRASS_Bits B;
} Ifx_VADC_G_RRASS;

/** \\brief  Source Event Flag Clear Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_SEFCLR_Bits B;
} Ifx_VADC_G_SEFCLR;

/** \\brief  Source Event Flag Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_SEFLAG_Bits B;
} Ifx_VADC_G_SEFLAG;

/** \\brief  Source Event Node Pointer Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_SEVNP_Bits B;
} Ifx_VADC_G_SEVNP;

/** \\brief  Service Request Software Activation Trigger, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_SRACT_Bits B;
} Ifx_VADC_G_SRACT;

/** \\brief  Synchronization Control Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_SYNCTR_Bits B;
} Ifx_VADC_G_SYNCTR;

/** \\brief  Valid Flag Register, Group */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_G_VFR_Bits B;
} Ifx_VADC_G_VFR;

/** \\brief  Global Boundary Select Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBBOUND_Bits B;
} Ifx_VADC_GLOBBOUND;

/** \\brief  Global Configuration Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBCFG_Bits B;
} Ifx_VADC_GLOBCFG;

/** \\brief  Global Event Flag Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBEFLAG_Bits B;
} Ifx_VADC_GLOBEFLAG;

/** \\brief  Global Event Node Pointer Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBEVNP_Bits B;
} Ifx_VADC_GLOBEVNP;

/** \\brief  Global Result Control Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBRCR_Bits B;
} Ifx_VADC_GLOBRCR;

/** \\brief  Global Result Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBRES_Bits B;
} Ifx_VADC_GLOBRES;

/** \\brief  Global Result Register, Debug */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBRESD_Bits B;
} Ifx_VADC_GLOBRESD;

/** \\brief  Global Test Functions Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_GLOBTF_Bits B;
} Ifx_VADC_GLOBTF;

/** \\brief  Input Class Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_ICLASS_Bits B;
} Ifx_VADC_ICLASS;

/** \\brief  Module Identification Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_ID_Bits B;
} Ifx_VADC_ID;

/** \\brief  Kernel Reset Register 0 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_KRST0_Bits B;
} Ifx_VADC_KRST0;

/** \\brief  Kernel Reset Register 1 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_KRST1_Bits B;
} Ifx_VADC_KRST1;

/** \\brief  Kernel Reset Status Clear Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_KRSTCLR_Bits B;
} Ifx_VADC_KRSTCLR;

/** \\brief  OCDS Control and Status Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_OCS_Bits B;
} Ifx_VADC_OCS;

/** \\brief  Group Result Control Reg. */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_RCR_Bits B;
} Ifx_VADC_RCR;

/** \\brief  Group Result Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_RES_Bits B;
} Ifx_VADC_RES;

/** \\brief  Group Result Reg., Debug */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_RESD_Bits B;
} Ifx_VADC_RESD;

/** \\brief  Calibration Control Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_SHS_CALCTR_Bits B;
} Ifx_VADC_SHS_CALCTR;

/** \\brief  Gain Calibration Control $2 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_SHS_CALGC_Bits B;
} Ifx_VADC_SHS_CALGC;

/** \\brief  Module Identification Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_SHS_ID_Bits B;
} Ifx_VADC_SHS_ID;

/** \\brief  SHS Configuration Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_SHS_SHSCFG_Bits B;
} Ifx_VADC_SHS_SHSCFG;

/** \\brief  Stepper Configuration Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_SHS_STEPCFG_Bits B;
} Ifx_VADC_SHS_STEPCFG;

/** \\brief  Timing Configuration $2 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_VADC_SHS_TIMCFG_Bits B;
} Ifx_VADC_SHS_TIMCFG;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Vadc_struct
 * \{  */
/******************************************************************************/
/** \name Object L1
 * \{  */

/** \\brief  Group objects */
typedef volatile struct _Ifx_VADC_G
{
    Ifx_VADC_G_ARBCFG ARBCFG;               /**< \brief 0, Arbitration Configuration Register, Group  */
    Ifx_VADC_G_ARBPR ARBPR;                 /**< \brief 4, Arbitration Priority Register, Group  */
    Ifx_VADC_G_CHASS CHASS;                 /**< \brief 8, Channel Assignment Register, Group  */
    Ifx_VADC_G_RRASS RRASS;                 /**< \brief C, Result Assignment Register, Group  */
    unsigned char reserved_10[16];          /**< \brief 10, \internal Reserved */
    Ifx_VADC_ICLASS ICLASS[2];              /**< \brief 20, Input Class Register */
    unsigned char reserved_28[8];           /**< \brief 28, \internal Reserved */
    Ifx_VADC_G_ALIAS ALIAS;                 /**< \brief 30, Alias Register, Group  */
    unsigned char reserved_34[4];           /**< \brief 34, \internal Reserved */
    Ifx_VADC_G_BOUND BOUND;                 /**< \brief 38, Boundary Select Register, Group  */
    unsigned char reserved_3C[4];           /**< \brief 3C, \internal Reserved */
    Ifx_VADC_G_SYNCTR SYNCTR;               /**< \brief 40, Synchronization Control Register, Group  */
    unsigned char reserved_44[4];           /**< \brief 44, \internal Reserved */
    Ifx_VADC_G_BFL BFL;                     /**< \brief 48, Boundary Flag Register, Group  */
    Ifx_VADC_G_BFLS BFLS;                   /**< \brief 4C, Boundary Flag Software Register, Group  */
    Ifx_VADC_G_BFLC BFLC;                   /**< \brief 50, Boundary Flag Control Register, Group  */
    Ifx_VADC_G_BFLNP BFLNP;                 /**< \brief 54, Boundary Flag Node Pointer Register, Group  */
    unsigned char reserved_58[40];          /**< \brief 58, \internal Reserved */
    Ifx_VADC_G_QCTRL0 QCTRL0;               /**< \brief 80, Queue 0 Source Control Register, Group  */
    Ifx_VADC_G_QMR0 QMR0;                   /**< \brief 84, Queue 0 Mode Register, Group  */
    Ifx_VADC_G_QSR0 QSR0;                   /**< \brief 88, Queue 0 Status Register, Group  */
    Ifx_VADC_G_Q0R0 Q0R0;                   /**< \brief 8C, Queue 0 Register 0, Group  */
    Ifx_VADC_G_QBUR_QINR0 QBUR_QINR0;       /**< \brief 90, Queue 0 Input Register, Group  */
    unsigned char reserved_94[12];          /**< \brief 94, \internal Reserved */
    Ifx_VADC_G_ASCTRL ASCTRL;               /**< \brief A0, Autoscan Source Control Register, Group  */
    Ifx_VADC_G_ASMR ASMR;                   /**< \brief A4, Autoscan Source Mode Register, Group  */
    Ifx_VADC_G_ASSEL ASSEL;                 /**< \brief A8, Autoscan Source Channel Select Register, Group  */
    Ifx_VADC_G_ASPND ASPND;                 /**< \brief AC, Autoscan Source Pending Register, Group  */
    unsigned char reserved_B0[80];          /**< \brief B0, \internal Reserved */
    Ifx_VADC_G_CEFLAG CEFLAG;               /**< \brief 100, Channel Event Flag Register, Group  */
    Ifx_VADC_G_REFLAG REFLAG;               /**< \brief 104, Result Event Flag Register, Group  */
    Ifx_VADC_G_SEFLAG SEFLAG;               /**< \brief 108, Source Event Flag Register, Group  */
    unsigned char reserved_10C[4];          /**< \brief 10C, \internal Reserved */
    Ifx_VADC_G_CEFCLR CEFCLR;               /**< \brief 110, Channel Event Flag Clear Register, Group  */
    Ifx_VADC_G_REFCLR REFCLR;               /**< \brief 114, Result Event Flag Clear Register, Group  */
    Ifx_VADC_G_SEFCLR SEFCLR;               /**< \brief 118, Source Event Flag Clear Register, Group  */
    unsigned char reserved_11C[4];          /**< \brief 11C, \internal Reserved */
    Ifx_VADC_G_CEVNP0 CEVNP0;               /**< \brief 120, Channel Event Node Pointer Register 0, Group  */
    Ifx_VADC_G_CEVNP1 CEVNP1;               /**< \brief 124, Channel Event Node Pointer Register 1, Group  */
    unsigned char reserved_128[8];          /**< \brief 128, \internal Reserved */
    Ifx_VADC_G_REVNP0 REVNP0;               /**< \brief 130, Result Event Node Pointer Register 0, Group  */
    Ifx_VADC_G_REVNP1 REVNP1;               /**< \brief 134, Result Event Node Pointer Register 1, Group  */
    unsigned char reserved_138[8];          /**< \brief 138, \internal Reserved */
    Ifx_VADC_G_SEVNP SEVNP;                 /**< \brief 140, Source Event Node Pointer Register, Group  */
    unsigned char reserved_144[4];          /**< \brief 144, \internal Reserved */
    Ifx_VADC_G_SRACT SRACT;                 /**< \brief 148, Service Request Software Activation Trigger, Group  */
    unsigned char reserved_14C[36];         /**< \brief 14C, \internal Reserved */
    Ifx_VADC_G_EMUXCTR EMUXCTR;             /**< \brief 170, External Multiplexer Control Register, Group x */
    unsigned char reserved_174[4];          /**< \brief 174, \internal Reserved */
    Ifx_VADC_G_VFR VFR;                     /**< \brief 178, Valid Flag Register, Group  */
    unsigned char reserved_17C[4];          /**< \brief 17C, \internal Reserved */
    Ifx_VADC_CHCTR CHCTR[16];               /**< \brief 180, Group, Channel Ctrl. Reg. */
    unsigned char reserved_1C0[64];         /**< \brief 1C0, \internal Reserved */
    Ifx_VADC_RCR RCR[16];                   /**< \brief 200, Group Result Control Reg. */
    unsigned char reserved_240[64];         /**< \brief 240, \internal Reserved */
    Ifx_VADC_RES RES[16];                   /**< \brief 280, Group Result Register */
    unsigned char reserved_2C0[64];         /**< \brief 2C0, \internal Reserved */
    Ifx_VADC_RESD RESD[16];                 /**< \brief 300, Group Result Reg., Debug */
    unsigned char reserved_340[192];        /**< \brief 340, \internal Reserved */
} Ifx_VADC_G;

/** \\brief  Group objects */
typedef volatile struct _Ifx_VADC_SHS
{
    unsigned char reserved_0[8];            /**< \brief 0, \internal Reserved */
    Ifx_VADC_SHS_ID ID;                     /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[52];           /**< \brief C, \internal Reserved */
    Ifx_VADC_SHS_SHSCFG SHSCFG;             /**< \brief 40, SHS Configuration Register */
    Ifx_VADC_SHS_STEPCFG STEPCFG;           /**< \brief 44, Stepper Configuration Register */
    unsigned char reserved_48[56];          /**< \brief 48, \internal Reserved */
    Ifx_VADC_SHS_TIMCFG TIMCFG[4];          /**< \brief 80, Timing Configuration Register */
    unsigned char reserved_90[44];          /**< \brief 90, \internal Reserved */
    Ifx_VADC_SHS_CALCTR CALCTR;             /**< \brief BC, Calibration Control Register */
    Ifx_VADC_SHS_CALGC CALGC[4];            /**< \brief C0, Gain Calibration Control Register */
    unsigned char reserved_D0[304];         /**< \brief D0, \internal Reserved */
} Ifx_VADC_SHS;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Vadc_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \\brief  VADC object */
typedef volatile struct _Ifx_VADC
{
    Ifx_VADC_CLC CLC;                       /**< \brief 0, Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_VADC_ID ID;                         /**< \brief 8, Module Identification Register */
    unsigned char reserved_C[28];           /**< \brief C, \internal Reserved */
    Ifx_VADC_OCS OCS;                       /**< \brief 28, OCDS Control and Status Register */
    Ifx_VADC_KRSTCLR KRSTCLR;               /**< \brief 2C, Kernel Reset Status Clear Register */
    Ifx_VADC_KRST1 KRST1;                   /**< \brief 30, Kernel Reset Register 1 */
    Ifx_VADC_KRST0 KRST0;                   /**< \brief 34, Kernel Reset Register 0 */
    unsigned char reserved_38[4];           /**< \brief 38, \internal Reserved */
    Ifx_VADC_ACCEN0 ACCEN0;                 /**< \brief 3C, Access Enable Register 0 */
    unsigned char reserved_40[64];          /**< \brief 40, \internal Reserved */
    Ifx_VADC_GLOBCFG GLOBCFG;               /**< \brief 80, Global Configuration Register */
    unsigned char reserved_84[4];           /**< \brief 84, \internal Reserved */
    Ifx_VADC_ACCPROT0 ACCPROT0;             /**< \brief 88, Access Protection Register */
    Ifx_VADC_ACCPROT1 ACCPROT1;             /**< \brief 8C, Access Protection Register */
    unsigned char reserved_90[16];          /**< \brief 90, \internal Reserved */
    Ifx_VADC_ICLASS GLOBICLASS[2];          /**< \brief A0, Input Class Register */
    unsigned char reserved_A8[16];          /**< \brief A8, \internal Reserved */
    Ifx_VADC_GLOBBOUND GLOBBOUND;           /**< \brief B8, Global Boundary Select Register */
    unsigned char reserved_BC[36];          /**< \brief BC, \internal Reserved */
    Ifx_VADC_GLOBEFLAG GLOBEFLAG;           /**< \brief E0, Global Event Flag Register */
    unsigned char reserved_E4[92];          /**< \brief E4, \internal Reserved */
    Ifx_VADC_GLOBEVNP GLOBEVNP;             /**< \brief 140, Global Event Node Pointer Register */
    unsigned char reserved_144[28];         /**< \brief 144, \internal Reserved */
    Ifx_VADC_GLOBTF GLOBTF;                 /**< \brief 160, Global Test Functions Register */
    unsigned char reserved_164[28];         /**< \brief 164, \internal Reserved */
    Ifx_VADC_BRSSEL BRSSEL[4];              /**< \brief 180, Background Request Source Channel Select Register, Group */
    unsigned char reserved_190[48];         /**< \brief 190, \internal Reserved */
    Ifx_VADC_BRSPND BRSPND[4];              /**< \brief 1C0, Background Request Source Pending Register, Group */
    unsigned char reserved_1D0[48];         /**< \brief 1D0, \internal Reserved */
    Ifx_VADC_BRSCTRL BRSCTRL;               /**< \brief 200, Background Request Source Control Register */
    Ifx_VADC_BRSMR BRSMR;                   /**< \brief 204, Background Request Source Mode Register */
    unsigned char reserved_208[120];        /**< \brief 208, \internal Reserved */
    Ifx_VADC_GLOBRCR GLOBRCR;               /**< \brief 280, Global Result Control Register */
    unsigned char reserved_284[124];        /**< \brief 284, \internal Reserved */
    Ifx_VADC_GLOBRES GLOBRES;               /**< \brief 300, Global Result Register */
    unsigned char reserved_304[124];        /**< \brief 304, \internal Reserved */
    Ifx_VADC_GLOBRESD GLOBRESD;             /**< \brief 380, Global Result Register, Debug */
    unsigned char reserved_384[108];        /**< \brief 384, \internal Reserved */
    Ifx_VADC_EMUXSEL EMUXSEL;               /**< \brief 3F0, External Multiplexer Select Register */
    unsigned char reserved_3F4[140];        /**< \brief 3F4, \internal Reserved */
    Ifx_VADC_G G[4];                        /**< \brief 480, Group objects */
    unsigned char reserved_1480[15232];     /**< \brief 1480, \internal Reserved */
    Ifx_VADC_SHS SHS[2];                    /**< \brief 5000, Group objects */
} Ifx_VADC;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXVADC_REGDEF_H */
