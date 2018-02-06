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
 * @defgroup ant_app_timer Application Timer
 * @{
 * @brief Application timer functionality.
 *
 * @details It enables the application to create multiple timer instances based on the RTC1
 *          timer peripheral. Applications using app_timer must have a configuration file named
 *          app_timer_cfg.h (see @ref ble_sdk_apps_config_files for details).
 *
 * @note Due to a problem in the way the application uses the RTC peripheral, timer interrupts
 *       may be lost. Therefore, the current implementation is not reliable, and should not be used
 *       in production code.
 */

#ifndef APP_TIMER_H__
#define APP_TIMER_H__

#include <stdint.h>
#include <stdbool.h>
#include "app_timer_cfg.h"

#define APP_TIMER_HIGHEST_PRI  0x00                 /**< Highest timer priority. */
#define APP_TIMER_LOWEST_PRI   0xff                 /**< Lowest timer priority. */

/**@brief Available timer modes. */
typedef enum {
    APP_TIMER_MODE_SINGLE_SHOT,
    APP_TIMER_MODE_REPEATED
} app_timer_mode_t;

/**@brief Application timeout handler type. */
typedef void (*app_timer_timeout_handler_t) (app_timer_id_t timer_id);

/**@brief Function pointer type for letting the application control how or when timeout handlers are
 *        executed. This will be used for connecting the timer module to the scheduler. 
 */
typedef uint32_t (*app_timer_issue_evt_func_t) (app_timer_id_t              timer_id,
                                                app_timer_timeout_handler_t timeout_handler,
                                                uint8_t                     priority);

/**@brief Initializes the timer module.
 *
 * @param[in]  issue_timeout_evt_func   Function for letting the application control how or when
 *                                      timeout handlers are executed. Normally this will be used
 *                                      for making the timer module pass timeout events to the
 *                                      scheduler (by supplying a pointer to
 *                                      app_sched_timer_event_schedule()). Set to NULL to make the
 *                                      timer module call the timeout handler directly from the
 *                                      timer interrupt handler.
 * @retval     NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t app_timer_init(app_timer_issue_evt_func_t issue_evt_func);

/**@brief Checks if the specified timer is running.
 *
 * @param[in]  timer_id   Timer ID of the timer to check.
 * @retval     true if timer is running, false otherwise.
 */
bool app_timer_is_running(app_timer_id_t timer_id);

/**@brief Starts a timer.
 *
 * @param[in]  timer_id          Id of timer to start.
 * @param[in]  timeout_handler   Handler to be called when timer expires.
 * @param[in]  timeout_ms        Number of milliseconds to timeout event.
 * @param[in]  mode              Timer mode.
 * @param[in]  priority          Priority level at which the timeout handler will be run. When using
 *                               the scheduler, this will be the scheduler queue id. When not using
 *                               the scheduler, this value will be ignored.
 * @retval     NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t app_timer_start(app_timer_id_t              timer_id, 
                         app_timer_timeout_handler_t timeout_handler,
                         uint32_t                    timeout_ms,
                         app_timer_mode_t            mode, 
                         uint8_t                     priority);

/**@brief Stops the specified timer.
 *
 * @param[in]  timer_id        Id of timer to stop.
 */
void app_timer_stop(app_timer_id_t timer_id);

#endif // APP_TIMER_H__

/** @} */
