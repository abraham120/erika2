/*****************************************************
 CPU12ISR.c - interrupt/exception handlers for HCS12    
 ----------------------------------------------------
  
 *****************************************************/

#ifndef __CPU12ISR_H_
#define __CPU12ISR_H_

#include "hidef.h" /* this file declares symbols user by the CodeWarrior environment */
#include "ee.h"
#include "ee_irq.h"
#include "test/assert/inc/ee_assert.h"
#include "mcu/hs12xs/inc/ee_timer.h"

/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED  // make sure this code is located in non banked  
interrupt void S12X_EntryPoint(void);
#pragma CODE_SEG DEFAULT                // back to the standard segment
*/

/* The functions called by the handlers can be allocated in the non banked area 
   The handlers are instead in _CX_CODE_INTERRUPT section because of COSMIC compatibility 
*/
/* #pragma CODE_SEG __NEAR_SEG NON_BANKED */

   
EE_S12_ISR void SpuriousISR(void);

EE_S12_ISR void CPU12ReservedISR(void);

EE_S12_ISR void XSRAM20KISR(void);

EE_S12_ISR void CPU12XGSWErrorISR(void);

EE_S12_ISR void CPU12XGSwTrig7ISR(void);

EE_S12_ISR void CPU12XGSwTrig6ISR(void);

EE_S12_ISR void CPU12XGSwTrig5ISR(void);

EE_S12_ISR void CPU12XGSwTrig4ISR(void);

EE_S12_ISR void CPU12XGSwTrig3ISR(void);

EE_S12_ISR void CPU12XGSwTrig2ISR(void);

EE_S12_ISR void CPU12XGSwTrig1ISR(void);

EE_S12_ISR void CPU12XGSwTrig0ISR(void);

EE_S12_ISR void CPU12PIT3ISR(void);

EE_S12_ISR void CPU12PIT2ISR(void);

EE_S12_ISR void CPU12PIT1ISR(void);

EE_S12_ISR void CPU12PIT0ISR(void);

EE_S12_ISR void CPU12APIISR(void);

EE_S12_ISR void CPU12LVIISR(void);

EE_S12_ISR void CPU12IIC1ISR(void);

EE_S12_ISR void CPU12SCI5ISR(void);

EE_S12_ISR void CPU12SCI4ISR(void);

EE_S12_ISR void CPU12SCI3ISR(void);

EE_S12_ISR void CPU12SCI2ISR(void);

EE_S12_ISR void CPU12PWMISR(void);

EE_S12_ISR void CPU12PortPISR(void);

EE_S12_ISR void CPU12CAN4TxISR(void);

EE_S12_ISR void CPU12CAN4RxISR(void);

EE_S12_ISR void CPU12CAN4ErrISR(void);

EE_S12_ISR void CPU12CAN4WakeISR(void);

EE_S12_ISR void CPU12CAN3TxISR(void);

EE_S12_ISR void CPU12CAN3RxISR(void);

EE_S12_ISR void CPU12CAN3ErrISR(void);

EE_S12_ISR void CPU12CAN3WakeISR(void);

EE_S12_ISR void CPU12CAN2TxISR(void);

EE_S12_ISR void CPU12CAN2RxISR(void);

EE_S12_ISR void CPU12CAN2ErrISR(void);

EE_S12_ISR void CPU12CAN2WakeISR(void);

EE_S12_ISR void CPU12CAN1TxISR(void);

EE_S12_ISR void CPU12CAN1RxISR(void);

EE_S12_ISR void CPU12CAN1ErrISR(void);

EE_S12_ISR void CPU12CAN1WakeISR(void);

EE_S12_ISR void CPU12CAN0TxISR(void);

EE_S12_ISR void CPU12CAN0RxISR(void);

EE_S12_ISR void CPU12CAN0ErrISR(void);

EE_S12_ISR void CPU12CAN0WakeISR(void);

EE_S12_ISR void CPU12FlashISR(void);

EE_S12_ISR void CPU12EEPROMISR(void);

EE_S12_ISR void CPU12SPI2ISR(void);

EE_S12_ISR void CPU12SPI1ISR(void);

EE_S12_ISR void CPU12IIC0ISR(void);

EE_S12_ISR void CPU12SRCSGISR(void);

EE_S12_ISR void CPU12PLLLockISR(void);

EE_S12_ISR void CPU12PACCBOVISR(void);

EE_S12_ISR void CPU12MDCUISR(void);

EE_S12_ISR void CPU12PortHISR(void);

EE_S12_ISR void CPU12PortJISR(void);

EE_S12_ISR void CPU12ATD1ISR(void);

EE_S12_ISR void CPU12ATD0ISR(void);

EE_S12_ISR void CPU12SCI1ISR(void);

EE_S12_ISR void CPU12SCI0ISR(void);

EE_S12_ISR void CPU12SPI0ISR(void);

EE_S12_ISR void CPU12PACCAIEISR(void);

EE_S12_ISR void CPU12PACCAOVISR(void);

EE_S12_ISR void CPU12TimerOVISR(void);

EE_S12_ISR void CPU12TimerCh7ISR(void);

EE_S12_ISR void CPU12TimerCh6ISR(void);

EE_S12_ISR void CPU12TimerCh5ISR(void);

EE_S12_ISR void CPU12TimerCh4ISR(void);

EE_S12_ISR void CPU12TimerCh3ISR(void);

EE_S12_ISR void CPU12TimerCh2ISR(void);

EE_S12_ISR void CPU12TimerCh1ISR(void);

EE_S12_ISR void CPU12TimerCh0ISR(void);

EE_S12_ISR void CPU12RTIISR(void);

EE_S12_ISR void CPU12IRQISR(void);

EE_S12_ISR void CPU12XIRQISR(void);

EE_S12_ISR void CPU12SWIISR(void);

EE_S12_ISR void CPU12TrapISR(void);

EE_S12_ISR void CPU12COPISR(void);

EE_S12_ISR void CPU12ClockMonISR(void);

EE_S12_ISR void CPU12SystemReset(void);

/* switch back to default segment */
/* #pragma CODE_SEG DEFAULT */

#endif
