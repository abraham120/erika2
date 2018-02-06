#include <string.h>
#include <stdio.h>

#include "ee.h"
#include "uwl_ieee802154.h"
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "lcd_log.h"



/******************************************************************************/
/*                         Constant Definitions                               */
/******************************************************************************/

#define USE_GTS 1 //Put 1 if you want to use GTSs

#define UWL_PANID		0x000A
#define UWL_CHANNEL		16
#define UWL_PACKET_SIZE	110


#define UWL_BO				6
#define UWL_SO				6

#define UWL_COORD_ADDR		0x0001
#define UWL_DEV_A_ADDR		0x0002
#define UWL_DEV_B_ADDR		0x0003
#define UWL_DEV_C_ADDR		0x0004
#define UWL_DEV_D_ADDR		0x0005
#define UWL_DEV_GTS_LEN	2

#define CHAT_PACKET_SIZE	100
#define UWL_SEND_OFFSET 3000
#define UWL_SEND_PERIOD	1000


/******************************************************************************/
/*                         Global Variables                                   */
/******************************************************************************/

static volatile unsigned char wait_button = 1;

uint8_t uwl_packet[UWL_PACKET_SIZE];
uint16_t uwl_destination_chat = UWL_MAC_SHORT_ADDRESS_BROADCAST;
uint16_t packet_ack = 0;
uint16_t tx_counter = 0;
uint16_t tx_success = 0;
uint16_t rx_counter = 0;
uint16_t rx_seq_errors = 0;


#ifdef USE_LCD_LOG

void console_init()
{
	/*Initialize the LCD*/
	STM32f4_Discovery_LCD_Init();
	LCD_LOG_Init();
	LCD_LOG_SetHeader("Powered by Erika RTOS");
	LCD_LOG_SetFooter("Erika RTOS UWL Coordinator Demo");
}

#else /* USE_LCD_LOG */

USART_InitTypeDef USART_InitStructure;

void console_init()
{
	/* USARTx configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	STM_EVAL_COMInit(COM1, &USART_InitStructure);	
}

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
 set to 'Yes') calls _write() */
#define PUTCHAR_PROTOTYPE int _write(int fd, char *ptr, int len)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PUTCHAR_PROTOTYPE
{
	
#ifdef __GNUC__
	/* Write "len" of char from "ptr" to file id "fd"
	 * Return number of char written.
	 * Need implementing with UART here. */
	EE_INT32 i;
	
	for (i = 0; i < len; i++) {
		/* Place your implementation of fputc here */
		/* e.g. write a character to the USART */
		USART_SendData(EVAL_COM1, (uint8_t) ptr[i]);
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	}
	
	return len;
#else
	
	USART_SendData(EVAL_COM1, (uint8_t) ch);
	while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	
	return ch;
	
#endif
}

#endif /* USE_LCD_LOG*/



/******************************************************************************/
/*                          Function Definitions                              */
/******************************************************************************/



/******************************************************************************/
/* Press button actions:                                                      */
/*                                                                            */
/* Reset the wait_button variable (allow active wait)			      */
/*																			  */
/******************************************************************************/

ISR2(button_usr_isr)
{
	if (STM_EVAL_PBGetState(BUTTON_USER) == 1 && wait_button == 1) {
		wait_button = 0;
	}

	/* Clear the EXTI line pending bit */
	EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
}


#ifdef USE_LCD_LOG
#define leds_blink() ((void)0)
#else

void leds_blink()
{
	volatile uint32_t i;

	do {
		STM_EVAL_LEDToggle(LED3);
		STM_EVAL_LEDToggle(LED4);
		STM_EVAL_LEDToggle(LED5);
		STM_EVAL_LEDToggle(LED6);

		i = 0;
		while (i++ < 500000);
	} while (1);
}

#endif

/* ----------------------------------------------------------------------------
|  Rx callback function:                                                       |
|                                                                              |
|  Called by the network stack when data have been received.                   |
 ---------------------------------------------------------------------------- */
static void rx_data(int8_t status, uint8_t *data, uint8_t len, uint16_t addr)
{
	if (len <= UWL_PACKET_SIZE) {
		memcpy(uwl_packet, data, len);
		uwl_destination_chat = addr;
		ActivateTask(UwlReceive);
	}
}


/******************************************************************************/
/*                                  TASKs                                     */
/******************************************************************************/

/* ----------------------------------------------------------------------------
|  UWL SIMPLE154 TX                                                           |
|                                                                              |
|  This task simply sends a packet to a remote node with two increasing IDs:        |
|  one for this node, the other to acknowledge the eventually received ID      |
 ---------------------------------------------------------------------------- */
TASK(UwlSend)
{
	int8_t retv;
	static uint8_t packet[CHAT_PACKET_SIZE];

	/* Set some payload constant bytes */
	memset(packet, 0, CHAT_PACKET_SIZE);
	packet[0] = 0x0A;
	packet[1] = 0x0B;
	packet[2] = 0x0C;
	packet[3] = 0x0D;
	packet[4] = 0x0E;
	packet[5] = 0x0F;
	/* Add tx_counter and ack number */
	packet[6] = tx_counter >> 8;
	packet[7] = tx_counter & 0x00FF;
	packet[8] = packet_ack >> 8;
	packet[9] = packet_ack & 0x00FF;
#ifndef USE_LCD_LOG
	STM_EVAL_LEDToggle(LED4);
#else
	GetResource(CONS_MUTEX);
	printf("PKT TX\r\n");
	ReleaseResource(CONS_MUTEX);
#endif
	/* Send chat packet */
	retv = uwl_simple154_send(packet, CHAT_PACKET_SIZE, uwl_destination_chat,
			USE_GTS);
	tx_counter++;
	
	if (retv < 0) {
		GetResource(CONS_MUTEX);
		printf("UwlSend: error SEND\r\n");
		ReleaseResource(CONS_MUTEX);
		/* NOTE: leds_blink() never returns!!!*/
		leds_blink();

	} else {
		tx_success++;
	}
}
/* ----------------------------------------------------------------------------
|  UWL SIMPLE154 RX                                                           |
|                                                                              |
|  This task is the receiving part of a 'chat' test application.               |
|  This simply check the packet sequence numbers.                              |
 ---------------------------------------------------------------------------- */
TASK(UwlReceive)
{

	/* Check some payload constant bytes */
	if (uwl_packet[0] != 0xAA || uwl_packet[1] != 0xBB ||
	    uwl_packet[2] != 0xCC || uwl_packet[3] != 0xDD ||
	    uwl_packet[4] != 0xEE || uwl_packet[5] != 0xFF) {

		GetResource(CONS_MUTEX);
		printf("UwlReceive: wrong packet type!\r\n");
		ReleaseResource(CONS_MUTEX);
#ifndef	USE_LCD_LOG
		STM_EVAL_LEDToggle(LED6);
#endif
		return;
	}

	packet_ack = uwl_packet[7];
	packet_ack += ((uint16_t) uwl_packet[6]) << 8;
	if (packet_ack != rx_counter)
		rx_seq_errors++;
	
	rx_counter = packet_ack;
	rx_counter++;

#ifndef USE_LCD_LOG
	STM_EVAL_LEDToggle(LED5);
#else
	GetResource(CONS_MUTEX);
	printf("PKT RX\r\n");
	ReleaseResource(CONS_MUTEX);
#endif

	GetResource(CONS_MUTEX);
	printf("\r\nUwlReceive:C ETX=%u  RX=%u ESEQ=%u\r\n",
			tx_counter - tx_success, rx_counter, rx_seq_errors);
	ReleaseResource(CONS_MUTEX);

	/* Activate the SEND task */
	ActivateTask(UwlSend);
}


/******************************************************************************/
/*                                   MAIN                                     */
/******************************************************************************/
int main(void)
{
	int8_t retv;
	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	SystemInit();
	
	/*Initialize Erika related stuffs*/
	EE_system_init();
	

#ifndef USE_LCD_LOG
	/*Initialize Leds. */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	
	STM_EVAL_LEDOff(LED3);
	STM_EVAL_LEDOff(LED4);
	STM_EVAL_LEDOff(LED5);
	STM_EVAL_LEDOff(LED6);
#endif

	/*Initialize the console device, either the LCD or the USART. */
	console_init();

	printf("Discovery board initialized!\r\n");

	/* Initialize the user button. */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

	printf("\r\nPress User Button to start C.\r\n");

	/*Wait the button pressing.*/
#ifdef	USE_LCD_LOG
	STM_EVAL_LEDOn(LED3);
#endif

	while (wait_button);


	/* Initialize the Network Stack */
	uwl_simple154_set_rx_callback(rx_data);

	retv = uwl_simple154_init_coordinator(
			UWL_COORD_ADDR,
			UWL_PANID,
			UWL_CHANNEL,
			UWL_BO,
			UWL_SO);

	if (retv < 0) {
		printf("\r\nS_154 error\ninit device\r\n");
		printf("ERROR = %d\r\n", retv);
		/* NOTE: this function never returns!!!*/
		leds_blink();
	}
	retv = uwl_simple154_gts_clear();
	if (retv < 0) {
		printf("\r\nS_154 error\nclear GTS\r\n");
		/* NOTE: leds_blink() never returns!!!*/
		leds_blink();
	}

	retv = uwl_simple154_gts_add(UWL_DEV_A_ADDR, UWL_DEV_GTS_LEN,
				     UWL_MAC_GTS_DIRECTION_OUT);
	if (retv < 0) {
		printf("\r\nS_154 error\nAdd GTS A\r\n");
		/* NOTE: this function never returns!!!*/
		leds_blink();
	}

	retv = uwl_simple154_gts_add(UWL_DEV_B_ADDR, UWL_DEV_GTS_LEN,
				     UWL_MAC_GTS_DIRECTION_OUT);
	if (retv < 0) {
		printf("\r\nS_154 error\nAdd GTS B\r\n");
		/* NOTE: this function never returns!!!*/
		leds_blink();
	}
	retv = uwl_simple154_gts_add(UWL_DEV_C_ADDR, UWL_DEV_GTS_LEN,
				     UWL_MAC_GTS_DIRECTION_OUT);
	if (retv < 0) {
		printf("\r\nS_154 error\nAdd GTS C\r\n");
		/* NOTE: this function never returns!!!*/
		leds_blink();
	}

	retv = uwl_simple154_gts_add(UWL_DEV_A_ADDR, UWL_DEV_GTS_LEN,
				     UWL_MAC_GTS_DIRECTION_IN);
	if (retv < 0) {
		printf("\r\nS_154 error\nAdd GTS A+\r\n");
		/* NOTE: this function never returns!!!*/
		leds_blink();
	}

	retv = uwl_simple154_gts_add(UWL_DEV_B_ADDR, UWL_DEV_GTS_LEN,
				     UWL_MAC_GTS_DIRECTION_IN);
	if (retv < 0) {
		printf("\r\nS_154 error\nAdd GTS B+\r\n");
		/* NOTE: this function never returns!!!*/
		leds_blink();
	}

	printf("Coordinator is ready!\r\n");

	/* Demo started */
	printf("Ok, let's go!\r\n");

#ifndef USE_LCD_LOG
	STM_EVAL_LEDOn(LED6);
#endif
	/* Forever loop: background activities (if any) should go here */
	for (;;) ;

	return 0;


}
