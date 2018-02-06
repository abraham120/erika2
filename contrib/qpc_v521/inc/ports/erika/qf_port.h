/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
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
 @file qf_port.h
 @author Gianluca Franchino
 @date 2014
 */ 

#ifndef qf_port_h
#define qf_port_h


#define QF_INT_ENABLE()		EnableAllInterrupts()
#define QF_INT_DISABLE()	DisableAllInterrupts()

#define QF_EQUEUE_TYPE              QEQueue
#define QF_OS_OBJECT_TYPE           EventMaskType
#define QF_THREAD_TYPE              TaskType

/* The maximum number of active objects in the application */
/* TODO: what's the maximum number of tasks for EE? 
 * Samek's book, on page 403 says: Currently QF_MAX_ACTIVE cannot exceed 63.
 * */
#ifdef  QF_MAX_ACTIVE

#if QF_MAX_ACTIVE > 63
#warning "Currently QF_MAX_ACTIVE cannot exceed 63!"
#undef	QF_MAX_ACTIVE
#endif

#endif

#ifndef QF_MAX_ACTIVE
#define QF_MAX_ACTIVE               63 
#endif

  /* Erika Ent. critical section operations.
   * Note: the Erika critical section must be able to nest.
   * Note: SuspendOSInterrupts()/ suspends/resumes all ISR2 type interrupts, to also 
   * suspend/resume ISR1 interrupts use SuspendAllInterrupts()/ResumeAllInterrupts()
   * See also NOTE01 below.
   */

#define QF_CRIT_ENTRY(dummy)       SuspendAllInterrupts() 
#define QF_CRIT_EXIT(dummy)        ResumeAllInterrupts() 

#include "qep_port.h"	/* QEP port, includes the master Erika Ent. include */
#include "qequeue.h"	/* Native QF event queue for deferring events */
#include "qmpool.h"		/* Erika uses native QF memory-pool */
#include "qf.h"			/* QF platform-independent public interface */

/*Routine and data structure called by each task*/
extern void *pdata[EE_MAX_TASK];
void task_function(void *pdata);

/*****************************************************************************
* interface used only inside QF, but not in applications
*/
#ifdef qf_pkg_h

/* OS-object implementation for Erika */		
	#define QACTIVE_EQUEUE_WAIT_(me_) \
		while ((me_)->eQueue.frontEvt == (QEvt *)0) {\
			QF_CRIT_EXIT();\
			WaitEvent(((me_)->osObject));\
			ClearEvent(((me_)->osObject));\
			QF_CRIT_ENTRY();\
		}
			
/*
 *	NOTE: Since Erika task IDs start from 0, but thread IDs start from 1 
 *	(because 0 means no thread), then TaskID = (me_)->thread - 1 
 */
    #define QACTIVE_EQUEUE_SIGNAL_(me_) \
		SetEvent((me_)->thread - 1,((me_)->osObject))

    #define QACTIVE_EQUEUE_ONEMPTY_(me_) ((void)0)

                                         /* native QF event pool operations */
    #define QF_EPOOL_TYPE_            QMPool
    #define QF_EPOOL_INIT_(p_, poolSto_, poolSize_, evtSize_) \
        QMPool_init(&(p_), poolSto_, poolSize_, evtSize_)
    #define QF_EPOOL_EVENT_SIZE_(p_)  ((p_).blockSize)
    #define QF_EPOOL_GET_(p_, e_, m_) ((e_) = (QEvt *)QMPool_get(&(p_), (m_)))
    #define QF_EPOOL_PUT_(p_, e_)     (QMPool_put(&(p_), e_))

#endif                                                    /* ifdef qf_pkg_h */

#endif                                                         /* qf_port_h */

/*****************************************************************************
* NOTE01: In this porting version the critical sections are protected by 
* disabling CPU interrupts. A better way would be using the Resource mechanism 
* of Erika. This avoid the priority inversion problem and longer delays that 
* disabling interrupts can cause. 
*/
