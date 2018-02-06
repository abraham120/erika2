
/**
 * $Id: usr_mlme_reset_conf.c,v 1.1 2007/06/22 13:50:48 romano Exp $
 * @file
 * generated code for user callback function
 * - Generator: -C
 *
 */
/**
 *   uthor
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */

#include "board.h"
#ifndef DEF_H
#include "def.h"
#endif
#include "ee_confMac.h"

#ifdef PANCOORDINATOR
extern coord_status_t c_status;
void usr_mlme_reset_conf(uint8_t status)
{

    if (( status == MAC_SUCCESS ) && ( c_status.state == PEND_RESET_C ))
    {
        mac_set_short_addr(PANCOORD_SHORT_ADD);
    }
    else
    {
        mac_do_reset();
    }
    return;
}

#elif DEVICE
extern device_status_t d_status;
extern void mac_scan(void);
void usr_mlme_reset_conf (uint8_t status)
{
	
   
    if ((status == MAC_SUCCESS) && (d_status.state == PEND_RESET_D))
    {
        mac_scan();
    }
    
    return;
}
#else
void usr_mlme_reset_conf (uint8_t status)
{
}
#endif





