#ifndef __console_serial_h__
#define __console_serial_h__
/** 
* @file console_serial.h
* @brief Serial console definition.
* @author Marinoni Mauro, Nastasi Christian
* @date 2008-11-03
*/

#if ((defined USE_CONSOLE) && (defined USE_CONSOLE_SERIAL))

#include "hal/compiler.h"
#include "hal/arch.h"
#include "console.h"

/* ************************************************************************** */
/*                             Macros Definition                              */
/* ************************************************************************** */
#ifndef CONSOLE_SERIAL_NUMBER
#define CONSOLE_SERIAL_NUMBER 2	/**< Default max number of serial consoles */
#endif

#if	0
/* TODO - Remap console constants to hal ones! */
#define CONSOLE_SERIALFLAG_BIT9		0x06
#define CONSOLE_SERIALFLAG_BIT8_ODD	0x04
#define CONSOLE_SERIALFLAG_BIT8_EVEN	0x02
#define CONSOLE_SERIALFLAG_BIT8_NO	0x00
#define CONSOLE_SERIALFLAG_BIT_STOP_1	0x00
#define CONSOLE_SERIALFLAG_BIT_STOP_2	0x01
#endif	/* 0 */

/* ************************************************************************** */
/*                          HAL Macros Declaration                            */
/* ************************************************************************** */
/** 
* @name Serial console HAL.
*
* These macros are required by the serial console implementation
* and must be defined in the HAL.
*
* @{ */
#define CONSOLE_SERIAL_FLAG_BIT9	CONSOLE_SERIAL_HAL_FLAG_BIT9
#define CONSOLE_SERIAL_FLAG_BIT8_ODD	CONSOLE_SERIAL_HAL_FLAG_BIT8_ODD
#define CONSOLE_SERIAL_FLAG_BIT8_EVEN	CONSOLE_SERIAL_HAL_FLAG_BIT8_EVEN
#define CONSOLE_SERIAL_FLAG_BIT8_NO	CONSOLE_SERIAL_HAL_FLAG_BIT8_NO
#define CONSOLE_SERIAL_FLAG_BIT_STOP1	CONSOLE_SERIAL_HAL_FLAG_BIT_STOP1
#define CONSOLE_SERIAL_FLAG_BIT_STOP2	CONSOLE_SERIAL_HAL_FLAG_BIT_STOP2

#define CONSOLE_SERIAL_CTRL_SIMPLE 	CONSOLE_SERIAL_HAL_CTRL_SIMPLE	
#define CONSOLE_SERIAL_CTRL_FLOW 	CONSOLE_SERIAL_HAL_CTRL_FLOW

#define CONSOLE_SERIAL_PORT_1		CONSOLE_SERIAL_HAL_PORT_1	
#define CONSOLE_SERIAL_PORT_2		CONSOLE_SERIAL_HAL_PORT_2

#if (CONSOLE_SERIAL_NUMBER > 2)
#define CONSOLE_SERIAL_PORT_3		CONSOLE_SERIAL_HAL_PORT_3
#define CONSOLE_SERIAL_PORT_4		CONSOLE_SERIAL_HAL_PORT_4
#define CONSOLE_SERIAL_PORT_5		CONSOLE_SERIAL_HAL_PORT_5
#define CONSOLE_SERIAL_PORT_6		CONSOLE_SERIAL_HAL_PORT_6
#endif
/**  @} */

/* ************************************************************************** */
/*                             Types Definition                               */
/* ************************************************************************** */
/** 
* @brief Serial console parameters descriptor.
*
* The structure allow to specify some parameters which describe the serial
* interface to be attached to the console port.
*/
typedef struct console_serial_t {
	uint8_t port;		/**< Serial interface identifier. */
	uint32_t baudrate; 	/**< Serial link baudrate. */
	uint16_t flags;		/**< Serial interface options. 
					\todo refer to something somewhere */
} console_serial_t;

/* ************************************************************************** */
/*                             Functions Delcaration                          */
/* ************************************************************************** */
/** 
* @brief Configure the serial interface.
* 
* @param[in] port 	Serial interface identifier.
* @param[in] baudrate 	Serial link baudrate.
* @param[in] flags 	Serial interface options. 
*			\todo refer to something somewhere.
* 
* @return 	A reference to an abstract console descriptor to be attached, 
*		by means of the \ref console_init, to the console port.
*		If the \c port parameter is invalid \c NULL is returned.
*/
console_descriptor_t *console_serial_config(uint8_t port, uint32_t baudrate, 
					    uint16_t flags);

/* ************************************************************************** */
/*                           HAL Functions Delcaration                        */
/* ************************************************************************** */
/** 
* @name Serial console HAL.
*
* These functions are the APIs required by the serial console implementation
* and must be implemented in the HAL.
*
* @{ */
int8_t console_serial_hal_open(uint8_t port, uint32_t baudrate, uint16_t flags);
int8_t console_serial_hal_close(uint8_t port);
int8_t console_serial_hal_write(uint8_t port, const uint8_t *mesg, uint16_t length);
int8_t console_serial_hal_read(uint8_t port, uint8_t *mesg, uint16_t length, 
			       uint16_t *read);
/**  @} */

#endif	/* USE_CONSOLE && USE_CONSOLE_SERIAL */

#endif	/* __console_serial_h__*/
