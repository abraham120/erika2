/*****************************************************
 CPU12ISR.c - interrupt/exception handlers for HCS12    
 ----------------------------------------------------
  
 *****************************************************/

#ifndef __CPU12ISR_H_
#define __CPU12ISR_H_

#include "hidef.h" /* this file declares symbols user by the CodeWarrior environment */
#include <ee.h>
#include <ee_irq.h>
#include "test/assert/inc/ee_assert.h"

EE_S12_ISR void SpuriousISR(void);

EE_S12_ISR void CPU12PortADISR(void);

EE_S12_ISR void CPU12ReservedISR(void);

EE_S12_ISR void CPU12APIISR(void);

EE_S12_ISR void CPU12ADCCompareISR(void);

EE_S12_ISR void CPU12LVIISR(void);

EE_S12_ISR void CPU12PortPISR(void);

EE_S12_ISR void CPU12CAN0TxISR(void);

EE_S12_ISR void CPU12CAN0RxISR(void);

EE_S12_ISR void CPU12CAN0ErrISR(void);

EE_S12_ISR void CPU12CAN0WakeISR(void);

EE_S12_ISR void CPU12FlashCmdISR(void);

EE_S12_ISR void CPU12FlashErrISR(void);

EE_S12_ISR void CPU12SPI2ISR(void);

EE_S12_ISR void CPU12SPI1ISR(void);

EE_S12_ISR void CPU12SCI2ISR(void);

EE_S12_ISR void  CPU12PLLLockISR(void);

EE_S12_ISR void CPU12OSCStatusISR(void);

EE_S12_ISR void CPU12ACMPISR(void);

EE_S12_ISR void CPU12PortJISR(void);

EE_S12_ISR void CPU12ADCISR(void);

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

EE_S12_ISR void  CPU12TimerCh0ISR(void);

EE_S12_ISR void CPU12RTIISR(void);

EE_S12_ISR void CPU12IRQISR(void);

EE_S12_ISR void CPU12XIRQISR(void);

EE_S12_ISR void CPU12SWIISR(void);

EE_S12_ISR void CPU12TrapISR(void);

EE_S12_ISR void CPU12COPISR(void);

EE_S12_ISR void CPU12ClockMonISR(void);

EE_S12_ISR void CPU12SystemReset(void);

#endif
