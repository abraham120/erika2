/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
 
 /** 
    @file      util.c
    @author    Dario Di Stefano
    @date      2011
*/

/* RT-Kernel */
#include <ee.h>
#include <cpu/pic32/inc/ee_utils.h>
#include "mcu/microchip_pic32/inc/ee_timer.h"
/* console */
#include <stdio.h>
#include <stdarg.h>
#include "console_serial.h"
/* Other libraries */
#include "util.h"


/* ================================================================================= */
/* SERIAL INTERFACE */
/* ================================================================================= */

/* A printf-like function */
void myprintf(const char *format, ...)
{
    EE_pic32_disableIRQ();
    const char printf_trunc[] = "..[TRUNCATED]..\n";
    char str[MAXCHARS];
    int len;
    va_list args;
    va_start(args, format);
    len = vsnprintf(str, MAXCHARS, format, args);
    va_end(args);
    if (len > MAXCHARS - 1) {
        /* vsnptintf() returns the number of characters needed */
	console_write(MY_FIRST_CONSOLE, str, MAXCHARS - 1 );
	console_write(MY_FIRST_CONSOLE, printf_trunc, sizeof(printf_trunc) - 1);

    } else {
        console_write(MY_FIRST_CONSOLE,str, len);
    }
    EE_pic32_enableIRQ();
}

void hex_dump(const void *base, int size)
{
    const unsigned char *p = base;
    char lbuf[16*3+4];
    int k, j;

    j = 0;
    for (k = 0; k < size; ++k) {
        sprintf(&lbuf[j], "%02x ", p[k]);
        j += 3;
        if (0 == ((k+1) % 16) || k == size-1) {
            lbuf[j++] = '\n';
            lbuf[j] = 0;
            console_write(MY_FIRST_CONSOLE, lbuf, j);
            j = 0;
        } else if (0 == ((k+1) % 8)) {
            lbuf[j++] = ' ';
        }
    }
}

/* ================================================================================= */
/* TIMER UTILS */
/* ================================================================================= */

EE_UINT32 elapsed(EE_UINT32 from, EE_UINT32 to)
{
	return to - from;
}

EE_UINT32 elapsed_us(EE_UINT32 from, EE_UINT32 to)
{
	EE_UINT32 cpu_freq = EE_get_peripheral_clock();
	return (to - from) / (cpu_freq / 1000000U);
}

EE_UINT32 elapsed_ms(EE_UINT32 from, EE_UINT32 to)
{
	EE_UINT32 cpu_freq = EE_get_peripheral_clock();
	return (to - from) / (cpu_freq / 1000U);
}

EE_UINT32 get_time_stamp(void)
{
	EE_UINT32 t;
	t = EE_pic32_get_core_timer_value();
	return t;
}

void msleep(EE_UINT32 ms)
{
	EE_UINT32 start, curr;
	EE_UINT32 cpu_freq = EE_get_peripheral_clock();
	start = get_time_stamp();
	do {
		curr = get_time_stamp();
	} while (elapsed(start, curr) < (ms * (cpu_freq / 1000U)));
}














