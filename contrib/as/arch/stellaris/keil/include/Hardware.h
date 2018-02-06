/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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

/** @file	Hardware.h
 *  @brief	Hardware Abstraction Header File.
 *
 *  This file contains all the functions and macros for abstraction of harware
 *  for Texas Instruments Stellaris LM4f232XXXX and Keil compiler.
 *
 *  @author	Giuseppe Serano
 *  @date	2011
 */

#ifndef	HARDWARE_H
#define	HARDWARE_H

/*
 * MACROS
 */
#define	HW_REG_SZ	0x00000004		/**< Register Size in Bytes   */
#define	HW_REG_SZ_S	0x00000002		/**< Register Size Shift Bits */

#define	HW_BASE_MASK	0x00000001		/**< HW Base Mask	      */

/** @brief	Channel to Hardware Unit.
 *  @param	_ch	Numeric ID of a Channel.
 *  @return	Numeric ID of Hardware Unit.
 *
 *  This macro function returns the numeric ID of the harware unit referred to
 *  numeric id of a channel.
 *
 *  @note	Requires <tt>HW_CH_UNIT_MASK</tt> macro.
 */
#ifdef	HW_CH_UNIT_MASK
#define	HW_CH_2_UNIT(_ch)	(uint32)( \
  (uint32)_ch & (uint32)HW_CH_UNIT_MASK \
)
#else
#define	HW_CH_2_UNIT(_ch)	(uint32)( 0x00000000 )
#endif

/** @brief	Channel to Hardware Module.
 *  @param	_ch	Numeric ID of a Channel.
 *  @return	Numeric ID of Hardware Module.
 *
 *  This macro function returns the numeric ID of the harware module referred to
 *  numeric id of a channel.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> macro.
 */
#ifdef	HW_CH_MOD_MASK
#ifdef	HW_CH_UNIT_MASK_SZ_S
#define	HW_CH_2_MOD(_ch)	(uint32)( \
  ( (uint32)_ch & (uint32)HW_CH_MOD_MASK ) >> (uint32)HW_CH_UNIT_MASK_SZ_S \
)
#else	/* HW_CH_UNIT_MASK_SZ_S */
#define	HW_CH_2_MOD(_ch)	(uint32)( \
  (uint32)_ch & (uint32)HW_CH_MOD_MASK \
)
#endif	/* !HW_CH_UNIT_MASK_SZ_S */
#endif	/* HW_CH_MOD_MASK */

/** @brief	Hardware Clock Gating Control Base Mask */
#define	HW_CGC_BASE_MASK	HW_BASE_MASK

/** @brief	Channel to Clock Gating Control Mask.
 *  @param	_ch	Numeric ID of a Channel.
 *  @return	Clock Gating Control Mask of the Hardware Module.
 *
 *  This macro function returns the Clock Gating Control Mask of the harware
 *  module referred to numeric id of a channel.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> macro.
 *
 *  @see	<tt>HW_CH_2_MOD</tt> macro.
 */
#ifdef	HW_CH_MOD_MASK
#define	HW_CH_2_CGC_MASK(_ch)	(uint32)( \
  (uint32)HW_CGC_BASE_MASK << HW_CH_2_MOD(_ch) \
)
#endif

#define	HW_MOD_ADDR_S	0x0000000C	/**< HW Module Address Shift Bits     */

/** @brief	Channel to Hardware Module Base Address
 *  @param	_ch	Channel Identifier.
 *  @return	Hardware Module Base Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_BASE_ADDR) )
#define	HW_CH_2_MOD_BASE_ADDR(_ch)	(uint32)( \
  ((uint32)HW_BASE_ADDR) + (HW_CH_2_MOD(_ch) << (uint32)HW_MOD_ADDR_S) \
)
#endif	/* HW_CH_MOD_MASK && HW_BASE_ADDR */

/** @brief	Channel to Hardware Module Register Address
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Module Register Offset.
 *  @return	Hardware Module Register Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		and <tt>HW_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD_BASE_ADDR</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_BASE_ADDR) )
#define	HW_CH_2_MOD_REG_ADDR(_ch, _ro)	(uint32)( \
  HW_CH_2_MOD_BASE_ADDR(_ch) + (uint32)_ro \
)
#endif	/* HW_CH_MOD_MASK && HW_BASE_ADDR */

/** @brief	Channel to Hardware Module Register
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Module Register Offset.
 *  @return	Hardware Module Register.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD_REG_ADDR</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_BASE_ADDR) )
#define	HW_CH_2_MOD_REG(_ch, _ro)	EE_HWREG( \
  HW_CH_2_MOD_REG_ADDR(_ch, _ro) \
)
#endif	/* HW_CH_MOD_MASK && HW_BASE_ADDR */

/** @brief	Channel to Hardware Unit Register Address
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Unit Register Offset.
 *  @return	Hardware Unit Register Address.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_MOD_REG_ADDR</tt> and <tt>HW_CH_2_UNIT</tt> macros.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_BASE_ADDR) )
#ifdef	HW_CH_UNIT_MASK
#define	HW_CH_2_UNIT_REG_ADDR(_ch, _ro)	(uint32)( \
  HW_CH_2_MOD_REG_ADDR(_ch,_ro) + (uint32)( \
    HW_CH_2_UNIT(_ch) << (uint32)HW_REG_SZ_S \
  ) \
)
#else	/* HW_CH_UNIT_MASK */
#define	HW_CH_2_UNIT_REG_ADDR(_ch, _ro)	(uint32)( HW_CH_2_MOD_REG_ADDR(_ch) )
#endif	/* !HW_CH_UNIT_MASK */
#endif	/* HW_CH_MOD_MASK && HW_BASE_ADDR */

/** @brief	Channel to Hardware Unit Register
 *  @param	_ch	Channel Identifier.
 *  @param	_ro	Harware Unit Register Offset.
 *  @return	Hardware Unit Register.
 *
 *  @note	Requires <tt>HW_CH_MOD_MASK</tt> and
 *  		<tt>HW_BASE_ADDR</tt> macros.
 *
 *  @see	<tt>HW_CH_2_UNIT_REG_ADDR</tt> macro.
 */
#if	( defined(HW_CH_MOD_MASK) && defined(HW_BASE_ADDR) )
#define	HW_CH_2_UNIT_REG(_ch, _ro)	EE_HWREG( \
  HW_CH_2_UNIT_REG_ADDR(_ch, _ro) \
)
#endif	/* HW_CH_MOD_MASK && HW_BASE_ADDR */

/*
 * FUNCTIONS
 */

/** @brief	Supported Core Check.
 *
 *  @return
 *  		- E_OK:		Core Supported.
 *  		- E_NOT_OK:	Core Not Supported.
 *
 *  Checs if the core is supported or not.
 */
Std_ReturnType Hw_CheckCore(
  void
);

#endif	/* HARDWARE_H */
