/** @file	avr8.c
 *  @brief	AVR8 Hardware Abstraction Layer implementation.
 *  @author	Giuseppe Serano
 *  @date	2014
 */

#ifdef USE_CONSOLE

#include "hal/avr8.h"

/* ************************************************************************** */
/*                           HAL Functions Definition                         */
/* ************************************************************************** */
#ifdef USE_CONSOLE_SERIAL


#ifndef __USE_UART__
#error "CONSOLE_SERIAL ERROR: UART support from Erika MCU is required!"
#endif

int8_t console_serial_hal_open(uint8_t port, uint32_t bdr, uint16_t flags)
{
	return EE_uart_init(port, bdr, flags, 0);
}

int8_t console_serial_hal_close(uint8_t port) 
{
	return 1;
}

int8_t console_serial_hal_write(uint8_t port, const uint8_t *mesg,
				uint16_t length)
{
	uint16_t i;
	int8_t retv;
	
	/* TODO!!! - Buffer management in interrupt mode */
	for (i = 0; i < length; i++) {
		retv = EE_uart_write_byte(port, mesg[i]);
		if (retv < 0)
			return retv;
	}
	return 1;
}

int8_t  console_serial_hal_read(uint8_t port, uint8_t *mesg, uint16_t length, 
				uint16_t *read)
{
	uint16_t i;
	int8_t retv;
	
	/* TODO!!! - Buffer management in interrupt mode */
	for (i = 0; i < length; i++) {
		retv = EE_uart_read_byte(port, mesg + i); 
		if (retv < 0)
			return retv;
	}
	return 1;
}


#endif /* USE_CONSOLE_SERIAL */

#endif /* USE_CONSOLE */
