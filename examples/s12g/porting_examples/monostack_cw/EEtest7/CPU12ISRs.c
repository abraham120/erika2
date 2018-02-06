/*****************************************************
 CPU12ISR.c - interrupt/exception handlers for HCS12    
 ----------------------------------------------------
  
 *****************************************************/

#include "hidef.h"       /* this file declares symbols user by the CodeWarrior environment */
#include "start12.h"     /* to call the C-startup code */
#include "CPU12ISRs.h"
#include "ee_s12regs.h"

/*************************************************************************************/

ISR2 ( SpuriousISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12ReservedISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12PortADISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12APIISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12ADCCompareISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12LVIISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12PortPISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12CAN0TxISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12CAN0RxISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12CAN0ErrISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12CAN0WakeISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12FlashCmdISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12FlashErrISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12SPI2ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12SPI1ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12SCI2ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 (  CPU12PLLLockISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12OSCStatusISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12ACMPISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12PortJISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12ADCISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12SCI1ISR ) {
    _asm("bgnd");
}

/*************************************************************************************/
volatile int counter_isr = 0;


ISR2 ( CPU12SCI0ISR ) {
	byte st = SCI0SR1;
	SCI0CR2 = 0x0C; /* disable SCI0 IRQ */
	_asm("cli");
	
	EE_assert(3, counter_isr==0, 2);
	counter_isr++;
	
	ActivateTask(Task1);
}

/*************************************************************************************/

ISR2 ( CPU12SPI0ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12PACCAIEISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12PACCAOVISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerOVISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerCh7ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerCh6ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerCh5ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerCh4ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerCh3ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerCh2ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TimerCh1ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/
ISR2 (  CPU12TimerCh0ISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12RTIISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12IRQISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12XIRQISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12SWIISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12TrapISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12COPISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

ISR2 ( CPU12ClockMonISR ) {
 _asm("bgnd");
}
/*************************************************************************************/

EE_S12_ISR void CPU12SystemReset(void) {
  asm jmp _Startup
 }	/* end CPU12SystemReset */
/*************************************************************************************/