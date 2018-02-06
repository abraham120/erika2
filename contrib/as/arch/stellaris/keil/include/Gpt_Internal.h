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
 *  @author	Giuseppe Serano
 *  @date	2012
 */

/* GPT Hardware Unit Mask */
#define	HW_CH_UNIT_MASK		0x00000001	/* Mask			*/
#define	HW_CH_UNIT_MASK_SZ_S	0x00000001	/* Mask Size Shift Bits */

/* GPT Hardware Module Mask */
#define	HW_CH_MOD_MASK		0x0000003E	/* Mask */

/* GPT Hardware Base Address */
#define	HW_BASE_ADDR		&TIMER0_CFG_R

/* Hardware Abstraction */
#include "Hardware.h"

/* Hardware Timer Mask */
#define	GPT_HW_TMR_MASK		0x03		/* Mask			*/
#define	GPT_HW_TMR_MASK_SZ_S	0x01		/* Mask Size Shift Bits */

#define	GPT_HW_TMR_WIDE_MASK	0x0000000F	/* Wide Timer Mask */

#define	GPT_HW_TMR_JOIN_MASK	0x00000040	/* Timer Join Mask */

/* Hardware Timer Module Status */
#define	GPT_HW_TMR_STAT_ALL_OFF		0x00
#define	GPT_HW_TMR_STAT_TMRA_ON		0x01
#define	GPT_HW_TMR_STAT_TMRB_ON		0x02
#define	GPT_HW_TMR_STAT_ALL_ON		0x03

/*
 * Channel to Mask Shift Bits.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	 Mask Shift Bits of a Hardware Timer Module.
 *
 * This macro function returns the number mask shift bits of a hardware timer
 * module referred to numeric id of a channel.
 *
 * Note:	Requires HW_CH_MOD_MASK, GPT_HW_TMR_WIDE_MASK and
 * 		HW_CH_UNIT_MASK_SZ_S macros.
 */
#define	GTP_CH_2_MASK_S(_ch)		(uint32) ( \
  (uint32)(HW_CH_2_MOD(_ch) & (uint32)GPT_HW_TMR_WIDE_MASK) << \
  (uint32)GPT_HW_TMR_MASK_SZ_S \
)

/*
 * Channel to Module Status Mask.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Status Mask of a Hardware Timer Module.
 *
 * This macro function returns the status mask of a hardware timer module
 * referred to numeric id of a channel.
 *
 * Note:	Requires HW_CH_MOD_MASK and HW_CH_UNIT_MASK_SZ_S macros.
 */
#define	GPT_CH_2_MOD_STAT_MASK(_ch)	(uint32)( \
  (uint32)GPT_HW_TMR_STAT_ALL_ON << GTP_CH_2_MASK_S(_ch) \
)

/*
 * Channel to Unit Status Mask.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Status Mask of a Hardware Timer Unit.
 *
 * This macro function returns the status mask of a hardware timer unit referred
 * to numeric id of a channel.
 *
 * Note:	Requires <tt>HW_CH_MOD_MASK</tt>, <tt>HW_CH_UNIT_MASK</tt> and
 * 		<tt>HW_CH_UNIT_MASK_SZ_S</tt> macros.
 */
#define	GPT_CH_2_UNIT_STAT_MASK(_ch)	(uint32)( \
  ( (uint32)GPT_HW_TMR_STAT_TMRA_ON << HW_CH_2_UNIT(_ch) ) << \
  GTP_CH_2_MASK_S(_ch) \
)

/* Hardware Timer Module Notifications */
#define	GPT_HW_TMR_NOTIF_ALL_OFF	0x00
#define	GPT_HW_TMR_NOTIF_TMRA_ON	0x01
#define	GPT_HW_TMR_NOTIF_TMRB_ON	0x02
#define	GPT_HW_TMR_NOTIF_ALL_ON		0x03

/*
 * Channel to Unit Notifications Mask.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Notifications Mask of a Hardware Timer Unit.
 *
 * This macro function returns the Notifications mask of a hardware timer unit
 * referred to numeric id of a channel.
 *
 * Note:	Requires <tt>HW_CH_MOD_MASK</tt>, <tt>HW_CH_UNIT_MASK</tt> and
 * 		<tt>HW_CH_UNIT_MASK_SZ_S</tt> macros.
 */
#define	GPT_CH_2_UNIT_NOTIF_MASK(_ch)	(uint32)( \
  ( (uint32)GPT_HW_TMR_NOTIF_TMRA_ON << HW_CH_2_UNIT(_ch) ) << \
  GTP_CH_2_MASK_S(_ch) \
)

/* GTP Wide Timer Not in Row Mask */
#define	GTP_TMR_WIDE_ROW_MASK	0x00000010

/* GTP Wide Timer Not in Row Channel Offset */
#define	GTP_TMR_WIDE_ROW_OFFSET	0x00000034

/*
 * Internal Cahnels Identifiers
 */ 
#define	GPT_INTERNAL_CHANNEL_0_A	0x00	/**< Channel 0 A */
#define	GPT_INTERNAL_CHANNEL_0_B	0x01	/**< Channel 0 B */
#define	GPT_INTERNAL_CHANNEL_1_A	0x02	/**< Channel 1 A */
#define	GPT_INTERNAL_CHANNEL_1_B	0x03	/**< Channel 1 B */
#define	GPT_INTERNAL_CHANNEL_2_A	0x04	/**< Channel 2 A */
#define	GPT_INTERNAL_CHANNEL_2 B	0x05	/**< Channel 2 B */
#define	GPT_INTERNAL_CHANNEL_3_A	0x06	/**< Channel 3 A */
#define	GPT_INTERNAL_CHANNEL_3_B	0x07	/**< Channel 3 B */
#define	GPT_INTERNAL_CHANNEL_4_A	0x08	/**< Channel 4 A */
#define	GPT_INTERNAL_CHANNEL_4_B	0x09	/**< Channel 4 B */
#define	GPT_INTERNAL_CHANNEL_5_A	0x0A	/**< Channel 5 A */
#define	GPT_INTERNAL_CHANNEL_5_B	0x0B	/**< Channel 5 B */

#define	GPT_INTERNAL_CHANNEL_W_0_A	0x0C	/**< Channel W 0 A */
#define	GPT_INTERNAL_CHANNEL_W_0_B	0x0D	/**< Channel W 0 B */
#define	GPT_INTERNAL_CHANNEL_W_1_A	0x0E	/**< Channel W 1 A */
#define	GPT_INTERNAL_CHANNEL_W_1_B	0x0F	/**< Channel W 1 B */
#define	GPT_INTERNAL_CHANNEL_W_2_A	0x38	/**< Channel W 2 A */
#define	GPT_INTERNAL_CHANNEL_W_2 B	0x39	/**< Channel W 2 B */
#define	GPT_INTERNAL_CHANNEL_W_3_A	0x3A	/**< Channel W 3 A */
#define	GPT_INTERNAL_CHANNEL_W_3_B	0x3B	/**< Channel W 3 B */
#define	GPT_INTERNAL_CHANNEL_W_4_A	0x3C	/**< Channel W 4 A */
#define	GPT_INTERNAL_CHANNEL_W_4_B	0x3D	/**< Channel W 4 B */
#define	GPT_INTERNAL_CHANNEL_W_5_A	0x3E	/**< Channel W 5 A */
#define	GPT_INTERNAL_CHANNEL_W_5_B	0x3F	/**< Channel W 5 B */

#define	GPT_INTERNAL_CHANNEL_J_0	0x40	/**< Channel J 0 */
#define	GPT_INTERNAL_CHANNEL_J_1	0x42	/**< Channel J 1 */
#define	GPT_INTERNAL_CHANNEL_J_2	0x44	/**< Channel J 2 */
#define	GPT_INTERNAL_CHANNEL_J_3	0x46	/**< Channel J 3 */
#define	GPT_INTERNAL_CHANNEL_J_4	0x48	/**< Channel J 4 */
#define	GPT_INTERNAL_CHANNEL_J_5	0x4A	/**< Channel J 5 */

#define	GPT_INTERNAL_CHANNEL_J_W_0	0x4C	/**< Channel W J 0 */
#define	GPT_INTERNAL_CHANNEL_J_W_1	0x4E	/**< Channel W J 1 */
#define	GPT_INTERNAL_CHANNEL_J_W_2	0x78	/**< Channel W J 2 */
#define	GPT_INTERNAL_CHANNEL_J_W_3	0x7A	/**< Channel W J 3 */
#define	GPT_INTERNAL_CHANNEL_J_W_4	0x7C	/**< Channel W J 4 */
#define	GPT_INTERNAL_CHANNEL_J_W_5	0x7E	/**< Channel W J 5 */


/*
 * Channel is Valid Test
 *
 * param	_ch	Numeric ID of a GPT channel. (Gpt_ChannelType)
 * return	TRUE:	Numeric ID od a GPT channel 
 * 		FALSE:	Invalid Channel
 *
 * This macro function returns if numeric id of a channel is valid or not.
 */
#define	GPT_CH_IS_VALID(_ch)	(boolean)( \
	( (uint32)_ch <= (uint32)GPT_INTERNAL_CHANNEL_W_1_B ) || ( \
		( (uint32)_ch >= (uint32)GPT_INTERNAL_CHANNEL_W_2_A ) && \
		( (uint32)_ch <= (uint32)GPT_INTERNAL_CHANNEL_W_5_B ) \
	) || ( \
		(\
		  ( \
		    ( (uint32)_ch >= (uint32)GPT_INTERNAL_CHANNEL_J_0 ) && \
		    ( (uint32)_ch <= (uint32)GPT_INTERNAL_CHANNEL_J_W_1 ) \
		  ) || ( \
		    ( \
			(uint32)_ch >= (uint32)GPT_INTERNAL_CHANNEL_J_W_2 \
		    ) && ( \
			(uint32)_ch <= (uint32)GPT_INTERNAL_CHANNEL_J_W_5 \
		    ) \
		  ) \
		) && !HW_CH_2_UNIT(_ch) \
	) \
)

/*
 * Channel is Wide Timer Test
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	TRUE:	Wide Timer
 * 		FALSE:	Normal Timer
 *
 * This macro function returns if the hardware timer module, referred to numeric
 * id of a channel is a wide timer or not.
 */
#define	GPT_CH_IS_WIDE(_ch)	(boolean)( \
	( \
		( (uint32)_ch >= (uint32)GPT_INTERNAL_CHANNEL_W_0_A ) && \
		( (uint32)_ch <= (uint32)GPT_INTERNAL_CHANNEL_W_5_B ) \
	) || \
	( \
		( (uint32)_ch >= (uint32)GPT_INTERNAL_CHANNEL_J_W_0 ) && \
		( (uint32)_ch <= (uint32)GPT_INTERNAL_CHANNEL_J_W_5 ) \
	) \
)

/*
 * Channel is Joined Timer Test
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	TRUE:	Joined Timer
 * 		FALSE:	Splitted Timer
 *
 * This macro function returns if the hardware timer module, referred to numeric
 * id of a channel is a joined timer or not.
 */
#define	GPT_CH_IS_JOINED(_ch)	(boolean)( \
	(uint32)_ch & (uint32)GPT_HW_TMR_JOIN_MASK \
)

/*
 * Channel is Wide Timer Not In Row Test
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	TRUE:	Wide Timer Not In Row
 * 		FALSE:	Wide Timer In Row
 *
 * This macro function returns if the hardware timer module, referred to numeric
 * id of a channel is a "wide timer not in row" or not.
 */
#define	GPT_CH_IS_WIDE_NOT_IN_ROW(_ch)	(boolean)( \
	( (uint32)_ch & (uint32)GTP_TMR_WIDE_ROW_MASK ) \
)

/*
 * Harware Timers Register Offsets
 */
#define	GPT_TMR_CFG_R_OFFSET	0x00000000	/* Configuration	      */
#define	GPT_TMR_MODE_R_OFFSET	0x00000004	/* Mode			      */
#define	GPT_TMR_CTL_R_OFFSET	0x0000000C	/* Control		      */

#define	GPT_TMR_IM_R_OFFSET	0x00000018	/* Interrupt Mask	      */
#define	GPT_TMR_RIS_R_OFFSET	0x0000001C	/* Raw Int Status	      */
#define	GPT_TMR_MIS_R_OFFSET	0x00000020	/* Masked Int Status	      */
#define	GPT_TMR_IC_R_OFFSET	0x00000024	/* Interrupt Clear	      */

#define	GPT_TMR_IL_R_OFFSET	0x00000028	/* Interval Load	      */
#define	GPT_TMR_P_R_OFFSET	0x00000038	/* Prescaler		      */

#define	GPT_TMR_V_R_OFFSET	0x00000050	/* Value		      */
#define	GPT_TMR_PV_R_OFFSET	0x00000064	/* Prescaler Value	      */

/*
 * Hardware Timers Controls
 */
#define	GPT_CH_HW_CTL_A_S_S		0x00000000	/* Timer A Shift Bits */
#define	GPT_CH_HW_CTL_B_S_S		0x00000003	/* Timer B Shift Bits */

/*
 * Hardware Timer Module Interrupt Sources
 */
#define	GPT_TMR_INT_WUE		0x00010000	/* 32/64-Bit Write Update     */
#define	GPT_TMR_INT_TBM		0x00000800	/* Timer B Mode Match	      */
#define	GPT_TMR_INT_CBE		0x00000400	/* Capture B Event	      */
#define	GPT_TMR_INT_CBM		0x00000200	/* Capture B Match	      */
#define	GPT_TMR_INT_TBTO	0x00000100	/* Timer B Time-Out	      */
#define	GPT_TMR_INT_TAM		0x00000010	/* Timer A Mode Match	      */
#define	GPT_TMR_INT_RTC		0x00000008	/* RTC Interrupt	      */
#define	GPT_TMR_INT_CAE		0x00000004	/* Capture A Event	      */
#define	GPT_TMR_INT_CAM		0x00000002	/* Capture A Match	      */
#define	GPT_TMR_INT_TATO	0x00000001	/* Timer A Time-Out	      */

/*
 * Hardware Timer A Interrupt Sources
 */
#define	GPT_TMRA_INT_ALL	( \
	GPT_TMR_INT_TAM	|	GPT_TMR_INT_CAE		| \
	GPT_TMR_INT_CAM	|	GPT_TMR_INT_TATO	\
)

/*
 * Hardware Timer B Interrupt Sources
 */
#define	GPT_TMRB_INT_ALL	( \
	GPT_TMR_INT_TBM	|	GPT_TMR_INT_CBE		| \
	GPT_TMR_INT_CBM	|	GPT_TMR_INT_TBTO	\
)
/*
 * All Hardware Timers Interrupts
 */
#define	GPT_TMR_INT_ALL	( \
	GPT_TMR_INT_WUE		|	GPT_TMR_INT_RTC		| \
	GPT_TMRA_INT_ALL	|	GPT_TMRB_INT_ALL	\
)

/*
 * Hardware Timers Units Interrupt
 */
#define	GPT_CH_HW_INT_A_S_S		0x00000000	/* Timer A Shift Bits */
#define	GPT_CH_HW_INT_B_S_S		0x00000003	/* Timer B Shift Bits */

/*
 * Hardware Configuration Retrieval.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Module Configuration
 */
#define	GPT_GET_CFG(_ch)	HW_CH_2_MOD_REG(_ch, GPT_TMR_CFG_R_OFFSET)

/*
 * Hardware Configuration Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_cfg	Harware Timer Module Configuratione
 */
#define	GPT_SET_CFG(_ch, _cfg)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CFG_R_OFFSET) = (uint32)_cfg \
)

/*
 * Harware Mode Retrieval.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Mode
 */
#define	GPT_GET_MODE(_ch)	HW_CH_2_UINT_REG(_ch, GPT_TMR_MODE_R_OFFSET)

/*
 * Hardware Mode Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_mode	Hardware Timer Unit Mode
 */
#define	GPT_SET_MODE(_ch, _mode)	( \
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_MODE_R_OFFSET) = (uint32)_mode \
)

/*
 * Hardware Control Retrieval.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Module Control
 */
#define	GPT_GET_CTL(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) >> (uint32)( \
		HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
	) \
)

/*
 * Hardware Control Setup.
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_ctl	Hardware Timer Module Control
 */
#define	GPT_SET_CTL(_ch, _ctl)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) |= ( \
		(uint32)_ctl << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		) \
	) \
)

/*
 * Hardware Counter Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Counter
 */
#define	GPT_GET_COUNTER(_ch)	HW_CH_2_UNIT_REG(_ch, GPT_TMR_V_R_OFFSET)

/*
 * Hardware Start Counter Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Start Counter
 */
#define	GPT_GET_START_COUNTER(_ch)	\
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_IL_R_OFFSET)

/*
 * Hardware Counter Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_val	Hardware Timer Unit Counter Value
 */
#define	GPT_SET_COUNTER(_ch, _val)	( \
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_IL_R_OFFSET) = (uint32)_val \
)

/*
 * Hardware Prescaler Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Prescaler
 */
#define	GPT_GET_PRESCALER(_ch)	HW_CH_2_UNIT_REG(_ch, GPT_TMR_PV_R_OFFSET)

/*
 * Hardware Start Prescaler Retrieval
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * return	Hardware Timer Unit Start Prescaler
 */
#define	GPT_GET_START_PRESCALER(_ch)	\
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_P_R_OFFSET)

/*
 * Hardware Prescaler Setup.
 *
 * param	_ch	Numeric ID of a GPT Channel. (Gpt_ChannelType)
 * param	_val	Hardware Timer Unit Prescaler Value
 */
#define	GPT_SET_PRESCALER(_ch, _val)	( \
	HW_CH_2_UNIT_REG(_ch, GPT_TMR_P_R_OFFSET) = (uint32)_val \
)

/*
 * Raw Interrupt Status Retrieval.
 */
#define	GPT_GET_RIS(_ch)	HW_CH_2_MOD_REG(_ch, GPT_TMR_RIS_R_OFFSET)

/*
 * Masked Interrupt Status Retrieval.
 */
#define	GPT_GET_MIS(_ch)	HW_CH_2_MOD_REG(_ch, GPT_TMR_MIS_R_OFFSET)

/*
 * Interrupt Clear
 */
#define	GPT_INT_CLR(_ch, _srcs)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_IC_R_OFFSET) |= (uint32)_srcs \
)

/*
 * Interrupt Enable
 */
#define	GPT_INT_EN(_ch, _srcs)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_IM_R_OFFSET) |= (uint32)_srcs \
)

/*
 * Interrupt Disable
 */
#define	GPT_INT_DIS(_ch, _srcs)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_IM_R_OFFSET) &= ~((uint32)_srcs) \
)

/*
 * Timer Stop.
 */
#define	GPT_TMR_STOP(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) &= \
	(uint32)~( \
		(uint32)GPT_CH_HW_CTL_ENABLE << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		) \
	) \
)

/*
 * Timer Start.
 */
#define	GPT_TMR_START(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) |= \
	(uint32)( \
		(uint32)GPT_CH_HW_CTL_ENABLE << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		)\
	) \
)

/*
 * Timer Running.
 */
#define	GPT_TMR_RUNNING(_ch)	( \
	HW_CH_2_MOD_REG(_ch, GPT_TMR_CTL_R_OFFSET) & \
	(uint32)( \
		(uint32)GPT_CH_HW_CTL_ENABLE << (uint32)( \
			HW_CH_2_UNIT(_ch) << (uint32)GPT_CH_HW_CTL_B_S_S \
		)\
	) \
)

/*
 * Timer Time-Out
 */
#define	GPT_TMR_TIMEOUT(_ch) ( \
	( \
		( \
			GPT_GET_RIS(_ch) >> (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) & GPT_TMR_INT_TATO \
	) || ( \
		( \
			GPT_GET_MIS(_ch) >> (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) & GPT_TMR_INT_TATO \
	) \
)

/*
 * Timer Time-Out Interrupt Clear
 */
#define	GPT_TMR_TIMEOUT_INT_CLR(_ch) ( \
	GPT_INT_CLR( \
		_ch, \
		( \
			(uint32)GPT_TMR_INT_TATO << (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) \
	)\
)

/*
 * Timer Time-Out Interrupt Enable
 */
#define	GPT_TMR_TIMEOUT_INT_EN(_ch) ( \
	GPT_INT_EN( \
		_ch, \
		( \
			(uint32)GPT_TMR_INT_TATO << (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) \
	)\
)

/*
 * Timer Time-Out Interrupt Disable
 */
#define	GPT_TMR_TIMEOUT_INT_DIS(_ch) ( \
	GPT_INT_DIS( \
		_ch, \
		( \
			(uint32)GPT_TMR_INT_TATO << (uint32)( \
				HW_CH_2_UNIT(_ch) << \
				(uint32)GPT_CH_HW_INT_B_S_S \
			) \
		) \
	)\
)

/* Value Masks */
#define	GPT_HW_TMR_EMPTY_VALUE			0x0000000000000000
#define	GPT_HW_TMR_SPLIT_VALUE_MASK		0xFFFFFFFFFF000000
#define	GPT_HW_TMR_SPLIT_WIDE_VALUE_MASK	0xFFFF000000000000
#define	GPT_HW_TMR_JOIN_VALUE_MASK		0xFFFFFFFF00000000
#define	GPT_HW_TMR_JOIN_WIDE_VALUE_MASK		0x0000000000000000
#define	GPT_HW_TMR_JOIN_WIDE_VALUE_S		0x0000000000000020

/* Prescaler Masks */
#define	GPT_HW_TMR_PRESCALER_IN_MASK		0x00000000000000FF
#define	GPT_HW_TMR_PRESCALER_IN_S		0x0000000000000008
#define	GPT_HW_TMR_PRESCALER_OUT_MASK		0x0000000000FF0000
#define	GPT_HW_TMR_PRESCALER_OUT_S		0x0000000000000010
#define	GPT_HW_TMR_WIDE_PRESCALER_IN_MASK	0x000000000000FFFF
#define	GPT_HW_TMR_WIDE_PRESCALER_IN_S		0x0000000000000010
#define	GPT_HW_TMR_WIDE_PRESCALER_OUT_MASK	0x0000FFFF00000000
#define	GPT_HW_TMR_WIDE_PRESCALER_OUT_S		0x0000000000000020
