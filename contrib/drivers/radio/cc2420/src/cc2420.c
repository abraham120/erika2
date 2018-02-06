/**
* @file cc2420.c
* @brief CC2420 Driver
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* File Contents: a set of functions to manage the EasyBee/CC2420
* radio transceiver.
*
* \todo Reformat the following text using doxygen
*
* Main documentation:
* <CC2420_Data_Sheet_1_3.pdf> The CC2420 datasheet. Available at www.ti.com
* <EasyBeeDS480.pdf> EasyBee board datasheet. Available at www.rfsolutions.co.uk
* <Flex_ref_man_027.pdf> Flex reference Manual. Available at erika.tuxfamily.org
* <70286A.pdf> The dsPIC33 datasheet. Available at www.microchip.com
*
* Author: Gianluca Franchino.
* Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
* Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
* Date: 02/27/2008.
*
 */

#include <cc2420.h>

/*chris: TODO: Choose a proper policy for the 'is_initialized' status variable,
		we have to use it in some function!!
*/
static uint8_t radio_initialized = 0;
static void (* volatile rx_callback)(void) = NULL;

void cc2420_set_rx_callback(void (*func)(void))
{
	rx_callback = func;
}

int8_t cc2420_radio_init(uint8_t port)
{
	int8_t retv;

	/*chris: do I need this chek? This currently avoid the init func to
		 be called twice!
	*/
	if (radio_initialized)
		return -2;
	/* init hal-specific things */
	cc2420_hal_init();

	retv = cc2420_spi_init(port);
	/*TODO; manage error code*/
	if (retv < 0)
		return -1;

	CC2420_CLEAR_PIN(CC2420_RESETn);//CC2420_RESETn = 0;
	CC2420_SET_PIN(CC2420_VREG_EN);//CC2420_VREG_EN = 1;
	cc2420_delay_us(1000);
	CC2420_SET_PIN(CC2420_RESETn);//CC2420_RESETn = 1;
	cc2420_delay_us(2000);

	/* turn on the crystal oscillator */
  	cc2420_turn_on();
	//hal_console_out('B');
	if (cc2420_check() == CC2420_UNDETECT)
		return -1;

	/*active CC2420 spi to set up the registers */
	CC2420_CSn_0();
	/* set up REG_MDMCTRL0
	 * 15:14 = '00'  = Reserved
	 * 13    = '0'   = Reserved frames are rejected
	 * 12    = '?'   = '1' if this is coordinator, '0' if otherwise
	 * 11    = '0'   = Address decoding is disabled
	 * 10:8  = '010' = CCA Hysteresis in DB - default value
	 * 7:6   = '11'  = CCA = 1, when RSSI_VAL < CCA_THR - CCA_HYST and not
	 *		   receiving valid IEEE 802.15.4 data
	 * 5     = '0'   = Auto CRC
	 * 4     = '0'   = Auto ACK
	 * 3:0   = '0010' = 3 leading zero bytes - IEEE compliant.
	 */
/* chris: What is this? This MUST NOT STAY IN THE DRIVER CODE!!! */
#if defined(COORDINATOR) /*chris: TODO: Don't use the AUTO CRC, 
					fix the COORDINATOR define!!! */
	/* MSB = 0b0001 0010 */
	/* LSB = 0b1100 0010 */
	//CC2420_REG_WRITE(CC2420_REG_MDMCTRL0, 0x12, 0xC2);
	CC2420_REG_WRITE(CC2420_REG_MDMCTRL0, 0x12, 0xE2);
	//CC2420_REG_WRITE(CC2420_REG_MDMCTRL0, 0x1A, 0xE2);
#else
	/* MSB = 0b0000 0010 */
	/* LSB = 0b1100 0010 */
	//CC2420_REG_WRITE(CC2420_REG_MDMCTRL0, 0x02, 0xC2);
	CC2420_REG_WRITE(CC2420_REG_MDMCTRL0, 0x02, 0xE2);
	//CC2420_REG_WRITE(CC2420_REG_MDMCTRL0, 0x1A, 0xE2);
#endif

	/* set up REG_MDMCTRL1
	 * 15:11  = '000000' = Reserved
	 * 10:6  = '10100'= 20 -> Demodulator threshold value set has indicated
	 *			  by the data sheet
	 * 5     = '0'   = Lock frequency offset filter after preamble match
	 * 4     = '0'   = Modulation mode set IEEE 802.15.4 compliant
	 * 3:2   = '00'  = Buffered mode -> use TXFIFO
	 * 1:0   = '0'   = Buffered mode -> use RXFIFO
	 */
	CC2420_REG_WRITE(CC2420_REG_MDMCTRL1, 0x05, 0x00);

	/* disable the MAC level security */

	/* set up REG_SECCTRL0
	 * 15:10  = '000000' = Reserved
	 * 9     = '0'   = Protection enable of the RXFIFO -> disabled
	 * 8     = '1'   = see data sheet
	 * 7     = '1'   = Stand alone key select -> key 1 is used
	 * 6     = '1'   = TX key select -> key 1 is selected
	 * 5     = '0'   = RX key select -> key 0 is used
	 * 4:2   = '001' = Number of bytes in authentication field for CBC_MAC,
	 *		   encoded as (M-2)/2 -> 4
	 * 1:0   = '0'   = In-line security is disabled
	 */
	CC2420_REG_WRITE(CC2420_REG_SECCTRL0, 0x01, 0xC4);

	/* Set FIFOP threshold to full RXFIFO buffer*/

	/* set up REG_IOCFG0
	 * 15:12  = '000000' = Reserved
	 * 11     = '0'      = Only accept beacons with a source PAN identifier
	 *			which mach the PAN identifier programmed into
	 *			CC2420 RAM. Note that, this bit is do not care
	 *			when MDMCTRL0.ADR_DECODE = 0;
	 * 10     = '0'      = Polarity of the FIFO pin
	 * 9     = '0'       = Polarity of the FIFOP pin
	 * 8     = '0'       = Polarity of the SFD pin
	 * 7     = '0'       = Polarity of the CCA pin
	 * 6:0   = '1111111' = FIFOP threshold equal to 127
	 */
	CC2420_REG_WRITE(CC2420_REG_IOCFG0, 0x00, 0x7F);

	/*disable CC2420 spi to set up the registers */
	CC2420_CSn_1();

	/* set tx power equal to the maximum value */
	cc2420_set_pa(CC2420_PA_MAXIMUM);

	/* Flush the TX FIFO */
	CC2420_STROBE_CMD_CSn(CC2420_STROBE_SFLUSHTX);

	/* Flush the RX FIFO */
	CC2420_RX_FIFO_FLUSH();
	
	return 1;
}

int8_t cc2420_radio_close(void)
{
	/*chris: TODO: Do we need a body in here??? */
	radio_initialized = 0;
	return cc2420_spi_close();
}

void cc2420_set_pa(uint8_t power)
{
/*          According to Table 9 of CC2420 datasheet
 *
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
 */

	/* Select desired TX output power level */
	CC2420_REG_WRITE_CSn(CC2420_REG_TXCTRL, 0xA0, power);
	radio_initialized = 1;
}
uint8_t cc2420_get_status()
{
	cc2420_radio_status status;
	CC2420_CSn_0();
	cc2420_spi_get(&(status.val));
///* TODO REMOVE----------> */
//char s[100];
//sprintf(s, "         status.val = %X", (uint16_t) status.val);
//ozb_debug_print(s);
///* <---------- TODO REMOVE */
	CC2420_CSn_1();
	return status.val;
}

void cc2420_store_msg(uint8_t *msg, uint8_t msg_length)
{
	uint8_t i, high_byte, low_byte;

	if (msg_length > 127)
		return;
	CC2420_REG_READ_CSn(CC2420_REG_MDMCTRL0, high_byte, low_byte);
	CC2420_CSn_0();
	cc2420_spi_put(CC2420_REG_TXFIFO, NULL);
	if (low_byte & 0x20)
		cc2420_spi_put(msg_length + CC2420_FCS_LENGTH, NULL);
	else
		cc2420_spi_put(msg_length, NULL);

	for (i = 0; i < msg_length; i++) {
		cc2420_spi_put(msg[i], NULL);
	}
	CC2420_CSn_1();
}

void cc2420_store_txfifo(uint8_t *buf, uint8_t buf_length)
{
	uint8_t i;

	if (buf_length > 127)
		return;
	CC2420_CSn_0();
	cc2420_spi_put(CC2420_REG_TXFIFO, NULL);
	for (i = 0; i < buf_length; i++)
		cc2420_spi_put(buf[i], NULL);
	CC2420_CSn_1();
}

int8_t cc2420_get_fifo_msg(uint8_t *fifo_msg)
{
	uint8_t i;

#ifndef __XBOW_MIB5X0__ /* TODO: adopted to port EE+uWireless on MicaZ! */
//#ifndef __USE_MOTIONBOARD__ /* TODO: adopted for EUROLAB 2009, bugged board */
	if (CC2420_GET_PIN(CC2420_FIFO) == 0) { //if (CC2420_FIFO == 0) {
		CC2420_RX_FIFO_FLUSH();
		//hal_console_out('F');
		return -1;
	}
#endif
	CC2420_CSn_0();
	cc2420_spi_put(CC2420_REG_RXFIFO | CC2420_CMD_READ, NULL);
	cc2420_spi_get(fifo_msg); 	/*get the msg length*/
	if (fifo_msg[0] > 127) {
		CC2420_RX_FIFO_FLUSH();
		//hal_console_out('G');
		return -1;
	}

	for (i = 1; i < fifo_msg[0] + 1; i++)
		 cc2420_spi_get(fifo_msg + i);
	CC2420_CSn_1();
	return (int8_t) fifo_msg[0];
}

int8_t cc2420_rssi_get()
{

	uint8_t cca_thr, rssi_val;
	int16_t rssi;
	cc2420_radio_status radio_status;

	CC2420_CSn_0();
	cc2420_spi_get(&(radio_status.val));

	if (radio_status.bits.rssi_valid) {
		CC2420_REG_READ(CC2420_REG_RSSI, cca_thr, rssi_val);
	}
	else
		return CC2420_INVALID_RSSI;
	CC2420_CSn_1();
	rssi = (int8_t) rssi_val + CC2420_RSSI_OFFSET;
	return rssi;
}

int8_t cc2420_check()
{
	int16_t reg_manfidl;
	int16_t reg_manfidh;
	uint8_t high, low;

	CC2420_REG_READ_CSn(CC2420_REG_MANFIDL, high, low);
	reg_manfidl = (high << 8)+ low;
	CC2420_REG_READ_CSn(CC2420_REG_MANFIDH, high, low);
	reg_manfidh = (high << 8)+ low;
	if ((reg_manfidl == 0x233D) && (reg_manfidh == 0x3000))
		return CC2420_DETECT;
	else
		return CC2420_UNDETECT;
}

uint8_t cc2420_FSM_get(void)
{
	uint8_t high, low;

	CC2420_REG_READ_CSn(CC2420_REG_FSMSTATE, high, low);

	return low;
}

void cc2420_set_tx()
{	/* if the radio is in sleep, that is, the oscillator is not running,
	   turn on the radio
	*/
	if( !(cc2420_get_status() & 0x40))
		cc2420_turn_on();
	CC2420_STROBE_CMD_CSn(CC2420_STROBE_STXON);
}

uint8_t cc2420_set_tx_on_cca()
{	/* if the radio is in sleep: the oscillator is not running
	   turn on  the radio
	*/

	/* if( !(radio_get_status() & 0x40))
		radio_turn_on();
	*/
   	cc2420_radio_status status;
	CC2420_CSn_0();
	cc2420_spi_put(CC2420_STROBE_STXONCCA, &(status.val));
	CC2420_CSn_1();
	return status.val;
}

void cc2420_set_rx()
{	/* if the radio is in sleep: the oscillator is not running so
	   turn on the radio
	*/
	if( !(cc2420_get_status() & 0x40))
		cc2420_turn_on();
	CC2420_STROBE_CMD_CSn(CC2420_STROBE_SRXON);
}

void cc2420_set_sleep(int16_t sleep_level)
{
	switch (sleep_level) {
	case CC2420_RADIO_SLEEP:
		CC2420_STROBE_CMD_CSn(CC2420_STROBE_SXOSCOFF);
		break;
	case CC2420_RADIO_IDLE:
		CC2420_STROBE_CMD_CSn(CC2420_STROBE_SRFOFF);
	}
}


void cc2420_turn_on(void)
{
	cc2420_radio_status status;
	/*TODO: Limit the infinite loop, return error*/
	for (;;) {
		CC2420_CSn_0();
		cc2420_spi_put(CC2420_STROBE_SXOSCON, &(status.val));
		CC2420_CSn_1();
		if ((status.val & 0x40)) {
		/*FIXME: the LOCK don't work here, WHY   ???????!    */
		/* if ((status.val & 0x44) == 0x44) { */
			return;
		}
	}
}

void cc2420_set_channel(uint8_t ch)
{
	uint8_t channel;

	if (ch < 11 || ch > 26)
		return;
	channel = 101 + 5 * (ch - 11);
	CC2420_REG_WRITE_CSn(CC2420_REG_FSCTRL, 0x41, channel);
}

void cc2420_set_short_mac_add(uint8_t* add )
{
	CC2420_CSn_0();
	cc2420_spi_put(CC2420_RAM_SHORTADR, NULL);
	cc2420_spi_put((CC2420_RAM_SHORTADR_BANK) | CC2420_CMD_RAM_RW, NULL);
	cc2420_spi_put(add[0], NULL);
	cc2420_spi_put(add[1], NULL);
	CC2420_CSn_1();
}

void cc2420_set_ex_mac_add(uint8_t* add)
{
	int16_t i;

	CC2420_CSn_0();
	cc2420_spi_put(CC2420_RAM_IEEEADR, NULL);
	cc2420_spi_put((CC2420_RAM_IEEEADR_BANK) | CC2420_CMD_RAM_RW, NULL);
	for (i=0; i < 8; i++)
		cc2420_spi_put(add[i], NULL);
	CC2420_CSn_1();
}

void cc2420_set_mac_pan_id(uint8_t* id)
{
	CC2420_CSn_0();
	cc2420_spi_put(CC2420_RAM_PANID, NULL);
	cc2420_spi_put((CC2420_RAM_PANID_BANK) | CC2420_CMD_RAM_RW, NULL);
	cc2420_spi_put(id[0], NULL);
	cc2420_spi_put(id[1], NULL);
	CC2420_CSn_1();
}

/* TODO: TEMP solution adopted for EUROLAB 2009! */
#ifdef __USE_MOTIONBOARD__
ISR2(_CNInterrupt)
{
	if (PORTDbits.RD15 && IEC1bits.CNIE && 
	    IFS1bits.CNIF && CNEN2bits.CN21IE) 
		if (rx_callback != NULL) 
			rx_callback();
	IFS1bits.CNIF = 0;
}
#else

#if defined ( __PIC30__ ) || defined( __STM32__)
COMPILER_ISR(CC2420_INTERRUPT_NAME)
#elif defined __AVR5__
void irq_cc2420_type2(void)
#endif
{
#ifdef __STM32__
	//debug_print("ISR CC2420: ");
	CC2420_CLEAR_ISR(CC2420_INTERRUPT_LINE); //CC2420_INTERRUPT_FLAG = 0;
#else
	//debug_print("ISR CC2420: ");
	CC2420_CLEAR_PIN(CC2420_INTERRUPT_FLAG); //CC2420_INTERRUPT_FLAG = 0;
#endif
	if (rx_callback != NULL) 
		rx_callback();
}
#endif /* __USE_MOTIONBOARD__ */
