/**
 * @file
 * @brief Implementation of the event queue
 *
 * $Id: queue.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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
#include <string.h>
#ifndef DEF_H
#include "def.h"
#endif
#include "ee_confMac.h"
#include "board.h"
#include "bios.h"
#include "avrtypes.h"

/* === Macros =============================================================== */

/** The number of entries in the UART routing table */
#define MESSAGE_ENTRIES         (32)

/* === Globals ============================================================= */

/** This is the event queue */
uint8_t equeue[QUEUE_SIZE + MAX_MESSAGE_SIZE];

/** This array specifies wether a message should be routed over the UART or not.

    index = cmdcode/8 , bitpos = cmdcode & 7

    If the corresponding bit is set to 1, then route the message over the UART,
    otherwies do nothing */
#if SPECIAL_PEER

/* No routing of PD_DATA and PLME primitives */
/* No routing of CMDIF_ECHO_INDICATION, TIMER_EXPIRED_INDICATION,
TRX_INTERRUPT_INDICATION primitives */
uint8_t uart_switch[MESSAGE_ENTRIES] = {
                          /*    0     8    16    24    32    40    48    54 */
                             0x00, 0x00, 0xff, 0xff, 0xff, 0x56, 0x00, 0x00,
                          /*   64    72    80    88    96   104   112   120 */
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                          /*  128   136   144   152   160   168   176   184 */
                             0x00, 0x00, 0xff, 0x7f, 0xf4, 0xff, 0xff, 0xff,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

#else   /* !SPECIAL_PEER */

uint8_t uart_switch[MESSAGE_ENTRIES] =
                            {0x00, 0x00, 0xff, 0xff, 0xff, 0x56, 0x56, 0xf5,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0x00, 0x00, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

#endif  /* SPECIAL_PEER */

/** This is the write index of the event queue. It points to the next free
    element. */
uint16_t wr_index;
/** This is the read index of the event queue. It points to the first element
    in the queue. */
uint16_t rd_index;
/** This is a flag, that indicates that the previouse bios_popfront_event
    delayed the update of the read index. */
uint8_t rd_delay;
/** This is a flag, that indicates that the queue will be full soon. */
bool bios_queue_watermark;

/* === Prototypes ========================================================== */

/* === Implementation ====================================================== */


/**
 * This function decides whether the message should be routed over the UART or not.
 * @param msg_type The message type.
 * @return Returns 1 if this message should be routed over UART, otherwise 0.
 */
uint8_t send_to_uart(uint8_t msg_type)
{
    return (uart_switch[msg_type >> 3] >> (msg_type & 7)) & 1;
}

/**
 * This function sets the UART routing.
 * @param msg_type The message type.
 * @param state    If 1 than the message should be routed, otherwise not.
 */
void set_uart_routing(uint8_t msg_type, uint8_t state)
{
    if (state == 1)
    {
        uart_switch[msg_type >> 3] = uart_switch[msg_type >> 3] | (1 << (msg_type & 7));
    }
    else
    {
        uart_switch[msg_type >> 3] = uart_switch[msg_type >> 3] & (~(1 << (msg_type & 7)));
    }
}

/**
 *  \brief
 *  Initialize Event Queue
 *
 * This function will initialize the event queue.
 */

void init_event_queue(void)
{
    wr_index = 0;
    rd_index = 0;
    rd_delay = 0;
}

/**
 * \brief
 *  Enqueue Event
 *
 * This function inserts an event into the event queue.
 * @param event A pointer to an event that should be inserted.
 * @return Returns true if successful.
 */
#ifdef DEVICE
extern device_status_t d_status;
#endif
#ifdef PANCOORDINATOR
extern coord_status_t c_status;
#endif

 
bool bios_pushback_event(void *event)
{
    uint16_t tmp_index;
    uint16_t old_wr_index;
    bool back = true;
    uint8_t sreg;

    save_irq_status();
    cli();

    tmp_index = wr_index + *((uint8_t *) event) + 1;
    old_wr_index = wr_index;

    if (wr_index >= rd_index)
    {
        bios_queue_watermark = (wr_index - rd_index) > (QUEUE_SIZE - MAX_MESSAGE_SIZE);
    }
    else
    {
        bios_queue_watermark = (rd_index - wr_index) < (QUEUE_SIZE - MAX_MESSAGE_SIZE);
    }

    if (wr_index >= rd_index)
    {
        /* normal case */
        if (tmp_index >= (rd_index + QUEUE_SIZE))
        {
            /* fatal error: queue overflow */
            back = false;
            ASSERT("fatal error: event queue overflow" == 0);
        }
    }
    else
    {
        /* wrap around case */
        if (tmp_index >= rd_index)
        {
            /* fatal error: queue overflow */
            back = false;
            ASSERT("fatal error: event queue overflow" == 0);
        }
    }

    if (back)
    {
        if (tmp_index > QUEUE_SIZE)
        {
            /* This is the one of the few places in the code where wr_index
               should be volatile. Therefore, do this casting */
            *((volatile uint16_t *)&wr_index) = 0;
        }
        else
        {
            /* This is the one of the few places in the code where wr_index
               should be volatile. Therefore, do this casting */
            *((volatile uint16_t *)&wr_index) = tmp_index;
        }
    }

    /*
     * Re-enable interrupts before the time consuming memcpy() below.
     */
    restore_irq_status();

    if (back)
    {
        memcpy(&equeue[old_wr_index], event, *((uint8_t *) event) + 1);
    }
 
    

   
    return back;
}

/**
 * \brief
 *  Dequeue Event
 *
 * This function retrieves an event from the event queue.
 * @return Returns a pointer to an event or NULL pointer in case of an empty
           queue.
 */
uint8_t* bios_popfront_event(void)
{
    uint8_t *back = 0;
    uint8_t sreg;

    save_irq_status();
    cli();

    /* did the reviouse bios_popfront_event
       delay the update of the read index? */
    if (rd_delay != 0)
    {
        /* yes, update of read index was delayed */
        if ((rd_index + equeue[rd_index] + 1) > QUEUE_SIZE)
            rd_index = 0;
        else
            rd_index = (rd_index + equeue[rd_index] + 1);
        if (rd_index != wr_index)
        {
            back = &equeue[rd_index];
        }
        else
        {
            rd_delay = 0;
        }
    }
    else
    {
        /* no delay */
        if (rd_index != wr_index)
        {
            back = &equeue[rd_index];
            rd_delay = 1;
        }
    }

    if (wr_index >= rd_index)
    {
        bios_queue_watermark = (wr_index - rd_index) > (QUEUE_SIZE - MAX_MESSAGE_SIZE);
    }
    else
    {
        bios_queue_watermark = (rd_index - wr_index) < (QUEUE_SIZE - MAX_MESSAGE_SIZE);
    }
    restore_irq_status();
    


    return back;
}


/* EOF */
