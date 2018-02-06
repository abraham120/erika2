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
 * CVS: $Id: ee_inline_d.h,v 1.2 2006/04/08 21:07:06 pj Exp $
 */

#include "h8/drivers.h"

/***********************
 * interrupt functions
 ***********************/

__INLINE__ void __ALWAYS_INLINE__ EE_interrupt_on(void)
{
   EE_hal_enableIRQ(); 
}

__INLINE__ void __ALWAYS_INLINE__ EE_interrupt_off(void)
{
   EE_hal_disableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_enable_irq(EE_TYPEIRQ irq)
{   
  (* (volatile EE_UINT8 *) (irq | 0xFF00)) |=  (1 << ((irq >>8) & 0x0007));
}

__INLINE__ void __ALWAYS_INLINE__ EE_disable_irq(EE_TYPEIRQ irq)
{ 
  (* (volatile EE_UINT8 *) (irq | 0xFF00)) &=  ~(1 << ((irq >>8) & 0x0007));
}


/********************
 * button functions
 ********************/

__INLINE__ void __ALWAYS_INLINE__ EE_button_irq_mode(EE_UINT8 mode)
{ 
   ISCR = mode; 
}


/***************************
 * A/D converter functions
 ***************************/
__INLINE__ void __ALWAYS_INLINE__ EE_ad_init(void)
{
    Port6DdrShadow |=0x07;
    Port6Ddr = Port6DdrShadow;
    ADCSR &= 0x00;
    ADCR   = 0x7F;    
}

__INLINE__ void __ALWAYS_INLINE__ EE_ad_select(EE_UINT8 c)    
{
    ADCSR &= 0xC0;
    ADCSR |= (c & 0x1F);
    /* bit 2,1,0 of port6(h8/3292) set to 1 if sensor (of port 1,2,3) is active, 0 if passive */
    Port6DdrShadow |= (c>>5);
    Port6Ddr=Port6DdrShadow;    	    
    Port6 &= 0xF8;
    Port6 |= (c>>5);
}

__INLINE__ void __ALWAYS_INLINE__ EE_ad_start(void)
{
   ADCSR |= 0x20;
}

__INLINE__ void __ALWAYS_INLINE__ EE_ad_start_fast(void)
{
   ADCSR |= 0x28;
}
__INLINE__ void __ALWAYS_INLINE__ EE_ad_stop(void)
{
   ADCSR &= ~0x20;
}
__INLINE__ void __ALWAYS_INLINE__ EE_ad_reset_end_flag(void)
{
   ADCSR &= 0x7F;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_ad_get_port1(void)
{
   return ADADDRC;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_ad_get_port2(void)
{
   return ADADDRB;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_ad_get_port3(void)
{
   return ADADDRA;
}


/***********************
 * I/O ports functions
 ***********************/

__INLINE__ void __ALWAYS_INLINE__ EE_ports_init (void)
{
  /* reset data direction (shadow) registers */
    Port1Ddr=Port1DdrShadow=0xFF;  /* output (address bus) */
    Port2Ddr=Port2DdrShadow=0xFF;  /* output (address bus) */
    Port3Ddr=Port3DdrShadow; 
    Port4Ddr=Port4DdrShadow;
    Port5Ddr=Port5DdrShadow=0x06;
    Port6Ddr=Port6DdrShadow;
}


/**************************
 * 16 bit timer functions
 **************************/

__INLINE__ void __ALWAYS_INLINE__ EE_t16_init(void)
{
   T16TCR   = 0x02;     // set clock to f/32 (f=16Mhz)
   T16TIER  = 0x01;     // disable all interrupt source   
   T16TOCR  = 0xE0;	// disable output compare 
   T16TCSR  &=0x00;	// reset flag int. and disable match 
    /* NOTE: to write TCSR register, MUST read it before.(see hitachi manual) */   
}

__INLINE__ void __ALWAYS_INLINE__ EE_t16_set_frc(EE_UINT16 value)
{
   T16FRC =value;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_t16_get_frc()
{
   return T16FRC;
}

__INLINE__ void __ALWAYS_INLINE__ EE_t16_reset_frc_ovf(void)
{
   T16TCSR &= 0xFD;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_t16_get_ocra(void)
{
  T16TOCR &=0xEF;   // select OCRA
  return T16OCRA;
}

__INLINE__ void __ALWAYS_INLINE__ EE_t16_set_ocra(EE_UINT16 value)
{
  T16TOCR &=0xEF;   // select OCRA
  T16OCRA = value;
}

__INLINE__ void __ALWAYS_INLINE__ EE_t16_reset_ocra_match_flag(void)
{
   T16TCSR &=0xF7;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_t16_get_ocrb(void)
{
  T16TOCR |=0xF0;   // select OCRB
  return T16OCRB;
}

__INLINE__ void __ALWAYS_INLINE__ EE_t16_set_ocrb(EE_UINT16 value)
{
  T16TOCR |=0xF0;   // select OCRB
  T16OCRB = value;
}

__INLINE__ void __ALWAYS_INLINE__ EE_t16_reset_ocrb_match_flag(void)
{
   T16TCSR &=0xFB;
}


/**************************
 * 8 bit timers functions
 **************************/

#ifdef __T80_SUPPORT__

    __INLINE__ void __ALWAYS_INLINE__ EE_t80_init(void)
    {
	/* stop timer */
	T80TCR   =0x00; 
	/* reset counter */
	T80TCNT  =0;    
	/* clear previous match; matchA=>output=1; matchB=>output=0; */	
	T80TCSR  =0x16; 
	/* set clock (4us period) */ 
	T8STCR  &=0xFE; 
    }

    __INLINE__ void __ALWAYS_INLINE__ EE_t80_start(void)
    {
	/* no interrupt; clear on tcroa match; set clock 500kHz (2us) */	
	T80TCR = 0x0A; 
    }
    
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_stop(void)
    {
	/* no interrupt; clear on match tcora; stop clock */
	T80TCR = 0x08; 
    }
    
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_set_cora(EE_UINT8 value)
    {
	T80TCORA = value; 
    }
    
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_set_corb(EE_UINT8 value)
    {
	T80TCORB = value; 
    }

#endif /* __T80_SUPPORT__ */


#ifdef __T81_SUPPORT__

    __INLINE__ void __ALWAYS_INLINE__ EE_t81_init(void)
    {
	/* stop timer */
	T81TCR   =0x00; 
	/* reset counter */
	T81TCNT  =0;    
	/* clear previous match */	
	T81TCSR  =0x10; 
	/* set group clock (8us period) */ 
	T8STCR  &=0xFA; 
    }

    __INLINE__ void __ALWAYS_INLINE__ EE_t81_start(void)
    {
	#if defined(__MOTOR_A_PWM_USED__) && defined(__MOTOR_C_PWM_USED__)
	/* MatchA, MatchB, Overflow interrupts; clock 8us */	
	    T81TCR = 0xE2; 
	#else
	#ifdef __MOTOR_A_PWM_USED__
	/* MatchA, Overflow interrupts; clock 8us */		
	    T81TCR = 0X62;
	#else
	#ifdef __MOTOR_C_PWM_USED__
	/* MatchB, Overflow interrupts; clock 8us */		
	    T81TCR = 0XA2;
	#else
	/* No Interrupt; clock 8us */		
	/* It could be usefull to define some constant for 	*
	 * specific application 				*/
	    T81TCR = 0x02;
	#endif
	#endif
	#endif
    }
    
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_stop(void)
    {
	/* no interrupt; stop clock */
	T81TCR = 0x00; 
    }
    
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_set_cora(EE_UINT8 value)
    {
	T81TCORA = value; 
    }
    
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_set_corb(EE_UINT8 value)
    {
	T81TCORB = value; 
    }

#endif /* __T81_SUPPORT__ */
/**********************
 * motors functions
 **********************/

#ifdef __MOTOR_VP_SUPPORT__
    struct motor_state { 
	EE_UINT8 power;  /* MIN_MOTOR_POWER, ..., MAX_MOTOR_POWER */ 
        EE_UINT8 action; /* brake, go0, go1, float */ 
    };
#endif


#ifdef __MOTOR_A_VP_USED__
    struct motor_state motorA_state;

    __INLINE__ void __ALWAYS_INLINE__ EE_motorA_power(EE_UINT8 pow)
    {	    
	motorA_state.power=pow;
    }    

    __INLINE__ void __ALWAYS_INLINE__ EE_motorA_action(EE_UINT8 action)
    {
	motorA_state.action=action;
    }
#endif

#ifdef __MOTOR_B_VP_USED__
    struct motor_state motorB_state;

    __INLINE__ void __ALWAYS_INLINE__ EE_motorB_power(EE_UINT8 pow)
    {
	motorB_state.power=pow;
    }

    __INLINE__ void __ALWAYS_INLINE__ EE_motorB_action(EE_UINT8 action)
    {
	motorB_state.action=action;
    }            
#endif

#ifdef __MOTOR_C_VP_USED__
    struct motor_state motorC_state;

    __INLINE__ void __ALWAYS_INLINE__ EE_motorC_power(EE_UINT8 pow)
    {
	motorC_state.power=pow;
    }        

    __INLINE__ void __ALWAYS_INLINE__ EE_motorC_action(EE_UINT8 action)
    {
	motorC_state.action=action;
    }    
#endif




#ifdef __MOTOR_A_PWM_USED__

    EE_UINT8 _motA_action;

    __INLINE__ void __ALWAYS_INLINE__ EE_motorA_action(EE_UINT8 act)
    {
	_motA_action=act;
    }
    
    __INLINE__ void __ALWAYS_INLINE__ EE_motorA_power(EE_UINT8 pow)
    {
	EE_t81_set_cora(pow);    
    }
    
#endif

#ifdef __MOTOR_C_PWM_USED__
    EE_UINT8 _motC_action;
    
    __INLINE__ void __ALWAYS_INLINE__ EE_motorC_action(EE_UINT8 act)
    {
	_motC_action=act;
    }

    __INLINE__ void __ALWAYS_INLINE__ EE_motorC_power(EE_UINT8 pow)
    {
	EE_t81_set_corb(pow);            
    }
    
#endif

#if defined(__MOTOR_PWM_SUPPORT__) || defined(__MOTOR_VP_SUPPORT__)

    __INLINE__ void __ALWAYS_INLINE__ EE_motor_init(void)
    {	
	#ifdef __MOTOR_A_VP_USED__
	    EE_motorA_power(VP_MIN_MOTOR_POWER);
	    EE_motorA_action(MotorFloat);
	#endif

	#ifdef __MOTOR_B_VP_USED__
	    EE_motorB_power(VP_MIN_MOTOR_POWER);	    
	    EE_motorB_action(MotorFloat);	    
	#endif

	#ifdef __MOTOR_C_VP_USED__
	    EE_motorC_power(VP_MIN_MOTOR_POWER);	
	    EE_motorC_action(MotorFloat);	    
	#endif
	
	MotorDevReg=0x00;    
		
	#ifdef __MOTOR_PWM_SUPPORT__
	    EE_t81_init();
	#endif
	
	#ifdef __MOTOR_A_PWM_USED__	
	    EE_motorA_action(MotorFloat);	
    	    EE_set_handler(CMI1A_IRQ, CMI1A_handler);	    
            EE_enable_irq(CMI1A_IRQ);            	
	#endif
	
	#ifdef __MOTOR_C_PWM_USED__	
    	    EE_motorC_action(MotorFloat);    		
	    EE_set_handler(CMI1B_IRQ, CMI1B_handler);	         
            EE_enable_irq(CMI1B_IRQ);        	    
	#endif
	
	#ifdef __MOTOR_PWM_SUPPORT__
            EE_set_handler(OVI1_IRQ, OVI1_handler);        
	    EE_enable_irq(OVI1_IRQ);            
            EE_t81_start();
	#endif
    }    
#endif
    
/********************
 * sound functions
 ********************/

#ifdef __PLAY_BUFFER_SUPPORT__  
    struct EE_note_type {
        EE_UINT8 n;  	/* tcroa value to obtain the frequency of that note */ 
	EE_UINT8 n_len; 	/* note length */
	EE_UINT8 p_len; 	/* pause length (after that note has been played) */
    };
               
    __INLINE__ void __ALWAYS_INLINE__ EE_play_buffer_init(void)
    {
	/* data used by timer handler */
	playing=0;

	/* set channel 0 of 8 bit timer to drive speaker */
	EE_t80_init();
    }

    __INLINE__ void __ALWAYS_INLINE__ EE_play_buffer_stop(void)
    {
	playing=0;            	
	EE_t80_stop();
    }

    __INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_is_playing_buffer(void)
    {
	return playing;
    }

#endif

#ifdef __PLAY_NOTE_SUPPORT__
__INLINE__ void __ALWAYS_INLINE__ EE_play_note_init(void)
{
    /* data used by timer handler */
    play_note_state=0;
    
    /* set channel 0 of 8 bit timer to drive speaker */
    EE_t80_init();
}

__INLINE__ void __ALWAYS_INLINE__ EE_play_note_stop(void)
{
    play_note_state=0;    
    EE_t80_stop();        
}
#endif


/***********************
 * initialize function 
 ***********************/
__INLINE__ void __ALWAYS_INLINE__ EE_init(void)
{
   /* Note that at this point I=1 (interrupt disabled) */
   
   /* sleep must cause sleep mode.
    * software standby mode would hack the system since all on-chip   *
    * modules would be halted and this is not good for real time!     *
    * Furthermore, settling time (~8ms) is needed to recover from.    *
    * So, this is why sleep mode is selected and not sw standby mode. */
    SYSCR= 0x0B; 

    /* clear pending IRQ (button) interrupt */
    EE_disable_irq(ONOFF_BUTTON);        
    EE_disable_irq(RUN_BUTTON);    
    EE_button_irq_mode(ONOFF_LEVEL_RUN_LEVEL);
    
    /* init 16bit timer: always neeed (ROM use it before downloading firmaware) */
    EE_t16_init();       
   
    /* init play buffer */
    #ifdef __PLAY_BUFFER_SUPPORT__   
	EE_play_buffer_init(); 
    #endif
    
    /* init play note */
    #ifdef __PLAY_NOTE_SUPPORT__
	EE_play_note_init();    
    #endif   
    
    /* init motors */
    #if defined(__MOTOR_VP_SUPPORT__) || defined(__MOTOR_PWM_SUPPORT__)
	EE_motor_init();
    #endif   
   
    /* init a/d converter */
    #ifdef __AD_SUPPORT__
	EE_ad_init();
    #endif
    
    /* init ports */
	//    EE_ports_init(); REALLY NEEDED???

    /* system handler installation */
  #ifdef __TIMER_A_SUPPORT__	       
	/* set handler to activate periodic task or to call user function */
	EE_set_handler(OCIA_IRQ, EE_timerA_handler);
	EE_t16_set_ocra(EE_t16_get_frc() + TIMER_A_PERIOD); /* next match */        
	EE_t16_reset_ocra_match_flag();    
	EE_enable_irq(OCIA_IRQ);
    #endif    

    #ifdef __TIMER_B_SUPPORT__
	/* set handler for sound, motors, user function, periodic task(if 	*
	 * timerA is not used for that purpose)					*/
	EE_set_handler(OCIB_IRQ, EE_timerB_handler);
	EE_t16_set_ocrb(EE_t16_get_frc() + TIMER_B_PERIOD); /* next match */        
	EE_t16_reset_ocrb_match_flag();    
	EE_enable_irq(OCIB_IRQ);
    #endif
}

/***************************
 * delete firmware function
 ***************************/            
__INLINE__ void __ALWAYS_INLINE__ delete_firmware(void)
{      
   *(char *) 0xFFCC=1;
   (*(void (**) (void))0) ();
}


