#ifdef USE_CONSOLE

#include "hal/mico32.h"

/* ************************************************************************** */
/*                           HAL Functions Definition                         */
/* ************************************************************************** */
#ifdef USE_CONSOLE_SERIAL


#ifndef __USE_UART__
#error "CONSOLE_SERIAL ERROR: UART support from Erika MCU is required!"
#endif

int8_t console_serial_hal_open(uint8_t port, uint32_t bdr, uint16_t flags)
{
	EE_hal_uart_config(& EE_ST_NAME(EE_UART1_NAME_LC), bdr, flags);
	EE_hal_uart_set_ISR_mode(& EE_ST_NAME(EE_UART1_NAME_LC), EE_UART_POLLING | EE_UART_RXTX_BLOCK);
	return 1;
}

int8_t console_serial_hal_close(uint8_t port) 
{
	//EE_uart_close();
	return 1;
}

int8_t console_serial_hal_write(uint8_t port, const uint8_t *mesg,
    uint16_t length)
{
	return EE_hal_uart_write_buffer(& EE_ST_NAME(EE_UART1_NAME_LC), mesg, length);
}

int8_t  console_serial_hal_read(uint8_t port, uint8_t *mesg, uint16_t length, 
				uint16_t *read)
{
	*read = EE_hal_uart_read_buffer(& EE_ST_NAME(EE_UART1_NAME_LC), mesg, length);
	
	return 1;
}


#endif /* USE_CONSOLE_SERIAL */

#endif /* USE_CONSOLE */
