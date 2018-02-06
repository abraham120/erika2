/**
 * \file
 * \brief ECHO, PRINT, and ASSERT macro implementations and CRC16 calulation
 *
 * This file implements ECHO and ASSERT for the debug build as well as crc16
 * calculation.
 *
 * $Id: bios.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#ifndef DEF_H
#include "def.h"
#endif
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "bios.h"
#include "msg_const.h"
#include "phy.h"


/* === Globals ============================================================= */

#if DEBUG > 0
static uint8_t              msg_buffer[MAX_MESSAGE_SIZE];
#endif

/* === Typedefs ============================================================ */
typedef void (*bootloader_handler_t)(void);

/* === Prototypes ========================================================== */


/* === Implementation ====================================================== */

#if DEBUG || defined(DOXYGEN)
/**
 * \brief Send a message back to the host application
 *
 * Send a message back to the host application using an echo
 * indication message.
 *
 * \param pData pointer to string to send
 */
void bios_echo(FLASH_STRING_T pData)
{
    echo_ind_t *eim = (echo_ind_t *) msg_buffer;
    size_t length;

    length = PGM_STRLEN(pData);
    if (length > MAX_OCTETSTRING_SIZE)
        length = MAX_OCTETSTRING_SIZE;
    eim->data[0] = length;
    PGM_READ_BLOCK(&eim->data[1], pData, length);
    eim->size = sizeof(echo_ind_t) + eim->data[0] - sizeof(eim->size);
    eim->cmdcode = CMDIF_ECHO_INDICATION;
    bios_pushback_event(eim);

    return;
}


/**
 * \brief Send a printf-style message back to the host application
 *
 * Send a message back to the host application using an echo
 * indication message.  The arguments are passed using a printf-style
 * format string.
 *
 * \param fmt pointer to format string
 * \param ... any arguments required by format string
 */
void bios_print(FLASH_STRING_T fmt, ...)
{
    va_list ap;
    echo_ind_t *eim = (echo_ind_t *) msg_buffer;
#if !HAS_PGM_VSNPRINTF
    char fmtbuf[MAX_OCTETSTRING_SIZE];
#endif

    va_start(ap, fmt);
#if HAS_PGM_VSNPRINTF
    eim->data[0] = PGM_VSNPRINTF((char *)&(eim->data[1]), MAX_OCTETSTRING_SIZE, fmt, ap);
#else
    PGM_STRCPY(fmtbuf, fmt);
    eim->data[0] = vsnprintf((char *)&(eim->data[1]), MAX_OCTETSTRING_SIZE, fmtbuf, ap);
#endif
    eim->size = sizeof(echo_ind_t) + eim->data[0] - sizeof(eim->size);
    eim->cmdcode = CMDIF_ECHO_INDICATION;
    bios_pushback_event(eim);
    va_end(ap);

    return;
}

/**
 * \brief Test an assertion, abort with a message if failed
 *
 * Test an expression, abort echoing a message back to the host
 * application if the assertion failed.  Meant to be used as the
 * backend to ASSERT.
 * Calls bios_abort which is not supposed to return.
 *
 * \param expr assertion to test for
 * \param sexpr string representation of the assertion
 * \param file name of source file
 * \param line line number in source file
 */
void bios_assert(int expr, FLASH_STRING_T sexpr, char *file, int line)
{
# if APP_TYPE >= APP_L0 || defined(DOXYGEN)
    echo_ind_t *eim = (echo_ind_t *) msg_buffer;
#  if !defined(PRINTF_FLASH_STRING)
    char tmpbuf[MAX_OCTETSTRING_SIZE];
#  endif

    if(!expr)
    {
#  if defined(PRINTF_FLASH_STRING)
        eim->data[0] = snprintf((char *)&(eim->data[1]), MAX_OCTETSTRING_SIZE,
                                "%s, line %d: assertion '"
                                PRINTF_FLASH_STRING
                                "' failed", file, line, (wchar_t *)sexpr);
#  else  /* !defined(PRINTF_FLASH_STRING) */
        PGM_STRCPY(tmpbuf, sexpr);
        eim->data[0] = snprintf((char *)&(eim->data[1]), MAX_OCTETSTRING_SIZE,
                                "%s, line %d: assertion '%s' failed", file, line, tmpbuf);
#  endif /* defined(PRINTF_FLASH_STRING) */
        eim->size = sizeof(echo_ind_t) + eim->data[0] - sizeof(eim->size);
        eim->cmdcode = CMDIF_ECHO_INDICATION;
#    if HAS_USB == 1
        usb_write((uint8_t *) eim);
#    else
        uart_write((uint8_t *) eim);
#    endif
        bios_abort();
    }
# endif /* APP_TYPE >= APP_L0 || defined(DOXYGEN) */
}
#endif /* DEBUG */

#if !(RADIO_TYPE == AT86RF231_1x || RADIO_TYPE == AT86RF231_2x) || defined(DOXYGEN)
/**
 * \brief Generate CRC16
 *
 * generate FCS field according to IEEE 802.15.4-2003 7.2.18
 * generator polynomial is G(x) = x^16 + x^12 + x^5 + 1
 *
 * \param msg The octetstring which should be checked.
 *            Its minimum length should be 2 and maximum is 255.
 */
void bios_gen_crc16(octetstr_t *msg)
{
    uint16_t taps;
    uint8_t  j, end;
    uint8_t  *octet = &msg[1];

    end = *msg;
    taps = 0x0000;

    ASSERT (end >= 2);
    if (end >= 2)
    {
        end = end - 2;
        for (j = 0; j < end; j++)
        {
            taps = CRC_CCITT_UPDATE(taps, octet[j]);
        }
        /* write out remainder to last 2 octets */
        /* the LSB of the octet is transmitted first */
        octet[j] = (uint8_t) ((taps) & 0x00FF);
        j++;
        octet[j] = (uint8_t) (((taps) >> 8) & 0x00FF) ;
    }
}
#endif /* !(RADIO_TYPE == AT86RF231_1x || RADIO_TYPE == AT86RF231_2x) || defined(DOXYGEN) */

/**
 * \brief Jump to the boot loader address.
 *
 * This function enters the bootloader code after resetting
 * the the transceiver hardware.
 */
void bios_jump_bootloader(void)
{
    bootloader_handler_t bootloader = (bootloader_handler_t)BOOTADDR;
    bios_reset_hardware();
    bootloader();
}


/* EOF */
