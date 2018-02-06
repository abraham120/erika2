/** @file sci.c 
*   @brief SCI Driver Implementation File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*/

/* (c) Texas Instruments 2009-2014, All rights reserved. */

/* USER CODE BEGIN (0) */
/* USER CODE END */

#include "sci.h"

/* USER CODE BEGIN (1) */
/* USER CODE END */
/** @struct g_sciTransfer
*   @brief Interrupt mode globals
*
*/
static struct g_sciTransfer
{
    uint32   mode;
    uint32   length;
    uint8    * data;
} g_sciTransfer_t[2U];


/** @fn void sciInit(void)
*   @brief Initializes the SCI Driver
*
*   This function initializes the SCI module.
*/
void sciInit(void)
{
/* USER CODE BEGIN (2) */
/* USER CODE END */

    /** @b initialize @b SCI1 */

    /** - bring SCI1 out of reset */
    sciREG1->GCR0 = 1U;

    /** - Disable all interrupts */
    sciREG1->CLRINT    = 0xFFFFFFFFU;
    sciREG1->CLRINTLVL = 0xFFFFFFFFU;

    /** - global control 1 */
    sciREG1->GCR1 = (1U << 25U)  /* enable transmit */
                  | (1U << 24U)  /* enable receive */
                  | (1U << 5U)   /* internal clock (device has no clock pin) */
                  | ((2U-1U) << 4U)  /* number of stop bits */
                  | (0U << 3U)  /* even parity, otherwise odd */
                  | (0U << 2U)  /* enable parity */
                  | (1U << 1U);  /* asynchronous timing mode */

    /** - set baudrate */
    sciREG1->BRS = 86U;  /* baudrate */

    /** - transmission length */
    sciREG1->FORMAT = 8U - 1U;  /* length */

    /** - set SCI1 pins functional mode */
    sciREG1->FUN = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI1 pins default output value */
    sciREG1->DOUT = (0U << 2U)  /* tx pin */
                  | (0U << 1U)  /* rx pin */
                  | (0U);  /* clk pin */

    /** - set SCI1 pins output direction */
    sciREG1->DIR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI1 pins open drain enable */
    sciREG1->ODR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI1 pins pullup/pulldown enable */
    sciREG1->PD = (0U << 2U)  /* tx pin */
                | (0U << 1U)  /* rx pin */
                | (0U);  /* clk pin */

    /** - set SCI1 pins pullup/pulldown select */
    sciREG1->PSL = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (1U);  /* clk pin */

    /** - set interrupt level */
    sciREG1->SETINTLVL = (0U << 26U)  /* Framing error */
                       | (0U << 25U)  /* Overrun error */
                       | (0U << 24U)  /* Parity error */
                       | (0U << 9U)  /* Receive */
                       | (0U << 8U)  /* Transmit */
                       | (0U << 1U)  /* Wakeup */
                       | (0U);  /* Break detect */

    /** - set interrupt enable */
    sciREG1->SETINT = (0U << 26U)  /* Framing error */
                    | (0U << 25U)  /* Overrun error */
                    | (0U << 24U)  /* Parity error */
                    | (0U << 9U)  /* Receive */
                    | (0U << 1U)  /* Wakeup */
                    | (0U);  /* Break detect */

    /** - initialize global transfer variables */
    g_sciTransfer_t[0U].mode   = 0U << 8U;
    g_sciTransfer_t[0U].length = 0U;

    /** - Finaly start SCI1 */
    sciREG1->GCR1 |= (1U << 7U);


    /** @b initialize @b SCI2 */

    /** - bring SCI2 out of reset */
    sciREG2->GCR0 = 1U;

    /** - Disable all interrupts */
    sciREG2->CLRINT    = 0xFFFFFFFFU;
    sciREG2->CLRINTLVL = 0xFFFFFFFFU;

    /** - global control 1 */
    sciREG2->GCR1 = (1U << 25U)  /* enable transmit */
                  | (1U << 24U)  /* enable receive */
                  | (1U << 5U)   /* internal clock (device has no clock pin) */
                  | ((2U-1U) << 4U)  /* number of stop bits */
                  | (0U << 3U)  /* even parity, otherwise odd */
                  | (0U << 2U)  /* enable parity */
                  | (1U << 1U);  /* asynchronous timing mode */

    /** - set baudrate */
    sciREG2->BRS = 1041U;  /* baudrate */

    /** - transmission length */
    sciREG2->FORMAT = 8U - 1U;  /* length */

    /** - set SCI2 pins functional mode */
    sciREG2->FUN = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI2 pins default output value */
    sciREG2->DOUT = (0U << 2U)  /* tx pin */
                  | (0U << 1U)  /* rx pin */
                  | (0U);  /* clk pin */

    /** - set SCI2 pins output direction */
    sciREG2->DIR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI2 pins open drain enable */
    sciREG2->ODR = (0U << 2U)  /* tx pin */
                 | (0U << 1U)  /* rx pin */
                 | (0U);  /* clk pin */

    /** - set SCI2 pins pullup/pulldown enable */
    sciREG2->PD = (0U << 2U)  /* tx pin */
                | (0U << 1U)  /* rx pin */
                | (0U);  /* clk pin */

    /** - set SCI2 pins pullup/pulldown select */
    sciREG2->PSL = (1U << 2U)  /* tx pin */
                 | (1U << 1U)  /* rx pin */
                 | (1U);  /* clk pin */

    /** - set interrupt level */
    sciREG2->SETINTLVL = (0U << 26U)  /* Framing error */
                       | (0U << 25U)  /* Overrun error */
                       | (0U << 24U)  /* Parity error */
                       | (0U << 9U)  /* Receive */
                       | (0U << 8U)  /* Transmit */
                       | (0U << 1U)  /* Wakeup */
                       | (0U);  /* Break detect */

    /** - set interrupt enable */
    sciREG2->SETINT = (0U << 26U)  /* Framing error */
                    | (0U << 25U)  /* Overrun error */
                    | (0U << 24U)  /* Parity error */
                    | (0U << 9U)  /* Receive */
                    | (0U << 1U)  /* Wakeup */
                    | (0U);  /* Break detect */

    /** - initialize global transfer variables */
    g_sciTransfer_t[0U].mode   = 0U << 8U;
    g_sciTransfer_t[0U].length = 0U;

    /** - Finaly start SCI2 */
    sciREG2->GCR1 |= (1U << 7U);
	
/* USER CODE BEGIN (3) */
/* USER CODE END */
}


/** @fn void sciSetFunctional(sciBASE_t *sci, uint32 port)
*   @brief Change functional behavior of pins at runtime.
*   @param[in] sci   - sci module base address
*   @param[in] port  - Value to write to FUN register
*
*   Change the value of the PCFUN register at runtime, this allows to
*   dynamically change the functionality of the SCI pins between functional
*   and GIO mode.
*/
void sciSetFunctional(sciBASE_t *sci, uint32 port)
{
/* USER CODE BEGIN (4) */
/* USER CODE END */

    sci->FUN = port;

/* USER CODE BEGIN (5) */
/* USER CODE END */
}


/** @fn void sciSetBaudrate(sciBASE_t *sci, uint32 baud)
*   @brief Change baudrate at runtime.
*   @param[in] sci  - sci module base address
*   @param[in] baud - baudrate in Hz
*
*   Change the SCI baudrate at runtime.
*/
void sciSetBaudrate(sciBASE_t *sci, uint32 baud)
{
    float64   vclk = 160.000 * 1000000.0;
    uint32 f    = ((sci->GCR1 & 2U) == 2U) ? 16U : 1U;

/* USER CODE BEGIN (6) */
/* USER CODE END */

    sci->BRS = ((uint32)((vclk /(f*baud) + 0.5)) - 1U) & 0x00FFFFFFU;

/* USER CODE BEGIN (7) */
/* USER CODE END */
}


/** @fn uint32 sciIsTxReady(sciBASE_t *sci)
*   @brief Check if Tx buffer empty
*   @param[in] sci - sci module base address
*
*   @return The TX ready flag
*
*   Checks to see if the Tx buffer ready flag is set, returns
*   0 is flags not set otherwise will return the Tx flag itself.
*/
uint32 sciIsTxReady(sciBASE_t *sci)
{
/* USER CODE BEGIN (8) */
/* USER CODE END */

    return sci->FLR & SCI_TX_INT;
}


/** @fn void sciSendByte(sciBASE_t *sci, uint8 byte)
*   @brief Send Byte
*   @param[in] sci  - sci module base address
*   @param[in] byte - byte to transfer
*
*   Sends a single byte in polling mode, will wait in the
*   routine until the transmit buffer is empty before sending
*   the byte.  Use sciIsTxReady to check for Tx buffer empty
*   before calling sciSendByte to avoid waiting.
*/
void sciSendByte(sciBASE_t *sci, uint8 byte)
{
/* USER CODE BEGIN (9) */
/* USER CODE END */

    while ((sci->FLR & SCI_TX_INT) == 0U) 
    { 
	} /* Wait */
    sci->TD = byte;

/* USER CODE BEGIN (10) */
/* USER CODE END */
}


/** @fn void sciSend(sciBASE_t *sci, uint32 length, uint8 * data)
*   @brief Send Data
*   @param[in] sci    - sci module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data to send
*
*   Send a block of data pointed to by 'data' and 'length' bytes
*   long.  If interrupts have been enabled the data is sent using
*   interrupt mode, otherwise polling mode is used.  In interrupt
*   mode transmission of the first byte is started and the routine
*   returns immediately, sciSend must not be called again until the
*   transfer is complete, when the sciNotification callback will
*   be called.  In polling mode, sciSend will not return  until 
*   the transfer is complete.
*
*   @note if data word is less than 8 bits, then the data must be left
*         aligned in the data byte.
*/
void sciSend(sciBASE_t *sci, uint32 length, uint8 * data)
{
    uint32 index = sci == sciREG1 ? 0U : 1U;

/* USER CODE BEGIN (11) */
/* USER CODE END */

    if ((g_sciTransfer_t[index].mode & SCI_TX_INT) != 0U)
    {
        /* we are in interrupt mode */
        
        g_sciTransfer_t[index].length = length;
        g_sciTransfer_t[index].data   = data;

        /* start transmit by sending first byte */        
        sci->TD     = *g_sciTransfer_t[index].data++ ;
        sci->SETINT = SCI_TX_INT;
    }
    else
    {
        /* send the data */
        while (length-- > 0U)
        {
            while ((sci->FLR & SCI_TX_INT) == 0U)
            { 
	        } /* Wait */
            sci->TD = *data++;
        }
    }

/* USER CODE BEGIN (12) */
/* USER CODE END */
}


/** @fn uint32 sciIsRxReady(sciBASE_t *sci)
*   @brief Check if Rx buffer full
*   @param[in] sci - sci module base address
*
*   @return The Rx ready flag
*
*   Checks to see if the Rx buffer full flag is set, returns
*   0 is flags not set otherwise will return the Rx flag itself.
*/
uint32 sciIsRxReady(sciBASE_t *sci)
{
/* USER CODE BEGIN (13) */
/* USER CODE END */

    return sci->FLR & SCI_RX_INT;
}


/** @fn uint32 sciRxError(sciBASE_t *sci)
*   @brief Return Rx Error flags
*   @param[in] sci - sci module base address
*
*   @return The Rx error flags
*
*   Returns the Rx framing, overrun and parity errors flags,
*   also clears the error flags before returning.
*/
uint32 sciRxError(sciBASE_t *sci)
{
    uint32 status = sci->FLR & (SCI_FE_INT | SCI_OE_INT |SCI_PE_INT);

/* USER CODE BEGIN (14) */
/* USER CODE END */

    sci->FLR = SCI_FE_INT | SCI_OE_INT | SCI_PE_INT;
    return status;
}


/** @fn uint32 sciReceiveByte(sciBASE_t *sci)
*   @brief Receive Byte
*   @param[in] sci - sci module base address
*
*   @return Received byte
*
*    Receives a single byte in polling mode.  If there is
*    not a byte in the receive buffer the routine will wait
*    until one is received.   Use sciIsRxReady to check to
*    see if the buffer is full to avoid waiting.
*/
uint32 sciReceiveByte(sciBASE_t *sci)
{
/* USER CODE BEGIN (15) */
/* USER CODE END */

    while ((sci->FLR & SCI_RX_INT) == 0U) 
    { 
	} /* Wait */

    return (sci->RD & 0x000000FFU);
}


/** @fn void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data)
*   @brief Receive Data
*   @param[in] sci    - sci module base address
*   @param[in] length - number of data words to transfer
*   @param[in] data   - pointer to data buffer
*
*   Receive a block of 'length' bytes long and place it into the 
*   data buffer pointed to by 'data'.  If interrupts have been 
*   enabled the data is received using interrupt mode, otherwise
*   polling mode is used.  In interrupt mode receive is setup and
*   the routine returns immediately, sciReceive must not be called 
*   again until the transfer is complete, when the sciNotification 
*   callback will be called.  In polling mode, sciReceive will not
*   return  until the transfer is complete.
*/
void sciReceive(sciBASE_t *sci, uint32 length, uint8 * data)
{
/* USER CODE BEGIN (16) */
/* USER CODE END */

    if ((sci->SETINT & SCI_RX_INT) == SCI_RX_INT)
    {
        /* we are in interrupt mode */
        uint32 index = sci == sciREG1 ? 0U : 1U;
        
        /* clear error flags */
        sci->FLR = SCI_FE_INT | SCI_OE_INT | SCI_PE_INT;

        g_sciTransfer_t[index].length = length;
        g_sciTransfer_t[index].data   = data;
    }
    else
    {   
        while (length-- > 0U)
        {
            while ((sci->FLR & SCI_RX_INT) == 0U) 
		    { 
	        } /* Wait */
            *data++ = (uint8)(sci->RD & 0x000000FFU);
        }
    }
}


/** @fn sciEnableNotification(sciBASE_t *sci, uint32 flags)
*   @brief Enable interrupts
*   @param[in] sci   - sci module base address
*   @param[in] flags - Interrupts to be enabled, can be ored value of:
*                      SCI_FE_INT    - framing error,
*                      SCI_OE_INT    - overrun error,
*                      SCI_PE_INT    - parity error,
*                      SCI_RX_INT    - receive buffer ready,
*                      SCI_TX_INT    - transmit buffer ready,
*                      SCI_WAKE_INT  - wakeup,
*                      SCI_BREAK_INT - break detect
*/
void sciEnableNotification(sciBASE_t *sci, uint32 flags)
{
    uint32 index = sci == sciREG1 ? 0U : 1U;

/* USER CODE BEGIN (17) */
/* USER CODE END */

    g_sciTransfer_t[index].mode |= (flags & SCI_TX_INT);
    sci->SETINT                = (flags & (~(SCI_TX_INT)));

/* USER CODE BEGIN (18) */
/* USER CODE END */
}


/** @fn sciDisableNotification(sciBASE_t *sci, uint32 flags)
*   @brief Disable interrupts
*   @param[in] sci   - sci module base address
*   @param[in] flags - Interrupts to be disabled, can be ored value of:
*                      SCI_FE_INT    - framing error,
*                      SCI_OE_INT    - overrun error,
*                      SCI_PE_INT    - parity error,
*                      SCI_RX_INT    - receive buffer ready,
*                      SCI_TX_INT    - transmit buffer ready,
*                      SCI_WAKE_INT  - wakeup,
*                      SCI_BREAK_INT - break detect
*/
void sciDisableNotification(sciBASE_t *sci, uint32 flags)
{
    uint32 index = sci == sciREG1 ? 0U : 1U;

/* USER CODE BEGIN (19) */
/* USER CODE END */

    g_sciTransfer_t[index].mode &= ~(flags & SCI_TX_INT);
    sci->CLRINT                = (flags & (~SCI_TX_INT));

/* USER CODE BEGIN (20) */
/* USER CODE END */
}


/** @fn void sci1HighLevelInterrupt(void)
*   @brief High Level Interrupt for SCI1
*/

void sci1HighLevelInterrupt(void)
{
    uint32 vec = sciREG1->INTVECT0;

    switch (vec)
    {
    case 1:
        sciNotification(sciREG1, SCI_WAKE_INT);
        break;
    case 3:
        sciNotification(sciREG1, SCI_PE_INT);
        break;
    case 6:
        sciNotification(sciREG1, SCI_FE_INT);
        break;
    case 7:
        sciNotification(sciREG1, SCI_BREAK_INT);
        break;
    case 9:
        sciNotification(sciREG1, SCI_OE_INT);
        break;

    case 11:
        /* receive */
        {   uint32 byte = sciREG1->RD;

            if (g_sciTransfer_t[0U].length > 0U)
            {
                *g_sciTransfer_t[0U].data++ = byte;
                g_sciTransfer_t[0U].length--;
                if (g_sciTransfer_t[0U].length == 0U)
                {
                    sciNotification(sciREG1, SCI_RX_INT);
                }
            }
        }
        break;

    case 12:
        /* transmit */
        if (--g_sciTransfer_t[0U].length > 0U)
        {
            sciREG1->TD = *g_sciTransfer_t[0U].data++;
        }
        else
        {
            sciREG1->CLRINT = SCI_TX_INT;
            sciNotification(sciREG1, SCI_TX_INT);
        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        sciREG1->FLR = ~sciREG1->SETINTLVL & 0x07000303U;
    }
}


/** @fn void sci1LowLevelInterrupt(void)
*   @brief Low Level Interrupt for SCI1
*/

void sci1LowLevelInterrupt(void)
{
    uint32 vec = sciREG1->INTVECT1;

    switch (vec)
    {
    case 1:
        sciNotification(sciREG1, SCI_WAKE_INT);
        break;
    case 3:
        sciNotification(sciREG1, SCI_PE_INT);
        break;
    case 6:
        sciNotification(sciREG1, SCI_FE_INT);
        break;
    case 7:
        sciNotification(sciREG1, SCI_BREAK_INT);
        break;
    case 9:
        sciNotification(sciREG1, SCI_OE_INT);
        break;

    case 11:
        /* receive */
        {   uint32 byte = sciREG1->RD;

            if (g_sciTransfer_t[0U].length > 0U)
            {
                *g_sciTransfer_t[0U].data++ = byte;
                g_sciTransfer_t[0U].length--;
                if (g_sciTransfer_t[0U].length == 0U)
                {
                    sciNotification(sciREG1, SCI_RX_INT);
                }
            }
        }
        break;

    case 12:
        /* transmit */
        if (--g_sciTransfer_t[0U].length > 0U)
        {
            sciREG1->TD = *g_sciTransfer_t[0U].data++;
        }
        else
        {
            sciREG1->CLRINT = SCI_TX_INT;
            sciNotification(sciREG1, SCI_TX_INT);
        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        sciREG1->FLR = sciREG1->SETINTLVL & 0x07000303U;
    }
}


/** @fn void sci2HighLevelInterrupt(void)
*   @brief High Level Interrupt for SCI2
*/

void sci2HighLevelInterrupt(void)
{
    uint32 vec = sciREG2->INTVECT0;

    switch (vec)
    {
    case 1:
        sciNotification(sciREG2, SCI_WAKE_INT);
        break;
    case 3:
        sciNotification(sciREG2, SCI_PE_INT);
        break;
    case 6:
        sciNotification(sciREG2, SCI_FE_INT);
        break;
    case 7:
        sciNotification(sciREG2, SCI_BREAK_INT);
        break;
    case 9:
        sciNotification(sciREG2, SCI_OE_INT);
        break;

    case 11:
        /* receive */
        {   uint32 byte = sciREG2->RD;

            if (g_sciTransfer_t[1U].length > 0U)
            {
                *g_sciTransfer_t[1U].data++ = byte;
                g_sciTransfer_t[1U].length--;
                if (g_sciTransfer_t[1U].length == 0U)
                {
                    sciNotification(sciREG2, SCI_RX_INT);
                }
            }
        }
        break;

    case 12:
        /* transmit */
        if (--g_sciTransfer_t[1U].length > 0U)
        {
            sciREG2->TD = *g_sciTransfer_t[1U].data++;
        }
        else
        {
            sciREG2->CLRINT = SCI_TX_INT;
            sciNotification(sciREG2, SCI_TX_INT);
        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        sciREG2->FLR = ~sciREG2->SETINTLVL & 0x07000303U;
    }
}


/** @fn void sci2LowLevelInterrupt(void)
*   @brief Low Level Interrupt for SCI2
*/

void sci2LowLevelInterrupt(void)
{
    uint32 vec = sciREG2->INTVECT1;

    switch (vec)
    {
    case 1:
        sciNotification(sciREG2, SCI_WAKE_INT);
        break;
    case 3:
        sciNotification(sciREG2, SCI_PE_INT);
        break;
    case 6:
        sciNotification(sciREG2, SCI_FE_INT);
        break;
    case 7:
        sciNotification(sciREG2, SCI_BREAK_INT);
        break;
    case 9:
        sciNotification(sciREG2, SCI_OE_INT);
        break;

    case 11:
        /* receive */
        {   uint32 byte = sciREG2->RD;

            if (g_sciTransfer_t[1U].length > 0U)
            {
                *g_sciTransfer_t[1U].data++ = byte;
                g_sciTransfer_t[1U].length--;
                if (g_sciTransfer_t[1U].length == 0U)
                {
                    sciNotification(sciREG2, SCI_RX_INT);
                }
            }
        }
        break;

    case 12:
        /* transmit */
        if (--g_sciTransfer_t[1U].length > 0U)
        {
            sciREG2->TD = *g_sciTransfer_t[1U].data++;
        }
        else
        {
            sciREG2->CLRINT = SCI_TX_INT;
            sciNotification(sciREG2, SCI_TX_INT);
        }
        break;

    default:
        /* phantom interrupt, clear flags and return */
        sciREG2->FLR = sciREG2->SETINTLVL & 0x07000303U;
    }
}

