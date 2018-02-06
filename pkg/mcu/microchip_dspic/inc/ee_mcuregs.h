/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: 
 * CVS: $Id: ee_mcuregs.h,v 1.7 2007/08/31 08:21:10 pj Exp $
 */

#include "cpu/pic30/inc/ee_cpu.h"

#ifndef __INCLUDE_MCU_MICROCHIP_DSPIC_MCUREGS__
#define __INCLUDE_MCU_MICROCHIP_DSPIC_MCUREGS__

/* This file should contain the definition of the registers available
   on the particular dsPIC being used */
   
/* Include a file with the registers from Microchip C30 distribution */ 
#ifdef __PIC30_INCLUDE_REGS__
#include "ee_pic30regs.h"
#endif


/* A set of features which are used by the MCU code... */
#ifdef __PIC24HJ128GP206__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ128GP210__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ128GP306__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ128GP310__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ128GP506__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ128GP510__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ256GP206__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ256GP210__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ256GP610__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ64GP206__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ64GP210__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ64GP506__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __PIC24HJ64GP510__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128GP206__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128GP306__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128GP310__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128GP706__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128GP708__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128GP710__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128MC506__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128MC510__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128MC706__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128MC708__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ128MC710__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ256GP506__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ256GP510__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ256GP710__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ256MC510__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ256MC710__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64GP206__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64GP306__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64GP310__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64GP706__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64GP708__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64GP710__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64MC506__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64MC508__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64MC510__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64MC706__
#define __PIC30_HAS_TMR8__
#endif

#ifdef __dsPIC33FJ64MC710__
#define __PIC30_HAS_TMR8__
#endif



 
#endif
