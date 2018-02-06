/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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

/*
 * Author: 2014 Arianna Avanzini
 */

#include "cpu/cortex_ax_xenpv/inc/xendebug.h"
#include "cpu/cortex_ax_xenpv/inc/ee_cax_cpu.h"

int cut_string(char *buffer, int length)
{
	int i = 0;

	for (i = 0 ; i < length ; i++)
		if (buffer[i] == 0) {
			buffer[i] = '\n';
			break;
		}

	return i+1;
}

char *itoa(int i, char *b)
{
	char const digit[] = "0123456789";
	char *p = b;
	int shifter;
	if (i < 0) {
		*p++ = '-';
		i *= -1;
	}
	shifter = i;
	do {
		++p;
		shifter = shifter / 10;
	} while(shifter);
	*p = '\0';
	do {
		*--p = digit[i%10];
		i = i / 10;
	} while(i);
	return b;
}

int strln(char *s)
{
    int i = 0;

    if (s == NULL)
	return -1;
    /* Safety: last character is always a \n */
    s[MAX_MSGLEN-1] = '\n';
    while (s[i] != '\n' && s[i] != '\0' && i < MAX_MSGLEN) i++;
    if (s[i] == '\0')
        s[i] = '\n';
    return ++i;
}

void print_number(int n)
{
	char buf[20];

	itoa(n, buf);
	printk(buf);
}
