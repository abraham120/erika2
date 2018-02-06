/*
 * Author: 2002 Davide Cantini
 * CVS: $Id: ee_func_d.s,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "eecfg.h"
#include "ee.h"
#include "h8/drivers.h"

/***************************
 *  DATA 		   *
 ***************************/

/* data for nested primitives */
EE_UINT16 EE_nested_primitive_counter=0;

/* data for nested irq */
/* It can assume only two values: 0 or 1 (since nested irq not allowed) */
EE_UREG EE_IRQ_nesting_level=0;
 
/* data for handling sound */
#ifdef __PLAY_BUFFER_SUPPORT__
    EE_UINT8  play_mode, note_num, playing, note_next, note2play, note_length, pause_length;    
    struct EE_note_type * buffer_addr;
#endif /* __PLAY_BUFFER_SUPPORT__ */

#ifdef __PLAY_NOTE_SUPPORT__
    EE_UINT8 play_note_state;
#endif  /* __PLAY_NOTE_SUPPORT__ */

/* data for handling motors */
#if defined(__MOTOR_A_VP_USED__)
    #define A_float_on  0x00
    #define A_go0_on	0x40
    #define A_go1_on	0x80
    #define A_brake_on	0xC0
    static EE_UINT8 motorA_period_on[4]=     
	{ A_float_on, A_go0_on, A_go1_on, A_brake_on};

    #define A_float_off	0x00
    #define A_go0_off	0xC0
    #define A_go1_off	0xC0
    #define A_brake_off	0x00
    static EE_UINT8 motorA_period_off[4]=     
	{ A_float_off, A_go0_off, A_go1_off, A_brake_off};
#endif

#if defined(__MOTOR_B_VP_USED__) || defined(__MOTOR_B_PVP_USED__)
    #define B_float_on	0x00
    #define B_go0_on	0x04
    #define B_go1_on	0x08
    #define B_brake_on	0x0C
    static EE_UINT8 motorB_period_on[4]=     
	{ B_float_on, B_go0_on, B_go1_on, B_brake_on };    
    #define B_float_off 0x00
    #define B_go0_off	0x0C
    #define B_go1_off	0x0C
    #define B_brake_off	0x00
    static EE_UINT8 motorB_period_off[4]=     
	{ B_float_off, B_go0_off, B_go1_off, B_brake_off}; 
#endif

#if defined(__MOTOR_C_VP_USED__)
    #define C_float_on	0x00
    #define C_go0_on	0x01
    #define C_go1_on	0x02
    #define C_brake_on	0x03
    static EE_UINT8 motorC_period_on[4]=     
	{ C_float_on, C_go0_on, C_go1_on, C_brake_on };        

    #define C_float_off 0x00
    #define C_go0_off	0x03
    #define C_go1_off	0x03
    #define C_brake_off 0x00
    static EE_UINT8 motorC_period_off[4]=     
	{ C_float_off, C_go0_off, C_go1_off, C_brake_off}; 
#endif


/* HANDLERS for PWM motor support*/

#ifdef __MOTOR_A_PWM_USED__

    void CMI1A_handler(void)
    {	
	_motorA_reg(MotorBrake); // N.B. set MotorDevReg
        // reset match flag
	T81TCSR &= 0xBF;
	#ifdef __MOTOR_C_PWM_USED__
	    // not strictly needed.....
            // if matchC flag is already set then we anticipate motorC_action setting    

	    __asm__("	mov	#0xFFD1, r3
			mov.b	@r3, r3l                \
			btst 	#7, r3l	  ;; check if CMI1B flag is set	\
			beq	cmi1a_go                \
			mov.b	@__motC_action, r0l     \
			jsr	@_EE_motorC_action   \
		        cmi1a_go:	                        \
		    ");
		    
	#endif	

    }
#endif

#ifdef __MOTOR_C_PWM_USED__
    
    void CMI1B_handler(void)
    {
	_motorC_reg(MotorBrake); // N.B. set MotorDevReg
        // reset match flag
	T81TCSR &= 0x7F;    
	#ifdef __MOTOR_A_PWM_USED__
	    // not strictly needed.....	
	    // if matchA flag is already set then we anticipate motorA_action setting

    	    __asm__("	mov	#0xFFD1, r3		\
        	        mov.b	@r3, r3l                \
			btst 	#6, r3l	  ;; check if CMI1A flag is set \
    		        beq	cmi1b_go                \
			mov.b	@__motA_action, r0l     \
			jsr	@_EE_motorA_action   \
		        cmi1b_go:	                        \
		    ");
		    
	#endif

    }
#endif

#ifdef __MOTOR_PWM_SUPPORT__
    void OVI1_handler(void)
    {
	// Off time is at the beginnig of the period     
	
	#ifdef __MOTOR_A_PWM_USED__	
            _motorA_reg(_motA_action); // N.B. set MotorDevReg
	#endif
	
	#ifdef __MOTOR_C_PWM_USED__
	    _motorC_reg(_motC_action); // N.B. set MotorDevReg    
	#endif
        // reset overflow flag
	T81TCSR &= 0xDF;        

    }
#endif

/****************************
 *   FUNCTIONS              *
 ****************************/

/* utility function */
EE_UINT8 EE_button_pressed(EE_UINT8 button)
{								
  switch (button)
  {
    case RUN_BUTTON   : return !(Port4 & 0x04); break;// bit2 (=0: pressed)
    case ONOFF_BUTTON : return !(Port4 & 0x02); break;// bit1
    case VIEW_BUTTON  : return !(Port7 & 0x40); break;// bit 6
    case PRGM_BUTTON  : return !(Port7 & 0x80); break;// bit 7
    default:
       return 0;
  }  
}


void EE_lcd_write_num(EE_INT16 num)
{   
    EE_UINT16 p6_ddr;
    EE_UINT8 p6;

    p6_ddr = Port6DdrShadow;
    p6 = Port6;
    rom_func3 ((EE_ADDR) 0x1ff2,0x3001,num,0); /* output "num". see ROM func. 0x1ff2 */
    rom_func0 ((EE_ADDR) 0x27c8);              /* refresh (needed) */  
    Port6Ddr=Port6DdrShadow=p6_ddr;
    Port6=p6;
    
}

void EE_lcd_clear(void)
{
    EE_UINT16 p6_ddr;
    EE_UINT8 p6;
    p6_ddr = Port6DdrShadow;
    p6 = Port6;
    rom_func0((EE_ADDR) 0x27AC);               	/* lcd clear. see ROM func. 0x27AC */
    rom_func0((EE_ADDR) 0x27C8);			/* refresh (needed) */
    Port6Ddr=Port6DdrShadow=p6_ddr;
    Port6=p6;    
}


/****************************
 * PERIODIC TASK ACTIVATION *
 ****************************/
/* Removed from here. Now that is application dependent */



#ifdef __TIMER_A_SUPPORT__
     
    void EE_timerA_handler(void)
    {
	EE_UINT8 i; 		    

	/******************************* 
	 * set next handler activation 
         *******************************/	
	EE_t16_set_ocra(EE_t16_get_ocra() + TIMER_A_PERIOD); /* next match */        
	EE_t16_reset_ocra_match_flag();        
    
	#ifdef __TIMER_A_USER_FUNCTION_USED__
	/************************
         * user defined function 
	 ************************/		
	    
	    EE_timerA_user_function();
	    
	#endif /* __TIMER_A_USER_FUNCTION_USED__ */
	
    }
#endif /* __TIMER_A_SUPPORT__ */


#ifdef __TIMER_B_SUPPORT__

    void EE_timerB_handler(void)  /* 16bit timer matchB handler */
    {
     /* this handler runs every 2000us (T16OCRB matchs FRC). Its purposes are:
       - handling motors (duty cicle)
       - handling sound (generated by output of 8bit timer0)
     */   

        EE_UINT8 i;

	#ifdef __MOTOR_VP_SUPPORT__
	    EE_UINT8  mask;       // used for handling motors
	    static EE_UINT8 x = 0; // used for handling motors	    
	#endif    
    

	/******************************* 
	 * set next handler activation 
         *******************************/
	EE_t16_reset_ocrb_match_flag();
	EE_t16_set_ocrb(EE_t16_get_ocrb() + TIMER_B_PERIOD); /* (next match) */    

	#ifdef __MOTOR_VP_SUPPORT__     /* some PVP or VP motors is used */
	/************************************************
         * motors with (precise) variable power handling 
         ************************************************/
        
	    mask = MotorDevReg;
    
	    #ifdef __MOTOR_A_VP_USED__	
		mask &=0x3F;
		if (x<motorA_state.power)
		    mask |= motorA_period_on[motorA_state.action];
//    		#ifdef __MOTOR_A_PVP_USED__	
		else
		    /* when == motor is keeped float to avoid rough movement */
		    if (x>motorA_state.power)
    			mask |= motorA_period_off[motorA_state.action];
//    		#endif
	    #endif

	    #ifdef __MOTOR_B_VP_USED__	
		mask &=0xF3;
		if (x<motorB_state.power)
		    mask |= motorB_period_on[motorB_state.action];
//    		#ifdef __MOTOR_B_PVP_USED__	
		else
		    /* when == motor is keeped float to avoid rough movement */
		    if (x>motorB_state.power)		  
    			mask |= motorB_period_off[motorB_state.action];
//    		#endif
	    #endif
    
	    #ifdef __MOTOR_C_VP_USED__	
    		mask &=0xFC;
		if (x<motorC_state.power)
		    mask |= motorC_period_on[motorC_state.action];
//    		#ifdef __MOTOR_C_PVP_USED__	
		else
		    /* when == motor is keeped float to avoid rough movement */
		    if (x>motorC_state.power)
		  	mask |= motorC_period_off[motorC_state.action];
//    		#endif
	    #endif    

	    x++;    
	    if (x >= VP_MOTOR_PERIOD)
    		x = 0;        
	
	    MotorDevReg=mask;

	#endif /* __MOTOR_VP_SUPPORT__ */
    

	/******** ********* 
	* sound handling 
	*****************/
	#ifdef __PLAY_BUFFER_SUPPORT__
    
	    if (playing)
		for (;;)
		{
		    if (note_length>0)
		    {
			note_length--;
			break;
		    }
		    if (pause_length>0)
		    {
			pause_length--;
			EE_t80_stop();
			break;
		    }
		    if (note_next>=note_num)
		    {
			playing=play_mode;
			note_next=0;
			EE_t80_stop();
			
			break;
		    }

		    note2play=buffer_addr[note_next].n;
		    note_length=buffer_addr[note_next].n_len;
		    pause_length=buffer_addr[note_next].p_len;	    

		    EE_t80_set_cora(note2play);
		    EE_t80_set_corb(note2play>>1); /* duty cycle 50% */
		    EE_t80_start();		
	    	
		    note_next++;	
		}	    
        
	#endif /* __PLAY_BUFFER_SUPPORT__ */

	#ifdef __PLAY_NOTE_SUPPORT__     	
	    if (play_note_state>0)
		play_note_state--;
	    else 
		EE_t80_stop();
	#endif /* __PLAY_NOTE_SUPPORT__ */

    
	#ifdef __TIMER_B_USER_FUNCTION_USED__
	/***********************
	* user defined function 
	***********************/
    
	    /* call user function */
	    EE_timerB_user_function();

	#endif /* __TIMER_B_USER_FUNCTION_USED__ */    
    }
    
#endif /* __TIMER_B_SUPPORT__ */


#ifdef __PLAY_BUFFER_SUPPORT__
    void EE_play_buffer (struct EE_note_type *  b_addr, EE_UINT8 n_note, EE_UINT8 mode)
    {    
	if (!playing)  /* wait that precedent buffer ends before accept another buffer */
	{
	    buffer_addr=(struct EE_note_type *) b_addr;	/* buffer that contains notes */    
	    note_num=n_note; 	 				/* number of notes to play    */
	
	    play_mode=mode;				/* 0: once, 1: continuos (background) */
	    note_next=0;
	    note_length=0;
	    pause_length=0;
	    playing=1; 		
	}
    }
#endif /* __PLAY_BUFFER_SUPPORT__ */


#ifdef __PLAY_NOTE_SUPPORT__
    void EE_play_note(EE_UINT8 note, EE_UINT8 length)
    { 
	if (play_note_state==0)
	{
	    play_note_state=length;
	    EE_t80_set_cora(note);
	    EE_t80_set_corb(note>>1); /* 50% duty cycle */
	    EE_t80_start();
	}
    }
#endif /* __PLAY_NOTE_SUPPORT__ */
