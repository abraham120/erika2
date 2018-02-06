/** 
* @file 	enc28j60.c
* @brief 	ENC28J60 library (can be used with LWIP)
			This file is taken from Microchip TCPIP stack. 
* @author 	Dario Di Stefano
* @version 	see Microchip documentation
* @date 	2010-07-12
*/

/** 
* \mainpage ENC28J60 driver 
*
* \section intro_sec 	ENC28J60 library was written starting from
* 						the code written by Howard Schlunder for the Microchip stack. 
*/

/**
 *********************************************************************
 *
 *  Medium Access Control (MAC) Layer for Microchip ENC28J60
 *  Module for Microchip TCP/IP Stack
 *   -Provides access to ENC28J60 Ethernet controller
 *   -Reference: ENC28J60 Data sheet, IEEE 802.3 Standard
 *
 *********************************************************************
 * FileName:        ENC28J60.c
 * Dependencies:    ENC28J60.h
 *                  MAC.h
 *                  string.h
 *                  StackTsk.h
 *                  Helpers.h
 *                  Delay.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 * Other copyrights:
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 * Copyright (C) 2010  Evidence Srl
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder     6/28/04 Original
 * Howard Schlunder     10/8/04 Cleanup
 * Howard Schlunder     10/19/04 Small optimizations and more cleanup
 * Howard Schlunder     11/29/04 Added Set/GetCLKOUT
 * Howard Schlunder     12/23/05 Added B1 silicon errata workarounds
 * Howard Schlunder     1/09/06 Added comments and minor mods
 * Howard Schlunder     1/18/06 Added more silicon errata workarounds
 * Howard Schlunder     6/16/06 Synchronized with PIC18F97J60 code
 * Howard Schlunder     7/17/06 Updated TestMemory() for C30
 * Howard Schlunder     8/07/06 Added SetRXHashTableEntry() function
 * Dario Di Stefano		12/07/10 Names of functions modified, 
 * 									code adapted for Erika Enterprise porting,
 * 									code adapted for usage with LWIP.   
********************************************************************
 */

#define __ENC28J60_C

#include "enc28j60.h"
#include "enc28j60_debug.h"
#include "enc28j60_time_debug.h"
#include "string.h"

void EE_enc28j60_handler(int level)
{
	EE_enc28j60_hal_handler(level);
}

/**
 * Variables used by Erika ENC28j60 debug functions. 
 */
#ifdef __ENC28J60_DEBUG__
uint8_t ee_enc28j60_db_msg[ENC28J60_STRING_MAXSIZE];
uint8_t enc28j60_debug_initialized = 0;
#endif

/**
 * Variables used by Erika ENC28j60 time-debug functions. 
 */
#ifdef __ENC28J60_TIME_DEBUG__
EE_UINT32 enc28j60_ts_buffer[ENC28J60_TS_BUFFER_SIZE];
#endif

/**
 * @brief ENC28J60 debug initialization function.
 *
 * This function configures a console for ENC28J60 serial debug. 
 *
 * @return Initialization result (1 ok, -1 failed).
 */
int8_t EE_enc28j60_debug_init(void)
{
	#ifdef __ENC28J60_DEBUG__
	if(enc28j60_debug_initialized==1)
		return 1;
		
	console_descriptor_t *des = NULL;
	
	#ifdef __ENC28J60_DEBUG_SERIAL__ 
	des = console_serial_config(ENC28J60_DEBUG_SERIAL_PORT, ENC28J60_DEBUG_SERIAL_BAUDRATE, ENC28J60_DEBUG_SERIAL_OPT);
	#endif
	
	if (des == NULL)
		return -1;
	if (console_init(ENC28J60_DEBUG_PORT, des) < 0)
		return -1;
		
	enc28j60_debug_initialized = 1;
	return console_open(ENC28J60_DEBUG_PORT);
	
	#else	/* ENC28J60_DEBUG */
	
	return 1;
	#endif 	/* ENC28J60_DEBUG */
}

/**
 * A header appended at the start of all RX frames by the hardware
 */
typedef struct  __attribute__((aligned(2), packed))
{
    WORD            NextPacketPointer;
    RXSTATUS        StatusVector;

    mac_addr        DestMACAddr;
    mac_addr        SourceMACAddr;
    WORD_VAL        Type;
} ENC_PREAMBLE;

/**
 * A simplified structure used in the code
 * @see EE_enc28j60_read_info(BYTE* PacketCount, WORD* length)
 */
typedef struct  __attribute__((aligned(2), packed))
{
    WORD            NextPacketPointer;
    RXSTATUS        StatusVector;
} ENC_INFO;

/**
 * To store MAC address.
 */
mac_addr ee_myMACaddress; 

/**
 * Internal MAC level variables and flags.
 */								
static WORD_VAL NextPacketLocation;
static WORD_VAL CurrentPacketLocation;
static BOOL WasDiscarded;
static BYTE ENCRevID;

/**
 * NOTE:	All code in this module expects Bank 0 to be currently selected.  
 * 			If code ever changes the bank, it must restore it to Bank 0 before returning.
 */
 
#ifdef __BIG_ENDIAN__
/**
 * @brief ENC28J60 driver utility to swap bytes of the type field. (__BIG_ENDIAN__ must be defined)
 *
 * The function is used to swap bytes of the type field.
 * @param v Word to be swapped.					
 * @return A word with swapped bytes.
 */
WORD swaps_type(WORD v)
{
	return v;
}
/**
 * @brief ENC28J60 driver utility to swap bytes of the byte-count field. (__BIG_ENDIAN__ must be defined)
 *
 * The function can be used to swap bytes of the byte-count field.
 * @param v Word to be swapped.					
 * @return A word with swapped bytes.
 */
WORD swaps_bytecount(WORD v)
{
	WORD_VAL t;
	BYTE b;
	t.Val   = v;
	b       = t.v[1];
	t.v[1]  = t.v[0];
	t.v[0]  = b;
	return t.Val;
}
#else
/**
 * @brief ENC28J60 driver utility to swap bytes of the type field. (__BIG_ENDIAN__ should not be defined)
 *
 * The function is used to swap bytes of the type field.
 * @param v Word to be swapped.					
 * @return A word with swapped bytes.
 */
WORD swaps_type(WORD v)
{
	WORD_VAL t;
	BYTE b;
	t.Val   = v;
	b       = t.v[1];
	t.v[1]  = t.v[0];
	t.v[0]  = b;
	return t.Val;
}
/**
 * @brief ENC28J60 driver utility to swap bytes of the byte-count field. (__BIG_ENDIAN__ should not be defined)
 *
 * The function can be used to swap bytes of the byte-count field.
 * @param v Word to be swapped.					
 * @return A word with swapped bytes.
 */
WORD swaps_bytecount(WORD v)
{
	return v;
}
#endif

/* 	This function initializes Mico32 spi interface, Mico32 GPIO pins
	used by the driver and ENC28J60 device. */
void EE_enc28j60_init(mac_addr myMACaddress)
{
	#ifdef __ENC28J60_DEBUG__
	EE_enc28j60_debug_init();
	#endif
	
	/* Disable IRQ */
	EE_enc28j60_disable_IRQ();
	/* SPI initialization */
	EE_enc28j60_spi_init();	// SPI module configuration
	/* Release reset */
	EE_enc28j60_enable();
	/* MAC layer initialization */
	EE_enc28j60_mac_init(myMACaddress);
	/* Enable IRQ */
	EE_enc28j60_enable_IRQ();
}


/**
 * @brief ENC28J60 driver function to intialize the device.
 *
 * This function sets up all the registers in the ENC28J60 so 
 * that normal operation can begin.	
 * @param myMACaddress Ethernet address
 * @return nothing.
 */
void EE_enc28j60_mac_init(mac_addr myMACaddress)
{
    BYTE i;

	enc28j60_dbg_print("EE_enc28j60_mac_init start!\n");
	
	/* Store the mac address */
	for(i=0; i< sizeof(mac_addr); i++)
		ee_myMACaddress.v[i] = myMACaddress.v[i];
	
    /* 	RESET the entire ENC28J60, clearing all registers
		Also wait for CLKRDY to become set.
		Bit 3 in ESTAT is an unimplemented bit.  If it reads out as '1' that
		means the part is in RESET or there is something wrong with the SPI
		connection.  This loop makes sure that we can communicate with the
		ENC28J60 before proceeding. */
    do
    {
        SendSystemReset();
        i = ReadETHReg(ESTAT).Val;
    } while((i & 0x08) || (~i & ESTAT_CLKRDY));
	
    /* Start up in Bank 0 and configure the receive buffer boundary pointers
		and the buffer write protect pointer (receive buffer read pointer). */
    WasDiscarded = TRUE;
    NextPacketLocation.Val = RXSTART;

    WriteReg(ERXSTL, LOW(RXSTART));
    WriteReg(ERXSTH, HIGH(RXSTART));
    WriteReg(ERXRDPTL, LOW(RXSTOP));    /* Write low byte first */
    WriteReg(ERXRDPTH, HIGH(RXSTOP));   /* Write high byte last */
    WriteReg(ERXNDL, LOW(RXSTOP));
    WriteReg(ERXNDH, HIGH(RXSTOP));
    WriteReg(ETXSTL, LOW(TXSTART));
    WriteReg(ETXSTH, HIGH(TXSTART));

    /* Write a permanant per packet control byte of 0x00 */
    WriteReg(EWRPTL, LOW(TXSTART));
    WriteReg(EWRPTH, HIGH(TXSTART));
    MACPut(0x00);

    /* 	Enter Bank 1 and configure Receive Filters
		(No need to reconfigure - Unicast OR Broadcast with CRC checking is
		acceptable)
		Write ERXFCON_CRCEN only to ERXFCON to enter promiscuous mode */

    /* 	Promiscious mode example:
		BankSel(ERXFCON);
		WriteReg((BYTE)ERXFCON, ERXFCON_CRCEN); */

    /* Enter Bank 2 and configure the MAC. */
    BankSel(MACON1);

    /* Enable the receive portion of the MAC */
    WriteReg((BYTE)MACON1, MACON1_TXPAUS | MACON1_RXPAUS | MACON1_MARXEN);

    /* Pad packets to 60 bytes, add CRC, and check Type/Length field. */
#if defined(FULL_DUPLEX)
    WriteReg((BYTE)MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN | MACON3_FULDPX);
    WriteReg((BYTE)MABBIPG, 0x15);
#else
    WriteReg((BYTE)MACON3, MACON3_PADCFG0 | MACON3_TXCRCEN | MACON3_FRMLNEN);
    WriteReg((BYTE)MABBIPG, 0x12);
#endif

    /* 	Allow infinite deferals if the medium is continuously busy
		(do not time out a transmission if the half duplex medium is
		completely saturated with other people's data). */
    WriteReg((BYTE)MACON4, MACON4_DEFER);

    /* 	Late collisions occur beyond 63+8 bytes (8 bytes for preamble/start of frame delimiter)
		55 is all that is needed for IEEE 802.3, but ENC28J60 B5 errata for improper link pulse
		collisions will occur less often with a larger number. */
    WriteReg((BYTE)MACLCON2, 63);

    /* 	Set non-back-to-back inter-packet gap to 9.6us.  The back-to-back
		inter-packet gap (MABBIPG) is set by MACSetDuplex() which is called
		later. */
    WriteReg((BYTE)MAIPGL, 0x12);
    WriteReg((BYTE)MAIPGH, 0x0C);

    /* Set the maximum packet size which the controller will accept */
    WriteReg((BYTE)MAMXFLL, LOW(6+6+2+1500+4));  /* 1518 is the IEEE 802.3 specified limit. */
    WriteReg((BYTE)MAMXFLH, HIGH(6+6+2+1500+4)); /* 1518 is the IEEE 802.3 specified limit. */

    /* Enter Bank 3 and initialize physical MAC address registers. */
    BankSel(MAADR1);
    WriteReg((BYTE)MAADR1, myMACaddress.v[0]);
    WriteReg((BYTE)MAADR2, myMACaddress.v[1]);
    WriteReg((BYTE)MAADR3, myMACaddress.v[2]);
    WriteReg((BYTE)MAADR4, myMACaddress.v[3]);
    WriteReg((BYTE)MAADR5, myMACaddress.v[4]);
    WriteReg((BYTE)MAADR6, myMACaddress.v[5]);

    /* Disable the CLKOUT output to reduce EMI generation. */
    WriteReg((BYTE)ECOCON, 0x00);   /* Output off (0V) */
    /* WriteReg((BYTE)ECOCON, 0x01); */ /* 25.000MHz */
    /* WriteReg((BYTE)ECOCON, 0x03); */ /* 8.3333MHz (*4 with PLL is 33.3333MHz) */

    /* Get the Rev ID so that we can implement the correct errata workarounds */
    ENCRevID = ReadETHReg((BYTE)EREVID).Val;

    /* 	Disable half duplex loopback in PHY.  Bank bits changed to Bank 2 as a 
		side effect. */
    WritePHYReg(PHCON2, PHCON2_HDLDIS);

    /* Configure LEDA to display LINK status, LEDB to display TX/RX activity. */
    SetLEDConfig(0x3472);

    /* Set the MAC and PHY into the proper duplex state */
#if defined(FULL_DUPLEX)
    WritePHYReg(PHCON1, PHCON1_PDPXMD);
#elif defined(HALF_DUPLEX)
    WritePHYReg(PHCON1, 0x0000);
#else
    /* Use the external LEDB polarity to determine weather full or half duplex
		communication mode should be set. */
    {
        REG Register;
        PHYREG PhyReg;

        /* Read the PHY duplex mode. */
        PhyReg = ReadPHYReg(PHCON1);
		DuplexState = PhyReg.Val & PHCON1_PDPXMD;
        
        /* Set the MAC to the proper duplex mode. */
        BankSel(MACON3);
        Register.Val = ReadMACReg((BYTE)MACON3).Val & (~MACON3_FULDPX);
		if(DuplexState)
			Register.Val |= MACON3_FULDPX;
		
        WriteReg((BYTE)MACON3, Register.Val);

        /* 	Set the back-to-back inter-packet gap time to IEEE specified
			requirements.  The meaning of the MABBIPG value changes with the duplex
			state, so it must be updated in this function.
			In full duplex, 0x15 represents 9.6us; 0x12 is 9.6us in half duplex. */
        WriteReg((BYTE)MABBIPG, DuplexState ? 0x15 : 0x12);
    }
#endif

    BankSel(ERDPTL);        /* Return to default Bank 0 */

	#ifdef __USE_ETHERNET_IRQ__
	/* Enable interrupt generation */
	BFSReg(EIE, EIE_PKTIE);
	BFSReg(EIE, EIE_INTIE);
	enc28j60_dbg_set_msg("eie: %x\n", ReadETHReg(EIE).Val);
	enc28j60_dbg_print(ee_enc28j60_db_msg);
	#endif
	
    /* Enable packet reception */
    BFSReg(ECON1, ECON1_RXEN);
	
	enc28j60_dbg_print("EE_enc28j60_mac_init end!\n");
}

/**
 * @brief ENC28J60 driver function to check link partners.
 *
 * This function is used to check link partners.
 *  
 * @return 	Returns the PHSTAT1.LLSTAT bit. 
 * 			TRUE: 	If the PHY reports that a link partner is present
 * 			and the link has been up continuously since the last
 * 			call to MACIsLinked()
 * 			FALSE: 	If the PHY reports no link partner, or the link went
 * 			down momentarily since the last call to MACIsLinked()
 */
BOOL EE_enc28j60_mac_IsLinked(void)
{
    /* LLSTAT is a latching low link status bit.  Therefore, if the link
		goes down and comes back up before a higher level stack program calls
		MACIsLinked(), MACIsLinked() will still return FALSE.  The next
		call to MACIsLinked() will return TRUE (unless the link goes down
		again). */
    enc28j60_dbg_print("EE_enc28j60_mac_IsLinked!\n");
	/* return ReadPHYReg(PHSTAT1).PHSTAT1bits.LLSTAT; */
	return ReadPHYReg(PHSTAT1).Val & PHSTAT1_LLSTAT;
}

/**
 * @brief ENC28J60 driver function to check Ethernet transmission status.
 *
 * This function is used to check Ethernet transmission status.
 *
 * @return 	Returns the ECON1.TXRTS bit.
 * 			TRUE: 	If no Ethernet transmission is in progress.
 *			FALSE: 	If a previous transmission was started, and it has
 * 			not completed yet.  While FALSE, the data in the
 * 			transmit buffer and the TXST/TXND pointers must not
 * 			be changed.
 */
BOOL EE_enc28j60_mac_IsTxReady(void)
{
	enc28j60_dbg_print("EE_enc28j60_mac_IsTxReady!\n");
    /* return !ReadETHReg(ECON1).ECON1bits.TXRTS; */
	return !(ReadETHReg(ECON1).Val & ECON1_TXRTS);
}

/**
 * @brief ENC28J60 driver function to mark the last received packets
 *
 * This function is used to mark the last received packet (obtained using
 * MACGetHeader())as being processed and frees the buffer
 * memory associated with it.
 * Note: 	Is is safe to call this function multiple times between
 * 			MACGetHeader() calls.  Extra packets won't be thrown away
 * 			until MACGetHeader() makes it available.
 *
 * @return nothing.
 */
void EE_enc28j60_mac_discard_rx(void)
{
    WORD_VAL NewRXRDLocation;

	enc28j60_dbg_print("EE_enc28j60_mac_discard_rx start!\n");
    /* Make sure the current packet was not already discarded. */
    if(WasDiscarded)
	{
		enc28j60_dbg_print("EE_enc28j60_mac_discard_rx was discarded!\n");
        return;
    }
	WasDiscarded = TRUE;

    /* 	Decrement the next packet pointer before writing it into
		the ERXRDPT registers.  This is a silicon errata workaround.
		RX buffer wrapping must be taken into account if the
		NextPacketLocation is precisely RXSTART. */
    NewRXRDLocation.Val = NextPacketLocation.Val - 1;
    if(NewRXRDLocation.Val > RXSTOP)
    {
        NewRXRDLocation.Val = RXSTOP;
    }

    /* Decrement the RX packet counter register, EPKTCNT. */
    BFSReg(ECON2, ECON2_PKTDEC);

    /* 	Move the receive read pointer to unwrite-protect the memory used by the
		last packet.  The writing order is important: set the low byte first,
		high byte last. */
	WriteReg(ERXRDPTL, NewRXRDLocation.byte.LB);
    WriteReg(ERXRDPTH, NewRXRDLocation.byte.HB);
	
	enc28j60_dbg_print("EE_enc28j60_mac_discard_rx end!\n");
}

/**
 * @brief ENC28J60 driver function to estimate free space in RX buffer.
 *
 * This function is used to return a WORD estimate of how much 
 * RX buffer space is free at the present time.
 *                 
 * @return Free space in RX buffer.
 */ 
WORD EE_enc28j60_mac_get_FreeRxSize(void)
{
    WORD_VAL ReadPT, WritePT;
	
	enc28j60_dbg_print("EE_enc28j60_mac_get_FreeRxSize!\n");

    /* 	Read the Ethernet hardware buffer write pointer.  Because packets can be
		received at any time, it can change between reading the low and high
		bytes.  A loop is necessary to make certain a proper low/high byte pair
		is read. */
    BankSel(EPKTCNT);
    do {
        /* Save EPKTCNT in a temporary location */
        ReadPT.v[0] = ReadETHReg((BYTE)EPKTCNT).Val;

		BankSel(ERXWRPTL);
		WritePT.byte.LB = ReadETHReg(ERXWRPTL).Val;
        WritePT.byte.HB = ReadETHReg(ERXWRPTH).Val;
		BankSel(EPKTCNT);
		
    } while(ReadETHReg((BYTE)EPKTCNT).Val != ReadPT.v[0]);

    /* Determine where the write protection pointer is. */
    BankSel(ERXRDPTL);
	ReadPT.byte.LB = ReadETHReg(ERXRDPTL).Val;
    ReadPT.byte.HB = ReadETHReg(ERXRDPTH).Val;
    /*	Calculate the difference between the pointers, taking care to account
		for buffer wrapping conditions */
    if(WritePT.Val > ReadPT.Val)
    {
        return (RXSTOP - RXSTART) - (WritePT.Val - ReadPT.Val);
    }
    else if(WritePT.Val == ReadPT.Val)
    {
        return RXSIZE - 1;
    }
    else
    {
        return ReadPT.Val - WritePT.Val - 1;
    }
}

/**
 * @brief ENC28J60 driver function to get header.
 *
 * This function is used to return a WORD estimate of how much 
 * RX buffer space is free at the present time.
 * Side Effects:    Last packet is discarded if MACDiscardRx() hasn't already
 *                  been called.           
 * @param *remote Location to store the Source MAC address of the received frame.      
 * @param *type Location of a BYTE to store the constant MAC_UNKNOWN, ETHER_IP, or ETHER_ARP, 
 * representing the contents of the Ethernet type field. 
 * @param *PacketCount number of received packets.
 * @param *length length in bytes.  
 * 
 * @return 	packet pending status (TRUE: a packet was waiting, The remote, and type values are updated
 * 			FALSE: a packet was not pending, remote and type are not changed).
 */ 
BOOL EE_enc28j60_mac_get_header(mac_addr *remote, BYTE* type, BYTE* PacketCount, WORD* length)
{
    ENC_PREAMBLE header;
   
   enc28j60_dbg_print("EE_enc28j60_mac_get_header start!\n");
   
    /* Test if at least one packet has been received and is waiting. */
    BankSel(EPKTCNT);
    *PacketCount = ReadETHReg((BYTE)EPKTCNT).Val;
    BankSel(ERDPTL);
    if(*PacketCount == 0u)
	{
		enc28j60_dbg_print("EE_enc28j60_mac_get_header PacketCount=0!\n");
        return FALSE;
	}

    /* Make absolutely certain that any previous packet was discarded. */
    if(WasDiscarded == FALSE)
    {
        MACDiscardRx();
		enc28j60_dbg_print("EE_enc28j60_mac_get_header WasDiscarded==FALSE!\n");
        return FALSE;
    }

    /* Set the SPI read pointer to the beginning of the next unprocessed packet. */
    CurrentPacketLocation.Val = NextPacketLocation.Val;
	WriteReg(ERDPTL, CurrentPacketLocation.byte.LB);
    WriteReg(ERDPTH, CurrentPacketLocation.byte.HB);

    /* Obtain the MAC header from the Ethernet buffer. */
    MACGetArray((BYTE*)&header, sizeof(header));
	
	header.StatusVector.bits.ByteCount = swaps_bytecount(header.StatusVector.bits.ByteCount);
	header.NextPacketPointer = swaps_bytecount(header.NextPacketPointer);
	
	*length = header.StatusVector.bits.ByteCount;
	
    /* The EtherType field, like most items transmitted on the Ethernet medium
		are in big endian. */
    header.Type.Val = swaps_type(header.Type.Val);

    /* Validate the data returned from the ENC28J60.  Random data corruption,
		such as if a single SPI bit error occurs while communicating or a
		momentary power glitch could cause this to occur in rare circumstances. */
    if(header.NextPacketPointer > RXSTOP || ((WORD_VAL*)(&header.NextPacketPointer))->bits.b0 ||
       header.StatusVector.bits.Zero ||
       header.StatusVector.bits.CRCError ||
       header.StatusVector.bits.ByteCount > 1518u ||
       !header.StatusVector.bits.ReceiveOk)
    {
		enc28j60_dbg_print("EE_enc28j60_mac_get_header Reset!\n");
        /* Reset(); */
    }

    /* Save the location where the hardware will write the next packet to. */
    NextPacketLocation.Val = header.NextPacketPointer;

    /* Return the Ethernet frame's Source MAC address field to the caller
		This parameter is useful for replying to requests without requiring an
		ARP cycle. */
    memcpy((void*)remote->v, (void*)header.SourceMACAddr.v, sizeof(*remote));

    /* Return a simplified version of the EtherType field to the caller. */
    *type = MAC_UNKNOWN;
	if( (header.Type.byte.HB == 0x08u) &&
        ((header.Type.byte.LB == ETHER_IP) || (header.Type.byte.LB == ETHER_ARP)) )
    {
        *type = header.Type.byte.LB;
    }
	
    /* Mark this packet as discardable. */
    WasDiscarded = FALSE;
	enc28j60_dbg_print("EE_enc28j60_mac_get_header end!\n");
    return TRUE;
}

/**
 * @brief ENC28J60 driver function to put header.
 * This function is used to put the header.
 * PreCondition:    MACIsTxReady() must return TRUE.
 * Side Effects:    Last packet is discarded if MACDiscardRx() hasn't already
 * @param remote Pointer to memory which contains the destination MAC address (6 bytes)
 * @param type 	The constant ETHER_ARP or ETHER_IP, defining which
 * 				value to write into the Ethernet header's type field.
 * @param dataLen Length of the Ethernet data payload
 * Note:	Because of the dataLen parameter, it is probably
 * 			advantagous to call this function immediately before
 * 			transmitting a packet rather than initially when the
 * 			packet is first created.  The order in which the packet
 * 			is constructed (header first or data first) is not important.
 
 * @return 	nothing.
 */ 
void EE_enc28j60_mac_put_header(mac_addr *remote, WORD type, WORD dataLen, mac_addr myMACaddress)
{

	enc28j60_dbg_print("EE_enc28j60_mac_put_header start!\n");
    /* Set the SPI write pointer to the beginning of the transmit buffer (post per packet control byte). */
    WriteReg(EWRPTL, LOW(TXSTART+1));
    WriteReg(EWRPTH, HIGH(TXSTART+1));

	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    /* Calculate where to put the TXND pointer
		dataLen += (WORD)sizeof(ETHER_HEADER) + TXSTART; */
	dataLen += TXSTART; /* Please pass dataLen + sizeof_eth_addr. */
	/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */

    /* Write the TXND pointer into the registers, given the dataLen given. */
	WriteReg(ETXNDL, ((WORD_VAL*)&dataLen)->byte.LB);
    WriteReg(ETXNDH, ((WORD_VAL*)&dataLen)->byte.HB);

    /* Set the per-packet control byte and write the Ethernet destination address. */
    MACPutArray((BYTE*)remote, sizeof(*remote));

    /* Write our MAC address in the Ethernet source field. */
    MACPutArray((BYTE*)&myMACaddress, sizeof(myMACaddress));

    /* Write the appropriate Ethernet Type WORD for the protocol being used
		type can be: 	#define ETHTYPE_ARP       0x0806
						#define ETHTYPE_IP        0x0800 */
    MACPut(HIGH(type)); /* MACPut(0x08); */
    MACPut(LOW(type));  /* ETHER_IP , ETHER_ARP */
	enc28j60_dbg_print("EE_enc28j60_mac_put_header end!\n");
}

/**
 * @brief ENC28J60 driver function to flush a packet.
 * This function is used to flush a packet.
 * PreCondition:    A packet has been created by calling MACPut() and MACPutHeader().
 * Overview:        This function causes the current TX packet to be sent out on
 *                  the Ethernet medium.  The hardware MAC will take control
 *                  and handle CRC generation, collision retransmission and
 *                  other details.
 * Note:            After transmission completes (MACIsTxReady() returns TRUE),
 *                  the packet can be modified and transmitted again by calling
 *                  MACFlush() again.  Until MACPutHeader() or MACPut() is
 *                  called (in the TX data area), the data in the TX buffer
 *                  will not be corrupted.
 * @return 	nothing.
 */ 
void EE_enc28j60_mac_flush(void)
{
	enc28j60_dbg_print("EE_enc28j60_mac_flush start!\n");
    /* Reset transmit logic if a TX Error has previously occured. This is a silicon errata workaround. */
    BFSReg(ECON1, ECON1_TXRST);
    BFCReg(ECON1, ECON1_TXRST);
    BFCReg(EIR, EIR_TXERIF | EIR_TXIF);

    /* Start the transmission
		After transmission completes (MACIsTxReady() returns TRUE), the packet
		can be modified and transmitted again by calling MACFlush() again.
		Until MACPutHeader() is called, the data in the TX buffer will not be corrupted. */
    BFSReg(ECON1, ECON1_TXRTS);

    /* Revision B5 and B7 silicon errata workaround. */
    if(ENCRevID == 0x05u || ENCRevID == 0x06u)
    {
        WORD AttemptCounter = 0x0000;
		
		EE_enc28j60_write_timestamp(ENC28J60_START_MAC_FLUSH_WAIT);
        while(!(ReadETHReg(EIR).Val & (EIR_TXERIF | EIR_TXIF)) && (++AttemptCounter < 1000u));
        EE_enc28j60_write_timestamp(ENC28J60_END_MAC_FLUSH_WAIT);
		
		EE_enc28j60_write_timestamp(ENC28J60_START_MAC_FLUSH_RETX);
		if((ReadETHReg(EIR).Val & EIR_TXERIF) || (AttemptCounter >= 1000u))
        {
            WORD_VAL ReadPtrSave;
            WORD_VAL TXEnd;
            TXSTATUS TXStatus;
            BYTE i;

            /* Cancel the previous transmission if it has become stuck set. */
            BFCReg(ECON1, ECON1_TXRTS);

            /* Save the current read pointer (controlled by application). */
			ReadPtrSave.byte.LB = ReadETHReg(ERDPTL).Val;
            ReadPtrSave.byte.HB = ReadETHReg(ERDPTH).Val;

            /* Get the location of the transmit status vector. */
			TXEnd.byte.LB = ReadETHReg(ETXNDL).Val;
            TXEnd.byte.HB = ReadETHReg(ETXNDH).Val;
			TXEnd.Val++;

            /* Read the transmit status vector. */
			WriteReg(ERDPTL, TXEnd.byte.LB);
            WriteReg(ERDPTH, TXEnd.byte.HB);
            MACGetArray((BYTE*)&TXStatus, sizeof(TXStatus));
			TXStatus.bits.ByteCount = swaps_bytecount(TXStatus.bits.ByteCount);
			TXStatus.bits.BytesTransmittedOnWire = swaps_bytecount(TXStatus.bits.BytesTransmittedOnWire);

            /* Implement retransmission if a late collision occured (this can
				happen on B5 when certain link pulses arrive at the same time
				as the transmission). */
            for(i = 0; i < 16u; i++)
            {
                if((ReadETHReg(EIR).Val & EIR_TXERIF) && TXStatus.bits.LateCollision)
                {
                    /* Reset the TX logic. */
                    BFSReg(ECON1, ECON1_TXRST);
                    BFCReg(ECON1, ECON1_TXRST);
                    BFCReg(EIR, EIR_TXERIF | EIR_TXIF);

                    /* Transmit the packet again. */
                    BFSReg(ECON1, ECON1_TXRTS);
                    while(!(ReadETHReg(EIR).Val & (EIR_TXERIF | EIR_TXIF)));

                    /* Cancel the previous transmission if it has become stuck set. */
                    BFCReg(ECON1, ECON1_TXRTS);

                    /* Read transmit status vector. */
					WriteReg(ERDPTL, TXEnd.byte.LB);
                    WriteReg(ERDPTH, TXEnd.byte.HB);
                    MACGetArray((BYTE*)&TXStatus, sizeof(TXStatus));
					TXStatus.bits.ByteCount = swaps_bytecount(TXStatus.bits.ByteCount);
					TXStatus.bits.BytesTransmittedOnWire = swaps_bytecount(TXStatus.bits.BytesTransmittedOnWire);
                }
                else
                {
                    break;
                }
            }

            /* Restore the current read pointer. */
			WriteReg(ERDPTL, ReadPtrSave.byte.LB);
            WriteReg(ERDPTH, ReadPtrSave.byte.HB);
        }
		EE_enc28j60_write_timestamp(ENC28J60_END_MAC_FLUSH_RETX);
    }
	enc28j60_dbg_print("EE_enc28j60_mac_flush end!\n");
}

/**
 * @brief ENC28J60 driver function to set read pointer.
 * PreCondition:    A packet has been obtained by calling MACGetHeader() and
 *                  getting a TRUE result.
 * @param  	offset WORD specifying how many bytes beyond the Ethernet
 * 			header's type field to relocate the SPI read pointer.
 * Overview:        SPI read pointer are updated.  All calls to
 *                  MACGet() and MACGetArray() will use these new values.
 *
 * Note:            RXSTOP must be statically defined as being > RXSTART for
 *                  this function to work correctly.  In other words, do not
 *                  define an RX buffer which spans the 0x1FFF->0x0000 memory
 *                  boundary.              
 * @return 	nothing.
 */  
void EE_enc28j60_mac_set_read_ptr_inRx(WORD offset)
{
    WORD_VAL ReadPT;

	enc28j60_dbg_print("EE_enc28j60_mac_set_read_ptr_inRx start!\n");
    /*	Determine the address of the beginning of the entire packet
		and adjust the address to the desired location. */
    ReadPT.Val = CurrentPacketLocation.Val + sizeof(ENC_PREAMBLE) + offset;

    /* Since the receive buffer is circular, adjust if a wraparound is needed. */
    if(ReadPT.Val > RXSTOP)
        ReadPT.Val -= RXSIZE;

    /* Set the SPI read pointer to the new calculated value. */
    WriteReg(ERDPTL, ReadPT.byte.LB);
    WriteReg(ERDPTH, ReadPT.byte.HB);
	enc28j60_dbg_print("EE_enc28j60_mac_set_read_ptr_inRx end!\n");
}

/**
 * @brief ENC28J60 driver function to set write pointer.
 * @param  	Address Address to seek to.
 * Overview:        SPI write pointer is updated.  All calls to
 *                  MACPut() and MACPutArray() will use this new value.             
 * @return 	Old EWRPT location.
 */ 
WORD EE_enc28j60_mac_set_write_ptr(WORD address)
{
    WORD_VAL oldVal;
	enc28j60_dbg_print("EE_enc28j60_mac_set_write_ptr start!\n");

    oldVal.byte.LB = ReadETHReg(EWRPTL).Val;
    oldVal.byte.HB = ReadETHReg(EWRPTH).Val;

    /* Set the SPI write pointer to the new calculated value. */
    WriteReg(EWRPTL, ((WORD_VAL*)&address)->byte.LB);
    WriteReg(EWRPTH, ((WORD_VAL*)&address)->byte.HB);

	
	enc28j60_dbg_print("EE_enc28j60_mac_set_write_ptr end!\n");
    return oldVal.Val;
}

/**
 * @brief ENC28J60 driver function to set read pointer.
 * @param  	Address Address to seek to.
 * Overview:        SPI read pointer is updated.  All calls to
 *                  MACGet() and MACGetArray() will use this new value.             
 * @return 	Old ERDPT value
 */ 
WORD EE_enc28j60_mac_set_read_ptr(WORD address)
{
    WORD_VAL oldVal;

	enc28j60_dbg_print("EE_enc28j60_mac_set_read_ptr start!\n");
    oldVal.byte.LB = ReadETHReg(ERDPTL).Val;
    oldVal.byte.HB = ReadETHReg(ERDPTH).Val;

    /* Set the SPI write pointer to the new calculated value. */
    WriteReg(ERDPTL, ((WORD_VAL*)&address)->byte.LB);
    WriteReg(ERDPTH, ((WORD_VAL*)&address)->byte.HB);

	enc28j60_dbg_print("EE_enc28j60_mac_set_read_ptr end!\n");
    return oldVal.Val;
}

/**
 * @brief ENC28J60 driver function to calculate checksum.
 * @param 	offset Number of bytes beyond the beginning of the 
 *			Ethernet data (first byte after the type field)
 * 			where the checksum should begin.
 * @param 	len Total number of bytes to include in the checksum
 * Overview:        This function performs a checksum calculation in the MAC
 *                  buffer itself.           
 * @return 	16-bit checksum as defined by RFC 793.
 */  
WORD EE_enc28j60_mac_CalcRxChecksum(WORD offset, WORD len)
{
    WORD_VAL temp;
    WORD_VAL RDSave;
	
	enc28j60_dbg_print("EE_enc28j60_mac_CalcRxChecksum start!\n");

    /* Add the offset requested by firmware plus the Ethernet header. */
    temp.Val = CurrentPacketLocation.Val + sizeof(ENC_PREAMBLE) + offset;
    if(temp.Val > RXSTOP)       /* Adjust value if a wrap is needed. */
    {
        temp.Val -= RXSIZE;
    }

    RDSave.byte.LB = ReadETHReg(ERDPTL).Val;
    RDSave.byte.HB = ReadETHReg(ERDPTH).Val;

    WriteReg(ERDPTL, temp.byte.LB);
    WriteReg(ERDPTH, temp.byte.HB);

    temp.Val = CalcIPBufferChecksum(len);

    WriteReg(ERDPTL, RDSave.byte.LB);
    WriteReg(ERDPTH, RDSave.byte.HB);

	enc28j60_dbg_print("EE_enc28j60_mac_CalcRxChecksum end!\n");
    return temp.Val;
}

/**
 * @brief ENC28J60 driver function to calculate checksum.
 * PreCondition:    Read buffer pointer set to starting of checksum data
 * @param 	len Total number of bytes to calculate the checksum over.
 * 			The first byte included in the checksum is the byte
 * 			pointed to by ERDPT, which is updated by calls to
 * 			MACSetReadPtr(), MACGet(), MACGetArray(),
 * 			MACGetHeader(), etc.
 * Overview:        This function performs a checksum calculation in the MAC
 *                  buffer itself.  The ENC28J60 has a hardware DMA module
 *                  which can calculate the checksum faster than software, so
 *                  this function replaces the CaclIPBufferChecksum() function
 *                  defined in the helpers.c file.  Through the use of
 *                  preprocessor defines, this replacement is automatic.
 *
 * Note:            This function works either in the RX buffer area or the TX
 *                  buffer area.  No validation is done on the len parameter.        
 * @return 	16-bit checksum as defined by RFC 793.
 */   
WORD EE_enc28j60_mac_CalcIPBufferChecksum(WORD len)
{
    WORD_VAL Start;
    DWORD_VAL Checksum = {0x00000000ul};
    WORD ChunkLen;
    WORD DataBuffer[10];
    WORD *DataPtr;

	enc28j60_dbg_print("EE_enc28j60_mac_CalcIPBufferChecksum start!\n");
	
    /* Save the SPI read pointer starting address. */
    Start.byte.LB = ReadETHReg(ERDPTL).Val;
    Start.byte.HB = ReadETHReg(ERDPTH).Val;

    while(len)
    {
        /* Obtain a chunk of data (less SPI overhead compared
			to requesting one byte at a time). */
        ChunkLen = len > sizeof(DataBuffer) ? sizeof(DataBuffer) : len;
        MACGetArray((BYTE*)DataBuffer, ChunkLen);

        len -= ChunkLen;

        /* Take care of a last odd numbered data byte. */
        if(((WORD_VAL*)&ChunkLen)->bits.b0)
        {
            ((BYTE*)DataBuffer)[ChunkLen] = 0x00;
            ChunkLen++;
        }

        /* Calculate the checksum over this chunk. */
        DataPtr = DataBuffer;
        while(ChunkLen)
        {
            Checksum.Val += *DataPtr++;
            ChunkLen -= 2;
        }
    }

    /* Restore old read pointer location. */
    WriteReg(ERDPTL, Start.byte.LB);
    WriteReg(ERDPTH, Start.byte.HB);

	/* Do an end-around carry (one's complement arrithmatic). */
	Checksum.Val = (DWORD)Checksum.w[0] + (DWORD)Checksum.w[1];

    /* Do another end-around carry in case if the prior add caused a carry out. */
    Checksum.w[0] += Checksum.w[1];

	enc28j60_dbg_print("EE_enc28j60_mac_CalcIPBufferChecksum end!\n");
    /* Return the resulting checksum. */
    return ~Checksum.w[0];
}
 
/**
 * @brief ENC28J60 driver function to transfer bytes within the buffer.
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * @param destAddr 	Destination address in the Ethernet memory to
 * 					copy to.  If the MSb is set, the current EWRPT
 * 					value will be used instead.
 * @param sourceAddr 	Source address to read from.  If the MSb is
 * 						set, the current ERDPT value will be used instead.
 * @param len Number of bytes to copy                            
 *                  
 * Overview:        Bytes are asynchrnously transfered within the buffer.  Call
 *                  MACIsMemCopyDone() to see when the transfer is complete.
 * Note:            If a prior transfer is already in progress prior to
 *                  calling this function, this function will block until it
 *                  can start this transfer.
 *                  If a negative value is used for the sourceAddr or destAddr
 *                  parameters, then that pointer will get updated with the
 *                  next address after the read or write.
 * @return 	Byte read from the ENC28J60's RAM.
 */   
void EE_enc28j60_mac_MemCopyAsync(WORD destAddr, WORD sourceAddr, WORD len)
{
    WORD_VAL ReadSave, WriteSave;
    BOOL UpdateWritePointer = FALSE;
    BOOL UpdateReadPointer = FALSE;
	
	enc28j60_dbg_print("EE_enc28j60_mac_MemCopyAsync start!\n");

    if(((WORD_VAL*)&destAddr)->bits.b15)
    {
        UpdateWritePointer = TRUE;
        ((WORD_VAL*)&destAddr)->byte.LB = ReadETHReg(EWRPTL).Val;
        ((WORD_VAL*)&destAddr)->byte.HB = ReadETHReg(EWRPTH).Val;
    }
    if(((WORD_VAL*)&sourceAddr)->bits.b15)
    {
        UpdateReadPointer = TRUE;
        ((WORD_VAL*)&sourceAddr)->byte.LB = ReadETHReg(ERDPTL).Val;
        ((WORD_VAL*)&sourceAddr)->byte.HB = ReadETHReg(ERDPTH).Val;
    }

    /* Handle special conditions where len == 0 or len == 1
    The DMA module is not capable of handling those corner cases. */
    if(len <= 1u)
    {
        if(!UpdateReadPointer)
        {
            ReadSave.byte.LB = ReadETHReg(ERDPTL).Val;
            ReadSave.byte.HB = ReadETHReg(ERDPTH).Val;
        }
        if(!UpdateWritePointer)
        {
            WriteSave.byte.LB = ReadETHReg(EWRPTL).Val;
            WriteSave.byte.HB = ReadETHReg(EWRPTH).Val;
        }
        WriteReg(ERDPTL, ((WORD_VAL*)&sourceAddr)->byte.LB);
        WriteReg(ERDPTH, ((WORD_VAL*)&sourceAddr)->byte.HB);
        WriteReg(EWRPTL, ((WORD_VAL*)&destAddr)->byte.LB);
        WriteReg(EWRPTH, ((WORD_VAL*)&destAddr)->byte.HB);
        while(len--)
            MACPut(MACGet());
        if(!UpdateReadPointer)
        {
            WriteReg(ERDPTL, ReadSave.byte.LB);
            WriteReg(ERDPTH, ReadSave.byte.HB);
        }
        if(!UpdateWritePointer)
        {
            WriteReg(EWRPTL, WriteSave.byte.LB);
            WriteReg(EWRPTH, WriteSave.byte.HB);
        }
    }
    else
    {
        if(UpdateWritePointer)
        {
            WriteSave.Val = destAddr + len;
            WriteReg(EWRPTL, WriteSave.byte.LB);
            WriteReg(EWRPTH, WriteSave.byte.HB);
        }
        len += sourceAddr - 1;
        while(ReadETHReg(ECON1).Val & ECON1_DMAST);
        WriteReg(EDMASTL, ((WORD_VAL*)&sourceAddr)->byte.LB);
        WriteReg(EDMASTH, ((WORD_VAL*)&sourceAddr)->byte.HB);
        WriteReg(EDMADSTL, ((WORD_VAL*)&destAddr)->byte.LB);
        WriteReg(EDMADSTH, ((WORD_VAL*)&destAddr)->byte.HB);
        if((sourceAddr <= RXSTOP) && (len > RXSTOP)) /* && (sourceAddr >= RXSTART)) */
            len -= RXSIZE;
        WriteReg(EDMANDL, ((WORD_VAL*)&len)->byte.LB);
        WriteReg(EDMANDH, ((WORD_VAL*)&len)->byte.HB);
        BFCReg(ECON1, ECON1_CSUMEN);
        BFSReg(ECON1, ECON1_DMAST);
        if(UpdateReadPointer)
        {
            len++;
            if((sourceAddr <= RXSTOP) && (len > RXSTOP)) /* && (sourceAddr >= RXSTART)) */
                len -= RXSIZE;
            WriteReg(ERDPTL, ((WORD_VAL*)&len)->byte.LB);
            WriteReg(ERDPTH, ((WORD_VAL*)&len)->byte.HB);
        }
    }
	enc28j60_dbg_print("EE_enc28j60_mac_MemCopyAsync end!\n");
}

BOOL EE_enc28j60_mac_IsMemCopyDone(void)
{
	enc28j60_dbg_print("EE_enc28j60_mac_IsMemCopyDone!\n");
    return !(ReadETHReg(ECON1).Val & ECON1_DMAST);
}

/**
 * @brief ENC28J60 driver function to turn off the device.
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Overview:        MACPowerDown puts the ENC28J60 in low power sleep mode. In
 *                  sleep mode, no packets can be transmitted or received.
 *                  All MAC and PHY registers should not be accessed.
 *
 * Note:            If a packet is being transmitted while this function is
 *                  called, this function will block until it is it complete.
 *                  If anything is being received, it will be completed.
 * @return 	nothing.
 */    
void EE_enc28j60_mac_power_down(void)
{
	enc28j60_dbg_print("EE_enc28j60_mac_power_down start!\n");
	
    /* Disable packet reception. */
    BFCReg(ECON1, ECON1_RXEN);

    /* Make sure any last packet which was in-progress when RXEN was cleared
		is completed. */
    while(ReadETHReg(ESTAT).Val & ESTAT_RXBUSY);

    /* If a packet is being transmitted, wait for it to finish. */
    while(ReadETHReg(ECON1).Val & ECON1_TXRTS);

    /* Enter sleep mode. */
    BFSReg(ECON2, ECON2_PWRSV);
	
	enc28j60_dbg_print("EE_enc28j60_mac_power_down end!\n");
}

/**
 * @brief ENC28J60 driver function to turn on the device.
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * Overview:        MACPowerUp returns the ENC28J60 back to normal operation
 *                  after a previous call to MACPowerDown().  Calling this
 *                  function when already powered up will have no effect.
 * Note:            If a link partner is present, it will take 10s of
 *                  milliseconds before a new link will be established after
 *                  waking up.  While not linked, packets which are
 *                  transmitted will most likely be lost.  MACIsLinked() can
 *                  be called to determine if a link is established.
 * @return 	nothing.
 */  
void EE_enc28j60_mac_power_up(void)
{
	enc28j60_dbg_print("EE_enc28j60_mac_power_up start!\n");
	
    /* Leave power down mode. */
    BFCReg(ECON2, ECON2_PWRSV);

    /* Wait for the 300us Oscillator Startup Timer (OST) to time out.  This
		delay is required for the PHY module to return to an operational state. */
    while(!ReadETHReg(ESTAT).Val & ESTAT_CLKRDY);

    /* Enable packet reception. */
    BFSReg(ECON1, ECON1_RXEN);
	enc28j60_dbg_print("EE_enc28j60_mac_power_up end!\n");
}

/**
 * @brief 	ENC28J60 driver function to Set the appropriate bit in the EHT* registers to allow
 * 			packets sent to DestMACAddr to be received if the HashTable receive filter is enabled.
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 *
 * @param DestMACAddr 	6 byte group destination MAC address to allow
 *                   	through the Hash Table Filter
 *
 * Overview:        Calculates a CRC-32 using polynomial 0x4C11DB7 and then,
 *                  using bits 28:23 of the CRC, sets the appropriate bit in
 *                  the EHT* registers
 * Note:            This code is commented out to save code space on systems
 *                  that do not need this function.  Change the "#if 0" line
 *                  to "#if 1" to uncomment it.
 * @return 	nothing.
 */  
#if 0
void EE_enc28j60_mac_set_rx_hash_table_entry(mac_addr DestMACAddr)
{
    DWORD_VAL CRC = {0xFFFFFFFF};
    BYTE HTRegister;
    BYTE i, j;
	
	enc28j60_dbg_print("EE_enc28j60_mac_set_rx_hash_table_entry!\n");

    /* Calculate a CRC-32 over the 6 byte MAC address
		using polynomial 0x4C11DB7. */
    for(i = 0; i < sizeof(mac_addr); i++)
    {
        BYTE  crcnext;

        /* shift in 8 bits */
        for(j = 0; j < 8; j++)
        {
            crcnext = 0;
            if(((BYTE_VAL*)&(CRC.v[3]))->bits.b7)
                crcnext = 1;
            crcnext ^= (((BYTE_VAL*)&DestMACAddr.v[i])->bits.b0);

            CRC.Val <<= 1;
            if(crcnext)
                CRC.Val ^= 0x4C11DB7;
            /* next bit */
            DestMACAddr.v[i] >>= 1;
        }
    }

    /* CRC-32 calculated, now extract bits 28:23
		Bits 25:23 define where within the Hash Table byte the bit needs to be set
		Bits 28:26 define which of the 8 Hash Table bytes that bits 25:23 apply to. */
    i = CRC.v[3] & 0x1F;
    HTRegister = (i >> 2) + (BYTE)EHT0;
    i = (i << 1) & 0x06;
    ((BYTE_VAL*)&i)->bits.b0 = ((BYTE_VAL*)&CRC.v[2])->bits.b7;

    /* Set the proper bit in the Hash Table. */
    BankSel(EHT0);
    BFSReg(HTRegister, 1<<i);

    BankSel(ERDPTL);            /* Return to Bank 0 */
}
#endif

/**
 * @brief 	ENC28J60 driver function to read info about the received packet.
 * PreCondition:    SPI bus must be initialized (done in MACInit()).
 * @param *PacketCount number of received packets.
 * @param *length length of received packets.
 * @return 0 if a packet is pending. -1 otherwise.
 */ 
int EE_enc28j60_read_info(BYTE* PacketCount, WORD* length)
{
	ENC_INFO info;
	
	enc28j60_dbg_print("EE_enc28j60_read_info start!\n");
   
    /* Test if at least one packet has been received and is waiting. */
    BankSel(EPKTCNT);
    *PacketCount = ReadETHReg((BYTE)EPKTCNT).Val;
    BankSel(ERDPTL);
    if(*PacketCount == 0u)
	{
		enc28j60_dbg_print("EE_enc28j60_read_info PacketCount==0!\n");
        return -1;
	}
    /* Make absolutely certain that any previous packet was discarded. */
    if(WasDiscarded == FALSE)
    {
        MACDiscardRx();
		enc28j60_dbg_print("EE_enc28j60_read_info WasDiscarded==FALSE!\n");
        return -1;
    }
	
    /* Set the SPI read pointer to the beginning of the next unprocessed packet. */
    CurrentPacketLocation.Val = NextPacketLocation.Val;
	WriteReg(ERDPTL, CurrentPacketLocation.byte.LB);
    WriteReg(ERDPTH, CurrentPacketLocation.byte.HB);
	
	/* Obtain the MAC header from the Ethernet buffer. */
    MACGetArray((BYTE*)&info, sizeof(info));
	
	/* Swaps Byte count and next pointer. */
	info.StatusVector.bits.ByteCount = swaps_bytecount(info.StatusVector.bits.ByteCount);
	info.NextPacketPointer = swaps_bytecount(info.NextPacketPointer);
	*length = info.StatusVector.bits.ByteCount;
	
    /*  Validate the data returned from the ENC28J60.  Random data corruption,
		such as if a single SPI bit error occurs while communicating or a
		momentary power glitch could cause this to occur in rare circumstances. */
    if(info.NextPacketPointer > RXSTOP || ((WORD_VAL*)(&info.NextPacketPointer))->bits.b0 ||
       info.StatusVector.bits.Zero ||
       info.StatusVector.bits.CRCError ||
       info.StatusVector.bits.ByteCount > 1518u ||
       !info.StatusVector.bits.ReceiveOk)
	{
		enc28j60_dbg_print("EE_enc28j60_read_info Reset!\n");
        /* Reset(); */
    }

    /* Save the location where the hardware will write the next packet to. */
    NextPacketLocation.Val = info.NextPacketPointer;
    /* Mark this packet as discardable. */
    WasDiscarded = FALSE;
	
	enc28j60_dbg_print("EE_enc28j60_read_info end!\n");
    return 0;

}





