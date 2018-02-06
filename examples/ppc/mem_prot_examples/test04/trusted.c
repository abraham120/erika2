#include <ee.h>
#include <ee_irq.h>
#include "error.h"

int EE_APPLICATION_UDATA(TrustedApp) error_var;

void signal_error(int e)
{
	error_var = e;
	error(err_wrong_irq_tos);
}

void check_irq_tos(void)
{
	static char init;
	static EE_ADDR orig[EE_MAX_APP+1];
	int i;

	if (init == 0) {
		for (i = 0; i < EE_MAX_APP + 1; ++i) {
			orig[i] = EE_as_Application_RAM[i].ISRTOS;
		}
		init = 1;
	}
	for (i = 0; i < EE_MAX_APP + 1; ++i) {
		if (orig[i] != EE_as_Application_RAM[i].ISRTOS) {
			signal_error(i);
		}
	}
}


TASK(MainTask)
{
	ActivateTask(TrustedTask1);
	ActivateTask(App1Bkg);
	TerminateTask();
}

TASK(TrustedTask1)
{
	check_irq_tos();
	/* This should be a NO-OP */
	ResumeAllInterrupts();
	TerminateTask();
}


ISR2(TrustedIsr)
{
	ActivateTask(TrustedTask1);
}
