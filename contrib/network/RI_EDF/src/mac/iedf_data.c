/**
 * @file iedf_data.c
 * @brief Implicit-EDF Data structure (Implementation)
 * @author Simone Madeo
 * @author Gianluca Franchino 2012
 * @version 0.1
 * @date 2011-10-10
 */

#include "mac/iedf_data.h"

const uint16_t IEDF_DB_INDEX2 = IEDF_MAX_NODES * 2;

/* IEDF Node data structure */
struct iedf_node_t
{
    uint16_t node_id;
    uint16_t budget;
    uint16_t period;
};

/* IEDF Schedule data structure */
struct iedf_schedule_t
{
    uint16_t total_nodes;
    uint32_t total_budget;
    uint32_t hyper_period;
};

/* Node's failure data structure */
struct failure_node_t
{
    uint16_t node_id;
    uint8_t num_fails;
};

/* Scheduling data structure */
static struct iedf_node_t db[3 * IEDF_MAX_NODES];

/* Stored scheduling data structure 
 * 0: current database
 * 1: next hyperperiod database
 * 2: additional database
 * */
static struct iedf_schedule_t schedule[3];

/* Nodes' budget data structure for current period */
static uint32_t remaining_budget[IEDF_MAX_NODES];

/* Nodes' fail counter */
static uint8_t num_nodes_failed;

/* Transmission failure data structure */
static struct failure_node_t data_failure[IEDF_MAX_NODES];

/* Join request buffer (Master use only) */
static struct iedf_node_t requests[IEDF_MAX_REQUESTS];

/* Master pending requests counter */
static uint8_t pending_requests;

/* Data buffer */
static uint8_t buffer[IEDF_BUFFER_SIZE];

/* Buffer slot pointers */
static uint8_t last_slot_read;
static uint8_t last_slot_write;
static uint8_t slot_count;

/* Node general scheduling data */
static uint16_t my_address;
static uint16_t my_budget;
static uint16_t my_period;


/* **************************************************************************
                                PRIVATE METHODS
   ************************************************************************** */

/* Return the closest EDF deadline (relative to current time t and a bound) */
static uint32_t iedf_get_next_deadline(uint32_t t, uint16_t period,
uint32_t hyper_bound)
{
    uint32_t tmp_deadline;
    uint32_t min_deadline = hyper_bound;
    uint32_t i;
    uint16_t tmp_period;
    uint16_t num_nodes = schedule[2].total_nodes;
    
    /* Optimization: master's deadine */
    if (t % IEDF_MASTER_BLOCKING_PERIOD == 0)
        return t + 1;
    for (i = 0; i <= num_nodes + 1; i++) {
        if (i == 0) {
            /* Master's deadline */
            tmp_deadline = ((t - 1) / IEDF_MASTER_BLOCKING_PERIOD + 1) *
                IEDF_MASTER_BLOCKING_PERIOD + 1;
        } else if (i == num_nodes + 1) {
            /* New node's deadline */
            tmp_deadline = (t / period + 1) * period;
        } else {
            /* Others nodes' deadline */
            tmp_period = db[IEDF_DB_INDEX2 + i - 1].period;
            tmp_deadline = (t / tmp_period + 1) * tmp_period;
        }
        if (tmp_deadline < min_deadline)
            min_deadline = tmp_deadline;
    }
        
    return min_deadline;    
}

/* Calculate maximum execution time requirement in a contiguous interval of
 * length t */
static uint32_t iedf_get_demand(uint32_t t, uint16_t budget, uint16_t period)
{
    int32_t cur_period;
    int32_t partial;
    int32_t cur_t = t;
    uint16_t cur_budget;
    uint16_t i;
    uint16_t num_nodes = schedule[2].total_nodes;
    uint32_t demand = 0;

    /* Check integer overflow */
    if (t > 0xFFFFFFFF / 2 - 1)
        return 0xFFFFFFFF;

    for (i = 0; i <= num_nodes + 1; i++) {
        if (i == 0) {
            partial = 1 + get_floor(cur_t - 1, IEDF_MASTER_BLOCKING_PERIOD);
            if (partial > 0) {
                demand = partial;
                //iedf_DEBUG_serial_int3(i, partial, demand);
                //iedf_DEBUG_serial(" demand");
            }
        } else {
            if (i != num_nodes + 1) {
                cur_period = db[IEDF_DB_INDEX2 + i - 1].period;
                cur_budget = db[IEDF_DB_INDEX2 + i - 1].budget;
            } else {
                cur_period = period;
                cur_budget = budget;
            }
            partial = 1 + get_floor(cur_t - cur_period, cur_period);
            if (partial > 0) {
                demand += partial * cur_budget;
                //iedf_DEBUG_serial_int3(i, partial, demand);
                //iedf_DEBUG_serial(" demand");
            }
        }
    }
    
    return demand;    
}

/* Calculate maximum absolute deadline according to QPA algorithm */
static uint32_t iedf_get_dmax(uint32_t t, uint32_t period)
{
    uint32_t Dj;
    uint32_t dj = 0;
    uint32_t dmax = 0;
    uint16_t j;
    uint16_t num_nodes = schedule[2].total_nodes;
    
    for (j = 0; j <= num_nodes + 1; j++) {
        if (j == 0)
            Dj = 1;
        else if (j != num_nodes + 1)
            Dj = db[IEDF_DB_INDEX2 + j - 1].period;
        else
            Dj = period;
        if (Dj < t) {
            dj = ((t - Dj) / Dj) * Dj + Dj;
            if (dj == t) dj = dj - Dj;
            if (dj > dmax) dmax = dj;
        }
        
    }
    
    //iedf_DEBUG_serial_int3(t, dmax, 111);
    //iedf_DEBUG_serial(" dmax");

    return dmax;    
}


/* **************************************************************************
                                PUBLIC METHODS
   ************************************************************************** */

/* Get my node-id */
uint16_t iedf_get_my_nodeid()
{
    return my_address;
}

/* Get my budget */
uint16_t iedf_get_my_budget()
{
    return my_budget;
}

/* Get my period */
uint16_t iedf_get_my_period()
{
    return my_period;
}

/* Get pending requests counter */
uint8_t iedf_get_pending_requests()
{
    return pending_requests;
}

/* Set my node-id */
void iedf_set_my_nodeid(uint16_t value)
{
    my_address = value;
}

/* Set my budget */
void iedf_set_my_budget(uint16_t value)
{
    my_budget = value;
}

/* Set my period */
void iedf_set_my_period(uint16_t value)
{
    my_period = value;
}

/* Retrieve total nodes info */
uint16_t iedf_get_total_nodes(uint8_t index)
{
    return schedule[index].total_nodes;
}

/* Retrieve total budget info */
uint32_t iedf_get_total_budget(uint8_t index)
{
    return schedule[index].total_budget;
}

/* Retrieve hyperperiod info */
uint32_t iedf_get_hyperperiod(uint8_t index)
{
    return schedule[index].hyper_period;
}

/* Store total nodes info */
void iedf_set_total_nodes(uint8_t index, uint16_t value)
{
    schedule[index].total_nodes = value;
}

/* Store hyperperiod info */
void iedf_set_hyperperiod(uint8_t index, uint32_t value)
{
    schedule[index].hyper_period = value;
}

/* Check pending requests */
uint8_t iedf_data_requests_flush()
{
    uint8_t schedule_changed = 0;
    
    while (pending_requests) {
        iedf_DEBUG_serial(" +");
        schedule_changed += iedf_data_join(
            requests[pending_requests - 1].node_id,
            requests[pending_requests - 1].budget,
            requests[pending_requests - 1].period, NULL);
        pending_requests--;
    }
    
    return schedule_changed;
}

/* Store pending requests */
void iedf_data_requests_store(uint8_t *packet, uint8_t stop_request)      
{
    uint16_t request_id;
    uint8_t check_request = 0, i;
    
    memcpy((uint16_t*)&request_id, &packet[0], 2);
    
    /* Check if node has already performed request */
    for (i = 0; i < pending_requests && !check_request; i++)
        if (requests[i].node_id == request_id)
            check_request = 1;
    if (!check_request) {
        /* Upgrade request database */
        if (stop_request)
            memset(&packet[2], 0, 2);
        memcpy(&requests[pending_requests].node_id, &packet[0], 2);
        memcpy(&requests[pending_requests].budget, &packet[2], 2);
        memcpy(&requests[pending_requests].period, &packet[4], 2);
        pending_requests++;            
    }    
}

/* Send a schedule database to serial port */
void iedf_DEBUG_print_db(uint8_t index, char* str)
{
    uint16_t i;
    
    iedf_DEBUG_serial("\r\n----- Database: ");
    iedf_DEBUG_serial(str);
    for (i = 0; i < schedule[index].total_nodes; i++) {
        iedf_DEBUG_serial_int3(db[IEDF_MAX_NODES * index + i].node_id,
            db[IEDF_MAX_NODES * index + i].budget,
            db[IEDF_MAX_NODES * index + i].period);
        iedf_DEBUG_serial(" [Database]");
    }
    iedf_DEBUG_serial("\r\n-----------------------------");
}

/* Send failure database to serial port */
void iedf_DEBUG_print_failure()
{
    uint8_t i;
    
    iedf_DEBUG_serial("\r\n@@@@@@@@@@@@@@@@@@@@@@@@");
    for (i = 0; i < num_nodes_failed; i++)
        iedf_DEBUG_serial_int3(i, data_failure[i].node_id,
            data_failure[i].num_fails);
    iedf_DEBUG_serial_int(pending_requests);
    iedf_DEBUG_serial(" pending requests");
    iedf_DEBUG_serial("\r\n@@@@@@@@@@@@@@@@@@@@@@@@");
}

/* Copy a database into another database. 
 * Return 1 if node can perform recovery. */
uint8_t iedf_db_copy(uint8_t i_dst, uint8_t i_src)
{
    uint16_t i;
    uint16_t index_src = IEDF_MAX_NODES * i_src;
    uint16_t index_dst = IEDF_MAX_NODES * i_dst;
    uint16_t num_nodes = schedule[i_src].total_nodes;
    uint16_t tmp_node;
    uint16_t recovery_address = 0xFFFF;
    
    /* Parameters */
    schedule[i_dst].total_nodes = num_nodes;
    schedule[i_dst].total_budget = schedule[i_src].total_budget;
    schedule[i_dst].hyper_period = schedule[i_src].hyper_period;

    /* Database */
    for (i = 0; i < num_nodes; i++) {
        db[index_dst + i].node_id = db[index_src + i].node_id;
        db[index_dst + i].budget = db[index_src + i].budget;
        db[index_dst + i].period = db[index_src + i].period;
    }
    /* Refill budget & prepare recovery nodes */
    if (i_dst == 0) {
        for (i = 0; i < num_nodes; i++) {
            remaining_budget[i] = db[index_src + i].budget;
            tmp_node = db[index_src + i].node_id;
            if (tmp_node < recovery_address && tmp_node != iedf_get_master())
                recovery_address = tmp_node;
        }
        /* Check for personal recovery */
        if (my_address == recovery_address)
            return 1;
    }

    return 0;
}

/* Store a new entry into a database. Return 1 if node is in database */
uint8_t iedf_db_store(uint8_t i_dst, uint8_t *mpdu, uint8_t counter)
{
    uint16_t index_dst = IEDF_MAX_NODES * i_dst;
    uint8_t ret = 0;
	uint8_t i;
    uint8_t nodes_stored = schedule[i_dst].total_nodes;
    
    for (i = 0; i < counter; i++) {
        memcpy(&db[index_dst + nodes_stored].node_id, &mpdu[i * 6], 2);
        memcpy(&db[index_dst + nodes_stored].budget, &mpdu[i * 6 + 2], 2);
        memcpy(&db[index_dst + nodes_stored].period, &mpdu[i * 6 + 4], 2);
        if (db[index_dst + nodes_stored].node_id == my_address) {
            ret = 1;
            iedf_DEBUG_serial("\r\nFOUND MYSELF");
        }
        
        iedf_DEBUG_serial_int3(db[index_dst + nodes_stored].node_id,
            db[index_dst + nodes_stored].budget,
            db[index_dst + nodes_stored].period);
        iedf_DEBUG_serial(" [RCV DATA]");
        
        nodes_stored++;
    }
    
    schedule[i_dst].total_nodes = nodes_stored;
    
    return ret;
}

/* Reset failed nodes' data structure */
void iedf_master_data_failure_reset()
{
    uint8_t i;
    
    for (i = 0; i < IEDF_MAX_NODES; i++) {
        data_failure[i].node_id = 0;
        data_failure[i].num_fails = 0;
    }
}

/* Add a failed node into data structure */
void iedf_master_data_failure_add(uint16_t address, uint8_t force_remove)
{
    uint8_t i;
    uint8_t found = 0;

    for (i = 0; i < num_nodes_failed && !found; i++)
        if (data_failure[i].node_id == address) {
            found = 1;
            if (data_failure[i].num_fails < IEDF_MAX_RECOVERY_TIMES) {
                /* Node's failure counter increased */
                data_failure[i].num_fails++;
            } else if (pending_requests < IEDF_MAX_REQUESTS &&
            data_failure[i].num_fails == IEDF_MAX_RECOVERY_TIMES) {
                /* Prepare to remove failed node from next schedulation */
                iedf_DEBUG_serial_int(address);
                iedf_DEBUG_serial("\r\nAdded to requests for removing");
                data_failure[i].num_fails = IEDF_MAX_RECOVERY_TIMES + 1;
                requests[pending_requests].node_id = address;
                requests[pending_requests].budget = 0;
                requests[pending_requests].period = 0;
                pending_requests++;
            } else if (data_failure[i].num_fails == IEDF_MAX_RECOVERY_TIMES + 1 
            && force_remove) {
                /* Node removed from next schedulation */
                iedf_DEBUG_serial_int(address);
                iedf_DEBUG_serial("\r\nNode removed from next schedulation");
                data_failure[i].num_fails++;
            }
        }
    
    if (!found && !force_remove && num_nodes_failed < IEDF_MAX_NODES) {
        /* New entry */
        data_failure[num_nodes_failed].node_id = address;
        data_failure[num_nodes_failed].num_fails = 1;
        num_nodes_failed++;
    }
}

/* Remove a failed node from data structure */
void iedf_master_data_failure_remove(uint16_t address)
{
    uint8_t i;
    uint8_t found = 0;
    
    if (address == 0 && num_nodes_failed > 0) {
        iedf_DEBUG_serial_int(num_nodes_failed);
        iedf_DEBUG_serial("\r\nInside nodes_failed");
        /* Clean old entries */
        for (i = num_nodes_failed - 1; ; i--) {
            iedf_DEBUG_serial_int(i);
            //iedf_DEBUG_serial(" sto analizzando l'entry i");
            if (data_failure[i].num_fails == IEDF_MAX_RECOVERY_TIMES + 2) {
                iedf_DEBUG_serial_int3(i, data_failure[i].node_id, data_failure[i].num_fails);
                iedf_DEBUG_serial("\r\n[i,node,numfails] sto rimuovendo dalla struttura");
                data_failure[i].node_id =
                    data_failure[num_nodes_failed - 1].node_id;
                data_failure[i].num_fails =
                    data_failure[num_nodes_failed - 1].num_fails;
                num_nodes_failed--;
            }
            if (i == 0)
                return;
        }
    } else {
        /* Remove a single entry */
        for (i = 0; i < num_nodes_failed && !found; i++)
            if (data_failure[i].node_id == address) {
                found = 1;
                data_failure[i].node_id =
                    data_failure[num_nodes_failed - 1].node_id;
                data_failure[i].num_fails =
                    data_failure[num_nodes_failed - 1].num_fails;
                num_nodes_failed--;
            }
    }
}

/* Clear iEDF data structure */
void iedf_data_clean()
{
    uint8_t i;
    uint16_t db_size = 3 * IEDF_MAX_NODES;
    
    num_nodes_failed = 0;
    last_slot_write = IEDF_MAX_SLOTS - 1;
    last_slot_read = IEDF_MAX_SLOTS - 1;
    slot_count = 0;
    pending_requests = 0;
    
    for (i = 0; i < IEDF_BUFFER_SIZE; i++)
        buffer[i] = 0;

    for (i = 0; i < 3; i++) {
        schedule[i].total_nodes = 0;
        schedule[i].total_budget = 0;
        schedule[i].hyper_period = 0;
    }
    
    for (i = 0; i < db_size; i++) {
        db[i].node_id = 0;
        db[i].budget = 0;
        db[i].period = 0;
    }
}

/* Store data into buffer */
uint8_t iedf_buffer_put(uint8_t *data, uint8_t len)
{
    uint8_t data_to_write;
    uint8_t write_pointer; 
    
    if (slot_count == IEDF_MAX_SLOTS)
        return 0;
    
    data_to_write = (len > IEDF_BUFFER_SIZE) ? IEDF_BUFFER_SIZE : len;
    write_pointer = (last_slot_write == IEDF_MAX_SLOTS - 1) ? 0 : 
        (last_slot_write + 1) * IEDF_MAC_MPDU_SIZE;
    
    memset(&buffer[write_pointer], 0x00, IEDF_MAC_MPDU_SIZE);
    memcpy(&buffer[write_pointer], data, data_to_write);

    slot_count++;
    last_slot_write = (last_slot_write + 1) % IEDF_MAX_SLOTS;
    
    iedf_DEBUG_serial_int3(len, data_to_write, write_pointer);
    iedf_DEBUG_serial("\r\nlen,datatow,writepointer");
    iedf_DEBUG_serial_int3(slot_count, last_slot_write, 0);
    iedf_DEBUG_serial("\r\nslt_count, lst_slt_wrt, 0");
    
    return data_to_write;
}

/* Load data from buffer */
uint8_t* iedf_buffer_get()
{
    if (slot_count == 0)
        return NULL;

    last_slot_read = (last_slot_read + 1) % IEDF_MAX_SLOTS;
    slot_count--;
    
    return &buffer[last_slot_read * IEDF_MAC_MPDU_SIZE];
}

/* Storage db info into packet */
void iedf_db_package(uint8_t *packet, uint8_t index, uint8_t offset)
{
    uint8_t level = IEDF_MAX_NODES * index;
    memcpy(&packet[0], (uint16_t*)&db[level + offset].node_id, 2);
    memcpy(&packet[2], (uint16_t*)&db[level + offset].budget, 2);
    memcpy(&packet[4], (uint16_t*)&db[level + offset].period, 2);
}

/* Return the next scheduled node id according to EDF algorithm. */
uint16_t iedf_data_turn(uint32_t t)
{
    uint32_t hyper_period = schedule[0].hyper_period;
    uint16_t num_nodes = schedule[0].total_nodes;
    
    uint16_t elected_node = IEDF_SLOT_FREE;
    uint32_t next_deadline = hyper_period;
    uint32_t prev_deadline = hyper_period;
    uint16_t i;
    uint8_t pos = 0;
    uint32_t tmp_period;
    uint32_t tmp_nxt_dl;
    uint32_t tmp_prv_dl;

    uint32_t time1, time2;

    time1 = TMR2;
    
    /* Returns if node is not initialized yet */
    if (num_nodes == 0) {
        return 0;
    }

    if (t >= hyper_period)
        t = 0;

    /* Refill budget if necessary */
    for (i = 0; i < num_nodes; i++)
        if (t % db[i].period == 0) {
            remaining_budget[i] = db[i].budget;
        }

    if (t % IEDF_MASTER_BLOCKING_PERIOD == 0) {
        /* Master */
        elected_node = 0;
    } else {
        for (i = 0; i < num_nodes; i++) {
            tmp_period = db[i].period;
            tmp_nxt_dl = (t / tmp_period + 1) * tmp_period;
            tmp_prv_dl = tmp_nxt_dl - tmp_period;
            if (remaining_budget[i] > 0 && (tmp_nxt_dl < next_deadline || 
            (tmp_nxt_dl == next_deadline && tmp_prv_dl < prev_deadline))) {
                elected_node = db[i].node_id;
                next_deadline = tmp_nxt_dl;
                prev_deadline = tmp_prv_dl;                
                pos = i;
            }
        }
        if (elected_node != IEDF_SLOT_FREE) {
            remaining_budget[pos]--;
        }
    }

    /* Execution time */ 
    time2 = TMR2;
    //iedf_DEBUG_serial_int(iedf_DEBUG_time(time1, time2));
    
    return elected_node;
}

/* Calculate Lb value in QPA algorithm */
/*static uint32_t iedf_get_lb()
{
    uint32_t w0 = 1;
    uint32_t w1 = 0;
    uint16_t i;
    uint16_t num_nodes = schedule[2].total_nodes;
    
    for (i = 0; i < num_nodes; i++)
        w0 += db_next2[i].budget;
    
    for (i = 0; i <= num_nodes + 1; i++) {
        if (i == 0)
            w1 = ceiling(w0, IEDF_MASTER_BLOCKING_PERIOD);
        else
            w1 += ceiling(w0, db_next2[i-1].period) * db_next2[i-1].budget;
    }

    while (w1 != w0) {
        w0 = w1;
        for (i = 0; i <= num_nodes + 1; i++) {
            if (i == 0)
                w1 = ceiling(w0, IEDF_MASTER_BLOCKING_PERIOD);
            else
                w1 += ceiling(w0, db_next2[i-1].period) * db_next2[i-1].budget;
        }
    }
    
    return w1;    
}*/

/* EDF Algorithm. Return 1 if node has been accepted (master use only) */
/* If budget equals 0, node is removed from schedulation */
uint8_t iedf_data_join(uint16_t node_id, uint16_t budget, uint16_t period,
uint16_t *timing)
{
    /* DB data structure */
    uint16_t num_nodes2 = schedule[2].total_nodes;
    uint32_t hyper_period2 = schedule[2].hyper_period;
    uint32_t total_budget2 = schedule[2].total_budget;
    /* Timer variables */
    uint16_t debugtimer1;
    uint16_t debugtimer2;
    /* Other variables */
    uint16_t i;
    uint16_t to_remove = IEDF_MAX_NODES;
    uint32_t Lstar = 0, l = 0, need = 0; 
    uint32_t old_tmp_hyper, tmp_hyper = 0;
    uint32_t tmp_total = 0;
    
    if (budget == 0) {
        /* Node must be removed */
        iedf_DEBUG_serial_int(node_id);
        iedf_DEBUG_serial("\r\n<--------------- To remove!");
        for (i = 0; i < num_nodes2; i++) {
            if (node_id == db[IEDF_DB_INDEX2 + i].node_id) {
                to_remove = i;
            } else {
                /* Calculate new hyperperiod and total budget */
                if (tmp_hyper == 0) {
                    tmp_hyper = lcm(IEDF_MASTER_BLOCKING_PERIOD, 
                        db[IEDF_DB_INDEX2 + i].period);
                    tmp_total = tmp_hyper / db[IEDF_DB_INDEX2 + i].period *
                        db[IEDF_DB_INDEX2 + i].budget + tmp_hyper
                        / IEDF_MASTER_BLOCKING_PERIOD;
                } else {
                    old_tmp_hyper = tmp_hyper;
                    tmp_hyper = lcm(tmp_hyper, db[IEDF_DB_INDEX2 + i].period);
                    tmp_total = tmp_hyper / db[IEDF_DB_INDEX2 + i].period * 
                        db[IEDF_DB_INDEX2 + i].budget + tmp_hyper /
                        old_tmp_hyper * tmp_total;
                }
            }
        }
        /* Node not found */
        if (to_remove == IEDF_MAX_NODES)
            return 0;
        /* Update database */
        iedf_master_data_failure_add(node_id, 1);
        schedule[2].total_budget = tmp_total;
        schedule[2].hyper_period = tmp_hyper;
        num_nodes2--;
        if (to_remove != num_nodes2) {
            db[IEDF_DB_INDEX2 + to_remove].node_id =
                db[IEDF_DB_INDEX2 + num_nodes2].node_id;
            db[IEDF_DB_INDEX2 + to_remove].budget =
                db[IEDF_DB_INDEX2 + num_nodes2].budget;
            db[IEDF_DB_INDEX2 + to_remove].period =
                db[IEDF_DB_INDEX2 + num_nodes2].period;
        }
        schedule[2].total_nodes = num_nodes2;

        iedf_DEBUG_serial_int3(schedule[2].total_nodes, schedule[2].total_budget, schedule[2].hyper_period);
        iedf_DEBUG_serial("\r\nDB2 (num, budg, hyper)");
    }
    
    else {
        /* Node must be added */
        debugtimer1 = TMR2;
        
        /* Check address vaule */ // TODO decommentare quando cambio gli indirizzi
        //if (node_id == IEDF_SLOT_FREE || node_id == IEDF_ADDRESS_BROADCAST)
        //    return 0;

        if (num_nodes2 == IEDF_MAX_NODES) {
            /* Memory full */
            iedf_DEBUG_serial("\r\n*** ERROR *** memory full");
            return 0;
        } else if (node_id == 0) {
            /* Insert master schedulation */
            schedule[2].hyper_period = period;
            schedule[2].total_budget = 1;
        } else {        
            /* Update & check temporary variables */
            tmp_hyper = lcm(hyper_period2, period);
            if (tmp_hyper == 0) {
                if (!IEDF_DEBUG_JOIN_EXEC) {
                    iedf_DEBUG_serial_int3(hyper_period2, period, 0);
                    iedf_DEBUG_serial("\r\n(Hyp, new, 0) *** ERROR *** overflow attempted");
                }
                return 0;
            }
            tmp_total = tmp_hyper / hyper_period2 * total_budget2 + 
                tmp_hyper / period * budget;
            if (!IEDF_DEBUG_JOIN_EXEC) {
                iedf_DEBUG_serial_int3(node_id, budget, period);
                iedf_DEBUG_serial("\r\nJOIN (n, b, p)");
                iedf_DEBUG_serial_int3(num_nodes2, total_budget2, hyper_period2);
                iedf_DEBUG_serial("\r\nOLD (nodes, budget, period)");
                iedf_DEBUG_serial_int3(0, tmp_total, tmp_hyper);
                iedf_DEBUG_serial("\r\nNEW (0, budget, period)");
            }
            if (tmp_total > tmp_hyper) {
                /* Schedulation not feasible */
                iedf_DEBUG_serial("\r\n *** NOT FEASIBLE (START) *** ");
                return 0;
            } else if (tmp_total == tmp_hyper) {
                /* Do not try test interval reduction */
                Lstar = tmp_hyper;
            } else {
                /* Try test interval reduction */
                Lstar = tmp_hyper / IEDF_MASTER_BLOCKING_PERIOD *
                    (IEDF_MASTER_BLOCKING_PERIOD - 1) / (tmp_hyper - tmp_total);
                if (tmp_hyper < Lstar)
                    Lstar = tmp_hyper;
            }

            if (IEDF_DEBUG_USE_QPA) {
                /* *** QPA *** */
                /* Note: parameter unuseful
                Lb = iedf_get_lb();
                if (tmp_totalbudget == tmp_hyperperiod || Lb < Lstar)
                    Lstar = Lb;
                */               
                l = iedf_get_dmax(Lstar, period);
                while ((need = iedf_get_demand(l, budget, period)) <= l && 
                need > 1) {
                    if (need < l)
                        l = need;
                    else
                        l = iedf_get_dmax(l, period);
                }
                if (need > l) {
                    debugtimer2 = TMR2;
                    if (IEDF_DEBUG_JOIN_EXEC)
                        *timing = iedf_DEBUG_time(debugtimer1, debugtimer2);
                    iedf_DEBUG_serial("\r\n *** NOT FEASIBLE (QPA) *** ");
                    return 0;
                }
            } else {
                /* *** PDC *** */
                /* Check if schedulation is feasible */
                while ((l = iedf_get_next_deadline(l, period, tmp_hyper)) <= 
                Lstar) {
                    /* Budget needed */
                    need = (l + IEDF_MASTER_BLOCKING_PERIOD - 1) /
                        IEDF_MASTER_BLOCKING_PERIOD;               
                    for (i = 0; i < num_nodes2; i++)
                        need += l / db[IEDF_DB_INDEX2 + i].period *
                            db[IEDF_DB_INDEX2 + i].budget;
                    need += l / period * budget;
                    /* Check */
                    if (need > l) {
                        debugtimer2 = TMR2;
                        if (IEDF_DEBUG_JOIN_EXEC)
                            *timing = iedf_DEBUG_time(debugtimer1, debugtimer2);
                        iedf_DEBUG_serial("\r\n *** NOT FEASIBLE (PDC) *** ");
                        return 0;
                    }
                }
            }
            /* The schedulation is feasible. Update database */
            schedule[2].hyper_period = tmp_hyper;
            schedule[2].total_budget = tmp_total;
            db[IEDF_DB_INDEX2 + num_nodes2].node_id = node_id;
            db[IEDF_DB_INDEX2 + num_nodes2].budget = budget;
            db[IEDF_DB_INDEX2 + num_nodes2].period = period;
            schedule[2].total_nodes = ++num_nodes2;
        }

        /* Compute procedure duration */
        debugtimer2 = TMR2;
        if (IEDF_DEBUG_JOIN_EXEC)
            *timing = iedf_DEBUG_time(debugtimer1, debugtimer2);        
    }

    return 1;
}
