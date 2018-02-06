/**
 * @file
 *
 * @brief This file implements the dispatchers for events and timers.
 *
 * $Id: dispatcher.c,v 1.1 2007/06/22 13:50:48 romano Exp $
 *
 */
/**
 *  \author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2006, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* === Includes ============================================================ */
#ifndef DEF_H
#include "def.h"
#endif

#include <string.h>
#include "board.h"
#include "cmdif.h"
#include "phy.h"
#include "mac.h"
#if APP_TYPE > APP_L2
    #include "nwk.h"
#endif
#include "timer_const.h"

#if APP_TYPE == APP_L0
# include "validation.h"
#endif

#if (APP_TYPE == APP_SNIFFER) || (APP_TYPE == APP_SCRPT_SNF)
#include "user_interface.h"
#endif

#if APP_TYPE == APP_L2
#include "wpan_mac.h"
#endif

#if (APP_TYPE == APP_L1) || (APP_TYPE == APP_SNIFFER) || (APP_TYPE == APP_SCRPT_SNF)
#include "wpan_phy.h"
#endif

#if APP_TYPE == APP_L0
#include "wpan_hal.h"
#endif

/* === Defines ============================================================= */
/*
 * Some application types do not use timer callbacks at all.
 */
#if APP_TYPE != LIB_HAL && ((APP_TYPE == APP_L0) || (APP_TYPE >= APP_L2))
#  define TIMERS_USED 1
#else
#  define TIMERS_USED 0
#endif

/* === Typedefs ============================================================ */
typedef void (*handler_t)(uint8_t *);

/* === Prototypes ========================================================== */
#if APP_TYPE >= APP_L1
static void bios_dispatch_timer(uint8_t *msg);
#endif
void mcps_data_confirm(uint8_t *m);

/* === Globals ============================================================= */

FLASH_DECLARE(static handler_t dispatch_table[LAST_MESSAGE + 1]) =
{
#if APP_TYPE == APP_L0
    /* validation specific commands*/
    [CMDIF_VALIDATION_REQUEST]   = cmdif_validation_request,
#endif /* APP_TYPE == APP_L0 */
#if APP_TYPE >= APP_L0 && APP_TYPE != APP_SNIFFER && APP_TYPE != APP_SCRPT_SNF
    /* general bios functions */
    [CMDIF_SET_ROUTE_REQUEST]    = cmdif_set_route_request,
    [CMDIF_GET_ROUTE_REQUEST]    = cmdif_get_route_request,
    [CMDIF_ECHO_REQUEST]         = cmdif_echo_request,
    [CMDIF_VERSION_REQUEST]      = cmdif_version_request,
    [CMDIF_TIMERSTART_REQUEST]   = cmdif_timerstart_request,
    [CMDIF_TIMERSTOP_REQUEST]    = cmdif_timerstop_request,
    /* Low Level HW Access to PHY */
    [CMDIF_REGWR_REQUEST]        = cmdif_regwr_request,
    [CMDIF_REGRD_REQUEST]        = cmdif_regrd_request,
    [CMDIF_BITRD_REQUEST]        = cmdif_bitrd_request,
    [CMDIF_BITWR_REQUEST]        = cmdif_bitwr_request,
    [CMDIF_PINSET_REQUEST]       = cmdif_pinset_request,
    [CMDIF_PINGET_REQUEST]       = cmdif_pinget_request,
    [CMDIF_SRAMUP_REQUEST]       = cmdif_sramup_request,
    [CMDIF_SRAMDN_REQUEST]       = cmdif_sramdn_request,
    [CMDIF_FRAMEUP_REQUEST]      = cmdif_frameup_request,
    [CMDIF_FRAMEDN_REQUEST]      = cmdif_framedn_request,
    [CMDIF_BOOTLOAD_REQUEST]     = cmdif_bootload_request,
#endif /* APP_TYPE >= APP_L0 */
    /* Internal message */
#if APP_TYPE >= APP_L1
    [TIMER_EXPIRED_INDICATION]   = bios_dispatch_timer,
#endif

#if APP_TYPE >= APP_L1
    /* PHY layer messages */
    [PD_DATA_REQUEST]            = pd_data_request,
    [PLME_CCA_REQUEST]           = plme_cca_request,
    [PLME_ED_REQUEST]            = plme_ed_request,
    [PLME_GET_REQUEST]           = plme_get_request,
    [PLME_SET_TRX_STATE_REQUEST] = plme_set_trx_state_request,
    [PLME_SET_REQUEST]           = plme_set_request,
#endif /* APP_TYPE >= APP_L1 */

#if APP_TYPE >= APP_L2
    [MLME_RESET_REQUEST]         = mlme_reset_request,
    [MLME_GET_REQUEST]           = mlme_get_request,
    [MLME_SET_REQUEST]           = mlme_set_request,
    [MLME_SCAN_REQUEST]          = mlme_scan_request,
#  if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    [MLME_START_REQUEST]         = mlme_start_request,
#  endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
    [MLME_ASSOCIATE_REQUEST]     = mlme_associate_request,
#  if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    [MLME_ASSOCIATE_RESPONSE]    = mlme_associate_response,
#  endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
    [MCPS_DATA_REQUEST]          = mcps_data_request,
    [MLME_DISASSOCIATE_REQUEST]  = mlme_disassociate_request,
#  if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    [MLME_ORPHAN_RESPONSE]       = mlme_orphan_response,
#  endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
    [MLME_POLL_REQUEST]          = mlme_poll_request,
    [MLME_RX_ENABLE_REQUEST]     = mlme_rx_enable_request,
    [MLME_SYNC_REQUEST]          = mlme_sync_request,
#  if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    [MCPS_PURGE_REQUEST]         = mcps_purge_request,
#  endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */

    /* MAC callbacks for PHY confirm and indication messages */
    [PLME_SET_TRX_STATE_CONFIRM] = mac_proc_plme_set_trx_state_confirm,
    [PLME_SET_CONFIRM]           = mac_proc_plme_set_confirm,
    [PD_DATA_CONFIRM]            = mac_proc_pd_data_confirm,
    [PD_DATA_INDICATION]         = mac_proc_pd_data_ind,
    [PLME_CCA_CONFIRM]           = mac_csma_ca_cca_done,
#  if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    [PLME_ED_CONFIRM]            = mac_proc_plme_ed_confirm,
#  endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
#endif /* APP_TYPE >= APP_L2 */
#if APP_TYPE >= APP_L3
    [NLDE_DATA_REQUEST]                   = nlde_data_request,

    [NLME_NETWORK_DISCOVERY_REQUEST]      = nlme_network_discovery_request,
    [NLME_NETWORK_FORMATION_REQUEST]      = nlme_network_formation_request,
    [NLME_PERMIT_JOINING_REQUEST]         = nlme_permit_joining_request,
    [NLME_START_ROUTER_REQUEST]           = nlme_start_router_request,
    [NLME_JOIN_REQUEST]                   = nlme_join_request,
    [NLME_DIRECT_JOIN_REQUEST]            = nlme_direct_join_request,
    [NLME_LEAVE_REQUEST]                  = nlme_leave_request,
    [NLME_RESET_REQUEST]                  = nlme_reset_request,
    [NLME_SYNC_REQUEST]                   = nlme_sync_request,
    [NLME_GET_REQUEST]                    = nlme_get_request,
    [NLME_SET_REQUEST]                    = nlme_set_request,

    /* NWK callbacks for MAC confirm and indication messages */
    [MCPS_DATA_CONFIRM]                   = nwk_proc_mcps_data_confirm,
    [MCPS_DATA_INDICATION]                = nwk_proc_mcps_data_indication,
    [MCPS_PURGE_CONFIRM]                  = nwk_proc_mcps_purge_confirm,

    [MLME_ASSOCIATE_INDICATION]           = nwk_proc_mlme_associate_indication,
    [MLME_ASSOCIATE_CONFIRM]              = nwk_proc_mlme_associate_confirm,
    [MLME_DISASSOCIATE_INDICATION]        = nwk_proc_mlme_disassociate_indication,
    [MLME_DISASSOCIATE_CONFIRM]           = nwk_proc_mlme_disassociate_confirm,
    [MLME_BEACON_NOTIFY_INDICATION]       = nwk_proc_mlme_beacon_notify_indication,
    [MLME_ORPHAN_INDICATION]              = nwk_proc_mlme_orphan_ind,
    [MLME_SCAN_CONFIRM]                   = nwk_proc_mlme_scan_confirm,
    [MLME_COMM_STATUS_INDICATION]         = nwk_proc_mlme_comm_status_ind,
    [MLME_SYNC_LOSS_INDICATION]           = nwk_proc_mlme_sync_loss_ind,
    [MLME_GET_CONFIRM]                    = nwk_proc_mlme_get_confirm,
    [MLME_SET_CONFIRM]                    = nwk_proc_mlme_set_confirm,
    [MLME_RESET_CONFIRM]                  = nwk_proc_mlme_reset_confirm,
    [MLME_RX_ENABLE_CONFIRM]              = nwk_proc_mlme_rx_enable_confirm,
    [MLME_START_CONFIRM]                  = nwk_proc_mlme_start_confirm,
    [MLME_POLL_CONFIRM]                   = nwk_proc_mlme_poll_confirm,
#endif /*APP_TYPE >= APP_L3  */

#if APP_TYPE >= APP_L3
    /* user callbacks for NWK confirm and indication messages */
    [NLDE_DATA_CONFIRM]                   = nlde_data_conf,
    [NLDE_DATA_INDICATION]                = nlde_data_ind,
    [NLME_NETWORK_DISCOVERY_CONFIRM]      = nlme_network_discovery_conf,
    [NLME_NETWORK_FORMATION_CONFIRM]      = nlme_network_formation_conf,
    [NLME_PERMIT_JOINING_CONFIRM]         = nlme_permit_joining_conf,
    [NLME_START_ROUTER_CONFIRM]           = nlme_start_router_conf,
    [NLME_JOIN_INDICATION]                = nlme_join_ind,
    [NLME_JOIN_CONFIRM]                   = nlme_join_conf,
    [NLME_DIRECT_JOIN_CONFIRM]            = nlme_direct_join_conf,
    [NLME_LEAVE_INDICATION]               = nlme_leave_ind,
    [NLME_LEAVE_CONFIRM]                  = nlme_leave_conf,
    [NLME_RESET_CONFIRM]                  = nlme_reset_conf,
    [NLME_SYNC_CONFIRM]                   = nlme_sync_conf,
    [NLME_GET_CONFIRM]                    = nlme_get_conf,
    [NLME_SET_CONFIRM]                    = nlme_set_conf,
#elif APP_TYPE >= APP_L2
    /* user callbacks for MAC confirm and indication messages */
    [MCPS_DATA_CONFIRM]                   = mcps_data_conf,
    [MCPS_DATA_INDICATION]                = mcps_data_ind,
    [MCPS_PURGE_CONFIRM]                  = mcps_purge_conf,

    [MLME_ASSOCIATE_INDICATION]           = mlme_associate_ind,
    [MLME_ASSOCIATE_CONFIRM]              = mlme_associate_conf,
    [MLME_DISASSOCIATE_INDICATION]        = mlme_disassociate_ind,
    [MLME_DISASSOCIATE_CONFIRM]           = mlme_disassociate_conf,
    [MLME_BEACON_NOTIFY_INDICATION]       = mlme_beacon_notify_ind,
    [MLME_ORPHAN_INDICATION]              = mlme_orphan_ind,
    [MLME_SCAN_CONFIRM]                   = mlme_scan_conf,
    [MLME_COMM_STATUS_INDICATION]         = mlme_comm_status_ind,
    [MLME_SYNC_LOSS_INDICATION]           = mlme_sync_loss_ind,
    [MLME_GET_CONFIRM]                    = mlme_get_conf,
    [MLME_SET_CONFIRM]                    = mlme_set_conf,
    [MLME_RESET_CONFIRM]                  = mlme_reset_conf,
    [MLME_RX_ENABLE_CONFIRM]              = mlme_rx_enable_conf,
    [MLME_START_CONFIRM]                  = mlme_start_conf,
    [MLME_POLL_CONFIRM]                   = mlme_poll_conf,
#elif APP_TYPE >= APP_L1
    /* user callbacks for PHY confirm and indication messages */
    [PLME_SET_TRX_STATE_CONFIRM] = plme_set_trx_state_conf,
    [PLME_SET_CONFIRM]           = plme_set_conf,
    [PLME_GET_CONFIRM]           = plme_get_conf,
    [PD_DATA_CONFIRM]            = pd_data_conf,
    [PD_DATA_INDICATION]         = pd_data_ind,
    [PLME_CCA_CONFIRM]           = plme_cca_conf,
#  if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    [PLME_ED_CONFIRM]            = plme_ed_conf,
#  endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
#endif /* APP_TYPE >= APP_L3/L2/L1 */
#if APP_TYPE == APP_SNIFFER || APP_TYPE == APP_SCRPT_SNF
    [SNIFFER_SET_CHANNEL_REQUEST] = sniffer_channel_select,
    [SNIFFER_START_REQUEST]      = sniffer_start,
    [SNIFFER_STOP_REQUEST]       = sniffer_stop,
    [SNIFFER_ACK_REQUEST]        = sniffer_ack_req,
    [SNIFFER_SET_FRMFILTER_REQUEST] = sniffer_set_frmfilter,
#endif /* APP_TYPE == APP_SNIFFER || APP_TYPE == APP_SCRPT_SNF */
};

#if TIMERS_USED
FLASH_DECLARE(static timer_callback_t timer_callback_table[T_LAST + 1])
/*
 * The initializer list below can become empty for certain
 * configurations, and IAR chokes on an empty list, so we need another
 * #if around it.
 */
= {
#if APP_TYPE == APP_L0
    [T_validation]           = val_t_process_timer,
#endif

#if APP_TYPE >= APP_L2
    /*
    [T_defertime]            = ...,
    */
    [T_bt_missedbeacon]      = mac_t_missed_beacons,
    [T_btp]                  = mac_t_tracking_beacons,
    [T_RxOnTime]             = mac_t_rx_enable_duration_start,
    [T_RxOffTime]            = mac_t_rx_enable_duration_expired,
    [T_ResponseWaitTime]     = mac_t_response_wait,
#  if DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS
    [T_superframe]           = mac_t_so_inactive,
    [T_beacon]               = mac_t_beacon,
#  endif /* DEVICE_TYPE == FD1 || DEVICE_TYPE == FD1_NOGTS */
    [T_scan_duration]        = mac_t_scan_duration,
    [T_backoff]              = mac_t_backoff,
    [T_AckWait]              = mac_t_ackwait,
    [T_MaxFrameResponseTime] = mac_t_maxframeresponsetime,
    [T_AssocResponseTime]    = mac_t_assocresponsetime,
#endif
#if APP_TYPE >= APP_L3
    [T_PERMIT_JOINING]       = nwk_t_permit_joining,
#endif
};
#endif /* TIMERS_USED */


/* === Implementation ====================================================== */

#if APP_TYPE >= APP_L1
/**
This function decodes all expired timer messages and calls the appropriate
handler.
@param msg The timer expired message.
*/
static void bios_dispatch_timer(uint8_t *msg)
{
    timer_expired_ind_t *event = (timer_expired_ind_t *)msg;
#if TIMERS_USED
    timer_callback_t callback;
#endif

    if (event->tid > T_LAST)
    {
        usr_timer_trigger(event->tid - T_LAST - 1);
    }
#if TIMERS_USED
    else
    {
        callback = (timer_callback_t)PGM_READ_WORD(&timer_callback_table[event->tid]);
        if (callback != NULL)
        {
            callback();
        }
    }
#endif

    return;
}
#endif

/**
 * This function decodes all events/messages and calls the appropriate handler.
 */
void bios_dispatch_event(uint8_t *event)
{
    if (event[1] <= LAST_MESSAGE)
    {
        handler_t handler = (handler_t)PGM_READ_WORD(&dispatch_table[event[1]]);
        if (handler != NULL)
        {
            handler(event);
        }
    }
    return;
}


/* EOF */
