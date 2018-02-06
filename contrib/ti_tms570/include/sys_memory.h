/** @file sys_memory.h
*   @brief System Memory Header File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*   This file contains:
*   - Memory Interface Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __SYS_MEMORY_H__
#define __SYS_MEMORY_H__

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* System Memory Interface Functions */

/** @fn void _memoryTest_(void)
*   @brief Pbist hardware memory selftest
*/
void _memoryTest_(void);

/** @fn void _memoryInit_(void)
*   @brief Automatic hardware memory initialization
*/
void _memoryInit_(void);


/* USER CODE BEGIN (1) */
/* USER CODE END */


#endif
