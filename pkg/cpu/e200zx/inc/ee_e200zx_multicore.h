/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Multicore support
 * Author: 2011 Bernardo  Dal Seno
 *         2012 Francesco Esposito
 */

#ifndef __INCLUDE_E200ZX_MULTICORE_H__
#define __INCLUDE_E200ZX_MULTICORE_H__

#ifdef __MSRP__

/* Temporary workaround, to make compile Multicore PPC, until full AS porting
   will be completed */
#define EE_PRIVATE_GETCOREID__

#ifdef __MPC5668G__
#include <mcu/freescale_mpc5668/inc/ee_dual.h>
#define EE_hal_spin_in EE_mpc5668_spin_in
#define EE_hal_spin_out EE_mpc5668_spin_out
#define EE_hal_IRQ_interprocessor_served(cpu) EE_mpc5668_ack_signal(cpu)
#define EE_hal_IRQ_interprocessor(cpu) EE_mpc5668_signal_cpu(cpu)
#define EE_E200ZX_INTER_IRQ_LEVEL(cpu) EE_MPC5668_INTER_IRQ_LEVEL(cpu)
/*#define EE_E200ZX_DUAL_SET_INT_PRIO(level, proc, pri) \
			EE_mpc5668_set_int_prio(level, proc, pri)*/

#elif EE_MPC5643L
#include <mcu/freescale_mpc5643l/inc/ee_dual.h>
#define EE_hal_spin_in EE_mpc5643l_spin_in
#define EE_hal_spin_out EE_mpc5643l_spin_out
#define EE_hal_IRQ_interprocessor_served(cpu) EE_mpc5643l_ack_signal(cpu)
#define EE_hal_IRQ_interprocessor(cpu) EE_mpc5643l_signal_cpu(cpu)
#define EE_E200ZX_INTER_IRQ_LEVEL(cpu) EE_MPC5643L_INTER_IRQ_LEVEL(cpu)
/* proc not necessary for mpc5643l */
/*#define EE_E200ZX_DUAL_SET_INT_PRIO(level, proc, pri) \
			EE_mpc5643l_set_int_prio(level, pri)*/

#endif /* __MPC5668G__ */


/*************************************************************************
 System startup
 *************************************************************************/

/** @brief ID type for cores */
typedef enum EE_tc_core_id {
  OS_CORE_ID_0 = 0x0,
  OS_CORE_ID_MASTER = OS_CORE_ID_0,
  OS_CORE_ID_1 = (OS_CORE_ID_MASTER + 0x1),
} EE_TYPECOREID;

typedef struct ee_barrier {
	volatile EE_UINT32 value;
} EE_TYPEBARRIER;

/*
 * New type added to allow RT-Druid providing the same generated
 * code for different architectures (using and not using this type)
 */
typedef EE_UINT32           EE_TYPESPINSTATUS;

/* Synchronize on the given barrier.  Wait until all CPUs have called this
 * function on the same barrier. */
void EE_e200zx_sync_barrier(EE_TYPEBARRIER *bar);

/* TODO: Add syncronization support for AS multicore StartOs requirements */
#define EE_AS_MULTICORE_NO_SYNC
#define EE_hal_sync_barrier(bar,mask) ((void)0)

/* Startup barrier data */
#ifdef USE_PRAGMAS
	#if EE_CURRENTCPU == 0

	#pragma section EE_SHARED_NOTINIT_BEGIN
	#pragma section EE_SHARED_FAST_NOTINIT_BEGIN
	extern EE_TYPEBARRIER EE_e200zx_start_barrier;
        #pragma section EE_SHARED_END
        #pragma section EE_SHARED_FAST_OR_SLOW_END

	#else

        #pragma section EE_SHARED_NOTINIT_BEGIN
	#pragma section EE_SHARED_SLOW_NOTINIT_BEGIN
	extern EE_TYPEBARRIER EE_e200zx_start_barrier;
        #pragma section EE_SHARED_END
        #pragma section EE_SHARED_FAST_OR_SLOW_END

	#endif
#else
extern EE_TYPEBARRIER EE_SHARED_UDATA EE_e200zx_start_barrier;
#endif


#endif /* __MSRP__ */

#endif /* __INCLUDE_E200ZX_MULTICORE_H__ */
