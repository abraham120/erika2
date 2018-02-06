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

#include "ee.h"
#include "ee_irq.h"

#include "nwl/Nwl.h"

// Primary (XT, HS, EC) Oscillator without PLL
_FOSCSEL(FNOSC_PRIPLL);
// OSC2 Pin Function: OSC2 is Clock Output - Primary Oscillator Mode: XT Crystanl
_FOSC(OSCIOFNC_ON & POSCMD_XT);
// Watchdog Timer Enabled/disabled by user software
_FWDT(FWDTEN_OFF);
// Disable Code Protection
_FGS(GCP_OFF);            							

#define LCD_PERIOD 100
#define SEND_PERIOD 100

/****************************************************************************************/
/* 				Global Variables 					*/
/****************************************************************************************/
static unsigned char data_pack[150];
static unsigned int data_length;
static unsigned long int device_packet_counter = 1;
static unsigned long int coordinator_packet_counter = 1;
static unsigned long int error_counter = 0;
static unsigned long int invalid_counter = 0;

static unsigned char lcd_pos = 0;
static char lcd_buf[32];
volatile char out_str[60] = {'\n','T','E','S','T','\0'};

static volatile unsigned char wait_button = 1;

/****************************************************************************************/
/* 				Forward Declarations 					*/
/****************************************************************************************/
void lcd_puts(const char *ch);
void timer_set(void);
void start_system(void);
void wpan_rx_func(OpenZB_ExitStatus code, EE_UINT8 *data, EE_UINT16 length);
void wpan_err_func(OpenZB_ExitStatus code);

/****************************************************************************************/
/* 				INLINE Functions 					*/
/****************************************************************************************/
__INLINE__ void sprint_uint32_6d(char *str, unsigned long int num)
{
	str[6] = '\0';
	str[5] = (num%10)     + '0';
	str[4] = ((num/10)%10) + '0';
	str[3] = ((num/100)%10) + '0';
	str[2] = ((num/1000)%10) + '0';
	str[1] = ((num/10000)%10) + '0';
	str[0] = ((num/100000)%10) + '0';
}

__INLINE__ void sprint_uint16_3d(char *str, unsigned int num)
{
	str[3] = '\0';
	str[2] = (num%10)     + '0';
	str[1] = ((num/10)%10) + '0';
	str[0] = ((num/100)%10) + '0';
}

/****************************************************************************************/
/* 				Task Section	 					*/
/****************************************************************************************/


/* Generate and send packet with openZB stack */
TASK(send_packet)
{
	#define MSG_LEN 100

	unsigned char data[MSG_LEN];
	static unsigned char tx_led_status = 0;

	memset(data, 0x0, MSG_LEN);

	#ifdef DEVICE_TYPE_END_DEVICE

	/* Packet fixed values */
	data[0] = 0xAA;
	data[1] = 0xBB;
	data[2] = 0xCC;
	data[3] = 0xDD;
	data[4] = 0xEE;
	data[5] = 0xFF;

	/* Add device packet counter */
	data[6] = (device_packet_counter >> 24) & 0x000000FF;
	data[7] = (device_packet_counter >> 16) & 0x000000FF;
	data[8] = (device_packet_counter >> 8 ) & 0x000000FF;
	data[9] = (device_packet_counter      ) & 0x000000FF;

	/* Send data */
	openZB_send_bytes(data, MSG_LEN, 1);
	
	device_packet_counter++;

	#else

	/* Packet fixed values */
	data[0] = 0x0A;
	data[1] = 0x0B;
	data[2] = 0x0C;
	data[3] = 0x0D;
	data[4] = 0x0E;
	data[5] = 0x0F;

	/* Add coordinator packet counter */
	data[6] = (coordinator_packet_counter >> 24) & 0x000000FF;
	data[7] = (coordinator_packet_counter >> 16) & 0x000000FF;
	data[8] = (coordinator_packet_counter >> 8 ) & 0x000000FF;
	data[9] = (coordinator_packet_counter      ) & 0x000000FF;

	/* Send data */
	openZB_send_bytes(data, MSG_LEN, 0);

	coordinator_packet_counter++;

	#endif

	/* TX LEDs blink */
        if (tx_led_status) {
                EE_led_7_on();
                EE_led_6_off();
                tx_led_status = 0;
        } else {
                EE_led_7_off();
                EE_led_6_on();
                tx_led_status = 1;
        }
}

/* Manage the packet received from the openZB stack */
TASK(receive_packet)
{
	static unsigned char rx_led_status = 0;
	unsigned long int m_count = 0;

	/* RX LEDs blink */
	 if (rx_led_status) {
                EE_led_5_off();
                EE_led_4_on();
                rx_led_status = 0;
        } else {
                EE_led_5_on();
                EE_led_4_off();
                rx_led_status = 1;
        }

	error_counter++;

	#ifdef DEVICE_TYPE_END_DEVICE

	GetResource(read_buffer_mutex);

	/* Check packet length and fixed values */
	if(	data_length == MSG_LEN &&
		((unsigned char) data_pack[0]) == 0x0A &&
		((unsigned char) data_pack[1]) == 0x0B &&
		((unsigned char) data_pack[2]) == 0x0C &&
		((unsigned char) data_pack[3]) == 0x0D &&
		((unsigned char) data_pack[4]) == 0x0E &&
		((unsigned char) data_pack[5]) == 0x0F
	)
		EE_led_1_on();
	else
	        EE_led_1_off();

	m_count  = data_pack[9];
	m_count += ((unsigned long int)data_pack[8]) << 8;
	m_count += ((unsigned long int)data_pack[7]) << 16;
	m_count += ((unsigned long int)data_pack[6]) << 24;

	ReleaseResource(read_buffer_mutex);	

	/* LCD Print! */
	if( m_count == coordinator_packet_counter)
		error_counter--;
	
	coordinator_packet_counter = m_count + 1;

	lcd_puts("\n#TX = ");
	sprint_uint32_6d(out_str, device_packet_counter);
	lcd_puts(out_str);

	#else

	GetResource(read_buffer_mutex);

	/* Check packet length and fixed values */
	if(	data_length == MSG_LEN &&
		((unsigned char) data_pack[0]) == 0xAA &&
		((unsigned char) data_pack[1]) == 0xBB &&
		((unsigned char) data_pack[2]) == 0xCC &&
		((unsigned char) data_pack[3]) == 0xDD &&
		((unsigned char) data_pack[4]) == 0xEE &&
		((unsigned char) data_pack[5]) == 0xFF
	)
		EE_led_1_on();
	else
	        EE_led_1_off();

	m_count  = data_pack[9];
	m_count += ((unsigned long int)data_pack[8]) << 8;
	m_count += ((unsigned long int)data_pack[7]) << 16;
	m_count += ((unsigned long int)data_pack[6]) << 24;

	ReleaseResource(read_buffer_mutex);	

	/* LCD Print! */
	if( m_count == device_packet_counter)
		error_counter--;

	device_packet_counter = m_count + 1;

	ActivateTask(send_packet);

	lcd_puts("\n#TX = ");
	sprint_uint32_6d(out_str, coordinator_packet_counter);
	lcd_puts(out_str);

	#endif
	lcd_puts("\nBAD=");
	sprint_uint16_3d(out_str, invalid_counter);
	lcd_puts(out_str);
	lcd_puts(" ERR=");
	sprint_uint16_3d(out_str, error_counter);
	lcd_puts(out_str);
}

/* Manage writing on the LCD */
TASK(lcd_write)
{
	unsigned char i;

	GetResource(lcd_mutex);
		
	for (i=0;i<16;i++)
		EE_lcd_putc(lcd_buf[i]);
	EE_lcd_line2();
	for (i=16;i<32;i++)
		EE_lcd_putc(lcd_buf[i]);
	EE_lcd_home();	
		
	ReleaseResource(lcd_mutex);	
}


/****************************************************************************************/
/* 				main() Section	 					*/
/****************************************************************************************/
int main(void)
{
	/* Clock setup for 4MIPS */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0; 
	CLKDIVbits.PLLPOST = 0; 
	PLLFBDbits.PLLDIV  = 78;
	while(OSCCONbits.LOCK!=1);	

	/* Init ERIKA components */	
	EE_demoboard_leds_init();
	EE_buttons_init(&start_system, 0x01);
	EE_lcd_init();
	EE_lcd_clear();

	timer_set();

	SetRelAlarm(lcd_write_alarm, 1000, LCD_PERIOD);

	#ifdef DEVICE_TYPE_END_DEVICE
	lcd_puts("\nHullo! Press to\ninit device");
	#else
	lcd_puts("\nHullo! Press to\ninit coordinator");
	#endif
	EE_leds_on();
	wait_button = 1;
	while(wait_button);
		
	if(openZB_init(wpan_rx_func, wpan_err_func) == OPENZB_SUCCESS){
		EE_led_0_on();
	}
	else{
		lcd_puts("\nINIT ERROR!\nRESET MANUALLY!");
		for (;;);
	}

	#ifdef DEVICE_TYPE_END_DEVICE
	lcd_puts("\nOK! Press\nto start send!");
	wait_button = 1;
	while(wait_button);
	SetRelAlarm(send_packet_alarm, 1000, SEND_PERIOD);
	#else
	lcd_puts("\nOK! Waiting\nfirst message!");
	#endif


	/* Forever loop: background activities (if any) should go here */
	for (;;);
		
	return 0;
}

/****************************************************************************************/
/* 				Function Section					*/
/****************************************************************************************/

/* Receive callback: 
*  It copies the received packet in the global buffer and activate the RX manager task. 
*/
void wpan_rx_func(OpenZB_ExitStatus code, EE_UINT8 *data, EE_UINT16 length)
{
	if(code == OPENZB_SUCCESS){

		GetResource(read_buffer_mutex);

		memcpy(data_pack, data, length);
		data_length = length;

		ReleaseResource(read_buffer_mutex);	

		ActivateTask(receive_packet);
	}
}

/* Error callback: 
*  
*/
void wpan_err_func(OpenZB_ExitStatus code)
{
	invalid_counter++;
}

/* Start the system:
*/
void start_system(void)
{
	if (EE_button_get_S1() == 1 && wait_button == 1){
		wait_button = 0;
		EE_leds_off();
	}
}

/* Put String on LCD:
*  Access the LCD through the distributed buffer and the lcd_writer mechanism
*/
void lcd_puts(const char *ch)
{
	GetResource(lcd_mutex);
	
	while (*ch != '\0') {
		if (lcd_pos == 0){			
			memcpy(lcd_buf,lcd_buf+16,16);
			memset(lcd_buf+16,' ',16);
			lcd_pos=16;
		}
		if(*ch == '\n'){
			memset(lcd_buf+lcd_pos, ' ', (32-lcd_pos) );
			ch++;
			lcd_pos=31;
		}
		else{
			lcd_buf[lcd_pos] =*ch++;
		}
		lcd_pos=(lcd_pos+1)%32;
	}

	ReleaseResource(lcd_mutex);	
}

/* Setup the system timer:
*/
void timer_set(void)
{
	/* TIMER 1 */

	T1CON = 0;		/* Stops the Timer1 and reset control reg */
	TMR1 = 0;		/* Clear contents of the timer register	*/
	PR1 = 0x9C40;		/* Load the Period register */
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 5 */
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag */
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts */
	T1CONbits.TON = 1;	/* Start Timer1 with prescaler settings at 1:1 and clock source set to the internal instruction cycle */
}


/****************************************************************************************/
/* 					ISR Sesction					*/
/****************************************************************************************/

ISR2(_T1Interrupt)
{
	IFS0bits.T1IF = 0;
	CounterTick(task_counter);
}


