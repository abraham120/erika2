#include "mcu/microchip_dspic/inc/ee_spi.h"

EE_INT8 EE_spi_init(EE_UINT8 port)
{
	/* Enable SPI internal clock
	 * Enable 8 bits communication mode
	 * Enable Master Mode
	 * Primary Prescale 1:1
	 * Secondary Prescale 8:1
	 * Note: with these prescale values the port works at 5 MHz. */
	/* Note: because the chip select pin (SS1)
	   does not work properly, we drive this pin
	   directly setting it as a normal I/O pin.  */

	if (port == EE_SPI_PORT_1) {
		SPI1STATbits.SPIEN = 0; /* Disable the SPI module */

		#if defined (__PIC24FJ32GA004__) || defined (__PIC24FJ64GA004__)
		SPI1CON1 = 0x13E;
		#elif defined (__EE_MOODLIGHT_BRD__) || defined (__EE_USB2SSI_BRD__)
		SPI1CON1 = 0x13A;
		#else
		SPI1CON1 = 0x13E;
		#endif

		SPI1CON2 = 0;
		SPI1STATbits.SPIEN = 1; /* Enable the SPI module */
		return 1;
	} else if (port == EE_SPI_PORT_2) {
		SPI2STATbits.SPIEN = 0; /* Disable the SPI module */
		#if defined (__PIC24FJ32GA004__) || defined (__PIC24FJ64GA004__)
		SPI2CON1 = 0x13E;
		#elif defined (__EE_MOODLIGHT_BRD__) || defined (__EE_USB2SSI_BRD__)
		SPI2CON1 = 0x13A;
		#else
		SPI2CON1 = 0x13E;
		#endif
		SPI2CON2 = 0;
		SPI2STATbits.SPIEN = 1; /* Enable the SPI module */
		return 1;
	}
	return -EE_SPI_ERR_BAD_PORT;
}

EE_INT8 EE_spi_close(EE_UINT8 port)
{
	if (port == EE_SPI_PORT_1) {
		/* chris: TODO: Release something */
		return 1;
	} else if (port == EE_SPI_PORT_2) {
		/* chris: TODO: Release something */
		return 1;
	}
	return -EE_SPI_ERR_BAD_PORT;
}

EE_INT8 EE_spi_rw_byte(EE_UINT8 port, EE_UINT8 data_in, EE_UINT8 *data_out)
{
	if (port == EE_SPI_PORT_1) {
		IFS0bits.SPI1IF = 0;
   		SPI1STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while (SPI1STATbits.SPITBF);
   		SPI1BUF = data_in;
   		while (!SPI1STATbits.SPIRBF);
   		SPI1STATbits.SPIROV = 0;
		*data_out = SPI1BUF & 0x00FF;
   		return 1;
	} else if (port == EE_SPI_PORT_2) {
		IFS2bits.SPI2IF = 0;
   		SPI2STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while (SPI2STATbits.SPITBF);
   		SPI2BUF = data_in;
   		while (!SPI2STATbits.SPIRBF);
   		SPI2STATbits.SPIROV = 0;
		*data_out = SPI2BUF & 0x00FF;
   		return 1;
   	}
	return -EE_SPI_ERR_BAD_PORT;
}

EE_INT8 EE_spi_write_byte(EE_UINT8 port, EE_UINT8 data)
{
	if (port == EE_SPI_PORT_1) {
		IFS0bits.SPI1IF = 0;
   		SPI1STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while (SPI1STATbits.SPITBF);
   		SPI1BUF = data;
   		while (!SPI1STATbits.SPIRBF);
   		SPI1STATbits.SPIROV = 0;
		data = SPI1BUF; /* Dummy Read Required */
   		return 1;
	} else if (port == EE_SPI_PORT_2) {
		IFS2bits.SPI2IF = 0;
   		SPI2STATbits.SPIROV = 0;
   		/* wait until the tx buffer is empty */
   		while (SPI2STATbits.SPITBF);
   		SPI2BUF = data;
   		while (!SPI2STATbits.SPIRBF);
   		SPI2STATbits.SPIROV = 0;
		data = SPI2BUF; /* Dummy Read Required */
   		return 1;
   	}
	return -EE_SPI_ERR_BAD_PORT;
}

EE_INT8 EE_spi_read_byte(EE_UINT8 port, EE_UINT8 *data)
{
	if (port == EE_SPI_PORT_1) {
   		/* wait until the tx buffer is empty */
   		while (SPI1STATbits.SPITBF);
   		SPI1BUF = 0x00;
   		while (!SPI1STATbits.SPIRBF);
   		SPI1STATbits.SPIROV = 0;
   		*data =  SPI1BUF & 0x00FF;

   		return 1;
	} else if (port == EE_SPI_PORT_2) {
   		/* wait until the tx buffer is empty */
   		while (SPI2STATbits.SPITBF);
   		SPI2BUF = 0x00;
   		while (!SPI2STATbits.SPIRBF);
   		SPI2STATbits.SPIROV = 0;
   		*data =  SPI2BUF & 0x00FF;
   		return 1;
   	}
	return -EE_SPI_ERR_BAD_PORT;
}

