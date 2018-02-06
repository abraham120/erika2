/** 
* @file uwl_ieee802154.h
* @brief IEEE 802.15.4 Interface
* @author Christian Nastasi
* @version 0.1
* @date 2009-06-22
*/

/** 
* \mainpage uWireless 
*
* \todo Write a brief description of the uWireless Stack
*
* \section intro_sec Introduction 
*
* \todo Write Intro
*
*/

#ifndef __uwl_ieee802154_h__
#define __uwl_ieee802154_h__

#if 	defined UWL_USE_ONLY_802154_MAC
#include <mac/uwl_mac.h>
#elif 	defined UWL_USE_SIMPLE_802154
#include <net/uwl_simple154.h>
#elif 	defined LWP_USE_6LOWPAN
#include <../../netInt/inc/net_int.h>
#else
#error "UWL IEEE 802.15.4: A valid API access method must be declared"
#endif

#endif /* Header Protection */
