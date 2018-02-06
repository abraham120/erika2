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
 * Author: 2002 Paolo Gai
 * CVS: $Id: ee_semwait.c,v 1.2 2006/12/03 22:07:50 pj Exp $
 */

#include "ee_internal.h"

/* WaitSem:
   - can be called from an extended task only
   - the task state is put to wait until a call to PostSem wakes it up
   - if the task blocks -> reschedulig + internal resource released
   - returns (only extended status)
       E_OS_RESOURCE task occupies a resource
       E_OS_ACCESS   if the task is not an extended task
       E_OS_CALLEVEL called at interrupt level
*/


#if defined(__OO_ECC1__) || defined(__OO_ECC2__)
#ifndef __PRIVATE_WAITSEM__

StatusType EE_oo_WaitSem( SemRefType Sem )
{
  /* Error Value */
  register StatusType ev;
  TaskType current;

  /* Primitive Lock Procedure */
  EE_OS_DECLARE_AND_ENTER_CRITICAL_SECTION();

  EE_ORTI_set_service_in(EE_SERVICETRACE_WAITSEM);

  EE_as_monitoring_the_stack();

  current = EE_stk_queryfirst();

#ifdef EE_SERVICE_PROTECTION__
  /* [OS093]: If interrupts are disabled/suspended by a Task/OsIsr and the
      Task/OsIsr calls any OS service (excluding the interrupt services)
      then the Operating System shall ignore the service AND shall return
      E_OS_DISABLEDINT if the service returns a StatusType value. */
  if ( EE_oo_check_disableint_error() ) {
    ev = E_OS_DISABLEDINT;
  } else
#endif /* EE_SERVICE_PROTECTION__ */

#if defined(__OO_EXTENDED_STATUS__) || defined(EE_SERVICE_PROTECTION__)
  /* check for a call at interrupt level:
   * Note: this must be the FIRST error check!!! */
  if ( (EE_hal_get_IRQ_nesting_level() != 0U) || (current == EE_NIL) ||
  (EE_as_get_execution_context() > TASK_Context) )
  {
    ev = E_OS_CALLEVEL;
  } else
#ifndef __OO_NO_RESOURCES__
  /* check for busy resources */ 
  if ( EE_th_resource_last[current] != EE_UREG_MINUS1 ) {
    ev = E_OS_RESOURCE;
  } else
#endif /* __OO_NO_RESOURCES__ */

  /* check if the task is an extended task */
  if ( EE_th_is_extended[current] == EE_FALSE) {
    ev = E_OS_ACCESS;
  } else
#endif /* __OO_EXTENDED_STATUS__ */

  /* handle a local semaphore queue */
  /* check if we have to wait */
  if ( Sem != NULL ) {
#if defined(EE_AS_OSAPPLICATIONS__) && (defined(EE_SERVICE_PROTECTION__) &&\
  defined(__EE_MEMORY_PROTECTION__))
    /* [SWS_Os_00051]: If an invalid address (address is not writable by this
        OS-Application) is passed as an out-parameter to an Operating System
        service, the Operating System module shall return the status code
        E_OS_ILLEGAL_ADDRESS. (SRS_Os_11009, SRS_Os_11013) */
    if ( !OSMEMORY_IS_WRITEABLE(EE_hal_get_app_mem_access(EE_as_active_app,
      Sem, sizeof(*Sem))) )
    {
      ev = E_OS_ILLEGAL_ADDRESS;
      returnvalue = -1;
    } else {
#else /* EE_AS_OSAPPLICATIONS__ && __EE_MEMORY_PROTECTION__ &&
  EE_SERVICE_PROTECTION__ */
    {
#endif /* EE_AS_OSAPPLICATIONS__ && __EE_MEMORY_PROTECTION__ &&
  EE_SERVICE_PROTECTION__ */
      if ( Sem->count != 0U ) {
        Sem->count--;
      } else {
        /* Prepare current Task to block */
        EE_oo_prepare_to_block();

        /* queue the task inside the semaphore queue */
        if ( Sem->first != EE_NIL ) {
          /* the semaphore queue is not empty */
          EE_th_next[Sem->last] = current;
        } else {
          /* the semaphore queue is empty */
          Sem->first = current;
        }

        Sem->last = current;
        EE_th_next[current] = EE_NIL;

        /* then, the task will be woken up by a PostSem using a EE_hal_stkchange... */

        /* Reschedule next task:
         * check if there is to schedule a ready thread or pop a preempted
         * thread 
         */
        EE_oo_reschedule_on_block();
      }
      ev = E_OK;
    }
  } else {
    ev = E_OS_PARAM_POINTER;
  }

  if ( ev != E_OK )
  {
    EE_OS_PARAM(os_sem);
    EE_OS_PARAM_REF(os_sem, sem_ref, Sem);
    EE_os_notify_error(OSServiceId_WaitSem, os_sem,
      EE_OS_INVALID_PARAM, EE_OS_INVALID_PARAM, ev);
  }

  EE_ORTI_set_service_out(EE_SERVICETRACE_WAITSEM);

  EE_OS_EXIT_CRITICAL_SECTION();

  return ev;
}

#endif /* __PRIVATE_WAITSEM__ */
#endif /* defined(__OO_ECC1__) || defined(__OO_ECC2__) */

