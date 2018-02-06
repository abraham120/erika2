/* Macros */
#define MY_ETHERNETIF_MAC_BYTE1     (0x00)
#define MY_ETHERNETIF_MAC_BYTE2     (0x04)
#define MY_ETHERNETIF_MAC_BYTE3     (0xA3)
#define MY_ETHERNETIF_MAC_BYTE4     (0x00)
#define MY_ETHERNETIF_MAC_BYTE5     (0x00)
#define MY_ETHERNETIF_MAC_BYTE6     (0x00)
#define MY_IPADDR_BYTE1             (192)
#define MY_IPADDR_BYTE2             (168)
#define MY_IPADDR_BYTE3             (0)
#define MY_IPADDR_BYTE4             (2)
#define MY_NETMASK_BYTE1            (255)
#define MY_NETMASK_BYTE2            (255)
#define MY_NETMASK_BYTE3            (255)
#define MY_NETMASK_BYTE4            (0)
#define MY_GATEWAY_ADDR_BYTE1       (192)
#define MY_GATEWAY_ADDR_BYTE2       (168)
#define MY_GATEWAY_ADDR_BYTE3       (0)
#define MY_GATEWAY_ADDR_BYTE4       (10)
#define REMOTE_IPADDR_BYTE1         (192)
#define REMOTE_IPADDR_BYTE2         (168)
#define REMOTE_IPADDR_BYTE3         (0)
#define REMOTE_IPADDR_BYTE4         (1)

/* Socket status structure */
struct mysocket_state { 
	struct pbuf *p;
	u32_t  pos;         /* where to start in this pbuf */
	u32_t  left;        /* how many are left in this pbuf */
};

err_t tcp_send_data(struct tcp_pcb *pcb, struct mysocket_state *mss);
err_t tcp_tx_callback(void *arg, struct tcp_pcb *pcb, u16_t len);
err_t tcp_rx_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
err_t tcp_connect_callback(void *arg, struct tcp_pcb *pcb, err_t err);
err_t tcp_close_connection(struct tcp_pcb *pcb, struct mysocket_state *mss);

