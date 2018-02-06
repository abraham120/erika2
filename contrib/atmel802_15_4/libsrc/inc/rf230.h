/**
 * @file
 * @brief This header file declares an interface between the MAC sublayer and the physical
 * radio channel.
 *
 * $Id: rf230.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef RF230_H
#define RF230_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros ================================================================ */

/** 180 us to lock PLL from TRX_OFF */
#define PLL_LOCK_TIMEOUT            (12)

/* The following Macros define the commands for SPI access */
/** \brief register write (short mode) */
#   define TRX_CMD_RW         (0xc0)
/** \brief register read (short mode) */
#   define TRX_CMD_RR         (0x80)
/** \brief frame transmit mode (long mode) */
#   define TRX_CMD_FW         (0x60)
/** \brief frame receive mode (long mode) */
#   define TRX_CMD_FR         (0x20)
/** \brief SRAM write */
#   define TRX_CMD_SW         (0x40)
/** \brief SRAM read */
#   define TRX_CMD_SR         (0x00)
/** \brief Register address mask */
#   define TRX_CMD_RADDRM     (0x3f)

/* The following Macros define the Interrupt Status */
/** \brief signals low battery */
#   define TRX_IRQ_BAT_LOW             (0x80)
/** \brief signals a FIFO underrun */
#   define TRX_IRQ_TRX_UR              (0x40)
/** \brief reserved */
#   define TRX_IRQ_5                   (0x20)
/** \brief reserved */
#   define TRX_IRQ_4                   (0x10)
/** \brief signals end of frames (transmit and receive)*/
#   define TRX_IRQ_TRX_END             (0x08)
/** \brief signals begin of a receiving frame*/
#   define TRX_IRQ_RX_START            (0x04)
/** \brief signals an unlocked PLL*/
#   define TRX_IRQ_PLL_UNLOCK          (0x02)
/** \brief PLL goes to lock-state */
#   define TRX_IRQ_PLL_LOCK            (0x01)

/** \brief Interrupt mask for all known IRQ's */
#   define TRX_KNOWN_IRQS     (TRX_IRQ_BAT_LOW | TRX_IRQ_TRX_END | TRX_IRQ_RX_START)
/** \brief RF230 FIFO size */
#   define RF230_RAM_SIZE              (0x80)

/**
 * Tolerance of the phyTransmitPower PIB attribute.  This is encoded
 * into the two MSBits of the attribute, and is effectively read-only.
 */
#   define RF230_TX_PWR_TOLERANCE      (0x40)

/**
 * \brief Number of tx power levels.
 */
#   define RF230_NUM_TX_PWR_LEVELS     (16)

/** \brief RF230 operates in 2.4GHz-band -> channels 11-26*/
#define RF230_SUPPORTED_CHANNELS (0x07FFF800)

/** \brief Time to wake up from sleep mode, in symbols. */
#define RF230_WAKEUP_TIME              (880 / 16)

/* === Prototypes ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup BIOS */
/*@{*/

uint8_t bios_frame_length_read(void);

/*@}*/

/** \addtogroup PHY */
/*@{*/

/* interrupt callbacks, radio dependant */

void phy_rx_start(uint32_t tst);
void phy_trx_end(void);

/*@}*/



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* RF230_H */
/* EOF */
