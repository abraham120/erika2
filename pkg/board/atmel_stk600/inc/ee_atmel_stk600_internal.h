/** @file	ee_atmel_stk600_internal.h
 *
 *  @brief	Erika Enterprise - BOARD Internal - Atmel STK600 Header File.
 *
 *  <!--
 *    ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 *    Copyright (C) 2002-2013  Evidence Srl
 *
 *    This file is part of ERIKA Enterprise.
 *
 *    ERIKA Enterprise is free software; you can redistribute it
 *    and/or modify it under the terms of the GNU General Public License
 *    version 2 as published by the Free Software Foundation, 
 *    (with a special exception described below).
 *
 *    Linking this code statically or dynamically with other modules is
 *    making a combined work based on this code.  Thus, the terms and
 *    conditions of the GNU General Public License cover the whole
 *    combination.
 *
 *    As a special exception, the copyright holders of this library give you
 *    permission to link this code with independent modules to produce an
 *    executable, regardless of the license terms of these independent
 *    modules, and to copy and distribute the resulting executable under
 *    terms of your choice, provided that you also meet, for each linked
 *    independent module, the terms and conditions of the license of that
 *    module.  An independent module is a module which is not derived from
 *    or based on this library.  If you modify this code, you may extend
 *    this exception to your version of the code, but you are not
 *    obligated to do so.  If you do not wish to do so, delete this
 *    exception statement from your version.
 *
 *    ERIKA Enterprise is distributed in the hope that it will be
 *    useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 *    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License version 2 for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    version 2 along with ERIKA Enterprise; if not, write to the
 *    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *    Boston, MA 02110-1301 USA.
 *  -->
 *
 *  This file contains Internal data types and functions declaration for
 *  Atmel STK600 BOARD.
 *
 *  @author	Giuseppe Serano
 *  @version	0.1
 *  @date	2013
 */

#ifndef	__INCLUDE_ATMEL_STK600_INTERNAL_H__
#define	__INCLUDE_ATMEL_STK600_INTERNAL_H__

#include "board/atmel_stk600/inc/ee_atmel_stk600_board.h"

#define	EE_STK600_VALIDATE(_exp)	\
  if( !(_exp) ) {	\
    return;		\
  }

#define	EE_STK600_VALIDATE_IRQ(_exp,_flags)	\
  if( !(_exp) ) {				\
    EE_hal_resumeIRQ(_flags);			\
    return;					\
  }

#define EE_STK600_VALIDATE_W_RV(_exp,_rv)	\
  if( !(_exp) ) {				\
    return (_rv);				\
  }

#define EE_STK600_VALIDATE_IRQ_W_RV(_exp,_rv,_flags)	\
  if( !(_exp) ) {					\
    EE_hal_resumeIRQ(_flags);				\
    return (_rv);					\
  }

#if	( defined(__LED_DRIVER__) )
#define	EE_LED_MASK	0xFF
#endif

#endif	/* __INCLUDE_ATMEL_ATXMEGA_INTERNAL_H__ */