/** @file adc.c 
*   @brief ADC Driver Source File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*   This file contains:
*   - API Functions
*   - Interrupt Handlers
*   .
*   which are relevant for the ADC driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */


/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "adc.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void adcInit(void)
*   @brief Initializes ADC Driver
*
*   This function initializes the ADC driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void adcInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */
    /** @b Initialize @b ADC1: */

    /** - Reset ADC module */
    adcREG1->RSTCR = 1U;
    adcREG1->RSTCR = 0U;
 
	
    /** - Setup prescaler */
    adcREG1->CLOCKCR = 15U;
 
    /** - Setup memory boundaries */
    adcREG1->BNDCR  =(8U << 16U)|(8U + 8U);
    adcREG1->BNDEND = (adcREG1->BNDEND & 0xFFFF0000U) | (2U);
 
    /** - Setup event group conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[0U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup event group hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->G0SRC = 0x00000000U
                   | ADC_EVENT;

    /** - Setup event group sample window */
    adcREG1->G0SAMP = 0U;

    /** - Setup event group sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G0SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Setup group 1 conversion mode
    *     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
    */
    adcREG1->GxMODECR[1U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 1 hardware trigger
     *     - Setup hardware trigger edge
     *     - Setup hardware trigger source
     */
    adcREG1->G1SRC = 0x00000000U
                   | ADC_EVENT;

    /** - Setup group 1 sample window */
    adcREG1->G1SAMP = 0U;

    /** - Setup group 1 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G1SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Setup group 2 conversion mode
     *     - Setup data format
     *     - Enable/Disable channel id in conversion result
     *     - Enable/Disable continuous conversion
     */
    adcREG1->GxMODECR[2U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 2 hardware trigger
	*     - Setup hardware trigger edge
    *     - Setup hardware trigger source
	*/
    adcREG1->G2SRC = 0x00000000U
                   | ADC_EVENT;

    /** - Setup group 2 sample window */
    adcREG1->G2SAMP = 0U;

    /** - Setup group 2 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG1->G2SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Enable ADC module */
    adcREG1->OPMODECR = 0x00140001U;

    /** - Wait for buffer initialization complete */
    while (((adcREG1->BNDEND & 0xFFFF0000U) >> 16U ) != 0U) 
    { 
	} /* Wait */
    
    /** - Setup parity */
    adcREG1->PARCR = 0x00000005U;

    /** @b Initialize @b ADC2: */

    /** - Reset ADC module */
    adcREG2->RSTCR = 1U;
    adcREG2->RSTCR = 0U;
 
    /** - Setup prescaler */
    adcREG2->CLOCKCR = 15U;
 
    /** - Setup memory boundaries */
    adcREG2->BNDCR  =(8U << 16U)|(8U + 8U);
    adcREG2->BNDEND = (adcREG2->BNDEND & 0xFFFF0000U) | (2U);
 
    /** - Setup event group conversion mode
	*     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
	*/
    adcREG2->GxMODECR[0U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup event group hardware trigger
	*     - Setup hardware trigger edge
    *     - Setup hardware trigger source
	*/
    adcREG2->G0SRC = 0x00000000U
                   | ADC_EVENT;

    /** - Setup event group sample window */
    adcREG2->G0SAMP = 0U;

    /** - Setup event group sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG2->G0SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Setup group 1 conversion mode
	*     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
	*/
    adcREG2->GxMODECR[1U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 1 hardware trigger
	*     - Setup hardware trigger edge
    *     - Setup hardware trigger source
	*/
    adcREG2->G1SRC = 0x00000000U
                   | ADC_EVENT;

    /** - Setup group 1 sample window */
    adcREG2->G1SAMP = 0U;

    /** - Setup group 1 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG2->G1SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Setup group 2 conversion mode
	*     - Setup data format
    *     - Enable/Disable channel id in conversion result
    *     - Enable/Disable continuous conversion
	*/
    adcREG2->GxMODECR[2U] = ADC_12_BIT
                          | 0x00000000U
                          | 0x00000000U
                          | 0x00000000U;

    /** - Setup group 2 hardware trigger
	*     - Setup hardware trigger edge
    *     - Setup hardware trigger source
	*/
    adcREG2->G2SRC = 0x00000000U
                   | ADC_EVENT;

    /** - Setup group 2 sample window */
    adcREG2->G2SAMP = 0U;

    /** - Setup group 2 sample discharge 
    *     - Setup discharge prescaler
    *     - Enable/Disable discharge
    */
    adcREG2->G2SAMPDISEN = (0U << 8U)
                         | 0x00000000U;

    /** - Enable ADC module */
    adcREG2->OPMODECR = 0x00140001U;

    /** - Wait for buffer initialization complete */
    while (((adcREG2->BNDEND & 0xFFFF0000U) >> 16U) != 0U)
    { 
	} /* Wait */
    
    /** - Setup parity */
    adcREG2->PARCR = 0x00000005U;

    /**   @note This function has to be called before the driver can be used.\n
    *           This function has to be executed in privileged mode.\n
    */
/* USER CODE BEGIN (4) */
/* USER CODE END */
}

/* USER CODE BEGIN (5) */
/* USER CODE END */


/** - s_adcSelect is used as constant table for channel selection */
static const uint32 s_adcSelect[2U][3U] =
{
    {0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U},
    {0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U,
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U |
    0x00000000U}
};

/** - s_adcFiFoSize is used as constant table for channel selection */
static const uint32 s_adcFiFoSize[2U][3U] =
{
    {16U,
    16U,
    16U},
    {16U,
    16U,
    16U}
};

/* USER CODE BEGIN (6) */
/* USER CODE END */

/** @fn void adcStartConversion(adcBASE_t *adc, uint32 group)
*   @brief Starts an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function starts a conversion of the ADC hardware group.
*
*/
void adcStartConversion(adcBASE_t *adc, uint32 group)
{
    uint32 index = adc == adcREG1 ? 0U : 1U;

/* USER CODE BEGIN (7) */
/* USER CODE END */

    /** - Setup FiFo size */
    adc->GxINTCR[group] = s_adcFiFoSize[index][group];

    /** - Start Conversion */
    adc->GxSEL[group] = s_adcSelect[index][group];

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (8) */
/* USER CODE END */
}

/* USER CODE BEGIN (9) */
/* USER CODE END */


/** @fn void adcStopConversion(adcBASE_t *adc, uint32 group)
*   @brief Stops an ADC conversion
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function stops a conversion of the ADC hardware group.
*
*/
void adcStopConversion(adcBASE_t *adc, uint32 group)
{
/* USER CODE BEGIN (10) */
/* USER CODE END */

    /** - Stop Conversion */
    adc->GxSEL[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (11) */
/* USER CODE END */
}

/* USER CODE BEGIN (12) */
/* USER CODE END */


/** @fn void adcResetFiFo(adcBASE_t *adc, uint32 group)
*   @brief Resets FiFo read and write pointer.
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function resets the FiFo read and write pointers.
*
*/
void adcResetFiFo(adcBASE_t *adc, uint32 group)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    /** - Reset FiFo */
    adc->GxFIFORESETCR[group] = 1U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           the conversion should be stopped before calling this function. 
    */

/* USER CODE BEGIN (14) */
/* USER CODE END */
}

/* USER CODE BEGIN (15) */
/* USER CODE END */


/** @fn uint32 adcGetData(adcBASE_t *adc, uint32 group, adcData_t * data)
*   @brief Gets converted a ADC values
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @param[out] data Pointer to store ADC converted data
*   @return The function will return the number of converted values copied into data buffer:
*
*   This function writes a ADC message into a ADC message box.
*
*/
uint32 adcGetData(adcBASE_t *adc, uint32 group, adcData_t * data)
{
    uint32       i;
    uint32  buf;
    uint32  index = adc == adcREG1 ? 0U : 1U;
    uint32       count = (adc->GxINTCR[group] >= 256U) ? s_adcFiFoSize[index][group] : (s_adcFiFoSize[index][group] - (uint32)(adc->GxINTCR[group] & 0xFF));
    adcData_t *ptr = data; 

/* USER CODE BEGIN (16) */
/* USER CODE END */

        /** -  Get conversion data and channel/pin id */
        for (i = 0U; i < count; i++)
        {
          buf        = adc->GxBUF[group].BUF0;
          ptr->value = (uint16)(buf & 0xFFFU);
          ptr->id    = (uint32)((buf >> 16U) & 0x1FU);
          ptr++;
        }

    adc->GxINTFLG[group] = 9U;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           The user is responsible to initialize the message box.
    */

/* USER CODE BEGIN (17) */
/* USER CODE END */

    return count;
}

/* USER CODE BEGIN (18) */
/* USER CODE END */


/** @fn uint32 adcIsFifoFull(adcBASE_t *adc, uint32 group)
*   @brief Checks if FiFo buffer is full
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When FiFo buffer is not full   
*           - 1: When FiFo buffer is full   
*           - 3: When FiFo buffer overflow occurred    
*
*   This function checks FiFo buffer status.
*
*/
uint32 adcIsFifoFull(adcBASE_t *adc, uint32 group)
{
    uint32 flags;

/* USER CODE BEGIN (19) */
/* USER CODE END */

    /** - Read FiFo flags */
    flags = adc->GxINTFLG[group] & 3U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (20) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (21) */
/* USER CODE END */


/** @fn uint32 adcIsConversionComplete(adcBASE_t *adc, uint32 group)
*   @brief Checks if Conversion is complete
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*   @return The function will return:
*           - 0: When is not finished   
*           - 8: When conversion is complete   
*
*   This function checks if conversion is complete.
*
*/
uint32 adcIsConversionComplete(adcBASE_t *adc, uint32 group)
{
    uint32 flags;

/* USER CODE BEGIN (22) */
/* USER CODE END */

    /** - Read conversion flags */
    flags = adc->GxINTFLG[group] & 8U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (23) */
/* USER CODE END */

    return flags;
}

/* USER CODE BEGIN (24) */
/* USER CODE END */


/** @fn void adcEnableNotification(adcBASE_t *adc, uint32 group)
*   @brief Enable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will enable the notification of a conversion.
*   In single conversion mode for conversion complete and
*   in continuous conversion mode when the FiFo buffer is full.
*
*/
void adcEnableNotification(adcBASE_t *adc, uint32 group)
{
    uint32 notif = (((uint32)(adc->GxMODECR[group]) & 2U) == 2U) ? 1U : 8U;

/* USER CODE BEGIN (25) */
/* USER CODE END */

    adc->GxINTENA[group] = notif;

    /**   @note The function adcInit has to be called before this function can be used.\n
    *           This function should be called before the conversion is started
    */

/* USER CODE BEGIN (26) */
/* USER CODE END */
}

/* USER CODE BEGIN (27) */
/* USER CODE END */


/** @fn void adcDisableNotification(adcBASE_t *adc, uint32 group)
*   @brief Disable notification
*   @param[in] adc Pointer to ADC module:
*              - adcREG1: ADC1 module pointer
*              - adcREG2: ADC2 module pointer
*              - adcREG3: ADC3 module pointer
*   @param[in] group Hardware group of ADC module:
*              - adcGROUP0: ADC event group
*              - adcGROUP1: ADC group 1
*              - adcGROUP2: ADC group 2
*
*   This function will disable the notification of a conversion.
*/
void adcDisableNotification(adcBASE_t *adc, uint32 group)
{
/* USER CODE BEGIN (28) */
/* USER CODE END */

    adc->GxINTENA[group] = 0U;

    /**   @note The function adcInit has to be called before this function can be used. */

/* USER CODE BEGIN (29) */
/* USER CODE END */
}

/* USER CODE BEGIN (30) */
/* USER CODE END */


/** @fn void adc1Group0Interrupt(void)
*   @brief ADC1 Event Group Interrupt Handler
*/

/* USER CODE BEGIN (31) */
/* USER CODE END */


void adc1Group0Interrupt(void)
{
/* USER CODE BEGIN (32) */
/* USER CODE END */
    
    adcREG1->GxINTFLG[0U] = 9U;

    adcNotification(adcREG1, adcGROUP0);

/* USER CODE BEGIN (33) */
/* USER CODE END */
}

/* USER CODE BEGIN (34) */
/* USER CODE END */


/** @fn void adc1Group1Interrupt(void)
*   @brief ADC1 Group 1 Interrupt Handler
*/

/* USER CODE BEGIN (35) */
/* USER CODE END */


void adc1Group1Interrupt(void)
{
/* USER CODE BEGIN (36) */
/* USER CODE END */
    
    adcREG1->GxINTFLG[1U] = 9U;

    adcNotification(adcREG1, adcGROUP1);

/* USER CODE BEGIN (37) */
/* USER CODE END */
}

/* USER CODE BEGIN (38) */
/* USER CODE END */


/** @fn void adc1Group2Interrupt(void)
*   @brief ADC1 Group 2 Interrupt Handler
*/

/* USER CODE BEGIN (39) */
/* USER CODE END */


void adc1Group2Interrupt(void)
{
/* USER CODE BEGIN (40) */
/* USER CODE END */
    
    adcREG1->GxINTFLG[2U] = 9U;

    adcNotification(adcREG1, adcGROUP2);

/* USER CODE BEGIN (41) */
/* USER CODE END */
}

/* USER CODE BEGIN (42) */
/* USER CODE END */


/** @fn void adc2Group0Interrupt(void)
*   @brief ADC2 Event Group Interrupt Handler
*/

/* USER CODE BEGIN (43) */
/* USER CODE END */


void adc2Group0Interrupt(void)
{
/* USER CODE BEGIN (44) */
/* USER CODE END */
    
    adcREG2->GxINTFLG[0U] = 9U;

    adcNotification(adcREG2, adcGROUP0);

/* USER CODE BEGIN (45) */
/* USER CODE END */
}

/* USER CODE BEGIN (46) */
/* USER CODE END */


/** @fn void adc2Group1Interrupt(void)
*   @brief ADC2 Group 1 Interrupt Handler
*/

/* USER CODE BEGIN (47) */
/* USER CODE END */


void adc2Group1Interrupt(void)
{
/* USER CODE BEGIN (48) */
/* USER CODE END */
    
    adcREG2->GxINTFLG[1U] = 9U;

    adcNotification(adcREG2, adcGROUP1);

/* USER CODE BEGIN (49) */
/* USER CODE END */
}

/* USER CODE BEGIN (50) */
/* USER CODE END */


/** @fn void adc2Group2Interrupt(void)
*   @brief ADC2 Group 2 Interrupt Handler
*/

/* USER CODE BEGIN (51) */
/* USER CODE END */


void adc2Group2Interrupt(void)
{
/* USER CODE BEGIN (52) */
/* USER CODE END */
    
    adcREG2->GxINTFLG[2U] = 9U;

    adcNotification(adcREG2, adcGROUP2);

/* USER CODE BEGIN (53) */
/* USER CODE END */
}

/* USER CODE BEGIN (54) */
/* USER CODE END */

