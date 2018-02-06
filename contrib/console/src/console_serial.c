#ifndef __console_serial_c__
#define __console_serial_c__
/** 
* @file console_serial.c
* @brief Serial console implementation.
* @author Marinoni Mauro, Nastasi Christian
* @date 2008-11-03
*/

#if ((defined USE_CONSOLE) && (defined USE_CONSOLE_SERIAL))

#include "console_serial.h"

/* ************************************************************************** */
/*                       Private Variables Definition                         */
/* ************************************************************************** */
/** 
* @brief Abstract console descriptors for the serial consoles.
*/
static console_descriptor_t serial_des[CONSOLE_SERIAL_NUMBER];
/** 
* @brief Serial console parameters.
*/
static console_serial_t	serial_params[CONSOLE_SERIAL_NUMBER];
#if	0
/** 
* @brief Number of console port currently initialized.
*/
static uint8_t ports = 0;
#endif	/* 0 */

/* ************************************************************************** */
/*                       Private Functions Definition                         */
/* ************************************************************************** */
static int console_serial_open(void *prm)
{
	console_serial_t *tmp = (console_serial_t *)prm;
	return console_serial_hal_open(tmp->port, tmp->baudrate, tmp->flags);
}

static int console_serial_close(void *prm)
{
	console_serial_t *tmp = (console_serial_t *)prm;
	return console_serial_hal_close(tmp->port);
}

static int console_serial_write(void *prm, const uint8_t *mesg, uint16_t leng)
{
	console_serial_t *tmp = (console_serial_t *)prm;
	return console_serial_hal_write(tmp->port, mesg, leng);
}

static int console_serial_read(void *prm, uint8_t *mesg, uint16_t leng, 
								uint16_t *read)
{
	console_serial_t *tmp = (console_serial_t *)prm;
	return console_serial_hal_read(tmp->port, mesg, leng, read);
}

/* ************************************************************************** */
/*                        Public Functions Definition                         */
/* ************************************************************************** */
console_descriptor_t *console_serial_config(uint8_t port, uint32_t baudrate, 
								uint16_t flags)
{
	if (port >= CONSOLE_SERIAL_NUMBER)
		return NULL;
	serial_params[port].port = port;
	serial_params[port].baudrate	= baudrate;
	serial_params[port].flags = flags;
	serial_des[port].params = (void *)(serial_params + port);
	serial_des[port].open = console_serial_open;
	serial_des[port].close = console_serial_close;
	serial_des[port].write = console_serial_write;
	serial_des[port].read = console_serial_read;
	return (serial_des + port);
	

#if	0
	/* Set console serial parameters */
	serial_params[ports].port = port;
	serial_params[ports].baudrate	= baudrate;
	serial_params[ports].flags = flags;
	/* Set abstract console hooks */
	serial_des[ports].params = (void *)(serial_params + ports);
	serial_des[ports].open = console_serial_open;
	serial_des[ports].close = console_serial_close;
	serial_des[ports].write = console_serial_write;
	serial_des[ports].read = console_serial_read;
	ports++;
	return (serial_des + ports - 1);
#endif	/* 0 */
}

#if	0
console_descriptor_t *
console_serial_create(uint8_t port, uint16_t baudrate, uint16_t flags)
{
	console_descriptor_t			*parms;
	console_serial_t	*serial_params;

	/* Serial console parameters structure - Allocate */
	serial_params = malloc( sizeof(console_serial_t) );
	
	/* Serial console parameters structure - Assign user values */
	serial_params->port		= port;
	serial_params->baudrate	= baudrate;
	serial_params->flags	= flags;
	
	/* Console parameters structure - Allocate */
	parms = malloc( sizeof(console_descriptor_t) );

	/* Serial console parameters structure - Assign user values */
	parms->params = (void *)serial_params;
	parms->open	 = NULL;
	parms->close = NULL;
	parms->write = NULL;
	parms->read  = NULL;
}
#endif	/* 0 */

#endif	/* USE_CONSOLE && USE_CONSOLE_SERIAL */
#endif	/* __console__serial_c__ */
