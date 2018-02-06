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

/*===========================================================================*/
/*                                                                           */
/* Device specific main header file to be included in all source files.      */
/*                                                                           */
/*===========================================================================*/
#ifndef	__INCLUDE_R7F701503_MCU_H__
#define	__INCLUDE_R7F701503_MCU_H__

/*===========================================================================*/
/* Global compiler definition */
/*===========================================================================*/ 
#define COMP_GHS     1
#define COMP_IAR     2


#if defined (__IAR__)
    #define COMPILER COMP_IAR
#elif defined (__GHS__) /*GHS */
    #define COMPILER COMP_GHS
#else
		#warning no_valid_compiler
#endif



/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#if COMPILER == COMP_GHS
	 #include "dr7f701503.dvf.h"
	 #include "icu_feret.h"
	 #include "io_macros_v2.h"
#endif

#if COMPILER == COMP_IAR
	#include <ior7f701503.h>
#endif

#ifdef __USE_CLOCK_INIT__
#include "ee_clock.h"
#endif

#ifdef __USE_TIMER_INT__
#include "ee_timer.h"
#endif 

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
/* Function for the write-sequence of protected registers */
#define protected_write(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;\
                                                  (reg)=(value);\
                                                  (reg)=~(value);\
                                                  (reg)=(value);\
                                                  }while((pstatus)==1u)
                                          
#if COMPILER == COMP_IAR
  #define __EI() __enable_interrupt()
  #define __DI() __disable_interrupt()
  typedef unsigned char     u08_T;
  typedef unsigned short    u16_T;
  typedef unsigned long     u32_T;
#endif

#define PE1 1
#define PE2 2

typedef signed char       s08_T;
typedef signed short      s16_T;
typedef signed int        s32_T;

                                                    
/****************************************************************************/
/* The IAR needs two different called main functions for each core while    */
/* the GHS needs a "main()"-function in each core-project.                  */
/* Thus the "main_peX"-functions are both executed as "main" when using GHS */
/****************************************************************************/
#if COMPILER == COMP_GHS
	#define main_pe1 main
	#define main_pe2 main
#endif


#endif	/* __INCLUDE_R7F701503_MCU_H__ */
