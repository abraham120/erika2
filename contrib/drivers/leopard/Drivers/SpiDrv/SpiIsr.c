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

#include "BswCommon.h"
#include <mcu/freescale_mpc5643l/inc/MPC5643L.h>
#include "SpiDrv.h"
#include "SpiCfg.h"
#include "Error.h"
#include "eecfg.h"
#include <ee.h>

#define MODULE_ID   (2)

// RTOS macros to declare ISRs routines
void Spi0RxIsr(void);
void Spi1RxIsr(void);

// Uncomment the following line to provide support for EOQ
//void Spi0EoqfIsr(void);

ISR2(Spi0RxIsr)
{
    ManageSpiRxIsr(CHANNEL_DSPI_0);
}

ISR2(Spi1RxIsr)
{
    ManageSpiRxIsr(CHANNEL_DSPI_1);
}

// Uncomment the following line to provide support for EOQ
/*ISR2(Spi0EoqfIsr)
{
    //Put your code here!!!
    SpiReceive(CHANNEL_DSPI_0, (SpiRxMsgConfigType *)&Rec);

    DSPI_0.SR.B.EOQF = 0x1; // clear only EOQ flag
}*/

