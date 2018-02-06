#include "hal/iedf_radio_cc2420.h"

/******************************************************************************/
/*                           Radio Public Functions                           */
/******************************************************************************/

int8_t iedf_radio_set_tx(void)
{
	return 0;
}

uint8_t iedf_radio_busy_tx(void)
{
	return (cc2420_get_status() & 0x08);
}

int8_t iedf_radio_set_rx_callback(void (*rx_callback)(void))
{
	cc2420_set_rx_callback(rx_callback);
	return 0;
}

uint32_t iedf_radio_get_bitrate(void)
{
	/* TODO: change this hard-coding! */
	return 250000;
}

int8_t iedf_radio_send(uint8_t *buf, uint8_t len)
{
	cc2420_store_msg(buf, len);
	cc2420_set_tx();
	/* Wait until the transmission has finished. */
	while (cc2420_get_status() & 0x08) ;

	if (cc2420_get_status() & 0x20) {
		CC2420_TX_FIFO_FLUSH();
		return -1;
	}
	/* Everything goes well. */
	return 0;
}

int8_t iedf_radio_sleep(void)
{
	cc2420_set_sleep(CC2420_RADIO_IDLE);
	return 0;
}

int8_t iedf_radio_set_cca_mode(uint8_t mode)
{
	uint8_t low, high;
	CC2420_REG_READ_CSn(CC2420_REG_MDMCTRL0, high, low)
	CC2420_REG_WRITE_CSn(CC2420_REG_MDMCTRL0, high | mode, low);
	/* chris: TODO: always success??? */
	return 0;
}

uint8_t iedf_radio_busy_rx()
{
	return cc2420_get_sfd();
}

int8_t iedf_radio_set_rx()
{
	cc2420_set_rx();
	return 0;
}

uint8_t iedf_radio_wakeup(uint8_t status)
{
	if (SLEEP2RX)
		cc2420_set_rx();
	else
		cc2420_set_tx();
	return 0;

}

int8_t iedf_radio_get_rx_power(uint8_t *energy)
{
    int8_t ret = cc2420_rssi_get();
    if (ret == CC2420_INVALID_RSSI)
        return -1;
    *energy = (uint8_t)ret; // ?????
	return 0;
}

int8_t iedf_radio_set_tx_power(uint8_t pwr)
{
	/* TODO: translate the value of pwr from PIB to radio related value! */
	pwr = CC2420_PA_0DBM;
	cc2420_set_pa(pwr);
	return 0;
}

int8_t iedf_radio_get_msg(uint8_t *msg)
{
	return cc2420_get_fifo_msg(msg);
}

int8_t iedf_radio_get_rx_data(uint8_t *msg, uint8_t *fcs_chk,
						uint8_t *lqi, uint8_t *rssi)
{
	/*FIXME: try to remove this buffer */
	uint8_t buf[130];
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
	*rssi= 255 - buf[len - 2];
	/* remove the FCS/LQI, RSSI, and lenght from the length */
	len -= 3;
	//memcpy(msg, buf+1, len);
	int i = 0;
	for (i = 0; i < len; i++) {
		msg[i] = buf[i+1];
	} 
	return len;
}

int8_t iedf_radio_init(void)
{
	#ifdef __USE_MOTIONBOARD_TWO__
	return cc2420_radio_init(CC2420_SPI_PORT_2);
	#endif
	#ifdef __USE_MOTIONBOARD__
	return cc2420_radio_init(CC2420_SPI_PORT_1);
	#else
	return cc2420_radio_init(CC2420_SPI_PORT_2);
	#endif
}

int8_t iedf_radio_set_channel(uint8_t ch)
{
	if (ch > IEDF_RADIO_CHANNEL_LAST || ch < IEDF_RADIO_CHANNEL_FIRST)
		return -1;
	cc2420_set_channel(ch);/* chris: TODO:  return nothing?? */
	return 0;
}

uint8_t iedf_radio_get_cca(void) {
    return cc2420_get_cca();
}
