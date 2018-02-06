#include "ee.h"
#include "uwl_ieee802154.h"
#include <string.h>
#include <stdio.h>


/* Primary (XT, HS, EC) Oscillator without PLL */
_FOSCSEL(FNOSC_PRIPLL);
/* OSC2 Pin Function: OSC2 is Clock Output
 * Primary Oscillator Mode: XT Crystanl */
_FOSC(OSCIOFNC_ON & POSCMD_XT);
/* Watchdog Timer Enabled/disabled by user software */
_FWDT(FWDTEN_OFF);
/* Disable Code Protection */
_FGS(GCP_OFF);

/******************************************************************************/
/*                         Constant Definitions                               */
/******************************************************************************/
#define LCD_PERIOD 		100

#define TEST_PANID			0x000A
#define TEST_CHANNEL		24
#define TEST_PACKET_SIZE	110
#define TEST_COORD_ADDR		0x0001
#define TEST_DEVICE_ADDR	0x0002

#define CHAT_PACKET_SIZE	100
#define CHAT_SEND_OFFSET 	3000
#define CHAT_SEND_PERIOD	1000

extern void _reset(void); /* RESET the device */

/******************************************************************************/
/*                         Global Variables                                   */
/******************************************************************************/
static unsigned char lcd_pos = 0;
static char lcd_buf[32];
static volatile unsigned char wait_button = 1;

volatile uint8_t keep_sending_gts = 0;
uint8_t test_packet[TEST_PACKET_SIZE];
uint16_t tx_counter = 0;
uint16_t tx_success = 0;
uint16_t rx_counter = 0;
uint16_t rx_seq_errors = 0;
uint16_t packet_ack = 0;

/******************************************************************************/
/*                          Function Definitions                              */
/******************************************************************************/
/* ----------------------------------------------------------------------------
|  Put String on LCD:                                                          |
|                                                                              |
|  Access the LCD through the distributed buffer and the lcd_writer mechanism  |
 ---------------------------------------------------------------------------- */
static void lcd_puts(const char *ch)
{
	GetResource(LCD_MUTEX);
	while (*ch != '\0') {
		if (lcd_pos == 0) {
			memcpy(lcd_buf, lcd_buf + 16, 16);
			memset(lcd_buf + 16, ' ', 16);
			lcd_pos = 16;
		}
		if (*ch == '\n') {
			memset(lcd_buf+lcd_pos, ' ', 32 - lcd_pos);
			ch++;
			lcd_pos = 31;
		} else {
			lcd_buf[lcd_pos] = *ch++;
		}
		lcd_pos = (lcd_pos + 1) % 32;
	}
	ReleaseResource(LCD_MUTEX);
}
/* ----------------------------------------------------------------------------
|  Press button actons:                                                        |
|                                                                              |
|  Button 1: Reset the wait_button variable (allow active wait)                |
|  Button 2: Do Nothing                                                        |
|  Button 3: Do Nothing                                                        |
|  Button 4: Reset the microcontroller                                         |
 ---------------------------------------------------------------------------- */
static void button_action(void)
{
	if (EE_button_get_S1() == 1 && wait_button == 1) {
		wait_button = 0;
		EE_leds_off();
	} else if (EE_button_get_S4() == 1) {
		_reset();
	}
}
/* ----------------------------------------------------------------------------
|  Rx callback function:                                                       |
|                                                                              |
|  Called by the network stack when data have been received.                   |
 ---------------------------------------------------------------------------- */
static void rx_data(int8_t status, uint8_t *data, uint8_t len, uint16_t addr)
{
	if (len <= TEST_PACKET_SIZE) {
		memcpy(test_packet, data, len);
		ActivateTask(CHAT_RECEIVE);
	}
}
/* ----------------------------------------------------------------------------
|  Setup system timers:                                                        |
|                                                                              |
|  Timer1: used for system ticks (CounterTick)                                 |
 ---------------------------------------------------------------------------- */
static void timer_set(void)
{
	/* TIMER 1  */
	T1CON = 0;		/* Stops the Timer1 and reset control reg */
	TMR1 = 0;		/* Clear contents of the timer register	*/
	PR1 = 0x9C40;		/* Load the Period register -> 1ms @ 40MHz */
	IPC0bits.T1IP = 5;	/* Set Timer1 priority to 5 */
	IFS0bits.T1IF = 0;	/* Clear the Timer1 interrupt status flag */
	IEC0bits.T1IE = 1;	/* Enable Timer1 interrupts */
	T1CONbits.TON = 1;	/* Start Timer1 without prescaler */
}

/******************************************************************************/
/*                                  TASKs                                     */
/******************************************************************************/
/* ----------------------------------------------------------------------------
|  LCD Writer                                                                  |
|                                                                              |
|  Manage writing on the LCD                                                   |
 ---------------------------------------------------------------------------- */
TASK(LCD_WRITE)
{
	unsigned char i;

	GetResource(LCD_MUTEX);
	for (i = 0; i < 16; i++)
		EE_lcd_putc(lcd_buf[i]);
	EE_lcd_line2();
	for (i = 16; i < 32;i++)
		EE_lcd_putc(lcd_buf[i]);
	EE_lcd_home();
	ReleaseResource(LCD_MUTEX);
}
/* ----------------------------------------------------------------------------
|  Test SIMPLE154 TX                                                           |
|                                                                              |
|  This task is the sending part of a 'chat' test application.                 |
|  This simply sends a packet to a remote node with two increasing IDs:        |
|  one for this node, the other to acknowledge the eventually received ID      |
 ---------------------------------------------------------------------------- */
TASK(CHAT_SEND)
{
	int8_t retv;
	static uint8_t packet[CHAT_PACKET_SIZE];
	static char tx_led = 0;

	memset(packet, 0, 100);
	packet[0] = 0xAA;
	packet[1] = 0xBB;
	packet[2] = 0xCC;
	packet[3] = 0xDD;
	packet[4] = 0xEE;
	packet[5] = 0xFF;
	packet[6] = tx_counter >> 8;
	packet[7] = tx_counter & 0x00FF;
	packet[8] = packet_ack >> 8;
	packet[9] = packet_ack & 0x00FF;
	if (tx_led) {
		tx_led = 0;
		EE_led_6_off();
		EE_led_7_on();
	} else {
		tx_led = 1;
		EE_led_6_on();
		EE_led_7_off();
	}
	retv = uwl_simple154_send(packet, CHAT_PACKET_SIZE, 0, 1);
	tx_counter++;
	if (retv < 0) {
	//	lcd_puts("\nCHAT error\nSEND GTS");
		EE_led_off();
		//for (;;) ;
	} else {
		tx_success++;
	}
}
/* ----------------------------------------------------------------------------
|  Test SIMPLE154 RX                                                           |
|                                                                              |
|  This task is the receiving part of a 'chat' test application.               |
|  This simply check the packet sequence numbers.                              |
 ---------------------------------------------------------------------------- */
TASK(CHAT_RECEIVE)
{
	char str[100];
	static char rx_led = 0;

	if (test_packet[0] != 0x0A || test_packet[1] != 0x0B ||
	    test_packet[2] != 0x0C || test_packet[3] != 0x0D ||
	    test_packet[4] != 0x0E || test_packet[5] != 0x0F) {
		EE_led_3_on();
		return;
	}
	packet_ack = test_packet[7];
	packet_ack += ((uint16_t) test_packet[6]) << 8;
	if (packet_ack != rx_counter)
		rx_seq_errors++;
	rx_counter = packet_ack;
	rx_counter++;
	if (rx_led) {
		rx_led = 0;
		EE_led_4_off();
		EE_led_5_on();
	} else {
		rx_led = 1;
		EE_led_4_on();
		EE_led_5_off();
	}
	sprintf(str, "\nCHAT:D ETX=%u\nRX=%u ERR=%u",
		tx_counter - tx_success, rx_counter, rx_seq_errors);
	lcd_puts(str);
}


/******************************************************************************/
/*                                   MAIN                                     */
/******************************************************************************/
int main(void)
{
	int8_t retv;

	/* Clock setup for 40 MHz */
	CLKDIVbits.DOZEN   = 0;
	CLKDIVbits.PLLPRE  = 0;
	CLKDIVbits.PLLPOST = 0;
	PLLFBDbits.PLLDIV  = 78;
	while (OSCCONbits.LOCK != 1) ;

	/* Init basic components */
	timer_set();
	EE_leds_init();
	EE_demoboard_leds_init();
	EE_buttons_init(&button_action, 0x0F);
	EE_lcd_init();
	EE_lcd_clear();
	EE_led_off();
	EE_leds_off();
	lcd_puts("\nHullo! Press\n1 to start D.");
	SetRelAlarm(LCD_WRITE_ALARM, 1000, LCD_PERIOD); /* Start LCD writer */
	wait_button = 1;
	while (wait_button) ;
	/* Init the Network Stack */
	uwl_simple154_set_rx_callback(rx_data);
	retv = uwl_simple154_init_device(TEST_DEVICE_ADDR, TEST_COORD_ADDR,
					 TEST_PANID, TEST_CHANNEL);
	if (retv < 0) {
		EE_leds_on();
		lcd_puts("\nS_154 error\ninit device");
		for (;;) ;
	}
	lcd_puts("\nD. is alive!\nReady!");
	SetRelAlarm(CHAT_SEND_ALARM, CHAT_SEND_OFFSET,
					    CHAT_SEND_PERIOD);

	/* Start the application */
	EE_led_on();

	/* Forever loop: background activities (if any) should go here */
	for (;;) ;

	return 0;
}

/******************************************************************************/
/*                                     ISRs                                   */
/******************************************************************************/
/* ----------------------------------------------------------------------------
|  ISR2 Timer1:                                                                |
|                                                                              |
|  Calls CounterTick for TASK_COUNTER                                          |
 ---------------------------------------------------------------------------- */
ISR2(_T1Interrupt)
{
	IFS0bits.T1IF = 0;
	CounterTick(TASK_COUNTER);
}

/******************************************************************************/
/*                                    TRAPs                                   */
/******************************************************************************/
//void _ISRFAST _OscillatorFail(void) { for(;;); }
//
//void _ISRFAST _AddressError(void) { for(;;); }
//
//void _ISRFAST _StackError(void) { for(;;); }
//
//void _ISRFAST _MathError(void) 	{ for(;;); }
//
//void _ISRFAST _DMACError(void) { for(;;); }
