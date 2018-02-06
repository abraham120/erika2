/**
 * @file
 * @brief Declarations for the Basic IO System (BIOS)
 *
 * $Id: bios.h,v 1.1 2007/06/22 13:50:48 romano Exp $
 */
/**
 *  \author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2006, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BIOS_H
#define BIOS_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

#include <stdarg.h>
#include <stdbool.h>

#include "board.h"  // Include before avrtypes.h to avoid redefinition of F_CPU
#include "avrtypes.h"
#include "ieee_const.h"
#include "msg_types.h"

/* === Externals ============================================================= */

extern volatile uint16_t bios_systime;
extern bool bios_queue_watermark;

/* === Types ================================================================= */

#if RADIO_TYPE == AT86RF230 || RADIO_TYPE == AT86RF231_1x || RADIO_TYPE == AT86RF231_2x || defined(DOXYGEN)
/** abstract type of a radio chip register (8 or 32 bits) */
typedef uint8_t radio_reg_t;
/** abstract type of a radio chip SRAM address (currently 8 bits) */
typedef uint8_t radio_ram_t;
#endif /* RADIO_TYPE == AT86RF230 || RADIO_TYPE == AT86RF231_1x ||  RADIO_TYPE == AT86RF231_2x */

/**
 * This defines the structure of the time type.
 */
typedef struct time_struct_tag
{
    /** This elements points to the next time structure. */
    int8_t      link;
    /** This identifies the timer. */
    uint8_t     tid;
    /** This is the time when it should expire. */
    uint32_t    expire;
} time_struct_t;


/**
 * callback for timer functions
 */
typedef void (*timer_callback_t)(void);

/* === Macros ================================================================ */

/** The smallest timeout in symbol periods (SIFS) */
#define BIOS_MIN_TIMEOUT        (8)
/** The largest timeout in symbol periods */
#define BIOS_MAX_TIMEOUT        (0x07ffffff)

#define SRAM_AVAILABLE 1

/* === Prototypes ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup BIOS BIOS Interface

    This group contains the interface of the BIOS
*/
/*@{*/

#if DEBUG || defined(DOXYGEN)
void bios_assert(int expr, FLASH_STRING_T sexpr, char *file, int name);
void bios_print(FLASH_STRING_T fmt, ...);
void bios_echo(FLASH_STRING_T pData);

/** DEBUG only: test for an assertion, similar to Std-C assert() */
# define ASSERT(expr)    bios_assert(expr, FLASH_STRING( #expr ), __FILE__, __LINE__)
/** DEBUG only: send an ECHO.indication with \c msg */
# define ECHO(msg)       bios_echo(FLASH_STRING(msg))
/** DEBUG only: send an ECHO.indication using a printf-style
 *  format string plus arbitrary arguments
 */
# define PRINT(fmt, ...) bios_print(FLASH_STRING(fmt), __VA_ARGS__)

#else  /* !DEBUG */

# define ASSERT(expr)
# define ECHO(msg)
# define PRINT(fmt, ...)

#endif /* DEBUG */

void bios_abort(void);
void bios_jump_bootloader(void);

void bios_bit_read(uint8_t addr, radio_reg_t mask, uint8_t pos, radio_reg_t *data);
void bios_bit_write(uint8_t addr, radio_reg_t mask, uint8_t pos, radio_reg_t value);

void bios_fasttimer(uint8_t timeout, timer_callback_t handler);

#if !(RADIO_TYPE == AT86RF231_1x || RADIO_TYPE == AT86RF231_2x)
uint8_t bios_frame_crc_read(uint8_t * data);
#endif /* !(RADIO_TYPE == AT86RF231_1x || RADIO_TYPE == AT86RF231_2x) */
uint8_t bios_frame_read(uint8_t * data);
void bios_frame_write(uint8_t length, uint8_t *data);

#if !(RADIO_TYPE == AT86RF231_1x || RADIO_TYPE == AT86RF231_2x)
void bios_gen_crc16(octetstr_t *msg);
#endif /* !(RADIO_TYPE == AT86RF231_1x || RADIO_TYPE == AT86RF231_2x) */

uint64_t bios_get_ieee_addr(void);

uint32_t  bios_gettime(void);

void bios_init(void);

bool bios_pinset(uint8_t pin, uint8_t value);
bool bios_pinget(uint8_t pin, uint8_t *pvalue);

uint8_t* bios_popfront_event(void);
bool bios_pushback_event(void *event);
void bios_dispatch_event(uint8_t *event);

radio_reg_t bios_reg_read(uint8_t addr);
void bios_reg_write(uint8_t addr, radio_reg_t val);

void bios_reset_hardware(void);

void bios_sleep(uint32_t sleep_time);

void bios_intern_timer_handler(void);
bool bios_start_absolute_timer(uint8_t timer_id, uint32_t point_in_time);
bool bios_starttimer(uint8_t timer_id, uint32_t timeout);
bool bios_stoptimer(uint8_t timer_id);

/**
 * Add two timers a+b and take care of the precission
 * @param a value
 * @param b value
 * @return value of a+b
 */
static inline uint32_t bios_add_time(uint32_t a, uint32_t b)
{
    return (a + b) & TMR1_INTERNAL_MASK;
}

/**
 * Subtract two timers a-b and take care of the precission
 * @param a value
 * @param b value
 * @return value a-b
 */
static inline uint32_t bios_sub_time(uint32_t a, uint32_t b)
{
    return (a - b) & TMR1_INTERNAL_MASK;
}

/**
 * @brief
 * This functions checks whether the BIOS could start a timer with
 * the specified timeout.
 * @param timeout is the timeout in symbol periods
 * @return true if the timeout is in a range that bios could handle
 */
static inline bool bios_check_timeout( uint32_t timeout )
{
    bool ret = false;

    if (timeout > BIOS_MIN_TIMEOUT)
    {
        if (timeout < BIOS_MAX_TIMEOUT)
        {
            ret= true;
        }
    }
    return ret;
}

/**
 * @brief This function returns the status of the queue.
 * @return true if queue is about to be full soon
 */
static inline bool bios_queue_full(void)
{
    return bios_queue_watermark;
}

void bios_sram_write(radio_ram_t addr, uint8_t length, uint8_t *data);
void bios_sram_read(radio_ram_t addr, uint8_t length, uint8_t *data);

/*@}*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*BIOS_H*/
/* EOF */
