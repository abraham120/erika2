#ifndef _HAL_H_
#define _HAL_H_


#include "hal/hal_defines.h" 


extern void ee_console_init(EE_UINT8 console_port);
extern void ee_console_out(EE_UINT8 ch);
extern void ee_console_out_str(const char *ch);

extern void ee_radio_spi_init(EE_UINT8 spi_port);
extern EE_UINT8 ee_radio_spi_put(EE_UINT8 v);
extern EE_UINT8 ee_radio_spi_get(void);

extern int cc2420_init(void);
extern void cc2420_set_pa(EE_UINT8);
extern EE_UINT8 cc2420_get_status(void);
extern int cc2420_get_fifo_msg(EE_UINT8 *);
extern int cc2420_rssi_get(void);
extern int cc2420_check(void);
extern EE_UINT8 cc2420_FSM_get(void);
extern void cc2420_store_msg(EE_UINT8 *, EE_UINT8);
extern void cc2420_store_txfifo(EE_UINT8*, EE_UINT8);
extern void cc2420_set_tx(void);
extern EE_UINT8 cc2420_set_tx_on_cca();
extern void cc2420_set_rx(void);
extern void cc2420_set_sleep(int);
extern void cc2420_turn_on(void);
extern void cc2420_set_channel(EE_UINT8 );
extern void cc2420_set_short_mac_add(EE_UINT8*);
extern void cc2420_set_ex_mac_add(EE_UINT8*);
extern void cc2420_set_mac_pan_id(EE_UINT8*);



#define	hal_console_init(a)  ee_console_init(a)
#define	hal_console_out(a) ee_console_out(a)
#define	hal_console_out_str(a) ee_console_out_str(a)
#define	hal_radio_spi_init(a) ee_radio_spi_init(a)
#define hal_radio_spi_put(a) ee_radio_spi_put(a)
#define hal_radio_spi_get()  ee_radio_spi_get()

#define hal_radio_init() cc2420_init()
#define hal_set_tx_power(a) cc2420_set_pa(a)
#define	hal_get_msg(a) cc2420_get_fifo_msg(a)
#define hal_store_msg(a,b) cc2420_store_msg(a,b)
#define	hal_store_buf(a,b) cc2420_store_txfifo(a,b)
#define	hal_set_tx() cc2420_set_tx()
#define	hal_set_tx_on_cca() cc2420_set_tx_on_cca()
#define	hal_set_rx() cc2420_set_rx()
#define	hal_set_sleep(a) cc2420_set_sleep(a)
#define	hal_radio_turn_on() cc2420_turn_on()
#define	hal_rssi_get() cc2420_rssi_get()
#define	hal_set_channel(a) cc2420_set_channel(a)
#define	hal_radio_get_status() cc2420_get_status()
#define	hal_radio_get_FSM() cc2420_get_FSM()
#define	hal_set_mac_short_add(a) cc2420_set_short_mac_add(a)
#define	hal_set_mac_ex_add(a) cc2420_set_ex_mac_add(a)
#define	hal_set_mac_pan_id(a) cc2420_set_mac_pan_id(a)

#endif
