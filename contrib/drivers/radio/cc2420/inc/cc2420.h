/**
* @file cc2420_compiler.h
* @brief CC2420 Abstract Compiler
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* File Contents: a set of macros to support the management of the
* EasyBee/CC2420 radio transceiver.
*
* Main documentation:
* <CC2420_Data_Sheet_1_3.pdf> The CC2420 datasheet. Available at www.ti.com
* <EasyBeeDS480.pdf> EasyBee board datasheet. Available at www.rfsolutions.co.uk
* <Flex_ref_man_027.pdf> Flex reference Manual. Available at erika.tuxfamily.org
*
* Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
* Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
*
*/

#ifndef _CC2420_H_
#define _CC2420_H_

#include <cc2420_compiler.h>
#include <cc2420_hal.h>

#ifdef CC2420_DEBUG
#include "console_serial.h"
#define DEBUG_PORT 0
#define debug_print(msg) 	console_write(DEBUG_PORT, msg, strlen(msg));
#endif /* CC2420_DEBUG */

/**
* @brief Stobe and CSn
*
* This routine stobes a command and uses the CSn pin of the radio.
*
* @param[in] cmd 	The command
*/
#define CC2420_STROBE_CMD_CSn(cmd){\
	CC2420_CSn_0();\
	cc2420_spi_put(cmd, NULL);\
	CC2420_CSn_1();\
}

/**
* @brief Stobe a command
*
* This routine stobes a command
*
* @param[in] cmd 	The command
*/
#define CC2420_STROBE_CMD(cmd) {\
	cc2420_spi_put(cmd, NULL);\
}

/**
* @brief Write Register and CSn
*
* This routine writes a register and uses the CSn pin of the radio.
*
* @param[in] reg 		The register
* @param[in] high_byte 	The high byte
* @param[in] low_byte	The low bype
*/
#define CC2420_REG_WRITE_CSn(reg, high_byte, low_byte){\
	CC2420_CSn_0();\
	cc2420_spi_put(reg, NULL);\
	cc2420_spi_put(high_byte, NULL);\
	cc2420_spi_put(low_byte, NULL);\
	CC2420_CSn_1();\
}

/**
* @brief Write Register
*
* This routine writes a register.
*
* @param[in] reg 		The register
* @param[in] high_byte 	The high byte
* @param[in] low_byte	The low bype
*/
#define CC2420_REG_WRITE(reg, high_byte, low_byte){\
	cc2420_spi_put(reg, NULL);\
	cc2420_spi_put(high_byte, NULL);\
	cc2420_spi_put(low_byte, NULL);\
}

/**
* @brief Read Register and CSn
*
* This routine reads a register and uses the CSn pin of the radio.
*
* @param[in] reg 		The register
* @param[in] high_byte 	The high byte
* @param[in] low_byte	The low bype
*/
#define CC2420_REG_READ_CSn(reg, high_byte, low_byte){\
	CC2420_CSn_0();\
	cc2420_spi_put(reg | CC2420_CMD_READ, NULL);\
	cc2420_spi_get(&(high_byte));\
	cc2420_spi_get(&(low_byte));\
	CC2420_CSn_1();\
}

/**
* @brief Read Register
*
* This routine reads a register.
*
* @param[in] reg 		The register
* @param[in] high_byte 	The high byte
* @param[in] low_byte	The low bype
*/
#define CC2420_REG_READ(reg, high_byte, low_byte){\
	cc2420_spi_put(reg | CC2420_CMD_READ, NULL);\
	cc2420_spi_get(&(high_byte));\
	cc2420_spi_get(&(low_byte));\
}


/**
* @brief Flush RX
*
* This routine slushes the RX FIFO buffer.
*
*/
#define CC2420_RX_FIFO_FLUSH(){\
	CC2420_CSn_0();\
	cc2420_spi_put(CC2420_REG_RXFIFO | CC2420_CMD_READ, NULL);\
	cc2420_spi_get(NULL);\
	CC2420_CSn_1();\
	CC2420_CSn_0();\
	cc2420_spi_put(CC2420_STROBE_SFLUSHRX, NULL);\
	cc2420_spi_put(CC2420_STROBE_SFLUSHRX, NULL);\
	CC2420_CSn_1();\
}

/**
* @brief Flush TX
*
* This routine slushes the TX FIFO buffer.
*cc2420_spi_put(CC2420_STROBE_SFLUSHTX, NULL);\
*/
#define CC2420_TX_FIFO_FLUSH(){\
	CC2420_CSn_0();\
	cc2420_spi_put(CC2420_STROBE_SFLUSHTX, NULL);\
	CC2420_CSn_1();\
}

/**
* @brief CSn up
*
* This routine sets the CSn pin high.
*
*/
#define CC2420_CSn_1()	CC2420_SET_PIN(CC2420_CSn)

/**
* @brief CSn down
*
* This routine sets the CSn pin down.
*
*/
#define CC2420_CSn_0()	CC2420_CLEAR_PIN(CC2420_CSn)

/**
* This constant is used to compute the receiving power
* as given  by the CC2420 datasheet on pag 49.
*/
#define CC2420_RSSI_OFFSET (-45) /* -45 dbm */

#define CC2420_INVALID_RSSI -128

#define CC2420_DETECT 0
#define CC2420_UNDETECT 1

#define CC2420_FCS_LENGTH 2

#define CC2420_RADIO_SLEEP 0
#define CC2420_RADIO_IDLE 1


/**
* \name CC2420 Power constants
*
*   The following macros define the values to pass to the function
*   void cc2420_set_pa(uint8_t power).
*
*          According to Table 9 of CC2420 datasheet
*\code
*          PA_LEVEL (TXCTRL.LSB)       Output Power (dBm)  Current Consumption
*          ====================================================================
*          0xFF                        0                   17.4 mA
*          0xFB                        -1                  16.5 mA
*          0xF7                        -3                  15.2 mA
*          0xF3                        -5                  13.9 mA
*          0xEF                        -7                  12.5 mA
*          0xEB                        -10                 11.2 mA
*          0xE7                        -15                 9.9 mA
*          0xE3                        -25                 8.5 mA
*\endcode
*\{
*/
#define CC2420_PA_0DBM	0xFF
#define CC2420_PA_MINUS1DBM	0xFB
#define CC2420_PA_MINUS3DBM	0xF7
#define CC2420_PA_MINUS5DBM	0xF3
#define CC2420_PA_MINUS7DBM	0xEF
#define CC2420_PA_MINUS10DBM 0xEB
#define CC2420_PA_MINUS15DBM 0xE7
#define CC2420_PA_MINUS25DBM 0xE3
#define CC2420_PA_MAXIMUM CC2420_PA_0DBM
/** \}
*/

/**
* \name CC2420 specific command set
* \{
*/
#define CC2420_STROBE_SNOP     (0x00)
#define CC2420_STROBE_SXOSCON  (0x01)
#define CC2420_STROBE_STXCAL   (0x02)
#define CC2420_STROBE_SRXON    (0x03)
#define CC2420_STROBE_STXON    (0x04)
#define CC2420_STROBE_STXONCCA (0x05)
#define CC2420_STROBE_SRFOFF   (0x06)
#define CC2420_STROBE_SXOSCOFF (0x07)
#define CC2420_STROBE_SFLUSHRX (0x08)
#define CC2420_STROBE_SFLUSHTX (0x09)
#define CC2420_STROBE_SACK     (0x0a)
#define CC2420_STROBE_SACKPEND (0x0b)
#define CC2420_STROBE_SRXDEC   (0x0c)
#define CC2420_STROBE_STXENC   (0x0d)
#define CC2420_STROBE_SAES     (0x0e)
/** \}
*/

/**
* \name CC2420 specific registers
* \{
*/
#define CC2420_REG_MAIN        (0x10)
#define CC2420_REG_MDMCTRL0    (0x11)
#define CC2420_REG_MDMCTRL1    (0x12)
#define CC2420_REG_RSSI        (0x13)
#define CC2420_REG_SYNCWORD    (0x14)
#define CC2420_REG_TXCTRL      (0x15)
#define CC2420_REG_RXCTRL0     (0x16)
#define CC2420_REG_RXCTRL1     (0x17)
#define CC2420_REG_FSCTRL      (0x18)
#define CC2420_REG_SECCTRL0    (0x19)
#define CC2420_REG_SECCTRL1    (0x1a)
#define CC2420_REG_BATTMON     (0x1b)
#define CC2420_REG_IOCFG0      (0x1c)
#define CC2420_REG_IOCFG1      (0x1d)
#define CC2420_REG_MANFIDL     (0x1e)
#define CC2420_REG_MANFIDH     (0x1f)
#define CC2420_REG_FSMTC       (0x20)
#define CC2420_REG_MANAND      (0x21)
#define CC2420_REG_MANOR       (0x22)
#define CC2420_REG_AGCCTRL     (0x23)
#define CC2420_REG_AGCTST0     (0x24)
#define CC2420_REG_AGCTST1     (0x25)
#define CC2420_REG_AGCTST2     (0x26)
#define CC2420_REG_FSTST0      (0x27)
#define CC2420_REG_FSTST1      (0x28)
#define CC2420_REG_FSTST2      (0x29)
#define CC2420_REG_FSTST3      (0x2a)
#define CC2420_REG_RXBPFTST    (0x2b)
#define CC2420_REG_FSMSTATE    (0x2c)
#define CC2420_REG_ADCTST      (0x2d)
#define CC2420_REG_DACTST      (0x2e)
#define CC2420_REG_TOPTST      (0x2f)
#define CC2420_REG_TXFIFO      (0x3e)
#define CC2420_REG_RXFIFO      (0x3f)
/** \}
*/

#define CC2420_CMD_WRITE       (0)
#define CC2420_CMD_READ        (0x40)

#define CC2420_CMD_RAM_RW      (0x00)
#define CC2420_CMD_RAM_R       (0x20)

//RAM registers are accessed using two bytes - 7-bit address and 2-bit bank address.
// 0x80 sets MSb to indicate RAM access.
#define CC2420_RAM_ADDR_LSB(a) (((a) & 0xff) | 0x80)
#define CC2420_RAM_ADDR_BANK(a) (((a) >> 1) & 0xc0)

#define CC2420_RAM_TXFIFO      CC2420_RAM_ADDR_LSB(0x000)
#define CC2420_RAM_TXFIFO_BANK CC2420_RAM_ADDR_BANK(0x000)

#define CC2420_RAM_RXFIFO      CC2420_RAM_ADDR_LSB(0x080)
#define CC2420_RAM_RXFIFO_BANK CC2420_RAM_ADDR_BANK(0x080)

#define CC2420_RAM_KEY0        ((0x100 & 0xff) | 0x80)
#define CC2420_RAM_KEY0_BANK   (0x100 >> 1)

#define CC2420_RAM_RXNONCE     ((0x110 & 0xff) | 0x80)
#define CC2420_RAM_RXNONCE_BANK (0x110 >> 1)

#define CC2420_RAM_SABUF       CC2420_RAM_ADDR_LSB(0x120)     // to 0x12F
#define CC2420_RAM_SABUF_BANK  CC2420_RAM_ADDR_BANK(0x120)

#define CC2420_RAM_KEY1        CC2420_RAM_ADDR_LSB(0x130)     // to 0x13f
#define CC2420_RAM_KEY1_BANK   CC2420_RAM_ADDR_BANK(0x130)

#define CC2420_RAM_TXNONCE     CC2420_RAM_ADDR_LSB(0x140)     // to 0x14f
#define CC2420_RAM_TXNONCE_BANK CC2420_RAM_ADDR_BANK(0x140)

#define CC2420_RAM_CBCSTATE    CC2420_RAM_ADDR_LSB(0x150)     // to 0x15f
#define CC2420_RAM_CBCSTATE_BANK CC2420_RAM_ADDR_BANK(0x150)

#define CC2420_RAM_IEEEADR     CC2420_RAM_ADDR_LSB(0x160)     // to 0x167
#define CC2420_RAM_IEEEADR_BANK CC2420_RAM_ADDR_BANK(0x160)

#define CC2420_RAM_PANID       CC2420_RAM_ADDR_LSB(0x168)     // to 0x169
#define CC2420_RAM_PANID_BANK  CC2420_RAM_ADDR_BANK(0x168)


#define CC2420_RAM_SHORTADR    CC2420_RAM_ADDR_LSB(0x16a)     // to 0x16b
#define CC2420_RAM_SHORTADR_BANK CC2420_RAM_ADDR_BANK(0x16a)


#define CC2420_BUFFER_SIZE 127

typedef union _radio_status
{
    struct
    {
        uint8_t :1; //reserved
        uint8_t rssi_valid : 1;
        uint8_t lock : 1;
        uint8_t tx_active : 1;
        uint8_t enc_busy : 1;
        uint8_t tx_underflow : 1;
        uint8_t xosc16m_stable : 1;
        uint8_t :1; //reserved
    } bits;
    uint8_t val;
} cc2420_radio_status;

/**
* @brief Init transceiver
*
* @param port \todo Reference
*
* This routine initializes the radio transceiver
*
* @return 1 if the initialization goes well, -1 otherwise.
*/
int8_t cc2420_radio_init(uint8_t port);

/**
* @brief Release the transceiver
*
* \todo Write more.
*
* @return 1 if the close goes well, -1 otherwise.
*/
int8_t 	cc2420_close(void);

/**
* @brief \todo
*
* @param func
*/
void cc2420_set_rx_callback(void (*func)(void));

/**
* @brief Set TX power
*
* This routine sets the transmission power of the CC2420.
*
* @param[in] power 	The TX power.
*/
void	cc2420_set_pa(uint8_t);

/**
* @brief Get radio status
*
* This routine returns the CC2420 status.
*
* @return The CC2420 status.
*/
uint8_t cc2420_get_status(void);

/**
* @brief Get message
*
* This routine is used by the routine that manages the interrupt raised
* by the fifop pin.
*
* @param[in] *fifo_msg 	The buffer where to store the message from the FIFO
*
* @return the lenght of the received message
*
* @pre	The pin FIFOP from the CC2420 is connected to an interrupt pin of
*	the used microcontroller.
*/
int8_t	cc2420_get_fifo_msg(uint8_t*);

/**
* @brief Get the RSSI
*
* This routine returns the rssi value mesured in dBm
*
* @return the rssi value in dbm, INVALID_RSSI otherwise
 */
int8_t	cc2420_rssi_get(void);

/**
* @brief Check the transceiver
*
* This routine check the presence of the transceiver.
*
* @return CC2420_DETECT if CC2420 is present, CC2420_UNDETECT otherwise
*
* @note 	Pay attention: check in the datasheet the CC2420 codes in
* 		C2420_REG_MANFIDL.
 */
int8_t	cc2420_check(void);

/**
* @brief Check the FSM status
*
* This routine returns the status of the FSM inside the CC2420.
*
* @return the status of the FSM inside the CC2420
 */
uint8_t	cc2420_FSM_get(void);

/**
* @brief Store message
*
* This routine stores a message in the TX_FIFO buffer of the CC2420.
*
* @param[in] *msg 	The message pointer
* @param[in] msg_legth 	The message lenght
*/
void	cc2420_store_msg(uint8_t*, uint8_t);

/**
* @brief Store message
*
* This routine stores a buffer of buf_length bytes in the
* TX_FIFO buffer of the CC2420.
*
* @param[in] *buf 	The message pointer
* @param[in] buf_legth 	The message lenght
*/
void	cc2420_store_txfifo(uint8_t*, uint8_t);

/**
* @brief Start trasmission
*
* This routine starts the transmission of a msg by the CC2420.
*/
void	cc2420_set_tx(void);

/**
* @brief Start trasmission in CSMA
*
* This routine starts the transmission of a msg by the CC2420 if the
* channel is clear (CSMA mode).
*
* @return \todo Write doc for this return.
*/
uint8_t	cc2420_set_tx_on_cca(void);

/**
* @brief Start receiving
*
* This routine puts the radio in RX mode.
 */
void	cc2420_set_rx(void);

/**
* @brief Start sleep
*
* This routine puts the radio in sleep mode.
*
* @param[in] sleep_level 	The sleep mode: POWER_DOWN or IDLE
*
 */
void	cc2420_set_sleep(int16_t);

/**
* @brief Start the radio
*
* This routine turns on the radio starting the oscillator.
*
* @note		After performing this routine the radio is in the idle state.
*
* @warning	If no radio is present the system is blocked in a infinite loop!
*/
void	cc2420_turn_on(void);

/**
* @brief Set channel
*
* This routine sets the channel to tune in the CC2420.
*
* @param[in] ch The channel to tune in (must be in the interval [11, 26])
*
 */
void	cc2420_set_channel(uint8_t);

/**
* @brief Store short MAC address
*
* This routine sets the short MAC address in the CC2420.
*
* @param[in] add 	The short MAC address to store in the transceiver.
*
*/
void	cc2420_set_short_mac_add(uint8_t*);

/**
* @brief Store extended MAC address
*
* This routine sets the extended MAC address in the CC2420.
*
* @param[in] add 	The extended MAC address to store in the transceiver.
*
 */
void	cc2420_set_ex_mac_add(uint8_t*);

/**
* @brief Store MAC PAN ID
*
* This routine sets the MAC PAN ID in the CC2420.
*
* @param[in] id 	The MAC PAN ID to store in the transceiver.
*
 */
void	cc2420_set_mac_pan_id(uint8_t*);


#endif
