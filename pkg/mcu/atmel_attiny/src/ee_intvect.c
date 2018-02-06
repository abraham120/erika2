/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2016  Evidence Srl
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
 * Atmel ATTINY MCUs Interrupts vector.
 *
 * Author: 2017,  Giuseppe Serano
 */

/* I need ISR2 Stub */
#include "cpu/avr8/inc/ee_avr8_irqstub.h"

/* Erika Interrupt Vector Definition */

/* DUMMY interrupt vector */
EE_AVR8_ISR_NOT_DEFINED(BADISR_vect)

/* Interrupt Vector Table Recall. */
void EE_attiny_intvect(void) {
  EE_AVR8_REQUEST_IRQ_ENTRY(BADISR_vect);
}

/* INT0 interrupt vector */
#if defined(EE_AVR8_INT0_ISR) && (EE_AVR8_INT0_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(INT0_vect, EE_AVR8_INT0_ISR)
#elif defined(EE_AVR8_INT0_ISR) && (EE_AVR8_INT0_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(INT0_vect, EE_AVR8_INT0_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(INT0_vect)
#endif /* EE_AVR8_INT0_ISR */

/* PCINT0 interrupt vector */
#if defined(EE_AVR8_PCINT0_ISR) && (EE_AVR8_PCINT0_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(PCINT0_vect, EE_AVR8_PCINT0_ISR)
#elif defined(EE_AVR8_PCINT0_ISR) && (EE_AVR8_PCINT0_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(PCINT0_vect, EE_AVR8_PCINT0_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(PCINT0_vect)
#endif /* EE_AVR8_PCINT0_ISR */

/* PCINT1 interrupt vector */
#if defined(EE_AVR8_PCINT1_ISR) && (EE_AVR8_PCINT1_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(PCINT1_vect, EE_AVR8_PCINT1_ISR)
#elif defined(EE_AVR8_PCINT1_ISR) && (EE_AVR8_PCINT1_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(PCINT1_vect, EE_AVR8_PCINT1_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(PCINT1_vect)
#endif /* EE_AVR8_PCINT1_ISR */

/* PCINT2 interrupt vector */
#if defined(EE_AVR8_PCINT2_ISR) && (EE_AVR8_PCINT2_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(PCINT2_vect, EE_AVR8_PCINT2_ISR)
#elif defined(EE_AVR8_PCINT2_ISR) && (EE_AVR8_PCINT2_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(PCINT2_vect, EE_AVR8_PCINT2_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(PCINT2_vect)
#endif /* EE_AVR8_PCINT2_ISR */

/* WDT interrupt vector */
#if defined(EE_AVR8_WDT_ISR) && (EE_AVR8_WDT_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(WDT_vect, EE_AVR8_WDT_ISR)
#elif defined(EE_AVR8_WDT_ISR) && (EE_AVR8_WDT_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(WDT_vect, EE_AVR8_WDT_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(WDT_vect)
#endif /* EE_AVR8_WDT_ISR */

/* TIMER1_CAPT interrupt vector */
#if defined(EE_AVR8_TIMER1_CAPT_ISR) && (EE_AVR8_TIMER1_CAPT_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TIMER1_CAPT_vect, EE_AVR8_TIMER1_CAPT_ISR)
#elif defined(EE_AVR8_TIMER1_CAPT_ISR) && (EE_AVR8_TIMER1_CAPT_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TIMER1_CAPT_vect, EE_AVR8_TIMER1_CAPT_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TIMER1_CAPT_vect)
#endif /* EE_AVR8_TIMER1_CAPT_ISR */

/* TIMER1_COMPA interrupt vector */
#if defined(EE_AVR8_TIMER1_COMPA_ISR) && (EE_AVR8_TIMER1_COMPA_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TIMER1_COMPA_vect, EE_AVR8_TIMER1_COMPA_ISR)
#elif defined(EE_AVR8_TIMER1_COMPA_ISR) && (EE_AVR8_TIMER1_COMPA_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TIMER1_COMPA_vect, EE_AVR8_TIMER1_COMPA_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TIMER1_COMPA_vect)
#endif /* EE_AVR8_TIMER1_COMPA_ISR */

/* TIMER1_COMPB interrupt vector */
#if defined(EE_AVR8_TIMER1_COMPB_ISR) && (EE_AVR8_TIMER1_COMPB_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TIMER1_COMPB_vect, EE_AVR8_TIMER1_COMPB_ISR)
#elif defined(EE_AVR8_TIMER1_COMPB_ISR) && (EE_AVR8_TIMER1_COMPB_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TIMER1_COMPB_vect, EE_AVR8_TIMER1_COMPB_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TIMER1_COMPB_vect)
#endif /* EE_AVR8_TIMER1_COMPB_ISR */

/* TIMER1_OVF interrupt vector */
#if defined(EE_AVR8_TIMER1_OVF_ISR) && (EE_AVR8_TIMER1_OVF_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TIMER1_OVF_vect, EE_AVR8_TIMER1_OVF_ISR)
#elif defined(EE_AVR8_TIMER1_OVF_ISR) && (EE_AVR8_TIMER1_OVF_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TIMER1_OVF_vect, EE_AVR8_TIMER1_OVF_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TIMER1_OVF_vect)
#endif /* EE_AVR8_TIMER1_OVF_ISR */

/* TIMER0_COMPA interrupt vector */
#if defined(EE_AVR8_TIMER0_COMPA_ISR) && (EE_AVR8_TIMER0_COMPA_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TIMER0_COMPA_vect, EE_AVR8_TIMER0_COMPA_ISR)
#elif defined(EE_AVR8_TIMER0_COMPA_ISR) && (EE_AVR8_TIMER0_COMPA_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TIMER0_COMPA_vect, EE_AVR8_TIMER0_COMPA_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TIMER0_COMPA_vect)
#endif /* EE_AVR8_TIMER0_COMPA_ISR */

/* TIMER0_COMPB interrupt vector */
#if defined(EE_AVR8_TIMER0_COMPB_ISR) && (EE_AVR8_TIMER0_COMPB_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TIMER0_COMPB_vect, EE_AVR8_TIMER0_COMPB_ISR)
#elif defined(EE_AVR8_TIMER0_COMPB_ISR) && (EE_AVR8_TIMER0_COMPB_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TIMER0_COMPB_vect, EE_AVR8_TIMER0_COMPB_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TIMER0_COMPB_vect)
#endif /* EE_AVR8_TIMER0_COMPB_ISR */

/* TIMER0_OVF interrupt vector */
#if defined(EE_AVR8_TIMER0_OVF_ISR) && (EE_AVR8_TIMER0_OVF_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TIMER0_OVF_vect, EE_AVR8_TIMER0_OVF_ISR)
#elif defined(EE_AVR8_TIMER0_OVF_ISR) && (EE_AVR8_TIMER0_OVF_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TIMER0_OVF_vect, EE_AVR8_TIMER0_OVF_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TIMER0_OVF_vect)
#endif /* EE_AVR8_TIMER0_OVF_ISR */

/* ANA_COMP interrupt vector */
#if defined(EE_AVR8_ANA_COMP_ISR) && (EE_AVR8_ANA_COMP_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(ANA_COMP_vect, EE_AVR8_ANA_COMP_ISR)
#elif defined(EE_AVR8_ANA_COMP_ISR) && (EE_AVR8_ANA_COMP_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(ANA_COMP_vect, EE_AVR8_ANA_COMP_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(ANA_COMP_vect)
#endif /* EE_AVR8_ANA_COMP_ISR */

/* ADC interrupt vector */
#if defined(EE_AVR8_ADC_ISR) && (EE_AVR8_ADC_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(ADC_vect, EE_AVR8_ADC_ISR)
#elif defined(EE_AVR8_ADC_ISR) && (EE_AVR8_ADC_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(ADC_vect, EE_AVR8_ADC_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(ADC_vect)
#endif /* EE_AVR8_ADC_ISR */

/* USART0_START interrupt vector */
#if defined(EE_AVR8_USART0_START_ISR) && (EE_AVR8_USART0_START_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART0_START_vect, EE_AVR8_USART0_START_ISR)
#elif defined(EE_AVR8_USART0_START_ISR) && (EE_AVR8_USART0_START_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART0_START_vect, EE_AVR8_USART0_START_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART0_START_vect)
#endif /* EE_AVR8_USART0_START_ISR */

/* USART0_RX interrupt vector */
#if defined(EE_AVR8_USART0_RX_ISR) && (EE_AVR8_USART0_RX_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART0_RX_vect, EE_AVR8_USART0_RX_ISR)
#elif defined(EE_AVR8_USART0_RX_ISR) && (EE_AVR8_USART0_RX_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART0_RX_vect, EE_AVR8_USART0_RX_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART0_RX_vect)
#endif /* EE_AVR8_USART0_RX_ISR */

/* USART0_UDRE interrupt vector */
#if defined(EE_AVR8_USART0_UDRE_ISR) && (EE_AVR8_USART0_UDRE_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART0_UDRE_vect, EE_AVR8_USART0_UDRE_ISR)
#elif defined(EE_AVR8_USART0_UDRE_ISR) && (EE_AVR8_USART0_UDRE_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART0_UDRE_vect, EE_AVR8_USART0_UDRE_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART0_UDRE_vect)
#endif /* EE_AVR8_USART0_UDRE_ISR */

/* USART0_TX interrupt vector */
#if defined(EE_AVR8_USART0_TX_ISR) && (EE_AVR8_USART0_TX_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART0_TX_vect, EE_AVR8_USART0_TX_ISR)
#elif defined(EE_AVR8_USART0_TX_ISR) && (EE_AVR8_USART0_TX_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART0_TX_vect, EE_AVR8_USART0_TX_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART0_TX_vect)
#endif /* EE_AVR8_USART0_TX_ISR */

/* USART1_START interrupt vector */
#if defined(EE_AVR8_USART1_START_ISR) && (EE_AVR8_USART1_START_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART1_START_vect, EE_AVR8_USART1_START_ISR)
#elif defined(EE_AVR8_USART1_START_ISR) && (EE_AVR8_USART1_START_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART1_START_vect, EE_AVR8_USART1_START_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART1_START_vect)
#endif /* EE_AVR8_USART1_START_ISR */

/* USART1_RX interrupt vector */
#if defined(EE_AVR8_USART1_RX_ISR) && (EE_AVR8_USART1_RX_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART1_RX_vect, EE_AVR8_USART1_RX_ISR)
#elif defined(EE_AVR8_USART1_RX_ISR) && (EE_AVR8_USART1_RX_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART1_RX_vect, EE_AVR8_USART1_RX_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART1_RX_vect)
#endif /* EE_AVR8_USART1_RX_ISR */

/* USART1_UDRE interrupt vector */
#if defined(EE_AVR8_USART1_UDRE_ISR) && (EE_AVR8_USART1_UDRE_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART1_UDRE_vect, EE_AVR8_USART1_UDRE_ISR)
#elif defined(EE_AVR8_USART1_UDRE_ISR) && (EE_AVR8_USART1_UDRE_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART1_UDRE_vect, EE_AVR8_USART1_UDRE_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART1_UDRE_vect)
#endif /* EE_AVR8_USART1_UDRE_ISR */

/* USART1_TX interrupt vector */
#if defined(EE_AVR8_USART1_TX_ISR) && (EE_AVR8_USART1_TX_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USART1_TX_vect, EE_AVR8_USART1_TX_ISR)
#elif defined(EE_AVR8_USART1_TX_ISR) && (EE_AVR8_USART1_TX_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USART1_TX_vect, EE_AVR8_USART1_TX_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USART1_TX_vect)
#endif /* EE_AVR8_USART1_TX_ISR */

/* USI_START interrupt vector */
#if defined(EE_AVR8_USI_START_ISR) && (EE_AVR8_USI_START_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USI_START_vect, EE_AVR8_USI_START_ISR)
#elif defined(EE_AVR8_USI_START_ISR) && (EE_AVR8_USI_START_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USI_START_vect, EE_AVR8_USI_START_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USI_START_vect)
#endif /* EE_AVR8_USI_START_ISR */

/* USI_OVF interrupt vector */
#if defined(EE_AVR8_USI_OVF_ISR) && (EE_AVR8_USI_OVF_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(USI_OVF_vect, EE_AVR8_USI_OVF_ISR)
#elif defined(EE_AVR8_USI_OVF_ISR) && (EE_AVR8_USI_OVF_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(USI_OVF_vect, EE_AVR8_USI_OVF_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(USI_OVF_vect)
#endif /* EE_AVR8_USI_OVF_ISR */

/* TWI interrupt vector */
#if defined(EE_AVR8_TWI_ISR) && (EE_AVR8_TWI_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(TWI_vect, EE_AVR8_TWI_ISR)
#elif defined(EE_AVR8_TWI_ISR) && (EE_AVR8_TWI_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(TWI_vect, EE_AVR8_TWI_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(TWI_vect)
#endif /* EE_AVR8_TWI_ISR */

/* EE_READY interrupt vector */
#if defined(EE_AVR8_EE_READY_ISR) && (EE_AVR8_EE_READY_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(EE_READY_vect, EE_AVR8_EE_READY_ISR)
#elif defined(EE_AVR8_EE_READY_ISR) && (EE_AVR8_EE_READY_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(EE_READY_vect, EE_AVR8_EE_READY_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(EE_READY_vect)
#endif /* EE_AVR8_EE_READY_ISR */

/* QTRIP interrupt vector */
#if defined(EE_AVR8_QTRIP_ISR) && (EE_AVR8_QTRIP_ISR_CAT == 2)
EE_AVR8_ISR2_DEFINITION(QTRIP_vect, EE_AVR8_QTRIP_ISR)
#elif defined(EE_AVR8_QTRIP_ISR) && (EE_AVR8_QTRIP_ISR_CAT == 1)
EE_AVR8_ISR1_DEFINITION(QTRIP_vect, EE_AVR8_QTRIP_ISR)
#elif defined(__MCU_EXTENDED_STATUS__)
EE_AVR8_ISR_NOT_DEFINED(QTRIP_vect)
#endif /* EE_AVR8_QTRIP_ISR */
