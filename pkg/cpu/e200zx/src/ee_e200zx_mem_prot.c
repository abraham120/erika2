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
 * CPU-specific support for memory protection
 * Author: 2011  Bernardo  Dal Seno
 */


#include <ee_internal.h>

/* Symbols set by the linker, used for section boundaries.  Declared as arrays,
 * so the compiler doesn't think they are in the small data area. */
extern int ee_stext[], ee_srodata[], ee_load_ram[];

#if defined(RTDRUID_CONFIGURATOR_NUMBER) \
 && (RTDRUID_CONFIGURATOR_NUMBER >= RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO)
#define check_stack(b,e,i) (((b) >= (EE_ADDR)((i)->stack_start))	\
	&& ((e) <= (EE_ADDR)(i)->data_ram))

#else /* RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO */
/* No stack address available: always return false */
#define check_stack(b,e,i) 0
#endif /* RTDRUID_CONFNUM_STACK_IN_APP_SEC_INFO */

/* Function intruced to prevent from misra error:
 * "cast from pointer to unsigned int"
 * and
 * "cast from unsigned int to pointer"
 */
static EE_ADDR compute_end_bound(EE_ADDR beg[], EE_UREG size){
        /* This op simply performs: beg+size */
        return &beg[size/sizeof(EE_ADDR)];
}

AccessType EE_hal_get_app_mem_access(ApplicationType app,
	MemoryStartAddressType beg, MemorySizeType size)
{
	AccessType ret = (AccessType)0;
	EE_UREG tend;
	EE_ADDR end;

	/* If the input region is not contained within a single section (e.g.,
	 * starting is inside the stack section and the end is inside BSS) we
	 * return 0 even if the task would have some permissions to the region,
	 * because an application should not rely upon the layout of sections
	 * to work correctly.  */

        /* Old code to compute end (not misra compliant) */
	/*tend = (EE_UREG)beg + (EE_UREG)size;
	end = (EE_ADDR)tend;
        end = end;*/

        /* New code to compute end (misra compliant)*/
        end = compute_end_bound(beg, size);

        if (end != NULL) {

	        if ((beg != NULL) && (beg >= (EE_ADDR)&ee_stext) && (end <= (EE_ADDR)&ee_srodata)) {
		        /* Executable code */
		        ret = EE_ACCESS_READ | EE_ACCESS_EXEC;
	        } else if ((beg != NULL) && (beg >= (EE_ADDR)&ee_srodata) && (end <= (EE_ADDR)&ee_load_ram)) {
		        /* Global constant data section */
		        ret = EE_ACCESS_READ;
	        } else {
		        /* Check the OS-Application sections */
		        const EE_APP_SEC_INFO_T *info;
		        /* FIXME: trusted OS-Applications should be treated
		         * differently as currently they can write.  Maybe we should also take into account whether
		         * a trusted function is executing? */
		        info = &(EE_as_Application_ROM[app-1].sec_info);
		        if ((beg != NULL) && check_stack(beg,end,info)) {
			        /* Stack section.  For the sake of efficiency, we don't
			         * check individual stacks. */
			        ret = EE_ACCESS_READ | EE_ACCESS_WRITE | EE_ACCESS_STACK;
		        } else if ((beg != NULL) && (beg >= (EE_ADDR)(info->data_ram))
			        && (end <= (EE_ADDR)info->bss_end)) {
			        /* Data section.  For the sake of efficiency, we don't
			         * check individual sections. */
			        ret = EE_ACCESS_READ | EE_ACCESS_WRITE;
		        } else {
			        /* No more sections; return the default (0) */
		        }
	        }
        }

	return ret;
}
