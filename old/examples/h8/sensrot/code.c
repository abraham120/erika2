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

/* Sensrot test: 
 * connect a motor to port A;
 * connect rotation sensor to port 3;
 * connect motor axe to rotation sensor.
 * Rotation sensor will misur motor velox which is displayed on LCD
 * OnOff Button turn on/off RCX.
 * Note that when RCX is turned off Run button has no effect
 * while when RCX is on pressing Run button causes a beep 
 */

#include "code.h"

const EE_UINT16 th_period[PERIODIC_THREAD_MAX]={
  5,   // =10 ms (2ms per cycle)
  4000 // 8s
  };

EE_UINT16 remaining_period[PERIODIC_THREAD_MAX];

void wait(void)
{    
    while (!EE_button_pressed(VIEW_BUTTON));
    while (EE_button_pressed(VIEW_BUTTON));
}

EE_UINT16 s2, s1;

EE_UINT16 round=0, prec_round=0;

EE_UINT8 mot_pow;

/* ************************
 *     periodic threads 
 * ************************/


void thread0(void)
{              
    Port6 &= 0xFC;  /* port3 e port2 uses bit 0 and bit 6 of port6 */
    
    EE_ad_start();    
} 


void thread1(void)
{         
    mot_pow +=30;
    round=0;    
    if (mot_pow>PWM_MAX_MOTOR_POWER)    
    {
	mot_pow=PWM_MIN_MOTOR_POWER;
	prec_round=0;
	EE_lcd_clear();    		
    }	
    EE_motorA_power(mot_pow);
    
    EE_play_note(_DO0,100);    
}


/* ************************
 * aperiodic threads
 * ************************/

void thread2(void)
{ 
    if (round>=prec_round)
    {
	prec_round=round;
	EE_lcd_write_num(prec_round<<2);    	
    }
        
    round=0;
}

void ADI_handler (void)
{
    int i;
    static EE_UINT16 ref_pos=0, pos, prec_pos, num=0, first=1, num_tick=0,conv=0;

    EE_ad_stop();    

    s1=(EE_ad_get_port3()>>12);
        
    if (!first)
    {    
	/* first time it returns always 5 so we ignore first read */

	if (ref_pos==0)
	{	
	    ref_pos=s1;	// referemet position (every 4 time it appears => 1 round done)
	    pos=s1;	// initial position
	    prec_pos=s1; 
	}
	else
	{
	    prec_pos=pos;
	    pos=s1;	
    
	    if (pos!=prec_pos)
	    {
		num_tick++;		    
		
		if (pos==ref_pos)
		{
		    num++;		// num=0..4
		    if (num==4)
		    {
			num=0;
			round++;
		    }
		    
		}
		
	    }
	
	    conv++;    	
	    /* when 150 AD conversions ended, activate thread 2 */
	    if (conv==150)
	    {
		EE_thread_activate(TID_thread2);
		num_tick=0;
		conv=0;    
		ref_pos=0;		
		first=1;	
	    }
	}
	    
    }
    else
    {
	first=0;
    }
	
    Port6 |= ~0xFC;
    
    EE_ad_reset_end_flag();
}




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

/* call this macro for each handler you need to install */
EE_declare_stub(ONOFFBUTTON_handler);
EE_declare_stub(RUNBUTTON_handler);
EE_declare_stub(ADI_handler);



void main(void)
{                 
    /* initialization */
    EE_init();     

    /* external interrupts on falling edge */
    EE_button_irq_mode(ONOFF_EDGE_RUN_EDGE);

    /* select mode for A/D converter */
    EE_ad_select(AD_PORT3_SCAN_ACT);        

    /* select motor action and power */
    mot_pow=PWM_MIN_MOTOR_POWER; 
    EE_motorA_action(MotorGo0);
    EE_motorA_power(mot_pow);

    /* install handlers */
    EE_set_handler(ONOFFBUTTON_IRQ, ONOFFBUTTON_handler);   
    EE_set_handler(RUNBUTTON_IRQ, RUNBUTTON_handler);
    EE_set_handler(ADI_IRQ, ADI_handler);
    
    /* enable external interrupt sources */ 
    EE_enable_irq(ONOFFBUTTON_IRQ);  
    EE_enable_irq(RUNBUTTON_IRQ);        
    
    /* enable AD interrupt */
    EE_enable_irq(ADI_IRQ);
        
    /* Activate threads and call scheduler */
    thread_activation(); 	         
        
    for (;;) {}
}
