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
 * fake-druid eecfg.c
 *
 * Author: 2013 Gianluca Franchino */

 #include "ee.h"




/***************************************************************************
 *
 * Kernel ( CPU 0 )
 *
 **************************************************************************/
    /* Definition of task's body */
    DeclareTask(TaskTMR0);
    DeclareTask(TaskCMT0);
    DeclareTask(TaskMTU0);
    DeclareTask(TaskTMR1);
    DeclareTask(TaskCMT1);
    DeclareTask(TaskMTU1);

    const EE_FADDR EE_hal_thread_body[EE_MAX_TASK] = {
    		(EE_FADDR)FuncTaskTMR0, 		/* thread TaskTMR0 */
    		(EE_FADDR)FuncTaskCMT0, 		/* thread TaskCMT0 */
    		(EE_FADDR)FuncTaskMTU0, 		/* thread TaskMTU0 */
    		(EE_FADDR)FuncTaskTMR1, 		/* thread TaskTMR1 */
    		(EE_FADDR)FuncTaskCMT1, 		/* thread TaskCMT1 */
    		(EE_FADDR)FuncTaskMTU1 		 	/* thread TaskMTU1 */

    };

    /* ready priority */
    const EE_TYPEPRIO EE_th_ready_prio[EE_MAX_TASK] = {
    		0x1U, 		/* thread TaskTMR0 */
    		0x1U, 		/* thread TaskCMT0 */
    		0x1U, 		/* thread TaskMTU0 */
    		0x1U, 		/* thread TaskTMR1 */
    		0x1U, 		/* thread TaskCMT1 */
    		0x1U 		/* thread TaskMTU1 */
    };

    /* dispatch priority */
    const EE_TYPEPRIO EE_th_dispatch_prio[EE_MAX_TASK] = {
    		0x1U, 		/* thread TaskTMR0 */
            0x1U, 		/* thread TaskCMT0 */
            0x1U, 		/* thread TaskMTU0 */
            0x1U, 		/* thread TaskTMR1 */
            0x1U, 		/* thread TaskCMT1 */
            0x1U 		/* thread TaskMTU1 */
    };

    /* thread status */
    #if defined(__MULTI__) || defined(__WITH_STATUS__)
        EE_TYPESTATUS EE_th_status[EE_MAX_TASK] = {
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY,
            EE_READY
        };
    #endif

    /* next thread */
    EE_TID EE_th_next[EE_MAX_TASK] = {
    		EE_NIL,
    		EE_NIL,
    		EE_NIL,
    		EE_NIL,
    		EE_NIL,
    		EE_NIL
    };

    EE_TYPEPRIO EE_th_nact[EE_MAX_TASK];
    /* The first stacked task */
    EE_TID EE_stkfirst = EE_NIL;

    /* The first task into the ready queue */
    EE_TID EE_rqfirst  = EE_NIL;

    /* system ceiling */
    EE_TYPEPRIO EE_sys_ceiling= 0x0000U;

