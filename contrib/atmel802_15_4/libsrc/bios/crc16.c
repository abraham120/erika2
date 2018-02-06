/**
 * \file
 * \brief CCITT-CRC16 implementation for the IAR compiler
 *
 * $Id: crc16.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#if defined(__ICCAVR__) || defined(DOXYGEN)

/* === Includes ============================================================ */
#ifndef DEF_H
#include "def.h"
#endif

#include "avrtypes.h"

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */

/* === Implementation ====================================================== */

/* Only needed for the IAR as avr-libc has an inlined implementation. */

/**
 * \brief Update the CCITT-CRC16
 *
 * Update the CRC for transmitted and received data using the CCITT 16bit
 * algorithm (X^16 + X^12 + X^5 + 1).
 *
 * \returns updated crc16
 * \param crc currrent crc value
 * \param data next byte that should be included into the crc16
 */

uint16_t crc_ccitt_update (uint16_t crc, uint8_t data)
{
    data ^= crc & 0xff;
    data ^= data << 4;

    return ((((uint16_t)data << 8) | ((crc & 0xff00) >> 8))
            ^ (uint8_t)(data >> 4)
            ^ ((uint16_t)data << 3));
}

#endif /* __ICCAVR__ || defined(DOXYGEN) */

/* EOF */
