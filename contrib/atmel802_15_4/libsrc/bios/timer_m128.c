/**
 * @file
 *
 * @brief BIOS timer service implementation for ATmega1281 MCUs.
 * This is close to the ATmega128 implementation but several registers
 * changed names
 *
 * $Id: timer_m128.c,v 1.1 2007/06/22 13:50:48 romano Exp $
 *
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

/* === Includes ============================================================ */

#include <stdbool.h>
#ifndef DEF_H
#include "def.h"
#endif

#include "board.h"
#include "bios.h"
#include "avrtypes.h"
#include "msg_const.h"
#include "msg_types.h"

#if CPU_TYPE == M128 || defined(DOXYGEN)

/* === Typedefs ============================================================ */

/* === Macros ============================================================== */

/* === Globals ============================================================= */

/** This is the most significant part of the system time. The least one is
    timer1 (TCNT1) itself.  Exported since input capture units might want
    to know about this value as well. */
volatile uint16_t           bios_systime;

#if APP_TYPE >= APP_L0 || defined(DOXYGEN)
/** These are the elements of the timer queue. */
static time_struct_t    timers[MAX_TIMER_QUEUE_SIZE];
/** This array contains a sorted list of indexes to the elements of the timer
 * queue */
static uint8_t          timer_queue[MAX_TIMER_QUEUE_SIZE];

/** This is the counter of all running timers. */
static volatile uint8_t     running_timers;
/** This index points to the timers which expires next. */
static volatile uint8_t     next_trigger;
/** This index points to the timer which expires at last. */
static volatile uint8_t     last_trigger;
/** This is a flag, that should indicate an expired timer. */
static volatile uint8_t     timer_trigger;
/**
 * Remembered value of the callback to call when fasttimer fires.
 */
static timer_callback_t     fasttimer_callback;

#endif /* APP_TYPE >= APP_L0 || defined(DOXYGEN) */

/* === Prototypes ========================================================== */

/* === Implementation ====================================================== */


/**
 * @brief get actual system time
 * This function is called to get the system time.
 * @return is the system time with symbol resolution.
 */
uint32_t  bios_gettime(void)
{
    uint16_t tmp;
    uint32_t back;

    do
    {
        tmp = bios_systime;
        back = tmp;
        back = back << 16;
        back = back | TCNT1;
    } while (tmp != bios_systime);

    return (back / TMR1_INTERNAL_SCALE) & TMR1_INTERNAL_MASK;
}


/**
 * @brief program output compare register OCR1A
 * This function is programming the output compare register to trigger an
 * interrupt when the next timer expires.
 */
#if APP_TYPE >= APP_L0 || defined(DOXYGEN)
static void prog_ocr(void)
{
    uint16_t  exp_hi, exp_lo;
    uint32_t  tmp;

    if (running_timers > 0)
    {
        tmp = timers[timer_queue[0]].expire * TMR1_INTERNAL_SCALE;
        exp_hi = tmp >> 16;
        exp_lo = tmp & 0xffff;

        if (exp_hi == bios_systime)
        {
            /* program output compare match */
            OCR1A = exp_lo;
            /* clear pending output compare matches */
            TIFR  = _BV(OCF1A);
            /* enable output compare match interrupt */
            TIMSK |= _BV(OCIE1A);
        }
        /* safty check: Trigger timer, if next_trigger is in the past */
        if(bios_sub_time(timers[timer_queue[0]].expire, bios_gettime()) > BIOS_MAX_TIMEOUT)
        {
            timer_trigger++;
        }
    }
}

/**
 * @brief internal timer handler
 * This handles the timers inside the BIOS
 */
void bios_intern_timer_handler(void)
{
    uint8_t tpos, i;

    if (timer_trigger > 0)
    {
        timer_expired_ind_t tm;

        if (running_timers != 0)
        {
            /* send timeout message */
            tm.size    = sizeof(timer_expired_ind_t) - sizeof(tm.size);
            tm.cmdcode = TIMER_EXPIRED_INDICATION;
            tm.tid     = timers[timer_queue[0]].tid;
            bios_pushback_event(&tm);

            tpos = timer_queue[0];
            running_timers--;

            /* collaps timer array */
            for (i = tpos; i < running_timers; i++)
            {
                timers[i].tid    = timers[i+1].tid;
                timers[i].expire = timers[i+1].expire;
            }
            /* collaps timer queue */
            for (i = 0; i < running_timers; i++)
            {
                timer_queue[i] = timer_queue[i+1];
            }
            /* fix timer queue indexes, that got shifted */
            for (i = 0; i < running_timers; i++)
            {
                if (timer_queue[i] > tpos)
                {
                    timer_queue[i] = timer_queue[i] - 1;
                }
            }
            TIMSK &= ~_BV(OCIE1A);
            timer_trigger = 0;
            prog_ocr();
        }
        else
        {
            timer_trigger = 0;
        }
    }
}


/**
 * @brief start a timer by setting its absolute expiration time
 * This function starts a timer which should expire at the point_in_time value
 * @param timer_id       is the timer idenitifier.
 * @param point_in_time  is the point in time in symbol periods
 * @return true if successful
 */
bool bios_start_absolute_timer(uint8_t timer_id, uint32_t point_in_time)
{
    bool        ret;
    uint8_t     new;
    uint8_t     i;

    /* disable all interrupts */
    cli();

    bios_intern_timer_handler();

    ret = false;
    if (running_timers < MAX_TIMER_QUEUE_SIZE)
    {
        uint32_t now     = bios_gettime(); /* in symbols */
        uint32_t expire  = point_in_time & TMR1_INTERNAL_MASK;  /* in symbols */
        uint32_t timeout = bios_sub_time(expire, now);

        ret = true;
        if (bios_check_timeout(timeout))
        {
            /* insert timer */
            timers[running_timers].tid    = timer_id;
            timers[running_timers].expire = expire;

            /* find the right position inside the queue */
            new = 0;
            while ((new < running_timers) &&
                    (timeout > bios_sub_time(timers[timer_queue[new]].expire, now)))
            {
                new++;
            }
            /* shift the rest of the queue by 1 to make some room */
            for (i = MAX_TIMER_QUEUE_SIZE - 1; i > new; i--)
            {
                timer_queue[i] = timer_queue[i-1];
            }
            /* set the index */
            timer_queue[new] = running_timers;
            running_timers++;
            prog_ocr();
        }
        else
        {
            ret = false;
        }
    }

    /* enable all interrupts */
    sei();

    return ret;
}

/**
 * @brief start a timer by setting a timeout value
 * This function starts a timer which should expire after timeout value
 * @param timer_id is the timer idenitifier.
 * @param timeout  is the timeout in symbol periods
 * @return true if successful
 */
bool bios_starttimer(uint8_t timer_id, uint32_t timeout)
{
    uint32_t now     = bios_gettime(); /* in symbols */
    uint32_t point_in_time = bios_add_time(timeout, now);

    return(bios_start_absolute_timer(timer_id, point_in_time));
}

/**
 * @brief This function stops a timer.
 * @param timer_id is the timer identifier.
 * @return true if successful
 */
bool bios_stoptimer(uint8_t timer_id)
{
    bool      ret;
    uint8_t   pos, tpos, i;

    cli();

    bios_intern_timer_handler();

    ret = false;
    if (running_timers != 0)
    {
        /* search for the timer id */
        for (pos = 0;
             (pos < running_timers) && (timers[timer_queue[pos]].tid != timer_id);
             pos++)
        {
        }
        if ((pos < running_timers) && (timers[timer_queue[pos]].tid == timer_id))
        {
            /* found it ! */
            tpos = timer_queue[pos];
            /* collaps timer array */
            for (i = tpos; i < running_timers-1; i++)
            {
                timers[i].tid    = timers[i+1].tid;
                timers[i].expire = timers[i+1].expire;
            }
            /* collaps timer queue */
            for (i = pos; i < running_timers-1; i++)
            {
                timer_queue[i] = timer_queue[i+1];
            }
            running_timers--;

            /* fix timer queue indexes, that got shifted */
            for (i = 0; i < running_timers; i++)
            {
                if (timer_queue[i] > tpos)
                {
                    timer_queue[i] = timer_queue[i] - 1;
                }
            }
            TIMSK &= ~_BV(OCIE1A);
            prog_ocr();
        }
    }
    sei();
    return ret;
}

/**
 * @brief start alternative fast timer
 * bios_fasttimer uses the OC1B compare match for launching
 * an user defined callback routine
 *
 * \param timeout 8 bit Timeout period, in symbols.
 * \param handler Function to call when the timer expires.
 */
void bios_fasttimer(uint8_t timeout, timer_callback_t handler)
{
    uint16_t timer_ocr;

    fasttimer_callback = handler;

    timer_ocr = TCNT1;
    timer_ocr += (uint16_t)(timeout * SYMBOL_PERIOD);
    /* program output compare match */
    OCR1B = timer_ocr;
    /* clear pending output compare matches */
    TIFR  = _BV(OCF1B);
    /* enable output compare match interrupt */
    TIMSK |= _BV(OCIE1B);
}
#endif /* APP_TYPE >= APP_L0 || defined(DOXYGEN) */

/**
 * @brief This function does the timer initilization.
 */
void bios_timer_init(void)
{
#if APP_TYPE >= APP_L0
    running_timers = 0;
    timer_trigger  = 0;
#endif /* APP_TYPE >= APP_L0 */
    bios_systime   = 0;

    TCCR1B |= TMR1_CFG_B;
    TIMSK |= _BV(TOIE1);
}

#if defined(DOXYGEN)
/**
 * @brief Timer Overflow ISR
 * This is the interrupt service routine for timer1 overflow.
 * It is triggered every 65536 * 8 us, if clk_io == 1MHz.
 *
 */
void TIMER1_OVF_vect(void);
#else  /* !DOXYGEN */
ISR (TIMER1_OVF_vect)
{
    bios_systime++;   // Running at clock time (1 MHz for RF230 system)
#  if APP_TYPE >= APP_L0
    prog_ocr();
#  endif /* APP_TYPE >= APP_L0 */
}
#endif /* defined(DOXYGEN) */

#if APP_TYPE >= APP_L0 || defined(DOXYGEN)

#  if defined(DOXYGEN)
/**
 * @brief Timer1 COMPA ISR
 * This is the interrupt service routine for timer1 output compare match.
 * It is triggered when a timer expires.
 */
void TIMER1_COMPA_vect(void);
#  else  /* !DOXYGEN */
ISR (TIMER1_COMPA_vect)
{
    if (running_timers > 0)
    {
        timer_trigger++;
    }
}
#  endif /* defined(DOXYGEN) */

#  if defined(DOXYGEN)
/**
 * @brief ISR for fasttimer, triggered by OCR1B
 * This is the interrupt service routine for timer1.OCR1B output compare match.
 * It is triggered when a timer expires.
 */
void TIMER1_COMPB_vect(void);
#  else  /* !DOXYGEN */
ISR (TIMER1_COMPB_vect)
{
    //turn off timer1 OCR1B interrupt
    TIMSK &= ~_BV(OCIE1B);

    sei();
    ASSERT(fasttimer_callback != NULL);
    if (fasttimer_callback != NULL)
    {
        fasttimer_callback();
    }
}
#  endif /* defined(DOXYGEN) */

#endif /* APP_TYPE >= APP_L0 || defined(DOXYGEN) */

#endif /* CPU_TYPE == M128 */

/* EOF */
