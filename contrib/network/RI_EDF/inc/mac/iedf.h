/**
 * @file iedf.h
 * @brief Implicit-EDF Core (Header)
 * @author Simone Madeo
 * @version 0.1
 * @date 2011-10-10
 */

#ifndef __iedf_h__
#define __iedf_h__

#include "mac/iedf_data.h"

#define USE_IEDF

/* Return values */
#define IEDF_DATA_RX				    0
#define IEDF_DATA_TX               		1
#define IEDF_OK 					    2
#define IEDF_ERROR_INIT				    3
#define IEDF_ERROR_TX				    4
#define IEDF_ERROR_RX				    5
#define IEDF_ERROR_STORE_DATA           6
#define IEDF_ERROR_FRAME_SIZE           7
#define IEDF_CHANGE_STATUS				8
#define IEDF_CHANGE_TOTAL_NODES		    9
#define IEDF_CHANGE_HYPERPERIOD		    10
#define IEDF_TIMESLOT                   11
#define IEDF_CORRUPTED_PACKET           12
#define IEDF_DEADLINE_MISSED            13
#define IEDF_TEST_SYNC                  14

/* Master special packets config */
#define IEDF_MASTER_BLOCKING_PERIOD     20  /* Master period */
#define IEDF_MASTER_INIT_PACKETS        1   /* Reserved slots for scheduling */
#define IEDF_MASTER_ROUTING_PACKETS     0   /* Reserved slots for routing */
#define IEDF_MASTER_CSMA_PACKETS        0   /* Reserved slots for requests 
                                               (do not modify) */
#define IEDF_MASTER_PACKETS             (IEDF_MASTER_INIT_PACKETS + \
                                        IEDF_MASTER_ROUTING_PACKETS)
#define IEDF_MASTER_TOT_PACKETS         (IEDF_MASTER_PACKETS + \
                                        IEDF_MASTER_CSMA_PACKETS)

/* IEDF reserved addresses */
#define IEDF_SLOT_FREE                  0xAAAA // TODO: 0xFFFE 
#define IEDF_ADDRESS_BROADCAST          0      // TODO: 0xFFFF

/* Master protocol/memory config */
#define IEDF_MAX_REQUESTS               5
#define IEDF_MAX_RECOVERY_TIMES         3
#define IEDF_MAX_NODES                  10

/* Time config */
#define IEDF_INIT_WAIT_MS               1000
#define IEDF_WAIT_SCHEDULER_MS          100
#define IEDF_WAIT_HOLETIME_RATIO        2

/* Debug */
#define IEDF_DEBUG_USE_ENERGY           0
#define IEDF_DEBUG_USE_QPA              1
#define IEDF_DEBUG_USE_CONVERSION       1
#define IEDF_DEBUG_USE_SERIAL           0
#define IEDF_DEBUG_JOIN_EXEC            0
#define IEDF_DEBUG_MISS_EXEC            0
#define IEDF_DEBUG_MISS_SIMULATION_SEC  1200

/* MAC protocol data unit */
#define IEDF_MAC_MPDU_SIZE              12
#define IEDF_MAC_HEADER_SIZE            12
#define IEDF_MAC_MPDU_RECOVERY_SIZE     0
#define IEDF_MAC_FRAME_RECOVERY_SIZE    (IEDF_MAC_MPDU_RECOVERY_SIZE + \
                                        IEDF_MAC_HEADER_SIZE)
#define IEDF_MAC_FRAME_SIZE             (IEDF_MAC_MPDU_SIZE + \
                                        IEDF_MAC_HEADER_SIZE)
/* Data buffer size */
#define IEDF_MAX_SLOTS                  3
#define IEDF_BUFFER_SIZE                IEDF_MAC_MPDU_SIZE * IEDF_MAX_SLOTS


/* Node init status */
enum iedf_init_status_type
{
    IEDF_STATUS_NOT_INIT            = 0,    /* Node not initialized */
    IEDF_STATUS_WAIT_SCHEDULE       = 1,    /* Node doesn't know schedulation */
    IEDF_STATUS_WAIT_SCHEDULE_H     = 2,    /* Node knows schedulation */
    IEDF_STATUS_WAIT_REQUEST        = 3,    /* Node must perform request */
    IEDF_STATUS_PENDING_REQUEST     = 4,    /* Node is waiting for grant */
    IEDF_STATUS_GRANTED             = 5,    /* Node granted for next hyper */
    IEDF_STATUS_INIT                = 6,    /* Node correctly joined */
    IEDF_STATUS_REJECTED            = 7,    /* Node has been rejected */
    IEDF_STATUS_WAIT_STOP           = 8,    /* Node is waiting for termination*/
    IEDF_STATUS_TERMINATED          = 9,    /* Node is terminated */
    IEDF_STATUS_SNIFFER             = 10    /* Node is in sniffer mode */
};

/* Initialize Implicit-EDF algorithm.
 *
 * ch: physical channel
 * addr: MAC address
 * n_bytes: data size required by application layer
 * per_ms: period required by application layer
 *
 */
int8_t iedf_init(uint8_t ch, uint16_t addr, uint8_t n_bytes, uint32_t per_ms);

/*
 * Stop Implicit-EDF algorithm.
 * 
 */
int8_t iedf_stop(void);

/*
 * Return 1 if node is iEDF Master.
 * 
 */
int8_t iedf_is_master(void);

/*
 * Return iEDF Master addres.
 * 
 */
uint16_t iedf_get_master(void);

/*
 * Physical-MAC layer data callback.
 * 
 * psduLen: PSDU length
 * psdu: PSDU frame
 * ppduLQ: PSDU link quality
 * 
 */
void iedf_phy2mac_cb(uint8_t psduLen, uint8_t *psdu, uint8_t ppduLQ);

/*
 * Link iEDF callback to upper layer.
 * 
 */
void iedf_link_notify_cb(void (*func) (uint8_t status, uint8_t *data, 
									   uint8_t len, uint16_t add_data));

/*
 * Store a packet into tx data buffer.
 * 
 */
int8_t iedf_packet_store(uint8_t *data, uint8_t len);

/*
 * Return iEDF status.
 * 
 */
enum iedf_init_status_type iedf_get_status(void);

/* TO REMOVE 1 clear, 0 busy */
uint8_t iedf_DEBUG_check_channel(void);

/* DEBUG */
void iedf_test_sync(void);

#endif
