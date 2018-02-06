#include <ee.h>
#include <ee_irq.h>

int EE_APPLICATION_UDATA(TrustedApp) error;

void signal_error(int e)
{
	error = e;
	ActivateTask(ErrorTask);
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
	ActivateTask(App1Init);
	ActivateTask(App2Init);
	ActivateTask(App1Bkg);
	TerminateTask();
}

TASK(TrustedTask1)
{
	check_irq_tos();
	TerminateTask();
}


ISR2(TrustedIsr)
{
	ActivateTask(TrustedTask1);
}

TASK(ErrorTask)
{
	DisableAllInterrupts();
	while (1) {
		/* Do nothing, just keep the system busy */
	}
}
