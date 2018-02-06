/*****************************************************
 HCS12vectors.c - HCS12 vector table     
 ----------------------------------------------------
  
 *****************************************************/

#include "hidef.h" /* this file declares symbols user by the CodeWarrior environment */
#include "CPU12ISRs.h"


void (* near const vectors[])(void) @ 0xFF80 = //void (* near const vectors[])(void) = 
  {
    SpuriousISR,	      /* Spurious Interrupt, Vector Base + $80 */
    CPU12PortADISR,	      /* Port AD, Vector Base + $82 */
    CPU12ADCCompareISR,   /* ADC compare, Vector Base + $84 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $86 */
    CPU12APIISR,	      /* API, Vector Base + $88 */
    CPU12LVIISR,	      /* LVI, Vector Base + $8a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $8c */
    CPU12PortPISR,	      /* Port P Interrupt, Vector Base + $8e */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $90 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $92 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $94 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $96 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $98 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $9a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $9c */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $9e */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $a0 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $a2 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $a4 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $a6 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $a8 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $aa */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $ac */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $ae */
    CPU12CAN0TxISR,	      /* CAN0 transmit, Vector Base + $b0 */
    CPU12CAN0RxISR,	      /* CAN0 receive, Vector Base + $b2 */
    CPU12CAN0ErrISR,	  /* CAN0 errors, Vector Base + $b4 */
    CPU12CAN0WakeISR,	  /* CAN0 wake-up, Vector Base + $b6 */
    CPU12FlashCmdISR,	  /* Flash cmd, Vector Base + $b8 */
    CPU12FlashErrISR,	  /* Flash err, Vector Base + $ba */
    CPU12SPI2ISR,	      /* SPI2, Vector Base + $bc */
    CPU12SPI1ISR,	      /* SPI1, Vector Base + $be */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $c0 */
    CPU12SCI2ISR,         /* SCI2, Vector Base + $c2 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $c4 */
    CPU12PLLLockISR,      /* CRG PLL lock, Vector Base + $c6 */
    CPU12OSCStatusISR,    /* Oscillator Status, Vector Base + $c8 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $ca */
    CPU12ACMPISR,         /* ACMP, Vector Base + $cc */
    CPU12PortJISR,        /* Port J, Vector Base + $ce */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $d0 */
    CPU12ADCISR,          /* ADC, Vector Base + $d2 */
    CPU12SCI1ISR,         /* SCI1, Vector Base + $d4 */
    CPU12SCI0ISR,         /* SCI0, Vector Base + $d6 */
    CPU12SPI0ISR,         /* SPI0, Vector Base + $d8 */
    CPU12PACCAIEISR,      /* Pulse accumulator input edge, Vector Base + $da */
    CPU12PACCAOVISR,      /* Pulse accumulator A overflow, Vector Base + $dc */
    CPU12TimerOVISR,    /* Enhanced Capture Timer overflow, Vector Base + $de */
    CPU12TimerCh7ISR,   /* Enhanced Capture Timer channel 7, Vector Base + $e0 */
    CPU12TimerCh6ISR,   /* Enhanced Capture Timer channel 6, Vector Base + $e2 */
    CPU12TimerCh5ISR,   /* Enhanced Capture Timer channel 5, Vector Base + $e4 */
    CPU12TimerCh4ISR,   /* Enhanced Capture Timer channel 4, Vector Base + $e6 */
    CPU12TimerCh3ISR,   /* Enhanced Capture Timer channel 3, Vector Base + $e8 */
    CPU12TimerCh2ISR,   /* Enhanced Capture Timer channel 2, Vector Base + $ea */
    CPU12TimerCh1ISR,   /* Enhanced Capture Timer channel 1, Vector Base + $ec */
    CPU12TimerCh0ISR,   /* Enhanced Capture Timer channel 0, Vector Base + $ee */
    CPU12RTIISR,        /* Real Time Interrupt, Vector Base + $f0 */
    CPU12IRQISR,        /* IRQ, Vector Base + $f2 */
    CPU12XIRQISR,       /* XIRQ, Vector Base + $f4 */
    CPU12SWIISR,        /* SWI, Vector Base + $f6 */
    CPU12TrapISR,       /* Unimplemented instruction trap, Vector Base + $f8 */
    CPU12COPISR,        /* COP Watchdog Reset, Vector Base + $fa */
    CPU12ClockMonISR,   /* Clock Monitor Reset, Vector Base + $fc */
    CPU12SystemReset    /* System Reset, Vector Base + $fe */ 
  };
  
 
  
  