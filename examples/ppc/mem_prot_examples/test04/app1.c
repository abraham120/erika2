#include <ee.h>
#include <ee_irq.h>
#include "error.h"

static volatile int EE_APPLICATION_UDATA(App1) state1;
static volatile int EE_APPLICATION_UDATA(App1) state2;
static volatile int EE_APPLICATION_UDATA(App1) state3;
static volatile int EE_APPLICATION_IDATA(App1) counter1 = 110100;
char EE_APPLICATION_IDATA(App1) err1 = 0x13;

ISR2(App1Isr)
{
	if (! (state1 & 1)) {
		ActivateTask(App2Task);
	} else {
		ActivateTask(App2Ack);
	}
	state1 ^= 1;
	state2 = 1;
	state3 = 1;
}

TASK(App1Task)
{
	DisableAllInterrupts();
	state2 = 0;
	/* Simulate the calling of an API in the ORTI tracer */
	EE_ORTI_ext_set_service_in(EE_SERVICETRACE_GETRESOURCE);
	EE_e200zx_delay(55000);
	EE_ORTI_ext_set_service_out(EE_SERVICETRACE_GETRESOURCE);
	if (state2 != 0) {
		/* Error: state2 has changed while interrupts were disabled */
		error(err_disable_irq_fail);
	}
	EnableAllInterrupts();
	/* Interrupts are enabled: pending IRQ should be served before reading
	 * state2 in the next instruction */
	if (state2 == 0) {
		/* Error: no interrupt though we have enabled interrupts */
		error(err_enable_irq_fail);
	}
	TerminateTask();
}

TASK(App1Ack)
{
	SuspendOSInterrupts();
	state3 = 0;
	EE_e200zx_delay(30000);
	if (state3 != 0) {
		/* Error: state3 has changed while interrupts were disabled */
		error(err_suspend_os_irq_fail);
	}
	/* Check nesting of suspend/resume */
	SuspendOSInterrupts();
	ResumeOSInterrupts();
	if (state3 != 0) {
		/* Error: state3 has changed while interrupts were disabled */
		error(err_resume_os_irq_early_fail);
	}
	ResumeOSInterrupts();
	/* Interrupts are enabled: pending IRQs should be served before reading
	 * state3 in the next instruction */
	if (state3 == 0) {
		/* Error: no interrupt though we have enabled interrupts */
		error(err_resume_os_irq_fail);
	}
	/* This should be a NO-OP */
	ResumeOSInterrupts();
	TerminateTask();
}

TASK(App1Bkg)
{
	while (1) {
		counter1 += 1;
	}
}
