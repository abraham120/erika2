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

/*
 * Author: 2006 Antonio Romano 
 * CVS: $Id: handlerinstall.S,v 1.1 2006/07/11 09:16:42 pj Exp $
 */


#include "mcu/atmega128/inc/ee_irqstub.S"


// vector table
// 1 external interrupt request 0
// 2 external interrupt request 1
// 3 external interrupt request 2
// 4 external interrupt request 3
// 5 external interrupt request 4
// 6 external interrupt request 5
// 7 external interrupt request 6
// 8 external interrupt request 7
// 9  Timer/Counter 2 Compare Match
// 10 Timer/Counter 2 Overflow
// 11 Timer/Counter 1 Capture Event
// 12 Timer/Counter 1 Compare Match A
// 13 Timer/Counter 1 Compare Match B
// 14 Timer/Counter 1 Overflow
// 15 Timer/Counter 0 Compare Match
// 16 timer/Counter 0 Overflow
// 17 SPI Serial Transfer Complete
// 18 USART0 Rx complete
// 19 USART0 Data Register Empty
// 20 Usart0 Tx complete
// 21 ADC Conversion Complete
// 22 EEPROM Ready
// 23 Analog Comparator
// 24 Timer/Counter 1 Compare Match C
// 25 Timer/Counter 3 Capture Event
// 26 Timer/Counter 3 Compare Match A
// 27 Timer/Counter 3 Compare Match B
// 28 Timer/Counter 3 Compare Match C
// 29 Timer/Counter 3 Overflow
// 30 USART1 Rx Complete
// 31 USART1 Data Register Empty
// 32 USART1 Tx Complete
// 33 Two-wire serial Interface
// 34 Store program Memory Ready











// external interrupt int0
.global __vector_8
__vector_8 :
.global __vector_7
__vector_7 :
		EE_ISR2_HANDLER_STUB ee_isr2h1, ASMstub1
		reti	


// timer/counter0 overflow interrupt			

.global __vector_16
__vector_16 :
		EE_ISR2_HANDLER_STUB ee_isr2h2, ASMstub2
		reti	

// timer/counter2 overflow interrupt

.global __vector_10
__vector_10 :
		EE_ISR2_HANDLER_STUB ee_isr2h3, ASMstub3
		reti	

// timer/counter1 overflow interrupt			

.global __vector_14
__vector_14 :
		EE_ISR2_HANDLER_STUB ee_isr2h4, ASMstub4
		reti	

// timer/counter3 overflow interrupt		
			
.global __vector_29
__vector_29 :
		EE_ISR2_HANDLER_STUB ee_isr2h5, ASMstub5
		reti	
			
			

