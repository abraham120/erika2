/** @file gio.c 
*   @brief GIO Driver Implementation File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "gio.h"

/* USER CODE BEGIN (1) */
#pragma WEAK(gioLowLevelInterrupt)
/* USER CODE END */

/** @fn void gioInit(void)
*   @brief Initializes the GIO Driver
*
*   This function initializes the GIO module and set the GIO ports 
*   to the initial values.
*/
void gioInit(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */
    /** bring GIO module out of reset */
    gioREG->GCR0      = 1U;
    gioREG->INTENACLR = 0xFFU;
    gioREG->LVLCLR    = 0xFFU;              

    /** @b initialize @b Port @b A */

    /** - Port A output values */
    gioPORTA->DOUT =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (0U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U); /* Bit 7 */

    /** - Port A direction */
    gioPORTA->DIR  =  1U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (0U << 2U)  /* Bit 2 */
                   | (1U << 3U)  /* Bit 3 */
                   | (1U << 4U)  /* Bit 4 */
                   | (1U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U); /* Bit 7 */

    /** - Port A open drain enable */
    gioPORTA->PDR  =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (0U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U); /* Bit 7 */

    /** - Port A pullup / pulldown selection */
    gioPORTA->PSL  =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (1U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (1U << 6U)  /* Bit 6 */
                   | (1U << 7U); /* Bit 7 */

    /** - Port A pullup / pulldown enable*/
    gioPORTA->PULDIS  =  0U         /* Bit 0 */
                      | (0U << 1U)  /* Bit 1 */
                      | (0U << 2U)  /* Bit 2 */
                      | (0U << 3U)  /* Bit 3 */
                      | (0U << 4U)  /* Bit 4 */
                      | (0U << 5U)  /* Bit 5 */
                      | (0U << 6U)  /* Bit 6 */
                      | (0U << 7U); /* Bit 7 */

    /** @b initialize @b Port @b B */

    /** - Port B output values */
    gioPORTB->DOUT =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (0U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U); /* Bit 7 */

    /** - Port B direction */
    gioPORTB->DIR  =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (1U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U); /* Bit 7 */

    /** - Port B open drain enable */
    gioPORTB->PDR  =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (0U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U); /* Bit 7 */

    /** - Port B pullup / pulldown selection */
    gioPORTB->PSL  =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (0U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U); /* Bit 7 */

    /** - Port B pullup / pulldown enable*/
    gioPORTB->PULDIS  =  0U         /* Bit 0 */
                      | (0U << 1U)  /* Bit 1 */
                      | (0U << 2U)  /* Bit 2 */
                      | (0U << 3U)  /* Bit 3 */
                      | (0U << 4U)  /* Bit 4 */
                      | (0U << 5U)  /* Bit 5 */
                      | (0U << 6U)  /* Bit 6 */
                      | (0U << 7U); /* Bit 7 */

/* USER CODE BEGIN (3) */
/* USER CODE END */

    /** @b initialize @b interrupts */

    /** - interrupt polarity */
    gioREG->POL =  0U         /* Bit 0 */
                | (0U << 1U)  /* Bit 1 */
                | (0U << 2U)  /* Bit 2 */
                | (0U << 3U)  /* Bit 3 */
                | (0U << 4U)  /* Bit 4 */
                | (0U << 5U)  /* Bit 5 */
                | (0U << 6U)  /* Bit 6 */
                | (0U << 7U); /* Bit 7 */

    /** - interrupt level */
                               /* Port A*/
    gioREG->LVLSET =  0U         /* Bit 0 */
                   | (0U << 1U)  /* Bit 1 */
                   | (0U << 2U)  /* Bit 2 */
                   | (0U << 3U)  /* Bit 3 */
                   | (0U << 4U)  /* Bit 4 */
                   | (0U << 5U)  /* Bit 5 */
                   | (0U << 6U)  /* Bit 6 */
                   | (0U << 7U);  /* Bit 7 */


    /** - clear all pending interrupts */
    gioREG->FLG = 0xFFU;

    /** - enable interrupts */
    gioREG->INTENASET =  0U         /* Bit 0 */
                      | (0U << 1U)  /* Bit 1 */
                      | (0U << 2U)  /* Bit 2 */
                      | (0U << 3U)  /* Bit 3 */
                      | (0U << 4U)  /* Bit 4 */
                      | (0U << 5U)  /* Bit 5 */
                      | (0U << 6U)  /* Bit 6 */
                      | (0U << 7U);  /* Bit 7 */
/* USER CODE BEGIN (4) */
/* USER CODE END */
}


/** @fn void gioSetDirection(gioPORT_t *port, uint32 dir)
*   @brief Set Port Direction
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] dir value to write to DIR register
*
*   Set the direction of GIO pins at runtime.
*/
void gioSetDirection(gioPORT_t *port, uint32 dir)
{
    port->DIR = dir;
}


/** @fn void gioSetBit(gioPORT_t *port, uint32 bit, uint32 value)
*   @brief Write Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*   @param[in] value binary value to write to bit
*
*   Writes a value to the specified pin of the given GIO port
*/
void gioSetBit(gioPORT_t *port, uint32 bit, uint32 value)
{
/* USER CODE BEGIN (5) */
/* USER CODE END */

    if (value != 0U)
    {
        port->DSET = 1U << bit;
    }
    else
    {
        port->DCLR = 1U << bit;
    }
}


/** @fn void gioSetPort(gioPORT_t *port, uint32 value)
*   @brief Write Port Value
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] value value to write to port
*
*   Writes a value to all pin of a given GIO port
*/
void gioSetPort(gioPORT_t *port, uint32 value)
{
/* USER CODE BEGIN (6) */
/* USER CODE END */

    port->DOUT = value;

/* USER CODE BEGIN (7) */
/* USER CODE END */

}


/** @fn uint32 gioGetBit(gioPORT_t *port, uint32 bit)
*   @brief Read Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*
*   Reads a the current value from the specified pin of the given GIO port
*/
uint32 gioGetBit(gioPORT_t *port, uint32 bit)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */

    return (port->DIN >> bit) & 1U;
}


/** @fn uint32 gioGetPort(gioPORT_t *port)
*   @brief Read Port Value
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*
*   Reads a the current value of a given GIO port
*/
uint32 gioGetPort(gioPORT_t *port)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    return port->DIN;
}

/** @fn void gioToggleBit(gioPORT_t *port, uint32 bit)
*   @brief Write Bit
*   @param[in] port pointer to GIO port:
*              - gioPORTA: PortA pointer
*              - gioPORTB: PortB pointer
*   @param[in] bit number 0-7 that specifies the bit to be written to.
*              - 0: LSB
*              - 7: MSB
*
*   Toggle a value to the specified pin of the given GIO port
*/
void gioToggleBit(gioPORT_t *port, uint32 bit)
{
/* USER CODE BEGIN (10) */
/* USER CODE END */

    if ((port->DIN & (1U << bit)) != 0U)
    {
        port->DCLR = 1U << bit;
    }
    else
    {
        port->DSET = 1U << bit;
    }
}

/** @fn void gioEnableNotification(uint32 bit)
*   @brief Enable Interrupt
*   @param[in] bit interrupt pin to enable
*              - 0: LSB
*              - 7: MSB
*
*   Enables an interrupt pin of PortA
*/
void gioEnableNotification(uint32 bit)
{
/* USER CODE BEGIN (11) */
/* USER CODE END */

    gioREG->INTENASET = 1U << bit;
}


/** @fn void gioDisableNotification(uint32 bit)
*   @brief Disable Interrupt
*   @param[in] bit interrupt pin to enable
*              - 0: LSB
*              - 7: MSB
*
*   Disables an interrupt pin of PortA
*/
void gioDisableNotification(uint32 bit)
{
/* USER CODE BEGIN (12) */
/* USER CODE END */

    gioREG->INTENACLR = 1U << bit;
}

/** @fn void gioHighLevelInterrupt(void)
*   @brief GIO Interrupt Handler
*
*   High Level Interrupt handler for GIO pin interrupt 
*
*/

void gioHighLevelInterrupt(void)
{
    sint32 offset = gioREG->OFFSET0 - 1U;

    if (offset >= 0)
    {
        gioNotification(offset);
    }
}


/** @fn void gioLowLevelInterrupt(void)
*   @brief GIO Interrupt Handler
*
*   Low Level Interrupt handler for GIO pin interrupt 
*
*/

void gioLowLevelInterrupt(void)
{
    sint32 offset = gioREG->OFFSET1 - 1U;

    if (offset >= 0)
    {
        gioNotification(offset);
    }
}

