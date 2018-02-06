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
 * CPU-dependent part of HAL
 * Derived from pkg/cpu/mico32/inc/ee_cpu.h
 * Author: 2010 Fabio Checconi
 *         2011 Bernardo  Dal Seno
 */


#ifndef PKG_CPU_E200ZX_INC_EE_CPU_H
#define PKG_CPU_E200ZX_INC_EE_CPU_H

/* Include types and functions for the kernel */
#include "ee_cpu_os.h"
/* defines used both by C and assembly */
#include "ee_cpu_asm.h"
/* INTC symbols */
#include "ee_mcu_regs.h"


/* This instruction should cause a trap when executed. Handy to mark invalid
 * functions */
/* XXX */
#define INVALID_ASM_INSTR  __asm volatile ( ".word 0xcccc" )


/* Alignment and section for program stacks */
#define EE_STACK_SEC "ee_stack"
#define STACK_SEC ".stack"
#define EE_STACK_ATTRIB		EE_COMPILER_ALIGN(EE_STACK_ALIGN)	\
	EE_COMPILER_SECTION(STACK_SEC)
#define EE_STACK_ATTRIB_NAME(n)	EE_COMPILER_ALIGN(EE_STACK_ALIGN)	\
	EE_COMPILER_SECTION(EE_STACK_SEC "_" EE_PREPROC_STRING(n))

/* Word used to build user stacks */
typedef EE_UINT32 EE_STACK_T;
/* Stack length in words */
#define EE_STACK_WLEN(bl) (((((EE_UREG)(bl) +				\
			(EE_UREG)EE_STACK_ALIGN) - 1U)			\
		/ (EE_UREG)EE_STACK_ALIGN)				\
	* ((EE_UREG)EE_STACK_ALIGN / sizeof(EE_STACK_T)))
/* Initial pointer (word offset) in user stacks */
#define EE_STACK_INITP(bl) (EE_STACK_WLEN(bl) -	\
	((EE_UREG)EE_STACK_ALIGN / sizeof(EE_STACK_T)))

/*********************************************************************
 Multicore and multiprocessor support
 *********************************************************************/

#ifdef __MSRP__

/* the MSB in a MUTEX type indicates if a resource is global (1) or
   local (0) to a processor */
#define EE_GLOBAL_MUTEX ((ResourceType)0x80000000U)

/* Type for spinlocks: an ID */
typedef EE_UINT32 EE_TYPESPIN;

/* For compatibilty with old code */
#define EE_SHARED_DATA(x) x

/* Shared data use separate sections; potentially, three different sections
 * could be used for constant, unitialized, and initialized data */
#ifndef USE_PRAGMAS
#define EE_SHARED_CDATA  EE_COMPILER_SECTION("ee_mcglobalc") EE_COMPILER_KEEP
#define EE_SHARED_UDATA  EE_COMPILER_SECTION("ee_mcglobald") EE_COMPILER_KEEP
#define EE_SHARED_IDATA  EE_COMPILER_SECTION("ee_mcglobald") EE_COMPILER_KEEP
#endif

#if 0  /* Shared code, resources and mutex not working yet */
#define EE_SHARED_CODE(x) EE_SHARED_CODE_##x
#define EE_SHARED_RES(name,var) EE_SHARED_RES_##name(var)
#endif

/* Include multicore support if needed (There's a guard inside the file too) */
#include "ee_e200zx_multicore.h"

#endif /* __MSRP__ */

#ifdef __EE_MEMORY_PROTECTION__

#define EE_HAL_IRQSTATE_INVALID ((EE_FREG)0U)
#define EE_hal_set_irq_valid_flag(f) ((f) | (MSR_EE << 1))
#define EE_hal_clear_irq_flag(f) ((f) & ~MSR_EE)
#define EE_hal_copy_irq_flag(from, to) (((to) & ~MSR_EE) | ((from) & MSR_EE))

#endif /* __EE_MEMORY_PROTECTION__ */

/*************************************************************************
 Access to CPU registers
 *************************************************************************/

#ifdef __DCC__

__asm static EE_UREG EE_e200zx_get_tcr(void)
{
! "r3"
	mfspr	r3, tcr
}

__asm static void EE_e200zx_set_tcr(EE_UREG val)
{
% reg val
!
	mtspr	tcr, val
}

__asm static EE_UREG EE_e200zx_get_tsr(void)
{
! "r3"
	mfspr	r3, tsr
}

__asm static void EE_e200zx_set_tsr(EE_UREG val)
{
% reg val
!
	mtspr	tsr, val
}

__asm static void EE_e200zx_set_dec(EE_UREG val)
{
% reg val
!
	mtspr	dec, val
}

__asm static void EE_e200zx_set_decar(EE_UREG val)
{
% reg val
!
	mtspr	decar, val
}

__asm static EE_UREG EE_e200zx_get_tbl(void)
{
! "r3"
	mfspr	r3, tbl
}

__asm static EE_UREG EE_e200zx_get_pvr(void)
{
! "r3"
	mfspr	r3, pvr
}

#else /* if __DCC__ */
__INLINE__ EE_UREG EE_e200zx_get_tcr(void)
{
	EE_UREG tcr;
#if 0
	__asm volatile ("mfspr %0, tcr" : "=r"(tcr));
	tcr = 340
#endif
	__asm volatile ("mfspr %0, 340" : "=r"(tcr));
	return tcr;
}

__INLINE__ void EE_e200zx_set_tcr(EE_UREG val)
{
#if 0
	__asm volatile ("mtspr tcr, %0" :: "r"(val) );
	tcr = 340
#endif
	__asm volatile ("mtspr 340, %0" :: "r"(val) );
}

__INLINE__ EE_UREG EE_e200zx_get_tsr(void)
{
	EE_UREG tsr;
#if 0
	__asm volatile ("mfspr %0, tsr" : "=r"(tsr));
	tsr = 336
#endif
	__asm volatile ("mfspr %0, 336" : "=r"(tsr));
	return tsr;
}

__INLINE__ void EE_e200zx_set_tsr(EE_UREG val)
{
#if 0
	__asm volatile ("mtspr tsr, %0" :: "r"(val) );
	tsr = 336
#endif
	__asm volatile ("mtspr 336, %0" :: "r"(val) );
}

__INLINE__ void EE_e200zx_set_dec(EE_UREG val)
{
#if 0
	__asm volatile ("mtspr dec, %0" :: "r"(val) );
	dec = 22
#endif
	__asm volatile ("mtspr 22, %0" :: "r"(val) );
}

__INLINE__ void EE_e200zx_set_decar(EE_UREG val)
{
#if 0
	__asm volatile ("mtspr decar, %0" :: "r"(val) );
	decar = 54
#endif
	__asm volatile ("mtspr 54, %0" :: "r"(val) );
}

__INLINE__ EE_UREG EE_e200zx_get_tbl(void)
{
	EE_UINT32 tbl;
#if 0
	__asm volatile ("mfspr %0, tbl" : "=r"(tbl));
	tbl = 284
#endif
	__asm volatile ("mfspr %0, 284" : "=r"(tbl));
	return tbl;
}

__INLINE__ EE_UREG EE_e200zx_get_pvr(void)
{
	EE_UINT32 pvr;
#if 0
	__asm volatile ("mfspr %0, pvr" : "=r"(pvr));
	pvr = 287
#endif
	__asm volatile ("mfspr %0, 287" : "=r"(pvr));
	return pvr;
}
#endif /* else __DCC__ */


/*************************************************************************
 Functions
 *************************************************************************/

__INLINE__ void __ALWAYS_INLINE__ EE_e200zx_isync(void)
{
	__asm volatile ("isync");
}

__INLINE__ EE_TYPEISR2PRIO __ALWAYS_INLINE__ EE_e200zx_get_int_prio(void)
{
	return INTC_CPR.R;
}

__INLINE__ void __ALWAYS_INLINE__ EE_e200zx_set_int_prio(EE_TYPEISR2PRIO prio)
{
	/* To understand why all this synchronization is needed look at one of
		 frescale ppc's reference manual at the following:
		 9.3.1.2 INTC Current Priority Register NOTE
		 9.5.5.2 Ensuring Coherency
	*/
	/* Execution syncronization -> all stores executed (for coherency: 9.5.5.2) */
	EE_e200zx_mbar();
	INTC_CPR.R = prio;
	/* Context syncronization + INTC_CPR store executed */
	EE_e200zx_mbar();
	EE_e200zx_isync();
}

#ifndef __PPCE200Z0__
/* e200z0 has no internal timer, so the functions below are not defined */

/* Enable the fixed-interval interrupt.  bitpos (0-63) is the bit of the time
 * base register that triggers the interrupt; 0 is the most significant bit of
 * the register.  See the Book E manual for details on this interrupt.  */
void EE_e200zx_setup_fixed_intv(EE_UREG bitpos);
/* Disable the fixed-interval interrupt */
void EE_e200zx_stop_fixed_intv(void);

/* Configure the decrementer to raise an interrupt every 'delay' cycles */
void EE_e200z7_setup_decrementer(EE_UINT32 dec_value);
/* Configure the decrementer to raise an interrupt once after `delay' cycles */
void EE_e200z7_setup_decrementer_oneshot(EE_UINT32 oneshotvalue);
/* Stop the decrementer from generating interrupts */
void EE_e200z7_stop_decrementer(void);

/* Wait a number of ticks as counted by the CPU time base */
void EE_e200zx_delay(EE_UINT32 ticks);

#endif /* ! __PPCE200Z0__ */


/*************************************************************************
 MMU
 *************************************************************************/

/* TLB entry specification.  Values to be loaded in the MAS1, MAS2, and MAS3
 * registers.  You can use the constants below to build such values.  Please
 * refer to the Book E or Freescale manuals for details.  */
typedef struct {
	EE_UREG mas1;
	EE_UREG mas2;
	EE_UREG mas3;
} EE_MMU_ENTRY_T;

/* Masks used for MAS0 */
#define EE_E200ZX_MMU_TLBSEL1	((EE_UREG)0x10000000U)	/* Use TLB1 */

/* Masks used for MAS1 */
#define EE_E200ZX_MMU_VALID	0x80000000U	/* TLB entry is valid */
#define EE_E200ZX_MMU_IPROT	0x40000000U	/* TLB entry is protected */

/* Page sizes (MAS1) */
#define EE_E200ZX_MMU_SIZE_256M	0x00000900U
#define EE_E200ZX_MMU_SIZE_64M	0x00000800U
#define EE_E200ZX_MMU_SIZE_16M	0x00000700U
#define EE_E200ZX_MMU_SIZE_4M	0x00000600U
#define EE_E200ZX_MMU_SIZE_1M	0x00000500U
#define EE_E200ZX_MMU_SIZE_256K	0x00000400U
#define EE_E200ZX_MMU_SIZE_64K	0x00000300U
#define EE_E200ZX_MMU_SIZE_16K	0x00000200U
#define EE_E200ZX_MMU_SIZE_4K	0x00000100U

/* Masks used for MAS2 */
#define EE_E200ZX_MMU_FLAG_GUARD 0x00000002U	/* Guarded access */
#define EE_E200ZX_MMU_FLAG_CE	0x00000000U	/* Cache enabled */
#define EE_E200ZX_MMU_FLAG_CD	0x00000008U	/* Cache disabled */
#define EE_E200ZX_MMU_FLAG_FLE	0x00000000U	/* Fixed-length encoding */
#define EE_E200ZX_MMU_FLAG_VLE	0x00000020U	/* Variable-length encoding */

/* Masks used for MAS3 */
#define EE_E200ZX_MMU_PROT_UR	0x02U		/* User read access */
#define EE_E200ZX_MMU_PROT_UW	0x08U		/* User write access */
#define EE_E200ZX_MMU_PROT_UX	0x20U		/* User execute access */
#define EE_E200ZX_MMU_PROT_SR	0x01U		/* Supervisor read access */
#define EE_E200ZX_MMU_PROT_SW	0x04U		/* Supervisor write access */
#define EE_E200ZX_MMU_PROT_SX	0x10U		/* Supervisor execute access */
#define EE_E200ZX_MMU_PROT_SRWX	0x15U		/* All supervisor access */
#define EE_E200ZX_MMU_PROT_URWX	0x2aU		/* All user access */
/* Permission for code: read + execute in both modes */
#define EE_E200ZX_MMU_PROT_CODE	(EE_E200ZX_MMU_PROT_SX | EE_E200ZX_MMU_PROT_UX \
	| EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_UR)

/* MMU initialization.  Load `count' entries specified in `entries' in the first
 * `count' entries of the TLB.  This is a C function, so RAM and stack must be
 * initialized already before calling this function. */
void EE_e200zx_mmu_setup(const EE_MMU_ENTRY_T *entries, EE_UREG count);

#ifdef __EE_CRT0_INIT_MMU__
/* Entries to be loaded by the crt0 */
extern const EE_MMU_ENTRY_T EE_e200zx_mmu_entries[];
/* Number of entries to be loaded by the crt0 */
extern const unsigned EE_e200zx_mmu_num_entries;
#endif /* __EE_CRT0_INIT_MMU__ */


/*************************************************************************
 Memory Protection
 *************************************************************************/

#if defined(__EE_MEMORY_PROTECTION__)
typedef EE_MMU_ENTRY_T EE_MEMPROT_ENTRY_T;

#define EE_MEMPROT_USR_DATA	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR \
	| EE_E200ZX_MMU_PROT_UW | EE_E200ZX_MMU_PROT_UR)
#define EE_MEMPROT_SYS_DATA	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR)
#define EE_MEMPROT_TRUST_DATA	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR)
#define EE_MEMPROT_ROM_CODE	(EE_E200ZX_MMU_PROT_SX | EE_E200ZX_MMU_PROT_UX \
	| EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_UR)
#define EE_MEMPROT_RAM_CODE	(EE_E200ZX_MMU_PROT_SX | EE_E200ZX_MMU_PROT_UX \
	| EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_UR | EE_E200ZX_MMU_PROT_SW)
#define EE_MEMPROT_HW_REG	(EE_E200ZX_MMU_PROT_SW | EE_E200ZX_MMU_PROT_SR \
	| ((EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD) << 16))

#ifdef __VLE__
#define EE_MEMPROT_USE_VLE EE_E200ZX_MMU_FLAG_VLE
#else
#define EE_MEMPROT_USE_VLE 0U
#endif

#define EE_MEMPROT_USER_ENTRY(appid, base, size, log2size, type)	\
	{ 0xc0000000U | ((EE_UREG)(appid) << 16)			\
		  | ((((EE_UREG)(log2size) - 10U) / 2U) << 8),		\
		(base) | EE_MEMPROT_USE_VLE				\
		  | ((EE_UREG)(((type) & 0xffff0000U) >> 16) & 0xffffU), \
		(base) | ((EE_UREG)(type) & 0xffffU) }



#define EE_MEMPROT_SYSTEM_ENTRY0   					 \
    { EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_1M,    \
   	 0xfff00000U | EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD, \
   	 0xfff00000U | EE_E200ZX_MMU_PROT_SRWX }
#define EE_MEMPROT_SYSTEM_ENTRY1   					 \
    { EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_16M,    \
   	 /*0x00000000U |*/ EE_E200ZX_MMU_FLAG_CE | EE_MEMPROT_USE_VLE,    \
   	 /*0x00000000U |*/ EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SX \
   	 | EE_E200ZX_MMU_PROT_UR | EE_E200ZX_MMU_PROT_UX }
#define EE_MEMPROT_SYSTEM_ENTRY2   					 \
    { EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_1M,    \
   	 0xc3f00000U | EE_E200ZX_MMU_FLAG_CD | EE_E200ZX_MMU_FLAG_GUARD, \
   	 0xc3f00000U | EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SW }
#define EE_MEMPROT_SYSTEM_ENTRY3   					 \
    { EE_E200ZX_MMU_VALID | EE_E200ZX_MMU_IPROT | EE_E200ZX_MMU_SIZE_64K,    \
   	 0x40000000U | EE_E200ZX_MMU_FLAG_CE,   			 \
   	 0x40000000U | EE_E200ZX_MMU_PROT_SR | EE_E200ZX_MMU_PROT_SW    \
   	 | EE_E200ZX_MMU_PROT_UR }
#define EE_MEMPROT_SYSTEM_ENTRY   	 \
    EE_MEMPROT_SYSTEM_ENTRY0,    \
    EE_MEMPROT_SYSTEM_ENTRY1,    \
    EE_MEMPROT_SYSTEM_ENTRY2,    \
    EE_MEMPROT_SYSTEM_ENTRY3


#define EE_HAL_MEMPROT_ENTRIES(numapps)	((numapps) + 4U)

extern const EE_MEMPROT_ENTRY_T EE_hal_memprot_entries[EE_HAL_MEMPROT_ENTRIES(EE_MAX_APP)];

/* SR value for trusted and unstrusted code */
#define EE_MEMPROT_TRUST_MODE 0x8000U
#define EE_MEMPROT_USR_MODE 0xc000U

/* Information about sections of each application */
typedef struct {
	/* Inizialized data section, Flash address */
	const void *data_flash;
#if (defined(RTDRUID_CONFIGURATOR_NUMBER))	\
 && (RTDRUID_CONFIGURATOR_NUMBER >= RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO)
	/* Stack section.  Its end coincides with data start */
	void *stack_start;
#endif /* RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO */
	/* Inizialized data section, RAM address.  Its end coincides with BSS
	 * start. */
	void *data_ram;
	/* BSS section start */
	void *bss_start;
	/* BSS section end (address of the byte after the section) */
	void *bss_end;
} EE_APP_SEC_INFO_T;

/* Initialize the memory sections (initialized data and BSS) of an application */
void EE_hal_app_init(const EE_APP_SEC_INFO_T *app_info);

#endif /* __EE_MEMORY_PROTECTION__ */

#ifndef USE_PRAGMAS
/*
 * Markers for application private areas
 */
/* Application private constant data (read-only) */
#define EE_APPLICATION_CDATA(app)  EE_COMPILER_SECTION(".rodata")
/* Application private uninitialized data (BSS) */
#define EE_APPLICATION_UDATA(app)  \
	EE_COMPILER_SECTION("ee_bss_" EE_PREPROC_STRING(app))
/* Application private initialized data */
#define EE_APPLICATION_IDATA(app)  \
	EE_COMPILER_SECTION("ee_data_" EE_PREPROC_STRING(app))
#endif /* USE_PRAGMAS */

#ifdef  __EE_MEMORY_PROTECTION__
#ifdef __DCC__

__asm static EE_UINT8 EE_as_raw_call_trusted_func(EE_UINT32 FunctionIndex,
	void *FunctionParams)
{
% reg FunctionIndex, FunctionParams
! "r0","r3","r4","r5","r6","r7","r8","r9","r10","r11","r12","ctr"
	mr	r3, FunctionParams
	mr	r0, FunctionIndex
	sc
}
#else
__INLINE__ EE_UINT8 EE_as_raw_call_trusted_func(EE_UINT32 FunctionIndex,
	void *FunctionParams)
{
	asm volatile ("mr r3, %0" :: "r"(FunctionParams) );
	asm volatile ("mr r0, %0" :: "r"(FunctionIndex) );
	asm volatile ("sc");
}
#endif
#endif /* __EE_MEMORY_PROTECTION__ */
#endif /* __INCLUDE_E200ZX_EE_CPU_H__ */
