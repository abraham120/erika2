/********************************************************************
* FileName:		Security.h
* Dependencies: none
* Processor:	PIC18, PIC24F, PIC24H, dsPIC30, dsPIC33
*               tested with 18F4620, dsPIC33FJ256GP710	
* Hardware:		PICDEM Z, Explorer 16, PIC18 Explorer
* Complier:     Microchip C18 v3.30 or higher
*				Microchip C30 v2.03 or higher
*               Microchip C32 v1.02 or higher	
* Company:		Microchip Technology, Inc.
*
* Copyright and Disclaimer Notice
*
* Copyright © 2007-2009 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy and distribute 
* Software only when embedded on a Microchip microcontroller or digital 
* signal controller and used with a Microchip radio frequency transceiver, 
* which are integrated into your product or third party product (pursuant 
* to the terms in the accompanying license agreement).   
*
* You should refer to the license agreement accompanying this Software for 
* additional information regarding your rights and obligations.
*
* SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY 
* KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY 
* WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A 
* PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE 
* LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, 
* CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY 
* DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO 
* ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, 
* LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, 
* TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT 
* NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*
*********************************************************************
* File Description:
*
*  Defines configurations and interfaces for security module
*
* Change History:
*  Rev   Date         Description
*  2.0   4/15/2009    MiMAC and MiApp revision
*  2.1   06/20/2009   Add LCD support
********************************************************************/

#ifndef __SECURITY_H
    #define __SECURITY_H

    #include "Transceivers/Transceivers.h"

    #if defined(SOFTWARE_SECURITY)
    
        /******************************************************************/
        // XTEA_128 or XTEA_64 are used to choose the XTEA implementation
        // of the MiMAC security module. XTEA-128 is the standard XTEA 
        // version, which is 64bit block cipher with 128bit key. XTEA-64 is 
        // the modified version, which is 32bit block cipher with 64bit key.
        // XTEA-64 is developed so that Microchip can ship the security
        // engine freely under US export control regulation. 
        // XTEA-64 is available in the MiMAC implementation for free download.
        // To receive XTEA-128, customer must place a valid purchase order via
        // Microchip-Direct or other means to follow US export control 
        // regulation.
        /*****************************************************************/ 
        //#define XTEA_128
        #define XTEA_64
        
        /******************************************************************/
        // XTEA_ROUND is used to defne the total rounds that XTEA engine 
        // applies. XTEA_ROUND can be used to fine tune the strength of
        // the security engine. The more rounds applied, the more strength 
        // for the XTEA engine, and more system resources required.
        // General speaking, for security strength of XTEA-128 security 
        // engine, 8 rounds are minimal, 16 are fine and 32 are considered very
        // secure. For the same rounds, XTEA-128 is more secured than 
        // XTEA-64, because of longer security key and cipher block size.
        /******************************************************************/    
        #define XTEA_ROUND  32

        #define SEC_LEVEL_CTR           0
        #define SEC_LEVEL_CBC_MAC_16    1
        #define SEC_LEVEL_CBC_MAC_32    2
        #define SEC_LEVEL_CBC_MAC_64    3
        #define SEC_LEVEL_CCM_16        4
        #define SEC_LEVEL_CCM_32        5
        #define SEC_LEVEL_CCM_64        6

        #if defined(XTEA_128)
            #define BLOCK_SIZE 8
            #define BLOCK_UNIT DWORD
            #define KEY_SIZE 16
        #elif defined(XTEA_64)
            #define BLOCK_SIZE 4
            #define BLOCK_UNIT WORD
            #define KEY_SIZE 8
        #endif
        
        #if SECURITY_LEVEL == SEC_LEVEL_CTR
            #define SEC_MIC_LEN     0
        #elif SECURITY_LEVEL == SEC_LEVEL_CBC_MAC_16
            #define SEC_MIC_LEN     2
        #elif SECURITY_LEVEL == SEC_LEVEL_CBC_MAC_32
            #define SEC_MIC_LEN     4
        #elif SECURITY_LEVEL == SEC_LEVEL_CBC_MAC_64
            #define SEC_MIC_LEN     8
        #elif SECURITY_LEVEL == SEC_LEVEL_CCM_16
            #define SEC_MIC_LEN     2
        #elif SECURITY_LEVEL == SEC_LEVEL_CCM_32
            #define SEC_MIC_LEN     4
        #elif SECURITY_LEVEL == SEC_LEVEL_CCM_64
            #define SEC_MIC_LEN     8
        #endif
        
        
        extern ROM const unsigned char mySecurityKey[];

        void CTR(BYTE *text, BYTE len, BYTE *key, BYTE *nounce);
        void CBC_MAC(BYTE *text, BYTE len, BYTE *key, BYTE *MIC);
        void CCM_Enc(BYTE *text, BYTE headerLen, BYTE payloadLen, BYTE *key);
        BOOL CCM_Dec(BYTE *text, BYTE headerLen, BYTE payloadLen, BYTE *key);
    
    #endif

#endif

