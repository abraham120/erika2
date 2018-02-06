/**
 * @file iedf_util.c
 * @brief Implicit-EDF Utilities (Implementation)
 * @author Gianluca Franchino 2012
 * @date 2012
 */

#include "util/iedf_debug.h"
#include <string.h>

#ifdef IEDF_DEBUG_LOG
static uint8_t debug_initialized = 0; 
#endif

#define IEDF_DEBUG_LOG_CONSOLE 0

int8_t iedf_debug_init(void)
{
#ifdef IEDF_DEBUG_LOG
	debug_initialized = 0;
	console_descriptor_t *des = NULL;
#ifdef IEDF_DEBUG_LOG_SERIAL 
	des = console_serial_config(IEDF_DEBUG_LOG_SERIAL_PORT, 
								IEDF_DEBUG_LOG_SERIAL_BAUDRATE,
								IEDF_DEBUG_LOG_SERIAL_OPT);
#endif
	if (des == NULL)
		return -1;
	if (console_init(IEDF_DEBUG_LOG_CONSOLE, des) < 0)
		return -1;
	debug_initialized = 1;
	return console_open(IEDF_DEBUG_LOG_CONSOLE);
#else
	return 1;
#endif /* IEDF_DEBUG_LOG */
}

int8_t iedf_debug_write(uint8_t *msg, uint16_t len) 
{
#ifdef IEDF_DEBUG_LOG
	if (debug_initialized)
		return console_write(IEDF_DEBUG_LOG_CONSOLE, msg, len);
	return -1;
#else
	return 0;
#endif /* IEDF_DEBUG_LOG */
}
