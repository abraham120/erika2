/*! \file ledctl.h
  *  \brief Simple LED control API definition
 *
 *  A simple LED control API providing functions to control single or all
 *  LEDs of a board.
 *
 *  \autor TGL
 *
 *  \version
 *    08.08.2010  initial version
 */

#ifndef INCLUDE_EE_APPKIT_TC2X5_BOARD_LED_H__
#define INCLUDE_EE_APPKIT_TC2X5_BOARD_LED_H__

#include "ee.h"

/* LEDs: P33.6 .. P33.13 */

#define LEDCTL_LED_FIRST	6
#define LEDCTL_LED_COUNT 4
/*! \brief Initialize LED port
 *  \return Number of LEDs
 */
__INLINE__ int LEDCTL_Init(void){
	volatile unsigned int ui;
	P33_OMR.U = (0x0FF << LEDCTL_LED_FIRST);
	ui = (P33_IOCR4.U & 0x0FFFF) | 0x80800000;
	P33_IOCR4.U = ui;
	P33_IOCR8.U = 0x80808080;
	ui = (P33_IOCR12.U & 0xFFFF0000) | 0x00008080;
	P33_IOCR12.U = ui;
	return LEDCTL_LED_COUNT;
}

/*! \brief Switch a single LED on
 *  \param Index of LED to control
 */
__INLINE__ void LEDCTL_On(int Index){
  if (Index > 3) return;
	unsigned int uiMask = (1 << (Index + 2 + LEDCTL_LED_FIRST + 16));
	P33_OMR.U = uiMask;
}

/*! \brief Switch a single LED off
 *  \param Index of LED to control
 */
__INLINE__ void LEDCTL_Off(int Index){
  if (Index > 3) return;
	unsigned int uiMask = (1 << (Index + 2 + LEDCTL_LED_FIRST));
	P33_OMR.U = uiMask;
}

/*! \brief Get status of a single LED
 *  \param Index of LED to control
 *  \return
 *    0 ... LED is off
 *    1 ... LED is on
 */
__INLINE__ int  LEDCTL_Status(int Index){
  if (Index > 3) return -1;
	unsigned int uiMask = (1 << (Index + 2 + LEDCTL_LED_FIRST));
	return ((P33_OUT.U & uiMask) ? 1 : 0);
}

/*! \brief Toggle a single LED
 *  \param Index of LED to control
 */
__INLINE__ void LEDCTL_Toggle(int Index){
  if (Index > 3) return;
	unsigned int uiMask = (1 << (Index + 2 + LEDCTL_LED_FIRST));
	P33_OUT.U ^= uiMask;
}

/*! \brief Output value to LED port
 */
__INLINE__ void LEDCTL_Out(unsigned int Value){
  if (Value > 15) return;
	P33_OUT.U = ~(Value << LEDCTL_LED_FIRST);
}

#endif /* INCLUDE_EE_APPKIT_TC2X5_BOARD_LED_H__ */
