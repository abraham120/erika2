/** 
 * @file iedf_radio_cc2420.h
 * @brief Abstract Radio functions
 * @author Simone Madeo 2011
 *
 * Using the Erika Enterprise abstraction for the compiler.
 */

#ifndef __iedf_radio_cc2420_h__
#define __iedf_radio_cc2420_h__

#include <hal/iedf_compiler.h>
#include <cc2420.h>

#define IEDF_RADIO_RX_BUFFER_SIZE           CC2420_BUFFER_SIZE
#define IEDF_RADIO_CURRENT_CHANNEL_INIT 	11
#define IEDF_RADIO_CHANNEL_SUPPORTED_INIT	{0x00000000} //TODO
#define IEDF_RADIO_TRANSMIT_POWER_INIT		0x00
#define IEDF_RADIO_CCA_MODE_INIT 			0x03
#define IEDF_RADIO_CURRENT_PAGE_INIT 		0
#define IEDF_RADIO_MAX_FRAME_DURATION_INIT	266
#define IEDF_RADIO_SHR_DURATION_INIT		10
#define IEDF_RADIO_SYMBOLS_PER_OCTET_INIT 	2
#define IEDF_RADIO_CHANNEL_FIRST 			11
#define IEDF_RADIO_CHANNEL_LAST 			26


/**
* @brief Send the packet memorized in buf.
*
* This routine stores a packet in the TX fifo of the radio,
* then transmits it.
*
* @param[in] *buf 	The message pointer
* @param[in] buf_legth 	The message lenght
* @return 0 if the initialization goes well, -1 otherwise.
*/
int8_t iedf_radio_send(uint8_t *buf, uint8_t len);

/**
* @brief Return the available bitrate.
*
*/
uint32_t iedf_radio_get_bitrate(void);

/**
* @brief Initialize the radio.
*
*/
int8_t iedf_radio_init(void);

/**
* @brief The channel to tune in (in the configured interval)
*
*/
int8_t iedf_radio_set_channel(uint8_t ch);

/**
* @brief Put the transceiver on transmission.
* @return 0 if the operation goes well.
*
*/
int8_t iedf_radio_set_tx(void);

/**
* @brief Verify transmission state
*
*/
uint8_t iedf_radio_busy_tx(void);


/**
* @brief Link a callback to the isr of the radio.
*
* This routine sets the callback for the isr of the radio.
*
* @param[in] rx_callback The callback function.
*/
int8_t iedf_radio_set_rx_callback(void (*rx_callback)(void));

/**
* @brief Get a msg from the rx_fifo.
*
* This routine retrives a msg from the radio rx_fifo.
*
* @param[in] *msg 	The buffer where to store the message from the FIFO
* @param[in] *fcs_chk	The variable where to store the FCS check result
* 			(1 if FCS is correct, 0 otherwise)
* @param[in] *lqi 	The variable where to store the LQI
* @param[in] *rssi 	The variable where to store the RSSI
*
* @return the lenght of the received message (without FCS), or -1 if something
* has gone wrong.
*/
int8_t iedf_radio_get_rx_data(uint8_t *msg, uint8_t *fcs_chk,
						uint8_t *lqi, uint8_t *rssi);

/**
* @brief Get a msg from the rx_fifo.
*
* This routine retrives a msg from the radio rx_fifo.
*
* @param[in] *msg 	The buffer where to store the message from the FIFO
*
* @return the lenght of the received message, or -1 if something has gone wrong.
*/
int8_t iedf_radio_get_msg(uint8_t *msg);

/**
* @brief Set the transmission power.
*
* This routine retrives a msg from the radio rx_fifo.
*
* @param[in] pwr The pwr level setting (see cc2420.h for the available valuses).
*
*/
int8_t iedf_radio_set_tx_power(uint8_t pwr);

/**
* @brief Get the RSSI
*
* This routine returns the rssi value mesured in dbm
*
* @return the rssi value in dbm, INVALID_RSSI otherwise
*/
int8_t iedf_radio_get_rx_power(uint8_t *energy);

/**
* @brief Start sleep
*
* This routine puts the radio in sleep mode.
*
*/
int8_t iedf_radio_sleep(void);

/**
* @brief Wake up the radio
*
* This routine resume the radio from sleep.
*
* @param[in] status 	The new working status: RX (st = SLEEP2RX)
* 						or TX (st = SLEEP2TX).
*/
#define SLEEP2RX 0
#define SLEEP2TX 1

uint8_t iedf_radio_wakeup(uint8_t status);

/**
* @brief Start receiving
*
* This routine puts the radio on RX mode.
*/
int8_t iedf_radio_set_rx();

/**
*
* @brief Check if the radio is receiving a message
*
*/
uint8_t iedf_radio_busy_rx();

/**
*
* @brief Get CCA pin value
*
*/
uint8_t iedf_radio_get_cca(void);

/**
* @brief Set the CCA (Clear Channel Assessment)
*
* This routine sets the CCA function of the radio.
*
* Note: the CCA is valid when the receiver has been enabled for at least
* 8 symbol period (8 * 16us = 128us).
*
* @param[in] mode. This mask is used to set the CCA mode.
*/
int8_t iedf_radio_set_cca_mode(uint8_t mode);

#endif /* Header Protection */
