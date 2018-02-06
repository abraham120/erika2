/** 
* @file iedf_debug.h
* @brief Debug Interfaceiedf
* @author Gianluca Franchino 2012
* @author Gianluca Franchino 2011 
*
* This file define the debug optional function that can be used by the stack
* declaring the build option \c IEDF_DEBUG.
*
*/
#ifndef __iedf_debug_h__
#define __iedf_debug_h__

#ifndef IEDF_DEBUG

#define iedf_debug_init() ((void)0)
#define iedf_debug_write(a, b) ((void)0)
#define iedf_debug_print() ((void)0)
#define iedf_debug_sprint_u8(a,b) ((void)0)
#define iedf_debug_sprint_u16(a,b) ((void)0)
#define iedf_debug_sprint_u32(a,b) ((void)0)
#define iedf_debug_sprint_d8(a,b) ((void)0)
#define iedf_debug_sprint_d16(a,b) ((void)0)
#define iedf_debug_sprint_d32(a,b) ((void)0)

#else 

#include <hal/iedf_compiler.h> 


#ifdef IEDF_DEBUG_LOG
#ifndef USE_CONSOLE
#error "IEDF_DEBUG_LOG: Console library is required for RI-EDF Debugging."
#endif

#include "console.h"	/* From the console contrib library. */

/* Select the specific debug mechanism (port). */
#ifdef IEDF_DEBUG_LOG_SERIAL		/* Serial Port */

#ifndef USE_CONSOLE_SERIAL	
#error "IEDF_DEBUG_LOG: Console Serial module is required for serial port."
#endif
#include "console_serial.h"  /* From the console contrib library. */
#ifndef IEDF_DEBUG_LOG_SERIAL_PORT 
#define IEDF_DEBUG_LOG_SERIAL_PORT 	CONSOLE_SERIAL_PORT_2		
#endif
#ifndef IEDF_DEBUG_LOG_SERIAL_BAUDRATE 
#define IEDF_DEBUG_LOG_SERIAL_BAUDRATE 	115200 
#endif
#ifndef IEDF_DEBUG_LOG_SERIAL_OPT
//#define IEDF_DEBUG_LOG_SERIAL_OPT 0x06
#define IEDF_DEBUG_LOG_SERIAL_OPT \
	CONSOLE_SERIAL_FLAG_BIT8_NO | CONSOLE_SERIAL_FLAG_BIT_STOP1

#endif

#else	/* Unspecified Port */
#error "IEDF_DEBUG_LOG: unselected debug mechanism."

#endif	/* End Select Debug Port */

#endif /* IEDF_DEBUG_LOG */

/** 
* @brief Initialize the uWireless debug port
* 
* @return A negative error code is return on failure, otherwise success.
*/
int8_t iedf_debug_init(void);



/** 
* @brief Write to the iedf debug port
* 
* @param[in] msg The message to write
* @param[in] len The message length
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref iedf_debug_init
*	function. 
*/
int8_t iedf_debug_write(uint8_t *msg, uint16_t len);

/** 
* @brief Print to the uWireless debug port
* 
* @param[in] msg The message to write
* 
* @return A negative error code is return on failure, otherwise success.
*
* @pre 	The debug port must be properly initialized with the \ref iedf_debug_init
*	function. 
*
* \todo Write a comment to this function.
*/
int8_t iedf_debug_print(const char *msg);


COMPILER_INLINE void iedf_debug_sprint_u8(uint8_t data, char *out)
{
	out[3] = '\0';
	out[2] = '0' + (data % 10);
	out[1] = '0' + ((data / 10) % 10);
	out[0] = '0' + ((data / 100) % 10);
}

COMPILER_INLINE void iedf_debug_sprint_u16(uint16_t data, char *out)
{
	out[5] = '\0';
	out[4] = '0' + (data % 10);
	out[3] = '0' + ((data / 10) % 10);
	out[2] = '0' + ((data / 100) % 10);
	out[1] = '0' + ((data / 1000) % 10);
	out[0] = '0' + ((data / 10000) % 10);
}

COMPILER_INLINE void iedf_debug_sprint_u32(uint32_t data, char *out)
{
	out[10] = '\0';
	out[9] = '0' + (data % 10);
	out[8] = '0' + ((data / 10) % 10);
	out[7] = '0' + ((data / 100) % 10);
	out[6] = '0' + ((data / 1000) % 10);
	out[5] = '0' + ((data / 10000) % 10);
	out[4] = '0' + ((data / 100000) % 10);
	out[3] = '0' + ((data / 1000000) % 10);
	out[2] = '0' + ((data / 10000000) % 10);
	out[1] = '0' + ((data / 100000000) % 10);
	out[0] = '0' + ((data / 1000000000) % 10);
}

COMPILER_INLINE void iedf_debug_sprint_d8(int8_t data, char *out)
{
	out[4] = '\0';
	out[3] = '0' + (data % 10);
	out[2] = '0' + ((data / 10) % 10);
	out[1] = '0' + ((data / 100) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void iedf_debug_sprint_d16(int16_t data, char *out)
{
	out[6] = '\0';
	out[5] = '0' + (data % 10);
	out[4] = '0' + ((data / 10) % 10);
	out[3] = '0' + ((data / 100) % 10);
	out[2] = '0' + ((data / 1000) % 10);
	out[1] = '0' + ((data / 10000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void iedf_debug_sprint_d32(int32_t data, char *out)
{
	out[11] = '\0';
	out[10] = '0' + (data % 10);
	out[9] = '0' + ((data / 10) % 10);
	out[8] = '0' + ((data / 100) % 10);
	out[7] = '0' + ((data / 1000) % 10);
	out[6] = '0' + ((data / 10000) % 10);
	out[5] = '0' + ((data / 100000) % 10);
	out[4] = '0' + ((data / 1000000) % 10);
	out[3] = '0' + ((data / 10000000) % 10);
	out[2] = '0' + ((data / 100000000) % 10);
	out[1] = '0' + ((data / 1000000000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

#endif /*ifndef IEDF_DEBUG*/

#endif /* Header Protection */
