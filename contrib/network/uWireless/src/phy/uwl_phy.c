/** 
* @file uwl_phy.c
* @brief IEEE 802.15.4 PHY Layer Implementation
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#include <phy/uwl_phy_internal.h>
#include <mac/uwl_mac_mutexes.h>
#include <util/uwl_debug.h>
#include <kal/uwl_kal.h>
#include <hal/uwl_radio.h>
#ifdef UWL_DEBUG_LOG
#ifdef __STDIO_COMPILER_BUG__
unsigned int strlen(const char *str);
int sprintf(char *, const char *, ...);
#else
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif
#endif

/* chris: if the PLME and PD code is not so much their implementation
	can be done just in this file. This helps to hide some global
	variable with the static keyword, otherwise we can try to limit the
	scope using the phy_internal header.
*/

/******************************************************************************/
/*                          PHY Layer Private Data                            */
/******************************************************************************/
static struct uwl_phy_pib_t uwl_phy_pib = {
	UWL_RADIO_CURRENT_CHANNEL_INIT,
	UWL_RADIO_CHANNEL_SUPPORTED_INIT,
	UWL_RADIO_TRANSMIT_POWER_INIT,
	UWL_RADIO_CCA_MODE_INIT,
	UWL_RADIO_CURRENT_PAGE_INIT,
	UWL_RADIO_MAX_FRAME_DURATION_INIT,
	UWL_RADIO_SHR_DURATION_INIT,
	UWL_RADIO_SYMBOLS_PER_OCTET_INIT
};

static struct {
	unsigned radio : 4;
	unsigned initialized : 1;
	unsigned reserved : 3;
} phy_status = {UWL_PHY_TRX_OFF, 0, 0};

/******************************************************************************/
/*                          PHY Layer TASK and ISR                            */
/******************************************************************************/
UWL_KAL_TASK_ASYNC(PHY_READ_DISPATCHER, 30);

UWL_PHY_IMPORT_MAC_MUTEXES(PHY_READ_DISPATCHER); /* TODO: write notes!! */

static void phy_read_dispatcher(void)
{
	uint8_t rssi = 0, lqi = 0, fcs_chk = 0;
	uint8_t buf[UWL_RADIO_RX_BUFFER_SIZE];
	int8_t len = 0;

//	#ifdef UWL_DEBUG_LOG
//	uwl_debug_print("UWL_TASK: PHY_READ_DISPATCHER Activated!");
//	#endif
//	/* chris: FIXME: maybe the error was in that part! */
//	/* chris: TODO: this part has been copied by the old ieee802154 stack.
//			maybe this is too dependent on the cc2420? can we
//			abstract something?
//	*/
//	len = uwl_radio_get_msg(buf);
//	if(len < 2)
//		return; /* chris: TODO: - Make something: notify to upper layer
//					(raise an error) or ignore
//					(return immediately)
//					- Check if the condition < 13 is ok (now
//					it is because of the minimal packet
//					size);
//			*/
//	len += 1; 	/* chris: TODO: Lenght does not consider the first
//					byte (which is length itself)
//					so add it! Is this correct????
//			*/
//	if (!(buf[len - 1] & 0x80))
//		return;	/* chris: TODO: - Make something: notify to upper layer
//					(raise an error) or ignore
//					(return immediately)
//			*/
//	/* The last two bytes in the buffer are the RSSI value
//	* and the CRC value respectively. They are not part
//	* of the message (payload), then we can discard them.
//	* For further information see the CC2420 datasheet
//	*/
//	lqi = buf[len - 1] & 0x7F;
//	rssi= 255 - buf[len - 2];
//	len -= 2;

	len = uwl_radio_get_rx_data(buf, &fcs_chk, &lqi, &rssi);
	if (len < 0)
		return; /* chris: TODO: - Make something: notify to upper layer
					(raise an error) or ignore
					(return immediately)
					- Check if the condition < 13 is ok (now
					it is because of the minimal packet
					size);
			*/
	if (fcs_chk == 0)
		return; /* chris: TODO: - Make something: notify to upper layer
					(raise an error) or ignore
					(return immediately)
			*/

	#ifdef UWL_DEBUG_LOG
//	int i = 0;
//	char s[130];
//	uwl_debug_print("\r\n");
//	for (i = 0; i < len; i++) {
//		sprintf(s, "%X", buf[i]);
//		uwl_debug_print(s);
//	}
	#endif

    #ifdef UWL_ADD_RSSI_LQI
    #warning RSSI VALUE added at the end of packet
    /* Make sure that the packet size does not exceed the maximum size */
    buf[len] = rssi;
    buf[len + 1] = lqi;
    len = (uint8_t)len + 2;
    #endif

	uwl_PD_DATA_indication((uint8_t) len,  buf, lqi);
}

static void phy_read_isr(void)
{
	#ifdef UWL_DEBUG_LOG
	//uwl_debug_print("!-> BCN <-!");
	#endif
	uwl_kal_activate(PHY_READ_DISPATCHER);
}

/******************************************************************************/
/*                      PHY Layer General Functions                           */
/******************************************************************************/
int8_t uwl_phy_init(void)
{
	/* TODO: Check if already initialized do something special?? */

	#ifdef UWL_DEBUG_LOG
	uwl_debug_print("Initializing PHY...");
	#endif
	if (uwl_kal_init(0) < 0)
		return -UWL_PHY_ERR_KAL_ERROR;
	if (uwl_kal_set_body(PHY_READ_DISPATCHER, phy_read_dispatcher) < 0)
		return -UWL_PHY_ERR_KAL_ERROR;
	#ifdef UWL_DEBUG_LOG
	uwl_debug_print("KAL init OK!");
	#endif
	if (uwl_radio_set_rx_callback(phy_read_isr) < 0)
		return -UWL_PHY_ERR_HW_FAILURE;
	if (uwl_radio_init() < 0)
		return -UWL_PHY_ERR_HW_FAILURE;
	#ifdef UWL_DEBUG_LOG
	uwl_debug_print("Radio init OK!");
	#endif
	/*if (uwl_radio_set_rx() < 0)
		return -UWL_PHY_ERR_HW_FAILURE;
	phy_status.radio = UWL_PHY_RX_ON;
	*/
	phy_status.radio = UWL_PHY_TRX_OFF;
	/* TODO: initialize the PLME and PD */
	phy_status.initialized = 1;
	return UWL_PHY_ERR_NONE;
}

/* chris: TODO: do we handle other error condition? :
		- the psduLength > 127
		- uwl_radio failure
*/



/******************************************************************************/
/*                      PD-SAP Definition (PHY SIDE)                          */
/******************************************************************************/
int8_t uwl_PD_DATA_request(uint8_t psduLength, uint8_t *psdu)
{
	enum uwl_phy_code_t status = UWL_PHY_SUCCESS;
	#ifdef UWL_DEBUG_LOG
	char s[100];
	sprintf(s, "PD_DATA_request(len=%u, *p=%u)", psduLength,(unsigned int)psdu);
	uwl_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -UWL_PHY_ERR_NOT_INITIALIZED;
	switch (phy_status.radio) {
	case UWL_PHY_TRX_OFF:
		status = UWL_PHY_TRX_OFF;
		break;
	case UWL_PHY_RX_ON:
		status = UWL_PHY_RX_ON;
		break;
	case UWL_PHY_BUSY_TX:
		status = UWL_PHY_BUSY_TX;
		break;
	case UWL_PHY_TX_ON:
		uwl_debug_print("   case TX_ON:");// TODO: REMOVE
		if (psduLength > UWL_aMaxPHYPacketSize)
			return -UWL_PHY_ERR_INVALID_PARAM;
		phy_status.radio = UWL_PHY_BUSY_TX;	//chris: do i need this?
		if (uwl_radio_send(psdu, psduLength) < 0)
			return -UWL_PHY_ERR_HW_FAILURE;
		phy_status.radio = UWL_PHY_TX_ON;
		break;
	}
	uwl_PD_DATA_confirm(status);
	return UWL_PHY_ERR_NONE;
}

/******************************************************************************/
/*                      PLME-SAP Definition (PHY SIDE)                        */
/******************************************************************************/
int8_t uwl_PLME_CCA_request(void)
{
	enum uwl_phy_code_t status;
	#ifdef UWL_DEBUG_LOG
	uwl_debug_print("PLME_CCA_request()");
	#endif

	if (!phy_status.initialized)
		return -UWL_PHY_ERR_NOT_INITIALIZED;
	switch (phy_status.radio) {
	case UWL_PHY_TRX_OFF:
		status = UWL_PHY_TRX_OFF;
		break;
	case UWL_PHY_TX_ON:
		status = UWL_PHY_BUSY;
		break;
	case UWL_PHY_RX_ON:
		if (uwl_radio_get_cca())
			status = UWL_PHY_IDLE;
		else
			status = UWL_PHY_BUSY;
		break;
	default:
		return -UWL_PHY_ERR_INVALID_PARAM;
	}
	uwl_PLME_CCA_confirm(status);
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_ED_request(void)
{
	enum uwl_phy_code_t status;
	uint8_t energy = 0;
	#ifdef UWL_DEBUG_LOG
	uwl_debug_print("PLME_ED_request");
	#endif

	if (!phy_status.initialized)
		return -UWL_PHY_ERR_NOT_INITIALIZED;
	switch (phy_status.radio) {
	case UWL_PHY_TRX_OFF:
		status = UWL_PHY_TRX_OFF;
		break;
	case UWL_PHY_TX_ON:
		status = UWL_PHY_TX_ON;
		break;
	case UWL_PHY_RX_ON:
		if (uwl_radio_get_rx_power(&energy) < 0)
			return -UWL_PHY_ERR_HW_FAILURE;
		status = UWL_PHY_SUCCESS;
		break;
	default:
		return -UWL_PHY_ERR_INVALID_PARAM;
	}
	uwl_PLME_ED_confirm(status, energy);
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_GET_request(enum uwl_phy_pib_id_t PIBAttribute)
{
	enum uwl_phy_code_t status = UWL_PHY_SUCCESS;
	void *value = NULL;
	#ifdef UWL_DEBUG_LOG
	char s[100];
	sprintf(s, "PLME_GET_request(%u)", PIBAttribute);
	uwl_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -UWL_PHY_ERR_NOT_INITIALIZED;
	switch (PIBAttribute) {
	case UWL_PHY_CURRENT_CHANNEL :
		value = (void *) &(uwl_phy_pib.phyCurrentChannel);
		break;
	case UWL_PHY_CHANNEL_SUPPORTED :
		value =  (void *) &(uwl_phy_pib.phyChannelsSupported);
		break;
	case UWL_PHY_TRANSMIT_POWER :
		value = (void *) &(uwl_phy_pib.phyTransmitPower);
		break;
	case UWL_PHY_CCA_MODE :
		value = (void *) &(uwl_phy_pib.phyCCAMode);
		break;
	case UWL_PHY_CURRENT_PAGE :
		value = (void *) &(uwl_phy_pib.phyCurrentPage);
		break;
	case UWL_PHY_MAX_FRAME_DURATION :
		value = (void *) &(uwl_phy_pib.phyMaxFrameDuration);
		break;
	case UWL_PHY_SHR_DURATION :
		value = (void *) &(uwl_phy_pib.phySHRDuration);
		break;
	case UWL_PHY_SYMBOLS_PER_OCTET :
		value = (void *) &(uwl_phy_pib.phySymbolsPerOctet);
		break;
	default:
		status = UWL_PHY_UNSUPPORTED_ATTRIBUTE;
		break;
	}
	uwl_PLME_GET_confirm(status, PIBAttribute, value);
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_SET_TRX_STATE_request(enum uwl_phy_code_t state)
{
	enum uwl_phy_code_t status;
	#ifdef UWL_DEBUG_LOG
//	char s[100];
//	char s1[30];
//	uwl_debug_sprint_phycode(state, s1);
//	sprintf(s, "PLME_SET_TRX_STATE_request(%s)", s1);
//	uwl_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -UWL_PHY_ERR_NOT_INITIALIZED;
	if (phy_status.radio == state) {
		status = phy_status.radio;
	} else {
		switch (state) {
		case UWL_PHY_TX_ON :
			if (uwl_radio_set_tx() < 0)
				return -UWL_PHY_ERR_HW_FAILURE;
			phy_status.radio = UWL_PHY_TX_ON;
			break;
		case UWL_PHY_FORCE_TRX_OFF :
			if (uwl_radio_sleep() < 0)
				return -UWL_PHY_ERR_HW_FAILURE;
			phy_status.radio = UWL_PHY_TRX_OFF;
			break;
		case UWL_PHY_TRX_OFF :
			if (phy_status.radio == UWL_PHY_RX_ON)
				while (uwl_radio_busy_rx()) ;
			else if (phy_status.radio == UWL_PHY_TX_ON)
				while (uwl_radio_busy_tx()) ;
			else
				return -UWL_PHY_ERR_INVALID_PARAM;
			if (uwl_radio_sleep() < 0)
					return -UWL_PHY_ERR_HW_FAILURE;
			phy_status.radio = UWL_PHY_TRX_OFF;
			break;
		case UWL_PHY_RX_ON :
			while (uwl_radio_busy_tx()) ;
			if (uwl_radio_set_rx() < 0)
				return -UWL_PHY_ERR_HW_FAILURE;
			phy_status.radio = UWL_PHY_RX_ON;
			break;
		default :
			return -UWL_PHY_ERR_INVALID_PARAM;
		}
		status = UWL_PHY_SUCCESS;
	}
	uwl_PLME_SET_TRX_STATE_confirm(status);
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_SET_request(enum uwl_phy_pib_id_t PIBAttribute,
			    void *PIBAttributeValue)
{
	enum uwl_phy_code_t status = UWL_PHY_SUCCESS;
	uint8_t param = *((uint8_t*) PIBAttributeValue);
	#ifdef UWL_DEBUG_LOG
	char s[100];
	sprintf(s, "PLME_SET_request(a=%u, val=%u)", PIBAttribute, param);
	uwl_debug_print(s);
	#endif

	if (!phy_status.initialized)
		return -UWL_PHY_ERR_NOT_INITIALIZED;
	switch (PIBAttribute) {
	case UWL_PHY_CURRENT_CHANNEL :
		if (param > UWL_RADIO_CHANNEL_LAST || 
		    param < UWL_RADIO_CHANNEL_FIRST) {
			status = UWL_PHY_INVALID_PARAMETER;
			break;
		}
		if (uwl_radio_set_channel(param) < 0)
			return -UWL_PHY_ERR_HW_FAILURE;
		uwl_phy_pib.phyCurrentChannel = param;
		break;
	case UWL_PHY_TRANSMIT_POWER :
		param = uwl_phy_pib.phyTransmitPower | (param & 0x3F);
		/* TODO: chris: call the radio primitive for this ...
				check on param is useless, right????  */
		if (uwl_radio_set_tx_power(param) < 0)
			return -UWL_PHY_ERR_HW_FAILURE;
		uwl_phy_pib.phyTransmitPower = param;
		break;
	case UWL_PHY_CCA_MODE :
		if (param < 1 || param > 3) {
			status = UWL_PHY_INVALID_PARAMETER;
			break;
		}
		if (uwl_radio_set_cca_mode(param) < 0)
			return -UWL_PHY_ERR_HW_FAILURE;
		uwl_phy_pib.phyCCAMode = param;
		break;
	case UWL_PHY_CURRENT_PAGE :
		/* chris: should I need to check according to the define
			   UWL_PHY_CHANNEL_PAGES ???
		 */
		if (param > UWL_PHY_CHANNEL_PAGE_LAST) {
			status = UWL_PHY_INVALID_PARAMETER;
			break;
		}
		/* TODO: chris: call the radio primitive for this ... exists??*/
		uwl_phy_pib.phyCurrentPage = param;
		break;
	case UWL_PHY_MAX_FRAME_DURATION :
	case UWL_PHY_SHR_DURATION :
	case UWL_PHY_SYMBOLS_PER_OCTET :
	case UWL_PHY_CHANNEL_SUPPORTED :
		status = UWL_PHY_READ_ONLY;
		break;
	default:
		status = UWL_PHY_UNSUPPORTED_ATTRIBUTE;
		break;
	}
	uwl_PLME_SET_confirm(status, PIBAttribute);
	return UWL_PHY_ERR_NONE;
}
