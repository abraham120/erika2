/** @file rti.c 
*   @brief RTI Driver Source File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the RTI driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */


/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "rti.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void rtiInit(void)
*   @brief Initializes RTI Driver
*
*   This function initializes the RTI driver.
*
*/

/* USER CODE BEGIN (2) */
/*
void __attribute__((weak)) rtiNotificationCompare0(void){};
void __attribute__((weak)) rtiNotificationCompare1(void){};
void __attribute__((weak)) rtiNotificationCompare2(void){};
void __attribute__((weak)) rtiNotificationCompare3(void){};
void __attribute__((weak)) rtiNotificationTimebase(void){};
void __attribute__((weak)) rtiNotificationOverflow5(void){};
void __attribute__((weak)) rtiNotificationOverflow1(void){};
*/
#pragma WEAK(rtiCompare0Interrupt)
#pragma WEAK(rtiCompare1Interrupt)
#pragma WEAK(rtiCompare2Interrupt)
#pragma WEAK(rtiCompare3Interrupt)

/* USER CODE END */

void rtiInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */
    /** @b Initialize @b RTI1: */

    /** - Setup NTU source, debug options and disable both counter blocks */
    rtiREG1->GCTRL = (1U << 16U) | 0x00000000U;

    /** - Setup timebase for free running counter 0 */
    rtiREG1->TBCTRL = 0x00000000U;

    /** - Enable/Disable capture event sources for both counter blocks */
    rtiREG1->CAPCTRL = 0U | 0U;

    /** - Setup input source compare 0-3 */
    rtiREG1->COMPCTRL = 0x00001000U | 0x00000100U | 0x00000000U | 0x00000000U;

    /** - Reset up counter 0 */
    rtiREG1->CNT[0U].UCx = 0x00000000U;

    /** - Reset free running counter 0 */
    rtiREG1->CNT[0U].FRCx = 0x00000000U;

    /** - Setup up counter 0 compare value 
    *     - 0x00000000: Divide by 2^32
    *     - 0x00000001-0xFFFFFFFF: Divide by (CPUC0 + 1)
    */
    rtiREG1->CNT[0U].CPUCx = 15U;

    /** - Reset up counter 1 */
    rtiREG1->CNT[1U].UCx = 0x00000000U;

    /** - Reset free running counter 1 */
    rtiREG1->CNT[1U].FRCx  = 0x00000000U;

    /** - Setup up counter 1 compare value 
    *     - 0x00000000: Divide by 2^32
    *     - 0x00000001-0xFFFFFFFF: Divide by (CPUC1 + 1)
    */
    rtiREG1->CNT[1U].CPUCx = 15U;

    /** - Setup compare 0 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[0U].COMPx = 1000000U;

    /** - Setup update compare 0 value. This value is added to the compare 0 value on each compare match. */
    rtiREG1->CMP[0U].UDCPx = 1000000U;

    /** - Setup compare 1 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[1U].COMPx = 2000000U;

    /** - Setup update compare 1 value. This value is added to the compare 1 value on each compare match. */
    rtiREG1->CMP[1U].UDCPx = 2000000U;

    /** - Setup compare 2 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[2U].COMPx = 3000000U;

    /** - Setup update compare 2 value. This value is added to the compare 2 value on each compare match. */
    rtiREG1->CMP[2U].UDCPx = 3000000U;

    /** - Setup compare 3 value. This value is compared with selected free running counter. */
    rtiREG1->CMP[3U].COMPx = 4000000U;

    /** - Setup update compare 3 value. This value is added to the compare 3 value on each compare match. */
    rtiREG1->CMP[3U].UDCPx = 4000000U;

    /** - Clear all pending interrupts */
    rtiREG1->INTFLAG = 0x0007000FU;

    /** - Disable all interrupts */
    rtiREG1->CLEARINT = 0x00070F0FU;

    /**   @note This function has to be called before the driver can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           This function does not start the counters.
    */

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** @fn void rtiStartCounter(uint32 counter)
*   @brief Starts RTI Counter block
*   @param[in] counter Select counter block to be started:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be started
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be started
*
*   This function starts selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (6) */
/* USER CODE END */

void rtiStartCounter(uint32 counter)
{
/* USER CODE BEGIN (7) */
/* USER CODE END */

    rtiREG1->GCTRL |= (1U << (counter & 3U));

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */


/** @fn void rtiStopCounter(uint32 counter)
*   @brief Stops RTI Counter block
*   @param[in] counter Select counter to be stopped:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be stopped
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be stopped
*
*   This function stops selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (10) */
/* USER CODE END */

void rtiStopCounter(uint32 counter)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    rtiREG1->GCTRL &= ~(1U << (counter & 3U));

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (12) */
/* USER CODE END */
}

/* USER CODE BEGIN (13) */
/* USER CODE END */


/** @fn uint32 rtiResetCounter(uint32 counter)
*   @brief Reset RTI Counter block
*   @param[in] counter Select counter block to be reset:
*              - rtiCOUNTER_BLOCK0: RTI counter block 0 will be reset
*              - rtiCOUNTER_BLOCK1: RTI counter block 1 will be reset
*   @return The function will return:
*           - 0: When the counter reset wasn't successful   
*           - 1: When the counter reset was successful   
*
*   This function resets selected counter block of the selected RTI module.
*/

/* USER CODE BEGIN (14) */
/* USER CODE END */

uint32 rtiResetCounter(uint32 counter)
{
    uint32 success = 0U;

/* USER CODE BEGIN (15) */
/* USER CODE END */

    if ((!(rtiREG1->GCTRL & (1U << (counter & 3U)))) != 0U)
    {
        rtiREG1->CNT[counter].UCx = 0x00000000U;
        rtiREG1->CNT[counter].FRCx = 0x00000000U;

        success = 1U;
    }

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           The selected counter block has to be stopped before it can reset.
    */

/* USER CODE BEGIN (16) */
/* USER CODE END */

    return success;
}

/* USER CODE BEGIN (17) */
/* USER CODE END */


/** @fn void rtiSetPeriod(uint32 compare, uint32 period)
*   @brief Set new period of RTI compare
*   @param[in] compare Select compare to change period:
*              - rtiCOMPARE0: RTI compare 0 will change the period
*              - rtiCOMPARE1: RTI compare 1 will change the period
*              - rtiCOMPARE2: RTI compare 2 will change the period
*              - rtiCOMPARE3: RTI compare 3 will change the period
*   @param[in] period new period in [ticks - 1]:
*              - 0x00000000: Divide by 1
*              - n: Divide by n + 1
*
*   This function will change the period of the selected compare.
*/

/* USER CODE BEGIN (18) */
/* USER CODE END */

void rtiSetPeriod(uint32 compare, uint32 period)
{
/* USER CODE BEGIN (19) */
/* USER CODE END */

    rtiREG1->CMP[compare].UDCPx = period;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.\n
    *           When the corresponding counter block is not stopped,\n
    *           the period will change on the next compare match of the old period.
    */

/* USER CODE BEGIN (20) */
/* USER CODE END */
}

/* USER CODE BEGIN (21) */
/* USER CODE END */


/** @fn uint32 rtiGetPeriod(uint32 compare)
*   @brief Get current period of RTI compare
*   @param[in] compare Select compare to return the current period:
*              - rtiCOMPARE0: RTI compare 0 will return the current period
*              - rtiCOMPARE1: RTI compare 1 will return the current period
*              - rtiCOMPARE2: RTI compare 2 will return the current period
*              - rtiCOMPARE3: RTI compare 3 will return the current period
*   @return Current period of selected compare in [ticks - 1]:
*           - 0x00000000: Divide by 1
*           - n: Divide by n + 1
*
*   This function will return the period of the selected compare.
*/

/* USER CODE BEGIN (22) */
/* USER CODE END */

uint32 rtiGetPeriod(uint32 compare)
{
    uint32 period;

/* USER CODE BEGIN (23) */
/* USER CODE END */

    period = rtiREG1->CMP[compare].UDCPx;

    /**   @note The function rtiInit has to be called before this function can be used.
    */

/* USER CODE BEGIN (24) */
/* USER CODE END */

    return period;
}

/* USER CODE BEGIN (25) */
/* USER CODE END */


/** @fn uint32 rtiGetCurrentTick(uint32 compare)
*   @brief Get current tick of RTI compare
*   @param[in] compare Select compare to return the current tick:
*              - rtiCOMPARE0: RTI compare 0 will return the current tick
*              - rtiCOMPARE1: RTI compare 1 will return the current tick
*              - rtiCOMPARE2: RTI compare 2 will return the current tick
*              - rtiCOMPARE3: RTI compare 3 will return the current tick
*   @return Current tick of selected compare
*
*   This function will return the current of the selected compare.
*/

/* USER CODE BEGIN (26) */
/* USER CODE END */

uint32 rtiGetCurrentTick(uint32 compare)
{
    uint32 tick;
    uint32 counter = ((rtiREG1->COMPCTRL & (1U << (compare << 2U))) !=0U ) ? 1U : 0U;

/* USER CODE BEGIN (27) */
/* USER CODE END */

    tick = rtiREG1->CNT[counter].FRCx - (rtiREG1->CMP[compare].COMPx - rtiREG1->CMP[compare].UDCPx);

    /**   @note The function rtiInit has to be called before this function can be used.
    */

/* USER CODE BEGIN (28) */
/* USER CODE END */

    return tick;
}

/* USER CODE BEGIN (29) */
/* USER CODE END */


/** @fn void rtiEnableNotification(uint32 notification)
*   @brief Enable notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   This function will enable the selected notification of a RTI module.
*   It is possible to enable multiple notifications masked.
*/

/* USER CODE BEGIN (30) */
/* USER CODE END */

void rtiEnableNotification(uint32 notification)
{
/* USER CODE BEGIN (31) */
/* USER CODE END */

    rtiREG1->INTFLAG = notification;
    rtiREG1->SETINT   = notification;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (32) */
/* USER CODE END */
}

/* USER CODE BEGIN (33) */
/* USER CODE END */

/** @fn void rtiDisableNotification(uint32 notification)
*   @brief Disable notification of RTI module
*   @param[in] notification Select notification of RTI module:
*              - rtiNOTIFICATION_COMPARE0: RTI compare 0 notification
*              - rtiNOTIFICATION_COMPARE1: RTI compare 1 notification
*              - rtiNOTIFICATION_COMPARE2: RTI compare 2 notification
*              - rtiNOTIFICATION_COMPARE3: RTI compare 3 notification
*              - rtiNOTIFICATION_TIMEBASE: RTI Timebase notification
*              - rtiNOTIFICATION_COUNTER0: RTI counter 0 overflow notification
*              - rtiNOTIFICATION_COUNTER1: RTI counter 1 overflow notification
*
*   This function will disable the selected notification of a RTI module.
*   It is possible to disable multiple notifications masked.
*/

/* USER CODE BEGIN (34) */
/* USER CODE END */

void rtiDisableNotification(uint32 notification)
{
/* USER CODE BEGIN (35) */
/* USER CODE END */

    rtiREG1->CLEARINT = notification;

    /**   @note The function rtiInit has to be called before this function can be used.\n
    *           This function has to be executed in privileged mode.
    */

/* USER CODE BEGIN (36) */
/* USER CODE END */
}

/* USER CODE BEGIN (37) */
/* USER CODE END */


/** @fn void rtiCompare0Interrupt(void)
*   @brief RTI1 Compare 0 Interrupt Handler
*
*   RTI1 Compare 0 interrupt handler 
*
*/

/* USER CODE BEGIN (38) */
/* USER CODE END */


void rtiCompare0Interrupt(void)
{
/* USER CODE BEGIN (39) */
/* USER CODE END */

    rtiREG1->INTFLAG = 1U;
    rtiNotification(rtiNOTIFICATION_COMPARE0);

/* USER CODE BEGIN (40) */
    //rtiNotificationCompare0();
/* USER CODE END */
}

/* USER CODE BEGIN (41) */
/* USER CODE END */


/** @fn void rtiCompare1Interrupt(void)
*   @brief RTI1 Compare 1 Interrupt Handler
*
*   RTI1 Compare 1 interrupt handler 
*
*/

/* USER CODE BEGIN (42) */
/* USER CODE END */


void rtiCompare1Interrupt(void)
{
/* USER CODE BEGIN (43) */
/* USER CODE END */

    rtiREG1->INTFLAG = 2U;
    rtiNotification(rtiNOTIFICATION_COMPARE1);

/* USER CODE BEGIN (44) */
//    rtiNotificationCompare1();
/* USER CODE END */
}

/* USER CODE BEGIN (45) */

/* USER CODE END */


/** @fn void rtiCompare2Interrupt(void)
*   @brief RTI1 Compare 2 Interrupt Handler
*
*   RTI1 Compare 2 interrupt handler 
*
*/

/* USER CODE BEGIN (46) */
/* USER CODE END */


void rtiCompare2Interrupt(void)
{
/* USER CODE BEGIN (47) */
/* USER CODE END */

    rtiREG1->INTFLAG = 4U;
    rtiNotification(rtiNOTIFICATION_COMPARE2);

/* USER CODE BEGIN (48) */
//    rtiNotificationCompare2();
/* USER CODE END */
}

/* USER CODE BEGIN (49) */
/* USER CODE END */


/** @fn void rtiCompare3Interrupt(void)
*   @brief RTI1 Compare 3 Interrupt Handler
*
*   RTI1 Compare 3 interrupt handler 
*
*/

/* USER CODE BEGIN (50) */
/* USER CODE END */


void rtiCompare3Interrupt(void)
{
/* USER CODE BEGIN (51) */
///* USER CODE END */

    rtiREG1->INTFLAG = 8U;
    rtiNotification(rtiNOTIFICATION_COMPARE3);

/* USER CODE BEGIN (52) */
///* USER CODE END */
}

/* USER CODE BEGIN (53) */
/* USER CODE END */


/** @fn void rtiTimebaseInterrupt(void)
*   @brief RTI1 Timebase Interrupt Handler
*
*   RTI1 timebase interrupt handler 
*
*/

/* USER CODE BEGIN (54) */
/* USER CODE END */


void rtiTimebaseInterrupt(void)
{
/* USER CODE BEGIN (55) */
/* USER CODE END */

    rtiREG1->INTFLAG = 0x10000U;
    rtiNotification(rtiNOTIFICATION_TIMEBASE);

/* USER CODE BEGIN (56) */
    //rtiNotificationTimebase();
/* USER CODE END */
}

/* USER CODE BEGIN (57) */
/* USER CODE END */


/** @fn void rtiOverflow5Interrupt(void)
*   @brief RTI1 Counter 0 overflow Interrupt Handler
*
*   RTI1 counter 0 overflow interrupt handler 
*
*/

/* USER CODE BEGIN (58) */
/* USER CODE END */


void rtiOverflow5Interrupt(void)
{
/* USER CODE BEGIN (59) */
/* USER CODE END */

    rtiREG1->INTFLAG = 0x20000U;
    rtiNotification(rtiNOTIFICATION_COUNTER0);

/* USER CODE BEGIN (60) */
    //rtiNotificationOverflow5();
/* USER CODE END */
}

/* USER CODE BEGIN (61) */
/* USER CODE END */


/** @fn void rtiOverflow1Interrupt(void)
*   @brief RTI1 Counter 1 overflow Interrupt Handler
*
*   RTI1 counter 1 overflow interrupt handler 
*
*/

/* USER CODE BEGIN (62) */
/* USER CODE END */


void rtiOverflow1Interrupt(void)
{
/* USER CODE BEGIN (63) */
/* USER CODE END */

    rtiREG1->INTFLAG = 0x40000U;
    rtiNotification(rtiNOTIFICATION_COUNTER1);

/* USER CODE BEGIN (64) */
    //rtiNotificationOverflow1();
/* USER CODE END */
}

/* USER CODE BEGIN (65) */
/* USER CODE END */

