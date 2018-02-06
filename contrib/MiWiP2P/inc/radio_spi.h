/*
 * Author: Gianluca Franchino.
 * Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
 * Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
 * Date: 02/16/2009.
 */

/** 
* @file radio_spi.h
* @brief SPI port configuration and use for the radio transceiver control.
* @author Gianluca Franchino 
* @date 2009-02-16
*
* \todo None
*/

#ifndef _RADIO_SPI_H_
#define _RADIO_SPI_H_

#include "P2PDefs.h"

#ifndef RADIO_SPI1
#define RADIO_SPI1 0
#endif

#ifndef RADIO_SPI2
#define RADIO_SPI2 1
#endif


#if defined(__dsPIC30F__) || defined(__dsPIC33F__) || defined(__PIC24F__) || defined(__PIC24H__)
	void dsPIC33F_radio_spi_init(unsigned char);
	unsigned char dsPIC33F_radio_spi_put(unsigned char);
	unsigned char dsPIC33F_radio_spi_get(void);
#else
	#error Unknow microcontroller. See radio_spi.h
#endif

#endif
