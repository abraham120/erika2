/**
 * @file iedf_phy.c
 * @brief Implicit-EDF physical layer
 * @author Simone Madeo
 * @author Gianluca Franchino 2012
 * @version 0.1
 * @date 2011-10-10
 */
#include "phy/iedf_phy.h"

/**********************************************************************
 *                       PHY Layer TASK and ISR                       *
 **********************************************************************/
IEDF_KAL_TASK_ASYNC(PHY_READ_DISPATCHER, 30);

static struct {
	uint8_t initialized;
	enum iedf_phy_code_t radio;
} phy_status = {0, IEDF_PHY_TRX_OFF};

IEDF_KAL_MUTEX(PHY_RECEIVE_MUTEX, PHY_READ_DISPATCHER);

static void phy_read_dispatcher(void)
{
	uint8_t rssi = 0, lqi = 0, fcs_chk = 0;
	uint8_t buf[IEDF_RADIO_RX_BUFFER_SIZE];
	int8_t len = 0;

	iedf_kal_mutex_wait(PHY_RECEIVE_MUTEX);
	len = iedf_radio_get_rx_data(buf, &fcs_chk, &lqi, &rssi);
	iedf_kal_mutex_signal(PHY_RECEIVE_MUTEX);
   
	if (len > 0 && fcs_chk != 0)
		iedf_phy2mac_cb((uint8_t) len, buf, lqi);
    // *** DEBUG ***
    else {
        if (len == 0) {
            //EE_led_1_on();
            iedf_phy2mac_cb(0, NULL, 1);
        }
        else if (len < 0) {
            //EE_led_2_on();
            iedf_phy2mac_cb(0, NULL, 2);
        }
        else {
            //EE_led_3_on();
            iedf_phy2mac_cb(0, NULL, 3);
        }      
    }
}

static void phy_read_isr(void)
{
	iedf_kal_activate(PHY_READ_DISPATCHER);
}

/**********************************************************************
 *                   PHY Layer Public Functions                       * 
 **********************************************************************/

int8_t iedf_phy_init(uint8_t ch)
{
	if (iedf_kal_set_body(PHY_READ_DISPATCHER, phy_read_dispatcher) < 0)
		return -IEDF_PHY_ERROR_INIT;
	if (iedf_radio_set_rx_callback(phy_read_isr) < 0)
		return -IEDF_PHY_ERROR_INIT;
	if (iedf_radio_init() < 0)
		return -IEDF_PHY_ERROR_INIT;
    if (iedf_radio_set_channel(ch) < 0)
		return -IEDF_PHY_ERROR_INIT;
    /* FIXME: Clear channel when received energy is below threshold */
    if (iedf_radio_set_cca_mode(0xC0) < 0)
		return -IEDF_PHY_ERROR_INIT;
	if (iedf_radio_set_rx() < 0)
		return -IEDF_PHY_ERROR_INIT;
	phy_status.radio = IEDF_PHY_RX_ON;
	phy_status.initialized = 1;
	return IEDF_PHY_ERROR_NONE;
}

int8_t iedf_phy_send(uint8_t *psdu, uint8_t psduLength)
{
	//enum iedf_phy_code_t status = IEDF_PHY_SUCCESS;
	if (!phy_status.initialized)
		return -IEDF_PHY_ERROR_INIT;
    if (phy_status.radio != IEDF_PHY_TX_ON)
		return -IEDF_PHY_ERROR_SEND;
	// TODO: lunghezza ???
	//if (psduLength > IEDF_aMaxPHYPacketSize)
	//	return -IEDF_PHY_ERR_INVALID_PARAM;
	phy_status.radio = IEDF_PHY_BUSY_TX;	//chris: do i need this?
    if (iedf_radio_send(psdu, psduLength) < 0)
        return -IEDF_PHY_ERROR_SEND;
	phy_status.radio = IEDF_PHY_TX_ON;
	//iedf_PD_DATA_confirm(status);
	// abbiamo vinto?
	return IEDF_PHY_ERROR_NONE;
}

enum iedf_phy_code_t iedf_phy_get_status(void)
{
    return phy_status.radio;
}

int8_t iedf_phy_set_status(enum iedf_phy_code_t state)
{
	enum iedf_phy_code_t status;
	if (!phy_status.initialized)
		return -IEDF_PHY_ERROR_INIT;
	if (phy_status.radio == state) {
		status = phy_status.radio;
	} else {
		switch (state) {
		case IEDF_PHY_TX_ON :
			if (iedf_radio_set_tx() < 0)
                return -IEDF_PHY_ERROR_INIT;
			phy_status.radio = IEDF_PHY_TX_ON;
            //EE_led_off();
			break;
		case IEDF_PHY_FORCE_TRX_OFF :
			if (iedf_radio_sleep() < 0)
                return -IEDF_PHY_ERROR_INIT;
            //EE_led_off();
			phy_status.radio = IEDF_PHY_TRX_OFF;
			break;
		case IEDF_PHY_TRX_OFF :
			if (phy_status.radio == IEDF_PHY_RX_ON)
				while (iedf_radio_busy_rx()) ;
			else if (phy_status.radio == IEDF_PHY_TX_ON)
				while (iedf_radio_busy_tx()) ;
			else
                return -IEDF_PHY_ERROR_INIT;
			if (iedf_radio_sleep() < 0)
                return -IEDF_PHY_ERROR_INIT;
            //EE_led_off();
			phy_status.radio = IEDF_PHY_TRX_OFF;
			break;
		case IEDF_PHY_RX_ON :
			while (iedf_radio_busy_tx()) ;
			if (iedf_radio_set_rx() < 0)
                return -IEDF_PHY_ERROR_INIT;
            //EE_led_on();
			phy_status.radio = IEDF_PHY_RX_ON;
			break;
		default :
            return -IEDF_PHY_ERROR_NONE;
		}
		status = IEDF_PHY_SUCCESS;
	}
	//iedf_PLME_SET_TRX_STATE_confirm(status);
	return IEDF_PHY_ERROR_NONE;
}

uint8_t iedf_phy_get_cca(void) {
    return iedf_radio_get_cca();
}
