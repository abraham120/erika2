/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Simple project to test the a fake example to demonstrate that the compile
 * toolchain is integrated into the makefiles.
 * Author: 2013  Giuseppe Serano
 * Based on examples/s12xs/porting_examples/monostack/EEtest0
 */


#include "ee.h"
#include "test/assert/inc/ee_assert.h"

#ifdef	__AVR__
#pragma message(EE_PREPROC_VAR_VALUE(__AVR__))
#endif
#ifdef	MEGA
#pragma message(EE_PREPROC_VAR_VALUE(MEGA))
#endif
#ifdef	__AVR8__
#pragma message(EE_PREPROC_VAR_VALUE(__AVR8__))
#endif
#ifdef	__MEGA__
#pragma message(EE_PREPROC_VAR_VALUE(__MEGA__))
#endif
#ifdef	__ATTINY__
#pragma message(EE_PREPROC_VAR_VALUE(__ATTINY__))
#endif
#ifdef	__ATMEGA__
#pragma message(EE_PREPROC_VAR_VALUE(__ATMEGA__))
#endif
#pragma message(EE_PREPROC_VAR_VALUE(__AVR_ARCH__))
#ifdef	AVR8_MCU
#pragma message(EE_PREPROC_VAR_VALUE(AVR8_MCU))
#endif
#ifdef	__AVR_ATmega128__ 
#pragma message(EE_PREPROC_VAR_VALUE(__AVR_ATmega128__))
#endif
#ifdef	__AVR_ATtiny1634__
#pragma message(EE_PREPROC_VAR_VALUE(__AVR_ATtiny1634__))
#endif

/* Assertions */
enum EE_ASSERTIONS {
  EE_ASSERT_FIN = 0,
  EE_ASSERT_INIT,
  EE_ASSERT_DIM
};
EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/* Stack Pointers */
volatile EE_UINT16 main_sp = 0x0000U;

EE_UINT16 EE_currentSP( void ) {
#if	0
  __asm__ __volatile__(
    /* r24:r25 = SP */
    "in	r24, 0x3D\n"	/* SPL -> r24 */
    "in	r25, 0x3E\n"	/* SPH -> r25 */
    ::
  );
#else	/* 0 */
  return _SFR_IO16(_SFR_IO_ADDR(SP));
#endif	/* 0 */
}

/*
 * TASK 1
 */
TASK(Task1)
{

}

/*
 * MAIN TASK
 */
int main(void)
{
  EE_UINT16	curr_sp;

#if	0
  EE_mcu_init();
#endif	/* 0 */

  EE_assert(EE_ASSERT_INIT, EE_TRUE, EE_ASSERT_NIL);
  EE_assert_range(EE_ASSERT_FIN, EE_ASSERT_INIT, EE_ASSERT_INIT);
  result = EE_assert_last();

  /* Forever loop: background activities (if any) should go here */
  for (;result == 1;)
  {

    curr_sp = EE_currentSP();
    if (main_sp != curr_sp) {
      main_sp = curr_sp;
    }

    counter++;
  }

}
