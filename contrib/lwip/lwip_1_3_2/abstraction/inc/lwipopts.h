/** 
* @file lwipopts.h
* @brief LWIP defualt options.
* @author Dario Di Stefano
* @version LWIP 1.3.2
* @date 2010-07-12
*/

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

/** 
 * ---------- Checksum options ---------- 
 */
#ifndef CHECKSUM_CHECK_UDP
#define CHECKSUM_CHECK_UDP		0
#endif
#ifndef CHECKSUM_GEN_UDP
#define CHECKSUM_GEN_UDP		0
#endif

/** 
 * ---------- Threads configuration ---------- 
 */
#ifndef NO_SYS
#define NO_SYS                  1  /* single thread */
#endif

/** 
 * ---------- Memory options ---------- 
 */
#ifndef MEM_ALIGNMENT
#define MEM_ALIGNMENT           4
#endif
#ifndef MEM_SIZE
#define MEM_SIZE                64*1024
#endif
#ifndef MEMP_NUM_PBUF
#define MEMP_NUM_PBUF           32
#endif
#ifndef MEMP_NUM_SYS_TIMEOUT 
#define MEMP_NUM_SYS_TIMEOUT    0
#endif
//#define MEMP_NUM_PBUF                   16
//#define MEMP_NUM_RAW_PCB                4
//#define MEMP_NUM_UDP_PCB                4
//#define MEMP_NUM_TCP_PCB                10          // default 5
//#define MEMP_NUM_TCP_PCB_LISTEN         8
//#define MEMP_NUM_TCP_SEG                16
//#define MEMP_NUM_REASSDATA              5
//#define MEMP_NUM_ARP_QUEUE              30
//#define MEMP_NUM_IGMP_GROUP             8
//#define MEMP_NUM_SYS_TIMEOUT            3
//#define MEMP_NUM_TCPIP_MSG_API          8
//#define MEMP_NUM_TCPIP_MSG_INPKT        8
//#define PBUF_POOL_SIZE                  16

/** 
 * The following four are used only with the sequential API and can be
 * set to 0 if the application only will use the raw API. 
 */
//#define MEMP_NUM_NETBUF         2
//#define MEMP_NUM_NETCONN        4
#ifndef MEMP_NUM_NETBUF
#define MEMP_NUM_NETBUF         0
#endif
#ifndef MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN        0
#endif
//#define MEMP_NUM_API_MSG        0
//#define MEMP_NUM_TCPIP_MSG      0

/** 
 * ---------- Pbuf options ---------- 
 */
#ifndef PBUF_POOL_SIZE
#define PBUF_POOL_SIZE          32
#endif
#ifndef PBUF_POOL_BUFSIZE
#define PBUF_POOL_BUFSIZE       1536
#endif
#ifndef PBUF_LINK_HLEN
#define PBUF_LINK_HLEN          16
#endif

/** 
 * ---------- ARP options ---------- 
 */
#ifndef ARP_QUEUEING
#define ARP_QUEUEING                      0
#endif
#ifndef LWIP_ARP
#define LWIP_ARP                          1
#endif
//#define ETHARP_ALWAYS_INSERT    0
//#define ARP_TABLE_SIZE                  10
//#define ARP_QUEUEING                    1
//#define ETHARP_TRUST_IP_MAC             1

/** 
 * ---------- IP options ---------- 
 */
//#define IP_FORWARD                      0
//#define IP_OPTIONS_ALLOWED              1
#ifndef IP_REASSEMBLY
#define IP_REASSEMBLY                     0           // default is 1
#endif
//#define IP_FRAG                         0           // default is 1
//#define IP_REASS_MAXAGE                 3
//#define IP_REASS_MAX_PBUFS              10
//#define IP_FRAG_USES_STATIC_BUF         1
//#define IP_FRAG_MAX_MTU                 1500
//#define IP_DEFAULT_TTL                  255

/** 
 * ---------- ICMP options ---------- 
 */
//#define LWIP_ICMP                       1
//#define ICMP_TTL                       (IP_DEFAULT_TTL)

/** 
 * ---------- RAW options ---------- 
 */
#ifndef LWIP_RAW
#define LWIP_RAW                0
#endif
//#define RAW_TTL                        (IP_DEFAULT_TTL)

/** 
 * ---------- DHCP options ---------- 
 */
#ifndef LWIP_DHCP
#define LWIP_DHCP               0
#endif
//#define DHCP_DOES_ARP_CHECK             ((LWIP_DHCP) && (LWIP_ARP))

/** 
 * ---------- UDP options ---------- 
 */
#ifndef LWIP_UDP
#define LWIP_UDP                0
#endif

/** 
 * ---------- TCP options ---------- 
 */
#ifndef LWIP_TCP
#define LWIP_TCP                0
#endif
#ifndef TCP_MSS
#define TCP_MSS                 1460
#endif
#ifndef TCP_SND_BUF
#define TCP_SND_BUF             4*TCP_MSS
#endif

/** 
 * ---------- Lwip Callbacks ---------- 
 */
#ifndef LWIP_CALLBACK_API
#define LWIP_CALLBACK_API       1
#endif

/** 
 * ---------- Statistics options ---------- 
 */
#ifndef LWIP_STATS
#define LWIP_STATS              0
#endif

/** 
 * ---------- Netconn ---------- 
 */
#ifndef LWIP_NETCONN
#define LWIP_NETCONN            0           // default is 1
#endif

/** 
 * ---------- Socket ---------- 
 */
#ifndef LWIP_SOCKET
#define LWIP_SOCKET             0           // default is 1
#endif

/** 
 * ---------- Ethernet ---------- 
 */
#ifndef ETH_PAD_SIZE
#define ETH_PAD_SIZE			2
#endif

/** 
 * ---------- UPNP options ---------- 
 */
//#define LWIP_UPNP             0

/** 
 * ---------- PTPD options ---------- 
 */
//#define LWIP_PTPD             0

/** 
 * ---------- DEBUG options ---------- 
 */
#ifdef __LWIP_DEBUG__
#define LWIP_DEBUG // Lwip DEBUG symbol
#endif
#ifndef EE_LWIP_DEBUG
#define EE_LWIP_DEBUG                   LWIP_DBG_OFF
#endif
//#define ETHARP_DEBUG                    LWIP_DBG_ON     // default is OFF
//#define NETIF_DEBUG                     LWIP_DBG_ON     // default is OFF
//#define PBUF_DEBUG                      LWIP_DBG_ON		// default is OFF
//#define API_LIB_DEBUG                   LWIP_DBG_OFF
//#define API_MSG_DEBUG                   LWIP_DBG_OFF
//#define SOCKETS_DEBUG                   LWIP_DBG_OFF
//#define ICMP_DEBUG                      LWIP_DBG_OFF
//#define IGMP_DEBUG                      LWIP_DBG_OFF
//#define INET_DEBUG                      LWIP_DBG_OFF
//#define IP_DEBUG                        LWIP_DBG_ON     // default is OFF
//#define IP_REASS_DEBUG                  LWIP_DBG_OFF
//#define RAW_DEBUG                       LWIP_DBG_OFF
//#define MEM_DEBUG                       LWIP_DBG_OFF
//#define MEMP_DEBUG                      LWIP_DBG_OFF
//#define SYS_DEBUG                       LWIP_DBG_OFF
//#define TCP_DEBUG                       LWIP_DBG_ON
//#define TCP_INPUT_DEBUG                 LWIP_DBG_ON
//#define TCP_FR_DEBUG                    LWIP_DBG_OFF
//#define TCP_RTO_DEBUG                   LWIP_DBG_OFF
//#define TCP_CWND_DEBUG                  LWIP_DBG_OFF
//#define TCP_WND_DEBUG                   LWIP_DBG_OFF
//#define TCP_OUTPUT_DEBUG                LWIP_DBG_ON
//#define TCP_RST_DEBUG                   LWIP_DBG_OFF
//#define TCP_QLEN_DEBUG                  LWIP_DBG_OFF
//#define UDP_DEBUG                       LWIP_DBG_ON     // default is OFF
//#define TCPIP_DEBUG                     LWIP_DBG_OFF
//#define PPP_DEBUG                       LWIP_DBG_OFF
//#define SLIP_DEBUG                      LWIP_DBG_OFF
//#define DHCP_DEBUG                      LWIP_DBG_ON     // default is OFF
//#define AUTOIP_DEBUG                    LWIP_DBG_OFF
//#define SNMP_MSG_DEBUG                  LWIP_DBG_OFF
//#define SNMP_MIB_DEBUG                  LWIP_DBG_OFF
//#define DNS_DEBUG                       LWIP_DBG_OFF

#endif /* __LWIPOPTS_H__ */
