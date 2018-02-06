
/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2011  Evidence Srl
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
 
 /** 
    @file      main.c
    @author    Salvatore Marrapese
    @date      2012
*/

#pragma config POSCMOD = HS
#pragma config FNOSC = PRIPLL
#pragma config FPLLMUL = MUL_20
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLODIV = DIV_1
#pragma config FPBDIV = DIV_1	/* SYSCLK = 80MHz, PBCLK = 80MHz */
#pragma config FWDTEN = OFF

#include "ee.h"
#include "string.h"
#include <stdio.h>
#include "util.h"
#include "console_serial.h"
#include "mcu/microchip_pic32/inc/ee_uart.h"
#include "ov9650.h"

/* UART RX Flag. */
#define UART_RX_FLAG  IFS2bits.U1BRXIF

/* Camera Definitions */
#define OV9650_COLOR_MODE_ON 	1
#define OV9650_COLOR_MODE_OFF 	0

/* Console definitions */
#define MY_FIRST_CONSOLE 		0
#define MY_DEBUG_CONSOLE		1
#define TICK_PERIOD 			1000
#define CONSOLE_ID 				0
#define CONSOLE_ERROR 			1

/* eDAC needs this image resolution */
#define FRAME_WIDTH 			160
#define FRAME_HEIGHT 			120
#define COLOR_MODE  			OV9650_COLOR_MODE_ON

/* The camera get always an image with colour */
#define FRAME_SIZE 				FRAME_WIDTH * FRAME_HEIGHT * (COLOR_MODE + 1)

/* Buffer data image  */
EE_UINT8 frame_buffer[FRAME_SIZE];

/* Parser variables */
volatile uint8_t done = 0;
volatile uint8_t image_dump = 0;

void delay_sec (EE_UINT32 seconds) {	
	EE_UINT32 milliseconds = seconds * 1000;
	int i;
	for (i = 0; i < milliseconds; i++)
		EE_delay_us(1000);
}

static void error(int err_value)
{
	int i;
	char str[30];
	
	if (err_value > CONSOLE_ERROR) {
		sprintf(str, "Err:=%d\n\r", err_value);
		console_write(CONSOLE_ID, str, strlen(str));
	}
	while(1) {
		for (i = 0; i < 10000; i++){
			delay_sec(1);
			EE_leds_toggle();
		}
	}
}

static void process_frame(ov9650_status_t status)
{
	EE_led_on(1);
	ActivateTask(process_image);
	done = 1;
}

void handshake_edaq(void)
{
	const unsigned char ack = 0x31;
	int16_t dummy = 0;
	unsigned char buff[20];

	while (1) {
		while (!UART_RX_FLAG) ;
		UART_RX_FLAG = 0;
		console_read(0, buff, 1, &dummy);
		if (buff[0] == ack) {
			console_write(0, (unsigned char *) &ack, 1);
			return;
		}
	}
}

static void send_data(void)
{
	unsigned char header[3] = {0xAA, 0xBB, 0xCC};
	unsigned char m_2byte[2];
	EE_UINT32 w, h, y , l;
	unsigned int s;
	volatile unsigned int dh = 0;
	volatile unsigned int dl = 0;

	l = 0;
	y = 120;
	w = ov9650_get_width();
	h = ov9650_get_height();
	s = ov9650_get_size();

	// Send header	
	console_write(0, header, 3);

	// Send width
	m_2byte[0] = ((unsigned int) w >> 8) & 0xFF;
	m_2byte[1] = ((unsigned int) w) & 0xFF;
	console_write(0, m_2byte, 2);
	// Send Height
	m_2byte[0] = 0x00;
	m_2byte[1] = ((unsigned int) h) & 0xFF;
	console_write(0, m_2byte, 2);
	// Send Frame duration (part 1)
	m_2byte[0] = ((unsigned int) dh >> 8) & 0xFF;
	m_2byte[1] = ((unsigned int) dh) & 0xFF;
	console_write(0, m_2byte, 2);
	// Send Frame duration (part 2)
	m_2byte[0] = ((unsigned int) dl >> 8) & 0xFF;
	m_2byte[1] = ((unsigned int) dl     ) & 0xFF;
	console_write(0, m_2byte, 2);
	// Send Frame lost
	m_2byte[0] = ((unsigned int) l	 >> 8) & 0xFF;
	m_2byte[1] = ((unsigned int) l	     ) & 0xFF;
	console_write(0, m_2byte, 2);
	// Send Y mean value
	m_2byte[0] = ((unsigned int) y >> 8) & 0xFF;
	m_2byte[1] = ((unsigned int) y     ) & 0xFF;
	console_write(0, m_2byte, 2);
	
	// Send Image
	int i;
	uint8_t dato;
	uint8_t image_dump_temp;

	image_dump_temp = image_dump;
	for (i = 0; i < FRAME_SIZE; i += 2) {	
		//dato = inv(frame_buffer[i]);
		dato = frame_buffer[i];
		console_write(0, &(dato), 1);
		if (image_dump_temp == 1) {
			myprintf("%d",  (dato / 100));
			myprintf("%d",  (dato % 100) / 10);
			myprintf("%d ", (dato % 10));
			if (!(i%10)) myprintf("\r\n");
		}
	}

	if (image_dump == 1){
		image_dump = 0;
	}

	memset(frame_buffer, 255, FRAME_SIZE);
	EE_leds_toggle();
}

uint8_t get_hex(uint8_t data)
{
	if (data <= 'F' && data >= 'A')
		data = data - 'A' + 10;
	else if (data <= 'f' && data >= 'a')
		data = data - 'a' + 10;
	else if (data <= '9' && data >= '0')
		data = data - '0';
	
	return data;
}

uint8_t is_hex(uint8_t data)
{
	if (data <= (uint8_t)'F' && data >= (uint8_t)'A')
		return 0;
	else if (data <= (uint8_t)'f' && data >= (uint8_t)'a')
		return 0;
	else if (data <= (uint8_t)'9' && data >= (uint8_t)'0')
		return 0;
	else return 0xFF;
}

static uart_init_port2A (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode)
{
	// Stop UART port
	U2AMODEbits.UARTEN = 0;

	// Disable Interrupts
	EE_UART_PORT2A_RX_INT_ENABLE = 0;
	EE_UART_PORT2A_TX_INT_ENABLE = 0;
	EE_UART_PORT2A_ERR_INT_ENABLE = 0;

	// Reset Interrupt Flags
	EE_UART_PORT2A_RX_INT_FLAG = 0;
 	EE_UART_PORT2A_TX_INT_FLAG = 0;
	EE_UART_PORT2A_ERR_INT_FLAG = 0;

	// Choice between the two available divisors
	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
		U2ABRG  = ((EE_get_peripheral_clock() / (16 * baud))) - 1;
	}
	else {
		U2ABRG  = ((EE_get_peripheral_clock() / (4 * baud))) - 1;
	}

	// Mode Register Reset
	U2AMODE = 0;

	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
		U2AMODEbits.BRGH = 0;
	else
		U2AMODEbits.BRGH = 1;

	// Setup and port start
	U2AMODEbits.UARTEN = 1;

	if ((mode & EE_UART_CTRL_MASK) == EE_UART_CTRL_FLOW) {
		U2AMODEbits.RTSMD = 1;
		U2AMODEbits.UEN = 0x10;
	} else {
		U2AMODEbits.RTSMD = 0;
		U2AMODEbits.UEN = 0;
	}

	U2AMODE |= byte_format & 0x07;	// Number of bit, Parity and Stop bits

	// Status bits
	U2ASTA = 0;			// TX & RX interrupt modes
	U2ASTAbits.UTXEN = 0; //Enable Transmission
	U2ASTAbits.URXEN = 1; //Enable Receiver
	return EE_UART_NO_ERROR;
}

uint8_t read_num(void)
{
	uint8_t data_h, data_l;
	// MSB
	do {
		while (EE_uart_read_byte(EE_UART_PORT_2A, &data_h) != EE_UART_NO_ERROR)
			;
	} while (is_hex(data_h));

	EE_uart_write_byte(EE_UART_PORT_2B, data_h);
	// LSB
	do {
		while (EE_uart_read_byte(EE_UART_PORT_2A, &data_l) != EE_UART_NO_ERROR)
			;
	} while (is_hex(data_l));

	EE_uart_write_byte(EE_UART_PORT_2B, data_l);
	EE_uart_write_byte(EE_UART_PORT_2B, '\r');
	EE_uart_write_byte(EE_UART_PORT_2B, '\n');

	return (get_hex(data_h) * 16 + get_hex(data_l));
}

/* ************************************************************************** */
/*                                  TASKS                                     */
/* ************************************************************************** */
TASK(process_image)
{
	send_data();
	if (ov9650_capture(frame_buffer, process_frame) != OV9650_SUCCESS){
		error(20);
	}
}

/* Console for debug and output image data. */
console_descriptor_t *my_console_uart;
console_descriptor_t *my_debug_uart_tx;
console_descriptor_t *my_debug_uart_rx;

int main(void)
{
	EE_system_init();
    EE_leds_init();

	EE_timer_soft_init(EE_TIMER_1, TICK_PERIOD); // TOGLIMI SE NO PERIODIC TASK
	EE_timer_start(EE_TIMER_1); // TOGLIMI SE NO PERIODIC TASK

    /* 
	 * Initialize Console:
	 * the parameters of the uart are specified in the file until.h 
	 */
    my_console_uart = console_serial_config(MY_FIRST_SERIAL, UART_BAUDRATE,
    					CONSOLE_SERIAL_FLAG_BIT8_NO |
    					CONSOLE_SERIAL_FLAG_BIT_STOP1);
    console_init(MY_FIRST_CONSOLE, my_console_uart);

	my_debug_uart_tx = console_serial_config(MY_DEBUG_SERIAL_TX, UART_BAUDRATE,
    					CONSOLE_SERIAL_FLAG_BIT8_NO |
    					CONSOLE_SERIAL_FLAG_BIT_STOP1);
    console_init(MY_DEBUG_CONSOLE_TX, my_debug_uart_tx);

	uart_init_port2A (115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1,
		     EE_UART_CTRL_SIMPLE);

    if (console_open(MY_FIRST_CONSOLE) < 0) {
    	for (;;) {
			msleep(100);
			EE_led_toggle(0);;
		}
    }

	if (console_open(MY_DEBUG_CONSOLE_TX) < 0) {
    	for (;;) {
			msleep(100);
			EE_led_toggle(1);;
		}
    }

	handshake_edaq();

	if (ov9650_init() != OV9650_SUCCESS) {
		while (1) {
			/* Something went wrong. */
			msleep(500);
			EE_led_toggle(0);
		}
	}

	if (ov9650_init_configure()!= OV9650_SUCCESS) {
			while (1) {
			/* Something went wrong. */
			msleep(500);
			EE_led_toggle(0);
		}
	}

	if (ov9650_capture(frame_buffer, process_frame) != OV9650_SUCCESS)
		error(2);

	while (1) {
		uint8_t num;
		uint8_t addr;
		uint8_t value;

		myprintf("menu> \r\n");
		myprintf("01) set register\r\n");
		myprintf("02) get register\r\n");
		myprintf("03) get registers configuration\r\n");
		myprintf("04) Image dump\r\n");
		myprintf("> ");

		num = read_num();
		if (num > 4) {
			myprintf("\r\n");
			continue;
		}

		switch (num) {
			case 1:
				myprintf("\taddr register >");
				addr = read_num();
				myprintf("\r\n");
				if (addr > 0xAA) {
					myprintf("\tAddress register out range\r\n");
					continue;
				}
				myprintf("\tvalue to write >");
				value = read_num();
				myprintf("\r\n");
				ov9650_i2c_hal_reg_write(addr, value);
				myprintf("\tdone.\r\n");
				break;
			case 2:
				myprintf("\taddr register >");
				addr = read_num();
				myprintf("\r\n");
				ov9650_i2c_hal_reg_read(addr, &value);
				myprintf("\tvalue = 0x%X\r\n", value);
				myprintf("\tdone.\r\n");
				break;
			case 3:
				myprintf("\tdump register configuration >\r\n");
				myprintf("\t<addr_reg>\t<value_reg>(press a key): ...");
				IFS1bits.U2ARXIF = 0;
				while (!IFS1bits.U2ARXIF);
				myprintf("\r\n");
				for (addr = 0x00; addr < 0xAA; addr++){
					ov9650_i2c_hal_reg_read(addr, &value);
					myprintf("\t0x%X\t0x%X\r\n", addr, value);
				}
				myprintf("\tdone.\r\n");
				break;
			case 4:
				myprintf("\tpress key to start download >\r\n");
				IFS1bits.U2ARXIF = 0;
				while (!IFS1bits.U2ARXIF);
				image_dump = 1;
				break;
		}
	}

	return 0;
}
