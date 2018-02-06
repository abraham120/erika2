/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * Author: Gianluca Franchino 2012
 */
 
#ifndef __BM_ERIKA_CONFIG_H__
#define __BM_ERIKA_CONFIG_H__

#include "ee.h"

#ifndef __TIMING_TEST_H__
#include "cpu/cortex_mx/inc/ee_irq.h"
#endif

//#include "cpu/common/inc/ee_stdint.h"

#define activate_task(task) ActivateTask(task)

#ifdef __FP__
#define terminate_task()	((void)0)
#else
#define terminate_task() TerminateTask()
#endif	

#ifndef ANALISYS_RES_DIM
#define ANALISYS_RES_DIM 9 
#endif

#ifndef TIMINGTEST_NUM_RECORDS
#define TIMINGTEST_NUM_RECORDS 50
#endif


#ifndef BM_MAX_LOOPS
#define BM_MAX_LOOPS  TIMINGTEST_NUM_RECORDS
#endif


static volatile unsigned int bm_loops = 0;
#ifdef __FP__
void bm_set_end();
#define bm_stop() return
#else
#define bm_stop() ShutdownOS(E_OK)
#endif

NORETURN __INLINE__ void bm_rtos_init(void)
{

	/*Initialize some Erika stuffs*/
	EE_system_init();
	
#ifdef __FP__
	activate_task(BM_task);
	
	for (;;) {  
	/* Background activities, if any, go here... */
		if (bm_loops == BM_MAX_LOOPS) {
			bm_set_end();
		}	
	}
#else
	/*
	 * Note: StartOs will active BM_task if we
	 * set AUTOSTART=TRUE in the oil file.
	 */
	StartOS(OSDEFAULTAPPMODE);
#endif

}


#endif /*__BM_ERIKA_CONFIG_H__*/

