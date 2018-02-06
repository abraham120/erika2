/**
* @file uwl_radio_cc2420.c
* @brief Abstract Radio functions
* @author Christian Nastasi
* @author Gianluca Franchino
* @author Mauro Nino Marinoni
* @version 0.1
* @date 2009-03-24
*
* This file contains the declarations of the abstract radio used by the uWireless
* modules.
*
*/
#ifndef __uwl_radio_cc2420_h__
#define __uwl_radio_cc2420_h__

#include <hal/uwl_radio.h>
#include <mac/uwl_mac_types.h>

#ifndef USE_CC2420
#error "UWL_RADIO ERROR: the CC2420 radio driver is required for this!"
#endif
#include <cc2420.h>

#ifdef UWL_DEBUG
#include <util/uwl_debug.h> //TODO: REMOVE together with the sprintf() !!!!!
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#define UWL_RADIO_RX_BUFFER_SIZE CC2420_BUFFER_SIZE

/**
* @name Phy PAN Information Base Init Value
*
* \todo Check if the initial values adopted in this case are compliant with the
* 	standard and set according to a certain policy, e.g. can read this
*	values from the specific transceiver (hal_radio)?.
* @{ */
#define UWL_RADIO_CURRENT_CHANNEL_INIT 		11
#define UWL_RADIO_CHANNEL_SUPPORTED_INIT	{0x00000000} //TODO
#define UWL_RADIO_TRANSMIT_POWER_INIT		0x00
#define UWL_RADIO_CCA_MODE_INIT 		0x03
#define UWL_RADIO_CURRENT_PAGE_INIT 		0
#define UWL_RADIO_MAX_FRAME_DURATION_INIT	266
#define UWL_RADIO_SHR_DURATION_INIT		10
#define UWL_RADIO_SYMBOLS_PER_OCTET_INIT 	2

#define UWL_RADIO_CHANNEL_FIRST 	11
#define UWL_RADIO_CHANNEL_LAST 		26
/**  @} */

/*
     TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
 TODO								TODO
 TODO	All the functio must have the syntax:			TODO
 TODO 		int8_t oab_radio_funcname(params...) 		TODO
 TODO	where							TODO
 TODO		- the return value is a status code of the 	TODO
 TODO		  function (1=success, < 0 failure), 		TODO
 TODO		  not a return value!				TODO
 TODO		- the params are for IN and OUT!!!!!|!		TODO
 TODO								TODO
     TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
*/

//int8_t uwl_radio_init(void *todo);/*TODO: chris: define params */
/**
* @brief Initializes the radio.
*
* This routine returns 0 if everything goes well, -1 otherwise.
*
* @return initialization result (0 ok, -1 failed).
 */
COMPILER_INLINE int8_t uwl_radio_init(void)
{
	/* chris: TODO: Find another way, maybe dynamic to set the Radio PORT
			e.g use defines at compiling time, use void* (nino's
			solution!)*/


	#if defined (__UWL_USE_SPI_PORT_2__) || !defined (__UWL_USE_SPI_PORT_1__) 
	return cc2420_radio_init(CC2420_SPI_PORT_2);
	#else
	return cc2420_radio_init(CC2420_SPI_PORT_1);
	#endif
}

#ifndef CSMA_UNSLOTTED
int8_t uwl_radio_mac_create_beacon(void);

int8_t uwl_radio_mac_send_beacon(void);
#endif

COMPILER_INLINE uint32_t uwl_radio_phy_get_bitrate(void)
{
	/* TODO: change this hard-coding! */
	return 250000;
}


/* chris: Sending function, can be used by the MAC or implement part of the
	  MAC itself! */
/*TODO: chris: do we use the same paradigm (store+send) for all the 4 type?
	Maybe is better to use only send for data, command, ack?
*/
/*TODO: chris: do we want to assume the auto ack generation?
	How do we model this in the generic radio?
*/

COMPILER_INLINE int8_t uwl_radio_slotted_csma_init(void)
{
	return 1;
}


int8_t uwl_radio_store_data(uint8_t *buf, uint8_t len);
int8_t uwl_radio_send_data(void);

int8_t uwl_radio_store_command(uint8_t *buf, uint8_t len);

int8_t uwl_radio_send_command(void);

int8_t uwl_radio_store_ack(uint8_t *buf, uint8_t len);

int8_t uwl_radio_send_ack(void);

/*TODO: chris: do we assume to use the CSMA in the abstract radio?
	we can use a specific function or a flag in the former send functions
*/
int8_t uwl_radio_send_csma(void *todo); /*TODO: chris: define params */

/* chris: Receiving function (callbback mechanism), can be used by the MAC! */
#ifndef CSMA_UNSLOTTED
int8_t uwl_radio_set_beacon_rx_callback(void *todo); /*TODO: chris: def params*/
#endif
int8_t uwl_radio_set_data_rx_callback(void *todo); /*TODO: chris: def params */
int8_t uwl_radio_set_command_rx_callback(void *todo); /*TODO: chris: def parms*/
int8_t uwl_radio_set_ack_rx_callback(void *todo); /*TODO: chris: define params*/

/* chris: this should be the set of common functionalities used by the PHY
	  TODO: add what is missing!
*/
/* chris: funzioni di base per GIANLUCA */

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
COMPILER_INLINE int8_t uwl_radio_send(uint8_t *buf, uint8_t len)
{
//uwl_debug_print("   uwl_radio_send(...)");// TODO: REMOVE
	//cc2420_store_txfifo(buf, len); //TODO: this don't define length!!!!!
	cc2420_store_msg(buf, len);
//uwl_debug_print("      Store FIFO OK!");// TODO: REMOVE
	cc2420_set_tx();
//uwl_debug_print("      Set TX OK!");// TODO: REMOVE
	/* Wait until the transmission has finished. */
	while (cc2420_get_status() & 0x08) ;
//uwl_debug_print("      Loop 0x08 ok!");// TODO: REMOVE
	/* If a tx underflow has occurred fix the problem
	 * and return -1.
	 */
	if (cc2420_get_status() & 0x20) {
		CC2420_TX_FIFO_FLUSH();
//uwl_debug_print("      TX FIFO underflow!");// TODO: REMOVE
		return -1;
	}
//uwl_debug_print("      returning OK!");// TODO: REMOVE
	/* Everything goes well. */
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Put the transceiver on transmission.
*
* This routine sets the radio on tx, such that a
* message stored into the txfifo will be sent.
*
*/
COMPILER_INLINE int8_t uwl_radio_start_tx(void)
{
	cc2420_set_tx();
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Put the transceiver on transmission.
*
* \todo
*
*/
COMPILER_INLINE int8_t uwl_radio_set_tx(void)
{
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Verify
*
* \todo
*
*/
COMPILER_INLINE uint8_t uwl_radio_busy_tx(void)
{
	return (cc2420_get_status() & 0x08);
}


/**
* @brief Link a callback to the isr of the radio.
*
* This routine sets the callback for the isr of the radio.
*
* @param[in] rx_callback The callback function.
*/
COMPILER_INLINE int8_t uwl_radio_set_rx_callback(void (*rx_callback)(void))
{
	cc2420_set_rx_callback(rx_callback);
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Get a msg from the rx_fifo.
*
* This routine retrives a msg from the radio rx_fifo.
*
* @param[in] *msg 	The buffer where to store the message from the FIFO
*
* @return the lenght of the received message, or -1 if something has gone wrong.
*/
COMPILER_INLINE int8_t uwl_radio_get_msg(uint8_t *msg)
{
	return cc2420_get_fifo_msg(msg);
}

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
COMPILER_INLINE int8_t uwl_radio_get_rx_data(uint8_t *msg, uint8_t *fcs_chk,
		uint8_t *lqi, uint8_t *rssi)
{
	/*FIXME: try to remove this buffer */
	uint8_t buf[130];
	uint8_t i = 0;
	
	/* len is the length of the packet with the appended LQI and RSSI plus
	 * one (since the buffer contains the lenght itself */
	int16_t len = cc2420_get_fifo_msg(buf);
	if (len < 2)
		return -1;
	/* Lenght does not consider the first byte (which is length itself) so
	 * add it! */
	len += 1;
	*fcs_chk = !!(buf[len - 1] & 0x80);
	/* The last two bytes in the buffer are the RSSI value
	* and the CRC value respectively. They are not part
	* of the message (payload), then we can discard them.
	* For further information see the CC2420 datasheet
	*/
	*lqi = buf[len - 1] & 0x7F;
	*rssi= (uint8_t)(buf[len - 2] - 45);
	/* remove the FCS/LQI, RSSI, and lenght from the length */
	len -= 3;
	//memcpy(msg, buf+1, len);

	for (i = 0; i < len; i++) {
		msg[i] = buf[i+1];
	}
	// safe cast because len is always <= 127
	return (int8_t) len;
}



/**
* @brief Set the transmission power.
*
* This routine retrives a msg from the radio rx_fifo.
*
* @param[in] pwr The pwr level setting (see cc2420.h for the available valuses).
*
*/
COMPILER_INLINE int8_t uwl_radio_set_tx_power(uint8_t pwr)
{
	/* TODO: translate the value of pwr from PIB to radio related value! */
	pwr = CC2420_PA_0DBM;
	cc2420_set_pa(pwr);
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Get the RSSI
*
* This routine returns the rssi value mesured in dbm
*
* @return the rssi value in dbm, INVALID_RSSI otherwise
*/
COMPILER_INLINE int8_t uwl_radio_get_rx_power(uint8_t *energy)
{
	/*TODO: calculate according to standard*/
	*energy = (uint8_t) cc2420_rssi_get();
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Start sleep
*
* This routine puts the radio in sleep mode.
*
* @param[in] sleep_level 	The sleep mode: POWER_DOWN or IDLE
*
*/
COMPILER_INLINE int8_t uwl_radio_sleep(void)
{
	cc2420_set_sleep(CC2420_RADIO_IDLE);
	return UWL_RADIO_ERR_NONE;
}

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

COMPILER_INLINE int8_t uwl_radio_wakeup(uint8_t status)
{
	/* chris: FIXME: wrong comparison: status cannot be less than 0!!*/
	if (status > SLEEP2TX)
		return -1;
	if (SLEEP2RX)
		cc2420_set_rx();
	if (SLEEP2TX)
		cc2420_set_tx();
	return 0;
}

/**
* @brief Start receiving
*
* This routine puts the radio on RX mode.
*/
COMPILER_INLINE int8_t uwl_radio_set_rx()
{
	cc2420_set_rx();
	return UWL_RADIO_ERR_NONE;
}

/**
*
* \todo
*/
COMPILER_INLINE uint8_t uwl_radio_busy_rx()
{
	return cc2420_get_sfd();
}
/**
* @brief Set channel
*
* This routine sets the channel to tune in the CC2420.
*
* @param[in] ch 	The channel to tune in (must be in the interval [11, 26] )
*
 */
COMPILER_INLINE int8_t uwl_radio_set_channel(uint8_t ch)
{
	cc2420_set_channel(ch);/* chris: TODO:  return nothing?? */
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Store MAC address
*
* This routine sets the MAC address (short or long) in the CC2420.
*
* @param[in] add 	The array containing the MAC address to store in the transceiver.
* @param[in] length The number of bytes forming the address. If length = 2,
* 					store the short address; if length = 8 store the long address.
* @return 0  if length is correct, -1 otherwise.
*/
COMPILER_INLINE int8_t uwl_radio_set_mac_address(uint8_t* add, uint8_t length)
{
	if (length == 2)
		cc2420_set_short_mac_add(add);
	else
		if (length == 8)
			cc2420_set_ex_mac_add(add);
		else
			return -1;
	return UWL_RADIO_ERR_NONE;
}

/**
* @brief Store MAC PAN ID
*
* This routine sets the MAC PAN ID in the CC2420.
*
* @param[in] id 	The MAC PAN ID to store in the transceiver.
*
 */
/*COMPILER_INLINE int8_t uwl_radio_set_mac_pan_id(uint8_t *id)
{
	cc2420_set_mac_pan_id(id);
}
*/
/**
* @brief Enable the auto CRC capability.
*
* This routine sets the auto CRC function of the radio.
*
*
*/

//COMPILER_INLINE int8_t uwl_radio_set_auto_crc()
//{
//	uint8_t low, high;
//
//	CC2420_REG_READ_CSn(CC2420_REG_MDMCTRL0, high, low)
//	/* chris: FIXME: check the constant! maybe 0b.... better to use 0x...*/
//	CC2420_REG_WRITE_CSn(CC2420_REG_MDMCTRL0, high | 0xb00100000, low);
//}

/**
* @brief Set the CCA (Clear Channel Assessment)
*
* This routine sets the CCA function of the radio.
*
* Note: the CCA is valid when the receiver has been enabled for at least
* 8 sysmbol period (8 * 16us = 128us).
*
* @param[in] mode. This mask is used to set the CCA mode.
*/

#define ENERGY 0x01000000 /* Clear channel when receiving energy is below
							 threshold. */
#define VALID_FRAME 0x10000000 /* clear channel when not receiving a
								  valid frame */
#define VALID_FRAME_AND_ENERGY 0x11000000 /* clear channel when energy is below
											 the threshold and not receiving
											 a valid frame */
COMPILER_INLINE int8_t uwl_radio_set_cca_mode(uint8_t mode)
{
	uint8_t low, high;

	CC2420_REG_READ_CSn(CC2420_REG_MDMCTRL0, high, low)
	CC2420_REG_WRITE_CSn(CC2420_REG_MDMCTRL0, high | mode, low);
	/* chris: TODO: always success??? */
	return UWL_RADIO_ERR_NONE;
}

COMPILER_INLINE uint8_t uwl_radio_get_cca(void)
{
	return cc2420_get_cca();
}


#endif /* Header Protection */
