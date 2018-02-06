/** 
* @file debug.h
* @brief Debug Interface
* @author Christian Nastasi, Dario Di Stefano
* @date 2009-03-22
*
* This file define the debug optional function that can be used by the stack
* declaring the build option \c lwip_DEBUG.
*
* \todo Include a dependency check in the header file inclusion that returns a 
* 	compilation error if the console library is not included in the build of
* 	the lwip one.
*
* \todo Write a more specific docs for this section that explain:
* 	- How to enable debugging (from the compiler line?);
* 	- What are the supported debug mechanisms (debug ports);
* 	- What are the port-specifc debug option (from the compiler line?).
* 	- What are the dependency with respect to other contrib dir.
*/

#ifndef __lwip_debug_h__
#define __lwip_debug_h__

#include "lwip/pbuf.h"
#include <hal/lwip_compiler.h> 

#define LWIP_DEBUG_ERR	-1
#define LWIP_DEBUG_OK	0

#ifdef __LWIP_DEBUG__
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE
#error "LWIP_DEBUG: Console library is required for LWIP Debugging."
#endif
#include "console.h"	/* From the console contrib library. */
/* Select the specific debug mechanism (port). */
#ifdef __LWIP_DEBUG_SERIAL__		/* Serial Port */
/* FIXME: chris: now this simbol is passed by the compiled -D option, 
 * we should have something automatically declared when the required contrib 
 * lib is included in the build. */
#ifndef USE_CONSOLE_SERIAL	
#error "LWIP_DEBUG: Console Serial module is required for serial port."
#endif
#include "console_serial.h"  /* From the console contrib library. */
#ifndef LWIP_DEBUG_SERIAL_PORT 
#define LWIP_DEBUG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_1		
#endif
#ifndef LWIP_DEBUG_SERIAL_BAUDRATE 
#define LWIP_DEBUG_SERIAL_BAUDRATE 	115200 
#endif
#ifndef LWIP_DEBUG_SERIAL_OPT
#define LWIP_DEBUG_SERIAL_OPT \
	CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1
#endif
#else	/* Unspecified Port */
#error "LWIP_DEBUG: unselected debug mechanism."
#endif	/* End Select Debug Port */
#define LWIP_DEBUG_CONSOLE 0

#endif /* LWIP_DEBUG */

/** 
* @brief Initialize the lwip debug port
* 
* @return A negative error code is return on failure, otherwise success.
*/
s8_t lwip_debug_init(void);

/** 
* @brief Write to the lwip debug port
* 
* @param[in] msg The message to write
* @param[in] len The message length
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref lwip_debug_init
*	function. 
*/
s8_t lwip_debug_write(char *msg, u16_t len);

/* Printf emulation */
s8_t lwip_debug_printf(const char* s, ...);

/* pbuf print */
s8_t lwip_debug_print_pbuf(const char *name, struct pbuf *p);

#endif /* Header Protection */
