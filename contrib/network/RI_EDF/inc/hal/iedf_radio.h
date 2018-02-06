/** 
 * @file iedf_radio.h
 * @brief Abstract Radio Definition
 * @author Simone Madeo 2011
 *
 * Using the Erika Enterprise abstraction for the compiler.
 */

#ifndef __iedf_radio_h__
#define __iedf_radio_h__


#ifdef USE_CC2420                   /* Texas Instruments CC2420 */
#include "iedf_radio_cc2420.h"

#elif defined USE_MRF24J40          /* Microchip MRF24J40. */
#include "iedf_radio_mrf24j40.h"

#else                               /* No radio */
#error "IEDF_HAL ERROR: radio type not specified!"

#endif

#endif /* Header Protection */
