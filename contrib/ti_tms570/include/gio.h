/** @file gio.h
*   @brief GIO Driver Definition File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __GIO_H__
#define __GIO_H__

#include "reg_gio.h"


/** 
 *  @defgroup GIO GIO
 *  @brief General-Purpose Input/Output Module.
 *  
 *  The GIO module provides the family of devices with input/output (I/O) capability. 
 *  The I/O pins are bidirectional and bit-programmable.
 *  The GIO module also supports external interrupt capability.
 *
 *	Related Files
 *   - reg_gio.h
 *   - gio.h
 *   - gio.c
 *  @addtogroup GIO
 *  @{
 */
 
/* GIO Interface Functions */
void gioInit(void);
void gioSetDirection(gioPORT_t *port, uint32 dir);
void gioSetBit(gioPORT_t *port, uint32 bit, uint32 value);
void gioSetPort(gioPORT_t *port, uint32 value);
uint32 gioGetBit(gioPORT_t *port, uint32 bit);
uint32 gioGetPort(gioPORT_t *port);
void gioToggleBit(gioPORT_t *port, uint32 bit);
void gioEnableNotification(uint32 bit);
void gioDisableNotification(uint32 bit);
void gioNotification(sint32 bit);

/**@}*/
#endif
