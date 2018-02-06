#ifndef __INCLUDE_EE_BOARD_H__
#define __INCLUDE_EE_BOARD_H__

#include "mcu/microchip_pic32/inc/ee_mcu.h"

#ifndef IPERMOB_DB_PIC32_VERSION
#define IPERMOB_DB_PIC32_VERSION 0
#endif

#if IPERMOB_DB_PIC32_VERSION == 0

#ifdef __USE_LEDS__
__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void) 
{
	TRISDCLR = 0x3CB0;
	LATDCLR = 0x3CB0;
	TRISFCLR = 0x0001;
	LATFCLR = 0x00001;
}

/* This macro allows the argument of EE_led_XXX() to be a macro */
#define DB_PIC32_CAT3(x,y,z) x ## y ## z

#define EE_led_0_on		(LATDSET = 0x0010)
#define EE_led_1_on		(LATDSET = 0x0020)
#define EE_led_2_on		(LATDSET = 0x0080)
#define EE_led_3_on		(LATFSET = 0x0001)
#define EE_led_4_on		(LATDSET = 0x0400)
#define EE_led_5_on		(LATDSET = 0x0800)
#define EE_led_6_on		(LATDSET = 0x1000)
#define EE_led_7_on		(LATDSET = 0x2000)
#define EE_led_on(n)		DB_PIC32_CAT3(EE_led_,n,_on)

#define EE_led_0_off		(LATDCLR = 0x0010)
#define EE_led_1_off		(LATDCLR = 0x0020)
#define EE_led_2_off		(LATDCLR = 0x0080)
#define EE_led_3_off		(LATFCLR = 0x0001)
#define EE_led_4_off		(LATDCLR = 0x0400)
#define EE_led_5_off		(LATDCLR = 0x0800)
#define EE_led_6_off		(LATDCLR = 0x1000)
#define EE_led_7_off		(LATDCLR = 0x2000)
#define EE_led_off(n)		DB_PIC32_CAT3(EE_led_,n,_off)

#define EE_led_0_toggle		(LATDINV = 0x0010)
#define EE_led_1_toggle		(LATDINV = 0x0020)
#define EE_led_2_toggle		(LATDINV = 0x0080)
#define EE_led_3_toggle		(LATFINV = 0x0001)
#define EE_led_4_toggle		(LATDINV = 0x0400)
#define EE_led_5_toggle		(LATDINV = 0x0800)
#define EE_led_6_toggle		(LATDINV = 0x1000)
#define EE_led_7_toggle		(LATDINV = 0x2000)
#define EE_led_toggle(n)	DB_PIC32_CAT3(EE_led_,n,_toggle)

__INLINE__ void __ALWAYS_INLINE__ EE_leds_on(void) 
{
	EE_led_0_on;
	EE_led_1_on;
	EE_led_2_on;
	EE_led_3_on;
	EE_led_4_on;
	EE_led_5_on;
	EE_led_6_on;
	EE_led_7_on;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_off(void) 
{
	EE_led_0_off;
	EE_led_1_off;
	EE_led_2_off;
	EE_led_3_off;
	EE_led_4_off;
	EE_led_5_off;
	EE_led_6_off;
	EE_led_7_off;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds_toggle(void) 
{
	EE_led_0_toggle;
	EE_led_1_toggle;
	EE_led_2_toggle;
	EE_led_3_toggle;
	EE_led_4_toggle;
	EE_led_5_toggle;
	EE_led_6_toggle;
	EE_led_7_toggle;
}

#endif	/* __USE_LEDS__ */

#else 
#error "IPERMOB_DB_PIC32: Invalid board version."
#endif	/* IPERMDB_DB_PIC32_VERSION version selection */


#endif /* __INCLUDE_EE_BOARD_H__ */
