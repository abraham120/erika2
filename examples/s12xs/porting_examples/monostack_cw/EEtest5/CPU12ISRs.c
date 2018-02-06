/*****************************************************
 CPU12ISR.c - interrupt/exception handlers for HCS12    
 ----------------------------------------------------
  
 *****************************************************/

#include "hidef.h" /* this file declares symbols user by the CodeWarrior environment */

//#include "VTypes.h"
//#include "XDP512Regs.h"
//#include "Globals.h"
//#include "Car.h"
//#include "main.h"
#include "start12.h"		     /* to call the C-startup code */
#include "CPU12ISRs.h"
#include "mc9s12xs128.h"


/*
#pragma CODE_SEG __NEAR_SEG NON_BANKED  // make sure this code is located in non banked 

interrupt void S12X_EntryPoint(void) {
  COPCTL = 0;                 // disable the watchdog & clock monitor timers.
  REFDV = REFDVVal;           // set the REFDV register.
  SYNR = SYNRVal;             // set the SYNR register to give us a 40.0 MHz E-clock.
  asm nop;			              // nops required for bug in initial silicon.
  asm nop;
  asm nop;
  asm nop;
  while((CRGFLG&LOCKm) == 0); // wait here till the PLL is locked.  
  CLKSEL |= PLLSELm; 		      //  switch the bus clock to the PLL.

  asm jmp _Startup
}

#pragma CODE_SEG DEFAULT    // back to the standard segment
*/


/* The functions called by the handlers can be allocated in the non banked area 
   The handlers are instead in _CX_CODE_INTERRUPT section because of COSMIC compatibility 
*/
/* #pragma CODE_SEG __NEAR_SEG NON_BANKED */
  

/*************************************************************************************/

ISR2 ( SpuriousISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function SpuriousISR() */
 
 _asm("bgnd");
 
}	/* end SpuriousISR */

/*************************************************************************************/

ISR2 ( CPU12ReservedISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12ReservedISR() */
 
 _asm("bgnd");
 
}	/* end CPU12ReservedISR */

/*************************************************************************************/

ISR2 ( XSRAM20KISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function XSRAM20KISR() */
 
 _asm("bgnd");
 
}	/* end XSRAM20KISR */

/*************************************************************************************/

ISR2 ( CPU12XGSWErrorISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSWErrorISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSWErrorISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig7ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSwTrig7ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig7ISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig6ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSwTrig6ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig6ISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig5ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSWErrorISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig5ISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig4ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSwTrig4ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig4ISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig3ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSwTrig3ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig3ISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig2ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSwTrig2ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig2ISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig1ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSwTrig1ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig1ISR */

/*************************************************************************************/

ISR2 ( CPU12XGSwTrig0ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSwTrig0ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XGSwTrig0ISR */

/*************************************************************************************/
ISR2 ( CPU12PIT3ISR )

 {
 
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSWErrorISR() */
 
 _asm("bgnd");
 }	/* end CPU12PIT3ISR */

/*************************************************************************************/

ISR2 ( CPU12PIT2ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSWErrorISR() */
 
 _asm("bgnd");
  
}	/* end CPU12PIT2ISR() */

/*************************************************************************************/
volatile int counter_isr = 0;

ISR2 ( CPU12PIT1ISR )

 {
	PITTF         = 0x02;        //@0x345;	/* PIT time-out flag register */
	counter_isr++;
	if(counter_isr==1)
	{
		ActivateTask(Task2);
		EE_assert(4, counter_isr==1, 3);
	}
	//_asm("cli");
	if((PORTA & 0x02)==1)
        PORTA &= 0xFD;
	else
        PORTA |= 0x02;
 
}	/* end CPU12PIT1ISR */

/*************************************************************************************/
volatile int counter0 = 0; 

ISR2 ( CPU12PIT0ISR )

 {
	///* This is an ISR Type 2 which is attached to the PIT0 peripheral IRQ pin
	// * The ISR simply calls CounterTick to implement the timing reference
	// */
	PITTF         = 0x01;        //@0x345;	/* PIT time-out flag register */
	//_asm("cli");
	PITCE = 0x02;
	counter0++;
	EE_assert(3, counter0==1, 2);
	while(1)
    	if(counter_isr > 10)
    		break;
	if((PORTA & 0x01)==1)
        PORTA &= 0xFE;
	else
        PORTA |= 0x01;
 }	/* end CPU12PIT0ISR */

/*************************************************************************************/

ISR2 ( CPU12APIISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12APIISR() */
 
 _asm("bgnd");
 
}	/* end CPU12APIISR */

/*************************************************************************************/

ISR2 ( CPU12LVIISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12LVIISR() */
 
 _asm("bgnd");
 
}	/* end CPU12LVIISR */

/*************************************************************************************/

ISR2 ( CPU12IIC1ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12IIC1ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12IIC1ISR */

/*************************************************************************************/

ISR2 ( CPU12SCI5ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SCI5ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SCI5ISR */

/*************************************************************************************/

ISR2 ( CPU12SCI4ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SCI4ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SCI4ISR */

/*************************************************************************************/

ISR2 ( CPU12SCI3ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SCI3ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SCI3ISR */

/*************************************************************************************/

ISR2 ( CPU12SCI2ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SCI2ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SCI2ISR */

/*************************************************************************************/

ISR2 ( CPU12PWMISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PWMISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PWMISR */

/*************************************************************************************/

ISR2 ( CPU12PortPISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PortPISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PortPISR */

/*************************************************************************************/

ISR2 ( CPU12CAN4TxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN4TxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN4TxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN4RxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN4RxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN4RxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN4ErrISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN4ErrISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN4ErrISR */

/*************************************************************************************/

ISR2 ( CPU12CAN4WakeISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN4WakeISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN4WakeISR */

/*************************************************************************************/

ISR2 ( CPU12CAN3TxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN3TxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN3TxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN3RxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN3RxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN3RxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN3ErrISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN3ErrISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN3ErrISR */

/*************************************************************************************/

ISR2 ( CPU12CAN3WakeISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN3WakeISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN3WakeISR */

/*************************************************************************************/

ISR2 ( CPU12CAN2TxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN4TxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN2TxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN2RxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN2RxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN2RxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN2ErrISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN2ErrISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN2ErrISR */

/*************************************************************************************/

ISR2 ( CPU12CAN2WakeISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN2WakeISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN2WakeISR */

/*************************************************************************************/

ISR2 ( CPU12CAN1TxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN1TxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN1TxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN1RxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN1RxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN1RxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN1ErrISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN1ErrISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN1ErrISR */

/*************************************************************************************/

ISR2 ( CPU12CAN1WakeISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN1WakeISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN1WakeISR */

/*************************************************************************************/

ISR2 ( CPU12CAN0TxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN0TxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN0TxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN0RxISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN0RxISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN0RxISR */

/*************************************************************************************/

ISR2 ( CPU12CAN0ErrISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN0ErrISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN0ErrISR */

/*************************************************************************************/

ISR2 ( CPU12CAN0WakeISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12CAN0WakeISR() */
 
 _asm("bgnd");
 
}	/* end CPU12CAN0WakeISR */

/*************************************************************************************/

ISR2 ( CPU12FlashISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12FlashISR() */
 
 _asm("bgnd");
 
}	/* end CPU12FlashISR */

/*************************************************************************************/

ISR2 ( CPU12EEPROMISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12EEPROMISR() */
 
 _asm("bgnd");
 
}	/* end CPU12EEPROMISR */

/*************************************************************************************/

ISR2 ( CPU12SPI2ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SPI2ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SPI2ISR */

/*************************************************************************************/

ISR2 ( CPU12SPI1ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SPI1ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SPI1ISR */

/*************************************************************************************/

ISR2 ( CPU12IIC0ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12IIC0ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12IIC0ISR */

/*************************************************************************************/

ISR2 ( CPU12SRCSGISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SRCSGISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SRCSGISR */

/*************************************************************************************/

ISR2 ( CPU12PLLLockISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PLLLockISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PLLLockISR */

/*************************************************************************************/

ISR2 ( CPU12PACCBOVISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PACCBOVISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PACCBOVISR */

/*************************************************************************************/

ISR2 ( CPU12MDCUISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12MDCUISR() */
 
 _asm("bgnd");
 
}	/* end CPU12MDCUISR */

/*************************************************************************************/

ISR2 ( CPU12PortHISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PortHISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PortHISR */

/*************************************************************************************/

ISR2 ( CPU12PortJISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PortJISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PortJISR */

/*************************************************************************************/

ISR2 ( CPU12ATD1ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12ATD1ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12ATD1ISR */

/*************************************************************************************/

ISR2 ( CPU12ATD0ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12ATD0ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12ATD0ISR */

/*************************************************************************************/

ISR2 ( CPU12SCI1ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SCI1ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SCI1ISR */

/*************************************************************************************/

ISR2 ( CPU12SCI0ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SCI0ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SCI0ISR */

/*************************************************************************************/

ISR2 ( CPU12SPI0ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SPI0ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SPI0ISR */

/*************************************************************************************/

ISR2 ( CPU12PACCAIEISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PACCAIEISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PACCAIEISR */

/*************************************************************************************/

ISR2 ( CPU12PACCAOVISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12PACCAOVISR() */
 
 _asm("bgnd");
 
}	/* end CPU12PACCAOVISR */

/*************************************************************************************/

ISR2 ( CPU12TimerOVISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerOVISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerOVISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh7ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerCh7ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerCh7ISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh6ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerCh6ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerCh6ISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh5ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerCh5ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerCh5ISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh4ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerCh4ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerCh4ISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh3ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerCh3ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerCh3ISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh2ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerCh2ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerCh2ISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh1ISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TimerCh1ISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TimerCh1ISR */

/*************************************************************************************/

ISR2 ( CPU12TimerCh0ISR )

 {
 
 /* Variable Declarations */

 
 /* Begin Function CPU12XGSWErrorISR() */
 
 _asm("bgnd");
  
}	/* end CPU12TimerCh0ISR */

/*************************************************************************************/

ISR2 ( CPU12RTIISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12RTIISR() */
 
 _asm("bgnd");
 
}	/* end CPU12RTIISR */

/*************************************************************************************/

ISR2 ( CPU12IRQISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12IRQISR() */
 
 _asm("bgnd");
 
}	/* end CPU12IRQISR */

/*************************************************************************************/

ISR2 ( CPU12XIRQISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12XIRQISR() */
 
 _asm("bgnd");
 
}	/* end CPU12XIRQISR */

/*************************************************************************************/

ISR2 ( CPU12SWIISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12SWIISR() */
 
 _asm("bgnd");
 
}	/* end CPU12SWIISR */

/*************************************************************************************/

ISR2 ( CPU12TrapISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12TrapISR() */
 
 _asm("bgnd");
 
}	/* end CPU12TrapISR */

/*************************************************************************************/

ISR2 ( CPU12COPISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12COPISR() */
 
 _asm("bgnd");
 
}	/* end CPU12COPISR */

/*************************************************************************************/

ISR2 ( CPU12ClockMonISR )

 {
  
 /* Variable Declarations */

 
 /* Begin Function CPU12ClockMonISR() */
 
 _asm("bgnd");
 
}	/* end CPU12ClockMonISR */

/*************************************************************************************/

EE_S12_ISR void CPU12SystemReset(void)
 {
  asm jmp _Startup
 }	/* end CPU12SystemReset */

/*************************************************************************************/

/* switch back to default segment */
/* #pragma CODE_SEG DEFAULT */
