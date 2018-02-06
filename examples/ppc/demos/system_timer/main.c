/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.  ERIKA Enterprise is free software;
 * you can redistribute it and/or modify it under the terms of the
 * GPLv2 + Linking Exception license (contained in the file `ee/LICENSE').
 *
 * ERIKA Enterprise is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the license for more details.
 *
 * ###*E*### */

/*
 * Example of use of the decrementer, fixed-interval interrupts and system timer
 * Author: 2012 Francesco Esposito
 */

#include <ee.h>
#include <ee_irq.h>
#include "board/axiom_mpc5674fxmb/inc/ee_board.h"

/* TODO implement in druid macro mapping */
#define ISR(f) ISR2_INT(f)

DeclareTask(time_slow);
DeclareTask(time_fast);
DeclareTask(fixed_interval);
void fixed_intv_handler(void);

TASK(time_slow)
{
  static unsigned char s;
  EE_led_set(1U, s);
  s = (s == 0 ? 1 : 0);
  TerminateTask();
}

TASK(time_fast)
{
  static unsigned char s;
  EE_led_set(2U, s);
  s = (s == 0 ? 1 : 0);
  TerminateTask();
}

TASK(fixed_interval)
{
  static unsigned char s;
  EE_led_set(3U, s);
  s = (s == 0 ? 1 : 0);
  TerminateTask();
}

ISR(fixed_intv_handler) {
  IncrementCounter(fixed_interval_timer);
}

void main(void)
{
  EE_leds_init();
  EE_e200zx_setup_fixed_intv(64-23);
  StartOS(OSDEFAULTAPPMODE);
}
