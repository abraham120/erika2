/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2012  Evidence Srl
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
 
/** @file	main.c
 *  @brief	LWIP UDP test (with ENC28J60, see oil files).
 *
 *  User can use this demo to learn how to write LWIP UDP based applications. 
 *  The demo requires a RS232 serial connection with user PC.
 *  The demo requires a SPI bus to communicate with ENC28J60.
 *  The demo requires a Ethernet connection with user PC.
 *
 *  @author	Errico Guidieri
 *  @author	Giuseppe Serano
 *  @date	2012
 */

/* RT-Kernel */
#include <ee.h>
/* Standard library */
#include <stdio.h>
#include <stdarg.h>
/* lwIP */
#include <ee_lwip.h>
#include "lwip.h"

/* AS MCAL */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#ifdef	DEBUG
#include "Sci.h"
#endif
#include "Spi.h"
#include "Icu.h"

#define UDP_SENDER_BUF_SIZE	1472
#define UDP_SENDER_PKT_NUM	4

#define time_diff_ms(t1,t2)	\
	((EE_UINT32)((t1) - (t2)) / (EE_UINT32)(EE_CPU_CLOCK / 1000U))
#define time_diff_us(t1,t2)	\
	((EE_UINT32)((t1) - (t2)) / (EE_UINT32)(EE_CPU_CLOCK / 1000000U))

/* Variables for UDP communication */
static const u16_t my_port = 9760;
static const u16_t remote_port = 8640;
struct ip_addr remote_ipaddr;

#define	MY_UDP_BUFFER_LEN	1472
static EE_UINT8 my_udp_buffer[MY_UDP_BUFFER_LEN];
static char *msg = "LwIP Packet %d\n";

static EE_UINT32 packet_num = 0;

#ifdef	DEBUG
static void EE_uart_send_buffer(const char * const str, size_t len) {
  size_t i;
  uint8 rx;
  Sci_StatusType st;
  for(i = 0U; i < len; ++i) {
	/* To eventually handle errors in rx */
    st = Sci_GetStatus(SCI_CHANNEL_4);
    while ((st != SCI_OPERATIONAL) && (st != SCI_TX_OK)) {
	  Sci_ReadRxData(SCI_CHANNEL_4, &rx);
	  st = Sci_GetStatus(SCI_CHANNEL_4);
	}
    Sci_WriteTxData(SCI_CHANNEL_4, str[i]);
  }
}

#define MAXCHARS 80

/* A printf-like function */
void myprintf(const char *format, ...)
{
    const char printf_trunc[] = "\n..[TRUNCATED]..\n";
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
#endif	/* DEBUG */

/* UDP rx handler */
static void udp_rx_handler(void *arg, struct udp_pcb *upcb,
    struct pbuf *p, struct ip_addr *addr, u16_t port)
{
    struct pbuf *q;
    u16_t len;
#ifdef	DEBUG
    int i;
    err_t ret;
#endif

    /* Make the LED blink in RX */
    Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_HIGH);
    
    /* Connect to the remote host, for replies */
    if (upcb->flags & UDP_FLAGS_CONNECTED) {

      udp_disconnect(upcb);

    }

    /* Connect to the remote host, for replies */
    udp_connect(upcb, &remote_ipaddr, remote_port);

#ifdef	DEBUG
    /* Print the received UDP packet */
    myprintf("\nReceived %d bytes from %d.%d.%d.%d, port %d\n", p->tot_len,
        ip4_addr1(addr), ip4_addr2(addr), ip4_addr3(addr), ip4_addr4(addr),
        port );
    for(i = 1, q = p; q != NULL; q = q->next, ++i) {
        myprintf("Chunk #%d, %d byte long\n",i, q->len);
        hex_dump(q->payload, q->len);
    }
#endif

    /* Estract the payload in a buffer, put it in a new pbuf, and send */
    len = pbuf_copy_partial(p, my_udp_buffer, MY_UDP_BUFFER_LEN, 0);
    if (len > 0) {
        q = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_REF);
        if (q != 0) {
            q->payload = my_udp_buffer;
#ifdef	DEBUG
            ret =
#endif
            udp_send(upcb, q);
#ifdef	DEBUG
            if (ret != ERR_OK)
                myprintf("ERROR in sending a reply\n");
#endif
            pbuf_free(q);
#ifdef	DEBUG
        } else {
            myprintf("ERROR while allocating a pbuf\n");
#endif
        }
#ifdef	DEBUG
    } else {
        myprintf("ERROR while extracting data\n");
#endif
    }

    /* Connect to the remote host, for replies */
    if (upcb->flags & UDP_FLAGS_CONNECTED) {

      udp_disconnect(upcb);

    }

    /* Don't leak the pbuf! */
    pbuf_free(p);

    /* Make the LED blink in RX */
    Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_LOW);
}

void fill_buff(char *b, EE_UINT16 sz, EE_UINT32 pkt_num)
{
  register EE_UINT16 ofs = 0;
  register int n;
  while ( (ofs + 23) < sz ) {
    n = sprintf(&b[ofs], msg, pkt_num);
    ofs += n;
  }
}

TASK(SenderTask)
{
    static EE_UINT8 buf[UDP_SENDER_BUF_SIZE] = {0};
    static EE_UINT16 size = 24; /* strlen(msg) */

    struct udp_pcb *socket;
    struct pbuf *pb;

    err_t ret;
    unsigned i;

#ifdef	DEBUG
    EE_UINT32 time1, time2, time3;
#endif

    GetResource(LwipMutex);

#ifdef	DEBUG
    myprintf(
      "\nSender: sending %d %d-byte packets\n", UDP_SENDER_PKT_NUM, size
    );

    time1 = EE_systick_get_value();
#endif

    socket = udp_new();
    if (0 == socket) {
#ifdef	DEBUG
        myprintf("ERROR: cannot create UDP socket\n");
#endif
        ReleaseResource(LwipMutex);
        return;
    }
    ret = udp_bind(socket, IP_ADDR_ANY, my_port+1);
    if (ret != ERR_OK) {
        udp_remove(socket);
#ifdef	DEBUG
        myprintf("ERROR while binding to UDP port %d\n", my_port+1);
#endif
        ReleaseResource(LwipMutex);
        return;
    }

    udp_connect(socket, &remote_ipaddr, remote_port);

    pb = pbuf_alloc(PBUF_TRANSPORT, size, PBUF_REF);

    if (pb != 0) {
#ifdef	DEBUG
        time2 = EE_systick_get_value();
#endif
        ReleaseResource(LwipMutex);
        pb->payload = buf;
        for (i = 0; i < UDP_SENDER_PKT_NUM; ++i) {
            fill_buff((char *)buf, size, packet_num++);
            GetResource(LwipMutex);
            ret = udp_send(socket, pb);
#ifdef	DEBUG
            if (ret != ERR_OK) {
                myprintf("ERROR in sending a packet\n");
            }
#endif
            ReleaseResource(LwipMutex);
        }
        GetResource(LwipMutex);
#ifdef	DEBUG
        time3 = EE_systick_get_value();
#endif
        udp_remove(socket);
        pbuf_free(pb);
#ifdef	DEBUG
        myprintf("Setup took %d us\n", time_diff_us(time1, time2));
        myprintf("Transmission of %d kB took %d ms (%d kB/s)\n",
          size * UDP_SENDER_PKT_NUM / 1024, time_diff_ms(time2, time3),
          size * UDP_SENDER_PKT_NUM / 1024 * 1000 / time_diff_ms(time2, time3));
#endif
        ReleaseResource(LwipMutex);
    } else {
        udp_remove(socket);
#ifdef	DEBUG
        myprintf("ERROR while allocating a pbuf\n");
#endif
        ReleaseResource(LwipMutex);
    }

    if ( (size << 1) <= UDP_SENDER_BUF_SIZE) {
        size <<= 1;
    }
    else {
      size = 24;
    }
}

TASK(InitTask)
{

    struct udp_pcb *my_udp_socket;
#ifdef	DEBUG
    err_t ret;
#endif

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

    IP4_ADDR(&remote_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3,
    MY_IPADDR_BYTE4 - 1);

    /* Create a UDP socket */
    my_udp_socket = udp_new();
    if (my_udp_socket != 0) {
        /* Set the incoming callback */
        udp_recv(my_udp_socket, &udp_rx_handler, 0);
        /* Bind to a local port */
#ifdef	DEBUG
        ret =
#endif
        udp_bind(my_udp_socket, IP_ADDR_ANY, my_port);
#ifdef	DEBUG
        if (ret != ERR_OK) {
            myprintf("ERROR while binding to UDP port %d\n", my_port);
        } else {
            myprintf("Listening on UDP port %d\n", my_port);
        }
    } else {
        myprintf("ERROR: cannot create UDP socket\n");
#endif
    }
}

int main (void) {
  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);

  /* 50 MHz Clock  */
  if ( Mcu_InitClock(MCU_CLOCK_MODE_MOSC_4_PLL) == E_NOT_OK ) {

    Mcu_PerformReset();

  }

  while ( Mcu_GetPllStatus() != MCU_PLL_LOCKED );

  Mcu_DistributePllClock();

  /* Initialize all AS MCAL */
  Port_Init(PORT_CONFIG_SPI_ENC28J60_PTR);
  Dio_Init(DIO_CONFIG_ENC28J60_PTR);
#ifdef	DEBUG
  Sci_Init(SCI_CONFIG_DEFAULT_PTR);
#endif
  Dma_Init(DMA_CONFIG_SPI_PTR);
  Spi_Init(SPI_CONFIG_ENC28J60_PTR);
  Icu_Init(ICU_CONFIG_ENC28J60_PTR);
  Icu_EnableNotification(ICU_ENC28J60_CHANNEL);

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
