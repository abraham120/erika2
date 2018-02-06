/** 
* @file uwl_debug.c
* @brief Debug Module Implementation
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#include <util/uwl_debug.h>
#include <string.h>

#ifdef UWL_DEBUG
struct uwl_debug_stat_t uwl_debug_stats;
#endif
#ifdef UWL_DEBUG_LOG
/* TODO: chris: shall waste memory for this check variable or not? */
static uint8_t debug_initialized = 0; 
#endif

#define UWL_DEBUG_LOG_CONSOLE 0

int8_t uwl_debug_init(void)
{
	#ifdef UWL_DEBUG_TIME
	/* TODO: change this hardcoding!!!!! */
	if (daq_time_init(40000) < 0)
		return -1;
	/* TODO: initialize uwl_debug_stats */
	#endif
	#ifdef UWL_DEBUG_LOG
	debug_initialized = 0;
	console_descriptor_t *des = NULL;
	#ifdef UWL_DEBUG_LOG_SERIAL 
	des = console_serial_config(UWL_DEBUG_LOG_SERIAL_PORT, 
				    UWL_DEBUG_LOG_SERIAL_BAUDRATE,
				    UWL_DEBUG_LOG_SERIAL_OPT);
	#endif
	if (des == NULL)
		return -1;
	if (console_init(UWL_DEBUG_LOG_CONSOLE, des) < 0)
		return -1;
	debug_initialized = 1;
	return console_open(UWL_DEBUG_LOG_CONSOLE);
	#else
	return 1;
	#endif /* UWL_DEBUG_LOG */
}

int8_t uwl_debug_write(uint8_t *msg, uint16_t len) 
{
	#ifdef UWL_DEBUG_LOG
	if (debug_initialized)
		return console_write(UWL_DEBUG_LOG_CONSOLE, msg, len);
	return -1;
	#else
	return 0;
	#endif /* UWL_DEBUG_LOG */
}

int8_t uwl_debug_print(const char *msg) 
{
	#ifdef UWL_DEBUG_LOG_HAS_PRINT
	int8_t retv = 0;
	const char *m = "\n\rUWL_DEBUG_LOG: ";

	if (debug_initialized) {
		retv = console_write(UWL_DEBUG_LOG_CONSOLE, (uint8_t *) m, 
				     strlen(m));
		if (retv < 0)
			return retv;
		return console_write(UWL_DEBUG_LOG_CONSOLE, (uint8_t *) msg, 
				     strlen(msg));
	}
	return -1;
	#else
	return 1;
	#endif /* UWL_DEBUG_LOG_HAS_PRINT */
}

#ifdef DO_CASE_STRCPY 	
#undef DO_CASE_STRCPY 	
#endif

#define DO_CASE_STRCPY(x, out) 	\
case x:				\
strcpy((out), #x);		\
break;				\

void uwl_debug_sprint_phycode(enum uwl_phy_code_t c, char *out) 
{
	switch (c) {
	DO_CASE_STRCPY(UWL_PHY_BUSY, out);
	DO_CASE_STRCPY(UWL_PHY_BUSY_RX, out);
	DO_CASE_STRCPY(UWL_PHY_BUSY_TX, out);
	DO_CASE_STRCPY(UWL_PHY_FORCE_TRX_OFF, out);
	DO_CASE_STRCPY(UWL_PHY_IDLE, out);
	DO_CASE_STRCPY(UWL_PHY_INVALID_PARAMETER, out);
	DO_CASE_STRCPY(UWL_PHY_RX_ON, out);
	DO_CASE_STRCPY(UWL_PHY_SUCCESS, out);
	DO_CASE_STRCPY(UWL_PHY_TRX_OFF, out);
	DO_CASE_STRCPY(UWL_PHY_TX_ON, out);
	DO_CASE_STRCPY(UWL_PHY_UNSUPPORTED_ATTRIBUTE, out);
	DO_CASE_STRCPY(UWL_PHY_READ_ONLY, out);
	}
}

void uwl_debug_sprint_maccode(enum uwl_mac_code_t c, char *out)
{
	switch (c) {
	DO_CASE_STRCPY(UWL_MAC_SUCCESS, out);
	DO_CASE_STRCPY(UWL_MAC_PAN_AT_CAPACITY, out);
	DO_CASE_STRCPY(UWL_MAC_PAN_ACCESS_DENIED, out);
	DO_CASE_STRCPY(UWL_MAC_COUNTER_ERROR, out);
	DO_CASE_STRCPY(UWL_MAC_IMPROPER_KEY_TYPE, out);
	DO_CASE_STRCPY(UWL_MAC_IMPROPER_SECURITY_LEVEL, out);
	DO_CASE_STRCPY(UWL_MAC_UNSUPPORTED_LEGACY, out);
	DO_CASE_STRCPY(UWL_MAC_UNSUPPORTED_SECURITY, out);
	DO_CASE_STRCPY(UWL_MAC_BEACON_LOSS, out);
	DO_CASE_STRCPY(UWL_MAC_CHANNEL_ACCESS_FAILURE, out);
	DO_CASE_STRCPY(UWL_MAC_DEFINED, out);
	DO_CASE_STRCPY(UWL_MAC_DISABLE_TRX_FAIULURE, out);
	DO_CASE_STRCPY(UWL_MAC_FRAME_TOO_LONG, out);
	DO_CASE_STRCPY(UWL_MAC_SECURITY_ERROR, out);
	DO_CASE_STRCPY(UWL_MAC_INVALID_GTS, out);
	DO_CASE_STRCPY(UWL_MAC_INVALID_HANDLE, out);
	DO_CASE_STRCPY(UWL_MAC_INVALID_PARAMETER, out);
	DO_CASE_STRCPY(UWL_MAC_NO_ACK, out);
	DO_CASE_STRCPY(UWL_MAC_NO_BEACON, out);
	DO_CASE_STRCPY(UWL_MAC_NO_DATA, out);
	DO_CASE_STRCPY(UWL_MAC_NO_SHORT_ADDRESS, out);
	DO_CASE_STRCPY(UWL_MAC_OUT_OF_CAP, out);
	DO_CASE_STRCPY(UWL_MAC_PAN_ID_CONFLICT, out);
	DO_CASE_STRCPY(UWL_MAC_REALIGNMENT, out);
	DO_CASE_STRCPY(UWL_MAC_TRANSACTION_EXPIRED, out);
	DO_CASE_STRCPY(UWL_MAC_TRANSACTION_OVERFLOW, out);
	DO_CASE_STRCPY(UWL_MAC_TX_ACTIVE, out);
	DO_CASE_STRCPY(UWL_MAC_UNAVAILABLE_KEY, out);
	DO_CASE_STRCPY(UWL_MAC_UNSUPPORTED_ATTRIBUTE, out);
	DO_CASE_STRCPY(UWL_MAC_INVALID_ADDRESS, out);
	DO_CASE_STRCPY(UWL_MAC_ON_TIME_TOO_LONG, out);
	DO_CASE_STRCPY(UWL_MAC_PAST_TIME, out);
	DO_CASE_STRCPY(UWL_MAC_TRACKING_OFF, out);
	DO_CASE_STRCPY(UWL_MAC_INVALID_INDEX, out);
	DO_CASE_STRCPY(UWL_MAC_LIMIT_REACHED, out);
	DO_CASE_STRCPY(UWL_MAC_READ_ONLY, out);
	DO_CASE_STRCPY(UWL_MAC_SCAN_IN_PROGRESS, out);
	DO_CASE_STRCPY(UWL_MAC_SUPERFRAME_OVERLAP, out);
	DO_CASE_STRCPY(UWL_MAC_BEACON_LOST, out);
	}
} 

