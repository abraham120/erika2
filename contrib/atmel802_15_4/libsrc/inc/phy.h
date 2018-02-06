/**
 * @file
 *
 * @brief This header file declares an interface between the MAC sublayer and
 * the physical radio channel.
 *
 * $Id: phy.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef PHY_H
#define PHY_H

/* === Includes ============================================================== */
#include "bios.h"
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros ================================================================ */

/**
 * Mask for the phyTransmitPower PIB attribute's actual value.  The
 * two MSBits describe the tx power tolerance.
 */
#define PHY_TXPOWER_MASK (0x3f)

/**
 * Maximal payload size for a PLME-GET.confirm.  Can be used by
 * callers to allocate the buffer.
 */
#define PHY_MAX_GETCONF_SIZE 8

/**
 * Number of octets added by the PHY: 4 sync octets + SFD octet.
 */
#define PHY_OVERHEAD  (5)

/* === Prototypes ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/** \defgroup PHY  PHY Layer Interface
 *
 * This module provides an interface between the MAC sublayer and the physical
 * radio channel, via the RF firmware and RF hardware. The PHY conceptually
 * includes a management entity called the PLME. This entity provides the layer
 * management service interfaces through which layer management functions may
 * be invoked. The PLME is also responsible for maintaining a database of
 * managed objects pertaining to the PHY. This database is referred to as the
 * PHY PAN information base (PIB).
 *
 */
/*@{*/

void phy_init(void);
void phy_reset_internal(void);
void phy_irq_handler(uint8_t irqstatus, uint32_t tstamp);

/* internal request handling */
bool    pd_data_request_internal(pd_data_req_t *msg, pd_data_conf_t *cm);
uint8_t plme_get_request_internal(plme_get_req_t *msg, plme_get_conf_t *cm);
uint8_t plme_set_request_internal(plme_set_req_t *msg, plme_set_conf_t *cm);
void    plme_set_trx_state_request_internal(plme_set_trx_state_req_t *msg, plme_set_trx_state_conf_t *cm);

/* 802.15.4 PHY layer entries */
void pd_data_request(uint8_t *msg);
void plme_cca_request(uint8_t *msg);
void plme_ed_request(uint8_t *msg);
void plme_get_request(uint8_t *msg);
void plme_get_confirm(uint8_t *msg);
void plme_set_trx_state_request(uint8_t *msg);
void plme_set_request(uint8_t *msg);

void pd_data_conf(uint8_t *m);
void pd_data_ind(uint8_t *m);
void plme_cca_conf(uint8_t *m);
void plme_ed_conf(uint8_t *m);
void plme_get_conf(uint8_t *m);
void plme_set_conf(uint8_t *m);
void plme_set_trx_state_conf(uint8_t *m);
/*@}*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* PHY_H */
/* EOF */
