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
 @file qf_port.c
 @author Gianluca Franchino
 @date 2014
 */

#include "qf_pkg.h"
#include "qassert.h"

#include "eecfg.h"

Q_DEFINE_THIS_MODULE("qf_port")

#ifndef NULL
#define NULL 0
#endif


/* Global objects ----------------------------------------------------------*/

void *pdata[EE_MAX_TASK];


/*..........................................................................*/
void QF_init(void) {
	
	unsigned int i;
	
	/*Initialize to NULL the array containing the pointers to AOs.*/
	for (i = 0; i < EE_MAX_TASK; i++) {
		pdata[i] = NULL; 
	}
	
}
/*..........................................................................*/
int_t QF_run(void) {

	QF_onStartup();
	
	StartOS(OSDEFAULTAPPMODE);
	
	Q_ERROR();            /* The Erika kernel should never returns to the caller 
    						from StartOS(). */
    
    return (int_t)0;      /* return success */
}

/*..........................................................................*/
void QF_stop(void) {
	/* stop the loop in QF_run() */
}
/*..........................................................................*/
void task_function(void *pdata) { /* routine called by each task. */
  
	while (((QActive *)pdata)->thread != (uint8_t)0) {
        QEvt const *e = QActive_get_((QActive *)pdata);
        QMSM_DISPATCH((QMsm *)pdata, e);         /* dispatch to the AO's SM */
        QF_gc(e);    /* check if the event is garbage, and collect it if so */
    }

    QF_remove_((QActive *)pdata);  /* remove this object from the framework */
}
/*..........................................................................*/
void QActive_start_(QActive *me, uint_t prio,
                    QEvt const *qSto[], uint_t qLen,
                    void *stkSto, uint_t stkSize,
                    QEvt const *ie)
{
	EE_UINT8 done = 0;
	TaskType NextTaskID = 0;
	

    Q_REQUIRE(stkSto == (void *)0);  /* Erika tasks allocate stack internally */

    QEQueue_init(&me->eQueue, qSto, qLen);
   
    me->prio = (uint8_t)prio;
    QF_add_(me);                     /* make QF aware of this active object */
    QMSM_INIT(&me->super, ie);            /* execute the initial transition */
    QS_FLUSH(); /* flush the trace buffer to the host */
    
	me->osObject = QFEvent;
 
	/*
	 * Object priority must by lower than the maximum value allowed by Erika RTOS.
	 * Note: the maximum priority number depends on the CPU register size.
	 */
#ifdef EE_UREG_SIZE
	if (me->prio > EE_UREG_SIZE * 8)		
		Q_ERROR();
#else
	if (me->prio > sizeof(EE_TYPEPRIO)* 8)		
		Q_ERROR();
#endif
	
	while (EE_MAX_TASK > NextTaskID && !done) {
		/* 
		 * Note: the association between a Task and Active Object (AO) is based 
		 * on the and priority. Thus, each time an AO is activated, the following
		 * code looks for an avaiable Task with prioirity equal 
		 
		 Priority of AO must match the priority of available task. 
		 */	
		if ((0x1 << (me->prio - 1)) & EE_th_ready_prio[NextTaskID]) {
			
			/*Check if the Task identified by NextTaskID is available.*/
			if (NULL == pdata[NextTaskID]) {
				/*This matches the AO and the Task*/
				pdata[NextTaskID] = me; 
				
				/* Note: Erika task Id starts from 0, 
				 * instead me->thread must start from 1.
				 */
				me->thread = NextTaskID + 1;
				
				done = 1;
			}
		}
		NextTaskID++;
	}
	
	/* If there are not available Tasks matching the AO priority throw an error.*/
	if (!done) {
		Q_ERROR();
	}
    
   
}

/*..........................................................................*/
void QActive_stop(QActive *me) {
    me->thread = (uint8_t)0;                /* stop the QActive thread loop */
}


