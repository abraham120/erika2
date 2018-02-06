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

/** @file   Utility.h
 *  @brief  header with macros and inclusions useful to all modules
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date 2012
 */

#ifndef UTILITY_H
#define UTILITY_H

/* Macro to calculate the effective length of an array. */
#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(x_) (sizeof(x_)/sizeof((x_)[0]))
#endif

/* Development error macros. */
#if ( MCU_DEV_ERROR_DETECT == STD_ON )

/* In Order To Use Following Validation Macrocs each module must define
   AS_MODULE_ID with correct value */

#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif

#define AS_ASSERt(exp_, api_, err_)\
  if( !(exp_) ) {\
    Det_ReportError(AS_MODULE_ID, 0, api_, err_);\
    return;\
  }

#define AS_ASSERT_W_RV(exp_, api_, err_, rv_)\
  if( !(exp_) ) {\
    Det_ReportError(AS_MODULE_ID, 0, api_, err_);\
    return (rv_);\
  }

#define AS_ERROR(api_, err_) Det_ReportError(AS_MODULE_ID, 0, api_, err_)

#else /* MCU_DEV_ERROR_DETECT */

#define AS_ASSERT(exp_, api_, err_)\
  if( !(exp_) ) {\
    return;\
  }

#define AS_ASSERT_W_RV(exp_, api_, err_, rv_)\
  if( !(exp_) ) {\
    return (rv_);\
  }

#define AS_ERROR(api_, err_)   ((void)0)

#endif  /* !MCU_DEV_ERROR_DETECT */

#endif  /* UTILITY_H */
