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

#ifndef _CCP_H_
#define _CCP_H_

#include "BswCommon.h"
#include "CanCfg.h"

// This Driver support s CCP 2.1
#define CCP_MAIN_PROTOCOL_VERSION   0x2
#define CCP_RELEASE_WITHIN_VERSION  0x1

// SRAM boundaries
#if defined(LOCK_STEP)
// 128 Kbytes SRAM in LOCKSTEP
#define CCP_SRAM_UPPER_BOUND_ADDR  (0x4001FFFF)
#define CCP_SRAM_LOWER_BOUND_ADDR  (0x40000000)
#else
// 64 Kbytes SRAM in DPM
#define CCP_SRAM_UPPER_BOUND_ADDR  (0x4000FFFF)
#define CCP_SRAM_LOWER_BOUND_ADDR  (0x40000000)
#endif

// ROM boundaries
#define OFFSET_LOW_BLOCK0               0x00000000U ///< Offset of low block 0
#define OFFSET_HIGH_BLOCK1              0x000C0000U ///< Offset of high block 1
#define HIGH_BLOCK1_SIZE                0x40000U    ///< 256KB block size
///< Flash lower bound
#define FLASH_MEMORY_LOWER_BOUND    (OFFSET_LOW_BLOCK0)
///< Flash upper bound
#define FLASH_MEMORY_UPPER_BOUND    (OFFSET_HIGH_BLOCK1 + HIGH_BLOCK1_SIZE)
#define CCP_FLASH_UPPER_BOUND_ADDR  FLASH_MEMORY_UPPER_BOUND
#define CCP_FLASH_LOWER_BOUND_ADDR  FLASH_MEMORY_LOWER_BOUND

// CCP Protocol command codes (CRO)
#define CCP_CONNECT             0x01
#define CCP_EXCHANGE_ID         0x17
#define CCP_GET_SEED            0x12
#define CCP_UNLOCK              0x13
#define CCP_SET_MTA             0x02
#define CCP_DNLOAD              0x03
#define CCP_DNLOAD_6            0x23
#define CCP_UPLOAD              0x04
#define CCP_SHORT_UPLOAD        0x0F
#define CCP_SELECT_CAL_PAGE     0x11
#define CCP_GET_DAQ_SIZE        0x14
#define CCP_SET_DAQ_PTR         0x15
#define CCP_WRITE_DAQ           0x16
#define CCP_START_STOP          0x06
#define CCP_DISCONNECT          0x07
#define CCP_SET_S_STATUS        0x0C
#define CCP_GET_S_STATUS        0x0D
#define CCP_START_STOP_ALL      0x08
#define CCP_BUILD_CHECKSUM      0x0E
#define CCP_MOVE                0x19
#define CCP_TEST                0x05

// CCP Protocol error codes
#define CCP_ACK                 0x00
#define CCP_DAQ_PROC_OVERLD     0x01
#define CCP_CMD_PROC_BUSY       0x10
#define CCP_DAQ_PROC_BUSY       0x11
#define CCP_INTERNAL_TOUT       0x12
#define CCP_KEY_REQ             0x18
#define CCP_SESSION_STATUS_REQ  0x19
#define CCP_COLD_START_REQ      0x20
#define CCP_COLD_DATA_INIT_REQ  0x21
#define CCP_DAQ_LIST_INIT_REQ   0x22
#define CCP_CODE_UPDATE_REQ     0x23
#define CCP_UNKNOW_CMD          0x30
#define CCP_CMD_SYNTAX          0x31
#define CCP_PARAMS_OUT_OF_RANGE 0x32
#define CCP_ACCESS_DENIED       0x33
#define CCP_OVERLOAD            0x34
#define CCP_ACCESS_LOCKED       0x35
#define CCP_RESORFUNC_UNAVAIL   0x36

// Used by Resource Availability Mask / Resource protection Status Mask
#define CCP_MASK_CAL                 0x01U   // CAL bit0
#define CCP_MASK_DAQ                 0x02U   // DAQ bit1
#define CCP_MASK_PGM                 0x40U   // PGM bit6

// Tester station address
#define CCP_TESTER_STATION_ADDR     0x39U

// Macro to set a resource as available/unavailable
#define CCP_SET_RES_AVAILABLE(res)     (res)
#define CCP_SET_RES_UNAVAILABLE(res)   (res & (~res))

// MAcro to set a resource as protected/unprotected
#define CCP_SET_RES_PROTECTED(res)     CCP_SET_RES_AVAILABLE(res)
#define CCP_SET_RES_UNPROTECTED(res)   CCP_SET_RES_UNAVAILABLE(res)

// This is the chjecksum size provided by BUILD_CHECKSUM request
#define CCP_CHECKSUM_SIZE       0x4U

// Maximum number of ODTs per DAQ list
#define CCP_MAX_ODT 25

// Maximum number of DAQ lists
#define CCP_MAX_DAQ 6

// Maximum number of Event Channels
#define CCP_EVENT_CH_NUM 3

/* Event Channel declaration */
#define EVENT_CHANNEL_1  1U // 100 msec task (periodic event)
#define EVENT_CHANNEL_2  2U // 10 msec task (periodic event)
#define EVENT_CHANNEL_3  3U // 5 msec task channel (periodic event)
#define EVENT_CHANNEL_4  4U // Event
#define EVENT_CHANNEL_5  5U // Event
#define EVENT_CHANNEL_6  6U // Event

// Temnporary/end connection in DISCONNECT command
#define CCP_DISCONNECT_TEMP         0x0U
#define CCP_DISCONNECT_END_SESSION  0x1U

// Denotes two available MTAs
typedef enum {
    IS_MTA0,
    IS_MTA1
} ccp_MtaX;

// Swap MTA (affects byte from 2 to 5) of a given CRO
#define CCP_COMPUTE_MTA(x) (x.CmdParams[2]<<24 | x.CmdParams[3]<<16 | \
            x.CmdParams[4]<<8 | x.CmdParams[5])

// Swap DAQ element address (affects byte from 4 to 7) of a given CRO
#define CCP_COMPUTE_DAQ_ADDR(x) CCP_COMPUTE_MTA(x)

// Swap short upload address
#define CCP_COMPUTE_SHORT_UPLOAD_ADDR(x) CCP_COMPUTE_MTA(x)

// Macro used to manipulate incoming address from 'address extended' to 'physical address'
#define CCP_COMPUTE_PHYSICAL_ADDR(x)    (x & (~0x0F000000))
#define CCP_COMPUTE_ADDR_SPACE_ID(x)    ((x & 0x0F000000) >> 24)

static uint8 Ccp_Current_Status = 0x00U;

// CRO:
// Type: Rx only
// Size: 8 bytes message field
// Purpose: Reception of commands in the slave device
typedef struct {
    uint8 Cmd;          // command code = CMD
    uint8 Ctr;          // command counter = CTR
    uint8 CmdParams[6]; // command related parameter and data area
} Ccp_Cro;

// DTOs: Command Return or Event Messages, and Data Acquisiton Messages
// Type: Tx (and Remote Tx Request reception)
// Size: 8 bytes message field
// Purpose: Command Return Message CRM or
//          Event Message or
//          Data Acquisition Message

// Command Return or Event Messages
typedef struct {
    uint8 Pid;          // data packet ID = PID
    uint8 Err;          // Command Return- / Error Code.
    uint8 Ctr;          // Command Counter as received in CRO with the last command
    uint8 ParamsData[5];// command related parameter and data area
} Ccp_Dto;

// Data Acquisiton Messages
typedef struct {
    uint8 Pid;          // data packet ID = PID
    uint8 ParamsData[7];// Data filed (DAQ values)
} Ccp_Dto_Daq;

// Command response PID
typedef enum {
    // 0 ≤ n ≤ 0xFD DTO contains a Data Acquisiton Message corresponding to ODT n 
    Event_Message = 0xFE,
    Command_Return_Message // 0xFF
} Dto_Pid;

// Single ODT element
typedef struct {
    uint8* ptr;
    uint32 size;
} Ccp_OdtObj;

// Single ODT (each ODT can have at most 7 elements)
typedef struct {
    Ccp_OdtObj ODT[7];
    uint8 data[7];
    uint8 transmitThisOdt;
} Ccp_ODT_List;

/* DAQ list */
#define DAQ_FLAG_START      0x01U
#define DAQ_FLAG_STOP       0x02U
#define DAQ_FLAG_PREPARE    0x04U
#define DAQ_FLAG_OVERRUN    0x08U
#define DAQ_FLAG_CLEAR      0x10U

typedef struct {
    Ccp_ODT_List odts[CCP_MAX_ODT];
    uint16  prescaler;
    uint16  cycle;
    uint8   eventChannel;
    uint8   last;
    uint8   flags;
} Ccp_DaqList;

typedef enum {
    STOP,
    START,
    PREPARE
} Ccp_StartStopCases;

// Maximum number of external DSP veriables
#define CCP_DSP_VARIABLES_NUM   (0xCU)

// Definitions of 'address space id'
#define PPC (0)
#define DSP (1)

// Valued used in dspMirror table management
typedef enum {
    CCP_DSP_MIRROR_FULL = CCP_DSP_VARIABLES_NUM,    ///< This enum start from this value to not interfere with return value of Ccp_InsertDspElement() and Ccp_RemoveDspElement()
    CCP_DSP_ELEMENT_NOT_FOUND
} Ccp_DspMirrorInfo;

// Used to handle external memory areas (e.g.: DSP, etc)
typedef struct {
    uint8   used;
    uint32  remoteAddr;
    uint32  value;
} Ccp_DspMirrorType;

extern char CanIn_Ccp_CRO[];
extern char CanOut_Ccp_DTO[];

void rxCallback_Ccp_CRO(CanRxMsgIndexType msgIndex);
void rxCallback_DSP_response_ready(void);
void CcpTask(void);

#endif      // _CCP_H_

