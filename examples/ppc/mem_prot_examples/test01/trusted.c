#include "common.h"

int EE_APPLICATION_UDATA(TrustedApp) error;

void signal_error(int e)
{
	error = e;
	while (1) {
	}
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
			signal_error(1);
		}
	}
}


TASK(MainTask)
{
	ActivateTask(TrustedTask1);
	ActivateTask(App1Task);
	ActivateTask(App2Task);
	TerminateTask();
}

TASK(TrustedTask1)
{
	check_irq_tos();
	TerminateTask();
}


ISR(TrustedIsr)
{
	ActivateTask(TrustedTask1);
}
