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

#include <ee.h>
#include "BswCommon.h"
#include "Kwp.h"
#include "CanCfg.h"
#include "CanIsoTpCfg.h"
#include "Error.h"
#include "CanDrv.h"
#include "CanCfg.h"
#include "CanCom.h"
#include "State.h"
#ifdef BRANCH_PIAGGIO
#include "SpaceVect.h"
#endif		// BRANCH_PIAGGIO

#define MODULE_ID   (25)

#define CAN_COM_COMPUTE_CURRENT_TIMESTAMP_INDEX(x)  (canComRxState[x].next + (NR_OF_RX_TIMESTAMPS - 1)) % NR_OF_RX_TIMESTAMPS
#define CAN_COM_COMPUTE_PREVIOUS_TIMESTAMP_INDEX(x) (canComRxState[x].next + (NR_OF_RX_TIMESTAMPS - 2)) % NR_OF_RX_TIMESTAMPS
#define CAN_COM_COMPUTE_OLDEST_TIMESTAMP_INDEX(x)   (canComRxState[x].next + (NR_OF_RX_TIMESTAMPS + 1)) % NR_OF_RX_TIMESTAMPS

static const uint8 cal_MinimumDelayFactor = 8;  /// Minimum accepted delay between the same message id. Range:0..15. Unit: 1/16. minimum_accepted_delay = message_period / 16 * cal_MinimumDelayFactor.

/// Internal state of the component
static InitializationStateType initializationState = COMPONENT_STATE_NOT_INIZIALIZED;
CanComRxMsgStateType canComRxState[NR_OF_CAN_RX_MESSAGES];
CanComTxMsgStateType canComTxState[NR_OF_CAN_TX_MESSAGES];
static StateMachineType stateMachine = STATE_NOT_VALID;     ///< State of the state machine.
static StateMachineType stateMachine_old = STATE_NOT_VALID; ///< Value of the stateMachine when the task started.
static uint16 after = 0;    ///< Used to calculate the timeout for every state of the 'stateMachine'. Unit:tick (see CAN_ISO_TP_TASK_PERIOD). The timer is automatically reset every time that 'stateMachine' changes. The name 'after' is the same as the Stateflow operator.

const uint32 CanComDelayStartup = 2000; // At startup wait for 2000 msec

/// Variables used to detect "too fast/too fast" message bursts
static uint8 history_ready = 0U;
static boolean first_sample = TRUE;

/// Debug variables
uint32 too_late_errors;
uint32 too_fast_errors;

/// CanCom main task declaration
DeclareTask(Task_CanCom);

static void CanComResetRxState(void)
{
    uint32 i = 0U;
    uint8 j = 0U;

    // Reset ALL message status
    for (i=0; i<NR_OF_CAN_RX_MESSAGES; i++) {
        canComRxState[i].next = 0;
        canComRxState[i].valid = FALSE;
#ifdef DEBUG
        // In DEBUG mode also reset lastTimestamp values (to be easly checked by using a debugger)
        for (j=0; j<NR_OF_RX_TIMESTAMPS; j++) {
            canComRxState[i].lastTimestamps[j] = 0;
        }
#endif
        canComRxState[i].avg = 0;
    }
}

/// This function handles receiving message tardiness (message tardiness is the time between two consecutive message of the same message ID).
static void CanCom_Handle_Msg_Too_Late(uint32 index)
{
    uint32 previous_timestamp = 0;
    uint32 current_timestamp = 0;
    uint32 message_period = 0;      // Unit: msec.
    uint32 interleave = 0U;
    uint8 current_index = 0U;
    uint8 previous_index = 0U;

    // Get current timestamp
    current_index = CAN_COM_COMPUTE_CURRENT_TIMESTAMP_INDEX(index);
    current_timestamp = canComRxState[index].lastTimestamps[current_index];

    if ( (canComRxState[index].next-1) == 0 ) {
        if (first_sample == TRUE) { // Handle first sample (at system startup the last-1 sample is not available)
            previous_timestamp = current_timestamp;

            first_sample = FALSE;
        }
        else {
            previous_timestamp = canComRxState[index].lastTimestamps[NR_OF_RX_TIMESTAMPS - 1];
        }
    }
    else {
        // Get previous timestamp
        previous_index = CAN_COM_COMPUTE_PREVIOUS_TIMESTAMP_INDEX(index);
        previous_timestamp = canComRxState[index].lastTimestamps[previous_index];
    }

    // delay between two consecutive incoming messages (converted to usec)
    interleave = (current_timestamp - previous_timestamp);

    // message period
    message_period = canRxMsgConfig[index].period;

    if ( interleave > (2 * message_period) ) {
        // Make current message as not valid
        canComRxState[index].valid = FALSE;

        // Increment the number of violations for this case
        too_late_errors++;

        // RX message has been received too late (two times later with respect to message period)
        SetError(ERR_ID_GENERIC, TRUE);

        // Reset CanCom
        CanComResetRxState();
        first_sample = TRUE;
        history_ready = 0U;
    }
}

/// Handle too frequent incoming messages.
/// This may be due to a malfunctioning ECU connected to CAN bus.
static CanCom_Handle_Msg_Too_Frequent(uint32 index)
{
    uint32 accumulator = 0U;
    uint8 i = 0U;
    uint32 avg = 0U;
    uint32 message_period = 0;  // Unit: usec.

    if (history_ready > NR_OF_RX_TIMESTAMPS) {  // Check if there are at least NR_OF_RX_TIMESTAMPS messages ready to be processed

        // message period in msec
        message_period = canRxMsgConfig[index].period;

        // Check if the avarage delay between messages is less than a fraction of the current message period
        if (canComRxState[index].avg < (message_period / 16 * cal_MinimumDelayFactor) ) {
            // Make current message as not valid
            canComRxState[index].valid = FALSE;

            // Increment the number of violations for this case
            too_fast_errors++;

            // Last RX messages have been received too fast
            SetError(ERR_ID_GENERIC, TRUE);

            // Reset CanCom
            CanComResetRxState();
            first_sample = TRUE;
            history_ready = 0U;
        }
    }

    history_ready++;
}

// This callback is called by CanDrv module whenever a new periodic CAN message is received
void CanComRxCallback(CanRxMsgIndexType msgIndex)
{
    uint32 current_timestamp;
    uint32 oldest_timestamp;
    uint8 oldestTimestamp_index;

    canComRxState[msgIndex].lastTimestamps[canComRxState[msgIndex].next] = GetClockMsec();  // get timestamp

    canComRxState[msgIndex].valid = TRUE; // Mark this message as new (recent message)

    oldestTimestamp_index = CAN_COM_COMPUTE_OLDEST_TIMESTAMP_INDEX(msgIndex); // Compute oldest timestamp index

    oldest_timestamp = canComRxState[msgIndex].lastTimestamps[oldestTimestamp_index];   // Compute oldest timestamp

    current_timestamp = canComRxState[msgIndex].lastTimestamps[canComRxState[msgIndex].next];   // Compute current timestamp (it is the "next" value immediately before its increment)

    canComRxState[msgIndex].avg = (current_timestamp - oldest_timestamp) / NR_OF_RX_TIMESTAMPS;   // Compute avarege timestamp for the current message

    canComRxState[msgIndex].next = (canComRxState[msgIndex].next + 1) % NR_OF_RX_TIMESTAMPS;    // compute index for next timestamp (increment "next")
}

/// Communication task in input from CANBUS
static void CanComtask(void)
{
    uint32 i = 0U;

    // Handle TX messages
    for (i=0; i<NR_OF_CAN_TX_MESSAGES; i++) {
        if (canComTxState[i].toBeSent == TRUE) {
            // send message
            CanTransmit(i);

            // mark the current message as "not to be sent"
            canComTxState[i].toBeSent = FALSE;
        }
    }
}

// CanCom interface used to send CAN messages
StdReturnType CanComTransmit(CanTxMsgIndexType msgIndex)
{    
    // Check parameters
    SetErrorFatal(ERR_ID_GENERIC, ((uint32)msgIndex >= NR_OF_CAN_TX_MESSAGES));       // Illegal 'msgIndex'

    // Set corresponding TX message as ready to be transmitted
    canComTxState[msgIndex].toBeSent = TRUE;
}

StateMachineType GetCanComState(void)
{
    StdReturnType result = CanDrvCheckBusOff(CHANNEL_FLEXCAN_A);

    // First of all check if CanDrv is in BUSOFF state...
    if (result == STD_NOT_OK) {
        stateMachine = STATE_BUS_OFF;
    }

    // ...if not simply return CanCom state

    return(stateMachine);
}

void CanComSetToBusOff(void)
{
    uint32 i = 0U;
    stateMachine = STATE_BUS_OFF;

    // Reset data structure
    CanComResetRxState();

    SetErrorDevelop(ERR_ID_GENERIC, TRUE);
}

void CanComInit(void)
{
    // todo: check cal_MinimumDelayFactor 0..15.
    
    stateMachine = STATE_START_UP;
}

TASK(Task_CanCom)
{
	uint32 i=0U;
    StdReturnType result = STD_NOT_OK;
    static uint32 old_index[NR_OF_CAN_RX_MESSAGES];
    static uint32 counter = 0U;

    // Send periodic messages
    for (i=0; i<NR_OF_CAN_TX_MESSAGES; i++) {
        if ((counter % (canTxMsgConfig[i].period) == 0U) && canTxMsgConfig[i].periodic == TRUE) {
            canComTxState[i].toBeSent = TRUE;  // Mark current message as a message to be sent
        }
    }

    // Immediatly start delivering periodic messages (if they are marked as "to BeSent" in the previous statement)
    CanComtask();

    // CanCom state machine
    switch (stateMachine)
    {
        case STATE_START_UP:
            // Check if initial delay is expired
            if (after>=(CanComDelayStartup / CAN_COM_TASK_PERIOD)) {  // If elapsed CanComDelayStartup msec ...
                // NOTICE that this is the only way to restart CanCom (even when Busoff condition is detected)
                stateMachine = STATE_RUNNING;
                // Reset data structure
                CanComResetRxState();
            }
            break;

        case STATE_RUNNING:
            // Handle RX messages
            for (i=0; i<NR_OF_CAN_RX_MESSAGES; i++) {
                if (canComRxState[i].next != old_index[i]) {    // Check if there are new incoming messages
                    // Handle incoming message tardiness
                    CanCom_Handle_Msg_Too_Late(i);

                    // Handle too frequent incoming messages (they may be due to a malfunctioning ECU connected to CAN bus)
                    CanCom_Handle_Msg_Too_Frequent(i);

                    // mark the current message as "no more valid"
                    old_index[i] = canComRxState[i].next;
                }
            }
            break;

        case STATE_BUS_OFF:
            // Dummy bus-off state
            break;

        default:
            SetErrorFatal(ERR_ID_DEVELOPMENT, TRUE);      // Fatal error: 'stateMachine' has a wrong value
            break;
    }

    after++;
    if (stateMachine != stateMachine_old) { // If the state has changed ...
        after = 0;                   // The timer is automatically reset every time that 'stateMachine' changes
        stateMachine_old = stateMachine;
    }

	TerminateTask();
}

