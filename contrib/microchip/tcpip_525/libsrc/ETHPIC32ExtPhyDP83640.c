/*********************************************************************
 *
 *          National DP83640 PHY API for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        ETHPIC32ExtPhyDP83640.c
 * Dependencies:
 * Processor:       PIC32
 *
 * Complier:        MPLAB C32
 *                  MPLAB IDE
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright � 2009 Microchip Technology Inc.  All rights reserved.
 * 
 * Microchip licenses the Software for your use with Microchip microcontrollers
 * and Microchip digital signal controllers pursuant to the terms of the
 * Non-Exclusive Software License Agreement accompanying this Software.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION,
 * ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS
 * FOR A PARTICULAR PURPOSE.
 * MICROCHIP AND ITS LICENSORS ASSUME NO RESPONSIBILITY FOR THE ACCURACY,
 * RELIABILITY OR APPLICATION OF THE SOFTWARE AND DOCUMENTATION.
 * IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED
 * UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH
 * OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL,
 * SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS
 * OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,
 * SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED
 * TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *
 * $Id: $
 ********************************************************************/

/** 
	@file ETHPIC32ExtPhyDP83640.c
	@brief Microchip TCPIP stack. External PHY functions.
	@author Dario Di Stefano, Evidence Srl
	@date 2010
	@note Added check on __USE_PHY_DP83640__ for compiling purpose.
*/ 
 
#ifdef __USE_PHY_DP83640__

#include <plib.h>


// Compile only for PIC32MX with Ethernet MAC interface (must not have external ENCX24J600, ENC28J60, or ZG2100M hardware defined)
#if defined(__PIC32MX__) && defined(_ETH) && !defined(ENC100_INTERFACE_MODE) && !defined(ENC_CS_TRIS) && !defined(ZG_CS_TRIS)

#include "TCPIP_Stack/ETHPIC32ExtPhy.h"

#include "HardwareProfile.h"

#include "TCPIP_Stack/ETHPIC32ExtPhyDP83640.h"



/****************************************************************************
 *                 interface functions
 ****************************************************************************/


/****************************************************************************
 * Function:        EthPhyConfigureMII
 *
 * PreCondition:    - Communication to the PHY should have been established.
 *
 * Input:           cFlags - the requested open flags: ETH_PHY_CFG_RMII/ETH_PHY_CFG_MII
 *
 * Output:          ETH_RES_OK - success,
 *                  an error code otherwise
 *
 *
 * Side Effects:    None
 *
 * Overview:        This function configures the PHY in one of MII/RMII operation modes.
 *
 * Note:            None
 *****************************************************************************/
eEthRes EthPhyConfigureMII(eEthPhyCfgFlags cFlags)
{
	unsigned short	phyReg;
	
	// RMII_BYPASS is in page 0
	EthMIIMWriteReg(PHY_REG_PAGESEL, PHY_ADDRESS, 0);
	
	phyReg=EthMIIMReadReg(PHY_REG_RMII_BYPASS, PHY_ADDRESS);
	
	if(cFlags&ETH_PHY_CFG_RMII)
	{
		phyReg|=_RMIIBYPASS_RMII_MODE_MASK;
		phyReg&=~_RMIIBYPASS_RMII_REV1_0_MASK;		// use RMII 1.2
	}
	else
	{
		phyReg&=~(_RMIIBYPASS_RMII_MODE_MASK);	// MII
	}
	
	EthMIIMWriteReg(PHY_REG_RMII_BYPASS, PHY_ADDRESS, phyReg);	// update the RMII and Bypass Register
	

	return ETH_RES_OK;	

}


/****************************************************************************
 * Function:        EthPhyConfigureMdix
 *
 * PreCondition:    - Communication to the PHY should have been established.
 *
 * Input:           oFlags - the requested open flags: ETH_OPEN_MDIX_AUTO, ETH_OPEN_MDIX_NORM/ETH_OPEN_MDIX_SWAP
 *
 * Output:          ETH_RES_OK - success,
 *                  an error code otherwise
 *
 *
 * Side Effects:    None
 *
 * Overview:        This function configures the MDIX mode for the PHY.
 *
 * Note:            None
 *****************************************************************************/
eEthRes EthPhyConfigureMdix(eEthOpenFlags oFlags)
{
	unsigned short	phyReg;

	// PHY_CTRL is in page 0
	EthMIIMWriteReg(PHY_REG_PAGESEL, PHY_ADDRESS, 0);	

	phyReg=EthMIIMReadReg(PHY_REG_PHY_CTRL, PHY_ADDRESS);

	if(oFlags&ETH_OPEN_MDIX_AUTO)
	{	// enable Auto-MDIX
		phyReg|=_PHYCTRL_MDIX_EN_MASK;
	}
	else
	{	// no Auto-MDIX
		phyReg&=~(_PHYCTRL_MDIX_EN_MASK);	// disable Auto-MDIX
	       if(oFlags&ETH_OPEN_MDIX_SWAP)
	       {
		       phyReg|=_PHYCTRL_FORCE_MDIX_MASK;	// swap
	       }
	       else
	       {
		       phyReg&=~(_PHYCTRL_FORCE_MDIX_MASK);	// normal
	       }
	}
	
	EthMIIMWriteReg(PHY_REG_PHY_CTRL, PHY_ADDRESS, phyReg);	

	return ETH_RES_OK;	

}

/****************************************************************************
 * Function:        EthPhyMIIMAddress
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          PHY MIIM address
 *
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the address the PHY uses for MIIM transactions
 *
 * Note:            None
 *****************************************************************************/
unsigned int EthPhyMIIMAddress(void)
{
	return PHY_ADDRESS;
}


/****************************************************************************
 * Function:        EthPhyMIIMClock
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          PHY MIIM clock, Hz
 *
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the maximum clock frequency that the PHY can use for the MIIM transactions
 *
 * Note:            None
 *****************************************************************************/
unsigned int EthPhyMIIMClock(void)
{
	return 25000000;		//  25 MHz max clock supported
}


#endif	// defined(__PIC32MX__) && defined(_ETH)

#endif //#ifdef __USE_PHY_DP83640__


