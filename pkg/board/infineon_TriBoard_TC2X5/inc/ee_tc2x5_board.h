/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

 /** @file   ee_tc2x5_board.h
  *  @brief  Board-dependent part of API
  *  @author Errico Guidieri
  *  @date 2012
  */
#ifndef INCLUDE_EE_TC2X5_BOARD_H__
#define INCLUDE_EE_TC2X5_BOARD_H__

/* This file have to be included after all API have been */

/* TriBoard 2x5 default clock frequency (20MHz) */
#define EE_TRIBOARD_2X5_FOSC    20000000U
/* Interface Board Oscillator Frequency Define */
#define EE_TC2YX_BOARD_FOSC     EE_TRIBOARD_2X5_FOSC
/* Interface Board Oscillator Frequency Define */
#define EE_TC27X_BOARD_FOSC     EE_TRIBOARD_2X5_FOSC

enum EE_tc2x5_led_id {
  EE_TRIBOARD_2X5_NO_LEDS = 0x00,
  EE_TRIBOARD_2X5_LED_1 = 0x01,
  EE_TRIBOARD_2X5_LED_2 = 0x02,
  EE_TRIBOARD_2X5_LED_3 = 0x04,
  EE_TRIBOARD_2X5_LED_4 = 0x08,
  EE_TRIBOARD_2X5_LED_5 = 0x10,
  EE_TRIBOARD_2X5_LED_6 = 0x20,
  EE_TRIBOARD_2X5_LED_7 = 0x40,
  EE_TRIBOARD_2X5_LED_8 = 0x80,
  EE_TRIBOARD_2X5_ALL_LEDS = 0xFF
};

/*  User LEDs are in pull down configuration so the logic is
    inverted respect pin output value */
enum EE_tc2x5_led_status {
  EE_TRIBOARD_2X5_LED_ON  = 0,
  EE_TRIBOARD_2X5_LED_OFF = 1
};

__INLINE__ void __ALWAYS_INLINE__ EE_tc2x5_turn_led(enum EE_tc2x5_led_id
    led_id, enum EE_tc2x5_led_status onoff)
{
  switch(led_id) {
    case EE_TRIBOARD_2X5_LED_8:
      P33_OUT.B.P13 = (EE_UINT8)onoff;
    break;
    case EE_TRIBOARD_2X5_LED_7:
      P33_OUT.B.P12 = (EE_UINT8)onoff;
    break;
    case EE_TRIBOARD_2X5_LED_6:
      P33_OUT.B.P11 = (EE_UINT8)onoff;
    break;
    case EE_TRIBOARD_2X5_LED_5:
      P33_OUT.B.P10 = (EE_UINT8)onoff;
    break;
    case EE_TRIBOARD_2X5_LED_4:
      P33_OUT.B.P9 = (EE_UINT8)onoff;
    break;
    case EE_TRIBOARD_2X5_LED_3:
      P33_OUT.B.P8 = (EE_UINT8)onoff;
    break;
    case EE_TRIBOARD_2X5_LED_2:
      P33_OUT.B.P7 = (EE_UINT8)onoff;
    break;
    case EE_TRIBOARD_2X5_LED_1:
      P33_OUT.B.P6 = (EE_UINT8)onoff;
    break;
    default:
      P33_OUT.B.P13 = (EE_UINT8)onoff;
      P33_OUT.B.P12 = (EE_UINT8)onoff;
      P33_OUT.B.P11 = (EE_UINT8)onoff;
      P33_OUT.B.P10 = (EE_UINT8)onoff;
      P33_OUT.B.P9 = (EE_UINT8)onoff;
      P33_OUT.B.P8 = (EE_UINT8)onoff;
      P33_OUT.B.P7 = (EE_UINT8)onoff;
      P33_OUT.B.P6 = (EE_UINT8)onoff;
    break;
  }
}

__INLINE__ void __ALWAYS_INLINE__ EE_tc2x5_set_leds_mask(EE_UINT8 leds_mask)
{
  P33_OUT.B.P13   =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_8) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P12   =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_7) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P11   =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_6) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P10   =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_5) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P9    =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_4) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P8    =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_3) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P7    =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_2) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
  P33_OUT.B.P6    =   (((EE_UINT32)leds_mask &
    (EE_UINT32)EE_TRIBOARD_2X5_LED_1) != (EE_UINT32)0U) ?
    (EE_UINT8)EE_TRIBOARD_2X5_LED_ON: (EE_UINT8)EE_TRIBOARD_2X5_LED_OFF;
}

__INLINE__ void __ALWAYS_INLINE__ EE_tc2x5_leds_on( void )
{
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_ALL_LEDS, EE_TRIBOARD_2X5_LED_ON);
}

__INLINE__ void __ALWAYS_INLINE__ EE_tc2x5_leds_off( void )
{
  EE_tc2x5_turn_led(EE_TRIBOARD_2X5_ALL_LEDS, EE_TRIBOARD_2X5_LED_OFF);
}

__INLINE__ void __ALWAYS_INLINE__ EE_tc2x5_leds_init( void )
{
  EE_tc2x5_leds_off();

  P33_IOCR12.B.PC13  =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR12.B.PC12  =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC11   =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC10   =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC9    =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR8.B.PC8    =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR4.B.PC7    =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
  P33_IOCR4.B.PC6    =   EE_TC2YX_OUTPUT_PUSH_PULL_GP;
}


/* Infineon TriBoard-TC2X5_V2.0 come without buttons, but RESET button.
   We put a flying button connected with signal REQ1 <-> pin P15.8 on
   pin 71 of PERIPHERALS (Xx02,Xx02) connector.

   Pin P15.8 is a valid input for the ESR5 (External Service Requests 5),
   that can be configured with EICR2.EIS1 (External Input Channel Register 1,
   External Input Selection 1 (the rule is EICRx.EISy -> ESR(2x + y) with
   x [0..3] and y [0,1]).

   The param intvec is used to configure the level of interrupt vector that
   will serve the request.
*/

__INLINE__ void __ALWAYS_INLINE__ EE_tc2x5_button_irq_init( EE_TYPEISR2PRIO intvec )
{
  /*  On reset all IOCR (input/output configuration register) configure port
      as input connected to pull-up, that is what we need, so we wont change
      it, but if the internal pull-up will have problem with button pull-up
      I have just to enable the following line */
  /* P15_IOCR8.PC8 = EE_TC2YX_INPUT_TRISTATE; */

  /* P15.8 is input selection 0 so I don't need to configure EIS */
  /* SCU_EICR2.B.EIS1 = 0U; */

  /*  The button will shortcut the pin with GND when pressed ->
      we will use the falling edge to generate the interrupt */
  SCU_EICR2.B.FEN1    = 1U;
  SCU_EICR2.B.EIEN1   = 1U;

  /* Configure OGU0 to respond on triggers (no pattern matching) */
  SCU_IGCR0.B.IGP0 = 1U;

  /* I will use OGU0 (Output Gate-in Unit 0) -> SRC_SCUERU0
   *  [0..7] SRPN = INTERRUPT_NR
   *  [10] Service Request enable
   *  [11..12] Type Of Service (means which CPU will handle it)
   */
  SRC_SCUERU0.U = EE_TC2YX_SRN_TYPE_OF_SERVICE(EE_CURRENTCPU) |
    EE_TC2YX_SRN_ENABLE | EE_TC2YX_SRN_PRIORITY(intvec);
}

__INLINE__ void __ALWAYS_INLINE__ EE_tc2x5_button_irq_clear_request( void )
{
  /* Clear the request */
  SCU_FMR.B.FC5       = 1U;
}

__INLINE__ EE_BIT __ALWAYS_INLINE__ EE_tc2x5_read_button( void )
{
  return P15_IN.B.P8;
}

#endif /* INCLUDE_EE_TC2X5_BOARD_H__ */
