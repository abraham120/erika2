/** 
* @file uwl_mac_mutexes.h
* @brief MAC to PHY Mutex Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/
#ifndef __uwl_mac_mutexes_h__
#define __uwl_mac_mutexes_h__

#include <kal/uwl_kal.h>

#define UWL_PHY_IMPORT_MAC_MUTEXES(task_id)		\
	UWL_KAL_MUTEX(MAC_RX_BEACON_MUTEX, task_id);	\
	UWL_KAL_MUTEX(MAC_RX_DATA_MUTEX, task_id);	\
	UWL_KAL_MUTEX(MAC_RX_COMMAND_MUTEX, task_id);	\

#endif /* Header Protection */
