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
 * Example of use of the decrementer and the fixed-interval interrupts
 * Author: 2011 Bernardo  Dal Seno
 */

#include <ee.h>
#include <ee_irq.h>
#include "board/ti_stellaris_lm4f232xxxx/inc/ee_board.h"

DeclareTask(time_slow);
DeclareTask(time_fast);

TASK(time_slow)
{
  EE_user_led_toggle();
  TerminateTask();
}

TASK(time_fast)
{
  EE_user_led_toggle();
  TerminateTask();
}

int main(void)
{
  EE_user_led_init();
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
