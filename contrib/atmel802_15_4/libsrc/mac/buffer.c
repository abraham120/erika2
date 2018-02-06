/**
 * @file
 * This file implements the buffer management routines for the MAC/PHY.
 *
 * $Id: buffer.c,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#include <string.h>
#include "mac.h"
#include "phy.h"

#if APP_TYPE >= APP_L2 || defined(DOXYGEN)

/* === Globals ============================================================= */

#define FIRST_INDIRECT_BUF  NO_OF_DIRECT_TX_BUFFERS

#define DESTINATION_ADDRESS_OFFSET     (5)         // Location of the dest. address in


/* All buffers belong to a single buffer array which is logically devided into 3 parts:
   1) NO_OF_DIRECT_TX_BUFFERS direct buffers start at position 0 up to NO_OF_DIRECT_TX_BUFFERS-1
   2) ADDR_LIST_LENGTH indirect buffers start at position NO_OF_DIRECT_TX_BUFFERS
      up to NO_OF_DIRECT_TX_BUFFERS+ADDR_LIST_LENGTH-1
*/
static frame_buffer_t frame_buffer_array[NO_OF_DIRECT_TX_BUFFERS + ADDR_LIST_LENGTH];
// pointer to 1st indirect frame buffer
static frame_buffer_t *frame_buffer_head = NULL;

/* === Prototypes ========================================================== */

#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
static void add_buffer_to_list(frame_buffer_t *new_buf);
static bool remove_buffer_from_list(frame_buffer_t *old_buf);
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

/* === Macros =============================================================== */

#define FRAME_CONTROL_1         (0x01)      // Position of frame control 1

/* === Implementation ====================================================== */

/**
 * @brief Free up an individual buffer
 *
 * This function will free up an individual buffer for further subsequent use.
 *
 * @param pointer to the buffer to free up
 *
 */
void mac_buffer_free(frame_buffer_t *buf)
{
    if (buf->usage == BUFFER_DIRECT)
    {
        // Direct buffer
        ASSERT((buf >= &frame_buffer_array[0])
            && (buf < &frame_buffer_array[NO_OF_DIRECT_TX_BUFFERS]));
        buf->usage = BUFFER_EMPTY;
    }
#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    else if (buf->usage == BUFFER_INDIRECT)
    {
        // Indirect buffer
        ASSERT((buf >= &frame_buffer_array[FIRST_INDIRECT_BUF])
            && (buf < &frame_buffer_array[FIRST_INDIRECT_BUF+ADDR_LIST_LENGTH]));
        remove_buffer_from_list(buf);
    }
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
    else
    {
        // the buffer has already been released, can happen under stress
        // do nothing
    }
}


/**
 * @brief Reset the buffer array
 *
 * This function will return all frame buffers to a 'free' condition. This will
 * nullify any data that currently exist in any of the buffers, thus making
 * them all available for use in the future. This routine should be called upon
 * reset and possibly other conditions in the MAC.
 */
void mac_buffer_flush(void)
{
    uint8_t i;

    for (i=0; i<(NO_OF_DIRECT_TX_BUFFERS + ADDR_LIST_LENGTH); i++)
    {
        frame_buffer_array[i].next_buf = NULL;
        frame_buffer_array[i].usage = BUFFER_EMPTY;
    }

    frame_buffer_head = NULL;
}



/**
 * @brief Finds a free buffer for a direct transmission
 *
 * This function finds the first available buffer that can be used for frame construction
 * and transfer. This routine should be called when the MAC needs a buffer
 * for direct transmission
 *
 * @return A pointer to the 1st free buffer that is available for use or NULL if no free buffer was found.
 */
frame_buffer_t* mac_buffer_request(void)
{
    uint8_t i;

    for (i=0; i<NO_OF_DIRECT_TX_BUFFERS; i++)
    {
        if (frame_buffer_array[i].usage == BUFFER_EMPTY)
        {
            frame_buffer_array[i].usage = BUFFER_DIRECT;
            return &frame_buffer_array[i];
        }
    }
    return NULL;
}


#if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN)
/**
 * @brief Finds a free buffer for an indirect transmission
 *
 * This function finds the first free buffer that can be used for frame construction
 * and transfer. This routine should be called when the MAC needs a buffer
 * for indirect transmission
 *
 * @return A pointer to the 1st free buffer that is available for use or NULL if no free buffer was found.
 */
frame_buffer_t* mac_buffer_request_indirect(void)
{
    uint8_t i;

#if SPECIAL_PEER
    if (mac_pib_privateTransactionOverflow >= 1)
    {
        // Private PIB is set to indicate no free indirect buffer for new transaction
        return NULL;
    }
#endif /* SPECIAL_PEER */

    // Find empty buffer from indirect buffer area
    for (i = FIRST_INDIRECT_BUF; i < FIRST_INDIRECT_BUF+ADDR_LIST_LENGTH; i++)
    {
        if (frame_buffer_array[i].usage == BUFFER_EMPTY)
        {
            frame_buffer_array[i].usage = BUFFER_INDIRECT;
            frame_buffer_array[i].transactiontime = mac_pib_macTransactionPersistenceTime;
            add_buffer_to_list(&frame_buffer_array[i]);
            return &frame_buffer_array[i];
        }
    }

    return NULL;
}


/**
 * @brief Adds an indirect buffer to the linked list
 *
 * This function appends a newly seized indirect buffer at the end of the existing buffer list.
 *
 * @param frame_buffer_t* Pointer to new frame buffer.
 */
void add_buffer_to_list(frame_buffer_t *new_buf)
{
    frame_buffer_t  *temp_buf = frame_buffer_head;
    uint8_t psrbuf[sizeof(plme_set_req_t) + sizeof(uint8_t)];
    plme_set_req_t *psr = (plme_set_req_t *)psrbuf;
    plme_set_conf_t psc;

    // travers through the existing list

    if (frame_buffer_head == NULL)
    {
        // 1st indirect buffer, set Head of linked list
        frame_buffer_head = new_buf;
    }
    else
    {
        for ( ; temp_buf->next_buf != NULL; temp_buf = temp_buf->next_buf)
        {
            ASSERT((temp_buf >= &frame_buffer_array[FIRST_INDIRECT_BUF])
                && (temp_buf < &frame_buffer_array[FIRST_INDIRECT_BUF+ADDR_LIST_LENGTH]));
        }

        // we found last item in list, now append new one
        temp_buf->next_buf = new_buf;
    }

    // new buffer is last in list
    new_buf->next_buf = NULL;

    if (mac_i_pan_coordinator && mac_phy_autoacks)
    {
        /*
         * When running a coordinator on a PHY that performs automatic
         * ACKs, tell it to set the pending bit for outgoing ACKs.
         */
        psr->PIBAttribute = phySetPending;
        psr->data[1] = true;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);
    }
}


/**
 * @brief Removes an indirect buffer from the linked list
 *
 * This function removes an obsolete indirect buffer from the existing buffer list.
 *
 * @param frame_buffer_t* Pointer to old frame buffer to be removed.
 *
 * @return bool Return true if head to buffer list changed, otherwise false
 */
bool remove_buffer_from_list(frame_buffer_t *old_buf)
{
    frame_buffer_t  *temp_buf = frame_buffer_head;
    frame_buffer_t  *prev_buf = NULL;
    bool head_changed = false;
    uint8_t psrbuf[sizeof(plme_set_req_t) + sizeof(uint8_t)];
    plme_set_req_t *psr = (plme_set_req_t *)psrbuf;
    plme_set_conf_t psc;

    ASSERT(frame_buffer_head != NULL);

    // traverse through the existing list
    while (temp_buf != NULL)
    {
        ASSERT((temp_buf > &frame_buffer_array[0]) && (temp_buf <= &frame_buffer_array[ADDR_LIST_LENGTH]));
        if (temp_buf == old_buf)
        {
            if (prev_buf == NULL)
            {
                // this was the first buffer in the list, so head will move
                frame_buffer_head = temp_buf->next_buf;
                head_changed = true;
            }
            else
            {
                // remove buf from list
                prev_buf->next_buf = temp_buf->next_buf;
            }
            temp_buf->usage = BUFFER_EMPTY;
            temp_buf->next_buf = NULL;
        }
        prev_buf = temp_buf;
        temp_buf = temp_buf-> next_buf;
    }

    if (frame_buffer_head == NULL && mac_i_pan_coordinator && mac_phy_autoacks)
    {
        /*
         * When running a coordinator on a PHY that performs automatic
         * ACKs, tell it to no longer set the pending bit for outgoing
         * ACKs.
         */
        psr->PIBAttribute = phySetPending;
        psr->data[1] = false;
        plme_set_request_internal(psr, &psc);
        ASSERT(psc.status == PHY_SUCCESS);
    }

    return head_changed;
}


/**
 * @brief Finds a buffer with an extended address
 *
 * This function finds the long address of a device that is requesting data.
 *
 * @param[in] extended_addr An IEEE address (8 byte address/64-bit).
 * @param[out] cnt Pointer to the number of pending messages (necessary for setting the pending bit later)
 *
 * @return A pointer to the buffer corresponding to the address if found .If
 *         a matching address isn't found, then a 'NULL' pointer is returned.
 */
frame_buffer_t* mac_buffer_report_long_indirect(uint64_t extended_addr, uint8_t *cnt)
{
    frame_buffer_t  *message_ptr = NULL;
    frame_buffer_t  *temp_buf = frame_buffer_head;
    uint64_t bs;

    *cnt = 0;              // Assume no messages found

    for ( ; temp_buf != NULL; temp_buf = temp_buf-> next_buf)
    {
        ASSERT (temp_buf->usage == BUFFER_INDIRECT);
        ASSERT((temp_buf > &frame_buffer_array[0]) && (temp_buf <= &frame_buffer_array[ADDR_LIST_LENGTH]));

        bs = *(uint64_t *) &(temp_buf->placeholder[DESTINATION_ADDRESS_OFFSET]);
        if(bs == extended_addr)
        {
            if (*cnt == 0)     // Return the 1st instance
            {
                message_ptr = temp_buf;
            }
            (*cnt)++;
        }
    }

    return message_ptr;
}



/**
 * @brief Finds a buffer with a short address
 *
 * This function finds the short address of a device that is requesting data.
 *
 * @param[in] A short address (2 byte address/16-bit).
 * @param[out] cnt Pointer to the number of pending messages (necessary for setting the pending bit later)
 *
 * @return A pointer to the buffer corresponding to the address if found.If
 *         a matching address isn't found, then a 'NULL' pointer is returned.
 */
frame_buffer_t* mac_buffer_report_short_indirect(uint16_t short_addr, uint8_t *cnt)
{
    frame_buffer_t  *message_ptr = NULL;
    frame_buffer_t  *temp_buf = frame_buffer_head;
    uint16_t bs;

    *cnt = 0;              // Assume no messages found

    for ( ; temp_buf != NULL; temp_buf = temp_buf-> next_buf)
    {
        ASSERT (temp_buf->usage == BUFFER_INDIRECT);
        ASSERT((temp_buf > &frame_buffer_array[0]) && (temp_buf <= &frame_buffer_array[ADDR_LIST_LENGTH]));

        bs = *(uint16_t *) &(temp_buf->placeholder[DESTINATION_ADDRESS_OFFSET]);
        if(bs == short_addr)
        {
            if (*cnt == 0)     // Return the 1st instance
            {
                message_ptr = temp_buf;
            }
            (*cnt)++;
        }
    }
    return message_ptr;
}


/**
 * @brief Purges a buffer corresponding to a MSDU handle
 *
 * This function finds a given msdu handle. If the handle is found, that buffer is freed up
 * for further use. This routine will typically be called from the
 * mlme_purge_request routine.
 *
 * @param An msdu handle.
 *
 * @return TRUE if the MSDU handle is found, FALSE if it is not found
 */
bool mac_buffer_purge(uint8_t msdu_handle)
{
    frame_buffer_t  *temp_buf = frame_buffer_head;

    for ( ; temp_buf != NULL; temp_buf = temp_buf-> next_buf)
    {
        ASSERT((temp_buf > &frame_buffer_array[0]) && (temp_buf <= &frame_buffer_array[ADDR_LIST_LENGTH]));

        if ((temp_buf->msduHandle == msdu_handle)
            && (temp_buf->usage == BUFFER_INDIRECT))
        {
            remove_buffer_from_list(temp_buf);
            return true;
        }
    }
    return false;
}


/**
 * @brief Decrements the transaction persistence time
 *
 * This function searches for active indirect buffers. If one is found
 * the transactiontime element will be decremented. If the
 * transactiontime element is decremented all the way to zero, the buffer is
 * then freed up for further use, and mac_persistence_buf_expired() is called
 * on the buffer.
 *
 * @return true if there are still active indirect buffers
 */
bool mac_buffer_decrement_persistence(void)
{
    frame_buffer_t  *temp_buf = frame_buffer_head;
    frame_buffer_t  *old_buf = frame_buffer_head;   // required in case we need to remove one buffer
                                                    // to be able to continue traversing through the list
    bool rv = false;
    bool head_changed = false;

    while (temp_buf != NULL)
    {
        ASSERT((temp_buf > &frame_buffer_array[0]) && (temp_buf <= &frame_buffer_array[ADDR_LIST_LENGTH]));
        ASSERT(temp_buf->usage == BUFFER_INDIRECT);

        temp_buf->transactiontime--;
        if (temp_buf->transactiontime == 0)
        {
            head_changed = remove_buffer_from_list(temp_buf);
            mac_persistence_buf_expired(temp_buf);
            // prepare buffer pointer to with next buffer in list
            if (head_changed)
            {
                // we have just removed the head of the buffer list, so continue with new head
                temp_buf = frame_buffer_head;
                head_changed = false;
            }
            else
            {
                // we have just removed a buffer in the middle of the list, so continue with next in list
                temp_buf = old_buf->next_buf;
            }
        }
        else
        {
            // move on loop pointer
            temp_buf = temp_buf->next_buf;
            // keep current buffer in case we need it after we have to remove one buffer
            old_buf = temp_buf;
            rv = true;
        }
    }
    return (rv);
}


/**
 * @brief Builds the pending address fields of a beacon frame
 *
 * The purpose of buffer_add_pending is to populate the pending address
 * specification fields of a beacon frame. Therefore this routine will be
 * called from the build_beacon_frame routine.
 *
 * This function will search the entire array of frame buffers for buffers that
 * contain frames that are to be transmitted indirectly. The number of indirect
 * buffers with short and long addresses will be counted and inserted into the
 * beacon frame as the address specification fiels. The addresses themselves
 * will be placed in the beacon frame after the address specification field.
 *
 * @param A pointer to the pending address speecification field of the beacon
 *        frame that is currenting being built.
 *
 * @return The number of bytes added to the beacon frame by mac_buffer_add_pending.
 */
uint8_t mac_buffer_add_pending(uint8_t *pending_addr_spec)
{
    frame_buffer_t  *temp_buf = frame_buffer_head;

    uint8_t i,h;             // General indices

    uint8_t long_array[ADDR_LIST_LENGTH][8];  // dummy Array for sorting long addresses
    uint8_t short_array[ADDR_LIST_LENGTH][2]; // dummy Array for sorting short addresses

    uint8_t short_num = 0;
    uint8_t long_num  = 0;

    uint8_t temp_pend_addr_spec = 0;    // Pending address specification
    uint8_t num_bytes = 0;              // The number of bytes added to the beacon frame
    uint16_t fcf;

    //get all pending adresses from frame buffer
    //may be there are multiple frames from one device pending.
    //In this case we put it only one time to the pending field
    for ( ; temp_buf != NULL; temp_buf = temp_buf-> next_buf)
    {
        ASSERT (temp_buf->usage == BUFFER_INDIRECT);
        ASSERT((temp_buf > &frame_buffer_array[0]) && (temp_buf <= &frame_buffer_array[ADDR_LIST_LENGTH]));

        if (temp_buf->usage == BUFFER_INDIRECT)
        {
            memcpy(&fcf, &temp_buf->placeholder[0], sizeof(uint16_t));
            if (FCF_GET_DEST_ADDR_MODE(fcf) == FCF_LONG_ADDR)
            {
                memcpy(long_array[long_num], &(temp_buf->placeholder[DESTINATION_ADDRESS_OFFSET]), sizeof(uint64_t));
                long_num++;
            }
            else if (FCF_GET_DEST_ADDR_MODE(fcf) == FCF_SHORT_ADDR)
            {
                memcpy(short_array[short_num], &(temp_buf->placeholder[DESTINATION_ADDRESS_OFFSET]), sizeof(uint16_t));
                short_num++;
            }
        }
    }
    // Build the Pending address specification field
    temp_pend_addr_spec = (long_num << 4);
    temp_pend_addr_spec |= short_num;
    *pending_addr_spec++ = temp_pend_addr_spec;
    num_bytes++;

    // Build the list of short addresses
    for (i=0; i < short_num; i++)
    {
        *pending_addr_spec++ = short_array[i][0];
        *pending_addr_spec++ = short_array[i][1];
        num_bytes+=2;
    }

    // Build the list of extended addresses
    for (i=0; i < long_num; i++)
    {
        //copy the long addr
        for (h=0; h<8; h++)
        {
            *pending_addr_spec++ = long_array[i][h];
        }
        num_bytes+=8;
    }
    return num_bytes;
}
#endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS || defined(DOXYGEN) */

#endif /* APP_TYPE >= APP_L2 */

/* EOF */
