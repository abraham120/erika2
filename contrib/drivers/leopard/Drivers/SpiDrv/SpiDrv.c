/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#include "Error.h"
#include "SpiDrv.h"
#include "SpiCfg.h"

#define MODULE_ID   (3)

#define THIS_DSPI_CHANNEL_IS_MASTER (0x10000000)

// CTR0 bits
#define PBR5        (0x20000U)
#define PBR3        (0x10000U)
#define PBR2        (0x0U)

#define BR4         (0x1U)
#define BR6         (0x2U)
#define BR8         (0x3U)
#define BR16        (0x4U)
#define BR64        (0x6U)

#define FMSZ_8BIT   (0x38000000)
#define FMSZ_16BIT  (0x78000000)

// Chip select bits
#define CHIP_SELECT_BASE    (0x00010000)            ///< Chip select base
#define CS(n)               (CHIP_SELECT_BASE<<n)   ///< Chip select number: from 0 to 7

#define SPI_CPOL_BIT    0x4000000U
#define SPI_CPHA_BIT    0x2000000U
#define SPI_LSBFE_BIT   0x1000000U

static InitializationStateType initializationState = COMPONENT_STATE_NOT_INIZIALIZED;

static const SpiConfType spiConfContainer[] = {
    /// DSPI                Peripheral      working         running       frame         Slave First-response  RX Callback
    /// enabled/disabled    boudrate        policy          mode          size          Enable/disable
    {SPI_ENABLED,           SPI_5_MBPS,     SPI_INTERRUPT,  MASTER,       FRAME_16BIT,  DO_NOT_CARE,          rxCallback_test_SPI0},
    {SPI_ENABLED,           DO_NOT_CARE,    SPI_INTERRUPT,  SLAVE,        FRAME_16BIT,  DO_NOT_CARE,          rxCallback_test_SPI1},
    {SPI_DISABLED,          DO_NOT_CARE,    DO_NOT_CARE,    DO_NOT_CARE,  DO_NOT_CARE,  DO_NOT_CARE,          NULL}
};

/// Set some properties for a given DSPI channel.
static void SpiSetFeatures(volatile DSPI_tag * dspiX, uint8 channel)
{
    // LSBFE setup (only for Master)
    if (spiConfContainer[channel].mode == MASTER) {
        if (spiConfContainer[channel].feature.lsbfe == SPI_MSB_FIRST) {
        dspiX->CTAR[0].R = (dspiX->CTAR[0].R & (~SPI_LSBFE_BIT));   // set LSBFE to 0
        }
        else if (spiConfContainer[channel].feature.lsbfe == SPI_LSB_FIRST) {
            dspiX->CTAR[0].R = (dspiX->CTAR[0].R | SPI_LSBFE_BIT);  // set LSBFE to 1
        }
        else {
            // Error: configuration not allowed
            SetErrorDevelop(ERR_ID_GENERIC, TRUE);
        }
    }
}

static void SpiStart(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Compute pointer to the correct dspi channel
    if (channel == CHANNEL_DSPI_0) {
        dspiX = &DSPI_0;
    }
    else if (channel == CHANNEL_DSPI_1) {
        dspiX = &DSPI_1;
    }
    else if (channel == CHANNEL_DSPI_2) {
        dspiX = &DSPI_2;
    }
    else {
        // Error: not existing DSPI channel
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);
    }

    // Exit HALT mode: go pad as DSPI SCK output
    dspiX->MCR.B.HALT = 0x0;
}

static void SpiStop(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Compute pointer to the correct dspi channel
    if (channel == CHANNEL_DSPI_0) {
        dspiX = &DSPI_0;
    }
    else if (channel == CHANNEL_DSPI_1) {
        dspiX = &DSPI_1;
    }
    else if (channel == CHANNEL_DSPI_2) {
        dspiX = &DSPI_2;
    }
    else {
        // Error: not existing DSPI channel
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);
    }

    // Enter HALT mode
    dspiX->MCR.B.HALT = 0x1;
}

/// Configure a single DSPI channel.
/// - Multithread: NO.
static StdReturnType InitDSPI(const uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Compute DSPI pointer (if it fails, this function return here with STD_NOT_OK error code)
    SpiComputeDspiPtr(dspiX, channel);

    // Set basic master/slave configuration
    if (spiConfContainer[channel].mode == MASTER) {
        dspiX->MCR.R = 0xC0010001;     /* Configure DSPI_0 as master, continuous clock */

        // Set basic SPI features (this configuration also works ok: 0x7A0A7727, but it is slower)
        if (spiConfContainer[channel].peripheralFreq == SPI_6_6_MBPS) {
            dspiX->CTAR[0].R = 0x7A097722;  /* Configure CTAR0, 16bit data  */
        }
        else if (spiConfContainer[channel].peripheralFreq == SPI_5_MBPS) {
            dspiX->CTAR[0].R = 0x7A097723;  /* Configure CTAR0, 16bit data  */
        }
        else {
            // Add here new DSPI speed!!!
        }

        // Set SPI main features for master: LSB/MSB
        //SpiSetFeatures(dspiX, channel);
    }
    else {
        // Set SPI main features for slave: LSB/MSB
        //SpiSetFeatures(dspiX, channel);

        dspiX->MCR.R = 0x40010001;     /* Configure DSPI_1 as slave, continuous clock */
        //dspiX->CTAR[0].R = 0x7A0A7727;

        // Set basic SPI features
        dspiX->CTAR[0].R = 0x7A000000;  /* Configure CTAR0, 16bit data  */
    }

    // Set frame size
    if (spiConfContainer[channel].frameSize == FRAME_8BIT) {
        dspiX->CTAR[0].R = dspiX->CTAR[0].R | FMSZ_8BIT;
    }
    else if (spiConfContainer[channel].frameSize == FRAME_16BIT) {
        dspiX->CTAR[0].R = dspiX->CTAR[0].R | FMSZ_16BIT;
    }
    else {
        // Error: frame-size not supported
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);
    }

    // Enable ISRs if required
    if (spiConfContainer[channel].policy == SPI_INTERRUPT) {
        // Enable required interrupts sources for this SPI channel
        dspiX->RSER.B.RFDF_RE = 1; // enable isr/dma
        dspiX->RSER.B.RFDF_DIRS = 0; // 0=generate interrupt, 1=generate DMA request
        // Uncomment the following line to provide support for EOQ isr (uncomment also the corresponding handler in SpiIsr.c and enable ISR genaration in .oil file)
        //dspiX->RSER.B.EOQF_RE = 1; // 0=generate interrupt in EOQ case
    }

    // Start this SPI Module
    SpiStart(channel);
}

StdReturnType SpiIsFifoFull(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Compute DSPI pointer (if it fails, this function return here with STD_NOT_OK error code)
    SpiComputeDspiPtr(dspiX, channel);

    dspiX->SR.R |= 0x0200000;   // Clear TFFF bit

    // Read back TFFF it value
    if (dspiX->SR.B.TFFF == 0U) {
        return(STD_NOT_OK); // If FIFO is full return STD_NOT_OK
    }
    else {
        return(STD_OK); // If FIFO has free slots return STD_OK
    }
}

StdReturnType SpiDrvTransmit(uint8 channel, dspiFrameType Msg)
{
    dspiFrameType msg = 0U;
    volatile DSPI_tag * dspiX = NULL;
    StdReturnType result;
    uint32 cs = 0U;

    // Check if this module has been previously initialized or not
    if (initializationState == COMPONENT_STATE_NOT_INIZIALIZED) {
        // Return error
        return(STD_NOT_OK);
    }

    // Check if FIFO is full
    result = SpiIsFifoFull(channel);

    // If fifo is FULL return STD_NOT_OK
    if (result == STD_NOT_OK) {
        return(STD_NOT_OK);
    }

    // Compute DSPI pointer (if it fails, this function return here with STD_NOT_OK error code)
    SpiComputeDspiPtr(dspiX, channel);

    // Compute correct chip select to use
    if (channel == CHANNEL_DSPI_0) {
        cs = CHIP_SEL_MAP(CHANNEL_DSPI_0);
    }
    else if (channel == CHANNEL_DSPI_1) {
        cs = CHIP_SEL_MAP(CHANNEL_DSPI_1);
    }
    else if (channel == CHANNEL_DSPI_2) {
        cs = CHIP_SEL_MAP(CHANNEL_DSPI_2);
    }
    else {
        // DSPI channel not supported
        return(STD_NOT_OK);
    }

    // Insert message into the RX FIFO
    if (spiConfContainer[channel].mode == MASTER) {
        dspiX->PUSHR.R = cs | Msg;  // For master bits from 0 to 15 reppresent command, the remaining are data
    }
    else {
        dspiX->PUSHR.R = Msg;    // For Slave bits from 0 to 31 reppresent data
    }

    // Return ok
    return(STD_OK);
}

StdReturnType SpiDrvReceive(uint8 channel, dspiFrameType * Msg)
{
    volatile DSPI_tag * dspiX = NULL;
    dspiFrameType res;

    // Check if this module has been previously initialized or not
    if (initializationState == COMPONENT_STATE_NOT_INIZIALIZED) {
        // Return error
        return(STD_NOT_OK);
    }

    // Compute DSPI pointer (if it fails, this function return here with STD_NOT_OK error code)
    SpiComputeDspiPtr(dspiX, channel);

    // get message from SPI channel (this statement works for polling mode and interrupt mode)
    if (spiConfContainer[channel].policy == SPI_INTERRUPT) {
        *Msg = dspiX->POPR.B.RXDATA;
    }
    else {
        // In polling mode user code must check the following bit (RFDF) to guarantee that a new message has been actually received
        if (dspiX->SR.B.RFDF == 1) {
            *Msg = dspiX->POPR.B.RXDATA;

            // In polling mode user code must clear the following bit (RFDF) since it has not been cleared by ISR handler
            dspiX->SR.R = 0x00020000;
        }
        else {
            // Immediately return since no messages has been received
            return(STD_NOT_OK);
        }
    }

    return(STD_OK);
}

StdReturnType SpiSwitchToPollingMode(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Check if this module has been previously initialized or not
    if (initializationState == COMPONENT_STATE_NOT_INIZIALIZED) {
        // Return error
        return(STD_NOT_OK);
    }

    // Compute DSPI pointer (if it fails, this function return here with STD_NOT_OK error code)
    SpiComputeDspiPtr(dspiX, channel);

    // Halt SPI channel
    SpiStop(channel);

    // Disable ALL interrupts sources for this SPI channel
    dspiX->RSER.R = 0U; // disable isr/dma

    spiConfContainer[channel].policy == SPI_POLLING;

    // restart SPI channel
    SpiStart(channel);

    return(STD_OK);
}

StdReturnType SpiSwitchToInterruptMode(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Check if this module has been previously initialized or not
    if (initializationState == COMPONENT_STATE_NOT_INIZIALIZED) {
        // Return error
        return(STD_NOT_OK);
    }

    // Compute DSPI pointer (if it fails, this function return here with STD_NOT_OK error code)
    SpiComputeDspiPtr(dspiX, channel);

    // Halt SPI channel
    SpiStop(channel);

    // Enable required interrupts sources for this SPI channel
    dspiX->RSER.B.RFDF_RE = 1; // enable isr/dma
    dspiX->RSER.B.RFDF_DIRS = 0; // 0=generate interrupt, 1=generate DMA request
    // Uncomment the following line to provide support for EOQ isr (uncomment also the corresponding handler in SpiIsr.c and enable ISR genaration in .oil file)
    //dspiX->RSER.B.EOQF_RE = 1; // 0=generate interrupt in EOQ case

    spiConfContainer[channel].policy == SPI_INTERRUPT;

    // restart SPI channel
    SpiStart(channel);

    return(STD_OK);
}

StdReturnType ManageSpiRxIsr(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    uint32 index = 0x00U;

    // Check if this module has been previously initialized or not
    if (initializationState == COMPONENT_STATE_NOT_INIZIALIZED) {
        // Return error
        return(STD_NOT_OK);
    }

    // Compute DSPI pointer (if it fails, this function return here with STD_NOT_OK error code)
    SpiComputeDspiPtr(dspiX, channel);
    
    // Trigger the handler if configured
    if (spiConfContainer[channel].rxCallback != NULL) {
        spiConfContainer[channel].rxCallback();
    }

    // Clear TCF, RDRF flags by writing 1 to them
    dspiX->SR.R = 0x80020000; // do not clear EOQ flag (only TCF and RDRF)

    return(STD_OK);
}

/// Initialization of component SpiDrv.
/// - Multithread: NO.
StdReturnType SpiDrvInit(void)
{
    uint8 i = 0U;
    StdReturnType tmp_result;

    // If DEVELOPMENT is defined (i.e. during system development), then every function provides stronger checks (see 'Extended error detection')
#ifdef DEVELOPMENT
    if (initializationState == COMPONENT_STATE_INIZIALIZED) {
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);      // Illegal re-initialization.

        return(STD_NOT_OK);     // Statement reachable only during unit testing
    }
#endif

    // Initialize DSPI channels
    for (i=0; i<CHANNEL_DSPI_NUM; i++) {
        if (SPI_ENABLED == spiConfContainer[i].peripheralEn) {
            tmp_result = InitDSPI(i);

            // Check whether the SPI channel has been properly initialized or not
            if (tmp_result == STD_NOT_OK) {
                return(STD_NOT_OK);
            }
        }
    }

    // Mark DSPI as initialized
    initializationState = COMPONENT_STATE_INIZIALIZED;

    return(STD_OK);
}

StdReturnType SpiDrvFlushTxFifo(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Compute pointer to the correct dspi channel
    if (channel == CHANNEL_DSPI_0) {
        dspiX = &DSPI_0;
    }
    else if (channel == CHANNEL_DSPI_1) {
        dspiX = &DSPI_1;
    }
    else if (channel == CHANNEL_DSPI_2) {
        dspiX = &DSPI_2;
    }
    else {
        // Error: not existing DSPI channel
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);
    }

    // Flush Tx FIFO
    dspiX->MCR.B.CLR_TXF = 1U;

    return(STD_OK);
}

StdReturnType SpiDrvFlushRxFifo(uint8 channel)
{
    volatile DSPI_tag * dspiX = NULL;

    // Compute pointer to the correct dspi channel
    if (channel == CHANNEL_DSPI_0) {
        dspiX = &DSPI_0;
    }
    else if (channel == CHANNEL_DSPI_1) {
        dspiX = &DSPI_1;
    }
    else if (channel == CHANNEL_DSPI_2) {
        dspiX = &DSPI_2;
    }
    else {
        // Error: not existing DSPI channel
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);
    }

    // Flush Rx FIFO
    dspiX->MCR.B.CLR_RXF = 1U;

    return(STD_OK);
}


