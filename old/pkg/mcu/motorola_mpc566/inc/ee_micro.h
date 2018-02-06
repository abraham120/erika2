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

#ifndef __INCLUDE_MPC566EVB_MICRO_H__
#define __INCLUDE_MPC566EVB_MICRO_H__

#ifndef __MPC5PROTECTED__
#include "cpu/mpc5xx/inc/ee_cpu.h"
#else
#include "cpu/mpc5protected/inc/ee_cpu.h"
#endif

/****************************************************************************/
/*                              MODULE : USIU - MPC566                      */
/****************************************************************************/
    struct USIU_tag {
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 EARB:1;
                EE_VUINT32 EARP:3;
                  EE_VUINT32:4;
                EE_VUINT32 DSHW:1;
                EE_VUINT32 DBGC:2;
                EE_VUINT32 DBPC:1;
                EE_VUINT32 ATWC:1;
                EE_VUINT32 GPC:2;
                EE_VUINT32 DLK:1;
                  EE_VUINT32:1;
                EE_VUINT32 SC:2;
                EE_VUINT32 RCTX:1;
                EE_VUINT32 MLRC:2;
                  EE_VUINT32:2;
                EE_VUINT32 MTSC:1;
                EE_VUINT32 NOSHOW:1;
                EE_VUINT32 EICEN:1;
                EE_VUINT32 LPMASK_EN:1;
                  EE_VUINT32:4;
            } B;
        } SIUMCR;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 SWTC:16;
                EE_VUINT32 BMT:8;
                EE_VUINT32 BME:1;
                  EE_VUINT32:3;
                EE_VUINT32 SWF:1;
                EE_VUINT32 SWE:1;
                EE_VUINT32 SWRI:1;
                EE_VUINT32 SWP:1;
            } B;
        } SYPCR;
        EE_VUINT32 res0;
        EE_VUINT16 res1;
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16 SWSR:16;
            } B;
        } SWSR;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IRQ0:1;
                EE_VUINT32 LVL0:1;
                EE_VUINT32 IRQ1:1;
                EE_VUINT32 LVL1:1;
                EE_VUINT32 IRQ2:1;
                EE_VUINT32 LVL2:1;
                EE_VUINT32 IRQ3:1;
                EE_VUINT32 LVL3:1;
                EE_VUINT32 IRQ4:1;
                EE_VUINT32 LVL4:1;
                EE_VUINT32 IRQ5:1;
                EE_VUINT32 LVL5:1;
                EE_VUINT32 IRQ6:1;
                EE_VUINT32 LVL6:1;
                EE_VUINT32 IRQ7:1;
                EE_VUINT32 LVL7:1;
                  EE_VUINT32:16;
            } B;
        } SIPEND;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IRM0:1;
                EE_VUINT32 LVM0:1;
                EE_VUINT32 IRM1:1;
                EE_VUINT32 LVM1:1;
                EE_VUINT32 IRM2:1;
                EE_VUINT32 LVM2:1;
                EE_VUINT32 IRM3:1;
                EE_VUINT32 LVM3:1;
                EE_VUINT32 IRM4:1;
                EE_VUINT32 LVM4:1;
                EE_VUINT32 IRM5:1;
                EE_VUINT32 LVM5:1;
                EE_VUINT32 IRM6:1;
                EE_VUINT32 LVM6:1;
                EE_VUINT32 IRM7:1;
                EE_VUINT32 LVM7:1;
                  EE_VUINT32:16;
            } B;
        } SIMASK;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 ED0:1;
                EE_VUINT32 WM0:1;
                EE_VUINT32 ED1:1;
                EE_VUINT32 WM1:1;
                EE_VUINT32 ED2:1;
                EE_VUINT32 WM2:1;
                EE_VUINT32 ED3:1;
                EE_VUINT32 WM3:1;
                EE_VUINT32 ED4:1;
                EE_VUINT32 WM4:1;
                EE_VUINT32 ED5:1;
                EE_VUINT32 WM5:1;
                EE_VUINT32 ED6:1;
                EE_VUINT32 WM6:1;
                EE_VUINT32 ED7:1;
                EE_VUINT32 WM7:1;
                  EE_VUINT32:16;
            } B;
        } SIEL;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 INTERRUPT_CODE:8;
                  EE_VUINT32:24;
            } B;
        } SIVEC;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32:18;
                EE_VUINT32 IEXT:1;
                EE_VUINT32 IBMT:1;
                  EE_VUINT32:6;
                EE_VUINT32 DEXT:1;
                EE_VUINT32 DBM:1;
                  EE_VUINT32:4;
            } B;
        } TESR;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } SGPIODT1;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 SGPIOC:8;
                EE_VUINT32 SGPIOA:24;
            } B;
        } SGPIODT2;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 SDDRC:8;
                  EE_VUINT32:8;
                EE_VUINT32 GDDR0:1;
                EE_VUINT32 GDDR1:1;
                EE_VUINT32 GDDR2:1;
                EE_VUINT32 GDDR3:1;
                EE_VUINT32 GDDR4:1;
                EE_VUINT32 GDDR5:1;
                  EE_VUINT32:2;
                EE_VUINT32 SDDRD:8;
            } B;
        } SGPIOCR;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32:16;
                EE_VUINT32 PRPM:1;
                EE_VUINT32 SLVM:1;
                  EE_VUINT32:1;
                EE_VUINT32 SIZE:2;
                EE_VUINT32 SUPU:1;
                EE_VUINT32 INST:1;
                  EE_VUINT32:2;
                EE_VUINT32 RESV:1;
                EE_VUINT32 CONT:1;
                  EE_VUINT32:1;
                EE_VUINT32 TRAC:1;
                EE_VUINT32 SIZEN:1;
                  EE_VUINT32:2;
            } B;
        } EMCR;
        EE_VUINT32 res1aa;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 PREDIS_EN:1;
                EE_VUINT32:31;
            } B;
        } PDMCR2;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 SLRC:4;
                  EE_VUINT32:2;
                EE_VUINT32 PRDS:1;
                EE_VUINT32 SPRDS:1;
                EE_VUINT32 FTPU_PU:1;
                EE_VUINT32 GP_MASK:7;
                EE_VUINT32 GSP_MASK:2;
                  EE_VUINT32:14;
            } B;
        } PDMCR;
        /* New USIU registers added 04Oct99 */
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IRQ0:1;
                EE_VUINT32 LVL0:1;
                EE_VUINT32 IMBIRQ0:1;
                EE_VUINT32 IMBIRQ1:1;
                EE_VUINT32 IMBIRQ2:1;
                EE_VUINT32 IMBIRQ3:1;
                EE_VUINT32 IRQ1:1;
                EE_VUINT32 LVL1:1;
                EE_VUINT32 IMBIRQ4:1;
                EE_VUINT32 IMBIRQ5:1;
                EE_VUINT32 IMBIRQ6:1;
                EE_VUINT32 IMBIRQ7:1;
                EE_VUINT32 IRQ2:1;
                EE_VUINT32 LVL2:1;
                EE_VUINT32 IMBIRQ8:1;
                EE_VUINT32 IMBIRQ9:1;
                EE_VUINT32 IMBIRQ10:1;
                EE_VUINT32 IMBIRQ11:1;
                EE_VUINT32 IRQ3:1;
                EE_VUINT32 LVL3:1;
                EE_VUINT32 IMBIRQ12:1;
                EE_VUINT32 IMBIR13:1;
                EE_VUINT32 IMBIR14:1;
                EE_VUINT32 IMBIRQ15:1;
                EE_VUINT32 IRQ4:1;
                EE_VUINT32 LVL4:1;
                EE_VUINT32 IMBIRQ16:1;
                EE_VUINT32 IMBIRQ17:1;
                EE_VUINT32 IMBIRQ18:1;
                EE_VUINT32 IMBIRQ19:1;
                EE_VUINT32 IRQ5:1;
                EE_VUINT32 LVL5:1;
            } B;
        } SIPEND2;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IMBIRQ20:1;
                EE_VUINT32 IMBIRQ21:1;
                EE_VUINT32 IMBIRQ22:1;
                EE_VUINT32 IMBIRQ23:1;
                EE_VUINT32 IRQ6:1;
                EE_VUINT32 LVL6:1;
                EE_VUINT32 IMBIRQ24:1;
                EE_VUINT32 IMBIRQ25:1;
                EE_VUINT32 IMBIRQ26:1;
                EE_VUINT32 IMBIRQ27:1;
                EE_VUINT32 IRQ7:1;
                EE_VUINT32 LVL7:1;
                EE_VUINT32 IMBIRQ28:1;
                EE_VUINT32 IMBIRQ29:1;
                EE_VUINT32 IMBIRQ30:1;
                EE_VUINT32 IMBIRQ31:1;
                  EE_VUINT32:16;
            } B;
        } SIPEND3;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IRQ0:1;
                EE_VUINT32 LVL0:1;
                EE_VUINT32 IMBIRQ0:1;
                EE_VUINT32 IMBIRQ1:1;
                EE_VUINT32 IMBIRQ2:1;
                EE_VUINT32 IMBIRQ3:1;
                EE_VUINT32 IRQ1:1;
                EE_VUINT32 LVL1:1;
                EE_VUINT32 IMBIRQ4:1;
                EE_VUINT32 IMBIRQ5:1;
                EE_VUINT32 IMBIRQ6:1;
                EE_VUINT32 IMBIRQ7:1;
                EE_VUINT32 IRQ2:1;
                EE_VUINT32 LVL2:1;
                EE_VUINT32 IMBIRQ8:1;
                EE_VUINT32 IMBIRQ9:1;
                EE_VUINT32 IMBIRQ10:1;
                EE_VUINT32 IMBIRQ11:1;
                EE_VUINT32 IRQ3:1;
                EE_VUINT32 LVL3:1;
                EE_VUINT32 IMBIRQ12:1;
                EE_VUINT32 IMBIRQ13:1;
                EE_VUINT32 IMBIRQ14:1;
                EE_VUINT32 IMBIRQ15:1;
                EE_VUINT32 IRQ4:1;
                EE_VUINT32 LVL4:1;
                EE_VUINT32 IMBIRQ16:1;
                EE_VUINT32 IMBIRQ17:1;
                EE_VUINT32 IMBIRQ18:1;
                EE_VUINT32 IMBIRQ19:1;
                EE_VUINT32 IRQ5:1;
                EE_VUINT32 LVL5:1;
            } B;
        } SIMASK2;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IMBIRQ20:1;
                EE_VUINT32 IMBIRQ21:1;
                EE_VUINT32 IMBIRQ22:1;
                EE_VUINT32 IMBIRQ23:1;
                EE_VUINT32 IRQ6:1;
                EE_VUINT32 LVL6:1;
                EE_VUINT32 IMBIRQ24:1;
                EE_VUINT32 IMBIRQ25:1;
                EE_VUINT32 IMBIRQ26:1;
                EE_VUINT32 IMBIRQ27:1;
                EE_VUINT32 IRQ7:1;
                EE_VUINT32 LVL7:1;
                EE_VUINT32 IMBIRQ28:1;
                EE_VUINT32 IMBIRQ29:1;
                EE_VUINT32 IMBIRQ30:1;
                EE_VUINT32 IMBIRQ31:1;
                  EE_VUINT32:16;
            } B;
        } SIMASK3;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IRQ0:1;
                EE_VUINT32 LVL0:1;
                EE_VUINT32 IMBIRQ0:1;
                EE_VUINT32 IMBIRQ1:1;
                EE_VUINT32 IMBIRQ2:1;
                EE_VUINT32 IMBIRQ3:1;
                EE_VUINT32 IRQ1:1;
                EE_VUINT32 LVL1:1;
                EE_VUINT32 IMBIRQ4:1;
                EE_VUINT32 IMBIRQ5:1;
                EE_VUINT32 IMBIRQ6:1;
                EE_VUINT32 IMBIRQ7:1;
                EE_VUINT32 IRQ2:1;
                EE_VUINT32 LVL2:1;
                EE_VUINT32 IMBIRQ8:1;
                EE_VUINT32 IMBIRQ9:1;
                EE_VUINT32 IMBIRQ10:1;
                EE_VUINT32 IMBIRQ11:1;
                EE_VUINT32 IRQ3:1;
                EE_VUINT32 LVL3:1;
                EE_VUINT32 IMBIRQ12:1;
                EE_VUINT32 IMBIRQ13:1;
                EE_VUINT32 IMBIRQ14:1;
                EE_VUINT32 IMBIRQ15:1;
                EE_VUINT32 IRQ4:1;
                EE_VUINT32 LVL4:1;
                EE_VUINT32 IMBIRQ16:1;
                EE_VUINT32 IMBIRQ17:1;
                EE_VUINT32 IMBIRQ18:1;
                EE_VUINT32 IMBIRQ19:1;
                EE_VUINT32 IRQ5:1;
                EE_VUINT32 LVL5:1;
            } B;
        } SISR2;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 IMBIRQ20:1;
                EE_VUINT32 IMBIRQ21:1;
                EE_VUINT32 IMBIRQ22:1;
                EE_VUINT32 IMBIRQ23:1;
                EE_VUINT32 IRQ6:1;
                EE_VUINT32 LVL6:1;
                EE_VUINT32 IMBIRQ24:1;
                EE_VUINT32 IMBIRQ25:1;
                EE_VUINT32 IMBIRQ26:1;
                EE_VUINT32 IMBIRQ27:1;
                EE_VUINT32 IRQ7:1;
                EE_VUINT32 LVL7:1;
                EE_VUINT32 IMBIRQ28:1;
                EE_VUINT32 IMBIRQ29:1;
                EE_VUINT32 IMBIRQ30:1;
                EE_VUINT32 IMBIRQ31:1;
                  EE_VUINT32:16;
            } B;
        } SISR3;
        EE_VUINT32 res2[42];
        /*Memory Controller Registers */
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 BA:17;
                EE_VUINT32 AT:3;
                EE_VUINT32 PS:2;
                  EE_VUINT32:1;
                EE_VUINT32 WP:1;
                  EE_VUINT32:2;
                EE_VUINT32 WEBS:1;
                EE_VUINT32 TBDIP:1;
                EE_VUINT32 LBDIP:1;
                EE_VUINT32 SETA:1;
                EE_VUINT32 BI:1;
                EE_VUINT32 V:1;
            } B;
        } BR0;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 AM:17;
                EE_VUINT32 ATM:3;
                EE_VUINT32 CSNT:1;
                EE_VUINT32 ACS:2;
                EE_VUINT32 EHTR:1;
                EE_VUINT32 SCY:4;
                EE_VUINT32 BSCY:3;
                EE_VUINT32 TRLX:1;
            } B;
        } OR0;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 BA:17;
                EE_VUINT32 AT:3;
                EE_VUINT32 PS:2;
                  EE_VUINT32:1;
                EE_VUINT32 WP:1;
                  EE_VUINT32:2;
                EE_VUINT32 WEBS:1;
                EE_VUINT32 TBDIP:1;
                EE_VUINT32 LBDIP:1;
                EE_VUINT32 SETA:1;
                EE_VUINT32 BI:1;
                EE_VUINT32 V:1;
            } B;
        } BR1;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 AM:17;
                EE_VUINT32 ATM:3;
                EE_VUINT32 CSNT:1;
                EE_VUINT32 ACS:2;
                EE_VUINT32 EHTR:1;
                EE_VUINT32 SCY:4;
                EE_VUINT32 BSCY:3;
                EE_VUINT32 TRLX:1;
            } B;
        } OR1;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 BA:17;
                EE_VUINT32 AT:3;
                EE_VUINT32 PS:2;
                  EE_VUINT32:1;
                EE_VUINT32 WP:1;
                  EE_VUINT32:2;
                EE_VUINT32 WEBS:1;
                EE_VUINT32 TBDIP:1;
                EE_VUINT32 LBDIP:1;
                EE_VUINT32 SETA:1;
                EE_VUINT32 BI:1;
                EE_VUINT32 V:1;
            } B;
        } BR2;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 AM:17;
                EE_VUINT32 ATM:3;
                EE_VUINT32 CSNT:1;
                EE_VUINT32 ACS:2;
                EE_VUINT32 EHTR:1;
                EE_VUINT32 SCY:4;
                EE_VUINT32 BSCY:3;
                EE_VUINT32 TRLX:1;
            } B;
        } OR2;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 BA:17;
                EE_VUINT32 AT:3;
                EE_VUINT32 PS:2;
                  EE_VUINT32:1;
                EE_VUINT32 WP:1;
                  EE_VUINT32:2;
                EE_VUINT32 WEBS:1;
                EE_VUINT32 TBDIP:1;
                EE_VUINT32 LBDIP:1;
                EE_VUINT32 SETA:1;
                EE_VUINT32 BI:1;
                EE_VUINT32 V:1;
            } B;
        } BR3;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 AM:17;
                EE_VUINT32 ATM:3;
                EE_VUINT32 CSNT:1;
                EE_VUINT32 ACS:2;
                EE_VUINT32 EHTR:1;
                EE_VUINT32 SCY:4;
                EE_VUINT32 BSCY:3;
                EE_VUINT32 TRLX:1;
            } B;
        } OR3;
        EE_VUINT32 res3[8];
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32:1;
                EE_VUINT32 BA:6;
                  EE_VUINT32:3;
                EE_VUINT32 AT:3;
                  EE_VUINT32:15;
                EE_VUINT32 DMCS:3;
                EE_VUINT32 DME:1;
            } B;
        } DMBR;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32:1;
                EE_VUINT32 AM:6;
                  EE_VUINT32:3;
                EE_VUINT32 ATM:3;
                  EE_VUINT32:19;
            } B;
        } DMOR;
        EE_VUINT32 res4[12];
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16:8;
                EE_VUINT16 WPER0:1;
                EE_VUINT16 WPER1:1;
                EE_VUINT16 WPER2:1;
                EE_VUINT16 WPER3:1;
                  EE_VUINT16:4;
            } B;
        } MSTAT;
        EE_VUINT16 res4a;
        EE_VUINT32 res4b[33];
        /*System integration Timers */
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16 TBIRQ:8;
                EE_VUINT16 REFA:1;
                EE_VUINT16 REFB:1;
                  EE_VUINT16:2;
                EE_VUINT16 REFAE:1;
                EE_VUINT16 REFBE:1;
                EE_VUINT16 TBF:1;
                EE_VUINT16 TBE:1;
            } B;
        } TBSCR;
        EE_VUINT16 res4c;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } TBREF0;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } TBREF1;
        EE_VUINT32 res5[5];
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16 RTCIRQ:8;
                EE_VUINT16 SEC:1;
                EE_VUINT16 ALR:1;
                  EE_VUINT16:1;
                EE_VUINT16 M:1;
                EE_VUINT16 SIE:1;
                EE_VUINT16 ALE:1;
                EE_VUINT16 RTF:1;
                EE_VUINT16 RTE:1;
            } B;
        } RTCSC;
        EE_VUINT16 res5a;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RTC;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RTSEC;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RTCAL;
        EE_VUINT32 res6[4];
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16 PIRQ:8;
                EE_VUINT16 PS:1;
                  EE_VUINT16:4;
                EE_VUINT16 PIE:1;
                EE_VUINT16 PITF:1;
                EE_VUINT16 PTE:1;
            } B;
        } PISCR;
        EE_VUINT16 res6a;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 PITC:16;
                  EE_VUINT32:16;
            } B;
        } PITC;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 PIT:16;
                  EE_VUINT32:16;
            } B;
        } PITR;
        EE_VUINT32 res7[13];
        /*Clocks and Reset */
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 DBCT:1;
                EE_VUINT32 COM:2;
                EE_VUINT32 DCSLR:1;
                EE_VUINT32 MFPDL:1;
                EE_VUINT32 LPML:1;
                EE_VUINT32 TBS:1;
                EE_VUINT32 RTDIV:1;
                EE_VUINT32 STBUC:1;
                EE_VUINT32 CQDS:1;
                EE_VUINT32 PRQEN:1;
                EE_VUINT32 RTSEL:1;
                EE_VUINT32 BUCS:1;
                EE_VUINT32 EBDF:2;
                EE_VUINT32 LME:1;
                EE_VUINT32 EECLK:2;
                EE_VUINT32 ENGDIV:6;
                  EE_VUINT32:1;
                EE_VUINT32 DFNL:3;
                  EE_VUINT32:1;
                EE_VUINT32 DFNH:3;
            } B;
        } SCCR;
        union {
            EE_VUINT32 R;
            struct {
                EE_VUINT32 MF:12;
                EE_VUINT32 MFPDL:1;
                EE_VUINT32 LOCS:1;
                EE_VUINT32 LOCSS:1;
                EE_VUINT32 SPLS:1;
                EE_VUINT32 SPLSS:1;
                EE_VUINT32 TEXPS:1;
                EE_VUINT32 LPML:1;
                EE_VUINT32 TMIST:1;
                  EE_VUINT32:1;
                EE_VUINT32 CSRC:1;
                EE_VUINT32 LPM:2;
                EE_VUINT32 CSR:1;
                EE_VUINT32 LOLRE:1;
                  EE_VUINT32:1;
                EE_VUINT32 DIVF:5;
            } B;
        } PLPRCR;
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16 EHRS:1;
                EE_VUINT16 ESRS:1;
                EE_VUINT16 LLRS:1;
                EE_VUINT16 SWRS:1;
                EE_VUINT16 CSRS:1;
                EE_VUINT16 DBHRS:1;
                EE_VUINT16 DBSRS:1;
                EE_VUINT16 JTRS:1;
                EE_VUINT16 OCCS:1;
                EE_VUINT16 ILBC:1;
                EE_VUINT16 GPOR:1;
                EE_VUINT16 GHRST:1;
                EE_VUINT16 GSRST:1;
                  EE_VUINT16:3;
            } B;
        } RSR;
        EE_VUINT16 res7a;
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16 COLIRQ:8;
                EE_VUINT16 COLIS:1;
                  EE_VUINT16:1;
                  EE_VUINT16 COLIE:1;
                  EE_VUINT16:5;
            } B;
        } COLIR;
        EE_VUINT16 res7B;
        union {
            EE_VUINT16 R;
            struct {
                EE_VUINT16:1;
                EE_VUINT16 LVSRS:4;
                EE_VUINT16 VSRDE:1;
                EE_VUINT16 LVDECRAM:1;
                  EE_VUINT16:9;
            } B;
        } VSRMCR;
        EE_VUINT16 res7c;
        EE_VUINT32 res8[27];
        /*System Inegration Timer Keys */
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } TBSCRK;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } TBREF0K;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } TBREF1K;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } TBK;
        EE_VUINT32 res9[4];
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RTCSCK;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RTCK;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RTSECK;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RTCALK;
        EE_VUINT32 res10[4];
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } PISCRK;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } PITCK;
        EE_VUINT32 res11[14];
        /*Clocks and Reset Keys */
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } SCCRK;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } PLPRCRK;
        union {
            EE_VUINT32 R;
            EE_VUINT32 B;
        } RSRK;
    };

/****************************************************************************/
/*                              MODULE :UIMB                                */
/****************************************************************************/
struct UIMB_tag {
    union {
        EE_VUINT32 R;
        struct {
            EE_VUINT32 STOP:1;
            EE_VUINT32 IRQMUX:2;
            EE_VUINT32 HSPEED:1;
              EE_VUINT32:28;
        } B;
    } UMCR;

    EE_VUINT32 res0[3];

    union {
        EE_VUINT32 R;
        EE_VUINT32 B;
    } UTSTCREG;

    EE_VUINT32 res1[3];

    union {
        EE_VUINT32 R;
        struct {
            EE_VUINT32 LVL0:1;
            EE_VUINT32 LVL1:1;
            EE_VUINT32 LVL2:1;
            EE_VUINT32 LVL3:1;
            EE_VUINT32 LVL4:1;
            EE_VUINT32 LVL5:1;
            EE_VUINT32 LVL6:1;
            EE_VUINT32 LVL7:1;
            EE_VUINT32 LVL8:1;
            EE_VUINT32 LVL9:1;
            EE_VUINT32 LVL10:1;
            EE_VUINT32 LVL11:1;
            EE_VUINT32 LVL12:1;
            EE_VUINT32 LVL13:1;
            EE_VUINT32 LVL14:1;
            EE_VUINT32 LVL15:1;
            EE_VUINT32 LVL16:1;
            EE_VUINT32 LVL17:1;
            EE_VUINT32 LVL18:1;
            EE_VUINT32 LVL19:1;
            EE_VUINT32 LVL20:1;
            EE_VUINT32 LVL21:1;
            EE_VUINT32 LVL22:1;
            EE_VUINT32 LVL23:1;
            EE_VUINT32 LVL24:1;
            EE_VUINT32 LVL25:1;
            EE_VUINT32 LVL26:1;
            EE_VUINT32 LVL27:1;
            EE_VUINT32 LVL28:1;
            EE_VUINT32 LVL29:1;
            EE_VUINT32 LVL30:1;
            EE_VUINT32 LVL31:1;
        } B;
    } UIPEND;
};

/****************************************************************************/
/*                                 IRQ Handling                             */
/****************************************************************************/
#ifndef __ENHANCED_IRQ__

#define IRQ_EXT0_MASK (1<<31)	/* IRQ Ext 0 */
#define IRQ_EXT1_MASK (1<<29)	/* IRQ Ext 1 */
#define IRQ_EXT2_MASK (1<<27)	/* IRQ Ext 2 */
#define IRQ_EXT3_MASK (1<<25)	/* IRQ Ext 3 */
#define IRQ_EXT4_MASK (1<<23)	/* IRQ Ext 4 */
#define IRQ_EXT5_MASK (1<<21)	/* IRQ Ext 5 */
#define IRQ_EXT6_MASK (1<<19)	/* IRQ Ext 6 */
#define IRQ_EXT7_MASK (1<<18)	/* IRQ Ext 7 */
#define IRQ_LVL0_MASK (1<<30)	/* IRQ Level 0 */
#define IRQ_LVL1_MASK (1<<28)	/* IRQ Level 1 */
#define IRQ_LVL2_MASK (1<<26)	/* IRQ Level 2 */
#define IRQ_LVL3_MASK (1<<24)	/* IRQ Level 3 */
#define IRQ_LVL4_MASK (1<<22)	/* IRQ Level 4 */
#define IRQ_LVL5_MASK (1<<20)	/* IRQ Level 5 */
#define IRQ_LVL6_MASK (1<<18)	/* IRQ Level 6 */
#define IRQ_LVL7_MASK (1<<16)	/* IRQ Level 7 */

#else // __ENHANCED_IRQ__

#define IRQ_EXT0_MASK 0x80000000   /* IRQ Ext 0 (Non-Maskable) */
#define IRQ_EXT1_MASK 0x02000000   /* IRQ Ext 1 */
#define IRQ_EXT2_MASK 0x00040000   /* IRQ Ext 2 */
#define IRQ_EXT3_MASK 0x00002000   /* IRQ Ext 3 */
#define IRQ_EXT4_MASK 0x00000080   /* IRQ Ext 4 */
#define IRQ_EXT5_MASK 0x00000002   /* IRQ Ext 5 */
#define IRQ_EXT6_MASK 0x08000000   /* IRQ Ext 6 */
#define IRQ_EXT7_MASK 0x00200000   /* IRQ Ext 7 */
#define IRQ_LVL0_MASK 0x40000000
#define IRQ_LVL1_MASK 0x01000000
#define IRQ_LVL2_MASK 0x00080000
#define IRQ_LVL3_MASK 0x00001000
#define IRQ_LVL4_MASK 0x00000080
#define IRQ_LVL5_MASK 0x00000001
#define IRQ_LVL6_MASK 0x08000000
#define IRQ_LVL7_MASK 0x00100000

#define DISCR 0x08100000

#endif // __ENHANCED_IRQ__
                                                                                
#define IRQ_LVL0 0x80
#define IRQ_LVL1 0x40
#define IRQ_LVL2 0x20
#define IRQ_LVL7 0x01
                                                                                
#define IRQ_GLOBAL_MASK (0)

#endif
