/**
 * @file
 *
 * @brief This file holds all project specific declarations.
 *
 * $Id: project.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef PROJECT_H
#define PROJECT_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros =============================================================== */

#define TRUE (1)
#define FALSE (0)

/* IEEE 802.15.4 device types, global macro DEVICE_TYPE */
#define FD1        (1)          /* full-function device, FFD */
#define FD1_NOGTS  (3)          /* FFD without GTS */
#define FD2        (2)          /* reduced-function device, RFD */
#define FD2_ACTSC  (4)          /* RFD with active scan */
#if !defined(DEVICE_TYPE)
#   define DEVICE_TYPE FD1_NOGTS
#endif

#if DEVICE_TYPE == FD1
#error      FD1 is currently NOT supported
#endif

/* UART communication framing */

/** The start of transmission delimiter. */
#define SOT (1)
/** The end of transmission delimiter. */
#define EOT (4)

/** identifier for sleep pin (EMU230) */
#define TRX_PIN_SLEEP (1)

/** identifier for reset pin (EMU230) */
#define TRX_PIN_RESET (2)

/** identifier for TEST pin (AT86RF230, read-write) */
#define TRX_PIN_TEST   (3)

/* application types */
#define LIB_HAL  (0)           /**< library, which contains just the HAL access */
#define APP_L0   (1)           /**< application, which contains the HAL only (basic PHY hardware access + queue + timer)*/
#define APP_L1   (10)           /**< application, which contains HAL + PLME */
#define APP_SNIFFER (15)        /**< application, which contains HAL + PLME + sniffer app */
#define APP_SCRPT_SNF (16)      /**< application, which contains HAL + PLME + sniffer app for scripting */
#define APP_L2   (20)           /**< application, which contains HAL + PLME + MAC */
#define APP_L3   (30)           /**< application, which contains HAL + PLME + MAC + NWK */

/* Known board, CPU, and radio types */
/* Boards: */
#define EMU230   (1)            /* dual AT86RF230 FPGA-emulation + STK500/501 */
#define EVAL230  (2)            /* AT86RF230 evaluation board */
#define EMU231   (3)            /* AT86RF231 FPGA emulation with STK500/501 */
#define RDK230   (4)            /* AT86RF230 reference design kit */
#define EVAL231  (5)            /* AT86RF231 evaluation board */

/* CPUs: */
#define M128     (20)           /* ATmega128 */
#define M1281    (21)           /* ATmega1281 */

/* Radios: */
#define AT86RF230 (40)          /* Atmel AT86RF230 */
#define AT86RF231_1x (41)       /* Atmel AT86RF231 (V1.0) */
#define AT86RF231_2x (42)       /* Atmel AT86RF231 (V2.x) */

/* Control Interfaces */
#define UART_NONE   (50)
#define UART0       (51)
#define UART1       (52)
#define USB_FT245   (53)

/* RF bands: */
#define BAND_900  (80)          /* 868/910 MHz (channels 0 through 10) */
#define BAND_2400 (81)          /* 2.4 GHz (channels 11 through 26) */

/* NDEBUG/DEBUG ------------------------------------------------- */

#ifndef DEBUG
#define DEBUG   (1)
#endif

/* ASSERT ------------------------------------------------------- */

#ifdef ASSERT
#undef ASSERT
#endif

/* COMPILER NAMES ----------------------------------------------- */

#ifdef __ICCAVR__
#   define COMPILER_NAME "IAR EW"
#endif
#ifdef __GNUC__
#   define COMPILER_NAME "AVR-GCC"
#endif

/* === Prototypes ============================================================
*/
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* PROJECT_H */
/* EOF */
