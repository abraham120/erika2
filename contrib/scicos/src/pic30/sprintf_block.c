/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010-2012 Evidence S.r.l.
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
	@file sprintf_block.c
	@brief www.scicos.org, www.scicoslab.org
	@author Giuseppe Arturi, Evidence S.r.l.
	@date 2012
*/ 
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <stdio.h>
#include <string.h>

#define IPAR_N_ARGUMENTS 0
#define IPAR_SIZES 1

#define MAX_OUT_SIZE (64)

static char buffer[MAX_OUT_SIZE + 1];

typedef enum {
	spf_parameter_type_int = 3,
	spf_parameter_type_unsigned = 6,
	spf_parameter_type_double = 1,
	spf_parameter_type_string = -1
}spf_parameter_type;

static void spf_generic(char* dst, int size, const char* fmt, void* param, 
				 spf_parameter_type type)
{
	int n;
	switch (type){
		case spf_parameter_type_int:
			n = snprintf(dst, size, fmt, *(int*)param);
			break;
		case spf_parameter_type_unsigned:
			n = snprintf(dst, size, fmt, *(unsigned*)param);
			break;
		case spf_parameter_type_double:
			n = snprintf(dst, size, fmt, *(double*)param);
			break;
		case spf_parameter_type_string:
			n = snprintf(dst, size, fmt);
			break;
		default:
			n = 0;
	}
	if (n >= 0 && n < size) {
		memset(dst+n, ' ', size - n);
	}
}

static void spf_build(char* dst, int size, const char** fmts, void** params, 
			   int* sizes, int* types, int arguments)
{
	int i, j, cur, is_string;
	for (i = 0, j = 0, cur = 0; i < arguments; ++i) {
		if (cur + sizes[i] >= size) {
			break;
		}
		is_string = (types[i] == spf_parameter_type_string);
		/*sizes[i]+1: extra char for null terminator*/
		spf_generic(dst + cur, sizes[i] + 1, fmts[i], 
			(!is_string ? params[j] : NULL), types[i]);
		if (!is_string) {
			++j;
		}
		cur += sizes[i];
	}
	dst[(cur < size?cur:size-1)] = '\0';
}

static void inout(scicos_block *block)
{
	char* dst = Getint8OutPortPtrs(block, 1);
	int size = GetOutPortSize(block, 1, 2);
	int arguments = (GetIparPtrs(block))[IPAR_N_ARGUMENTS];
	const char** fmts = (const char**)block->oparptr;
	void** params = block->inptr;
	int* sizes = &(GetIparPtrs(block))[IPAR_SIZES];
	int* types = &(GetIparPtrs(block))[IPAR_SIZES + arguments];
	if (size > MAX_OUT_SIZE) {
		return;
	}
	spf_build(buffer, size, fmts, params, sizes, types, arguments);
	memcpy(dst, buffer, size);
}

void sprintf_block(scicos_block *block, int flag)
{
	switch (flag) {
		case OutputUpdate:  /* set output */
			inout(block);
			break;
    }
}

