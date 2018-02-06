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

/*
 * Author: 2006 Paolo Gai
 * CVS: $Id: ee_mcu.h,v 1.2 2008/07/24 14:26:55 francesco Exp $
 */

#ifndef __INCLUDE_NIOSII_MCU_H__
#define __INCLUDE_NIOSII_MCU_H__

#include "system.h"
#include "altera_avalon_timer_regs.h"

/*************************************************************************
 Time handling
 *************************************************************************/

/* Time types
 *
 * This is the type used to store the circular timer. It is in the MCU
 * because it highly depends on the hardware timers which are present 
 * in a particular microcontroller version.
 *
 * There are two TIME types, an unsigned type, typically used to store
 * time values since they are read from a register which is
 * traditionally considered as unsigned, and a signed type, which is
 * used in the EDF comparisons.
 */


#ifndef EE_TIME
#define EE_TIME EE_UINT32
#endif

#ifndef EE_STIME
#define EE_STIME EE_INT32
#endif

/* 40 us @ 50 Mhz */
#ifndef EE_TIMER_MINCAPACITY
#define EE_TIMER_MINCAPACITY       2000
#endif

#define EE_TIMER_MAXFUTUREVALUE    0x7fffffff
#define EE_TIMER_LIFETIME          0xffffffff

/*
 This function initialize the timer used for the timing reference as
 freerunning.  The timers will be used for the EDF/FRSH timing reference.
*/

#ifndef __PRIVATE_TIME_INIT__
void EE_time_init(void);
#endif

#ifndef __PRIVATE_HAL_GETTIME__
EE_TIME EE_hal_gettime(void);
#endif


/* This function is used to initialize the two timers used for 
 * budget exaustion and for the recharging queue
 */
#if defined(__FRSH__)
void EE_frsh_time_init(void);
#endif

#if defined(__HR__)
void EE_hr_time_init(void);
#endif

#endif  // initial include
