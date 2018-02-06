/** 
* @file uwl_mac_types.h
* @brief IEEE 802.15.4 MAC Types
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_types_h__
#define __uwl_mac_types_h__

#include <hal/uwl_compiler.h>
#include <mac/uwl_mac_const.h>

typedef uint32_t uwl_mac_dev_addr_extd_t[2]; 
typedef uint16_t uwl_mac_dev_addr_short_t; 
typedef uint32_t *uwl_mac_dev_addr_extd_ptr_t; 
typedef uint16_t *uwl_mac_dev_addr_short_ptr_t; 
#ifdef UWL_DEVICE_ADDRESS_16_ONLY /* TODO: check this in the varius call!*/
typedef uwl_mac_dev_addr_short_t uwl_mac_dev_addr_t; 
#else
typedef uwl_mac_dev_addr_extd_t uwl_mac_dev_addr_t; 
/*TODO: simplify writing the address with some macro? */
#endif

enum uwl_mac_code_t {
	//UWL_MAC_ASSOCIATION_SUCCESS	= 0x00,
	UWL_MAC_SUCCESS			= 0x00,
	UWL_MAC_PAN_AT_CAPACITY		= 0x01,
	UWL_MAC_PAN_ACCESS_DENIED	= 0x02,
	UWL_MAC_COUNTER_ERROR		= 0xDB,
	UWL_MAC_IMPROPER_KEY_TYPE	= 0xDC,
	UWL_MAC_IMPROPER_SECURITY_LEVEL	= 0xDD,
	UWL_MAC_UNSUPPORTED_LEGACY	= 0xDE,
	UWL_MAC_UNSUPPORTED_SECURITY	= 0xDF,
	UWL_MAC_BEACON_LOSS		= 0xE0,
	UWL_MAC_CHANNEL_ACCESS_FAILURE	= 0xE1,
	UWL_MAC_DEFINED			= 0xE2,
	UWL_MAC_DISABLE_TRX_FAIULURE	= 0xE3,
	UWL_MAC_FRAME_TOO_LONG		= 0xE5,
	UWL_MAC_SECURITY_ERROR		= 0xE4,
	UWL_MAC_INVALID_GTS		= 0xE6, 
	UWL_MAC_INVALID_HANDLE		= 0xE7,
	UWL_MAC_INVALID_PARAMETER	= 0xE8,
	UWL_MAC_NO_ACK			= 0xE9,
	UWL_MAC_NO_BEACON		= 0xEA,
	UWL_MAC_NO_DATA			= 0xEB,
	UWL_MAC_NO_SHORT_ADDRESS	= 0xEC,
	UWL_MAC_OUT_OF_CAP		= 0xED,
	UWL_MAC_PAN_ID_CONFLICT		= 0xEE,
	UWL_MAC_REALIGNMENT		= 0xEF,
	UWL_MAC_TRANSACTION_EXPIRED	= 0xF0,
	UWL_MAC_TRANSACTION_OVERFLOW	= 0xF1,
	UWL_MAC_TX_ACTIVE		= 0xF2,
	UWL_MAC_UNAVAILABLE_KEY		= 0xF3,
	UWL_MAC_UNSUPPORTED_ATTRIBUTE	= 0xF4,
	UWL_MAC_INVALID_ADDRESS		= 0xF5,
	UWL_MAC_ON_TIME_TOO_LONG	= 0xF6,
	UWL_MAC_PAST_TIME		= 0xF7,
	UWL_MAC_TRACKING_OFF		= 0xF8,
	UWL_MAC_INVALID_INDEX		= 0xF9,
	UWL_MAC_LIMIT_REACHED		= 0xFA,
	UWL_MAC_READ_ONLY		= 0xFB,
	UWL_MAC_SCAN_IN_PROGRESS	= 0xFC,
	UWL_MAC_SUPERFRAME_OVERLAP	= 0xFD,
	UWL_MAC_BEACON_LOST // TODO: is this an error? should be LOSS??? 
};

/* TODO complete this struc!!!! */
enum uwl_mac_pib_id_t {
	UWL_MAC_TODO,
	UWL_MAC_COORD_SHORT_ADDRESS	= 0x4b,
	UWL_MAC_PAN_ID				= 0x50,
	UWL_MAC_SHORT_ADDRESS 		= 0x53,
};

/* TODO: optimization on the types!! (make use of bit fields!!) */
struct uwl_pan_des_t {
	uint8_t CoordAddrMode;
	uint16_t CoordPANId;
	uwl_mac_dev_addr_t CoordAddress;
	uint8_t LogicalChannel;
	uint8_t ChannelPage;
	uint16_t SuperframeSpec;
	uint8_t GTSPermit;
	uint8_t LinkQuality;
	uint32_t TimeStamp;
	enum uwl_mac_code_t SecurityFailure;
	uint8_t SecurityLevel;
	uint8_t KeyIdMode;
	uint8_t KeySource[8];
	uint8_t KeyIndex;
};

/** 
* @brief IEEE 802.15.4 MAC PAN Information Base
*
* \todo Write comments!
*/

/*TODO: reorder the fields to have chance for compact representation (packing)*/
struct uwl_mac_pib_t {
	uint8_t macAckWaitDuration;	/*TODO: check representation! */
	unsigned macAssociatedPANCoord : 1;
	#ifndef UWL_RFD_DISABLE_OPTIONAL
	unsigned macAssociationPermit : 1;
	#endif /* UWL_RFD_DISABLE_OPTIONAL */
	unsigned macAutoRequest : 1;
	unsigned macBattLifeExt : 1;
	uint8_t macBattLifeExtPeriods; /* TODO: reduce representation! */
	#ifndef UWL_RFD_DISABLE_OPTIONAL
	//uint8_t macBeaconPayload[aMaxBeaconPayloadLength];
	uint8_t *macBeaconPayload; /* TODO: use this?? */
	uint8_t macBeaconPayloadLenght; /* TODO: reduce representation! */
	uint8_t macBeaconOrder;		/* TODO: reduce representation! */
	uint32_t macBeaconTxTime;	/* TODO: reduce representation?? */
	uint8_t macBSN;
	#endif /* UWL_RFD_DISABLE_OPTIONAL */
	//EE_UINT32 macCoordExtendedAddress0;	// TODO: REMOVE
	//EE_UINT32 macCoordExtendedAddress1;	// TODO: REMOVE
	uwl_mac_dev_addr_extd_t macCoordExtendedAddress;
	uwl_mac_dev_addr_short_t macCoordShortAddress;
	uint8_t macDSN;
	#ifndef UWL_DEVICE_DISABLE_OPTIONAL
	uint8_t macGTSPermit;
	#endif /* UWL_DEVICE_DISABLE_OPTIONAL */
	uint8_t macMaxBE;		/* TODO: reduce representation! */
	uint8_t macMaxCSMABackoffs;	/* TODO: reduce representation! */
	uint32_t macMaxFrameTotalWaitTime; /*TODO: check representation! */
	uint8_t macMaxFrameRetries; 	/* TODO: reduce representation! */
	uint8_t macMinBE;		/* TODO: reduce representation! */
	uint8_t macMinLIFSPeriod;	/* TODO: check representation! */
	uint8_t macMinSIFSPeriod;	/* TODO: check representation! */
	uint16_t macPANId;
	#ifndef UWL_RFD_DISABLE_OPTIONAL
	unsigned macPromiscuousMode : 1;
	#endif /* UWL_RFD_DISABLE_OPTIONAL */
	uint8_t macResponseWaitTime;	/* TODO: reduce representation! */
	unsigned macRxOnWhenIdle : 1;
	unsigned macSecurityEnabled : 1;
	uwl_mac_dev_addr_short_t macShortAddress;
	#ifndef UWL_RFD_DISABLE_OPTIONAL
	uint8_t macSuperframeOrder;	/* TODO: reduce representation! */
	#endif /* UWL_RFD_DISABLE_OPTIONAL */
	uint16_t macSyncSymbolOffset;	/* TODO: reduce representation! */
	unsigned macTimestampSupported : 1;	
	uint32_t macTransactionPersistenceTime; /*TODO: check representation!*/
};


typedef uint8_t uwl_mpdu_t[UWL_MAC_MPDU_SIZE]; 
typedef uint8_t *uwl_mpdu_ptr_t; 

struct uwl_mac_frame_t {
	uwl_mpdu_t mpdu;
	unsigned reserved : 1;
	unsigned mpdu_size : 7;
	uint8_t msdu_handle;
};

enum uwl_mac_frame_type_t {
	UWL_MAC_TYPE_BEACON 	= 0x0,
	UWL_MAC_TYPE_DATA	= 0x1,
	UWL_MAC_TYPE_ACK	= 0x2,
	UWL_MAC_TYPE_COMMAND	= 0x3,
};

enum uwl_mac_addr_mode_t {
	UWL_MAC_ADDRESS_NONE 	= 0x0,
	UWL_MAC_ADDRESS_SHORT 	= 0x2,
	UWL_MAC_ADDRESS_EXTD 	= 0x3,
};

enum uwl_mac_cmd_type_t {
	UWL_MAC_CMD_ASSOCIATION_REQUEST = 0x01,
	UWL_MAC_CMD_ASSOCIATION_RESPONSE = 0x02,
	UWL_MAC_CMD_DATA_REQUEST = 0x04,
};

struct uwl_gts_info_t {
//	uint8_t gts_id;
	unsigned starting_tslot : 4;
	unsigned length : 4;
	unsigned direction : 1;
	uint16_t dev_address; 
	uint8_t expiration;
};

#endif /* Header Protection */
