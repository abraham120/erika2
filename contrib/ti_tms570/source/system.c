/** @file system.c 
*   @brief System Driver Source File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*   This file contains:
*   - API Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* Include Files */

#include "system.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */


/** @fn void systemInit(void)
*   @brief Initializes System Driver
*
*   This function initializes the System driver.
*
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void systemInit(void)
{
/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** @b Initialize @b Flash @b Wrapper: */

    /** - Setup flash read mode, address wait states and data wait states */
    flashWREG->FRDCNTL =  0x01000000U 
                       | (3U << 8U) 
                       | (1U << 4U) 
                       |  1U;

    /** - Setup flash bank power modes */
    flashWREG->FBFALLBACK = 0x05050000
                          | (SYS_SLEEP << 14U) 
                          | (SYS_SLEEP << 12U) 
                          | (SYS_SLEEP << 10U) 
                          | (SYS_SLEEP << 8U) 
                          | (SYS_ACTIVE << 6U) 
                          | (SYS_ACTIVE << 4U) 
                          | (SYS_ACTIVE << 2U) 
                          |  SYS_ACTIVE;

    /** @b Initialize @b Lpo: */

    systemREG1->LPOMONCTL = (1U << 24U)
                          | (8U << 8U)
                          |  8U;

    /** @b Initialize @b Secondary Pll: */

    systemREG2->PLLCTL3 = ((2U - 1U) << 22U)
                        | ((10U - 1U) << 8U)
                        |  (1U - 1U);


    /** @b Initialize @b Pll: */

    /** - Setup pll control register 1:
    *     - Setup reset on oscillator slip 
    *     - Setup bypass on pll slip
    *     - Setup Pll output clock divider
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider 
    *     - Setup Pll multiplier          
    */
    systemREG1->PLLCTL1 =  0x00000000U 
                        |  0x20000000U 
                        | (0U << 24U) 
                        |  0x00000000U 
                        | (5U << 16U) 
                        | (119U << 8U);

    /** - Setup pll control register 1 
    *     - Enable/Disable frequency modulation
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    systemREG1->PLLCTL2 = 0x00000000U
                        | (255U << 22U)
                        | (7U << 12U)
                        | (1U << 9U)
                        |  61U;


    /** @b Initialize @b Clock @b Tree: */

    /** - Start clock source lock */
    systemREG1->CSDIS = 0x00000000U 
                      | 0x00000000U 
                      | 0x00000000U 
                      | 0x00000008U 
                      | 0x00000004U 
                      | 0x00000000U 
                      | 0x00000000U;

    /** - Wait for until clocks are locked */
    while ((systemREG1->CSVSTAT & ((systemREG1->CSDIS ^ 0xFF) & 0xFF)) != ((systemREG1->CSDIS ^ 0xFF) & 0xFF));

    /** - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    systemREG1->GHVSRC = (SYS_OSC << 24U) 
                       | (SYS_OSC << 16U) 
                       |  SYS_PLL;

    /** - Power-up all peripherals */
    pcrREG->PSPWRDWNCLR0 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR1 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR2 = 0xFFFFFFFFU;
    pcrREG->PSPWRDWNCLR3 = 0xFFFFFFFFU;

    /** - Setup synchronous peripheral clock dividers for VCLK1 and VCLK2 */
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xFFF0FFFFU) 
                         | (15U << 16U); 
    systemREG1->CLKCNTL  = (systemREG1->CLKCNTL & 0xF0F0FFFFU) 
						 | (0U << 24U)  
						 | (0U << 16U);  

    /** - Setup RTICLK1 and RTICLK2 clocks */
    systemREG1->RCLKSRC = (1U << 24U)
                        | (SYS_VCLK << 16U) 
                        | (0U << 8U)  
                        |  SYS_VCLK;

    /** - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    systemREG1->VCLKASRC = (SYS_PLL << 8U)
                         |  SYS_VCLK;

    /** - Enable Peripherals */
    systemREG1->CLKCNTL |= 1U << 8U;

    /** - set ECLK pins functional mode */
    systemREG1->SYSPC1 = 0U;

    /** - set ECLK pins default output value */
    systemREG1->SYSPC4 = 0U;

    /** - set ECLK pins output direction */
    systemREG1->SYSPC2 = 1U;

    /** - set ECLK pins open drain enable */
    systemREG1->SYSPC7 = 0U;

    /** - set ECLK pins pullup/pulldown enable */
    systemREG1->SYSPC8 = 0U;

    /** - set ECLK pins pullup/pulldown select */
    systemREG1->SYSPC9 = 1U;

    /** - Setup ECLK */
    systemREG1->ECPCNTL = (0U << 24U)
                        | (0U << 23U)
                        | ((8U - 1U) & 0xFFFFU);

    /** @note: HCLK >= VCLK2 >= VCLK_sys */

/* USER CODE BEGIN (4) */
/* USER CODE END */
}

void systemPowerDown(uint32 mode)
{
/* USER CODE BEGIN (5) */
/* USER CODE END */
    /* Disable clock sources */
    systemREG1->CSDISSET = mode & 0x000000FFU;

    /* Disable clock domains */
    systemREG1->CDDIS = (mode >> 8U) & 0x00000FFFU;

    /* Idle CPU */
	/*SAFETYMCUSW 88 S MR:2.1 <REVIEWED> "Assembly in C needed" */
    asm(" wfi");
/* USER CODE BEGIN (6) */
/* USER CODE END */
}


/* USER CODE BEGIN (7) */
/* USER CODE END */
