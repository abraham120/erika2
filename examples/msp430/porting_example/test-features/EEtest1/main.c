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
* Author:2010, Christian Grioli
* Testing options LPMODE. 
* In this case two Tasks and only one interrupt (monostack case).
*/

#include "ee.h"


void delay(unsigned int d) {
   int i;
   for (i = 0; i<d; i++) {
      nop();
      nop();
   }
}

int counter=0;
ISR2(TIMERA0_VECTOR){
EE_leds_on();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);
EE_led_0_off();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);
EE_msp430_exit_LPM(LPMODE_0);




}


TASK(Task1)
{
EE_leds_off();
EE_led_0_on();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);
EE_msp430_enter_LPM(LPMODE_0);

EE_leds_off();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);

EE_led_0_on();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);
}


TASK(Task2)
{
counter=0;
EE_leds_off();
EE_led_1_on();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);

EE_msp430_enter_LPM(LPMODE_0);
EE_leds_off();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);

EE_led_1_on();
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);
delay(0x4fff);

}



/**
Main function with some blinking leds
*/
int main(void) {

  EE_msp430_init();
  EE_leds_init();
  EE_leds_on();

/*Set the timer A*/
   TACCTL0=CCIE;
   TACTL=TASSEL_1+ MC_2;
/*EnableInterrupt*/
   eint();
   ActivateTask(Task1);
   ActivateTask(Task2);
   for(;;);
}

