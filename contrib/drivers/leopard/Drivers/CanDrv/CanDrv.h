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

#ifndef EE_MCU_MPC5643L_CAN_H
#define EE_MCU_MPC5643L_CAN_H

#include <cpu/common/inc/ee_stdint.h>
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>

#include "CanCfg.h"

#define CANDRV_125KBPS     (125U)  ///< 125 Kbps
#define CANDRV_250KBPS     (250U)  ///< 250 Kbps
#define CANDRV_500KBPS     (500U)  ///< 500 Kbps
#define CANDRV_1MBPS       (1000U) ///< 1 Mbps

#define CANDRV_THREE_SAMPLE   (0x0U)  ///< 3 samples acquisition mode
#define CANDRV_SINGLE_SAMPLE  (0x1U)  ///< 1 samples acquisition mode

#define CANDRV_INTERRUPT_MODE           ///< Enable CanDrv.c to work using the 'interrupt mode'. \n If defined it's possible to switch at runtime from 'interrupt mode' to 'polling mode' and vice-versa. \n If not defined, only the 'polling mode' is available, and the application must poll CanDrv.c in order to detect CAN bus events. 

// #define CANDRV_EXTENDED_IDENTIFIERS      ///< Enable extended CAN identifiers (29 bits). If not defined, CanDrv.c uses standard identifiers (11 bits).

#define CANDRV_ENABLED      (0x1U)          ///< Enable FlexCan capability
#define CANDRV_DISABLED     (0x0U)          ///< Disable FlexCan capability
#define CANDRV_DO_NOT_CARE  CANDRV_DISABLED ///< Used for irrelevat value

#define CANDRV_NUMBER_OF_CHANNELS   (2U)    ///< This MCU has two FlexCan Modules

#define CANDRV_NORMAL       (0U)        ///< Normal mode
#define CANDRV_LOOPBACK     (1U)        ///< Loopback mode
#define CANDRV_OPENDRAIN    (2U)        ///< Opendrain mode

/* FlexCAN module register's bit masks */
#define CAN_MCR_MDIS        0x80000000  ///< MDIS bit
#define CAN_MCR_FRZ         0x40000000  ///< FRZ bit
#define CAN_MCR_FEN         0x20000000  ///< FEN bit
#define CAN_MCR_HALT        0x10000000  ///< HALT bit
#define CAN_MCR_NOTRDY      0x08000000  ///< NOTRDY bit
#define CAN_MCR_SOFTRST     0x02000000  ///< SOFTRST bit
#define CAN_MCR_FRZACK      0x01000000  ///< FRZACK bit
#define CAN_MCR_WRNEN       0x00200000  ///< WRNEN bit
#define CAN_MCR_LPMACK      0x00100000  ///< LPMACK bit
#define CAN_MCR_SRXDIS      0x00020000  ///< SRXDIS bit
#define CAN_MCR_BCC         0x00010000  ///< BCC bit
#define CAN_MCR_LPRIOEN     0x00002000  ///< LPRIOEN bit
#define CAN_MCR_AEN         0x00001000  ///< AEN bit

#define BUFF_OFFSET_0_3     (0U)    ///< Offset of the 0-3 set of FlexCan buffer
#define BUFF_OFFSET_4_7     (4U)    ///< Offset of the 4-7 set of FlexCan buffer
#define BUFF_OFFSET_8_11    (8U)    ///< Offset of the 8-11 set of FlexCan buffer
#define BUFF_OFFSET_12_15   (12U)   ///< Offset of the 12-15 set of FlexCan buffer
#define BUFF_OFFSET_16_31   (16U)   ///< Offset of the 16-31 set of FlexCan buffer

#define BUFF_MASK_0_3       (0xFU<<BUFF_OFFSET_0_3)       ///< Mask of the 0-3 set of FlexCan buffer
#define BUFF_MASK_4_7       (0xFU<<BUFF_OFFSET_4_7)       ///< Mask of the 4-7 set of FlexCan buffer
#define BUFF_MASK_8_11      (0xFU<<BUFF_OFFSET_8_11)      ///< Mask of the 8-11 set of FlexCan buffer
#define BUFF_MASK_12_15     (0xFU<<BUFF_OFFSET_12_15)     ///< Mask of the 12-15 set of FlexCan buffer
#define BUFF_MASK_16_31     (0xFFFFU<<BUFF_OFFSET_16_31)  ///< Mask of the 16-31 set of FlexCan buffer

typedef enum {
    CHANNEL_FLEXCAN_A = 0,
    CHANNEL_FLEXCAN_B = 1
} CanChannelType;

#define TX_BUFFER_OFFSET    (0U)                   ///< TX FlexCan buffer offset
#define RX_BUFFER_OFFSET    (TX_BUFFER_OFFSET+NR_OF_CAN_TX_MESSAGES)    ///< RX FlexCan buffer offset
#define BUFFER_BORDERLINE   (TX_BUFFER_OFFSET+NR_OF_CAN_TX_MESSAGES-1)  ///< Borderline indicating the maximum TX buffers index and the start of RX buffer indexes
#define MAX_BUFF_INDEX_MASK (0x80000000)  ///< Mask indicating the last buffer index

#define FLEXCAN_A_MSG_BUFFER_BASE	(0xFFFC0000U)   ///< FlexcanA msg buffer base address
#define FLEXCAN_B_MSG_BUFFER_BASE	(0xFFFC4000U)   ///< FlexcanB msg buffer base address
#define MESSAGE_BUFFER_BASE_OFFSET	(0x80U)

#define FLEXCAN_A_MSG_BUFF_BASE(x) (volatile uint8 *)(FLEXCAN_A_MSG_BUFFER_BASE + MESSAGE_BUFFER_BASE_OFFSET+(0x10*(x))+0x8)  ///< Macro useful to compute x-th FlexCan A buffer base address

#define FLEXCAN_B_MSG_BUFF_BASE(x) (volatile uint8 *)(FLEXCAN_B_MSG_BUFFER_BASE + MESSAGE_BUFFER_BASE_OFFSET+(0x10*(x))+0x8)  ///< Macro useful to compute x-th FlexCan B buffer base address

typedef uint8 MessageBufferIndex;   ///< FlexCan message buffer index. Range [0..31].

/// CAN Buffer status macros
#define BUFFER_AVAILABLE        0U      ///< Buffer-available flag
#define BUFFER_NOT_AVAILABLE    1U      ///< Buffer-not-available flag

#define ISR_MODE            (0x0U)  ///< Isr mode
#define POLLING_MODE        (0x1U)  ///< Polling mode

/* Transmission Buffer Codes */

#define TX_UNCOND_ONCE      0x0000000CU ///<    CODE=0xC: Transmit data frame unconditionally once. After transmission, the MB automatically returns to the INACTIVE state.
#define TX_INACTIVE         0x00000008U ///<    Tx MB does not participate in the arbitration process
#define TX_ABORT            0x00000009U ///<    Tx msg abort

/* Reception Buffer Codes */
#define RX_INACTIVE         0x00000000U ///<    Rx inactive
#define RX_ACTIVE_EMPTY     0x00000004U ///<    Rx active and empty
#define RX_FULL             0x00000002U ///<    Rx Message Buffer is FULL
#define RX_OVERRUN          0x00000006U ///<    Rx Message Overun

extern void CanDrvInit(void);
extern StdReturnType CanTransmit(CanTxMsgIndexType msgIndex);
extern StdReturnType CanPollMessage(CanRxMsgIndexType msgIndex);
extern void CanDrvEnableInterrupts(void);
extern void CanDrvDisableInterrupts(void);
extern void CanDrvPolling(void);
extern boolean SetCanDrvFreezeFrame(uint8 rxTx, CanRxMsgIndexType msgIndex, boolean enabled);
extern StdReturnType CanDrvCheckBusOff(CanChannelType canChannel);

extern void Ch0_busOff_callback(void);
extern void Ch1_busOff_callback(void);

static inline uint32 suspend_CAN0_IRQ(void)
{
	uint32 old_mask = FLEXCAN_A.IMASK1.R;	// get old value
	FLEXCAN_A.IMASK1.R = 0;					// disable ALL CAN Isr Buffer sources
	return old_mask;						// return old value
}

static inline void resume_CAN0_IRQ(uint32 old_mask)
{
	FLEXCAN_A.IMASK1.R = old_mask;  // resume old condition
}

static inline uint32 suspend_CAN1_IRQ(void)
{
	uint32 old_mask = FLEXCAN_B.IMASK1.R;	// get old value
	FLEXCAN_B.IMASK1.R = 0;					// disable ALL CAN Isr Buffer sources
	return old_mask;						// return old value
}

static inline void resume_CAN1_IRQ(uint32 old_mask)
{
	FLEXCAN_B.IMASK1.R = old_mask;  // resume old condition
}

#endif
