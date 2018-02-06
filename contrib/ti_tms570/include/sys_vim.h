/** @file sys_vim.h
*   @brief Vectored Interrupt Module Header File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*   This file contains:
*   - VIM Type Definitions
*   - VIM General Definitions
*   .
*   which are relevant for Vectored Interrupt Controller.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */


#ifndef __SYS_VIM_H__
#define __SYS_VIM_H__

#include "reg_vim.h"
/* USER CODE BEGIN (0) */
/* USER CODE END */


/* VIM Type Definitions */

/** @typedef t_isrFuncPTR
*   @brief ISR Function Pointer Type Definition
*
*   This type is used to access the ISR handler.
*/
typedef void (*t_isrFuncPTR)();

/* USER CODE BEGIN (1) */
/* USER CODE END */


/* VIM General Configuration */

#define VIM_CHANNELS 64U

/* USER CODE BEGIN (2) */
/* USER CODE END */

/* Interrupt Handlers */

extern void esmHighInterrupt(void);
extern void phantomInterrupt(void);
extern void rtiCompare0Interrupt(void);
extern void rtiCompare1Interrupt(void);
extern void rtiCompare2Interrupt(void);
extern void rtiCompare3Interrupt(void);

/* USER CODE BEGIN (3) */
/* USER CODE END */


#endif
