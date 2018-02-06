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

#include "ant_app_timer.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "nrf_assert.h"
#include "nrf_soc.h"
#include "app_util.h"


#define RTC_CLOCK_FREQ  32768
#define MAX_RTC_COUNTER 0xFFFFFF

/**@brief Computed value of the RTC prescaler register. */
#define RTC_PRESCALER   (ROUNDED_DIV(RTC_CLOCK_FREQ, APP_TIMER_FREQ) - 1)
    
/**@brief Compute the required value of the Capture Compare register to get the specified delay.
 *
 * @details This macro will take into account the fact that the actual counting rate of the RTC
 *          timer may be slightly different than the value being requested by the application in
 *          APP_TIMER_FREQ.
 *
 * @param[in]   DELAY_MS   Delay duration in number of milliseconds.
 * @retval      Value to be passed to the RTC Capture Compare register.
 */
#define RTC_COUNTER_COMPUTE(DELAY_MS)\
    ROUNDED_DIV((uint64_t)(DELAY_MS) * RTC_CLOCK_FREQ, 1000 * (RTC_PRESCALER + 1))

/**@brief Macro for checking if the timer queue is empty. */
#define TIMER_QUEUE_EMPTY()     (sp_timer_queue == NULL)

/**@brief Macro for checking if the timer queue is not empty. */
#define TIMER_QUEUE_NOT_EMPTY() (sp_timer_queue != NULL)

/**@brief Timer queue structure.
 *
 * @details The timer queue is a linked list of all the active timers.
 */
typedef struct app_timer_s
{
    app_timer_mode_t              mode;                 /**< Timer mode. */
    app_timer_id_t                timer_id;             /**< Timer id. */
    app_timer_timeout_handler_t   timeout_handler;      /**< Handler to call when the timer expires. */
    uint32_t                      time_units_left;      /**< Number of time units left until the timer expires. */
    uint32_t                      time_units_timeout;   /**< Duration from the timer is started until it is supposed to expire. */
    uint8_t                       priority;             /**< Priority level at which the timeout handler will be run. When using the scheduler, this will be the scheduler queue id. When not using the scheduler, this value will be ignored. */
    volatile struct app_timer_s * p_next;               /**< Pointer to next running timer. */
} app_timer_t;

/**@brief Array holding all available timers. */
static volatile app_timer_t s_timer_queue_mem[APP_TIMER_LAST_ELEMENT];

/**@brief Pointer to head of timer queue. */
static volatile app_timer_t * volatile sp_timer_queue = NULL;

/**@brief Pointer to functions for issuing the timeout event (will normally be used for passing the 
 *        event to the scheduler). */
static app_timer_issue_evt_func_t s_issue_evt_func = NULL;


static void queue_add(const app_timer_t * timer);
static void queue_remove_first(void);
static void timers_update(uint32_t elapsed_time_units);


static uint32_t rtc_init(void)
{
    uint32_t err_code;
    
    // Initialize RTC
    NRF_RTC1->PRESCALER = RTC_PRESCALER;
    NRF_RTC1->CC[0]     = MAX_RTC_COUNTER;
    NRF_RTC1->EVTENSET  = RTC_EVTENSET_COMPARE0_Msk;
    NRF_RTC1->INTENSET  = RTC_INTENSET_COMPARE0_Msk;

    // Enable RTC event interrupt
    err_code = sd_nvic_ClearPendingIRQ(RTC1_IRQn);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = sd_nvic_SetPriority(RTC1_IRQn, NRF_APP_PRIORITY_LOW);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    err_code = sd_nvic_EnableIRQ(RTC1_IRQn);
    if (err_code != NRF_SUCCESS)
    {
        return err_code;
    }
    
    return NRF_SUCCESS;
}


static uint32_t rtc_counter_get(void)
{
    return (uint32_t)NRF_RTC1->COUNTER;
}


static void rtc_comparereg_update(uint32_t time_units)
{
    ASSERT(time_units < MAX_RTC_COUNTER);

    if (time_units > NRF_RTC1->COUNTER)
    {
        NRF_RTC1->CC[0] = time_units;
    }
    else
    {
        // Timeout should already have occured
        NRF_RTC1->CC[0] = NRF_RTC1->COUNTER + 1;
    }
}


static void rtc_start(void)
{
    NRF_RTC1->TASKS_CLEAR = 1;
    NRF_RTC1->TASKS_START = 1;
}


static void rtc_stop(void)
{
    NRF_RTC1->TASKS_STOP  = 1;
    NRF_RTC1->TASKS_CLEAR = 1;
}


/** RTC interrupt handler.
*/
void RTC1_IRQHandler()
{
    if (
        (NRF_RTC1->EVENTS_COMPARE[0] != 0) 
        && 
        ((NRF_RTC1->INTENSET & RTC_INTENSET_COMPARE0_Msk) != 0)
    )
    {
        // Clear event
        NRF_RTC1->EVENTS_COMPARE[0] = 0;
        
        // Stop timer
        NRF_RTC1->TASKS_CLEAR = 1;

        // Call event handler
        timers_update(NRF_RTC1->CC[0]);
    }
}


uint32_t app_timer_init(app_timer_issue_evt_func_t issue_evt_func)
{
    s_issue_evt_func = issue_evt_func;
    return rtc_init();
}


bool app_timer_is_running(app_timer_id_t timer_id)
{
    bool                   timer_found = false;
    volatile app_timer_t * p_queue_entry;
    
    CRITICAL_REGION_ENTER();
    
    p_queue_entry = sp_timer_queue;
    while (p_queue_entry != NULL)
    {
        if (p_queue_entry->timer_id == timer_id)
        {
           timer_found = true;
           break;
        }
        p_queue_entry = p_queue_entry->p_next;
    }
    
    CRITICAL_REGION_EXIT();
    
    return timer_found;
}


uint32_t app_timer_start(app_timer_id_t              timer_id, 
                         app_timer_timeout_handler_t timeout_handler,
                         uint32_t                    timeout_ms, 
                         app_timer_mode_t            mode, 
                         uint8_t                     priority)
{
    uint32_t err_code;
    
    // Stop timer if running
    app_timer_stop(timer_id);

    if (timeout_ms > 0)
    {
        // Start timer
        app_timer_t timer;
        uint32_t    rtc_cc_reg = RTC_COUNTER_COMPUTE(timeout_ms);
        
        timer.mode               = mode;
        timer.timer_id           = timer_id;
        timer.timeout_handler    = timeout_handler;
        timer.time_units_left    = rtc_cc_reg + rtc_counter_get();
        timer.time_units_timeout = rtc_cc_reg;
        timer.priority           = priority;
        
        CRITICAL_REGION_ENTER();
        queue_add(&timer);
        CRITICAL_REGION_EXIT();
        
        err_code = NRF_SUCCESS;
    }
    else
    {
        if (mode == APP_TIMER_MODE_SINGLE_SHOT)
        {
            // Execute timeout handler immediately, either by calling it directly,
            // or through the "issue" function.
            if (s_issue_evt_func != NULL)
            {
                err_code = (*s_issue_evt_func)(timer_id, timeout_handler, priority);
            }
            else
            {
                (*timeout_handler)(timer_id);
                err_code = NRF_SUCCESS;
            }
        }
        else
        {
            // Repeated timer with timout equal 0 not allowed
            err_code = NRF_ERROR_INVALID_PARAM;
        }
    }
        
    return err_code;
}


void app_timer_stop(app_timer_id_t timer_id)
{
    CRITICAL_REGION_ENTER();
    
    if (TIMER_QUEUE_NOT_EMPTY())
    {
        volatile app_timer_t * p_queue_entry = sp_timer_queue;
        
        if (p_queue_entry->timer_id == timer_id)
        {
            // Match on first element
            sp_timer_queue = p_queue_entry->p_next;
            if (sp_timer_queue == NULL)
            {
                rtc_stop();
            }
            else
            {
                rtc_comparereg_update(sp_timer_queue->time_units_left);
            }
        }
        else
        {   
            while (p_queue_entry->p_next != NULL)
            {
                if (p_queue_entry->p_next->timer_id == timer_id)
                {
                   // Match in middle or end of queue
                   p_queue_entry->p_next = p_queue_entry->p_next->p_next;
                   break;
                }
                p_queue_entry = p_queue_entry->p_next;
            }
        }
    }
    
    CRITICAL_REGION_EXIT();
}


/**@brief Callback called from the RTC interrupt. Keeps track of the timeouts.
 *
 * @param[in]  elapsed_time_units   Number of elapsed time units since the last time the handler was
 *                                  called.
 */
static void timers_update(uint32_t elapsed_time_units)
{
    volatile app_timer_t * p_queue_entry;
    
    // NOTE: This function will be called from the RTC interrupt handler, which runs in
    //       App Low interrupt level. If starting timers from App High is to be supported, the
    //       list handling in this function needs to be protected by a critical region.

    ASSERT(TIMER_QUEUE_NOT_EMPTY());

    // Update timer queue
    p_queue_entry = sp_timer_queue;
    while (p_queue_entry != NULL)
    {
        if (p_queue_entry->time_units_left > elapsed_time_units)
        {
            p_queue_entry->time_units_left -= elapsed_time_units;
        }
        else
        {
            p_queue_entry->time_units_left = 0;
        }
        p_queue_entry = p_queue_entry->p_next;
    }
    
    // Handle timeouts
    // NOTE: The timer queue is sorted, so if first timer in queue has not expired, none have.
    while (TIMER_QUEUE_NOT_EMPTY() && (sp_timer_queue->time_units_left == 0))
    {
        // Execute timeout handler, either by calling it directly, or through the "issue" function
        if (s_issue_evt_func != NULL)
        {
            uint32_t               err_code;
            volatile app_timer_t * p_timer = sp_timer_queue;
            
            err_code = (*s_issue_evt_func)(p_timer->timer_id,
                                           p_timer->timeout_handler,
                                           p_timer->priority);
            if (err_code != NRF_SUCCESS)
            {
                ASSERT(false);
            }
        }
        else
        {
            volatile app_timer_t * p_timer = sp_timer_queue;
            
            (*p_timer->timeout_handler)(p_timer->timer_id);
        }

        if (sp_timer_queue->mode == APP_TIMER_MODE_REPEATED)
        {   
            // Repeated timer, restart
            app_timer_t timer;
            
            timer.mode               = sp_timer_queue->mode;
            timer.timer_id           = sp_timer_queue->timer_id;
            timer.timeout_handler    = sp_timer_queue->timeout_handler;
            timer.time_units_left    = sp_timer_queue->time_units_timeout;
            timer.time_units_timeout = sp_timer_queue->time_units_timeout;
            timer.priority           = sp_timer_queue->priority;
            
            queue_remove_first();
            queue_add(&timer);
        }
        else
        {
            // Stop timer
            queue_remove_first();
        }
    }

    if (TIMER_QUEUE_EMPTY())
    {
        rtc_stop();
    }  
}


/**@brief Put a timer in the queue.
 *
 * @param[in]  p_timer   Pointer to timer structure.
 */
static void queue_add(const app_timer_t *p_timer)
{
    volatile app_timer_t * p_new_timer;
    
    // Allocate new timer
    p_new_timer  = &s_timer_queue_mem[p_timer->timer_id];
    *p_new_timer = *p_timer;
    
    // Insert timer in sorted timer queue
    if (TIMER_QUEUE_EMPTY())
    {
        // Insert timer as the only timer in queue
        sp_timer_queue         = p_new_timer;
        sp_timer_queue->p_next = NULL;

        rtc_comparereg_update(p_new_timer->time_units_left);
        rtc_start();
    }
    else
    {
        volatile app_timer_t * p_queue_entry = sp_timer_queue;
        
        if (p_new_timer->time_units_left < p_queue_entry->time_units_left)
        {
          // Insert timer at the beginning of the queue
          sp_timer_queue         = p_new_timer;
          sp_timer_queue->p_next = p_queue_entry;
          
          rtc_comparereg_update(p_new_timer->time_units_left);
        }
        else
        {
            while (p_queue_entry->p_next != NULL)
            {
                if (p_new_timer->time_units_left < p_queue_entry->p_next->time_units_left)
                {
                    // Insert timer in middle of queue
                    p_new_timer->p_next   = p_queue_entry->p_next;
                    p_queue_entry->p_next = p_new_timer;
                    
                    break;
                }
                p_queue_entry = p_queue_entry->p_next;
            }
            
            // Check if new timer is last
            if (p_queue_entry->p_next == NULL)
            {
                // Insert timer at the end of the queue
                p_queue_entry->p_next = p_new_timer;
                p_new_timer->p_next   = NULL;
            }
        }
    }
}


/**@brief Removes the first timer in the queue.
 */
static void queue_remove_first(void)
{
    sp_timer_queue = sp_timer_queue->p_next;
    if (TIMER_QUEUE_NOT_EMPTY())
    {
        rtc_comparereg_update(sp_timer_queue->time_units_left);
    }
}
