/**
 * \file IfxPmu_bf.h
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
 * \defgroup IfxLld_Pmu_BitfieldsMask Bitfields mask and offset
 * \ingroup IfxLld_Pmu
 * 
 */
#ifndef IFXPMU_BF_H
#define IFXPMU_BF_H
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Pmu_BitfieldsMask
 * \{  */

/** \\brief  Length for Ifx_PMU_ID_Bits.MODNUMBER */
#define IFX_PMU_ID_MODNUMBER_LEN (16)

/** \\brief  Mask for Ifx_PMU_ID_Bits.MODNUMBER */
#define IFX_PMU_ID_MODNUMBER_MSK (0xffff)

/** \\brief  Offset for Ifx_PMU_ID_Bits.MODNUMBER */
#define IFX_PMU_ID_MODNUMBER_OFF (16)

/** \\brief  Length for Ifx_PMU_ID_Bits.MODREV */
#define IFX_PMU_ID_MODREV_LEN (8)

/** \\brief  Mask for Ifx_PMU_ID_Bits.MODREV */
#define IFX_PMU_ID_MODREV_MSK (0xff)

/** \\brief  Offset for Ifx_PMU_ID_Bits.MODREV */
#define IFX_PMU_ID_MODREV_OFF (0)

/** \\brief  Length for Ifx_PMU_ID_Bits.MODTYPE */
#define IFX_PMU_ID_MODTYPE_LEN (8)

/** \\brief  Mask for Ifx_PMU_ID_Bits.MODTYPE */
#define IFX_PMU_ID_MODTYPE_MSK (0xff)

/** \\brief  Offset for Ifx_PMU_ID_Bits.MODTYPE */
#define IFX_PMU_ID_MODTYPE_OFF (8)
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXPMU_BF_H */
