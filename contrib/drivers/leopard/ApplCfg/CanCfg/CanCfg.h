/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef _CANCFG_H_
#define _CANCFG_H_

#include "BswCommon.h"

#define CANCOM_CHANNEL_0_ENABLED                ///< EnableCAN channel 0
#define CANCOM_CHANNEL_1_ENABLED                ///< EnableCAN channel 1

#define CAN_DATA_SIZE_8_BYTES       (8)

////////////////////////////////////////////////////////////////////////////////
// Start of auto-generated section
// ...
// ...

/// List of rx messages. Range [0..NR_OF_CAN_RX_MESSAGES-1].
typedef enum
{
    Ccp_CRO,
    NR_OF_CAN_RX_MESSAGES
} CanRxMsgIndexType;

/// List of tx messages. Range [0..NR_OF_CAN_TX_MESSAGES-1].
typedef enum
{
    Ccp_DTO,
    NR_OF_CAN_TX_MESSAGES
} CanTxMsgIndexType;

typedef uint32 CanMessageId;    ///< CAN message identifier (11 bits or 29 bits, depending on CAN configuration)

/// Handling incoming periodic messages
typedef uint32 CanMessageRxTimestamp;

/// Incomig messages history length
#define HISTORY 4

typedef struct {
    uint8 last;
    uint8 isNew;
    CanMessageRxTimestamp timestamps[HISTORY];
} CanRxConfigTimestamp;

extern CanRxConfigTimestamp canRxMsgPeriods[NR_OF_CAN_RX_MESSAGES];

/// Type for configuration of CanCom.c (tx messages)
typedef struct
{
    uint8 channel;          ///< Message channel.
    CanMessageId id;        ///< Message id.
    uint8 length;           ///< Message length.
    sint8* data;            ///< Pointer to message data.
    boolean periodic;       ///< To be sent on a periodic base.
    sint32 period;          ///< Unit 10 msec.
    void (*txCallback)(CanTxMsgIndexType msgIndex);  ///< If NULL the callback is ignored.
} CanTxMsgConfigType;

/// Type for configuration of CanCom.c (rx messages)
typedef struct
{
    uint8 channel;          ///< Message channel.
    CanMessageId id;        ///< Message id.
    uint8 length;           ///< Message length (DLC).
    sint8* data;            ///< Pointer to message data.
    boolean periodic;       ///< The message is expected to be received periodically.
    sint32 period;          ///< Unit 10 msec.
    void (*rxCallback)(CanRxMsgIndexType msgIndex);  ///< If NULL the callback is ignored.
} CanRxMsgConfigType;

extern const CanTxMsgConfigType canTxMsgConfig[];
extern const CanRxMsgConfigType canRxMsgConfig[];

#endif      // _CANCFG_H_
