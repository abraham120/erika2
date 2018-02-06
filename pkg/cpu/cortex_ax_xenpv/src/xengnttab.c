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
 * Author: 2014 Arianna Avanzini
 */

#include "cpu/common/inc/ee_types.h"
#include "cpu/cortex_ax_xenpv/inc/xenincludes.h"
#include "cpu/cortex_ax_xenpv/inc/xendebug.h"
#include "cpu/cortex_ax_xenpv/inc/xengnttab.h"
#include "cpu/cortex_ax_xenpv/inc/hyper-calls.h"

#define MAX_GNTTAB	32
#define XENMAPSPACE_grant_table 1

extern unsigned long grant_table;

static grant_entry_t *gnttab_table[MAX_GNTTAB];
static int last_mapped_idx = 0;

void gnttab_update_entry_v2(grant_ref_t ref,
			    domid_t domid,
                            unsigned long frame,
                            unsigned flags)
{
	grant_ref_t line = GTABLE_LINE(ref);
	grant_ref_t col = GTABLE_COL(ref);

	gnttab_table[line][col].domid = domid;
        gnttab_table[line][col].frame = frame;
        wmb();
        gnttab_table[line][col].flags = GTF_permit_access | flags;
}

void EE_Xen_map_gnttab(int idx_start, int idx_end)
{
	struct xen_add_to_physmap xatp;
	int i = idx_end;

	if (idx_end >= MAX_GNTTAB || idx_start < 0)
		return;

	/* Map grant table ensuring to let it grow only once */
	for (; i >= idx_start ; i--) {
		xatp.domid = DOMID_SELF;
		xatp.space = XENMAPSPACE_grant_table;
		xatp.idx = i;
		xatp.gpfn = virt_to_pfn(&grant_table);
		if (HYPERVISOR_memory_op(XENMEM_add_to_physmap, &xatp))
			BUG();
		gnttab_table[i] = (grant_entry_t *)&grant_table;
	}

	last_mapped_idx = idx_end;

	printk("EE: grant table mapped\n");
}

void EE_Xen_init_gnttab(void)
{
	EE_Xen_map_gnttab(last_mapped_idx, 0);

	printk("EE: gnttab frames init\n");
}
