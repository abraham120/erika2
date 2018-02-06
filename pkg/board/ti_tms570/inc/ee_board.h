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

#ifndef __INCLUDE_TI_TMS570_BOARD_H__
#define __INCLUDE_TI_TMS570_BOARD_H__

#include "gio.h"
#include "het.h"
#include "board/ti_tms570/inc/TMS570_emif.h"
#include "board/ti_tms570/inc/EMIF.h"
#include "board/ti_tms570/inc/Display.h"
#include "board/ti_tms570/inc/Font.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/*
 * Check Button 1
 */
static int CheckSwitch1 (void) {         // Switch 1 is connected to pin GIOB3 (active low)
  return (1 - ((gioPORTB->DIN >> 3) & 0x01));
}

/*
 * Check Button 2
 */
static int CheckSwitch2 (void) {         // Switch 2 is connected to pin GIOB6 (active low)
  return (1 - ((gioPORTB->DIN >> 6) & 0x01));
}

/*
 * User Led
 */

#define LED_NUM    6                    /* Number of user LEDs                */
static const unsigned long led_gioMask[]  = { 1UL<< 0, 1UL<< 3, 1UL<< 4,  1UL<< 5};
static const unsigned long led_nhetMask[] = { 1UL<< 1, 1UL<< 31};


/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
static void EE_LED_On (unsigned int num) {
  if (num < 4) {
    gioPORTA->DSET = led_gioMask[num];
  } else {
    hetREG->DSET = led_nhetMask[num-4];
  }
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
static void EE_LED_Off (unsigned int num) {
  if (num < 4) {
    gioPORTA->DCLR = led_gioMask[num];
  } else {
    hetREG->DCLR = led_nhetMask[num-4];
  }
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
static void EE_LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      EE_LED_On (i);
    } else {
      EE_LED_Off(i);
    }
  }
}

/*----------------------------------------------------------------------------
  Function that toggles requested LED
 *----------------------------------------------------------------------------*/
static void EE_LED_Toggle (unsigned int num) {
  if (num < 4) {
    if ((gioPORTA->DIN & led_gioMask[num]) != 0U)
    {
      gioPORTA->DCLR = led_gioMask[num];
    }
    else
    {
      gioPORTA->DSET = led_gioMask[num];
    }

  } else {
    if ((hetREG->DIN & led_nhetMask[num-4]) != 0U)
    {
      hetREG->DCLR = led_nhetMask[num-4];
    }
    else
    {
      hetREG->DSET = led_nhetMask[num-4];
    }
  }

}



#endif /*__INCLUDE_TI_TMS570_BOARD_H__ */
