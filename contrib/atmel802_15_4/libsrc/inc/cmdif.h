/**
 * @file
 *
 * @brief Defines, macros and function prototypes for command interface
 *
 * $Id: cmdif.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef CMDIF_H
#define CMDIF_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros ================================================================ */

/* === Prototypes ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/** \ingroup grpCmdif
 *  This group contains the function prototypes for the command interface
 */
/*@{*/

void cmdif_regrd_request(uint8_t *msg);
void cmdif_regwr_request(uint8_t *msg);

void cmdif_bitrd_request(uint8_t *msg);
void cmdif_bitwr_request(uint8_t *msg);

void cmdif_pinset_request(uint8_t *msg);
void cmdif_pinget_request(uint8_t *msg);
void cmdif_sramup_request(uint8_t *msg);
void cmdif_sramdn_request(uint8_t *msg);

void cmdif_frameup_request(uint8_t *msg);
void cmdif_framedn_request(uint8_t *msg);

void cmdif_timerstart_request(uint8_t *msg);
void cmdif_timerstop_request(uint8_t *msg);
void cmdif_set_route_request(uint8_t *msg);
void cmdif_get_route_request(uint8_t *msg);
void cmdif_bootload_request(uint8_t *msg);
void cmdif_echo_request(uint8_t *msg);
void cmdif_version_request(uint8_t *msg);

#if APP_TYPE == APP_L0
void cmdif_validation_request(uint8_t *msg);
#endif
/*@}*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CMDIF_H */
/* EOF */
