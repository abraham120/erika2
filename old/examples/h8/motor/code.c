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
 * Author: 2002 Davide Cantini
 * CVS: $Id: code.c,v 1.4 2006/01/05 14:38:25 pj Exp $
 */


/* Motor test:
 * it shows increasing power for motorA (with VP control)
 * and motorC (with PWM control).
 * Display shows motorA power.
 * Hint: modify code just to switch motorA power and motorB
 *       power by pressing a button.
 */
  
#include "code.h"

#define PERIODIC_THREAD_MAX 1

/* used by first_thread_activation() */
const EE_UINT16 th_period[PERIODIC_THREAD_MAX]={
  4000 // 8000 ms
  };

EE_UINT16 remaining_period[PERIODIC_THREAD_MAX];

 
EE_UINT8 mA_pow, mC_pow;

void wait(void)
{    
    while (!EE_button_pressed(VIEW_BUTTON));
    while (EE_button_pressed(VIEW_BUTTON));
}

void thread0(void)
{          
    EE_play_note(_DO0, 10);

    EE_motorA_power(mA_pow);
    EE_motorC_power(mC_pow);    	
        
    EE_lcd_write_num(mA_pow);

    mA_pow += 1;
    mC_pow += 1;
    
    if (mA_pow>VP_MAX_MOTOR_POWER)
	mA_pow=VP_MIN_MOTOR_POWER;

//    if (mC_pow>PWM_MAX_MOTOR_POWER)
//	mC_pow=PWM_MIN_MOTOR_POWER;
    if (mC_pow>VP_MAX_MOTOR_POWER)
	mC_pow=VP_MIN_MOTOR_POWER;	
} 

void thread1(void)         
{                     
    EE_motorA_action(MotorGo0);
    EE_motorC_action(MotorGo1);        
}


/* call this macro for each handler you need to install */
EE_declare_stub(ONOFF_handler);

void EE_timerB_user_function(void)
{
  EE_UINT8 i;

	for (i=0; i<PERIODIC_THREAD_MAX; i++)
    	{
	    remaining_period[i]--;	/* periods of threads are multiple of timer period */	
 
	    if (remaining_period[i]==0)
	    {				
		remaining_period[i]=th_period[i];
	    		
		EE_thread_activate(i);   // N.B. this function is called into an IRQ!!!! 
	    }	 
	}
}

void thread_activation(void)
{
    EE_UINT8 i;

    /* used by first_thread_activation() */
  
    for (i=0; i<PERIODIC_THREAD_MAX; i++)
	remaining_period[i]=th_period[i];

    for (i=0; i<THREAD_MAX; i++)	
	EE_thread_activate(i);      
 
   /* call scheduler (Note: after this call, I=0 (Interrupt On) */    
    EE_sys_scheduler();        
}

void main(void)
{                 
    /* initialization */
    EE_init();     

    /* external interrupts generated once when you press the button (and not *
     * for all the time you are are pressing the button)                     */
    EE_button_irq_mode(ONOFF_EDGE_RUN_EDGE);

    /* set velox of motors */
    mA_pow=VP_MIN_MOTOR_POWER;    
//    mC_pow=PWM_MIN_MOTOR_POWER;        
    mC_pow=VP_MIN_MOTOR_POWER;        

    /* set handler */
    EE_set_handler(ONOFFBUTTON_IRQ, ONOFF_handler);   
    
    /* enable external interrupt sources */
    EE_enable_irq(ONOFFBUTTON_IRQ);  
        
    /* activate threads and call scheduler */
    thread_activation(); 
	                          
    for (;;)
    {     	    
        while (!EE_button_pressed(PRGM_BUTTON));	    
        delete_firmware();	
    }    
}
