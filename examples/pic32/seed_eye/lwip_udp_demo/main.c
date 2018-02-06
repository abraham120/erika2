/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2011  Evidence Srl
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
    @file      main.c
    @author    Dario Di Stefano
    @date      2011
*/

/* RT-Kernel */
#include <ee.h>
#include <cpu/pic32/inc/ee_utils.h>
#include "mcu/microchip_pic32/inc/ee_timer.h"
/* console */
#include <stdio.h>
#include <stdarg.h>
#include "console_serial.h"
/* lwIP */
#include <ee_lwip.h>
#include "lwip.h"
/* Other libraries */
#include "util.h"

#pragma config POSCMOD = XT
#pragma config FNOSC = PRIPLL
#pragma config FPLLMUL = MUL_20
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLODIV = DIV_1
//#pragma config FPBDIV = DIV_1	/* SYSCLK = 80MHz, PBCLK = 80MHz */
#pragma config FPBDIV = DIV_2 	/* SYSCLK = 80MHz, PBCLK = 40MHz */
//#pragma config FPBDIV = DIV_8 /* SYSCLK = 80MHz, PBCLK = 10MHz */
#pragma config FWDTEN = OFF
#pragma config FMIIEN = OFF, FETHIO = ON	// external PHY in RMII/default configuration
#pragma config FSOSCEN = OFF

#define ENABLE_1V2_VOLTAGE() 	ODCCbits.ODCC14 = 0;\
								TRISCbits.TRISC14 = 0;\
								LATCbits.LATC14 = 1;

/* Variables for UDP communication */
static const u16_t my_port = MY_UDP_PORT;
static const u16_t remote_port = REMOTE_UDP_PORT;
static EE_UINT8 my_udp_buffer[MY_UDP_BUFFER_LEN];
/* Variables and macros for console */
console_descriptor_t *my_console_1;

/* UDP rx handler */
static void udp_rx_handler(void *arg, struct udp_pcb *upcb,
    struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    struct pbuf *q;
    int i;
    u16_t len;
    err_t ret;

    /* Connect to the remote host, for replies */
    if (! (upcb->flags & UDP_FLAGS_CONNECTED))
        udp_connect(upcb, addr, port);

    /* Print the received UDP packet */
    myprintf("\nReceived %d bytes from %d.%d.%d.%d, port %d\n", p->tot_len,
        ip4_addr1(addr), ip4_addr2(addr), ip4_addr3(addr), ip4_addr4(addr),
        port );
    for(i = 1, q = p; q != NULL; q = q->next, ++i) {
        myprintf("Chunk #%d, %d byte long\n",i, q->len);
        hex_dump(q->payload, q->len);
    }

    /* Estract the payload in a buffer, put it in a new pbuf, and send */
    len = pbuf_copy_partial(p, my_udp_buffer, MY_UDP_BUFFER_LEN, 0);
    if (len > 0) {
        q = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_REF);
        if (q != 0) {
            q->payload = my_udp_buffer;
            ret = udp_send(upcb, q);
            if (ret != ERR_OK)
                myprintf("ERROR in sending a reply\n");
            pbuf_free(q);
        } else {
            myprintf("ERROR while allocating a pbuf\n");
        }
    } else {
        myprintf("ERROR while extracting data\n");
    }

    /* Don't leak the pbuf! */
    pbuf_free(p);
}

TASK(Sender)
{
    EE_UINT32 time1, time2, time3;
    struct udp_pcb *socket;
    struct ip_addr ipaddr;
    static EE_UINT8 buf[UDP_SENDER_BUF_SIZE];
    const unsigned num_packets = UDP_NUM_PACKETS;
    static EE_UINT16 size = UDP_SENDER_INIT_SIZE;
    struct pbuf *pb;
    err_t ret;
    unsigned i;

    myprintf("\nSender: sending %d %d-byte packets\n", num_packets, size);

    time1 = get_time_stamp();
    GetResource(LwipMutex);
    socket = udp_new();
    if (0 == socket) {
        ReleaseResource(LwipMutex);
        myprintf("ERROR: cannot create UDP socket\n");
        return;
    }
    ret = udp_bind(socket, IP_ADDR_ANY, my_port+1);
    if (ret != ERR_OK) {
        udp_remove(socket);
        ReleaseResource(LwipMutex);
        myprintf("ERROR while binding to UDP port %d\n", my_port+1);
        return;
    }
    IP4_ADDR(&ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2,
        MY_IPADDR_BYTE3, MY_IPADDR_BYTE4 - 1);
    udp_connect(socket, &ipaddr, remote_port);

    pb = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_REF);
    if (pb != 0) {
        ReleaseResource(LwipMutex);
        pb->payload = buf;
        time2 = get_time_stamp();
        for (i = 0; i < num_packets; ++i) {
            msleep(2);
            sprintf((char *)buf, "%5d", i);
            GetResource(LwipMutex);
            ret = udp_send(socket, pb);
            ReleaseResource(LwipMutex);
            if (ret != ERR_OK)
                myprintf("ERROR in sending a packet\n");
        }
        time3 = get_time_stamp();
        GetResource(LwipMutex);
        udp_remove(socket);
        pbuf_free(pb);
        ReleaseResource(LwipMutex);
        myprintf("Setup took %d us\n", elapsed_us(time1, time2));
        myprintf("Transmission of %d kB took %d ms (%d kB/s)\n",
            size * num_packets / 1024, elapsed_ms(time2, time3),
            size * num_packets / 1024 * 1000 / elapsed_ms(time2, time3));
    } else {
        udp_remove(socket);
        ReleaseResource(LwipMutex);
        myprintf("ERROR while allocating a pbuf\n");
    }
    if (size*2 <= UDP_SENDER_BUF_SIZE)
        size *= 2;
}

static void timer_tick(void)
{
    CounterTick(SenderCounter);
}

int main(void)
{
    struct udp_pcb *my_udp_socket;
    err_t ret;

	ENABLE_1V2_VOLTAGE();
    EE_system_init();
    EE_leds_init();

    /* Initialize Console */
    my_console_1 = console_serial_config(MY_FIRST_SERIAL, UART_BAUDRATE,
    					CONSOLE_SERIAL_FLAG_BIT8_NO |
    					CONSOLE_SERIAL_FLAG_BIT_STOP1);
    console_init(MY_FIRST_CONSOLE, my_console_1);
    if (console_open(MY_FIRST_CONSOLE) < 0) {
    	for (;;);
    }

    /* Initialize lwIP */
    struct ip_addr my_ipaddr, netmask, gw;
    struct eth_addr my_ethaddr;
    IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3,
        MY_IPADDR_BYTE4);
    IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3,
        MY_NETMASK_BYTE4);
    IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2,
        MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
    ETH_ADDR(&my_ethaddr, MY_ETHERNETIF_MAC_BYTE1, MY_ETHERNETIF_MAC_BYTE2,
        MY_ETHERNETIF_MAC_BYTE3, MY_ETHERNETIF_MAC_BYTE4,
        MY_ETHERNETIF_MAC_BYTE5, MY_ETHERNETIF_MAC_BYTE6);
    EE_lwip_init(&my_ipaddr, &netmask, &gw, &my_ethaddr);

    /* Create a UDP socket */
    my_udp_socket = udp_new();
    if (my_udp_socket != 0) {
        /* Set the incoming callback */
        udp_recv(my_udp_socket, &udp_rx_handler, 0);
        /* Bind to a local port */
        ret = udp_bind(my_udp_socket, IP_ADDR_ANY, my_port);
        if (ret != ERR_OK) {
            myprintf("ERROR while binding to UDP port %d\n", my_port);
        } else {
            myprintf("Listening on UDP port %d\n", my_port);
        }
    } else {
        myprintf("ERROR: cannot create UDP socket\n");
    }

    /* Application main timer */
    EE_timer_soft_init(EE_TIMER_3, 1000);
    EE_timer_set_callback(EE_TIMER_3, timer_tick);
    SetRelAlarm(SenderAlarm, 100, 10000); //ActivateTask(Sender);
    EE_timer_start(EE_TIMER_3);
   
    while(1)
        ;
}

/******************************************************************************/
/* General Excepiton Handler: overrides the default handler                   */
/******************************************************************************/
static enum {
	EXCEP_IRQ = 0,	// interrupt
	EXCEP_AdEL = 4,	// address error exception (load or ifetch)
	EXCEP_AdES,	// address error exception (store)
	EXCEP_IBE,	// bus error (ifetch)
	EXCEP_DBE,	// bus error (load/store)
	EXCEP_Sys,	// syscall
	EXCEP_Bp,	// breakpoint
	EXCEP_RI,	// reserved instruction
	EXCEP_CpU,	// coprocessor unusable
	EXCEP_Overflow,	// arithmetic overflow
	EXCEP_Trap,	// trap (possible divide by zero)
	EXCEP_IS1 = 16,	// implementation specfic 1
	EXCEP_CEU,	// CorExtend Unuseable
	EXCEP_C2E	// coprocessor 2
} cp0_exception_code;

static unsigned int cp0_exception_cause; // CP0: CAUSE register
static unsigned int cp0_exception_epc;   // CP0: Exception Program Counter

void _general_exception_handler(void)
{
	asm volatile("mfc0 %0,$14" : "=r" (cp0_exception_epc));
	asm volatile("mfc0 %0,$13" : "=r" (cp0_exception_cause));
	cp0_exception_code = (cp0_exception_cause >> 2) & 0x0000001F;
	EE_led_toggle(0);
	EE_led_toggle(1);
	while (1) ;
}


