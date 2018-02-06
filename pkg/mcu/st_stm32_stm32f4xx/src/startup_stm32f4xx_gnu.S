/**
  ******************************************************************************
  * @file      startup_stm32f4xx.s
  * @author    MCD Application Team
  * @version   V1.0.0
  * @date      30-September-2011
  * @brief     STM32F4xx Devices vector table for Atollic TrueSTUDIO toolchain. 
  *            This module performs:
  *                - Set the initial SP
  *                - Set the initial PC == EE_cortex_mx_default_reset_ISR,
  *                - Set the vector table entries with the exceptions ISR address
  *                - Configure the clock system and the external SRAM mounted on 
  *                  STM324xG-EVAL board to be used as data memory (optional, 
  *                  to be enabled by user)
  *                - Branches to main in the C library (which eventually
  *                  calls main()).
  *            After Reset the Cortex-M4 processor is in Thread mode,
  *            priority is Privileged, and the Stack is set to Main.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */
    
#include "eecfg.h"	/* Configurable by RT-Druid */
	
	.syntax unified
	.cpu cortex-m4
	.arch armv7e-m
 // .fpu softvfp

    .section .stack
    .align 3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0xc00
#endif
    .globl    __StackTop
    .globl    __StackLimit
__StackLimit:
    .space    Stack_Size
    .size __StackLimit, . - __StackLimit
__StackTop:
    .size __StackTop, . - __StackTop

    .section .heap
    .align 3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0x100
#endif
    .globl    __HeapBase
    .globl    __HeapLimit
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif
    .size __HeapBase, . - __HeapBase
__HeapLimit:
    .size __HeapLimit, . - __HeapLimit

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

	.section  .text.EE_cortex_mx_default_reset_ISR
    .thumb
    .thumb_func
    .align 2	
	.weak  EE_cortex_mx_default_reset_ISR
	.global  EE_cortex_mx_default_ISR
	.type  EE_cortex_mx_default_reset_ISR, %function
EE_cortex_mx_default_reset_ISR:  
/* Copy the data segment initializers from flash to SRAM */  
  movs  r1, #0
  b  LoopCopyDataInit

CopyDataInit:
  ldr  r3, =__etext
  ldr  r3, [r3, r1]
  str  r3, [r0, r1]
  adds  r1, r1, #4
    
LoopCopyDataInit:
  ldr  r0, =__data_start__
  ldr  r3, =__data_end__
  adds  r2, r0, r1
  cmp  r2, r3
  bcc  CopyDataInit
  ldr  r2, =__bss_start__
  b  LoopFillZerobss
/* Zero fill the bss segment. */  
FillZerobss:
  movs  r3, #0
  str  r3, [r2], #4
    
LoopFillZerobss:
  ldr  r3, = __bss_end__
  cmp  r2, r3
  bcc  FillZerobss

/* Call the clock system intitialization function.*/
/*#ifndef __NO_SYSTEM_INIT
    bl    SystemInit
#endif*/
  
/* Call static constructors */
    /******* bl __libc_init_array ******/

/* Call the application's entry point.*/
	bl  main
	bx  lr  
	.pool
	.size  EE_cortex_mx_default_reset_ISR, .-EE_cortex_mx_default_reset_ISR

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None     
 * @retval None       
*/
    .section  .text.EE_cortex_mx_default_ISR,"ax",%progbits
	.align 1
	.thumb_func
	.type EE_cortex_mx_default_ISR, %function
	
EE_cortex_mx_default_ISR:
#ifdef	DEBUG
	bkpt	#0x00
#endif	/* DEBUG */
Infinite_Loop:
	b  Infinite_Loop
	.size  EE_cortex_mx_default_ISR, .-EE_cortex_mx_default_ISR


/******************************************************************************
*																			
* This is the code that gets called when the processor receives a BUS FAULT 
* exception.
*
*******************************************************************************/
#ifdef	__AUTOSAR_R4_0__
	.section  .text.EE_cortex_mx_as_bus_fault_ISR,"ax",%progbits
	.align 1
	.thumb_func
	.type EE_cortex_mx_as_bus_fault_ISR, %function
EE_cortex_mx_as_bus_fault_ISR:
#ifdef	DEBUG
	bkpt	#0x00
#endif	/* DEBUG */
	b	EE_cortex_mx_as_bus_fault_ISR
	.size  EE_cortex_mx_as_bus_fault_ISR, .-EE_cortex_mx_as_bus_fault_ISR
#endif	/* __AUTOSAR_R4_0__ */

/******************************************************************************
*
* This is the code that gets called when the processor receives a HARD FAULT
* exception.
*
*******************************************************************************/
#ifdef	__AUTOSAR_R4_0__
	.section  .text.EE_cortex_mx_as_hard_fault_ISR,"ax",%progbits
	.align 1
	.thumb_func
	.type EE_cortex_mx_as_hard_fault_ISR, %function	
EE_cortex_mx_as_hard_fault_ISR:
#ifdef	DEBUG
	bkpt	#0x00
#endif	/* DEBUG */
	b	EE_cortex_mx_as_hard_fault_ISR
	.size  EE_cortex_mx_as_hard_fault_ISR, .-EE_cortex_mx_as_hard_fault_ISR
#endif	/* __AUTOSAR_R4_0__ */

/******************************************************************************
*
* This is the code used to provide _exit
*
*******************************************************************************/
	.section  .text._exit,"ax",%progbits
	.align 1
	.thumb_func
	.weak _exit
	.type _exit, %function	
_exit:
#ifdef	DEBUG
	bkpt	#0x00
#endif	/* DEBUG */
	b	_exit
	.size  _exit, .-_exit

/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
	.section  .isr_vector,"a",%progbits
	.align 2
	.type  __isr_vector, %object
	.global  __isr_vector
    
__isr_vector:
	.word  __StackTop
	.word  EE_cortex_mx_default_reset_ISR
	.word  EE_CORTEX_MX_NMI_ISR
	.word  EE_CORTEX_MX_HARD_FAULT_ISR
	.word  EE_CORTEX_MX_MPU_FAULT_ISR
	.word  EE_CORTEX_MX_BUS_FAULT_ISR
	.word  EE_CORTEX_MX_USAGE_FAULT_ISR
	.word  0
	.word  0
	.word  0
	.word  0
	.word  EE_cortex_mx_svc_ISR
	.word  EE_CORTEX_MX_DEBUG_MONITOR_ISR
	.word  0
	.word  EE_cortex_mx_pendsv_ISR
	.word  EE_CORTEX_MX_SYSTICK_ISR

	/* External Interrupts */
	.word     EE_CORTEX_MX_WWDG_ISR               /* Window WatchDog              */                                        
	.word     EE_CORTEX_MX_PVD_ISR                /* PVD through EXTI Line detection */                        
	.word     EE_CORTEX_MX_TAMP_STAMP_ISR         /* Tamper and TimeStamps through the EXTI line */            
	.word     EE_CORTEX_MX_RTC_WKUP_ISR           /* RTC Wakeup through the EXTI line */                      
	.word     EE_CORTEX_MX_FLASH_ISR              /* FLASH                        */                                          
	.word     EE_CORTEX_MX_RCC_ISR                /* RCC                          */                                            
	.word     EE_CORTEX_MX_EXTI0_ISR              /* EXTI Line0                   */                        
	.word     EE_CORTEX_MX_EXTI1_ISR              /* EXTI Line1                   */                          
	.word     EE_CORTEX_MX_EXTI2_ISR              /* EXTI Line2                   */                          
	.word     EE_CORTEX_MX_EXTI3_ISR              /* EXTI Line3                   */                          
	.word     EE_CORTEX_MX_EXTI4_ISR              /* EXTI Line4                   */                          
	.word     EE_CORTEX_MX_DMA1_STREAM0_ISR       /* DMA1 Stream 0                */
	.word     EE_CORTEX_MX_DMA1_STREAM1_ISR       /* DMA1 Stream 1                */
	.word     EE_CORTEX_MX_DMA1_STREAM2_ISR       /* DMA1 Stream 2                */
	.word     EE_CORTEX_MX_DMA1_STREAM3_ISR       /* DMA1 Stream 3                */
	.word     EE_CORTEX_MX_DMA1_STREAM4_ISR       /* DMA1 Stream 4                */
	.word     EE_CORTEX_MX_DMA1_STREAM5_ISR       /* DMA1 Stream 5                */
	.word     EE_CORTEX_MX_DMA1_STREAM6_ISR       /* DMA1 Stream 6                */
	.word     EE_CORTEX_MX_ADC_ISR                /* ADC1, ADC2 and ADC3s         */                   
	.word     EE_CORTEX_MX_CAN1_TX_ISR            /* CAN1 TX                      */                         
	.word     EE_CORTEX_MX_CAN1_RX0_ISR           /* CAN1 RX0                     */                          
	.word     EE_CORTEX_MX_CAN1_RX1_ISR           /* CAN1 RX1                     */                          
	.word     EE_CORTEX_MX_CAN1_SCE_ISR           /* CAN1 SCE                     */                          
	.word     EE_CORTEX_MX_EXTI9_5_ISR            /* External Line[9:5]s          */                          
	.word     EE_CORTEX_MX_TIM1_BRK_TIM9_ISR      /* TIM1 Break and TIM9          */         
	.word     EE_CORTEX_MX_TIM1_UP_TIM10_ISR      /* TIM1 Update and TIM10        */         
	.word     EE_CORTEX_MX_TIM1_TRG_COM_TIM11_ISR /* TIM1 Trigger and Commutation and TIM11 */
	.word     EE_CORTEX_MX_TIM1_CC_ISR            /* TIM1 Capture Compare         */                          
	.word     EE_CORTEX_MX_TIM2_ISR               /* TIM2                         */                   
	.word     EE_CORTEX_MX_TIM3_ISR               /* TIM3                         */                   
	.word     EE_CORTEX_MX_TIM4_ISR               /* TIM4                         */                   
	.word     EE_CORTEX_MX_I2C1_EV_ISR            /* I2C1 Event                   */                          
	.word     EE_CORTEX_MX_I2C1_ER_ISR            /* I2C1 Error                   */                          
	.word     EE_CORTEX_MX_I2C2_EV_ISR            /* I2C2 Event                   */                          
	.word     EE_CORTEX_MX_I2C2_ER_ISR            /* I2C2 Error                   */                            
	.word     EE_CORTEX_MX_SPI1_ISR               /* SPI1                         */                   
	.word     EE_CORTEX_MX_SPI2_ISR               /* SPI2                         */                   
	.word     EE_CORTEX_MX_USART1_ISR             /* USART1                       */                   
	.word     EE_CORTEX_MX_USART2_ISR             /* USART2                       */                   
	.word     EE_CORTEX_MX_USART3_ISR             /* USART3                       */                   
	.word     EE_CORTEX_MX_EXTI15_10_ISR          /* External Line[15:10]s        */                          
	.word     EE_CORTEX_MX_RTC_Alarm_ISR          /* RTC Alarm (A and B) through EXTI Line */                 
	.word     EE_CORTEX_MX_OTG_FS_WKUP_ISR        /* USB OTG FS Wakeup through EXTI line */                       
	.word     EE_CORTEX_MX_TIM8_BRK_TIM12_ISR     /* TIM8 Break and TIM12         */         
	.word     EE_CORTEX_MX_TIM8_UP_TIM13_ISR      /* TIM8 Update and TIM13        */         
	.word     EE_CORTEX_MX_TIM8_TRG_COM_TIM14_ISR /* TIM8 Trigger and Commutation and TIM14 */
	.word     EE_CORTEX_MX_TIM8_CC_ISR            /* TIM8 Capture Compare         */                          
	.word     EE_CORTEX_MX_DMA1_Stream7_ISR       /* DMA1 Stream7                 */                          
	.word     EE_CORTEX_MX_FSMC_ISR               /* FSMC                         */                   
	.word     EE_CORTEX_MX_SDIO_ISR               /* SDIO                         */                   
	.word     EE_CORTEX_MX_TIM5_ISR               /* TIM5                         */                   
	.word     EE_CORTEX_MX_SPI3_ISR               /* SPI3                         */                   
	.word     EE_CORTEX_MX_UART4_ISR              /* UART4                        */                   
	.word     EE_CORTEX_MX_UART5_ISR              /* UART5                        */                   
	.word     EE_CORTEX_MX_TIM6_DAC_ISR           /* TIM6 and DAC1&2 underrun errors */                   
	.word     EE_CORTEX_MX_TIM7_ISR               /* TIM7                         */
	.word     EE_CORTEX_MX_DMA2_STREAM0_ISR       /* DMA2 Stream 0                */
	.word     EE_CORTEX_MX_DMA2_STREAM1_ISR       /* DMA2 Stream 1                */
	.word     EE_CORTEX_MX_DMA2_STREAM2_ISR       /* DMA2 Stream 2                */
	.word     EE_CORTEX_MX_DMA2_STREAM3_ISR       /* DMA2 Stream 3                */
	.word     EE_CORTEX_MX_DMA2_STREAM4_ISR       /* DMA2 Stream 4                */
	.word     EE_CORTEX_MX_ETH_ISR                /* Ethernet                     */                   
	.word     EE_CORTEX_MX_ETH_WKUP_ISR           /* Ethernet Wakeup through EXTI line */                     
	.word     EE_CORTEX_MX_CAN2_TX_ISR            /* CAN2 TX                      */                          
	.word     EE_CORTEX_MX_CAN2_RX0_ISR           /* CAN2 RX0                     */                          
	.word     EE_CORTEX_MX_CAN2_RX1_ISR           /* CAN2 RX1                     */                          
	.word     EE_CORTEX_MX_CAN2_SCE_ISR           /* CAN2 SCE                     */                          
	.word     EE_CORTEX_MX_OTG_FS_ISR             /* USB OTG FS                   */                   
	.word     EE_CORTEX_MX_DMA2_STREAM5_ISR       /* DMA2 Stream 5                */
	.word     EE_CORTEX_MX_DMA2_STREAM6_ISR       /* DMA2 Stream 6                */
	.word     EE_CORTEX_MX_DMA2_STREAM7_ISR       /* DMA2 Stream 7                */
	.word     EE_CORTEX_MX_USART6_ISR             /* USART6                       */                    
	.word     EE_CORTEX_MX_I2C3_EV_ISR            /* I2C3 event                   */                          
	.word     EE_CORTEX_MX_I2C3_ER_ISR            /* I2C3 error                   */                          
	.word     EE_CORTEX_MX_OTG_HS_EP1_OUT_ISR     /* USB OTG HS End Point 1 Out   */                   
	.word     EE_CORTEX_MX_OTG_HS_EP1_IN_ISR      /* USB OTG HS End Point 1 In    */                   
	.word     EE_CORTEX_MX_OTG_HS_WKUP_ISR        /* USB OTG HS Wakeup through EXTI */                         
	.word     EE_CORTEX_MX_OTG_HS_ISR             /* USB OTG HS                   */                   
	.word     EE_CORTEX_MX_DCMI_ISR               /* DCMI                         */                   
	.word     EE_CORTEX_MX_CRYP_ISR               /* CRYP crypto                  */                   
	.word     EE_CORTEX_MX_HASH_RNG_ISR           /* Hash and Rng                 */
	.word     EE_CORTEX_MX_FPU_ISR                /* FPU                          */

	.size  __isr_vector, .-__isr_vector							 
							 
/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the EE_cortex_mx_default_ISR. 
* As they are weak aliases, any function with the same name will override 
* this definition.
* 
*******************************************************************************/


   .weak      EE_CORTEX_MX_NMI_ISR
   .thumb_set EE_CORTEX_MX_NMI_ISR,EE_cortex_mx_default_ISR
  
   .weak      EE_CORTEX_MX_HARD_FAULT_ISR
#ifdef	__AUTOSAR_R4_0__  
   .thumb_set EE_CORTEX_MX_HARD_FAULT_ISR,EE_cortex_mx_as_hard_fault_ISR
#else
   .thumb_set EE_CORTEX_MX_HARD_FAULT_ISR,EE_cortex_mx_default_ISR
#endif /*__AUTOSAR_R4_0__*/
  
   .weak      EE_CORTEX_MX_MPU_FAULT_ISR
   .thumb_set EE_CORTEX_MX_MPU_FAULT_ISR,EE_cortex_mx_default_ISR
  
   .weak      EE_CORTEX_MX_BUS_FAULT_ISR
#ifdef	__AUTOSAR_R4_0__  
   .thumb_set EE_CORTEX_MX_BUS_FAULT_ISR,EE_cortex_mx_as_bus_fault_ISR
#else
   .thumb_set EE_CORTEX_MX_BUS_FAULT_ISR,EE_cortex_mx_default_ISR
#endif /*__AUTOSAR_R4_0__*/
   
   .weak      EE_CORTEX_MX_USAGE_FAULT_ISR
   .thumb_set EE_CORTEX_MX_USAGE_FAULT_ISR,EE_cortex_mx_default_ISR

   .weak      EE_cortex_mx_svc_ISR
   .thumb_set EE_cortex_mx_svc_ISR,EE_cortex_mx_default_ISR

   .weak      EE_CORTEX_MX_DEBUG_MONITOR_ISR
   .thumb_set EE_CORTEX_MX_DEBUG_MONITOR_ISR,EE_cortex_mx_default_ISR

   .weak      EE_cortex_mx_pendsv_ISR
   .thumb_set EE_cortex_mx_pendsv_ISR,EE_cortex_mx_default_ISR

   .weak      EE_CORTEX_MX_SYSTICK_ISR
   .thumb_set EE_CORTEX_MX_SYSTICK_ISR,EE_cortex_mx_default_ISR              
  
   .weak      EE_CORTEX_MX_WWDG_ISR                   
   .thumb_set EE_CORTEX_MX_WWDG_ISR,EE_cortex_mx_default_ISR      
                  
   .weak      EE_CORTEX_MX_PVD_ISR      
   .thumb_set EE_CORTEX_MX_PVD_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_TAMP_STAMP_ISR            
   .thumb_set EE_CORTEX_MX_TAMP_STAMP_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_RTC_WKUP_ISR                  
   .thumb_set EE_CORTEX_MX_RTC_WKUP_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_FLASH_ISR         
   .thumb_set EE_CORTEX_MX_FLASH_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_RCC_ISR      
   .thumb_set EE_CORTEX_MX_RCC_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_EXTI0_ISR         
   .thumb_set EE_CORTEX_MX_EXTI0_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_EXTI1_ISR         
   .thumb_set EE_CORTEX_MX_EXTI1_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_EXTI2_ISR         
   .thumb_set EE_CORTEX_MX_EXTI2_ISR,EE_cortex_mx_default_ISR 
                 
   .weak      EE_CORTEX_MX_EXTI3_ISR         
   .thumb_set EE_CORTEX_MX_EXTI3_ISR,EE_cortex_mx_default_ISR
                        
   .weak      EE_CORTEX_MX_EXTI4_ISR         
   .thumb_set EE_CORTEX_MX_EXTI4_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA1_STREAM0_ISR
   .thumb_set EE_CORTEX_MX_DMA1_STREAM0_ISR,EE_cortex_mx_default_ISR
         
   .weak      EE_CORTEX_MX_DMA1_STREAM1_ISR
   .thumb_set EE_CORTEX_MX_DMA1_STREAM1_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA1_STREAM2_ISR
   .thumb_set EE_CORTEX_MX_DMA1_STREAM2_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA1_STREAM3_ISR
   .thumb_set EE_CORTEX_MX_DMA1_STREAM3_ISR,EE_cortex_mx_default_ISR
                 
   .weak      EE_CORTEX_MX_DMA1_STREAM4_ISR
   .thumb_set EE_CORTEX_MX_DMA1_STREAM4_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA1_STREAM5_ISR
   .thumb_set EE_CORTEX_MX_DMA1_STREAM5_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA1_STREAM6_ISR
   .thumb_set EE_CORTEX_MX_DMA1_STREAM6_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_ADC_ISR      
   .thumb_set EE_CORTEX_MX_ADC_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_CAN1_TX_ISR   
   .thumb_set EE_CORTEX_MX_CAN1_TX_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_CAN1_RX0_ISR                  
   .thumb_set EE_CORTEX_MX_CAN1_RX0_ISR,EE_cortex_mx_default_ISR
                           
   .weak      EE_CORTEX_MX_CAN1_RX1_ISR                  
   .thumb_set EE_CORTEX_MX_CAN1_RX1_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_CAN1_SCE_ISR                  
   .thumb_set EE_CORTEX_MX_CAN1_SCE_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_EXTI9_5_ISR   
   .thumb_set EE_CORTEX_MX_EXTI9_5_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_TIM1_BRK_TIM9_ISR            
   .thumb_set EE_CORTEX_MX_TIM1_BRK_TIM9_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_TIM1_UP_TIM10_ISR            
   .thumb_set EE_CORTEX_MX_TIM1_UP_TIM10_ISR,EE_cortex_mx_default_ISR
      
   .weak      EE_CORTEX_MX_TIM1_TRG_COM_TIM11_ISR      
   .thumb_set EE_CORTEX_MX_TIM1_TRG_COM_TIM11_ISR,EE_cortex_mx_default_ISR
      
   .weak      EE_CORTEX_MX_TIM1_CC_ISR   
   .thumb_set EE_CORTEX_MX_TIM1_CC_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_TIM2_ISR            
   .thumb_set EE_CORTEX_MX_TIM2_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_TIM3_ISR            
   .thumb_set EE_CORTEX_MX_TIM3_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_TIM4_ISR            
   .thumb_set EE_CORTEX_MX_TIM4_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_I2C1_EV_ISR   
   .thumb_set EE_CORTEX_MX_I2C1_EV_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_I2C1_ER_ISR   
   .thumb_set EE_CORTEX_MX_I2C1_ER_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_I2C2_EV_ISR   
   .thumb_set EE_CORTEX_MX_I2C2_EV_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_I2C2_ER_ISR   
   .thumb_set EE_CORTEX_MX_I2C2_ER_ISR,EE_cortex_mx_default_ISR
                           
   .weak      EE_CORTEX_MX_SPI1_ISR            
   .thumb_set EE_CORTEX_MX_SPI1_ISR,EE_cortex_mx_default_ISR
                        
   .weak      EE_CORTEX_MX_SPI2_ISR            
   .thumb_set EE_CORTEX_MX_SPI2_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_USART1_ISR      
   .thumb_set EE_CORTEX_MX_USART1_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_USART2_ISR      
   .thumb_set EE_CORTEX_MX_USART2_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_USART3_ISR      
   .thumb_set EE_CORTEX_MX_USART3_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_EXTI15_10_ISR               
   .thumb_set EE_CORTEX_MX_EXTI15_10_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_RTC_Alarm_ISR               
   .thumb_set EE_CORTEX_MX_RTC_Alarm_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_OTG_FS_WKUP_ISR         
   .thumb_set EE_CORTEX_MX_OTG_FS_WKUP_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_TIM8_BRK_TIM12_ISR         
   .thumb_set EE_CORTEX_MX_TIM8_BRK_TIM12_ISR,EE_cortex_mx_default_ISR
         
   .weak      EE_CORTEX_MX_TIM8_UP_TIM13_ISR            
   .thumb_set EE_CORTEX_MX_TIM8_UP_TIM13_ISR,EE_cortex_mx_default_ISR
         
   .weak      EE_CORTEX_MX_TIM8_TRG_COM_TIM14_ISR      
   .thumb_set EE_CORTEX_MX_TIM8_TRG_COM_TIM14_ISR,EE_cortex_mx_default_ISR
      
   .weak      EE_CORTEX_MX_TIM8_CC_ISR   
   .thumb_set EE_CORTEX_MX_TIM8_CC_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA1_Stream7_ISR               
   .thumb_set EE_CORTEX_MX_DMA1_Stream7_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_FSMC_ISR            
   .thumb_set EE_CORTEX_MX_FSMC_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_SDIO_ISR            
   .thumb_set EE_CORTEX_MX_SDIO_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_TIM5_ISR            
   .thumb_set EE_CORTEX_MX_TIM5_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_SPI3_ISR            
   .thumb_set EE_CORTEX_MX_SPI3_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_UART4_ISR         
   .thumb_set EE_CORTEX_MX_UART4_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_UART5_ISR         
   .thumb_set EE_CORTEX_MX_UART5_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_TIM6_DAC_ISR                  
   .thumb_set EE_CORTEX_MX_TIM6_DAC_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_TIM7_ISR            
   .thumb_set EE_CORTEX_MX_TIM7_ISR,EE_cortex_mx_default_ISR
         
   .weak      EE_CORTEX_MX_DMA2_STREAM0_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM0_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_DMA2_STREAM1_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM1_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA2_STREAM2_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM2_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_DMA2_STREAM3_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM3_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_DMA2_STREAM4_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM4_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_ETH_ISR      
   .thumb_set EE_CORTEX_MX_ETH_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_ETH_WKUP_ISR                  
   .thumb_set EE_CORTEX_MX_ETH_WKUP_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_CAN2_TX_ISR   
   .thumb_set EE_CORTEX_MX_CAN2_TX_ISR,EE_cortex_mx_default_ISR
                           
   .weak      EE_CORTEX_MX_CAN2_RX0_ISR                  
   .thumb_set EE_CORTEX_MX_CAN2_RX0_ISR,EE_cortex_mx_default_ISR
                           
   .weak      EE_CORTEX_MX_CAN2_RX1_ISR                  
   .thumb_set EE_CORTEX_MX_CAN2_RX1_ISR,EE_cortex_mx_default_ISR
                           
   .weak      EE_CORTEX_MX_CAN2_SCE_ISR                  
   .thumb_set EE_CORTEX_MX_CAN2_SCE_ISR,EE_cortex_mx_default_ISR
                           
   .weak      EE_CORTEX_MX_OTG_FS_ISR      
   .thumb_set EE_CORTEX_MX_OTG_FS_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_DMA2_STREAM5_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM5_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA2_STREAM6_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM6_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DMA2_STREAM7_ISR
   .thumb_set EE_CORTEX_MX_DMA2_STREAM7_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_USART6_ISR      
   .thumb_set EE_CORTEX_MX_USART6_ISR,EE_cortex_mx_default_ISR
                        
   .weak      EE_CORTEX_MX_I2C3_EV_ISR   
   .thumb_set EE_CORTEX_MX_I2C3_EV_ISR,EE_cortex_mx_default_ISR
                        
   .weak      EE_CORTEX_MX_I2C3_ER_ISR   
   .thumb_set EE_CORTEX_MX_I2C3_ER_ISR,EE_cortex_mx_default_ISR
                        
   .weak      EE_CORTEX_MX_OTG_HS_EP1_OUT_ISR         
   .thumb_set EE_CORTEX_MX_OTG_HS_EP1_OUT_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_OTG_HS_EP1_IN_ISR            
   .thumb_set EE_CORTEX_MX_OTG_HS_EP1_IN_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_OTG_HS_WKUP_ISR         
   .thumb_set EE_CORTEX_MX_OTG_HS_WKUP_ISR,EE_cortex_mx_default_ISR
            
   .weak      EE_CORTEX_MX_OTG_HS_ISR      
   .thumb_set EE_CORTEX_MX_OTG_HS_ISR,EE_cortex_mx_default_ISR
                  
   .weak      EE_CORTEX_MX_DCMI_ISR            
   .thumb_set EE_CORTEX_MX_DCMI_ISR,EE_cortex_mx_default_ISR
                     
   .weak      EE_CORTEX_MX_CRYP_ISR            
   .thumb_set EE_CORTEX_MX_CRYP_ISR,EE_cortex_mx_default_ISR
               
   .weak      EE_CORTEX_MX_HASH_RNG_ISR                  
   .thumb_set EE_CORTEX_MX_HASH_RNG_ISR,EE_cortex_mx_default_ISR   

   .weak      EE_CORTEX_MX_FPU_ISR                  
   .thumb_set EE_CORTEX_MX_FPU_ISR,EE_cortex_mx_default_ISR  
   
