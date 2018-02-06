/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * This is a basic demo to test NXP lpc12xx through the LPCXpresso board.
 *
 * It is a minimal EEB demo including:
 * - One task
 * - One periodic alarm controlled by System tick (SysTick) timer
 * - Support for LPCXpresso board
 *
 * This demo exploits the CMSIS library to set the timer, to control I/O pins
 * and the system initialization.
 *
 * Author: 2011  Gianluca Franchino
 *               Giuseppe Serano
 */

#include "ee.h"
#include "lpc12xx_libcfg_default.h"
#include "ee_irq.h"

/* Counter */
int task1_fired = 0;

/*
 * SysTick ISR
 */
ISR2(SysTick_Handler)
{
  /* count the interrupts, waking up expired alarms */
  CounterTick(myCounter);
}

/*
 * LED INITIALIZATION
 */
void led_init(void)
{
  IOCON_PIO_CFG_Type PIO_mode;

  /*Initialize the IO system*/
  SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_GPIO2, ENABLE);
  IOCON_StructInit(&PIO_mode);
  PIO_mode.type = IOCON_PIO_0_7;
  IOCON_SetFunc(&PIO_mode);
  GPIO_SetDir(LPC_GPIO0, 7, 1);
  GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
}

/*
 * LED Blink
 */
void led_blink(void)
{
  if ( GPIO_GetPinValue(LPC_GPIO0, 7) )
    GPIO_SetLowLevel(LPC_GPIO0, 7, 1);
  else
    GPIO_SetHighLevel(LPC_GPIO0, 7, 1);
}

/*
 * INTERRUPT INITIALIZATION
 */
void interrupt_init()
{
  /* Generate systemtick interrupt each 1 ms   */
  SysTick_Config(SystemCoreClock/1000 - 1);
#ifdef	__IAR__
  __enable_interrupt();
#else
#ifdef	__KEIL__
  __enable_irq();
#endif	/* __KEIL__ */
#endif	/* __IAR__ */
}

/*
 * TASK 1
 */
TASK(Task1)
{
  task1_fired++;
  led_blink();
}

/*
 * MAIN TASK
 */
int main(void)
{
  /*
   Setup the microcontroller system:
    -System Clock Setup;
    -PLL setup
    -Whatchdog setup (Default Watchdog = disabled)
    
    The system (core) clock frequency (CF):  CF= Fin * P /M;
    For Fin<15 P=4 and M=2
    If your board mounts a 12MHz cristal oscillator, i.e. Fin=12MHz,
    then the default system clock frequency is CF = 12 MHz * P /M= 24MHZ.

    See "system_LPC12xx.c" in <contrib/nxp/lpc12xx_cmsis_v2_0> 
    for further informations.
    To modify the system setup, use functions provided by 
    "lpc12xx_sysctrl.c" in <contrib/nxp/lpc12xx_cmsis_v2_0>
  */
  SystemInit();
  
  /*Initializes Erika related stuffs*/
  EE_system_init(); 

  led_init();
  
  interrupt_init();

  SetRelAlarm(myAlarm, 500, 500);

  /* Forever loop: background activities (if any) should go here */
  for (;;)
  {
    ;
  }

}
