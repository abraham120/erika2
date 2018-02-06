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
 * Derived from pkg/cpu/pic30/inc/ee_irqstub.h
 * Author: 2010,Christian Grioli
*/



#ifndef __INCLUDE_MSP430_EE_IRQSTUB_H__
#define __INCLUDE_MSP430_EE_IRQSTUB_H__


#include "eecfg.h"

#include <cpu/common/inc/ee_compiler_gcc.h>
#include <cpu/common/inc/ee_context.h>
#include <cpu/common/inc/ee_primitives.h>



extern void EE_IRQ_end_instance(void);

#ifdef __ALLOW_NESTED_IRQ__

#define EE_std_enableIRQ_nested() EE_msp430_enableIRQ()
#define EE_std_disableIRQ_nested() EE_msp430_disableIRQ()

#endif


#include <cpu/common/inc/ee_irqstub.h>

/*Function and macro for implementing of prestub and poststub*/


#ifdef __LPMODE__

extern EE_UINT16* EE_sr_on_stack; /*Save the address of the SR value saved on stack during ISR*/ 
extern EE_UINT16* EE_sr_nested; /*Save the EE_sr_on_stack value, used with ISR nested*/


/*Save in EE_sr_on_stack the address of SR on stack , if nesting is enable, save the preceding address*/
#define EE_ISR2_prestub_LPM(name) EE_sr_nested=EE_sr_on_stack;\
__asm__("mov r1,&EE_sr_on_stack"::);\
__asm__("add #.L__FrameOffset_"#name", &EE_sr_on_stack"::);\
if(EE_is_inside_ISR_call())\
__asm__("push &EE_sr_nested"::);\

/*Recharge the old value of EE_sr_on_stack*/
#define EE_ISR2_poststub_LPM() __asm__("pop &EE_sr_on_stack"::);\


#else


#define EE_ISR2_prestub_LPM(name)
#define EE_ISR2_poststub_LPM()

#endif /*end __LPMODE__*/


#ifdef __ALLOW_NESTED_IRQ__

#define EE_irq_nesting_prestub() EE_std_enableIRQ_nested()
#define EE_irq_nesting_poststub()  \
  if (EE_is_inside_ISR_call()) {\
	EE_ISR2_poststub_LPM();\
       /*In ISR Nesting, enable again interrupt*/\
	EE_std_enableIRQ_nested();\
	return;\
}


#else

#define EE_irq_nesting_prestub()
#define EE_irq_nesting_poststub()

#endif /* end __ALLOW_NESTED_IRQ__*/



#if defined(__MULTI__) && defined(__IRQ_STACK_NEEDED__)

EE_ADDR EE_msp430_temp_tos;

#define EE_change_stack() if(EE_IRQ_nesting_level==1){\
/*save the stack pointer*/\
__asm__("mov r1, EE_msp430_temp_tos"::);\
/*Load new stack pointer*/\
__asm__("mov EE_msp430_IRQ_tos,r1"::);\
}

#define EE_change_stack_back() __asm__("mov EE_msp430_temp_tos,r1"::);

#else

#define EE_change_stack()
#define EE_change_stack_back()

#endif /*end __MULTI__ && __IRQ_STACK_NEEDED__*/



__INLINE__ void  __ALWAYS_INLINE__ EE_ISR2_prestub(void)
{

/* See /common/ee_iqstub.h, this function set the correct value of IRQ nesting level in both case with IRQ nested allow or not*/ 
EE_increment_IRQ_nesting_level();

/*Change the stack*/
EE_change_stack();
/*IRQ nested is allowed, so enable IRQ*/
EE_irq_nesting_prestub();

}

__INLINE__ void __ALWAYS_INLINE__ EE_ISR2_poststub(void)
{

EE_std_disableIRQ_nested();
EE_decrement_IRQ_nesting_level();
 
/*Disable interrupt and check if irq is nesting*/
EE_irq_nesting_poststub();


/*Reload the preceding stack*/
EE_change_stack_back();
/*Call the scheduler*/
EE_std_after_IRQ_schedule();

/*Enable interrupt*/
 EE_msp430_enableIRQ();
}



#define ISR2(f) \
void ISR2_##f(void); \
 interrupt (f) routine_##f(void) \
{ \
  EE_msp430_disableIRQ();\
  EE_ISR2_prestub_LPM(routine_##f);\
  EE_ISR2_prestub(); \
  ISR2_##f(); \
  EE_ISR2_poststub(); \
} \
void ISR2_##f(void)

/* Code for ISR1*/
#ifdef __ALLOW_NESTED_IRQ__   
#define NESTED enablenested
#else
#define NESTED
#endif

#define ISR1(f) \
interrupt(f) NESTED routine_##f(void)
#endif
