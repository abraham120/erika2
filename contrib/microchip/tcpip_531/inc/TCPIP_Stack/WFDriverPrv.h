/******************************************************************************

 MRF24WB0M Driver Internal use
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24WB0M WiFi controller
  -Reference: MRF24WB0M Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WFDriverPrv.h
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
 KO                 31 Oct 2008 Port to PIC24F and PIC32 for TCP/IP stack v4.52
 KH                 27 Jan 2010 Updated for MRF24WB0M
******************************************************************************/

#ifndef _WFDRIVERPRV_H_
#define _WFDRIVERPRV_H_

/*
*********************************************************************************************************
*                                           DEFINES                               
*********************************************************************************************************
*/

/*--------------------*/
/* Endianness defines */
/*--------------------*/
#define WF_BIG_ENDIAN                   (0)
#define WF_LITTLE_ENDIAN                (1)

/* Indicate whether the Host CPU is big-endian or little-endian */
#define HOST_CPU_ENDIANNESS                 WF_LITTLE_ENDIAN    /* WF_BIG_ENDIAN or WF_LITTLE_ENDIAN */


/*-------------------*/
/* Endianness Macros */
/*-------------------*/
/* if the Host CPU is Little Endian, which does not match the MRF24WB0M */
#if (HOST_CPU_ENDIANNESS == WF_LITTLE_ENDIAN)
    
    /* 32-bit data type conversion */
    #define HTOWFL(a) (((a & 0x000000ff) << 24) | ((a & 0x0000ff00) << 8) | ((a & 0x00ff0000) >> 8) | ((a & 0xff000000) >> 24))
    #define WFTOHL(a) HTOWFL(a)

    /* 16-bit data type conversion */
    #define HSTOWFS(a) (((a) << 8) | ((a) >> 8))
    #define WFSTOHS(a) HSTOWFS(a)
    
/* else Host CPU is Big-Endian, which matches the MRF24WB0M */
#else
    #define HTOWFL(a)   (a)
    #define WFTOHL(a)   (a)    
    #define HSTOWFS(a)  (a)
    #define WFSTOHS(a)  (a)
#endif

/*------------*/
/* Endianness */
/*------------*/
/* ensure that endianness has been defined */
#if (HOST_CPU_ENDIANNESS != WF_LITTLE_ENDIAN) && (HOST_CPU_ENDIANNESS != WF_BIG_ENDIAN)
#error Must define HOST_CPU_ENDIANNESS to either WF_LITTLE_ENDIAN or WF_BIG_ENDIAN
#endif



#define WF_SetCE_N(level)                                           \
    /* configure I/O as ouput         */                            \
    WF_HIBERNATE_TRIS = 0;                                          \
    /* set pin to desired level       */                            \
    WF_HIBERNATE_IO   = level    

#define WF_SetRST_N(level)                                          \
    /* configure the I/O as an output   */                          \
    WF_RESET_TRIS = 0;                                              \
    /* set pin to desired level         */                          \
    WF_RESET_IO   = level    


/* SPI Tx Message Types */
#define WF_DATA_REQUEST_TYPE            ((UINT8)1)
#define WF_MGMT_REQUEST_TYPE            ((UINT8)2)

/* SPI Rx Message Types */
#define WF_DATA_TX_CONFIRM_TYPE         ((UINT8)1)
#define WF_MGMT_CONFIRM_TYPE            ((UINT8)2)
#define WF_DATA_RX_INDICATE_TYPE        ((UINT8)3)
#define WF_MGMT_INDICATE_TYPE           ((UINT8)4)

/* SPI Tx/Rx Data Message Subtypes */
#define WF_STD_DATA_MSG_SUBTYPE         ((UINT8)1)
#define WF_NULL_DATA_MSG_SUBTYPE        ((UINT8)2)
/* reserved value                       ((UINT8)3) */
#define WF_UNTAMPERED_DATA_MSG_SUBTYPE  ((UINT8)4)


#define WF_TX_DATA_MSG_PREAMBLE_LENGTH  ((UINT8)3)

#define WF_READ_REGISTER_MASK           ((UINT8)(0x40))
#define WF_WRITE_REGISTER_MASK          ((UINT8)(0x00))


/*--------------------------------*/
/* MRF24WB0M 8-bit Host Registers */
/*--------------------------------*/
#define WF_HOST_INTR_REG            ((UINT8)(0x01))  /* 8-bit register containing 1st level interrupt bits. */
#define WF_HOST_MASK_REG            ((UINT8)(0x02))  /* 8-bit register containing 1st level interrupt mask. */

/*---------------------------------*/
/* MRF24WB0M 16-bit Host Registers */
/*---------------------------------*/
#define WF_HOST_RAW0_CTRL1_REG      ((UINT16)(0x26))
#define WF_HOST_RAW0_STATUS_REG     ((UINT16)(0x28))
#define WF_HOST_RAW1_CTRL1_REG      ((UINT16)(0x2a))
#define WF_HOST_INTR2_REG           ((UINT16)(0x2d)) /* 16-bit register containing 2nd level interrupt bits */
#define WF_HOST_INTR2_MASK_REG      ((UINT16)(0x2e))
#define WF_HOST_WFIFO_BCNT0_REG     ((UINT16)(0x2f)) /* 16-bit register containing available write size for fifo 0 (data)   */
                                                     /* (LS 12 bits contain the length)                                     */
                                                       
#define WF_HOST_WFIFO_BCNT1_REG     ((UINT16)(0x31)) /* 16-bit register containing available write size for fifo 1 (mgmt)   */
                                                     /* (LS 12 bits contain the length)                                     */

#define WF_HOST_RFIFO_BCNT0_REG     ((UINT16)(0x33)) /* 16-bit register containing number of bytes in read fifo 0 (data rx) */
                                                     /* (LS 12 bits contain the length)                                     */
#define WF_HOST_RESET_REG           ((UINT16)(0x3c))
#define WF_HOST_RESET_MASK          ((UINT16)(0x0001))
                                                       
#define WF_PSPOLL_H_REG             ((UINT16)(0x3d)) /* 16-bit register used to control low power mode                      */
#define WF_INDEX_ADDR_REG           ((UINT16)(0x3e)) /* 16-bit register to move the data window                             */
#define WF_INDEX_DATA_REG           ((UINT16)(0x3f)) /* 16-bit register to read or write address-indexed register           */

/*----------------------------------------------------------------------------------------*/
/* MRF24WB0M registers accessed via the WF_INDEX_ADDR_REG and WF_INDEX_DATA_REG registers */
/*----------------------------------------------------------------------------------------*/
#define WF_HW_STATUS_REG            ((UINT16)(0x2a)) /* 16-bit read only register providing hardware status bits */
#define WF_CONFIG_CTRL0_REG         ((UINT16)(0x2e)) /* 16-bit register used to initiate Hard reset              */
#define WF_LOW_POWER_STATUS_REG     ((UINT16)(0x3e)) /* 16-bit register read to determine when low power is done */

/* This bit mask is used in the HW_STATUS_REG to determine */
/* when the MRF24WB0M has completed its hardware reset.       */
/*  0 : MRF24WB0M is in reset                                 */
/*  1 : MRF24WB0M is not in reset                             */
#define WF_HW_STATUS_NOT_IN_RESET_MASK ((UINT16)(0x1000)) 

/* Definitions represent individual interrupt bits for the 8-bit host interrupt registers */
/*  WF_HOST_INTR_REG and WF_HOST_MASK_REG                                                 */
#define WF_HOST_INT_MASK_INT2               ((UINT8)(0x01))
#define WF_HOST_INT_MASK_FIFO_1_THRESHOLD   ((UINT8)(0x80))
#define WF_HOST_INT_MASK_FIFO_0_THRESHOLD   ((UINT8)(0x40))
#define WF_HOST_INT_MASK_RAW_1_INT_0        ((UINT8)(0x04))
#define WF_HOST_INT_MASK_RAW_0_INT_0        ((UINT8)(0x02))
#define WF_HOST_INT_MASK_ALL_INT            ((UINT8)(0xff))

/* Bit mask for all interrupts in the level 2 16-bit interrupt register */
#define WF_HOST_2_INT_MASK_ALL_INT          ((UINT16)(0xffff))

/* these definitions are used in calls to enable and
 * disable interrupt bits. */
#define WF_INT_DISABLE ((UINT8)0)
#define WF_INT_ENABLE  ((UINT8)1)

#define WF_LOW_POWER_MODE_ON            (1)
#define WF_LOW_POWER_MODE_OFF           (0)

#if defined(WF_USE_POWER_SAVE_FUNCTIONS)
    void EnsureWFisAwake(void);
    void WFConfigureLowPowerMode(UINT8 action);    
    BOOL WFisPsPollEnabled(void);
    BOOL WFIsPsPollActive(void);
#else
    #define EnsureWFisAwake()         
    #define WFConfigureLowPowerMode(action)     
#endif    



#define WF_MAC_ADDRESS_LENGTH            (6)

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES                               
*********************************************************************************************************
*/

/* tComContext - Used by the COM layer to manage State information */
typedef struct
{
	volatile UINT8 rawInterrupt;
	BOOL           waitingForRawMoveCompleteInterrupt;
} tRawMoveState;

extern tRawMoveState RawMoveState;


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES                               
*********************************************************************************************************
*/

void    WFHardwareInit(void);
UINT16  Read16BitWFRegister(UINT8 regId);
void    Write16BitWFRegister(UINT8 regId, UINT16 value);
UINT8   Read8BitWFRegister(UINT8 regId);
void    Write8BitWFRegister(UINT8 regId, UINT8 value);
void    WriteWFArray(UINT8 regId, UINT8 *pBuf, UINT16 length);
void    WriteWFROMArray(UINT8 regId, ROM UINT8 *pBuf, UINT16 length);
void    ReadWFArray(UINT8  regId, UINT8 *pBuf, UINT16 length);

BOOL WFisConnected(void);
void SetLogicalConnectionState(BOOL state);
UINT8 GetEventNotificationMask(void);



#endif /*_WFDRIVERPRV_H_ */
