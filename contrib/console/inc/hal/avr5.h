#ifndef __avr5_h__
#define __avr5_h__
/** 
* @file pic30.h
* @brief PIC30 Hardware Abstraction Layer definition.
* @author Marinoni Mauro, Nastasi Christian
* @date 2008-11-03
*/

#ifdef __ERIKA__

#include "console_serial.h"
#ifdef __ATMEGA128__
#include "mcu/atmel_atmega128/inc/ee_uart.h"
#endif
#ifdef __ATMEGA1281__
#include "mcu/atmel_atmega1281/inc/ee_uart.h"
#endif

/* ************************************************************************** */
/*                          HAL Macros Declaration                            */
/* ************************************************************************** */
/** 
* @name Serial console HAL.
*
* These macros are required by the serial console implementation.
*
* @{ */
#define CONSOLE_SERIAL_HAL_FLAG_BIT9		EE_UART_BIT9
#define CONSOLE_SERIAL_HAL_FLAG_BIT8_ODD	EE_UART_BIT8_ODD
#define CONSOLE_SERIAL_HAL_FLAG_BIT8_EVEN	EE_UART_BIT8_EVEN
#define CONSOLE_SERIAL_HAL_FLAG_BIT8_NO		EE_UART_BIT8_NO
#define CONSOLE_SERIAL_HAL_FLAG_BIT_STOP1	EE_UART_BIT_STOP_1
#define CONSOLE_SERIAL_HAL_FLAG_BIT_STOP2	EE_UART_BIT_STOP_2

#define CONSOLE_SERIAL_HAL_CTRL_SIMPLE		EE_UART_CTRL_SIMPLE
#define CONSOLE_SERIAL_HAL_CTRL_FLOW		EE_UART_CTRL_FLOW

#define CONSOLE_SERIAL_HAL_PORT_1		EE_UART_PORT_1
#define CONSOLE_SERIAL_HAL_PORT_2		EE_UART_PORT_2
/**  @} */

#endif /* __ERIKA__ */
#endif /* __avr5_h__ */
