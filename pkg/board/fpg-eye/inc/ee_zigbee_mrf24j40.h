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
 
/** 
	@file ee_zigbee_mrf24j40.h 
	@brief MRF24J40 Zigbee tranceiver header file (board dependent file: XP2 CAMERA BOARD). 
	@author Dario Di Stefano
	@date 2010
*/

#ifndef __EE_ZIGBEE_MRF24J40_H__
#define __EE_ZIGBEE_MRF24J40_H__

/* Board-dependent macros */

#define EE_MRF24J40_GPIO_NAME_UC	MISC_GPIO
#define EE_MRF24J40_GPIO_NAME_LC	misc_gpio
#define EE_MRF24J40_BASE_ADDRESS	MISC_GPIO_BASE_ADDRESS
#define EE_MRF24J40_IRQ				MISC_GPIO_IRQ

// 	XP2 CAMERA BOARD:
//  LOCATE COMP "misc_gpioPIO_IO_0" SITE "75" ;     -> INT1 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_1" SITE "77" ;     -> INT2 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_2" SITE "82" ;     -> FIFOP 	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_3" SITE "76" ;     -> CN1 		(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_0" SITE "75" ;     -> ~INT1  	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_1" SITE "77" ;     -> ~INT2	(fpga input)
//  LOCATE COMP "misc_gpioPIO_IO_4" SITE "122";     -> DL3 		(fpga output)
//  LOCATE COMP "misc_gpioPIO_IO_5" SITE "86" ;     -> GP1 		(fpga output)
//  LOCATE COMP "misc_gpioPIO_IO_6" SITE "84" ;     -> CCA 		(fpga output)

#define EE_INT1_BIT 			(0) 
#define EE_INT2_BIT 			(1)
#define EE_FIFOP_BIT 			(2) 
#define EE_CN1_BIT 				(3)
#define EE_NOT_INT1_BIT 		(4)
#define EE_NOT_INT2_BIT			(5)
#define EE_DL3_BIT 				(0) 
#define EE_GP1_BIT 				(1)
#define EE_CCA_BIT 				(2) 

#define EE_INT1_MASK 			(0x0001) 
#define EE_INT2_MASK 			(0x0002)
#define EE_FIFOP_MASK 			(0x0004)
#define EE_CN1_MASK				(0x0008)
#define EE_NOT_INT1_MASK 		(0x0010) 
#define EE_NOT_INT2_MASK 		(0x0020)
#define EE_DL3_MASK				(0x0001) 
#define EE_GP1_MASK				(0x0002) 
#define EE_CCA_MASK				(0x0004)

#ifdef INT_POLARITY_HIGH
#define EE_INTPIN_MASK 			EE_INT2_MASK
#define EE_INTPIN_BIT 			EE_INT2_BIT
#else
#define EE_INTPIN_MASK 			EE_NOT_INT2_MASK
#define EE_INTPIN_BIT 			EE_NOT_INT2_BIT
#endif 

#define EE_MRF24J40_BOARD_FUNCTION(uc,lc) \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_hold_in_reset(void){ \
	cat3(EE_, lc, _write_bit_data)(0, EE_GP1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_release_reset(void){ \
	cat3(EE_, lc, _write_bit_data)(1, EE_GP1_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_write_output_pins(int val){ \
	cat3(EE_, lc, _write_data)(val); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_enable_IRQ(void){ \
	cat3(EE_, lc, _write_bit_irqMask)(1, EE_INTPIN_BIT); \
} \
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_disable_IRQ(void){ \
	cat3(EE_, lc, _write_bit_irqMask)(0, EE_INT2_BIT); \
	cat3(EE_, lc, _write_bit_irqMask)(0, EE_NOT_INT2_BIT); \
} \
__INLINE__ int __ALWAYS_INLINE__ EE_mrf24j40_gpio_IRQ_enabled(void){ \
	return (cat3(EE_, lc, _read_irqMask)() & EE_INTPIN_MASK); \
}

EE_MRF24J40_BOARD_FUNCTION(EE_MRF24J40_GPIO_NAME_UC, EE_MRF24J40_GPIO_NAME_LC)

/**
	@brief			This function is called before GPIO handler.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_IRQ_pre_stub(void){ 
}

/**
	@brief			This function is called after GPIO handler.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_IRQ_post_stub(void){ 
	while(1){ 
		if( (EE_misc_gpio_read_data() & EE_INTPIN_MASK) == 0 ) 
			break; 
	} 
} 

/**
	@brief			This function changes status of the WAKE pin in ACTIVE. (not yet supported)
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_wake_active(void){
}

/**
	@brief			This function changes status of the WAKE pin in INACTIVE. (not yet supported)
*/
__INLINE__ void __ALWAYS_INLINE__ EE_mrf24j40_gpio_wake_inactive(void){
}

#endif //__EE_ZIGBEE_MRF24J40_H__
