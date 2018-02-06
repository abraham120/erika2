/**
 * @file
 * @brief These are all constants which are used in messages.
 *
 * $Id: timer_const.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef TIMER_CONST_H
#define TIMER_CONST_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros ================================================================ */

/* Please add new timers to the end, and update T_LAST then. */

typedef enum
{
    /* MAC timers */
    T_AckWait =               (0), /**< waiting time for ack */
    T_backoff =               (1), /**< backoff timer */
    T_beacon =                (2), /**< beacon timer */
    T_btp =                   (3), /**< beacon tracking period to wake up radio before beacon is expected */
    T_MaxFrameResponseTime =  (4), /**< timer for maximum frame response time */
    T_AssocResponseTime =     (5), /**< response time for association */
    T_ResponseWaitTime =      (6), /**< waiting time for a response */
    /** the number of symbols from the start of the superframe
        before the receiver is to be enabled */
    T_RxOnTime =              (7),
    T_RxOffTime =             (8), /**< the number of symbols before the receiver is to be enabled */
    T_scan_duration =         (9), /**< timer for measuring the duration of a channel scan */
    T_superframe =            (10),/**< superframe timer */
    T_bt_missedbeacon =       (11),/**< beacon tracking period to count missed beacon frames */

    /* NWK timers */
    T_PERMIT_JOINING =        (12),

    /* Misc timers */
    T_validation =            (13), /**< this timer is started from the validation application */
} mac_timer_t;

#define T_MAC_FIRST_TIMER       T_AckWait
#define T_MAC_LAST_TIMER        T_bt_missedbeacon

#define T_NWK_FIRST_TIMER       T_PERMIT_JOINING
#define T_NWK_LAST_TIMER        T_PERMIT_JOINING

/* bump this when adding timers */
#define T_LAST                  T_validation


/* === Prototypes ============================================================
*/
#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* TIMER_CONST_H */
/* EOF */
