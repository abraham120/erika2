/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 *  @author	Gianluca Franchino
 *  @date	2013
 */
 
#ifndef __SCI_INTERNAL_H__ 
#define __SCI_INTERNAL_H__

#include "ee.h"
#include "Hardware.h"	/* Hardware Abstraction Header File. */

/*Channel Enable Masks */
#define UART_CH_HW_RTS_CTS_EN		0x80000000
#define UART_HW_CH_89_ENABLE_MASK	0x04000000
#define UART_HW_CH_12_ENABLE_MASK	0x00000010

/*Registers bit masks*/
#define UART_CLEAR_ERR_FLAGS	0xC7 /*< Clear Error Flags Mask */
#define UART_DISABLE_VAL		0xCF /*< UART channel Disable Mask */
#define UART_RESET_VAL			0x00 /*< UART channel Reset Mask */
#define UART_SCMR_RESET			0xF2 /*< Reset value of SCMR register */
#define UART_SSR_TEND_BIT		0x04 /*< UART channel Busy Mask */
#define UART_EXT_OSC			0x02 /*< UART set external clock Mask */
#define UART_SYS_OSC_NO_OUTPUT	0xFC /*< UART set sys clock, no ouput pin Mask*/
#define UART_SYS_OSC_OUTPUT		0xFD /*< UART set sys clock, with ouput pin Mask*/
#define UART_CLK_DIV_BIT		0x03 /*< UART clock divisor bits Mask */
#define UART_SSR_RX_ERRORS_BITS 0x38 /*< UART RX Errors Mask */
#define UART_RTS_CTS_EN			0x02 /*< UART Enable RTS/CTS */
#define	UART_CH_HW_RX			0x10 /*< UART Enable RX bit */
#define UART_CH_HW_TX			0x20 /*< UART Enable TX bit */
#define UART_ABCS_EN			0x10 /*< UART Async. Mode Base Clk set 8 bits.*/
#define UART_NFEN_EN			0x20 /*< UART Enable Digital Noise Filter */

/*Bit masks used to get the pckb (Peripheral Clock B) divisor. */
#define UART_PCKB_BITS_SHIFT_MASK 0x8
#define UART_PCKB_BITS_MASK 0xF


/* Channel Interrupt Sources */
#define	UART_INT_TX_END		0x04	/* Transmission	End	      */
#define	UART_INT_RX_ER		0x40	/* Reception and Error 	  */
#define	UART_INT_TX_START	0x80	/* Transmission Start	  */


/* All Interrupt	      */
#define	UART_INT_ALL (UART_INT_TX_END |	UART_INT_RX_ER | UART_INT_TX_START )

/**@brief Get registers base address of channel _ch
 */
#define UART_GET_BASE_ADDR(_ch) \
	(_ch != SCI_CHANNEL_12 ? HW_SCI_C_BASE_ADDR : HW_SCI_D_BASE_ADDR  )

/* Channel Hardware Registers Read/Write */
#define	UART_REG(_ch, _ofs)	EE_HWREG8( (uint32) (UART_GET_BASE_ADDR(_ch)) | \
		(_ch * HW_SCI_CH_OFFSET) | _ofs)

#define	UART_REG_SET(_ch, _ofs, _val) (UART_REG(_ch,_ofs) = _val)

#define	UART_REG_AND(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) & _val)

#define	UART_REG_OR(_ch,_ofs,_val)	(UART_REG(_ch,_ofs) | _val)

#define	UART_REG_AND_SET(_ch,_ofs,_val) (UART_REG(_ch,_ofs) &= _val)

#define	UART_REG_OR_SET(_ch,_ofs,_val) (UART_REG(_ch,_ofs) |= _val)

/* Utils */

#define	UART_RESET(_ch)	\
	do { \
		UART_REG_SET(_ch, HW_SCI_SCR_OFFSET, UART_RESET_VAL);\
		UART_REG_SET(_ch, HW_SCI_SSR_OFFSET, UART_RESET_VAL);\
		UART_REG_SET(_ch, HW_SCI_SCMR_OFFSET, UART_SCMR_RESET);\
		UART_REG_SET(_ch, HW_SCI_SIMR1_OFFSET, UART_RESET_VAL);\
		UART_REG_SET(_ch, HW_SCI_SPMR_OFFSET, UART_RESET_VAL);\
		UART_REG_SET(_ch, HW_SCI_SEMR_OFFSET, UART_RESET_VAL);\
	} while (0)


#define	UART_DISABLE(_ch)	\
	UART_REG_AND_SET(_ch, HW_SCI_SCR_OFFSET, UART_DISABLE_VAL)

#define UART_CLK_SYS_NO_OUTPUT(_ch)	\
	UART_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, \
			UART_REG_AND(_ch, HW_SCI_SCR_OFFSET, 0xFF) & UART_SYS_OSC_NO_OUTPUT)

#define UART_CLK_SYS_OUTPUT(_ch)	\
	UART_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, \
			UART_REG_AND(_ch, HW_SCI_SCR_OFFSET, 0xFF) & UART_SYS_OSC_OUTPUT)

#define UART_CLK_EXT_OSC(_ch)	\
	UART_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, UART_EXT_OSC)

/*#define UART_SET_CLK_DIV(_ch, _div)	\
	UART_REG_AND_SET(_ch, HW_SCI_SCMR_OFFSET, _div & UART_CLK_DIV_BIT)
*/

#define UART_GET_PCKB_DIV(_clk_conf) \
	( 0x1 << ((_clk_conf >> UART_PCKB_BITS_SHIFT_MASK) & UART_PCKB_BITS_MASK) )

#define UART_GET_CLOCK_DIV(_n) \
	(_n > 0  ? ( 0x1 << (2 * _n - 1 ) ) : 0.5  )

//#define UART_GET_CLOCK_DIV(_n) ( 0x1 << (2 * _n - 1 ) )

#define UART_BRD(_br,_clk, _n, _div)	\
	( (uint8) ((_clk) / \
			( (float32) ( UART_GET_CLOCK_DIV(_n) * _div) * _br ) )  - 1 )

#define UART_SET_BRD(_ch, _brd) \
	UART_REG_SET(_ch, HW_SCI_BRR_OFFSET, _brd)

#define UART_SET_MODE(_ch, _val) \
	UART_REG_SET(_ch, HW_SCI_SMR_OFFSET, _val)

#define UART_SET_RTS_CTS(_ch) \
	UART_REG_OR_SET(_ch, HW_SCI_SPMR_OFFSET, UART_RTS_CTS_EN)
	
#define UART_TX_ENDED(_ch) \
	UART_REG_AND(_ch, HW_SCI_SSR_OFFSET, UART_SSR_TEND_BIT)
	
#define	UART_TX_DATA(_ch,_data) \
	UART_REG_SET(_ch, HW_SCI_TDR_OFFSET, _data)

#define UART_RX_ERR(_ch) \
	UART_REG_AND(_ch, HW_SCI_SSR_OFFSET, UART_SSR_RX_ERRORS_BITS)

#define	UART_RX_ERR_CLR(_ch)	\
	UART_REG_AND_SET(_ch, HW_SCI_SSR_OFFSET, UART_CLEAR_ERR_FLAGS)

#define UART_RX_DATA(_ch) \
	UART_REG(_ch, HW_SCI_RDR_OFFSET)

#define	UART_ENABLE_RX(_ch)	\
	UART_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, UART_CH_HW_RX)

#define	UART_ENABLE_TX(_ch)	\
	UART_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, UART_CH_HW_TX)

#define	UART_DISABLE_RX(_ch)	\
	UART_REG_AND_SET(_ch, HW_SCI_SCR_OFFSET, ~UART_CH_HW_RX)

#define	UART_DISABLE_TX(_ch)	\
	UART_REG_AND_SET(_ch, HW_SCI_SCR_OFFSET, ~UART_CH_HW_TX)

#define	UART_INT_ENABLE(_ch, _srcs)	\
	UART_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, _srcs)

#define	UART_INT_DISABLE(_ch, _srcs)	\
	UART_REG_AND_SET(_ch, HW_SCI_SCR_OFFSET, ~((uint8)_srcs))

#define UART_SET_8_BIT_BASE_CK(_ch) \
	UART_REG_OR_SET(_ch, HW_SCI_SEMR_OFFSET, UART_ABCS_EN)

#define UART_EN_DFN(_ch) \
	UART_REG_OR_SET(_ch, HW_SCI_SEMR_OFFSET, UART_NFEN_EN)
	
#define UART_SET_SCR(_ch, _val) \
	UART_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, _val)



/** @brief	Enable SCI Module: clear stop bit in Module Stop Control Registers.
 *	@param  _ch SCI Channel Identifier.
 *  
 */
 
__INLINE__ void __ALWAYS_INLINE__  Sci_EnableChannel(Sci_ChannelType _ch)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of clock/pll related registers. 
	 */
	SYSTEM.PRCR.WORD = 0xA503;
	
	if (_ch < SCI_CHANNEL_8){
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) &= 
				(~(UART_CH_HW_RTS_CTS_EN >> _ch));
	} else if (_ch < SCI_CHANNEL_12) {
		EE_HWREG(HW_SYSTEM_MSTPCRC_ADDR) &= 
				(~(UART_HW_CH_89_ENABLE_MASK << (SCI_CHANNEL_9 - _ch)) );
	} else {
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) &= (~UART_HW_CH_12_ENABLE_MASK);
	}
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;

}


/** @brief	Disable SCI Module: set stop bit in Module Stop Control Registers.
 *	@param  _ch SCI Channel Identifier.
 *  
 */
__INLINE__ void __ALWAYS_INLINE__  Sci_DisableChannel(Sci_ChannelType _ch)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of clock/pll related registers. 
	 */
	SYSTEM.PRCR.WORD = 0xA503;
	
	if (_ch < SCI_CHANNEL_8){
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) |= (UART_CH_HW_RTS_CTS_EN >> _ch);
	} else if (_ch < SCI_CHANNEL_12) {
		EE_HWREG(HW_SYSTEM_MSTPCRC_ADDR) |= 
				(UART_HW_CH_89_ENABLE_MASK << (SCI_CHANNEL_9 - _ch));
	} else {
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) |= UART_HW_CH_12_ENABLE_MASK;
	}
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;

}

/** @brief Return Module stop/star bit from Module Stop Control Register
 *	(MSTPCRA).
 *	@param  _ch SCI Channel Identifier.
 *	@return  Status Mask of a Sci Module. 
 */
__INLINE__ uint32 __ALWAYS_INLINE__  Sci_IsChannelEnabled(Sci_ChannelType _ch)
{
	
	if (_ch < SCI_CHANNEL_8){
		return ((~EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR)) & 
				(UART_CH_HW_RTS_CTS_EN >> _ch));
	} else if (_ch < SCI_CHANNEL_12) {
		return ((~EE_HWREG(HW_SYSTEM_MSTPCRC_ADDR)) & 
				(UART_HW_CH_89_ENABLE_MASK << (SCI_CHANNEL_9 - _ch)));
	} else {
		return ((~EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR)) & UART_HW_CH_12_ENABLE_MASK);
	}
}

#endif