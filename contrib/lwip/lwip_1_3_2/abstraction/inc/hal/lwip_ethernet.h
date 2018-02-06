/*
  Name: lwip_ethernet.h
  Copyright: Evidence Srl
  Author: Dario Di Stefano
  Date: 29/03/10 18.23
  Description: 	This file contains the declarations of the abstract 
				ethernet used by LWIP modules.
*/

#ifndef __lwip_ethernet_h__
#define __lwip_ethernet_h__

//#include "ee_lwip.h"
#include <hal/lwip_compiler.h>

#if defined (__USE_ETHERNET_ENC28J60__)
  #include <hal/lwip_enc28j60.h>
#elif defined (__USE_PHY_SMSC8720__)
  #ifdef __PIC32__
    #include <hal/lwip_pic32mac.h>
  #else
    #error "LWIP_HAL ERROR: device not supported! (valid devices list: PIC32)"
  #endif
#else
  #error "LWIP_HAL ERROR: ethernet controller not specified! (valid controllers list: ENC28J60 (mac/phy), SMSC8720 (phy))"
#endif	 /* End ethernet Selection */

/* Forward declarations. */
err_t EE_ethernet_input(struct netif *netif);
err_t EE_ethernet_init(struct netif *netif);
err_t EE_ethernet_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr);
//err_t EE_ethernet_service(struct netif *netif);


#endif /* Header Protection */
