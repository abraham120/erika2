/**
 * @file iedf_data.h
 * @brief Implicit-EDF Data structure (Header)
 * @author Simone Madeo
 * @version 0.1
 * @date 2011-10-10
 */

#ifndef __iedf_data_h__
#define __iedf_data_h__

#include "util/iedf_util.h"
#include "mac/iedf.h"

/* Get my node-id */
uint16_t iedf_get_my_nodeid();

/* Get my budget */
uint16_t iedf_get_my_budget();

/* Get my period */
uint16_t iedf_get_my_period();

/* Set my node-id */
void iedf_set_my_nodeid(uint16_t value);

/* Set my budget */
void iedf_set_my_budget(uint16_t value);

/* Set my period */
void iedf_set_my_period(uint16_t value);

/* Get pending requests counter */
uint8_t iedf_get_pending_requests();

/* Retrieve total nodes info */
uint16_t iedf_get_total_nodes(uint8_t index);

/* Retrieve total budget info */
uint32_t iedf_get_total_budget(uint8_t index);

/* Retrieve hyperperiod info */
uint32_t iedf_get_hyperperiod(uint8_t index);

/* Store total nodes info */
void iedf_set_total_nodes(uint8_t index, uint16_t value);

/* Store hyperperiod info */
void iedf_set_hyperperiod(uint8_t index, uint32_t value);

/* Copy a database into another database. 
 * Return 1 if node can perform recovery. */
uint8_t iedf_db_copy(uint8_t i_dst, uint8_t i_src);

/* Store a new entry into a database. Return 1 if node is in database */
uint8_t iedf_db_store(uint8_t i_dst, uint8_t *mpdu, uint8_t counter);

/* Check pending requests */
uint8_t iedf_data_requests_flush();

/* Store pending requests */
void iedf_data_requests_store(uint8_t *packet, uint8_t stop_request);

/* Reset failed nodes' data structure */
void iedf_master_data_failure_reset();

/* Add a failed node into data structure */
void iedf_master_data_failure_add(uint16_t address, uint8_t force_remove);

/* Remove a failed node from data structure */
void iedf_master_data_failure_remove(uint16_t address);

/* Clear iEDF data structure */
void iedf_data_clean();

/* Store data into buffer */
uint8_t iedf_buffer_put(uint8_t *data, uint8_t len);

/* Load data from buffer */
uint8_t* iedf_buffer_get();

/* Storage db info into packet */
void iedf_db_package(uint8_t *packet, uint8_t index, uint8_t offset);

/* Return the next scheduled node id according to EDF algorithm. */
uint16_t iedf_data_turn(uint32_t t);

/* EDF Algorithm. Return 1 if node has been accepted (master use only) */
/* If budget equals 0, node is removed from schedulation */
uint8_t iedf_data_join(uint16_t node_id, uint16_t budget, uint16_t period,
uint16_t *timing);

// ***TODO*** to remove
void iedf_DEBUG_print_db(uint8_t index, char* str);
void iedf_DEBUG_print_failure();

#endif
