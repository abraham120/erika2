#include <ee.h>
#include <ee_irq.h>
#include "error.h"

static char EE_APPLICATION_UDATA(App2) var0;
static int EE_APPLICATION_UDATA(App2) var1;
static int EE_APPLICATION_IDATA(App2) var2 = 0x374a430b;
static char EE_APPLICATION_IDATA(App2) var3 = 0x34;
static int EE_APPLICATION_IDATA(App2) err = 0;
static volatile char EE_APPLICATION_UDATA(App2) state1;
static char EE_APPLICATION_UDATA(App2) state2;
static volatile char EE_APPLICATION_UDATA(App2) state3;

ISR2(App2Isr)
{
	ActivateTask(TrustedTask1);
	if (state2 & 1) {
		ActivateTask(App1Task);
	}
	state2 ^= 1;
	state3 = 1;
}


TASK(App2Task)
{
	SuspendAllInterrupts();
	state3 = 0;
	EE_e200zx_delay(35000);
	if (state3 != 0) {
		/* Error: state3 has changed with interrupts disabled */
		error(err_suspend_irq_fail);
	}
	/* Check nesting of suspend/resume */
	SuspendAllInterrupts();
	ResumeAllInterrupts();
	if (state3 != 0) {
		/* Error: state3 has changed with interrupts disabled */
		error(err_resume_irq_early_fail);
	}
	ResumeAllInterrupts();
	/* Interrupts are enabled: pending IRQs should be served before
	 * reading state3 in the next instruction */
	if (state3 == 0) {
		/* Error: state3 hasn't changed yet */
		error(err_resume_irq_fail);
	}
	while (! (state1 & 1)) {
		/* Wait for App2Ack */
	}
	state1 = 0;
	TerminateTask();
}

TASK(App2Ack)
{
	state1 |= 1;
	/* This should be a NO-OP */
	EnableAllInterrupts();
	TerminateTask();
}
