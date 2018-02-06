/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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

/** 
	@file ee_gpio.h
	@brief 	GPIO library header file.\n
			GPIO API explanation:\n
			API is generated with DECLARE_FUNC_GPIO(uc, lc) and only if the macros
			EE_GPIO1_NAME_UC, EE_GPIO2_NAME_UC, EE_GPIO3_NAME_UC, EE_GPIO4_NAME_UC
			are defined in "eecfg.h". 
	@author Dario Di Stefano, Bernardo Dal Seno
	@date 	2010
	@example	
			The name of the GPIO module specified inside the platform and
			inside the conf.oil file is "User_Gpio".
			
			The macros generated in "eecfg.h" are:\n
			\#define EE_GPIO1_NAME_LC user_gpio\n
			\#define EE_GPIO1_NAME_UC USER_GPIO\n
			
			The user must use the lower case form of the name, "user_gpio", 
			to call the functions of the GPIO API as shown in the following example list.
	
			Name: 				unsigned int EE_user_gpio_read_data(void);\n
			Action: 			This function reads data register;\n
			Return: 			data register.\n
			
			Name: 				unsigned int EE_user_gpio_read_data_out(void);\n
			Action:				This function reads output data;\n
			Return:				output data.\n
			
			Name: 				void EE_user_gpio_write_data(unsigned int val);\n
			Action: 			This function writes data register;\n
			Parameter val:		desired value for data register;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_bit_data(unsigned int val, unsigned char numbit);\n
			Action: 			This function writes a bit in data register;\n
			Parameter val:		value for the bit to be changed;\n
			Parameter numbit:	Number of the bit; \n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_mask_data(unsigned int val, unsigned int mask);\n
			Action: 			This function writes data register using a mask;\n
			Parameter val:		value to be masked;\n
			Parameter mask:		mask to be used;\n
			Return:				nothing.\n
			
			Name: 				int EE_user_gpio_read_tristate(void);\n
			Action: 			This function reads tristate register;\n
			Return: 			tristate register.\n
			
			Name: 				void EE_user_gpio_write_tristate(unsigned int val);\n
			Action: 			This function writes tristate register;\n
			Parameter val:		desired value for tristate register;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_bit_tristate(unsigned int val, unsigned char numbit);\n
			Action: 			This function writes a bit in tristate register;\n
			Parameter val:		value for the bit to be changed;\n
			Parameter numbit:	Number of the bit;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_mask_tristate(unsigned int val, unsigned int mask);\n
			Action: 			This function writes tristate register using a mask;\n
			Parameter val:		value to be masked;\n
			Parameter mask:		mask to be used;\n
			Return:				nothing.\n
			
			Name: 				int EE_user_gpio_read_irqMask(void);\n
			Action: 			This function reads irqMask register;\n
			Return: 			irqMask register.\n
			
			Name: 				void EE_user_gpio_write_irqMask(unsigned int val);\n
			Action: 			This function writes irqMask register;\n
			Parameter val:		desired value for irqMask register;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_bit_irqMask(unsigned int val, unsigned char numbit);\n
			Action: 			This function writes a bit in irqMask register;\n
			Parameter val:		value for the bit to be changed;\n
			Parameter numbit:	Number of the bit;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_mask_irqMask(unsigned int val, unsigned int mask);\n
			Action: 			This function writes irqMask register using a mask;\n
			Parameter val:		value to be masked;\n
			Parameter mask:		mask to be used;\n
			Return:				nothing.\n
			
			Name: 				int EE_user_gpio_read_edgeCapture(void);\n
			Action: 			This function read edgeCapture register;\n
			Return: 			edgeCapture register.\n
			
			Name: 				void EE_user_gpio_write_edgeCapture(unsigned int val);\n
			Action: 			This function writes edgeCapture register;\n
			Parameter val:		desired value for edgeCapture register;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_bit_edgeCapture(unsigned int val, unsigned char numbit);\n
			Action: 			This function writes a bit in edgeCapture register;\n
			Parameter val:		value for the bit to be changed;\n
			Parameter numbit:	Number of the bit;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_write_mask_edgeCapture(unsigned int val, unsigned int mask);\n
			Action: 			This function writes edgeCapture register using a mask;\n
			Parameter val:		value to be masked;\n
			Parameter mask:		mask to be used;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_enable_IRQ(unsigned int ch);\n
			Action:				This function enables GPIO IRQ;\n
			Parameter ch:		GPIO channel to enable interrupt to;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_disable_IRQ(void);\n
			Action:				This function disables GPIO IRQ;\n
			Return:				nothing.\n
			
			Name: 				void EE_user_gpio_set_IRQ_callback(EE_ISR_callback cbk);\n
			Action:				This function sets GPIO IRQ callback;\n 
			Parameter cbk:		pointer to the callback;\n
			Return:				nothing.\n
*/

#ifndef __INCLUDE_EEMCUMICO32_GPIO_H__
#define __INCLUDE_EEMCUMICO32_GPIO_H__

//#include "cpu/mico32/inc/ee_internal.h"
#include <ee_irq.h>
#include "mcu/mico32/inc/ee_internal.h"
//#include <cpu/mico32/inc/ee_irq.h>
#include <MicoGPIO.h>

/*************************************************************************
 GPIO
*************************************************************************/
/* Generic Macros */
#define EE_GPIO_OK                              (0x00) 
#define EE_GPIO_FAILURE                         (-1)
/* Macro for Structure declaration */
#define DECLARE_STRUCT_GPIO(uc, lc)             \
extern EE_gpio_st EE_ST_NAME(lc);
/* Macro for structure definition */
#define DEFINE_STRUCT_GPIO(uc, lc)                      \
EE_gpio_st cat3(ee_, lc, _st) = {                       \
    .base = (MicoGPIO_t* )cat2(uc, _BASE_ADDRESS),      \
    .irqf = cat2(uc, _IRQ),                             \
    .cbk = EE_NULL_CBK,                                 \
    .flag = 0};

/* GPIO structure */
typedef struct {
    /** Pins that caused the latest interrupt; this mask is valid only in
     * the callback */
    unsigned int flag;
    /** Controller base address */
    MicoGPIO_t* const base;
    /** IRQ number to register the handler */
    const int irqf;
    /** Interrupt callback */
    EE_ISR_callback cbk;
    /** Copy of the data register.  Used for GPIO configured as both input and
     * output or configured as output only */
    volatile unsigned int data_copy;
} EE_gpio_st;

/* GPIO API */
#define DECLARE_FUNC_GPIO(uc, lc)                                       \
__INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_data)(void){ \
    return EE_hal_gpio_read_data((MicoGPIO_t*)EE_BASE_ADD(uc)); }       \
 __INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_data_out)(void){ \
     if (! cat2(uc, _TRISTATE_PORTS))                              \
         return EE_hal_gpio_output_read_data_out(&EE_ST_NAME(lc));      \
     else                                                               \
         return EE_hal_gpio_read_data_out((MicoGPIO_t*)EE_BASE_ADD(uc)); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_data)(unsigned int val){ \
     if (! cat2(uc, _TRISTATE_PORTS))                              \
         EE_hal_gpio_output_write_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, &EE_ST_NAME(lc)); \
     else                                                               \
         EE_hal_gpio_write_data((MicoGPIO_t*)EE_BASE_ADD(uc), val); }   \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_data)(unsigned int val, unsigned char numbit){ \
     if (! cat2(uc, _TRISTATE_PORTS))                              \
         EE_hal_gpio_output_write_bit_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit, &EE_ST_NAME(lc)); \
     else                                                               \
         EE_hal_gpio_write_bit_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_data)(unsigned int val, unsigned int mask){ \
     if (! cat2(uc, _TRISTATE_PORTS))                              \
         EE_hal_gpio_output_write_mask_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask, &EE_ST_NAME(lc)); \
     else                                                               \
         EE_hal_gpio_write_mask_data((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ int __ALWAYS_INLINE__ cat3(EE_, lc, _read_tristate)(void){  \
     return EE_hal_gpio_read_tristate((MicoGPIO_t*)EE_BASE_ADD(uc)); }  \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_tristate)(unsigned int val){ \
     EE_hal_gpio_write_tristate((MicoGPIO_t*)EE_BASE_ADD(uc), val); }   \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_tristate)(unsigned int val, unsigned char numbit){ \
     EE_hal_gpio_write_bit_tristate((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_tristate)(unsigned int val, unsigned int mask){ \
     EE_hal_gpio_write_mask_tristate((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_irqMask)(void){ \
     return EE_hal_gpio_read_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc)); }   \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_irqMask)(unsigned int val){ \
     EE_hal_gpio_write_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc), val); }    \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_irqMask)(unsigned int val, unsigned char numbit){ \
     EE_hal_gpio_write_bit_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_irqMask)(unsigned int val, unsigned int mask){ \
     EE_hal_gpio_write_mask_irqMask((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ unsigned int __ALWAYS_INLINE__ cat3(EE_, lc, _read_edgeCapture)(void){ \
     return EE_hal_gpio_read_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc)); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_edgeCapture)(unsigned int val){ \
     EE_hal_gpio_write_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc), val); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_bit_edgeCapture)(unsigned int val, unsigned char numbit){ \
     EE_hal_gpio_write_bit_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc), val, numbit); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _write_mask_edgeCapture)(unsigned int val, unsigned int mask){ \
     EE_hal_gpio_write_mask_edgeCapture((MicoGPIO_t*)EE_BASE_ADD(uc), val, mask); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _enable_IRQ)(unsigned int ch){ \
     EE_hal_gpio_enable_IRQ(& EE_ST_NAME(lc), cat2(uc, _IRQ_MODE), ch); } \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _disable_IRQ)(void){   \
     EE_hal_gpio_disable_IRQ(& EE_ST_NAME(lc)); }                       \
 __INLINE__ void __ALWAYS_INLINE__ cat3(EE_, lc, _set_IRQ_callback)(EE_ISR_callback cbk){ \
     EE_hal_gpio_set_IRQ_callback(& EE_ST_NAME(lc), cbk); }


#ifdef __USE_DIAMOND__
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_word_inversion(unsigned int word)
{
	unsigned int xw;
	EE_UINT8* x = (EE_UINT8*)&xw;
	x[0] = ((EE_UINT8*)&word)[3];
	x[1] = ((EE_UINT8*)&word)[2];
	x[2] = ((EE_UINT8*)&word)[1];
	x[3] = ((EE_UINT8*)&word)[0];
	return xw;
}

#else
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_word_inversion(unsigned int word)
{
	return word;
}

#endif
 
/**
	@brief 			This function is GPIO IRQ handler.
	@param level 	IRQ number
*/
void EE_gpio_common_handler(int level);
  
#ifndef __STATIC_ISR_TABLE__
/**
	@brief 			This function sets the interrupt handler
	@param gpio_sp 	Pointer to GPIO controller structure
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_handler_setup(EE_gpio_st* gpio_sp)
{
	/* Register IRQ handler */
    EE_mico32_register_ISR(gpio_sp->irqf, EE_gpio_common_handler);   
}
#else // __STATIC_ISR_TABLE__
#define EE_hal_gpio_handler_setup(gpio_sp)
#endif // __STATIC_ISR_TABLE__

/**
	@brief 			This function reads data register
	@param base 	Pointer to GPIO register structure
	@return			data register
*/
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_data(MicoGPIO_t* base)
{
    return EE_hal_word_inversion(base->data);
}
 
/**
	@brief 			This function reads output data
	@param base 	Pointer to GPIO register structure
	@return			data register
*/ 
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_data_out(MicoGPIO_t* base)
{
    return EE_hal_word_inversion(base->data);
}

/**
	@brief 			This function reads output data
	@param gpio_sp 	Pointer to GPIO driver structure
	@return			an internal copy of data register
*/ 
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_output_read_data_out(EE_gpio_st *gpio_sp)
{
    return gpio_sp->data_copy;
}
 
/**
	@brief 			This function writes on data register
	@param base 	Pointer to GPIO driver structure
	@param val		desired value for data register
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_data(MicoGPIO_t *base, unsigned int val)
{
    base->data = EE_hal_word_inversion(val);
} 

/**
	@brief 			This function writes data and data_copy 
					(called by EE_hal_gpio_output_write_data)
	@param base 	Pointer to GPIO driver structure
	@param val		desired value for data register
	@param gpio_sp	Pointer to GPIO driver structure
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_output_write_data_internal(MicoGPIO_t *base, unsigned int val, EE_gpio_st *gpio_sp)
{
	gpio_sp->data_copy = val;
    base->data = EE_hal_word_inversion(val);
} 

/**
	@brief 			This function writes data
					(critical section protected by disabling IRQ)
	@param base 	Pointer to GPIO driver structure
	@param val		desired value for data register
	@param gpio_sp	Pointer to GPIO driver structure
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_output_write_data(MicoGPIO_t *base, unsigned int val, EE_gpio_st *gpio_sp)
{
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    EE_hal_gpio_output_write_data_internal(base, val, gpio_sp);
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 

/**
	@brief 			This function writes a bit in data register
					(critical section protected by disabling IRQ)
	@param base 	Pointer to GPIO driver structure
	@param val		desired value for the bit [1,0]
	@param numbit	Number of the bit to be modified
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_data(MicoGPIO_t *base, unsigned int val, unsigned char numbit)
{
    unsigned int mask = (1 << numbit);
    unsigned int data;
    EE_FREG irqstat;

	// --
    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_read_data_out(base);
    if(val) {
        EE_hal_gpio_write_data(base, data | mask);
    } else {
        EE_hal_gpio_write_data(base, data & (~mask));
	}
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 
   
/**
	@brief 			This function writes a bit in data register
					(critical section protected by disabling IRQ)
	@param base 	Pointer to GPIO driver structure
	@param val		desired value for the bit [1,0]
	@param numbit	Number of the bit to be modified
	@param gpio_sp	Pointer to GPIO driver structure
*/   
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_output_write_bit_data(
    MicoGPIO_t *base, unsigned int val, unsigned char numbit,
    EE_gpio_st *gpio_sp)
{
    unsigned int mask = (1 << numbit);
    unsigned int data;
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_output_read_data_out(gpio_sp);
    if(val) {
        EE_hal_gpio_output_write_data_internal(base, data | mask, gpio_sp);
    } else {
        EE_hal_gpio_output_write_data_internal(base, data & (~mask), gpio_sp);
	}	
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 

/**
	@brief 			This function writes data register with a mask
					(critical section protected by disabling IRQ)
	@param base 	Pointer to GPIO driver structure
	@param val		value to be masked
	@param mask		Mask to be used
*/      
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_data(MicoGPIO_t* base,
    unsigned int val, unsigned int mask)
{ 
    unsigned int data;
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_read_data_out(base);
    EE_hal_gpio_write_data(base, (data & (~mask)) | (val & mask));
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
}
   
/**
	@brief 			This function writes data register with a mask
					(critical section protected by disabling IRQ)
	@param base 	Pointer to GPIO driver structure
	@param val		value to be masked
	@param mask		Mask to be used
	@param gpio_sp	Pointer to GPIO driver structure
*/    
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_output_write_mask_data(
    MicoGPIO_t* base, unsigned int val, unsigned int mask, EE_gpio_st *gpio_sp)
{ 
    unsigned int data;
    EE_FREG irqstat;

    irqstat = EE_mico32_disableIRQ();
    data = EE_hal_gpio_output_read_data_out(gpio_sp);
    EE_hal_gpio_output_write_data_internal(base,
        ((data & (~mask)) | (val & mask)), gpio_sp);
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
}
     
/**
	@brief 			This function reads tristate register
	@param base 	Pointer to GPIO register structure
	@return			tristate register
*/ 	 
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_tristate(
    MicoGPIO_t* base)
{
	return EE_hal_word_inversion(base->tristate);
} 
 
/**
	@brief 			This function writes tristate register
	@param base 	Pointer to GPIO register structure
	@param val 		desired value for tristate register
*/ 	
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_tristate(MicoGPIO_t* base,
    unsigned int val)
{
    base->tristate = EE_hal_word_inversion(val);
} 
 
/**
	@brief 			This function writes bit in tristate register
					(critical section protected by disabling IRQ)
	@param base 	Pointer to GPIO register structure
	@param val 		desired value for tristate register
	@param numbit	Number of the bit to be modified
*/ 	
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_tristate(MicoGPIO_t* base, unsigned int val, unsigned char numbit)
{ 
    unsigned int mask = (1 << numbit);
    unsigned int tristate;
    EE_FREG irqstat;
    
    irqstat = EE_mico32_disableIRQ();
        tristate = EE_hal_word_inversion(base->tristate);
    if(val)
        base->tristate = EE_hal_word_inversion(tristate | mask);
    else
        base->tristate = EE_hal_word_inversion(tristate & (~mask));
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 
   
/**
	@brief 			This function writes tristate register with a mask
					(critical section protected by disabling IRQ)
	@param base 	Pointer to GPIO register structure
	@param val 		Value to be masked
	@param mask		Mask to be used
*/  
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_tristate(MicoGPIO_t* base, unsigned int val, unsigned int mask)
{ 
    unsigned int tristate;
    EE_FREG irqstat;
    	
    irqstat = EE_mico32_disableIRQ();
    tristate = EE_hal_word_inversion(base->tristate);
    base->tristate = EE_hal_word_inversion((tristate & (~mask)) | (val & mask));
    if (EE_mico32_are_IRQs_enabled(irqstat))
        EE_mico32_enableIRQ();
} 
     
/**
	@brief 			This function reads irqMask register
	@param base 	Pointer to GPIO register structure
	@return 		irqMask register
*/   
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_irqMask(MicoGPIO_t* base)
{ 
    return EE_hal_word_inversion(base->irqMask);
} 
 
/**
	@brief 			This function writes irqMask register
	@param base 	Pointer to GPIO register structure
	@param val		desired value for irqMask register
*/  
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_irqMask(MicoGPIO_t* base, unsigned int val)
{ 
	base->irqMask = EE_hal_word_inversion(val);
}       
    
/**
	@brief 			This function writes a bit in irqMask register
	@param base 	Pointer to GPIO register structure
	@param val		desired value for the bit to be modified
	@param numbit	number of the bit
*/   
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_irqMask(MicoGPIO_t* base, unsigned int val, unsigned char numbit)
{ 
    unsigned int mask = (1 << numbit);
    unsigned int irqMask = EE_hal_word_inversion(base->irqMask);
	
    if(val)
        base->irqMask = EE_hal_word_inversion(irqMask | mask);
    else
        base->irqMask = EE_hal_word_inversion(irqMask & (~mask));
} 
  
/**
	@brief 			This function writes irqMask register with a mask 
	@param base 	Pointer to GPIO register structure
	@param val		value to be masked
	@param mask		mask to be used
*/     
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_irqMask(MicoGPIO_t* base, unsigned int val, unsigned int mask)
{ 
    unsigned int irqMask = EE_hal_word_inversion(base->irqMask);

	base->irqMask = EE_hal_word_inversion((irqMask & (~mask)) | (val & mask));
} 
        
/**
	@brief 			This function reads edgeCapture register
	@param base 	Pointer to GPIO register structure
	@return			edgeCapture register
*/	
 __INLINE__ unsigned int __ALWAYS_INLINE__ EE_hal_gpio_read_edgeCapture(MicoGPIO_t* base)
{ 
    return EE_hal_word_inversion(base->edgeCapture);
} 

/**
	@brief 			This function writes edgeCapture register
	@param base 	Pointer to GPIO register structure
	@param val		desired value for the edgeCapture register
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_edgeCapture(MicoGPIO_t* base, unsigned int val)
{ 
    base->edgeCapture = EE_hal_word_inversion(val);
} 

/**
	@brief 			This function writes a bit in edgeCapture register
	@param base 	Pointer to GPIO register structure
	@param val		desired value for the bit to be modified
	@param numbit	number of the bit
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_bit_edgeCapture(MicoGPIO_t* base, unsigned int val, unsigned char numbit)
{ 
    unsigned int mask = (1 << numbit);
    unsigned int edgeCapture = EE_hal_word_inversion(base->edgeCapture);
	
    if(val)
        base->edgeCapture = EE_hal_word_inversion(edgeCapture | mask);
    else
        base->edgeCapture = EE_hal_word_inversion(edgeCapture & (~mask));
} 

/**
	@brief 			This function writes edgeCapture register with a mask 
	@param base 	Pointer to GPIO register structure
	@param val		value to be masked
	@param mask		mask to be used
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_write_mask_edgeCapture(MicoGPIO_t *base, unsigned int val, unsigned int mask)
{ 
    unsigned int edgeCapture = EE_hal_word_inversion(base->edgeCapture); 
	base->edgeCapture = EE_hal_word_inversion((edgeCapture & (~mask)) | (val & mask));
}

/**
	@brief 			This function enables GPIO IRQ 
	@param gpio_sp 	Pointer to GPIO driver structure
	@param irq_mode	IRQ mode specified in system_conf.h
	@param ch		GPIO channel
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_enable_IRQ(EE_gpio_st *gpio_sp, int irq_mode, unsigned int ch)
{
    if(ch!=0 && irq_mode!=0) {
        EE_hal_gpio_handler_setup(gpio_sp);
        mico32_enable_irq(gpio_sp->irqf);
    } else {
        mico32_disable_irq(gpio_sp->irqf);
    }
    EE_hal_gpio_write_irqMask(gpio_sp->base, ch);
}

/**
	@brief 			This function disables GPIO IRQ 
	@param gpio_sp 	Pointer to GPIO driver structure
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_disable_IRQ(EE_gpio_st *gpio_sp)
{
    mico32_disable_irq(gpio_sp->irqf);
    EE_hal_gpio_write_irqMask(gpio_sp->base, 0);
}

/**
	@brief 			This function sets IRQ callback
	@param gpio_sp 	Pointer to GPIO driver structure
	@param cbk		pointer to the callback
*/ 
__INLINE__ void __ALWAYS_INLINE__ EE_hal_gpio_set_IRQ_callback(EE_gpio_st* gpio_sp, EE_ISR_callback cbk)
{
    gpio_sp->cbk = cbk;
}


#ifdef EE_GPIO1_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO1_NAME_UC, EE_GPIO1_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO1_NAME_UC, EE_GPIO1_NAME_LC)
#endif

#ifdef EE_GPIO2_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO2_NAME_UC, EE_GPIO2_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO2_NAME_UC, EE_GPIO2_NAME_LC)
#endif

#ifdef EE_GPIO3_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO3_NAME_UC, EE_GPIO3_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO3_NAME_UC, EE_GPIO3_NAME_LC)
#endif

#ifdef EE_GPIO4_NAME_UC
DECLARE_STRUCT_GPIO(EE_GPIO4_NAME_UC, EE_GPIO4_NAME_LC)
DECLARE_FUNC_GPIO(EE_GPIO4_NAME_UC, EE_GPIO4_NAME_LC)
#endif

/**
	@brief 			This function is used inside the interrupt handler to determinate
					the GPIO structure associated with the given IRQ level
	@param level 	IRQ level
    @return 		the pointer of the structure associated with the given IRQ level
*/ 
__DECLARE_INLINE__ EE_gpio_st *EE_get_gpio_st_from_level(int level);
__INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
{
	#ifdef EE_GPIO1_NAME_UC
	if (level == EE_IRQ_NAME(EE_GPIO1_NAME_UC))
        return & EE_ST_NAME(EE_GPIO1_NAME_LC);
	#endif
	#ifdef EE_GPIO2_NAME_UC
	if (level == EE_IRQ_NAME(EE_GPIO2_NAME_UC))
        return & EE_ST_NAME(EE_GPIO2_NAME_LC);
	#endif
	#ifdef EE_GPIO3_NAME_UC
	if (level == EE_IRQ_NAME(EE_GPIO3_NAME_UC))
        return & EE_ST_NAME(EE_GPIO3_NAME_LC);
	#endif
	#ifdef EE_GPIO4_NAME_UC
	if (level == EE_IRQ_NAME(EE_GPIO4_NAME_UC))
        return & EE_ST_NAME(EE_GPIO4_NAME_LC);
	#endif
    return (EE_gpio_st *)0;
}

// #ifndef EE_GPIO2_NAME_UC
// /* If there is only one component of this kind, no test is done */
// __INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
// {
    // return & EE_ST_NAME(EE_GPIO1_NAME_LC);
// }
// #elif ! defined(EE_GPIO3_NAME_UC)
// __INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
// {
    // if (level == EE_IRQ_NAME(EE_GPIO1_NAME_UC))
        // return & EE_ST_NAME(EE_GPIO1_NAME_LC);
	// return & EE_ST_NAME(EE_GPIO2_NAME_LC);
// }
// #elif ! defined(EE_GPIO4_NAME_UC)
// __INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
// {
    // if (level == EE_IRQ_NAME(EE_GPIO1_NAME_UC))
        // return & EE_ST_NAME(EE_GPIO1_NAME_LC);
    // if(level == EE_IRQ_NAME(EE_GPIO2_NAME_UC))
        // return & EE_ST_NAME(EE_GPIO2_NAME_LC);
    // return & EE_ST_NAME(EE_GPIO3_NAME_LC);
// }
// #else // #ifndef EE_GPIO4_NAME_UC
// __INLINE__ EE_gpio_st * __ALWAYS_INLINE__ EE_get_gpio_st_from_level(int level)
// {
    // if (level == EE_IRQ_NAME(EE_GPIO1_NAME_UC))
        // return & EE_ST_NAME(EE_GPIO1_NAME_LC);
    // if(level == EE_IRQ_NAME(EE_GPIO2_NAME_UC))
        // return & EE_ST_NAME(EE_GPIO2_NAME_LC);
    // if(level == EE_IRQ_NAME(EE_GPIO3_NAME_UC))
        // return & EE_ST_NAME(EE_GPIO3_NAME_LC);
    // return & EE_ST_NAME(EE_GPIO4_NAME_LC);
// }
// #endif /* #ifndef EE_GPIO_NAME2_UC */

#endif //__INCLUDE_EEMCUMICO32_GPIO_H__
