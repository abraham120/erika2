/******************************************************************************

 MRF24WB0M Driver Tx Power functions
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFTxPower.c
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
#if defined(WF_CS_TRIS) && defined(WF_USE_TX_POWER_CONTROL_FUNCTIONS)


/*
*********************************************************************************************************
*                                           DEFINES                               
*********************************************************************************************************
*/

/* used for assertions */
#if defined(WF_DEBUG)
    #define WF_MODULE_NUMBER   WF_MODULE_WF_TX_POWER
#endif

#define TX_THOTTLE_ENABLE_BIT_MASK   ((UINT8)0x01)


#define WF_ZERO_DB_VALUE        (64)   

#define DEFAULT_MIN_TX_POWER        (-10) /* dB */


/*
*********************************************************************************************************
*                                           LOCAL FUNCTION PROTOTYPES                              
*********************************************************************************************************
*/

static INT8 WFPowerToAppPower(UINT8 wfPower);
static UINT8 AppPowerToWFPower(INT8 appPower);

/*******************************************************************************
  Function:	
    void WF_ThrottleTableSet(tWFThrottleTable *p_table)

  Summary:
    Sets Tx throttle table on MRF24WB0M.

  Description:
    Writes out Tx Throttle Table to MRF24WB0M.  Each msg byte of the throttle 
    table uses bit 7 as the data rate (0 for 1Mbit, 1 for 2Mbit).  Bits 6:0 
    are used for the Tx power level, where 64 corresponds to 0dB and each count
    is a 0.5dB step up or down.  Thus:
    <table>
        Value   dB
        -----   --
        44      -10.0dB
        ...     ...
        60      -2.0dB
        61      -1.5dB
        62      -1.0dB
        63      -0.5dB
        64      0.0dB (WF_ZERO_DB_VALUE)
        65      0.5dB
        66      1.0dB
        67      1.5dB
        68      2.0dB
        ...     ...
        84      10.0dB
    </table>

    Formula is: dB = 64 + (p_table->txPower * 2) [MRF24WB0M value]

  Precondition:
  	MACInit must be called first.

  Parameters:
    p_table -- pointer to Tx Throttle Table structure

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_ThrottleTableSet(tWFThrottleTable *p_table)
{
    UINT8  msgBuf[WF_NUM_THROTTLE_TABLE_ROWS];
    UINT8  i;
     
    /* for each row of the throttle table */     
    for (i = 0; i < WF_NUM_THROTTLE_TABLE_ROWS; ++i)
    {
        WF_ASSERT( (p_table->dataRate[i] == WF_ONE_MBIT_TX_RATE) || (p_table->dataRate[i] == WF_TWO_MBIT_TX_RATE) )
        WF_ASSERT( (p_table->txPower[i] >= -10) && (p_table->txPower[i] <= 10) );
        
        /* set MSB if 2mbps, else clear msb (indicating 1mbps) */
        msgBuf[i] = (p_table->dataRate[i] == WF_TWO_MBIT_TX_RATE) ? 0x80:0x00;
        
        /* OR in tx power level */
        msgBuf[i] |= AppPowerToWFPower(p_table->txPower[i]);  /* mask in tx power level  */
    }    
    
    SendSetParamMsg(PARAM_TX_THROTTLE_TABLE, msgBuf, sizeof(msgBuf)); 
}
    
/*******************************************************************************
  Function:	
    void WF_ThrottleTableGet(tWFThrottleTable *p_table)

  Summary:
    Gets Tx throttle table from MRF24WB0M.

  Description:
    Reads out Tx Throttle Table from MRF24WB0M.  Each msg byte of the throttle 
    table uses bit 7 as the data rate (0 for 1Mbit, 1 for 2Mbit).  Bits 6:0 
    are used for the Tx power level, where 64 corresponds to 0dB and each count
    is a 0.5dB step up or down.  Thus:
    <table>
        Value   dB
        -----   --
        44      -10.0dB
        ...     ...
        60      -2.0dB
        61      -1.5dB
        62      -1.0dB
        63      -0.5dB
        64      0.0dB (WF_ZERO_DB_VALUE)
        65      0.5dB
        66      1.0dB
        67      1.5dB
        68      2.0dB
        ...     ...
        84      10.0dB
    </table>

    Formula is: dB = 64 + (p_table->txPower * 2) [MRF24WB0M value]

  Precondition:
  	MACInit must be called first.

  Parameters:
    p_table -- pointer to Tx Throttle Table structure

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_ThrottleTableGet(tWFThrottleTable *p_table)
{
    UINT8  msgBuf[WF_NUM_THROTTLE_TABLE_ROWS];
    int i;
   
    memset(p_table, 0x00, sizeof(tWFThrottleTable));
    
    SendGetParamMsg(PARAM_TX_THROTTLE_TABLE, msgBuf, sizeof(msgBuf)); 
        
    for (i = 0; i < WF_NUM_THROTTLE_TABLE_ROWS; ++i)
    {
        /* strip off data rate bit */
        if ((msgBuf[i] & 0x80) > 0)
        {
            p_table->dataRate[i] = WF_TWO_MBIT_TX_RATE;
        }    
        else
        {
            p_table->dataRate[i] = WF_ONE_MBIT_TX_RATE;
        }    

        msgBuf[i] &= ~0x80;         /* strip off rate bit */
        
        /* convert tx power from chip throttle table to user value (in dB) */
        p_table->txPower[i] = WFPowerToAppPower(msgBuf[i]);
    }         
}

/*******************************************************************************
  Function:	
    static INT8 WFPowerToAppPower(UINT8 wfPower)

  Summary:
    Converts Tx power value from MRF24WB0M to dB value for Host application.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    wfPower - Value from 0-128 indicating the power level from the MRF24WB0M.

  Returns:
  	A UINT8 of the converted power level.
  	
  Remarks:
  	None.
  *****************************************************************************/
static INT8 WFPowerToAppPower(UINT8 wfPower)
{
    /* MRF24WB0M returns 0 to 128 where 64 is 0.0 dB and each step is 0.5 dB */
    return  (((INT8)wfPower - WF_ZERO_DB_VALUE) / 2);         
}  

/*******************************************************************************
  Function:	
    static INT8 WFPowerToAppPower(UINT8 wfPower)

  Summary:
    Converts application Tx Power value to MRF24WB0M Tx power level.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    appPower - Value from the host application indicating the power level.
  Returns:
  	A UINT8 of the converted power level.
  	
  Remarks:
  	None.
  *****************************************************************************/
static UINT8 AppPowerToWFPower(INT8 appPower)
{
    return ((WF_ZERO_DB_VALUE + (appPower * 2)));
}       

/*******************************************************************************
  Function:	
    void WF_ThrottleTableEnable()

  Summary:
    Directs the MRF24WB0M to use the Tx Throttle Table.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    None.

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_ThrottleTableEnable()
{
    UINT8 msgByte;
    
    msgByte = TX_THOTTLE_ENABLE_BIT_MASK;
    SendSetParamMsg(PARAM_TX_THROTTLE_TABLE_ON_OFF, &msgByte, sizeof(msgByte)); 
}

/*******************************************************************************
  Function:	
    void WF_ThrottleTableDisable(UINT8 bitRate)

  Summary:
    Directs the MRF24WB0M to not use the Tx Throttle Table, and instead use the 
    input data rate at max Tx power.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    bitRate -- Desired bit rate.  Can be either:
               * WF_ONE_MBIT_TX_RATE
               * WF_TWO_MBIT_TX_RATE

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_ThrottleTableDisable(UINT8 bitRate)
{
    UINT8 msgBuf[1];

    WF_ASSERT( (bitRate == WF_ONE_MBIT_TX_RATE) || (bitRate == WF_TWO_MBIT_TX_RATE) )

    msgBuf[0] = 0;  /* set LSB to 0, disabling throttle table */
    
    /* fill in message byte with desired bit rate (in the upper 4 bits) */
    if (bitRate == WF_ONE_MBIT_TX_RATE)
    {
        msgBuf[0] |= (0x02 << 4);  /* 0x02 * 500kbps = 1mbps */
    }
    else
    {
        msgBuf[0] |= (0x04 << 4);  /* 0x04 * 500kbps = 2mbps */
    }        

    SendSetParamMsg(PARAM_TX_THROTTLE_TABLE_ON_OFF, msgBuf, sizeof(msgBuf)); 
}

/*******************************************************************************
  Function:	
    void WF_ThrottleTableGetState(BOOL *p_state, UINT8 *p_bitRate)

  Summary:
    Retrieves the current state of the MRF24WB0M Throttle Table.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    p_state -- pointer to where state will be written.  TRUE if the Tx Throttle 
               Table is enabled, else FALSE.
    bitRate -- only valid if *p_state is FALSE.  Indicates the bit rate being 
               used by the MRF24WB0M (WF_ONE_MBIT_TX_RATE or 
               WF_TWO_MBIT_TX_RATE).

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/
void WF_ThrottleTableGetState(BOOL *p_state, UINT8 *p_bitRate)
{
    UINT8 msgByte;
    
    SendGetParamMsg(PARAM_TX_THROTTLE_TABLE_ON_OFF, &msgByte, sizeof(msgByte)); 
	
	/* if throttle table is enabled */
	if ((msgByte & TX_THOTTLE_ENABLE_BIT_MASK) > 0)
	{
    	*p_state = TRUE;
    	*p_bitRate = 0xff;  /* not applicable, but give it a known value */
    }   
    /* else throttle table is disabled (upper 4 bits contain bit rate) */	
    else
    {
    	*p_state = FALSE;
        /* convert the message bit rate value to the API bit rate value.  If upper 4 bits equal to 2 then 1mbps, else upper */
        /* 4 bits are equal to 4, indicating 2mbps.                                                                         */
    	if ( (msgByte >> 4) == 0x02)
    	{
        	*p_bitRate = WF_ONE_MBIT_TX_RATE;
        }   	
        else
        {
            *p_bitRate = WF_TWO_MBIT_TX_RATE;
        }    
    }    
}    
    
/*******************************************************************************
  Function:	
    void WF_TxPowerSetMinMax(INT8 minTxPower, INT8 maxTxPower)

  Summary:
    Sets the Tx min and max power on the MRF24WB0M.

  Description:
    After initialization the MRF24WB0M max Tx power is determined by a 
    factory-set value.  This function can set a different minimum and maximum 
    Tx power levels.  However, this function can never set a maximum Tx power 
    greater than the factory-set value, which can be read via 
    WF_TxPowerGetFactoryMax(). 

    If the Tx Throttle Table is used, Tx power levels will be clipped, if 
    needed, by the values set in this function.  In other words, values set here 
    will override values in the Tx Throttle Table to ensure that Tx power is 
    within the min/max range.

  Precondition:
  	MACInit must be called first.

  Parameters:
    minTxPower -- desired minTxPower (-10 to 10dB) 
    maxTxPower -- desired maxTxPower (-10 to 10dB)

  Returns:
  	None.
  	
  Remarks:
  	No conversion of units needed, input to MRF24WB0M is in dB.
  *****************************************************************************/
void WF_TxPowerSetMinMax(INT8 minTxPower, INT8 maxTxPower)
{
    INT8  factoryMaxPower;
    UINT8 msgData[4];  /* need to input to chip two signed 16-bit values, max power followed by min power */
    INT16 max = (INT16)maxTxPower;
    INT16 min = (INT16)minTxPower;
    
    WF_ASSERT(minTxPower <= maxTxPower);

    WF_TxPowerGetFactoryMax(&factoryMaxPower);
    WF_ASSERT(maxTxPower <= factoryMaxPower); /* cannot set max tx power greater than factor-set max tx power */
    
    msgData[0] = (INT8)(max >> 8);      /* msb of max power */
    msgData[1] = (INT8)(max & 0xff);    /* lsb of max power */

    msgData[2] = (INT8)(min >> 8);      /* msb of min power */
    msgData[3] = (INT8)(min & 0xff);    /* lsb of min power */
    
    SendSetParamMsg(PARAM_TX_POWER, msgData, sizeof(msgData)); 
}

/*******************************************************************************
  Function:	
    void WF_TxPowerGetMinMax(INT8 *p_minTxPower, INT8 *p_maxTxPower)

  Summary:
    Gets the Tx min and max power on the MRF24WB0M.

  Description:
    After initialization the MRF24WB0M max Tx power is determined by a 
    factory-set value.  This function can set a different minimum and maximum 
    Tx power levels.  However, this function can never set a maximum Tx power 
    greater than the factory-set value, which can be read via 
    WF_TxPowerGetFactoryMax(). 

    If the Tx Throttle Table is used, Tx power levels will be clipped, if 
    needed, by the values set in this function.  In other words, values set here 
    will override values in the Tx Throttle Table to ensure that Tx power is 
    within the min/max range.

  Precondition:
  	MACInit must be called first.

  Parameters:
    p_minTxPower -- pointer to location to write the minTxPower
    p_maxTxPower -- pointer to location to write the maxTxPower

  Returns:
  	None.
  	
  Remarks:
  	No conversion of units needed, input to MRF24WB0M is in dB.
  *****************************************************************************/ 
void WF_TxPowerGetMinMax(INT8 *p_minTxPower, INT8 *p_maxTxPower)
{
    UINT8 msgData[6];
    INT16 tmp;
    
    SendGetParamMsg(PARAM_TX_POWER, msgData, sizeof(msgData)); 

    /* max tx power is a signed 16-bit value stored in the [1:0] msg data */
    tmp = ((INT16)(msgData[0]) << 8);
    tmp |= (INT16)msgData[1];
    *p_maxTxPower = (INT8)tmp;
    
    /* min tx power is a signed 16-bit value stored in the [3:2] msg data */
    tmp = ((INT16)(msgData[2]) << 8);
    tmp |= (INT16)msgData[3];
    *p_minTxPower = (INT8)tmp;
    
}
  
/*******************************************************************************
  Function:	
    void WF_TxPowerGetFactoryMax(INT8 *p_factoryMaxTxPower)

  Summary:
    Retrieves the factory-set max Tx power from the MRF24WB0M.

  Description:

  Precondition:
  	MACInit must be called first.

  Parameters:
    p_factoryMaxTxPower -- desired maxTxPower (-10 to 10dB), in 1dB steps

  Returns:
  	None.
  	
  Remarks:
  	None.
  *****************************************************************************/  
void WF_TxPowerGetFactoryMax(INT8 *p_factoryMaxTxPower)
{
    UINT8 msgData[2];

    /* read max and min factory-set power levels */
    SendGetParamMsg(PARAM_FACTORY_SET_TX_MAX_POWER, msgData, sizeof(msgData)); 

    /* msgData[0] = max power, msgData[1] = min power */
    *p_factoryMaxTxPower = msgData[0];  
}
    
    
    
#endif /* WF_CS_TRIS && WF_USE_TX_POWER_CONTROL_FUNCTIONS */
