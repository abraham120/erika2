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

#ifndef _ERIKA_XEN_GNTTAB_
#define _ERIKA_XEN_GNTTAB_

#define GNTTABOP_setup_table	2
#define GTF_permit_access	(1U<<0)
typedef short int16_t;

struct grant_entry_header {
    uint16_t flags;
    domid_t  domid;
};
typedef struct grant_entry_header grant_entry_header_t;

typedef uint32_t grant_ref_t;

#if 0
union grant_entry_v2 {
    grant_entry_header_t hdr;

    struct {
        grant_entry_header_t hdr;
        uint32_t pad0;
        uint64_t frame;
    } full_page;
    struct {
        grant_entry_header_t hdr;
        uint16_t page_off;
        uint16_t length;
        uint64_t frame;
    } sub_page;

    struct {
        grant_entry_header_t hdr;
        domid_t trans_domid;
        uint16_t pad0;
        grant_ref_t gref;
    } transitive;

    uint32_t __spacer[4]; /* Pad to a power of two */
};
typedef union grant_entry_v2 grant_entry_v2_t;
typedef grant_entry_v2_t grant_entry_t;
#endif

struct grant_entry_v1 {
    /* GTF_xxx: various type and flag information.  [XEN,GST] */
    uint16_t flags;
    /* The domain being granted foreign privileges. [GST] */
    domid_t  domid;
    /*
     * GTF_permit_access: Frame that @domid is allowed to map and access. [GST]
     * GTF_accept_transfer: Frame whose ownership transferred by @domid. [XEN]
     */
    uint32_t frame;
};
typedef struct grant_entry_v1 grant_entry_v1_t;
typedef grant_entry_v1_t grant_entry_t;

struct gnttab_setup_table {
    /* IN parameters. */
    domid_t  dom;
    uint32_t nr_frames;
    /* OUT parameters. */
    int16_t  status;              /* => enum grant_status */
    unsigned long *frame_list;
};

#define PAGE_SHIFT		12
#define PAGE_SIZE		(1 << PAGE_SHIFT)
#define PHYS_SIZE		(40*1024*1024)

#define GTABLE_COL(ref)		(ref % GSTRUCT_NUM)
#define GSTRUCT_NUM		(PAGE_SIZE / sizeof(grant_entry_t))
#define GTABLE_LINE(ref)	(ref / GSTRUCT_NUM)

void EE_Xen_init_gnttab(void);
void EE_Xen_map_gnttab(int idx_start, int idx_end);
void gnttab_update_entry_v2(grant_ref_t ref,
			    domid_t domid,
                            unsigned long frame,
                            unsigned flags);
int HYPERVISOR_grant_table_op(unsigned int cmd, void *uop, unsigned int count);

#endif /*_ERIKA_XEN_GNTTAB_*/
