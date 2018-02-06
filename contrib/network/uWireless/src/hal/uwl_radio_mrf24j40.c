/**
* @file uwl_radio_mrf24j40.c
* @brief Abstract Radio functions
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file contains the abstraction layer for the radio capabilities
* used by the uWireless modules.
*
*/

#include <util/uwl_debug.h>

#ifdef UWL_DEBUG_LOG
#include <string.h>

#ifdef __STDIO_COMPILER_BUG__
//unsigned int strlen(const char *str);
int sprintf(char *, const char *, ...);
#else
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#endif

#include <hal/uwl_radio_mrf24j40.h>
#include <mac/uwl_mac_internal.h>

/******************************************************************************/
/*                      Radio MAC/PHY Private Data                            */
/******************************************************************************/
#ifndef CSMA_UNSLOTTED
static uwl_mpdu_t beacon;
static uint8_t beacon_size;
#endif
static enum uwl_phy_code_t phy_status;

static uwl_mpdu_t ack;

static volatile uint8_t tx_status;

/******************************************************************************/
/*                         Radio MAC Public Functions                         */
/******************************************************************************/
uint8_t uwl_last_tx_status(void)
{
	return tx_status;
}

static void tx_finished_func(uint8_t status) {
	mrf24j40_enable_carrier_sense();
	if (status)
		tx_status = UWL_RADIO_ERR_PHY_FAILURE;
	else
		tx_status = UWL_RADIO_ERR_NONE;
}

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
int8_t uwl_radio_send(uint8_t *buf, uint8_t len)
{
	/** Carrier sense is disabled and Energy threshold is set to the maximum value.
	The registers of the MRF24J40 transceiver are restored
	to the initial values in tx_finished callback */
	mrf24j40_disable_carrier_sense();
	tx_status = UWL_RADIO_ERR_TX_WAIT;
	uwl_debug_print("   uwl_radio_send(...)");// TODO: REMOVE
	if (mrf24j40_store_norm_txfifo( buf, len) < 0)
		return -1; // len is either less than 0 or
			   // greter than 127.
	uwl_debug_print("      Store FIFO OK!");// TODO: REMOVE
	mrf24j40_set_tx();
	uwl_debug_print("      Set TX OK!");// TODO: REMOVE
	/* Wait until the transmission has finished. */
	while( tx_status == UWL_RADIO_ERR_TX_WAIT )
		;
	uwl_debug_print("      Loop 0x08 ok!");// TODO: REMOVE
	uwl_debug_print("      returning OK!");// TODO: REMOVE
	/* Everything goes well. */
	return tx_status;
}


int8_t uwl_radio_init(void)
{
	/* GF: interrupt set up is hard coded. May be a better way to do that
	*	is needed!
	*
	*Set interrupts register with 0xF6, which means:
	* 7 = '1' = Disables the Sleep alert interrupt
	* 6 = '1' = Disables the wake-up alert interrupt
	* 5 = '1' = Disables the half symbol timer interrupt
	* 4 = '1' = Disables the security key request interrupt
	* 3 = '0' = Enables the RX FIFO reception interrupt
	* 2 = '1' = Disables the TX GTS2 FIFO transmission interrupt
	* 1 = '1' = Disables the TX GTS1 FIFO transmission interrupt
	* 0 = '0' = Enables the TX Normal FIFO transmission interrupt	
	*/
	mrf24j40_set_tx_finished_callback(&tx_finished_func);
	#if defined(UWL_USE_SPI_PORT_1)
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_1);
	#elif defined(UWL_USE_SPI_PORT_1A) && defined(__32MX795F512L__)
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_1A);	
	#elif defined(UWL_USE_SPI_PORT_2A) && defined (__32MX795F512L__)
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_2A);
	#elif defined(UWL_USE_SPI_PORT_3A) && defined (__32MX795F512L__)
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_3A);
	#elif defined(UWL_USE_SPI_PORT_2) && defined (__32MX795F512L__)
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_2);
	#else //Original Default Behaviour
	return mrf24j40_init(0xF6, 11, MRF24J40_SPI_PORT_2);
	#endif

}

#ifndef CSMA_UNSLOTTED
int8_t uwl_radio_mac_create_beacon(void)
{
	/* TODO: chris: IDEA: We can use this symbol to force the 
			uwl_radio_mac module to always use software mac */
	#ifdef UWL_MAC_ALWAYS_SOFTWARE
	#else
	#endif
	beacon_size = uwl_mac_create_beacon(beacon);
	if (beacon_size >= UWL_MAC_MPDU_SIZE)
		return -1;
	return 1;
}

int8_t uwl_radio_mac_send_beacon(void)
{
	/* TODO: chris: IDEA: We can use this symbol to force the 
			uwl_radio_mac module to always use software mac */
	#ifdef UWL_MAC_ALWAYS_SOFTWARE
	#else
	#endif
	/* NOTE: this is not going through the uwl_PD_DATA function thus the
		 exception caught is performed within  the radio_send!! */
	/* TODO: is the error returned in the readio_send?? */
	/* phy_status = UWL_PHY_SUCCESS; */
	if (uwl_radio_send((uint8_t *) beacon, beacon_size) < 0) {
		/* phy_status = ERROR_OF_THE_PD_DATA_CONFIRM; */
		return -UWL_RADIO_ERR_PHY_FAILURE;
	}
	return -UWL_RADIO_ERR_NONE; 
}
#endif

int8_t uwl_radio_store_ack(uint8_t *buf, uint8_t len)
{
    /* TODO: chris: IDEA: We can use this symbol to force the
            uwl_radio_mac module to always use software mac */
    #ifdef UWL_MAC_ALWAYS_SOFTWARE
    #else
    #endif

    if (len != UWL_MAC_ACK_SIZE)
        return -1;
    memcpy(ack, buf, len);

    return 1;
}

int8_t uwl_radio_send_ack(void)
{
    /* TODO: chris: IDEA: We can use this symbol to force the
            uwl_radio_mac module to always use software mac */
    #ifdef UWL_MAC_ALWAYS_SOFTWARE
    #else
    #endif
    /* NOTE: this is not going through the uwl_PD_DATA function thus the
         exception caught is performed within  the radio_send!! */
    /* TODO: is the error returned in the readio_send?? */
    /* phy_status = UWL_PHY_SUCCESS; */
    if (uwl_radio_send((uint8_t *) ack, UWL_MAC_ACK_SIZE) < 0) {
        /* phy_status = ERROR_OF_THE_PD_DATA_CONFIRM; */
        return -UWL_RADIO_ERR_PHY_FAILURE;
    }
    return -UWL_RADIO_ERR_NONE;
}

/******************************************************************************/
/*                         Radio PHY Public Functions                         */
/******************************************************************************/
enum uwl_phy_code_t uwl_radio_phy_get_status(void)
{
	return phy_status;
}

int8_t uwl_radio_phy_set_channel(uint8_t ch)
{
	int8_t retv;

	retv = uwl_PLME_SET_request(UWL_PHY_CURRENT_CHANNEL, (void *) &ch);
	if (retv < 0)
		return retv;
	if (phy_status != UWL_PHY_SUCCESS) /* Check Expected status */
		return -UWL_RADIO_ERR_PHY_FAILURE;
	return UWL_RADIO_ERR_NONE;
}

int8_t uwl_radio_phy_set_rx_on(void)
{
	int8_t retv;

	retv = uwl_PLME_SET_TRX_STATE_request(UWL_PHY_RX_ON);
	if (retv < 0)
		return retv;
	if (phy_status != UWL_PHY_RX_ON) /* Check Expected status */
		return -UWL_RADIO_ERR_PHY_FAILURE;
	return UWL_RADIO_ERR_NONE;
}

int8_t uwl_radio_phy_send_now(uint8_t *data, uint8_t size)
{
	/* NOTE: this is not going through the uwl_PD_DATA function thus the
		 exception caught is performed within  the radio_send!! */
	/* TODO: is the error returned in the readio_send?? */
	/* phy_status = UWL_PHY_SUCCESS; */
	if (uwl_radio_send(data, size) < 0) {
		/* phy_status = ERROR_OF_THE_PD_DATA_CONFIRM; */
		return -UWL_RADIO_ERR_PHY_FAILURE;
	}
	return -UWL_RADIO_ERR_NONE; 
}

#ifndef UWL_USE_ONLY_802154_PHY	
/******************************************************************************/
/*                                                                            */
/*                   PHY LAYER CALLBACKS: Indication + Confirms               */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                 PD-Callback Definition (phy2mac SIDE)                      */
/******************************************************************************/
int8_t uwl_PD_DATA_confirm(enum uwl_phy_code_t status)
{
	#ifdef UWL_DEBUG_LOG
	char s[100];
	char s1[30];
	uwl_debug_sprint_phycode(status, s1);
	sprintf(s, "PD_DATA_confirm(%s)", s1);
	uwl_debug_print(s);
	#endif
	return UWL_PHY_ERR_NONE;
}
 
int8_t uwl_PD_DATA_indication(uint8_t psduLength, uint8_t *psdu, 
			      uint8_t ppduLinkQuality)
{
	#ifdef UWL_DEBUG_LOG
	char s[100];
	sprintf(s, "PD_DATA_indication(len=%u,*p=%p,lqi=%u)",
		psduLength, psdu, ppduLinkQuality);
	uwl_debug_print(s);
	#endif
	/* TODO: use return value!!*/
	uwl_mac_parse_received_mpdu(psdu, psduLength);
	return UWL_PHY_ERR_NONE;
}
 

/******************************************************************************/
/*               PLME-Callback Definition (phy2mac SIDE)                      */
/******************************************************************************/
int8_t uwl_PLME_CCA_confirm(enum uwl_phy_code_t status)
{
	#ifdef UWL_DEBUG_LOG
	char s[100];
	char s1[30];
	uwl_debug_sprint_phycode(status, s1);
	sprintf(s, "PLME_CCA_confirm(%s)", s1);
	uwl_debug_print(s);
	#endif
	phy_status = status;
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_ED_confirm(enum uwl_phy_code_t status, uint8_t EnergyLevel)
{
	#ifdef UWL_DEBUG_LOG
	char s[100];
	char s1[30];
	uwl_debug_sprint_phycode(status, s1);
	sprintf(s, "PLME_ED_confirm(%s, el=%u)", s1, EnergyLevel);
	uwl_debug_print(s);
	#endif
	phy_status = status;
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_GET_confirm(enum uwl_phy_code_t status, 
			    enum uwl_phy_pib_id_t PIBAttribute, 
			    void *PIBAttributeValue)
{
	#ifdef UWL_DEBUG_LOG
	uint8_t value = *((uint8_t*)PIBAttributeValue);
	char s[100];
	char s1[30];
	uwl_debug_sprint_phycode(status, s1);
	sprintf(s, "PLME_GET_confirm(%s, a=%u, v=%u)", s1, PIBAttribute, value);
	uwl_debug_print(s);
	#endif
	phy_status = status;
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_SET_TRX_STATE_confirm(enum uwl_phy_code_t status)
{
//	#ifdef UWL_DEBUG_LOG
//	char s[100];
//	char s1[30];
//	uwl_debug_sprint_phycode(status, s1);
//	sprintf(s, "PLME_SET_TRX_STATE_confirm(%s)", s1);
//	uwl_debug_print(s);
//	#endif
	phy_status = status;
	return UWL_PHY_ERR_NONE;
}

int8_t uwl_PLME_SET_confirm(enum uwl_phy_code_t status, 
			    enum uwl_phy_pib_id_t PIBAttribute)
{
	#ifdef UWL_DEBUG_LOG
	char s[100];
	char s1[30];
	uwl_debug_sprint_phycode(status, s1);
	sprintf(s, "PLME_SET_confirm(%s, a=%u)", s1, PIBAttribute);
	uwl_debug_print(s);
	#endif
	phy_status = status;
	return UWL_PHY_ERR_NONE;
}

#endif /* UWL_USE_ONLY_802154_PHY */
