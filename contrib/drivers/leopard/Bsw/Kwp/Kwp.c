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

/// Thim module implements the KWP2000 protocol (ISO 14230-3) and the CAN bus transport layer (ISO 15765-2).
/// - REQ: Riceve i comandi da \b CanCom e li inoltra a \b DiagService (nota: controlla che il messaggio sia corretto rispetto a KWP2000).
/// - REQ: Gestisce l'invio di messaggi 'keep alive' e 'pending request'.
/// - REQ: E' presente un timeout nell'attesa di risposta da DiagService.
/// - REQ: Implements CAN bus transport layer (ISO 15765-2).

#include "BswCommon.h"
#include "Kwp.h"
#include "CanCfg.h"
#include "CanIsoTpCfg.h"
#include "Error.h"
#include "CanDrv.h"
#include "Utilities.h"
#include "DiagService.h"
#include <ee.h>

#define MODULE_ID   (22)

// Task period
#define CAN_ISO_TP_TASK_PERIOD      (20)     /* Unit: msec */

#ifdef UNIT_TEST
#define static          /* Allow unit testing to access private variables */
#endif

// Values for the field PCI (Protocol Control Information, 4 bits)
#define PCI_SINGLE_FRAME            (0)
#define PCI_FIRST_FRAME             (1)
#define PCI_CONSECUTIVE_FRAME       (2)
#define PCI_FLOW_CONTROL_FRAME      (3)

// Size of the fields 'data'
#define SINGLE_FRAME_DATA_SIZE      (6)
#define FIRST_FRAME_DATA_SIZE       (5)
#define CONSECUTIVE_FRAME_DATA_SIZE (6)

/// States for the state machine
typedef enum
{
    STATE_NOT_VALID,
    STATE_IDLE,                     ///< Idle.
    STATE_RX_RECEIVING_CONSECUTIVE, ///< (used during reception) Receiving consecutive frames
    STATE_LOCKED,                   ///< The state machine is waiting for an unlock from DiagService.c. Used to discard receiving data while DiagService.c is managing a response.
    STATE_TX_WAIT_FOR_FC,           ///< (used during transmission) Waiting for a FC (flow control) message, while transmitting a tp-message.
    STATE_TX_SENDING_CONSECUTIVE,   ///< (used during transmission) Sending consecutive frames
} StateMachineType;

/// Events for the state machine
typedef enum
{
    EVENT_NO_EVENT,
    EVENT_TX_REQUESTED,             ///< (used during transmission) DiagService.c request for a transmission.
    EVENT_TX_DONE,                  ///< (used during transmission) DiagService.c has sent the response.
    EVENT_WAIT_FOR_FC,              ///< (used during transmission) Wait for flow control frame
    EVENT_FC_RECEIVED,              ///< (used during transmission) Received a flow control frame
    EVENT_RECEIVED_MESSAGE,         ///< (used during reception) Reception completed (i.e. received a single frame or a last frame).
    EVENT_RECEIVED_FIRST_FRAME,     ///< (used during reception) Received a first frame
    EVENT_RECEIVING_CONSECUTIVE,    ///< (used during reception) Received a consecutive frame
    EVENT_ERROR
} StateMachineEventType;

/// Type for CAN message 8 bytes
typedef union
{
    // Generic frame
    struct
    {
        uint8 kwpAddress;   ///< KWP2000 node address.
#ifdef BITFIELD_MOST_FIRST
        uint8 notUsed1:4;   ///< Bits 4..7. 
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information.
#else
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information.
        uint8 notUsed1:4;   ///< Bits 4..7. 
#endif
        uint8 notUsed2[SINGLE_FRAME_DATA_SIZE];
    } frame;
    
    // Single frame
    // Ex. 85 02 21 95 00 00 00 00
    struct
    {
        uint8 kwpAddress;   ///< KWP2000 node address.
#ifdef BITFIELD_MOST_FIRST
        uint8 size:4;       ///< Bits 4..7. 
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (single frame => pci=0)
#else
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (single frame => pci=0)
        uint8 size:4;       ///< Bits 4..7. 
#endif
        uint8 data[SINGLE_FRAME_DATA_SIZE];
    } singleFrame;
    
    // First frame
    // Ex. 85 10 5F 3B 23 30 31 38
    struct
    {
        uint8 kwpAddress;   ///< KWP2000 node address.
#ifdef BITFIELD_MOST_FIRST
        uint8 size1:4;      ///< Bits 4..7. Size (high)  
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (first frame => pci=1)
#else
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (first frame => pci=1)
        uint8 size1:4;      ///< Bits 4..7. Size (high)  
#endif
        uint8 size2;        ///< Size (low)
        uint8 data[FIRST_FRAME_DATA_SIZE];
    } firstFrame;
    
    // Consecutive frame
    // Ex. 85 20 30 38 34 31 30 30
    struct
    {
        uint8 kwpAddress;   ///< KWP2000 node address.
#ifdef BITFIELD_MOST_FIRST
        uint8 sequenceNr:4; ///< Bits 4..7. Sequence number
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (consecutive frame => pci=2)
#else
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (consecutive frame => pci=2)
        uint8 sequenceNr:4; ///< Bits 4..7. Sequence number.
#endif
        uint8 data[CONSECUTIVE_FRAME_DATA_SIZE];
    } consecutiveFrame;
    
    // Flow control frame
    // Ex. F1 30 FF 0A 00 00 00 00
    struct
    {
        uint8 kwpAddress;   ///< KWP2000 node address.
#ifdef BITFIELD_MOST_FIRST
        uint8 fc:4;         ///< Bits 4..7. Flow control (0 = Clear To Send, 1 = Wait, 2 = Overflow/abort)
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (flow control => pci=3)
#else
        uint8 pci:4;        ///< Bits 0..3. Protocol Control Information (flow control => pci=3)
        uint8 fc:4;         ///< Bits 4..7. Flow control (0 = Clear To Send, 1 = Wait, 2 = Overflow/abort)
#endif
        uint8 blockSize;
        uint8 separationTime;
        uint8 notUsed[4];
    } flowControlFrame;
} CAN_TP_8bytes_buffer_Type;

// Internal state of the component
static InitializationStateType initializationState = COMPONENT_STATE_NOT_INIZIALIZED;
static StateMachineType stateMachine = STATE_NOT_VALID;
static StateMachineEventType event = EVENT_NO_EVENT;
static boolean inhibitRx = FALSE;
static IsoTpChannel_Type currentChannel = 0;

/// CAN 8 bytes message buffer declaration (see CanCfg.c).
static CAN_TP_8bytes_buffer_Type * pIsoTpRx = (CAN_TP_8bytes_buffer_Type *)CanIn_IsoTpRequest_CH0;
static CAN_TP_8bytes_buffer_Type * pIsoTpTx = (CAN_TP_8bytes_buffer_Type *)CanOut_IsoTpResponse_CH0;

static CanTxMsgIndexType responseMessageIndex = IsoTpResponse_CH0;      ///< IsoTo response message index

/// IsoTp message declaration.
static IsoTpRxBuffer_Type rxBuffer;
static IsoTpTxBuffer_Type txBuffer;

/// Transmit a CAN ISO TP message.
/// This is an asynchronous sending: the message is not sent by the current function, it'ssent instead by CanIsoTpTask().
/// - Data are NOT copied locally. The caller must keep the data buffer without modifications, until the sending is completed.
/// - Called by Kwp.c.
/// - Multithread: NO. 
StdReturnType CanIsoTpTransmit()
{
    if (initializationState != COMPONENT_STATE_INIZIALIZED)
    {
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);      // Component must be in INIZIALIZED state.
        return(STD_NOT_INITIALIZED);
    }
    if (stateMachine != STATE_LOCKED)    
    {
        SetError(ERR_ID_GENERIC, TRUE);             // Error: CanIsoTpTransmit() calling sequence error.
        event = EVENT_ERROR;
        return(STD_WRONG_SEQUENCE);
    }
    
    event = EVENT_TX_REQUESTED;     // Note that if this function is called by the callback DiagServiceRequest(), then this event will be lost.
    
    return(STD_OK);
}

/// Receives a diagnostic CAN message on channel 0 or 1.
/// This is an ISR.
/// Data are copied locally, so that a message overrun will not currupt data.
static void RxCallback()
{
    uint16 remainingBytes;
    
    if ( pIsoTpRx->frame.kwpAddress != ECU_KWP_ADDRESS)          // If the message is not for me ...
    {
        return;      // ... ignore the message.
    }
    if (initializationState != COMPONENT_STATE_INIZIALIZED)   // If the message is for me, but I'm not initialized ...
    {
        return;      // ... ignore the message.
    }

//    memcpy(&isoTpRx, CanIn_IsoTpRequest, CAN_DATA_SIZE_8_BYTES);   // Get data
    
    switch (pIsoTpRx->frame.pci)
    {
        case PCI_SINGLE_FRAME:
            // Ex. : 85 02 21 95 00 00 00 00
            if ( (stateMachine != STATE_IDLE)       // State machine must be in idle state
                || (event != EVENT_NO_EVENT) )      // State machine must have consumed all events
            {
                SetError(ERR_ID_GENERIC, TRUE);                        // Error: IsoTp message overrun (protocol error).
                event = EVENT_ERROR;
                return;      // ... ignore the message.
            }
            rxBuffer.size = pIsoTpRx->singleFrame.size;
            if (rxBuffer.size > SINGLE_FRAME_DATA_SIZE)
            {
                SetError(ERR_ID_GENERIC, TRUE);                     // Protocol error: illegal 'size' field.
                event = EVENT_ERROR;
                return;      // ... ignore the message.
            }
            memcpy(rxBuffer.data, pIsoTpRx->singleFrame.data, pIsoTpRx->singleFrame.size);
            event = EVENT_RECEIVED_MESSAGE;
            break;
            
        case PCI_FIRST_FRAME:
            if ( (stateMachine != STATE_IDLE)       // State machine must be in idle state
                || (event != EVENT_NO_EVENT) )      // State machine must have consumed all events
            {
                SetError(ERR_ID_GENERIC, TRUE);                        // Error: IsoTp message overrun (protocol error).
                event = EVENT_ERROR;
                return;      // ... ignore the message.
            }
            rxBuffer.size = (pIsoTpRx->firstFrame.size1 << 8) + pIsoTpRx->firstFrame.size2;
            if (rxBuffer.size <= SINGLE_FRAME_DATA_SIZE)
            {
                SetError(ERR_ID_GENERIC, TRUE);                     // Error: protocol error - with 'first frame' data size must be greater than 7.
                event = EVENT_ERROR;
                return;      // ... ignore the message.
            }
            memcpy(rxBuffer.data, pIsoTpRx->firstFrame.data, FIRST_FRAME_DATA_SIZE);
            rxBuffer.index = FIRST_FRAME_DATA_SIZE;
            rxBuffer.sequenceNr = 0;
            event = EVENT_RECEIVED_FIRST_FRAME;
            break;
            
        case PCI_CONSECUTIVE_FRAME:
            if ( (stateMachine != STATE_RX_RECEIVING_CONSECUTIVE)     // State machine must be in 'receiving consecutive' state
                || ((event != EVENT_NO_EVENT) && (event != EVENT_RECEIVING_CONSECUTIVE)) )    // State machine must have consumed all events, or there's a not consumed 'receiving consecutive' (this is allowed because consecutive frames are received in a burst)
            {
                SetError(ERR_ID_GENERIC, TRUE);                        // Error: IsoTp message overrun (protocol error).
                event = EVENT_ERROR;
                return;      // ... ignore the message.
            }
            if (pIsoTpRx->consecutiveFrame.sequenceNr != rxBuffer.sequenceNr)
            {
                SetError(ERR_ID_GENERIC, TRUE);      // Error: wrong sequence number
                event = EVENT_ERROR;
                return;      // ... ignore the message.
            }
            rxBuffer.sequenceNr = (rxBuffer.sequenceNr+1) & 0x0F;
            remainingBytes = rxBuffer.size - rxBuffer.index;
            if (remainingBytes > CONSECUTIVE_FRAME_DATA_SIZE)  // If this is not the last frame ...
            {
                memcpy(&(rxBuffer.data[rxBuffer.index]), pIsoTpRx->consecutiveFrame.data, CONSECUTIVE_FRAME_DATA_SIZE);
                rxBuffer.index += CONSECUTIVE_FRAME_DATA_SIZE;
                event = EVENT_RECEIVING_CONSECUTIVE;
            }
            else    // If last frame ...
            {   
                memcpy(&(rxBuffer.data[rxBuffer.index]), pIsoTpRx->consecutiveFrame.data, remainingBytes);
                event = EVENT_RECEIVED_MESSAGE;
            }
            break;
            
        case PCI_FLOW_CONTROL_FRAME:
            if ( (stateMachine != STATE_TX_WAIT_FOR_FC)     // State machine must be in 'wait for FC' state
                || (event != EVENT_NO_EVENT) )              // State machine must have consumed all events
            if (stateMachine != STATE_TX_WAIT_FOR_FC)
            {
                SetError(ERR_ID_GENERIC, TRUE);                        // Error: protocol error.
                event = EVENT_ERROR;
                return;      // ... ignore the message.
            }
            event = EVENT_FC_RECEIVED;
            break;
            
        default:
            SetError(ERR_ID_GENERIC, TRUE);      // Error: protocol error - unexpected PCI.
            event = EVENT_ERROR;
            return;      // ... ignore the message.
            break;
    }
}

/// Called by CanDrv.c when the driver receives a diagnostic CAN message on channel 0.
/// This is an ISR.
void rxCallback_IsoTpRequest_CH0(CanRxMsgIndexType msgIndex)
{
    currentChannel = CAN_ISO_TP_CH0;
    pIsoTpRx = (CAN_TP_8bytes_buffer_Type *)CanIn_IsoTpRequest_CH0;
    pIsoTpTx = (CAN_TP_8bytes_buffer_Type *)CanOut_IsoTpResponse_CH0;
    responseMessageIndex = IsoTpResponse_CH0;
    SetPrintChannel(currentChannel);

    GetResource(FlexCAN_mutex);     // Get resource
    RxCallback();
    ReleaseResource(FlexCAN_mutex); // Release resource
}

/// Called by CanDrv.c when the driver receives a diagnostic CAN message on channel 1.
/// This is an ISR.
void rxCallback_IsoTpRequest(CanRxMsgIndexType msgIndex)
{
    currentChannel = CAN_ISO_TP_CH1;
    pIsoTpRx = (CAN_TP_8bytes_buffer_Type *)CanIn_IsoTpRequest;
    pIsoTpTx = (CAN_TP_8bytes_buffer_Type *)CanOut_IsoTpResponse;
    responseMessageIndex = IsoTpResponse;
    SetPrintChannel(currentChannel);

    // TODO: This code may require mutex
    RxCallback();
}

/// Called by CanDrv.c when the transmission of a CAN message is completed.
/*
// todo: serve?
void txCallback_IsoTpResponse(CanTxMsgIndexType msgIndex)
{
    if (initializationState != COMPONENT_STATE_INIZIALIZED)
    {
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);      // Component must be in INIZIALIZED state.
    }
}
*/

/// Initialize the component.
StdReturnType CanIsoTpInit(void)
{
    // If DEVELOPMENT is defined (i.e. during system development), then every function provides stronger checks (see 'Extended error detection')
#ifdef DEVELOPMENT
    // Ensure that sizeof(CAN_TP_8bytes_buffer_Type)=8. Unfortunately sizeof() is evaluated by the compiler, not by the preprocessor, so an #if cannot be used.
    if (sizeof(CAN_TP_8bytes_buffer_Type) != CAN_DATA_SIZE_8_BYTES)
    {
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);      // Size of CAN_TP_8bytes_buffer_Type must be 8.
        return(STD_NOT_OK);     // Statement reachable only during unit testing
    }
#endif

    initializationState = COMPONENT_STATE_NOT_INIZIALIZED;
    
    stateMachine = STATE_IDLE;
    event = EVENT_NO_EVENT;

    initializationState = COMPONENT_STATE_INIZIALIZED;
    
    return(STD_OK);
}

/// Task period: 20 msec (see CAN_ISO_TP_TASK_PERIOD).
// Note: CAN msg (100 bits) at 500kbps = 200 usec
void CanIsoTpTask(void)
{
    uint16 remainingBytes;
    StdReturnType ret;
    static uint16 timer = 0;    // Unit: CAN_ISO_TP_TASK_PERIOD

    // If DEVELOPMENT is defined (i.e. during system development), then every function provides stronger checks (see 'Extended error detection')
#ifdef DEVELOPMENT
    if (initializationState != COMPONENT_STATE_INIZIALIZED)
    {
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);      // Component must be in INIZIALIZED state.
        return;
    }
#endif

    if (event == EVENT_ERROR)
    {
        stateMachine = STATE_IDLE;
    }
    
    switch (stateMachine)
    {
        case STATE_IDLE:
            if (event == EVENT_RECEIVED_MESSAGE)
            {
                ret = DiagServiceRequest(rxBuffer.data, rxBuffer.size, txBuffer.data, &(txBuffer.size) );
                if (ret != STD_OK)      // If DiagService is busy ...
                {
                    SetError(ERR_ID_GENERIC, TRUE);                     // Protocol error: DiagService is busy.
                    break;      // todo: si riesce a fare qualcosa di meglio?
                }
                timer = 0;
                stateMachine = STATE_LOCKED;
            }
            else if (event == EVENT_RECEIVED_FIRST_FRAME)
            {
                // Send flow control frame
                pIsoTpTx->flowControlFrame.kwpAddress = TESTER_KWP_ADDRESS;
                pIsoTpTx->flowControlFrame.pci = PCI_FLOW_CONTROL_FRAME;
                pIsoTpTx->flowControlFrame.fc = 0;               // Clear to send
                pIsoTpTx->flowControlFrame.blockSize = 0;        // No other flow control ftrames
                pIsoTpTx->flowControlFrame.separationTime = 0;   // No separation time required
                CanTransmit(responseMessageIndex);
                
                timer = 0;
                stateMachine = STATE_RX_RECEIVING_CONSECUTIVE;
            }
            break;
            
        case STATE_LOCKED:
            timer++;
            if (timer>=(5000 / CAN_ISO_TP_TASK_PERIOD))      // If elapsed 500 msec ...
            {
                // Error: timeout waiting for flow control frame
                stateMachine = STATE_IDLE;
            }
            else if (event == EVENT_TX_REQUESTED)
            {
                if (txBuffer.size>MAX_ISOTP_TX_MESSAGE_LEN)
                {
                    SetErrorDevelop(ERR_ID_GENERIC, TRUE);
                    stateMachine = STATE_IDLE;
                    break;
                }
                if (txBuffer.size <= SINGLE_FRAME_DATA_SIZE)       // If Single frame ...
                {
                    pIsoTpTx->singleFrame.kwpAddress = TESTER_KWP_ADDRESS;
                    pIsoTpTx->singleFrame.pci = PCI_SINGLE_FRAME;
                    pIsoTpTx->singleFrame.size = txBuffer.size;
                    memset(pIsoTpTx->singleFrame.data, 0, SINGLE_FRAME_DATA_SIZE);
                    memcpy(pIsoTpTx->singleFrame.data, txBuffer.data, txBuffer.size);
                    CanTransmit(responseMessageIndex);
                    stateMachine = STATE_IDLE;
                }
                else    // If multi-frame ...
                {
                    pIsoTpTx->firstFrame.kwpAddress = TESTER_KWP_ADDRESS;
                    pIsoTpTx->firstFrame.pci = PCI_FIRST_FRAME;
                    pIsoTpTx->firstFrame.size1 = (uint8)(txBuffer.size >> 8);
                    pIsoTpTx->firstFrame.size2 = (uint8)txBuffer.size;
                    memcpy(pIsoTpTx->firstFrame.data, txBuffer.data, FIRST_FRAME_DATA_SIZE);
                    txBuffer.index = FIRST_FRAME_DATA_SIZE;     // Next byte to be transmitted
                    txBuffer.sequenceNr = 0;
                    CanTransmit(responseMessageIndex);
                    timer = 0;
                    stateMachine = STATE_TX_WAIT_FOR_FC;
                }
            }
            else if (event == EVENT_TX_DONE)     // If Kwp.c has sent the response ...
            {
                stateMachine = STATE_IDLE;
            }
            break;
        
        case STATE_RX_RECEIVING_CONSECUTIVE:
            timer++;
            if (timer>=(500 / CAN_ISO_TP_TASK_PERIOD))      // If elapsed 500 msec ...
            {
                // Error: timeout waiting for flow consecutive frames
                stateMachine = STATE_IDLE;
            }
            else if (event == EVENT_RECEIVING_CONSECUTIVE)
            {
                // Message is not yet complete
                timer = 0;
            }
            else if (event == EVENT_RECEIVED_MESSAGE)
            {
                ret = DiagServiceRequest(rxBuffer.data, rxBuffer.size, txBuffer.data, &(txBuffer.size) );
                if (ret != STD_OK)      // If DiagService is busy ...
                {
                    SetError(ERR_ID_GENERIC, TRUE);                     // Protocol error: DiagService is busy.
                    stateMachine = STATE_IDLE;
                    break;      // todo: si riesce a fare qualcosa di meglio?
                }
                timer = 0;
                stateMachine = STATE_LOCKED;
            }
            break;
            
        case STATE_TX_WAIT_FOR_FC:
            timer++;
            if (timer>=(500 / CAN_ISO_TP_TASK_PERIOD))      // If elapsed 500 msec ...
            {
                // Error: timeout waiting for flow control frame
                stateMachine = STATE_IDLE;
            }
            else if (event == EVENT_FC_RECEIVED)
            {
                stateMachine = STATE_TX_SENDING_CONSECUTIVE;
            }
            break;
            
        case STATE_TX_SENDING_CONSECUTIVE:
            pIsoTpTx->consecutiveFrame.kwpAddress = TESTER_KWP_ADDRESS;
            pIsoTpTx->consecutiveFrame.pci = PCI_CONSECUTIVE_FRAME;
            pIsoTpTx->consecutiveFrame.sequenceNr = txBuffer.sequenceNr++;
            txBuffer.sequenceNr = (txBuffer.sequenceNr+1) & 0x0F;
            memset(pIsoTpTx->consecutiveFrame.data, 0, CONSECUTIVE_FRAME_DATA_SIZE);
            remainingBytes = txBuffer.size - txBuffer.index;
            if (remainingBytes > CONSECUTIVE_FRAME_DATA_SIZE)  // If this is not the last frame ...
            {
                memcpy(pIsoTpTx->consecutiveFrame.data, &(txBuffer.data[txBuffer.index]), CONSECUTIVE_FRAME_DATA_SIZE);
                CanTransmit(responseMessageIndex);
                txBuffer.index += CONSECUTIVE_FRAME_DATA_SIZE;
            }
            else    // If last frame ...
            {   
                memcpy(pIsoTpTx->consecutiveFrame.data, &(txBuffer.data[txBuffer.index]), remainingBytes);
                CanTransmit(responseMessageIndex);
                //KwpRespTransmitted_callback();
                stateMachine = STATE_IDLE;      // Transmission completed
            }
            break;
            
        default:
            SetErrorDevelop(ERR_ID_GENERIC, TRUE);      // Fatal error: 'stateMachine' has a wrong value
            break;
    }
    
    event = EVENT_NO_EVENT;     // Consume the event
}
