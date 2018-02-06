/** 
* @file uwl_mac_const.h
* @brief IEEE 802.15.4 MAC Constants
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_const_h__
#define __uwl_mac_const_h__

#ifdef UWL_TRUE
#undef UWL_TRUE
#endif
#define UWL_TRUE	1

#ifdef UWL_FALSE	
#undef UWL_FALSE	
#endif
#define UWL_FALSE	0

#define UWL_DEVICE_FFD		1
#define UWL_DEVICE_RFD		0

#ifndef UWL_MAC_GTS_QUEUE_SIZE	
#ifdef __AVR5__ /* FIXME: tmp solution!*/
#define UWL_MAC_GTS_QUEUE_SIZE	5
#else
#define UWL_MAC_GTS_QUEUE_SIZE	20
#endif
#endif /* UWL_MAC_GTS_QUEUE_SIZE */

#ifndef UWL_MAC_CAP_QUEUE_SIZE	
#ifdef __AVR5__ /* FIXME: tmp solution!*/
#define UWL_MAC_CAP_QUEUE_SIZE	5
#else
#define UWL_MAC_CAP_QUEUE_SIZE	20
#endif
#endif /* UWL_MAC_CAP_QUEUE_SIZE */

#ifndef UWL_MAC_IND_LIST_SIZE
#ifdef __AVR5__ /* FIXME: tmp solution!*/
#define UWL_MAC_IND_LIST_SIZE	5
#else
#define UWL_MAC_IND_LIST_SIZE	1
#endif
#endif /* UWL_MAC_IND_LIST_SIZE */

#define UWL_MAC_ERR_NONE 			1 /* Returned as positive! */
#define UWL_MAC_ERR_NOT_INITIALIZED		1
#define UWL_MAC_ERR_SF_NOT_INITIALIZED		2
#define UWL_MAC_ERR_INVALID_PARAM		3
#define UWL_MAC_ERR_PHY_FAILURE			4 /**< PHY bad reply. */
#define UWL_MAC_ERR_INVALID_LENGTH	5
#define UWL_MAC_ERR_STANDARD_UNSUPPORTED	10
#define UWL_MAC_ERR_DEBUG_INIT			11
#define UWL_MAC_ERR_GTS_MANIPULATION_DISABLED	20
#define UWL_MAC_ERR_GTS_CFP_TOO_LARGE		21
#define UWL_MAC_ERR_SUPERFRAME_CALLBACKS_DISABLED   22


/* TODO: these should depend on the current SO and BO settings!! */
#ifndef UWL_MAC_TICKS_BEFORE_TIMESLOT
//#define UWL_MAC_TICKS_BEFORE_BI			2
#define UWL_MAC_TICKS_BEFORE_TIMESLOT		2
#endif

/* chris: TODO: could we have a better choice for a default 64bits address? */
#ifndef UWL_MAC_DEVICE_EXTD_ADDRESS
#define UWL_MAC_DEVICE_EXTD_ADDRESS_HIGH	0x00000002
#define UWL_MAC_DEVICE_EXTD_ADDRESS_LOW		0x00000002
#endif

#define UWL_MAC_PANID_BROADCAST			0xFFFF
#define UWL_MAC_SHORT_ADDRESS_BROADCAST		0xFFFF
#define UWL_MAC_SHORT_ADDRESS_ASSOC_INVALID	0xFFFF
#define UWL_MAC_SHORT_ADDRESS_INVALID		0xFFFF
#define UWL_MAC_SHORT_ADDRESS_USE_EXTD		0xFFFE

#define UWL_MAC_NULL_SECURITY_PARAMS_LIST	0, 0, NULL, 0

/**
* @name IEEE 802.15.4 MAC Layer Constants
* 
* \see Table 85: Mac Sublayer Constants
* @{ */
#define UWL_aBaseSlotDuration		60 /**< Base Time slot duration 
						in symbols. */
#define UWL_aBaseSuperframeDuration	960/**< UWL_aBaseSlotDuration x 
						UWL_aNumSuperframeSlots. */
#define UWL_aExtendedAddress_high	UWL_MAC_DEVICE_EXTD_ADDRESS_HIGH
#define UWL_aExtendedAddress_low	UWL_MAC_DEVICE_EXTD_ADDRESS_LOW
#define UWL_aGTSDescPersistenceTime	4  /**< Duration in number of SFs. */
#define UWL_aMaxBeaconOverhead		75 /**< Overhead in bytes */
#define UWL_aMaxBeaconPayloadLength	52 /**< UWL_aMaxPHYPacketSize - 
						UWL_aMaxBeaconOverhead */
#define UWL_aMaxLostBeacons		4  /**< Number of consecutive losts. */
#define UWL_aMaxMACSafePayloadSize	102/**< UWL_aMaxPHYPacketSize -
						UWL_aMaxMPDUUnsecuredOverhead.*/
#define UWL_aMaxMACPayloadSize		118/**< UWL_aMaxPHYPacketSize -
						UWL_aMinMPDUOverhead. */
#define UWL_aMaxMPDUUnsecuredOverhead	25 /**< In bytes.*/
#define UWL_aMaxSIFSFrameSize		18 /**< In bytes. */
#define UWL_aMinCAPLength		440/**< In symbols. */
#define UWL_aMinMPDUOverhead		9  /**< In bytes.*/
#define UWL_aNumSuperframeSlots 	16 /**< Number of slots in a SF. */
#define UWL_aUnitBackoffPeriod		20 /**< In symbols. */
/**  @} */

#define UWL_MAC_ACK_MPDU_SIZE			4
#define UWL_MAC_MPDU_SIZE			127 /* TODO: WHY NOT 127 ???? */
#define UWL_MAC_MAX_MSDU_SIZE			UWL_aMaxMACPayloadSize 
//#define UWL_MAC_MPDU_SIZE			125 /* TODO: WHY NOT 127 ???? */
#define UWL_MAC_MPDU_FRAME_CONTROL_SIZE		2
#define UWL_MAC_MPDU_SEQ_NUMBER_SIZE		1
#define UWL_MAC_MPDU_PANID_SIZE			2
#define UWL_MAC_MPDU_ADDRESS_SHORT_SIZE		2
#define UWL_MAC_MPDU_ADDRESS_EXTD_SIZE		8
#define UWL_MAC_MPDU_MHR_BASE_SIZE		3
#define UWL_MAC_MPDU_MFR_SIZE			2
#define UWL_MAC_MPDU_SUPERFRAME_SPEC_SIZE	2
#define UWL_MAC_MPDU_GTS_SPEC_SIZE		1
#define UWL_MAC_MPDU_GTS_DIRECTIONS_SIZE	1
#define UWL_MAC_MPDU_GTS_DESCRIPTOR_SIZE	3
#define UWL_MAC_MPDU_PENDING_ADDR_SPEC_SIZE	1
#define UWL_MAC_ACK_SIZE			3

#define UWL_MAC_SUPERFRAME_FIRST_SLOT 		0
#define UWL_MAC_SUPERFRAME_LAST_SLOT 		15

#define UWL_MAC_GTS_MAX_NUMBER 			7
#define UWL_MAC_GTS_DIRECTION_IN 		1
#define UWL_MAC_GTS_DIRECTION_OUT 		0

#define UWL_MAC_COMMAND_FRAME_IDENTIFIER_SIZE	1
#define UWL_MAC_CAPABILITY_INFORMATION_SIZE		1
#define UWL_MAC_SHORT_ADDRESS_SIZE				2
#define UWL_MAC_ASSOCIATION_STATUS_SIZE			1




/* chris: TODO: What are these supposed to be???? ------> */
#define UWL_aMaxBE	5 
#define UWL_aMaxFrameOverhead          25
#define UWL_aMaxFrameResponseTime      1220
#define UWL_aMaxFrameRetries           1
//(SYNC)number of beacons lost before sending a Beacon-Lost indication
#define UWL_aMaxMACFrameSize           aMaxPHYPacketSize-aMaxFrameOverhead
#define UWL_aMinLIFSPeriod             40
#define UWL_aMinSIFSPeriod             12
#define UWL_aResponseWaitTime          32*aBaseSuperframeDuration
/* <-------------- TODO: see prev. comment!*/

#endif /* Header Protection */
