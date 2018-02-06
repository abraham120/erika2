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

#include "pwm.h"
#include "BswCommon.h"

#define MODULE_ID   (4)

uint16 u16sectorTest = 0;
void PWMOutputLow (void)
{

	SIU.GPDO58.B.PDO = 0;
	SIU.GPDO47.B.PDO  = 0;
	SIU.GPDO99.B.PDO  = 0;
	SIU.GPDO59.B.PDO  = 0;
	SIU.GPDO48.B.PDO  = 0;
	SIU.GPDO100.B.PDO  = 0;

}
void TestPWMOutputDrive(void)
{
	switch (u16sectorTest){
	case 0:
		SIU.GPDO58.B.PDO = 0;
		SIU.GPDO47.B.PDO  = 0;
		SIU.GPDO99.B.PDO  = 0;
		SIU.GPDO59.B.PDO  = 0;
		SIU.GPDO48.B.PDO  = 0;
		SIU.GPDO100.B.PDO  = 0;
	break;
	case 1:
		SIU.GPDO58.B.PDO = 1;
		SIU.GPDO47.B.PDO  = 0;
		SIU.GPDO99.B.PDO  = 0;
		SIU.GPDO59.B.PDO  = 0;
		SIU.GPDO48.B.PDO  = 1;
		SIU.GPDO100.B.PDO  = 1;
	break;
	case 2:
		SIU.GPDO58.B.PDO = 0;
		SIU.GPDO47.B.PDO  = 1;
		SIU.GPDO99.B.PDO  = 0;
		SIU.GPDO59.B.PDO  = 1;
		SIU.GPDO48.B.PDO  = 0;
		SIU.GPDO100.B.PDO  = 1;
	break;
	case 3:
		SIU.GPDO58.B.PDO = 0;
		SIU.GPDO47.B.PDO  = 0;
		SIU.GPDO99.B.PDO  = 1;
		SIU.GPDO59.B.PDO  = 1;
		SIU.GPDO48.B.PDO  = 1;
		SIU.GPDO100.B.PDO  = 0;
		break;
	case 4:
		SIU.GPDO58.B.PDO = 0;
		SIU.GPDO47.B.PDO  = 1;
		SIU.GPDO99.B.PDO  = 1;
		SIU.GPDO59.B.PDO  = 1;
		SIU.GPDO48.B.PDO  = 0;
		SIU.GPDO100.B.PDO  = 0;
	break;
	case 8:
				SIU.GPDO58.B.PDO = 1;
				SIU.GPDO47.B.PDO  = 0;
				SIU.GPDO99.B.PDO  = 0;
				SIU.GPDO59.B.PDO  = 1;
				SIU.GPDO48.B.PDO  = 0;
				SIU.GPDO100.B.PDO  = 0;
	break;
	case 9:
				SIU.GPDO58.B.PDO = 0;
				SIU.GPDO47.B.PDO  = 1;
				SIU.GPDO99.B.PDO  = 0;
				SIU.GPDO59.B.PDO  = 0;
				SIU.GPDO48.B.PDO  = 1;
				SIU.GPDO100.B.PDO  = 0;
			break;
	case 10:
				SIU.GPDO58.B.PDO = 0;
				SIU.GPDO47.B.PDO  = 0;
				SIU.GPDO99.B.PDO  = 1;
				SIU.GPDO59.B.PDO  = 0;
				SIU.GPDO48.B.PDO  = 0;
				SIU.GPDO100.B.PDO  = 1;
			break;
	case 11:
		SIU.GPDO58.B.PDO = 1;
		SIU.GPDO47.B.PDO  = 1;
		SIU.GPDO99.B.PDO  = 1;
		SIU.GPDO59.B.PDO  = 1;
		SIU.GPDO48.B.PDO  = 1;
		SIU.GPDO100.B.PDO  = 1;
	default:
	break;	
	}	
}


static void InitPWM0_A0(void)
{
	FLEXPWM_0.SUB[0].CTRL.R     = 0x0400;	// full cycle reload, every opportunity,IPBus/1, double switching enable
	FLEXPWM_0.SUB[0].CTRL2.R    = 0x2000;
	FLEXPWM_0.SUB[0].DTCNT0.R   = 0x003c;	// deadtime values
	FLEXPWM_0.SUB[0].DTCNT1.R   = 0x003c;
	FLEXPWM_0.SUB[0].VAL[1].R   = PWM_MODULO;	// PWM modulo

	FLEXPWM_0.SUB[0].VAL[2].R   = (unsigned short)PWMA_RISING_EDGE;	// PWM A0 rising edge at t=0 (Edge-Aligned PWM Startegy)
	FLEXPWM_0.SUB[0].VAL[3].R   = PWMA_FALLING_EDGE;	// PWM A0 falling edge

	FLEXPWM_0.SUB[0].DISMAP.R   = 0x0000;
}
static void InitPWM0_A0B0(void)
{
	FLEXPWM_0.SUB[0].CTRL.R     = 0x0400;	// full cycle reload, every opportunity,IPBus/1, double switching enable
	FLEXPWM_0.SUB[0].CTRL2.R    = 0x0000;	//complementary configuration
	FLEXPWM_0.SUB[0].DTCNT0.R   = 0x003c;	// deadtime values 0x0f0 = 60d time= 240*IPTime= 240/120MHz=2us
	FLEXPWM_0.SUB[0].DTCNT1.R   = 0x003c;
	FLEXPWM_0.SUB[0].VAL[1].R   = PWM_MODULO;	// PWM modulo

	FLEXPWM_0.SUB[0].VAL[2].R   = (unsigned short)PWMA_RISING_EDGE;	// PWM A0 rising edge at t=0 (Edge-Aligned PWM Startegy)
	FLEXPWM_0.SUB[0].VAL[3].R   = PWMA_FALLING_EDGE;	// PWM A0 falling edge

	FLEXPWM_0.SUB[0].DISMAP.R   = 0x0000;
}
static void InitPWM0_A1(void)
{
	FLEXPWM_0.SUB[1].CTRL.R     = 0x0400;	// full cycle reload, every opportunity,IPBus/1, double switching enable
	FLEXPWM_0.SUB[1].CTRL2.R    = 0x2000;
	FLEXPWM_0.SUB[1].DTCNT0.R   = 0x003c;	// deadtime values
	FLEXPWM_0.SUB[1].DTCNT1.R   = 0x003c;
	FLEXPWM_0.SUB[1].VAL[1].R   = PWM_MODULO;	// PWM modulo

	FLEXPWM_0.SUB[1].VAL[2].R   = (unsigned short)PWMA_RISING_EDGE;	// PWM A1 rising edge at t=0 (Edge-Aligned PWM Startegy)
	FLEXPWM_0.SUB[1].VAL[3].R   = PWMA_FALLING_EDGE;	// PWM A1 falling edge

	FLEXPWM_0.SUB[1].DISMAP.R   = 0x0000;
}
static void InitPWM0_A1B1(void)
{
	FLEXPWM_0.SUB[1].CTRL.R     = 0x0400;	// full cycle reload, every opportunity,IPBus/1, double switching enable
	FLEXPWM_0.SUB[1].CTRL2.R    = 0x0000;	//complementary configuration
	FLEXPWM_0.SUB[1].DTCNT0.R   = 0x003c;	// deadtime values 0x0f0 = 240d time= 240*IPTime= 240/120MHz=2us
	FLEXPWM_0.SUB[1].DTCNT1.R   = 0x003c;
	FLEXPWM_0.SUB[1].VAL[1].R   = PWM_MODULO;	// PWM modulo

	FLEXPWM_0.SUB[1].VAL[2].R   = (unsigned short)PWMA_RISING_EDGE;	// PWM A1 rising edge at t=0 (Edge-Aligned PWM Startegy)
	FLEXPWM_0.SUB[1].VAL[3].R   = PWMA_FALLING_EDGE;	// PWM A1 falling edge

	FLEXPWM_0.SUB[1].DISMAP.R   = 0x0000;
}

static void InitPWM0_A2(void)
{
	FLEXPWM_0.SUB[2].CTRL.R     = 0x0400;	// full cycle reload, every opportunity,IPBus/1, double switching enable
	FLEXPWM_0.SUB[2].CTRL2.R    = 0x2000;
	FLEXPWM_0.SUB[2].DTCNT0.R   = 0x003c;	// deadtime values
	FLEXPWM_0.SUB[2].DTCNT1.R   = 0x003c;
	FLEXPWM_0.SUB[2].VAL[1].R   = PWM_MODULO;	// PWM modulo

	FLEXPWM_0.SUB[2].VAL[2].R   = (unsigned short)PWMA_RISING_EDGE;	// PWM A1 rising edge at t=0 (Edge-Aligned PWM Startegy)
	FLEXPWM_0.SUB[2].VAL[3].R   = PWMA_FALLING_EDGE;	// PWM A1 falling edge

	FLEXPWM_0.SUB[2].DISMAP.R   = 0x0000;
}

static void InitPWM0_A2B2(void)
{
	FLEXPWM_0.SUB[2].CTRL.R     = 0x0400;	// full cycle reload, every opportunity,IPBus/1, double switching enable
	FLEXPWM_0.SUB[2].CTRL2.R    = 0x0000;	//complementary configuration
	FLEXPWM_0.SUB[2].DTCNT0.R   = 0x003c;	// deadtime values 0x0f0 = 240d time= 240*IPTime= 240/120MHz=2us
	FLEXPWM_0.SUB[2].DTCNT1.R   = 0x003c;
	FLEXPWM_0.SUB[2].VAL[1].R   = PWM_MODULO;	// PWM modulo

	FLEXPWM_0.SUB[2].VAL[2].R   = (unsigned short)PWMA_RISING_EDGE;	// PWM A1 rising edge at t=0 (Edge-Aligned PWM Startegy)
	FLEXPWM_0.SUB[2].VAL[3].R   = PWMA_FALLING_EDGE;	// PWM A1 falling edge

	FLEXPWM_0.SUB[2].DISMAP.R   = 0x0000;
}


void PWM0_A0_load_new_rising_edge(unsigned int val)
{
	FLEXPWM_0.SUB[0].VAL[2].R = (unsigned short)val;
}

void PWM0_A0_load_new_falling_edge(unsigned int val)
{
	FLEXPWM_0.SUB[0].VAL[3].R = (unsigned short)val;
}

void PWM0_A1_load_new_rising_edge(unsigned int val)
{
	FLEXPWM_0.SUB[1].VAL[2].R = (unsigned short)val;
}

void PWM0_A1_load_new_falling_edge(unsigned int val)
{
	FLEXPWM_0.SUB[1].VAL[3].R = (unsigned short)val;
}

void PWM0_A2_load_new_rising_edge(unsigned int val)
{
	FLEXPWM_0.SUB[2].VAL[2].R = (unsigned short)val;
}

void PWM0_A2_load_new_falling_edge(unsigned int val)
{
	FLEXPWM_0.SUB[2].VAL[3].R = (unsigned short)val;
}

void InitFlexPWM0(void)
{
	/* Submodule 0 Initialisation */
	FLEXPWM_0.OUTEN.R           = PWM0_A0_ENABLE | PWM0_A1_ENABLE | PWM0_A2_ENABLE;	// enable A outputs on submodule 0

	FLEXPWM_0.SUB[0].TCTRL.R    = 0x0002;	// VAL0 reg determines OUT_TRIG0 generation (Edge-Aligned PWM Startegy)

	FLEXPWM_0.INIT0.R   = (unsigned short)PWM_INIT;
	FLEXPWM_0.INIT1.R   = (unsigned short)PWM_INIT;
	FLEXPWM_0.INIT2.R   = (unsigned short)PWM_INIT;

	InitPWM0_A0();
	InitPWM0_A1();
	InitPWM0_A2();

	FLEXPWM_0.MCTRL.R = PWM0_A0_ENABLE | PWM0_A1_ENABLE | PWM0_A2_ENABLE;		// Submodule 0 PWM generator enabled
	FLEXPWM_0.MCTRL.B.LDOK = PWM0_A0_LOAD | PWM0_A1_LOAD | PWM0_A2_LOAD;	/* Load the PRSC bits of CTRL1 and the INIT, and VALx registers 
    								   into a set of buffers */
}

void InitFlexPWM0_AB(void)
{
	/* Submodule 0 Initialisation */
	FLEXPWM_0.OUTEN.R           = PWM0_A0_ENABLE | PWM0_A1_ENABLE | PWM0_A2_ENABLE | PWM0_B0_ENABLE | PWM0_B1_ENABLE | PWM0_B2_ENABLE;	// enable A and B outputs on submodule 0

	FLEXPWM_0.SUB[0].TCTRL.R    = 0x0002;	// VAL0 reg determines OUT_TRIG0 generation (Edge-Aligned PWM Startegy)

	FLEXPWM_0.INIT0.R   = (unsigned short)PWM_INIT;
	FLEXPWM_0.INIT1.R   = (unsigned short)PWM_INIT;
	FLEXPWM_0.INIT2.R   = (unsigned short)PWM_INIT;

	InitPWM0_A0B0();
	InitPWM0_A1B1();
	InitPWM0_A2B2();

	FLEXPWM_0.MCTRL.R = PWM0_A0_ENABLE | PWM0_A1_ENABLE | PWM0_A2_ENABLE;		// Submodule 0 PWM generator enabled
	FLEXPWM_0.MCTRL.B.LDOK = PWM0_A0_LOAD | PWM0_A1_LOAD | PWM0_A2_LOAD;	/* Load the PRSC bits of CTRL1 and the INIT, and VALx registers 
    								   into a set of buffers */
			
}
void OffPWM (void)
{
	FLEXPWM_0.OUTEN.R           = FLEXPWM_0.OUTEN.R&0x0f;	// enable A and B outputs on submodule 0

}

void OnPWM (void)
{
	FLEXPWM_0.OUTEN.R           = PWM0_A0_ENABLE | PWM0_A1_ENABLE | PWM0_A2_ENABLE | PWM0_B0_ENABLE | PWM0_B1_ENABLE | PWM0_B2_ENABLE;	// enable A and B outputs on submodule 0

}
