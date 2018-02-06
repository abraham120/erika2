/**
 * @file iedf.c
 * @brief Implicit-EDF Core (Implementation)
 * @author Simone Madeo
 * @author Gianluca Franchino 2012
 * @version 0.1
 * @date 2011-10-10
 */

#include "mac/iedf.h"

/* Deadline miss test data */
const uint8_t miss_nodes = 10;
uint16_t MISS_UMAX = 7;
uint16_t MISS_ITER = 0;
uint16_t miss_test_db[30];
uint16_t miss_test_budget[IEDF_MAX_NODES];
uint16_t miss_db[IEDF_MAX_NODES];
uint8_t miss_wait_for_sync;
uint8_t miss_wait_for_sync2;
uint8_t miss_disable_sniffer;
uint32_t miss_expected;
uint32_t miss_hyperperiod;
uint32_t miss_temp_count;
uint32_t miss_temp_final;

/* Master init config */
#define INIT_NODE_SIZE                6
#define INIT_FIRST_SIZE              12
#define INIT_COMMON_SIZE              3

/* Timeouts for recovery (ms) */
const uint16_t recovery_timeout1_ms =
    IEDF_WAIT_SCHEDULER_MS + IEDF_WAIT_SCHEDULER_MS / 5;
const uint16_t recovery_timeout2_ms =
    IEDF_WAIT_SCHEDULER_MS + IEDF_WAIT_SCHEDULER_MS / 5 * 2;

/* Nodes located in first init packet */
const uint8_t MASTER_INIT_NODES_FIRST = (IEDF_MAC_MPDU_SIZE - INIT_FIRST_SIZE) 
                                        / INIT_NODE_SIZE;
/* Nodes located in others init packet */
const uint8_t MASTER_INIT_NODES_OTHER = (IEDF_MAC_MPDU_SIZE - INIT_COMMON_SIZE)
                                        / INIT_NODE_SIZE;

/* Master blocking interval */
const uint16_t IEDF_WAIT_BLOCKING_MS =
    IEDF_MASTER_BLOCKING_PERIOD * IEDF_WAIT_SCHEDULER_MS;

/* Holetime interval */
const uint16_t IEDF_WAIT_HOLETIME_MS =
    IEDF_WAIT_SCHEDULER_MS / IEDF_WAIT_HOLETIME_RATIO;

/* MPDU type */
typedef uint8_t iedf_mpdu_t[IEDF_MAC_MPDU_SIZE]; 

/* Frame type */
enum iedf_mac_frame_type
{
    IEDF_PACKET_INIT                = 0,    /* 0000 */
    IEDF_PACKET_INIT_UPDATE         = 1,    /* 0001 */
    IEDF_PACKET_DATA                = 2,    /* 0010 */
    IEDF_PACKET_REQUEST             = 4,    /* 0100 */
    IEDF_PACKET_REQUEST_RESERVED    = 5,    /* 0101 */
    IEDF_PACKET_RECOVERY            = 8,    /* 1000 */
    IEDF_PACKET_RECOVERY_RESERVED   = 9,    /* 1001 */
    IEDF_PACKET_RECOVERY_MASTER     = 10,   /* 1010 */
    IEDF_PACKET_ROUTING             = 12,   /* 1100 */
    IEDF_PACKET_STOP                = 15    /* 1111 */
};

/* Node activity type */
enum iedf_activity_type
{
    IEDF_ACTIVITY_NONE              = 0,
    IEDF_ACTIVITY_JOIN_FREE         = 1,
    IEDF_ACTIVITY_JOIN_RESERVED     = 2,
    IEDF_ACTIVITY_NODE_TX           = 3,
    IEDF_ACTIVITY_MASTER_TX         = 4,
    IEDF_ACTIVITY_HOLETIME          = 5
};

/* 
 * MAC FRAME
 * node_turn_stored
struct iedf_mac_frame_t {
	uint16_t dest_addr;             destination address
	uint16_t src_addr;              source address
	uint8_t bitmask;                options:
                                        0123: frame type
                                        4   : packet train compl (node)
                                        4   : new master bit (master)
                                        567 : packet counter (master)
	uint16_t fw_budget;             forwarded budget
	uint32_t seqnum;                sequence number
	uint8_t mpdu_len;               MPDU length
	iedf_mpdu_t mpdu;               MPDU
};
*/

/* Master schedule info to transmit (Init frame) */
static uint8_t mpdu_init[IEDF_MAC_MPDU_SIZE];

/* Master recovery info (Recovery frame) */
static uint8_t mpdu_recovery[IEDF_MAC_MPDU_SIZE];

/* Master routing info (Routing frame) */
static uint8_t mpdu_routing[IEDF_MAC_MPDU_SIZE];

/* Node general scheduling data */
static uint16_t my_params[3];

/* Node initialization status */
static enum iedf_init_status_type init_status;

/* Node id & node activity for next timeslot scheduling */
static uint16_t node_turn_stored;
static enum iedf_activity_type node_turn_activity;

static uint32_t internal_state;         /* Current sequence number stored */
static uint16_t master_address;         /* Master MAC address */
static uint8_t is_master;               /* 1 if this node is master */
static uint8_t master_packet_counter;   /* Init - routing - CSMA counter */
static uint8_t master_update;           /* Node: new schedulation to load 
                                           Master: there are pending requests */
static uint8_t master_update2;          /* New residual schedulation to load */ 
static uint8_t disable_data_tx;         /* Node termination */
static uint8_t master_fails;            /* Master fail counter */
static uint8_t partial_schedule;		/* Node cannot update schedule */
static uint8_t train_stored;    		/* Check if tx train will be stored */
static uint8_t next_init_expected;      /* Next init packet expected */
static uint8_t found_myself;	        /* Check presence of node in db */
static uint8_t new_master;              /* New master election */
static uint8_t new_master_sync;         /* New master synchronization packet */
static uint8_t activate_request;        /* Join request has been transmitted */
static uint8_t train_start_request;     /* Train will be checked after join */
static uint8_t holeslot_enabled;        /* Next slot is free */

static uint16_t recovery_timeout_ms;    /* Node's recovery timeout value */

static uint8_t master_init_mpdu_len;    /* Next mpdu init length */
static uint8_t master_init_train_update;/* Check init train to transmit */
static uint8_t master_init_counter;     /* Current init packet to transmit */
static uint8_t master_init_total;       /* Total init packet number */
static uint8_t master_init_nodes_left;	/* Nodes left to be added */
static uint8_t master_init_tx;	        /* Database enabled to transmit 
                                            0 - current database 
                                            1 - next database 
                                            2 - residual database */
static uint8_t master_init_in_period;   /* Check if packet init train has been 
                                           completed in last hyperperiod */
/* Scheduler tasks */
IEDF_KAL_TASK_ASYNC(IEDF_SCHEDULER, 10);
IEDF_KAL_TASK_ASYNC(IEDF_SCHEDULER_SET_RX_ON, 10);
IEDF_KAL_TASK_ASYNC(IEDF_SCHEDULER_HOLETIME, 10);
IEDF_KAL_TASK_ASYNC(IEDF_SCHEDULER_BLOCKING, 10);
IEDF_KAL_MUTEX(IEDF_DATA_MUTEX, IEDF_SCHEDULER);
IEDF_KAL_MUTEX(IEDF_DATA_MUTEX, IEDF_SCHEDULER_HOLETIME);
IEDF_KAL_MUTEX(IEDF_DATA_MUTEX, IEDF_SCHEDULER_BLOCKING);

/* Recovery task */
IEDF_KAL_TASK_ASYNC(IEDF_RECOVERY, 10);
IEDF_KAL_MUTEX(IEDF_DATA_MUTEX, IEDF_RECOVERY);

/* Master init task */
IEDF_KAL_TASK_ASYNC(IEDF_MASTER_START, 10);
IEDF_KAL_MUTEX(IEDF_DATA_MUTEX, IEDF_MASTER_START);

/* Higher level data callback */
static void (*iedf_notify) (uint8_t, uint8_t*, uint8_t, uint16_t) = NULL;


/* **************************************************************************
                                PRIVATE METHODS
   ************************************************************************** */

/* Change node's iEDF internal status */
static void iedf_change_status(enum iedf_init_status_type new_status)
{
    init_status = new_status;
    iedf_notify(IEDF_CHANGE_STATUS, NULL, 0, init_status);
}

/* Return the amount of init packets for a given number of nodes */
static uint8_t iedf_master_init_total(uint16_t nodes)
{
    uint8_t total = 1;
    
    if (nodes > MASTER_INIT_NODES_FIRST) {
        total = 1 + (nodes - MASTER_INIT_NODES_FIRST) / MASTER_INIT_NODES_OTHER;
        if ((nodes - MASTER_INIT_NODES_FIRST) % MASTER_INIT_NODES_OTHER > 0)
            total++;
    }
    return total;
}

/* Return 1 if next train will be enterely transmitted in curr hyperperiod */
static uint8_t iedf_master_init_complete(uint8_t index)
{
    uint32_t master_packets;            /* Master packets in cur hyperperiod */
    uint32_t remaining_init_packets;    /* Init packets left */
    uint32_t additional_init_packets;   /* Init packets bonus */

    uint32_t hyper_period = iedf_get_hyperperiod(0);
    uint16_t num_nodes_next2 = iedf_get_total_nodes(index);
    
    master_packets =
        (hyper_period - internal_state) / IEDF_MASTER_BLOCKING_PERIOD;
    remaining_init_packets =
        master_packets / IEDF_MASTER_TOT_PACKETS * IEDF_MASTER_INIT_PACKETS;
    additional_init_packets =
        master_packets % IEDF_MASTER_TOT_PACKETS;
    remaining_init_packets +=
        (additional_init_packets < IEDF_MASTER_INIT_PACKETS) ?
        additional_init_packets : IEDF_MASTER_INIT_PACKETS;
    
    iedf_DEBUG_serial_int3(internal_state, master_packets, remaining_init_packets);
    iedf_DEBUG_serial("\r\n -- init_complete (slot, m_p_in_p, remaining_init)"); 
    iedf_DEBUG_serial_int(iedf_master_init_total(num_nodes_next2));
    iedf_DEBUG_serial(" need"); 
    
    if (iedf_master_init_total(num_nodes_next2) > remaining_init_packets) {
        iedf_DEBUG_serial("\r\n --> Master packet train does not fit the\
						  current hyper."); 
        return 0;
    }
    
	iedf_DEBUG_serial("\r\n --> Master packet train fits in the current hyper.");
	
    return 1;
}

/* Update master packet counter */
static void iedf_master_packet_counter_update(uint8_t old_value)
{
    master_packet_counter = old_value + 1;
    if (master_packet_counter >= IEDF_MASTER_TOT_PACKETS)
        master_packet_counter = 0;
}

/* Build next mpdu init packet. */
static void iedf_master_build_mpdu_init(uint8_t *packet)
{
    uint16_t blocking_period = IEDF_MASTER_BLOCKING_PERIOD;    
	uint8_t nodes_per_packet = MASTER_INIT_NODES_OTHER;
	uint8_t pos = 2, to_add, i, counter;
    
    uint16_t num_nodes = iedf_get_total_nodes(master_init_tx);
    uint32_t hyper_period = iedf_get_hyperperiod(master_init_tx);
    
    /* Reset packet */
    memset(&packet[0], 0x00, IEDF_MAC_MPDU_SIZE);
    /* New init packet train in current hyperperiod */
	if (master_init_counter == 0) {
        /* Number of Init packets in this train */
        master_init_total = iedf_master_init_total(num_nodes);
        /* Nodes to put into next init packets train */
        master_init_nodes_left = num_nodes;
        /* Special fields for first mpdu init */
        /* *** TODO *** Master tot packets not transmitted 
         * (packet[3] = IEDF_MASTER_TOT_PACKETS;) */
        packet[3] = 0x0E;
        if (master_init_tx == 2 || !iedf_master_init_complete(0)) {
            /* Train not covered by hyperperiod */
            iedf_DEBUG_serial("\r\n## # - next train NOT in hyperperiod!!- # ##");
            /* Note: first bit check train coverage */
            packet[3] |= 0x80;
        } else {
            /* Train covered by hyperperiod */
            iedf_DEBUG_serial("\r\n## # - next train IN hyperperiod!!- # ##");
        }
        if (master_update)
            iedf_DEBUG_serial("\r\nupdate set!");
        memcpy(&packet[4], (uint16_t*)&blocking_period, 2);
        memcpy(&packet[6], (uint16_t*)&num_nodes, 2);
        memcpy(&packet[8], (uint32_t*)&hyper_period, 4);
        /* Nodes to put into first init packet */
        nodes_per_packet = MASTER_INIT_NODES_FIRST;
		/* Last writed byte */
		pos = 11;
	}

	/* Nodes stored in packet */
	if (master_init_nodes_left < nodes_per_packet)
		counter = master_init_nodes_left;
	else
		counter = nodes_per_packet;

    /* Common fields */
    packet[0] = master_init_counter;
    packet[1] = master_init_total;
	packet[2] = counter;

	/* Nodes addition */
    for (i = 0; i < counter; i++) {
        to_add = num_nodes - master_init_nodes_left;
        iedf_db_package(&packet[pos + i * 6 + 1], master_init_tx, to_add);
        master_init_nodes_left--;
    }
	/* Prepare next mpdu init */
	master_init_counter++;
	if (master_init_counter == master_init_total) {
        master_init_counter = 0;
        /* Init train has been completed in this hyperperiod */
        master_init_in_period = 1;
    }
    
    master_init_mpdu_len = pos + 1 + counter * 6;
}

/* Recovery & scheduler task activation according to last packet received.
 * If address not equals SLOT_FREE, next timeout will be activated
 * in a different time. */
static void iedf_scheduler_set(uint16_t src_address)
{
    uint16_t gap_timeout = 0;

    if (holeslot_enabled) {
        /* Hole in this slot */
        gap_timeout = IEDF_WAIT_HOLETIME_MS;
    }
    if (src_address == master_address) {
        /* Master recovery */
        gap_timeout += (recovery_timeout1_ms - IEDF_WAIT_SCHEDULER_MS);
    } else if (src_address != IEDF_SLOT_FREE) {
        /* Node recovery */
        gap_timeout += (recovery_timeout2_ms - IEDF_WAIT_SCHEDULER_MS);
    }
    /* TX Schedule */
    iedf_kal_set_activation(IEDF_SCHEDULER, IEDF_WAIT_SCHEDULER_MS - gap_timeout, 0);
    /* RX Schedule */
    if (IEDF_DEBUG_USE_ENERGY)
        iedf_kal_set_activation(IEDF_SCHEDULER_SET_RX_ON, IEDF_WAIT_SCHEDULER_MS - gap_timeout - 5, 0);
    /* Idle Schedule */
    iedf_kal_set_activation(IEDF_SCHEDULER_HOLETIME, IEDF_WAIT_SCHEDULER_MS - gap_timeout + IEDF_WAIT_HOLETIME_MS, 0);
    
    if (recovery_timeout_ms && init_status == IEDF_STATUS_INIT) {
        /* Recovery timer activation */
        iedf_kal_set_activation(IEDF_RECOVERY, recovery_timeout_ms - gap_timeout, 0);
    }
}

/* Scheduler task disabling */
static void iedf_scheduler_cancel(uint8_t holetime)
{
    if (holetime)
        iedf_kal_cancel_activation(IEDF_SCHEDULER);
    else
        iedf_kal_cancel_activation(IEDF_SCHEDULER_HOLETIME);
}

/* Recovery task disabling */
static void iedf_recovery_cancel()
{
    iedf_kal_cancel_activation(IEDF_RECOVERY);
}

/* Update all schedule info (at beginning of hyperperiod) */
static uint8_t iedf_scheduler_update(uint8_t check)
{
    uint8_t ret = 0;

    if (master_update && check) {
        /* Overwriting new scheduling data structure */
        if (iedf_db_copy(0, 1))
            recovery_timeout_ms = recovery_timeout2_ms;
        else if (!is_master)
            recovery_timeout_ms = 0;
        iedf_notify(IEDF_CHANGE_TOTAL_NODES, NULL, 0, iedf_get_total_nodes(0));
        iedf_notify(IEDF_CHANGE_HYPERPERIOD, NULL, 0, iedf_get_hyperperiod(0));
        iedf_DEBUG_print_db(0, "New database!");
        master_update = 0;
        ret = 1;
    } else {
        iedf_DEBUG_serial("\r\n# # # # DB not modified # # # #");
        if (master_update && !check && !is_master)
            iedf_DEBUG_serial("\r\nPacket train not completed [**] !!!");
    }
    if (master_update2) {
        /* Overwriting next scheduling data structure */
        iedf_db_copy(1, 2);
        iedf_DEBUG_print_db(1, "DB2 --> DB1");
        master_update = 1;
        master_update2 = 0;
    } else {
        iedf_DEBUG_serial("\r\n# # # # DB_next non modificato # # # #");
    }
    return ret;
}

/* Accept scheduling changes */
static void iedf_master_requests()
{
    if (master_init_counter == 0) {
        /* Note: at beginning of hyperperiod 2 --> 1, then source is always 1;
         * no residual train (init == 0), 2 is not used and can be overwrited,
         * and mantain last update */
        master_init_train_update = 0;
        
        iedf_DEBUG_serial("\r\nMASTER_REQUESTS");
        
        if (iedf_get_pending_requests() == 0) {
            /* No request has been submitted */
            return;
        }

        /* Master database update for next Init packet train */
        if (!iedf_data_requests_flush()) {
            /* No changes in schedulation */
            master_init_tx = 1;
            return;
        }

        /* Prepare info for a new train */
        master_init_train_update = 1;
        if (iedf_master_init_complete(2)) {
            /* Modified schedule completely in this hyperperiod */
            master_init_tx = 1;
            master_update = 1;
            iedf_db_copy(1, 2);
        } else {
            /* Modified schedule not completely in this hyperperiod */
            master_init_tx = 2;
            master_update2 = 1;
        }
    }
}

/* This operations will be executed at the beginning of period */
static void iedf_hyperperiod_begin()
{
    if (!is_master) {
        /* --- Node update --- */
        if (init_status == IEDF_STATUS_WAIT_SCHEDULE_H)
            iedf_change_status(IEDF_STATUS_WAIT_REQUEST);
        else if (init_status == IEDF_STATUS_GRANTED)
            iedf_change_status(IEDF_STATUS_INIT);

        iedf_scheduler_update(!partial_schedule);
        partial_schedule = 1;
    } else {
        /* --- Master scheduler update --- */
        if (iedf_scheduler_update(master_init_in_period) ) {
            /* Current db modified - check for failure data structure */
            iedf_master_data_failure_remove(0);
        }
        /* Note: if (update2) transmit 2 --> 1; if (update) transmit 1 --> 0
         * in both cases the correct transmit-id is 1 */
        master_init_tx = 1;
        /* Reset master init train completion */
        master_init_in_period = 0;
    }
}

/* Prepare iEDF data structure for next timeslot */
static void iedf_scheduler_next(uint8_t master_turn)
{
    /* Update scheduling info at beginning of hyperperiod */
    if (internal_state == 0)
        iedf_hyperperiod_begin();

    /* Check for schedulation changes / init mpdu build */
    if (is_master) {
        if (master_packet_counter < IEDF_MASTER_INIT_PACKETS && master_turn) {
            iedf_master_requests();
            iedf_DEBUG_serial("\r\nPrepare build mpdu");
            iedf_master_build_mpdu_init((uint8_t*)&mpdu_init[0]);
        }
    }
}

/* Prepare next timeslot into iEDF scheduling */
static char* iedf_scheduler_manage(uint8_t master_exception)
{
    /* Scheduled node for next time slot */
    node_turn_stored = iedf_data_turn(internal_state);
    node_turn_activity = IEDF_ACTIVITY_NONE;
    if (master_exception) {
        new_master_sync = 1;
    }
    
    /* Schedulation */
    if (init_status == IEDF_STATUS_WAIT_REQUEST) {
        // TODO da rivedere con backoff
        if (node_turn_stored == IEDF_SLOT_FREE) {
            /* Node has to perform join request in a free slot */
            node_turn_activity = IEDF_ACTIVITY_JOIN_FREE;
        } else if (node_turn_stored == 0 && master_packet_counter >= 
        IEDF_MASTER_PACKETS && master_fails == 0) {
            /* Node has to perform join request in a reserved free slot */
            node_turn_activity = IEDF_ACTIVITY_JOIN_RESERVED;
        }
    } else if (node_turn_stored == iedf_get_my_nodeid()) {
        /* Node's turn */
        node_turn_activity = IEDF_ACTIVITY_NODE_TX;
    } else if (node_turn_stored == 0 && is_master &&
    master_packet_counter < IEDF_MASTER_PACKETS) {
        /* Master's turn */
        node_turn_activity = IEDF_ACTIVITY_MASTER_TX;
    }
    
    if (node_turn_activity != IEDF_ACTIVITY_NONE) {
        /* Next timeslot it's my turn - Scheduler enabled */
        iedf_scheduler_cancel(0);
        iedf_recovery_cancel();
        if (node_turn_activity == IEDF_ACTIVITY_MASTER_TX) {
            if (new_master_sync) {
                new_master_sync = 0;
				return "\r\nI do erase recovery and hole and -NO- sched [SCHED MAS]";
            } else {
                iedf_scheduler_cancel(1);
                return "\r\nI do erase recovery and hole and sched [SCHED MAS]";
            }
        } else
            return "\r\nI do erase recovery and hole [SCHED]";
    } else {
        if (node_turn_stored == IEDF_SLOT_FREE) {
            /* Holeslot anabled */
            node_turn_activity = IEDF_ACTIVITY_HOLETIME;
            iedf_scheduler_cancel(1);
            iedf_recovery_cancel();
            iedf_kal_cancel_activation(IEDF_SCHEDULER_SET_RX_ON);
            holeslot_enabled = 1;
            return "\r\nI do erase recovery and sched [HOLE]";
        } else {
            /* Master synchronization */
            if (node_turn_stored == 0 && IEDF_DEBUG_USE_ENERGY)
                iedf_phy_set_status(IEDF_PHY_RX_ON);
            /* Recovery enabled */
            iedf_scheduler_cancel(0);
            iedf_scheduler_cancel(1);
            return "\r\nI do erase scheduler, set recovery [NONE]";
        }
    }
    
    return "";
}

/* Build MAC frame with MAC header and upper layer info */
static void iedf_mac_build_frame(uint8_t *mpdu, uint8_t mpdu_len, uint8_t type,
uint16_t dst_addr, uint8_t *frame)
{
    /* Note: master_packet_counter is 3 bits sized */
    uint32_t cur_internal_state = internal_state;
    
    /* Internal state update */
    internal_state++;
    if (internal_state == iedf_get_hyperperiod(0))
        internal_state = 0;
    /* Build frame */   
    memcpy(&frame[0], (uint16_t*)&dst_addr, 2);         /* destination */
    memcpy(&frame[2], (uint16_t*)&my_params[0], 2);     /* source */
    /* Update master packet type counter */
    if (type == IEDF_PACKET_INIT || type == IEDF_PACKET_INIT_UPDATE || 
    (is_master && type == IEDF_PACKET_RECOVERY_RESERVED) ||
    type == IEDF_PACKET_ROUTING) {
        /* Master */
        frame[4] = master_packet_counter;
        iedf_master_packet_counter_update(master_packet_counter);
    } else if (type == IEDF_PACKET_REQUEST_RESERVED) {
        /* Node in reserved slot */
        frame[4] = master_packet_counter;
        iedf_master_packet_counter_update(master_packet_counter);
    } else if (type == IEDF_PACKET_RECOVERY_MASTER) {
        /* Node in master recovery slot */
        if (cur_internal_state % IEDF_MASTER_BLOCKING_PERIOD == 0) {
            /* Master packet counter must be increased */
            frame[4] = master_packet_counter;
            iedf_master_packet_counter_update(master_packet_counter);
        } else {
            /* Master packet counter must remain unchanged */
            if (master_packet_counter == 0)
                frame[4] = IEDF_MASTER_TOT_PACKETS - 1;
            else
                frame[4] = master_packet_counter - 1;
        }
    } else {
        /* Node in regular slot */
        // *** TODO *** PTC not implemented
        frame[4] = 0;
    }
    frame[4] |= type << 4;                              /* bitmask */
    /* Set new master bit. Note: only first packet of train is set */
    if (new_master) {
        frame[4] |= 0x08;
        new_master = 0;
        new_master_sync = 1;
        iedf_DEBUG_serial("\r\n\r\nsync\r\n");
    }
    memset(&frame[5], 0, 2);                            /* fw_budget */
    memcpy(&frame[7], (uint32_t*)&internal_state, 4);   /* seqnum */
    frame[11] = mpdu_len;                               /* mpdulen */
    memset(&frame[12], 0, IEDF_MAC_MPDU_SIZE);          /* mpdu */
    memcpy(&frame[12], mpdu, mpdu_len);
}

/* Data transmission routine */
static int8_t iedf_send(uint8_t *data, uint8_t len,
enum iedf_mac_frame_type type, uint16_t dst_addr)
{
    uint8_t frame[IEDF_MAC_FRAME_SIZE];

    if (len > IEDF_MAC_MPDU_SIZE)
        return -IEDF_ERROR_FRAME_SIZE;
    if (data == NULL) {
        /* All zeros packet */
        memset(data, 0x00, IEDF_MAC_MPDU_SIZE);
    }
    iedf_mac_build_frame(data, len, type, dst_addr, &frame[0]);
	if (iedf_phy_set_status(IEDF_PHY_TX_ON) < 0)
		return -IEDF_ERROR_TX;
	if (iedf_phy_send(frame, IEDF_MAC_FRAME_SIZE) < 0)
		return -IEDF_ERROR_TX;
    /* Default behavior: sleep mode */
    if (IEDF_DEBUG_USE_ENERGY && init_status != IEDF_STATUS_SNIFFER) {
        if (iedf_phy_set_status(IEDF_PHY_FORCE_TRX_OFF) < 0)
            return -IEDF_ERROR_RX;
    } else {
        if (iedf_phy_set_status(IEDF_PHY_RX_ON) < 0)
            return -IEDF_ERROR_RX;
	}
    return IEDF_OK;
}

/* Master transmission */
static char* iedf_master_send()
{
    enum iedf_mac_frame_type type = IEDF_PACKET_INIT;
    
    //EE_led_1_on();
    if (master_packet_counter < IEDF_MASTER_INIT_PACKETS) {
        /* Init packet */
        if (master_init_train_update)
            type = IEDF_PACKET_INIT_UPDATE;
        iedf_notify(IEDF_TIMESLOT, NULL, 0, internal_state);
        iedf_send((uint8_t*)&mpdu_init[0], master_init_mpdu_len, type,
            IEDF_ADDRESS_BROADCAST);
        return "\r\n[INIT]";
    } else if (master_packet_counter < IEDF_MASTER_PACKETS) {
        /* Routing packet */
        // ***TODO*** Not implemented
        iedf_notify(IEDF_TIMESLOT, NULL, 0, internal_state);
        iedf_send((uint8_t*)&mpdu_routing[0], IEDF_MAC_MPDU_SIZE,
            IEDF_PACKET_ROUTING, IEDF_ADDRESS_BROADCAST);
        return "\r\n[ROUT]";
    } else {
        /* Note: master called uselessly */
        //EE_leds_on();
        iedf_DEBUG_serial("\r\n*** ERROR *** Unsynchronized master");
        for(;;);
        return "";
    }
}

/* This function is called when recovery timer is fired */
static void iedf_task_recovery()
{
    uint16_t turn = 0;
    uint16_t my_addr = iedf_get_my_nodeid();

    if (init_status != IEDF_STATUS_SNIFFER) {
        //EE_led_6_on();
	}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    iedf_kal_mutex_wait(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
      
    /* Set timer for next timeslot */
    iedf_scheduler_set(my_addr);
    holeslot_enabled = 0;

    iedf_DEBUG_serial_int(internal_state);
    if (internal_state == 0)
        iedf_DEBUG_serial("\r\n@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=");
    else
        iedf_DEBUG_serial(" ================================");
    iedf_DEBUG_serial("\r\nRecovery");
   
    turn = node_turn_stored;
	/*
    EE_led_0_off();
    EE_led_1_off();
    EE_led_2_on();
	 */
    if (turn == 0 && is_master) {
        /* --- CSMA not used --- */
        iedf_DEBUG_serial("\r\n[C S M A]");
        memset(&mpdu_recovery[0], 0xCC, IEDF_MAC_MPDU_SIZE);
        iedf_notify(IEDF_TIMESLOT, NULL, 0, internal_state);
        iedf_send((uint8_t*)&mpdu_recovery[0], IEDF_MAC_MPDU_SIZE,
            IEDF_PACKET_RECOVERY_RESERVED, IEDF_ADDRESS_BROADCAST);
    } else if (turn != 0 && is_master) {
        /* --- Master recovery from node failure --- */
        if (turn != IEDF_SLOT_FREE) {
            iedf_DEBUG_serial_int(turn);
            iedf_DEBUG_serial(" has failed transmission (recovery)");
        }
        memset(&mpdu_recovery[0], 0x77, IEDF_MAC_MPDU_SIZE);
        iedf_notify(IEDF_TIMESLOT, NULL, 0, internal_state);
        iedf_send((uint8_t*)&mpdu_recovery[0], IEDF_MAC_MPDU_SIZE,
            IEDF_PACKET_RECOVERY, IEDF_ADDRESS_BROADCAST);
        if (turn != IEDF_SLOT_FREE && !IEDF_DEBUG_MISS_EXEC) {
            /* Check node's presence in failure data structure */
            iedf_master_data_failure_add(turn, 0);
            // TODO: da rimuovere
            iedf_DEBUG_print_failure();                
        }
    } else if (!IEDF_DEBUG_MISS_EXEC) {
        /* --- Master has failed transmission --- */
        master_fails++;
        iedf_DEBUG_serial_int(master_fails);
        iedf_DEBUG_serial("\r\n *** MASTER FAILURE ***");
        if (master_fails >= IEDF_MAX_RECOVERY_TIMES) {
            iedf_DEBUG_serial("\r\n  *** NEW MASTER ***");
            /* Note: only current db is valid */
            iedf_db_copy(2, 0);
            iedf_db_copy(1, 0);
            master_update = 0;
            master_update2 = 0;
            /* Old Master removed */
            uint8_t req[6];
            memset(&req[0], 0x00, 6);
            memcpy(&req[0], &master_address, 2);
            iedf_data_requests_store(req, 1);            
            /* New Master election */
            master_fails = 0;
            master_address = iedf_get_my_nodeid();
            is_master = 1;
            iedf_master_data_failure_reset();
            recovery_timeout_ms = recovery_timeout1_ms;
            /* Reset master init packet */
            new_master = 1;
            master_packet_counter = 0;
            master_init_tx = 1;
			master_init_counter = 0;
            iedf_master_build_mpdu_init((uint8_t*)&mpdu_init[0]);
            /* New master transmission */
            if (turn == 0)
                iedf_master_send();            
            else {
                memset(&mpdu_recovery[0], 0x76, IEDF_MAC_MPDU_SIZE);
                iedf_send((uint8_t*)&mpdu_recovery[0], IEDF_MAC_MPDU_SIZE, 
                IEDF_PACKET_RECOVERY, IEDF_ADDRESS_BROADCAST);
            }
        } else {
            /* Single master recovery */
            memset(&mpdu_recovery[0], 0x88, IEDF_MAC_MPDU_SIZE);
            iedf_send((uint8_t*)&mpdu_recovery[0], IEDF_MAC_MPDU_SIZE, 
            IEDF_PACKET_RECOVERY_MASTER, IEDF_ADDRESS_BROADCAST);
        }
    } else {
		/*
        EE_led_3_on();
        EE_led_2_off();
		 */
        memset(&mpdu_recovery[0], 0xAE, IEDF_MAC_MPDU_SIZE);
        iedf_notify(IEDF_TIMESLOT, NULL, 0, internal_state);
        iedf_send((uint8_t*)&mpdu_recovery[0], IEDF_MAC_MPDU_SIZE,
            IEDF_PACKET_RECOVERY_MASTER, IEDF_ADDRESS_BROADCAST);
        //iedf_recovery_cancel();
        //EE_led_7_on();
    }
    
    /* Prepare next timeslot */
    char *msg = iedf_scheduler_manage(0);
    iedf_DEBUG_serial(msg);

    /* Check for additional operations */
    iedf_scheduler_next(node_turn_activity == IEDF_ACTIVITY_MASTER_TX);

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	iedf_kal_mutex_signal(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    
    //EE_led_6_off();
    
}

/* Task activated at the beginning of a new time slot */
static void iedf_task_scheduler()
{
    uint32_t msg_state = internal_state;
    uint32_t msg_node = node_turn_stored;
    char *msg1 = ""; // TODO
    char *msg2 = "";
    uint8_t tx[5];

    if (init_status != IEDF_STATUS_SNIFFER) { 
        EE_led_7_on();
	}
    
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	iedf_kal_mutex_wait(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    /* Checking for blocking period */
    if (node_turn_activity == IEDF_ACTIVITY_MASTER_TX) {
        iedf_kal_set_activation(IEDF_SCHEDULER_BLOCKING, IEDF_WAIT_BLOCKING_MS, 0);
    }

    /* Set timer for next timeslot */
    iedf_scheduler_set(IEDF_SLOT_FREE);
    holeslot_enabled = 0;
    /*
    EE_led_0_off();
    EE_led_1_off();
    EE_led_2_off();
    EE_led_3_off();
    EE_led_4_off();
	 */
    // TODO: (CCA)
    if ((node_turn_activity == IEDF_ACTIVITY_JOIN_FREE || node_turn_activity == 
    IEDF_ACTIVITY_JOIN_RESERVED) && iedf_phy_get_cca()) {
        /* Node has to perform join request in a free/reserved slot */
        //EE_led_6_on();
        if (node_turn_activity == IEDF_ACTIVITY_JOIN_FREE) {
            iedf_send((uint8_t*)&my_params[0], 6, IEDF_PACKET_REQUEST, IEDF_ADDRESS_BROADCAST);
            msg1 = "\r\nJOIN REQUEST in free slot";
        } else {
            iedf_send((uint8_t*)&my_params[0], 6, IEDF_PACKET_REQUEST_RESERVED, IEDF_ADDRESS_BROADCAST);
            msg1 = "\r\nJOIN REQUEST in reserved slot";
        }
        iedf_change_status(IEDF_STATUS_PENDING_REQUEST);
        activate_request = 1;
        iedf_scheduler_cancel(0);
        iedf_scheduler_cancel(1);
        iedf_recovery_cancel();
    }
    
    else {
        if (node_turn_activity == IEDF_ACTIVITY_MASTER_TX) {
            /* *** Master's turn *** */
            msg1 = iedf_master_send();
        } else if (node_turn_activity == IEDF_ACTIVITY_NODE_TX) {
            /* *** Node's turn *** */
            //EE_led_0_on();
            if (disable_data_tx) {
                /* Node has to perform part request (in one's own slot) */
                /* Pay attention: node does not perform data transfer anymore */
                //EE_led_6_off();
                msg1 = "\r\nSTOP REQUEST";
                if (iedf_send((uint8_t*)&my_params[0], 6, IEDF_PACKET_STOP, IEDF_ADDRESS_BROADCAST) >= 0)
                    iedf_change_status(IEDF_STATUS_WAIT_STOP);
            } else {
                /* Node's transmission */
                if (is_master)
                    iedf_notify(IEDF_TIMESLOT, NULL, 0, internal_state);
                /* Data to transmit */
                tx[0] = (uint8_t)internal_state + 1;
                tx[1] = (uint8_t)internal_state + 2;
                tx[2] = (uint8_t)internal_state + 3;
                tx[3] = (uint8_t)internal_state + 4;
                tx[4] = (uint8_t)internal_state + 5;
                iedf_buffer_put(tx, 5);
                if (iedf_send(iedf_buffer_get(), IEDF_MAC_MPDU_SIZE, IEDF_PACKET_DATA, IEDF_ADDRESS_BROADCAST) >= 0)
                    if (iedf_notify != NULL)
                        iedf_notify(IEDF_DATA_TX, NULL, 0, IEDF_ADDRESS_BROADCAST);
            }
        } else {
            msg1 = "\r\n B U C O (sempre posticipato)";
            internal_state++;
            if (internal_state == iedf_get_hyperperiod(0))
                internal_state = 0;  
        }
        /* Prepare next timeslot */
        msg2 = iedf_scheduler_manage(0);
    }

    iedf_DEBUG_serial_int(msg_state);
    if (msg_state == 0)
        iedf_DEBUG_serial(" @=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=");
    else
        iedf_DEBUG_serial(" ================================");
    iedf_DEBUG_serial_int(msg_node);
    iedf_DEBUG_serial("\r\nScheduled to transmit");
    iedf_DEBUG_serial(msg1);
    iedf_DEBUG_serial(msg2);
    /*iedf_DEBUG_serial_int3(remaining_budget[0],remaining_budget[1],remaining_budget[2]);
    iedf_DEBUG_serial(" Budget");
    */

    /* Check for additional operations */
    iedf_scheduler_next(node_turn_activity == IEDF_ACTIVITY_MASTER_TX);

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	iedf_kal_mutex_signal(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //EE_led_7_off();
}

/* Puts the radio on RX mode */
static void iedf_task_set_rx_on()
{
    if (node_turn_stored != IEDF_SLOT_FREE && node_turn_stored != my_params[0]) {
        iedf_phy_set_status(IEDF_PHY_RX_ON);
    }
    else if (init_status == IEDF_STATUS_INIT) {
        iedf_phy_set_status(IEDF_PHY_FORCE_TRX_OFF);
    }
}

/* Execute deadline miss test for sniffer */
void iedf_test_miss(uint16_t src_addr, uint8_t recovery)
{
    uint8_t i;
    uint8_t miss = 0;
    uint32_t j;
    uint32_t miss_tot = 0, packet_tot = 0;
    
    /* Waiting for hyperperiod sync */
    if (internal_state == 0)
        internal_state = miss_hyperperiod;
    if (miss_wait_for_sync && internal_state == 1) {
        //EE_led_7_off();
        miss_wait_for_sync = 0;
    }
    if (miss_wait_for_sync || miss_disable_sniffer)
        return;
    if (internal_state == miss_expected - 1)
        return;
    /* Refill budget */
    for (j = miss_expected;; j++) {
        if (j > miss_hyperperiod)
            j = 1;
        miss_temp_count++;
        for (i = 0; i < miss_nodes; i++)
            if ((j - 1) % miss_test_db[i * 3 + 2] == 0 && !miss_wait_for_sync2) {
                if (miss_test_budget[i] != 0) {
                    miss = 1;
                    miss_db[i] += miss_test_budget[i];
                }
                miss_test_budget[i] = miss_test_db[i * 3 + 1];
            }
        if (miss_wait_for_sync2)
            miss_wait_for_sync2 = 0;
        if (j == internal_state)
            break;
    }
    /* Schedule */
    if ((internal_state - 1) % IEDF_MASTER_BLOCKING_PERIOD != 0 && !recovery) {
        if (miss_test_budget[src_addr - 1] == 0) {
            iedf_DEBUG_serial_int3(internal_state, src_addr, 88);
            iedf_DEBUG_serial("\r\nsniffer problem");
        } else
            miss_test_budget[src_addr - 1]--;
    } //else
      //  iedf_DEBUG_serial(" *");
    if (miss)
        iedf_notify(IEDF_DEADLINE_MISSED, (uint8_t*)&miss_db[0], 2 * miss_nodes, 0);
        
    miss_expected = internal_state + 1;
    if (miss_expected > miss_hyperperiod)
        miss_expected = 1;
    /* Check for end test */
    if (miss_temp_count > miss_temp_final) {
        miss_disable_sniffer = 1;
        for (i = 0; i < miss_nodes; i++) {
            packet_tot += miss_temp_final / miss_test_db[i * 3 + 2] * miss_test_db[i * 3 + 1];
            miss_tot += miss_db[i];
        }
        iedf_DEBUG_serial_int3(MISS_UMAX, miss_tot, packet_tot);
        iedf_DEBUG_serial("\r\n");
        iedf_test_sync();
    }
}

/* Execute QPA/PDC join test */
void iedf_test_join()
{
    const uint8_t maxnodes = 2;
    const uint8_t iterations = 1;
    uint16_t time_min[maxnodes];
    uint16_t time_max[maxnodes];
    uint16_t time_sum[maxnodes];
    uint16_t time_num[maxnodes];
    uint16_t C[maxnodes];
    uint16_t T[maxnodes];
    uint16_t timing;
    uint8_t j, i;
    double u_max = 0.75;
    double u_tot = 0;
    
    srand(0);

    for (i = 0; i < maxnodes; i++) {
        time_min[i] = 65535;
        time_max[i] = 0;
        time_sum[i] = 0;
        time_num[i] = 0;
    }

    for (j = 0; j < iterations; j++) {
        u_tot = UUniFast(maxnodes, u_max, &C[0], &T[0]);
        C[0] = 4;
        T[0] = 8;
        C[1] = 2;
        T[1] = 12;
        //iedf_DEBUG_serial_double(u_tot);
        //iedf_DEBUG_serial(" banda effettivamente utilizzata");
        iedf_data_join(0, 1, IEDF_MASTER_BLOCKING_PERIOD, NULL);
        for (i = 0; i < maxnodes; i++) {
            //iedf_DEBUG_serial_int3(i+2, C[i], T[i]);
            //iedf_DEBUG_serial(" frazione");
            if (C[i] != 0) {
                if (iedf_data_join(0xEF00 + i, C[i], T[i], &timing)) {
                    if (timing < time_min[i]) time_min[i] = timing;
                    if (timing > time_max[i]) time_max[i] = timing;
                    time_sum[i] += timing;
                    time_num[i] ++;
                }                    
            }
        }
        /* Reset db structure */
        iedf_data_clean();
    }
    /* Send collected data */
    //for (i = 0; i < maxnodes; i++)
    //    iedf_DEBUG_serial_int3(time_sum[i] / time_num[i], time_min[i], time_max[i]);
     
    for(;;); /* end test */
}

/* Task activated when the new node is elected mater */
static void iedf_task_master_start()
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	iedf_kal_mutex_wait(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    if (!IEDF_DEBUG_JOIN_EXEC) {
        /* Master node update */
        is_master = 1;
        iedf_data_join(0, 1, IEDF_MASTER_BLOCKING_PERIOD, NULL);
        iedf_DEBUG_serial("\r\nNode is elected master");   

        /* Generic node update */
        if (iedf_data_join(iedf_get_my_nodeid(), iedf_get_my_budget(),
        iedf_get_my_period(), NULL) == 0) {
            //EE_leds_on();
            return;
        }
    } else {
        /* Feasibility test */
        iedf_test_join();
    }
    
    /* Immediate schedule update */
    iedf_db_copy(0, 2);
    iedf_db_copy(1, 0);
    
    /* Set global variables - Master node is automatically initialized */
    iedf_change_status(IEDF_STATUS_INIT);
    internal_state = 0;
    master_address = iedf_get_my_nodeid();
    node_turn_activity = IEDF_ACTIVITY_MASTER_TX;
    recovery_timeout_ms = recovery_timeout1_ms;
    iedf_master_build_mpdu_init((uint8_t*)&mpdu_init[0]);

    /* Prepare data structure */
    iedf_master_data_failure_reset();
        
    /* Upper layer notifications */
    iedf_notify(IEDF_CHANGE_TOTAL_NODES, NULL, 0, iedf_get_total_nodes(0));
    iedf_notify(IEDF_CHANGE_HYPERPERIOD, NULL, 0, iedf_get_hyperperiod(0));

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	iedf_kal_mutex_signal(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    /* Start of protocol */
    iedf_kal_set_activation(IEDF_SCHEDULER, IEDF_WAIT_SCHEDULER_MS, 0);
}

/* Init packet reception from master */
static void iedf_receive_init(uint8_t update, uint8_t bitmask, uint8_t *mpdu)
{
	uint8_t init_counter, init_total;
	uint8_t pos = 2, counter, index;
	uint16_t num_nodes_next;
    uint32_t hyper_period;
    
	master_fails = 0;
    iedf_master_packet_counter_update(bitmask & 0x07); // last 3 bits
    
	init_counter = mpdu[0];
	init_total = mpdu[1]; 
    /* Number of nodes stored in the packet */
    counter = mpdu[2];

    iedf_DEBUG_serial_int3(init_counter, init_total, counter);
    iedf_DEBUG_serial("\r\n(init_counter, init_total, counter)");
	
    // Note: new nodes are not synchronized
    if (init_status == IEDF_STATUS_WAIT_SCHEDULE)
        next_init_expected = init_counter;
        
	else if (init_counter != next_init_expected) {
        iedf_DEBUG_serial_int3(init_counter, next_init_expected, 0);
        iedf_DEBUG_serial("\r\n(cur, exp, 0) *** ERROR *** Fail sync in next_init_expected");
        /* Disable recovery, scheduler and master election timer */
        iedf_recovery_cancel();
        iedf_scheduler_cancel(0);
        iedf_scheduler_cancel(1);
        init_status = IEDF_STATUS_REJECTED;
        iedf_DEBUG_serial("\r\nNode terminated");
        /* Node turned off */
        for(;;);
    }
	/* Update next init packet expected counter */
	next_init_expected++;
	if (next_init_expected == init_total)
		next_init_expected = 0;
	/* Next hyperperiod schedulation will be changed */
	if (update || init_status != IEDF_STATUS_INIT) {
		if (init_counter == 0) {
            /* Init train will be stored */
            train_stored = 1;
            /* Check if attendance test is feasible for a new node */
            if (activate_request)
                train_start_request = 1;
			/* First packet of init train: reset internal database */
            iedf_DEBUG_serial("\r\n First init packet");
			found_myself = 0;
			// TODO: varMastTotPack = &mpdu[3];
            /* Total nodes for next/next2 schedule */
			memcpy((uint16_t*)&num_nodes_next, &mpdu[6], 2);
			/* Check correct value interval (TODO) */
			if (num_nodes_next < 1 || num_nodes_next > IEDF_MAX_NODES) {
                iedf_DEBUG_serial("\r\n *** ERROR *** nodes of the master out\
								  of scale.");
            }
			// TODO: memcpy((uint16_t*)&block, &mpdu[4], 2);

            /* Check for train completion in current hyperperiod */
            if (mpdu[3] & 0x80) {
                master_update2 = 1;
                index = 2;
            } else {
                master_update = 1;
                index = 1;
            }

            /* Reset db */
            iedf_set_total_nodes(index, 0);

            /* Store new hyperperiod and total nodes */
            memcpy((uint32_t*)&hyper_period, &mpdu[8], 4);
            iedf_set_hyperperiod(index, hyper_period);
            iedf_DEBUG_serial_int3(num_nodes_next, hyper_period, index);
            iedf_DEBUG_serial("\r\n(num_nodes_next, hyper_period_next, NEXT/NEXT2)");
            /* Last byte read */
			pos = 11;
		} else {
            iedf_DEBUG_serial("\r\n Other init packet");
		}
        
        if (train_stored) {
            /* Update table */
            if (master_update2) {
                if (iedf_db_store(2, &mpdu[pos + 1], counter))
                    found_myself = 1;
            } else {
                if (iedf_db_store(1, &mpdu[pos + 1], counter))
                    found_myself = 1;
            }
        }

		/* Check if init train is complete */
		if (init_counter + 1 == init_total) {
			if (train_stored) {
                partial_schedule = 0;
                iedf_DEBUG_serial("\r\n!! Train complete");
                if (init_status == IEDF_STATUS_PENDING_REQUEST) {
                    if (train_start_request) {
                        if (found_myself) {
                            /* Request accepted */
                            iedf_change_status(IEDF_STATUS_GRANTED);
                            iedf_DEBUG_serial("\r\nREQUEST ACCEPTED");
                            //EE_led_7_on();
                        } else {
                            /* Request rejected */
                            iedf_change_status(IEDF_STATUS_REJECTED);
                            iedf_DEBUG_serial("\r\nREQUEST REJECTED");
                            return;
                        }
                    }
                } else if (init_status == IEDF_STATUS_WAIT_SCHEDULE) {
                    /* Node knows schedule info */
                    //EE_led_5_on();
                    iedf_change_status(IEDF_STATUS_WAIT_SCHEDULE_H);
                    iedf_DEBUG_serial("\r\nSchedule info downloaded");
                } else if (!found_myself) {
                    if (init_status == IEDF_STATUS_WAIT_STOP) {
                        /* Node correctly removed */
                        iedf_change_status(IEDF_STATUS_TERMINATED);
                        iedf_DEBUG_serial("\r\nNODE TERMINATED");
                        return;
                    } else if (init_status == IEDF_STATUS_INIT) {
                        /* Node no longer operable / tx problems */
                        iedf_change_status(IEDF_STATUS_REJECTED);
                        iedf_DEBUG_serial("\r\n*** ERROR *** TX problems");
                        return;
                    }
                }                
            } else
                iedf_DEBUG_serial("\r\n!! Unuseful packet train !!");
            train_stored = 0;
		}

	} else
        iedf_DEBUG_serial("\r\nUnuseful Init packet!!");
}

/* **************************************************************************
                                PUBLIC METHODS
   ************************************************************************** */

int8_t iedf_init(uint8_t ch, uint16_t addr, uint8_t n_bytes, uint32_t period_ms)
{
    uint8_t i;

    /* Preliminary check for iEDF sniffer */
    init_status = IEDF_STATUS_NOT_INIT;
    if (addr == 0 || n_bytes == 0 || period_ms == 0)
        iedf_change_status(IEDF_STATUS_SNIFFER);
   
    if (ch != 0) {
        /* Init debug timer */
        iedf_DEBUG_timer_set();
        /* Init uWireless libraries */
        iedf_debug_init();
        iedf_rand_init();
        if (iedf_kal_init(1000) < 0)
            return -IEDF_ERROR_INIT;
        /* Init phy level */
        if (iedf_phy_init(ch) < 0)
            return -IEDF_ERROR_INIT;
        /* Init IEDF task */
        iedf_kal_set_body(IEDF_SCHEDULER, iedf_task_scheduler);
        iedf_kal_set_body(IEDF_SCHEDULER_SET_RX_ON, iedf_task_set_rx_on);
        iedf_kal_set_body(IEDF_SCHEDULER_HOLETIME, iedf_task_scheduler);
        iedf_kal_set_body(IEDF_SCHEDULER_BLOCKING, iedf_task_scheduler);
        iedf_kal_set_body(IEDF_RECOVERY, iedf_task_recovery);
        iedf_kal_set_body(IEDF_MASTER_START, iedf_task_master_start);
    } else {
        /* Disable all timers */
        iedf_recovery_cancel();
        iedf_scheduler_cancel(0);
        iedf_scheduler_cancel(1);
        iedf_task_set_rx_on();
        MISS_ITER++;
        if (MISS_ITER >= 10) {
            MISS_UMAX++;
            MISS_ITER = 0;
        }
        if (MISS_UMAX >= 10) {
			/*
            EE_led_5_on();
            EE_led_6_on();
            EE_led_7_on();
			 */
            for(;;);
        }
    }
    
    /* Init global variables */
    iedf_set_my_nodeid(addr);
    if (IEDF_DEBUG_MISS_EXEC) {
        /* Get data from test database */
        miss_hyperperiod = store_miss_values(miss_test_db, MISS_UMAX, MISS_ITER);
        if (init_status != IEDF_STATUS_SNIFFER) {
            iedf_set_my_budget(miss_test_db[(addr - 1) * 3 + 1]);
            iedf_set_my_period(miss_test_db[(addr - 1) * 3 + 2]);
        }
    } else if (IEDF_DEBUG_USE_CONVERSION) {
        /* Set slotted budget */
        iedf_set_my_budget(ceiling(n_bytes, IEDF_MAC_MPDU_SIZE));
        /* Set slotted period */
        iedf_set_my_period(period_ms / IEDF_WAIT_SCHEDULER_MS);
        iedf_DEBUG_serial_int3(iedf_get_my_budget(), iedf_get_my_period(), 0);
        iedf_DEBUG_serial("\r\n [C,T,0]");
    } else {
        /* Budget-period info passed by high layer */
        iedf_set_my_budget(n_bytes);
        iedf_set_my_period(period_ms);
        iedf_DEBUG_serial_int3(iedf_get_my_budget(), iedf_get_my_period(), 0);
        iedf_DEBUG_serial("\r\n [C,T,0] not converted");
    }
    
    my_params[0] = iedf_get_my_nodeid();
    my_params[1] = iedf_get_my_budget();
    my_params[2] = iedf_get_my_period();

    master_address = 0;
    is_master = 0;
    node_turn_stored = 0;
    node_turn_activity = IEDF_ACTIVITY_NONE;
    master_packet_counter = 0;
    master_update = 0;
    master_update2 = 0;
    master_fails = 0;
    disable_data_tx = 0;
    next_init_expected = 0;
    master_init_train_update = 0;
    master_init_mpdu_len = 0;
    master_init_total = 0;
    master_init_counter = 0;
	master_init_nodes_left = 0;
	master_init_tx = 0;
    master_init_in_period = 0; 
    partial_schedule = 1;
	found_myself = 0;
    train_stored = 0;
    new_master = 0;
    new_master_sync = 0;
    activate_request = 0;
    train_start_request = 0;
    holeslot_enabled = 0;
    recovery_timeout_ms = 0;

    // ***TODO*** Not implemented
    memset(&mpdu_routing[0], 0xFF, IEDF_MAC_MPDU_SIZE);

    /* Init data structure */
    iedf_data_clean();
    
    if (!IEDF_DEBUG_JOIN_EXEC && ch != 0) {
        iedf_DEBUG_serial_int(addr);
        iedf_DEBUG_serial("\r\n <--- Node correctly initialized");
    }
    
    if (init_status == IEDF_STATUS_SNIFFER) {
        /* Sniffer mode */
        /*EE_leds_off();
        switch (MISS_ITER) {
            case 0:
                EE_led_0_on();
                break;
            case 1:
                EE_led_1_on();
                break;
            case 2:
                EE_led_2_on();
                break;
            case 3:
                EE_led_3_on();
                break;
            case 4:
                EE_led_4_on();
                break;
            case 5:
                EE_led_5_on();
                break;
            case 6:
                EE_led_6_on();
                break;
            case 7:
                EE_led_7_on();
                break;
        }*/
        miss_disable_sniffer = 0;
        miss_expected = 1;
        miss_wait_for_sync = 1;
        miss_wait_for_sync2 = 1;
        miss_temp_count = 0;
        miss_temp_final = (uint32_t)IEDF_DEBUG_MISS_SIMULATION_SEC * 1000 / IEDF_WAIT_SCHEDULER_MS;
        memset(miss_db, 0, IEDF_MAX_NODES * 2);
        memset(miss_test_budget, 0, IEDF_MAX_NODES * 2);
		
        for (i = 0; i < miss_nodes; i++)
            miss_test_budget[i] = miss_test_db[i * 3 + 1];
		
    } else if (IEDF_DEBUG_MISS_EXEC) {
        /* Deadline miss test mode */
        master_address = 1;
        iedf_change_status(IEDF_STATUS_INIT);
        master_update = 1;
        iedf_db_store(2, (uint8_t*)&miss_test_db[0], miss_nodes);
        iedf_set_hyperperiod(2, miss_hyperperiod);
        iedf_db_copy(1, 2);
        iedf_scheduler_update(1);
        internal_state = 0;
        if (addr == master_address) {
            is_master = 1;
            node_turn_activity = IEDF_ACTIVITY_MASTER_TX;
            recovery_timeout_ms = recovery_timeout1_ms;
            iedf_master_build_mpdu_init((uint8_t*)&mpdu_init[0]);
            iedf_master_data_failure_reset();
            /* Start of protocol */
            iedf_kal_set_activation(IEDF_SCHEDULER, IEDF_WAIT_SCHEDULER_MS, 0);
        }
    } else {
        /* Node is waiting for schedulation (CSMA to join) */
        iedf_change_status(IEDF_STATUS_WAIT_SCHEDULE);
        /* Master election timeout */
        iedf_kal_set_activation(IEDF_MASTER_START, IEDF_INIT_WAIT_MS, 0);
    }
	return IEDF_OK;
}

int8_t iedf_stop(void)
{
	if (init_status != IEDF_STATUS_INIT)
        return -IEDF_ERROR_INIT;
    disable_data_tx = 1;
    return IEDF_OK;
}

void iedf_phy2mac_cb(uint8_t psduLen, uint8_t *psdu, uint8_t ppduLQ)
{
    uint16_t post_addr, dst_addr, src_addr;
    uint16_t fw_budget;
    uint8_t recovery_received = 0;
    uint8_t bitmask, packet_type, mpdu_len;
    uint8_t mpdu[IEDF_MAC_MPDU_SIZE];
    uint8_t master_change;

    char *msg1 = "";
    char *msg2 = "";

    if (init_status != IEDF_STATUS_SNIFFER) {
        /*EE_led_4_on();
        EE_led_0_off();
        EE_led_1_off();*/
    }

    /* Check reception status */
    if (psduLen != IEDF_MAC_FRAME_SIZE &&
    psduLen != IEDF_MAC_FRAME_RECOVERY_SIZE) {
        if (init_status == IEDF_STATUS_SNIFFER)
            iedf_notify(IEDF_CORRUPTED_PACKET, NULL, 0, 0);
        return;
    }

    if (init_status != IEDF_STATUS_SNIFFER) {
        /*EE_led_4_off();
        EE_led_5_on();*/
        /* Default behavior: sleep mode */
        if (IEDF_DEBUG_USE_ENERGY && !is_master) {
            iedf_phy_set_status(IEDF_PHY_FORCE_TRX_OFF);
        }
    }
    
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	iedf_kal_mutex_wait(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    // ***TODO*** CRC not implemented

    /* Disable recovery, scheduler and master election timer */
    iedf_recovery_cancel();
    iedf_scheduler_cancel(0);
    iedf_scheduler_cancel(1);
    if (init_status == IEDF_STATUS_WAIT_SCHEDULE) {
        iedf_kal_cancel_activation(IEDF_MASTER_START);
        iedf_DEBUG_serial("\r\nMaster detected. Waiting for schedule info");
    } else if (init_status == IEDF_STATUS_REJECTED ||
    init_status == IEDF_STATUS_TERMINATED) {
        iedf_DEBUG_serial("\r\nNode rejected or terminated");
        /* Node turned off */
        //EE_leds_on();
        for(;;);
    }

    memcpy((uint16_t*)&dst_addr, &psdu[0], 2);          /* destination */
    memcpy((uint16_t*)&src_addr, &psdu[2], 2);          /* source */
    if (src_addr == 0xBBBB) {
        /* Test sync */
        iedf_notify(IEDF_TEST_SYNC, NULL, 0, 0);
        iedf_init(0, my_params[0], my_params[1], my_params[2]);
        iedf_kal_mutex_signal(IEDF_DATA_MUTEX);
        if (init_status != IEDF_STATUS_SNIFFER) {
            //EE_led_5_off();
		}
        return;
    }
    bitmask = psdu[4];                                  /* bitmask */
    memcpy((uint16_t*)&fw_budget, &psdu[5], 2);         /* fw_budget */
    memcpy((uint32_t*)&internal_state, &psdu[7], 4);    /* seqnum */
    mpdu_len = psdu[11];                                /* mpdulen */
    memcpy(&mpdu[0], &psdu[12], mpdu_len);              /* mpdu */

    /* iEDF sniffer */
    if (init_status == IEDF_STATUS_SNIFFER) {
        iedf_test_miss(src_addr, (bitmask >> 4) == IEDF_PACKET_RECOVERY);
        iedf_kal_mutex_signal(IEDF_DATA_MUTEX);
        return;
    }
                
    /* Note: master must transmit init packet in last hyperperiod slot */
    if (internal_state == 1 && init_status <= IEDF_STATUS_WAIT_SCHEDULE_H) {
        /* Update for not init nodes */
        iedf_hyperperiod_begin();
    }
    
    /* New master has been elected */
    master_change = bitmask & 0x08;
    
    /* Get iEDF packet type */
    packet_type = bitmask >> 4;
    // TODO: ptc = (bitmask & 0x01)
    
    if (packet_type == IEDF_PACKET_RECOVERY) {
        /* *** Recovery frame *** */
        master_address = src_addr;
        recovery_received = 1;
    } else if (packet_type == IEDF_PACKET_RECOVERY_MASTER) {
        /* *** Recovery Master frame *** */
        recovery_received = 1;
        iedf_master_packet_counter_update(bitmask & 0x07);
    } else if (packet_type == IEDF_PACKET_RECOVERY_RESERVED) {
        /* *** Recovery CSMA frame in reserved slot *** */
        master_address = src_addr;
        recovery_received = 1;
        master_fails = 0;
        iedf_master_packet_counter_update(bitmask & 0x07);
    }
    
    /* Scheduler / Recovery timer activation */
    holeslot_enabled = 0;
    post_addr = (recovery_received == 1) ? src_addr : IEDF_SLOT_FREE;
    iedf_scheduler_set(post_addr);

    /* Prepare next timeslot */
    msg2 = iedf_scheduler_manage(recovery_received);
    
    /* Check if a new master has been elected */
    if (master_change) {
        iedf_DEBUG_serial("\r\n\r\n EXP = 0 \r\n");
        next_init_expected = 0;
        master_update = 0;
        master_update2 = 0;
        iedf_db_copy(1, 0);
        iedf_db_copy(2, 0);
    }
    
    if (is_master)
        iedf_notify(IEDF_TIMESLOT, NULL, 0, (internal_state == 0) ?
        iedf_get_hyperperiod(0) - 1 : internal_state - 1);
        
    iedf_DEBUG_serial_int((internal_state == 0) ? 333 : internal_state - 1);
    if (internal_state == 0)
        iedf_DEBUG_serial("\r\n@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=@=");
    else
        iedf_DEBUG_serial(" ================================");
    iedf_DEBUG_serial_int(internal_state);
    iedf_DEBUG_serial("\r\nReceived!");
    iedf_DEBUG_serial(msg1);
    iedf_DEBUG_serial(msg2);

    if (!is_master && packet_type <= IEDF_PACKET_INIT_UPDATE) {
        /* *** Init frame *** */
        iedf_DEBUG_serial("\r\nRECV init packet");
        master_address = src_addr;
        if (!IEDF_DEBUG_MISS_EXEC)
            iedf_receive_init(packet_type != IEDF_PACKET_INIT, bitmask, &mpdu[0]);
    } else if (packet_type == IEDF_PACKET_DATA && init_status == IEDF_STATUS_INIT) {
        /* *** Data frame *** */
        if (is_master) {
            /* Check node's presence in failure data structure */
            iedf_master_data_failure_remove(src_addr);
        }
        if (iedf_notify != NULL)
            iedf_notify(IEDF_DATA_RX, mpdu, mpdu_len, src_addr);
    } else if (is_master && iedf_get_pending_requests() < IEDF_MAX_REQUESTS && (
    packet_type == IEDF_PACKET_REQUEST || 
    packet_type == IEDF_PACKET_REQUEST_RESERVED ||
    packet_type == IEDF_PACKET_STOP)) {
        /* *** Join/Stop request frame *** */
        iedf_DEBUG_serial("\r\nRECV Init change");        
        /* Check if node has already performed request and upgrade request db */
        iedf_data_requests_store(mpdu, packet_type == IEDF_PACKET_STOP);
    } else if (packet_type == IEDF_PACKET_ROUTING) {
        /* *** Routing frame *** */
        master_address = src_addr;
        master_fails = 0;
        iedf_master_packet_counter_update(bitmask & 0x07);
    }
    
    if (packet_type == IEDF_PACKET_REQUEST_RESERVED) {
        iedf_master_packet_counter_update(bitmask & 0x07);
    }

    /* Check for additional operations */
    iedf_scheduler_next(node_turn_activity == IEDF_ACTIVITY_MASTER_TX);

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	iedf_kal_mutex_signal(IEDF_DATA_MUTEX);
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    //EE_led_5_off();
}

void iedf_link_notify_cb(void (*func) (uint8_t, uint8_t*, uint8_t, uint16_t))
{
	iedf_notify = func;
}

int8_t iedf_packet_store(uint8_t *data, uint8_t len)
{
    /* Lower layer storage */
    if (data == NULL || len == 0 || iedf_buffer_put(data, len) == 0)
        return -IEDF_ERROR_STORE_DATA;
    return IEDF_OK;
}

uint8_t iedf_DEBUG_check_channel(void) {
    return iedf_phy_get_cca();
}

enum iedf_init_status_type iedf_get_status(void)
{
    return init_status;
}

int8_t iedf_is_master(void)
{
    return is_master;
}

uint16_t iedf_get_master(void)
{
    return master_address;
}

void iedf_test_sync()
{
    uint8_t test_sync_packet[IEDF_MAC_FRAME_RECOVERY_SIZE];

    memset(&test_sync_packet[0], 0xBB, IEDF_MAC_FRAME_RECOVERY_SIZE);
    iedf_phy_set_status(IEDF_PHY_TX_ON);
    iedf_phy_send(&test_sync_packet[0], IEDF_MAC_FRAME_RECOVERY_SIZE);
    iedf_phy_set_status(IEDF_PHY_RX_ON);
    iedf_notify(IEDF_TEST_SYNC, NULL, 0, 0);
    iedf_init(0, my_params[0], my_params[1], my_params[2]);
}
