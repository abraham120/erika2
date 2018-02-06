/** @file rti.h
*   @brief RTI Driver Header File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   - Interface Prototypes
*   .
*   which are relevant for the RTI driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */


#ifndef __RTI_H__
#define __RTI_H__

#include "reg_rti.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* RTI General Definitions */

/** @def rtiCOUNTER_BLOCK0
*   @brief Alias name for RTI counter block 0
*
*   This is an alias name for the RTI counter block 0.
*
*   @note This value should be used for API argument @a counter
*/
#define rtiCOUNTER_BLOCK0 0U

/** @def rtiCOUNTER_BLOCK1
*   @brief Alias name for RTI counter block 1
*
*   This is an alias name for the RTI counter block 1.
*
*   @note This value should be used for API argument @a counter
*/
#define rtiCOUNTER_BLOCK1 1U

/** @def rtiCOMPARE0
*   @brief Alias name for RTI compare 0
*
*   This is an alias name for the RTI compare 0.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE0 0U

/** @def rtiCOMPARE1
*   @brief Alias name for RTI compare 1
*
*   This is an alias name for the RTI compare 1.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE1 1U

/** @def rtiCOMPARE2
*   @brief Alias name for RTI compare 2
*
*   This is an alias name for the RTI compare 2.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE2 2U

/** @def rtiCOMPARE3
*   @brief Alias name for RTI compare 3
*
*   This is an alias name for the RTI compare 3.
*
*   @note This value should be used for API argument @a compare
*/
#define rtiCOMPARE3 3U

/** @def rtiNOTIFICATION_COMPARE0
*   @brief Alias name for RTI compare 0 notification
*
*   This is an alias name for the RTI compare 0 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE0 1U

/** @def rtiNOTIFICATION_COMPARE1
*   @brief Alias name for RTI compare 1 notification
*
*   This is an alias name for the RTI compare 1 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE1 2U

/** @def rtiNOTIFICATION_COMPARE2
*   @brief Alias name for RTI compare 2 notification
*
*   This is an alias name for the RTI compare 2 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE2 4U

/** @def rtiNOTIFICATION_COMPARE3
*   @brief Alias name for RTI compare 3 notification
*
*   This is an alias name for the RTI compare 3 notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COMPARE3 8U

/** @def rtiNOTIFICATION_TIMEBASE
*   @brief Alias name for RTI timebase notification
*
*   This is an alias name for the RTI timebase notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_TIMEBASE 0x10000U

/** @def rtiNOTIFICATION_COUNTER0
*   @brief Alias name for RTI counter block 0 overflow notification
*
*   This is an alias name for the RTI counter block 0 overflow notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COUNTER0 0x20000U

/** @def rtiNOTIFICATION_COUNTER1
*   @brief Alias name for RTI counter block 1 overflow notification
*
*   This is an alias name for the RTI counter block 1 overflow notification.
*
*   @note This value should be used for API argument @a notification
*/
#define rtiNOTIFICATION_COUNTER1 0x40000U

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** 
 *  @defgroup RTI RTI
 *  @brief Real Time Interrupt Module.
 *  
 *  The real-time interrupt (RTI) module provides timer functionality for operating systems and for
 *  benchmarking code. The RTI module can incorporate several counters that define the timebases needed
 *  for scheduling in the operating system.
 *
 *	Related Files
 *   - reg_rti.h
 *   - rti.h
 *   - rti.c
 *  @addtogroup RTI
 *  @{
 */
 
/* RTI Interface Functions */

void rtiInit(void);
void rtiStartCounter(uint32 counter);
void rtiStopCounter(uint32 counter);
uint32 rtiResetCounter(uint32 counter);
void rtiSetPeriod(uint32 compare, uint32 period);
uint32 rtiGetPeriod(uint32 compare);
uint32 rtiGetCurrentTick(uint32 compare);
void rtiEnableNotification(uint32 notification);
void rtiDisableNotification(uint32 notification);

/** @fn void rtiNotification(uint32 notification)
*   @brief Notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   @note This function has to be provide by the user.
*/
void rtiNotification(uint32 notification);

/**@}*/
/* USER CODE BEGIN (2) */
/*
void rtiNotificationCompare0(void);
void rtiNotificationCompare1(void);
void rtiNotificationCompare2(void);
extern void rtiNotificationCompare3(void);
void rtiNotificationTimebase(void);
void rtiNotificationOverflow5(void);
void rtiNotificationOverflow1(void);
*/
/* USER CODE END */


#endif
