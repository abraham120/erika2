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

/*
 * Author: 2012 Giuseppe Serano
 */

#include "board/ti_stellaris_lm4f232xxxx/inc/ee_board.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "grlib/grlib.h"
#include "drivers/cfal96x64x16.h"
#include "driverlib/gpio.h"

/*
 * The error routine that is called if the driver library encounters an error.
 */
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif

/*
 * User Led Status.
 */
static EE_UINT8 leds_status;

#define	OLED_DISPLAY_MESSAGE_LINE_1	"I LOVE ERIKA"
#define	OLED_DISPLAY_MESSAGE_LINE_2	"ENTERPRISE!!"
/*
 * Graphics Context
 */
static tContext sContext;

/*
 * OLED Display Initialization
 */
void EE_oled_display_init(void)
{

  /* Initialize the display driver. */
  CFAL96x64x16Init();

  /* Initialize the graphics context. */
  GrContextInit(&sContext, &g_sCFAL96x64x16);

  /* set-up font */
  GrContextFontSet(&sContext, g_pFontFixed6x8);

  /* Reset User Leds Status */
  leds_status = OLED_DISPLAY_LEDS_ON;
  EE_oled_display_leds(OLED_DISPLAY_LEDS_OFF);

  /* just a nice subliminal welcome message :-) */
  EE_oled_display_line1(OLED_DISPLAY_MESSAGE_LINE_1);
  EE_oled_display_line2(OLED_DISPLAY_MESSAGE_LINE_2);

}

/*
 * OLED Display Clear display.
 */
void EE_oled_display_clear(void)
{

  tRectangle sRect;

  sRect.sXMin = 0;
  sRect.sYMin = 0;
  sRect.sXMax = GrContextDpyWidthGet(&sContext) - 1;
  sRect.sYMax = GrContextDpyHeightGet(&sContext) - 1;

  /* Set-up Foreground Color */
  GrContextForegroundSet(&sContext, ClrBlack);

  /* Clear Display */
  GrRectFill(&sContext, &sRect);

  /* Flush any cached drawing operations. */
  GrFlush(&sContext);

}

#define	OLED_DISPLAY_LED_X	0
#define	OLED_DISPLAY_LED_Y	0
#define	OLED_DISPLAY_LED_SIZE	12

/*
 * OLED Display User Leds display.
 */
void EE_oled_display_leds(EE_UINT8 leds_mask)
{

  tRectangle sRect;
  char led_num_string[2] = "0";
  register EE_UINT8 led = OLED_DISPLAY_LED_0;

  sRect.sXMin = OLED_DISPLAY_LED_X;
  sRect.sYMin = OLED_DISPLAY_LED_Y;
  sRect.sXMax = OLED_DISPLAY_LED_SIZE - 1;
  sRect.sYMax = OLED_DISPLAY_LED_Y + OLED_DISPLAY_LED_SIZE;

  do {

    if ((led & leds_status) ^ (led & leds_mask)) {

      if (leds_mask & led) GrContextForegroundSet(&sContext, ClrGreen);
      else GrContextForegroundSet(&sContext, ClrBlack);

      GrRectFill(&sContext, &sRect);

      if (leds_mask & led) GrContextForegroundSet(&sContext, ClrBlack);
      else GrContextForegroundSet(&sContext, ClrGreen);

      GrRectDraw(&sContext, &sRect);

      GrStringDraw(
	&sContext,
	led_num_string,
	-1,
	sRect.sXMin + 4 ,
	sRect.sYMin + 3,
	0
      );

      leds_status &= ~led;
      leds_status |= (led & leds_mask);

    }

    /* Next Led */
    led = led << 1;
    led_num_string[0]++;
    sRect.sXMin = sRect.sXMin + OLED_DISPLAY_LED_SIZE;
    sRect.sXMax = sRect.sXMax + OLED_DISPLAY_LED_SIZE;

  }
  while ((led & OLED_DISPLAY_LEDS_ON) != OLED_DISPLAY_LEDS_OFF);

  /* Flush any cached drawing operations. */
  GrFlush(&sContext);

}

#define	OLED_DISPLAY_LINE_1_X	0
#define	OLED_DISPLAY_LINE_1_Y	32
#define	OLED_DISPLAY_LINE_1_X2	95
#define	OLED_DISPLAY_LINE_1_Y2	47

/*
 * OLED Display User Message Line 1 display.
 */
void EE_oled_display_line1(const char *s)
{

  tRectangle sRect;

  sRect.sXMin = OLED_DISPLAY_LINE_1_X;
  sRect.sYMin = OLED_DISPLAY_LINE_1_Y;
  sRect.sXMax = OLED_DISPLAY_LINE_1_X2;
  sRect.sYMax = OLED_DISPLAY_LINE_1_Y2;

  GrContextForegroundSet(&sContext, ClrBlack);

  GrRectFill(&sContext, &sRect);

  GrContextForegroundSet(&sContext, ClrGreen);

  GrStringDraw(
    &sContext, s, -1, OLED_DISPLAY_LINE_1_X, OLED_DISPLAY_LINE_1_Y, 0
  );

  /* Flush any cached drawing operations. */
  GrFlush(&sContext);
}

#define	OLED_DISPLAY_LINE_2_X	0
#define	OLED_DISPLAY_LINE_2_Y	48
#define	OLED_DISPLAY_LINE_2_X2	95
#define	OLED_DISPLAY_LINE_2_Y2	63

/*
 * OLED Display User Message Line 2 display.
 */
void EE_oled_display_line2(const char *s)
{

  tRectangle sRect;

  sRect.sXMin = OLED_DISPLAY_LINE_2_X;
  sRect.sYMin = OLED_DISPLAY_LINE_2_Y;
  sRect.sXMax = OLED_DISPLAY_LINE_2_X2;
  sRect.sYMax = OLED_DISPLAY_LINE_2_Y2;

  GrContextForegroundSet(&sContext, ClrBlack);

  GrRectFill(&sContext, &sRect);

  GrContextForegroundSet(&sContext, ClrGreen);

  GrStringDraw(
    &sContext, s, -1, OLED_DISPLAY_LINE_2_X, OLED_DISPLAY_LINE_2_Y, 0
  );

  /* Flush any cached drawing operations. */
  GrFlush(&sContext);

}
