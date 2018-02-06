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

/*
 * Author: 2016 Nils Scharnke
 * Derived from cpu/rx200/inc/ee_irq.h
 */

#ifndef __INCLUDE_RH850_IRQ_H__
#define __INCLUDE_RH850_IRQ_H__

/* Use angled parenthesis to include the main "ee_internal.h" */
#include "cpu/rh850/inc/ee_cpu.h"
#include "cpu/common/inc/ee_context.h"
#include "cpu/common/inc/ee_irqstub.h"


#ifdef __ALLOW_NESTED_IRQ__

extern struct EE_TOS EE_rh850_IRQ_tos;

#define EE_std_enableIRQ_nested() EE_rh850_enableIRQ_nested()
#define EE_std_disableIRQ_nested() EE_rh850_disableIRQ_nested()

#else	/* else __ALLOW_NESTED_IRQ__*/

#define EE_std_enableIRQ_nested() ((void)0)
#define EE_std_disableIRQ_nested() ((void)0)

#endif /* end __ALLOW_NESTED_IRQ__*/


#if defined(__MULTI__) && defined(__IRQ_STACK_NEEDED__)

extern void EE_rh850_change_IRQ_stack(void);
extern void EE_rh850_change_IRQ_stack_back(void);

/*save the stack pointer*/ /*Load new stack pointer*/
#define EE_rh850_change_stack()\
do{ \
	if(EE_IRQ_nesting_level==1) {\
	EE_rh850_change_IRQ_stack(); \
}\
}while(0)


#define EE_rh850_stack_back()\
do{ \
	EE_rh850_change_IRQ_stack_back();\
}while(0)

#else	/* else __MULTI__ && __IRQ_STACK_NEEDED__*/

#define EE_rh850_change_stack() ((void)0)
#define EE_rh850_stack_back() ((void)0)

#endif	/* end __MULTI__ && __IRQ_STACK_NEEDED__*/
 
 
 
#define EE_ISR2_prestub(void) \
do { \
	EE_rh850_disableIRQ();\
	EE_increment_IRQ_nesting_level();\
	EE_rh850_change_stack();\
	EE_std_enableIRQ_nested();\
	EE_rh850_enableIRQ(); \
}while(0)


#define EE_ISR2_poststub(void) \
do{ \
		EE_rh850_disableIRQ();\
		EE_std_end_IRQ_post_stub();\
    EE_decrement_IRQ_nesting_level();\
    if (!EE_is_inside_ISR_call()) {\
		 EE_rh850_stack_back();\
		 EE_std_disableIRQ_nested();\
		 EE_rh850_enableIRQ();\
		 EE_std_after_IRQ_schedule();\
    }\
    else {\
     EE_rh850_enableIRQ();\
    }\
  } while(0)




#define ISR1(f)			\
void ISR1_ ## f(void);		\
intvect __interrupt void INT ## f(void)		\
{				\
	ISR1_ ## f();		\
}				\
void ISR1_ ## f(void)


#define ISR2(f)			\
void ISR2_ ## f(void); \
intvect __interrupt void INT ## f(void)		\
{				\
	EE_ISR2_prestub();	\
	ISR2_ ## f();		\
	EE_ISR2_poststub();	\
}				\
void ISR2_ ## f(void)

#endif /* __INCLUDE_RH850_IRQ_H__ */

