#ifndef __INCLUDE_EE_BOARD_H__
#define __INCLUDE_EE_BOARD_H__

#include "mcu/microchip_pic32/inc/ee_mcu.h"

#ifndef IPERMOB_MB_PIC32_VERSION
#define IPERMOB_MB_PIC32_VERSION 0
#endif

#if IPERMOB_MB_PIC32_VERSION == 0



#if (defined __USE_LEDS__) && (!defined __SENSYS_BOARD__) 
__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void)
{
	TRISECLR = 0x0F;
	LATECLR = 0X0F;
}

#define MB_PIC32_CAT3(x,y,z) x ## y ## z

#define EE_led_0_on	(LATESET = 0x01)
#define EE_led_1_on	(LATESET = 0x02)
#define EE_led_2_on	(LATESET = 0x04)
#define EE_led_3_on	(LATESET = 0x08)
#define EE_led_on(n)	MB_PIC32_CAT3(EE_led_,n,_on)

#define EE_led_0_off	(LATECLR = 0x01)
#define EE_led_1_off	(LATECLR = 0x02)
#define EE_led_2_off	(LATECLR = 0x04)
#define EE_led_3_off	(LATECLR = 0x08)
#define EE_led_off(n)	MB_PIC32_CAT3(EE_led_,n,_off)

#define EE_led_0_toggle		(LATEINV = 0x01)
#define EE_led_1_toggle		(LATEINV = 0x02)
#define EE_led_2_toggle		(LATEINV = 0x04)
#define EE_led_3_toggle		(LATEINV = 0x08)
#define EE_led_toggle(n)	MB_PIC32_CAT3(EE_led_,n,_toggle)

__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void) 
{
	EE_led_0_on;
	EE_led_1_on;
	EE_led_2_on;
	EE_led_3_on;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void) 
{
	EE_led_0_off;
	EE_led_1_off;
	EE_led_2_off;
	EE_led_3_off;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_toggle(void) 
{
	EE_led_0_toggle;
	EE_led_1_toggle;
	EE_led_2_toggle;
	EE_led_3_toggle;
}

#elif (defined __USE_LEDS__) && (defined __SENSYS_BOARD__) 

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void)
{
	TRISBCLR = 0x300;
	LATBCLR = 0X300;
}

#define SB_PIC32_CAT3(x,y,z) x ## y ## z

#define EE_led_0_on	(LATBSET = 0x100)
#define EE_led_1_on	(LATBSET = 0x200)
#define EE_led_on(n)	SB_PIC32_CAT3(EE_led_,n,_on)

#define EE_led_0_off	(LATBCLR = 0x100)
#define EE_led_1_off	(LATBCLR = 0x200)

#define EE_led_off(n)	SB_PIC32_CAT3(EE_led_,n,_off)

#define EE_led_0_toggle		(LATBINV = 0x100)
#define EE_led_1_toggle		(LATBINV = 0x200)
#define EE_led_toggle(n)	SB_PIC32_CAT3(EE_led_,n,_toggle)

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

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init(void)
{
	/* set BUTTON pins as inputs */
	TRISCbits.TRISC1 = 1;
	TRISCbits.TRISC2 = 1;
	TRISCbits.TRISC3 = 1;
	TRISCbits.TRISC4 = 1;
	/* Enable Interrupt */
	// TODO
	/* Save callback */
	// TODO
}

#define EE_button_0_read	(PORTCbits.RC1)
#define EE_button_1_read	(PORTCbits.RC2)
#define EE_button_2_read	(PORTCbits.RC4)
#define EE_button_3_read	(PORTCbits.RC3)
#define EE_button_read(n)	EE_button_##n##_read

/*
 //Button

 //Raw, latched and debounced

 extern void (*EE_button_callback)(void); // Not used for now

 //  Callback = NULL
 __INLINE__ void __ALWAYS_INLINE__ EE_button_init(uint8 button_name, void(*isr_callback)(void), EE_UINT8 mask )
 {

 }

 void EE_button_setup(uint8 button_name, uint8 mode) // button_name =  functional name of button, mode = RAW

 void EE_button_control(uint8 button_name, unit8 param, uint8 value) // not used

 EE_UINT8 EE_button_read(uint8 button_name) // button_name =  functional name of button
 */

#endif /* __USE_BUTTONS__ */

#else 
#error "IPERMOB_MB_PIC32: Invalid board version."
#endif	/* IPERMOB_MB_PIC32_VERSION version selection */

#endif /* __INCLUDE_EE_BOARD_H__ */
