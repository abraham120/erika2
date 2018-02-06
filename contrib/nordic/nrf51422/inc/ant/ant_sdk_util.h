/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 */

/** @file
 *
 * @defgroup ant_sdk_lib_util Utility Functions and Definitions
 * @{
 * @ingroup ant_sdk_lib
 */

#ifndef ANT_SDK_UTIL_H__
#define ANT_SDK_UTIL_H__

#include <stdint.h>
#include <stdbool.h>
#include "compiler_abstraction.h"

#define PACKED __packed

/**@brief Macro for entering a critical region. */
#define CRITICAL_REGION_ENTER()                                                         \
    {                                                                                   \
        uint8_t IS_NESTED_CRITICAL_REGION;                                              \
        uint32_t ERR_CODE = sd_nvic_critical_region_enter(&IS_NESTED_CRITICAL_REGION); \
        if (ERR_CODE != NRF_SUCCESS)                                                    \
        {                                                                               \
            ASSERT(false);                                                              \
        }                                                     
    
/**@brief Macro for leaving a critical region. */
#define CRITICAL_REGION_EXIT()                                                          \
        ERR_CODE = sd_nvic_critical_region_exit(IS_NESTED_CRITICAL_REGION);            \
        if (ERR_CODE != NRF_SUCCESS)                                                    \
        {                                                                               \
            ASSERT(false);                                                              \
        }                                                                               \
    }
    
/**@brief Perform rounded integer division (as opposed to truncating the result).
 *
 * @param[in]   A   Numerator.
 * @param[in]   B   Denominator.
 * @retval      Rounded (integer) result of dividing A by B.
 */
#define ROUNDED_DIV(A,B) (((A) + ((B) / 2)) / (B))
    
#endif // ANT_SDK_UTIL_H__

/** @} */
