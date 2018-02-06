#include<stdio.h>
#include <stdarg.h>
#include "MicoUart.h"
#include "MicoGPIO.h"
#include "MicoInterrupts.h"
#include "MicoTimer.h"
#include "system_conf.h"

#define SWAP

MicoGPIO_t *pin = (MicoGPIO_t*)MISC_GPIO_BASE_ADDRESS;
MicoUart_t *uartc = (MicoUart_t *)UART_BASE_ADDRESS;
MicoTimer_t *freetimerc = (MicoTimer_t *)FREETIMER_BASE_ADDRESS;

#ifdef SWAP
unsigned int swap(unsigned int word)
{
	unsigned int xw;
	unsigned char* x = (unsigned char*)&xw;
	x[0] = ((unsigned char*)&word)[3];
	x[1] = ((unsigned char*)&word)[2];
	x[2] = ((unsigned char*)&word)[1];
	x[3] = ((unsigned char*)&word)[0];
	return xw;
}
#else
unsigned int swap(unsigned int word)
{
	return word;	
}
#endif


unsigned int elapsed(unsigned int from, unsigned int to)
{
	/* Timers are decrementing */
	return from - to;
}

unsigned int get_time_stamp(void)
{
	return freetimerc->Snapshot;
}

static void msleep(unsigned int ms)
{
	unsigned int start, curr;
	start = get_time_stamp();
	do {
		curr = get_time_stamp();
	} while (elapsed(start, curr) < (ms * (unsigned int)(CPU_FREQUENCY / 1000)));
}


void put_byte(unsigned char msg)
{
    uartc->lcr = 0x3; // 8N1
        while (! (uartc->lsr & MICOUART_LSR_TX_RDY_MASK))
            ;
    uartc->rxtx = msg;
}

void uart_send_buffer(char *str, unsigned int len)
{
	while(len--)
		put_byte(*str++);
}

void uart_print_bit(unsigned int str)
{
	unsigned char count = 31;
	
	while(count--){
		if (str & 0x80000000)
			put_byte('1');
		else
			put_byte('0');
		str <<= 1;
	}
	put_byte('\r');
	put_byte('\n');
}


/* A printf-like function */
void myprintf(const char *format, ...)
{
#define MAXCHARS 128
    const char printf_trunc[] = "..[TRUNCATED]..\r\n";
    char str[MAXCHARS];
    int len;
    va_list args;
    va_start(args, format);
    len = vsnprintf(str, MAXCHARS, format, args);
    va_end(args);
    if (len > MAXCHARS - 1) {
        /* vsnptintf() returns the number of characters needed */
        uart_send_buffer(str, MAXCHARS - 1 );
        uart_send_buffer(printf_trunc, sizeof(printf_trunc) - 1);
    } else {
        uart_send_buffer(str, len);
    }
}

/*
typedef struct st_MicoGPIO_t{
        volatile unsigned int data;
        volatile unsigned int tristate;
        volatile unsigned int irqMask;
        volatile unsigned int edgeCapture; 
 }MicoGPIO_t;
 */
void handler_irq_gpio(int i, void* pun)
{
	put_byte('B');
	pin->edgeCapture = 0;	
}

void LatticeDDInit(void)
{
	MicoRegisterISR(2, NULL, handler_irq_gpio);
	MicoEnableInterrupt(2);
	pin->tristate = 0x00000000;
	pin->irqMask = swap(0x00000020);
 	put_byte('A');
	myprintf("Hello World\n");
	while(1){
		//pin->irqMask = swap(0x00000020);
		msleep(1000);
		pin->data = swap(0x00000002);
		msleep(1000);
		pin->data = swap(0x00000000);		
	}
}
