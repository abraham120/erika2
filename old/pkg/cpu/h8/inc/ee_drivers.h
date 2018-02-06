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
 * CVS: $Id: ee_drivers.h,v 1.2 2006/04/08 21:07:06 pj Exp $
 */

#include "eecfg.h"
#include "erikahal.h"
 

/********************************
 *      INTERRUPT HANDLING
 ********************************/
 
/* 
 * constants (passed to sethandler, enableIRQ, disableIRQ (decr. interr. priority order) 
 */
 
/* external interrupt source (buttons) */
#define RUNBUTTON_IRQ   0x00C7  // IRQ0 (offset 0, bit 0 of IER (0xFFC7)) 
#define ONOFFBUTTON_IRQ 0x09C7  // IRQ1 

/* internal interrupt source */
#define ICIA_IRQ        0x1F90  // 16 bit timer 
#define ICIB_IRQ        0x2690   
#define ICIC_IRQ        0x2D90
#define ICID_IRQ        0x3490
#define OCIA_IRQ        0x3B90
#define OCIB_IRQ        0x4290
#define FOVI_IRQ        0x4990
#define CMI0A_IRQ       0x56C8  // 8 bit timers (bit 6 of TCR, 0xFFC8)
#define CMI0B_IRQ       0x5FC8
#define OVI0_IRQ        0x65C8
#define CMI1A_IRQ       0x6ED0
#define CMI1B_IRQ       0x77D0
#define OVI1_IRQ        0x7DD0
#define ERI_IRQ         0x86DA  // ERI and RXI controlled by
#define RXI_IRQ         0x8EDA  // the same bit of the register.
#define TXI_IRQ         0x97DA  // (bit 7 of SCR, 0xFFDA)
#define TEI_IRQ         0x9ADA
#define ADI_IRQ         0xA6E8  // A/D converter (bit 6 of ADSCR, 0xFFE8)
#define WOVF_IRQ        0xADA8  // watchdog timer (bit 5 of TCSR, 0xFFA8)

/* 
 * Macros needed to install handlers 
 */
 
/* call this macro just when you declare interrupt 'handler' */
#define EE_declare_stub(handler) void  handler##_stub(void);

/* call this macro after the previous, to install 'handler'  */
#define EE_set_handler(type_irq,handler) *(void (**) (void)) (0xFD94+(type_irq>>10))=handler##_stub; 


/* 
 * functions 
 */
 
/* Interrupt requests passed to the cpu (I=0) */
__INLINE__ void __ALWAYS_INLINE__ EE_interrupt_on(void);

/* Interrupt requests masked (I=1) */
__INLINE__ void __ALWAYS_INLINE__ EE_interrupt_off(void);

/* enable an interrupt source (irq is one of the previous defined constant) */
__INLINE__ void __ALWAYS_INLINE__ EE_enable_irq(EE_TYPEIRQ irq);

/* disable an interrupt source (irq is one of the previous defined constant) */
__INLINE__ void __ALWAYS_INLINE__ EE_disable_irq(EE_TYPEIRQ irq);     


#define ONOFF_EDGE_RUN_EDGE	0xFB
#define ONOFF_EDGE_RUN_LEVEL	0xFA
#define ONOFF_LEVEL_RUN_EDGE	0xF9
#define ONOFF_LEVEL_RUN_LEVEL	0xF8

/* When run or on/off button are pressed an interrupt request is generated in two ways: 	*
 * - a single time, when button is falling down (edge sensed)
 * - continuously while button is still pressed (level sensed)
 * The parameter 'mode' is one of the costant upper defined. */
__INLINE__ void __ALWAYS_INLINE__ EE_button_irq_mode(EE_UINT8 mode);


/**********************
 *      BUTTONS
 **********************/

/* 
 * constants 
 */
 
#define RUN_BUTTON   0
#define ONOFF_BUTTON 1
#define VIEW_BUTTON  2
#define PRGM_BUTTON  3

/* 
 * function 
 */

/* return 1 if button is pressed, 0 otherwise */
EE_UINT8 EE_button_pressed(EE_UINT8 button);


/**********************
 *      SOUND
 **********************/

/* 
 * constants
 */

/* these are the value used to set TCROA for playing that note */
/* octave 0 */
#define _DO0	250  	/* 1000Hz */
#define _RE0 	222	/* 1126Hz */
#define _MI0 	200	/* 1250Hz */
#define _FA0 	188	/* 1330Hz */
#define _SOL0	167	/* 1497Hz */
#define _LA0	150	/* 1667Hz */
#define _SI0	133	/* 1880Hz */
/* octave 1 */
#define _DO1    125	/* 2000Hz (=_DO0 * 2) */ 
#define _RE1 	111
#define _MI1 	100
#define _FA1 	94
#define _SOL1	83
#define _LA1	75
#define _SI1	66
/* octave 2 */
#define _DO2    62
#define _RE2 	55
#define _MI2 	50
#define _FA2 	47
#define _SOL2	42
#define _LA2	38
#define _SI2	33

/* pause */

//   #define _PAUSE	1
/*											*
 *  _PAUSE is useless. To play only a pause you can play some note witn 0 length	*
 *  and with p as value for the pause. For example, to play a pause of 100ms:		*
 *		play (_FA2,0,50);							*
 *  I prefer to don't define _PAUSE to prevent improper use like this:			*
 *		play (_PAUSE, n, p)							*
 *  with n>0. This would result in playing a sound and not a pause!			*
 *  You can define your own 'pause' in a way like this: 				*
 *		#define _pause _D01							*
 *  remembering that if you specify an n>0 you will get a _DO1 instead of a pause!	*
 *											*       
 *  Remeber that the mininum length is the period of the timer handler (2ms at present) *
 *											*/

#ifdef __PLAY_BUFFER_SUPPORT__        
    /* 
     * data 
     */     
    extern EE_UINT8  play_mode, note_num, note2play, 
		  note_next, playing, note_length, pause_length;    
    extern struct EE_note_type * EE_buffer_addr;        
    
    #define PLAY_ONCE		0	/* play buffer only one time */
    #define PLAY_BACKGROUND	1	/* play buffer continuously   */
    
    /* 
     * functions
     */     

    /* called by init(): initialize data for playing a buffer */
    __INLINE__ void __ALWAYS_INLINE__ EE_play_buffer_init(void);

    /* stop playing (asincronous) */
    __INLINE__ void __ALWAYS_INLINE__ EE_play_buffer_stop(void);
    
    /* return 1 if a buffer is playing, otherwise 0 */
    __INLINE__ EE_UINT8 __ALWAYS_INLINE__ EE_is_playing_buffer(void);    

    /* Play num_note notes which are stored starting from buffer_addr address; 		*
     * mode= PLAY_ONCE, PLAY_BACKGROUND.  						*
     * Note that while a buffers is playing, a call to play cause to ignore new buffer  *
     * If you want to stop playing buffer and play new buffer, use play_buffer_stop()   */				
    void EE_play_buffer(struct EE_note_type *  buffer_addr, EE_UINT8 num_note, EE_UINT8 mode); 
    
#endif  /* __PLAY_BUFFER_SUPPORT__ */

#ifdef __PLAY_NOTE_SUPPORT__
    /*
     * data
     */    
    
    extern EE_UINT8 play_note_state;
    
    /*
     * functions
     */
     
    /* called by init(): initialize data for playing notes */
    __INLINE__ void __ALWAYS_INLINE__ EE_play_note_init(void);
    
    /* stop playing (asincronous) */
    __INLINE__ void __ALWAYS_INLINE__ EE_play_note_stop(void);    
    
    /* play the note for the specified length: if you try to play a new note while a	*
     * previous note is still playing, new note is ignored. If you want to avoid this,  *
     * call play_note_stop before playing new note 					*/
    void EE_play_note(EE_UINT8 note, EE_UINT8 length);
    
#endif  /* __PLAY_NOTE_SUPPORT__ */



/**********************
 *      MOTORS
 **********************/

/* 
 * device register 
 */

#define MotorDevRegAddr 0xF000
#define MotorDevReg (* (volatile EE_UINT8 *) MotorDevRegAddr) 


/* 
 * constants
 */

/* motor name */ 
#define MotorA     0   
#define MotorB     1 
#define MotorC     2    

/* motor action */ 
#define MotorGo0   1 
#define MotorGo1   2             					  
#define MotorBrake 3            					  
#define MotorFloat 0            

#ifdef __MOTOR_VP_SUPPORT__
    #define VP_MOTOR_PERIOD    15

    /* macro used by application */
    #define VP_MIN_MOTOR_POWER  1
    #define VP_MAX_MOTOR_POWER  15 
#endif

#ifdef __MOTOR_PWM_SUPPORT__
    #define PWM_MOTOR_PERIOD     255
    /* macro used by application */
    #define PWM_MIN_MOTOR_POWER  15
    #define PWM_MAX_MOTOR_POWER  (PWM_MOTOR_PERIOD-10)    

    void OVI1_handler(void);
    EE_declare_stub(OVI1_handler);    
#endif


/* 
 * functions 
 */

/* Variable power motors: 
 * you can set the power and the action of the motors. So motors can run but 		*
 * also brake with different intensity. 						*
 * The range of possible powers is: 							*
 * - (VP_MIN_MOTOR_POWER, VP_MAX_MOTOR_POWER) for VP controlled motors. 		*
 * - (PWM_MIN_MOTOR_POWER, PWM_MAX_MOTOR_POWER) for PWM controlled motors. 		*
 */
 
#if defined(__MOTOR_A_VP_USED__) || defined(__MOTOR_A_PWM_USED__)

    /* set power of motor A */    
    __INLINE__ void __ALWAYS_INLINE__ EE_motorA_power(EE_UINT8 power);
    
    /* set action (one of the previous defined constants)  of motor A */
    __INLINE__ void __ALWAYS_INLINE__ EE_motorA_action(EE_UINT8 action);

    #ifdef __MOTOR_A_PWM_USED__    
	EE_declare_stub(CMI1A_handler);
	void CMI1A_handler(void);
        void _motorA_reg(EE_UINT8 act); // in asm (set device reg.)
    #endif
#endif

#ifdef __MOTOR_B_VP_USED__
    /* set power of motor B */    
    __INLINE__ void __ALWAYS_INLINE__ EE_motorB_power(EE_UINT8 power);
    
    /* set action (one of the previous defined constants)  of motor B */    
    __INLINE__ void __ALWAYS_INLINE__ EE_motorB_action(EE_UINT8 action);
#endif    

#if defined(__MOTOR_C_VP_USED__) || defined(__MOTOR_C_PWM_USED__)
    /* set power of motor C */    
    __INLINE__ void __ALWAYS_INLINE__ EE_motorC_power(EE_UINT8 power);
    
    /* set action (one of the previous defined constants)  of motor C */    
    __INLINE__ void __ALWAYS_INLINE__ EE_motorC_action(EE_UINT8 action);
    
    #ifdef __MOTOR_C_PWM_USED__
        void CMI1B_handler(void);
	EE_declare_stub(CMI1B_handler);
	void _motorC_reg(EE_UINT8 act); // in asm (set device reg.)
    #endif
#endif
	    
/* Fixed power motors: you cannot set power which is assumed to be maximum power (this	*
 * could appear rough but in this way timer handler is not overheaded handling motors)	*/
 
#ifdef __MOTOR_A_FP_USED__    
    /* set action (one of the previous defined constants)  of motor A */    
    void EE_motorA_action(EE_UINT8 action);
#endif    

#ifdef __MOTOR_B_FP_USED__
    /* set action (one of the previous defined constants)  of motor B */    
    void EE_motorB_action(EE_UINT8 action);
#endif

#ifdef __MOTOR_C_FP_USED__    
    /* set action (one of the previous defined constants)  of motor C */    
    void EE_motorC_action(EE_UINT8 action);
#endif 

#if defined(__MOTOR_VP_SUPPORT__) || defined(__MOTOR_PWM_SUPPORT__)
    /* called by init(): initialize data for motors handling */
    __INLINE__ void __ALWAYS_INLINE__ EE_motor_init (void);
#endif


/************************
 *      SYSTEM
 ************************/ 

/* 
 * control registers 
 */
 
#define SYSCRAddr 	0xFFC4
#define IERAddr   	0xFFC7
#define ISCRAddr  	0xFFC6
#define MDCRAddr  	0xFFC5
#define SYSCR 		(* (volatile EE_UINT8 *) SYSCRAddr)
#define IER   		(* (volatile EE_UINT8 *) IERAddr)
#define ISCR  		(* (volatile EE_UINT8 *) ISCRAddr)
#define MDCR  		(* (volatile EE_UINT8 *) MDCRAddr)

/*
 * function 
 */
 
 /* this function must be called before everything. It initialize:	*
  * - 16 bit timer, always. (calling t16_init());			*
  * - motors, if needed (calling motor_init());				*
  * - sound, if needed  (calling play_buffer_init or play_note_init) 	*
  * - a/d converter, always (calling ad_init());
  * - I/O ports, always (calling ports_init()) 				*
  * Finally, it  installs timer handlers needed (TIMER_A a/o TIMER_B),  *
  * according with defined macros.                                      */
__INLINE__ void __ALWAYS_INLINE__ EE_init(void);


/***************************************
 *      16 BIT FREE RUNNING TIMER 
 ***************************************/

/* 
 * registers 
 */
 
#define T16TIERAddr 	0xFF90
#define T16TCSRAddr 	0xFF91
#define T16TCRAddr  	0xFF96
#define T16TOCRAddr 	0xFF97
#define T16FRCAddr  	0xFF92     
#define T16OCRAAddr 	0xFF94
#define T16OCRBAddr 	0xFF94 // N.B. same address of OCRA (bit4 of TOCR select one)
#define T16TIER     	(* (volatile EE_UINT8 *) T16TIERAddr)
#define T16TCSR     	(* (volatile EE_UINT8 *) T16TCSRAddr)
#define T16TCR      	(* (volatile EE_UINT8 *) T16TCRAddr)
#define T16TOCR     	(* (volatile EE_UINT8 *) T16TOCRAddr)
#define T16FRC      	(* (volatile EE_UINT16 *) T16FRCAddr)     
#define T16OCRA     	(* (volatile EE_UINT16 *) T16OCRAAddr)     
#define T16OCRB     	(* (volatile EE_UINT16 *) T16OCRBAddr)     

/* 
 * timer handlers
 */
#ifdef __TIMER_A_USER_FUNCTION_USED__
    /* user function, called by timerA_handler */
    void EE_timerA_user_function(void);
#endif    

#ifdef __TIMER_B_USER_FUNCTION_USED__
    /* user function, called by timerB_handler */
    void EE_timerB_user_function(void);
#endif    

#ifdef __TIMER_A_SUPPORT__
    /* application must #define 'TIMER_A_PERIOD' ... in "eecfg.h" */
    EE_declare_stub (EE_timerA_handler);
    void EE_timerA_handler(void); /* 16bit timer matchA handler */
#endif

#ifdef __TIMER_B_SUPPORT__
    #define TIMER_B_PERIOD 1000   /* 1000tick = 2ms */ 
    
    EE_declare_stub (EE_timerB_handler);    
    void EE_timerB_handler(void);    /* 16bit timer matchB handler */  
#endif


/* 
 * 16bit timer functions 
 */
 
/* called by init(), to initialize timer */
__INLINE__ void __ALWAYS_INLINE__ EE_t16_init(void);     
				    
/* load value into FRC */
__INLINE__ void __ALWAYS_INLINE__ EE_t16_set_frc(EE_UINT16 value);

/* return FRC */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_t16_get_frc(void);

/* reset overflow flag when FRC overflows (from 0xFFFF to 0x0000) */
__INLINE__ void __ALWAYS_INLINE__ EE_t16_reset_frc_ovf(void);         

/* return OCRA value */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_t16_get_ocra(void);

/* load value into OCRA: when FRC matchs OCRA ocra_match_flag is set  */
__INLINE__ void __ALWAYS_INLINE__ EE_t16_set_ocra(EE_UINT16 value);

/* when frc and ocra match this bit is set: reset it to prevent continuous irq) */
__INLINE__ void __ALWAYS_INLINE__ EE_t16_reset_ocra_match_flag(void);

/* return OCRB value */
__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_t16_get_ocrb(void);

/* load value into OCRB: when FRC matchs OCRB ocrb_match_flag is set  */
__INLINE__ void __ALWAYS_INLINE__ EE_t16_set_ocrb(EE_UINT16 value);

/* when frc and ocra match this bit is set: you have to reset (prevent continuous irq) */
__INLINE__ void __ALWAYS_INLINE__ EE_t16_reset_ocrb_match_flag(void);


/***************************
 *      8 BIT TIMERS
 ***************************/

/* 
 * registers 
 */
 
#define T80TCRAddr  	0xFFC8
#define T80TCSRAddr 	0xFFC9
#define T81TCRAddr  	0xFFD0
#define T81TCSRAddr 	0xFFD1
#define T8STCRAddr  	0xFFC3
#define T80TCORAAddr  	0xFFCA
#define T80TCORBAddr  	0xFFCB
#define T80TCNTAddr   	0xFFCC
#define T81TCORAAddr  	0xFFD2
#define T81TCORBAddr  	0xFFD3
#define T81TCNTAddr   	0xFFD4
#define T80TCR    	(* (volatile EE_UINT8 *) T80TCRAddr)
#define T80TCSR   	(* (volatile EE_UINT8 *) T80TCSRAddr)
#define T81TCR    	(* (volatile EE_UINT8 *) T81TCRAddr)
#define T81TCSR   	(* (volatile EE_UINT8 *) T81TCSRAddr)
#define T8STCR    	(* (volatile EE_UINT8 *) T8STCRAddr)
#define T80TCORA  	(* (volatile EE_UINT8 *) T80TCORAAddr)     
#define T80TCORB  	(* (volatile EE_UINT8 *) T80TCORBAddr)     
#define T80TCNT   	(* (volatile EE_UINT8 *) T80TCNTAddr)
#define T81TCORA  	(* (volatile EE_UINT8 *) T81TCORAAddr)     
#define T81TCORB  	(* (volatile EE_UINT8 *) T81TCORBAddr)     
#define T81TCNT   	(* (volatile EE_UINT8 *) T81TCNTAddr)

#ifdef __T80_SUPPORT__

/* funtions for channel 0 of 8bit timer 
 * Note that this timer is used expressly to drive the on board speaker.
 */

    /* set registers so that a sound with frequency 1/tcora will be played */
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_init(void);
    
    /* start timer (start sound a frequency) */
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_start(void);
    
    /* stop timer (stop sound) */
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_stop(void);            
    
    /* set frequency for played sound */
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_set_cora(EE_UINT8 value);
    
    /* set duty cycle of square wave: typically set corb=(cora/2) (50%) */
    __INLINE__ void __ALWAYS_INLINE__ EE_t80_set_corb(EE_UINT8 value);

#endif /* __T80_SUPPORT__ */

/* channel 1: suitable for infrared carrier (output connected to infrared diode)
 * At the moment, it is used for PWM motor support when requested. 
 * However, basic functions are always avaible (as like as for channel 0).
 */ 

#ifdef __T81_SUPPORT__

/* funtions for channel 1 of 8bit timer 
 */

    /* initialize timer */
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_init(void);
    
    /* start timer (clock 8us)*/
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_start(void);
    
    /* stop timer */
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_stop(void);            
    
    /* set TCORA */
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_set_cora(EE_UINT8 value);
    
    /* set TCORB */
    __INLINE__ void __ALWAYS_INLINE__ EE_t81_set_corb(EE_UINT8 value);

#endif /* __T81_SUPPORT__ */


/*****************************
 *      WATCHDOG TIMER          
 *****************************/

/* 
 * registers 
 */
 
#define WDTCSRAddr 	0xFFA8
#define WDTCSR 		(* (volatile EE_UINT8 *) WDTCSRAddr)


/*******************************
 *      SERIAL INTERFACE
 *******************************/

/* 
 * registers 
 */

#define SISMRAddr  	0xFFD8
#define SISCRAddr  	0xFFDA
#define SISTCRAddr 	0xFFC3
#define SISMR  		( * (volatile EE_UINT8 *) SISMRAddr)
#define SISCR  		( * (volatile EE_UINT8 *) SISCRAddr)
#define SISTCR 		( * (volatile EE_UINT8 *) SISTCRAddr)


/***************************
 *      A/D CONVERTER 
 ***************************/ 

/* 
 * registers 
 */
 
#define ADCSRAddr   	0xFFE8
#define ADCRAddr    	0xFFE9
#define ADADDRAAddr 	0xFFE0 
#define ADADDRBAddr 	0xFFE2
#define ADADDRCAddr 	0xFFE4 
#define ADCSR       	(* (volatile EE_UINT8 *) ADCSRAddr)
#define ADCR        	(* (volatile EE_UINT8 *) ADCRAddr)
#define ADADDRA     	(* (volatile EE_UINT16 *) ADADDRAAddr)
#define ADADDRB     	(* (volatile EE_UINT16 *) ADADDRBAddr)
#define ADADDRC     	(* (volatile EE_UINT16 *) ADADDRCAddr)


#ifdef __AD_SUPPORT__
    /*
     * macros used to set mode and channels to be converted
     */

    /* macro format: "pqrm0ccc"
     *   p  : 0 or 1 if port 1 has a passive or active sensor
     *   q  : 0 or 1 if port 2 has a passive or active sensor
     *   r  : 0 or 1 if port 3 has a passive or active sensor
     *   m  : 0 single mode, 1 scan mode
     *   ccc: channel 
     */
    
    /* convert port 1; single mode; passive sensor */
    #define AD_PORT1_SINGLE_PAS		0x02 // 0b00000010 

    /* convert port 2; single mode; passive sensor */
    #define AD_PORT2_SINGLE_PAS		0x01 // OB00000001 

    /* convert port 3; single mode; passive sensor */
    #define AD_PORT3_SINGLE_PAS		0x00 // OB00000000

    /* convert port 1; single mode; active sensor */
    #define AD_PORT1_SINGLE_ACT		0x82 // OB10000010

    /* convert port 2; single mode; active sensor */
    #define AD_PORT2_SINGLE_ACT		0x41 // OB01000001

    /* convert port 3; single mode; active sensor */
    #define AD_PORT3_SINGLE_ACT		0x20 // OB00100000

    /* convert port 3; scan mode; passive sensor */
    #define AD_PORT3_SCAN_PAS		0x10 // OB00010000

    /* convert port 3; scan mode; active sensor */
    #define AD_PORT3_SCAN_ACT		0x30 // OB00110000

    /* convert ports 3, 2; scan mode; passive sensors */
    #define AD_PORT32_SCAN_PAS_PAS 	0x11 // OB00010001

    /* convert ports 3, 2; scan mode; p.3 passive, p.2 active sensors */
    #define AD_PORT32_SCAN_PAS_ACT	0x51 // OB01010001

    /* convert ports 3, 2; scan mode; p.3 active, p.2 passive sensors */
    #define AD_PORT32_SCAN_ACT_PAS	0x31 // OB00110001

    /* convert ports 3, 2; scan mode; active sensors */
    #define AD_PORT32_SCAN_ACT_ACT	0x71 // OB01110001

    /* convert ports 3, 2, 1; scan mode; pass. pass. pass. sensors */
    #define AD_PORT321_SCAN_PAS_PAS_PAS	0x12 // OB00010010

    /* convert ports 3, 2, 1; scan mode; pass. pass. act. sensors */
    #define AD_PORT321_SCAN_PAS_PAS_ACT	0x92 // OB10010010

    /* convert ports 3, 2, 1; scan mode; pass. act. pass. sensors */
    #define AD_PORT321_SCAN_PAS_ACT_PAS	0x52 // OB01010010

    /* convert ports 3, 2, 1; scan mode; pass. act. act. sensors */
    #define AD_PORT321_SCAN_PAS_ACT_ACT	0xD2 // OB11010010

    /* convert ports 3, 2, 1; scan mode; act. pass. pass. sensors */
    #define AD_PORT321_SCAN_ACT_PAS_PAS	0x32 // OB00110010

    /* convert ports 3, 2, 1; scan mode; act. pass. act. sensors */
    #define AD_PORT321_SCAN_ACT_PAS_ACT	0xB2 // OB10110010

    /* convert ports 3, 2, 1; scan mode; act. act. pass. sensors */
    #define AD_PORT321_SCAN_ACT_ACT_PAS	0x72 // OB01110010

    /* convert ports 3, 2, 1; scan mode; act. act. act. sensors */
    #define AD_PORT321_SCAN_ACT_ACT_ACT	0xF2 // OB11110010

    /* 
     * functions 
     */
 
    /* called by init(): initialize registers used by a/d converter */
    __INLINE__ void __ALWAYS_INLINE__ EE_ad_init(void);

    /* select mode and ports to be converted. 'c' is one of the previous macros */
    __INLINE__ void __ALWAYS_INLINE__ EE_ad_select(EE_UINT8 c);

    /* start conversion of selected ports */
    __INLINE__ void __ALWAYS_INLINE__ EE_ad_start(void);

    /* start fast conversion of selected ports (half time needed) */
    __INLINE__ void __ALWAYS_INLINE__ EE_ad_start_fast(void);

    /* stop conversion. Useful to stop conversion in scan mode. */
    __INLINE__ void __ALWAYS_INLINE__ EE_ad_stop(void);

    /* reset flag set at end of conversion. It is typically used at the 	*
     * end of A/D handler to avoid continous interrupt requests.        	*/
    __INLINE__ void __ALWAYS_INLINE__ EE_ad_reset_end_flag(void);

    /* return value stored after last conversion of port 1 */
    __INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_ad_get_port1(void); 				

    /* return value stored after last conversion of port 2 */
    __INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_ad_get_port2(void); 				

    /* return value stored after last conversion of port 3 */
    __INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_ad_get_port3(void);

#endif /* __AD_SUPPORT__ */

/***********************
 *      I/O PORTS
 ***********************/ 

/* 
 * Data registers 
 */
#define Port1Addr 	0xFFB2
#define Port2Addr 	0xFFB3
#define Port3Addr 	0xFFB6
#define Port4Addr 	0xFFB7
#define Port5Addr 	0xFFBA
#define Port6Addr 	0xFFBB
#define Port7Addr 	0xFFBE
#define Port1 		(* (volatile EE_UINT8 *) Port1Addr)
#define Port2 		(* (volatile EE_UINT8 *) Port2Addr)
#define Port3 		(* (volatile EE_UINT8 *) Port3Addr)
#define Port4 		(* (volatile EE_UINT8 *) Port4Addr)
#define Port5 		(* (volatile EE_UINT8 *) Port5Addr)
#define Port6 		(* (volatile EE_UINT8 *) Port6Addr)
#define Port7 		(* (volatile EE_UINT8 *) Port7Addr)

/* 
 * Data direction registers (only write) 
 */
 
#define Port1DdrAddr 	0xFFB0
#define Port2DdrAddr 	0xFFB1
#define Port3DdrAddr 	0xFFB4
#define Port4DdrAddr 	0xFFB5
#define Port5DdrAddr 	0xFFB8
#define Port6DdrAddr 	0xFFB9
#define Port1Ddr 	(* (volatile EE_UINT8 *) Port1DdrAddr)
#define Port2Ddr 	(* (volatile EE_UINT8 *) Port2DdrAddr)
#define Port3Ddr 	(* (volatile EE_UINT8 *) Port3DdrAddr)
#define Port4Ddr 	(* (volatile EE_UINT8 *) Port4DdrAddr)
#define Port5Ddr 	(* (volatile EE_UINT8 *) Port5DdrAddr)
#define Port6Ddr 	(* (volatile EE_UINT8 *) Port6DdrAddr)

/* 
 * Data direction shadow register (read/write):
 * (you must write them when you write corresponding data dir. reg.) 
 */
 
#define Port1DdrShadowAddr 	0xFD80
#define Port2DdrShadowAddr 	0xFD81
#define Port3DdrShadowAddr 	0xFDB2
#define Port4DdrShadowAddr 	0xFDB3
#define Port5DdrShadowAddr 	0xFDB4
#define Port6DdrShadowAddr 	0xFDB5
#define Port1DdrShadow 		(* (volatile EE_UINT8 *) Port1DdrShadowAddr)
#define Port2DdrShadow 		(* (volatile EE_UINT8 *) Port2DdrShadowAddr)
#define Port3DdrShadow 		(* (volatile EE_UINT8 *) Port3DdrShadowAddr)
#define Port4DdrShadow 		(* (volatile EE_UINT8 *) Port4DdrShadowAddr)
#define Port5DdrShadow	 	(* (volatile EE_UINT8 *) Port5DdrShadowAddr)
#define Port6DdrShadow 		(* (volatile EE_UINT8 *) Port6DdrShadowAddr)
/* Port7 has no data dir. reg. becouse it is an input port (A/D converter)) */

/* 
 * functions
 */

/* called by init(): initilize data direction regeister */
__INLINE__ void __ALWAYS_INLINE__ EE_ports_init (void);


/* write num on LCD (use ROM routine): if abs(num)>9999 then 9999 is showed */
void EE_lcd_write_num (EE_INT16 num);

/* clear LCD (use ROM routine) */
void EE_lcd_clear (void);

#ifdef __LCD_USED__
#define EE_LCD_display EE_lcd_write_num
#define EE_LCD_init	  EE_lcd_clear
#define EE_LCD_clear	  EE_lcd_clear
#endif

/*******************************
 *      UTILITY FUNCTIONS (Maybe this functions should be removed from final version.....)
 *******************************/ 
 
/* call ROM routine with one parameter */
void rom_func0 (EE_ADDR func);
 
/* call ROM routine with two parameter */
void rom_func1 (EE_ADDR func, EE_INT16 p1);

/* call ROM routine with three parameter */
void rom_func2 (EE_ADDR func, EE_INT16 p1, EE_INT16 p2);
 
/* call ROM routine with four parameter */
void rom_func3 (EE_ADDR func, EE_INT16 p1, EE_INT16 p2, EE_INT16 p3);

/* delete firmware */
__INLINE__ void __ALWAYS_INLINE__ delete_firmware (void);
