/*
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */
 
#include "ee.h"

#include "hal/hal_defines.h"

#include "common/eeuart.h"

/*******************************************************************************
 * Function:        void ee_console_init(EE_UINT8 console_port)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          none
 *
 * Side Effects:    None
 *
 * Overview:        This routine initializes the console.
 *                  
 * Note:            None
 ******************************************************************************/
 
void ee_console_init(EE_UINT8 port);

/*******************************************************************************
 * Function:        void ee_console_out(EE_UINT8 ch)
 *
 * PreCondition:    None
 *
 * Input:           the character to send out to the console.
 *
 * Output:          0 all right, -1 otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This routine send a character to the console.
 *                  
 * Note:            None
 ******************************************************************************/
 
void ee_console_out(EE_UINT8 ch);

/*******************************************************************************
 * Function:        void ee_console_out_str(const char *ch)
 *
 * PreCondition:    None
 *
 * Input:           the string to send out to the console.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine send a string to the console.
 *                  
 * Note:            None
 ******************************************************************************/
 
void ee_console_out_str(const char *ch);

void ee_console_out16_radix(EE_UINT16 val, int radix);

void ee_console_out32_radix(EE_UINT32 val, int radix);

void ee_console_out_radix(EE_UINT8 val, int radix);
