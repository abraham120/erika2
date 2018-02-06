/**
* @file mrf24j40_compiler.h
* @brief MRF24J40 Abstract Compiler
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* File Contents: a set of functions to manage the Microchip MRF24J40 radio transceiver.
*
* \todo Reformat the following text using doxygen
*
* Author: Gianluca Franchino.
* Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
* Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
* Date: 02/27/2008.
*
 */
//#define MRF24J40_DEBUG

#include "mrf24j40.h"


/*chris: TODO: Choose a proper policy for the 'is_initialized' status variable,
		we have to use it in some function!!
*/
static uint8_t radio_initialized = 0;
static void (*rx_callback)(void) = NULL;
static void (*tx_finished_callback)(uint8_t tx_status) = NULL;
/* variables to store register values for carrier sense enabling and disabling*/
static uint8_t bbreg2;
static uint8_t ccaedth;
#ifdef MRF24J40_DEBUG
static uint8_t mrf24j40_db_msg[80];

#ifdef __STDIO_COMPILER_BUG__
unsigned int strlen(const char *str);
int sprintf(char *, const char *, ...);
#else
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#endif

void mrf24j40_set_rx_callback(void (*func)(void))
{
	rx_callback = func;
}

/**
* @brief Init transceiver
*
* This routine initializes the radio transceiver
*
* @return 0 if the initialization goes well, -1 otherwise.
*/
int8_t mrf24j40_init(uint8_t int_setup, uint8_t ch, uint8_t port)
{
	uint8_t i;
	int8_t retv;
	int8_t iteration;
	

	//return 0;
	if (radio_initialized)
		return -2;

	/* init hal-specific things */
	mrf24j40_hal_init();
	retv = mrf24j40_hal_spi_init(port);

	/*TODO; manage error code*/
	if (retv < 0)
		return -1;

	mrf24j40_hal_retsetn_low();
	mrf24j40_hal_delay_us(2500);
	mrf24j40_hal_retsetn_high();
	mrf24j40_hal_delay_us(2500);
	
	
	/**
	 * Software reset:
	 * 7:3 = '00'  = Reserved
	 * 2:0   = '111' = Reset MAC, baseband
	 * and power management circuitries
	 */
	mrf24j40_set_short_add_mem(MRF24J40_SOFTRST, 0x07);

	/**
	* wait until the radio reset is completed
	*/
	iteration = 3;
	do {
		i = mrf24j40_get_short_add_mem(MRF24J40_SOFTRST);

	} while (iteration-- > 0 || (i & 0x07) != 0);

	mrf24j40_set_short_add_mem(MRF24J40_RXFLUSH, 0x01);

	mrf24j40_hal_delay_us(2500);

	mrf24j40_set_short_add_mem(MRF24J40_PACON2, 0x98);

	mrf24j40_dbg_print("\r\nMRF24J40 Init1");

	/*
	 * Read back to value just written.
	 * This trick is used to verify if the radio is connected.
	 */
	
	if (mrf24j40_get_short_add_mem(MRF24J40_PACON2) != 0x98)
		return -1;

	mrf24j40_dbg_print("\r\nMRF24J40 Init2");

	/**
	* Reset RF state machine
	*/
	mrf24j40_set_short_add_mem(MRF24J40_RFCTL, 0x04);
      	mrf24j40_set_short_add_mem(MRF24J40_RFCTL, 0x00);


	/** flush RX fifo */
	mrf24j40_set_short_add_mem(MRF24J40_RXFLUSH, 0x01);

	/** setup */
	mrf24j40_set_channel(ch); //set channel
	mrf24j40_hal_delay_us(200); // After a reset the datasheet suggests to wait at least 180us

	mrf24j40_set_long_add_mem(MRF24J40_RFCON1, 0x01); //program the RF and Baseband Register as
						//suggested by the datasheet

	mrf24j40_set_long_add_mem(MRF24J40_RFCON2, 0x80); //enable PLL
	mrf24j40_set_long_add_mem(MRF24J40_RFCON3, 0x00); //set maximum power 0dBm

	/** set up RFCON6
	* 7 = 1 = as suggested by the datasheet
	* 6:5 = '00' = Reserved
	* 4 = '1' recovery from sleep 1 usec
	* 3 = '0' = battery monitor disabled
	* 2:0 = '00' = Reserved
	*/

	mrf24j40_set_long_add_mem(MRF24J40_RFCON6, 0x90);

	mrf24j40_set_long_add_mem(MRF24J40_RFCON7, 0x80); //sleep clock = 100kHz

	mrf24j40_set_long_add_mem(MRF24J40_RFCON8, 0x10); //as suggested by the datasheet

	mrf24j40_set_long_add_mem(MRF24J40_SLPCON1, 0x21);

	/** Program CCA mode using RSSI */

	mrf24j40_set_short_add_mem(MRF24J40_BBREG2, 0x80);

	#ifdef MRF24J40MB
	/** Activate the external amplifier needed by the MRF24J40MB */
	mrf24j40_set_long_add_mem(MRF24J40_TESTMODE, 0x1F);
	mrf24j40_dbg_print("\r\nMRF24J40 Init Amplifier activated ");
	#endif


	#ifdef ADD_RSSI_AND_LQI_TO_PACKET
	/** Enable the packet RSSI */
	mrf24j40_dbg_print("\r\nMRF24J40 Init append RSSI and LQI to packet");
	mrf24j40_set_short_add_mem(MRF24J40_BBREG6, 0x40);
	#endif

	/** Program CCA, RSSI threshold values */
	mrf24j40_set_short_add_mem(MRF24J40_CCAEDTH, 0x60);

	/**
	* wait until the radio state machine is not on rx mode
	*/
	do {
        	i = mrf24j40_get_long_add_mem(MRF24J40_RFSTATE);}
	while((i&0xA0) != 0xA0);

	//mrf24j40_dbg_set_msg("\r\nRFSTATE=0x%X",i);
	//mrf24j40_dbg_print(mrf24j40_db_msg);
	/**
	*
	*Set interrupts.
	*/
	/**
	* set INTCON
	* 7 = '1' = Disables the Sleep alert interrupt
	* 6 = '1' = Disables the wake-up alert interrupt
	* 5 = '1' = Disables the half symbol timer interrupt
	* 4 = '1' = Disables the security key request interrupt
	* 3 = '0' = Enables the RX FIFO reception interrupt
	* 2 = '1' = Disables the TX GTS2 FIFO transmission interrupt
	* 1 = '1' = Disables the TX GTS1 FIFO transmission interrupt
	* 0 = '0' = Enables the TX Normal FIFO transmission interrupt
	*/
	//mrf24j40_set_short_add_mem(INTCON,0xF6);

	mrf24j40_set_short_add_mem(MRF24J40_INTCON, int_setup);

	#ifdef INT_POLARITY_HIGH
	/* Set interrupt edge polarity high */
	mrf24j40_dbg_print("\r\nMRF24J40 Init INT Polarity High");
	mrf24j40_set_long_add_mem(MRF24J40_SLPCON0, 0x02);
	#endif

	/**
	Disables automatic Acknowledgement response.
	Receive all packet types with good CRC.
	*/
	//mrf24j40_set_short_add_mem(RXMCR,0x21);

	i = 0;

	#ifdef MRF24J40_DISABLE_AUTOMATIC_ACK
	mrf24j40_dbg_print("\r\nMRF24J40 Init NO_AUTO_ACK");
	//i = i | 0b00100000;
	i |= 0x20;
	#endif

	#ifdef MRF24J40_PAN_COORDINATOR
	mrf24j40_dbg_print("\r\nMRF24J40 Init PAN COORD");
	//i = i | 0b00001000;
	i |= 0x08;
	#endif

	#ifdef MRF24J40_COORDINATOR
	mrf24j40_dbg_print("\r\nMRF24J40 Init COORD");
	//i = i | 0b00000100;
	i |= 0x04;
	#endif

	#ifdef MRF24J40_ACCEPT_WRONG_CRC_PKT
	mrf24j40_dbg_print("\r\nMRF24J40 Init Accept Wrong CRC");
	//i = i | 0b00000010;
	i |= 0x02;
	#endif

	#ifdef MRF24J40_PROMISCUOUS_MODE
	mrf24j40_dbg_print("\r\nMRF24J40 Init PROMISUOUS MODE");
	//i = i | 0b00000001;
	i |= 0x01;
	#endif

	/*
	 * Set the RXMCR register.
	 * Default setting i=0x00, which means:
	 * - Automatic ACK;
	 * - Device is not a PAN coordinator;
	 * - Device is not a coordinator;
	 * - Accept only packets with good CRC
	 * - Discard packet when there is a MAC address mismatch,
	 *   illegal frame type, dPAN/sPAN or MAC short address mismatch.
	 * See the datasheet for further information.
	 */


	mrf24j40_set_short_add_mem(MRF24J40_RXMCR, i);

	#ifndef MRF24J40_DISABLE_CSMA

	mrf24j40_dbg_print("\r\nMRF24J40 Init CSMA ENABLED");

	#ifdef MRF24J40_BEACON_ENABLED_MODE

	mrf24j40_dbg_print("\r\nMRF24J40 Init BEACON MODE ENABLED");

	#ifdef MRF24J40_BATT_LIFE_EXT
	/*
	 *Set the TXMCR register.
	 * bit 7 = '0';  Enable No Carrier Sense Multiple Access (CSMA)
	 * Algorithm.
	 * bit 6 = '1';  Enable Battery Life Extension Mode bit.
	 * bit 5 = '1';  Enable Slotted CSMA-CA Mode bit.
	 * bit 4-3 = '11'; MAC Minimum Backoff Exponent bits (macMinBE).
	 * bit 2-0 = '100';  CSMA Backoff bits (macMaxCSMABackoff)
	 */
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, 0x7C);
	mrf24j40_dbg_print("\r\nMRF24J40 Init Battery life enabled");
	#else
	/*
	 *Set the TXMCR register.
	 * bit 7 = '0';  Enable No Carrier Sense Multiple Access (CSMA)
	 * Algorithm.
	 * bit 6 = '0';  Disable Battery Life Extension Mode bit.
	 * bit 5 = '1';  Enable Slotted CSMA-CA Mode bit.
	 * bit 4-3 = '11'; MAC Minimum Backoff Exponent bits (macMinBE).
	 * bit 2-0 = '100';  CSMA Backoff bits (macMaxCSMABackoff)
	 */
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, 0x3C);
	mrf24j40_dbg_print("\r\nMRF24J40 Init Battery life disabled");
	#endif

	#else

	#ifdef MRF24J40_BATT_LIFE_EXT
	/*
	 *Set the TXMCR register.
	 * bit 7 = '0';  Enable No Carrier Sense Multiple Access (CSMA)
	 * Algorithm.
	 * bit 6 = '1';  Enable Battery Life Extension Mode bit.
	 * bit 5 = '0';  Disable Slotted CSMA-CA Mode bit.
	 * bit 4-3 = '11'; MAC Minimum Backoff Exponent bits (macMinBE).
	 * bit 2-0 = '100';  CSMA Backoff bits (macMaxCSMABackoff)
	 */
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, 0x5C);
	mrf24j40_dbg_print("\r\nMRF24J40 Init Battery life enabled");
	#else
	/*
	 *Set the TXMCR register.
	 * bit 7 = '0';  Enable No Carrier Sense Multiple Access (CSMA)
	 * Algorithm.
	 * bit 6 = '0';  Disable Battery Life Extension Mode bit.
	 * bit 5 = '0';  Disable Slotted CSMA-CA Mode bit.
	 * bit 4-3 = '11'; MAC Minimum Backoff Exponent bits (macMinBE).
	 * bit 2-0 = '100';  CSMA Backoff bits (macMaxCSMABackoff)
	 */
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, 0x1C);
	mrf24j40_dbg_print("\r\nMRF24J40 Init Battery life disabled");
	#endif

	#endif

	#else
	mrf24j40_dbg_print("\r\nMRF24J40 Init CSMA DISABLED");
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, 0x80); /* Disable CSMA */
	#endif

	/**
	 * Set TX turn around time as defined by IEEE802.15.4 standard
	 */
	mrf24j40_set_short_add_mem(MRF24J40_TXTIME, 0x30);
	mrf24j40_set_short_add_mem(MRF24J40_TXSTBL, 0x95);

	/*
	 * if TURBO_MODE is defined, the transceiver works
	 * at 625 Kbit/sec.
	 */
	#ifdef TURBO_MODE
	mrf24j40_set_short_add_mem(MRF24J40_BBREG0, 0x01);
    	mrf24j40_set_short_add_mem(MRF24J40_BBREG3, 0x38);
    	mrf24j40_set_short_add_mem(MRF24J40_BBREG4, 0x5C);
    	mrf24j40_dbg_print("\r\nMRF24J40 Init TURBO MODE enabled");
	#endif

	i = mrf24j40_get_short_add_mem(MRF24J40_TXMCR);
	mrf24j40_dbg_set_msg("\r\nTXMCR 0x%X",i);
	mrf24j40_dbg_print(mrf24j40_db_msg);
	/**
	* Reset RF state machine
	*/

	mrf24j40_set_short_add_mem(MRF24J40_RFCTL, 0x04);
	mrf24j40_set_short_add_mem(MRF24J40_RFCTL, 0x00);
	mrf24j40_dbg_print("\r\nMRF24J40 Init Done!");

	#ifdef MRF24J40_ZERO_MIN_BE
	/*
	 * Set the MAC Minimum Backoff Exponent bits (macMinBE) to 0
	 * --> collision avoidance disabled (only for the first try!)
	 */
	uint8_t tmp_val = mrf24j40_get_short_add_mem(MRF24J40_TXMCR);
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, tmp_val & 0xE7);
//	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, 0x80);

	/* CCA MODE 3 */
//	tmp_val = mrf24j40_get_short_add_mem(MRF24J40_BBREG2);
//	mrf24j40_set_short_add_mem(MRF24J40_BBREG2, tmp_val | 0xFC);
//	mrf24j40_set_short_add_mem(MRF24J40_CCAEDTH, 0xFF);
	/* CCA MODE 1?*/
//	tmp_val = mrf24j40_get_short_add_mem(MRF24J40_BBREG2);
//	mrf24j40_set_short_add_mem(MRF24J40_BBREG2, tmp_val & 0x7F);
//	mrf24j40_set_short_add_mem(MRF24J40_CCAEDTH, 0xFF);
	#endif
	/* Store values for carrier sense enabling and disabling */
	bbreg2 = mrf24j40_get_short_add_mem(MRF24J40_BBREG2);
	ccaedth = mrf24j40_get_short_add_mem(MRF24J40_CCAEDTH);

	#ifdef __LM32__
	mrf24j40_hal_int_enable();
	#endif //#ifdef __LM32__

	return 0;
}

void mrf24j40_disable_carrier_sense()
{
	mrf24j40_set_short_add_mem(MRF24J40_BBREG2, 0x80);
	mrf24j40_set_short_add_mem(MRF24J40_CCAEDTH, 0xFF);
}

void mrf24j40_enable_carrier_sense()
{
	mrf24j40_set_short_add_mem(MRF24J40_BBREG2, bbreg2);
	mrf24j40_set_short_add_mem(MRF24J40_CCAEDTH, ccaedth);
}



/**
* @brief Store message
*
* This routine stores a buffer of buf_length bytes in the TX_FIFO buffer of the
* MRF24J40.
*
* @param[in] *buf 	The message pointer
* @param[in] len 	The message lenght
*/
int8_t mrf24j40_store_norm_txfifo(uint8_t* buf, uint8_t len)
{
	uint8_t i;

	if (len > 127 || len <= 0)
		return -1;
	mrf24j40_set_long_add_mem(MRF24J40_NORMAL_TX_FIFO, 1);
	mrf24j40_set_long_add_mem(MRF24J40_NORMAL_TX_FIFO + 1, len);
	for (i = 0; i < len; i++)
		mrf24j40_set_long_add_mem(MRF24J40_NORMAL_TX_FIFO + 2 + i,
					  buf[i]);
	//mrf24j40_dbg_print("\n\rSTORE NOR_TXFIFO DONE!");
	return 0;
}
/**
* @brief Store message
*
* This retrieve a byte at  position pos from TX_FIFO buffer of the MRF24J40.
*
* @param[in] pos 	The byte position
*/
uint8_t mrf24j40_get_norm_txfifo(uint8_t pos)
{
	if (pos > 127)
		return 0;
	return mrf24j40_get_long_add_mem(MRF24J40_NORMAL_TX_FIFO + pos);
}


/**
* @brief Get message
*
* This routine is used to retrieve a message store in the RX_FIFO
*
* @param[in] *msg 	The buffer where to store the message from the RX_FIFO
*
* @return the lenght of the received message
*
* Note: the last two bytes, representing the CRC code, are discarded.
*/
uint8_t mrf24j40_get_fifo_msg(uint8_t *msg)
{
	uint8_t i, len;

	#ifdef MRF24J40_PROMISCUOUS_MODE
	/*
	 * Flush RX FIFO as suggested by the work around 1 in
	 * MRF24J40 Silicon Errata.
	 */
	mrf24j40_set_short_add_mem(MRF24J40_RXFLUSH,0x01);
	#endif
	/*Disable packet reception*/
	mrf24j40_set_short_add_mem(MRF24J40_BBREG1, 0x04);
	/* Get packet length */
	len = mrf24j40_get_long_add_mem(MRF24J40_RX_FIFO);
	#ifdef MRF24J40_UWL_MODE
	/* Discard CRC bytes */
	// don't discard it in UWL_MODE
	//len = len - 2;

	/* Get the packet */
	mrf24j40_dbg_print("\r\nPacket received:\r\n");
//	msg[0] = len;
//	mrf24j40_dbg_set_msg("Len = 0x%X \n", len);
//	mrf24j40_dbg_print(mrf24j40_db_msg);
	for (i=0;i < len + 2; i++) {
		msg[i] = mrf24j40_get_long_add_mem(MRF24J40_RX_FIFO + i + 1);
//		mrf24j40_dbg_set_msg("0x%X ", msg[i]);
//		mrf24j40_dbg_print(mrf24j40_db_msg);
	}

	#else
	/*Discard CRC bytes */
	len = len - 2;
	/* Get the packet */
	mrf24j40_dbg_print("\r\nPacket received:\r\n");
	for (i=0;i < len; i++) {
		msg[i] = mrf24j40_get_long_add_mem(MRF24J40_RX_FIFO + 1 + i);
		mrf24j40_dbg_set_msg("0x%X ", msg[i]);
		mrf24j40_dbg_print(mrf24j40_db_msg);
	}
	#endif /* MRF24J40_UWL_MODE */

	/*Enable packet reception*/
	mrf24j40_set_short_add_mem(MRF24J40_BBREG1, 0x00);
	return len;
}

/**
* @brief Get message
*
* This routine is used to retrieve a message store in the RX_FIFO
*
* @param[in] *msg 	The buffer where to store the message from the RX_FIFO
*
* @return the lenght of the received message
* Note
*
*/
uint8_t mrf24j40_get_fifo_msg_with_lqi(uint8_t *msg, uint8_t *rssi,
				       uint8_t *lqi)
{
	uint8_t i, len;

	#ifdef MRF24J40_PROMISCUOUS_MODE
 	/*
	* Flush RX FIFO as suggested by the work around 1 in
	* MRF24J40 Silicon Errata.
	*/
	mrf24j40_set_short_add_mem(MRF24J40_RXFLUSH,0x01);
	#endif

	/*Disable packet reception*/
	mrf24j40_set_short_add_mem(MRF24J40_BBREG1, 0x04);

	/* Get packet length */
	len = mrf24j40_get_long_add_mem(MRF24J40_RX_FIFO);

	/* Get the packet excluding CRC bytes*/
	for (i=0;i < len - 2; i++)
		msg[i] = mrf24j40_get_long_add_mem(MRF24J40_RX_FIFO + 1 + i);

	/*
	 * packet len includes = header + paylod + CRC
	 */
	*lqi = mrf24j40_get_long_add_mem(MRF24J40_RX_FIFO + 1 + len );
	*rssi = mrf24j40_get_long_add_mem(MRF24J40_RX_FIFO + 1 + len + 1);

	/*Enable packet reception*/
	mrf24j40_set_short_add_mem(MRF24J40_BBREG1, 0x00);

	/*Discard CRC bytes */
	len = len - 2;

	return len;
}

/**
* @brief Start sleep
*
* This routine puts the radio in sleep mode.
*
*
*/
void mrf24j40_put_to_sleep()
{
	/* Prepare wake pin */
	#ifdef MRF24J40_USE_WAKE_PIN
	MRF24J40_WAKE_INACTIVE();
	#else
	mrf24j40_set_short_add_mem(MRF24J40_RXFLUSH, 0x60);
	mrf24j40_set_short_add_mem(MRF24J40_WAKECON, 0x80);
	#endif
	/* Put to sleep*/
	mrf24j40_set_short_add_mem(MRF24J40_SOFTRST, 0x04);
	mrf24j40_set_short_add_mem(MRF24J40_SLPACK, 0x80);
}
/**
* @brief Awake the radio
*
* This routine turns on a sets the radio on receiving mode.
*
* Note:   After performing this routine the radio is in the receiving  state.
*
* Warning:      If no radio is present the system is blocked in a infinite loop!
*/
void mrf24j40_wake()
{
	#ifdef MRF24J40_USE_WAKE_PIN
	MRF24J40_WAKE_ACTIVE();
	#else
	mrf24j40_set_short_add_mem(MRF24J40_WAKECON, 0xC0);
	mrf24j40_set_short_add_mem(MRF24J40_WAKECON, 0x80);
	#endif
	mrf24j40_hal_delay_us(2000); /* Delay for 2 ms */

	/* Wait until the transceiver is not on receiving mode */
	while (mrf24j40_get_long_add_mem(MRF24J40_RFSTATE) != 0xA0 );
}

void mrf24j40_set_tx_finished_callback(void (*tx_finished_func)(uint8_t))
{
	tx_finished_callback = tx_finished_func;
}

MRF24J40_HAL_ISR()
{
	/* chris: TODO: change the version with bit-fields, this in NOT compiler
			independent. USE masks and bitwise ANDs instead.
	*/
	INT_status int_status;
	TX_status tx_status;

	mrf24j40_hal_irq_clean();
	mrf24j40_dbg_print("\r\nMRF24J40 Interrupt");
	int_status.val = mrf24j40_get_short_add_mem(MRF24J40_INTSTAT);
	if (int_status.bits.TXNIF) {
		mrf24j40_dbg_print("\r\nNormal TX finished");
		tx_status.val = mrf24j40_get_short_add_mem(MRF24J40_TXSTAT);
		if (tx_status.bits.TXNSTAT)
			mrf24j40_dbg_print("\r\nNormal TX failed");
		else
			mrf24j40_dbg_print("\r\nNormal TX success");
		if (tx_finished_callback)
			tx_finished_callback(tx_status.bits.TXNSTAT);
	}
	if (int_status.bits.RXIF) {
		mrf24j40_dbg_print("\r\nRX received");
		if (rx_callback != NULL)
			rx_callback();
	}
}
