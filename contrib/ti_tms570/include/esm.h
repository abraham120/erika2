/** @file esm.h
*   @brief Error Signaling Module Driver Header File
*   @date 9.Sep.2014
*   @version 04.01.00
*   
*   This file contains:
*   - Definitions
*   - Types
*   .
*   which are relevant for the Esm driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

#ifndef __ESM_H__
#define __ESM_H__

#include "reg_esm.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* ESM General Definitions */

/** @def esmGROUP1
*   @brief Alias name for ESM group 1
*
*   This is an alias name for the ESM group 1.
*
*   @note This value should be used for API argument @a group
*/
#define esmGROUP1 0U

/** @def esmGROUP2
*   @brief Alias name for ESM group 2
*
*   This is an alias name for the ESM group 2.
*
*   @note This value should be used for API argument @a group
*/
#define esmGROUP2 1U

/** @def esmGROUP3
*   @brief Alias name for ESM group 3
*
*   This is an alias name for the ESM group 3.
*
*   @note This value should be used for API argument @a group
*/
#define esmGROUP3 2U

/** @def esmCHANNEL0
*   @brief Alias name for ESM group x channel 0
*
*   This is an alias name for the ESM group x channel 0.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL0 0x0000000000000001ULL

/** @def esmCHANNEL1
*   @brief Alias name for ESM group x channel 1
*
*   This is an alias name for the ESM group x channel 1.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL1 0x0000000000000002ULL

/** @def esmCHANNEL2
*   @brief Alias name for ESM group x channel 2
*
*   This is an alias name for the ESM group x channel 2.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL2 0x0000000000000004ULL

/** @def esmCHANNEL3
*   @brief Alias name for ESM group x channel 3
*
*   This is an alias name for the ESM group x channel 3.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL3 0x0000000000000008ULL

/** @def esmCHANNEL4
*   @brief Alias name for ESM group x channel 4
*
*   This is an alias name for the ESM group x channel 4.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL4 0x0000000000000010ULL

/** @def esmCHANNEL5
*   @brief Alias name for ESM group x channel 5
*
*   This is an alias name for the ESM group x channel 5.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL5 0x0000000000000020ULL

/** @def esmCHANNEL6
*   @brief Alias name for ESM group x channel 6
*
*   This is an alias name for the ESM group x channel 6.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL6 0x0000000000000040ULL

/** @def esmCHANNEL7
*   @brief Alias name for ESM group x channel 7
*
*   This is an alias name for the ESM group x channel 7.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL7 0x0000000000000080ULL

/** @def esmCHANNEL8
*   @brief Alias name for ESM group x channel 8
*
*   This is an alias name for the ESM group x channel 8.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL8 0x0000000000000100ULL

/** @def esmCHANNEL9
*   @brief Alias name for ESM group x channel 9
*
*   This is an alias name for the ESM group x channel 9.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL9 0x0000000000000200ULL

/** @def esmCHANNEL10
*   @brief Alias name for ESM group x channel 10
*
*   This is an alias name for the ESM group x channel 10.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL10 0x0000000000000400ULL

/** @def esmCHANNEL11
*   @brief Alias name for ESM group x channel 11
*
*   This is an alias name for the ESM group x channel 11.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL11 0x0000000000000800ULL

/** @def esmCHANNEL12
*   @brief Alias name for ESM group x channel 12
*
*   This is an alias name for the ESM group x channel 12.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL12 0x0000000000001000ULL

/** @def esmCHANNEL13
*   @brief Alias name for ESM group x channel 13
*
*   This is an alias name for the ESM group x channel 13.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL13 0x0000000000002000ULL

/** @def esmCHANNEL14
*   @brief Alias name for ESM group x channel 14
*
*   This is an alias name for the ESM group x channel 14.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL14 0x0000000000004000ULL

/** @def esmCHANNEL15
*   @brief Alias name for ESM group x channel 15
*
*   This is an alias name for the ESM group x channel 15.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL15 0x0000000000008000ULL

/** @def esmCHANNEL16
*   @brief Alias name for ESM group x channel 16
*
*   This is an alias name for the ESM group x channel 16.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL16 0x0000000000010000ULL

/** @def esmCHANNEL17
*   @brief Alias name for ESM group x channel 17
*
*   This is an alias name for the ESM group x channel 17.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL17 0x0000000000020000ULL

/** @def esmCHANNEL18
*   @brief Alias name for ESM group x channel 18
*
*   This is an alias name for the ESM group x channel 18.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL18 0x0000000000040000ULL

/** @def esmCHANNEL19
*   @brief Alias name for ESM group x channel 19
*
*   This is an alias name for the ESM group x channel 19.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL19 0x0000000000080000ULL

/** @def esmCHANNEL20
*   @brief Alias name for ESM group x channel 20
*
*   This is an alias name for the ESM group x channel 20.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL20 0x0000000000100000ULL

/** @def esmCHANNEL21
*   @brief Alias name for ESM group x channel 21
*
*   This is an alias name for the ESM group x channel 21.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL21 0x0000000000200000ULL

/** @def esmCHANNEL22
*   @brief Alias name for ESM group x channel 22
*
*   This is an alias name for the ESM group x channel 22.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL22 0x0000000000400000ULL

/** @def esmCHANNEL23
*   @brief Alias name for ESM group x channel 23
*
*   This is an alias name for the ESM group x channel 23.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL23 0x0000000000800000ULL

/** @def esmCHANNEL24
*   @brief Alias name for ESM group x channel 24
*
*   This is an alias name for the ESM group x channel 24.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL24 0x0000000001000000ULL

/** @def esmCHANNEL25
*   @brief Alias name for ESM group x channel 25
*
*   This is an alias name for the ESM group x channel 25.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL25 0x0000000002000000ULL

/** @def esmCHANNEL26
*   @brief Alias name for ESM group x channel 26
*
*   This is an alias name for the ESM group x channel 26.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL26 0x0000000004000000ULL

/** @def esmCHANNEL27
*   @brief Alias name for ESM group x channel 27
*
*   This is an alias name for the ESM group x channel 27.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL27 0x0000000008000000ULL

/** @def esmCHANNEL28
*   @brief Alias name for ESM group x channel 28
*
*   This is an alias name for the ESM group x channel 28.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL28 0x0000000010000000ULL

/** @def esmCHANNEL29
*   @brief Alias name for ESM group x channel 29
*
*   This is an alias name for the ESM group x channel 29.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL29 0x0000000020000000ULL

/** @def esmCHANNEL30
*   @brief Alias name for ESM group x channel 30
*
*   This is an alias name for the ESM group x channel 30.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL30 0x0000000040000000ULL

/** @def esmCHANNEL31
*   @brief Alias name for ESM group x channel 31
*
*   This is an alias name for the ESM group x channel 31.
*
*   @note This value should be used for API argument @a channel
*/
#define esmCHANNEL31 0x0000000080000000ULL

/* USER CODE BEGIN (1) */
/* USER CODE END */

/** 
 *  @defgroup ESM ESM
 *  @brief Error Signaling Module.
 *  
 *  The ESM module aggregates device errors and provides internal and external error response based on error severity.
 *
 *	Related Files
 *   - reg_esm.h
 *   - esm.h
 *   - esm.c
 *  @addtogroup ESM
 *  @{
 */
 
/* Esm Interface Functions */
void     esmInit(void);
uint32 esmError(void);
void     esmEnableError(uint32 channels);
void     esmDisableError(uint32 channels);
void     esmTriggerErrorPinReset(void);
void     esmActivateNormalOperation(void);
void     esmEnableInterrupt(uint32 channels);
void     esmDisableInterrupt(uint32 channels);
void     esmSetInterruptLevel(uint32 channels, uint32 flags);
void     esmClearStatus(uint32 group, uint32 channels);
void     esmClearStatusBuffer(uint32 channels);
void     esmSetCounterPreloadValue(uint32 value);

uint32 esmGetStatus(uint32 group, uint32 channels);
uint32 esmGetStatusBuffer(uint32 channels);


/** @fn void esmGroup1Notification(uint32 channel)
*   @brief Interrupt callback
*   @param[in] channel - Group 1 channel
*
* This is a callback that is provided by the application and is called upon
* an interrupt. The parameter passed to the callback is group 1 channel caused the interrupt.
*/
void esmGroup1Notification(uint32 channel);


/** @fn void esmGroup2Notification(uint32 channel)
*   @brief Interrupt callback
*   @param[in] channel - Group 2 channel
*
* This is a callback that is provided by the application and is called upon
* an interrupt. The parameter passed to the callback is group 2 channel caused the interrupt.
*/
void esmGroup2Notification(uint32 channel);

/**@}*/
/* USER CODE BEGIN (2) */
/* USER CODE END */


#endif
