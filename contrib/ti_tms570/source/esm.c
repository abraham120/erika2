/** @file esm.c 
*   @brief Esm Driver Source File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*   This file contains:
*   - API Functions
*   .
*   which are relevant for the Esm driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "esm.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void esmInit(void)
*   @brief Initializes Esm Driver
*
*   This function initializes the Esm driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void esmInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** - Disable error pin channels */
    esmREG->EPENACLR1 = 0xFFFFFFFFU;

    /** - Disable interrupts */
    esmREG->INTENACLR1 = 0xFFFFFFFFU;

    /** - Clear error status flags */
    esmREG->ESTATUS1[0U] = 0xFFFFFFFFU;
    esmREG->ESTATUS1[1U] = 0xFFFFFFFFU;
    esmREG->ESTATUS1[2U] = 0xFFFFFFFFU;

    /** - Setup LPC preload */
    esmREG->LTCPRELOAD = 16384U - 1U;

    /** - Reset error pin */
    if (esmREG->EPSTATUS == 0U)
    {
        esmREG->KEY = 0x00000005U;
    }
    else
    {
        esmREG->KEY = 0x00000000U;
    }

    /** - Clear interrupt level */
    esmREG->INTLVLCLR1 = 0xFFFFFFFFU;

    /** - Set interrupt level */
    esmREG->INTLVLSET1 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);


    /** - Enable error pin channels */
    esmREG->EPENASET1 = (0U << 31U)
                      | (0U << 30U)
                      | (0U << 29U)
                      | (0U << 28U)
                      | (0U << 27U)
                      | (0U << 26U)
                      | (0U << 25U)
                      | (0U << 24U)
                      | (0U << 23U)
                      | (0U << 22U)
                      | (0U << 21U)
                      | (0U << 20U)
                      | (0U << 19U)
                      | (0U << 18U)
                      | (0U << 17U)
                      | (0U << 16U)
                      | (0U << 15U)
                      | (0U << 14U)
                      | (0U << 13U)
                      | (0U << 12U)
                      | (0U << 11U)
                      | (0U << 10U)
                      | (0U <<  9U)
                      | (0U <<  8U)
                      | (0U <<  7U)
                      | (0U <<  6U)
                      | (0U <<  5U)
                      | (0U <<  4U)
                      | (0U <<  3U)
                      | (0U <<  2U)
                      | (0U <<  1U)
                      | (0U);


    /** - Enable interrupts */
    esmREG->INTENASET1 = (0U << 31U)
                       | (0U << 30U)
                       | (0U << 29U)
                       | (0U << 28U)
                       | (0U << 27U)
                       | (0U << 26U)
                       | (0U << 25U)
                       | (0U << 24U)
                       | (0U << 23U)
                       | (0U << 22U)
                       | (0U << 21U)
                       | (0U << 20U)
                       | (0U << 19U)
                       | (0U << 18U)
                       | (0U << 17U)
                       | (0U << 16U)
                       | (0U << 15U)
                       | (0U << 14U)
                       | (0U << 13U)
                       | (0U << 12U)
                       | (0U << 11U)
                       | (0U << 10U)
                       | (0U <<  9U)
                       | (0U <<  8U)
                       | (0U <<  7U)
                       | (0U <<  6U)
                       | (0U <<  5U)
                       | (0U <<  4U)
                       | (0U <<  3U)
                       | (0U <<  2U)
                       | (0U <<  1U)
                       | (0U);


/* USER CODE BEGIN (4) */
/* USER CODE END */
}


/** @fn uint32 esmError(void)
*   @brief Return Error status
*
*   @return The error status
*
*   Returns the error status.
*/
uint32 esmError(void)
{
    uint32 status;

/* USER CODE BEGIN (5) */
/* USER CODE END */

    status = esmREG->EPSTATUS;

/* USER CODE BEGIN (6) */
/* USER CODE END */

    return status;
}


/** @fn void esmEnableError(uint32 channels)
*   @brief Enable Group 1 Channels Error Signals propagation
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmEnableError(uint32 channels)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

    esmREG->EPENASET1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (8) */
/* USER CODE END */
}


/** @fn void esmDisableError(uint32 channels)
*   @brief Disable Group 1 Channels Error Signals propagation
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Error Signals propagation to the error pin.
*/
void esmDisableError(uint32 channels)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    esmREG->EPENACLR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (10) */
/* USER CODE END */
}


/** @fn void esmTriggerErrorPinReset(void)
*   @brief Trigger error pin reset and switch back to normal operation
*
*   Trigger error pin reset and switch back to normal operation.
*/
void esmTriggerErrorPinReset(void)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    esmREG->KEY = 5U;

/* USER CODE BEGIN (12) */
/* USER CODE END */
}


/** @fn void esmActivateNormalOperation(void)
*   @brief Activate normal operation
*
*   Activates normal operation mode.
*/
void esmActivateNormalOperation(void)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    esmREG->KEY = 0U;

/* USER CODE BEGIN (14) */
/* USER CODE END */
}


/** @fn void esmEnableInterrupt(uint32 channels)
*   @brief Enable Group 1 Channels Interrupts
*
*   @param[in] channels - Channel mask
*
*   Enable Group 1 Channels Interrupts.
*/
void esmEnableInterrupt(uint32 channels)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    esmREG->INTENASET1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (16) */
/* USER CODE END */
}


/** @fn void esmDisableInterrupt(uint32 channels)
*   @brief Disable Group 1 Channels Interrupts
*
*   @param[in] channels - Channel mask
*
*   Disable Group 1 Channels Interrupts.
*/
void esmDisableInterrupt(uint32 channels)
{
/* USER CODE BEGIN (17) */
/* USER CODE END */

    esmREG->INTENACLR1 = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (18) */
/* USER CODE END */
}


/** @fn void esmSetInterruptLevel(uint32 channels, uint32 flags)
*   @brief Set Group 1 Channels Interrupt Levels
*
*   @param[in] channels - Channel mask
*   @param[in] flags - Level mask: - 0: Low priority interrupt
*                                  - 1: High priority interrupt
*
*   Set Group 1 Channels Interrupts levels.
*/
void esmSetInterruptLevel(uint32 channels, uint32 flags)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    esmREG->INTLVLCLR1 = (uint32)((channels & (~flags)) & 0xFFFFFFFU);
    esmREG->INTLVLSET1 = (uint32)((channels & flags) & 0xFFFFFFFFU);

/* USER CODE BEGIN (20) */
/* USER CODE END */
}


/** @fn void esmClearStatus(uint32 group, uint32 channels)
*   @brief Clear Group error status
*
*   @param[in] group    - Error group
*   @param[in] channels - Channel mask
*
*   Clear Group error status.
*/
void esmClearStatus(uint32 group, uint32 channels)
{
/* USER CODE BEGIN (21) */
/* USER CODE END */

    esmREG->ESTATUS1[group] = (uint32)(channels & 0xFFFFFFFFU);

/* USER CODE BEGIN (22) */
/* USER CODE END */
}


/** @fn void esmSetCounterPreloadValue(uint32 value)
*   @brief Set counter preload value
*
*   @param[in] value - Counter preload value
*
*   Set counter preload value.
*/
void esmSetCounterPreloadValue(uint32 value)
{
/* USER CODE BEGIN (23) */
/* USER CODE END */

    esmREG->LTCPRELOAD = value & 0xC000U;

/* USER CODE BEGIN (24) */
/* USER CODE END */
}

/** @fn uint32 esmGetStatus(uint32 group, uint32 channels)
*   @brief Return Error status
*
*   @param[in] group   - Error group
*   @param[in] channels - Error Channels
*
*   @return The channels status of selected group
*
*   Returns the channels status of selected group.
*/
uint32 esmGetStatus(uint32 group, uint32 channels)
{
    uint32 status;

/* USER CODE BEGIN (25) */
/* USER CODE END */

    status = ((uint32)esmREG->ESTATUS1[group]) & channels;

/* USER CODE BEGIN (26) */
/* USER CODE END */

    return status;
}


/** @fn void esmLowInterrupt(void)
*   @brief High Level Interrupt for ESM
*/

#pragma CODE_STATE(esmHighInterrupt, 32)
#pragma INTERRUPT(esmHighInterrupt, FIQ)

void esmHighInterrupt(void)
{
    sint32 vec = esmREG->INTOFFH - 1;

/* USER CODE BEGIN (27) */
/* USER CODE END */

    if (vec >= 32U)
    {
        esmREG->ESTATUS1[1U] = 1U << (vec-32U);
        esmGroup2Notification(vec-32U);
    }
    else if (vec >= 0U)
    {
        esmREG->ESTATUS1[0U] = 1U << vec;
        esmGroup1Notification(vec);
    }
    else
    {
        esmREG->ESTATUS1[0U] = 0xFFFFFFFFU;
        esmREG->ESTATUS1[1U] = 0xFFFFFFFFU;
    }

/* USER CODE BEGIN (28) */
/* USER CODE END */
}


/** @fn void rtiCompare0Interrupt(void)
*   @brief Low Level Interrupt for ESM
*/


/* USER CODE BEGIN (32) */
/* USER CODE END */
