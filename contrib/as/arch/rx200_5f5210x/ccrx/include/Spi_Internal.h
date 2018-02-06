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

/** @file	Spi_Internal.h
 *  @brief	AUTOSAR SPI Handler/Driver Internal Header File.
 *  @author	Gianluca Franchino
 *  @date	2013
 */

#ifndef	SPI_INTERNAL_H
#define	SPI_INTERNAL_H

#include "ee.h"
/* Hardware Abstraction */
#include "Hardware.h"

/* Development error macros. */
#if ( SPI_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
		if( !(_exp) ) { \
			Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
			return; \
		}

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
		if( !(_exp) ) { \
			Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
			EE_hal_resumeIRQ(_flags); \
			return; \
		}

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
		if( !(_exp) ) { \
			Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
			return (_rv); \
		}

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
		if( !(_exp) ) { \
			Det_ReportError(SPI_MODULE_ID,0,_api,_err); \
			EE_hal_resumeIRQ(_flags); \
			return (_rv); \
		}

#else	/* SPI_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err) \
		if( !(_exp) ) { \
			return; \
		}

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
		if( !(_exp) ) { \
			EE_hal_resumeIRQ(_flags); \
			return; \
		}

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
		if( !(_exp) ) { \
			return (_rv); \
		}

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
		if( !(_exp) ) { \
			EE_hal_resumeIRQ(_flags); \
			return (_rv); \
		}

#endif	/* !SPI_DEV_ERROR_DETECT */

#define SPI_E_WRONG_BAUDRATE	0x5A /*< SPI  Baudrate out of range.*/


/*Channel Enable Masks */
#define SPI_CH_HW_RTS_CTS_EN		0x80000000
#define SPI_HW_CH_89_ENABLE_MASK	0x04000000
#define SPI_HW_CH_12_ENABLE_MASK	0x00000010
#define SPI_HW_CH_RSPI_ENABLE_MASK	0x00020000


#define SCI_RESET_VAL				0x00 /*< SCI channel Reset mask */
#define SCI_SCMR_RESET				0xF2 /*< Reset value of SCMR register */
#define SCI_SIMPLE_SPI_MODE_MASK	0x80 /*< Set the SCI module in simple SPI */
#define	SPI_CLOCK_SOURCE_MASK		0x02 /*< Set the SCI module in simple SPI */
#define SCI_HW_UNIT_12				0x0C /*< Last hardware ch. of unit SCIb	*/
#define SCI_ENABLE_SPI_RTX			0x30 /*< Enable TX and RX for simple SPI */
#define SCI_ENABLE_SPI_TXI_RXI		0xC0 /*< SPI Enable TXI and RXI IRQs */


#define RSPI_SPCR_SPI_EN			0x41 /*< RSPI SPI Enable bits 			*/
#define RSPI_EN_TX_RX_IRQ			0xA0 /*< RSPI TX and RX IRQs bits	*/



/*Bit masks used to get the pckb (Peripheral Clock B) divisor. */
#define SCR_PCKB_BITS_SHIFT_MASK	0x08
#define SCR_PCKB_BITS_MASK 			0x0F

#define SCR_CLK_DIV_BIT				0x03 /*< SCI clock divisor bits mask */

#define SCI_CS_POLARITY_SHIFT_MASK	0x06 /*< SCI Chip Select Pol. shift mask */

#define SPI_MASTER_SLAVE_MODE_MASK	0x02 /*< SCI Master/Slave select mask */
#define SPI_CLOCK_SEL_MODE_MASK		0x01 /*< SCI Ext/Internal clock select mask */
#define SPI_MASTER_SLAVE_SHIFT_MASK 0x01 /*< SCI Master/Slave shift mask  */
#define SPI_MULTI_MASTER_MODE_MASK	0x04 /*< SCI Multi-Master Mode mask   */
#define SMR_CLK_DIV_BIT_MASK		0x03 /*< SCI bit mask to set CLK DIV bits.*/
#define SCI_SSR_RX_ERRORS_MASK		0x38 /*< SPI RX Errors bit mask */  
#define SCI_CLEAR_ERR_FLAGS			0xC7 /*< Clear RX Errors bits mask */
#define RSPI_MULTI_MASTER_MODE_MASK	0x04 /*< RSPI Multi-Master Mode mask   */
#define RSPI_MASTER_SLAVE_MODE_MASK	0x02 /*< RSPI Master/Slave select mask */
#define RSPI_MASTER_SLAVE_SHIFT_MASK 0x02/*< RSPI Master/Slave shift mask */
#define RSPI_SPPCR_02_MASK			0x38 /*< RSPI SPPCR b0,b1,b2 mask*/
#define RSPI_SPPCR_02_SHIFT_MASK	0x03 /*< RSPI SPPCR b0,b1,b2  shift mask*/
#define RSPI_SPPCR_45_MASK			0xC0 /*< RSPI SPPCR b4,b5, mask*/
#define RSPI_SPPCR_45_SHIFT_MASK	0x02 /*< RSPI SPPCR b4,b5 reg. shift mask*/
#define RSPI_SPDCR_SHIFT_MASK		0x08 /*< RSPI SPDCR register bits shift mask*/
#define RSPI_SPDCR_MASK				0x3F /*< RSPI SPDCR register bits mask*/
#define RSPI_SPCKD_MASK				0x1C000/*< RSPI SPCKD register bits mask*/
#define RSPI_SPCKD_SHIFT_MASK		0x0E /*< RSPI SPCKD register bits shift mask*/
#define RSPI_SPCMD_CPOL_SHIFT_MASK	0x01 /*< RSPI SPCMD.CPOL bit shift mask*/
#define RSPI_SPCMD_SSLA_MASK		0x07 /*< RSPI SPCMD.SSLA bit mask*/
#define RSPI_SPCMD_SSLA_SHIFT_MASK	0x04 /*< RSPI SPCMD.SSLA bit shift mask*/
#define RSPI_SPCMD_CPHA_MASK		0x4000000 /*< RSPI SPCMD.CPHA bit mask*/
#define RSPI_SPCMD_CPHA_SHIFT_MASK	0x1A /*< RSPI SPCKD.SSLA bit shift mask*/
#define RSPI_SPCMD_MASK				0x3FE0000 /*< RSPI SPCMD bits mask*/
#define RSPI_SPCMD_SHIFT_MASK		0x0A 	/*< RSPI SPCMD bits shift mask*/
#define RSPI_SPCR2_MASK				0x58000000 /*< RSPI SPCR2 bitsmask*/
#define RSPI_SPCR2_SHIFT_MASK		0x1B	/*< RSPI SPCR2 bits shift mask*/
#define RSPI_SPCMD_BRDV_MASK		0x03 	/*< RSPI SPCMD BRDV bits mask*/
#define RSPI_SPCMD_BRDV_SHIFT_MASK	0x02 	/*< RSPI SPCMD BRDV bits sh. mask*/
#define RSPI_SPND_MASK				0xC000	/*< RSPI SPND bits mask*/
#define RSPI_SPND_SHIFT_MASK		0xF 	/*< RSPI SPND bits shift mask*/
#define RSPI_SPSR_ERR_FLAGS			0x0D 	/*< RSPI RX error flags*/
#define RSPI_SPSR_ERR_CLEAR_MASK	0xA2 	/*< RSPI RX error flags clear*/
#define RSPI_SPDR_ERR_CLR			0xF2 	/*<RSPI RX claear error flags mask.*/

#define RSPI_SET_LSB_MASK 0x00001000 /* Bit mask to set LSB mode for RSPI mod.*/

/**@brief Get registers base address of channel _ch
 */
#define SCI_GET_BASE_ADDR(_ch) \
	(_ch != SPI_HW_UNIT_12 ? HW_SCI_C_BASE_ADDR : HW_SCI_D_BASE_ADDR  )

/* Channel Hardware Registers Read/Write */
#define	SCI_REG(_ch, _ofs)	EE_HWREG8( (uint32)(SCI_GET_BASE_ADDR(_ch)) | \
		(_ch * HW_SCI_CH_OFFSET) | _ofs) 

#define	SCI_REG_SET(_ch,_ofs,_val)	(SCI_REG(_ch,_ofs) = _val)

#define	SCI_REG_AND(_ch,_ofs,_val)	(SCI_REG(_ch,_ofs) & _val)

#define	SCI_REG_OR(_ch,_ofs,_val)	(SCI_REG(_ch,_ofs) | _val)

#define	SCI_REG_AND_SET(_ch,_ofs,_val)	(SCI_REG(_ch,_ofs) &= _val)

#define	SCI_REG_OR_SET(_ch,_ofs,_val)	(SCI_REG(_ch,_ofs) |= _val)


/* HW configuration macros */

#define SCR_GET_PCKB_DIV(_clk_conf) \
	( 0x1 << ((_clk_conf >> SCR_PCKB_BITS_SHIFT_MASK) & SCR_PCKB_BITS_MASK) )


#define	SCI_RESET(_ch)	\
	do { \
		SCI_REG_SET(_ch, HW_SCI_SCR_OFFSET, SCI_RESET_VAL);\
		SCI_REG_SET(_ch, HW_SCI_SSR_OFFSET, SCI_RESET_VAL);\
		SCI_REG_SET(_ch, HW_SCI_SCMR_OFFSET, SCI_SCMR_RESET);\
		SCI_REG_SET(_ch, HW_SCI_SIMR1_OFFSET, SCI_RESET_VAL);\
		SCI_REG_SET(_ch, HW_SCI_SPMR_OFFSET, SCI_RESET_VAL);\
		SCI_REG_SET(_ch, HW_SCI_SEMR_OFFSET, SCI_RESET_VAL);\
	} while (0)

#define SCI_SET_SIMPLE_SPI(_ch) \
	SCI_REG_OR(_ch, HW_SCI_SMR_OFFSET, SCI_SIMPLE_SPI_MODE_MASK)

#define SCI_SET_SMR(_ch, _val) \
	SCI_REG_SET(_ch, HW_SCI_SMR_OFFSET, _val)

#define SCI_SET_SCR(_ch, _val) \
	SCI_REG_SET(_ch, HW_SCI_SCR_OFFSET, _val)

#define SCI_SET_CLOCK_DIV(_ch, _val) \
		SCI_REG_OR_SET(_ch, HW_SCI_SMR_OFFSET, (_val) & SMR_CLK_DIV_BIT_MASK)


#define SCI_SET_BAUDRATE(_ch, _val) \
	SCI_REG_SET(_ch, HW_SCI_BRR_OFFSET, _val)

#define SCI_SET_SPMR(_ch, _mode, _cs, _csp) \
	SCI_REG_SET(_ch, HW_SCI_SPMR_OFFSET, \
			( (_mode & SPI_MASTER_SLAVE_MODE_MASK) << \
				SPI_MASTER_SLAVE_SHIFT_MASK ) | (uint8) _cs | \
				( (uint8)(_csp) << SCI_CS_POLARITY_SHIFT_MASK ) | \
				(_mode & SPI_MULTI_MASTER_MODE_MASK) )

#define SCI_SPI_EN(_ch) \
	do {\
		SCI_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, SCI_ENABLE_SPI_RTX);\
		SCI_REG_OR_SET(_ch, HW_SCI_SCR_OFFSET, SCI_ENABLE_SPI_TXI_RXI);\
	} while(0)
		

#define SCI_SPI_DIS(_ch) \
	SCI_REG_AND_SET(_ch, HW_SCI_SCR_OFFSET, \
			(~SCI_ENABLE_SPI_RTX) & (~SCI_ENABLE_SPI_TXI_RXI))

#define SCI_SPI_SET_TDR(_ch, _val) \
	SCI_REG_SET(_ch, HW_SCI_TDR_OFFSET, _val)

#define SCI_SPI_GET_RDR(_ch) SCI_REG(_ch, HW_SCI_RDR_OFFSET)

#define SCI_GET_RX_ERR_FLAGS(_ch) \
	SCI_REG_AND(_ch, HW_SCI_SSR_OFFSET, SCI_SSR_RX_ERRORS_MASK)

#define	SCI_RX_ERR_CLR(_ch)	\
	SCI_REG_AND_SET(_ch, HW_SCI_SSR_OFFSET, SCI_CLEAR_ERR_FLAGS)
	
	
#define	RSPI_RESET(_ch)	\
	do { \
		EE_HWREG8(HW_RSPI_SPCR_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SSLP_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPPCR_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPSR_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPSCR_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPSSR_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPBR_ADDR) = 0xFF;\
		EE_HWREG8(HW_RSPI_SPDCR_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPCKD_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SSLND_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPSCR_ADDR) = 0;\
		EE_HWREG8(HW_RSPI_SPND_ADDR) = 0;\
		EE_HWREG16(HW_RSPI_SPCMD0_ADDR) = 0x070D;\
	} while (0)
	
#define RSPI_SET_SPCR(_val) \
	EE_HWREG8(HW_RSPI_SPCR_ADDR) = (uint8) (_val)

#define RSPI_ENABLE() \
	EE_HWREG8(HW_RSPI_SPCR_ADDR) |= (RSPI_SPCR_SPI_EN | RSPI_EN_TX_RX_IRQ)

#define RSPI_DISABLE() \
	EE_HWREG8(HW_RSPI_SPCR_ADDR) &= ((~RSPI_SPCR_SPI_EN) & (~RSPI_EN_TX_RX_IRQ))

#define RSPI_SET_MODE_BITS(_val, _cs_en) \
	(uint8)( (_val & RSPI_MULTI_MASTER_MODE_MASK) | \
			( (_val & RSPI_MASTER_SLAVE_MODE_MASK) << \
					RSPI_MASTER_SLAVE_SHIFT_MASK) | (uint8) (_cs_en) )
	

#define RSPI_SET_SSLP(_val, _val1) \
	EE_HWREG8(HW_RSPI_SSLP_ADDR) = (uint8) (_val << ( _val1 - SPI_HW_UNIT_13))


#define RSPI_SET_SPPCR(_val) \
	EE_HWREG8(HW_RSPI_SPPCR_ADDR) = \
	(uint8) ( ((_val & RSPI_SPPCR_02_MASK)  >> RSPI_SPPCR_02_SHIFT_MASK) | \
			((_val & RSPI_SPPCR_45_MASK)   >> RSPI_SPPCR_45_SHIFT_MASK) )

#define RSPI_SET_SPDCR(_val) \
	EE_HWREG8(HW_RSPI_SPDCR_ADDR) = \
	(uint8) ( (_val >> RSPI_SPDCR_SHIFT_MASK) & RSPI_SPDCR_MASK)


#define RSPI_SET_SPCKD(_val) \
	EE_HWREG8(HW_RSPI_SPCKD_ADDR) = \
	(uint8) ( (_val & RSPI_SPCKD_MASK) >> RSPI_SPCKD_SHIFT_MASK )


#define RSPI_SET_SSLND(_val) \
	EE_HWREG8(HW_RSPI_SSLND_ADDR) = (uint8) (_val)

#define RSPI_SET_SPND(_val) \
	EE_HWREG8(HW_RSPI_SPND_ADDR) = \
	(uint8) ( (_val & RSPI_SPND_MASK) >> RSPI_SPND_SHIFT_MASK )

#define RSPI_SET_SPCMD0(_val0, _val1, _val2) \
	EE_HWREG16(HW_RSPI_SPCMD0_ADDR) = (\
							((uint16)(_val0) << RSPI_SPCMD_CPOL_SHIFT_MASK) |\
							(((uint16)(_val1 - SPI_HW_UNIT_13) & \
										RSPI_SPCMD_SSLA_MASK) >> \
										RSPI_SPCMD_SSLA_SHIFT_MASK) | \
							(uint16)((_val2 & RSPI_SPCMD_CPHA_MASK) >> \
									RSPI_SPCMD_CPHA_SHIFT_MASK) |\
							(uint16)((_val2 & RSPI_SPCMD_MASK) >> \
									RSPI_SPCMD_SHIFT_MASK) )

									
#define RSPI_SET_SPCR2(_val) \
	EE_HWREG8(HW_RSPI_SPCR2_ADDR) = \
			(uint8)( (_val & RSPI_SPCR2_MASK) >> RSPI_SPCR2_SHIFT_MASK )

#define RSPI_SET_CLOCK_DIV(_val) \
	EE_HWREG16(HW_RSPI_SPCMD0_ADDR) |= (uint16) (\
			 (_val & RSPI_SPCMD_BRDV_MASK) << RSPI_SPCMD_BRDV_SHIFT_MASK )


#define RSPI_SET_SPBR(_val) \
	EE_HWREG8(HW_RSPI_SPBR_ADDR) = (uint8) (_val)

#define RSPI_SET_SSLND(_val) \
	EE_HWREG8(HW_RSPI_SSLND_ADDR) = (uint8) (_val)

#define RSPI_SET_SPDR(_val) \
	EE_HWREG(HW_RSPI_SPDR_ADDR) = (uint32) (_val)
	
#define RSPI_GET_SPDR() EE_HWREG(HW_RSPI_SPDR_ADDR) 

#define RSPI_GET_SPDCR(_val) EE_HWREG8(HW_RSPI_SPDCR_ADDR)

#define RSPI_GET_RX_ERR_FLAGS() \
	( EE_HWREG8(HW_RSPI_SPSR_ADDR) & RSPI_SPSR_ERR_FLAGS)

#define RSPI_CLR_RX_ERR_FLAGS() \
	( EE_HWREG8(HW_RSPI_SPSR_ADDR) &= RSPI_SPSR_ERR_CLEAR_MASK)

#define RSPI_SET_LSB_SCPMD0() \
	( EE_HWREG16(HW_RSPI_SPCMD0_ADDR) |= RSPI_SET_LSB_MASK)


/** @brief	Enable SPI Module: clear stop bit in Module Stop Control Registers.
 *	@param  _mod SPI Module Identifier.
 *  
 */
__INLINE__ void __ALWAYS_INLINE__  Spi_EnableChannel(Spi_HWUnitType _mod)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of clock/pll related registers. 
	 */
	SYSTEM.PRCR.WORD = 0xA503;
	
	if (_mod < SPI_HW_UNIT_8) {
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) &= (~(SPI_CH_HW_RTS_CTS_EN >> _mod));
	} else if (_mod < SPI_HW_UNIT_12) {
		EE_HWREG(HW_SYSTEM_MSTPCRC_ADDR) &= 
				(~(SPI_HW_CH_89_ENABLE_MASK << (SPI_HW_UNIT_9 - _mod)) );
	} else if (_mod < SPI_HW_UNIT_13){
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) &= (~SPI_HW_CH_12_ENABLE_MASK);
	} else {
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) &= (~SPI_HW_CH_RSPI_ENABLE_MASK);
	}
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;

}


/** @brief	Disable SPI Module: set stop bit in Module Stop Control Registers.
 *	@param  _mod SPI Module Identifier.
 *  
 */
__INLINE__ void __ALWAYS_INLINE__  Spi_DisableChannel(Spi_HWUnitType _mod)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of clock/pll related registers. 
	 */
	SYSTEM.PRCR.WORD = 0xA503;
	
	if (_mod < SPI_HW_UNIT_8){
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) |= (SPI_CH_HW_RTS_CTS_EN >> _mod);
	} else if (_mod < SPI_HW_UNIT_12) {
		EE_HWREG(HW_SYSTEM_MSTPCRC_ADDR) |= 
				(SPI_HW_CH_89_ENABLE_MASK << (SPI_HW_UNIT_9 - _mod));
	} else if (_mod < SPI_HW_UNIT_13) {
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) |= SPI_HW_CH_12_ENABLE_MASK;
	} else {
		EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR) |= SPI_HW_CH_RSPI_ENABLE_MASK;
	}
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;

}

/** @brief Return Module stop/star bit from Module Stop Control Register
 *	(MSTPCRA).
 *	@param  _mod SPI Module Identifier.
 *	@return  Status mask of a Spi Module. 
 */
__INLINE__ uint32 __ALWAYS_INLINE__  Spi_IsChannelEnabled(Spi_HWUnitType _mod)
{
	
	if (_mod < SPI_HW_UNIT_8){
		return ((~EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR)) & 
				(SPI_CH_HW_RTS_CTS_EN >> _mod));
	} else if (_mod < SPI_HW_UNIT_12) {
		return ((~EE_HWREG(HW_SYSTEM_MSTPCRC_ADDR)) & 
				(SPI_HW_CH_89_ENABLE_MASK << (SPI_HW_UNIT_9 - _mod)));
	} else if (_mod < SPI_HW_UNIT_13) {
		return ((~EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR)) & SPI_HW_CH_12_ENABLE_MASK);
	} else {
		return ((~EE_HWREG(HW_SYSTEM_MSTPCRB_ADDR)) & SPI_HW_CH_RSPI_ENABLE_MASK);		
	}
}


/*
 * Type that holds all global data for Spi Driver
 */
 typedef struct {
	 Spi_StatusType	DriverState;		/* SPI Handler/Driver State   */

	const Spi_ConfigType *ConfigPtr;	/* Actual Configuration	      */

#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
	Spi_AsyncModeType AsyncMode;	/* Asynchronous Mode.	      */
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
	Spi_SynchronousType	TransmitMode;/* Transmission Mode.	      */
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
	/* Current Asynchronous Job Index. */
	Spi_JobType			CurrAsyncJobIdx;
	/* Current Synchronous Job Index.  */
	Spi_JobType			CurrSyncJobIdx;
#else	/* ( SPI_LEVEL_DELIVERED == 2 ) */
	Spi_JobType			CurrJobIdx;	/* Current Job Index.         */
#endif	/* !( SPI_LEVEL_DELIVERED == 2 ) */
} Spi_GlobalType;

/*
 * Global config
 */
extern	Spi_GlobalType Spi_Global;

#include "Mcu.h"

/*
 * MCU Global Configuration Reference
 */
typedef struct {
	boolean			Init;		/* MCU Driver Initialized?    */

	const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

	Mcu_ClockType	ClockSetting;	/* Actual Clock Setting	      */

}	Mcu_GlobalType;

/*
 * MCU Global Configuration External Reference
 */
extern Mcu_GlobalType Mcu_Global;

/*
 * Channel State.
 */
typedef struct {

#if	( \
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
)
	Spi_NumberOfDataType	SpiEbLen;	/* External Buffers Elements Number.  */
	const Spi_DataType *	SpiSrcEbPtr;	/* Source External Buffer Pointer.*/
	Spi_DataType *	SpiDstEbPtr;  /* Destination External Buffer Pointer. */

	/* Dummy Buffers to be used when User don't call Spi_SetupEB(). */
	Spi_DataType		SpiSrcEb;	/* Fake Source External Buffer.	      */
	Spi_DataType		SpiDstEb;	/* Fake Destination External Buffer.  */
#endif	/* 
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) ||
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */
#if	( \
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) \
)
	boolean	SpiSrcIbEmpty;	/* Source Internal Buffer Empty Flag.	      */
	boolean	SpiDstIbEmpty;	/* Destination Internal Buffer Empty Flag.    */
#endif	/* 
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
 	 */

}	Spi_ChannelStateType;

#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
/* Internal Buffers moved in Spi_Cfg.c */
extern	Spi_DataType *	SpiChSrcIb[];	/* Source Internal Buffer.			*/
extern	Spi_DataType *	SpiChDstIb[];	/* Destination Internal Buffer.		*/
#endif	/* 
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
 	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
 	 */

/*
 * Channel Status Array.
 */
extern Spi_ChannelStateType	SpiChannelStatus[SPI_CHANNELS_MAX_NUMBER];

/*
 * Hardware Unit State.
 */
typedef struct {

	Spi_JobType		SpiOwnerIdx;	/* Hardware Unit Owner Job Index.     */

}	Spi_HwUnitStateType;

/*
 * Hardware Unit Status Array.
 */
extern Spi_HwUnitStateType	SpiHwUnitStatus[SPI_MAX_HW_UNIT];

/*
 * Job State.
 */
typedef	struct {

	Spi_SequenceType	SpiOwnerIdx;	/* Job Owner Sequence Index.	      */
	Spi_JobResultType	SpiJobResult;	/* Job Result.			      */

}	Spi_JobStateType;

/*
 * Job Status Array.
 */
extern Spi_JobStateType	SpiJobStatus[SPI_JOBS_MAX_NUMBER];

/*
 * Sequence State.
 */
typedef	struct {
	Spi_JobType	SpiCurrJobIdx;			/* Current Job Index.	*/
	Spi_SeqResultType	SpiSeqResult;	/* Sequence Result.		*/
}	Spi_SeqStateType;

/*
 * Sequence Status Array.
 */
extern Spi_SeqStateType	SpiSeqStatus[SPI_SEQUENCES_MAX_NUMBER];

/*
 * Current Job Index Setup.
 *
 * param	CallType	(A)Synchronous Call Type.
 * return	SpiJobIdx		Job Index to Setup.
 */
void Spi_SetCurrSpiJobIdx(
#if	( SPI_LEVEL_DELIVERED == 2 )
		Spi_SynchronousType	CallType,
#endif
  Spi_JobType		SpiJobIdx
);


/*
 * Main Function Internal Handling.
 *
 * param	CallType	(A)Synchronous Call Type.
 */
void Spi_MainFunction_Internal_Handling(
#if	( SPI_LEVEL_DELIVERED == 2 )
		Spi_SynchronousType	CallType
#else
  void
#endif
);

/*
 * Job End. Function used to handling the end of a job.
 *
 */
void Spi_JobEnd(Spi_HWUnitType	HWUnit, Spi_JobResultType	JobResult);

/*
 * Function used to transmit and receive a Spi frame.
 * 
 */
void Spi_trx(Spi_HWUnitType HWUnit);

/*
 * Store a spi frame into SpiRxTable.
 */
void Spi_store(Spi_HWUnitType HWUnit);

/*
 * Stop Spi hw unit.
 */
void Spi_HwDisable(Spi_HWUnitType HWUnit);


#endif /* SPI_INTERNAL_H*/
