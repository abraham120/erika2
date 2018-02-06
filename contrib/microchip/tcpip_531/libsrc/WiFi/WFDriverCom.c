/******************************************************************************

 MRF24WB0M Driver Com Layer
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFDriverCom.c
 Dependencies:	TCP/IP Stack header files
 Processor:		PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 Compiler:		Microchip C32 v1.10b or higher
				Microchip C30 v3.22 or higher
				Microchip C18 v3.34 or higher
 Company:		Microchip Technology, Inc.

 Software License Agreement

 Copyright (C) 2002-2010 Microchip Technology Inc.  All rights reserved.

 Microchip licenses to you the right to use, modify, copy, and distribute:
 (i)  the Software when embedded on a Microchip microcontroller or digital 
      signal controller product ("Device") which is integrated into 
      Licensee's product; or
 (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
      ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device used in 
	  conjunction with a Microchip ethernet controller for the sole purpose 
	  of interfacing with the ethernet controller.

 You should refer to the license agreement accompanying this Software for 
 additional information regarding your rights and obligations.

 THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY INCIDENTAL,
 SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST
 OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS BY
 THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS
 FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON
 THE BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR
 OTHERWISE.


 Author				Date		Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 KH                 27 Jan 2010 Updated for MRF24WB0M
******************************************************************************/

/*
*********************************************************************************************************
*                                           INCLUDES                               
*********************************************************************************************************
*/

#include "TCPIP_Stack/WFMac.h"
#if defined(WF_CS_TRIS)

/*
*********************************************************************************************************
*                                           DEFINES      
*********************************************************************************************************
*/

/* used for assertions */
#if defined(WF_DEBUG)
    #define WF_MODULE_NUMBER    WF_MODULE_WF_DRIVER_COM
#endif

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES      
*********************************************************************************************************
*/

/* Functions that are called from the External Interrupt routine use these global */
/* variables instead of local variables to avoid stack corruption on CPU's that   */
/* that use overlay memory.  See note in WFEintHandler() function.                */
static UINT8 g_txBuf[3];
static UINT8 g_rxBuf[3];

static UINT8 g_HostIntSaved = 0;

// Keep these as static globals instead of local variables in the Eint Handler.
// If declared as local variables, causes stack corruption in PIC18
static UINT8  g_EintHostIntRegValue;
static UINT8  g_EintHostIntMaskRegValue;
static UINT8  g_EintHostInt;

static BOOL             g_MgmtReadMsgReady;                  /* TRUE if rx mgmt msg to process, else FALSE              */
static volatile BOOL    g_ExIntNeedsServicing;               /* TRUE if external interrupt needs processing, else FALSE */

tRawMoveState RawMoveState;

/*
*********************************************************************************************************
*                                       LOCAL FUNCTION PROTOTYPES      
*********************************************************************************************************
*/

static void ProcessMgmtRxMsg(void);
static void ChipReset(void);
static void ProcessInterruptServiceResult(void);

/*****************************************************************************
 * FUNCTION: WFProcess
 *
 * RETURNS:  None
 *
 * PARAMS:   None
 *
 *  NOTES:   This function is called from WFProcess.  It does the following:
 *             1) checks for and processes MRF24WB0M external interrupt events
 *             2) checks for and processes received management messages from the MRF24WB0M
 *             3) maintains the PS-Poll state (if applicable)
 *           
 *****************************************************************************/
void WFProcess(void)
{
    UINT16 len;

    //----------------------------------------------------------
    // if there is a MRF24WB0M External interrupt (EINT) to process
    //----------------------------------------------------------
    if (g_ExIntNeedsServicing == TRUE)
    {
        g_ExIntNeedsServicing = FALSE;
        ProcessInterruptServiceResult();
    }
    //----------------------------------------
    // else if there is management msg to read
    //----------------------------------------
    else if (g_MgmtReadMsgReady == TRUE)
    {
        /* Ensure the MRF24WB0M is awake (only applies if PS-Poll was enabled) */
        EnsureWFisAwake();

        //-----------------------------
        // process management read
        //-----------------------------
        // if the Raw Rx buffer is available, or only has the scratch mounted, then mount it so
        // we can process received Mgmt message.  Otherwise, stay in this state and keep checking
        // until we can mount the Raw Rx buffer and get the management message.  Once the Raw Rx
        // is acquired, rx data packets are held off until we finish processing mgmt message.
        if ( RawGetMgmtRxBuffer(&len) )
        {
            // handle received managment message
            g_MgmtReadMsgReady = FALSE;
            ProcessMgmtRxMsg();

            // reenable interrupts
            WF_EintEnable();
        }
    }
    //-----------------------------------
    // else no EINT or Mgmt Rx to process
    //-----------------------------------
    else
    {
#if defined (WF_USE_POWER_SAVE_FUNCTIONS)
        /* if PS-Poll mode was enabled by application and was previously deactivated by WF driver */
        if (WFisPsPollEnabled() && !WFIsPsPollActive() )
        {
            /* reactivate PS-Poll mode on MRF24WB0M (allow MRF24WB0M to sleep) */
            WFConfigureLowPowerMode(WF_LOW_POWER_MODE_ON);
        }    
#endif                
    }
}


/*****************************************************************************
 * FUNCTION: ProcessInterruptServiceResult
 *
 * RETURNS: N/A
 *
 * PARAMS:
 *      N/A
 *
 *
 *  NOTES: Processes EXINT from MRF24WB0M.  Called by WFProcess().
 *****************************************************************************/
static void ProcessInterruptServiceResult(void)
{
    UINT8  hostIntRegValue;
    UINT8  hostIntMaskRegValue;
    UINT8  hostInt;

    /* Ensure the MRF24WB0M stays awake (only applies if PS-Poll was enabled) */
    EnsureWFisAwake();

    /* read hostInt register to determine cause of interrupt */
    hostIntRegValue = Read8BitWFRegister(WF_HOST_INTR_REG);

    // OR in the saved interrupts during the time when we were waiting for raw complete, set by WFEintHandler()
    hostIntRegValue |= g_HostIntSaved;
    
    // done with the saved interrupts, clear variable
    g_HostIntSaved = 0;


    hostIntMaskRegValue  = Read8BitWFRegister(WF_HOST_MASK_REG);

    // AND the two registers together to determine which active, enabled interrupt has occurred
    hostInt = hostIntRegValue & hostIntMaskRegValue;

    // if received a level 2 interrupt (should not happen!)
    if((hostInt & WF_HOST_INT_MASK_INT2) == WF_HOST_INT_MASK_INT2)
    {
        /* read the 16 bit interrupt register */
        /* CURRENTLY unhandled interrupt */
        WF_ASSERT(FALSE);
        WF_EintEnable();
    }
    // else if got a FIFO 1 Threshold interrupt (Management Fifo)
    else if((hostInt & WF_HOST_INT_MASK_FIFO_1_THRESHOLD) == WF_HOST_INT_MASK_FIFO_1_THRESHOLD)
    {
        /* clear this interrupt */
        Write8BitWFRegister(WF_HOST_INTR_REG, WF_HOST_INT_MASK_FIFO_1_THRESHOLD);
        // notify MAC state machine that management message needs to be processed
        g_MgmtReadMsgReady = TRUE; 
    }
    // else if got a FIFO 0 Threshold Interrupt (Data Fifo)
    else if((hostInt & WF_HOST_INT_MASK_FIFO_0_THRESHOLD) == WF_HOST_INT_MASK_FIFO_0_THRESHOLD)
    {
        /* clear this interrupt */
        Write8BitWFRegister(WF_HOST_INTR_REG, WF_HOST_INT_MASK_FIFO_0_THRESHOLD);

        g_HostRAWDataPacketReceived = TRUE;  /* this global flag is used in MACGetHeader() to determine a received data packet */
#if defined(WF_USE_DATA_TX_RX_FUNCTIONS)
        {
            UINT16 rxDataPacketLength;
            /* determine length of packet and signal the rx data packet event */
            rxDataPacketLength = Read16BitWFRegister(WF_HOST_RFIFO_BCNT0_REG) & 0x0fff; /* LS 12 bits are the data length */
            WF_ProcessEvent(WF_EVENT_RX_PACKET_RECEIVED, rxDataPacketLength); 
        }
#endif
    }
    // else got a Host interrupt that we don't handle
    else if(hostInt)
    {
        /* unhandled interrupt */
       /* clear this interrupt */
        Write8BitWFRegister(WF_HOST_INTR_REG, hostInt);
        WF_EintEnable();
    }
    // we got a spurious interrupt (no bits set in register)
    else
    {
        /* spurious interrupt */
        WF_EintEnable();
    }
}


/*****************************************************************************
 * FUNCTION: Read8BitWFRegister
 *
 * RETURNS: register value
 *
 * PARAMS:
 *      regId -- ID of 8-bit register being read
 *
 *  NOTES: Reads WF 8-bit register
 *****************************************************************************/
UINT8 Read8BitWFRegister(UINT8 regId)
{
    g_txBuf[0] = regId | WF_READ_REGISTER_MASK;
    WF_SpiEnableChipSelect();
    
    WFSpiTxRx(g_txBuf, 
              1,
              g_rxBuf,
              2);

    WF_SpiDisableChipSelect();
    
    return g_rxBuf[1];   /* register value returned in the second byte clocking */
}

/*****************************************************************************
 * FUNCTION: Write8BitWFRegister
 *
 * RETURNS: None
 *
 * PARAMS:
 *      regId -- ID of 8-bit register being written to
 *      value -- value to write
 *
 *  NOTES: Writes WF 8-bit register
 *****************************************************************************/
void Write8BitWFRegister(UINT8 regId, UINT8 value)
{
    g_txBuf[0] = regId | WF_WRITE_REGISTER_MASK;
    g_txBuf[1] = value;
    
    WF_SpiEnableChipSelect();

    WFSpiTxRx(g_txBuf, 
              2,
              g_rxBuf,
              1);

    WF_SpiDisableChipSelect();
}

/*****************************************************************************
 * FUNCTION: Read16BitWFRegister
 *
 * RETURNS: register value
 *
 * PARAMS:
 *      regId -- ID of 16-bit register being read
 *
 *  NOTES: Reads WF 16-bit register
 *****************************************************************************/
UINT16 Read16BitWFRegister(UINT8 regId)
{
    g_txBuf[0] = regId | WF_READ_REGISTER_MASK;
    WF_SpiEnableChipSelect();
    
    WFSpiTxRx(g_txBuf, 
              1,
              g_rxBuf,
              3);

    WF_SpiDisableChipSelect();
    
    return (((UINT16)g_rxBuf[1]) << 8) | ((UINT16)(g_rxBuf[2]));
}

/*****************************************************************************
 * FUNCTION: Write16BitWFRegister
 *
 * RETURNS: None
 *
 * PARAMS:
 *      regId -- ID of 16-bit register being written to
 *      value -- value to write
 *
 *  NOTES: Writes WF 16-bit register
 *****************************************************************************/
void Write16BitWFRegister(UINT8 regId, UINT16 value)
{
    g_txBuf[0] = regId | WF_WRITE_REGISTER_MASK;
    g_txBuf[1] = (UINT8)(value >> 8);       /* MS byte being written     */
    g_txBuf[2] = (UINT8)(value & 0x00ff);   /* LS byte being written     */
    
    WF_SpiEnableChipSelect();

    WFSpiTxRx(g_txBuf, 
              3,
              g_rxBuf,
              1);

    WF_SpiDisableChipSelect();
}

/*****************************************************************************
 * FUNCTION: WriteWFArray
 *
 * RETURNS: None
 *
 * PARAMS:
 *      regId  -- Raw register being written to
 *      pBuf   -- pointer to array of bytes being written
 *      length -- number of bytes in pBuf
 *
 *  NOTES: Writes a data block to specified raw register
 *****************************************************************************/
void WriteWFArray(UINT8 regId, UINT8 *p_Buf, UINT16 length)
{
    g_txBuf[0] = regId;

    WF_SpiEnableChipSelect();

    /* output cmd byte */
    WFSpiTxRx(g_txBuf, 
              1,
              g_rxBuf,
              1);

    /* output data array bytes */
    WFSpiTxRx(p_Buf, 
              length,
              g_rxBuf,
              1);

    WF_SpiDisableChipSelect();
}

/*****************************************************************************
 * FUNCTION: ReadWFArray
 *
 * RETURNS: None
 *
 * PARAMS:
 *      regId  -- Raw register being read from
 *      pBuf   -- pointer where to write out bytes
 *      length -- number of bytes to read
 *
 *  NOTES: Reads a block of data from a raw register
 *****************************************************************************/
void ReadWFArray(UINT8  regId, UINT8 *p_Buf, UINT16 length)
{
    WF_SpiEnableChipSelect();
    
    /* output command byte */
    g_txBuf[0] = regId | WF_READ_REGISTER_MASK;
    WFSpiTxRx(g_txBuf, 
              1,
              g_rxBuf,
              1);

    /* read data array */
    WFSpiTxRx(g_txBuf, 
              1,   /* garbage tx byte */
              p_Buf,
              length);

    WF_SpiDisableChipSelect();
}

#if defined (__18CXX)
/*****************************************************************************
 * FUNCTION: WriteWFROMArray
 *
 * RETURNS: None
 *
 * PARAMS:
 *      regId  -- Raw register being written to
 *      pBuf   -- pointer to array of bytes being written
 *      length -- number of bytes in pBuf
 *
 *  NOTES: Writes a data block (in ROM) to specified raw register.  This function
 *         is only needed for the Microchip PIC18.
 *****************************************************************************/
void WriteWFROMArray(UINT8 regId, ROM UINT8 *p_Buf, UINT16 length)
{
    g_txBuf[0] = regId;

    WF_SpiEnableChipSelect();

    /* output cmd byte */
    WFSpiTxRx(g_txBuf, 
              1,
              g_rxBuf,
              1);

    /* output data array bytes */
    WFSpiTxRx_Rom(p_Buf, 
                  length,
                  g_rxBuf,
                  1);


    WF_SpiDisableChipSelect();
}
#endif 

#include "TCPIP_Stack/TCPIP.h"


/*****************************************************************************
 * FUNCTION: ChipReset
 *
 * RETURNS: N/A
 *
 * PARAMS:
 *      N/A
 *
 *
 *  NOTES: Performs the necessary SPI operations to cause the MRF24WB0M to reset.
 *      This function also implements a delay so that it will not return until
 *      the WiFi device is ready to receive messages again.  The delay time will
 *      vary depending on the amount of code that must be loaded from serial
 *      flash.
 *****************************************************************************/
static void ChipReset(void)
{
    UINT16 value;
    UINT32 timeoutPeriod;
    UINT32 startTickCount;
    
    timeoutPeriod = TICKS_PER_SECOND;  /* 1000 ms */

    /* needed for Microchip PICTail (chip enable active low) */
    WF_SetCE_N(WF_LOW); /* set low to enable regulator */

    /* Configure reset pin */
    WF_SetRST_N(WF_HIGH);

    /* clear the power bit to disable low power mode on the MRF24WB0M */
    Write16BitWFRegister(WF_PSPOLL_H_REG, 0x0000);


    /* Set HOST_RESET bit in register to put device in reset */
    Write16BitWFRegister(WF_HOST_RESET_REG, Read16BitWFRegister(WF_HOST_RESET_REG) | WF_HOST_RESET_MASK);

    /* Clear HOST_RESET bit in register to take device out of reset */
    Write16BitWFRegister(WF_HOST_RESET_REG, Read16BitWFRegister(WF_HOST_RESET_REG) & ~WF_HOST_RESET_MASK);


    /* after reset is started poll register to determine when HW reset has completed */
    startTickCount = (UINT32)TickGet();  
    do
    {
        Write16BitWFRegister(WF_INDEX_ADDR_REG, WF_HW_STATUS_REG);
        value = Read16BitWFRegister(WF_INDEX_DATA_REG);
        if (TickGet() - startTickCount >= timeoutPeriod)
        {
            WF_ASSERT(FALSE);
        }   
    } while ( (value & WF_HW_STATUS_NOT_IN_RESET_MASK) == 0);

    
    /* if SPI not connected will read all 1's */
    WF_ASSERT(value != 0xffff);

    /* now that chip has come out of HW reset, poll the FIFO byte count register */
    /* which will be set to a non-zero value when the MRF24WB0M initialization is   */
    /* complete.                                                                 */
    startTickCount = (UINT32)TickGet();
    do
    {
        value = Read16BitWFRegister(WF_HOST_WFIFO_BCNT0_REG);
        if (TickGet() - startTickCount >= timeoutPeriod)
        {
            WF_ASSERT(FALSE);
        } 
    } while (value == 0);
    
}


/*****************************************************************************
 * FUNCTION: HostInterrupt2RegInit
 *
 * RETURNS: N/A
 *
 * PARAMS:
 *      hostIntrMaskRegMask - The bit mask to be modified.
 *      state               - One of WF_INT_DISABLE, WF_INT_ENABLE where
 *                             Disable implies clearing the bits and enable sets the bits.
 *
 *
 *  NOTES: Initializes the 16-bit Host Interrupt register on the MRF24WB0M with the
 *      specified mask value either setting or clearing the mask register
 *      as determined by the input parameter state. 
 *****************************************************************************/
static void HostInterrupt2RegInit(UINT16 hostIntMaskRegMask,
                                  UINT8  state)
{
    UINT16 int2MaskValue;

    /* Host Int Register is a status register where each bit indicates a specific event  */
    /* has occurred. In addition, writing a 1 to a bit location in this register clears  */
    /* the event.                                                                        */

    /* Host Int Mask Register is used to enable those events activated in Host Int Register */
    /* to cause an interrupt to the host                                                    */

    /* read current state of int2 mask reg */
    int2MaskValue = Read16BitWFRegister(WF_HOST_INTR2_MASK_REG);

    /* if caller is disabling a set of interrupts */
    if (state == WF_INT_DISABLE)
    {
        /* zero out that set of interrupts in the interrupt mask copy */
        int2MaskValue &= ~hostIntMaskRegMask;
    }
    /* else caller is enabling a set of interrupts */
    else
    {
        /* set to 1 that set of interrupts in the interrupt mask copy */
        int2MaskValue |= hostIntMaskRegMask;
    }
    
    /* write out new interrupt mask value */
    Write16BitWFRegister(WF_HOST_INTR2_MASK_REG, int2MaskValue);
    
    /* ensure that pending interrupts from those updated interrupts are cleared */
    Write16BitWFRegister(WF_HOST_INTR2_REG, hostIntMaskRegMask);
    
}

/*****************************************************************************
 * FUNCTION: HostInterruptRegInit
 *
 * RETURNS: N/A
 *
 * PARAMS:
 *      hostIntrMaskRegMask - The bit mask to be modified.
 *      state -  one of WF_EXINT_DISABLE, WF_EXINT_ENABLE where
 *                Disable implies clearing the bits and enable sets the bits.
 *
 *
 *  NOTES: Initializes the 8-bit Host Interrupt register on the MRF24WB0M with the
 *      specified mask value either setting or clearing the mask register
 *      as determined by the input parameter state.  The process requires
 *      2 spi operations which are performed in a blocking fashion.  The
 *      function does not return until both spi operations have completed.
 *****************************************************************************/
static void HostInterruptRegInit(UINT8 hostIntrMaskRegMask,
                                 UINT8 state)
{
    UINT8 hostIntMaskValue;

    /* Host Int Register is a status register where each bit indicates a specific event  */
    /* has occurred. In addition, writing a 1 to a bit location in this register clears  */
    /* the event.                                                                        */

    /* Host Int Mask Register is used to enable those events activated in Host Int Register */
    /* to cause an interrupt to the host                                                    */

    /* read current state of Host Interrupt Mask register */
    hostIntMaskValue = Read8BitWFRegister(WF_HOST_MASK_REG);

    /* if caller is disabling a set of interrupts */
    if (state == WF_INT_DISABLE)
    {
        /* zero out that set of interrupts in the interrupt mask copy */
        hostIntMaskValue = (hostIntMaskValue & ~hostIntrMaskRegMask);
    }
    /* else caller is enabling a set of interrupts */
    else
    {
        /* set to 1 that set of interrupts in the interrupt mask copy */
        hostIntMaskValue = (hostIntMaskValue & ~hostIntrMaskRegMask) | hostIntrMaskRegMask;
    }

    /* write out new interrupt mask value */
    Write8BitWFRegister(WF_HOST_MASK_REG, hostIntMaskValue);

    /* ensure that pending interrupts from those updated interrupts are cleared */
    Write8BitWFRegister(WF_HOST_INTR_REG, hostIntrMaskRegMask);
    
    
}


/*****************************************************************************
 * FUNCTION: WFEintHandler
 *
 * RETURNS: N/A
 *
 * PARAMS:
 *      N/A
 *
 *
 *  NOTES: This function must be called once, each time an external interrupt
 *      is received from the WiFi device.   The WiFi Driver will schedule any
 *      subsequent SPI communication to process the interrupt.
 *
 * IMPORTANT NOTE: This function, and functions that are called by this function
 *                 must NOT use local variables.  The PIC18, or any other processor
 *                 that uses overlay memory will corrupt the logical stack within
 *                 overlay memory if the interrupt uses local variables.  
 *                 If local variables are used within an interrupt routine the toolchain 
 *                 cannot properly determine how not to overwrite local variables in 
 *                 non-interrupt releated functions, specifically the function that was 
 *                 interrupted.
 *****************************************************************************/
void WFEintHandler(void)
{
    /*--------------------------------------------------------*/    
    /* if driver is waiting for a RAW Move Complete interrupt */
    /*--------------------------------------------------------*/
	if (RawMoveState.waitingForRawMoveCompleteInterrupt)
	{
		/* read hostInt register and hostIntMask register to determine cause of interrupt */
		g_EintHostIntRegValue      = Read8BitWFRegister(WF_HOST_INTR_REG);
		g_EintHostIntMaskRegValue  = Read8BitWFRegister(WF_HOST_MASK_REG);
    
		// AND the two registers together to determine which active, enabled interrupt has occurred
		g_EintHostInt = g_EintHostIntRegValue & g_EintHostIntMaskRegValue;

        /* if a RAW0 or RAW1 interrupt occurred, signifying RAW Move completed */
		if(g_EintHostInt & (WF_HOST_INT_MASK_RAW_0_INT_0 | WF_HOST_INT_MASK_RAW_1_INT_0))
		{
    		/* save the copy of the active interrupts */
			RawMoveState.rawInterrupt = g_EintHostInt;
			RawMoveState.waitingForRawMoveCompleteInterrupt = FALSE;
			
			/* if no other interrupts occurred other than a RAW0 or RAW1 interrupt */
			if((g_EintHostInt & ~(WF_HOST_INT_MASK_RAW_0_INT_0 | WF_HOST_INT_MASK_RAW_1_INT_0)) == 0u)
			{
				/* clear the RAW interrupts, re-enable interrupts, and exit */
				Write8BitWFRegister(WF_HOST_INTR_REG, (WF_HOST_INT_MASK_RAW_0_INT_0 | WF_HOST_INT_MASK_RAW_1_INT_0));
				WF_EintEnable();
				return;
			}
			/* else we got a RAW0 or RAW1 interrupt, but, there is also at least one other interrupt present */
    		else
    		{
    			// save the other interrupts and clear them for now
    			// keep interrupts disabled
    			g_HostIntSaved |= (g_EintHostInt & ~(WF_HOST_INT_MASK_RAW_0_INT_0 | WF_HOST_INT_MASK_RAW_1_INT_0));
    			Write8BitWFRegister(WF_HOST_INTR_REG, g_EintHostInt);
    		}
	    }
	    /*----------------------------------------------------------------------------------*/	    
	    /* else we did not get a RAW interrupt, but we did get at least one other interrupt */
	    /*----------------------------------------------------------------------------------*/
	    else
        {
			g_HostIntSaved |= g_EintHostInt;
			Write8BitWFRegister(WF_HOST_INTR_REG, g_EintHostInt);
			WF_EintEnable();
        }
	}

   	// Once we're in here, external interrupts have already been disabled so no need to call WF_EintDisable() in here
   
    /* notify state machine that an interrupt occurred */
    g_ExIntNeedsServicing = TRUE;
}


/*****************************************************************************
 * FUNCTION: WFHardwareInit
 *
 * RETURNS:  error code
 *
 * PARAMS:   None
 *
 *  NOTES:   Initializes CPU Host hardware interfaces (SPI, External Interrupt).
 *           Also resets the MRF24WB0M.
 *****************************************************************************/
void WFHardwareInit(void)
{
    g_MgmtReadMsgReady = FALSE;
    g_ExIntNeedsServicing = FALSE;

    RawMoveState.rawInterrupt  = 0;
    RawMoveState.waitingForRawMoveCompleteInterrupt = FALSE;   /* not waiting for RAW move complete */

    /* initialize the SPI interface */
    WF_SpiInit();
    
    /* Reset the MRF24WB0M (using SPI bus to write/read MRF24WB0M registers */
    ChipReset();
    
    /* disable the interrupts gated by the 16-bit host int register */
    HostInterrupt2RegInit(WF_HOST_2_INT_MASK_ALL_INT, WF_INT_DISABLE);
    
    /* disable the interrupts gated the by main 8-bit host int register */
    HostInterruptRegInit(WF_HOST_INT_MASK_ALL_INT, WF_INT_DISABLE);
    
    /* Initialize the External Interrupt for the MRF24WB0M allowing the MRF24WB0M to interrupt
     * the Host from this point forward. */
    WF_EintInit();
    WF_EintEnable();
    
    /* enable the following MRF24WB0M interrupts */
    HostInterruptRegInit((WF_HOST_INT_MASK_FIFO_1_THRESHOLD |     /* Mgmt Rx Msg interrupt        */
                          WF_HOST_INT_MASK_FIFO_0_THRESHOLD |     /* Data Rx Msg interrupt        */
                          WF_HOST_INT_MASK_RAW_0_INT_0      |     /* RAW0 Move Complete interrupt */
                          WF_HOST_INT_MASK_RAW_1_INT_0),          /* RAW1 Move Complete interrupt */
                          WF_INT_ENABLE);

     /* Disable PS-Poll mode */
    WFConfigureLowPowerMode(WF_LOW_POWER_MODE_OFF);

}



static void ProcessMgmtRxMsg(void)
{
    UINT8 msgType;
    
    /* read first byte from Mgmt Rx message (msg type) */
    RawRead(RAW_RX_ID, 0, 1, &msgType);

    /* if not a management response or management indicate then fatal error */
    WF_ASSERT( (msgType == WF_MGMT_CONFIRM_TYPE) || (msgType == WF_MGMT_INDICATE_TYPE) );

    if (msgType == WF_MGMT_CONFIRM_TYPE)
    {
        /* signal that a mgmt response has been received */
        SignalMgmtConfirmReceivedEvent();
    }
    else  /* must be WF_MGMT_INDICATE_TYPE */
    {
        /* handle the mgmt indicate */
        WFProcessMgmtIndicateMsg();
    }    
}


#else
// dummy func to keep compiler happy when module has no executeable code
void WFDriverCom_EmptyFunc(void)
{
}

#endif /* WF_CS_TRIS */




