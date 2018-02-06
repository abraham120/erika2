

#include "common/cc2420.h"
#include "hal/hal_defines.h"
#include "common/hal.h"


/*******************************************************************************
 * Function:        int cc2420_init(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          0 if the initialization goes well, -1 otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This routine initializes the radio transceiver
 *
 * Note:            None
 ******************************************************************************/
 
int cc2420_init()
{
	EE_UINT8 i=0;
	
	RESETn = 0;
	VREG_EN = 1;
   	while (++i);
	RESETn = 1;
   	while (++i);
   	while (++i);
	
	/* turn on the crystal oscillator */
  	cc2420_turn_on();
	if (cc2420_check() == CC2420_UNDETECT)
		return -1;
	
	/*active CC2420 spi to set up the registers */
	CSn_0(); 

	/* set up REG_MDMCTRL0 
	 * 15:14 = '00'  = Reserved
	 * 13    = '0'   = Reserved frames are rejected
	 * 12    = '?'   = '1' if this is coordinator, '0' if otherwise
	 * 11    = '0'   = Address decoding is disabled
	 * 10:8  = '010' = CCA Hysteresis in DB - default value
	 * 7:6   = '11'  = CCA = 1, when RSSI_VAL < CCA_THR - CCA_HYST and not 
	 *		   receiving valid IEEE 802.15.4 data
	 * 5     = '1'   = Auto CRC
	 * 4     = '0'   = Auto ACK
	 * 3:0   = '0010' = 3 leading zero EE_UINT8s - IEEE compliant.
	 */
	 
#if defined(COORDINATOR) 
	/* MSB = 0b0001 0010 */
	/* LSB = 0b1110 0010 */
	
	CC2420_REG_WRITE(REG_MDMCTRL0, 0x12, 0xE2); 
	//CC2420_REG_WRITE(REG_MDMCTRL0, 0x1A, 0xE2); 
#else
	/* MSB = 0b0000 0010 */
	/* LSB = 0b1110 0010 */
	CC2420_REG_WRITE(REG_MDMCTRL0, 0x02, 0xE2);
	//CC2420_REG_WRITE(REG_MDMCTRL0, 0x1A, 0xE2);  
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
	CC2420_REG_WRITE(REG_MDMCTRL1, 0x05, 0x00);

	/* disable the MAC level security */
	
	/* set up REG_SECCTRL0
	 * 15:10  = '000000' = Reserved
	 * 9     = '0'   = Protection enable of the RXFIFO -> disabled
	 * 8     = '1'   = see data sheet
	 * 7     = '1'   = Stand alone key select -> key 1 is used 
	 * 6     = '1'   = TX key select -> key 1 is selected
	 * 5     = '0'   = RX key select -> key 0 is used
	 * 4:2   = '001' = Number of EE_UINT8s in authentication field for CBC_MAC,
	 *		   encoded as (M-2)/2 -> 4
	 * 1:0   = '0'   = In-line security is disabled
	 */
	CC2420_REG_WRITE(REG_SECCTRL0, 0x01, 0xC4);
	
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
	CC2420_REG_WRITE(REG_IOCFG0, 0x00, 0x7F);

	/*disable CC2420 spi to set up the registers */
	CSn_1();
	
	/* set tx power equal to the maximum value */	
	cc2420_set_pa(PA_MAXIMUM);
	
	/* Flush the TX FIFO */
	CC2420_STROBE_CMD_CSn(STROBE_SFLUSHTX);
	
	/* Flush the RX FIFO */
	RX_FIFO_FLUSH();
	
	return 0;


}

/*******************************************************************************
 * Function:        void cc2420_set_pa(EE_UINT8 power)
 *
 * PreCondition:    None
 *
 * Input:           EE_UINT8 power. TX power
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine set the transmission power of the CC2420.
 *
 * Note:            None
 ******************************************************************************/
 
void cc2420_set_pa(EE_UINT8 power)
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
	CC2420_REG_WRITE_CSn(REG_TXCTRL, 0xA0, power);
}

/*******************************************************************************
 * Function:        cc2420_status cc2420_get_status()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          cc2420_status. The CC2420 status
 *
 * Side Effects:    None
 *
 * Overview:        This routine returns the CC2420 status.
 *
 * Note:            None
 ******************************************************************************/
 
EE_UINT8 cc2420_get_status()
{
	cc2420_status status;	

	CSn_0();
	status.val = hal_radio_spi_get();
	CSn_1();
	
	return status.val;
}   

/*******************************************************************************
 * Function:        void cc2420_store_msg(EE_UINT8 *msg, EE_UINT8 msg_lenght)
 *
 * PreCondition:    None
 *
 * Input:           EE_UINT8 *msg, EE_UINT8 msg_length
 *
 * Output:          None 
 *
 * Side Effects:    None
 *
 * Overview:        This routine stores a message in the TX_FIFO buffer 
 *					of the CC2420.
 *
 * Note:            None
 ******************************************************************************/
void cc2420_store_msg(EE_UINT8 *msg, EE_UINT8 msg_length)
{
	EE_UINT8 i, high_EE_UINT8, low_EE_UINT8 ;

	if (msg_length > 127)
		return;

	CC2420_REG_READ_CSn(REG_MDMCTRL0, high_EE_UINT8, low_EE_UINT8);

	CSn_0();
	hal_radio_spi_put(REG_TXFIFO);
	/*if (low_EE_UINT8 & 0x20)
		hal_radio_spi_put(msg_length + FCS_LENGTH );
	else
		hal_radio_spi_put(msg_length);*/

	for (i = 0; i < msg_length; i++) {
		hal_radio_spi_put(msg[i]);
	}
	CSn_1(); 
		
}

/*******************************************************************************
 * Function:        void cc2420_store_txfifo(EE_UINT8 *buf, EE_UINT8 buf_length)
 *
 * PreCondition:    None
 *
 * Input:           EE_UINT8 *buf, EE_UINT8 buf_lenght
 *
 * Output:          None 
 *
 * Side Effects:    None
 *
 * Overview:        This routine stores a buffer of buf_length EE_UINT8s in the 
 *					TX_FIFO buffer of the CC2420.
 *
 * Note:            None
 ******************************************************************************/
void cc2420_store_txfifo(EE_UINT8 *buf, EE_UINT8 buf_length)
{
	EE_UINT8 i;

	if (buf_length > 127)
		return;

	CSn_0();
	hal_radio_spi_put(REG_TXFIFO);
	for (i = 0; i < buf_length; i++)
		hal_radio_spi_put(buf[i]);
	CSn_1(); 
		
}

/*******************************************************************************
 * Function:        int cc2420_get_fifo_msg(EE_UINT8 *fifo_msg)
 *
 * PreCondition:    The pin FIFOP from the CC2420 is connected to an interrupt 
 *		    pin of the used microcontroller.
 *
 * Input:           EE_UINT8 *fifo_msg. The buffer where to store the message from 
 *		    the FIFO
 *
 * Output:          msg_leght. the lenght of the received message
 *
 * Side Effects:    None
 *
 * Overview:        This routine is used by the routine that manages the
 *			interrupt raised by the fifop pin.
 *
 * Note:            None
 ******************************************************************************/
 
int cc2420_get_fifo_msg(EE_UINT8 *fifo_msg)
{
	EE_UINT8 i;

	if (FIFO == 0) {
		if (FIFOP == 1) {
			RX_FIFO_FLUSH();
		}
		return -1;	
	}
	CSn_0();
	hal_radio_spi_put(REG_RXFIFO | CMD_READ);
	fifo_msg[0] = hal_radio_spi_get(); /*get the msg length*/

	if (fifo_msg[0] > 127) {
		RX_FIFO_FLUSH();
		return -1;	
	}

	for (i = 1; i < fifo_msg[0] + 1; i++){
		fifo_msg[i] = hal_radio_spi_get();
	}
		
	CSn_1();

	return (int)fifo_msg[0];
		     
}

/*******************************************************************************
 * Function:        int cc2420_rssi_get()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the rssi value in dbm, INVALID_RSSI otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This routine returns the rssi value mesured in dbm
 *                  
 *
 * Note:            None
 ******************************************************************************/
 
int cc2420_rssi_get()
{
	
	EE_UINT8 cca_thr, rssi_val;
	int rssi;
	cc2420_status radio_status;
	
	CSn_0();
	radio_status.val = hal_radio_spi_get();
	
	if(radio_status.bits.rssi_valid){
		CC2420_REG_READ(REG_RSSI, cca_thr, rssi_val);
	}
	else
		return INVALID_RSSI;	
		
	CSn_1();
	rssi = (int)rssi_val + RSSI_OFFSET;
	return (rssi);
	
}

/*******************************************************************************
 * Function:        int cc2420_check(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          CC2420_DETECT if CC2420 is present, CC2420_UNDETECT otherwise 
 *
 * Side Effects:    None
 *
 * Overview:        This routine check the presence of the transceiver.
 *
 * Note:            Pay attention: check in the datasheet the CC2420 codes in
 *					REG_MANFIDL.	
 ******************************************************************************/
 
int cc2420_check(){
	
	int reg_manfidl;
	int reg_manfidh;
	EE_UINT8 high, low;
	
	CC2420_REG_READ_CSn(REG_MANFIDL, high, low);
	
	reg_manfidl = (high << 8)+ low;
	
	CC2420_REG_READ_CSn(REG_MANFIDH, high, low);
	
	reg_manfidh = (high << 8)+ low;
	
	if((reg_manfidl == 0x233D) && (reg_manfidh == 0x3000))
		return CC2420_DETECT;
	else
		return CC2420_UNDETECT;  
}

/*******************************************************************************
 * Function:        EE_UINT8 cc2420_FSM_get(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          the status of the FSM inside the CC2420 
 *
 * Side Effects:    None
 *
 * Overview:        This routine returns the status of the FSM inside the CC2420.
 *
 * Note:            None
 ******************************************************************************/
 
EE_UINT8 cc2420_FSM_get(void)
{
	EE_UINT8 high, low;
	
	CC2420_REG_READ_CSn(REG_FSMSTATE, high, low);
	
	return low;
}	
 

/*******************************************************************************
 * Function:        void cc2420_set_tx()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None 
 *
 * Side Effects:    None
 *
 * Overview:        This routine starts the transmission of a msg by the CC2420.
 *
 * Note:            None
 ******************************************************************************/
 		
void cc2420_set_tx()
{	/* if the radio is in sleep, that is, the oscillator is not running,
	   turn on the radio 
	*/ 
	if( !(cc2420_get_status() & 0x40))
		cc2420_turn_on();

	CC2420_STROBE_CMD_CSn(STROBE_STXON);
}

/*******************************************************************************
 * Function:        void cc2420_set_tx_on_cca()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None 
 *
 * Side Effects:    None
 *
 * Overview:        This routine starts the transmission of a msg by the CC2420
 * 			if the channel is clear (CSMA mode).
 *
 * Note:            None
 ******************************************************************************/
 
EE_UINT8 cc2420_set_tx_on_cca()
{	/* if the radio is in sleep: the oscillator is not running
	   turn on  the radio 
	*/ 
	/*if( !(cc2420_get_status() & 0x40))
		cc2420_turn_on();
   */
   	cc2420_status status;
   		
	CSn_0();
	status.val = hal_radio_spi_put(STROBE_STXONCCA);
	CSn_1();
	
	return status.val;

}

/*******************************************************************************
 * Function:        void cc2420_set_rx()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None 
 *
 * Side Effects:    None
 *
 * Overview:        This routine puts the radio in RX mode.
 *
 * Note:            None
 ******************************************************************************/
 
void cc2420_set_rx()
{	/* if the radio is in sleep: the oscillator is not running so
	   turn on the radio 
	*/ 
	if( !(cc2420_get_status() & 0x40))
		cc2420_turn_on();

	CC2420_STROBE_CMD_CSn(STROBE_SRXON);
}

/*******************************************************************************
 * Function:        void cc2420_set_sleep(int sleep_level)
 *
 * PreCondition:    None
 *
 * Input:           sleep_level: POWER_DOWN or IDLE
 *
 * Output:          None 
 *
 * Side Effects:    None
 *
 * Overview:        This routine puts the radio in sleep mode.
 *
 * Note:            None
 ******************************************************************************/
 
void cc2420_set_sleep(int sleep_level)
{
	
	switch (sleep_level) {
	case RADIO_SLEEP: 
		CC2420_STROBE_CMD_CSn(STROBE_SXOSCOFF);
		break;
	case RADIO_IDLE:
		CC2420_STROBE_CMD_CSn(STROBE_SRFOFF);
	}
}

/*******************************************************************************
 * Function:        void cc2420_turn_on()
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None 
 *
 * Side Effects:    None
 *
 * Overview:        This routine turns on the radio starting the oscillator.
 *
 * Note:            After performing this routine the radio is in the idle state.
 ******************************************************************************/
 
void cc2420_turn_on()
{
	cc2420_status status;

    	for(;;) {
			CSn_0();
			status.val = hal_radio_spi_put(STROBE_SXOSCON);
			CSn_1();
			
			if(status.bits.xosc16m_stable == 1){
            		return;
			}
		}	
	
}



/*******************************************************************************
 * Function:        void cc2420_set_channel(EE_UINT8 ch)
 *
 * PreCondition:    None
 *
 * Input:           EE_UINT8 ch. The channel to tune in 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine set the channel to tune in the CC2420.
 *
 * Note:            ch must be in the interval [11, 26] 
 ******************************************************************************/

void cc2420_set_channel(EE_UINT8 ch)
{
	EE_UINT8 channel;

	if (ch < 11 || ch > 26) 
		return;

	channel = 101 + 5 * (ch - 11);
 	
	
	CC2420_REG_WRITE_CSn(REG_FSCTRL, 0x41, channel);
}

/*******************************************************************************
 * Function:        void cc2420_set_short_mac_add(EE_UINT16 add)
 *
 * PreCondition:    None
 *
 * Input:           EE_UINT16 add. The short MAC address to store in the transceiver. 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine set the short MAC address in the CC2420.
 *
 * Note:            None 
 ******************************************************************************/
void cc2420_set_short_mac_add(EE_UINT8* add)
{
	CSn_0();
	hal_radio_spi_put(RAM_SHORTADR);
	hal_radio_spi_put((RAM_SHORTADR_BANK) | CMD_RAM_RW);
	hal_radio_spi_put(add[0]);
	hal_radio_spi_put(add[1]);
	CSn_1();
}
/*void cc2420_set_short_mac_add(EE_UINT16 add)
{
	CSn_0();
	hal_radio_spi_put(RAM_SHORTADR);
	hal_radio_spi_put((RAM_SHORTADR_BANK) | CMD_RAM_RW);
	hal_radio_spi_put(add);
	hal_radio_spi_put(add);
	CSn_1();
}
*/
/*******************************************************************************
 * Function:        void cc2420_set_ex_mac_add(EE_UINT8* add)
 *
 * PreCondition:    None
 *
 * Input:           EE_UINT8* add. The extended MAC address to be stored in the 
 *					transceiver. 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine set the extended MAC address in the CC2420.
 *
 * Note:            None
 ******************************************************************************/
void cc2420_set_ex_mac_add(EE_UINT8* add)
{
	int i;

	CSn_0();
	hal_radio_spi_put(RAM_IEEEADR);
	hal_radio_spi_put((RAM_IEEEADR_BANK) | CMD_RAM_RW);
	for (i=0; i < 8; i++)
		hal_radio_spi_put(add[i]);
	CSn_1();
}

/*
void cc2420_set_ex_mac_add(QEE_UINT16 add)
{
	CSn_0();
	hal_radio_spi_put(RAM_IEEEADR);
	hal_radio_spi_put((RAM_IEEEADR_BANK) | CMD_RAM_RW);
	hal_radio_spi_put(add);
	hal_radio_spi_put(add >> 8);
	hal_radio_spi_put(add >> 16);
	hal_radio_spi_put(add >> 24);
	hal_radio_spi_put(add >> 32);
	hal_radio_spi_put(add >> 48);
	hal_radio_spi_put(add >> 56);
	CSn_1();
}
*/
/*******************************************************************************
 * Function:        void cc2420_set_mac_pan_id(EE_UINT8* id)
 *
 * PreCondition:    None
 *
 * Input:           EE_UINT8* add. The MAC PAN ID to be stored in the transceiver. 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine set the MAC PAN ID in the CC2420.
 *
 * Note:            None 
 ******************************************************************************/
void cc2420_set_mac_pan_id(EE_UINT8* id)
{
	CSn_0();
	hal_radio_spi_put(RAM_PANID);
	hal_radio_spi_put((RAM_PANID_BANK) | CMD_RAM_RW);
	hal_radio_spi_put(id[0]);
	hal_radio_spi_put(id[1]);
	CSn_1();
}

/*void cc2420_set_mac_pan_id(EE_UINT16 id)
{
	CSn_0();
	hal_radio_spi_put(RAM_PANID);
	hal_radio_spi_put((RAM_PANID_BANK) | CMD_RAM_RW);
	hal_radio_spi_put(id);
	hal_radio_spi_put(id >> 8);
	CSn_1();
}
*/
