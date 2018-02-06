/**
 * @file
 *
 * @brief Command Interface implementation
 *
 * $Id: cmdif.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#include "version.h"
#include "board.h"
#include "bios.h"
#if APP_TYPE == APP_L0
# include "validation.h"
#endif /* APP_LEVEL == APP_L0 */

/* === Typedefs ============================================================ */

typedef void (*bootloader_handler_t)(void);

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */

/* === Implementation ====================================================== */

/**
 * This function is called for processing a register write request message.
 * @param p pointer to the message
 */
void cmdif_regwr_request(uint8_t *msg)
{
    regwr_req_t *p = (regwr_req_t *)msg;
    regwr_conf_t cp;

    bios_reg_write(p->address, p->value);
    /* assemble register write confirm */
    cp.size  =  sizeof(regwr_conf_t) - sizeof(cp.size);
    cp.cmdcode = CMDIF_REGWR_CONFIRM;
    cp.cnfcode = CNF_SUCCESS;
    bios_pushback_event(&cp);
}

/**
 * This function is called for processing a register read request message.
 * @param p pointer to the message
 */
void cmdif_regrd_request(uint8_t *msg)
{
    regrd_req_t *p = (regrd_req_t *)msg;
    regrd_conf_t cp;

    cp.size    = sizeof(regrd_conf_t) - sizeof(cp.size);
    cp.cmdcode = CMDIF_REGRD_CONFIRM;
    cp.value   = bios_reg_read(p->address);
    cp.cnfcode = CNF_SUCCESS;
    bios_pushback_event(&cp);
}

/**
 * This function is called for processing a subregister read request message.
 * @param p pointer to the message
 */
void cmdif_bitrd_request(uint8_t *msg)
{
    bitrd_req_t *p = (bitrd_req_t *)msg;
    bitrd_conf_t cp;
    radio_reg_t result;

    cp.size    = sizeof(bitrd_conf_t) - sizeof(cp.size);
    cp.cmdcode = CMDIF_BITRD_CONFIRM;
    bios_bit_read(p->address, (radio_reg_t)p->mask, p->pos, &result);
    cp.value = result;
    cp.cnfcode = CNF_SUCCESS;
    bios_pushback_event(&cp);
}


/**
 * This function is called for processing a subregister write request message.
 * @param p pointer to the message
 */
void cmdif_bitwr_request(uint8_t *msg)
{
    bitwr_req_t *p = (bitwr_req_t *)msg;
    bitwr_conf_t cp;

    cp.size    = sizeof(bitwr_conf_t) - sizeof(cp.size);
    cp.cmdcode = CMDIF_BITWR_CONFIRM;
    bios_bit_write(p->address, (radio_reg_t)p->mask, p->pos, (radio_reg_t)p->value);
    cp.cnfcode = CNF_SUCCESS;
    bios_pushback_event(&cp);
}

/**
 * This function is called for processing a pin set request message.
 * @param p pointer to the message
 */

void cmdif_pinset_request(uint8_t *msg)
{
    pinset_req_t *p = (pinset_req_t *)msg;
    pinset_conf_t cp;

    cp.size = sizeof(pinset_conf_t) - sizeof(cp.size);
    cp.cmdcode = CMDIF_PINSET_CONFIRM;
    cp.cnfcode = bios_pinset( p->pinid, p->value)? CNF_SUCCESS: CNF_FAILED;
    bios_pushback_event(&cp);
}


/**
 * This function is called for processing a pin set request message.
 * @param p pointer to the message
 */

void cmdif_pinget_request(uint8_t *msg)
{
    pinget_req_t *p = (pinget_req_t *)msg;
    pinget_conf_t cp;

    cp.size = sizeof(pinget_conf_t) - sizeof(cp.size);
    cp.cmdcode = CMDIF_PINGET_CONFIRM;
    cp.cnfcode = bios_pinget( p->pinid, &cp.value)? CNF_SUCCESS: CNF_FAILED;
    bios_pushback_event(&cp);
}

/**
 * This function is called for processing a sram up request message.
 *
 * From the given p->address of the sram p->length bytes are read and
 * returned in the confirm message. If p->length is 0, the message returns
 * 1 byte 0 and a confirm code 1.
 *
 * <pre>
 * req.length : confirm.size : confirm.cnfcode
 *    0       :    4         :        1
 *    1       :    4         :        0
 *    2       :    5         :        0
 *    3       :    6         :        0
 *   ...      :   ...        :       ...
 * </pre>
 *
 * @param p pointer to the message
 *
 */

void cmdif_sramup_request(uint8_t *msg)
{
    uint8_t databuffer[sizeof(sramup_conf_t) + TRX_RAM_SIZE];
#if SRAM_AVAILABLE
    sramup_req_t *p = (sramup_req_t *)msg;
#endif /* SRAM_AVAILABLE */
    sramup_conf_t * pcnf;

    pcnf = (sramup_conf_t *) databuffer;
    pcnf->cmdcode = CMDIF_SRAMUP_CONFIRM;
    pcnf->cnfcode = CNF_FAILED;
    pcnf->data[0] = 0;
    pcnf->size = sizeof(sramup_conf_t) - sizeof(pcnf->size);

#if SRAM_AVAILABLE
    if (p->length > 0)
    {
        pcnf->data[0] = p->length;
        bios_sram_read(p->address, p->length, &(pcnf->data[1]));
        pcnf->size = sizeof(sramup_conf_t) + p->length - sizeof(pcnf->size);
        pcnf->cnfcode = CNF_SUCCESS;
    }
#endif /* SRAM_AVAILABLE */

    bios_pushback_event(pcnf);
}


/**
 * This function is called for processing a sram dwn request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_sramdn_request(uint8_t *msg)
{
#if SRAM_AVAILABLE
    sramdn_req_t *p = (sramdn_req_t *)msg;
#endif /* SRAM_AVAILABLE */
    sramdn_conf_t  cnf;

    cnf.size    = sizeof(sramdn_conf_t) - sizeof(cnf.size);
    cnf.cmdcode = CMDIF_SRAMDN_CONFIRM;
    cnf.cnfcode = CNF_FAILED;

#if SRAM_AVAILABLE
    if (p->data[0] > 0)
    {
        bios_sram_write( p->address, p->data[0], &(p->data[1]) );
        cnf.cnfcode = CNF_SUCCESS;
    }
#endif /* SRAM_AVAILABLE */

    bios_pushback_event(&cnf);
}

/**
 * This function is called for processing a frame up request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_frameup_request(uint8_t *msg)
{
    uint8_t databuffer[sizeof(frameup_conf_t) + TRX_RAM_SIZE];
    frameup_conf_t *pcnf = (frameup_conf_t *)databuffer;
    uint8_t length;

    pcnf->cmdcode = CMDIF_FRAMEUP_CONFIRM;
    pcnf->cnfcode = CNF_FAILED;
    pcnf->data[0] = 0;
    pcnf->size = sizeof(frameup_conf_t) - sizeof(pcnf->size);

    length = bios_frame_read(&(pcnf->data[0]));
    pcnf->size = sizeof(sramup_conf_t) + length - sizeof(pcnf->size);
    pcnf->cnfcode = CNF_SUCCESS;
    bios_pushback_event(pcnf);
}



/**
 * This function is called for processing a sram dwn request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_framedn_request(uint8_t *msg)
{
    framedn_req_t *p = (framedn_req_t *)msg;
    framedn_conf_t  cnf;

    cnf.size    = sizeof(framedn_conf_t) - sizeof(cnf.size);
    cnf.cmdcode = CMDIF_FRAMEDN_CONFIRM;
    cnf.cnfcode = CNF_FAILED;

    if (p->data[0] > 0)
    {
        bios_frame_write( p->data[0], &(p->data[1]) );
        cnf.cnfcode = CNF_SUCCESS;
    }
    bios_pushback_event(&cnf);
}


/**
 * This function is called for processing a timer start request message.
 *
 * @param p pointer to the message
 *
 */

void cmdif_timerstart_request(uint8_t *msg)
{
    timerstart_req_t *p = (timerstart_req_t *)msg;
    timerstart_conf_t  cnf;

    cnf.size    = sizeof(timerstart_conf_t) - sizeof(cnf.size);
    cnf.cmdcode = CMDIF_TIMERSTART_CONFIRM;
#if APP_TYPE == APP_L0
    cnf.cnfcode = val_timer_start(p->tid, p->timeout );
#else
    cnf.cnfcode = bios_starttimer(p->tid, p->timeout / SYMBOL_PERIOD)?
        CNF_SUCCESS: CNF_FAILED;
#endif
    bios_pushback_event(&cnf);
}


/**
 * This function is called for processing a timer stop request message.
 *
 * @param p pointer to the message
 *
 */

void cmdif_timerstop_request(uint8_t *msg)
{
    timerstop_req_t *p = (timerstop_req_t *)msg;
    timerstop_conf_t  cnf;

    cnf.size    = sizeof(timerstop_conf_t) - sizeof(cnf.size);
    cnf.cmdcode = CMDIF_TIMERSTOP_CONFIRM;
    cnf.cnfcode = bios_stoptimer(p->tid)? CNF_SUCCESS: CNF_FAILED;
    bios_pushback_event(&cnf);
}

/**
 * This function is called for processing a set route request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_set_route_request(uint8_t *msg)
{
    cmdif_set_route_req_t *p = (cmdif_set_route_req_t *)msg;
    cmdif_set_route_conf_t cnf;

    cnf.size    = sizeof(cmdif_set_route_conf_t) - sizeof(cnf.size);
    cnf.cmdcode = CMDIF_SET_ROUTE_CONFIRM;
    cnf.status  = CNF_SUCCESS;
    set_uart_routing(p->mtype, p->state);
    bios_pushback_event(&cnf);
}

/**
 * This function is called for processing a get route request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_get_route_request(uint8_t *msg)
{
    cmdif_get_route_req_t *p = (cmdif_get_route_req_t *)msg;
    cmdif_get_route_conf_t cnf;

    cnf.size    = sizeof(cmdif_set_route_conf_t) - sizeof(cnf.size);
    cnf.cmdcode = CMDIF_GET_ROUTE_CONFIRM;
    cnf.status  = send_to_uart(p->mtype);
    bios_pushback_event(&cnf);
}

/**
 * This function is called for processing a bootload request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_bootload_request(uint8_t *msg)
{
    bios_reset_hardware();

    bootloader_handler_t bootloader = (bootloader_handler_t)BOOTADDR;
    bootloader();
}


/**
 * This function is called for processing a echo request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_echo_request(uint8_t *msg)
{
    cmdif_echo_conf_t *pcnf = (cmdif_echo_conf_t *)msg;

    pcnf->cmdcode = CMDIF_ECHO_CONFIRM;
    bios_pushback_event(pcnf);
}

/**
 * This function is called for processing a version request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_version_request(uint8_t *msg)
{
    cmdif_version_conf_t cnf;

    cnf.size = sizeof(cmdif_version_conf_t) - sizeof(cnf.size);
    cnf.cmdcode = CMDIF_VERSION_CONFIRM;
    cnf.major = WPAN_MAJOR;
    cnf.minor = WPAN_MINOR;
    cnf.revision = WPAN_REVISION;
    cnf.apptype = APP_TYPE;
    cnf.boardtype = BOARD_TYPE;
    cnf.macaddr = bios_get_ieee_addr();
    bios_pushback_event(&cnf);
}

#if APP_TYPE == APP_L0
/**
 * This function is called for processing a validation request message.
 *
 * @param p pointer to the message
 *
 */
void cmdif_validation_request(uint8_t *msg)
{
    uint8_t databuffer[sizeof(cmdif_validation_conf_t) + TRX_RAM_SIZE];
    cmdif_validation_req_t *p = (cmdif_validation_req_t *)msg;
    cmdif_validation_conf_t *pCnf;

    pCnf = (cmdif_validation_conf_t *)databuffer;
    validation_process_cmd(p, pCnf);

    bios_pushback_event(pCnf);
}
#endif
/* EOF */
