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

/* 
 * Differential-steering vehicle
 * -----------------------------
 *
 * Connecting robot with sensors and motors:  
 *
 *  - MotorA is connected to the right wheel;
 *  - MotorC is connected to the left wheel;
 *  - Light sensor on the front side (s1) is connected to port3;
 *  - Light sensor on the back side (s2) is connected to port2.
 *
 * Position of the robot on the track:
 *
 *  - Left wheel is in the dark side of the track 
 *  - Right wheel is in the light side of the track
 * (in this way theta angle will be positive when vehicle turns anti-orario)
 *
 * Setup:
 *  
 *  use the sensor on the front side (s1,port3) to setup these parameters:
 *  - ydark: put s1 on the darkest point of the track and press Run Button;
 *  - yref: put s1 on the point corresponding on the drive-line and press Run;
 *  - ylight: put s1 on the lightest point of the track and press Run;
 *  Now put the vehicle on the track and press Run Button to exit setup mode
 *  and the vehicle will start....
 *  
 *  Note that you can enter into setup mode everytime just pressing Run button.
 */

#include "code.h"

#define PERIODIC_THREAD_MAX 1

/* used by first_thread_activation() */
const EE_UINT16 th_period[PERIODIC_THREAD_MAX]={
  15 // 30 ms
  };

EE_UINT16 remaining_period[PERIODIC_THREAD_MAX];

/* Used for light noise reduction (0: very sensible, 1, .., 10: insensible) */
#define LIGHT_TOLERANCE 0
/* light sensors have different ranges so I use this offset */
#define OFFSET_ERR (20>>LIGHT_TOLERANCE)
/* application needs to setup sensor (see setup_handler) */
EE_UINT8 setup=0;


EE_DF_TYPE w, y, yscale, theta, alfa, beta, y1, y2, 
	      q, b, c, g1, g2, g3,g4, temp1, temp2, K1, K2, r;

EE_INT16   s1, s2, yref=0, yblack=0, ywhite=0;

EE_INT16   l_motor_pow, r_motor_pow, powref;


EE_UINT8 visualizza=1;


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


void wait(void)
{    
    while (!EE_button_pressed(VIEW_BUTTON));
    while (EE_button_pressed(VIEW_BUTTON));
}


void thread0(void)
{          
    int i;
    /* turn off light (bits 0-1 of port6) before A/D conversion */
    Port6 &= 0xFC;  
    for (i=0; i<20; i++);
    /* start A/D conversion */    
    if (power)
	EE_ad_start();     
} 


void thread1(void)         
{         
    
    if ((setup==4) && power)
    {

	EE_int2df(&y1,s1-yref); 
	EE_int2df(&y2,s2-yref); 

	/* now convert y1 and y2 in meters */
        EE_df_mul(&y1, &y1, &yscale);
	EE_df_mul(&y2, &y2, &yscale);

	y=y1;	
	
//      EE_df_add(&temp1, &y1, &y2);    
//      EE_int2df(&temp2, 2);
//      EE_df_div(&y, &temp1, &temp2);

	/* theta=(y1-y2)/q */
        EE_df_sub(&temp1, &y1, &y2);
        EE_df_div(&theta, &temp1, &q);

	/* c(t)=K1*y(t) + K2*theta(t) */
        EE_df_mul(&temp1, &K1, &y);
        EE_df_mul(&temp2, &K2, &theta);    
        EE_df_add(&c, &temp1, &temp2);

	/* Calculate new power */
	r_motor_pow=powref + EE_df2int(&c);
	l_motor_pow=powref - EE_df2int(&c);     
	
//	if (visualizza==1)
//	{
	
//	    EE_lcd_write_num(s1);

//	    EE_int2df(&temp1, 1000);
//	    EE_df_mul(&temp2, &y, &temp1);
//	    EE_lcd_write_num(EE_df2int(&temp2));

//	}
//	else
//	if (visualizza==2)
//	{
//	    EE_int2df(&temp1, 573);
//	    EE_int2df(&temp2, 10);	    
//	    EE_df_div(&temp2, &temp1, &temp2);	    
//	    EE_df_mul(&temp1, &theta, &temp2);
//	    EE_lcd_write_num(EE_df2int(&temp1));

//	    EE_lcd_write_num(s2);

//	    EE_int2df(&temp1, 1000);
//	    EE_df_mul(&temp2, &y2, &temp1);
//	    EE_lcd_write_num(EE_df2int(&temp2));

//	}	
	

	/* set motor A action */
        if (r_motor_pow>0)     
    	    EE_motorA_action(MotorGo0);
        else
	if (r_motor_pow<0)
	    EE_motorA_action(MotorGo1);	
	else
	    EE_motorA_action(MotorBrake);
	/* set motor A power */
	if (r_motor_pow<0)
	    r_motor_pow=-r_motor_pow;
	if (r_motor_pow < PWM_MIN_MOTOR_POWER)
	{
	    r_motor_pow=0;
	    EE_motorA_action(MotorBrake);;
	}
	else
	if (r_motor_pow > PWM_MAX_MOTOR_POWER)
	    r_motor_pow=PWM_MAX_MOTOR_POWER;	    
	    
	EE_motorA_power(r_motor_pow);	
	
	/* set motor C action */    
        if (l_motor_pow>0)     
    	    EE_motorC_action(MotorGo0);
        else
	if (l_motor_pow<0)
	    EE_motorC_action(MotorGo1);
	else
	    EE_motorC_action(MotorBrake);
	/* set motor C power */
	if (l_motor_pow<0)
	    l_motor_pow=-l_motor_pow;
	if (l_motor_pow < PWM_MIN_MOTOR_POWER)
	{
	    l_motor_pow=0;
	    EE_motorC_action(MotorBrake);
	}
	else
	if (l_motor_pow > PWM_MAX_MOTOR_POWER)
	    l_motor_pow=PWM_MAX_MOTOR_POWER;	
        EE_motorC_power(l_motor_pow);    	          
    }    

// display theta
//    EE_int2df(&temp1,573);
//    EE_df_mul(&temp1,&theta,&temp1);
//    EE_lcd_write_num(EE_df2int(&temp1));    
    
}


void ADI_handler (void)
{
    int i;
    EE_UINT16 a, b;
    EE_ad_stop();    

    a=(EE_ad_get_port3()>>(6+LIGHT_TOLERANCE))+OFFSET_ERR;	
    // NOTE: one sensor read OFFSET_ERR units less than other.
    //       suppose it is S1, so offset is summed to it
    b=(EE_ad_get_port2()>>(6+LIGHT_TOLERANCE)); 
    
    /* s1, s2 are integer, if a,b are unsigned so >> is logical */
    s1=a;   
    s2=b;
    
    /* when AD conversion ended, activate thread for control (if setup done)*/
    if (setup==4)
	EE_thread_activate(TID_thread1);
    
    /* turn on red light for sensor */
    Port6 |= ~0xFC;
    
    /* reset A/D end-conversion flag */
    EE_ad_reset_end_flag();
}


void setup_handler(void)
{
    
    if ((setup==0) || (setup==4))
    {

#ifdef __PLAY_NOTE_SUPPORT__		
      EE_play_note(_DO0,10);     
#endif
      
//	EE_motorA_action(MotorGo0);	
//	EE_motorC_action(MotorGo0);	
//	wait();
//	EE_motorA_action(MotorFloat);	
//	EE_motorC_action(MotorFloat);		
	setup=1;
	yblack=s1;	
	//
	EE_lcd_write_num(yblack);
	//
	
#ifdef __PLAY_NOTE_SUPPORT__
        EE_play_note(_DO0,20);
#endif	
    } 
    else
    if (setup==1)
    {   
	setup=2;
	yref=s1;

	// 
	EE_lcd_write_num(yref);		
	//
		
#ifdef __PLAY_NOTE_SUPPORT__
        EE_play_note(_RE0,6);	
#endif	
    }
    else
    if (setup==2)
    {
	
	setup=3;
	ywhite=s1;
	if (yblack > ywhite)
	  EE_int2df(&temp1, yblack-ywhite); 
	else
	  EE_int2df(&temp1, ywhite-yblack);

        EE_df_div(&yscale, &w, &temp1);
	
	//
	EE_lcd_write_num(ywhite);	
//	wait();
	EE_int2df(&temp1,10000);
	EE_df_mul(&temp1, &yscale, &temp1);
	EE_lcd_write_num(EE_df2int(&temp1));	
//	wait();	
	
#ifdef __PLAY_NOTE_SUPPORT__
        EE_play_note(_MI0,10);	
#endif	
    }
    else
    { 
	setup=4;		        
	EE_lcd_clear();
#ifdef __PLAY_BUFFER_SUPPORT__
	EE_play_buffer(kuka_buffer, kuka_buffer_len,PLAY_BACKGROUND);
#endif	
    }
}

/* call this macro for each handler you need to install */
EE_declare_stub(ONOFF_handler);
EE_declare_stub(setup_handler);
EE_declare_stub(ADI_handler);


void main(void)
{                 
    /* initialization */
    EE_init();     

    /* external interrupts generated once when you press the button (and not *
     * for all the time you are are pressing the button)                     */
    EE_button_irq_mode(ONOFF_EDGE_RUN_EDGE);

    /* 
     * init application data 
     */
    
    /* linear velox of wheels (m/s) */
//  EE_int2df(&temp1, 50);
//  EE_int2df(&temp2, 1);
//  EE_df_div(&vref, &temp1, &temp2); 	// vref=0.05 m/s


    // NOTE: linear velox (m/s) = 0.00121501 * pow; 
    //       where PWM_MIN_MOTOR_POWER < pow < PWM_MAX_MOTOR_POWER
    
    /* Center to center wheels distance (m) */
    EE_int2df(&temp1, 105);
    EE_int2df(&temp2, 1000);    
    EE_df_div(&b, &temp1, &temp2); 		// b=0.105 m 
    
    /* Sensor to sensor distance (m) */
    EE_int2df(&temp1, 134);
    EE_int2df(&temp2, 1000);        
    EE_df_div(&q, &temp1, &temp2);		// q=0.134 m
    
    /* Width of track (from dark side to white side) */
    EE_int2df(&temp1, 10);
    EE_int2df(&temp2, 100);
    EE_df_div(&w, &temp1, &temp2);		// w=0.1 m 
    
    /* radius of wheels */
//    EE_int2df(&temp1, 4);
//    EE_int2df(&temp2, 100);
//    EE_df_div(&r, &temp1, &temp2);		// r=0.0408 m 
    
    
    /* Gains for controller */
/*    EE_int2df(&temp1, -9);
    EE_int2df(&temp2, 10);            
    EE_df_div(&g1, &temp1, &temp2);		// g1=-0.9 
    EE_int2df(&temp1, -5);    
    EE_df_div(&g2, &temp1, &temp2);  	// g2=-0.5 
    EE_int2df(&temp1, -1);
    EE_df_div(&g3, &temp1, &temp2);  	// g3=-0.1
    EE_int2df(&temp1, -1);
    EE_df_div(&g4, &temp1, &temp2);  	// g4=-0.1
*/    
    /* Constants for c(t)=alfa*y+beta*theta */ 
    /* alfa= (b*g1)/(b-2*g4) */   
/*  
    EE_int2df(&temp2,2);
    EE_df_mul(&temp1,&temp2,&g4);
    EE_df_sub(&temp2, &b, &temp1);
    EE_df_mul(&temp1, &b, &g1);
    EE_df_div(&alfa, &temp1, &temp2);	
*/
    
    /* beta= b*(g2*vref+g3)/(b-2*g4) */
/*
    EE_df_mul(&temp1, &vref, &g2);
    EE_df_add(&temp1, &temp1, &g3);
    EE_df_mul(&temp1, &temp1, &b);
    EE_df_div(&beta, &temp1, &temp2);        
*/    

    /* Constants K1,K2 map linear velox of wheels with power of motor;
     * indirectly use g1,g2,g3,g4,r,b,vref;				*/
    /* K1 */

    EE_int2df(&K1, -3000 /*-3000*/ /*-1152*/);
    
    
    /* K2 */
    EE_int2df(&K2, -823 /*-2058*/);       		
    EE_int2df(&temp2, 10);    
    EE_df_div(&K2, &temp1, &temp2);	  // K2=-82.3 (0.05m/s); K2=--205.8 (0.15 m/s)


    /* select A/D channel and mode */
    EE_ad_select (AD_PORT32_SCAN_ACT_ACT);


    /* set motors power */
    powref=PWM_MAX_MOTOR_POWER-20;	// 41= 0.05 m/s;   82=0.1 m/s;  123=0.15 m/s
    
    /* 
     * install handlers 
     */
    EE_set_handler(ONOFFBUTTON_IRQ, ONOFF_handler);   
    EE_set_handler(RUNBUTTON_IRQ, setup_handler);
    EE_set_handler(ADI_IRQ, ADI_handler);
    
    /* 
     * enable external interrupt sources 
     */ 
    EE_enable_irq(ONOFFBUTTON_IRQ);  
    EE_enable_irq(RUNBUTTON_IRQ);        
    
    /* enable AD interrupt */
    EE_enable_irq(ADI_IRQ);
    
    thread_activation();
	              
#ifdef __PLAY_NOTE_SUPPORT__
    EE_play_note(_FA0, 40);
    EE_play_note(_LA0, 25);
#endif
//    visualizza=1; // 1= vedo la y, 2=vedo theta
    
            
    for (;;) {}
}
