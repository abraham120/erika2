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

#include "BswCommon.h"
#include "Ccp.h"
#include "Error.h"
#include "CanDrv.h"
#include <ee.h>

#define CCP_MESSAGE_DIM         8
#define TransmitDTO()           CanTransmit(Ccp_DTO)
#define CMD_IMPLEMENTATION(n)   Ccp_Implementation_##n()

// This task is in charge of managing periodic messages
DeclareTask(Task_Ccp_PeriodicTx);

// States used for CCP state machine (check manual for details)
typedef enum
{
    CCP_CLEAR               = 0,
    CCP_CAL                 = 1<<0,
    CCP_DAQ                 = 1<<1,
    CCP_RESUME              = 1<<2,
    CCP_STORE               = 1<<6,
    CCP_RUNNING             = 1<<7,
    CCP_CONNECTED           = 1<<8,
    CCP_UNCONNECTED         = 1<<9,
    CCP_TEMP_DISCONNECTED   = 1<<10
} StateMachineType;

// This mask has the status reserved bits set to 1
#define STATUS_RESERVED_BITS    (~(CCP_RUNNING | CCP_STORE | CCP_RESUME | CCP_DAQ | CCP_CAL))

// Events for the state machine (inherited by DiagService)
typedef enum
{
    EVENT_NO_EVENT,
    EVENT_RECEIVED_MESSAGE,
    EVENT_DSP_PENDING_RESPONSE
} StateMachineEventType;

typedef enum {
    CCP_RESP_OK,
    CCP_RESP_NOT_OK,
    CCP_NO_RESPONSE
} CcpResponseType;

// Internal state of the component
static InitializationStateType initializationState = COMPONENT_STATE_NOT_INIZIALIZED;
static StateMachineType stateMachine = CCP_CLEAR;
static StateMachineEventType event = EVENT_NO_EVENT;

static uint32 last_mta0 = 0x0U; // Used by DNLOAD, UPLOAD, DNLOAD_6 , SELECT_CAL_PAGE, CLEAR_MEMORY, PROGRAM and PROGRAM_6
static uint32 last_mta1 = 0x0U; // Used by MOVE
static uint8 result = CCP_RESP_NOT_OK;

char CanIn_Ccp_CRO[CCP_MESSAGE_DIM];
char CanOut_Ccp_DTO[CCP_MESSAGE_DIM];
char ccp_tmp_received_buffer[CCP_MESSAGE_DIM];

const uint32 CanIn_Ccp_CRO_size = sizeof(CanIn_Ccp_CRO);
const uint32 CanOut_Ccp_DTO_size = sizeof(CanOut_Ccp_DTO);

// DAQ lists
Ccp_DaqList DaqList[CCP_MAX_DAQ];

static Ccp_Cro Current_CRO;
static Ccp_ConnectionStatus = CCP_UNCONNECTED; // ECU Initial status

// Used by SET_DAQ_PTR and WRITE_DAQ
static uint8* DaqPtr = NULL;
static uint32* DaqSizePtr = NULL;

// Data structure fetauring the ECU in term of resource availability:
// This ECU has Calibrations
// This ECU has Daq
// This ECU does not have Flash programming capability (using CCP)
static const uint8 Ccp_ResourceAvailabilityMask = CCP_SET_RES_AVAILABLE(CCP_MASK_CAL) | \
                                                CCP_SET_RES_AVAILABLE(CCP_MASK_DAQ) | \
                                                CCP_SET_RES_UNAVAILABLE(CCP_MASK_PGM);

// Initial resource protection status:
// This ECU has Calibrations not protected
// This ECU has Daq not protected
// This ECU has Flash programming capability (using CCP) not protected
const uint8 Ccp_InitialResourceProtectionMask = CCP_SET_RES_UNPROTECTED(CCP_MASK_CAL) | \
                                                CCP_SET_RES_UNPROTECTED(CCP_MASK_DAQ) | \
                                                CCP_SET_RES_UNPROTECTED(CCP_MASK_PGM);

// Data structure featuring the ECU in term of resource protection
static uint8 Ccp_ResourceProtectionMask = Ccp_InitialResourceProtectionMask;

// shared between isr callback and periodc task (CcpTask)
char tmp_receive_buffer[CCP_MESSAGE_DIM];

// Statically defined as Expected by Tester Tool in .a2l file
static const uint32 Ccp_EventChannels[CCP_EVENT_CH_NUM] = {100U, 10U, 5U};

// Slave Device Id (mentioned in EXCHANGE_ID command)
static const uint32 slaveId = 0x00000001U;

// (Slave) Station Address (Trivially, slave is the ECU where this code is running)
static const uint16 slaveStationAddress = CCP_TESTER_STATION_ADDR; // This value is reported in .a2l file (see StationAddress value)

// This table contains all DSP variable used by CCP
static Ccp_DspMirrorType dspMirror[CCP_DSP_VARIABLES_NUM];

// This variable is populated as soon as a response from the DSP is ready (the allowed values for this variable are: CCP_DNLOAD, CCP_DNLOAD_6, CCP_UPLOAD, CCP_SHORT_UPLOAD)
static uint8 DSP_response = 0x00U;

// This variable is used to manage DSP response message size
static uint8 DSP_size = 0x00U;

static uint32 Ccp_InsertDspElement(uint32 dsp_address)
{
    uint32 i = 0U;
    uint32 position = CCP_DSP_MIRROR_FULL;

    // Find out the first free position inside the dsp mirror table
    for (i=0; i<CCP_DSP_VARIABLES_NUM; i++) {
        if (dspMirror[i].used == FALSE) {   // Check if this i-th position is free
            dspMirror[i].used = TRUE;   // If it is free, it is marked as used
            dspMirror[i].remoteAddr = dsp_address;
            dspMirror[i].value = 0xFFFFFFFF;   // Init with a dummy value

            position = i;

            break;
        }
    }

    return(position);
}

static uint32 Ccp_RemoveDspElement(uint32 dsp_address)
{
    uint32 i = 0U;
    uint32 position = CCP_DSP_ELEMENT_NOT_FOUND;

    for (i=0; i<CCP_DSP_VARIABLES_NUM; i++) {
        if ( (dspMirror[i].used == TRUE) && (dsp_address == (uint32)&dspMirror[i].value) ) {
            dspMirror[i].used = FALSE;

            position = i;

            break;
        }
    }

    return(position);
}

static void Ccp_ClearDaqList(uint8 DaqListIndex)
{
    uint8 i = 0U;
    uint8 j = 0U;

    // No need to check DaqListIndex since it is already checked from the caller

    DaqList[DaqListIndex].prescaler = 1;        // Reset prescaler

    // Reset last, it is set to the minimum value to prevent from starting the sampling this DAQ list
    DaqList[DaqListIndex].last = 0;
    DaqList[DaqListIndex].eventChannel = 0xFF;  // Reset eventChannel

    // Reset ODTs
    for (i=0; i<CCP_MAX_ODT; i++) { // for ech ODT of this DAQlist
        for (j=0; j<7; j++) { // for each element of this ODT
            // Remove the corresponding DSP-mirrored address if it exists
            Ccp_RemoveDspElement((uint32)DaqList[DaqListIndex].odts[i].ODT[j].ptr);

            DaqList[DaqListIndex].odts[i].ODT[j].ptr = NULL; // reset data pointer for this ODT element
            DaqList[DaqListIndex].odts[i].ODT[j].size = 0U;  // reset size for this ODT element
            DaqList[DaqListIndex].odts[i].transmitThisOdt = FALSE; // reset transmission flag

            memset(DaqList[DaqListIndex].odts[i].data, 0x00, sizeof(DaqList[DaqListIndex].odts[i].data));   // reset 7-bytes ODT data field
        }
    }

    DaqList[DaqListIndex].flags = DAQ_FLAG_CLEAR;    // Set this DAQ list as cleared

    // This DAQ list is now cleared
}

static void Ccp_ClearAllDaqList(void)
{
    uint8 i;

    for (i=0; i<CCP_MAX_DAQ; i++) { // for ech DAQ List
        Ccp_ClearDaqList(i); // Clear current DAQ List
    }
}

static void Ccp_PrepareDaqList(uint8 DaqListIndex, uint8 last, uint8 eventChannel, uint8 prescaler)
{
    // No need to check DaqListIndex since it is already checked from the caller

    DaqList[DaqListIndex].prescaler = prescaler;        // Prepare prescaler
    DaqList[DaqListIndex].last = last;                  // Prepare last ODT value (All ODT from 0 to last are activated)
    DaqList[DaqListIndex].eventChannel = eventChannel;  // Prepare eventChannel
    DaqList[DaqListIndex].flags = DAQ_FLAG_PREPARE;     // Set this DAQ list prepared

    // This DAQ list is now prepared
}

static uint8 Ccp_IsDaqListPrepared(uint8 DaqListIndex)
{
    uint8 local_flag;

    if (DaqList[DaqListIndex].flags == DAQ_FLAG_PREPARE) {
        local_flag = TRUE;
    }
    else {
        local_flag = FALSE;
    }

    return local_flag;
}

static void Ccp_StartDaqlist(uint8 DaqListNumber)
{
    DaqList[DaqListNumber].flags = DAQ_FLAG_START;   // Mark this DAQ list as STARTED
}

// This command is used to start the periodic transmission of all DAQ lists
// configured with the previously sent START_STOP command (start/stop modus
// = 2) as „prepared to start“ in a synchronized manner
static void Ccp_StartAllDaqLists(void)
{
    uint32 i;

    for (i=0; i<CCP_MAX_DAQ; i++) { // Loop through ALL DAQ lists
        if (DaqList[i].flags == DAQ_FLAG_PREPARE) { // If this DAQ list has been previously configured as PREPARED
            DaqList[i].flags = DAQ_FLAG_START;   // Mark this DAQ list as STARTED
        }   
    }
}

// The command is used to stop the periodic transmission of all
// DAQ lists, including those not started synchronized.
static void Ccp_StopDaqlist(uint8 DaqListNumber)
{
    DaqList[DaqListNumber].flags = DAQ_FLAG_STOP;   // Mark this DAQ list as STARTED
}

static void Ccp_StopAllDaqLists(void)
{
    uint32 i;

    for (i=0; i<CCP_MAX_DAQ; i++) { // Loop through ALL DAQ lists
        DaqList[i].flags = DAQ_FLAG_STOP;   // Mark this DAQ list as STOPPED
    }
}

static uint8 Ccp_IsThisEcuConnected(void)
{
    if (Ccp_ConnectionStatus == CCP_CONNECTED) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

static void Ccp_Implementation_CCP_CONNECT(void)
{
    // CCP Guide: 12.1 Connect
    // A CONNECT command to an already connected station is acknowledged. A slave device
    // does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address

    // Get station address from incoming message.
    // Notice that station address is specified as a number in little-endian byte order (Intel format, low byte first)
    uint16 local_station_address = Current_CRO.CmdParams[1]<<8 | Current_CRO.CmdParams[0];

    // Check if the connection command has been sent by a valid station
    // A CONNECT command to an already connected station is acknowledged
    if (local_station_address == slaveStationAddress) {
        Ccp_ConnectionStatus = CCP_CONNECTED;

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
    else {
        // In case of "Invalid station address" return CCP_PARAMS_OUT_OF_RANGE (check Error code Matrix)
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
}

static void Ccp_Implementation_CCP_GET_DAQ_SIZE(void)
{
    // Get current DAQ list index
    uint8 DaqIndex = Current_CRO.CmdParams[0];

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Check the availability of the specified DAQ list
    if (DaqIndex < CCP_MAX_DAQ) {
        CanOut_Ccp_DTO[3] = CCP_MAX_ODT;    // All the DAQ list have the same number of ODTs
        CanOut_Ccp_DTO[4] = CCP_MAX_ODT * Current_CRO.CmdParams[0]; // the first ODT pid of a DAQ list can be easily computed by using this formula

        // TODO: CAN Identifier of DTO is not used in this ECU (for details 12.11 Get Size of DAQ list). It seems not used by Eldor ECU too.

        // Clears and initializes the current list
        Ccp_ClearDaqList(DaqIndex);
    }
    else {
        // If the specified list number is not available, size = 0 should be returned (source: CCP 2.1 guide, Ch. 12.11)
        CanOut_Ccp_DTO[3] = 0U; // TODO: check this point since it could not match with the error matrix (CCP 2.1 guide, Ch. 16.1)
    }

    // This assignment affects first three bytes of the response message
    result = CCP_RESP_OK;
}

static void Ccp_Implementation_CCP_SET_MTA(void)
{
    // Get MTA0/1
    uint8 mtaId = Current_CRO.CmdParams[0];

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Decode current MTA (It may be 0 or 1)
    if (mtaId == IS_MTA0) {
        last_mta0 = CCP_COMPUTE_MTA(Current_CRO);

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
    else if (mtaId == IS_MTA1) {
        last_mta1 = CCP_COMPUTE_MTA(Current_CRO);

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
    else {
        // Error in input parameters
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
}

// This function implements a XCP_ADD_44 checksum as expected by ATI Vision Tool
// Result size: 32 bit
// Family (CS=Checksum/CRC=Cyclic redundancy check): CS
// Default size: 32768
// Description: Add 4-byte values to a 4-byte checksum.
static void Ccp_Implementation_CCP_BUILD_CHECKSUM(void)
{
    uint32 size = 0U;
    uint32 swappedWord = 0U;
    uint32 checksum = 0U;
    uint32 localaddr = 0U;

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Embed checksum dimension in the response
    CanOut_Ccp_DTO[3] = CCP_CHECKSUM_SIZE;

    // Get the size of the area the user request to compute checksum
    size = Current_CRO.CmdParams[0]<<24 | Current_CRO.CmdParams[1]<<16 |
        Current_CRO.CmdParams[2]<<8 | Current_CRO.CmdParams[3];

    for (localaddr = last_mta0;  localaddr < last_mta0 + size; localaddr+=4)
    {
            swappedWord = 0x0U;
            swappedWord |=  *(uint8_t *)(localaddr  );
            swappedWord |= (*(uint8_t *)(localaddr+1))<<8;
            swappedWord |= (*(uint8_t *)(localaddr+2))<<16;
            swappedWord |= (*(uint8_t *)(localaddr+3))<<24;
                
            checksum += swappedWord;
    }

    // Assign checksum to DTO response
    memcpy(&CanOut_Ccp_DTO[4], &checksum, 4);

    // This assignment affects first three bytes of the response message
    result = CCP_RESP_OK;
}

static void Ccp_Implementation_CCP_GET_SEED(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_UNLOCK(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_SELECT_CAL_PAGE(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_CLEAR_MEMORY(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_PROGRAM(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_PROGRAM_6(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_DIAG_SERVICE(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_ACTION_SERVICE(void) { /* TODO!!! */ while(1); }
static void Ccp_Implementation_CCP_GET_ACTIVE_CAL_PAGE(void) { /* TODO!!! */ while(1); }

// This function has never been tested (no known way to trigger from a CCP master tool)
static void Ccp_Implementation_CCP_MOVE(void)
{
    // It is expected that MTA0 and MTA1 are properly populated before receiving this command from Master Station

    uint32 size;

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command wiCCP_SRAM_UPPER_BOUND_ADDRth the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Get the size of the area to be copied from MTA0 to MTA1
    size = Current_CRO.CmdParams[0]<<24 | Current_CRO.CmdParams[1]<<16 |
        Current_CRO.CmdParams[2]<<8 | Current_CRO.CmdParams[3];

    memcpy((uint8*)last_mta1, (uint8*)last_mta0, size);

    // This assignment affects first three bytes of the response message
    result = CCP_RESP_OK;
}

static void Ccp_Implementation_CCP_CCP_VERSION(void)
{
    // This command performs a mutual identification of the protocol version used in the
    // master and in the slave device to aggree on a common protocol version. This
    // command is expected to be executed prior to the EXCHANGE_ID command.

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    if (Current_CRO.CmdParams[0] == CCP_MAIN_PROTOCOL_VERSION &&    // Check if main protocol version is as expected
        Current_CRO.CmdParams[1] == CCP_RELEASE_WITHIN_VERSION)     // Check if release within version is as expected
    {
        CanOut_Ccp_DTO[3] = CCP_MAIN_PROTOCOL_VERSION;
        CanOut_Ccp_DTO[4] = CCP_RELEASE_WITHIN_VERSION;

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
}

static void Ccp_Implementation_CCP_TEST(void)
{
    // This command is used to test if the slave with the specified station address is
    // available for CCP communication. This command does not establish a logical
    // connection nor does it trigger any activities in the specified slave. Station
    // address is specified as a number in little-endian byte order (Intel format, low
    // byte first).

    uint16 local_stationAddress;

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Get Station Address
    local_stationAddress = (Current_CRO.CmdParams[1] << 8) | Current_CRO.CmdParams[0];

    // Check whether the received station address is refere to slaveStationAddress
    if (local_stationAddress == slaveStationAddress) {
        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
    else {
        // Error in input parameter
        result = CCP_RESP_NOT_OK;
    }
}

static void Ccp_Implementation_CCP_EXCHANGE_ID(void)
{
    // The CCP master and slave stations exchange IDs for automatic session
    // configuration. This might include automatic assignment of a data acquisition
    // setup file depending on the slave's returned ID (Plug ́n ́Play)

    uint8 masterId;

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }
    
    // get Master Id information
    masterId = Current_CRO.CmdParams[0];

    // Build up response
    CanOut_Ccp_DTO[3] = sizeof(slaveId);    // length of slave device ID in bytes

    CanOut_Ccp_DTO[4] = 0x00;   // data type qualifier of slave device ID (optional and implementation specific). Not used by this CCP driver

    CanOut_Ccp_DTO[5] = Ccp_ResourceProtectionMask;   // Resource Availability Mask

    CanOut_Ccp_DTO[6] = Ccp_InitialResourceProtectionMask;   // Resource Protection Mask

    // byte 7 is "don't care"

    // This assignment affects first three bytes of the response message
    result = CCP_RESP_OK;
}

static void Ccp_Implementation_CCP_DNLOAD(void)
{
    uint8 size = Current_CRO.CmdParams[0]; // Size of data block to be downloaded in bytes (1...5)

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Check Size (Must be from 1 to 5)
    if (size > 5U || size == 0U) {
        // Error in input parameter
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
    else if (last_mta0 >= CCP_FLASH_LOWER_BOUND_ADDR && last_mta0 <= CCP_FLASH_UPPER_BOUND_ADDR) {  // Write attempt to ROM
        result = CCP_ACCESS_DENIED;
    }
    else {
        // Notice that MTA0 is alredy populated by a previous SET_MTA command (SET_MTA must precede DOWNLOAD)

        // The data block of the specified length (size) contained in the CRO will be copied into
        // memory, starting at the current Memory Transfer Address 0 (MTA0). The MTA0 pointer will
        // be post-incremented by the value of 'size'...
        // ...but first of all check if this memory address (MTA0) belongs to the DSP or PPC memory area

        memcpy((uint8*)last_mta0, &Current_CRO.CmdParams[1], size); // get MTA0

        if (CCP_COMPUTE_ADDR_SPACE_ID(last_mta0) == DSP) {
            // If the address is a DSP-address
            // TODO: send the corresponding message to DSP (by using SpiDrv)

            // Save "size" value for this specific command, it will be used as soon as the DSP will send the response (look at the state machine in CcpTask)
            DSP_size = size;

            // Set command type (used by CcpTask to figure out which type of DSP response is received)
            DSP_response = CCP_DNLOAD;

            // Do not send the response at this step because the DSP result for this command arrives (asynchronously) through rxCallback_DSP_response_ready()
            result = CCP_NO_RESPONSE;
        }
        else {
            // Build up the remaining bytes of the response message
            CanOut_Ccp_DTO[3] = 0x00;   // MTA extension not used by this CCP Driver (hence don't care)

            // The MTA0 pointer is post-incremented by the value of 'size'...
            last_mta0 = last_mta0 + size;

            // ...and returned as response values (from 4 to 7)
            memcpy(&CanOut_Ccp_DTO[4], &last_mta0, sizeof(last_mta0));

            // This assignment affects first three bytes of the response message
            result = CCP_RESP_OK;
        }
    }
}

static void Ccp_Implementation_CCP_DNLOAD_6(void)
{
    // Notice that MTA0 is alredy populated by a previous SET_MTA command (SET_MTA must precede DOWNLOAD)

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    if (last_mta0 >= CCP_FLASH_LOWER_BOUND_ADDR && last_mta0 <= CCP_FLASH_UPPER_BOUND_ADDR) {  // Write attempt to ROM
        result = CCP_ACCESS_DENIED;
    }
    else {
        // The data block with the fixed length (size) of 6 bytes contained in the CRO will be copied
        // into memory, starting at the current Memory Transfer Address0 (MTA0). The MTA0 pointer
        // will be post-incremented by the value 6...
        // ...but first of all check if this memory address (MTA0) belongs to the DSP or PPC memory area

        memcpy((uint8*)last_mta0, &Current_CRO.CmdParams[0], 6);    // get MTA0

        if (CCP_COMPUTE_ADDR_SPACE_ID(last_mta0) == DSP) {
            // If the address is a DSP-address
            // TODO: send the corresponding message to DSP (by using SpiDrv)

            // Set command type (used by CcpTask to figure out which type of DSP response is received)
            DSP_response = CCP_DNLOAD_6;

            // Do not send the response at this step because the DSP result for this command arrives (asynchronously) through rxCallback_DSP_response_ready()
            result = CCP_NO_RESPONSE;
        }
        else {
            // Build up the remaining bytes of the response message
            CanOut_Ccp_DTO[3] = 0x00;   // MTA extension not used by this CCP Driver (hence don't care)

            // The MTA0 pointer is post-incremented by the value of 6...
            last_mta0 = last_mta0 + 6;

            // ...and returned as response values (from 4 to 7)
            memcpy(&CanOut_Ccp_DTO[4], &last_mta0, sizeof(last_mta0));

            // This assignment affects first three bytes of the response message
            result = CCP_RESP_OK;
        }
    }
}

static void Ccp_Implementation_CCP_SHORT_UPLOAD(void)
{
    uint8 size = Current_CRO.CmdParams[0]; // Size of data block to be uploaded in bytes (1...5)
    uint8* addr = (uint8*)CCP_COMPUTE_SHORT_UPLOAD_ADDR(Current_CRO);

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    if ((size > 5U) ||    // Check Size (Must be from 1 to 5)
    ((uint32)addr < CCP_SRAM_LOWER_BOUND_ADDR || (uint32)addr > CCP_SRAM_UPPER_BOUND_ADDR) && // Check if base address is illegal (out of SRAM)
    ((uint32)addr < CCP_FLASH_LOWER_BOUND_ADDR || (uint32)addr > CCP_FLASH_UPPER_BOUND_ADDR) ) { // Check if base address is illegal (out of FLASH)
        // Error in input parameter
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
    else {
        // A data block of the specified length (size), starting at source address will be copied into the
        // corresponding DTO data field. The MTA0 pointer remains unchanged...
        // ...but first of all check if this memory address (addr) belongs to the DSP or PPC memory area
        if (CCP_COMPUTE_ADDR_SPACE_ID((uint32)addr) == DSP) {
            // If the address is a DSP-address
            // TODO: send the corresponding message to DSP (by using SpiDrv)

            // Set command type (used by CcpTask to figure out which type of DSP response is received)
            DSP_response = CCP_SHORT_UPLOAD;

            // Save "size" value for this specific command, it will be used as soon as the DSP will send the response (look at the state machine in CcpTask)
            DSP_size = size;

            // Do not send the response at this step because the DSP result for this command arrives (asynchronously) through rxCallback_DSP_response_ready()
            result = CCP_NO_RESPONSE;
        }
        else {
            memcpy(&CanOut_Ccp_DTO[3], addr, size);

            // This assignment affects first three bytes of the response message
            result = CCP_RESP_OK;
        }         
    }
}

static void Ccp_Implementation_CCP_UPLOAD(void)
{
    uint8 size = Current_CRO.CmdParams[0]; // Size of data block to be uploaded in bytes (1...5)
    // remaining bytes are don't care

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Check Size (Must be from 1 to 5)
    if (size > 5U) {    // Check Size (Must be from 1 to 5)

        // Error in input parameter
        result = CCP_PARAMS_OUT_OF_RANGE;   // This value is returned even thought not directly mentioned b y Ch. 16.1
    }
    else {
        // A data block of the specified length (size), starting at source address will be copied into the
        // corresponding DTO data field. The MTA0 pointer remains unchanged...
        // ...but first of all check if this memory address (MTA0) belongs to the DSP or PPC memory area
        if (CCP_COMPUTE_ADDR_SPACE_ID(last_mta0) == DSP) {
            // If the address is a DSP-address
            // TODO: send the corresponding message to DSP (by using SpiDrv)

            // Set command type (used by CcpTask to figure out which type of DSP response is received)
            DSP_response = CCP_UPLOAD;

            // Save "size" value for this specific command, it will be used as soon as the DSP will send the response (look at the state machine in CcpTask)
            DSP_size = size;

            // Do not send the response at this step because the DSP result for this command arrives (asynchronously) through rxCallback_DSP_response_ready()
            result = CCP_NO_RESPONSE;
        }
        else {
            memcpy(&CanOut_Ccp_DTO[3], (uint8*)last_mta0, size);    // copy MTA0 to response message

            // The MTA0 pointer is post-incremented by the value of 'size'.
            last_mta0 = last_mta0 + size;

             // This assignment affects first three bytes of the response message
            result = CCP_RESP_OK;
        }
    }
}

static void Ccp_Implementation_CCP_START_STOP(void)
{
    // Get input parameters
    uint8 DaqListNumber = Current_CRO.CmdParams[1];
    uint8 LastOdtNumber = Current_CRO.CmdParams[2];
    uint8 EventChannelNumber = Current_CRO.CmdParams[3];
    uint16 Prescaler = Current_CRO.CmdParams[4]<<8 | Current_CRO.CmdParams[5];

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    if (DaqListNumber >= CCP_MAX_DAQ) {
        // Error in case of Start/Stop of nonexistent DAQ list
        result = CCP_ACCESS_DENIED;
    }
    else if ( (LastOdtNumber >= CCP_MAX_ODT) || 
                (EventChannelNumber >= CCP_EVENT_CH_NUM) ||
                (Prescaler <= 0U) || 
                ((Current_CRO.CmdParams[0] != START) &&
                (Current_CRO.CmdParams[0] != STOP) &&
                (Current_CRO.CmdParams[0] != PREPARE)) ) {
        // Illegal last ODT/Line transm. interval, illegal start/stop param.
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
    else if (Current_CRO.CmdParams[0] == START && Ccp_IsDaqListPrepared(DaqListNumber) == FALSE) {
        // Error Starting DAQ of an unconfigured DAQ list (CCP 2.1 guide, Ch. 16.1: Matrix Error Codes)
        result = CCP_DAQ_LIST_INIT_REQ;

        // But ATI Vision expects DAQ list is configured and then expects to receive messages from such List...
        Ccp_PrepareDaqList(DaqListNumber, LastOdtNumber, EventChannelNumber, Prescaler);

        // ...hence start this DAQ list
        Ccp_StartDaqlist(DaqListNumber);

        // TODO: this solution seem to meet ATI Vision requirements, hence it has been adopted but
        // in the future (with different tools) it may produce a non standard behaviour.
    }
    else {
        // Decode if this command is: start, stop or prepare
        if (Current_CRO.CmdParams[0] == START) {
            // Start this DAQ list
            Ccp_StartDaqlist(DaqListNumber);
        }
        else if (Current_CRO.CmdParams[0] == STOP) {
            // Stop this DAQ
            Ccp_StopDaqlist(DaqListNumber);
        }
        else {  // ...else PREPARE case
            // Only prepare this DAQ list for a synchronized start (START_STOP_ALL)
            Ccp_PrepareDaqList(DaqListNumber, LastOdtNumber, EventChannelNumber, Prescaler);
        }

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
}

static void Ccp_Implementation_CCP_WRITE_DAQ(void)
{
    uint32 daq_addr;
    uint32 physical_ddr;        // Address in the space of PPC or DSP, depending on AddrSpId
    uint32 AddrSpId;            //  'address space id' is used to identify the address space (i.e. PPC or DPS)
    uint32 current_position;
    uint32 dspMirrorTmpValue;

    daq_addr = CCP_COMPUTE_DAQ_ADDR(Current_CRO);

    *DaqSizePtr = Current_CRO.CmdParams[0]; // Size of DAQ element in bytes { MUST be 1, 2, 4 }

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_ConnectionStatus != CCP_CONNECTED) {
        result = CCP_NO_RESPONSE;
    }
    else {
        // Compute physical address starting from addrExt
        physical_ddr = CCP_COMPUTE_PHYSICAL_ADDR(daq_addr);

        // Compute AddrSpId
        AddrSpId = CCP_COMPUTE_ADDR_SPACE_ID(daq_addr);

        // Check input parameters
        if ( (AddrSpId != PPC && AddrSpId != DSP) ||                                                    // Check if the address does not belong to DSP or PPC SRAM-area OR...
            (*DaqSizePtr != 1 && *DaqSizePtr != 2 && *DaqSizePtr != 4) ||                               // ...check if the size of this ODT is allowed (1,2,4 bytes) OR...
            ( AddrSpId == PPC && (physical_ddr < CCP_SRAM_LOWER_BOUND_ADDR || physical_ddr > CCP_SRAM_UPPER_BOUND_ADDR) ) ) {   // ...check if destination address is outside PPC SRAM memory area

            // In ALL these cases the following error (according with the Error Matrix 16.1 of the CCP manual) is issued
            result = CCP_PARAMS_OUT_OF_RANGE;
        }
        else {
            if (AddrSpId == PPC) {
                // Internal PPC SRAM
                memcpy(DaqPtr, &physical_ddr, 4); // Address of DAQ element is (Always) a 4 bytes value
            }
            else {
                // DSP memory area
                current_position = Ccp_InsertDspElement(physical_ddr); // Insert a new element in DSP mirror table
                dspMirrorTmpValue = (uint32)&dspMirror[current_position].value; // Address of DAQ element is (Always) a 4 bytes value
                memcpy(DaqPtr, &dspMirrorTmpValue, 4); // Address of DAQ element is (Always) a 4 bytes value
            }


            // This assignment affects first three bytes of the response message
            result = CCP_RESP_OK;
        }
    }
}

static void Ccp_Implementation_CCP_SET_DAQ_PTR(void)
{
    // Get input parameters
    uint8 DaqListNumber = Current_CRO.CmdParams[0];
    uint8 OdtNumber = Current_CRO.CmdParams[1];
    uint8 OdtElement = Current_CRO.CmdParams[2];

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Check input parameters
    if ( (DaqListNumber >= CCP_MAX_DAQ) ||  /* Check DAQ List Number*/
        (OdtNumber >= CCP_MAX_ODT) ||       /* Check ODT Number */
        (OdtElement >= 7) )  /* Check Event Channel Number */
    {
        // Input parameters error
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
    else {
        // This value i used by subsequent WRITE_DAQ command to populate a specific element (the address value)
        DaqPtr = (uint8*)&DaqList[DaqListNumber].odts[OdtNumber].ODT[OdtElement].ptr;
        DaqSizePtr = &DaqList[DaqListNumber].odts[OdtNumber].ODT[OdtElement].size;

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
}

static void Ccp_Implementation_CCP_DISCONNECT(void)
{
    // The session status bits are read/write to the slave device and are be cleared on power-up,
    // on session log-off and in applicable fault conditions.

    // Get Station Address
    uint16 local_stationAddress = (Current_CRO.CmdParams[3] << 8) | Current_CRO.CmdParams[2];

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    if ((Current_CRO.CmdParams[0] != CCP_DISCONNECT_TEMP &&
        Current_CRO.CmdParams[0] != CCP_DISCONNECT_END_SESSION) ||
        local_stationAddress != slaveStationAddress) {
        // Invalid Station Address, invalid temporary disconnect param (CCP 2.1 guide, Ch. 16.1 Matrix of error Codes)
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
    else {
        if (Current_CRO.CmdParams[0] == CCP_DISCONNECT_TEMP) {
            // A temporary disconnect doesn’t stop the transmission of DAQ messages.
            // The MTA values, the DAQ setup, the session status and the protection
            // status are unaffected by the temporary disconnect and remain unchanged.

            Ccp_ConnectionStatus = CCP_TEMP_DISCONNECTED;
        }
        else {
            // Reset MTA0 and MTA1
            last_mta0 = 0x0U;
            last_mta1 = 0x0U;

            // Reset DAQ Lists
            Ccp_ClearAllDaqList();

            // Set current status as UNCONNECTED
            Ccp_ConnectionStatus = CCP_UNCONNECTED;

            // Terminating the session invalidates all state information and
            // resets the slave protection status.
            stateMachine = CCP_CLEAR;
            Ccp_ResourceProtectionMask = Ccp_InitialResourceProtectionMask;
        }

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
}

static void Ccp_Implementation_CCP_START_STOP_ALL(void)
{
    // Get START/STOP command
    uint8 start_stop = Current_CRO.CmdParams[0];

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    if (start_stop == START) {
        // Start All (previously configured as PREPARED) DAQ lists
        Ccp_StartAllDaqLists();

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
    else if (start_stop == STOP) {
        // Start All DAQ lists (including those not started synchronized)
        Ccp_StopAllDaqLists();

        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
    else {
        // Error in input parameter
        result = CCP_RESP_NOT_OK;
    }   
}

static void Ccp_Implementation_CCP_SET_S_STATUS(void)
{
    stateMachine = Current_CRO.CmdParams[0];

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // Check if status requested by Station is valid or affects reserved bits
    if ((stateMachine & STATUS_RESERVED_BITS) == STATUS_RESERVED_BITS) {
        // There is an error in the transition status requested by Station
        result = CCP_PARAMS_OUT_OF_RANGE;
    }
    else {
        // This assignment affects first three bytes of the response message
        result = CCP_RESP_OK;
    }
}

static void Ccp_Implementation_CCP_GET_S_STATUS(void) 
{
    CanOut_Ccp_DTO[3] = stateMachine;

    // A slave device does not respond to any commands unless being addressed by a prior CONNECT
    // command with the correct station address
    if (Ccp_IsThisEcuConnected() == FALSE) {
        result = CCP_NO_RESPONSE;
        return;
    }

    // This assignment affects first three bytes of the response message
    result = CCP_RESP_OK;
}

// This function unpack the incoming message (that represents the request sent by the Tester Tool) to a CRO instance
static void Cro_Get_Message(void)
{
    Current_CRO.Cmd = ccp_tmp_received_buffer[0];
    Current_CRO.Ctr = ccp_tmp_received_buffer[1];
    memcpy(Current_CRO.CmdParams, &ccp_tmp_received_buffer[2], 6);
}

// Asyncronously called by Can Driver
extern void rxCallback_Ccp_CRO(CanRxMsgIndexType msgIndex)
{
    // TODO: required mutex lock since this is called asynchronously with respect to CcpTask
    memcpy(tmp_receive_buffer, CanIn_Ccp_CRO, CanIn_Ccp_CRO_size);
    // TODO: required mutex unlock since this is called asynchronously with respect to CcpTask

    // Set response message to zero
    memset(CanOut_Ccp_DTO, 0x00, CanOut_Ccp_DTO_size);

    // Signal message reception
    event = EVENT_RECEIVED_MESSAGE;
}

// Asyncronously called by Spi Driver whenever a DSP response is ready
extern void rxCallback_DSP_response_ready(void)
{
    // Signal message reception
    event = EVENT_DSP_PENDING_RESPONSE;
}

// Taskable (piu prio di kw2000 ma meno del resto dell'applicativo
extern void CcpTask(void)
{
    if (event == EVENT_RECEIVED_MESSAGE)
    {
        // TODO: required mutex lock since this is called asynchronously with respect to rxCallback_Ccp_CRO
        memcpy(ccp_tmp_received_buffer, tmp_receive_buffer, CanIn_Ccp_CRO_size);
        // TODO: required mutex unlock since this is called asynchronously with respect to rxCallback_Ccp_CRO

        // Store raw incoming message to a DTO instance
        Cro_Get_Message();

        // Reset response message to "NOT OK"
        result = CCP_RESP_NOT_OK;

        // Decode incoming ccp command id
        switch (Current_CRO.Cmd) {

            case CCP_CONNECT :
                CMD_IMPLEMENTATION(CCP_CONNECT);
                break;

            case CCP_EXCHANGE_ID :
                CMD_IMPLEMENTATION(CCP_EXCHANGE_ID);
                break;


            case CCP_GET_SEED :
                CMD_IMPLEMENTATION(CCP_GET_SEED);
                break;

            case CCP_UNLOCK :
                CMD_IMPLEMENTATION(CCP_UNLOCK);
                break;

            case CCP_SET_MTA :
                CMD_IMPLEMENTATION(CCP_SET_MTA);
                break;

            case CCP_DNLOAD :
                CMD_IMPLEMENTATION(CCP_DNLOAD);
                break;

            case CCP_DNLOAD_6 :
                CMD_IMPLEMENTATION(CCP_DNLOAD_6);
                break;

            case CCP_UPLOAD :
                CMD_IMPLEMENTATION(CCP_UPLOAD);
                break;

            case CCP_SHORT_UPLOAD :
                CMD_IMPLEMENTATION(CCP_SHORT_UPLOAD);
                break;

            case CCP_SELECT_CAL_PAGE :
                CMD_IMPLEMENTATION(CCP_SELECT_CAL_PAGE);
                break;

            case CCP_GET_DAQ_SIZE :
                CMD_IMPLEMENTATION(CCP_GET_DAQ_SIZE);
                break;

            case CCP_SET_DAQ_PTR :
                CMD_IMPLEMENTATION(CCP_SET_DAQ_PTR);
                break;

            case CCP_WRITE_DAQ :
                CMD_IMPLEMENTATION(CCP_WRITE_DAQ);
                break;

            case CCP_START_STOP :
                CMD_IMPLEMENTATION(CCP_START_STOP);
                break;

            case CCP_DISCONNECT :
                CMD_IMPLEMENTATION(CCP_DISCONNECT);
                break;

            case CCP_SET_S_STATUS :
                CMD_IMPLEMENTATION(CCP_SET_S_STATUS);
                break;

            case CCP_GET_S_STATUS :
                CMD_IMPLEMENTATION(CCP_GET_S_STATUS);
                break;

            case CCP_START_STOP_ALL :
                CMD_IMPLEMENTATION(CCP_START_STOP_ALL);
                break;

            case CCP_BUILD_CHECKSUM :
                CMD_IMPLEMENTATION(CCP_BUILD_CHECKSUM);
                break;

            case CCP_MOVE :
                CMD_IMPLEMENTATION(CCP_MOVE);
                break;

            case CCP_TEST :
                CMD_IMPLEMENTATION(CCP_TEST);
                break;

            default :
                // Empty default statement
                break;
        }

        // Manage CCP response according with the previous switch statement result
        if (result == CCP_RESP_OK)
        {
            // Buildup "Command Return Message" with No errors
            CanOut_Ccp_DTO[0] = Command_Return_Message;
            CanOut_Ccp_DTO[1] = CCP_ACK;
            CanOut_Ccp_DTO[2] = Current_CRO.Ctr;
            // remaining bytes are "don't care"

            // transmit response
            TransmitDTO();
        }
        else if (result == CCP_NO_RESPONSE) {
            // No response required
        }
        else {
            // The remaining cases are ALL Errors
            CanOut_Ccp_DTO[0] = Command_Return_Message;
            CanOut_Ccp_DTO[1] = result;
            CanOut_Ccp_DTO[2] = Current_CRO.Ctr;
            // remaining bytes are "don't care"

            // transmit response
            TransmitDTO();
        }

        // Reset last DTO/CRO command
        memset(CanOut_Ccp_DTO, 0x0U, sizeof(CanOut_Ccp_DTO));
        memset(&Current_CRO, 0x0U, sizeof(Current_CRO));

        event = EVENT_NO_EVENT;     // Consume the event
    }

    // Manage DSP response (if they exist) or go further...
    if (event == EVENT_DSP_PENDING_RESPONSE) {
        if (DSP_response == CCP_DNLOAD) {
            /* Build up response for this command */

            // Notice that this command uses "DSP_size" variable initially populated by previous DNLOAD
        }
        else if (DSP_response == CCP_DNLOAD_6) {
            /* Build up response for this command */

            // Notice that this is the only command not needing "size" value
        }
        else if (DSP_response == CCP_UPLOAD) {
            /* Build up response for this command */

            // Notice that this command uses "DSP_size" variable initially populated by previous UPLOAD
        }
        else if (DSP_response == CCP_SHORT_UPLOAD) {
            /* Build up response for this command */

            // Notice that this command uses "DSP_size" variable initially populated by previous SHORT_UPLOAD
        }
        else {
            /* Error, this response type from DSP is not allowed */
        }

        // transmit response
        TransmitDTO();

        // Reset last DTO/CRO command
        memset(CanOut_Ccp_DTO, 0x0U, sizeof(CanOut_Ccp_DTO));
        memset(&Current_CRO, 0x0U, sizeof(Current_CRO));

        event = EVENT_NO_EVENT;     // Consume the event
    }
}

static void Ccp_SampleDaqList(uint8 i, uint8 j, uint32 counter)
{
    uint8 k;
    uint8 offset = 0U;

    uint8* source_addr = NULL;
    uint8* destination_addr = NULL;
    uint32 data_size = 0U;

    if (DaqList[i].prescaler != 0 && ((counter) % (Ccp_EventChannels[DaqList[i].eventChannel-1] / DaqList[i].prescaler)) == 0U) {

        for (k=0; k<7; k++) {   // For each element of the current ODT... (up to 7 for each ODT)

            // This addr represents the place from where data will be sampled
            source_addr = DaqList[i].odts[j].ODT[k].ptr;

            // This is the place (in DaqList structure) where data will be stored
            destination_addr = &DaqList[i].odts[j].data[offset];

            // This is the amount of data (in bytes) involved in this operation
            data_size = DaqList[i].odts[j].ODT[k].size;

            // Check if the k-th element of the j-th ODT has data to be transmitted and if pointers are valid (do not rely on these pointers since they come from external CCP tools (through CAN bus)
            if ( data_size != 0 && source_addr != NULL && destination_addr != NULL &&
                offset < 7) { // Check if offset is less then 7 (this check should be redundant, because this condition should be guaranteed by the Master Station Toll)

                // DAQ sampling...
                memcpy(destination_addr, source_addr, data_size);
            }

            // Compute next position in DAQ-ODT message
            offset = offset + data_size;

            // set this ODT as ready to be delivered
            DaqList[i].odts[j].transmitThisOdt = TRUE;
        }
    }
}

static void Ccp_SendDaqList(uint8 i, uint8 j, uint32 counter)
{
    uint8 k;

    // Build up the PID of the current ODT
    CanOut_Ccp_DTO[0] = (i * CCP_MAX_ODT) + j;

    if (DaqList[i].prescaler != 0 && (counter % (Ccp_EventChannels[DaqList[i].eventChannel-1] / DaqList[i].prescaler)) == 0U) {

        if (DaqList[i].odts[j].transmitThisOdt == TRUE) {

            // Build up data field of the response message
            memcpy(&CanOut_Ccp_DTO[1], DaqList[i].odts[j].data, sizeof(DaqList[i].odts[j].data));

            TransmitDTO();

            memset(CanOut_Ccp_DTO, 0x0U, sizeof(CanOut_Ccp_DTO));

            DaqList[i].odts[j].transmitThisOdt = FALSE;
        }
    }
}

// This task is in charge of managing periodic messages
TASK(Task_Ccp_PeriodicTx)
{
    uint32 i;
    uint32 j;
    uint32 k;
    uint8 offset = 0U;
    static uint32 counter = 0U;
    StdReturnType returnCode = STD_NOT_OK;

    // Managing periodic DAQ sampling
    for (i=0; i<CCP_MAX_DAQ; i++) { // For each DAQ list...

        if (DaqList[i].flags == DAQ_FLAG_START) { // ... if it is scheduled to be sent

            // DaqList sampling
            for (j=0; j<DaqList[i].last+1; j++) {   // This loop goes up to the last ODT that has to be sampled for this DAQ list

                // i-th DaqList
                // j-th ODT
                // counter is the time reference
                Ccp_SampleDaqList(i, j, counter);   // sample can be synchronous (all ODTs can be sampled synchronously)

                // j is used as a gap (counter - j) between two syncronous DAQ-ODTs (it is a 1 msec phase between two consecutive DAQ_ODTs)
                // it is phase shifted (counter - j) to prevent from sending CAN messages at the same time, HW can't do this
                Ccp_SendDaqList(i, j, counter - j);

            }   // for (j=0; j<DaqList[i].last+1; j++)

        } // if (DaqList[i].flags == DAQ_FLAG_START)

    } // for (i=0; i<CCP_MAX_DAQ; i++)

    // Increment counter
	counter++;

    TerminateTask();
}

