/*****************************************************
 HCS12vectors.c - HCS12 vector table     
 ----------------------------------------------------
  
 *****************************************************/

#include "hidef.h" /* this file declares symbols user by the CodeWarrior environment */
#include "CPU12ISRs.h"

void (* near const vectors[])(void) @ 0xFF10 = //void (* near const vectors[])(void) = 
  {
    SpuriousISR,	      /* Spurious Interrupt, Vector Base + $10 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $12 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $14 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $16 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $18 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $1a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $1c */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $1e */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $20 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $22 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $24 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $26 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $28 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $2a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $2c */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $2e */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $30 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $32 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $34 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $36 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $38 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $3a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $3c */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $3e */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $40 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $42 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $44 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $46 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $48 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $4a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $4c */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $4e */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $50 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $52 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $54 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $56 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $58 */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $5a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $5c */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $5e */
    XSRAM20KISR,        /* XSRAM20K Access Violation, Vector Base + $60 */
    CPU12XGSWErrorISR,  /* XGATE Software Error Interrupt, Vector Base + $62 */
    CPU12XGSwTrig7ISR,  /* XGATE Software Trigger 7, Vector Base + $64 */
    CPU12XGSwTrig6ISR,  /* XGATE Software Trigger 6, Vector Base + $66 */
    CPU12XGSwTrig5ISR,  /* XGATE Software Trigger 5, Vector Base + $68 */
    CPU12XGSwTrig4ISR,  /* XGATE Software Trigger 4, Vector Base + $6a */
    CPU12XGSwTrig3ISR,  /* XGATE Software Trigger 3, Vector Base + $6c */
    CPU12XGSwTrig2ISR,  /* XGATE Software Trigger 2, Vector Base + $6e */
    CPU12XGSwTrig1ISR,  /* XGATE Software Trigger 1, Vector Base + $70 */
    CPU12XGSwTrig0ISR,  /* XGATE Software Trigger 0, Vector Base + $72 */
    CPU12PIT3ISR,	      /* Periodic Interrupt Timer 3, Vector Base + $74 */
    CPU12PIT2ISR,	      /* Periodic Interrupt Timer 2, Vector Base + $76 */
    CPU12PIT1ISR,	      /* Periodic Interrupt Timer 1, Vector Base + $78 */
    CPU12PIT0ISR,	      /* Periodic Interrupt Timer 0, Vector Base + $7a */
    CPU12ReservedISR,	  /* Reserved, Vector Base + $7c */
    CPU12APIISR,	      /* Autonomous Periodical interrupt API, Vector Base + $7e */
    CPU12LVIISR,	      /* Low Voltage interrupt LVI, Vector Base + $80 */
    CPU12IIC1ISR,	      /* IIC1 Bus, Vector Base + $82 */
    CPU12SCI5ISR,	      /* SCI5, Vector Base + $84 */
    CPU12SCI4ISR,	      /* SCI4, Vector Base + $86 */
    CPU12SCI3ISR,	      /* SCI3, Vector Base + $88 */
    CPU12SCI2ISR,	      /* SCI2, Vector Base + $8a */
    CPU12PWMISR,	      /* PWM Emergency Shutdown, Vector Base + $8c */
    CPU12PortPISR,	    /* Port P Interrupt, Vector Base + $8e */
    CPU12CAN4TxISR,	    /* CAN4 transmit, Vector Base + $90 */
    CPU12CAN4RxISR,	    /* CAN4 receive, Vector Base + $92 */
    CPU12CAN4ErrISR,	  /* CAN4 errors, Vector Base + $94 */
    CPU12CAN4WakeISR,	  /* CAN4 wake-up, Vector Base + $96 */
    CPU12CAN3TxISR,	    /* CAN3 transmit, Vector Base + $98 */
    CPU12CAN3RxISR,	    /* CAN3 receive, Vector Base + $9a */
    CPU12CAN3ErrISR,	  /* CAN3 errors, Vector Base + $9c */
    CPU12CAN3WakeISR,	  /* CAN3 wake-up, Vector Base + $9e */
    CPU12CAN2TxISR,	    /* CAN2 transmit, Vector Base + $a0 */
    CPU12CAN2RxISR,	    /* CAN2 receive, Vector Base + $a2 */
    CPU12CAN2ErrISR,	  /* CAN2 errors, Vector Base + $a4 */
    CPU12CAN2WakeISR,	  /* CAN2 wake-up, Vector Base + $a6 */
    CPU12CAN1TxISR,	    /* CAN1 transmit, Vector Base + $a8 */
    CPU12CAN1RxISR,	    /* CAN1 receive, Vector Base + $aa */
    CPU12CAN1ErrISR,	  /* CAN1 errors, Vector Base + $ac */
    CPU12CAN1WakeISR,	  /* CAN1 wake-up, Vector Base + $ae */
    CPU12CAN0TxISR,	    /* CAN0 transmit, Vector Base + $b0 */
    CPU12CAN0RxISR,	    /* CAN0 receive, Vector Base + $b2 */
    CPU12CAN0ErrISR,	  /* CAN0 errors, Vector Base + $b4 */
    CPU12CAN0WakeISR,	  /* CAN0 wake-up, Vector Base + $b6 */
    CPU12FlashISR,	    /* Flash, Vector Base + $b8 */
    CPU12EEPROMISR,	    /* EEPROM, Vector Base + $ba */
    CPU12SPI2ISR,	      /* SPI2, Vector Base + $bc */
    CPU12SPI1ISR,	      /* SPI1, Vector Base + $be */
    CPU12IIC0ISR,	      /* IIC0 Bus, Vector Base + $c0 */
    CPU12ReservedISR,   /* Reserved, Vector Base + $c2 */
    CPU12SRCSGISR,      /* CRG Self Clock Mode, Vector Base + $c4 */
    CPU12PLLLockISR,    /* CRG PLL lock, Vector Base + $c6 */
    CPU12PACCBOVISR,    /* Pulse Accumulator B Overflow, Vector Base + $c8 */
    CPU12MDCUISR,       /* Modulus Down Counter underflow, Vector Base + $ca */
    CPU12PortHISR,      /* Port H, Vector Base + $cc */
    CPU12PortJISR,      /* Port J, Vector Base + $ce */
    CPU12ATD1ISR,       /* ATD1, Vector Base + $d0 */
    CPU12ATD0ISR,       /* ATD0, Vector Base + $d2 */
    CPU12SCI1ISR,       /* SCI1, Vector Base + $d4 */
    CPU12SCI0ISR,       /* SCI0, Vector Base + $d6 */
    CPU12SPI0ISR,       /* SPI0, Vector Base + $d8 */
    CPU12PACCAIEISR,    /* Pulse accumulator input edge, Vector Base + $da */
    CPU12PACCAOVISR,    /* Pulse accumulator A overflow, Vector Base + $dc */
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
  
 
  
  