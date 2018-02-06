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

#include <ee.h>
#include "adc.h"
#include "pwm.h"
#include "ctu.h"
#include "initHW.h"
#include "CanDrv.h"
#include "CanCom.h"
#include "FasterLoop.h"
#include "Ccp.h"
#include "WdDrv.h"

DeclareTask(Task_5msec);
DeclareTask(Task_20msec);

/*
 * Do not init the following variable from here since boot code does not
 * manage (does not init) this memory area. This variable is forced in this
 * location to prevent compiler moving it (This address is used by CCP,
 * since It expects variable located in this position). The variable is 
 * populated in "Task_5msec"
 */
#pragma push
#pragma section data_type ".abs.40000010" ".abs.40000010" data_mode=far_abs
/* Read from ADC */
__declspec (force_export) __declspec (section ".abs.40000010") uint16 ccp_test0;
#pragma pop
extern uint32 FinalResult;

/* Task running at 5 msec */
TASK(Task_5msec)
{
	static int cnt = 0;

    // Update ccp_test0 with data read from the ADC
    ccp_test0 = FinalResult;

	// Blink led at 1 sec
	if (cnt == 200) {
        SIU.GPDO[54].R ^= 1;
        cnt = 0;
    }
    cnt++;

	// CCP main body task
	CcpTask();

    // Servive WatchDog (To prevent from reset system)
    ServiceWatchdog();

    TerminateTask();
}

void main(void) 
{
    InitHW();
    InitFlexPWM0_AB();
    InitCTU();

    // Initialize Drivers
    InitADC();
    CanDrvInit();

    // Init WatcDog
    InitWatchdog();

    // Enable WatchDog
    EnableWatchdog();

    // Initialize Bsw modules
    CanComInit();

    /* Start with multitasking environment */
    StartOS(OSDEFAULTAPPMODE);
}

