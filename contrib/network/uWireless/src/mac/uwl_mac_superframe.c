/* @file uwl_mac_superframe.c
* @brief IEEE 802.15.4 MAC Layer Superframe Management
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/

#include <mac/uwl_mac_internal.h>
#include <hal/uwl_radio.h>
#include <hal/uwl_rand.h>
#include <kal/uwl_kal.h>
#include <util/uwl_debug.h>
#include <net/uwl_net.h>

#ifdef NEXT_TSLOT
#undef NEXT_TSLOT
#endif
#define NEXT_TSLOT(idx) (((idx) + 1) % 16)

#ifdef TIME32_SUBTRACT
#undef TIME32_SUBTRACT
#endif
//#ifdef UWL_DEBUG_LOG
//#include <stdio.h> //TODO: REMOVE together with the sprintf() !!!!!
//#endif
//#ifdef UWL_DEBUG_LOG
//char stri[100];
//#endif
#define TIME32_SUBTRACT(t1, t2) ((t1)>=(t2) ? (t1)-(t2) : 0xFFFFFFFF-(t2)+(t1))

enum uwl_mac_csma_state_t {
	CSMA_STATE_INIT = 0,
	CSMA_STATE_DELAY,
	CSMA_STATE_CCA,
};

struct uwl_mac_csma_params_t {
	unsigned NB : 4;
	unsigned BE : 4;
	unsigned CW : 2;
	unsigned state : 2;
	unsigned slotted : 1;
	unsigned reserved : 2;
};

UWL_KAL_TASK(MAC_TIMESLOT, 10);
UWL_KAL_TASK(MAC_BEFORE_TIMESLOT, 10);
UWL_KAL_TASK(MAC_BACKOFF_PERIOD, 10);
UWL_KAL_TASK(MAC_GTS_SEND, 10);

UWL_KAL_MUTEX(MAC_MUTEX, MAC_TIMESLOT);
UWL_KAL_MUTEX(MAC_SEND_MUTEX, MAC_BACKOFF_PERIOD);
/*
UWL_KAL_MUTEX(MAC_MUTEX, MAC_BEFORE_TIMESLOT);
UWL_KAL_MUTEX(MAC_MUTEX, MAC_BACKOFF_PERIOD);
*/

UWL_KAL_MUTEX(MAC_GTS_SEND_MUTEX, MAC_TIMESLOT);
UWL_KAL_MUTEX(MAC_GTS_SEND_MUTEX, MAC_GTS_SEND);

/******************************************************************************/
/*                          MAC Tasks Private Data                            */
/******************************************************************************/
static uint8_t current_tslot = UWL_MAC_SUPERFRAME_LAST_SLOT;
static struct {
	unsigned has_idle : 1;		/* There is an Idle period */
	unsigned wait_sf_end : 1;	/* Wait for End Of SF (BO<SO) */
	unsigned had_cfp : 1;		/* There was a CFP in the previous SF */
	unsigned first_tslot_twice : 1;	/* First tslot activated twice */
	unsigned gts_sending : 1;	/* GTS_SENT task is 'active' */
	unsigned in_tx_gts : 1;		/* Current tslot is in a TX GTS */
	unsigned gts_tx_on_cfp_end : 1;	/* There is a TX GET at the CFP end */
	unsigned gts_schedule_idx : 3;	/* ID of the next GTS slot (0...6) */
	unsigned cfp_start_tslot : 5;	/* CFP Start tslot */
} sf_flags = {
	.has_idle = UWL_FALSE,
	.wait_sf_end = UWL_FALSE,
	.had_cfp = UWL_FALSE,
	.first_tslot_twice = UWL_FALSE,
	.gts_sending = UWL_FALSE,
	.in_tx_gts = UWL_FALSE,
	.gts_tx_on_cfp_end = UWL_FALSE,
	.gts_schedule_idx = 0,
	.cfp_start_tslot = UWL_MAC_SUPERFRAME_LAST_SLOT + 1
};
static uint32_t time_reference = 0;
static struct uwl_mac_csma_params_t csma_params;
static uint8_t csma_delay_counter = 0;
static uint16_t lifs_bytes = 0;
static uint16_t sifs_bytes = 0;
static uint16_t btick_bytes = 0;
static uint32_t cap_available_bytes = 0;
//static uint32_t gts_available_bytes = 0;
static uint32_t gts_available_bytes[UWL_MAC_GTS_MAX_NUMBER]
		COMPILER_ATTRIBUTE_FAR = {0, 0, 0, 0, 0, 0, 0};
#ifdef UWL_SUPERFRAME_CALLBACKS
static void (* before_beacon_callback)(void) = NULL;
static void (* on_beacon_callback)(void) = NULL;
#endif

//Variable for associtae request at the device, to resend association req.
extern int16_t associate_ack_counter;
//extern struct uwl_mac_frame_t ass_req_ack_wait;
/******************************************************************************/
/*                      MAC Genaral Private Functions                         */
/******************************************************************************/
COMPILER_INLINE void stop_activations(void)
{
	/* FIXME: now I'm ignoring the return values! */
	uwl_kal_cancel_activation(MAC_TIMESLOT);
	uwl_kal_cancel_activation(MAC_BEFORE_TIMESLOT);
	uwl_kal_cancel_activation(MAC_BACKOFF_PERIOD);
}

COMPILER_INLINE void start_activations(uint32_t offset)
{
	uint32_t t;

	if (offset == 0)
		offset = UWL_MAC_TICKS_BEFORE_TIMESLOT;
		//offset = UWL_MAC_TICKS_BEFORE_TIMESLOT + 1;
	t = UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder);
	/* FIXME: now I'm ignoring the return values! */
	uwl_kal_set_activation(MAC_BEFORE_TIMESLOT,
				offset + t - UWL_MAC_TICKS_BEFORE_TIMESLOT, t);
	uwl_kal_set_activation(MAC_TIMESLOT, offset, t);
	uwl_kal_set_activation(MAC_BACKOFF_PERIOD, offset, 1);
}

COMPILER_INLINE void restart_activations(uint32_t offset)
{
	stop_activations();
	start_activations(offset);
}

COMPILER_INLINE void resync_activations(void)
{
	uint32_t t;

	stop_activations();
	t = UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder);
	current_tslot = UWL_MAC_SUPERFRAME_LAST_SLOT;
	uwl_kal_set_activation(MAC_BEFORE_TIMESLOT,
			       t - UWL_MAC_TICKS_BEFORE_TIMESLOT, t);
	uwl_kal_set_activation(MAC_TIMESLOT, 0, t);
	uwl_kal_set_activation(MAC_BACKOFF_PERIOD, 0, 1);
}

COMPILER_INLINE uint32_t bticks_to_bytes(uint32_t bt)
{
	/* TODO: change this hard-coding (320 microsecond) ? */
	bt *= 32; /* bt1 = bt0 x 320us x 10^-1 */
	bt *= uwl_radio_phy_get_bitrate() / 80; /* bt2 = bt1 x Bps x 10^-1 */
	bt /= 10000; /* bt3 = bt2 x 10^-4 [us x Bps x 10^-6] */
	return bt;
}

COMPILER_INLINE void recharge_gts_bytes(uint8_t len, uint8_t gts_idx)
{
	if (len != 0) {
		gts_available_bytes[gts_idx] = bticks_to_bytes((uint32_t) len *
			       UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder));
		gts_available_bytes[gts_idx] -= lifs_bytes;
	} else {
		gts_available_bytes[gts_idx] = 0;
	}
}

COMPILER_INLINE void csma_init(void)
{
	csma_params.NB = 0;
	if (csma_params.slotted) {
		csma_params.CW = 2;
		csma_params.BE = (uwl_mac_pib.macBattLifeExt == 1 &&
				 2 < uwl_mac_pib.macMinBE) ?
				 2 : uwl_mac_pib.macMinBE;
	} else {
		csma_params.BE = uwl_mac_pib.macMinBE;
	}
}

COMPILER_INLINE void csma_set_delay(void)
{
	csma_delay_counter = uwl_rand_8bit() %
			     ((((uint8_t) 1) << csma_params.BE) - 1);
}

COMPILER_INLINE uint8_t csma_check_available_cap(uint8_t len, uint8_t has_ack)
{
	/* TODO: verify if the current check is correct
		 (what about phy padding?)
	*/
	uint32_t x = len;
//char s[100];

//sprintf(s,"a=%u l=%u", has_ack, len);
//uwl_debug_print(s);
	x = x << 1; /* X = len x 2 */
//sprintf(s,"x1=%lu", x);
//uwl_debug_print(s);
	if (has_ack) {
		x += UWL_MAC_ACK_MPDU_SIZE << 1; /* X = (len + ACK) x 2 */
		x += bticks_to_bytes(UWL_aTurnaroundTime_btick);
	}
//sprintf(s,"x2=%lu", x);
//uwl_debug_print(s);
	x += len < UWL_aMaxSIFSFrameSize ?  sifs_bytes : lifs_bytes;
//sprintf(s,"x3=%lu c=%lu", x, cap_available_bytes);
//uwl_debug_print(s);
	return (x <= cap_available_bytes);
}

COMPILER_INLINE void stop_previous_cfp(void)
{
	uint8_t i = 0;

	/* NOTE: this if for the GTS that terminates
		 with last timeslot expiration */
	if (sf_flags.gts_tx_on_cfp_end == UWL_FALSE)
		return;
	uwl_kal_mutex_wait(MAC_MUTEX);
	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator){
		i = UWL_MAC_GTS_MAX_NUMBER - 1;
		recharge_gts_bytes(uwl_gts_schedule[i].length, i);
	} else {
		recharge_gts_bytes(uwl_mac_gts_stat.tx_length, 0);
	}
	uwl_kal_mutex_signal(MAC_MUTEX);
	sf_flags.in_tx_gts = UWL_FALSE;
	sf_flags.gts_sending = 0;
	/* NOTE: recharging of 'gts_available_bytes' is done
	 by the start_beacon_interval() */
	uwl_gts_queue_flush(i);
	uwl_kal_cancel_activation(MAC_GTS_SEND); /* TODO: has effect? */
}

/******************************************************************************/
/*                      MAC CAP and CFP Management Functions                  */
/******************************************************************************/
#ifdef __JUST_MEASURE_FOR_PAPER__
#include "daq_time.h"
extern struct daq_time_t downlink;
#endif
static void csma_perform_slotted(void)
{
	int8_t tmp;
	uint32_t dst_addr1;
	uint32_t dst_addr2;
	uint8_t pointer;
	uint16_t dst_pan_addr;

	struct uwl_mac_frame_t *frame;

	if (uwl_mac_status.sf_context != UWL_MAC_SF_CAP) {
		return;
	}
	if (cap_available_bytes >= btick_bytes) {
		cap_available_bytes -= btick_bytes;
	}
	if (csma_params.state == CSMA_STATE_INIT) {
		if (cqueue_is_empty(&uwl_mac_queue_cap) &&
				uwl_mac_data_req.data_req == 0)
			return;
		csma_init();
		csma_set_delay();
		csma_params.state = CSMA_STATE_DELAY;
		//uwl_debug_print("I->D");
		return;
	}
	if (csma_params.state == CSMA_STATE_DELAY) {
		if (csma_delay_counter-- == 0) {
			uwl_kal_mutex_wait(MAC_SEND_MUTEX);
			frame = (struct uwl_mac_frame_t*)
					cqueue_first(&uwl_mac_queue_cap);
			uwl_kal_mutex_signal(MAC_SEND_MUTEX);
			/* Something must be there, check again? */
			/* if (!frame) ERRORE!!!!!*/
			if (frame) {
				tmp = UWL_MAC_FCTL_GET_ACK_REQUEST(
						UWL_MAC_MPDU_FRAME_CONTROL(frame->mpdu));
				if (!csma_check_available_cap(frame->mpdu_size, tmp)) {
					csma_set_delay();
					csma_params.state = CSMA_STATE_DELAY;
					//uwl_debug_print("D->D");
					return;
				}
			} else if (uwl_mac_data_req.data_req == 0) {
				// FIXME: return error!!!
				return;
			}
			// FIXME: no csma_check_available_cap is done for
			// requested data
			csma_params.state = CSMA_STATE_CCA;
		}
	}
	if (csma_params.state == CSMA_STATE_CCA) {
		if (!uwl_radio_get_cca()) {
			csma_params.CW = 2;
			if (csma_params.NB > uwl_mac_pib.macMaxCSMABackoffs) {
				/* TODO: CSMA Failure status!!
				Notify with confirm primitive!!!!
				 */
				frame = (struct uwl_mac_frame_t *)
								 cqueue_pop(&uwl_mac_queue_cap);
				uwl_MCPS_DATA_confirm(frame->msdu_handle,
						UWL_MAC_CHANNEL_ACCESS_FAILURE, 0);
				csma_params.state = CSMA_STATE_INIT;
				//uwl_debug_print("C->I fail");
				return;
			}
			csma_params.NB++;
			if (csma_params.BE < uwl_mac_pib.macMaxBE)
				csma_params.BE++;
			csma_set_delay();
			csma_params.state = CSMA_STATE_DELAY;
			//uwl_debug_print("C->D");
			return;
		}
		if (--csma_params.CW > 0)
			return;

		if (uwl_mac_data_req.data_req == 1) {
			
			/* we need to find the requested frame, so we check if
			 * the destination addresses are the same of the
			 * requester */
			frame = (struct uwl_mac_frame_t*)list_iter_front(&uwl_mac_list_ind);
			memcpy(&dst_pan_addr, &frame->mpdu[3], 2);
			memcpy(&dst_addr1, &frame->mpdu[5], 4);
			memcpy(&dst_addr2, &frame->mpdu[9], 4);
			pointer = 0;
			while(dst_addr1 != uwl_mac_data_req.addr_dev[0] &&
					dst_addr2 != uwl_mac_data_req.addr_dev[1] &&
					dst_pan_addr != uwl_mac_data_req.addr_pan) {
				frame = (struct uwl_mac_frame_t*)
						list_iter_next(&uwl_mac_list_ind);
				pointer++;
				memcpy(&dst_pan_addr, &frame->mpdu[3], 2);
				memcpy(&dst_addr1, &frame->mpdu[5], 4);
				memcpy(&dst_addr2, &frame->mpdu[9], 4);
			}
			/* we already have the frame in the variable frame, so
			 * we delete it from the list */
			list_extract(&uwl_mac_list_ind, pointer);
			uwl_mac_data_req.data_req = 0;

		} else
				frame = (struct uwl_mac_frame_t*)cqueue_pop(&uwl_mac_queue_cap);

		/* Something must be there, check again? */
		/* if (!frame) ERRORE!!!!!*/
		#ifdef __JUST_MEASURE_FOR_PAPER__
		daq_time_get(1, &downlink); // FIXME: this must be done ONLY  IN COORDINATOR
		#endif

		if(frame != 0){
			tmp = uwl_radio_phy_send_now(frame->mpdu, frame->mpdu_size);
			if (tmp == UWL_RADIO_ERR_NONE)
				uwl_MCPS_DATA_confirm(frame->msdu_handle,
							  UWL_MAC_SUCCESS, 0);
			else
			/* TODO: we have to choose a well formed reply
				 for the indication primitive (status=??) */
				uwl_MCPS_DATA_confirm(frame->msdu_handle,
							  UWL_MAC_CHANNEL_ACCESS_FAILURE,0);
		}

		csma_params.state = CSMA_STATE_INIT;
		//uwl_debug_print("C->I succ");
	}
}

static void cfp_perform_coordinator(void)
{
	struct uwl_gts_info_t *gts;
//	char str[100];

	if (uwl_mac_status.sf_context != UWL_MAC_SF_CFP)
		return;
	gts = uwl_gts_schedule + sf_flags.gts_schedule_idx;
//	sprintf(str, "COORD: GTS=%u s=%u l=%u d=%u a=0x%X",
//		sf_flags.gts_schedule_idx, gts->starting_tslot,
//		gts->length, gts->direction, gts->dev_address);
//	uwl_debug_print(str);
	if (current_tslot != sf_flags.cfp_start_tslot &&
	    current_tslot != gts->starting_tslot + gts->length)
		return; /* NO need to update coordinator GTS behaviour */
	if (current_tslot != sf_flags.cfp_start_tslot) {
		uwl_kal_mutex_wait(MAC_GTS_SEND_MUTEX);
		/* Next GTS starts here (start of first is skipped) */
		if (sf_flags.gts_sending) {
			/* Stop previous GTS */
			sf_flags.gts_sending = 0;
			/* TODO: has effect? */
			uwl_kal_cancel_activation(MAC_GTS_SEND);
		}
		uwl_kal_mutex_wait(MAC_MUTEX);
		recharge_gts_bytes(gts->length, sf_flags.gts_schedule_idx);
		uwl_kal_mutex_signal(MAC_MUTEX);
		uwl_gts_queue_flush(sf_flags.gts_schedule_idx);
		sf_flags.gts_schedule_idx++;
		gts++;
		uwl_kal_mutex_signal(MAC_GTS_SEND_MUTEX);
		//uwl_debug_print("COORDINATOR: GTS ContextSwitch");
	}
	/* NOTE: output for device, means input for coordinator */
	if (gts->direction == UWL_MAC_GTS_DIRECTION_OUT) {
		sf_flags.in_tx_gts = UWL_FALSE;
		uwl_radio_phy_set_rx_on(); /*TODO:Raise error if < 0 */
		//uwl_debug_print("COORDINATOR: GTS RX");
		return;
	}
	//uwl_debug_print("COORDINATOR: GTS TX");
	sf_flags.in_tx_gts = UWL_TRUE;
	sf_flags.gts_sending = 1;
	time_reference = (uwl_mac_gts_stat.tx_length *
		         UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder)) +
		         uwl_kal_get_time();
	uwl_kal_set_activation(MAC_GTS_SEND, UWL_MAC_LIFS_PERIOD, 0);
	if (gts->starting_tslot + gts->length == UWL_MAC_SUPERFRAME_LAST_SLOT)
		sf_flags.gts_tx_on_cfp_end = UWL_TRUE;
}

static void cfp_perform_device(void)
{
	if (uwl_mac_gts_stat.tx_length != 0 &&
            current_tslot == uwl_mac_gts_stat.tx_start_tslot) {
		/* Start Device TX GTS */
		sf_flags.in_tx_gts = UWL_TRUE;
		sf_flags.gts_sending = 1;
		time_reference = (uwl_mac_gts_stat.tx_length *
			       UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder)) +
			       uwl_kal_get_time();
		uwl_kal_set_activation(MAC_GTS_SEND, UWL_MAC_LIFS_PERIOD, 0);
		if (uwl_mac_gts_stat.tx_start_tslot +
		    uwl_mac_gts_stat.tx_length == UWL_MAC_SUPERFRAME_LAST_SLOT)
			sf_flags.gts_tx_on_cfp_end = UWL_TRUE;
	} else if (uwl_mac_gts_stat.tx_length != 0 &&
		   current_tslot >= uwl_mac_gts_stat.tx_start_tslot +
		   uwl_mac_gts_stat.tx_length) {
		/* Stop Devie TX GTS */
		sf_flags.in_tx_gts = UWL_FALSE;
		sf_flags.gts_sending = 0;
		uwl_kal_mutex_wait(MAC_MUTEX);
		recharge_gts_bytes(uwl_mac_gts_stat.tx_length, 0);
		uwl_kal_mutex_signal(MAC_MUTEX);
		uwl_gts_queue_flush(0);
		uwl_kal_cancel_activation(MAC_GTS_SEND);/* TODO: has effect? */
	}
}

/******************************************************************************/
/*                      MAC Layer TASKs and Activities                        */
/******************************************************************************/
COMPILER_INLINE void start_beacon_interval(void)
{
	uint8_t i;
	/*
	char s[100];
	uint32_t mmm = uwl_debug_time_get_us(UWL_DEBUG_TIME_CLOCK_DEVEL);
	*/

	uwl_debug_time_get(UWL_DEBUG_TIME_CLOCK_BI);
	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator){
		uwl_kal_mutex_wait(MAC_GTS_SEND_MUTEX);
		sf_flags.gts_schedule_idx = 0;
		uwl_kal_mutex_signal(MAC_GTS_SEND_MUTEX);
		uwl_radio_mac_send_beacon(); /* TODO: parse ret value*/
	} else if (uwl_mac_status.count_beacon_lost++ > UWL_aMaxLostBeacons) {
		//uwl_debug_print("MAC beacon-enabled STOPPING!");
		sf_flags.gts_sending = 0;
		uwl_kal_mutex_wait(MAC_MUTEX);
		//gts_available_bytes = 0;
		memset(gts_available_bytes, 0,
		       sizeof(uint32_t) * UWL_MAC_GTS_MAX_NUMBER);
		uwl_kal_mutex_signal(MAC_MUTEX);
		uwl_gts_queue_flush(0); /* NOTE: this is the device case! */
		stop_activations();
		return;
	}
	sf_flags.in_tx_gts = UWL_FALSE;
	if (sf_flags.had_cfp == UWL_TRUE && !uwl_mac_status.has_rx_beacon) {
		sf_flags.had_cfp = UWL_FALSE;
		uwl_kal_set_activation(MAC_BACKOFF_PERIOD, 0, 1);
	} else {
		uwl_kal_mutex_wait(MAC_MUTEX);
		if (uwl_mac_status.is_pan_coordinator ||
		    uwl_mac_status.is_coordinator)
			for (i = 0; i < UWL_MAC_GTS_MAX_NUMBER; i++)
			       recharge_gts_bytes(uwl_gts_schedule[i].length,i);
		else
			recharge_gts_bytes(uwl_mac_gts_stat.tx_length, 0);
		uwl_kal_mutex_signal(MAC_MUTEX);
	}
	if (uwl_mac_pib.macSuperframeOrder < uwl_mac_pib.macBeaconOrder) {
		sf_flags.has_idle = UWL_TRUE;
		sf_flags.wait_sf_end = UWL_TRUE;
	}
	cap_available_bytes =
			bticks_to_bytes((uint32_t) uwl_mac_gts_get_cap_size()) *
			       UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder);
	uwl_mac_status.sf_context = UWL_MAC_SF_CAP;
	/*
	sprintf(s, "DEVICE: Start BI - %lu: B0=%u S0=%u TX=%u LTX=%u ",
		mmm,uwl_mac_pib.macBeaconOrder, uwl_mac_pib.macSuperframeOrder,
		uwl_mac_gts_stat.tx_start_tslot, uwl_mac_gts_stat.tx_length);
	uwl_debug_print(s);
	*/
	//uwl_debug_print("SF: start BI");
	#ifdef UWL_SUPERFRAME_CALLBACKS
	if (on_beacon_callback)
		on_beacon_callback();
	#endif
	uwl_mac_status.has_rx_beacon = 0; /* MUST be at the END of Function */
}

COMPILER_INLINE void stop_superframe(void)
{
	uint32_t t;

	uwl_mac_status.sf_context = UWL_MAC_SF_IDLE;
	sf_flags.wait_sf_end = UWL_FALSE;
	t = UWL_MAC_GET_BI(uwl_mac_pib.macBeaconOrder) -
	    UWL_MAC_GET_SD(uwl_mac_pib.macSuperframeOrder);
	restart_activations(t);
	current_tslot = UWL_MAC_SUPERFRAME_LAST_SLOT;
	sf_flags.in_tx_gts = UWL_FALSE;
	sf_flags.wait_sf_end = UWL_FALSE;
	sf_flags.has_idle = UWL_FALSE;
	//uwl_debug_print("SF: End Of SF");
}

COMPILER_INLINE void before_beacon_interval(void)
{
	#ifdef UWL_DEBUG
	//uint8_t str[UWL_DEBUG_STAT_STRLEN];
	#endif

	#ifdef UWL_SUPERFRAME_CALLBACKS
	if (before_beacon_callback)
		before_beacon_callback();
	#endif
	sf_flags.cfp_start_tslot = uwl_mac_gts_stat.first_cfp_tslot;
	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator)
		uwl_radio_mac_create_beacon(); /* TODO: parse error! */
	#ifdef UWL_DEBUG
	//uwl_debug_stat2str(str);
	//uwl_debug_write(str, UWL_DEBUG_STAT_STRLEN);
	#endif
	//uwl_debug_print("SF: before Start BI");
}

static void on_timeslot_start(void)
{
	uint32_t t, tmin;
	/*
	char s[100];
	uint32_t mmm = uwl_debug_time_get_us(UWL_DEBUG_TIME_CLOCK_DEVEL);
	*/
	/* TODO: Implement an efficient version:
		 In case of a device that is not coordinator we can do:
			- if in CAP do whatever
			- if in CFP, since I already know when to Tx/Rx I can
			  suspend until that time (manage this!)
	*/
	current_tslot = NEXT_TSLOT(current_tslot);
	if (current_tslot == UWL_MAC_SUPERFRAME_FIRST_SLOT) {
		if (sf_flags.has_idle) { 	/* Has to go in IDLE? */
			stop_superframe();
			return;
		}
		/* Check if the first slot has been activated twice */
		if (sf_flags.first_tslot_twice) {
			start_beacon_interval();
			return;
		}
		sf_flags.first_tslot_twice = UWL_TRUE;
		stop_previous_cfp();
		time_reference = uwl_kal_get_time();
		start_beacon_interval();
	} else if (current_tslot == UWL_MAC_SUPERFRAME_FIRST_SLOT + 1) {
		sf_flags.first_tslot_twice = UWL_FALSE;
		/* Check if the second slot is too close to the first one */
		t = uwl_kal_get_time();
		t = TIME32_SUBTRACT(t, time_reference);
		tmin = UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder);
		tmin -= UWL_MAC_GET_TS(uwl_mac_pib.macSuperframeOrder) >> 2;
		if (t < tmin) { /* t=<TS_1-TS_0>,  tmin=3/4<TS_size> */
			current_tslot = UWL_MAC_SUPERFRAME_FIRST_SLOT;
			return;
		}
	}
	/*
	sprintf(s, "DEVICE: CFP=%u slot=%u  Dck=%lu  ck=%lu ref_ck=%lu  t=%lu",
		sf_flags.cfp_start_tslot,
		current_tslot, mmm-test_time, mmm, time_reference, t);
	uwl_debug_print(s);
	*/
	/* GTS Management part */
	if (uwl_mac_pib.macGTSPermit == 0)
		return;
	if (current_tslot == sf_flags.cfp_start_tslot) {
		uwl_mac_status.sf_context = UWL_MAC_SF_CFP;
		sf_flags.had_cfp = UWL_TRUE;
		sf_flags.gts_tx_on_cfp_end = UWL_FALSE;
		uwl_kal_cancel_activation(MAC_BACKOFF_PERIOD);
	}
	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator)
		cfp_perform_coordinator();
	else
		cfp_perform_device();
}

static void before_timeslot_start(void)
{
	/*
	char s[100];
	uint32_t mmm = uwl_debug_time_get_us(UWL_DEBUG_TIME_CLOCK_DEVEL);
	*/
	if (NEXT_TSLOT(current_tslot) == UWL_MAC_SUPERFRAME_FIRST_SLOT) {
		/* Is before the BI? */
		if (sf_flags.wait_sf_end == UWL_FALSE)
			before_beacon_interval();
			/* TODO: if something must be done before first slot,
				 that is the place!! */
		return;
	}
	/*
	sprintf(s, "DEVICE: before slot = %u, Dck%lu, ck=%lu",
		NEXT_TSLOT(current_tslot), mmm-test_time, mmm);
	uwl_debug_print(s);
	test_time = mmm;
	*/
}

#ifndef UWL_NO_DYN_ASS
static void perform_associate_request_ack_check(void){

	static uint8_t associate_req_attempts = 1;

/* FIXME: Work-around usato per aumentare l'attesa dell'arrivo dell'ack in
 * associazione. Un ack al momento impiega circa 1.1 ms, il limite max è
 * di circa 860 us per cui sfora. Due possibilità:
 * - ack più veloce spostandolo a livello fisico
 * - farlo in hardware.
 */

	if(associate_ack_counter > 0){
		associate_ack_counter+= 1; //20 valore corretto

		if(associate_ack_counter >= uwl_mac_pib.macAckWaitDuration &&
				associate_req_attempts < uwl_mac_pib.macMaxFrameRetries){

/* The retransmitted frame not contain the same DSN!!!
 *
 * Standard 802.15.4 - 7.5.6.4.2
 * "The retransmitted frame shall contain the same DSN as was used in
 * the original transmission..."
 */
			uwl_mac_association_request_cmd(UWL_MAC_ADDRESS_SHORT,
					uwl_mac_pib.macPANId,
					(void *)&uwl_mac_pib.macCoordShortAddress,
					uwl_mac_associate_retry.capability);

			associate_ack_counter = 1;
			associate_req_attempts++;
		}
	}
}
#endif

static void on_backoff_period_start(void)
{
#ifndef UWL_NO_DYN_ASS
	perform_associate_request_ack_check();
#endif

		csma_perform_slotted();
}

static void on_gts_send(void)
{
	struct uwl_mac_frame_t *frame;
	/*
	uint32_t t;
	char s[100];
	*/
	if (!sf_flags.gts_sending) {
		/*
		sprintf(s,"DEVICE: On GTS SEND -- STOP -- @ %d",current_tslot);
		uwl_debug_print(s);
		*/
		return;
	}
	uwl_kal_mutex_wait(MAC_GTS_SEND_MUTEX);
	/*
	uint32_t mmm = uwl_debug_time_get_us(UWL_DEBUG_TIME_CLOCK_DEVEL);
	sprintf(s, "DEVICE: On GTS SEND  @ %u idx=%u, %lu",
		current_tslot, sf_flags.gts_schedule_idx, mmm);
	uwl_debug_print(s);
	*/
	//uwl_debug_print("On GTS SEND |");
	if (uwl_gts_queue_is_empty(sf_flags.gts_schedule_idx)) {
		sf_flags.gts_sending = 0; /* Nothing more to send by now. */
		uwl_kal_mutex_signal(MAC_GTS_SEND_MUTEX);
		//uwl_debug_print("            |-> EMPTY Q");
		return;
	}
	frame = uwl_gts_queue_extract(sf_flags.gts_schedule_idx);
	if (frame == 0) { /* TODO: this is extra check, empty check is enough!*/
		uwl_kal_mutex_signal(MAC_GTS_SEND_MUTEX);
		//uwl_debug_print("            |-> Really BAD!");
		return;
	}
	if (!sf_flags.in_tx_gts) { /* Check if GTS is no longer valid */
		/* TODO: we have to choose a well formed reply
			 for the indication primitive (status=??) */
		uwl_kal_mutex_signal(MAC_GTS_SEND_MUTEX);
		uwl_MCPS_DATA_confirm(frame->msdu_handle,UWL_MAC_INVALID_GTS,0);
		//uwl_debug_print("            |-> No More GTS");
		return;
	}
//LATEbits.LATE0 = 1;
	if (uwl_radio_phy_send_now(frame->mpdu, frame->mpdu_size) ==
	    						UWL_RADIO_ERR_NONE)
		uwl_MCPS_DATA_confirm(frame->msdu_handle, UWL_MAC_SUCCESS, 0);
	else
		/* TODO: we have to choose a well formed reply
			 for the indication primitive (status=??) */
		uwl_MCPS_DATA_confirm(frame->msdu_handle,UWL_MAC_INVALID_GTS,0);
	if (frame->mpdu_size > UWL_aMaxSIFSFrameSize) /* TODO: check!!!! */
		uwl_kal_set_activation(MAC_GTS_SEND, UWL_MAC_LIFS_PERIOD, 0);
	else
		uwl_kal_set_activation(MAC_GTS_SEND, UWL_MAC_SIFS_PERIOD, 0);
	//uwl_debug_print("            |-> SENT");
//LATEbits.LATE0 = 0;
	uwl_kal_mutex_signal(MAC_GTS_SEND_MUTEX);
}

/******************************************************************************/
/*                      MAC Superframe General Functions                      */
/******************************************************************************/
int8_t uwl_mac_superframe_init(void)
{
	int8_t retv = 1;

	if (uwl_mac_status.sf_initialized)
		return 1;
	retv = uwl_kal_init(320); /* TODO: this comes from the PHY, because
	it's just the duration of the aUnitBackoffPeriod = 20 symbols so...
	backoff_period = aUnitBackoffPeriod x bit_per_symbols / bandwidth
		       = 20 x 4bits / 250000 bps = 320 microseconds .
	How can we make this general? Where can this change? When? */
	if (retv < 0)
		return retv;
	retv = uwl_kal_set_body(MAC_TIMESLOT, on_timeslot_start);
	if (retv < 0)
		return retv;
	retv = uwl_kal_set_body(MAC_BEFORE_TIMESLOT, before_timeslot_start);
	if (retv < 0)
		return retv;
	retv = uwl_kal_set_body(MAC_BACKOFF_PERIOD, on_backoff_period_start);
	if (retv < 0)
		return retv;
	retv = uwl_kal_set_body(MAC_GTS_SEND, on_gts_send);
	if (retv < 0)
		return retv;
	uwl_mac_status.sf_initialized = UWL_TRUE;
	csma_params.state = CSMA_STATE_INIT;
	csma_params.slotted = 1;
	lifs_bytes = bticks_to_bytes(UWL_MAC_LIFS_PERIOD);
	sifs_bytes = bticks_to_bytes(UWL_MAC_SIFS_PERIOD);
	btick_bytes = bticks_to_bytes(1);
//TRISEbits.TRISE0 = 0;
//LATEbits.LATE0 = 0;
	return 1;
}

void uwl_mac_superframe_start(uint32_t offset)
{
	/* TODO: check this behaviour*/
	if (uwl_mac_status.track_beacon) {
		uwl_radio_phy_set_rx_on(); /* TODO: Raise error if < 0 */
		uwl_debug_time_start(UWL_DEBUG_TIME_CLOCK_BI);
		return;
	}
	uwl_debug_time_start(UWL_DEBUG_TIME_CLOCK_DEVEL);
	uwl_debug_time_start(UWL_DEBUG_TIME_CLOCK_BI);
	current_tslot = UWL_MAC_SUPERFRAME_LAST_SLOT;
	sf_flags.wait_sf_end = UWL_FALSE;
	sf_flags.has_idle = UWL_FALSE;
	sf_flags.had_cfp = UWL_FALSE;
	sf_flags.first_tslot_twice = UWL_FALSE;
	sf_flags.gts_tx_on_cfp_end = UWL_FALSE;
	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator)
		start_activations(offset);
}

void uwl_mac_superframe_stop(void)
{
	stop_activations();
}

void uwl_mac_superframe_resync(void)
{
	/*
	char s[100];
	uint32_t mmm = uwl_debug_time_get_us(UWL_DEBUG_TIME_CLOCK_DEVEL);
	*/
	uwl_mac_status.count_beacon_lost = 0;
	uwl_mac_status.has_rx_beacon = 1;
	if (!uwl_mac_status.track_beacon)
		return;
	resync_activations();
	/*
	sprintf(s, "BCN -> SF Resync: Dck=%lu, ck=%lu, %u, %u",
		mmm - test_time, mmm,
		(uint16_t) uwl_mac_pib.macBeaconOrder,
		(uint16_t) uwl_mac_pib.macSuperframeOrder);
	uwl_debug_print(s);
	test_time = mmm;
	*/
}

void uwl_mac_superframe_gts_wakeup(uint8_t gts_idx)
{
	struct uwl_gts_info_t *gts;

	uwl_debug_print("GTS WAKEUP? |");
	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator){
		/* Coordinator wakeup gts */
		gts = uwl_gts_schedule + gts_idx;
		if (gts_idx == sf_flags.gts_schedule_idx &&
		    current_tslot == gts->starting_tslot &&
		    gts->direction == UWL_MAC_GTS_DIRECTION_IN &&
		    !sf_flags.gts_sending && gts->length != 0) {
			//uwl_debug_print("            |-> Coord!");
			sf_flags.gts_sending = 1;
			uwl_kal_set_activation(MAC_GTS_SEND, 0, 0);
		}
	} else {
	 	/* Device wakeup gts */
	 	if (!sf_flags.gts_sending && uwl_mac_gts_stat.tx_length != 0 &&
	 	    current_tslot == uwl_mac_gts_stat.tx_start_tslot) {
	 		sf_flags.gts_sending = 1;
	 		uwl_kal_set_activation(MAC_GTS_SEND, 0, 0);
			//uwl_debug_print("            |-> Device!");
	 	}
	}
}

uint8_t uwl_mac_superframe_check_gts(uint8_t length, uint8_t gts_idx)
{
	uint32_t x;
	uint32_t *bytes = gts_available_bytes;
//char str[100];

	if (uwl_mac_status.is_pan_coordinator || uwl_mac_status.is_coordinator){
		/* GTS presence must be already checked, gts_idx range too. */
		bytes += gts_idx;
	} else {
		if (uwl_mac_gts_stat.tx_length == 0)
			return 0;
	}
	//sprintf(str, "CHECK: currGTS=%u GTS%u l=%u",
	//	sf_flags.gts_schedule_idx, gts_idx, length);
	//uwl_debug_print(str);
	//sprintf(str, "CHECK: Avail %lu %lu %lu %lu %lu %lu %lu",
	//	gts_available_bytes[0], gts_available_bytes[1],
	//	gts_available_bytes[2], gts_available_bytes[3],
	//	gts_available_bytes[4], gts_available_bytes[5],
	//	gts_available_bytes[6]);
	//uwl_debug_print(str);

	/* TODO: use the extra bytes for protection??? in this case 10 */
	uwl_kal_mutex_wait(MAC_MUTEX);
	uwl_debug_print("CHECK GTS |");
//sprintf(str,"DEVICE: -->>> R=%lu l=%u", *bytes, length);
//uwl_debug_print(str);
	if (*bytes < length + 10) {
		uwl_kal_mutex_signal(MAC_MUTEX);
		//uwl_debug_print("          |-> 0 (apriori)");
		return 0;
	}
	x = *bytes;
	if (sf_flags.in_tx_gts) {
		/* x = remaining btick in GTS */
		x = uwl_kal_get_time();
		x = TIME32_SUBTRACT(time_reference, x);
		/* x = remaining bytes in GTS */
		x = bticks_to_bytes(x);
/* sprintf(s,"DEVICE: ####--->>> Remaining Byte =  %lu", x);
uwl_debug_print(s); */
		if (x < length + 10) {
			*bytes = 0;
			uwl_kal_mutex_signal(MAC_MUTEX);
			//uwl_debug_print("          |-> 0 (on remaining)");
			return 0;
		}
	}
	*bytes = x - (length + 10);
	/* x = LISF or SIFS in bytes */
	x = length < UWL_aMaxSIFSFrameSize ?  sifs_bytes : lifs_bytes;
	*bytes = (*bytes) >= x ?  (*bytes) - x : 0;
	uwl_kal_mutex_signal(MAC_MUTEX);
	//uwl_debug_print("          |-> 1 (ok)");
	return 1;
}

int8_t uwl_mac_set_before_beacon_callback(void (* func)(void))
{
	#ifdef UWL_SUPERFRAME_CALLBACKS
	before_beacon_callback = func;
	return UWL_MAC_ERR_NONE;
	#else
	return -UWL_MAC_ERR_SUPERFRAME_CALLBACKS_DISABLED;
	#endif
}

int8_t uwl_mac_set_on_beacon_callback(void (* func)(void))
{
	#ifdef UWL_SUPERFRAME_CALLBACKS
	on_beacon_callback = func;
	return UWL_MAC_ERR_NONE;
	#else
	return -UWL_MAC_ERR_SUPERFRAME_CALLBACKS_DISABLED;
	#endif
}
