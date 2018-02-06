#ifndef __mico32_h__
#define __mico32_h__

#include "console_serial.h"

///* Include a file with the registers of the s12 micro-controller */ 
#include "ee_internal.h"
#include "mcu/mico32/inc/ee_uart.h"

#ifndef NULL
#define NULL 0
#endif

#define CONSOLE_SERIAL_HAL_FLAG_BIT8_NO EE_UART_BIT8_NO
#define CONSOLE_SERIAL_HAL_FLAG_BIT_STOP1 EE_UART_BIT_STOP_1

#define CONSOLE_SERIAL_HAL_PORT_1		0
#define CONSOLE_SERIAL_HAL_PORT_2		1

#endif /* __mico32_h__ */
