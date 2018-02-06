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

/** 
* \file ee_cpu.h
* \brief CPU section main header (common files for HAL have been integrated), Erika HCS12 cpu.
* \author Dario Di Stefano
* \version 0.1
* \date 2011-01-12
*/

/** 
* \mainpage Erika CPU for HCS12 
*
* \section intro_sec This documentation describes the functions, the macros and the variables of the 
* Erika CPU support for Freescale HCS12. For further info see the wiki page: 
* http://erika.tuxfamily.org/wiki/index.php?title=Freescale_S12
*/

#ifndef	__INCLUDE_HC12_EE_CPU_H__
#define	__INCLUDE_HC12_EE_CPU_H__

#include	"eecfg.h"
#include	"cpu/hs12xs/inc/ee_compiler.h"
#include	"ee_s12regs.h"

/******************************************************************************
 HAL Types and Structures
 ******************************************************************************/

/* Primitive data types */
#if !defined(RTDRUID_CONFIGURATOR_NUMBER) || (RTDRUID_CONFIGURATOR_NUMBER<1276) //RTDRUID_CONFNUM_S12_COMMON_SUPPORT

  #define __EE_HAL_CUSTOM_POINTERS__ // used in cpu/common/inc/ee_types.h
  /* Code addresses (same size of function pointers) */
  typedef @far void *EE_ADDR;			// N.B. 16-bit for @near pointer and 32-bit for @far pointer
  #ifdef __CODEWARRIOR__
    typedef void (*EE_FADDR)(void);
  #else
    #define EE_FADDR EE_ADDR
  #endif
  /* Callbacks with no parameters nor return value */
  typedef void (*EE_VOID_CALLBACK)(void);
  /* Callback function called by driver handlers */
  typedef EE_VOID_CALLBACK EE_ISR_callback;
  
  #define EE_s12xs_active_tos EE_s12_active_tos
  #define EE_s12xs_system_tos EE_s12_system_tos
  #define EE_s12xs_thread_tos EE_s12_thread_tos
  #define EE_s12xs_IRQ_tos    EE_s12_IRQ_tos
  
#endif

#include	"cpu/common/inc/ee_types.h"

/* Data addresses (that have the same size of a pointer) */
typedef EE_UINT16 *EE_DADD;		// N.B. in s12 for data pointer you can use only 16 bit 

typedef EE_UINT16 EE_UREG;
typedef EE_INT16  EE_SREG;
typedef EE_UINT16 EE_FREG;

/* boolean type */
#ifndef EE_TYPEBOOL
typedef EE_UREG EE_TYPEBOOL;
#endif

/* boolean true define */
#ifndef EE_TRUE
#define EE_TRUE ((EE_TYPEBOOL)1U)
#endif

/* boolean false define */
#ifndef EE_FALSE
#define EE_FALSE ((EE_TYPEBOOL)0U)
#endif

// Thread IDs
typedef EE_INT32 EE_TID;
typedef EE_UINT32 EE_UTID;

#define	TID_IS_STACKED_MARK	0x8000

/* EE_TYPEIRQ is currently unused */

/* invalid pointer */
#ifndef NULL
#define NULL 0
#endif

/**
 * This structure is used by the Multistack HAL to contain the
 * information about a "stack", that is composed by a user stack
 * (SYS-mode) and a system stack (IRQ-mode). This type is
 * used internally by the HAL and is not used by the Kernels.
 */
#ifdef __MULTI__
struct EE_TOS {
    EE_DADD SYS_tos;
};
#endif

/* Thread function body pointer */
extern const EE_FADDR EE_hal_thread_body[];

/******************************************************************************
 HAL Variables
 ******************************************************************************/

#ifdef	__MULTI__

/* Top-Of-Stacks (tos) structure defined by RT-Druid in eecfg.c */

extern	EE_UREG EE_s12_active_tos;
#define	EE_hal_active_tos EE_s12_active_tos
extern	struct EE_TOS EE_s12_system_tos[];
#define	EE_std_system_tos EE_s12_system_tos
extern	EE_UREG EE_s12_thread_tos[];
#define	EE_std_thread_tos EE_s12_thread_tos

/* stack used by IRQ handlers */
#ifdef __IRQ_STACK_NEEDED__
extern	struct EE_TOS EE_s12_IRQ_tos;
#endif

#endif	/* __MULTI__ */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || \
    defined(__OO_ECC1__) || defined(__OO_ECC2__)

/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern	EE_UINT16 EE_terminate_data[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern	const EE_FADDR EE_terminate_real_th_body[];

/* this is the stub that have to be put into the EE_th_body array */
extern	void EE_oo_thread_stub(void);

#endif

/*********************************************************************
 s12 interrupt disabling/enabling
 *********************************************************************/

#ifdef __CODEWARRIOR__
  #include "cpu/hs12xs/inc/ee_cpu_cw_utils.h"
#endif
#ifdef __COSMIC__
  #include "cpu/hs12xs/inc/ee_cpu_cosmic_utils.h"
#endif
 
/**
 * \brief				This function is used to enable I-bit maskable interrupts.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_s12_enableIRQ(void)
{
  ASM_EN_INT;
}

/**
 * \brief				This function is used to disable I-bit maskable interrupts.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_s12_disableIRQ(void)
{
  ASM_DIS_INT;
}

/**
 * \brief				This function is used to suspend (disable) I-bit maskable interrupts and read the old state.
 * \return				CCR before the change.
*/
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_s12_suspendIRQ(void)
{
  register EE_FREG retvalue;
  retvalue = EE_READ_CCR();
  EE_s12_disableIRQ();
  return retvalue;
}

/**
 * \brief				This function is used to resume (enable if needed) I-bit maskable interrupts.
 * \param sr			CCR value returned by EE_s12_suspendIRQ().
*/
__INLINE__ void __ALWAYS_INLINE__ EE_s12_resumeIRQ(EE_FREG sr)
{
  // check the I bit in CCR
  if(sr & 0x10)
    EE_s12_disableIRQ();
  else
    EE_s12_enableIRQ();
}

/*************************************************************************
 Functions
 *************************************************************************/

/*
 * Interrupt Handling
 */

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
    EE_s12_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
    EE_s12_disableIRQ();
}

/* Suspend/Resume Interrupts */
__INLINE__ EE_FREG __ALWAYS_INLINE__ EE_hal_suspendIRQ(void)
{
    return EE_s12_suspendIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_resumeIRQ(EE_FREG flags)
{
    EE_s12_resumeIRQ(flags);
}

#endif /* __INCLUDE_HC12_ARCH_H__ */
