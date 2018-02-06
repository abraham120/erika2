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

#ifndef __RESOURCEDATA_H__
#define __RESOURCEDATA_H__

/* 
 * Shared data structures
 * 
 * Whenever different tasks have to access the same data structure, 
 * and the access cannot be considered atomic (because the data 
 * structure is not accessed in an atomic way), the application have to protect
 * EVERY access done by each task using a "Resource", and protecting the access
 * to that resource using the couple of functions GetResource/ReleaseResource.
 *
 * There are two cases:
 *
 * 1) If all the tasks using the Resource are assigned to the same CPU, the data 
 * structures that are protected by that Resource does not need to be shared 
 * among all the processors, and the definition of these data structures have 
 * to remain local to that cpu.
 * 
 * 2) If the tasks using the Resource are assigned to different CPUs, the data 
 * structures that are protected by that Resource need to be shared 
 * among all the processors, and the definition of these data structures have 
 * to be set into the MASTER_CPU.
 * 
 * RT_Druid takes care of the two cases automatically. To do that the user have 
 * to:
 * 1) put all the data structures related to a resource in a separate file 
 *    (because depending on the kind of resource the file will be linked to a 
 *     different ELF image)
 * 2) use the EE_SHARED_RES() macro when defining the data structure. 
 *    When defining the data structure, you should also specify the fact that 
 *    is used by a particular resource.
 *    See shareddata.c for the definition of this variable.
 * 
 * Same rules explained in shareddata.h applies for disabling GP-relative 
 * addressing.
 */

extern int mutex_mydata EE_DISABLE_GP_ADDRESSING;

#endif
