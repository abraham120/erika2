/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010  Evidence Srl
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
    @brief     LWIP TCP test (with ENC28J60, see oil files).
               User can use this demo to learn how to write LWIP TCP based applications.
               The demo requires a RS232 serial connection with user PC (115200 bps,8N1 configuration).
               The demo requires a SPI bus to communicate with ENC28J60.
               The demo requires a Ethernet connection with user PC.
    @author    Dario Di Stefano
    @date      2010
*/

/* RT-Kernel */
#include <ee.h>
/* Platform description */
#include <system_conf.h>
/* Standard library */
#include <stdio.h>
#include <stdarg.h>
#include <MicoMacros.h>
/* lwIP */
#include <ee_lwip.h>
#include "lwip.h"

/* Variables for TCP communication */
static const u16_t my_port = 9760;
static const u16_t remote_port = 50001;
struct mysocket_state *mssg;
struct tcp_pcb *my_tcp_socket;

#define time_diff_ms(t1,t2)  (((t1) - (t2)) / (EE_UINT32)(CPU_FREQUENCY / 1000))
#define time_diff_us(t1,t2)  (((t1) - (t2)) / (EE_UINT32)(CPU_FREQUENCY / 1000000))

EE_UINT32 time1, time2, time3;
struct pbuf *pb = 0;
volatile int tx_finished = 0;
volatile int is_connected = 0;

/* A printf-like function */
void myprintf(const char *format, ...)
{
#define MAXCHARS 128
	const char printf_trunc[] = "..[TRUNCATED]..\n";
	char str[MAXCHARS];
	int len;
	va_list args;
	va_start(args, format);
	len = vsnprintf(str, MAXCHARS, format, args);
	va_end(args);
	if (len > MAXCHARS - 1) {
		/* vsnptintf() returns the number of characters needed */
		EE_uart_send_buffer(str, MAXCHARS - 1 );
		EE_uart_send_buffer(printf_trunc, sizeof(printf_trunc) - 1);
	} else {
		EE_uart_send_buffer(str, len);
	}
}

/* In case of fatal error */
void die(int code)
{
	myprintf("\nError! code: %d\n", code);
	while(1);
}

/* This function is used to display received packets on serial terminal */
static void hex_dump(const void *base, int size)
{
	const unsigned char *p = base;
	char lbuf[16*3+4];
	int k, j;
	
	j = 0;
	for (k = 0; k < size; ++k) {
		sprintf(&lbuf[j], "%02x ", p[k]);
		j += 3;
		if (0 == ((k+1) % 16) || k == size-1) {
			lbuf[j++] = '\n';
			lbuf[j] = 0;
			EE_uart_send_buffer(lbuf, j);
			j = 0;
		} else if (0 == ((k+1) % 8)) {
			lbuf[j++] = ' ';
		}
	}
}

TASK(Sender)
{
#define TCP_SENDER_BUF_SIZE 1460
	static EE_UINT8 buf[TCP_SENDER_BUF_SIZE];
	static EE_UINT16 size = 50;
	err_t ret;

	myprintf("\nSender: sending %d-byte packets\n", size);
	tx_finished = 0;
	
	/* TCP packet setup */
	EE_freetimer_get_value(&time1);
	GetResource(LwipMutex);
	
	pb = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_REF); /* Occuped memory is then freed in tx callback. */
	if (pb != 0){
		pb->payload = buf;
	}
	else {
		myprintf("ERROR while allocating a pbuf\n");
	}
	if (mssg->p){
		pbuf_chain(mssg->p, pb);
	}
	else{
		mssg->p    = pb;
		mssg->left = pb->len;
		mssg->pos  = 0;
	}
	ReleaseResource(LwipMutex);
	EE_freetimer_get_value(&time2);
	
	/* Send */
	GetResource(LwipMutex);       
	ret = tcp_send_data(my_tcp_socket, mssg);	/* Send the packet */
	ReleaseResource(LwipMutex);
	if (ret != ERR_OK)
		myprintf("ERROR in sending a packet\n"); 
	while(tx_finished==0)	/* wait transmission end */
		;  
	
	/* Results */    
	myprintf("Setup took %d us\n", time_diff_us(time1, time2));
	myprintf("Transmission of %d B took %d ms (%d B/s)\n",
	size, time_diff_ms(time2, time3),
	size * 1000 / time_diff_ms(time2, time3));
	if ((size+350) <= TCP_SENDER_BUF_SIZE)
		size += 350;
}

/* MAIN (Background task) */
int main(void)
{
	/* ------------------- */
	/* Disable IRQ         */
	/* ------------------- */
	EE_mico32_disableIRQ();
	
	/* -------------------------- */
	/* Uart configuration         */
	/* -------------------------- */
	EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
	EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);   
	
	/* ------------------- */
	/* LWIP configuration  */
	/* ------------------- */
	myprintf("\n\n\nLWIP configuration in progress...");
	struct ip_addr my_ipaddr, netmask, gw;
	struct eth_addr my_ethaddr;
	IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3, MY_IPADDR_BYTE4);
	IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3, MY_NETMASK_BYTE4);
	IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2, MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
	ETH_ADDR(&my_ethaddr, MY_ETHERNETIF_MAC_BYTE1, MY_ETHERNETIF_MAC_BYTE2, MY_ETHERNETIF_MAC_BYTE3, 
	MY_ETHERNETIF_MAC_BYTE4, MY_ETHERNETIF_MAC_BYTE5, MY_ETHERNETIF_MAC_BYTE6);	
	EE_lwip_init(&my_ipaddr, &netmask, &gw, &my_ethaddr);
	myprintf("Done!\n");
	
	/* ------------------- */
	/* Enable IRQ         */
	/* ------------------- */
	EE_mico32_enableIRQ();
	
	/* ------------------- */
	/* My app initialization */
	/* ------------------- */
	my_tcp_socket = tcp_new();	/* Create an tcp socket */
	myprintf("my_tcp_socket: %p\n", my_tcp_socket);
	err_t ret = tcp_bind(my_tcp_socket, &my_ipaddr, my_port);	/* Bind the tcp socket */ 
	myprintf("tcp_bind return value: %d\n", ret);
	struct ip_addr remote_ipaddr;
	IP4_ADDR(&remote_ipaddr, REMOTE_IPADDR_BYTE1, REMOTE_IPADDR_BYTE2, REMOTE_IPADDR_BYTE3, REMOTE_IPADDR_BYTE4);
	ret = tcp_connect(my_tcp_socket, &remote_ipaddr, remote_port, &tcp_connect_callback);
	myprintf("tcp_connect return value: %d\n", ret);
	
	/* ------------------- */
	/* Background activity */
	/* ------------------- */
	while(1)
	if(is_connected)
		ActivateTask(Sender);
	
	return 0;
}

/* TCP send data callback */
err_t tcp_close_connection(struct tcp_pcb *pcb, struct mysocket_state *mss)
{
	myprintf("\ntcp_close_connection start!\n");
	tcp_arg(pcb, NULL);
	tcp_sent(pcb, NULL);
	tcp_recv(pcb, NULL);
	if (mss) {
		if (mss->p) {
			pbuf_free(mss->p);
		}
		mem_free(mss);
	}
	err_t err = tcp_close(pcb);
	myprintf("tcp_close_connection end!\n");
	return err;
}

/* TCP send data callback */
err_t tcp_send_data(struct tcp_pcb *pcb, struct mysocket_state *mss)
{
	err_t err;
	u16_t len;

	myprintf("\ntcp_send_data start!\n");
	if (mss->p == NULL){
		myprintf("p=NULL -> tcp_send_data end!\n");
		return ERR_OK;
	}
	/* We cannot send more data than space avaliable in the send buffer. */    
	len = tcp_sndbuf(pcb); 
	myprintf("tcp_send_data: max length available %d\n", len);
	if(len > mss->left){
		len = mss->left;
	} 
	myprintf("tcp_send_data: length required %d\n", len);
	/* Send the extracted packet */
	myprintf("\ntcp_send_data write...");
	err = tcp_write(pcb, mss->p->payload + mss->pos, len, 1);
	if(err == ERR_OK){
		mss->pos  += len;
		mss->left -= len;
		myprintf("done!\n");
	} else {
		myprintf("error! code: %d, len: %d, space: %d\n", err, len, tcp_sndbuf(pcb));
		die(err);
	}
	myprintf("tcp_send_data end!\n");
	return err;
}

/* TCP tx handler */
err_t tcp_tx_callback(void *arg, struct tcp_pcb *pcb, u16_t len)
{
	struct pbuf *p;
	struct mysocket_state *mss = arg;
	
	myprintf("\ntcp_tx_callback start!\n");
	if (mss->left > 0) {
		tcp_send_data(pcb, mss);
	} else {
		if (mss->p) {
			/* free the pbuf and send the next one */
			p = mss->p;
			mss->p = pbuf_dechain(p);
			mss->pos = 0;
			if (mss->p) 
				mss->left = mss->p->len;
			else       
			{
				mss->left = 0;
				tx_finished = 1;
				myprintf("tcp_tx_callback FINISHED!\n");
				EE_freetimer_get_value(&time3);
			}
			pbuf_free(p);
			if (mss->left > 0) 
				tcp_send_data(pcb, mss);
		}
	}
	myprintf("tcp_tx_callback end!\n");
	return ERR_OK;
}

/* TCP rx handler */
err_t tcp_rx_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
	struct pbuf *q;
	int i;
	
	myprintf("\ntcp_rx_callback start!\n");
	/* The red leds form an 8-bit counter for packets.  The system led (9)
	* indicates activity. */
	EE_UINT32 leds;
	leds = EE_led_get_all();
	EE_led_set_all(((leds + 1) & 0xff) | (1<<9));
	
	/* Print the received UDP packet */
	myprintf("\nReceived %d bytes from %d.%d.%d.%d, port %d\n", p->tot_len,
	ip4_addr1(&(tpcb->remote_ip)), ip4_addr2(&(tpcb->remote_ip)), 
	ip4_addr3(&(tpcb->remote_ip)), ip4_addr4(&(tpcb->remote_ip)),
	tpcb->remote_port );     
	for(i = 1, q = p; q != NULL; q = q->next, ++i) {
		myprintf("Chunk #%d, %d byte long\n",i, q->len);
		hex_dump(q->payload, q->len);
	}
	if(p != NULL){
		tcp_recved(tpcb, p->tot_len);	/* Inform TCP that we have taken the data. */
	} 
	else{
		myprintf("rxcbk no data received, connection closed\n");
		tcp_close_connection(tpcb, mssg);
		die(1);
	}
	if(err != ERR_OK){
		myprintf("rxcbk error %d, connection closed \n", err);
		tcp_close_connection(tpcb, mssg);
		die(err);
	}
	/* Don't leak the pbuf! */
	pbuf_free(p);
	EE_led_off(9);
	myprintf("tcp_rx_callback end!\n");
	return err;
}

/* TCP connect callback */
err_t tcp_connect_callback(void *arg, struct tcp_pcb *pcb, err_t err)
{
	myprintf("\ntcp_connect_callback start!\n");
	/* Initialize the server structure. */
	mssg = mem_malloc(sizeof(struct mysocket_state));
	if(mssg == NULL) {
		myprintf("\ntcp_connect_callback: mem_malloc out of memory!\n");
		myprintf("\ntcp_connect_callback end!\n");
		return ERR_MEM;
	}
	mssg->p    = NULL;
	mssg->left = 0;
	mssg->pos  = 0;

	/* Tell TCP that this is the structure we wish to be passed for our
	callbacks. */
	tcp_arg(pcb, mssg);		/* Set the argument that will be passed to all the callbacks for that connection */
	tcp_sent(pcb, &tcp_tx_callback);		/* Set the tx callback */
	tcp_recv(pcb, &tcp_rx_callback);		/* Set the rx callback */ 

	is_connected = 1;
	myprintf("tcp_connect_callback end!\n");
	return ERR_OK;
}

