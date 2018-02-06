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

/** @file	Gpt_Internal.h
 *  @brief	AUTOSAR-"like" GPT Driver Internal Header File.
 *  @author	Gianluca Franchino
 *  @date	2012
 */

#ifndef	__GPT_INTERNAL_H__
#define	__GPT_INTERNAL_H__


/* Hardware Abstraction */
#include "ee.h"
#include "Hardware.h"

extern uint8 start_flag;

/* Hardware Timer Module Status (MSTPCR A)*/
#define GPT_HW_TMR_TMR_ON		0x00000030
#define GPT_HW_TMR_CMT_ON		0x0000C000
#define GPT_HW_TMR_MTU2A_ON		0x00000200
#define	GPT_HW_TMR_STOP_TMR01	0x00000020
#define	GPT_HW_TMR_STOP_TMR23	0x00000010
#define	GPT_HW_TMR_STOP_CMT01	0x00008000
#define	GPT_HW_TMR_STOP_CMT23	0x00004000
#define GPT_HW_TMR_STOP_MTU2A	0x00000200
#define	GPT_HW_TMR_NSTOP_TMR01	0xFFFFFFDF
#define	GPT_HW_TMR_NSTOP_TMR23	0xFFFFFFEF
#define	GPT_HW_TMR_NSTOP_CMT01	0xFFFF7FFF
#define	GPT_HW_TMR_NSTOP_CMT23	0xFFFFBFFF
#define GPT_HW_TMR_NSTOP_MTU2A	0xFFFFFDFF


#define GPT_TIMER_NOT_RUNNING 0
#define GPT_TIMER_RUNNING	1
#define GPT_TIMER_EXPIRED 1
#define GPT_TIMER_NOT_EXPIRED 0
#define GPT_TIMER_STOPPED 1
#define GPT_TIMER_NOT_STOPPED 0

/* Hardware Timer Module Notifications */
#define	GPT_HW_TMR_NOTIF_ALL_OFF	0x00
#define	GPT_HW_TMR_NOTIF_TMR0_ON	0x01
#define	GPT_HW_TMR_NOTIF_TMR1_ON	0x02
#define	GPT_HW_TMR_NOTIF_TMR2_ON	0x03
#define	GPT_HW_TMR_NOTIF_TMR3_ON	0x04
#define	GPT_HW_TMR_NOTIF_TMR01_ON	0x05
#define	GPT_HW_TMR_NOTIF_TMR23_ON	0x06
#define	GPT_HW_TMR_NOTIF_CMT0_ON	0x07
#define	GPT_HW_TMR_NOTIF_CMT1_ON	0x08
#define	GPT_HW_TMR_NOTIF_CMT2_ON	0x09
#define	GPT_HW_TMR_NOTIF_CMT3_ON	0x0A
#define GPT_HW_TMR_NOTIF_MTU0_ON	0x0B
#define GPT_HW_TMR_NOTIF_MTU1_ON	0x0C
#define GPT_HW_TMR_NOTIF_MTU2_ON	0x0D
#define GPT_HW_TMR_NOTIF_MTU3_ON	0x0E
#define GPT_HW_TMR_NOTIF_MTU4_ON	0x0F
#define GPT_HW_TMR_NOTIF_MTU5_ON	0x10
#define	GPT_HW_TMR_NOTIF_ALL_ON		0x11

#define GTP_EN_TMR_CMIA 1
#define GTP_EN_TMR_CMIB 0

/*
 * Internal Channels Identifiers
 */ 
#define	GPT_INTERNAL_CHANNEL_TMR0	0x00	/**< Channel TMR 0  */
#define	GPT_INTERNAL_CHANNEL_TMR1	0x01	/**< Channel TMR 1  */
#define	GPT_INTERNAL_CHANNEL_TMR2	0x02	/**< Channel TMR 2  */
#define	GPT_INTERNAL_CHANNEL_TMR3	0x03	/**< Channel TMR 3  */
#define	GPT_INTERNAL_CHANNEL_TMR01	0x04	/**< Channel TMR 01 */
#define	GPT_INTERNAL_CHANNEL_TMR23	0x05	/**< Channel TMR 23 */
#define	GPT_INTERNAL_CHANNEL_CMT0	0x06	/**< Channel CMT 0  */
#define	GPT_INTERNAL_CHANNEL_CMT1	0x07	/**< Channel CMT 1  */
#define	GPT_INTERNAL_CHANNEL_CMT2	0x08	/**< Channel CMT 2  */
#define	GPT_INTERNAL_CHANNEL_CMT3	0x09	/**< Channel CMT 3  */
#define	GPT_INTERNAL_CHANNEL_MTU0	0x0A	/**< Channel MTU2A MTU0 */
#define	GPT_INTERNAL_CHANNEL_MTU1	0x0B	/**< Channel MTU2A MTU1 */
#define	GPT_INTERNAL_CHANNEL_MTU2	0x0C	/**< Channel MTU2A MTU2 */
#define GPT_INTERNAL_CHANNEL_MTU12	0x0D	/**< Channel MTU2A MTU12 */
#define	GPT_INTERNAL_CHANNEL_MTU3	0x0E	/**< Channel MTU2A MTU3 */
#define	GPT_INTERNAL_CHANNEL_MTU4	0x0F	/**< Channel MTU2A MTU4 */
#define	GPT_INTERNAL_CHANNEL_MTU5U	0x10	/**< Channel MTU2A MTU5U */
#define	GPT_INTERNAL_CHANNEL_MTU5V	0x11	/**< Channel MTU2A MTU5V */
#define	GPT_INTERNAL_CHANNEL_MTU5W	0x12	/**< Channel MTU2A MTU5W */
/**< Number of GPT channels. */
#define GPT_INTERNAL_NUMBER_OF_CH (GPT_INTERNAL_CHANNEL_MTU5W + 1) 

/*
 * Configuration bit masks
 */	
#define GPT_MTU2A_CLEAR_DIS 	0x00	/**< TMR Clearing is disabled. */
#define GPT_MTU2A_CMP_A_MASK	0x20	/**< MTU Cleared by compare match A */
#define GPT_MTU2A_CMP_B_MASK	0x40	/**< MTU Cleared by compare match B */
#define GPT_MTU2A_CMP_C_MASK	0xA0	/**< MTU Cleared by compare match C */
#define GPT_MTU2A_CMP_D_MASK	0xC0	/**< MTU Cleared by compare match D */

#define GPT_PRE_BITS_MASK	0x1F	/**< Prescaler Setting bits mask */

#define GPT_TMR_CLK_MASK	0x1F	/**< TMR module clock setting mask. */
#define GPT_TMR_CCLR_MASK	0x18	/**< TMR module clear mode setting mask. */
#define GPT_TMR_CMP_A_MASK	0x08	/**< TMR module Cleared by compare match A.*/
#define GPT_TMR_CMP_B_MASK	0x10	/**< TMR module Cleared by compare match B.*/
#define GPT_TMR_CCLR_SH_MASK 0x02	/**< TMR module clear mode shift mask. */
#define GPT_TMR_TMRIS_DIS 	0xEF	/**< TMR module TMRIS bit disable mask. */
#define GPT_TMR_CMP_A_ISR_MASK 	0x40 /**< TMR module CMIA enable mask. */
#define GPT_TMR_CMP_B_ISR_MASK 	0x80 /**< TMR module CMIB enable mask. */
#define GPT_CMT_CLK_MASK	0x03	/**< CMT module clock setting mask. */
#define GPT_MTU_CLK_MASK	0x1F	/**< CMT module clock setting mask. */
#define GPT_MTU2A_CCLR_MASK 0xE0	/**< MTU2A module clear mode setting mask.*/
#define GPT_MTU2A_TMDR_N_MODE_MASK	0xF0 /**< MTU2A normal mode setting mask.*/
#define GPT_MTU2A_TSR_MASK	0x7F 	/**< MTU2A TSR register setting mask.*/
#define GPT_MTU34_TRWER_EN_MASK	0x01 /**< MTU3 and MTU4 write/read enable mask.*/
#define GPT_MTU34_TRWER_DIS_MASK	0x00 /**< MTU3 and MTU4 write/read dis. mask.*/
#define GPT_MTU5_CLR_BIT_MASK 0x0010	/**< MTU5 CLR enable bit mask. */
#define GPT_MTU5U_TCNTCMPCLR_EN_MASK 0x04	/**< MTU5U TCNTCMPCLR enable bit.*/
#define GPT_MTU5V_TCNTCMPCLR_EN_MASK 0x02	/**< MTU5V TCNTCMPCLR enable bit.*/
#define GPT_MTU5W_TCNTCMPCLR_EN_MASK 0x01	/**< MTU5W TCNTCMPCLR enable bit.*/
#define GPT_MTUA2_CASCADE_MODE	0x07	/**< MTU1 clock is on MUT2 overflow. */
#define GPT_TSYR_MTU12_ENABLE	0x06	/**< MTU12 synchronous operation enable.*/
#define GPT_CMTx_CMCR_RESET_VAL	0x0080 /**< CMT CMCR register reset value. */
#define GPT_MSTPCRA_TIMERS_MASK 0xC230 /** Stop bits concerning timer modules.*/

#define GPT_HW_TMR_EMPTY_VALUE	0x0 /**< Timer empty */


/* Bit positions in interrupt enable registers of MTU2A */
#define GPT_MTU2A_TGIEA_POS	0x0 /**< MTU2A TGR Interrupt Enable A bit pos. */
#define GPT_MTU2A_TGIEB_POS	0x1 /**< MTU2A TGR Interrupt Enable B bit pos. */
#define GPT_MTU2A_TGIEC_POS	0x2 /**< MTU2A TGR Interrupt Enable C bit pos. */
#define GPT_MTU2A_TGIED_POS	0x3 /**< MTU2A TGR Interrupt Enable D bit pos. */
#define GPT_MTU2A_TGIE5W_POS 0x0 /**< MTU2A TGR Interrupt Enable 5W bit pos. */
#define GPT_MTU2A_TGIE5V_POS 0x1 /**< MTU2A TGR Interrupt Enable 5V bit pos. */
#define GPT_MTU2A_TGIE5U_POS 0x2 /**< MTU2A TGR Interrupt Enable 5U bit pos. */
#define GPT_EN_NOTIF_MASK 	0x1	/**<  Enable Notification mask. */

/*
 * Channel is Valid Test
 *
 * param	_ch	Numeric ID of a GPT channel. (Gpt_ChannelType)
 * return	TRUE:	Valid GPY channel 
 * 			FALSE:	Invalid Channel
 *
 * This macro function returns if numeric id of a channel is valid or not.
 */
#define	GPT_CH_IS_VALID(_ch) ( _ch <= GPT_INTERNAL_NUMBER_OF_CH )


/** @brief	Set notification enabled bit.
 *	@param	_ch Timer channel.
 */		
#define GPT_CH_2_NOTIF_MASK(_ch) (GPT_EN_NOTIF_MASK << _ch)

#define GPT_CLEAR_FLAG(_flag, _ch) \
	( _flag &= ~(0x1 << _ch) )

#define GPT_SET_FLAG(_flag, _ch) \
	( _flag |= (0x1 << _ch) )

#define GPT_GET_FLAG(_flag, _ch) ( _flag & (0x1 << _ch) )

/** @brief	Get prescaler configuration bits from _pre.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_PRES_CONF(_pre) \
	( (uint8) (_pre & GPT_PRE_BITS_MASK) )

/** @brief	Get reset condition bit from _val.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_RESET_COND_BIT(_val) \
	( (ConfigPtr->GptChannelHWConfig >> 0x1) & 0x80 )

/** @brief	Set 8 bits registers.
 *	@param	_reg Register addr.
 *	@param  _val Register value.
 */
#define GPT_SET_REG8(_reg, _val) \
		( EE_HWREG8(_reg) = (uint8)(_val) )

/** @brief	Set 16 bits registers.
 *	@param	_reg Register addr.
 *	@param  _val Register value.
 */
#define GPT_SET_REG16(_reg, _val) \
		( EE_HWREG16(_reg) = (uint16)(_val) )

/** @brief	Set 32 bits registers.
 *	@param	_reg Register addr.
 *	@param  _val Register value.
 */
#define GPT_SET_REG(_reg, _val) \
		( EE_HWREG(_reg) = (uint32)(_val) )

/** @brief	Get 8 bits registers.
 *	@param	_reg Register addr.
 */
#define GPT_GET_REG8(_reg) \
		( EE_HWREG8(_reg) )

/** @brief	Get 16 bits registers.
 *	@param	_reg Register addr.
 */
#define GPT_GET_REG16(_reg) \
		( EE_HWREG16(_reg) )

/** @brief	Get 32 bits registers.
 *	@param	_reg Register addr.
 */
#define GPT_GET_REG(_reg) \
		( EE_HWREG(_reg) )


/** @brief	Enable Interrupt Control Unit (ICU) IER reg bit. 
 *  @param _reg IER register.
 *  @param _b_mask Bit mask used to set the correct bit. 
 */
#define GPT_EN_ICU_IER(_reg, _b_mask) \
	GPT_SET_REG8(_reg, GPT_GET_REG8(_reg) | _b_mask)

/** @brief	Disable Interrupt Control Unit (ICU) IER reg bit. 
 *  @param _reg IER register.
 *  @param _b_mask Bit mask used to clear the correct bit. 
 */
#define GPT_DIS_ICU_IER(_reg, _b_mask) \
	GPT_SET_REG8(_reg, GPT_GET_REG8(_reg) & (~(_b_mask)))

/** @brief	Set  Interrupt priority into Interrupt  prior. Register (IPR). 
 *  @param _reg IPR register.
 *  @param _pri Priority level. 
 */
#define GPT_SET_ICU_IPR(_reg, _pri) GPT_SET_REG8(_reg, _pri)


/** @brief	TCCR register address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_TMR_TCCR_ADDR(_ch) \
	( ((uint32)HW_TCCR_ADDR_BASE | ((_ch & 0x2) << 3)) | (_ch & 0x1) )

/** @brief	Get TCR register address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_TMR_TCR_ADDR(_ch) \
	( ((uint32)HW_TMR_TCR_ADDR_BASE | ((_ch & 0x2) << 3)) | (_ch & 0x1) )

/** @brief	Get TCORA register address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_TMR_TCORA_ADDR(_ch) \
	( ( (uint32)(HW_TMR0_TCORA_ADDR) | ( (_ch & 0x2) << 3 )) | (_ch & 0x1) )
		
/** @brief	Get TCORB register address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_TMR_TCORB_ADDR(_ch) \
	( ((uint32)HW_TMR0_TCORB_ADDR | ((_ch & 0x2) << 3)) | (_ch & 0x1) )

/** @brief	GET CMT UNIT bit for CMCR address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define GPT_CH_TO_CMCR_UNIT(_ch) \
	( 0x2 << (0x2 & (0x1 << (_ch & 0x1))) )

/** @brief	GET CMT UNIT bit for CMCOR address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define GPT_CH_TO_CMCOR_UNIT(_ch) \
	( 0x6 << (0x1 & _ch) )

/** @brief	GET CMCR register address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_CMT_CMCR_ADDR(_ch) \
	( ((uint32)HW_CMT_BASE_ADDR | ((_ch << 1) & 0x10)) | \
			GPT_CH_TO_CMCR_UNIT(_ch) )

/** @brief	GET CMCOR register address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_CMT_CMCOR_ADDR(_ch) \
	( ((uint32)HW_CMT_BASE_ADDR | ((_ch << 1) & 0x10)) | \
			GPT_CH_TO_CMCOR_UNIT(_ch) )

/** @brief	Get TRM TCNT register address of channel _ch.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_TMR_TCNT_ADDR(_ch) \
	( ((uint32)HW_TCNT_ADDR_BASE | ((_ch & 0x2) << 3)) | (_ch & 0x1) )

/** @brief	Get TMR TCCR register value of channel _ch.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_TMR_TCCR(_ch) ( EE_HWREG8(GPT_GET_TMR_TCCR_ADDR(_ch)) )

/** @brief	Get TCR register of TMRx.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_TMR_TCR(_ch) ( EE_HWREG8(GPT_GET_TMR_TCR_ADDR(_ch)) )

/** @brief	Get TCORA register of TMRx.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_TMR_TCORA(_ch) \
			( EE_HWREG8(GPT_GET_TMR_TCORA_ADDR(_ch)) )

/** @brief	Get TCORB register of TMRx.
 *	@param	_ch Timer channel.
 */
#define	GPT_GET_TMR_TCORB(_ch) \
			( EE_HWREG8(GPT_GET_TMR_TCORB_ADDR(_ch)) )

/** @brief	Get CMCOR register of CMTx.
*	@param	_ch Timer channel.	
*/
#define	GPT_GET_CMT_CMCOR(_ch) \
		( EE_HWREG16(GPT_GET_CMT_CMCOR_ADDR(_ch)) )

/*MTU2A, MTU0 timer  TCR register offset. */
#define GPT_MTU0_TCR_OFFSET	0x00000080

/*MTU2A, MTU0 timer TMDR register offset. */
#define GPT_MTU0_TMDR_OFFSET	0x00000080
		
/** @brief	Get TCR register address of channel MTU0 <= _ch <= MTU2.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_MTU0_2_TCR_ADDR(_ch) \
		((uint32)(HW_MTU0_TCR_ADDR) + \
				(GPT_MTU0_TCR_OFFSET & ((_ch - GPT_INTERNAL_CHANNEL_MTU0) << 7))+\
				(GPT_MTU0_TCR_OFFSET & ((_ch - GPT_INTERNAL_CHANNEL_MTU0)) << 6) )

/** @brief	Get TCR register address of channel MTU3 <= _ch <= MTU4.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_MTU3_4_TCR_ADDR(_ch) \
		((uint32)HW_MTU3_TCR_ADDR | (_ch & 0x1 ))
		
/** @brief	Get TCR register address of channel MTU5U <= _ch <= MTU5W.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_MTU5_TCR_ADDR(_ch) \
		((uint32) HW_MTU5U_TCR_ADDR | (_ch & 0x1 ) << 4)

/** @brief	Get TMDR register address of channel MTU0 <= _ch <= MTU2.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_MTU0_2_TMDR_ADDR(_ch) \
		((uint32)HW_MTU3_TMDR_ADDR | (_ch & 0x1 ))

/** @brief	Get TMDR register address of channel MTU3 <= _ch <= MTU4.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_MTU3_4_TMDR_ADDR(_ch) \
		((uint32)(HW_MTU0_TMDR_ADDR) + \
				(GPT_MTU0_TMDR_OFFSET & (_ch - GPT_INTERNAL_CHANNEL_MTU0) << 7)+\
				(GPT_MTU0_TMDR_OFFSET & (_ch - GPT_INTERNAL_CHANNEL_MTU0)) << 6 )


/** @brief	Get registers value of mdule MTU2A.
 *	@param	_addr Register address.
 */
#define GPT_GET_MTU2A_REG8(_addr) ( EE_HWREG8(_addr) )


/** @brief	Get CNTCMPCLR value of module MTU2A.
 */
#define GPT_GET_MTU5_CMP_CLR() \
	( GPT_GET_MTU2A_REG8(HW_MTU5_TCNTCMPCLR_ADDR))

/** @brief	Set CNTCMPCLR value of module MTU2A.
 *  @param _val Value to set
 */
#define GPT_SET_MTU5_CMP_CLR(_val) \
	( EE_HWREG8(HW_MTU5_TCNTCMPCLR_ADDR) = _val)

		
/** @brief	Set TCCR register of TMRx.
 *	@param	_ch Timer channel.
 *	@param  _val Register value.
 */
#define GPT_SET_TMR_CLK(_ch, _val) \
		( EE_HWREG8(GPT_GET_TMR_TCCR_ADDR(_ch)) |= \
				(uint8)(_val  & GPT_TMR_CLK_MASK) )

/** @brief	Enable Compare match A interrupt requests of TMRx.
 *	@param	_ch Timer channel.
 */
#define GPT_SET_TMR_CMIEA(_ch) \
		( EE_HWREG8(GPT_GET_TMR_TCR_ADDR(_ch)) |= 0x40 )
		
/** @brief	Disable Compare match A interrupt requests of TMRx.
 *	@param	_ch Timer channel.
 */
#define GPT_CLEAR_TMR_CMIEA(_ch) \
		( EE_HWREG8(GPT_GET_TMR_TCR_ADDR(_ch)) &= 0xBF )

/** @brief	Enable Compare match B interrupt requests of TMRx.
 *	@param	_ch Timer channel.
 */
#define GPT_SET_TMR_CMIEB(_ch) \
		( EE_HWREG8(GPT_GET_TMR_TCR_ADDR(_ch)) |= 0x80 )

/** @brief	Disable Compare match B interrupt requests of TMRx.
 *	@param	_ch Timer channel.
 */
#define GPT_CLEAR_TMR_CMIEB(_ch) \
		( EE_HWREG8(GPT_GET_TMR_TCR_ADDR(_ch)) &= 0x7F )

/** @brief	Set TCR register of TMRx.
 *	@param	_ch Timer channel.
 *	@param  _val Register value.
 */
#define GPT_SET_TMR_TCR(_ch, _val) \
		( EE_HWREG8(GPT_GET_TMR_TCR_ADDR(_ch)) = (uint8) (_val) )

/** @brief	Set TMR TCCR register value of channel _ch.
 *	@param	_ch Timer channel.
 *	@param  _val Register value.
 */
#define GPT_SET_TMR_TCCR(_ch, _val) \
	( EE_HWREG8(GPT_GET_TMR_TCCR_ADDR(_ch)) = (uint8) (_val))

/** @brief	Set TCORA register of TMRx.
 *	@param	_ch Timer channel.
 *	@param  _val Register value.
 */
#define	GPT_SET_TMR_TCORA(_ch, _val) \
			( EE_HWREG8(GPT_GET_TMR_TCORA_ADDR(_ch)) = (uint8) (_val) )

/** @brief	Set TCORA (16 bits access) register of TMRx.
 *	@param	_ch Timer channel.
 *	@param  _val Register value.
 */
#define	GPT_SET_TMR_TCORA16(_ch, _val)\
			(EE_HWREG16(GPT_GET_TMR_TCORA_ADDR(_ch)) = (uint16) (_val) )

/** @brief	Set TCORB register of TMRx.
 *	@param	_ch Timer channel.
 *	@param  _val Register value.
 */
#define	GPT_SET_TMR_TCORB(_ch, _val)\
		(EE_HWREG8(GPT_GET_TMR_TCORB_ADDR(_ch)) = (uint8) (_val) )


/** @brief	Set TCORB (16 bits access) register of TMRx.
 *	@param	_ch Timer channel.
 *	@param  _val Register value.
 */
#define	GPT_SET_TMR_TCORB16(_ch, _val)\
			(EE_HWREG16(GPT_GET_TMR_TCORB_ADDR(_ch)) = (uint16) (_val) )


/** @brief	Set register bit of module MTU2A.
 *	@param	_addr Register address.
 *	@param  _pos Bit position.
 */
#define GPT_SET_MTU2A_BIT_REG8(_addr, _pos) \
		( EE_HWREG8(_addr) |= (uint8) (0x1 << _pos) )

/** @brief	Set TCNT register of TMRx.
 *	@param	_ch Timer channel.
 */
#define GPT_SET_TMR_TCNT(_ch, _val) \
	do { \
			if (_ch == GPT_INTERNAL_CHANNEL_TMR01) {\
				EE_HWREG16(HW_TMR01_TCNT_ADDR_BASE) = _val;\
			} else if (_ch == GPT_INTERNAL_CHANNEL_TMR23) {\
				EE_HWREG16(HW_TMR23_TCNT_ADDR_BASE) = _val;\
			} else {\
				EE_HWREG8(GPT_GET_TMR_TCNT_ADDR(_ch)) = _val;\
			}\
} while (0)
			

/** @brief	Clear TCNT register of TMRx.
 *	@param	_ch Timer channel.
 */
#define GPT_CLEAR_TMR_TCNT(_ch) GPT_SET_TMR_TCNT(_ch, 0)


/** @brief	Set CKS bits in CMCR register of CMTx.
 *	@param	_ch Timer channel.
 *	@param  _val Bit values.	
 */
/*#define GPT_SET_CMT_CLK(_ch, _val) \
		(EE_HWREG16(GPT_GET_CMT_CMCR_ADDR(_ch)) |= \
				((uint16)_val & GPT_CMT_CLK_MASK))
				*/
	
/** @brief	Set CMCR register of CMTx.
*	@param	_ch Timer channel.
*	@param  _val Register value.	
*/
#define	GPT_SET_CMT_CMCR(_ch, _val) \
		( EE_HWREG16(GPT_GET_CMT_CMCR_ADDR(_ch)) = (uint16) (_val) )

/** @brief	Set CMCOR register of CMTx.
*	@param	_ch Timer channel.
*	@param  _val Register value.	
*/
#define	GPT_SET_CMT_CMCOR(_ch, _val) \
		( EE_HWREG16(GPT_GET_CMT_CMCOR_ADDR(_ch)) = (uint16) (_val) )


/** @brief	Enable Compare Match Interrupt of CMTx.
*	@param	_ch Timer channel.	
*/
#define	GPT_SET_CMT_CMIE(_ch) \
	( EE_HWREG16(GPT_GET_CMT_CMCR_ADDR(_ch)) |= 0x0040 )

/** @brief	Disable Compare match A interrupt requests of CMTx.
 *	@param	_ch Timer channel.
 */
#define GPT_CLEAR_CMT_CMIE(_ch) \
	( GPT_SET_CMT_CMCR(_ch, GPT_GET_CMT_CMCR(_ch) & 0xBF) )


/** @brief	Set CMSTR register of CMTx.
*	@param	_ch Timer channel.
*	@param  _val Register value.	
*/
#define	GPT_SET_CMT_CMSTR(_ch, _val) \
		( EE_HWREG16(GPT_GET_CMT_CMSTR_ADDR(_ch)) = (uint16) (_val) )


/** @brief	Get the address of CMSTR register of CMTx module.
*	@param	_ch Timer channel.	
*/
#define GPT_GET_CMT_CMSTR_ADDR(_ch) \
	((uint32)HW_CMT_BASE_ADDR + ((_ch & 0x80) >> 3))

/*Displacement of CMCNT address with respect to HW_CMT_BASE_ADDR. */
#define GPT_CMT_CMCNT_DISP 0x00000004	
											
/** @brief	Get the address of CMCNT register of CMTx module.
*	@param	_ch Timer channel.	
*/
#define GPT_GET_CMT_CMCNT_ADDR(_ch) \
	( ((uint32)HW_CMT_BASE_ADDR |  \
			((GPT_CMT_CMCNT_DISP | (_ch & 0x1)) << \
					(_ch & 0x1)) | ((_ch & 0x80) >> 3)))

/** @brief	Get CMCR register of CMTx.
*	@param	_ch Timer channel.	
*/
#define GPT_GET_CMT_CMCR(_ch) ( EE_HWREG16(GPT_GET_CMT_CMCR_ADDR(_ch)) )


/** @brief	Start the timer of CMTx module.
*	@param	_ch Timer channel.	
*/
#define	GPT_START_CMT(_ch) \
		( EE_HWREG16(GPT_GET_CMT_CMSTR_ADDR(_ch)) |= 0x1 << (_ch & 0x01) )
	
/** @brief	Stop the timer of CMTx module.
*	@param	_ch Timer channel.	
*/
#define	GPT_STOP_CMT(_ch) \
		( EE_HWREG16(GPT_GET_CMT_CMSTR_ADDR(_ch)) &= ~(0x01 << (_ch & 0x01)) )

/** @brief	Clear TCNT register of CMTx.
 *	@param	_ch Timer channel.
 */
#define GPT_CLEAR_CMT_TCNT(_ch) (EE_HWREG16(GPT_GET_CMT_CMCNT_ADDR(_ch)) = 0x0)

/** @brief	Get TCNT register of CMTx.
 *	@param	_ch Timer channel.
 */
#define GPT_GET_CMT_TCNT(_ch) ( EE_HWREG16(GPT_GET_CMT_CMCNT_ADDR(_ch)) )

/** @brief	Is MTU5x running?
*	@param	_ch Timer channel.
*/
#define GPT_CMT_IS_RUNNING(_ch) \
		( EE_HWREG16(GPT_GET_CMT_CMSTR_ADDR(_ch)) & (0x1 << (_ch & 0x01)) )

/** @brief	Start the timer of MTU2A module.
*	@param	_ch Timer channel.	
*/
#define GPT_START_MTU2A(_ch) \
		do { \
				if (_ch < GPT_INTERNAL_CHANNEL_MTU12) {\
					EE_HWREG8(HW_TSTR_BASE_ADDR) |= \
						0x1 << (_ch - GPT_INTERNAL_CHANNEL_MTU0);\
				} else if (_ch == GPT_INTERNAL_CHANNEL_MTU12) {\
					EE_HWREG8(HW_TSTR_BASE_ADDR) |= 0x06;\
				} else if(_ch < GPT_INTERNAL_CHANNEL_MTU5U) {\
					EE_HWREG8(HW_TSTR_BASE_ADDR) |= 0x40 << (_ch & 0x1);\
				} else  {\
					EE_HWREG8(HW_TSTR5_ADDR) |= 0x1 << (0x2 - (_ch & 0x7));\
				}\
			} while (0)

/** @brief	Stop the timer of MTU2A module.
*	@param	_ch Timer channel.	
*/
#define GPT_STOP_MTU2A(_ch) \
		do { \
				if (_ch < GPT_INTERNAL_CHANNEL_MTU12) {\
					EE_HWREG8(HW_TSTR_BASE_ADDR) &= \
						~(0x1 << (_ch - GPT_INTERNAL_CHANNEL_MTU0));\
				} else if (_ch == GPT_INTERNAL_CHANNEL_MTU12) {\
					EE_HWREG8(HW_TSTR_BASE_ADDR) &= 0xF9;\
				} else if(_ch < GPT_INTERNAL_CHANNEL_MTU5U) {\
					EE_HWREG8(HW_TSTR_BASE_ADDR) &= ~(0x40 << (_ch & 0x1));\
				} else  {\
					EE_HWREG8(HW_TSTR5_ADDR) |= ~(0x1 << (0x2 - (_ch & 0x7)));\
				}\
			} while (0)


/** @brief	Set TCNT register of MTU2Ax.
 *	@param	_ch Timer channel.
 */
#define GPT_SET_MTU2A_TCNT(_ch, _val) \
		do { \
				if (_ch < GPT_INTERNAL_CHANNEL_MTU12) {\
					EE_HWREG16((uint32)HW_MTU0_TCNT_ADDR + \
						(0x180 & ( 0x40 << (_ch - GPT_INTERNAL_CHANNEL_MTU0))))\
						= (uint16) (_val);\
				} else if (_ch == GPT_INTERNAL_CHANNEL_MTU12) {\
					EE_HWREG16(GPT_INTERNAL_CHANNEL_MTU1) = \
					(uint16) (_val >> 16);\
					EE_HWREG16(GPT_INTERNAL_CHANNEL_MTU2) = (uint16) (_val);\
				} else if(_ch < GPT_INTERNAL_CHANNEL_MTU5U) {\
					EE_HWREG16((uint32)HW_MTU3_TCNT_ADDR | \
						(0x2 & ( 0x1 << (_ch - GPT_INTERNAL_CHANNEL_MTU3))))\
						= (uint16) (_val);\
				} else  {\
					EE_HWREG16((uint32)HW_MTU5U_TCNT_ADDR + \
						((_ch - GPT_INTERNAL_CHANNEL_MTU5U) << 0x4)) = \
						(uint16) (_val);\
				}\
			} while (0)
				
				

/** @brief	Clear TCNT register of MTU2Ax.
 *	@param	_ch Timer channel.
 */
#define GPT_CLEAR_MTU2A_TCNT(_ch) GPT_SET_MTU2A_TCNT(_ch, 0)

/** @brief	Is MTUx (0 <= x <= 2) running?
 *	@param	_ch Timer channel.
 */
#define GPT_MTU0_2_IS_RUNNING(_ch) \
		( EE_HWREG8(HW_TSTR_BASE_ADDR) & \
				(0x1 << (_ch - GPT_INTERNAL_CHANNEL_MTU0)) )

/** @brief	Is MTUx (12 <= x <= 4) running?
 *	@param	_ch Timer channel.
 */
#define GPT_MTU12_4_IS_RUNNING(_ch)\
	( EE_HWREG8(HW_TSTR_BASE_ADDR) & (0x40 << (_ch & 0x1)) )

/** @brief	Is MTU5x running?
*	@param	_ch Timer channel.
*/
#define GPT_MTU5_IS_RUNNING(_ch) \
		(EE_HWREG8(HW_TSTR5_ADDR) & (0x1 << (0x2 - (_ch & 0x7))) )

/** @brief Get TCR register of module MTU2A.
 *	@param ch_id Timer Channel Identifier.
 *	@return  Value of Timer Control Regiater (TCR).
 */
__INLINE__ uint8 __ALWAYS_INLINE__	Gpt_get_mtu2a_tcr(Gpt_ChannelType _ch)
{
		if (_ch < GPT_INTERNAL_CHANNEL_MTU3) {
			return GPT_GET_MTU2A_REG8(GPT_GET_MTU0_2_TCR_ADDR(_ch));
		} else if (_ch < GPT_INTERNAL_CHANNEL_MTU5U) {
			return GPT_GET_MTU2A_REG8(GPT_GET_MTU3_4_TCR_ADDR(_ch));
		} else {
			return GPT_GET_MTU2A_REG8(GPT_GET_MTU5_TCR_ADDR(_ch));
		}
	
}

 /** @brief Set TCR register of module MTU2A.
  *	 @param _ch Timer Channel Identifier.
  *	 @param _val Value of Timer Control Regiater (TCR).
  */
 __INLINE__ void __ALWAYS_INLINE__	Gpt_set_mtu2a_tcr(Gpt_ChannelType _ch, 
		 uint8 _val)
 {
 		if (_ch < GPT_INTERNAL_CHANNEL_MTU3) {
 			GPT_SET_REG8(GPT_GET_MTU0_2_TCR_ADDR(_ch), _val);
 		} else if (_ch < GPT_INTERNAL_CHANNEL_MTU5U) {
 			GPT_SET_REG8(GPT_GET_MTU3_4_TCR_ADDR(_ch), _val);
 		} else {
 			GPT_SET_REG8(GPT_GET_MTU5_TCR_ADDR(_ch), _val);
 		}
 	
 }

 /** @brief Set TMDR register of module MTU2A.
  *	 @param _ch Timer Channel Identifier.
  *	 @param _val Value of Timer Control Regiater (TMDR).
  */
 __INLINE__ void __ALWAYS_INLINE__	Gpt_set_mtu2a_tmdr(Gpt_ChannelType _ch, 
		 uint8 _val)
 {
 		if (_ch < GPT_INTERNAL_CHANNEL_MTU3) {
 			GPT_SET_REG8(GPT_GET_MTU0_2_TMDR_ADDR(_ch), _val);
 		} else if (_ch < GPT_INTERNAL_CHANNEL_MTU5U) {
 			GPT_SET_REG8(GPT_GET_MTU3_4_TMDR_ADDR(_ch), _val);
 		} 
 }
 
/** @brief Set Timer General Register A of Module MTU2A.
 *	@param ch_id Timer Channel Identifier.
 *	@param _val register value.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu2a_set_tgra(Gpt_ChannelType _ch, 
		uint16 _val)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		GPT_SET_REG16(HW_MTU0_TGRA_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU1:
		GPT_SET_REG16(HW_MTU1_TGRA_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU2:
		GPT_SET_REG16(HW_MTU2_TGRA_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		GPT_SET_REG16(HW_MTU3_TGRA_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		GPT_SET_REG16(HW_MTU2_TGRA_ADDR, _val);
		GPT_SET_REG16(HW_MTU1_TGRA_ADDR, _val >> 16);
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		GPT_SET_REG16(HW_MTU4_TGRA_ADDR, _val);
		break;
	}
}

/** @brief Set Timer General Register B of Module MTU2A.
 *	@param ch_id Timer Channel Identifier.
 *	@param _val register value.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu2a_set_tgrb(Gpt_ChannelType _ch, 
		uint16 _val)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		GPT_SET_REG16(HW_MTU0_TGRB_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU1:
		GPT_SET_REG16(HW_MTU1_TGRB_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU2:
		GPT_SET_REG16(HW_MTU2_TGRB_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		GPT_SET_REG16(HW_MTU3_TGRB_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		GPT_SET_REG16(HW_MTU2_TGRB_ADDR, _val);
		GPT_SET_REG16(HW_MTU1_TGRB_ADDR, _val >> 16);
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		GPT_SET_REG16(HW_MTU4_TGRB_ADDR, _val);
		break;
	}
}

/** @brief Set Timer General Register C of Module MTU2A.
 *	@param ch_id Timer Channel Identifier.
 *	@param _val register value.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu2a_set_tgrc(Gpt_ChannelType _ch, 
		uint16 _val)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		GPT_SET_REG16(HW_MTU0_TGRC_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		GPT_SET_REG16(HW_MTU3_TGRC_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		GPT_SET_REG16(HW_MTU4_TGRC_ADDR, _val);
		break;
	}
}


/** @brief Set Timer General Register D of Module MTU2A.
 *	@param ch_id Timer Channel Identifier.
 *	@param _val register value.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu2a_set_tgrd(Gpt_ChannelType _ch, 
		uint16 _val)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		GPT_SET_REG16(HW_MTU0_TGRD_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		GPT_SET_REG16(HW_MTU3_TGRD_ADDR, _val);
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		GPT_SET_REG16(HW_MTU4_TGRD_ADDR, _val);
		break;
	}
}

/** @brief Get Timer General Register A of Module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@return  TGRA value of channel _ch.
 */
__INLINE__ uint32 __ALWAYS_INLINE__ Gpt_mtu2a_get_tgra(Gpt_ChannelType _ch)
{
	
	if (_ch == GPT_INTERNAL_CHANNEL_MTU0)
		return GPT_GET_REG16(HW_MTU0_TGRA_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU1)
		return GPT_GET_REG16(HW_MTU1_TGRA_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU2)
		return GPT_GET_REG16(HW_MTU2_TGRA_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU3)
		return GPT_GET_REG16(HW_MTU3_TGRA_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU12)
		return (GPT_GET_REG16(HW_MTU2_TGRA_ADDR) | 
				(GPT_GET_REG16(HW_MTU1_TGRA_ADDR) >> 16));
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU4)
		return GPT_GET_REG16(HW_MTU4_TGRA_ADDR);
	
	return 0;
}

/** @brief Get Timer General Register B of Module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@return  GRB value of channel _ch.
 */
__INLINE__ uint32 __ALWAYS_INLINE__ Gpt_mtu2a_get_tgrb(Gpt_ChannelType _ch)
{
	
	if (_ch == GPT_INTERNAL_CHANNEL_MTU0)
		return GPT_GET_REG16(HW_MTU0_TGRB_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU1)
		return GPT_GET_REG16(HW_MTU1_TGRB_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU2)
		return GPT_GET_REG16(HW_MTU2_TGRB_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU3)
		return GPT_GET_REG16(HW_MTU3_TGRB_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU12)
		return (GPT_GET_REG16(HW_MTU2_TGRB_ADDR) | 
				(GPT_GET_REG16(HW_MTU1_TGRB_ADDR) >> 16));
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU4)
		return GPT_GET_REG16(HW_MTU4_TGRB_ADDR);
	
	return 0;
}

/** @brief Get Timer General Register C of Module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@return TGRC value of channel _ch.
 */
__INLINE__ uint16 __ALWAYS_INLINE__ Gpt_mtu2a_get_tgrc(Gpt_ChannelType _ch)
{
	if (_ch == GPT_INTERNAL_CHANNEL_MTU0)
		return GPT_GET_REG16(HW_MTU0_TGRC_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU3)
		return GPT_GET_REG16(HW_MTU3_TGRC_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU4)
		return GPT_GET_REG16(HW_MTU4_TGRC_ADDR);
	
	return 0;
}


/** @brief Get Timer General Register D of Module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@return TGRD value of channel _ch.
 */
__INLINE__ uint16 __ALWAYS_INLINE__ Gpt_mtu2a_get_tgrd(Gpt_ChannelType _ch)
{
	if (_ch == GPT_INTERNAL_CHANNEL_MTU0)
		return GPT_GET_REG16(HW_MTU0_TGRD_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU3)
		return GPT_GET_REG16(HW_MTU3_TGRD_ADDR);
	else if (_ch == GPT_INTERNAL_CHANNEL_MTU4)
		return GPT_GET_REG16(HW_MTU4_TGRD_ADDR);
	
	return 0;
}

/** @brief Get Timer General Register value of Module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@return Register value.
 */
__INLINE__ uint32 Gpt_get_mtu2a_tgr(Gpt_ChannelType _ch)
{
	uint32 _tcr = Gpt_get_mtu2a_tcr(_ch);
	
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
	case GPT_INTERNAL_CHANNEL_MTU1:
	case GPT_INTERNAL_CHANNEL_MTU2:
	case GPT_INTERNAL_CHANNEL_MTU3:
	case GPT_INTERNAL_CHANNEL_MTU4:
		if ((_tcr & GPT_MTU2A_CMP_A_MASK) == GPT_MTU2A_CMP_A_MASK ) {
			_tcr = Gpt_mtu2a_get_tgra(_ch);
		} else if ((_tcr & GPT_MTU2A_CMP_B_MASK) == GPT_MTU2A_CMP_B_MASK) {
			_tcr = Gpt_mtu2a_get_tgrb(_ch);
		}  else if ((_tcr & GPT_MTU2A_CMP_C_MASK) == GPT_MTU2A_CMP_C_MASK) {
			_tcr = Gpt_mtu2a_get_tgrc(_ch);
		}  else if ((_tcr & GPT_MTU2A_CMP_D_MASK) == GPT_MTU2A_CMP_D_MASK) {
			_tcr = Gpt_mtu2a_get_tgrd(_ch);
		}
		break;
	case GPT_INTERNAL_CHANNEL_MTU5U:
		_tcr = GPT_GET_REG16(HW_MTU5_TGRU_ADDR);
		break;
	case GPT_INTERNAL_CHANNEL_MTU5V:
		_tcr = GPT_GET_REG16(HW_MTU5_TGRV_ADDR);
		break;
	case GPT_INTERNAL_CHANNEL_MTU5W:
		_tcr = GPT_GET_REG16(HW_MTU5_TGRW_ADDR);
		break;
	default:
		_tcr = 0;
		break;
	}
	
	return _tcr;
}

/** @brief Set compare match values for MTU0 to MTU4 channels of module MTU2A.
 *	@param ch_id Timer Channel Identifier.
 *	@param _val register value.
 *	@param _tcr vlaue set on TCR reg..
 *	@return  Status Mask of a Hardware Timer Module.
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_mtu0_4_set_cmp(Gpt_ChannelType _ch, 
		uint16 _val, uint8 _tcr)
{
	if ((_tcr & GPT_MTU2A_CMP_A_MASK) == GPT_MTU2A_CMP_A_MASK) {
		Gpt_mtu2a_set_tgra(_ch, _val);
	} else if ((_tcr & GPT_MTU2A_CMP_B_MASK) == GPT_MTU2A_CMP_B_MASK) {
		Gpt_mtu2a_set_tgrb(_ch, _val);
	}  else if ((_tcr & GPT_MTU2A_CMP_C_MASK) == GPT_MTU2A_CMP_C_MASK) {
		Gpt_mtu2a_set_tgrc(_ch, _val);
	}  else if ((_tcr & GPT_MTU2A_CMP_D_MASK) == GPT_MTU2A_CMP_D_MASK) {
		Gpt_mtu2a_set_tgrd(_ch, _val);
	}
	
}


/** @brief Set compare match values for MTU5x channels of module MTU2A.
 *	@param ch_id Timer Channel Identifier.
 *	@param _val register value.
 *	@return  Status Mask of a Hardware Timer Module.
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_mtu5_set_cmp(Gpt_ChannelType _ch, 
		uint16 _val)
{
	if (_ch == GPT_INTERNAL_CHANNEL_MTU5U) {
		GPT_SET_REG16(HW_MTU5_TGRU_ADDR, _val);
	} else if (_ch == GPT_INTERNAL_CHANNEL_MTU5V) {
		GPT_SET_REG16(HW_MTU5_TGRV_ADDR, _val);
	}  else if (_ch ==GPT_INTERNAL_CHANNEL_MTU5W) {
		GPT_SET_REG16(HW_MTU5_TGRW_ADDR, _val);
	}
}
/*TODO: MTU0 has also Interrupt compare/match channel E, F. We should support
 * them.
 */		
/** @brief Enable Interrupt of compare/match A/B/C/D of Module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@param _b_pos Position of the interrupt bit.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu2a_int_en(Gpt_ChannelType _ch, 
		uint8 _b_pos)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		GPT_SET_REG8(HW_MTU0_TIER_ADDR, (0x1 << _b_pos));
		break;
	case GPT_INTERNAL_CHANNEL_MTU1:
		GPT_SET_REG8(HW_MTU1_TIER_ADDR, (0x1 << _b_pos));
		break;
	case GPT_INTERNAL_CHANNEL_MTU2:
		GPT_SET_REG8(HW_MTU2_TIER_ADDR, (0x1 << _b_pos));
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		GPT_SET_REG8(HW_MTU3_TIER_ADDR, (0x1 << _b_pos));
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		/*TODO*/
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		GPT_SET_REG8(HW_MTU4_TIER_ADDR, (0x1 << _b_pos));
		break;
	}
}

/*TODO: MTU0 has also Interrupt compare/match channel E, F. We should support
 * them.
 */	
/** @brief Disable Interrupt of compare/match A/B/C/D of Module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@param _b_pos Position of the interrupt bit.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu2a_int_dis(Gpt_ChannelType _ch, 
		uint8 _b_pos)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		GPT_SET_REG8(HW_MTU0_TIER_ADDR,
				GPT_GET_REG8(HW_MTU0_TIER_ADDR) & ~(0x1 << _b_pos));
		GPT_DIS_ICU_IER(HW_ICU_IER_MTU0_TGIA, HW_ICU_MTU0_IER_TGIA_MASK | 
				HW_ICU_MTU0_IER_TGIB_MASK | HW_ICU_MTU0_IER_TGIC_MASK | 
				HW_ICU_MTU0_IER_TGID_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU1:
		GPT_SET_REG8(HW_MTU1_TIER_ADDR, 
				GPT_GET_REG8(HW_MTU1_TIER_ADDR) & ~(0x1 << _b_pos));
		GPT_DIS_ICU_IER(HW_ICU_IER_MTU1_TGIA, HW_ICU_MTU1_IER_TGIA_MASK | 
				HW_ICU_MTU1_IER_TGIB_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU2:
		GPT_SET_REG8(HW_MTU2_TIER_ADDR, 
				GPT_GET_REG8(HW_MTU2_TIER_ADDR) & ~(0x1 << _b_pos));
		GPT_DIS_ICU_IER(HW_ICU_IER_MTU2_TGIA, HW_ICU_MTU2_IER_TGIA_MASK | 
				HW_ICU_MTU2_IER_TGIB_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		GPT_SET_REG8(HW_MTU3_TIER_ADDR, 
				GPT_GET_REG8(HW_MTU3_TIER_ADDR) & ~(0x1 << _b_pos));
		GPT_DIS_ICU_IER(HW_ICU_IER_MTU3_TGIA, HW_ICU_MTU3_IER_TGIA_MASK | 
				HW_ICU_MTU3_IER_TGIB_MASK | HW_ICU_MTU3_IER_TGIC_MASK | 
				HW_ICU_MTU3_IER_TGID_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		/*TODO*/
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		GPT_SET_REG8(HW_MTU4_TIER_ADDR, 
				GPT_GET_REG8(HW_MTU4_TIER_ADDR) & ~(0x1 << _b_pos));
		GPT_DIS_ICU_IER(HW_ICU_IER_MTU4_TGIA, HW_ICU_MTU4_IER_TGIA_MASK | 
				HW_ICU_MTU4_IER_TGIB_MASK | HW_ICU_MTU4_IER_TGIC_MASK | 
				HW_ICU_MTU4_IER_TGID_MASK);
		break;
	}
}

/** @brief Enable ICU for MTUx channels of module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@param _isr ISR to enable.
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_mtu2a_icu_en(Gpt_ChannelType _ch,
		uint8 _isr)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		GPT_EN_ICU_IER(HW_ICU_IER_MTU0_TGIA, _isr);
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU0_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU1:
		GPT_EN_ICU_IER(HW_ICU_IER_MTU1_TGIA, _isr);
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU1_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU2:
		GPT_EN_ICU_IER(HW_ICU_IER_MTU2_TGIA, _isr);
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU2_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		GPT_EN_ICU_IER(HW_ICU_IER_MTU3_TGIA, _isr);
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU3_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		/*TODO*/
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		if ((_isr != HW_ICU_MTU4_IER_TGIC_MASK) && 
				(_isr != HW_ICU_MTU4_IER_TGID_MASK)) { 
			GPT_EN_ICU_IER(HW_ICU_IER_MTU4_TGIA, _isr);
		} else {
			GPT_EN_ICU_IER(HW_ICU_IER_MTU4_TGIC, _isr);	
		}
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU4_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	}
}

/*TODO: MTU0 has also Interrupt compare/match channel E, F. We should support
 * them.
 */	
/** @brief Enable interrupt for MTU0 to MTU4 channels of module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@param _tcr value set on TCR reg..
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_mtu0_4_int_en(Gpt_ChannelType _ch,
		uint8 _tcr)
{
	if ((_tcr & GPT_MTU2A_CMP_A_MASK) == GPT_MTU2A_CMP_A_MASK) {
		Gpt_mtu2a_int_en(_ch, GPT_MTU2A_TGIEA_POS);
		Gpt_mtu2a_icu_en(_ch, HW_ICU_MTU0_IER_TGIA_MASK);
	} else if ((_tcr & GPT_MTU2A_CMP_B_MASK) == GPT_MTU2A_CMP_B_MASK) {
		Gpt_mtu2a_int_en(_ch, GPT_MTU2A_TGIEB_POS);
		Gpt_mtu2a_icu_en(_ch, HW_ICU_MTU0_IER_TGIB_MASK);
	}  else if ((_tcr & GPT_MTU2A_CMP_C_MASK) == GPT_MTU2A_CMP_C_MASK) {
		Gpt_mtu2a_int_en(_ch, GPT_MTU2A_TGIEC_POS);
		Gpt_mtu2a_icu_en(_ch, HW_ICU_MTU0_IER_TGIC_MASK);
	}  else if ((_tcr & GPT_MTU2A_CMP_D_MASK) == GPT_MTU2A_CMP_D_MASK) {
		Gpt_mtu2a_int_en(_ch, GPT_MTU2A_TGIED_POS);
		Gpt_mtu2a_icu_en(_ch, HW_ICU_MTU0_IER_TGID_MASK);
	}
	
}

/*TODO: MTU0 has also Interrupt compare/match channel E, F. We should support
 * them.
 */	
/** @brief Disable interrupt for MTU0 to MTU4 channels of module MTU2A.
 *	@param _ch Timer Channel Identifier.
 *	@param _tcr value set on TCR reg..
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_mtu0_4_int_dis(Gpt_ChannelType _ch,
		uint8 _tcr)
{
	if ((_tcr & GPT_MTU2A_CMP_A_MASK) == GPT_MTU2A_CMP_A_MASK) {
		Gpt_mtu2a_int_dis(_ch, GPT_MTU2A_TGIEA_POS);
	} else if ((_tcr & GPT_MTU2A_CMP_B_MASK) == GPT_MTU2A_CMP_B_MASK) {
		Gpt_mtu2a_int_dis(_ch, GPT_MTU2A_TGIEB_POS);
	}  else if ((_tcr & GPT_MTU2A_CMP_C_MASK) == GPT_MTU2A_CMP_C_MASK) {
		Gpt_mtu2a_int_dis(_ch, GPT_MTU2A_TGIEC_POS);
	}  else if ((_tcr & GPT_MTU2A_CMP_D_MASK) ==GPT_MTU2A_CMP_D_MASK) {
		Gpt_mtu2a_int_dis(_ch, GPT_MTU2A_TGIED_POS);
	}
	
}

/** @brief Enable interrupt for MTU5x channels of MTU2A.
 *	@param _ch Timer Channel Identifier.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu5_int_en(Gpt_ChannelType _ch)
{
	GPT_SET_REG8(HW_MTU5_TIER_ADDR, (0x1 << (GPT_INTERNAL_CHANNEL_MTU5W - _ch)));

}

/** @brief Disable interrupt for MTU5x channels of MTU2A.
 *	@param _ch Timer Channel Identifier.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_mtu5_int_dis(Gpt_ChannelType _ch)
{
	GPT_SET_REG8(HW_MTU5_TIER_ADDR, GPT_GET_REG8(HW_MTU5_TIER_ADDR) & 
			~(0x1 << (GPT_INTERNAL_CHANNEL_MTU5W - _ch)));
	GPT_DIS_ICU_IER(HW_ICU_IER_MTU5_TGI, HW_ICU_MTU5_IER_TGIU_MASK | 
			HW_ICU_MTU5_IER_TGIV_MASK | HW_ICU_MTU5_IER_TGIW_MASK);
}

/** @brief Return Module stop/star bit from Module Stop Control Register A 
 *	(MSTPCRA).
 *	@param ch_id Timer Channel Identifier.
 *	@return  Status Mask of a Hardware Timer Module.
 */
__INLINE__ uint32 __ALWAYS_INLINE__  Gpt_ch_2_mod_stat(Gpt_ChannelType ch_id)
{
	if (ch_id == GPT_INTERNAL_CHANNEL_TMR0 || 
			ch_id == GPT_INTERNAL_CHANNEL_TMR1 || 
			ch_id == GPT_INTERNAL_CHANNEL_TMR01) {
		return (~EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) & GPT_HW_TMR_STOP_TMR01);
	}
	
	if (ch_id == GPT_INTERNAL_CHANNEL_TMR2 || 
			ch_id == GPT_INTERNAL_CHANNEL_TMR3 || 
			ch_id == GPT_INTERNAL_CHANNEL_TMR23) {
		return (~EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) & GPT_HW_TMR_STOP_TMR23);
	}
	
	if (ch_id == GPT_INTERNAL_CHANNEL_CMT0 || 
			ch_id == GPT_INTERNAL_CHANNEL_CMT1) {
		return (~EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) & GPT_HW_TMR_STOP_CMT01);
	}
	if (ch_id == GPT_INTERNAL_CHANNEL_CMT2 || 
			ch_id == GPT_INTERNAL_CHANNEL_CMT3) {
		return (~EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) & GPT_HW_TMR_STOP_CMT23);
	}
/*	If we get here, then:
 *  ch_id >= GPT_INTERNAL_CHANNEL_MTU0 <= ch_id <= GPT_INTERNAL_CHANNEL_MTU5W
 */ 
	return (~EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) & GPT_HW_TMR_STOP_MTU2A);

}

/** @brief	Clear stop bit in Module Stop Control Register A (MSTPCRA).
 *	@param  _ch Timer Channel Identifier.
 *  
 */
__INLINE__ void __ALWAYS_INLINE__  Gpt_EnableChannel(Gpt_ChannelType _ch)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of clock/pll related registers. 
	 */
	SYSTEM.PRCR.WORD = 0xA503;
	
	if (_ch >= GPT_INTERNAL_CHANNEL_MTU0 && _ch <= GPT_INTERNAL_CHANNEL_MTU5W) {
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) &= GPT_HW_TMR_NSTOP_MTU2A;
		return;
	}
	
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_TMR0:
	case GPT_INTERNAL_CHANNEL_TMR1:
	case GPT_INTERNAL_CHANNEL_TMR01:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) &= GPT_HW_TMR_NSTOP_TMR01;
		break;
	case GPT_INTERNAL_CHANNEL_TMR2:
	case GPT_INTERNAL_CHANNEL_TMR3:
	case GPT_INTERNAL_CHANNEL_TMR23:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) &= GPT_HW_TMR_NSTOP_TMR23;
		break;
	case GPT_INTERNAL_CHANNEL_CMT0:
	case GPT_INTERNAL_CHANNEL_CMT1:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) &= GPT_HW_TMR_NSTOP_CMT01;
		break;
	case GPT_INTERNAL_CHANNEL_CMT2:
	case GPT_INTERNAL_CHANNEL_CMT3:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) &= GPT_HW_TMR_NSTOP_CMT23;
		break;	
	}
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;

}

/** @brief	Set stop bit in Module Stop Control Register A (MSTPCRA).
 *	@param  _ch Timer Channel Identifier.
 *  
 */
__INLINE__ void __ALWAYS_INLINE__  Gpt_DisableChannel(Gpt_ChannelType _ch)
{
	/* 
	 * Write protect off. 
	 * This enables the writing of clock/pll related registers. 
	 */
	SYSTEM.PRCR.WORD = 0xA503;
	
	if (_ch >= GPT_INTERNAL_CHANNEL_MTU0 && _ch <= GPT_INTERNAL_CHANNEL_MTU5W) {
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) |= GPT_HW_TMR_STOP_MTU2A;
		
		return;
	}
	
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_TMR0:
	case GPT_INTERNAL_CHANNEL_TMR1:
	case GPT_INTERNAL_CHANNEL_TMR01:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) |= GPT_HW_TMR_STOP_TMR01;
		break;
	case GPT_INTERNAL_CHANNEL_TMR2:
	case GPT_INTERNAL_CHANNEL_TMR3:
	case GPT_INTERNAL_CHANNEL_TMR23:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) |= GPT_HW_TMR_STOP_TMR23;
		break;
	case GPT_INTERNAL_CHANNEL_CMT0:
	case GPT_INTERNAL_CHANNEL_CMT1:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) |= GPT_HW_TMR_STOP_CMT01;
		break;
	case GPT_INTERNAL_CHANNEL_CMT2:
	case GPT_INTERNAL_CHANNEL_CMT3:
		EE_HWREG(HW_SYSTEM_MSTPCRA_ADDR) |= GPT_HW_TMR_STOP_CMT23;
		break;	
	}
	
	/* Write protect on */
	SYSTEM.PRCR.WORD = 0xA500;
	
}

/** @brief	Stop the timer identified by ch_id.
 *	@param ch_id Timer Channel Identifier.
 */
__INLINE__ void __ALWAYS_INLINE__  Gpt_tmr_stop(Gpt_ChannelType ch_id)
{
	/* If ch_id is one of the TMR module channels, return because the TMR module
	 * has not start/stop timer register. 
	 */
	if (ch_id < GPT_INTERNAL_CHANNEL_CMT0)
		return;
	if (ch_id < GPT_INTERNAL_CHANNEL_MTU0) {
		GPT_STOP_CMT(ch_id);
	} else {
		GPT_STOP_MTU2A(ch_id);
	}
		
}


/** @brief	Configure and initialize TMR module.
 *	@param ConfigPtr Address of channel configuration structure.
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_tmr_init(
		const Gpt_ChannelConfigType *ConfigPtr) 
{
	if (ConfigPtr->GptChannelId == GPT_INTERNAL_CHANNEL_TMR01) {
		/*TODO*/
	} else if (ConfigPtr->GptChannelId == GPT_INTERNAL_CHANNEL_TMR23){
		/*TODO*/
	} else {
		/*Initialize clock and prescaler.*/
		GPT_SET_TMR_CLK(ConfigPtr->GptChannelId, 
				GPT_GET_PRES_CONF(ConfigPtr->GptChannelHWConfig));
		/* Set CCLR bits in TCR and disable all interrupts.*/
		GPT_SET_TMR_TCR(ConfigPtr->GptChannelId, 
				(ConfigPtr->GptChannelHWConfig >> GPT_TMR_CCLR_SH_MASK) &
					GPT_TMR_CCLR_MASK);
		/* Set Timer Reset Detection Condition bit (TCCR.TMRIS). 
		 * This is meaningful if "Cleared by the external reset input is 
		 * selected" by TCR.CCLR bits.
		 */
		GPT_SET_TMR_TCCR(ConfigPtr->GptChannelId, 
				 (GPT_GET_TMR_TCCR(ConfigPtr->GptChannelId) & 
						 GPT_TMR_TMRIS_DIS) | 
				GPT_GET_RESET_COND_BIT(ConfigPtr->GptChannelHWConfig));
	}
}


/** @brief	Configure and initialize CMT module.
 *	@param ConfigPtr Address of channel configuration structure.
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_cmt_init(
		const Gpt_ChannelConfigType *ConfigPtr) 
{
	/*GPT_SET_CMT_CLK(ConfigPtr->GptChannelId, 
					GPT_GET_PRES_CONF(ConfigPtr->GptChannelHWConfig));
					*/
	/* Set clock/prescaler bits in CMCR.
	 * Disable all interrupts.
	 */
	GPT_SET_CMT_CMCR(ConfigPtr->GptChannelId, 
			ConfigPtr->GptChannelHWConfig & GPT_CMT_CLK_MASK);
}

/** @brief	Enable TMR CMIx interrupt.
 *	@param _ch Channel id.
 *	@param f_cmia Interrupt type flag (0 -> CMIB, CMIA otherwise)
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_tmr_en_icu_int(Gpt_ChannelType _ch, 
		uint8 f_cmia)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_TMR0:
		if (f_cmia) {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR0_CMIA, HW_ICU_TMR0_IER_CMIA_MASK);
		} else {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR0_CMIB, HW_ICU_TMR0_IER_CMIB_MASK);
		}
		GPT_SET_ICU_IPR(HW_ICU_IPR_TMR0_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_TMR1:
		if (f_cmia) {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR1_CMIA, HW_ICU_TMR1_IER_CMIA_MASK);
		} else {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR1_CMIB, HW_ICU_TMR1_IER_CMIB_MASK);
		}
		GPT_SET_ICU_IPR(HW_ICU_IPR_TMR1_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_TMR2:
		if (f_cmia) {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR2_CMIA, HW_ICU_TMR2_IER_CMIA_MASK);
		} else {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR2_CMIB, HW_ICU_TMR2_IER_CMIB_MASK);
		}
		GPT_SET_ICU_IPR(HW_ICU_IPR_TMR2_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_TMR3:
		if (f_cmia) {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR3_CMIA, HW_ICU_TMR3_IER_CMIA_MASK);
		} else {
			GPT_EN_ICU_IER(HW_ICU_IER_TMR3_CMIB, HW_ICU_TMR3_IER_CMIB_MASK);
		}
		GPT_SET_ICU_IPR(HW_ICU_IPR_TMR3_REG, HW_IPR_PRI_LEVEL_1);
		break;
	}
	
}

/** @brief	Disable TMR CMIx interrupt.
 *	@param _ch Channel id.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_tmr_dis_icu_int(Gpt_ChannelType _ch)
{
	switch (_ch) {
	case GPT_INTERNAL_CHANNEL_TMR0:
		GPT_DIS_ICU_IER(HW_ICU_IER_TMR0_CMIA, HW_ICU_TMR0_IER_CMIA_MASK | 
				HW_ICU_TMR0_IER_CMIB_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_TMR1:
		GPT_DIS_ICU_IER(HW_ICU_IER_TMR1_CMIA, HW_ICU_TMR1_IER_CMIA_MASK | 
				HW_ICU_TMR1_IER_CMIB_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_TMR2:
		GPT_DIS_ICU_IER(HW_ICU_IER_TMR2_CMIA, HW_ICU_TMR2_IER_CMIA_MASK | 
				HW_ICU_TMR2_IER_CMIB_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_TMR3:
		GPT_DIS_ICU_IER(HW_ICU_IER_TMR3_CMIA, HW_ICU_TMR3_IER_CMIA_MASK | 
				HW_ICU_TMR3_IER_CMIB_MASK);
		break;
	}
	
}

/** @brief	Enable TMR interrupts to handle one-shot mode.
 *	@param ConfigPtr Address of channel configuration structure.
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_tmr_en_oneshot(
		const Gpt_ChannelConfigType *ConfigPtr) 
{
	if (ConfigPtr->GptChannelId == GPT_INTERNAL_CHANNEL_TMR01) {
		/*TODO*/
	} else if (ConfigPtr->GptChannelId == GPT_INTERNAL_CHANNEL_TMR23){
		/*TODO*/
	} else {
		if (((ConfigPtr->GptChannelHWConfig >> 2) & GPT_TMR_CMP_A_MASK) == 
				GPT_TMR_CMP_A_MASK) {
			Gpt_tmr_en_icu_int(ConfigPtr->GptChannelId, GTP_EN_TMR_CMIA);

		} else {
			Gpt_tmr_en_icu_int(ConfigPtr->GptChannelId, GTP_EN_TMR_CMIB);
		}
	}
}


/** @brief	Enable CMT interrupts to handle one-shot mode.
 *	@param _ch Channel id.
 */
__INLINE__ void __ALWAYS_INLINE__	Gpt_cmt_en_oneshot(Gpt_ChannelType _ch) 
{
	GPT_SET_CMT_CMIE(_ch);
	
	GPT_EN_ICU_IER(HW_ICU_IER_CMT_CMI, HW_ICU_CMT0_IER_CMI_MASK << 
			(_ch - GPT_INTERNAL_CHANNEL_CMT0));
	GPT_SET_ICU_IPR((uint32)HW_ICU_IPR_CMT0_REG + _ch - GPT_INTERNAL_CHANNEL_CMT0, 
			HW_IPR_PRI_LEVEL_1);
}


/** @brief	Enable Notification callback.
 *	@param _ch Timer Channel Identifier.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_timeout_int_en(Gpt_ChannelType _ch)
{
	if (_ch < GPT_INTERNAL_CHANNEL_TMR01) {
		if ((GPT_GET_TMR_TCR(_ch) & GPT_TMR_CMP_A_MASK) == GPT_TMR_CMP_A_MASK) {
			Gpt_tmr_en_icu_int(_ch, GTP_EN_TMR_CMIA);
		} else {
			Gpt_tmr_en_icu_int(_ch, GTP_EN_TMR_CMIB);
		}
	} else if (_ch < GPT_INTERNAL_CHANNEL_CMT0) {
		/*TODO*/
	} else if (_ch < GPT_INTERNAL_CHANNEL_MTU0) {
		GPT_SET_CMT_CMIE(_ch);
		GPT_EN_ICU_IER(HW_ICU_IER_CMT_CMI, HW_ICU_CMT0_IER_CMI_MASK << 
				(_ch - GPT_INTERNAL_CHANNEL_CMT0));
		GPT_SET_ICU_IPR((uint32)HW_ICU_IPR_CMT0_REG + 
				EE_HWREG8_ADDR(_ch - GPT_INTERNAL_CHANNEL_CMT0), 
				HW_IPR_PRI_LEVEL_1);
	} else if (_ch < GPT_INTERNAL_CHANNEL_MTU5U){
		Gpt_mtu0_4_int_en(_ch, Gpt_get_mtu2a_tcr(_ch));
	} else {
		Gpt_mtu5_int_en(_ch);
	}
}

/** @brief	Disable Notification callback.
 *	@param _ch Timer Channel Identifier.
 */
__INLINE__ void __ALWAYS_INLINE__ Gpt_timeout_int_dis(Gpt_ChannelType _ch)
{
	if (_ch < GPT_INTERNAL_CHANNEL_TMR01) {
		GPT_CLEAR_TMR_CMIEA(_ch);
		GPT_CLEAR_TMR_CMIEB(_ch);
		Gpt_tmr_dis_icu_int(_ch);
	} else if (_ch < GPT_INTERNAL_CHANNEL_CMT0) {
		/*TODO*/
	} else if (_ch < GPT_INTERNAL_CHANNEL_MTU0) {
		GPT_CLEAR_CMT_CMIE(_ch);
		GPT_DIS_ICU_IER(HW_ICU_IER_CMT_CMI, HW_ICU_CMT0_IER_CMI_MASK | 
				HW_ICU_CMT1_IER_CMI_MASK | HW_ICU_CMT2_IER_CMI_MASK | 
				HW_ICU_CMT3_IER_CMI_MASK);
	} else if (_ch < GPT_INTERNAL_CHANNEL_MTU5U){
		Gpt_mtu0_4_int_dis(_ch, Gpt_get_mtu2a_tcr(_ch));
	} else {
		Gpt_mtu5_int_dis(_ch);
	}
}

/** @brief	Check if the timer is running.
 *	@param _ch Timer Channel Identifier.
 */
__INLINE__ uint8 __ALWAYS_INLINE__ Gpt_is_running(Gpt_ChannelType _ch)
{
	
	/*If the timer is on sleep mode return NOT RUNNING */
	if (!Gpt_ch_2_mod_stat(_ch))
		return GPT_TIMER_NOT_RUNNING;
	
	/* If TMR0 <= _ch <= TMR23, there is not start/stop bit, so the timer is 
	 * running for sure.
	 */
	if (_ch < GPT_INTERNAL_CHANNEL_CMT0 && GPT_GET_FLAG(start_flag, _ch)) {
		
		return GPT_TIMER_RUNNING;
	}
			
	/* If CMT0 <= _ch <= CMT3 */
	if (_ch < GPT_INTERNAL_CHANNEL_MTU0) {
		if (GPT_CMT_IS_RUNNING(_ch))
			return GPT_TIMER_RUNNING;
		else 
			return GPT_TIMER_NOT_RUNNING;
	}
	/* If MTU0 <= _ch <= MTU2 */
	if (_ch < GPT_INTERNAL_CHANNEL_MTU12) {
		if (GPT_MTU0_2_IS_RUNNING(_ch))
			return GPT_TIMER_RUNNING;
		else 
			return GPT_TIMER_NOT_RUNNING;
	}
	/* If MTU12 <= _ch <= MTU4 */
	if (_ch < GPT_INTERNAL_CHANNEL_MTU5U) {
		if (GPT_MTU12_4_IS_RUNNING(_ch))
			return GPT_TIMER_RUNNING;
		else 
			return GPT_TIMER_NOT_RUNNING;
	}
	
	/* We are sure that  MTU5U <= _ch <= MTU5W. */ 
	if (GPT_MTU5_IS_RUNNING(_ch)) {
		return GPT_TIMER_RUNNING;
	}
	
	return GPT_TIMER_NOT_RUNNING;
	
}

/** @brief	Get TCNT register value of TMR module .
 *	@param _ch Timer Channel Identifier.
 *	@return Counter value of channel _ch.
 */
__INLINE__ uint16 __ALWAYS_INLINE__ Gpt_get_tmr_tcnt(Gpt_ChannelType _ch)
{
	if (_ch == GPT_INTERNAL_CHANNEL_TMR01)
		return EE_HWREG16(HW_TMR01_TCNT_ADDR_BASE);
	if (_ch == GPT_INTERNAL_CHANNEL_TMR23) 
		return EE_HWREG16(HW_TMR23_TCNT_ADDR_BASE);
	
	return	EE_HWREG8(GPT_GET_TMR_TCNT_ADDR(_ch));
}

/** @brief	Get TCNT register value of MTU2A module .
 *	@param _ch Timer Channel Identifier.
 */
__INLINE__ uint32 __ALWAYS_INLINE__ Gpt_get_mtu2a_tcnt(Gpt_ChannelType _ch)
{
	if (_ch < GPT_INTERNAL_CHANNEL_MTU12)
		return EE_HWREG16((uint32) (HW_MTU0_TCNT_ADDR) +
				(0x180 & ( 0x40 << (_ch - GPT_INTERNAL_CHANNEL_MTU0))));
	if (_ch == GPT_INTERNAL_CHANNEL_MTU12)
		return ((uint32)(EE_HWREG16(GPT_INTERNAL_CHANNEL_MTU2)) | 
				(uint32)(EE_HWREG16(GPT_INTERNAL_CHANNEL_MTU1)<< 16));
	if (_ch < GPT_INTERNAL_CHANNEL_MTU5U)
		return EE_HWREG16(((uint32)(HW_MTU3_TCNT_ADDR) | 0x2 & 
				( 0x1 << (_ch - GPT_INTERNAL_CHANNEL_MTU3))));
				
	return 	EE_HWREG16((uint32)(HW_MTU5U_TCNT_ADDR) + 
			((_ch - GPT_INTERNAL_CHANNEL_MTU5U) << 0x4));	
}

#endif
	