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
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#include "initHW.h"

#define MODULE_ID   (15)

void InitHW(void)
{
    DisableWatchdog();
    ClearFails();
    InitSysclk();    
    InitGPIO();
}

void InitSysclk(void)
{
    InitModesAndClks();
    InitPeriClkGen();
}

void InitModesAndClks(void) 
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

#if 0
    /* 80 MHz */
    CGM.FMPLL[0].CR.B.IDF = 0x7;    /* FMPLL0 IDF=5 --> divide by 8 */
    CGM.FMPLL[0].CR.B.ODF = 0x1;    /* FMPLL0 ODF=1 --> divide by 4*/
    CGM.FMPLL[0].CR.B.NDIV = 64;    /* FMPLL0 NDIV=72 --> divide by 64 */
    
    /* 120 MHz */
    CGM.FMPLL[1].CR.B.IDF = 0x5;    /* FMPLL0 IDF=5 --> divide by 8 */
    CGM.FMPLL[1].CR.B.ODF = 0x1;    /* FMPLL0 ODF=1 --> divide by 4*/
    CGM.FMPLL[1].CR.B.NDIV = 72;    /* FMPLL0 NDIV=72 --> divide by 64 */
#else
    /* 120 MHz */
    CGM.FMPLL[0].CR.B.IDF = 0x5;    /* FMPLL0 IDF=5 --> divide by 6 */
    CGM.FMPLL[0].CR.B.ODF = 0x1;    /* FMPLL0 ODF=1 --> divide by 4*/
    CGM.FMPLL[0].CR.B.NDIV = 72;    /* FMPLL0 NDIV=72 --> divide by 72 */
    
    /* 80 MHz */
    CGM.FMPLL[1].CR.B.IDF = 0x7;    /* FMPLL0 IDF=5 --> divide by 8 */
    CGM.FMPLL[1].CR.B.ODF = 0x1;    /* FMPLL0 ODF=1 --> divide by 4*/
    CGM.FMPLL[1].CR.B.NDIV = 64;    /* FMPLL0 NDIV=72 --> divide by 64 */
#endif

    CGM.FMPLL[0].CR.B.EN_PLL_SW = 1; 	/* enable progressive clock switching */
    CGM.FMPLL[1].CR.B.EN_PLL_SW = 1; 	/* enable progressive clock switching */
    
    ME.RUNPC[0].R = 0x000000FE; /* enable peripherals run in all modes */
    ME.LPPC[0].R = 0x00000000;  /* disable peripherals run in LP modes */

#if 0    
    ME.RUN[0].R = 0x001F0032;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,syclk=OSC */
    
    /* Mode Transition to enter RUN0 mode: */
    ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
    ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
    while (ME.IS.B.I_MTC != 1) {}    /* Wait for mode transition to complete */
    ME.IS.R = 0x00000001;           /* Clear Transition flag */
#endif
    
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

void InitPeriClkGen(void) 
{
    CGM.AC0SC.R = 0x04000000;  /* MPC56xxP: Select PLL0 for aux clk 0  */
    CGM.AC0DC.R = 0x80800000;  /* MPC56xxP: Enable aux clk 0 div by 1 */
    CGM.AC1SC.R = 0x04000000;  /* MPC56xxP: Select PLL0 for aux clk 1  */
    CGM.AC1DC.R = 0x80000000;  /* MPC56xxP: Enable aux clk 1 div by 1 */
    CGM.AC2SC.R = 0x04000000;  /* MPC56xxP: Select PLL0 for aux clk 2  */
    CGM.AC2DC.R = 0x80000000;  /* MPC56xxP: Enable aux clk 2 div by 1 */
}

void DisableWatchdog(void) 
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


void TestPWMOutput(void)
{
	SIU.PCR[58].R = 0x200; // GPIO-D[10] pin as FlexPWM A[0] output PWMA 0 UP
	/* Added for PWMA 1 UP and PWMA 2 UP */
	SIU.PCR[47].R = 0x200; // GPIO-PWM A[1] C[15]
	SIU.PCR[99].R = 0x200; // GPIO-PWM A[2] G[3]
	/* Added for PWM0 DW, PWMA 1 DW and PWMA 2 DW */
	SIU.PCR[59].R = 0x200; // GPIO-PWM B[0] D[11]
	SIU.PCR[48].R = 0x200; // GPIO-PWM B[1] D[0]
	SIU.PCR[100].R = 0x200; // GPIO-PWM B[2] G[4]

}
void InitGPIO(void)
{
	/* Init pin for ADC from Trimmer */
	SIU.PCR[23].R = 0x2000; // Pin connected to the potentiometer

	/* Init the remaining pins */
	SIU.PCR[46].R = 0x0A04; // C[14] pin as CTU0 EXT TRG output
	SIU.PCR[52].R = 0x0204; // D[4] pin as GPIO output (led)
	SIU.PCR[58].R = 0x0600; // D[10] pin as FlexPWM A[0] output PWMA 0 UP

	/* Added for PWMA 1 UP and PWMA 2 UP */
	SIU.PCR[47].R = 0xE00; // PWM A[1] C[15]
	SIU.PCR[99].R = 0x600; // PWM A[2] G[3]

	/* Added for PWM0 DW, PWMA 1 DW and PWMA 2 DW */
	SIU.PCR[59].R = 0x0600; // PWM B[0] D[11]
	SIU.PCR[48].R = 0xE00; // PWM B[1] D[0]
	SIU.PCR[100].R = 0x600; // PWM B[2] G[4]
	
		
	/* Added to support ADC-CH1 and ADC-CH2 */
	SIU.PCR[24].R = 0x2000; /* B[8] */
	SIU.PCR[33].R = 0x2000; /* C[1] */

	SIU.PCR[34].R = 0x2000;/* C[2] */
	SIU.PCR[70].R = 0x2000;/* E[6] */
	SIU.PCR[66].R = 0x2000;/* E[2] */
	SIU.PCR[71].R = 0x2000;/* E[7] */
	SIU.PCR[68].R = 0x2000;/* E[4] */

	SIU.PCR[52].B.OBE = 0x01;
	SIU.PCR[53].B.OBE = 0x01;
	SIU.PCR[54].B.OBE = 0x01;
	SIU.PCR[55].B.OBE = 0x01;

	/* Init GPIO for leds */
	SIU.GPDO[52].R = 1; //D[5] - LED1
	SIU.GPDO[53].R = 1; //D[5] - LED2
	SIU.GPDO[54].R = 1; //D[6] - LED3
	SIU.GPDO[55].R = 1; //D[7] - LED4

    // DSPI_0
    SIU.PCR[39].R = 0x0103;        /* MPC56xxB: Config pad as DSPI_0 SIN input */
    SIU.PCR[38].R = 0x0604;        /* MPC56xxB: Config pad as DSPI_0 SOUT output */
    SIU.PCR[37].R = 0x0604;        /* MPC56xxB: Config pad as DSPI_0 SCK output */
    SIU.PCR[36].R = 0x0604;        /* MPC56xxB: Config pad as DSPI_0 PCS0 output */

    // DSPI_1
    SIU.PCR[8].R = 0x0103;        /* MPC56xxB: Config pad as DSPI_1 SIN input */
    SIU.PCR[7].R = 0x0604;        /* MPC56xxB: Config pad as DSPI_1 SOUT output */
    SIU.PCR[6].R = 0x0103;        /* MPC56xxB: Config pad as DSPI_1 SCK intput */
    SIU.PCR[5].R = 0x0103;        /* MPC56xxB: Config pad as DSPI_1 PCS0 intput */
}

static void ClearNCF(void)
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

static void ClearCF(void)
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

void ClearFails(void)
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
