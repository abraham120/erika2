/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * MPC564XL register mappings
 * Author: 2012 Francesco Esposito
 *
 * The following APIs work for XPC56XX mother board and XPC56XL
 * 144LQFP Mini-module.
 * All J8 jumpers ON (Enable leds)
 * J9 jumpers (buttons):
 * - pin2 (J9) - pin1 (PJ9, pinX X+1,2,3,...)
 * - pin4 (J9) - pin16 (PJ9)
 * - pin6 (J9) - pin2 (PJ7)
 * - pin8 (J9) - pin14 (PJ5)
 * Note: the default button pins cannot be used since PD0, PD1,
 *       PD2 and PD3 of the MPC5643L do not support external IRQs
 */

#ifndef INCLUDE_EE_FREESCALE_MPC564XL_BOARD_H
#define INCLUDE_EE_FREESCALE_MPC564XL_BOARD_H

#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>

/* Macro used to manage fault conditions */
#define FCCU_NCFK_KEY 0xAB3498FE
#define FCCU_CFK_KEY  0x618B7A50

__INLINE__ void __ALWAYS_INLINE__ InitHW(void);
__INLINE__ void __ALWAYS_INLINE__ InitSysclk(void);
__INLINE__ void __ALWAYS_INLINE__ DisableWatchdog(void);
__INLINE__ void __ALWAYS_INLINE__ InitModesAndClks(void);
__INLINE__ void __ALWAYS_INLINE__ InitPeriClkGen(void);
__INLINE__ void __ALWAYS_INLINE__ ClearFails(void);

#define SIU_BASE	0xc3f90000

#define SIU_PCRS	((volatile EE_UINT16 *)(SIU_BASE+0x0040))

/* Leds */
#define SIU_PCR52	SIU_PCRS[52]
#define SIU_PCR53	SIU_PCRS[53]
#define SIU_PCR54	SIU_PCRS[54]
#define SIU_PCR55	SIU_PCRS[55]

/* Button */
#define SIU_PCR0    SIU_PCRS[0]
#define SIU_PCR15   SIU_PCRS[15]
#define SIU_PCR17   SIU_PCRS[17]
#define SIU_PCR77   SIU_PCRS[77]

#define SIU_GPIO	((volatile EE_UINT8 *)(SIU_BASE + 0x0600))
#define SIU_IREER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0028))
#define SIU_IFEER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x002c))
#define SIU_ISR		(*(volatile EE_UINT32 *)(SIU_BASE + 0x0014))
#define SIU_IRER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0018))
#define SIU_IFER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0030))

#ifdef __USE_LEDS__

#define LED_0	1
#define LED_1	2
#define LED_2	4
#define LED_3	8

/* Leds initialization */
__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void)
{
	SIU_PCR52 = 0x4200;
	SIU_PCR53 = 0x4200;
	SIU_PCR54 = 0x4200;
	SIU_PCR55 = 0x4200;

	/* Turn leds off after initialization */
	SIU_GPIO[52] = 1;
	SIU_GPIO[53] = 1;
	SIU_GPIO[54] = 1;
	SIU_GPIO[55] = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds(EE_UREG led)
{
	SIU_GPIO[52] = ~(led & 1) & 1;
	SIU_GPIO[53] = ~((led >> 1) & 1) & 1;
	SIU_GPIO[54] = ~((led >> 2) & 1) & 1;
	SIU_GPIO[55] = ~((led >> 3) & 1) & 1;
}

/* Turn ALL leds on */
__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void)
{
	SIU_GPIO[52] = 0;
	SIU_GPIO[53] = 0;
	SIU_GPIO[54] = 0;
	SIU_GPIO[55] = 0;
}

/* Turn ALL leds off */
__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void)
{
	SIU_GPIO[52] = 1;
	SIU_GPIO[53] = 1;
	SIU_GPIO[54] = 1;
	SIU_GPIO[55] = 1;
}

/* turn specific led on/off: val=1 off, val=0 on */
__INLINE__ void __ALWAYS_INLINE__ EE_led_set(EE_UREG idx, EE_UREG val)
{
	SIU_GPIO[52 + idx] = val;
}

/* Active Low */
#define EE_led_0_on()	EE_led_set(0, 0);
#define EE_led_0_off()	EE_led_set(0, 1);
#define EE_led_1_on()	EE_led_set(1, 0);
#define EE_led_1_off()	EE_led_set(1, 1);
#define EE_led_2_on()	EE_led_set(2, 0);
#define EE_led_2_off()	EE_led_set(2, 1);
#define EE_led_3_on()	EE_led_set(3, 0);
#define EE_led_3_off()	EE_led_set(3, 1);

#endif

#ifdef __USE_BUTTONS__

#define BUTTON_0	1U
#define BUTTON_1	2U
#define BUTTON_2	4U
#define BUTTON_3	8U

/* input parameter necessary to guarantee backward compatibility of demos */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_disable_interrupts(EE_UREG btn)
{
	EE_UINT32 old_irer;

	old_irer = SIU_IRER;

	/* Disable EIRQ[0], EIRQ[14], EIRQ[16], EIRQ[25] */
    if (btn == BUTTON_0) {
		SIU_IRER = old_irer & ~0x1U;
	}
	else if(btn == BUTTON_1) {
		SIU_IRER = old_irer & ~0x4000U;
	}
	else if(btn == BUTTON_2) {
		SIU_IRER = old_irer & ~0x10000U;
	}
	else if(btn == BUTTON_3) {
		SIU_IRER = old_irer & ~0x02000000U;
	}
	else {
		/* button not supported */
	}
}

/* input parameter necessary to guarantee backward compatibility of demos */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_enable_interrupts(EE_UREG btn)
{
	EE_UINT32 old_irer;
	EE_UINT32 old_ifeer;

	old_irer = SIU_IRER;
    old_ifeer = SIU_IFEER;

	/* Enable EIRQ[0], EIRQ[14], EIRQ[16], EIRQ[25] */
    if (btn == BUTTON_0) {
		SIU_IRER = old_irer | 0x1U;
        SIU_IFEER = old_ifeer | 0x1;
	}
	else if(btn == BUTTON_1) {
		SIU_IRER = old_irer | 0x4000U;
        SIU_IFEER = old_ifeer | 0x4000U;
	}
	else if(btn == BUTTON_2) {
		SIU_IRER = old_irer | 0x10000U;
        SIU_IFEER = old_ifeer | 0x10000U;
	}
	else if(btn == BUTTON_3) {
		SIU_IRER = old_irer | 0x02000000U;
        SIU_IFEER = old_ifeer | 0x02000000U;
	}
	else {
		/* button not supported */
	}
}

/* Clear specific ISR flag associated to a specific button */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_clear_ISRflag(EE_UREG btn)
{
	EE_UINT32 val;

	/* Save old ISR value */
	val = SIU_ISR;

    /* Clear EIRQ[0], EIRQ[14], EIRQ[16], EIRQ[25] */
	if (btn == BUTTON_0) {
		SIU_ISR = val | 0x1U;
	}
	else if(btn == BUTTON_1) {
		SIU_ISR = val | 0x4000U;
	}
	else if(btn == BUTTON_2) {
		SIU_ISR = val | 0x10000U;
	}
	else if(btn == BUTTON_3) {
		SIU_ISR = val | 0x02000000U;
	}
	else {
		/* button not supported */
	}
}

/* Get button 0 status: 1 if button is pressed */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B0(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0800))&0x01000000);
}

/* Get button 1 status: 1 if button is pressed */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B1(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x080C))&0x00000001);
}

/* Get button 2 status: 1 if button is pressed */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B2(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0810))&0x00010000);
}

/* Get button 3 status: 1 if button is pressed */
__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B3(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x084C))&0x00010000);
}

/* Buttons initialization */
__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init(void)
{
	/* Enable PRC0/15/17/77 as inputs */
	SIU_PCR0 = 0x100;   /* PA0  (default pin muxing) */
    SIU_PCR15 = 0x100;  /* PA15 (default pin muxing) */
    SIU_PCR17 = 0x100;  /* PB1  (default pin muxing) */
    SIU_PCR77 = 0x100;  /* PE13 (default pin muxing) */

    /* Enable ISRs for ALL available buttons */
    EE_buttons_enable_interrupts(BUTTON_0);
    EE_buttons_enable_interrupts(BUTTON_1);
    EE_buttons_enable_interrupts(BUTTON_2);
    EE_buttons_enable_interrupts(BUTTON_3);
}

#endif

/* HW specific configuration */
__INLINE__ void __ALWAYS_INLINE__ InitHW(void)
{
    DisableWatchdog();
    ClearFails();
    InitSysclk();
}

__INLINE__ void __ALWAYS_INLINE__ InitSysclk(void)
{
    InitModesAndClks();
    InitPeriClkGen();
}

__INLINE__ void __ALWAYS_INLINE__ InitModesAndClks(void) 
{
    int32_t cnt = 0;
    
    ME.MER.R = 0x0000003D;        /* Enable DRUN, RUN0, RUN1 SAFE, RESET modes */
    
    /* Mode Transition to enter RUN1 mode: */    
    ME.RUN[1].R = 0x001F0030;       /* RUN1 cfg: 16MHzIRCON,OSC0ON,PLL0OFF,PLL1OFF,syclk=16MIRC */
    ME.MCTL.R = 0x50005AF0;         /* Enter RUN1 Mode & Key */        
    ME.MCTL.R = 0x5000A50F;         /* Enter RUN1 Mode & Inverted Key */
    while(0 == ME.GS.B.S_XOSC) {};               /* Wait for mode entry to complete */
    while(1 == ME.GS.B.S_MTRANS) {}    /* Wait for mode transition to complete */
    while(5 != ME.GS.B.S_CURRENT_MODE) {};       /* Check RUN1 mode has been entered */ 
    
    
    /* Initialize PLL before turning it on: */
    /* fsys = fcrystal*ndiv/idf/odf */
    /* fvco must be from 256 MHz to 512 MHz */
    /* we want fsys = 120 MHz. fvco = fsys*odf = 120 MHz * 4 = 480 MHz */
    /* fsys =  40*72/6/4 = 120 MHz */

    CGM.AC3SC.R = 0x01000000; /* Select Xosc as PLL0 source clock */
    CGM.AC4SC.R = 0x01000000; /* Select Xosc as PLL1 source clock */

    /* 120 MHz */
    CGM.FMPLL[0].CR.B.IDF = 0x5;    /* FMPLL0 IDF=5 --> divide by 6 */
    CGM.FMPLL[0].CR.B.ODF = 0x1;    /* FMPLL0 ODF=1 --> divide by 4*/
    CGM.FMPLL[0].CR.B.NDIV = 72;    /* FMPLL0 NDIV=72 --> divide by 72 */
    
    /* 80 MHz */
    CGM.FMPLL[1].CR.B.IDF = 0x7;    /* FMPLL0 IDF=5 --> divide by 8 */
    CGM.FMPLL[1].CR.B.ODF = 0x1;    /* FMPLL0 ODF=1 --> divide by 4*/
    CGM.FMPLL[1].CR.B.NDIV = 64;    /* FMPLL0 NDIV=72 --> divide by 64 */

    CGM.FMPLL[0].CR.B.EN_PLL_SW = 1; 	/* enable progressive clock switching */
    CGM.FMPLL[1].CR.B.EN_PLL_SW = 1; 	/* enable progressive clock switching */
    
    ME.RUNPC[0].R = 0x000000FE; /* enable peripherals run in all modes */
    ME.LPPC[0].R = 0x00000000;  /* disable peripherals run in LP modes */
    
    /* Mode Transition to enter RUN0 mode: */
    ME.RUN[0].R = 0x001F00F0;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,PLL1ON,syclk=16M IRC */
    ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
    ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */      
    while (1 == ME.GS.B.S_MTRANS) {}    /* Wait for mode transition to complete */
    while(4 != ME.GS.B.S_CURRENT_MODE) {};       /* Check RUN0 mode has been entered */ 
    
    /* Mode Transition to enter RUN1 mode: */    
    ME.RUN[1].R = 0x001F00F4;       /* RUN1 cfg: 16MHzIRCON,OSC0ON,PLL0ON,PLL1ON,syclk=PLL0 */
    ME.MCTL.R = 0x50005AF0;         /* Enter RUN1 Mode & Key */        
    ME.MCTL.R = 0x5000A50F;         /* Enter RUN1 Mode & Inverted Key */
    while(1 == ME.GS.B.S_MTRANS) {}    /* Wait for mode transition to complete */
    while(5 != ME.GS.B.S_CURRENT_MODE) {};       /* Check RUN1 mode has been entered */
    
    /* enable CLKOUT on PB6 */
    /* ALT1 - PCR[22] - PA = 0b01 */
    SIU.PCR[22].R = 0x0600;
    
    /* set CLKOUT divider of 8 */
    CGM.OCDS_SC.R = 0x32000000; /* div by 8, system FMPLL, cut2 */ 
    CGM.OCEN.B.EN = 1; 			/* enable CLKOUT signal */
}

__INLINE__ void __ALWAYS_INLINE__ InitPeriClkGen(void) 
{
    CGM.AC0SC.R = 0x04000000;  /* MPC56xxP: Select PLL0 for aux clk 0  */
    CGM.AC0DC.R = 0x80800000;  /* MPC56xxP: Enable aux clk 0 div by 1 */
    CGM.AC1SC.R = 0x04000000;  /* MPC56xxP: Select PLL0 for aux clk 1  */
    CGM.AC1DC.R = 0x80000000;  /* MPC56xxP: Enable aux clk 1 div by 1 */
    CGM.AC2SC.R = 0x04000000;  /* MPC56xxP: Select PLL0 for aux clk 2  */
    CGM.AC2DC.R = 0x80000000;  /* MPC56xxP: Enable aux clk 2 div by 1 */
}

__INLINE__ void __ALWAYS_INLINE__ DisableWatchdog(void) 
{
    SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
    SWT.SR.R = 0x0000d928; 
    SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
    
    /* e200 Core Watchdog Timer */
    asm
    {
        li  r3, 0
        mtspr   340, r3
    }
}

__INLINE__ void __ALWAYS_INLINE__ ClearNCF(void)
{
    uint32_t i,b[4];
    for(i=0;i<4;i++)
    {
        FCCU.NCFK.R = FCCU_NCFK_KEY;
        FCCU.NCF_S[i].R = 0xFFFFFFFF;
        while(FCCU.CTRL.B.OPS != 0x3)
        {
        
        };              /* wait for the completion of the operation */
        b[i]=FCCU.NCF_S[i].R;
    }
}

__INLINE__ void __ALWAYS_INLINE__ ClearCF(void)
{
    uint32_t i,a[4];
    for(i=0;i<4;i++)
    {
        FCCU.CFK.R = FCCU_CFK_KEY;
   
        FCCU.CF_S[i].R = 0xFFFFFFFF;
  
        while(FCCU.CTRL.B.OPS != 0x3)
        {
            
        };      /* wait for the completion of the operation */

        a[i]=FCCU.CF_S[i].R;
    }
}

__INLINE__ void __ALWAYS_INLINE__ ClearFails(void)
{
    uint16_t reset_register;
    
    if(RGM.FES.B.F_FCCU_SAFE || RGM.FES.B.F_FCCU_HARD)
    {
        reset_register = RGM.FES.R;
        ME.IMTS.R = 0x00000001;
        ClearCF();
        ClearNCF();
        
        RGM.FES.R = 0xFFFF;
        RGM.DES.R = 0xFFFF;
        
        /* re-enter DRUN */
        ME.MCTL.R = 0x30005AF0; /* Enter DRUN Mode & Key */        
        ME.MCTL.R = 0x3000A50F; /* Enter DRUN Mode & Inverted Key */
    }
}

#endif
