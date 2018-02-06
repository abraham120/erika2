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

#ifndef _SPICFG_H_
#define _SPICFG_H_

#include "BswCommon.h"

#define SPI_ENABLED     (0x0U)          ///< Enable DSPI module
#define SPI_DISABLED    (0x1U)          ///< Disable DSPI module
#define DO_NOT_CARE     SPI_DISABLED    ///< Ignored value

#define SPI_INTERRUPT   (0x0U)          ///< Interrupt mode
#define SPI_POLLING     (0x1U)          ///< Polling mode

#define SPI_5_MBPS      (0x2U)          ///< 5 Mbps
#define SPI_6_6_MBPS    (0x3U)          ///< 6.6 Mbps

#define MASTER          (0x0U)          ///< Set device as a master
#define SLAVE           (0x1U)          ///< Set device as a slave

#define SPI_INTERRUPT_MODE              ///< General enable/disable isr flag

#define FRAME_8BIT      (0x0U)          ///< 8-bit frame
#define FRAME_16BIT     (0x1U)          ///< 16-bit frame

#define SPI_CPOL_0      (0x9U)
#define SPI_CPHA_0      (0xAU)
#define SPI_MSB_FIRST   (0xBU)
#define SPI_CPOL_1      (0xCU)
#define SPI_CPHA_1      (0xDU)
#define SPI_LSB_FIRST   (0xEU)

#define SPI_RX_BUFFER_LENGTH    (8)     ///< Rx Buffer length

#define SPI_COMMAND_LENGTH      (8)     ///< Length of the command sent via SPI.

#define SPICOM_CHANNEL          (0)     ///< Select the SPI channel used by SpiCom.

/// DSPI chip select mapping
#define CHIP_SEL_MAP(n)         CHIP_SEL_##n

// DSPI0 channel is mapped ONLY to chip select 0
#define CHIP_SEL_CHANNEL_DSPI_0 CS(0)
// set chip select used by DSPI_1 (it may be: 0,1,2,3,4,5,6,7)
#define CHIP_SEL_CHANNEL_DSPI_1 CS(0) // 0 is a dummy value to build SpiDrv
// set chip select used by DSPI_2 (it may be: 0,1,2,3,4,5,6,7)
#define CHIP_SEL_CHANNEL_DSPI_2 CS(0) // 0 is a dummy value to build SpiDrv

/// SPI frame size definition
typedef uint16 dspiFrameType;
//typedef uint8 dspiFrameType;  // use this in case of 8 bit SPI transmission

extern void rxCallback_test_SPI0(void);
extern void rxCallback_test_SPI1(void);
extern void SpiComRxCallback(uint16 spiData);

typedef struct
{
    uint8 lsbfe;
} SpiFeatureType;

/// DSPI Module configuration
typedef struct
{
    boolean             peripheralEn;       ///< Peripheral enable/disable
    uint32              peripheralFreq;     ///< Peripheral working freq.
    uint8               policy;             ///< Policy: interrupt/polling/dma
    uint8               mode;               ///< Mode: master/slave
    uint8               frameSize;          ///< Frame size (number of bit)
    SpiFeatureType      feature;            ///< Define the combination of CPOL, CPHA and mode-shifting (MSB/LSB first)
    void (*rxCallback)(void);               ///< If NULL the callback is ignored.
} SpiConfType;

/// Data message from PPC to DSP.
typedef struct {
    // Section 0
    uint16 var0;
    uint16 var1;
    uint16 var2;
    uint16 ctrl0;   ///< Bits0-7: checksum. Bits8-11: counter. Bits12-13: not used. Bit14: error. Bit15: nextSection. 
    
    // Section 1
    uint16 var3;
    uint16 var4;
    uint16 var5;
    uint16 ctrl1;   ///< Bits0-7: checksum. Bits8-11: counter. Bits12-13: not used. Bit14: error. Bit15: nextSection. 
    
    // Section 2
    uint16 cmd[SPI_COMMAND_LENGTH];  ///< Request to be sent.
    uint16 ctrl2;   ///< Bits0-7: checksum. Bits8-11: counter. Bits12-13: channel. Bit14: error. Bit15: nextSection. 
} SpiComTxType;   

/// Data message from DPS to PPC.
typedef struct {
    // Section 0
    uint16 var0;
    uint16 var1;
    uint16 var2;
    uint16 ctrl0;   ///< Bits0-7: checksum. Bits8-11: counter. Bits12-13: not used. Bit14: error. Bit15: nextSection.

// TODO Francesco: immagino che manchi una sezione quì????
    
    // Section 1
    uint16 cmd[SPI_COMMAND_LENGTH];  ///< Response received.
    uint16 ctrl1;   ///< Bits0-7: checksum. Bits8-11: counter. Bits12-13: channel. Bit14: error. Bit15: nextSection. 
} SpiComRxType;   


#endif      // _SPICFG_H_

