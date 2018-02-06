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
 * Author: Gianluca Franchino 2012
 */
#ifndef __BM_CORTEX_M0__CONFIG_H__
#define __BM_CORTEX_M0__CONFIG_H__



#ifdef __LPC1227__

//#include "lpc12xx_libcfg.h"
#include "lpc12xx_libcfg_default.h"

#ifdef __BM_ERIKA__
#include "cpu/cortex_mx/inc/ee_cpu.h"

#define bm_are_IRQs_enabled(ie) EE_cortex_m0_are_IRQs_enabled(ie)
#define bm_disableIRQ() EE_cortex_m0_disableIRQ()
#define bm_enableIRQ() EE_cortex_m0_enableIRQ()

#elif defined __BM_EMBOS__

/*#define bm_are_IRQs_enabled(ie) EE_cortex_m0_are_IRQs_enabled(ie)*/
#define bm_disableIRQ()  OS_DI()
#define bm_enableIRQ()	OS_RestoreI()
#define bm_enableIRQ()	OS_ARM_ISRSetPrio()

#endif /*__BM_ERIKA__*/


#define isr1_handler PIOINT0_IRQHandler
#define isr2_handler PIOINT1_IRQHandler
#define isr2_act_task_handler PIOINT2_IRQHandler

#define bm_clear_isr1() NVIC_ClearPendingIRQ(EINT0_IRQn)
#define bm_clear_isr2() NVIC_ClearPendingIRQ(EINT1_IRQn)
#define bm_clear_isr2_act_task() NVIC_ClearPendingIRQ(EINT2_IRQn)

#define	bm_raise_isr1() NVIC_SetPendingIRQ(EINT0_IRQn)
#define	bm_raise_isr2() NVIC_SetPendingIRQ(EINT1_IRQn)
#define	bm_raise_isr2_act_task() NVIC_SetPendingIRQ(EINT2_IRQn)

#ifdef __BM_EMBOS__
/*Under embOS, only low priority interrupt can call OS routines. */
#define	bm_set_isr2_act_pri() NVIC_SetPriority(EINT2_IRQn, 0x3)
#else
#define	bm_set_isr2_act_pri() ((void)0)
#endif


#ifdef	BM_USE_UART

#define BM_UART_PORT LPC_UART0 /* LPC_UART0 */
#define BM_UART_RXD  IOCON_UART_RXD0_LOC0
#define BM_UART_TXD  IOCON_UART_TXD0_LOC0


__INLINE__ void bm_uart_init(void)
{
	UART_CFG_Type UARTConfigStruct;
    IOCON_PIO_CFG_Type PIO_mode;

    /*
     * Initialize UART pins
     */
    IOCON_StructInit(&PIO_mode);
    PIO_mode.type = BM_UART_RXD;
    IOCON_SetFunc(&PIO_mode);
    PIO_mode.type = BM_UART_TXD;
    IOCON_SetFunc(&PIO_mode);    
    if((LPC_UART0_TypeDef*)BM_UART_PORT == LPC_UART0){ 
        SYS_ResetPeripheral(SYS_PRESETCTRL_UART0_RST,DISABLE);
        SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_UART0, ENABLE); 
        SYS_SetUART0ClockDiv(1);
    }else{
        SYS_ResetPeripheral(SYS_PRESETCTRL_UART1_RST,DISABLE);
        SYS_ConfigAHBCLK(SYS_AHBCLKCTRL_UART1, ENABLE); 
        SYS_SetUART1ClockDiv(1);
    }
    UART_Init((LPC_UART_TypeDef*)BM_UART_PORT);

    UART_GetConfig((LPC_UART_TypeDef*)BM_UART_PORT, &UARTConfigStruct);
    UARTConfigStruct.baudrate = 115200;
    UARTConfigStruct.databits = UART_CFG_DATABIT_8;

    UART_SetConfig((LPC_UART_TypeDef*)BM_UART_PORT, &UARTConfigStruct);
    UART_ConfigTXD((LPC_UART_TypeDef*)BM_UART_PORT, ENABLE);
}


__INLINE__ void bm_uart_send_buffer(unsigned char *str, unsigned len)
{
	while (len--) {
		UART_Send((LPC_UART_TypeDef*)BM_UART_PORT, (uint8_t*)(str), 1, 
			UART_BLOKING_TIMEOUT);
		str++;
		while (!(UART_GetLineStatus((LPC_UART_TypeDef*)BM_UART_PORT) & 
			UART_LS_TX_EMPTY_ALL));
	}
}

#endif /*BM_USE_UART*/


#ifdef BM_USE_SYSTICK

#define USEC2TICK (1000000000.0/SystemCoreClock)
#define ticks_to_us(x) (x*USEC2TICK)

#define get_time_stamp() (SysTick->LOAD - SysTick->VAL) 

__INLINE__ void bm_time_stamp_init(void) 
{
	SysTick->LOAD = SysTick_LOAD_RELOAD_Msk - 1 ;
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |  SysTick_CTRL_ENABLE_Msk; 
}

#else

/*
 * Note: USEC2TICK depends on the system clock and on the timer
 *       initialization by bm_time_stamp_init(). 
 */
#define USEC2TICK (1000000000.0/SystemCoreClock)
#define ticks_to_us(x) (x*USEC2TICK)

#define get_time_stamp() (LPC_CT32B0->TC)

/*Initialize Timer0 (CT32B0)*/
__INLINE__ void bm_time_stamp_init(void) 
{
	TIM32_InitTypeDef TIM32_mode;
	TIM32_MATCHTypeDef TIM32_MATCH_mode;
	
#if defined (USE_USEC_VAL) /* 1 tick of the timer correspond to 1 usec*/
	TIM32_StructInit(TIM32_MODE_TIMER, &TIM32_mode);
#else /*Use TICK VAL: /* 1 tick of the timer correspond to 1 system tick*/
	TIM32_mode.PrescaleOption = TIM32_PRESCALE_TICKVAL;
	TIM32_mode.PrescaleValue = 1;
#endif	
	
	TIM32_Init(LPC_CT32B0, TIM32_MODE_TIMER, &TIM32_mode);
	TIM32_Cmd(LPC_CT32B0, ENABLE);
    	
}

#endif /*BM_USE_SYSTICK*/


__INLINE__ void bm_interrupt_init(void) 
{
	NVIC_SetPriority(EINT0_IRQn, 0);
	NVIC_EnableIRQ(EINT0_IRQn);
	
	NVIC_SetPriority(EINT1_IRQn, 0);
	NVIC_EnableIRQ(EINT1_IRQn);
	
	NVIC_SetPriority(EINT2_IRQn, 0);
	NVIC_EnableIRQ(EINT2_IRQn);
}


__INLINE__ void bm_hw_init(void) 
{
	 /*Setup the microcontroller system:
	-System Clock Setup;
	-PLL setup
	-Whatchdog setup (Default Watchdog = disabled)
	
	The system (core) clock frequency (CF):  CF= Fin * P /M;
	For Fin<15 P=4 and M=2
	If your board mounts a 12MHz cristal oscillator, i.e. Fin=12MHz,
	then the default system clock frequency is CF = 12 MHz * P /M= 24MHZ.

	See "system_LPC12xx.c" in <lpc12cc_cmsis_driver_library> 
	for further informations.
	To modify the system setup, use functions provided by 
	"lpc12xx_sysctrl.c" in <lpc12cc_cmsis_driver_library>
	*/
	/*
	SystemInit(); -> This routine is called by the startup module 
					(startup_LPC12xx.s) if the symbol 
					EE_DEF_SYS_INIT is defined.
	*/

	/*Init ISR1 and ISR2 interrupts */
	bm_interrupt_init();
	
	/*Initialize the timer for timestamping*/
	bm_time_stamp_init();
#ifdef	BM_USE_UART	
	/*Initialize the UART communication*/
	bm_uart_init();
#endif

}


#endif /*__LPC1227__*/

#endif /*__BM_CORTEX_M0__CONFIG_H__*/
