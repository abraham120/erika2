/*
 * Copyright (c) 2011 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is confidential property of Nordic Semiconductor. The use,
 * copying, transfer or disclosure of such information is prohibited except by express written
 * agreement with Nordic Semiconductor.
 *
 */
/**
  @defgroup nrf_sdm_api SoftDevice Manager API
  @{
     
  @brief APIs for SoftDevice management.
 
*/

/* Header guard */
#ifndef NRF_SDM_H__
#define NRF_SDM_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "nrf_soc.h"
#include "nrf_error_sdm.h"

#ifndef SVCALL
#if defined(__arm__)
#define SVCALL(x) __svc(x)
#else 
#define SVCALL(x)
#endif
#endif  // SVCALL

/**@brief SoftDevice Manager SVC Base number. */
#define SDM_SVC_BASE 0x10   

/**@brief nRF SoftDevice Manager API SVC numbers. */
enum {
  SD_NRF_SOFTDEVICE_ENABLE = SDM_SVC_BASE, /**< ::sd_softdevice_enable */
  SD_NRF_SOFTDEVICE_DISABLE,               /**< ::sd_softdevice_disable */
  SD_NRF_SOFTDEVICE_IS_ENABLED,            /**< ::sd_softdevice_is_enabled */
  SVC_NRF_SDM_LAST                          /**< Placeholder for last SDM SVC */
};

/**@brief Possible lfclk oscillator sources. */
enum {
  NRF_CLOCK_LFCLKSRC_RC_250_PPM,            /**< LFCLK RC oscillator. */
  NRF_CLOCK_LFCLKSRC_SYNTH_250_PPM,         /**< LFCLK Synthesized from hfclk */
  NRF_CLOCK_LFCLKSRC_XTAL_500_PPM,          /**< LFCLK crystal oscillator 500 PPM accuracy */
  NRF_CLOCK_LFCLKSRC_XTAL_250_PPM,          /**< LFCLK crystal oscillator 250 PPM accuracy */
  NRF_CLOCK_LFCLKSRC_XTAL_150_PPM,          /**< LFCLK crystal oscillator 150 PPM accuracy */
  NRF_CLOCK_LFCLKSRC_XTAL_100_PPM,          /**< LFCLK crystal oscillator 100 PPM accuracy */
  NRF_CLOCK_LFCLKSRC_XTAL_75_PPM,           /**< LFCLK crystal oscillator 75 PPM accuracy */
  NRF_CLOCK_LFCLKSRC_XTAL_50_PPM,           /**< LFCLK crystal oscillator 50 PPM accuracy */
  NRF_CLOCK_LFCLKSRC_XTAL_30_PPM,           /**< LFCLK crystal oscillator 30 PPM accuracy */
  NRF_CLOCK_LFCLKSRC_XTAL_20_PPM,           /**< LFCLK crystal oscillator 20 PPM accuracy */
};

/**@brief Type representing lfclk oscillator source. */
typedef uint32_t nrf_clock_lfclksrc_t;

/**@brief SoftDevice Assertion Handler type.
 *
 * When an unexpected error occurs within the SoftDevice it will call the SoftDevice assertion handler callback.
 * The protocol stack will be in an undefined state when this happens and the only way to recover will be to
 * perform a reset, using e.g. CMSIS NVIC_SystemReset().
 *
 * @note This callback is executed in HardFault context, thus SVC functions cannot be called from the SoftDevice assert callback.
 *       
 * @param[in] pc The program counter of the failed assert.
 * @param[in] line_number Line number where the assert failed.
 * @param[in] file_name File name where the assert failed.
 */
typedef void (*softdevice_assertion_handler_t)(uint32_t pc, uint16_t line_number, const uint8_t * p_file_name);

/**@brief Enables the SoftDevice and by extension the protocol stack.
 *
 * Idempotent function to enable the SoftDevice.
 *
 * @note Some care must be taken if a low frequency clock source is already running when calling this function:
 *       If the LF clock has a different source then the one currently running, it will be stopped. Then, the new
 *       clock source will be started.
 *
 * @note This function has no effect when returning with an error.
 *
 * @post If return code is ::NRF_SUCCESS 
 *       - SoC library and protocol stack APIs are made available
 *       - A portion of RAM will be unavailable (see relevant SDS documentation)
 *       - Some peripherals will be unavailable or available only through the SoC API (see relevant SDS documentation)
 *       - Interrupts will not arrive from protected peripherals or interrupts
 *       - nrf_nvic_ functions must be used instead of CMSIS NVIC_ functions for reliable usage of the softdevice.
 *       - Interrupt latency may be affected by the SoftDevice  (see relevant SDS documentation)
 *       - Chosen low frequency clock source will be running
 *
 * @param clock_source Low frequency clock source and accuracy. (Note: In the case of XTAL source, the PPM accuracy of the chosen clock source must be greater than or equal to the actual characteristics of your XTAL clock).
 * @param assertion_handler Callback for SoftDevice assertions.
 *
 * @return ::NRF_SUCCESS
 * @return ::NRF_ERROR_SDM_INCORRECT_INTERRUPT_CONFIGURATION SoftDeviceinterrupt is already enabled, or an enabled interrupt has an illegal priority level
 * @return ::NRF_ERROR_SDM_LFCLK_SOURCE_UNKNOWN Unknown low frequency clock source selected
 */
uint32_t SVCALL(SD_NRF_SOFTDEVICE_ENABLE) sd_softdevice_enable(nrf_clock_lfclksrc_t clock_source, softdevice_assertion_handler_t assertion_handler);

/**@brief Disables the SoftDevice and by extension the protocol stack.
 * 
 * Idempotent function to disable the SoftDevice.
 *
 * @post SoC library and protocol stack APIs are made unavailable.
 * @post All interrupts that was protected by the SoftDevice will be disabled and initialized to priority 0 (highest).
 * @post All peripherals used by the SoftDevice will be reset to default values.
 * @post All of RAM become available.
 * @post All interrupts are forwarded to the application.
 * @post LFCLK source chosen in ::sd_softdevice_enable will be left running.
 *
 * @return ::NRF_SUCCESS
 */
uint32_t SVCALL(SD_NRF_SOFTDEVICE_DISABLE) sd_softdevice_disable(void);

/**@brief Check if the SoftDevice is enabled.
 *
 * @param[out]  p_softdevice_enabled If the SoftDevice is enabled: 1 else 0.
 *
 * @return ::NRF_SUCCESS
 */
uint32_t SVCALL(SD_NRF_SOFTDEVICE_IS_ENABLED) sd_softdevice_is_enabled(uint8_t * p_softdevice_enabled);

#endif // NRF_SDM_H__

/**
  @}
*/
