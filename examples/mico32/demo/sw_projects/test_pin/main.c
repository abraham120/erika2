/*
 * Copyright: 2010, Evidence Srl
 * Author: Alessandro Paolinelli
 * Description: Web Server with camera support.
 */

/* RT-Kernel */
#include <ee.h>
/* Erika Mico32 interrupts */
#include <ee_irq.h>
/* Platform description */
#include <system_conf.h>
/* Standard library */
#include <stdio.h>
#include <stdarg.h>
#include <MicoMacros.h>


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
        EE_uart_send_buffer(str, MAXCHARS - 1 );
        EE_uart_send_buffer(printf_trunc, sizeof(printf_trunc) - 1);
    } else {
        EE_uart_send_buffer(str, len);
    }
}

MicoGPIO_t* pin = (MicoGPIO_t*)MISC_GPIO_BASE_ADDRESS;
EE_gpio_st gpio_p;

static MicoUart_t * const uartc = (MicoUart_t *)UART_BASE_ADDRESS;

void put_byte(unsigned char msg)
{
    uartc->lcr = 0x3; // 8N1
        while (! (uartc->lsr & MICOUART_LSR_TX_RDY_MASK))
            ;
    uartc->rxtx = msg;
}

void myISRcallback(void)
{
	put_byte('B');
	while(1);
}

int main(void)
{
	gpio_p.data_copy = 0;

    /* Let's start everything: interrupts drive the application */
    EE_mico32_enableIRQ();
    
    EE_misc_gpio_write_data(0x0);
    EE_misc_gpio_set_IRQ_callback(&myISRcallback);
    EE_misc_gpio_write_irqMask(0xFF000000);
    EE_misc_gpio_write_data(0x02000000);
    
    while(1);
    
	while(1){
		EE_misc_gpio_write_bit_data(1, 1);
		//EE_hal_gpio_output_write_mask_data(pin, 2, 2, &gpio_p);
		//EE_hal_gpio_output_write_bit_data(pin, 1, 1, &gpio_p);
		//EE_hal_gpio_output_write_data(pin, 2, &gpio_p);
		//EE_hal_gpio_output_write_data_internal(pin, 2, &gpio_p);
		//EE_hal_gpio_write_data(pin, 2);	
		myprintf("hv7131gp_configure_x_flip 2\r\n");
		myprintf("%d\r\n", EE_hal_gpio_output_read_data_out(&gpio_p));
		EE_hal_gpio_output_write_mask_data(pin, 0, 2, &gpio_p);
		//EE_hal_gpio_output_write_bit_data(pin, 0, 1, &gpio_p);
		//EE_hal_gpio_output_write_data(pin, 0, &gpio_p);
		//EE_hal_gpio_output_write_data_internal(pin, 0, &gpio_p);
		//EE_hal_gpio_write_data(pin, 0);
		myprintf("hv7131gp_configure_x_flip 0\r\n");
		myprintf("%d\r\n", EE_hal_gpio_output_read_data_out(&gpio_p));
	}
    return 0;
}
