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
 * CVS: $Id: ee_internal.h,v 1.21 2006/04/23 12:45:49 pj Exp $
 */

#include "cpu/nios2/inc/ee_cpu.h"

#ifndef __INCLUDE_NIOS2_INTERNAL_H__
#define __INCLUDE_NIOS2_INTERNAL_H__

/*************************************************************************
 From Altera
 *************************************************************************/

#if defined(__NIOS2_SPIN_AVALON_MUTEX__)
#include <altera_avalon_mutex.h>
#endif

#if defined(__NIOS2_SPIN_AVALON_MUTEX_DIRECT__)
#include <altera_avalon_mutex_regs.h>
#endif

#ifdef __NIOS2_IPIC_PIO__
#include <altera_avalon_pio_regs.h>
#endif



/*************************************************************************
 System startup
 *************************************************************************/

/* defining this let the StartOS routine to call this function */
#define OO_CPU_HAS_STARTOS_ROUTINE

/* This function starts ths system,
 * register the IPIC and synchronize the CPUs 
 * returns 1 in case of error (typically a mutex name error)
 */
#ifdef __OO_EXTENDED_STATUS__
EE_TYPEBOOL EE_cpu_startos(void);
#else
void EE_cpu_startos(void);
#endif


/*************************************************************************
 Functions
 *************************************************************************/

/*
 * Generic Primitives
 */

/* Same as alt_irq_disable_all in altera_nios2/HAL/inc/sys/alt_irq.h */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_begin_nested_primitive(void)
{
  EE_FREG context;

  NIOS2_READ_STATUS (context);
  NIOS2_WRITE_STATUS (0);
  
  return context;
}

/* Same as alt_irq_enable_all in altera_nios2/HAL/inc/sys/alt_irq.h */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_end_nested_primitive(EE_FREG f)
{
  NIOS2_WRITE_STATUS (f);
}




/* 
 * Context Handling  
 */

/* WARNING: All these functions may be non-reentrant */

extern EE_UREG EE_hal_endcycle_next_thread;
extern EE_UREG EE_hal_endcycle_next_tos;


/* NOTE: hal_thread_tos[0]=main, hal_thread_tos[1]=thread0, ... */
#ifdef __MONO__
void EE_nios2_hal_ready2stacked(EE_ADDR thread_addr); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
    EE_nios2_hal_ready2stacked(EE_hal_thread_body[thread]);
}
#endif
#ifdef __MULTI__
void EE_nios2_hal_ready2stacked(EE_ADDR thread_addr, EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_ready2stacked(EE_TID thread)
{
    EE_nios2_hal_ready2stacked(EE_hal_thread_body[thread],
			         EE_hal_thread_tos[thread+1]);
}
#endif


/* typically called at the end of a thread instance */
#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
  EE_hal_endcycle_next_thread = 0;
  /* TID is useless */
}
#endif
#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_stacked(EE_TID thread)
{
  EE_hal_endcycle_next_tos = EE_hal_thread_tos[thread+1];
  EE_hal_endcycle_next_thread = 0;
}
#endif



#ifdef __MONO__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
  EE_hal_endcycle_next_thread = (EE_UREG)EE_hal_thread_body[thread];
}
#endif
#ifdef __MULTI__
__INLINE__ void __ALWAYS_INLINE__ EE_hal_endcycle_ready(EE_TID thread)
{
  EE_hal_endcycle_next_tos = EE_hal_thread_tos[thread+1];
  EE_hal_endcycle_next_thread = (EE_UREG)EE_hal_thread_body[thread];
}
#endif

/* typically called at the end of an interrupt */
#define EE_hal_IRQ_stacked EE_hal_endcycle_stacked
#define EE_hal_IRQ_ready EE_hal_endcycle_ready



/* called to change the active stack, typically inside blocking primitives */
/* there is no mono version for this primitive...*/
#ifdef __MULTI__
void EE_nios2_hal_stkchange(EE_UREG, EE_UREG tos_index); /* in ASM */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_stkchange(EE_TID thread)
{
    EE_nios2_hal_stkchange(0, EE_hal_thread_tos[thread+1]);
}
#endif



/*
 * Nested Interrupts Handling
 */

/* can be called with interrupt enabled */
#ifdef __ALLOW_NESTED_IRQ__
extern EE_UREG EE_IRQ_nesting_level;

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_hal_get_IRQ_nesting_level(void)
{
  return EE_IRQ_nesting_level;
}
#endif


/* 
 * OO TerminateTask related stuffs
 */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)

void EE_nios2_terminate_savestk(EE_ADDR sp, EE_ADDR realbody);
void EE_nios2_terminate_task(EE_ADDR sp) NORETURN;

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_savestk(EE_TID t)
{
  EE_nios2_terminate_savestk(&EE_terminate_data[t],
				(EE_ADDR)EE_terminate_real_th_body[t]);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_terminate_task(EE_TID t)
{
  EE_nios2_terminate_task(&EE_terminate_data[t]);
}

#endif




/*
 * Spin Locks on NIOS
 */







#ifdef __MSRP__

/*
 * EE has three ways for implementing an atomic transaction:
 *
 * 1- using the Altera Avalon Mutex component with the HAL Interface
 * 2- using the Altera Avalon Mutex component directly using the
 *    mutex registers
 * 3- using a Custom Instruction
 *
 * NOTE: There MUST be at least 1 spin for each GLOBAL mutex, +1 for
 * each CPU if the notification mechanism is used.  
 * 
 * A global mutexes use the spin lock that has the same mutex number. 
 * I.e., mutex 2 will use the spin address number 2.
 *
 * The spin locks used by the notification mechanisms of each CPU must
 * have an index greater than the iggest mutex address.
 */


#ifdef __NIOS2_SPIN_AVALON_MUTEX__

/* 
   Case 1 - using the Altera Avalon Mutex component with the HAL Interface

   The Avalon Mutex interface is used to implement a software atomic
   swap operation. The HAL interface is used to ensure compatibility
   with future versions of the Altera HAL.

   but... Note that using thread safe functions and semaphores with the
   Altera HAL is discouraged because the altera mutex internally calls
   the semaphore functions!

   Note that the cache must be disabled!!!

   About the initialization values of the spin locks...
   Bit 0 of EE_hal_spin_status[i] should be != EE_hal_spin_cpu0[i]

   For that reason, an early initialization value was 
   EE_hal_spin_status[i] = (EE_UINT32)((&EE_hal_spin_cpu0[i])+1);
   EE_hal_spin_cpu[cpu][i] = 0; for each cpu, for each i
*/

/* the name of the mutex to be used when initializing the mutex */
extern const char *EE_NAME_MUTEX_DEVICE;

/* the mutex device handle */
extern alt_mutex_dev* EE_nios2_avalon_mutex;

/* init value = all (EE_UINT32)(&EE_hal_spin_value[i][cpu])+1 */
extern EE_UINT32 EE_hal_spin_status[]; 

/* The first version of this data structure was the following:
 * init value = blank (BSS) extern EE_UINT32 EE_hal_spin_value[][EE_MAX_CPU]; 
 * 
 * That way of initializing the variable does not work when using a binary 
 * distribution, because the number of CPUs is not specified in eecfg.h as a 
 * define, but it its an external variable.
 * The data structure we are currently using is basically an array of pointers.
 * each pointer points to a vector of data.
 * 
 * The EE_hal_spin_value must point to other spinlock arrays, one for each 
 * spinlock. The spinlock array must be allocated in RAM, initialized to 0.
 */
extern EE_UINT32 * const EE_hal_spin_value[];

__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_in(EE_TYPESPIN m)
{
  register EE_UINT32 new_lock_value;
  register volatile EE_UINT32 *wait_address;
  register EE_UINT32 what_means_locked;

	new_lock_value = ((EE_UINT32)&EE_hal_spin_value[m][EE_CURRENTCPU]) |
										EE_hal_spin_value[m][EE_CURRENTCPU];

  //  wait_address = SWP(&EE_hal_spin_status[m], new_lock_value);
	altera_avalon_mutex_lock( EE_nios2_avalon_mutex, 1 );
	wait_address = (EE_UINT32 *)EE_hal_spin_status[m];
  EE_hal_spin_status[m] = new_lock_value;
	altera_avalon_mutex_unlock( EE_nios2_avalon_mutex );

  what_means_locked = ((EE_UINT32)wait_address) & 1;
  wait_address = (EE_ADDR) ( ((EE_UINT32)wait_address) & 0xFFFFFFFE );
  while (*wait_address == what_means_locked);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_out(EE_TYPESPIN m)
{
  EE_hal_spin_value[m][EE_CURRENTCPU] = !EE_hal_spin_value[m][EE_CURRENTCPU];
}

#endif



#ifdef  __NIOS2_SPIN_AVALON_MUTEX_DIRECT__

// No queuing spinlock, only Altera Mutexes
// see the comments below

__INLINE__ void __ALWAYS_INLINE__ EE_altera_mutex_spin_in(void)
{
  alt_u32 data, check;

  /* the data we want the mutex to hold */
  data = (EE_CURRENTCPU << ALTERA_AVALON_MUTEX_MUTEX_OWNER_OFST) | 1;

  do {
    /* attempt to write to the mutex */
    IOWR_ALTERA_AVALON_MUTEX_MUTEX(EE_ALTERA_MUTEX_BASE, data);
    
    check = IORD_ALTERA_AVALON_MUTEX_MUTEX(EE_ALTERA_MUTEX_BASE);
    
  } while ( check != data);
}


__INLINE__ void __ALWAYS_INLINE__ EE_altera_mutex_spin_out(void)
{
  //  IOWR_ALTERA_AVALON_MUTEX_RESET(EE_ALTERA_MUTEX_BASE, 
  //                                  ALTERA_AVALON_MUTEX_RESET_RESET_MSK);
  IOWR_ALTERA_AVALON_MUTEX_MUTEX(EE_ALTERA_MUTEX_BASE, 
				 EE_CURRENTCPU << ALTERA_AVALON_MUTEX_MUTEX_OWNER_OFST);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_in(EE_TYPESPIN m)
{
  EE_altera_mutex_spin_in();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_out(EE_TYPESPIN m)
{
  EE_altera_mutex_spin_out();
}
#endif




#ifdef __NIOS2_SPIN_AVALON_MUTEX_DIRECT_QUEUING__

/*
  NOTE: Although this is probably the right queuing spin-lock
  mechanism available, what happens is that it seems that some times
  writes to the shared memory fails, or at least that they are not
  recorded. It may be some problem related to the avalon bus error
  when using shared memory locations with cache disabled.

  In fact, it has been reported some sync problems by Altera about
  bridges to memory whan multple masters access it. Maybe some other
  bug?
*/




/* 
   Case 2 - using the Altera Avalon Mutex component directly using the
   mutex registers

   The Avalon Mutex component is used to implement a software atomic
   swap operation. The HAL interface is NOT used because 

   - the semaphore calls inside the altera mutex may cause problems
     whan instantiating the HAL 

   - directly using the register is really much more efficient! In
     fact, most of the addresses are resolved statically by the compiler.

   Note that the owner value of the mutex DOES NOT contain the CPUID
   value of the owner but the EE_CURRENTCPU value!!!

   Note that the cache must be disabled!!!

   EE_ALTERA_MUTEX_BASE is defined to be:
   - the *_BASE define in system.h if EE is compiled from source
   - an extern const void* if EE is compiled from a binary distribution

   About the initialization values of the spin locks...
   Bit 0 of EE_hal_spin_status[i] should be != EE_hal_spin_cpu0[i]
*/

/* init value = all (EE_UINT32)(&EE_hal_spin_value[i][cpu])+1 */
extern EE_UINT32 EE_hal_spin_status[]; 

/* The first version of this data structure was the following:
 * init value = blank (BSS) extern EE_UINT32 EE_hal_spin_value[][EE_MAX_CPU]; 
 * 
 * That way of initializing the variable does not work when using a binary 
 * distribution, because the number of CPUs is not specified in eecfg.h as a 
 * define, but it its an external variable.
 * The data structure we are currently using is basically an array of pointers.
 * each pointer points to a vector of data.
 * 
 * The EE_hal_spin_value must point to other spinlock arrays, one for each 
 * spinlock. The spinlock array must be allocated in RAM, initialized to 0.
 */
extern EE_UINT32 * const EE_hal_spin_value[];


__INLINE__ void __ALWAYS_INLINE__ EE_altera_mutex_spin_in(void)
{
  alt_u32 data, check;

  /* the data we want the mutex to hold */
  data = (EE_CURRENTCPU << ALTERA_AVALON_MUTEX_MUTEX_OWNER_OFST) | 1;

  do {
    /* attempt to write to the mutex */
    IOWR_ALTERA_AVALON_MUTEX_MUTEX(EE_ALTERA_MUTEX_BASE, data);
    
    check = IORD_ALTERA_AVALON_MUTEX_MUTEX(EE_ALTERA_MUTEX_BASE);
    
  } while ( check != data);
}


__INLINE__ void __ALWAYS_INLINE__ EE_altera_mutex_spin_out(void)
{
  //  IOWR_ALTERA_AVALON_MUTEX_RESET(EE_ALTERA_MUTEX_BASE, 
  //                                  ALTERA_AVALON_MUTEX_RESET_RESET_MSK);
  IOWR_ALTERA_AVALON_MUTEX_MUTEX(EE_ALTERA_MUTEX_BASE, 
				 EE_CURRENTCPU << ALTERA_AVALON_MUTEX_MUTEX_OWNER_OFST);
}



__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_in(EE_TYPESPIN m)
{
  register EE_UINT32 new_lock_value;
  register volatile EE_UINT32 *wait_address;
  register EE_UINT32 what_means_locked;

  new_lock_value = ((EE_UINT32)&EE_hal_spin_value[m][EE_CURRENTCPU]) |
    EE_hal_spin_value[m][EE_CURRENTCPU];

  //  wait_address = SWP(&EE_hal_spin_status[m], new_lock_value);
  EE_altera_mutex_spin_in();
  wait_address = (EE_UINT32 *)EE_hal_spin_status[m];
  EE_hal_spin_status[m] = new_lock_value;
  EE_altera_mutex_spin_out();

  what_means_locked = ((EE_UINT32)wait_address) & 1;
  wait_address = (EE_ADDR) ( ((EE_UINT32)wait_address) & 0xFFFFFFFE );
  while (*wait_address == what_means_locked);
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_out(EE_TYPESPIN m)
{
  EE_hal_spin_value[m][EE_CURRENTCPU] = !EE_hal_spin_value[m][EE_CURRENTCPU];
}

#endif



#ifdef __NIOS2_SPIN_CUSTOM_INSTRUCTION__
/* 
 * Case 3- using a Custom Instruction
 *
 * This implementation provides spin lock support using NiosII custom
 * instructions.
 *
 * NiosII Custom Instruction do not need ram/rom data and initialization.
 *
 * Names that must be defined for each CPU: EE_NAME_GTCUSTOM
 */


/* SpinRead:
 * A = spinlock number
 * B = cpu number
 * RETURN = cpu's spin value read (0 or 1 extended to 32 bits)
 */
#define EE_nios2_custom_spinread(A,B) \
				EE_CONCATENATE2(ALT_CI_,EE_NAME_GTCUSTOM)(0x0001,(A),(B))

/* GTSwap:
 * A = spinlock number
 * RETURN = value of the spinlock status (Cpu_Index + Lock_Value)
 *          before swapping the contents, extended to 32 bits
 */
#define EE_nios2_custom_gtswap(A) \
				EE_CONCATENATE2(ALT_CI_,EE_NAME_GTCUSTOM)(0x0002,(A),0x0000)

/* SpinFlip:
 * A = spinlock number
 * RETURN = void
 */
#define EE_nios2_custom_spinflip(A) \
				EE_CONCATENATE2(ALT_CI_,EE_NAME_GTCUSTOM)(0x0000,(A),0x0000)




__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_in(EE_TYPESPIN m)
{
  register EE_UINT32 the_status;
  register EE_UINT32 value;

  /* the_status contains the LSBit that is "what means locked", and
     the rest is the number of the spinlock that has to be read */
  the_status = EE_nios2_custom_gtswap(m);
    
  /* SpinRead only takes bit 31...1, bit 0 is ignored */
  do {
    value = EE_nios2_custom_spinread(m, the_status);
  }
  while (value == (the_status & 0x00000001));
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_spin_out(EE_TYPESPIN m)
{
  EE_nios2_custom_spinflip(m);
}


#endif

/* Synchronous startup */

#ifndef __NIOS2_NO_STARTUP_BARRIER__
/* this location is used to synchronously start all the various CPUs.
 * The value is initialized by CPU0 to EE_MAX_CPU-1, and is decremented by 1 
 * everytime a processor reach the synch position.
 * 
 * MUST be EE_SHARED, because this location have to be shared among all the 
 * different CPUs
 */
extern volatile EE_UREG EE_startsynclocation EE_DISABLE_GP_ADDRESSING;

/* this variable is set to 1 if the startup barrier is present, 0 otherwise */
extern const EE_UREG EE_has_startup_barrier EE_DISABLE_GP_ADDRESSING;
#endif





/*
 *  Interprocessor Interrupt on Altera Nios II
 */

/*
 * EE has two ways for implementing an atomic transaction:
 *
 * 1- using a custom SOPCBuilder component IPIC Sublogic (obsolete)
 * 2- using an Altera Avalon PIO
 */

#ifdef __NIOS2_IPIC_SUBLOGIC__

/* 
 * Case 1: Matteo Duranti's IPIC
 *
 * Although Matteo's implementation of the IPIC was more efficient
 * than implementation 2 (a few LE less), implementation 2 still has a
 * simpler implementation and, more important, only uses the Altera
 * components.
 */

/* These variables points to the IPIC logic on the particular Nios II COPU */
extern alt_u32 * const EE_IPIC_BASE;
extern alt_u32 const EE_IPIC_IRQ;


/* This is used to raise an Interrupt on another CPU */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_interprocessor(EE_UREG cpu)
{
	*EE_IPIC_BASE = cpu;
}

/* This is used to signal that the interprocessor interrupt on the current CPU 
 * has been handled */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_interprocessor_served(EE_UINT8 cpu)
{
  *EE_IPIC_BASE = cpu;
}

#endif

#ifdef __NIOS2_IPIC_PIO__

/* 
 * Case 2: Altera IPIC PIO
 *
 * In this case, each CPU has an input PIO to raise interprocessor
 * interrupt, that is externally connected to an output PIO shared
 * among all teh CPUs.
 */

/* These variables points to the IPIC PIO */
extern alt_u32 *const EE_IPIC_OUTPUT_BASE;
extern alt_u32 *const EE_IPIC_INPUT_BASE;
extern alt_u32 const EE_IPIC_IRQ;

/* This is used to raise an Interrupt on another CPU */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_interprocessor(EE_UREG cpu)
{
  IOWR_ALTERA_AVALON_PIO_DATA(EE_IPIC_OUTPUT_BASE, 1<<cpu);
  IOWR_ALTERA_AVALON_PIO_DATA(EE_IPIC_OUTPUT_BASE, 0);
}

/* This is used to signal that the interprocessor interrupt on the current CPU 
 * has been handled */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_IRQ_interprocessor_served(EE_UINT8 cpu)
{
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(EE_IPIC_INPUT_BASE, 0)   ;
}

#endif

#endif /* MSRP */



#endif
