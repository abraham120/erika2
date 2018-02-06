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

/*
 * ERIKA Enterprise Basic - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2007  Evidence Srl
 *
 * This file is part of ERIKA Enterprise Basic.
 *
 * ERIKA Enterprise Basic is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * ERIKA Enterprise Basic is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise Basic; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 */

/*
 * Author: 2006 Paolo Gai
 * CVS: $Id: code.c,v 1.1 2008/01/17 18:22:29 pj Exp $
 */

#include "ee.h"
#include "cpu/pic30/inc/ee_irqstub.h"

// Primary (XT, HS, EC) Oscillator without PLL
_FOSCSEL(FNOSC_PRI);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							


volatile int xxx;

EE_UINT32 EE_terminate_data[1];

void pippo(void);
/* this is the real thread body that is called if the thread use the
   TerminateTask function */
const EE_ADDR EE_terminate_real_th_body[] = { (EE_ADDR)pippo };

void EE_pic30_terminate_savestk(EE_ADDR sp, EE_ADDR realbody);
void EE_pic30_terminate_task(EE_ADDR sp) NORETURN;


TASK(myTask)
{
  register EE_TID temp;

  temp = 0;

	EE_pic30_terminate_savestk(&EE_terminate_data[0],
			       (EE_ADDR)EE_terminate_real_th_body[0]);	
			       
}

void pippo(void)
{
	xxx++;		       
//    EE_pic30_terminate_task(&EE_terminate_data[0]);
}

int main(void)
{
 
	/* A task can be activated directly by using ActivateTask */
	ActivateTask(myTask);
  
	/* Forever loop: background activities (if any) should go here */
	for (;;);
  
	return 0;
}
