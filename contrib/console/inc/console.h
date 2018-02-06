#ifndef __console_h__
#define __console_h__
/** 
* @file console.h
* @brief Generic console port definition.
* @author Marinoni Mauro, Nastasi Christian 
* @date 2008-10-29
*
* \todo Write more, explain how to use the console in general!
*/

#ifdef USE_CONSOLE	
/** 
* \mainpage Generic Console Interface for Microcontrollers  
*
* \todo Write a brief description of the idea behind the 
*	definition of this console.
*
* \section intro_sec Introduction 
*
* Bla Bla Bla... 
*
* \section usage_sec Usage 
*
* \subsection static_allocation Microcontroller Resource Allocation 
*
* \section compilation Compilation 
* 
* \subsection make Makefile Targets 
*
* Try to type <c>\$ make help </c> in the library directory.
*
* \subsection defs Pre-Compilier Definitions 
*
* Here is a list the compiler defines .... :
* - \c DEFINE_1 : 
* - \c DEFINE_2 : 
*
* @section consider Consideration
*
* \todo 
* - fix this documentation main page!! 
*
*/

#if	0
#include <string.h>
#endif	/* 0 */
#include "hal/compiler.h"

/* ************************************************************************** */
/*                             Macros Definition                              */
/* ************************************************************************** */
#ifndef CONSOLE_NUMBER
#define CONSOLE_NUMBER 2	/**< Default max number of console ports */
#endif

#define NULLP	(void *)0

/* ************************************************************************** */
/*                             Types Definition                               */
/* ************************************************************************** */
/** 
* @brief Hook to concrete consoles.
*
* The console descriptor allows to map the generic abstract console
* to a concrete implementation of it.
* For each concrete function the first argument, the \c void pointer, 
* is for generic parameters passing.
* This depends on the specific console implementation and is filled by the 
* abstract console functions with the \ref params element.
*/
typedef struct console_descriptor_t {
	/** Pointer to the concrete close function. */
	int (*close)(void *);
	/** Pointer to the concrete open function. */
	int (*open)(void *);	
	/** Pointer to the concrete write function. */
	int (*write)(void *, const uint8_t *, uint16_t);
	/** Pointer to the concrete read function. */
	int (*read)(void *, uint8_t *, uint16_t, uint16_t *);
	/** Pointer to generic parameter(s) for the concrete functions. */
	void *params;
} console_descriptor_t;

/* ************************************************************************** */
/*                        Global Variables Declaration                        */
/* ************************************************************************** */
extern console_descriptor_t *consoles[CONSOLE_NUMBER];

/* ************************************************************************** */
/*                        INLINE  Functions Delcaration                       */
/* ************************************************************************** */
/** 
* @brief Initialize the console port.
*
* The function hooks the concrete console descriptor \p hook to the 
* console port specified by \p cons.
* In other words maps the consolore port to a concrete console.
*
* @param[in] cons 	The number of the console port to be initialized, 
* 			must less than \ref CONSOLE_NUMBER.
* @param[in] hook 	The concrete console descriptor.
* 
* @return 	\todo Write the return specification.
*
* @pre		The \p hook must be properly set before calling this function.
*/
COMPILER_INLINE
int console_init(uint8_t cons, console_descriptor_t *hook)
{
	if (cons >= CONSOLE_NUMBER)
		return -1;
	consoles[cons] = hook;
	return 0;
}


/** 
* @brief Call the concrete console open.
* 
* @param[in] cons 	A valid console port identifier.
* 
* @return 	\todo Write the return specification.
*
* @pre		The \ref console_init must be called on the same \p cons 
* 		port identifier.
*/
COMPILER_INLINE
int console_open(uint8_t cons)
{
	if (consoles[cons]->open != NULLP)
		return consoles[cons]->open(consoles[cons]->params);
	else
		return -1;
}

/** 
* @brief Write bytes to console.
*
* The function attempts to write \p length bytes via the console port,
* using the hooked concrete console implementation.
* 
* @param[in] cons 	A valid console port identifier.
* @param[in] mesg 	The pointer to the source buffer.
* @param[in] length 	The number of bytes to write.
* 
* @return 	\todo Write the return specification.
*
* @pre		The \ref console_init and the \ref console_open functions
* 		must be called on the same \p cons port identifier.
*/
COMPILER_INLINE
int console_write(uint8_t cons, const uint8_t *mesg, uint16_t length)
{
	if (consoles[cons]->write != NULLP)
		return consoles[cons]->write(consoles[cons]->params, mesg, length);
	else
		return -1;
}

/** 
* @brief Read bytes from console.
* 
* The function attempts to read \p length bytes via the console port into the
* destination buffer, using the hooked concrete console implementation.
*
* @param[in]  cons 	A valid console port identifier.
* @param[out] mesg 	The pointer to destination buffer.
* @param[in]  length 	The number of bytes to read.
* @param[out] read 	A pointer to store the actual amount of bytes
*			written into the \p mesg buffer. If it is \c NULL the
*			is ignored.
* 
* @return 	\todo Write the return specification.
*
* @pre		The \ref console_init and \ref console_open functions
* 		must be called on the same \p cons port identifier.
*/
COMPILER_INLINE
int console_read(uint8_t cons, uint8_t *mesg, uint16_t length, uint16_t *read)
{
	if (consoles[cons]->read != NULLP)
		return consoles[cons]->read(consoles[cons]->params, mesg, length, read);
	else
		return -1;
}

/** 
* @brief Call the concrete console close.
* 
* @param[in] cons 	A valid console port identifier.
* 
* @return 	\todo Write the return specification.
*
* @pre		The \ref console_init and \ref console_open functions
* 		must be called on the same \p cons port identifier.
*/
COMPILER_INLINE
int console_close(uint8_t cons)
{
	if (consoles[cons]->close != NULLP)
		return consoles[cons]->close(consoles[cons]->params);
	else
		return -1;
}

/* TODO: document the functions below */

COMPILER_INLINE 
void console_puts(uint8_t cons, const char *str)
{
	uint16_t i = 0;

	while (str[i++] != '\0') ;
	console_write(cons, (uint8_t *) str, i);
}

COMPILER_INLINE void console_sprint_u8(uint8_t data, char *out)
{
	out[3] = '\0';
	out[2] = '0' + (data % 10);
	out[1] = '0' + ((data / 10) % 10);
	out[0] = '0' + ((data / 100) % 10);
}

COMPILER_INLINE void console_sprint_u16(uint16_t data, char *out)
{
	out[5] = '\0';
	out[4] = '0' + (data % 10);
	out[3] = '0' + ((data / 10) % 10);
	out[2] = '0' + ((data / 100) % 10);
	out[1] = '0' + ((data / 1000) % 10);
	out[0] = '0' + ((data / 10000) % 10);
}

COMPILER_INLINE void console_sprint_u32(uint32_t data, char *out)
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

COMPILER_INLINE void console_sprint_d8(int8_t data, char *out)
{
	out[4] = '\0';
	out[3] = '0' + (data % 10);
	out[2] = '0' + ((data / 10) % 10);
	out[1] = '0' + ((data / 100) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void console_sprint_d16(int16_t data, char *out)
{
	out[6] = '\0';
	out[5] = '0' + (data % 10);
	out[4] = '0' + ((data / 10) % 10);
	out[3] = '0' + ((data / 100) % 10);
	out[2] = '0' + ((data / 1000) % 10);
	out[1] = '0' + ((data / 10000) % 10);
	out[0] = data < 0 ? '-' : ' ';
}

COMPILER_INLINE void console_sprint_d32(int32_t data, char *out)
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

#endif	/* USE_CONSOLE */
#endif	/* __console_h__ */
