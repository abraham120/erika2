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

#include <string.h>
#include <ee.h>
#include "BswCommon.h"
#include "CanDrv.h"
#include "CanCom.h"
#include "CanCfg.h"
#include "Error.h"
#include "CanCfg.h"
#include "State.h"

#define MODULE_ID   (10)

/* Function declarations */
void ManageCanIsr(uint8 isrSourceIndex, uint32 bufferFlags, CanChannelType canChannel);

/// State of a RX message.
/// Used to define the array canRxMsgState[].
typedef struct
{
    boolean freezeFrameEnabled:1;       ///< If freezeFrameEnabled==TRUE, the message is saved in the freeze frame buffer.
} CanRxMsgStateType;

/// State of a TX message.
/// Used to define the array canTxMsgState[].
typedef struct
{
    boolean freezeFrameEnabled:1;       ///< If freezeFrameEnabled==TRUE, the message is saved in the freeze frame buffer.
} CanTxMsgStateType;

/// FlexCan Module configuration
typedef struct
{
    boolean peripheralEn;
    uint8   mode;
    boolean autobusonEn;
    uint16  peripheralFreq;
    boolean errorHandlingEn;
    boolean sampleNumMode;
} FlexCanConfType;

// Internal state of the component
static InitializationStateType initializationState = COMPONENT_STATE_NOT_INIZIALIZED;
static CanRxMsgStateType canRxMsgState[NR_OF_CAN_RX_MESSAGES];
static CanTxMsgStateType canTxMsgState[NR_OF_CAN_TX_MESSAGES];

/* Configurations of FlexCan_A and FlexCan B */
static const FlexCanConfType flexCanMcuConf[CANDRV_NUMBER_OF_CHANNELS] = {
    //                      Peripheral          Mode                        AutoBuson               FlexCan             Error                   Number
    //                      enabled/disabled    normal/loopback/opendrain   enabled/disabled        frequency           handling                of samples
    /* FlexCan_A */     {   CANDRV_ENABLED,     CANDRV_NORMAL,              CANDRV_ENABLED,         CANDRV_500KBPS,     CANDRV_ENABLED,         CANDRV_THREE_SAMPLE},
    //                      Peripheral          Open Drain                  AutoBuson               FlexCan             Error                   Number
    //                      enabled/disabled    enabled/disabled            enabled/disabled        frequency           handling                of samples
    /* FlexCan_B */     {   CANDRV_DISABLED,    CANDRV_DO_NOT_CARE,         CANDRV_DO_NOT_CARE,     CANDRV_DO_NOT_CARE, CANDRV_DO_NOT_CARE,     CANDRV_DO_NOT_CARE}
};

/* Initial driver mode */
#ifdef CANDRV_INTERRUPT_MODE
static uint8 canDriverMode = ISR_MODE;
#else
static uint8 canDriverMode = POLLING_MODE;
#endif

/// Initialize FlexCan channel A
static void InitFlexCAN_A(void)
{
	uint32_t i = 0;

	/* enable the FlexCAN module, reset and freeze */
	FLEXCAN_A.MCR.R = (0
		            | CAN_MCR_FRZ  /* enabled to enter Freeze mode */ 
		            | CAN_MCR_HALT /* enter freeze mode if FRZ bit is set */
		            | CAN_MCR_SOFTRST); /* soft reset */

	/* wait until soft reset completes */
	while(1 == FLEXCAN_A.MCR.B.SOFT_RST)
        ;

	/* double check that we are actually in freeze mode */
	while(0 == FLEXCAN_A.MCR.B.FRZ_ACK) 
        ;

	while(0 == FLEXCAN_A.MCR.B.NOT_RDY)
        ;

	FLEXCAN_A.MCR.R = (0
		            | CAN_MCR_FRZ  /* enabled to enter Freeze mode */ 
		            | CAN_MCR_HALT /* enter freeze mode if FRZ bit is set */
		            /*| CAN_MCR_SRXDIS */ /* self reception enabled */
		            | CAN_MCR_BCC  /* individual Rx masking and queue */
		            | CAN_MCR_AEN  /* Safe Tx abort enable */
		            | 0x0000001F); /* enable 32 MBs */

    /* Self Reception Disabled: 1 = Disabled, 0 = Enabled */
    if (flexCanMcuConf[CHANNEL_FLEXCAN_A].mode == CANDRV_LOOPBACK) {
        /*
         * Requirement:
         * self-reception must be disabled,
         * except for loopback mode (of course).
         */
        FLEXCAN_A.MCR.B.SRX_DIS = 0x0;
    }
    else {
        FLEXCAN_A.MCR.B.SRX_DIS = 0x1;
    }

	/* configure CAN0TX and CAN0RX pin functions */
    if (flexCanMcuConf[CHANNEL_FLEXCAN_A].mode == CANDRV_OPENDRAIN) {
	    SIU.PCR[16].R = 0x624;  /*CAN_A TX open drain*/
    }
    else {
        SIU.PCR[16].R = 0x604;
    }

	SIU.PCR[17].R = 0x104;  /*CAN_A RX*/
	SIU.PSMI[33].B.PADSEL = 0x1;  /*CAN_A RX*/
	     
	/* FlexCan working frequency setup */
	if (flexCanMcuConf[CHANNEL_FLEXCAN_A].peripheralFreq == CANDRV_1MBPS) {
	    /* Configure for OSC (40 MHz), 1.0 MHz bit time */          
	    FLEXCAN_A.CTRL.R = 0x01ED0046;
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_A].peripheralFreq == CANDRV_500KBPS) {
	    /* Configure for OSC (40 MHz), 500 Kbps */
	    FLEXCAN_A.CTRL.R = 0x03ED0046;
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_A].peripheralFreq == CANDRV_250KBPS) {
        /* 40 MHz OSC, 250 kbps */
        FLEXCAN_A.CTRL.R = 0x07ED0046;
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_A].peripheralFreq == CANDRV_125KBPS) {
        /* 40 MHz OSC, 125 kbps */
        FLEXCAN_A.CTRL.R = 0x0FED0046;
    }
#ifdef DEVELOPMENT
    // If DEVELOPMENT is defined (i.e. during system development), then every function provides stronger checks (see 'Extended error detection')
    else {
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);      /* FlexCan working frequency not still supported */
    }
#endif

    if (flexCanMcuConf[CHANNEL_FLEXCAN_A].mode == CANDRV_LOOPBACK) {
	    FLEXCAN_A.CTRL.B.LPB = 0x1;  /* Loopback mode - LPB bit set */
    }

    if (flexCanMcuConf[CHANNEL_FLEXCAN_A].errorHandlingEn == CANDRV_ENABLED) {
        FLEXCAN_A.CTRL.B.ERR_MSK = 0x1;  /* Enable isr error */
    }

    if (flexCanMcuConf[CHANNEL_FLEXCAN_A].autobusonEn == CANDRV_ENABLED) {
        /* Bus off autorecovery enabled */
	    FLEXCAN_A.CTRL.B.BOFF_REC = 0x0;
    }

    /* Enable interrupt in case of Bus off
     * and manage the scenario through the isr handler (if configured) */
	FLEXCAN_A.CTRL.B.BOFF_MSK = 0x1;

    /* Lowest Buffer Transmitted First */
	FLEXCAN_A.CTRL.B.LBUF = 0x1;

    /* Three samples are used to determine the value of the received bit if required */
    if (flexCanMcuConf[CHANNEL_FLEXCAN_A].sampleNumMode == CANDRV_THREE_SAMPLE) {
        FLEXCAN_A.CTRL.B.SMP = 0x1U;
    }

	/* Make first 32 message buffers inactive by writing their control fields
	* to "not active". They will be left
	* inactive until we're ready for communication. */      
	for(i=0;i<32;i++)
	{
		FLEXCAN_A.MB[i].CS.R = 0;
	}

	/* set mask registers - all ID bits must match */
	for(i=0;i<32;i++)
	{
		FLEXCAN_A.RXIMR[i].R = 0x1FFFFFFF;
	}
	    
	/* Finally clear the HALT flag in MCR to enable the FlexCAN
	* to synchronize with the CAN bus and allow
	* participation in communication. */
	FLEXCAN_A.MCR.B.HALT = 0;   /* Clear this flag to exit from Freeze mode  */

	/* wait until FlexCAN exits from freeze mode */
	while(1 == FLEXCAN_A.MCR.B.FRZ_ACK)
        ;

    /*
     * wait until FlexCAN is ready
     * ready means:
     * - normal mode
     * - loop-back mode
     * - listen-only mode
     */
	while(1 == FLEXCAN_A.MCR.B.NOT_RDY)
        ;
}

/// Initialize FlexCan channel B
static void InitFlexCAN_B(void)
{
	uint32_t i = 0;

	/* enable the FlexCAN module, reset and freeze */
	FLEXCAN_B.MCR.R = (0
		            | CAN_MCR_FRZ  /* enabled to enter Freeze mode */ 
		            | CAN_MCR_HALT /* enter freeze mode if FRZ bit is set */
		            | CAN_MCR_SOFTRST); /* soft reset */

	/* wait until soft reset completes */
	while(1 == FLEXCAN_B.MCR.B.SOFT_RST)
		;

	/* double check that we are actually in freeze mode */
	while(0 == FLEXCAN_B.MCR.B.FRZ_ACK)
		;

	while(0 == FLEXCAN_B.MCR.B.NOT_RDY)
		;

	FLEXCAN_B.MCR.R = (0
		            | CAN_MCR_FRZ  /* enabled to enter Freeze mode */ 
		            | CAN_MCR_HALT /* enter freeze mode if FRZ bit is set */
		            /*| CAN_MCR_SRXDIS */ /* self reception enabled */
		            | CAN_MCR_BCC  /* individual Rx masking and queue */
		            | CAN_MCR_AEN  /* Safe Tx abort enable */
		            | 0x0000001F); /* enable 32 MBs */ 

    /* Self Reception Disabled: 1 = Disabled, 0 = Enabled */
    if (flexCanMcuConf[CHANNEL_FLEXCAN_B].mode == CANDRV_LOOPBACK) {
        /*
         * Requirement:
         * self-reception must be disabled,
         * except for loopback mode (of course).
         */
        FLEXCAN_B.MCR.B.SRX_DIS = 0x0;
    }
    else {
        FLEXCAN_B.MCR.B.SRX_DIS = 0x1;
    }

	/* configure CAN0TX and CAN0RX pin functions */
    if (flexCanMcuConf[CHANNEL_FLEXCAN_B].mode == CANDRV_OPENDRAIN) {  
	    SIU.PCR[14].R = 0x624;  /*CAN_B TX open drain*/
    }
    else {
        SIU.PCR[14].R = 0x604;
    }

	SIU.PCR[15].R = 0x104;  /*CAN_B RX*/
	SIU.PSMI[34].B.PADSEL = 0x0;  /*CAN_B RX*/

	/* FlexCan working frequency setup */
	if (flexCanMcuConf[CHANNEL_FLEXCAN_B].peripheralFreq == CANDRV_1MBPS) {
	    /* Configure for OSC (40 MHz), 1.0 MHz bit time */          
	    FLEXCAN_B.CTRL.R = 0x01ED0046;
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_B].peripheralFreq == CANDRV_500KBPS) {
	    /* Configure for OSC (40 MHz), 500 Kbps */
	    FLEXCAN_B.CTRL.R = 0x03ED0046;
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_B].peripheralFreq == CANDRV_250KBPS) {
        /* 40 MHz OSC, 250 kbps */
        FLEXCAN_B.CTRL.R = 0x07ED0046;
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_B].peripheralFreq == CANDRV_125KBPS) {
        /* 40 MHz OSC, 125 kbps */
        FLEXCAN_B.CTRL.R = 0x0FED0046;
    }
    else {
        /* FlexCan working frequency not still supported */
    }

    if (flexCanMcuConf[CHANNEL_FLEXCAN_B].mode == CANDRV_LOOPBACK) {
	    FLEXCAN_B.CTRL.B.LPB = 0x1;  /* Loopback mode - LPB bit set */
    }

    if (flexCanMcuConf[CHANNEL_FLEXCAN_B].errorHandlingEn == CANDRV_ENABLED) {
        FLEXCAN_B.CTRL.B.ERR_MSK = 0x1;  /* Enable isr error */
    }

    if (flexCanMcuConf[CHANNEL_FLEXCAN_B].autobusonEn == CANDRV_ENABLED) {
        /* Bus off autorecovery enabled */
	    FLEXCAN_B.CTRL.B.BOFF_REC = 0x0;
    }

    /* Enable interrupt in case of Bus off
     * and manage the scenario through the isr handler (if configured) */
	FLEXCAN_B.CTRL.B.BOFF_MSK = 0x1;

    /* Lowest Buffer Transmitted First */
	FLEXCAN_B.CTRL.B.LBUF = 0x1;

    /* Three samples are used to determine the value of the received bit if required */
    if (flexCanMcuConf[CHANNEL_FLEXCAN_B].sampleNumMode == CANDRV_THREE_SAMPLE) {
        FLEXCAN_B.CTRL.B.SMP = 0x1U;
    }

	/* Make first 32 message buffers inactive by writing their control fields
	* to "not active". They will be left
	* inactive until we're ready for communication. */      
	for(i=0;i<32;i++)
	{
		FLEXCAN_B.MB[i].CS.R = 0;
	}

	/* set mask registers - all ID bits must match */
	for(i=0;i<32;i++)
	{
		FLEXCAN_B.RXIMR[i].R = 0x1FFFFFFF;
	}

	/* Finally clear the HALT flag in MCR to enable the FlexCAN
	* to synchronize with the CAN bus and allow
	* participation in communication. */
	FLEXCAN_B.MCR.B.HALT = 0;   /* Clear this flag to exit from Freeze mode  */

	/* wait until FlexCAN exits from freeze mode */
	while(1 == FLEXCAN_B.MCR.B.FRZ_ACK)
        ;

    /*
     * wait until FlexCAN is ready
     * ready means:
     * - normal mode
     * - loop-back mode
     * - listen-only mode
     */
	while(1 == FLEXCAN_B.MCR.B.NOT_RDY)
        ;
}

/// Configure transmission message buffers.
static void SendConfig(void)
{
	CanChannelType canChannel = 0U;             // CAN channel identifier (it can be CHANNEL_FLEXCAN_A or CHANNEL_FLEXCAN_B).
    uint32 tmp = 0U;
	CanTxMsgIndexType msgIndex = 0U;            // Index of a tx message. Range [0..NR_OF_CAN_TX_MESSAGES-1].
    MessageBufferIndex bufferIndex = 0U;        // FlexCan message buffer index. Range [0..31].

	/* Variables used for data copy */
	sint8 *source = 0x0U;
    sint8 *destination = 0x0U;

	while (msgIndex<NR_OF_CAN_TX_MESSAGES)
	{
		canChannel = canTxMsgConfig[msgIndex].channel;

		bufferIndex = msgIndex + TX_BUFFER_OFFSET;

		if (canChannel == 0U) {
            //FLEXCAN_A.MB[bufferIndex].MSG_CS.R = 0x00400000;  /* SRR = 1 */
			FLEXCAN_A.MB[bufferIndex].MSG_CS.B.CODE = TX_INACTIVE;   /* Tx INACTIVE */

//FLEXCAN_A.MB[bufferIndex].MSG_CS.B.SRR = 0x1;  /* SRR = 1 */

			// copy msg ID to the CAN ID buffer field 
#ifdef CANDRV_EXTENDED_IDENTIFIERS
            /* EXT.ID */
			FLEXCAN_A.MB[bufferIndex].ID.R = canTxMsgConfig[msgIndex].id;
            /* EXT frame: 1 = Extended */
			FLEXCAN_A.MB[bufferIndex].MSG_CS.B.IDE = 0x1;
#else       // Standard identifiers
            /* STD frame: 0 = Standard */
			FLEXCAN_A.MB[bufferIndex].MSG_CS.B.IDE = 0x0;
            /* Std.ID */
			FLEXCAN_A.MB[bufferIndex].ID.R = canTxMsgConfig[msgIndex].id<<18;
#endif

			/* copy msg length to the CAN length buffer field */
			FLEXCAN_A.MB[bufferIndex].MSG_CS.B.LENGTH = canTxMsgConfig[msgIndex].length;

#ifdef CANDRV_INTERRUPT_MODE
            /*
             * If this CAN msg has a TX Callback configured,
             * hence enable the corresponding isr
             */
            if (canTxMsgConfig[msgIndex].txCallback != NULL) {
                tmp = FLEXCAN_A.IMASK1.R;
			    FLEXCAN_A.IMASK1.R = tmp | (0x1U<<bufferIndex);
            }
#endif
		}
		else {
			//FLEXCAN_B.MB[bufferIndex].MSG_CS.R = 0x00400000;  /* SRR = 1 */
			FLEXCAN_B.MB[bufferIndex].MSG_CS.B.CODE = TX_INACTIVE;   /* Tx INACTIVE */

			// copy msg ID to the CAN ID buffer field
#ifdef CANDRV_EXTENDED_IDENTIFIERS
            /* EXT.ID */
			FLEXCAN_B.MB[bufferIndex].ID.R = canTxMsgConfig[msgIndex].id;
            /* EXT frame: 1 = Extended */
			FLEXCAN_B.MB[bufferIndex].MSG_CS.B.IDE = 0x1;
#else       // Standard identifiers
            /* STD frame: 0 = Standard */
			FLEXCAN_B.MB[bufferIndex].MSG_CS.B.IDE = 0x0;
            /* Std.ID */
			FLEXCAN_B.MB[bufferIndex].ID.R = canTxMsgConfig[msgIndex].id<<18;
#endif

			/* copy msg length to the CAN length buffer field */
			FLEXCAN_B.MB[bufferIndex].MSG_CS.B.LENGTH = canTxMsgConfig[msgIndex].length;

#ifdef CANDRV_INTERRUPT_MODE
            /*
             * If this CAN msg has a TX Callback configured,
             * hence enable the corresponding isr
             */
            if (canTxMsgConfig[msgIndex].txCallback != NULL) {
                tmp = FLEXCAN_B.IMASK1.R;
			    FLEXCAN_B.IMASK1.R = tmp | (0x1U<<bufferIndex);
            }
#endif
		}

		msgIndex++;
	}
}

/// Configure reception message buffers.
static void ReceiveConfig(void)
{
	MessageBufferIndex bufferIndex = 0U;        // FlexCan message buffer index. Range [0..31].
    CanRxMsgIndexType msgIndex = 0U;            // Index of a rx message. Range [0..NR_OF_CAN_RX_MESSAGES-1].
    CanChannelType canChannel = 0U;             // CAN channel identifier (it can be CHANNEL_FLEXCAN_A or CHANNEL_FLEXCAN_B).
    uint32 tmp = 0U;

	while (msgIndex<NR_OF_CAN_RX_MESSAGES)
	{
		canChannel = canRxMsgConfig[msgIndex].channel;

        bufferIndex = msgIndex + RX_BUFFER_OFFSET;

		if (canChannel == 0U) {
            /* Rx inactive */
			FLEXCAN_A.MB[bufferIndex].CS.R = RX_INACTIVE;

#ifdef CANDRV_EXTENDED_IDENTIFIERS
            /* EXT.ID */
			FLEXCAN_A.MB[bufferIndex].ID.R = canRxMsgConfig[msgIndex].id;
            /* EXT frame: 1 = Extended */
			FLEXCAN_A.MB[bufferIndex].MSG_CS.B.IDE = 0x1;
#else       // Standard identifiers
            /* STD frame: 0 = Standard */
			FLEXCAN_A.MB[bufferIndex].MSG_CS.B.IDE = 0x0;
            /* Std.ID */
			FLEXCAN_A.MB[bufferIndex].ID.R = canRxMsgConfig[msgIndex].id<<18;
#endif

            /* Rx active and empty */
            FLEXCAN_A.MB[bufferIndex].MSG_CS.B.CODE = RX_ACTIVE_EMPTY;

#ifdef CANDRV_INTERRUPT_MODE
            /*
             * If this CAN msg has a RX Callback configured,
             * hence enable the corresponding isr
             */
            if (canRxMsgConfig[msgIndex].rxCallback != NULL) {
                tmp = FLEXCAN_A.IMASK1.R;
			    FLEXCAN_A.IMASK1.R = tmp | (0x1U<<bufferIndex);
            }
#endif
		}
		else {
            /* Rx inactive */
			FLEXCAN_B.MB[bufferIndex].CS.R = RX_INACTIVE;

#ifdef CANDRV_EXTENDED_IDENTIFIERS
            /* EXT.ID */
			FLEXCAN_B.MB[bufferIndex].ID.R = canRxMsgConfig[msgIndex].id;
            /* EXT frame: 1 = Extended */
			FLEXCAN_B.MB[bufferIndex].MSG_CS.B.IDE = 0x1;
#else       // Standard identifiers
            /* STD frame: 0 = Standard */
			FLEXCAN_B.MB[bufferIndex].MSG_CS.B.IDE = 0x0;
            /* Std.ID */
			FLEXCAN_B.MB[bufferIndex].ID.R = canRxMsgConfig[msgIndex].id<<18;
#endif

            /* Rx active and empty */
            FLEXCAN_B.MB[bufferIndex].MSG_CS.B.CODE = RX_ACTIVE_EMPTY;

#ifdef CANDRV_INTERRUPT_MODE
            /*
             * If this CAN msg has a RX Callback configured,
             * hence enable the corresponding isr
             */
            if (canRxMsgConfig[msgIndex].rxCallback != NULL) {
                tmp = FLEXCAN_B.IMASK1.R;
			    FLEXCAN_B.IMASK1.R = tmp | (0x1U<<bufferIndex);
            }
#endif
		}

		msgIndex++;
	}
}

/// Set the message wise 'freezeFrameEnabled' state for a given CAN message.
boolean SetCanDrvFreezeFrame(uint8 rxTx, CanRxMsgIndexType msgIndex, boolean enabled)
{
    int i = 0;
    
    if (rxTx == 0)          // Enable/disable rx messages
    {
        if (msgIndex >= NR_OF_CAN_RX_MESSAGES)
        {
            return(FALSE);      // Illegal msgIndex parameter for rx messages.
        }
        canRxMsgState[msgIndex].freezeFrameEnabled = enabled;
    }
    else if (rxTx == 1)     // Enable/disable tx messages
    {
        if (msgIndex >= NR_OF_CAN_TX_MESSAGES)
        {
            return(FALSE);      // Illegal msgIndex parameter for tx messages.
        }
        canTxMsgState[msgIndex].freezeFrameEnabled = enabled;
    }
    else if (rxTx == 0xFF)  // Enable/disable all messages
    {
        for (i = 0; i<NR_OF_CAN_RX_MESSAGES; i++)
        {
            canRxMsgState[i].freezeFrameEnabled = enabled;
        }
        for (i = 0; i<NR_OF_CAN_TX_MESSAGES; i++)
        {
            canTxMsgState[i].freezeFrameEnabled = enabled;
        }
    }
    else
    {
        return(FALSE);      // Illegal rxTx parameter.
    }
    
    return(TRUE);
}

/// This function manages incoming messages.
/// Can be called by the application (polling mode) or by an ISR (interrupt mode).
/// \param MessageBufferIndex bufferIndex : MB index
/// \param CanChannelType canChannel: CAN channel identifier (it can be CHANNEL_FLEXCAN_A or CHANNEL_FLEXCAN_B).
static void CanManageReceivedMsg(MessageBufferIndex bufferIndex, CanChannelType canChannel)
{
    /* temporary and volatile 32bit */
	volatile CanMessageId messageId = 0U;

    /* temporary and volatile 8bit */
    volatile uint8 u8_temp = 0U;

    /* Variables used for data copy */
	sint8 *source = 0x0U;
	sint8 *destination = 0x0U;
	sint8 length = 0U;

    CanRxMsgIndexType msgIndex = bufferIndex - RX_BUFFER_OFFSET;    // Index of a rx message. Range [0..NR_OF_CAN_RX_MESSAGES-1].

	if (canChannel == CHANNEL_FLEXCAN_A) {
        /* mandatory - read control/status word - lock the MB */
        u8_temp = *(volatile uint8*)&FLEXCAN_A.MB[bufferIndex].CS.R;

        if (FLEXCAN_A.MB[bufferIndex].MSG_CS.B.IDE == 0x0) {
            /* bit IDE == 0 ==> Standard Frame */
		    messageId = FLEXCAN_A.MB[bufferIndex].ID.B.STD_ID;
        }
        else {
            /* bit IDE == 1 ==> Extended Frame */
            messageId = FLEXCAN_A.MB[bufferIndex].ID.B.EXT_ID;
        }

        /* Message lenght acquisition */
		length = (sint8)FLEXCAN_A.MB[bufferIndex].MSG_CS.B.LENGTH;
	}
	else if (canChannel == CHANNEL_FLEXCAN_B) {
        /* mandatory - read control/status word - lock the MB */
        u8_temp = *(volatile uint8*)&FLEXCAN_B.MB[bufferIndex].CS.R;

        if (FLEXCAN_B.MB[msgIndex].MSG_CS.B.IDE == 0x0) {
            /* bit IDE == 0 ==> Standard Frame */
		    messageId = FLEXCAN_B.MB[bufferIndex].ID.B.STD_ID;
        }
        else {
            /* bit IDE == 1 ==> Extended Frame */
            messageId = FLEXCAN_B.MB[bufferIndex].ID.B.EXT_ID;
        }

        /* Message lenght acquisition */
		length = (sint8)FLEXCAN_B.MB[bufferIndex].MSG_CS.B.LENGTH;
	}
	else {
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);   // Not existing FlexCAN module
	}
    
    // Check CAN identifier of the message
    SetErrorFatal(ERR_ID_GENERIC, (canRxMsgConfig[msgIndex].id != messageId));       // The received message is not the expected one

    if (canRxMsgConfig[msgIndex].length != length) {
        SetError(ERR_ID_GENERIC, TRUE);    // The length of the received message is not the expected one
        // Message will be discarded
	}
    else {
        /*
         * If msg length is ok, hence copy data and
         * call the corresponding handler if configured.
         */
	    if (canChannel == CHANNEL_FLEXCAN_A) {
		    source = (void*)FLEXCAN_A_MSG_BUFF_BASE(bufferIndex);
	    }
	    else {
		    source = (void*)FLEXCAN_B_MSG_BUFF_BASE(bufferIndex);
	    }

	    destination = canRxMsgConfig[msgIndex].data;
	    memcpy(destination, source, length);

        /* Get message timestamp */
        if (canRxMsgConfig[msgIndex].periodic == TRUE) { // If the received message is periodic, hence get timestamp
            CanComRxCallback(msgIndex);
         }

        /* Trigger the handler if configured */
	    if (canRxMsgConfig[msgIndex].rxCallback != 0U) {
		    canRxMsgConfig[msgIndex].rxCallback((CanTxMsgIndexType)(msgIndex));
	    }
    }
}

/// Poll for the reception of a message.
/// Used when interrupts are disabled.
/// Called bythe application.
/// \param CanRxMsgIndexType msgIndex : Index of a rx message. Range [0..NR_OF_CAN_RX_MESSAGES-1].
/// Ex. CanPollMessage(IsoTpRequest);
StdReturnType CanPollMessage(CanRxMsgIndexType msgIndex)
{
    /* temporary and volatile 32bit */
	volatile uint32 tmp = 0U;
    
    CanChannelType canChannel = canRxMsgConfig[msgIndex].channel;

    MessageBufferIndex bufferIndex = msgIndex + RX_BUFFER_OFFSET;    // FlexCan message buffer index. Range [0..31].

    uint32 bufferMask = 1U<<bufferIndex;                // Message buffer mask.
    
    // Check parameters
    SetErrorFatal(ERR_ID_GENERIC, ((uint32)msgIndex >= NR_OF_CAN_RX_MESSAGES));       // Illegal 'msgIndex'

    /*
     * Return error if this function attempts to poll a
     * message buffer for which a isr has been defined and the
     * driver is working in interrupt mode
     */
    if (canDriverMode == ISR_MODE && canRxMsgConfig[msgIndex].rxCallback != 0U) {
        return(STD_NOT_OK);
    }

    if (canChannel == CHANNEL_FLEXCAN_A) {
        /* Check whether a new message is received in FlexCan_A module or not */
        if ((FLEXCAN_A.IFLAG1.R & bufferMask) != 0x0) {

            /* Manage the incoming message */
            CanManageReceivedMsg(bufferIndex, canChannel);

            /* release the internal lock for all Rx MBs
	         * by reading the TIMER */
            tmp = FLEXCAN_A.TIMER.R;

            /* Clear flag register */
            FLEXCAN_A.IFLAG1.R = bufferMask;
        }
    }
    else if (canChannel == CHANNEL_FLEXCAN_B) {
        /* Check whether a new message is received in FlexCan_B module or not */
        if ((FLEXCAN_B.IFLAG1.R & bufferMask) != 0x0) {

            /* Manage the incoming message */
            CanManageReceivedMsg(bufferIndex, canChannel);

            /* release the internal lock for all Rx MBs
	         * by reading the TIMER */
            tmp = FLEXCAN_B.TIMER.R;

            /* Clear flag register */
            FLEXCAN_B.IFLAG1.R = bufferMask;
        }
    }
    else {
        return STD_NOT_OK;
    }

    return STD_OK;
}

/// Function used to warn that a message has been sent properly
/// \param MessageBufferIndex bufferIndex : MB index
static void CanManageSentMsg(MessageBufferIndex bufferIndex)
{
    CanTxMsgIndexType msgIndex = 0U;

    msgIndex = bufferIndex - TX_BUFFER_OFFSET;

    /* Trigger the handler if configured */
    if (canTxMsgConfig[msgIndex].txCallback != 0U) {
        canTxMsgConfig[msgIndex].txCallback(msgIndex);
    }
}

/// Manages ISRs caused by a message rx or tx.
/// Called by an ISR.
/// \param isrSourceIndex: isr index
/// \param uint32 bufferFlags : mask representing FlexCan isr source
/// \param CanChannelType canChannel : CAN channel identifier (it can be CHANNEL_FLEXCAN_A or CHANNEL_FLEXCAN_B).
void ManageCanIsr(uint8 isrSourceIndex, uint32 bufferFlags, CanChannelType canChannel)
{
    /* temporary and volatile 32bit */
	volatile uint32 tmp = 0U;

	/* index variables */
    uint32 i;

    /*
     * This mask indicates the buffer in charge of managing the
     * incoming message (and for which is configured the corresponding isr).
     */
    volatile uint32 thisBufferHasTheIsr = 0U;

    /* FlexCan message buffer index. Range [0..31] */
    MessageBufferIndex bufferIndex;

    /* Initialize "i" and "bufferIndex" to speed while loop up */
    if (TX_BUFFER_OFFSET >= isrSourceIndex) {
        i = 1U << TX_BUFFER_OFFSET;
        bufferIndex = TX_BUFFER_OFFSET;
    }
    else {
        i = 1U << isrSourceIndex;
        bufferIndex = isrSourceIndex;
    }

    // Check parameters
    SetErrorFatal(ERR_ID_GENERIC, ((canChannel!=CHANNEL_FLEXCAN_A) && (canChannel!=CHANNEL_FLEXCAN_B)));       // Illegal 'canChannel'

    /* Notice that MAX_BUFF_INDEX_MASK is just an upper bound, it is never reached except for MB[31] */
	while (i <= MAX_BUFF_INDEX_MASK) {

        if (canChannel == CHANNEL_FLEXCAN_A) {
            thisBufferHasTheIsr = ((bufferFlags & i) & FLEXCAN_A.IMASK1.R);
        }
        else {
            thisBufferHasTheIsr = ((bufferFlags & i) & FLEXCAN_B.IMASK1.R);
        }

		/* Check if the incoming msg has its corresponding isr */
		if (thisBufferHasTheIsr == i) {

            if (bufferIndex > BUFFER_BORDERLINE) {       // If rx message ...
			    CanManageReceivedMsg(bufferIndex, canChannel);
            }
            else {                              // If tx message ...
                CanManageSentMsg(bufferIndex);
            }

            /* Break since the incoming/outgoing msg has been handled */
            break;
		}

		i = i<<1;
		bufferIndex++;
	}

	if (canChannel == CHANNEL_FLEXCAN_A) {
        /* release the internal lock for all Rx MBs
	     * by reading the TIMER */
		tmp = FLEXCAN_A.TIMER.R;

        /* Clear the proper isr flag. Note: write "0" has no effect */
	    FLEXCAN_A.IFLAG1.R = thisBufferHasTheIsr;
	}
	else {
        /* release the internal lock for all Rx MBs
	     * by reading the TIMER */
		tmp = FLEXCAN_B.TIMER.R;

        /* Clear the proper isr flag. Note: write "0" has no effect */
	    FLEXCAN_B.IFLAG1.R = thisBufferHasTheIsr;
	}
}

/// Initialize can Driver module
void CanDrvInit(void)
{
    uint8 i = 0;
    
    // Check development errors
#ifndef BRANCH_PIAGGIO
    // If DEVELOPMENT is defined (i.e. during system development), then every function provides stronger checks (see 'Extended error detection')
#ifdef DEVELOPMENT
    CanTxMsgIndexType msgIndex;
    CanMessageId messageId;

    SetErrorDevelop(ERR_ID_GENERIC, ( (NR_OF_CAN_TX_MESSAGES+NR_OF_CAN_RX_MESSAGES) > 32));
    
    for (msgIndex=0; msgIndex<NR_OF_CAN_TX_MESSAGES; msgIndex++)
    {
        messageId = canTxMsgConfig[msgIndex].id;   
        SetErrorDevelop(ERR_ID_GENERIC, (messageId>0x7FF));
        SetErrorDevelop(ERR_ID_GENERIC, 
            ( (canTxMsgConfig[msgIndex].channel != CHANNEL_FLEXCAN_A) 
            && (canTxMsgConfig[msgIndex].channel != CHANNEL_FLEXCAN_B) ));
    }
    // todo: check pTxMsgConfig->length
#endif  // DEVELOPMENT    
#endif		// BRANCH_PIAGGIO

    if (flexCanMcuConf[CHANNEL_FLEXCAN_A].peripheralEn == CANDRV_ENABLED &&
    flexCanMcuConf[CHANNEL_FLEXCAN_B].peripheralEn == CANDRV_DISABLED) {
	    InitFlexCAN_A();
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_B].peripheralEn ==
    CANDRV_ENABLED && flexCanMcuConf[CHANNEL_FLEXCAN_A].peripheralEn == CANDRV_DISABLED) {
	    InitFlexCAN_B();
    }
    else if (flexCanMcuConf[CHANNEL_FLEXCAN_B].peripheralEn ==
    CANDRV_ENABLED && flexCanMcuConf[CHANNEL_FLEXCAN_A].peripheralEn == CANDRV_ENABLED) {
	    /* Use both */
	    InitFlexCAN_A();
	    InitFlexCAN_B();
    }
    else {  
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);
    }

	SendConfig();
	ReceiveConfig();

    initializationState = COMPONENT_STATE_INIZIALIZED;
}

/// Manage message to send
/// \param CanRxMsgIndexType msgIndex : Index of a rx message. Range [0..NR_OF_CAN_RX_MESSAGES-1].
/// \param CanChannelType canChannel : CAN channel identifier (it can be CHANNEL_FLEXCAN_A or CHANNEL_FLEXCAN_B).
static StdReturnType CanSendManageMsg(CanTxMsgIndexType msgIndex, CanChannelType canChannel)
{
    /* Variables used for data copy */
	sint8 *source = 0x0;
	sint8 *dest = 0x0;
    uint8 length = 0;

    /* return value */
    StdReturnType returnCode = STD_NOT_OK;

    /* Flag usefull to warn the calling environemnt if an ABORT is occurred */
    boolean abortOccurred = FALSE;

    /* Buffer Id */
    MessageBufferIndex bufferIndex = msgIndex + TX_BUFFER_OFFSET;       // FlexCan message buffer index. Range [0..31].

    /* Compute Message buffer mask */
    uint32 bufferMask = 0x1U << bufferIndex;

    volatile FLEXCAN_tag * FLEXCAN_X = NULL;

    if (CHANNEL_FLEXCAN_A == canChannel) {
        FLEXCAN_X = &FLEXCAN_A;
    }
    else {
        FLEXCAN_X = &FLEXCAN_B;
    }

    /*
     * When the Abort feature is enabled (AEN in MCR is asserted), after the Interrupt Flag is asserted
     * for an MB configured as transmit buffer, the MB is blocked, therefore the CPU is not able to update it until
     * the Interrupt Flag be negated by CPU. It means that the CPU must clear the corresponding IFLAG before
     * starting to prepare this MB for a new transmission or reception.
     */
    if (FLEXCAN_X->MCR.B.AEN == 1U && 
    ( (canTxMsgConfig[msgIndex].txCallback == NULL) ||
    (canDriverMode == POLLING_MODE) ) ) {
        FLEXCAN_X->IFLAG1.R = bufferMask;
    }

    /* Check if MB is active */
    if (FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE != TX_INACTIVE &&
        FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE != TX_ABORT) {

        /* Check if ABORT capability is enabled */
        if (FLEXCAN_X->MCR.B.AEN == 1U) {
            /* ABORT enabled */
            FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE = TX_ABORT;

            /* Check if ABORT has been finalized */
            if (FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE == TX_ABORT) {
                /* ABORT finalized: raise error, set return flag and continue to send new msg */
                SetError(ERR_ID_GENERIC, TRUE);

                /* Set flasg to warn the calling environment that an ABORT is occurred */
                abortOccurred = TRUE;
            }
            else {
                /* ABORT has not been finalized */
                if (FLEXCAN_X->IFLAG1.R & bufferMask) {
                    /* If the corresponding IFLAG is set, previous msg has been correctly sent. Continue to send new message */
                }
                else {
                    // The following while loop is the correct management policy for TX abort mechanism...
                    /* If the corresponding IFLAG is reset, the CPU must wait for it to be set */
                    //while ( ! (FLEXCAN_X->IFLAG1.R & bufferMask) )
                    //    ;

                    //...but the simple while does not solve the following critic cases:
                    // 1) accidental cable disconnection (or ECU alone in the network)
                    // 2) heavy bus condition (CAN bus always busy)

                    // the solutions to prevent from while loop to never exits are (previous two cases):
                    // 1) capture this condition using ESR register (ACK_ERR) to exits from while loop
                    // 2) timeout when the while loop starts

                    // In this phase of the project the while loop has been removed and a more simple/performing
                    // "if" statement has been introduced. If the while loop (for ever) condition is captured,
                    // hence an error flag will be raised to the calling environment

                    // TODO: the proper way to manage the Tx Abort strategy is as described above. But the following "if"
                    // statement will be used to simplify the management.

                    // Alternative solution for while loop
                    if ((FLEXCAN_X->IFLAG1.R & bufferMask) == FALSE) {
                        return STD_BUSY; // But we will never know the reason since this solution is a workaround
                    }

                    /* Check CODE to figure out the ABORT request to be accomplished or not */
                    if (FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE == TX_ABORT) {
                        /* ABORT finalized: raise error, set return flag and continue to send new msg */
                        SetError(ERR_ID_GENERIC, TRUE);

                        /* Set flag to warn the calling environment that an ABORT is occurred */
                        abortOccurred = TRUE;
                    }
                    else if (FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE == TX_INACTIVE) {
                        /* ABORT has not been finalized, previous msg has been correctly sent. Continue to send new message */
                    }
                    else {
                        /* Unreachble scenario, raise exception if application runs this branch */
                        SetError(ERR_ID_GENERIC, TRUE);
                    }
                }
            }

        }
        else { /* ABORT disabled */
            /*
             * If backwards compatibility is desired (AEN in MCR negated), just
             * write ‘1000’ (TX_INACTIVE) to the Code field to inactivate the MB
             * but then the pending frame may be transmitted without notification
             */
            FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE = TX_INACTIVE;
        }
    }

    /* Copy source data to CAN buffer */
    if (CHANNEL_FLEXCAN_A == canChannel) {
        dest = (void*)FLEXCAN_A_MSG_BUFF_BASE(bufferIndex);
    }
    else {
        dest = (void*)FLEXCAN_B_MSG_BUFF_BASE(bufferIndex);
    }
    source = canTxMsgConfig[msgIndex].data;
    length = canTxMsgConfig[msgIndex].length;
    memcpy(dest, source, canTxMsgConfig[msgIndex].length);

    /* Send msg directly */
    FLEXCAN_X->MB[bufferIndex].MSG_CS.B.CODE = TX_UNCOND_ONCE;

    /* Message has been sent but we have to warn the calling environment if the ABORT is occurred */
    if (TRUE == abortOccurred) {
        returnCode = STD_ABORT_PREVIUOS;
    }
    else {
        returnCode = STD_OK;
    }

    return(returnCode);
}

/// CanDrv Message transmission
/// - Multithread: YES.
/// \param CanTxMsgIndexType msgIndex : Index of a tx message. Range [0..NR_OF_CAN_TX_MESSAGES-1].
StdReturnType CanTransmit(CanTxMsgIndexType msgIndex)
{
    /* return value */
    StdReturnType returnCode = STD_NOT_OK;

    /* CAN channel identifier (it can be CHANNEL_FLEXCAN_A or CHANNEL_FLEXCAN_B) */
    CanChannelType canChannel;

    canChannel = canTxMsgConfig[msgIndex].channel;

    /* Check if the corresponding canChannel is valid */
    if (canChannel != CHANNEL_FLEXCAN_A && canChannel != CHANNEL_FLEXCAN_B) {
        SetErrorFatal(ERR_ID_GENERIC,TRUE); /* Illegal CAN channel */
    }

    if (canChannel == CHANNEL_FLEXCAN_A) {
        returnCode = CanSendManageMsg(msgIndex, CHANNEL_FLEXCAN_A);
    }
    else {
        returnCode = CanSendManageMsg(msgIndex, CHANNEL_FLEXCAN_B);
    }

    return(returnCode);
}

/// Enable CAN interrupts.
/// Used to switch from 'polling mode' to 'interrupt mode'.
void CanDrvEnableInterrupts(void)
{
    uint32 i = 0U;
    uint32 tmp = 0U;

    for (i=0U; i<NR_OF_CAN_TX_MESSAGES; i++) {
        if (canTxMsgConfig[i].txCallback != NULL) {
            if (canTxMsgConfig[i].channel == CHANNEL_FLEXCAN_A) {
                if (flexCanMcuConf[0].peripheralEn == CANDRV_ENABLED) {
                    tmp = FLEXCAN_A.IMASK1.R;
			        FLEXCAN_A.IMASK1.R = tmp | (0x1U<<(i+TX_BUFFER_OFFSET));
                }
            }
            else {
                if (flexCanMcuConf[1].peripheralEn == CANDRV_ENABLED) {
                    tmp = FLEXCAN_B.IMASK1.R;
                    FLEXCAN_B.IMASK1.R = tmp | (0x1U<<(i+TX_BUFFER_OFFSET));
                }
            }
        }
    }

    for (i=0U; i<NR_OF_CAN_RX_MESSAGES; i++) {
        if (canRxMsgConfig[i].rxCallback != NULL) {
            if (canRxMsgConfig[i].channel == CHANNEL_FLEXCAN_A) {
                if (flexCanMcuConf[0].peripheralEn == CANDRV_ENABLED) {
                    tmp = FLEXCAN_A.IMASK1.R;
			        FLEXCAN_A.IMASK1.R = tmp | (0x1U<<(i+RX_BUFFER_OFFSET));
                }
            }
            else {
                if (flexCanMcuConf[1].peripheralEn == CANDRV_ENABLED) {
                    tmp = FLEXCAN_B.IMASK1.R;
                    FLEXCAN_B.IMASK1.R = tmp | (0x1U<<(i+RX_BUFFER_OFFSET));
                }
            }
        }
    }

    /* Set global variable to isr mode */
    canDriverMode = ISR_MODE;
}

/// Disable all CAN interrupts.
/// Used to switch from 'interrupt mode' to 'polling mode'.
/// After this function is called, only 'polling mode' can be used.
void CanDrvDisableInterrupts(void)
{
    /* Channel A */
    if (flexCanMcuConf[0].peripheralEn == CANDRV_ENABLED) {
        FLEXCAN_A.CTRL.B.ERR_MSK = 0x0; /* Disable error isr */
        FLEXCAN_A.IMASK1.R = 0x0;       /* Disable all can buffer isr */
    }

    /* Channel B */
    if (flexCanMcuConf[1].peripheralEn == CANDRV_ENABLED) {
        FLEXCAN_B.CTRL.B.ERR_MSK = 0x0; /* Disable error isr */
        FLEXCAN_B.IMASK1.R = 0x0;       /* Disable all can buffer isr */
    }

    /* Set global variable to polling mode */
    canDriverMode = POLLING_MODE;
}

/// Manage the reception of messages when interrupts are disabled.
/// This function must be called periodically.
/// - Multithread: NO.
void CanDrvPolling(void)
{
    uint8 i = 0U;

    for (i=0U; i<NR_OF_CAN_RX_MESSAGES; i++) {      // Loop for every MB ...
        CanPollMessage(i);
    }
}

StdReturnType CanDrvCheckBusOff(CanChannelType canChannel)
{
    StdReturnType result;
    volatile FLEXCAN_tag * FLEXCAN_X = NULL;

    if (CHANNEL_FLEXCAN_A == canChannel) {
        FLEXCAN_X = &FLEXCAN_A;
    }
    else {
        FLEXCAN_X = &FLEXCAN_B;
    }

    if (FLEXCAN_X->ESR.B.BOFF_INT == 0x1U) {
        result = STD_NOT_OK;
    }
    else {
        result = STD_OK;
    }

    return(result);
}

