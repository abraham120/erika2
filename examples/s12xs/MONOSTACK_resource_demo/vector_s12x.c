/*	INTERRUPT VECTORS TABLE S12X
 *	Copyright (c) 2004 by COSMIC Software
 */

#include "stdlib.h"
#include <math.h>
#include "ee.h"
#include "ee_irq.h"
#include "ee_s12regs.h" 

#include "myapp.h"
#include "mcu/hs12xs/inc/ee_pit.h"
#include "mcu/hs12xs/inc/ee_sci.h"
 
extern volatile int timer_fired;
extern volatile int timer_divisor; 
extern volatile int button_fired;
 
ISR2(PIT0_Interrupt)
{
	/* clear the interrupt source */
	EE_pit0_clear_ISRflag();
	timer_divisor++;
	if (timer_divisor == 5000) {
		timer_divisor = 0;
		timer_fired++;
        ActivateTask(Task1);
	}

}


ISR2(Buttons_Interrupt)
{
	EE_buttons_disable_interrupts(BUTTON_0);
	button_fired++;
	ActivateTask(Task2); 
	mydelay((long int)5000);
	EE_buttons_enable_interrupts(BUTTON_0);
	EE_buttons_clear_ISRflag(BUTTON_0);
}
 
 
@interrupt @near void _stext(void);	/* startup routine */

/*	dummy interrupt routine
 */
static @interrupt @near void dummit(void)
	{
		EE_sci_send_byte(SCI_0,0xEE);
	}
	
/*	User interrupt routines
 */	
//extern @interrupt @near void uisr_pit0(void);
//extern @interrupt @near void uisr_pit1(void);

#pragma section const {vector}

/*	vector table to be located at address 0xFF10
 */
@interrupt @near void (* const _vectab[])(void) = {
	dummit,			/* 0xFF10  Spurious Interrupt         */
	dummit,         /* 0xFF12  System Call interrupt (sys) */
    dummit, dummit, dummit, dummit, dummit, dummit, dummit, 
    dummit, dummit, dummit, dummit, dummit, dummit, dummit,
    dummit, dummit, dummit, dummit, dummit, dummit, dummit, 
    dummit,         /* 0xFF3E ATD0 compare int */ 
	dummit, dummit, dummit, dummit, dummit, dummit, dummit, dummit,
	dummit, dummit, dummit, dummit, dummit, dummit, dummit, dummit,
	dummit,			/* 0xFF60  NO!!! XRAM access violation     */
	dummit,			/* 0xFF62  NO!!! XGATE software error      */
	dummit,			/* 0xFF64  NO!!! XGATE software trigger 7  */
	dummit,			/* 0xFF66  NO!!! XGATE software trigger 6  */
	dummit,			/* 0xFF68  NO!!! XGATE software trigger 5  */
	dummit,			/* 0xFF6a  NO!!! XGATE software trigger 4  */
	dummit,			/* 0xFF6c  NO!!! XGATE software trigger 3  */
	dummit,			/* 0xFF6e  NO!!! XGATE software trigger 2  */
	dummit,			/* 0xFF70  NO!!! XGATE software trigger 1  */
  	dummit,			/* 0xFF72  NO!!! XGATE software trigger 0  */
  	dummit,			/* 0xFF74  Periodic Interrupt Timer  */
  	dummit,			/* 0xFF76  Periodic Interrupt Timer  */
  	dummit,			/* 0xFF78  Periodic Interrupt Timer  */
  	PIT0_Interrupt,			/* 0xFF7A  Periodic Interrupt Timer  */
  	dummit,			/* 0xFF7C  HTI                  */
  	dummit,			/* 0xFF7E  Autonomous Periodical Int */
	dummit,			/* 0xFF80  Low Voltage Interrupt     */
  	dummit,			/* 0xFF82  NO!!! IIC1                      */
  	dummit,			/* 0xFF84  NO!!! SCI5                      */
  	dummit,			/* 0xFF86  NO!!! SCI4                      */
  	dummit,			/* 0xFF88  NO!!! SCI3                      */
  	dummit,			/* 0xFF8A  NO!!! SCI2                      */
  	dummit,			/* 0xFF8C  PWM Emergency Shutdown    */
  	Buttons_Interrupt,			/* 0xFF8E  Port P Interrupt          */
  	dummit,			/* 0xFF90  NO!!! MSCAN 4 transmit          */
  	dummit,			/* 0xFF92  NO!!! MSCAN 4 receive           */
  	dummit,			/* 0xFF94  NO!!! MSCAN 4 errors            */
  	dummit,			/* 0xFF96  NO!!! MSCAN 4 wake-up           */
  	dummit,			/* 0xFF98  NO!!! MSCAN 3 transmit          */
  	dummit,			/* 0xFF9A  NO!!! MSCAN 3 receive           */
  	dummit,			/* 0xFF9C  NO!!! MSCAN 3 errors            */
  	dummit,			/* 0xFF9E  NO!!! MSCAN 3 wake-up           */
  	dummit,			/* 0xFFA0  NO!!! MSCAN 2 transmit          */
  	dummit,			/* 0xFFA2  NO!!! MSCAN 2 receive           */
  	dummit,			/* 0xFFA4  NO!!! MSCAN 2 errors            */
  	dummit,			/* 0xFFA6  NO!!! MSCAN 2 wake-up           */
  	dummit,			/* 0xFFA8  NO!!! MSCAN 1 transmit          */
  	dummit,			/* 0xFFAA  NO!!! MSCAN 1 receive           */
  	dummit,			/* 0xFFAC  NO!!! MSCAN 1 errors            */
  	dummit,			/* 0xFFAE  NO!!! MSCAN 1 wake-up           */
  	dummit,			/* 0xFFB0  MSCAN 0 transmit          */
  	dummit,			/* 0xFFB2  MSCAN 0 receive           */
  	dummit,			/* 0xFFB4  MSCAN 0 errors            */
  	dummit,			/* 0xFFB6  MSCAN 0 wake-up           */
  	dummit,			/* 0xFFB8  FLASH                     */
  	dummit,			/* 0xFFBA  FLASH fault                    */
  	dummit,			/* 0xFFBC  NO!!! SPI2                      */
  	dummit,			/* 0xFFBE  NO!!! SPI1                      */
  	dummit,			/* 0xFFC0  NO!!! IIC0                      */
  	dummit,			/* 0xFFC2  NO!!! reserved                  */
  	dummit,			/* 0xFFC4  CRG self clock mode                       */
  	dummit,			/* 0xFFC6  CRG PLL lock                  */
  	dummit,			/* 0xFFC8  NO!!! Pulse Acc B Overflow      */
  	dummit,			/* 0xFFCA  NO!!! Modulus Counter underflow */
  	dummit,			/* 0xFFCC  Port H                    */
  	dummit,			/* 0xFFCE  Port J                    */
  	dummit,			/* 0xFFD0  NO!!! ATD1                      */
  	dummit,			/* 0xFFD2  ATD0                      */
  	dummit,			/* 0xFFD4  SCI 1                     */
  	dummit,			/* 0xFFD6  SCI 0                     */
  	dummit,			/* 0xFFD8  SPI0                      */
  	dummit,			/* 0xFFDA  Pulse acc input edge      */
  	dummit,			/* 0xFFDC  Pulse acc A overflow      */
  	dummit,			/* 0xFFDE  Timer overflow            */
  	dummit,			/* 0xFFE0  Timer channel 7           */
  	dummit,			/* 0xFFE2  Timer channel 6           */
  	dummit,			/* 0xFFE4  Timer channel 5           */
  	dummit,			/* 0xFFE6  Timer channel 4           */
  	dummit,			/* 0xFFE8  Timer channel 3           */
  	dummit,			/* 0xFFEA  Timer channel 2           */
  	dummit,			/* 0xFFEC  Timer channel 1           */
  	dummit,			/* 0xFFEE  Timer channel 0           */
  	dummit,			/* 0xFFF0  Real Time Interrupt       */
  	dummit,			/* 0xFFF2  IRQ                       */
  	dummit,			/* 0xFFF4  XIRQ                      */
  	dummit,			/* 0xFFF6  SWI                       */
  	dummit,			/* 0xFFF8  Illegal opcode            */
  	dummit,			/* 0xFFFA  COP failure reset         */
  	dummit,			/* 0xFFFC  Clock Monitor fail reset  */
  	_stext,			/* 0xFFFE  Reset                     */
	};

#pragma section const {}
