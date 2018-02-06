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
 * Author: 2011  Bernardo  Dal Seno
 *         2010  Fabio Checconi
 */

#include <ee_internal.h>

#ifdef USE_PRAGMAS
#pragma section PRAGMA_SECTION_BEGIN_SYS_STACK
EE_STACK_T EE_e200zx_sys_stack[EE_STACK_WLEN(EE_SYS_STACK_SIZE)];
#pragma section PRAGMA_SECTION_END_SYS_STACK
#else
EE_STACK_T EE_STACK_ATTRIB EE_e200zx_sys_stack[EE_STACK_WLEN(EE_SYS_STACK_SIZE)];
#endif

#if (defined(__EE_MEMORY_PROTECTION__)) && (defined(OO_CPU_HAS_STARTOS_ROUTINE))
EE_TYPEBOOL EE_cpu_startos(void)
{
	EE_UREG i;
	for (i = 0U; i < EE_MAX_APP; i++) {
		EE_hal_app_init(&(EE_as_Application_ROM[i].sec_info));
	}
	/* When the MMU is set up, access to an application space is permitted
	 * only if the CPU PID matches the application; so application memory is
	 * initialized before configuring the MMU. */
	EE_e200zx_mmu_setup(EE_hal_memprot_entries,
		EE_HAL_MEMPROT_ENTRIES(EE_MAX_APP));

	/* Initialize System Timer */
	EE_initialize_system_timer();
	return 0;
}
#endif /* __EE_MEMORY_PROTECTION__ && OO_CPU_HAS_STARTOS_ROUTINE */


#ifdef __EE_MEMORY_PROTECTION__
/*
 * MISRA NOTE: This function is a workaround to provide
 * the capability to access arrays as a real arrays
 * although it is declared as pointer.
 * This solution prevents from misra error:
 * "pointer arithmetic by increment or decrement used"
 */
#if defined(RTDRUID_CONFIGURATOR_NUMBER) \
 && (RTDRUID_CONFIGURATOR_NUMBER >= RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO)
static void copy_mem(EE_UINT32 dest_data[], const EE_UINT32 *dest_end, \
		const EE_UINT32 src_data[], EE_UINT32 bss[], \
                const EE_UINT32 *bss_end, EE_UINT32 stack[], \
                const EE_UINT32 *stack_end)
#else
static void copy_mem(EE_UINT32 dest_data[], const EE_UINT32 *dest_end, \
		const EE_UINT32 src_data[], EE_UINT32 bss[], \
                const EE_UINT32 bss_end[])
#endif
{
	EE_UINT32 i = 0U;
        if ((dest_end != NULL) && (bss_end != NULL)) {
	        while (&dest_data[i] < dest_end) {
		        dest_data[i] = src_data[i];
		        i++;
	        }

#if defined(RTDRUID_CONFIGURATOR_NUMBER) \
 && (RTDRUID_CONFIGURATOR_NUMBER >= RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO)
                i = 0U;
                if (stack_end != NULL) {
                        while (&stack[i] < stack_end) {
                                /* Stack fill pattern */
		                stack[i] = 0xa5a5a5a5U;
		                i++;
	                }
                }
#endif

	        i = 0U;
	        while (&bss[i] < bss_end) {
		        bss[i] = 0U;
		        i++;
	        }
        }
}

void EE_hal_app_init(const EE_APP_SEC_INFO_T *app_info)
{
	const EE_UINT32 *src_data;
	EE_UINT32 *dest_data;
	const EE_UINT32 *dest_end;
	EE_UINT32 *bss;
	const EE_UINT32 *bss_end;
        
	EE_UINT32 *stack_start;
        const EE_UINT32 *stack_end;

	if (app_info != NULL) {
		src_data = (const EE_UINT32 *)(app_info->data_flash);
		dest_data = (EE_UINT32 *)(app_info->data_ram);
		dest_end = (EE_UINT32 *)(app_info->bss_start);

		bss = (EE_UINT32 *)(app_info->bss_start);
		bss_end = (EE_UINT32 *)(app_info->bss_end);
#if defined(RTDRUID_CONFIGURATOR_NUMBER) \
 && (RTDRUID_CONFIGURATOR_NUMBER >= RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO)
                stack_start = (EE_UINT32 *)(app_info->stack_start);
                stack_end = (EE_UINT32 *)(app_info->data_ram);
                copy_mem(dest_data, dest_end, src_data, bss, bss_end, \
                                stack_start, stack_end);
#else
		copy_mem(dest_data, dest_end, src_data, bss, bss_end);
#endif
	}
}
#endif /* __EE_MEMORY_PROTECTION__ */

/*
 * MMU setup
 *
 * MMU is normally initialized by BAM.  A different configuration can be
 * programmed with EE_e200zx_mmu_setup().
 */

#ifdef __EE_USE_MMU__

#define MMU_MAS0	624
#define MMU_MAS1	625
#define MMU_MAS2	626
#define MMU_MAS3	627


#ifdef __DCC__

__asm volatile void mmu_write_mas(EE_SREG mas, EE_UREG val)
{
% reg val; con mas;
!
	mtspr	mas, val
}

__asm volatile void mmu_write_sync(void)
{
!
	tlbwe
	isync
}

#else /* if __DCC__ */

#define mmu_write_mas(mas, val) asm volatile ("mtspr	(" \
	EE_PREPROC_STRING(mas) "), %0" : : "r"(val))

__INLINE__ void __ALWAYS_INLINE__ mmu_write_sync(void)
{
	asm volatile ("tlbwe	\n\t"
		"isync");
}

#endif /* else if __DCC__ */


void EE_e200zx_mmu_setup(const EE_MMU_ENTRY_T entries[], EE_UREG count)
{
	EE_UREG i;

	for (i = 0U; i < count; i++) {
		mmu_write_mas(MMU_MAS0, EE_E200ZX_MMU_TLBSEL1 | (i << 16));
		mmu_write_mas(MMU_MAS1, entries[i].mas1);
		mmu_write_mas(MMU_MAS2, entries[i].mas2);
		mmu_write_mas(MMU_MAS3, entries[i].mas3);
		mmu_write_sync();
	}
}

#endif /* __EE_USE_MMU__ */
