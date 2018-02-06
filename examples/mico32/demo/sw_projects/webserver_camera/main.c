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
/* lwIP */
#include <ee_lwip.h>

#include "lwip.h"
#include "httpd.h"
#include "hv7131gp.h"
#include "color_image.h"

extern volatile unsigned char camera_image_ready;
extern void process_frame(hv7131gp_status_t status);
extern unsigned char camera_image[];

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

int main(void)
{
	hv7131gp_status_t init_camera_status =  HV7131GP_SUCCESS;
    EE_led_set_all(0x01);
    
    /* Initialize PNG image */
    color_image_rgb2png_init();
    
    /* Initialize UART */
    EE_uart_config(115200, EE_UART_BIT8_NO | EE_UART_BIT_STOP_1);
    EE_uart_set_ISR_mode(EE_UART_POLLING | EE_UART_RXTX_BLOCK);
    
    /* Initialize lwIP */
    struct ip_addr my_ipaddr, netmask, gw;
    struct eth_addr my_ethaddr;
    IP4_ADDR(&my_ipaddr, MY_IPADDR_BYTE1, MY_IPADDR_BYTE2, MY_IPADDR_BYTE3,
        MY_IPADDR_BYTE4);
    IP4_ADDR(&netmask, MY_NETMASK_BYTE1, MY_NETMASK_BYTE2, MY_NETMASK_BYTE3,
        MY_NETMASK_BYTE4);
    IP4_ADDR(&gw, MY_GATEWAY_ADDR_BYTE1, MY_GATEWAY_ADDR_BYTE2,
        MY_GATEWAY_ADDR_BYTE3, MY_GATEWAY_ADDR_BYTE4);
    ETH_ADDR(&my_ethaddr, MY_ETHERNETIF_MAC_BYTE1, MY_ETHERNETIF_MAC_BYTE2,
        MY_ETHERNETIF_MAC_BYTE3, MY_ETHERNETIF_MAC_BYTE4,
        MY_ETHERNETIF_MAC_BYTE5, MY_ETHERNETIF_MAC_BYTE6);
    EE_lwip_init(&my_ipaddr, &netmask, &gw, &my_ethaddr);
    
    /* Let's start everything: interrupts drive the application */
    EE_mico32_enableIRQ();
    
    /* Configure the camera device */
    init_camera_status = hv7131gp_init();
    if (init_camera_status != HV7131GP_SUCCESS){
    	myprintf("hv7131gp_init %d \n\r",init_camera_status);
    	while(1);
    }
    
    init_camera_status = hv7131gp_configure_time_divisor(HV7131GP_T_1);
	if (init_camera_status != HV7131GP_SUCCESS)
	{
		myprintf("hv7131gp_configure_time_divisor %d \r\n",init_camera_status);
    	while(1);
	}

	init_camera_status = hv7131gp_configure_x_flip(0);
	if (init_camera_status != HV7131GP_SUCCESS)
	{
		myprintf("hv7131gp_configure_x_flip %d \r\n",init_camera_status);
    	while(1);
	}
	
	switch(PNG_IMG_WIDTH_DEFAULT){
		case 160:
			// Resolution 160 x 120 
			init_camera_status = hv7131gp_configure_subsampling(HV7131GP_1_16_SUB);
		break;
		case 320:
			// Resolution 320 x 240 
			init_camera_status = hv7131gp_configure_subsampling(HV7131GP_1_4_SUB);
		break;
		case 640:
			// Resolution 640 x 480 
			init_camera_status = hv7131gp_configure_subsampling(HV7131GP_NO_SUB);
		break;
		default:
			myprintf("resolution not supported \r\n");
    		while(1);
		break;
	}
	if (init_camera_status != HV7131GP_SUCCESS)
	{
		myprintf("hv7131gp_configure_subsampling %d \r\n",init_camera_status);
    	while(1);
	}
	
	/* Color */
	init_camera_status = hv7131gp_configure_color(1);
	if (init_camera_status != HV7131GP_SUCCESS)
	{
		myprintf("hv7131gp_configure_color %d \r\n",init_camera_status);
    	while(1);
	}
	
	httpd_init();

    while(1);
}
