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

#ifndef _INCLUDES_ARM_32_H_
#define _INCLUDES_ARM_32_H_

#define CONSOLEIO_write         0
#define XENFEAT_NR_SUBMAPS 1
#define XEN_LEGACY_MAX_VCPUS 1	/* arch == ARM */

typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef uint64_t xen_pfn_t;
typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef uint64_t xen_ulong_t;

/* Arch is ARM, following two structures can be empty */
struct arch_vcpu_info {
};
typedef struct arch_vcpu_info arch_vcpu_info_t;
struct arch_shared_info {
};
typedef struct arch_shared_info arch_shared_info_t;

struct vcpu_time_info {
    /*
     * Updates to the following values are preceded and followed by an
     * increment of 'version'. The guest can therefore detect updates by
     * looking for changes to 'version'. If the least-significant bit of
     * the version number is set then an update is in progress and the guest
     * must wait to read a consistent set of values.
     * The correct way to interact with the version number is similar to
     * Linux's seqlock: see the implementations of read_seqbegin/read_seqretry.
     */
    uint32_t version;
    uint32_t pad0;
    uint64_t tsc_timestamp;   /* TSC at last update of time vals.  */
    uint64_t system_time;     /* Time, in nanosecs, since boot.    */
    /*
     * Current system time:
     *   system_time +
     *   ((((tsc - tsc_timestamp) << tsc_shift) * tsc_to_system_mul) >> 32)
     * CPU frequency (Hz):
     *   ((10^9 << 32) / tsc_to_system_mul) >> tsc_shift
     */
    uint32_t tsc_to_system_mul;
    int8_t   tsc_shift;
    int8_t   pad1[3];
}; /* 32 bytes */
typedef struct vcpu_time_info vcpu_time_info_t;

struct vcpu_info {
    /*
     * 'evtchn_upcall_pending' is written non-zero by Xen to indicate
     * a pending notification for a particular VCPU. It is then cleared
     * by the guest OS /before/ checking for pending work, thus avoiding
     * a set-and-check race. Note that the mask is only accessed by Xen
     * on the CPU that is currently hosting the VCPU. This means that the
     * pending and mask flags can be updated by the guest without special
     * synchronisation (i.e., no need for the x86 LOCK prefix).
     * This may seem suboptimal because if the pending flag is set by
     * a different CPU then an IPI may be scheduled even when the mask
     * is set. However, note:
     *  1. The task of 'interrupt holdoff' is covered by the per-event-
     *     channel mask bits. A 'noisy' event that is continually being
     *     triggered can be masked at source at this very precise
     *     granularity.
     *  2. The main purpose of the per-VCPU mask is therefore to restrict
     *     reentrant execution: whether for concurrency control, or to
     *     prevent unbounded stack usage. Whatever the purpose, we expect
     *     that the mask will be asserted only for short periods at a time,
     *     and so the likelihood of a 'spurious' IPI is suitably small.
     * The mask is read before making an event upcall to the guest: a
     * non-zero mask therefore guarantees that the VCPU will not receive
     * an upcall activation. The mask is cleared when the VCPU requests
     * to block: this avoids wakeup-waiting races.
     */
    uint8_t evtchn_upcall_pending;
#ifdef XEN_HAVE_PV_UPCALL_MASK
    uint8_t evtchn_upcall_mask;
#else /* XEN_HAVE_PV_UPCALL_MASK */
    uint8_t pad0;
#endif /* XEN_HAVE_PV_UPCALL_MASK */
    xen_ulong_t evtchn_pending_sel;
    struct arch_vcpu_info arch;
    struct vcpu_time_info time;
}; /* 64 bytes (x86) */
typedef struct vcpu_info vcpu_info_t;

struct shared_info {
    struct vcpu_info vcpu_info[XEN_LEGACY_MAX_VCPUS];

    /*
     * A domain can create "event channels" on which it can send and receive
     * asynchronous event notifications. There are three classes of event that
     * are delivered by this mechanism:
     *  1. Bi-directional inter- and intra-domain connections. Domains must
     *     arrange out-of-band to set up a connection (usually by allocating
     *     an unbound 'listener' port and avertising that via a storage service
     *     such as xenstore).
     *  2. Physical interrupts. A domain with suitable hardware-access
     *     privileges can bind an event-channel port to a physical interrupt
     *     source.
     *  3. Virtual interrupts ('events'). A domain can bind an event-channel
     *     port to a virtual interrupt source, such as the virtual-timer
     *     device or the emergency console.
     *
     * Event channels are addressed by a "port index". Each channel is
     * associated with two bits of information:
     *  1. PENDING -- notifies the domain that there is a pending notification
     *     to be processed. This bit is cleared by the guest.
     *  2. MASK -- if this bit is clear then a 0->1 transition of PENDING
     *     will cause an asynchronous upcall to be scheduled. This bit is only
     *     updated by the guest. It is read-only within Xen. If a channel
     *     becomes pending while the channel is masked then the 'edge' is lost
     *     (i.e., when the channel is unmasked, the guest must manually handle
     *     pending notifications as no upcall will be scheduled by Xen).
     *
     * To expedite scanning of pending notifications, any 0->1 pending
     * transition on an unmasked channel causes a corresponding bit in a
     * per-vcpu selector word to be set. Each bit in the selector covers a
     * 'C long' in the PENDING bitfield array.
     */
    xen_ulong_t evtchn_pending[sizeof(xen_ulong_t) * 8];
    xen_ulong_t evtchn_mask[sizeof(xen_ulong_t) * 8];

    /*
     * Wallclock time: updated only by control software. Guests should base
     * their gettimeofday() syscall on this wallclock-base value.
     */
    uint32_t wc_version;      /* Version counter: see vcpu_time_info_t. */
    uint32_t wc_sec;          /* Secs  00:00:00 UTC, Jan 1, 1970.  */
    uint32_t wc_nsec;         /* Nsecs 00:00:00 UTC, Jan 1, 1970.  */

    struct arch_shared_info arch;

};
typedef struct shared_info shared_info_t;

struct start_info {
    /* THE FOLLOWING ARE FILLED IN BOTH ON INITIAL BOOT AND ON RESUME.    */
    char magic[32];             /* "xen-<version>-<platform>".            */
    unsigned long nr_pages;     /* Total pages allocated to this domain.  */
    unsigned long shared_info;  /* MACHINE address of shared info struct. */
    uint32_t flags;             /* SIF_xxx flags.                         */
    xen_pfn_t store_mfn;        /* MACHINE page number of shared page.    */
    uint32_t store_evtchn;      /* Event channel for store communication. */
    union {
        struct {
            xen_pfn_t mfn;      /* MACHINE page number of console page.   */
            uint32_t  evtchn;   /* Event channel for console page.        */
        } domU;
        struct {
            uint32_t info_off;  /* Offset of console_info struct.         */
            uint32_t info_size; /* Size of console_info struct from start.*/
        } dom0;
    } console;
    /* THE FOLLOWING ARE ONLY FILLED IN ON INITIAL BOOT (NOT RESUME).     */
    unsigned long pt_base;      /* VIRTUAL address of page directory.     */
    unsigned long nr_pt_frames; /* Number of bootstrap p.t. frames.       */
    unsigned long mfn_list;     /* VIRTUAL address of page-frame list.    */
    unsigned long mod_start;    /* VIRTUAL address of pre-loaded module   */
                                /* (PFN of pre-loaded module if           */
                                /*  SIF_MOD_START_PFN set in flags).      */
    unsigned long mod_len;      /* Size (bytes) of pre-loaded module.     */
#define MAX_GUEST_CMDLINE 1024
    int8_t cmd_line[MAX_GUEST_CMDLINE];
    /* The pfn range here covers both page table and p->m table frames.   */
    unsigned long first_p2m_pfn;/* 1st pfn forming initial P->M table.    */
    unsigned long nr_p2m_frames;/* # of pfns forming initial P->M table.  */
};
typedef struct start_info start_info_t;

typedef struct { unsigned long pte_low, pte_high; } pte_t;
#define __pte(x) ({ unsigned long long _x = (x);        \
    ((pte_t) {(unsigned long)(_x), (unsigned long)(_x>>32)}); })

#define UVMF_INVLPG (2UL<<0)

#ifdef __ASSEMBLY__
#define _AC(X,Y)        X
#define _AT(T,X)        X
#else
#define __AC(X,Y)       (X##Y)
#define _AC(X,Y)        __AC(X,Y)
#define _AT(T,X)        ((T)(X))
#endif
#define PML4_ENTRY_BITS  39
#define PML4_ENTRY_BYTES (_AC(1,UL) << PML4_ENTRY_BITS)
#define PML4_ADDR(_slot)                              \
    (((_AC(_slot, UL) >> 8) * _AC(0xffff000000000000,UL)) | \
             (_AC(_slot, UL) << PML4_ENTRY_BITS))
#define RDWR_MPT_VIRT_START     (PML4_ADDR(261))
#define machine_to_phys_mapping  ((unsigned long *)RDWR_MPT_VIRT_START)

#define DOMID_SELF (0x7FF0U)

#define L1_PAGETABLE_SHIFT      12
#define VIRT_START              ((unsigned long)0)
#define to_phys(x)              ((unsigned long)(x)-VIRT_START)
#define to_virt(x)		((void *)((unsigned long)(x)+VIRT_START))
#define PFN_DOWN(x)     	((x) >> L1_PAGETABLE_SHIFT)
#define PFN_PHYS(x)		((uint64_t)(x) << L1_PAGETABLE_SHIFT)

#define virt_to_pfn(_virt)      (PFN_DOWN(to_phys(_virt)))
#define pfn_to_virt(_pfn)	(to_virt(PFN_PHYS(_pfn)))

typedef unsigned short uint16_t;
typedef uint16_t domid_t;

#define XENMEM_add_to_physmap      7
struct xen_add_to_physmap {
    /* Which domain to change the mapping for. */
    domid_t domid;

    /* Number of pages to go through for gmfn_range */
    uint16_t    size;

    unsigned int space; /* => enum phys_map_space */

#define XENMAPIDX_grant_table_status 0x80000000

    /* Index into space being mapped. */
    xen_ulong_t idx;

    /* GPFN in domid where the source mapping page should appear. */
    xen_pfn_t     gpfn;
};

#define XENMAPSPACE_shared_info  0 /* shared info page */

#define BUG() while (1){}

#define wmb() __asm__("dmb");
#define rmb() __asm__("dmb");
#define mb()  do { dsb(); } while (0)
static __inline__ void clear_bit(int nr, volatile void * addr)
{
        //TODO
        unsigned long *tmp = (unsigned long *)addr;
        tmp[nr >> 5] &= (unsigned long)~(1 << (nr & 0x1f));
}
static __inline__ void set_bit(int nr, volatile void * addr)
{
        //TODO:
        unsigned long *tmp = (unsigned long *)addr;
        tmp[nr >> 5] |= (1 << (nr & 0x1f));
}

static __inline__ void synch_clear_bit(int nr, volatile void * addr)
{
	//TODO:
    clear_bit(nr, addr);
}

typedef uint32_t evtchn_port_t;

struct pt_regs {
        unsigned long r0;
        unsigned long r1;
        unsigned long r2;
        unsigned long r3;
        unsigned long r4;
        unsigned long r5;
        unsigned long r6;
        unsigned long r7;
        unsigned long r8;
        unsigned long r9;
        unsigned long r10;
        unsigned long r11;
        unsigned long r12;
};

#define xchg(ptr,v) ((__typeof__(*(ptr)))__xchg((unsigned long)(v),(ptr),sizeof(*(ptr))))
#define __xg(x) ((volatile long *)(x))

static inline unsigned long __xchg(unsigned long x, volatile void * ptr, int size)
{
	//TODO
	unsigned volatile long y;
	switch(size){
	case 1:
#if CPU_EXCLUSIVE_LDST
		__asm__ __volatile__("1:ldrexb %0, [%1]\n"
			"strexb %3, %2, [%1]\n"
			"cmp %3, #1\n"
			"beq 1b\n\n"
			"dmb\n":"=&r"(y):"r"(ptr), "r"(x), "r"(tmp):"memory");
#else
		y = (*(char *)ptr) & 0x000000ff;
		*((char *)ptr) = (char)x;
#endif
		break;
	case 2:
#if CPU_EXCLUSIVE_LDST
		__asm__ __volatile__("1:ldrexh %0, [%1]\n"
			"strexh %3, %2, [%1]\n"
			"cmp %3, #1\n"
			"beq 1b\n\n"
			"dmb\n":"=&r"(y):"r"(ptr), "r"(x), "r"(tmp):"memory");
#else
		y = (*(short *)ptr) & 0x0000ffff;
		*((short *)ptr) = (short)x;
#endif
		break;
	default: // 4
#if CPU_EXCLUSIVE_LDST
		__asm__ __volatile__("1:ldrex %0, [%1]\n"
			"strex %3, %2, [%1]\n"
			"cmp %3, #1\n"
			"beq 1b\n\n"
			"dmb\n":"=&r"(y):"r"(ptr), "r"(x), "r"(tmp):"memory");
#else
		y = (*(unsigned long *)ptr) & 0xffffffff;
		*((unsigned long *)ptr) = x;
#endif
		break;
	}
    return y;
}

static __inline__ unsigned long __ffs(unsigned long word)
{
	//TODO
	int index = 0;
	while(!(word & (1 << index++))){};

	return index - 1;
}


static inline unsigned long active_evtchns(unsigned int cpu, shared_info_t *sh,
                                                unsigned int idx)
{
        return (sh->evtchn_pending[idx] & ~sh->evtchn_mask[idx]);
}

typedef void (*evtchn_handler_t)(evtchn_port_t, struct pt_regs *, void *);
/* this represents a event handler. Chaining or sharing is not allowed */
typedef struct _ev_action_t {
        evtchn_handler_t handler;
        void *data;
    uint32_t count;
} ev_action_t;
#define NR_EVS 1024

extern shared_info_t shared_info;
extern shared_info_t *HYPERVISOR_shared_info;

static inline void clear_evtchn(uint32_t port)
{
    shared_info_t *s = HYPERVISOR_shared_info;
    synch_clear_bit(port, &s->evtchn_pending[0]);
}

int do_event(evtchn_port_t port, struct pt_regs *regs);
evtchn_port_t bind_evtchn(evtchn_port_t port, evtchn_handler_t handler,
                                                  void *data);

#define L1_PAGETABLE_SHIFT     	   12
#define PFN_PHYS(x)   		   ((uint64_t)(x) << L1_PAGETABLE_SHIFT)
#define VIRT_START                 ((unsigned long)0)
#define to_virt(x)                 ((void *)((unsigned long)(x)+VIRT_START))
#define pfn_to_virt(_pfn)          (to_virt(PFN_PHYS(_pfn)))
#define paddr_to_pfn(pa) ((unsigned long )((pa) >> PAGE_SHIFT))
#define pfn_to_paddr(pf) ((pf) << PAGE_SHIFT)

#endif
