/**
 * @file
 * @brief Defines, macros and function prototypes for board abstraction
 *
 * $Id: board.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef BOARD_H
#define BOARD_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

#include "project.h"

#if BOARD_TYPE == EMU230
#   include "board_def_emu230.h"
#elif BOARD_TYPE == EVAL230
#   include "board_def_eval230.h"
#elif BOARD_TYPE == EMU231
#   include "board_def_emu231.h"
#elif BOARD_TYPE == RDK230
#   include "board_def_rdk230.h"
#elif BOARD_TYPE == EVAL231
#   include "board_def_eval231.h"
//#elif BOARD_TYPE == ...
//...
#else
# error "Unknown board type"
#endif /* BOARD_TYPE */

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros ================================================================ */

#if RF_BAND == BAND_2400
#  define SYMBOLS_PER_OCTET (2)  /** 4 bits form one symbol since O-QPSK is used */
#elif RF_BAND == BAND_900
#  define SYMBOLS_PER_OCTET (8)  /** 1 bit forms one symbol since BPSK is used */
#else
#  error "Unsupported RF band"
#endif

/* === Prototypes ============================================================ */

#if !defined(SLEEP_ENABLED)
/** Whether to put the CPU on sleep while idle. */
#  define SLEEP_ENABLED 0
#endif

#if !defined(HAS_USB)
/** Per default we have no USB. */
#  warning "HAS_USB is not defined by board_def*.h"
#  define HAS_USB 0
#endif


/** Debug PIN-F macros for test of absolute timers on RDK230. */
#if DEBUG
    #define PORT_SET(pin)       (PORTF |= (1 << pin))
    #define PORT_CLR(pin)       (PORTF &= (~(1 << pin)))
#else  /* !DEBUG */
    #define PORT_SET(pin)
    #define PORT_CLR(pin)
#endif /* DEBUG */

#ifdef __cplusplus
extern "C" {
#endif

#if HAS_USB == 1
void init_usb(void);
void usb_handler(void);
void usb_write(uint8_t *message);
#else
void init_uart(void);
void uart_write(uint8_t *message);
#endif

void board_irq_init(void);
uint8_t send_intern(uint8_t msg_type);
uint8_t send_to_uart(uint8_t msg_type);
void set_intern_routing(uint8_t msg_type, uint8_t state);
void set_uart_routing(uint8_t msg_type, uint8_t state);
void bios_timer_handler(void);
void bios_timer_init(void);

#if BOARD_TYPE == EMU230 || BOARD_TYPE == EVAL230 || BOARD_TYPE == EMU231 || \
    BOARD_TYPE == RDK230 || BOARD_TYPE == EVAL231
void spi_init (void);
void spi_set_rate (uint8_t);

#  if RADIO_TYPE == AT86RF231_1x
void bios_activate_slptr_timer(void);
#  endif

#endif /* BOARD_TYPE == *23[01] ... */

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*BOARD_H*/
/* EOF */
