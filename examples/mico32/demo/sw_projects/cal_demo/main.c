/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010  Evidence Srl
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
 * Author: 2011 Antonio Marcello Catinella
 */

/* Use Erika */
#include <ee.h>
/* Platform configuration */
#include <system_conf.h>
/* Lattice Timer component */
#include <MicoTimer.h>
/* Lattice GPIO component */
#include <MicoGPIO.h>
/* Erika Mico32 interrupts */
#include <ee_irq.h>
/* Lattice components */
#include <MicoMacros.h>
/* cal interface  */
#include "ee_cal.h"

int main_cal(int argc, char *argv[]);

TASK(calTask)
{
  char *argv[] = { "",
#ifdef CAL_STATISTICS
  "--statistics"
#else
  ""
#endif
  };
  int argc = sizeof(argv)/sizeof(argv[0]);
  main_cal(argc, argv);
}

void system_timer_callback(void)
{
  /* count the interrupts, waking up expired alarms */
  CounterTick(myCounter);
}

int main(void)
{
  EE_transistor_all_on();
  /* ------------------- */
  /* Kernel timer configuration */
  /* ------------------- */
  EE_timer_set_ISR_callback(system_timer_callback);
  EE_timer_init(MILLISECONDS_TO_TICKS(1), MICO32_TIMER_CONTROL_INT_BIT_MASK | MICO32_TIMER_CONTROL_CONT_BIT_MASK);

  EE_timer_on();

  EE_cal_init();
  EE_cal_start(calTask);

  /* Forever loop: background activities (if any) should go here */
  for (;;);

  return 0;
}
