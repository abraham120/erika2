#ifndef __console_c__
#define __console_c__
/** 
* @file console.c
* @brief Generic console port definition.
* @author Marinoni Mauro, Christian Nastasi
* @date 2008-10-29
*/

#ifdef USE_CONSOLE

#include <console.h>

/* ************************************************************************** */
/*                        Global Variables Definition                         */
/* ************************************************************************** */
console_descriptor_t *consoles[CONSOLE_NUMBER];

#endif	/* USE_CONSOLE */
#endif	/* __console_c__ */
