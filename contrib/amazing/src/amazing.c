#include "ee.h"
#include "amazing.h"
#include "dee_emulation_16-bit.h"
#include "touch.h"

#define AMAZING_LAPS			2
#define AMAZING_ALREADY_SET_ADDR	2
#define AMAZING_TUNE_ADDR		4
#define AMAZING_DUTY_MIN		1200
#define AMAZING_DUTY_MAX		1800

volatile EE_UINT8 pwm_phase = 0;
volatile EE_UINT8 modified = 0;

/* Program the Timer9 peripheral to raise interrupts */
static void T9_program(void)
{
	T9CON = 0;		/* Stops the Timer9 and reset control reg	*/
	TMR9  = 0;		/* Clear contents of the timer register	*/
	PR9 = 40000;
	IPC13bits.T9IP = 5;	/* Set Timer9 priority to 1		*/
	IFS3bits.T9IF = 0;	/* Clear the Timer1 interrupt status flag	*/
	IEC3bits.T9IE = 1;	/* Enable Timer1 interrupts		*/
	T9CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1  and clock source set to the internal  instruction cycle */
}

/* Clear the Timer9 interrupt status flag */
static void T9_clear(void)
{
	IFS3bits.T9IF = 0;
}

ISR2(_T9Interrupt)
{
	static EE_UINT16 c_tick = 0;
	// clear the interrupt source
	T9_clear();

	if(c_tick == 2000){

		switch(pwm_phase%4)
		{
			case 0: 
				EE_ocpwm_set_duty(EE_PWM_PORT1,AMAZING_DUTY_MIN);
				EE_ocpwm_set_duty(EE_PWM_PORT2,AMAZING_DUTY_MIN);
				break;
			case 1:
				EE_ocpwm_set_duty(EE_PWM_PORT1,AMAZING_DUTY_MAX);
				break;
			case 2:
				EE_ocpwm_set_duty(EE_PWM_PORT2,AMAZING_DUTY_MAX);
				break;
			case 3:
				EE_ocpwm_set_duty(EE_PWM_PORT1,AMAZING_DUTY_MIN);
				break;
		}

		if(++pwm_phase == AMAZING_LAPS*4) T9CONbits.TON = 0; 

		c_tick = 0;

	} else c_tick++;
}

void amazing_reset_body()
{
	DataEEInit();
	dataEEFlags.val = 0;	
	DataEEWrite(0x00,AMAZING_ALREADY_SET_ADDR);
	asm("reset");
}

static EE_UINT8 read_permanent_conf(tune_raw_t *tn)
{
/*	EE_UINT8 i;
	if(DataEERead(AMAZING_ALREADY_SET_ADDR) == 0xEE){	
		for(i=0; i<sizeof(tune_raw_t); i++)
			tn->value[i] = DataEERead(AMAZING_TUNE_ADDR+i);
		return 1;
	}
	return 0;
*/

	EE_UINT8 i;
	EE_UINT8* pointer = (EE_UINT8*)tn;
	if(DataEERead(AMAZING_ALREADY_SET_ADDR) == 0xEE){	
		for(i=0; i<sizeof(tune_raw_t); i++){
			*pointer = DataEERead(AMAZING_TUNE_ADDR+i);
			pointer++;
		}
		return 1;
	}
	return 0;
}

static void write_permanent_conf(tune_raw_t *tn)
{
	/*
	EE_UINT8 i;
	for(i=0; i<sizeof(tune_raw_t); i++)
		DataEEWrite(tn->value[i],AMAZING_TUNE_ADDR+i);
	*/
	
	EE_UINT8 i;
	EE_UINT8* pointer = (EE_UINT8*)tn;
	for(i=0; i<sizeof(tune_raw_t); i++){
		DataEEWrite(*pointer,AMAZING_TUNE_ADDR+i);
		pointer++;
	}
}

void amazing_tuner_body(EE_UINT16 horiz_width, EE_UINT16 vert_height)
{
	tune_raw_t t_raw;
	EE_INT16 X_raw,Y_raw;
	EE_UINT16 min_x=65535,max_x=0;
	EE_UINT16 min_y=65535,max_y=0;

	DataEEInit();
	dataEEFlags.val = 0;	

	touch_set_dimension(TOUCH_X_AXIS,horiz_width);
	touch_set_dimension(TOUCH_Y_AXIS,vert_height);
	touch_raw_init();
	touch_start();

	EE_ocpwm_init( EE_PWM_PORT1 , 20000 , 0 );
	EE_ocpwm_init( EE_PWM_PORT2 , 20000 , 0 );

	if(!read_permanent_conf(&t_raw))
	{
		pwm_phase = 0;
		T9_program();
	
#ifdef CONFIG_AMAZING_UART_DEBUG
		EE_uart_write_byte(EE_UART_PORT_2,'S');		
#endif
	
		while(1)
		{
			modified = 0;
			
			//touch_wait_raw_position(&X_raw,&Y_raw);
			touch_wait_raw_position(TOUCH_X_AXIS,&X_raw);
			touch_wait_raw_position(TOUCH_Y_AXIS,&Y_raw);
	
	        	if(X_raw < min_x){
	        	        min_x = X_raw;
	        	        modified = 1;
	        	}
	        	else if(X_raw > max_x){
	        	        max_x = X_raw;
	        	        modified = 1;
	        	}
	
	        	if(Y_raw < min_y){
	        	        min_y = Y_raw;
	        	        modified = 1;
	        	}
	        	else if(Y_raw > max_y){
	        	        max_y = Y_raw;
	        	        modified = 1;
	        	}
	
	        	if(!modified){
	
				if(pwm_phase>=AMAZING_LAPS*4) break;
			}
			else 
			{ 
#ifdef CONFIG_AMAZING_UART_DEBUG
				EE_uart_write_byte(EE_UART_PORT_2,'<');
				EE_uart_write_byte(EE_UART_PORT_2,(X_raw >> 8) & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,X_raw & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,(Y_raw >> 8) & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,Y_raw & 0xFF);
				EE_uart_write_byte(EE_UART_PORT_2,'>');
#endif
				t_raw.xt1 = min_x + 0.9*(max_x-min_x);  
				t_raw.yt1 = min_y + 0.5*(max_y-min_y);  
				t_raw.xt2 = min_x + 0.5*(max_x-min_x);  
				t_raw.yt2 = min_y + 0.9*(max_y-min_y);  
				t_raw.xt3 = min_x + 0.1*(max_x-min_x);  
				t_raw.yt3 = min_y + 0.1*(max_y-min_y);
			}
		}
	
		DataEEWrite(0xEE,AMAZING_ALREADY_SET_ADDR);
		write_permanent_conf(&t_raw);
	}
	
	EE_ocpwm_set_duty(EE_PWM_PORT1,EE_PWM_ZERO_DUTY);
	EE_ocpwm_set_duty(EE_PWM_PORT2,EE_PWM_ZERO_DUTY);

	touch_tune(&t_raw);
}

