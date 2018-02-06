/**
* @file uwl_radio_cc2420.c
* @brief Abstract Radio functions
* @author Christian Nastasi
* @author Gianluca Franchino
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file contains the abstraction layer for the radio capabilities
* used by the uWireless modules.
*
*/

#ifdef UWL_DEBUG_LOG
#include <util/uwl_debug.h>
#include <string.h>
#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
#endif

#include <hal/uwl_radio_cc2420.h>
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

/******************************************************************************/
/*                         Radio MAC Public Functions                         */
/******************************************************************************/
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
	/*
	char s[100];
	sprintf(s, "PD_DATA_indication(len=%u,*p=%u,lqi=%u)",
		psduLength, (uint16_t) psdu, ppduLinkQuality);
	uwl_debug_print(s);
	*/
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
	#ifdef UWL_DEBUG_LOG
//	char s[100];
//	char s1[30];
//	uwl_debug_sprint_phycode(status, s1);
//	sprintf(s, "PLME_SET_TRX_STATE_confirm(%s)", s1);
//	uwl_debug_print(s);
	#endif
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
