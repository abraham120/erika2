/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

/** @file	Sci_Internal.h
 *  @brief	AUTOSAR-"like" SCI Driver Internal Header File.
 *  @author	Giuseppe Serano
 *  @date	2012
 */

/* UART Hardware Channel Unit Mask */
#define	HW_CH_MOD_MASK		0x00000007	/* Mask			*/

/* UART Hardware Base Address */
#define	HW_BASE_ADDR		&UART0_DR_R

#include "Hardware.h"	/* Hardware Abstraction Header File. */

/* Channel Harware Register Offsets */
#define	UART_DATA_R_OFFSET		0x00000000	/* Data               */
#define	UART_RS_EC_R_OFFSET		0x00000004	/* Rx Status/Err Clr  */
#define	UART_FLAG_R_OFFSET		0x00000018	/* Flags	      */
#define	UART_IBRD_R_OFFSET		0x00000024	/* Integer BRD	      */
#define	UART_FBRD_R_OFFSET		0x00000028	/* Fractional BRD     */
#define	UART_LCRH_R_OFFSET		0x0000002C	/* Line Control	      */
#define	UART_CTL_R_OFFSET		0x00000030	/* System Control     */
#define	UART_IFLS_R_OFFSET		0x00000034	/* Int FIFO Lvl	      */
#define	UART_IM_R_OFFSET		0x00000038	/* Interrupt Mask     */
#define	UART_RIS_R_OFFSET		0x0000003C	/* Raw Int Status     */
#define	UART_MIS_R_OFFSET		0x00000040	/* Masked Int Status  */
#define	UART_IC_R_OFFSET		0x00000044	/* Interrupt Clear    */
#define	UART_CC_R_OFFSET		0x00000FC8	/* Clock Control      */

/* Channel Interrupt Sources */
#define	UART_INT_LME5	0x00008000	/* LIN Mode Edge 5	      */
#define	UART_INT_LME1	0x00004000	/* LIN Mode Edge 1	      */
#define	UART_INT_LMSB	0x00002000	/* LIN Mode Sync Break	      */
#define	UART_INT_9BIT	0x00001000	/* 9-Bit Mode		      */
#define	UART_INT_OE	0x00000400	/* Overrun Error	      */
#define	UART_INT_BE	0x00000200	/* Break Error		      */
#define	UART_INT_PE	0x00000100	/* Parity Error		      */
#define	UART_INT_FE	0x00000080	/* Frame Error		      */
#define	UART_INT_RT	0x00000040	/* Receive Timeout	      */
#define	UART_INT_TX	0x00000020	/* Transmission		      */
#define	UART_INT_RX	0x00000010	/* Reception		      */
#define	UART_INT_DSR	0x00000008	/* Data Set Ready	      */
#define	UART_INT_DCD	0x00000004	/* Data Carrier Detect	      */
#define	UART_INT_CTS	0x00000002	/* Clear To Send	      */
#define	UART_INT_RI	0x00000001	/* Ring Indicator	      */

/* Interrupt Receive Error	      */
#define	UART_INT_RX_ERR	( \
	UART_INT_OE  |	UART_INT_BE  |	UART_INT_PE  |	UART_INT_FE \
)

/* All Interrupt	      */
#define	UART_INT_ALL	( \
	UART_INT_LME5 |	UART_INT_LME1 |	UART_INT_LMSB |	UART_INT_9BIT | \
	UART_INT_OE   |	UART_INT_BE   |	UART_INT_PE   |	UART_INT_FE   | \
	UART_INT_RT   |	UART_INT_TX   |	UART_INT_RX   |	UART_INT_DSR  | \
	UART_INT_DCD  |	UART_INT_CTS  |	UART_INT_RI \
)

/* Channel Hardware Registers Read/Write */
#define	UART_REG(_ch,_ofs)	HW_CH_2_MOD_REG(_ch,_ofs)

#define	UART_REG_SET(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) = _val)

#define	UART_REG_AND(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) & _val)

#define	UART_REG_OR(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) | _val)

#define	UART_REG_AND_SET(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) &= _val)

#define	UART_REG_OR_SET(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) |= _val)

/* Utils */
#define	UART_RX_DATA(_ch)	UART_REG(_ch, UART_DATA_R_OFFSET)

#define	UART_TX_DATA(_ch,_data)	UART_REG_SET(_ch, UART_DATA_R_OFFSET, _data)

#define	UART_RX_ERR(_ch)	UART_REG(_ch, UART_RS_EC_R_OFFSET)

#define	UART_RX_ERR_CLR(_ch)	\
	UART_REG_SET(_ch, UART_RS_EC_R_OFFSET, 0x00000000)

#define	UART_RX_FIFO_EMPTY(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_RXFE)

#define	UART_RX_FIFO_FULL(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_RXFF)

#define	UART_TX_FIFO_EMPTY(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_TXFE)

#define	UART_TX_FIFO_FULL(_ch)	\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_TXFF)

#define	UART_BUSY(_ch)		\
	UART_REG_AND(_ch, UART_FLAG_R_OFFSET, UART_FR_BUSY)

#define	UART_FIFO_FLUSH(_ch)	\
	UART_REG_AND_SET(_ch, UART_LCRH_R_OFFSET, ~SCI_CH_HW_FIFO)

#define	UART_ENABLE(_ch)	\
	UART_REG_OR_SET(_ch, UART_CTL_R_OFFSET, SCI_CH_HW_ENABLE)

#define	UART_ENABLE_RX(_ch)	\
	UART_REG_OR_SET(_ch, UART_CTL_R_OFFSET, SCI_CH_HW_RX)

#define	UART_ENABLE_TX(_ch)	\
	UART_REG_OR_SET(_ch, UART_CTL_R_OFFSET, SCI_CH_HW_TX)

#define	UART_DISABLE(_ch)	\
	UART_REG_AND_SET(_ch, UART_CTL_R_OFFSET, ~SCI_CH_HW_ENABLE)

#define	UART_DISABLE_RX(_ch)	\
	UART_REG_AND_SET(_ch, UART_CTL_R_OFFSET, ~SCI_CH_HW_RX)

#define	UART_DISABLE_TX(_ch)	\
	UART_REG_AND_SET(_ch, UART_CTL_R_OFFSET, ~SCI_CH_HW_TX)

#define	UART_CLK_SYS(_ch)	\
	UART_REG_SET(_ch, UART_CC_R_OFFSET, SCI_CH_SYSCLK)

#define	UART_CLK_PIOSC(_ch)	\
	UART_REG_SET(_ch, UART_CC_R_OFFSET, SCI_CH_PIOSC)

#define	UART_BRD(_br,_clk,_div)	(_clk / ((float32) (_div * _br)))

#define	UART_SET_IBRD(_ch,_ibrd)	\
	UART_REG_SET(_ch, UART_IBRD_R_OFFSET, _ibrd)

#define	UART_SET_FBRD(_ch,_fbrd)	\
	UART_REG_SET(_ch, UART_FBRD_R_OFFSET, _fbrd)

#define	UART_SET_LINE_CTRL(_ch,_ctrl)	\
	UART_REG_SET(_ch, UART_LCRH_R_OFFSET, _ctrl)

#define	UART_SET_SYS_CTRL(_ch,_ctrl)	\
	UART_REG_SET(_ch, UART_CTL_R_OFFSET, _ctrl)

#define	UART_RIS(_ch)	UART_REG(_ch, UART_RIS_R_OFFSET)

#define	UART_MIS(_ch)	UART_REG(_ch, UART_MIS_R_OFFSET)

#define	UART_INT_CLEAR(_ch,_srcs)	\
	UART_REG_OR_SET(_ch, UART_IC_R_OFFSET, _srcs)

#define	UART_INT_ENABLE(_ch,_srcs)	\
	UART_REG_OR_SET(_ch, UART_IM_R_OFFSET, _srcs)

#define	UART_INT_DISABLE(_ch,_srcs)	\
	UART_REG_AND_SET(_ch, UART_IM_R_OFFSET, ~((uint32)_srcs))
