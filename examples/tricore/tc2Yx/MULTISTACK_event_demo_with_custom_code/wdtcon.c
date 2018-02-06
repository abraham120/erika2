/*  wdtcon.c -- Lock/unlock the ENDINIT bit in WDTCON to gain write access
                for ENDINIT-protected SFRs (such as BIV, BTV and the CLC
                registers of the various core functional blocks).

    Copyright (C) 2000 - 2012 HighTec EDV-Systeme GmbH.

    This file is part of GCC.

    GCC is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3, or (at your option)
    any later version.

    GCC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    Under Section 7 of GPL version 3, you are granted additional
    permissions described in the GCC Runtime Library Exception, version
    3.1, as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License and
    a copy of the GCC Runtime Library Exception along with this program;
    see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
    <http://www.gnu.org/licenses/>.  */


#include <machine/intrinsics.h>


typedef struct
{
    unsigned long _con0;
    unsigned long _con1;
} WdtCon_t;


/* on the AURIX (TC27XX) each core has its own WDTCON address
   therefore we need special read/write-function to the wdtcon0/1
   registers
   */
#define CORE_ID_ADDR            0xFE1C
#define WDTCON_BASE_ADDR        0xF0036100

static inline WdtCon_t * __getWdtBase(void)
{
    unsigned int coreId;

    /* get the core ID from CPU_ID (csfr_base + 0xfe1c) */
    coreId = __MFCR(CORE_ID_ADDR) & 3;

    return (WdtCon_t *)(WDTCON_BASE_ADDR + (coreId * 0xc));
}


/* Unlock (reset) the ENDINIT bit.  */
void unlock_wdtcon(void)
{
    unsigned int passwd;
    volatile WdtCon_t *wdtaddr;

    wdtaddr = __getWdtBase();

    passwd  = wdtaddr->_con0;
    passwd &= 0xffffff00;
    wdtaddr->_con0 = passwd | 0xf1;
    _dsync();
    wdtaddr->_con0 = passwd | 0xf2;
    /* read back new value ==> synchronise LFI */
    passwd = wdtaddr->_con0;
}

/* Lock (set) the ENDINIT bit.  */
void lock_wdtcon(void)
{
    unsigned int passwd;
    volatile WdtCon_t *wdtaddr;

    wdtaddr = __getWdtBase();

    passwd  = wdtaddr->_con0;
    passwd &= 0xffffff00;
    wdtaddr->_con0 = passwd | 0xf1;
    _dsync();
    passwd |= 3;
    wdtaddr->_con0 = passwd | 0xf2;
    /* read back new value ==> synchronise LFI */
    passwd = wdtaddr->_con0;
}
