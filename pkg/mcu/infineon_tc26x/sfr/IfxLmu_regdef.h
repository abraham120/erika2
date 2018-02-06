/**
 * \file IfxLmu_regdef.h
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
 * \defgroup IfxLld_Lmu Lmu
 * \ingroup IfxLld
 * 
 * \defgroup IfxLld_Lmu_Bitfields Bitfields
 * \ingroup IfxLld_Lmu
 * 
 * \defgroup IfxLld_Lmu_union Union
 * \ingroup IfxLld_Lmu
 * 
 * \defgroup IfxLld_Lmu_struct Struct
 * \ingroup IfxLld_Lmu
 * 
 */
#ifndef IFXLMU_REGDEF_H
#define IFXLMU_REGDEF_H
/******************************************************************************/
#include "Ifx_TypesReg.h"
/******************************************************************************/
/** \addtogroup IfxLld_Lmu_Bitfields
 * \{  */

/** \\brief  LMU Access Enable Register 0 */
typedef struct _Ifx_LMU_ACCEN0_Bits
{
    unsigned int EN0:1;                     /**< \brief [0:0] Access Enable for Master TAG ID n (rw) */
    unsigned int EN1:1;                     /**< \brief [1:1] Access Enable for Master TAG ID n (rw) */
    unsigned int EN2:1;                     /**< \brief [2:2] Access Enable for Master TAG ID n (rw) */
    unsigned int EN3:1;                     /**< \brief [3:3] Access Enable for Master TAG ID n (rw) */
    unsigned int EN4:1;                     /**< \brief [4:4] Access Enable for Master TAG ID n (rw) */
    unsigned int EN5:1;                     /**< \brief [5:5] Access Enable for Master TAG ID n (rw) */
    unsigned int EN6:1;                     /**< \brief [6:6] Access Enable for Master TAG ID n (rw) */
    unsigned int EN7:1;                     /**< \brief [7:7] Access Enable for Master TAG ID n (rw) */
    unsigned int EN8:1;                     /**< \brief [8:8] Access Enable for Master TAG ID n (rw) */
    unsigned int EN9:1;                     /**< \brief [9:9] Access Enable for Master TAG ID n (rw) */
    unsigned int EN10:1;                    /**< \brief [10:10] Access Enable for Master TAG ID n (rw) */
    unsigned int EN11:1;                    /**< \brief [11:11] Access Enable for Master TAG ID n (rw) */
    unsigned int EN12:1;                    /**< \brief [12:12] Access Enable for Master TAG ID n (rw) */
    unsigned int EN13:1;                    /**< \brief [13:13] Access Enable for Master TAG ID n (rw) */
    unsigned int EN14:1;                    /**< \brief [14:14] Access Enable for Master TAG ID n (rw) */
    unsigned int EN15:1;                    /**< \brief [15:15] Access Enable for Master TAG ID n (rw) */
    unsigned int EN16:1;                    /**< \brief [16:16] Access Enable for Master TAG ID n (rw) */
    unsigned int EN17:1;                    /**< \brief [17:17] Access Enable for Master TAG ID n (rw) */
    unsigned int EN18:1;                    /**< \brief [18:18] Access Enable for Master TAG ID n (rw) */
    unsigned int EN19:1;                    /**< \brief [19:19] Access Enable for Master TAG ID n (rw) */
    unsigned int EN20:1;                    /**< \brief [20:20] Access Enable for Master TAG ID n (rw) */
    unsigned int EN21:1;                    /**< \brief [21:21] Access Enable for Master TAG ID n (rw) */
    unsigned int EN22:1;                    /**< \brief [22:22] Access Enable for Master TAG ID n (rw) */
    unsigned int EN23:1;                    /**< \brief [23:23] Access Enable for Master TAG ID n (rw) */
    unsigned int EN24:1;                    /**< \brief [24:24] Access Enable for Master TAG ID n (rw) */
    unsigned int EN25:1;                    /**< \brief [25:25] Access Enable for Master TAG ID n (rw) */
    unsigned int EN26:1;                    /**< \brief [26:26] Access Enable for Master TAG ID n (rw) */
    unsigned int EN27:1;                    /**< \brief [27:27] Access Enable for Master TAG ID n (rw) */
    unsigned int EN28:1;                    /**< \brief [28:28] Access Enable for Master TAG ID n (rw) */
    unsigned int EN29:1;                    /**< \brief [29:29] Access Enable for Master TAG ID n (rw) */
    unsigned int EN30:1;                    /**< \brief [30:30] Access Enable for Master TAG ID n (rw) */
    unsigned int EN31:1;                    /**< \brief [31:31] Access Enable for Master TAG ID n (rw) */
} Ifx_LMU_ACCEN0_Bits;

/** \\brief  LMU Access Enable Register 1 */
typedef struct _Ifx_LMU_ACCEN1_Bits
{
    unsigned int reserved_0:32;             /**< \brief \internal Reserved */
} Ifx_LMU_ACCEN1_Bits;

/** \\brief  LMU Buffer Control Register */
typedef struct _Ifx_LMU_BUFCON_Bits
{
    unsigned int TAG1:6;                    /**< \brief [5:0] Master Tag ID 1 (rw) */
    unsigned int reserved_6:2;              /**< \brief \internal Reserved */
    unsigned int TAG2:6;                    /**< \brief [13:8] Master Tag ID 2 (rw) */
    unsigned int reserved_14:8;             /**< \brief \internal Reserved */
    unsigned int EREN:1;                    /**< \brief [22:22] EMEM Read Buffer Enable (rw) */
    unsigned int EPEN:1;                    /**< \brief [23:23] EMEM Prefetch Enable (rw) */
    unsigned int reserved_24:6;             /**< \brief \internal Reserved */
    unsigned int EN1:1;                     /**< \brief [30:30] TAG1 Field Enable (rw) */
    unsigned int EN2:1;                     /**< \brief [31:31] TAG2 Field Enable (rw) */
} Ifx_LMU_BUFCON_Bits;

/** \\brief  LMU Clock Control Register */
typedef struct _Ifx_LMU_CLC_Bits
{
    unsigned int DISR:1;                    /**< \brief [0:0] Module LMU Disable Request Bit (rw) */
    unsigned int DISS:1;                    /**< \brief [1:1] Module LMU Disable Status Bit (rh) */
    unsigned int reserved_2:30;             /**< \brief \internal Reserved */
} Ifx_LMU_CLC_Bits;

/** \\brief  LMU Memory Control Register */
typedef struct _Ifx_LMU_MEMCON_Bits
{
    unsigned int OLDAEN:1;                  /**< \brief [0:0] Online Data Acquisition Enabled (rw) */
    unsigned int POLDAEN:1;                 /**< \brief [1:1] Protection Bit for OLDAEN (w) */
    unsigned int reserved_2:1;              /**< \brief \internal Reserved */
    unsigned int ERERR:1;                   /**< \brief [3:3] EMEM Read Error (rwh) */
    unsigned int reserved_4:1;              /**< \brief \internal Reserved */
    unsigned int EWERR:1;                   /**< \brief [5:5] EMEM Write Error (rwh) */
    unsigned int DATAERR:1;                 /**< \brief [6:6] SRI Data Phase ECC Error (rwh) */
    unsigned int ADDERR:1;                  /**< \brief [7:7] SRI Address Phase ECC Error (rwh) */
    unsigned int reserved_8:4;              /**< \brief \internal Reserved */
    unsigned int WSTATES:4;                 /**< \brief [15:12] EMEM Wait States (rw) */
    unsigned int reserved_16:16;            /**< \brief \internal Reserved */
} Ifx_LMU_MEMCON_Bits;

/** \\brief  LMU Module ID Register */
typedef struct _Ifx_LMU_MODID_Bits
{
    unsigned int ID_VALUE:32;               /**< \brief [31:0] Module Identification Value (r) */
} Ifx_LMU_MODID_Bits;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Lmu_union
 * \{  */

/** \\brief  LMU Access Enable Register 0 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_LMU_ACCEN0_Bits B;
} Ifx_LMU_ACCEN0;

/** \\brief  LMU Access Enable Register 1 */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_LMU_ACCEN1_Bits B;
} Ifx_LMU_ACCEN1;

/** \\brief  LMU Buffer Control Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_LMU_BUFCON_Bits B;
} Ifx_LMU_BUFCON;

/** \\brief  LMU Clock Control Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_LMU_CLC_Bits B;
} Ifx_LMU_CLC;

/** \\brief  LMU Memory Control Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_LMU_MEMCON_Bits B;
} Ifx_LMU_MEMCON;

/** \\brief  LMU Module ID Register */
typedef union
{
    /** \brief Unsigned access */
    unsigned int U;
    /** \brief Signed access */
    signed int I;
    /** \brief Bitfield access */
    Ifx_LMU_MODID_Bits B;
} Ifx_LMU_MODID;
/** \}  */
/******************************************************************************/
/******************************************************************************/
/** \addtogroup IfxLld_Lmu_struct
 * \{  */
/******************************************************************************/
/** \name Object L0
 * \{  */

/** \\brief  LMU object */
typedef volatile struct _Ifx_LMU
{
    Ifx_LMU_CLC CLC;                        /**< \brief 0, LMU Clock Control Register */
    unsigned char reserved_4[4];            /**< \brief 4, \internal Reserved */
    Ifx_LMU_MODID MODID;                    /**< \brief 8, LMU Module ID Register */
    unsigned char reserved_C[4];            /**< \brief C, \internal Reserved */
    Ifx_LMU_ACCEN0 ACCEN0;                  /**< \brief 10, LMU Access Enable Register 0 */
    Ifx_LMU_ACCEN1 ACCEN1;                  /**< \brief 14, LMU Access Enable Register 1 */
    unsigned char reserved_18[8];           /**< \brief 18, \internal Reserved */
    Ifx_LMU_MEMCON MEMCON;                  /**< \brief 20, LMU Memory Control Register */
    unsigned char reserved_24[12];          /**< \brief 24, \internal Reserved */
    Ifx_LMU_BUFCON BUFCON[3];               /**< \brief 30, LMU Buffer Control Register */
    unsigned char reserved_3C[196];         /**< \brief 3C, \internal Reserved */
} Ifx_LMU;
/** \}  */
/******************************************************************************/
/** \}  */
/******************************************************************************/
/******************************************************************************/
#endif /* IFXLMU_REGDEF_H */
