#ifndef __console_cortex_mx_h__
#define __console_cortex_mx_h__

#ifdef __ERIKA__

#include "console_serial.h"
#include "Sci.h"

/* ************************************************************************** */
/*                          HAL Macros Declaration                            */
/* ************************************************************************** */
/** 
* @name Serial console HAL.
*
* These macros are required by the serial console implementation.
*
* @{ */
#define CONSOLE_SERIAL_HAL_FLAG_BIT8_NO		1
#define CONSOLE_SERIAL_HAL_FLAG_BIT_STOP1	1
#define CONSOLE_SERIAL_HAL_PORT_1			0

/**  @} */

#endif /* __ERIKA__ */
#endif /* __console_cortex_mx_h__ */

