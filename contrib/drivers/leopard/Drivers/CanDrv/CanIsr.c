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
#include "CanDrv.h"
#include "CanCom.h"
#include "eecfg.h"
#include <ee.h>

/* RTOS macros to declare ISRs routines */
void FlexCan0_0_3_isr_handler(void);
void FlexCan0_ESR_ERR_INT(void);
void FlexCan0_ESR_BOFF_TX_RX_WARN_handler(void);

extern void ManageCanIsr(uint8 isrSourceIndex, uint32 bufferFlags, CanChannelType canChannel);  // The 'extern' is here (and not in a .h file) because ManageCanIsr() must be called only by CanIsr.c

/* Isr for FlexCAN0 */

ISR2(FlexCan0_0_3_isr_handler)
{
    /* Manage isr since it may be RX or TX isr */
	ManageCanIsr(BUFF_OFFSET_0_3, FLEXCAN_A.IFLAG1.R & BUFF_MASK_0_3, CHANNEL_FLEXCAN_A);
}

/* Isr for Errors coming from FlexCAN0 */
ISR2(FlexCan0_ESR_ERR_INT)
{
    if (FLEXCAN_A.ESR.B.CRC_ERR == 0x1U) {
        // Trap here in case of FlexCAN0 CRC error
	    while(1)
	    ;
    }
    else {
        /*
         * Errors not still handled:
         * BIT1_ERR
         * BIT2_ERR
         * ACK_ERR
         * CRC_ERR <---- handled by the "if" branch above
         * FRM_ERR
         * STF_ERR
         *
         * For now, siply clear isr flag and go forward
         * TODO: a specific isr management has to be implemented for each isr error
         */
        FLEXCAN_A.ESR.B.ERR_INT = 0x1U;
    }
}

ISR2(FlexCan0_ESR_BOFF_TX_RX_WARN_handler)
{
    if (FLEXCAN_A.ESR.B.BOFF_INT == 0x1U) {
        // Call the following CanCom callback in case of Bus Off
        Ch0_busOff_callback();

        // This bit is cleared by writing it to 1
        FLEXCAN_A.ESR.B.BOFF_INT = 0x1U;
    }
    else {
        /* Error not handled */
    }
}

