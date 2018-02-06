/**
* @file mrf24j40.h
* @brief MRF24J40 driver
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*/

#ifndef _MRF24J40_H_
#define _MRF24J40_H_

#include "mrf24j40_compiler.h"
#include "mrf24j40_hal.h"

/* Functions prototypes */
int8_t  mrf24j40_init(uint8_t int_setup, uint8_t ch, uint8_t port);
int8_t	mrf24j40_store_norm_txfifo(uint8_t* buf, uint8_t len);
uint8_t	mrf24j40_get_norm_txfifo(uint8_t pos);
uint8_t	mrf24j40_get_fifo_msg(uint8_t *msg);
uint8_t mrf24j40_get_fifo_msg_with_lqi(uint8_t *msg, uint8_t *rssi,
				       uint8_t *lqi);
void	mrf24j40_put_to_sleep();
void	mrf24j40_wake();
void mrf24j40_set_rx_callback(void (*func)(void));
void mrf24j40_set_tx_finished_callback(void (*tx_finished_func)(uint8_t));
void mrf24j40_disable_carrier_sense();
void mrf24j40_enable_carrier_sense();

#define MRF24J40_BUFFER_SIZE 127

#ifdef MRF24J40_DEBUG
#ifdef __STDIO_COMPILER_BUG__
unsigned int strlen(const char *str);
int sprintf(char *, const char *, ...);
#else
#include <stdio.h>
#include <string.h>
#endif
#include "console_serial.h"
#define DEBUG_PORT 0
#define mrf24j40_dbg_print(msg) console_write(DEBUG_PORT, (uint8_t*) msg, strlen((char*)msg))
#define mrf24j40_dbg_set_msg(str,val) sprintf((char*)mrf24j40_db_msg, str, val)
#else
#define	mrf24j40_dbg_print(msg)
#define mrf24j40_dbg_set_msg(str,val)
#endif /* MRF24J40_DEBUG */

/* long address registers */
#define MRF24J40_RFCON0 (0x200)
#define MRF24J40_RFCON1 (0x201)
#define MRF24J40_RFCON2 (0x202)
#define MRF24J40_RFCON3 (0x203)
#define MRF24J40_RFCON5 (0x205)
#define MRF24J40_RFCON6 (0x206)
#define MRF24J40_RFCON7 (0x207)
#define MRF24J40_RFCON8 (0x208)
#define MRF24J40_SPCAL0 (0x209)
#define MRF24J40_SPCAL1 (0x20a)
#define MRF24J40_SPCAL2 (0x20b)
#define MRF24J40_RFSTATE (0x20f)
#define MRF24J40_RSSI (0x210)
#define MRF24J40_SLPCON0 (0x211)
#define MRF24J40_SLPCON1 (0x220)
#define MRF24J40_WAKETIMEL (0x222)
#define MRF24J40_WAKETIMEH (0x223)
#define MRF24J40_REMCNTL (0x224)
#define MRF24J40_REMCNTH (0x225)
#define MRF24J40_MAINCNT0 (0x226)
#define MRF24J40_MAINCNT1 (0x227)
#define MRF24J40_MAINCNT2 (0x228)
#define MRF24J40_MAINCNT3 (0x229)
#define MRF24J40_TESTMODE (0x22f)
#define MRF24J40_NORMAL_TX_FIFO  (0x000)
#define MRF24J40_BEACON_TX_FIFO  (0x080)
#define MRF24J40_GTS1_TX_FIFO    (0x100)
#define MRF24J40_GTS2_TX_FIFO    (0x180)
#define MRF24J40_RX_FIFO         (0x300)
#define MRF24J40_SECURITY_FIFO   (0x280)

/* Short address registers */
#define MRF24J40_RXMCR (0x00)
#define MRF24J40_PANIDL (0x01)
#define MRF24J40_PANIDH (0x02)
#define MRF24J40_SADRL (0x03)
#define MRF24J40_SADRH (0x04)
#define MRF24J40_EADR0 (0x05)
#define MRF24J40_EADR1 (0x06)
#define MRF24J40_EADR2 (0x07)
#define MRF24J40_EADR3 (0x08)
#define MRF24J40_EADR4 (0x09)
#define MRF24J40_EADR5 (0x0A)
#define MRF24J40_EADR6 (0x0B)
#define MRF24J40_EADR7 (0x0C)
#define MRF24J40_RXFLUSH (0x0D)
#define MRF24J40_ORDER (0x10)
#define MRF24J40_TXMCR (0x11)
#define MRF24J40_ACKTOUT (0x12)
#define MRF24J40_ESLOTG1 (0x13)
#define MRF24J40_SYMTICKL (0x14)
#define MRF24J40_SYMTICKH (0x15)
#define MRF24J40_PACON0 (0x16)
#define MRF24J40_PACON1 (0x17)
#define MRF24J40_PACON2 (0x18)
#define MRF24J40_TXBCON0 (0x1A)
#define MRF24J40_TXNCON (0x1B)
#define MRF24J40_TXG1CON (0x1C)
#define MRF24J40_TXG2CON (0x1D)
#define MRF24J40_ESLOTG23 (0x1E)
#define MRF24J40_ESLOTG45 (0x1F)
#define MRF24J40_ESLOTG87 (0x20)
#define MRF24J40_TXPEND (0x21)
#define MRF24J40_WAKECON (0x22)
#define MRF24J40_FRMOFFSET (0x23)
#define MRF24J40_TXSTAT (0x24)
#define MRF24J40_TXBCON1 (0x25)
#define MRF24J40_GATECLK (0x26)
#define MRF24J40_TXTIME (0x27)
#define MRF24J40_HSYMTMRL (0x28)
#define MRF24J40_HSYMTMRH (0x29)
#define MRF24J40_SOFTRST (0x2A)
#define MRF24J40_SECCON0 (0x2C)
#define MRF24J40_SECCON1 (0x2D)
#define MRF24J40_TXSTBL (0x2E)
#define MRF24J40_RXSR (0x30)
#define MRF24J40_INTSTAT (0x31)
#define MRF24J40_INTCON (0x32)
#define MRF24J40_GPIO (0x33)
#define MRF24J40_TRISGPIO (0x34)
#define MRF24J40_SLPACK (0x35)
#define MRF24J40_RFCTL (0x36)
#define MRF24J40_SECCR2 (0x37)
#define MRF24J40_BBREG0 (0x38)
#define MRF24J40_BBREG1 (0x39)
#define MRF24J40_BBREG2 (0x3A)
#define MRF24J40_BBREG3 (0x3B)
#define MRF24J40_BBREG4 (0x3C)
#define MRF24J40_BBREG6 (0x3E)
#define MRF24J40_CCAEDTH (0x3F)

/* Channel setting codes */
#define MRF24J40_CHANNEL_11 0x00
#define MRF24J40_CHANNEL_12 0x10
#define MRF24J40_CHANNEL_13 0x20
#define MRF24J40_CHANNEL_14 0x30
#define MRF24J40_CHANNEL_15 0x40
#define MRF24J40_CHANNEL_16 0x50
#define MRF24J40_CHANNEL_17 0x60
#define MRF24J40_CHANNEL_18 0x70
#define MRF24J40_CHANNEL_19 0x80
#define MRF24J40_CHANNEL_20 0x90
#define MRF24J40_CHANNEL_21 0xa0
#define MRF24J40_CHANNEL_22 0xb0
#define MRF24J40_CHANNEL_23 0xc0
#define MRF24J40_CHANNEL_24 0xd0
#define MRF24J40_CHANNEL_25 0xe0
#define MRF24J40_CHANNEL_26 0xf0

/*
 * INTCON register setting masks 
 * Note: These masks are mainly used to set int_setup parameters of the
 * mrf24j40_init(uint8_t int_setup, uint8_t ch) function: they must combined 
 * with the & operand (bit-wise AND). 
 */

//Enables the TX Normal FIFO transmission interrupt
#define MRF24J40_EN_TX_NORMAL_FIFO (0b11111110)  
//Enables TX GTS1 FIFO transmission interrupt
#define MRF24J40_EN_TX_GTS1_FIFO (0b11111101)    
//Enables TX GTS2 FIFO transmission interrupt
#define MRF24J40_EN_TX_GTS2_FIFO (0b11111011)    
//Enables the RX FIFO reception interrupt
#define MRF24J40_EN_RX_FIFO (0b11110111)         
//Enables the security key request interrupt
#define MRF24J40_EN_SEC_KEY_REQ (0b11101111)     
//Enables the half symbol timer interrupt
#define MRF24J40_EN_HALF_SYMB_TIMER (0b11011111) 
//Enables the wake-up alert interrupt
#define MRF24J40_EN_WAKE_UP_INT (0b10111111)     
//Enables the Sleep alert interrupt
#define MRF24J40_EN_SLEEP_ALERT_INT (0b01111111) 

/* TX power levels masks */
#define MRF24J40_TXPWRL_0dB 0x00
#define MRF24J40_TXPWRL_MINUS_10dB 0x01
#define MRF24J40_TXPWRL_MINUS_20dB 0x02
#define MRF24J40_TXPWRL_MINUS_30dB 0x03
#define MRF24J40_TXPWRS_0dB 0x00
#define MRF24J40_TXPWRS_MINUS0_5dB 0x01
#define MRF24J40_TXPWRS_MINUS1_2dB 0x02
#define MRF24J40_TXPWRS_MINUS1_9dB 0x03
#define MRF24J40_TXPWRS_MINUS2_8dB 0x04
#define MRF24J40_TXPWRS_MINUS3_7dB 0x05
#define MRF24J40_TXPWRS_MINUS4_9dB 0x06
#define MRF24J40_TXPWRS_MINUS6_3dB 0x07

/* TX power setting generation:
 * tx_pwr_set(large_val, samll_val) computes the value for the RFCON3 register.
 * Examples: 
 * - if we want to set tx power to -11,2 dB then: 
 *   mrf24j40_tx_pwr_set(TXPWRL_MINUS_10dB, TXPWRS_MINUS1_2dB).
 * - if we want to set the tx power to -4,9 dB then:
 *   mrf24j40_tx_pwr_set(TXPWRL_0dB, TXPWRS_MINUS4_9dB).
 * - if we want to set the tx power to -20 dB then:
 *   mrf24j40_tx_pwr_set(TXPWRL_MINUS_20dB, TXPWRS_0dB 0x00).
 */
#define MRF24J40_TX_PWR_SET(large_val, small_val)\
	((large_val << 6) | (small_val << 3))

#ifndef __LM32__
typedef union _TX_status {
	uint8_t val;
	struct TX_bits {
		uint8_t TXNSTAT: 1;
		uint8_t TXG1STAT: 1;
		uint8_t TXG2STAT: 1;
		uint8_t TXG1FNT: 1;
		uint8_t TXG2FNT: 1;
		uint8_t CCAFAIL: 1;
		uint8_t TXNRETRY: 2;
	}bits; 
}TX_status;

typedef union _INT_status {
	uint8_t val;

	struct INT_bits {
		uint8_t TXNIF: 1;
		uint8_t TXG1IF: 1;
		uint8_t TXG2IF: 1;
		uint8_t RXIF: 1;
		uint8_t SECIF: 1;
		uint8_t HSYMTMRIF: 1;
		uint8_t WAKEIF: 1;
		uint8_t SLPIF: 1;
	}bits; 

}INT_status;
#else /* different types because of LM32 endianness */
typedef union _TX_status {
	uint8_t val;
	struct TX_bits {
		uint8_t TXNRETRY: 2;
		uint8_t CCAFAIL: 1;
		uint8_t TXG2FNT: 1;
		uint8_t TXG1FNT: 1;
		uint8_t TXG2STAT: 1;
		uint8_t TXG1STAT: 1;
		uint8_t TXNSTAT: 1;
	}bits; 
}TX_status;

typedef union _INT_status {
	uint8_t val;

	struct INT_bits {
		uint8_t SLPIF: 1;
		uint8_t WAKEIF: 1;
		uint8_t HSYMTMRIF: 1;
		uint8_t SECIF: 1;
		uint8_t RXIF: 1;
		uint8_t TXG2IF: 1;
		uint8_t TXG1IF: 1;
		uint8_t TXNIF: 1;
	}bits; 

}INT_status;
#endif //#ifndef __LM32__

/**
* Write val in the short address register addr
*/
COMPILER_INLINE void mrf24j40_set_short_add_mem(uint8_t addr, uint8_t val)
{
	uint8_t tmp = mrf24j40_hal_irq_status();
	uint8_t msg[2];
    
	mrf24j40_hal_irq_disable();
	mrf24j40_hal_csn_low();
	msg[0] = (addr << 1) | 0x01;
	msg[1] = val;
	mrf24j40_hal_spi_write(msg, 2);
	mrf24j40_hal_csn_high();
	if (tmp) 
		mrf24j40_hal_irq_enable();
}

/**
* Write val in the long address register addr
*/
COMPILER_INLINE void mrf24j40_set_long_add_mem(uint16_t addr, uint8_t val)
{
	uint8_t tmp = mrf24j40_hal_irq_status();
	uint8_t msg[3];

	mrf24j40_hal_irq_disable();
	mrf24j40_hal_csn_low();
	msg[0] = (((uint8_t)(addr >> 3)) & 0x7F) | 0x80;
	msg[1] = (((uint8_t)(addr << 5)) & 0xE0) | 0x10;
	msg[2] = val; 
	mrf24j40_hal_spi_write(msg, 3);
	mrf24j40_hal_csn_high();
	if (tmp) 
		mrf24j40_hal_irq_enable();
}

/**
* Read the short address register addr
*/
COMPILER_INLINE uint8_t mrf24j40_get_short_add_mem(uint8_t addr)
{
	uint8_t ret_val;
	uint8_t tmp = mrf24j40_hal_irq_status();
	
	mrf24j40_hal_irq_disable();
	mrf24j40_hal_csn_low();
	addr <<= 1;
	mrf24j40_hal_spi_write(&addr, 1);
	mrf24j40_hal_spi_read(&ret_val, 1);
	mrf24j40_hal_csn_high();

	//while(ret_val !=0);
	
	if (tmp) 
		mrf24j40_hal_irq_enable();
	return ret_val;

}

/**
* Read the long address register addr
*/
COMPILER_INLINE uint8_t mrf24j40_get_long_add_mem(uint16_t addr)
{
	uint8_t ret_val;
	uint8_t tmp = mrf24j40_hal_irq_status();
	uint8_t msg[2];
	
	mrf24j40_hal_irq_disable();
	mrf24j40_hal_csn_low();
	msg[0] = (((uint8_t)(addr >> 3)) & 0x7F) | 0x80;
	msg[1] = ((uint8_t)(addr << 5)) & 0xE0;
	mrf24j40_hal_spi_write(msg, 2);
	mrf24j40_hal_spi_read(&ret_val, 1);
	mrf24j40_hal_csn_high();
	if (tmp) 
		mrf24j40_hal_irq_enable();
	return ret_val;
}

/**
* @brief Flush the rx fifo
*
* This routine flushes the rx fifo
*
*/
COMPILER_INLINE void mrf24j40_flush_rx_fifo(void)
{
	mrf24j40_set_short_add_mem(MRF24J40_RXFLUSH, 0x01);
}

/**
* @brief Flush the rx fifo
*
* This routine flushes the rx fifo
*
*/
COMPILER_INLINE void mrf24j40_set_channel(uint8_t ch)
{   

	//mrf24j40_set_long_add_mem(MRF24J40_RFCON0, ((ch - 11) << 4) | 0x02);
	
	mrf24j40_set_long_add_mem(MRF24J40_RFCON0, (ch | 0x03));
	/**
	* Reset RF state machine as suggested by the datasheet
	*/ 
	mrf24j40_set_short_add_mem(MRF24J40_RFCTL, 0x04);
	mrf24j40_set_short_add_mem(MRF24J40_RFCTL, 0x00);

	//mrf24j40_hal_delay_us(200);
}

/**
* @brief Store short MAC address
*
* This routine sets the short MAC address in the MRF24J40.
*
* @param[in] addr The short MAC address to store in the transceiver.
*
*/
COMPILER_INLINE void mrf24j40_set_short_MAC_addr(uint16_t addr)
{
	mrf24j40_set_short_add_mem(MRF24J40_SADRL, (uint8_t)addr);
	mrf24j40_set_short_add_mem(MRF24J40_SADRH, (uint8_t)(addr>>8));
}

/**
* @brief Store MAC PAN ID
*
* This routine sets the MAC PAN ID in the MRF24J40.
*
* @param[in] id The MAC PAN ID to store in the transceiver.
*
*/
COMPILER_INLINE void mrf24j40_set_PAN_id(uint16_t id)
{
	mrf24j40_set_short_add_mem(MRF24J40_PANIDL, (uint8_t)id);
	mrf24j40_set_short_add_mem(MRF24J40_PANIDH, (uint8_t)(id>>8));
}

/**
* @brief Store extended MAC address
*
* This routine sets the extended MAC address in the MRF24J40.
*
* @param[in] addr The extended MAC address to store in the transceiver.
*
 */
COMPILER_INLINE void mrf24j40_set_ex_MAC_addr(uint64_t addr)
{
	mrf24j40_set_short_add_mem(MRF24J40_EADR0, (uint8_t)addr);
	mrf24j40_set_short_add_mem(MRF24J40_EADR1, (uint8_t)(addr>>8));
	mrf24j40_set_short_add_mem(MRF24J40_EADR2, (uint8_t)(addr>>16));
	mrf24j40_set_short_add_mem(MRF24J40_EADR3, (uint8_t)(addr>>24));
	mrf24j40_set_short_add_mem(MRF24J40_EADR4, (uint8_t)(addr>>32));
	mrf24j40_set_short_add_mem(MRF24J40_EADR5, (uint8_t)(addr>>40));
	mrf24j40_set_short_add_mem(MRF24J40_EADR6, (uint8_t)(addr>>48));
	mrf24j40_set_short_add_mem(MRF24J40_EADR7, (uint8_t)(addr>>56));
}

/**
* @brief Start trasmission
*
* This routine starts the transmission of a msg by the MRF24J40.
*/
COMPILER_INLINE void mrf24j40_set_tx()
{
	/**
	Transmit the packet from the Normal TX FIFO.
	Transmit without security and ack request.
	Transmit with frame pending bit=0.
	Indirect transmit disabled. 
	*/

	mrf24j40_set_short_add_mem(MRF24J40_TXNCON, 0x01);
	//mrf24j40_dbg_print("\n\rTXDONE!");
}

/**
* @brief Set TX power
*
* This routine sets the transmission power of the MRF24J40.
*
* @param[in] pwr 	The TX power.
*
* Note: the value of pwr can be calculated using the macro tx_pwr_set and the
* related masks defined above in this file (mrf24j40.h).
*/
COMPILER_INLINE void mrf24j40_set_pa(uint8_t pwr)
{
	mrf24j40_set_long_add_mem(MRF24J40_RFCON3, pwr);	
}

/**
* @brief Get radio TX power
*
* This routine returns the transmission power of the MRF24J40.
*
* @return The MRF24J40 tx power.
*
*/
COMPILER_INLINE uint8_t mrf24j40_get_pa()
{
	return mrf24j40_get_long_add_mem(MRF24J40_RFCON3);
}

/**
* @brief Get radio status
*
* This routine returns the MRF24J40 status.
*
* @return The MRF24J40 status.
*/
COMPILER_INLINE uint8_t mrf24j40_get_status()
{ 
	return mrf24j40_get_long_add_mem(MRF24J40_RFSTATE);
}

/**
* @brief Get the RSSI
*
* This routine returns the rssi value mesured in dbm
*
* @return the rssi value in the range 0 - 255.
*
* Note: to convert the returned value to dBm, use the table 3-8 available
* in the MRF24J40 datasheet.  
*/
COMPILER_INLINE uint8_t mrf24j40_get_rssi()
{
	/* Initiate RSSI calculation */
	#ifdef ADD_RSSI_AND_LQI_TO_PACKET
	mrf24j40_set_short_add_mem(MRF24J40_BBREG6, 0xC0);
	#else
	mrf24j40_set_short_add_mem(MRF24J40_BBREG6, 0x40); 
	#endif
	/* Wait until RSSI calculation is done */
	while (!(mrf24j40_get_short_add_mem(MRF24J40_BBREG6) & 0x01));
	return mrf24j40_get_long_add_mem(MRF24J40_RSSI);
}

/**
* @brief Set the CSMA parameters
*
* This routine sets the parameters of the CSMA algorithm.
*
* @param[in] be Backoff Exponent
* @param[in] nb Number of Backoff
*
*/
COMPILER_INLINE void mrf24j40_set_CSMA_par(uint8_t be, uint8_t nb)
{
	if (nb > 5)
		nb = 5;
	if (be > 3)
		be = 3;
	#ifdef BEACON_ENABLED_MODE
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, 0x20 | nb | (be << 3));
	#else
	mrf24j40_set_short_add_mem(MRF24J40_TXMCR, nb | (be << 3));
	#endif
}

/**
* @brief Set minimum Short InterFrame Spacing (SIFS)
*
* This routine sets SIFS.
*
* @param[in] val The SIFS value.
*
*/
COMPILER_INLINE void mrf24j40_set_sifs(uint8_t val)
{
	if (val > 15)
		val = 15;
	mrf24j40_set_short_add_mem(MRF24J40_TXSTBL, val | 0x90);
}

/**
* @brief Set minimum Long InterFrame Spacing (LIFS)
*
* This routine sets LIFS.
*
* @param[in] val The LIFS value.
*
*/
COMPILER_INLINE void mrf24j40_set_lifs(uint8_t val)
{
	uint8_t old_txpend = mrf24j40_get_short_add_mem(MRF24J40_TXPEND);
	
	old_txpend &= 0x03;
	if (val > 63)
		val = 63;
	mrf24j40_set_short_add_mem(MRF24J40_TXPEND, old_txpend | (val << 2));
}

#endif
