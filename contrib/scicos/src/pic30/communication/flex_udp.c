/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Evidence Srl
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
    @file flex_udp.c
    @brief www.scicos.org, www.scicoslab.org
    @author Daniele Alessandrelli, RetisLab, Pisa
    @date 2009
*/

/*
 * This macro uniquely defines this file as the main entry point.
 * There should only be one such definition in the entire project,
 * and this file must define the AppConfig variable as described below.
 */
#define THIS_IS_STACK_APPLICATION

#include "ee.h"
#include "pic30/communication/flex_udp.h"

/******************************************************************************/
/*                              Global variables                              */
/******************************************************************************/
UDP_buffer UDP_rx_buffer;
UDP_buffer UDP_tx_buffer;
volatile int UDP_num_rx_channels = 0; /* 0 == disabled */
volatile int UDP_num_tx_channels = 0; /* 0 == disabled */
volatile UDP_message tx_msg[EESCI_UDP_BUFFER_LENGTH];
volatile UDP_message rx_msg[EESCI_UDP_BUFFER_LENGTH];

volatile unsigned long int UDP_flex_port;        /* FLEX UDP socket port */
volatile unsigned long int UDP_pc_port;          /* PC UDP socket port */
NODE_INFO UDP_remote;                            /* PC IP address */

unsigned long int MY_DEFAULT_IP_ADDR_BYTE1;
unsigned long int MY_DEFAULT_IP_ADDR_BYTE2;
unsigned long int MY_DEFAULT_IP_ADDR_BYTE3;
unsigned long int MY_DEFAULT_IP_ADDR_BYTE4;

unsigned long int MY_DEFAULT_MASK_BYTE1;
unsigned long int MY_DEFAULT_MASK_BYTE2;
unsigned long int MY_DEFAULT_MASK_BYTE3;
unsigned long int MY_DEFAULT_MASK_BYTE4;

unsigned long int MY_DEFAULT_GATE_BYTE1;
unsigned long int MY_DEFAULT_GATE_BYTE2;
unsigned long int MY_DEFAULT_GATE_BYTE3;
unsigned long int MY_DEFAULT_GATE_BYTE4;

unsigned long int MY_DEFAULT_PRIMARY_DNS_BYTE1;
unsigned long int MY_DEFAULT_PRIMARY_DNS_BYTE2;
unsigned long int MY_DEFAULT_PRIMARY_DNS_BYTE3;
unsigned long int MY_DEFAULT_PRIMARY_DNS_BYTE4;

unsigned long int MY_DEFAULT_SECONDARY_DNS_BYTE1;
unsigned long int MY_DEFAULT_SECONDARY_DNS_BYTE2;
unsigned long int MY_DEFAULT_SECONDARY_DNS_BYTE3;
unsigned long int MY_DEFAULT_SECONDARY_DNS_BYTE4;

/* Declare AppConfig structure and some other supporting stack variables */
APP_CONFIG AppConfig;
static UDP_SOCKET MySocket;
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

        /*  Load the default NetBIOS Host Name*/
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
}

void UDP_Buffer_Close(UDP_buffer *buf)
{
    buf->g = 0;
    buf->p = 0;
    buf->counter = 0;
}

int UDP_Buffer_Putmsg(UDP_buffer *buf, BYTE* msg)
{
    int i=0;
    int dim  = sizeof(buf->data)/sizeof(UDP_message);
    
    EE_hal_disableIRQ();
    if((buf->g == buf->p) && (buf->counter==dim)) //if( ((buf->p+1) % dim) == buf->g )    
    {
        EE_hal_enableIRQ();    
        return 0;     
    }
    for(i=0; i<sizeof(UDP_message); i++)    
        buf->data[buf->p][i] = msg[i];
    buf->p++;
    //if (buf->p == BUFFSIZE) buf->p = 0;
    buf->p = (buf->p % dim);
    buf->counter++;
    EE_hal_enableIRQ();    
    return 1;
}

int UDP_Buffer_Getmsg(UDP_buffer *buf, BYTE* msg)
{
    int i=0;
    int dim  = sizeof(buf->data)/sizeof(UDP_message);
    
    EE_hal_disableIRQ();
    if((buf->g == buf->p) && (buf->counter==0)) //if(buf->g == buf->p)
    {
        EE_hal_enableIRQ();    
        return 0;     
    }
    for(i=0; i<sizeof(UDP_message); i++)    
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

int UDP_Buffer_Isfull(UDP_buffer *buf)
{
    int retvalue;
    int dim  = sizeof(buf->data)/sizeof(UDP_message);
    
    EE_hal_disableIRQ();
    //if( ((buf->p+1) % dim) == buf->g )    
    //    retvalue = 1;
    if((buf->g == buf->p) && (buf->counter==dim))
        retvalue = 1;
    else
        retvalue = 0;
    EE_hal_enableIRQ();        
    return retvalue;
}

int UDP_Buffer_count(UDP_buffer *buf)
{
    int retvalue;
    EE_hal_disableIRQ();
    retvalue = buf->counter;
    EE_hal_enableIRQ();    
    return retvalue;
}






/******************************************************************************/
/*                          UDP TASKs                                          */
/******************************************************************************/

TASK(UDP_TASK)
{
    /* Initialize stack-related hardware components that may be
       required by the UART configuration routines */
    TickInit();
    /* Initialize Stack and application related NV variables into AppConfig. */
    InitAppConfig();
    /* Initialize core stack layers (MAC, ARP, TCP, UDP) */
    StackInit();
    
    MySocket = UDPOpen(UDP_flex_port, &UDP_remote, UDP_pc_port);
    if (MySocket == INVALID_UDP_SOCKET)
        return;
        
    for(;;) {
        StackTask();
        
        /***  Reception ***/
        /* This section implements a "polling" approach for reception */
        /* The next version should be based on ISR */
        if( UDP_num_rx_channels) {
            /* Figure out how many bytes have been received and set the currently active socket. */
            WORD wMaxGet = UDPIsGetReady(MySocket); /* Get UDP RX FIFO byte count */
            if(wMaxGet == EE_UDP_BUF_SIZE) {
                /* Copy data from internal buffer to application buffer */
                UDPGetArray((BYTE*)rx_msg, EE_UDP_BUF_SIZE);
                int i;
                for(i=0; i<UDP_num_rx_channels; i++)
                    UDP_Buffer_Putmsg(&UDP_rx_buffer, (BYTE*)rx_msg + i*sizeof(UDP_message) );
            }
        }
        
        /***  Transmission ***/
        if( UDP_num_tx_channels && 
           (ARPIsResolved(&UDP_remote.IPAddr,&UDP_remote.MACAddr)==TRUE) && 
           (!UDP_Buffer_Isempty(&UDP_tx_buffer)) ) {
            //ReleaseResource(MTCPIP_STACK_TASK_MUTEX);
            if( UDPIsPutReady(MySocket) >= EE_UDP_BUF_SIZE ) {
                int i;
                for(i=0; i<UDP_num_tx_channels; i++)
                    UDP_Buffer_Getmsg(&UDP_tx_buffer, (BYTE*)tx_msg + i*sizeof(UDP_message) );
                /* Load UDP segment in the internal buffer. */
                /* Data size is: sizeof(UDP_message)*UDP_num_tx_channels */
                /* UDP packet size is EE_UDP_BUF_SIZE for compatibility with other boards. */
                UDPPutArray((BYTE*)tx_msg, EE_UDP_BUF_SIZE); 
                /* Set the destination socket */
                UDPSocketInfo[MySocket].localPort = UDP_flex_port;
                UDPSocketInfo[MySocket].remotePort = UDP_pc_port;
                UDPSocketInfo[MySocket].remoteNode = UDP_remote;
                /* UDPFlush must be called before returning to the main stack loop. */
                /* There is no auto transmit for UDP segments. */
                UDPFlush();    /* Tx signal to start transmission of the UDP segment. */
            }
        }
        else if( UDP_num_tx_channels && ARPIsResolved(&UDP_remote.IPAddr,&UDP_remote.MACAddr)==FALSE )
            ARPResolve(&UDP_remote.IPAddr);
    }
}
