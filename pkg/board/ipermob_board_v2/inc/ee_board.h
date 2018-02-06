

#ifndef __INCLUDE_EE_IPERMOB_BOARD_V2_H__
#define __INCLUDE_EE_IPERMOB_BOARD_V2_H__

#include "mcu/microchip_pic32/inc/ee_mcu.h"

#ifndef IPERMOB_BOARD_V2_VERSION
#define IPERMOB_BOARD_V2_VERSION 0
#endif

#if IPERMOB_BOARD_V2_VERSION == 0

__INLINE__ void __ALWAYS_INLINE__ EE_board_power_1V2_init(int on_off)
{
	TRISCbits.TRISC14 = 0;     /* pin configured as output */
	LATCbits.LATC14 = on_off;
}

#if defined __USE_LEDS__ 
__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void)
{
	TRISCCLR = 0x0C;
	LATCCLR = 0X04;
	LATCSET = 0X08;
}


#define IPERMOB_BOARD_V2_CAT3(x,y,z) x ## y ## z

/*NOTE: Led0 works in a negated logic.*/
#define EE_led_0_on	(LATCCLR = 0x08)
#define EE_led_1_on	(LATCSET = 0x04) 
#define EE_led_on(n)	IPERMOB_BOARD_V2_CAT3(EE_led_,n,_on)

/*NOTE: Led0 works in a negated logic.*/
#define EE_led_0_off	(LATCSET = 0x08)
#define EE_led_1_off	(LATCCLR = 0x04)
#define EE_led_off(n)	IPERMOB_BOARD_V2_CAT3(EE_led_,n,_off)

/*NOTE: Led0 works in a negated logic.*/
#define EE_led_0_toggle		(LATCINV = 0x08) 
#define EE_led_1_toggle		(LATCINV = 0x04)
#define EE_led_toggle(n)	IPERMOB_BOARD_V2_CAT3(EE_led_,n,_toggle)

__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void) 
{
	EE_led_0_on;
	EE_led_1_on;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void) 
{
	EE_led_0_off;
	EE_led_1_off;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_toggle(void) 
{
	EE_led_0_toggle;
	EE_led_1_toggle;
}

#endif	/* __USE_LEDS__ */

#ifdef __USE_BUTTONS__

//TODO: implement an interrupt driven version of the button driver.

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init(void)
{
	/* set BUTTON pins as inputs */
	TRISDbits.TRISD5 = 1;
	/* Enable Interrupt */
	// TODO
	/* Save callback */
	// TODO
}

#define EE_button_0_read	(PORTDbits.RD5)
#define EE_button_read(n)	EE_button_##n##_read


#endif /* __USE_BUTTONS__ */

#else 
#error "IPERMOB_MB_PIC32: Invalid board version."
#endif	/* IPERMOB_MB_PIC32_VERSION version selection */

#endif /* __INCLUDE_EE_IPERMOB_BOARD_V2_H__*/
