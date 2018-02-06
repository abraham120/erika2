/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
* @file 	enc28j60_time.h
* @brief 	ENC28J60 driver - Time debug library. 
* @author 	Dario Di Stefano
* @date 	2010
*/ 

#ifndef __ENC28J60_TIME_DEBUG_H__
#define __ENC28J60_TIME_DEBUG_H__

#ifdef __ENC28J60_TIME_DEBUG__

#include <stdio.h>
#include <string.h>
#ifdef	__CORTEX_MX__
#if	( \
  !defined(EE_SYSTEM_TIMER_DEVICE) || \
  ( EE_SYSTEM_TIMER_DEVICE != EE_CORTEX_MX_SYSTICK ) \
)
#error "ENC28J60_TIME_DEBUG ERROR: SysTick based SystemTimer is required!"
#endif
#else
/* Platform description */
#include <system_conf.h>
#endif

#define enc28j60_time_diff_ms(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000))
#define enc28j60_time_diff_us(from,to)  ((EE_UINT32)((from) - (to)) / (EE_UINT32)(CPU_FREQUENCY / 1000000))

/**
	@brief	This functions returns the value of the freetimer counter.
*/
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_enc28j60_read_freetimer(void)
{
#ifdef	__CORTEX_MX__
	return EE_systick_get_value();
#else
	EE_UINT32 time_val;
	EE_freetimer_get_value(&time_val);
	return time_val;
#endif
}

enum{	
	ENC28J60_START_MAC_FLUSH_WAIT,
	ENC28J60_START_MAC_FLUSH_RETX,
	ENC28J60_START_GET_ARRAY,
	ENC28J60_START_PUT_ARRAY,
	ENC28J60_END_MAC_FLUSH_WAIT,
	ENC28J60_END_MAC_FLUSH_RETX,
	ENC28J60_END_GET_ARRAY,
	ENC28J60_END_PUT_ARRAY,
	ENC28J60_TS_BUFFER_SIZE };
	
extern EE_UINT32 enc28j60_ts_buffer[ENC28J60_TS_BUFFER_SIZE];

/**
	@brief	This functions writes a time value in the time buffer.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_write_timestamp(EE_UINT32 id)
{
	enc28j60_ts_buffer[id] = EE_enc28j60_read_freetimer();
}

/**
	@brief	This functions reads time values from the time buffer.
*/
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_enc28j60_read_timestamp(EE_UINT32 id)
{
	return enc28j60_ts_buffer[id];
}

/**
	@brief	This functions initializes time buffer.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_reset_timestamp(void)
{
	int i;
	for(i=0; i<ENC28J60_TS_BUFFER_SIZE; i++)
		enc28j60_ts_buffer[i] = 0;
}

#else

#define EE_enc28j60_write_timestamp(id)
#define EE_enc28j60_read_timestamp(id)	-1
#define EE_enc28j60_reset_timestamp()

#endif

#endif	//__ENC28J60_TIME_DEBUG_H__


