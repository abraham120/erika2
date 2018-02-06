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
 * Author: 2004 Paolo Gai
 * CVS: $Id: ee_start.c,v 1.17 2006/04/23 12:45:49 pj Exp $
 */

#include "ee_internal.h"

#ifdef __RN__
/* This is the Interprocessor IRQ handler, that basically is an interruptible
 * call to the remote notification handler.
 * The question is: can this function be optimized?
 */
static void EE_nios2_IIRQ_handler(void *arg, alt_u32 intno)
{
  alt_u32 pending;
  pending = alt_irq_interruptible(EE_IPIC_IRQ);
  EE_rn_handler();
  alt_irq_non_interruptible(pending);
}
#endif

/* the mutex is only needed when the spin lock is based upon altera mutexes 
 * or when the sync at boot is implemented using a mutex 
 */
#if defined(__NIOS2_SPIN_AVALON_MUTEX__)
alt_mutex_dev* EE_nios2_avalon_mutex;
#endif


#ifdef __OO_EXTENDED_STATUS__
EE_TYPEBOOL EE_cpu_startos(void)
#else
void EE_cpu_startos(void)
#endif
{
  /* Register the Interprocessor IRQ handler */
#ifdef __RN__
  alt_irq_register( EE_IPIC_IRQ, 0, EE_nios2_IIRQ_handler );
#endif



  /* enable interrupts for the local IPIC */
#ifdef __NIOS2_IPIC_PIO__
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK( EE_IPIC_INPUT_BASE, 1 );
#endif



#if defined(__NIOS2_SPIN_AVALON_MUTEX__)
  /* Mutex device initialization
   * The mutex needs to be opened before the system can use it.
   */
  EE_nios2_avalon_mutex = altera_avalon_mutex_open(EE_NAME_MUTEX_DEVICE);
  
#ifdef __OO_EXTENDED_STATUS__
  if (!EE_nios2_avalon_mutex)
    return 1;
#endif
#endif // __NIOS2_SPIN_AVALON_MUTEX__



#if defined(__NIOS2_SPIN_AVALON_MUTEX__) && !defined(__NIOS2_NO_STARTUP_BARRIER__)	
  /* the synchronization is done using the Altera avalon mutex. In this case, 
   * the Altera Avalon Mutex is initialized in a way that CPU0 owns it when 
   * the system boots up.
   *
   * The owner register of the Avalon mutex must store the value of
   * the CPUID of the master CPU
   *
   */
  if (EE_has_startup_barrier) {
    if (EE_CURRENTCPU)
      {
	altera_avalon_mutex_lock( EE_nios2_avalon_mutex, 1);
	EE_startsynclocation--;
	altera_avalon_mutex_unlock( EE_nios2_avalon_mutex );
      }
    else
      {
	/* CPU0, when it starts the mutex is already locked */
	EE_startsynclocation = EE_MAX_CPU-1;
	altera_avalon_mutex_unlock( EE_nios2_avalon_mutex );
      }
    
    /* wait for all the processors to start */
    while (EE_startsynclocation);
  }
#endif



#if defined(__NIOS2_SPIN_AVALON_MUTEX_DIRECT__) && !defined(__NIOS2_NO_STARTUP_BARRIER__)
  /* the synchronization is done using the Altera avalon mutex. In this case, 
   * the Altera Avalon Mutex is initialized in a way that CPU0 owns it when 
   * the system boots up.
   *
   * The owner register of the Avalon mutex must store 0. Note that 0
   * is the Master CPU value for the constant EE_CURRENTCPU
   *
   */
  if (EE_has_startup_barrier) {
    if (EE_CURRENTCPU)
      {
	EE_altera_mutex_spin_in();
	EE_startsynclocation--;
	EE_altera_mutex_spin_out();
      }
    else
      {
	/* CPU0, when it starts the mutex is already locked */
	EE_startsynclocation = EE_MAX_CPU-1;
	EE_altera_mutex_spin_out();
      }
    
    /* wait for all the processors to start */
    while (EE_startsynclocation);
  }
#endif



#ifdef __OO_EXTENDED_STATUS__
  return 0;
#endif
}
