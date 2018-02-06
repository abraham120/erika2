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

#ifndef _SPIDRV_H_
#define _SPIDRV_H_

#include "BswCommon.h"
#include <cpu/common/inc/ee_stdint.h>
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>
#include "Error.h"
#include "SpiCfg.h"

typedef enum {
    CHANNEL_DSPI_0 = 0,
    CHANNEL_DSPI_1 = 1,
    CHANNEL_DSPI_2 = 2,
    CHANNEL_DSPI_NUM
} SpiChannelType;

// length can be at most 128, hence the following macro defines the maximum SPI command length (expressed in bytes)
#define SPI_MAX_COMMAND_LENGTH  128

typedef struct {
    uint8 stuff;
    uint8 length;
    uint8 counter_command;
    uint8 lref_CHOP;
    uint8 lref_HBR;
    uint8 lref_CHRG;
    uint8 checksum;
    uint8 end;
} SpiTxMsgConfigType;

// Compute pointer to the correct dspi channel (using static inline function seems to do not provide the correct pointer)
#define SpiComputeDspiPtr(dspiX, channel)       \
    if (channel == CHANNEL_DSPI_0) {            \
        dspiX = &DSPI_0;                        \
    }                                           \
    else if (channel == CHANNEL_DSPI_1) {       \
        dspiX = &DSPI_1;                        \
    }                                           \
    else if (channel == CHANNEL_DSPI_2) {       \
        dspiX = &DSPI_2;                        \
    }                                           \
    else {                                      \
        SetErrorDevelop(ERR_ID_GENERIC, TRUE);  \
        return(STD_NOT_OK);                     \
    }

StdReturnType SpiDrvInit(void);
StdReturnType SpiDrvTransmit(uint8 channel, dspiFrameType Msg);
StdReturnType SpiDrvReceive(uint8 channel, dspiFrameType * Msg);
StdReturnType SpiSwitchToPollingMode(uint8 channel);
StdReturnType SpiSwitchToInterruptMode(uint8 channel);
StdReturnType ManageSpiRxIsr(uint8 channel);
StdReturnType SpiIsFifoFull(uint8 channel);
StdReturnType SpiDrvFlushTxFifo(uint8 channel);
StdReturnType SpiDrvFlushRxFifo(uint8 channel);

#endif      // _SPIDRV_H_
