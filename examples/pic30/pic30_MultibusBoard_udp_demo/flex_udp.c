/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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

/**
 * flex_udp.c
 */

/*
 * This macro uniquely defines this file as the main entry point.
 * There should only be one such definition in the entire project,
 * and this file must define the AppConfig variable as described below.
 */
#define THIS_IS_STACK_APPLICATION

#include "ee.h"
#include "flex_udp.h"

/******************************************************************************/
/*                              Global variables                              */
/******************************************************************************/
volatile unsigned long int UDP_flex_port = 9760;		// FLEX SERVER PORT NUMBER
volatile unsigned long int UDP_pc_port = 9761;			// PC SERVER PORT NUMBER
volatile unsigned char UDP_is_initialized = 0;		// udp initialization flag
NODE_INFO UDP_remote;
UDP_buffer UDP_rx_buffer;
UDP_buffer UDP_tx_buffer;


// Declare AppConfig structure and some other supporting stack variables
APP_CONFIG AppConfig;
static UDP_SOCKET MySocket;
//static void (*rx_callback)(BYTE *, unsigned int len);
static ROM BYTE SerializedMACAddress[6] = { MY_DEFAULT_MAC_BYTE1,
                MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3,
                MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5,
                MY_DEFAULT_MAC_BYTE6 };

/******************************************************************************/
/*                           Forward Declarations                             */
/******************************************************************************/
static void InitAppConfig(void);

/******************************************************************************/
/*                                InitAppConfig()                             */
/******************************************************************************/
/**
 * Function to initialize StackApplication
 * Write/Read non-volatile config variables.
 * PreCondition:    MPFSInit() is already called.
 */
static void InitAppConfig(void)
{
        AppConfig.Flags.bIsDHCPEnabled = TRUE;
        AppConfig.Flags.bInConfigMode = TRUE;
        memcpypgm2ram((void*)&AppConfig.MyMACAddr,
                        (ROM void*)SerializedMACAddress,
                        sizeof(AppConfig.MyMACAddr));
        //  {
        //      _prog_addressT MACAddressAddress;
        //      MACAddressAddress.next = 0x157F8;
        //      _memcpy_p2d24((char*)&AppConfig.MyMACAddr, MACAddressAddress, sizeof(AppConfig.MyMACAddr));
        //  }
        AppConfig.MyIPAddr.Val = MY_DEFAULT_IP_ADDR_BYTE1
                        | MY_DEFAULT_IP_ADDR_BYTE2 << 8ul
                        | MY_DEFAULT_IP_ADDR_BYTE3 << 16ul
                        | MY_DEFAULT_IP_ADDR_BYTE4 << 24ul;
        AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
        AppConfig.MyMask.Val = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2
                        << 8ul | MY_DEFAULT_MASK_BYTE3 << 16ul
                        | MY_DEFAULT_MASK_BYTE4 << 24ul;
        AppConfig.DefaultMask.Val = AppConfig.MyMask.Val;
        AppConfig.MyGateway.Val = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2
                        << 8ul | MY_DEFAULT_GATE_BYTE3 << 16ul
                        | MY_DEFAULT_GATE_BYTE4 << 24ul;
        AppConfig.PrimaryDNSServer.Val = MY_DEFAULT_PRIMARY_DNS_BYTE1
                        | MY_DEFAULT_PRIMARY_DNS_BYTE2 << 8ul
                        | MY_DEFAULT_PRIMARY_DNS_BYTE3 << 16ul
                        | MY_DEFAULT_PRIMARY_DNS_BYTE4 << 24ul;
        AppConfig.SecondaryDNSServer.Val = MY_DEFAULT_SECONDARY_DNS_BYTE1
                        | MY_DEFAULT_SECONDARY_DNS_BYTE2 << 8ul
                        | MY_DEFAULT_SECONDARY_DNS_BYTE3 << 16ul
                        | MY_DEFAULT_SECONDARY_DNS_BYTE4 << 24ul;

        // Load the default NetBIOS Host Name
        memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
        FormatNetBIOSName(AppConfig.NetBIOSName);
}

/******************************************************************************/
/*                             Buffer Management                              */
/******************************************************************************/

void UDP_Buffer_Init(UDP_buffer *buf, int dim)
{
  	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
  	return;
}

void UDP_Buffer_Close(UDP_buffer *buf)
{
	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
	return;
}

int UDP_Buffer_Putmsg(UDP_buffer *buf, BYTE* msg, int dim)
{
	int i=0;
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==dim)) //if( ((buf->p+1) % dim) == buf->g )
	{
		EE_hal_enableIRQ();
		return 0;
	}
	for(i=0;i<UDP_PKG_LEN;i++)
    	buf->data[buf->p][i] = msg[i];
    buf->p++;
    //if (buf->p == BUFFSIZE) buf->p = 0;
    buf->p = (buf->p % dim);
    buf->counter++;
    EE_hal_enableIRQ();
    return 1;
}

int UDP_Buffer_Getmsg(UDP_buffer *buf, BYTE* msg, int dim)
{
	int i=0;
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0)) //if(buf->g == buf->p)
	{
		EE_hal_enableIRQ();
		return 0;
	}
  	for(i=0;i<UDP_PKG_LEN;i++)
    	msg[i] = buf->data[buf->g][i];
  	buf->g++;
  	//if (buf->g == BUFFSIZE) buf->g = 0;
  	buf->g = (buf->g % dim);
  	buf->counter--;
  	EE_hal_enableIRQ();
  	return 1;
}

int UDP_Buffer_Isempty(UDP_buffer *buf)
{
	int retvalue;
	EE_hal_disableIRQ();
	if((buf->g == buf->p) && (buf->counter==0))
		retvalue = 1;
	else
		retvalue = 0;
	EE_hal_enableIRQ();
	return retvalue;
}

int UDP_Buffer_Isfull(UDP_buffer *buf, int dim)
{
	int retvalue;
	EE_hal_disableIRQ();
	//if( ((buf->p+1) % dim) == buf->g )
	//	retvalue = 1;
	if((buf->g == buf->p) && (buf->counter==dim))
		retvalue = 1;
	else
		retvalue = 0;
	EE_hal_enableIRQ();
	return retvalue;
}

/******************************************************************************/
/*                          UDP TASKs			                              */
/******************************************************************************/

TASK(UDP_TASK)
{
	WORD wMaxGet;						//! Variable to hold available RX data count
    BYTE msg[UDP_PKG_LEN];
    static int arp_flag=0;

    // Initialize stack-related hardware components that may be
    // required by the UART configuration routines
    TickInit();
    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();
    // Initialize core stack layers (MAC, ARP, TCP, UDP)
    StackInit();

	// Open the UDP socket
    MySocket = UDPOpen(UDP_flex_port, &UDP_remote, UDP_pc_port);
    if (MySocket == INVALID_UDP_SOCKET)
    	return;

    // Main: ActivateTask(UDP_TASK)
	for(;;)
	{
        StackTask();

        /***  Reception ***/
        // Figure out how many bytes have been received and set the currently active socket
        wMaxGet = UDPIsGetReady(MySocket); // Get TCP RX FIFO byte count
        if(wMaxGet == UDP_PKG_LEN)
		{
                // Copy data from internal buffer to application buffer
                UDPGetArray(msg, wMaxGet);
                // ...metti il pacchetto nella coda rx... (la coda rx è una sezione critica!!!)
                UDP_Buffer_Putmsg(&UDP_rx_buffer,msg,UDP_BUF_SIZE);
        }

        /***  Arp resolving ***/
        if(arp_flag==0)
        {
        	if(ARPIsResolved(&UDP_remote.IPAddr,&UDP_remote.MACAddr))
        	    arp_flag=2;
        	else
        	{
        		ARPResolve(&UDP_remote.IPAddr);
        		arp_flag=1;
        	}
        }
        else
        	if(arp_flag==1)
			{
        		if(ARPIsResolved(&UDP_remote.IPAddr,&UDP_remote.MACAddr))
        			arp_flag=2;
        		else
        			ARPResolve(&UDP_remote.IPAddr);
			}

        /***  Transmission ***/
		if((arp_flag==2)&&(!UDP_Buffer_Isempty(&UDP_tx_buffer)))
		{
				//ReleaseResource(MTCPIP_STACK_TASK_MUTEX);
            	if(UDPIsPutReady(MySocket)>=UDP_PKG_LEN)
            	{
					// estraggo un pacchetto dalla coda e lo spedisco...
					UDP_Buffer_Getmsg(&UDP_tx_buffer, msg, UDP_BUF_SIZE);
                	UDPPutArray(msg, UDP_PKG_LEN);	// Load UDP segment in the internal buffer
                	// UDPFlush must be called before returning to the main stack
                	// loop. There is no auto transmit for UDP segments.
                	UDPSocketInfo[MySocket].localPort = UDP_flex_port;
                	UDPSocketInfo[MySocket].remotePort = UDP_pc_port;
					UDPSocketInfo[MySocket].remoteNode = UDP_remote;
                	UDPFlush();	// Transmit UDP segment
				}
        }
	}
}
