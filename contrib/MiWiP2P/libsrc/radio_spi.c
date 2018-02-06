#include "radio_spi.h"
#include "compiler.h"
#include "ee.h"

/*
 * Author: Gianluca Franchino.
 * Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
 * Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
 * Date: 02/16/2009.
 */

/**
* @file radio_spi.c
* @brief SPI port configuration and use for the radio transceiver control.
* @author Gianluca Franchino
* @date 2009-02-16
*
* \todo None
*/

#if defined(__dsPIC30F__) || defined(__dsPIC33F__) || defined(__PIC24F__) || defined(__PIC24H__)

/**
* @brief SPI port.
*/
unsigned char spi_port;

/**
* @brief Initialize the SPI peripheral.
*
* This function initializes the SPI peripheral defined by the input parameter \p port.
*
* @param[in] port 	The number of the SPI port to be initialized,
* 			it must be RADIO_SP1 or RADIO_SP2 defined in radio_spi.h.
*
* @return 	void
*
* @pre		None
*/
void dsPIC33F_radio_spi_init(unsigned char port)
{
		spi_port = port;

		if (spi_port == RADIO_SPI1) {

			SPI1STATbits.SPIEN = 0; /* Disable the SPI module */

			/*	Enable SPI internal clock
			 *	Enable 8 bits communication mode
			 *	Enable Master Mode
			 *	Primary Prescale 1:1
			 *	Secondary Prescale 8:1
			 *	Note: with these prescale values the port is working at 5 MHz.
			 */
			 //SPI1CON1 = 0x23;
			 SPI2CON1 = 0x13E;
			/* Note: because the chip select pin (SS1) does not work properly, we
			 * drive this pin directly setting it as a normal I/O pin.
			 */
			 SPI1CON2 = 0;
			 SPI1STATbits.SPIEN = 1; /* Enable the SPI module */

		} else {
			SPI2STATbits.SPIEN = 0; /* Disable the SPI module */

			/*	Enable SPI internal clock
			 *	Enable 8 bits communication mode
			 *	Enable Master Mode
			 *	Primary Prescale 1:1
			 *	Secondary Prescale 8:1
			 *	Note: with these prescale values the port is working at 5 MHz.
			 */
			//SPI1CON1 = 0x23;
			SPI2CON1 = 0x13E; //0b0000000100111110; //SPI is working at 10 MHz

			/* Note: because the chip select pin (SS1) does not work properly, we
			 * drive this pin directly setting it as a normal I/O pin.
			 */

			 SPI2CON2 = 0;

			 SPI2STATbits.SPIEN = 1; /* Enable the SPI module */


		}
}

/**
* @brief Send a byte through  the SPI peripheral.
*
* This function send a character ( 8 bits) through the SPI port controlling the radio.
*
* @param[in] v	The character to be sent
*
* @return 	the character received during the transaction.
*
* @pre		The SPI port must be correctly initialized.
*/
unsigned char dsPIC33F_radio_spi_put(unsigned char v)
{
	if (spi_port == RADIO_SPI1) {
		IFS0bits.SPI1IF = 0;
   		SPI1STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while(SPI1STATbits.SPITBF);
   		SPI1BUF = v;
   		while(!SPI1STATbits.SPIRBF);
   		SPI1STATbits.SPIROV = 0;

   		return SPI1BUF;

	} else {
		IFS2bits.SPI2IF = 0;
   		SPI2STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while(SPI2STATbits.SPITBF);
   		SPI2BUF = v;
   		while(!SPI2STATbits.SPIRBF);
   		SPI2STATbits.SPIROV = 0;

   		return SPI2BUF;

   	}

	return 0;
}

/**
* @brief Get a character through the SPI peripheral.
*
* This function send a character ( 8 bits) through the SPI port controlling the radio.
*
* @param[in] v	The character to be sent
*
* @return 	the character received during the transaction.
*
* @pre		The SPI port must be correctly initialized.
*/

unsigned char dsPIC33F_radio_spi_get(void)
{

	if (spi_port == RADIO_SPI1) {
   		/* wait until the tx buffer is empty */
   		while(SPI1STATbits.SPITBF);
   		SPI1BUF = 0x00;
   		while(!SPI1STATbits.SPIRBF);
   		SPI1STATbits.SPIROV = 0;

   		return SPI1BUF;

	} else {
   		/* wait until the tx buffer is empty */
   		while(SPI2STATbits.SPITBF);
   		SPI2BUF = 0x00;
   		while(!SPI2STATbits.SPIRBF);
   		SPI2STATbits.SPIROV = 0;

   		return SPI2BUF;

   	}
	return 0;
}


#else
	#error Unknown microcontroller. See radio_spi.c
#endif





