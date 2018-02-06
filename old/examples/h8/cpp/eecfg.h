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
 * Author: 2002 Davide Cantini
 * CVS: $Id: eecfg.h,v 1.2 2007/06/01 09:02:27 pj Exp $
 */

#ifndef __EDFTEST_CONFIG_H__
#define	__EDFTEST_CONFIG_H__

#include "erikahal.h"  /* needed for EE_th_period[] */
/*
 * Kernel configuration
 */

/* used by first_thread_activation() */
const extern EE_UINT16 EE_th_period[];

/* number of threads */
#define THREAD_MAX 3

/* number of periodic threads */
#define PERIODIC_THREAD_MAX 2

/* if 0 <= TID <= (PERIODIC_THREAD_MAX-1) then TID is a periodic thread */
#define TID_thread0 0    /*  periodic */
#define TID_thread1 1    /*  periodic */
#define TID_thread2 2    /*  not periodic */

/* MUTEX definitions */

#define MUTEX_MAX  1
#define MUTEX_sync 0


#ifdef __TIMER_A_SUPPORT__
    #define TIMER_A_PERIOD  500  /* 500tick = 1ms (1tick=2us) */
#endif

	
#endif /* __EDFTEST_CONFIG_H__ */
