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
 * Author: 2013 Bruno Morelli
 */

#ifndef EE_CAX_SPINLOCK_H__
#define EE_CAX_SPINLOCK_H__

#include "cpu/common/inc/ee_compiler_gcc.h"

typedef struct {
	volatile EE_UINT32 lock;
} EE_SPINLOCK;

/** @brief Type for spinlocks: an ID */
typedef EE_UINT32 EE_TYPESPIN;

typedef EE_SPINLOCK           EE_TYPESPINVALUE;
typedef EE_TYPESPINVALUE  * EE_TYPESPINVALUEREF;
extern EE_TYPESPINVALUEREF const EE_hal_spinlock_value[];
typedef EE_SPINLOCK           EE_TYPESPINSTATUS;
extern EE_TYPESPINSTATUS EE_hal_spinlock_status[];

#define SEV "sev\n"

#if __ARM_ARCH__ >= 7
#define isb() __asm__ __volatile__ ("isb" : : : "memory")
#define dsb() __asm__ __volatile__ ("dsb" : : : "memory")
#define dmb() __asm__ __volatile__ ("dmb" : : : "memory")
#else
#define isb() __asm__ __volatile__ ("" : : : "memory")
#define dsb() __asm__ __volatile__ ("mcr p15, 0, %0, c7, c10, 4" \
				    : : "r" (0) : "memory")
#define dmb() __asm__ __volatile__ ("" : : : "memory")
#endif

__INLINE__ void dsb_sev(void)
{
#if __ARM_ARCH__ >= 7
	__asm__ __volatile__ (
		"dsb\n"
		SEV
	);
#else
	__asm__ __volatile__ (
		"mcr p15, 0, %0, c7, c10, 4\n"
		SEV
		: : "r" (0)
	);
#endif
}


__INLINE__ void __ALWAYS_INLINE__ EE_cax_spin_lock(EE_SPINLOCK *lock)
{
	unsigned long tmp;

	__asm__ volatile(
"1: 	ldrex 		%0, [%1]\n"
" 	teq 		%0, #0\n"
"	wfene\n"
"	strexeq 	%0, %2, [%1]\n"
"	teqeq 		%0, #0\n"
"	bne 		1b"
	: "=&r" (tmp)
	: "r" (&lock->lock), "r" (1)
	: "cc");

	dmb();
}

__INLINE__ void __ALWAYS_INLINE__ EE_cax_spin_in(EE_TYPESPIN spin_id)
{
	EE_cax_spin_lock(&(EE_hal_spinlock_status[spin_id]));
}

__INLINE__ void EE_cax_spin_unlock(EE_SPINLOCK *lock)
{
	__asm__ volatile(
"	str	%1, [%0]\n"
	:
	: "r" (&lock->lock), "r" (0)
	: "cc");

	dsb_sev();
}

__INLINE__ void __ALWAYS_INLINE__ EE_cax_spin_out(EE_TYPESPIN spin_id)
{
	EE_cax_spin_unlock(&EE_hal_spinlock_status[spin_id]);
}


typedef enum EE_cax_core_id {
  OS_CORE_ID_0 = 0,
  OS_CORE_ID_MASTER = OS_CORE_ID_0,
  OS_CORE_ID_1 = (OS_CORE_ID_MASTER + 1),
  OS_CORE_ID_2 = (OS_CORE_ID_MASTER + 2),
  OS_CORE_ID_3 = (OS_CORE_ID_MASTER + 3),
  OS_CORE_ID_4 = (OS_CORE_ID_MASTER + 4),
  OS_CORE_ID_5 = (OS_CORE_ID_MASTER + 5),
  OS_CORE_ID_6 = (OS_CORE_ID_MASTER + 6),
  OS_CORE_ID_7 = (OS_CORE_ID_MASTER + 7),
} EE_TYPECOREID;

#define OS_CORE_ID_INVALID ((EE_TYPECOREID)-1)

/* Map Spin Locks API on HAL */
#define EE_hal_spin_in                        EE_cax_spin_in
#define EE_hal_spin_out                       EE_cax_spin_out
#define EE_hal_IRQ_interprocessor_served(cpu) ((void)0)
#define EE_CAX_IPC_INT                        10
#define EE_hal_IRQ_interprocessor(cpu)        EE_cax_signal(cpu, EE_CAX_IPC_INT)

/* shared stuff sections */
#define EE_SHARED_CDATA  EE_COMPILER_SECTION("ee_mcglobalc")
#define EE_SHARED_UDATA  EE_COMPILER_SECTION("ee_mcglobald")
#define EE_SHARED_IDATA  EE_COMPILER_SECTION("ee_mcglobald")

#endif /* EE_CAX_SPINLOCK_H__ */
