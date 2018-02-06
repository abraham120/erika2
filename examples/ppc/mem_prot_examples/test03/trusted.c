#include <ee.h>
#include <ee_irq.h>
#include "app.h"
#include "trusted.h"

struct trusted_params
{
	EE_INT32 arg0;
	EE_INT32 res;
};

int EE_APPLICATION_UDATA(TrustedApp) error;
EE_UREG EE_APPLICATION_UDATA(TrustedApp) gvar;
/* flag1 is allocated in the OS segment */
static volatile int flag1;


/* User inteface */
EE_INT32 CallMyTaskTrustedService(EE_INT32 arg)
{
	struct trusted_params str;
	StatusType s;
	str.arg0 = arg;
	s = CallTrustedFunction(EE_ID_TRUSTED_MyTaskTrustedService, &str);
	if (s != E_OK) {
		str.res = -1;
	}
	return str.res;
}
 
/* User inteface */
EE_INT32 CallMyIsrTrustedService(EE_INT32 arg)
{
	struct trusted_params str;
	StatusType s;
	str.arg0 = arg;
	s = CallTrustedFunction(EE_ID_TRUSTED_MyIsrTrustedService, &str);
	if (s != E_OK) {
		str.res = -1;
	}
	return str.res;
}
 
void TRUSTED_MyTaskTrustedService(TrustedFunctionIndexType index,
	TrustedFunctionParameterRefType ref)
{
	struct trutes_params *params = ref;
	EE_UREG x;
	/* Privileged function */
	x = EE_e200zx_get_tcr();
	discard(x);
	flag1 = 0;
	while (flag1 == 0) {
		/* Wait for MyIsrTrustedService */
	}
	/* Again, a privileged function */
	x = EE_e200zx_get_tcr();
	discard(x);
	/* Launch a non-trusted, high-priority task */
	ActivateTask(App2HiPriTask);
	/* Again, a privileged function */
	x = EE_e200zx_get_tcr();
	discard(x);
}


void TRUSTED_MyIsrTrustedService(TrustedFunctionIndexType index,
	TrustedFunctionParameterRefType ref)
{
	EE_UREG x;
	/* Privileged function */
	x = EE_e200zx_get_tcr();
	discard(x);
	flag1 = 1;
}


EE_INT32 TRUSTED_MyQuickTrustedService(EE_INT32 arg)
{
	return arg + 10;
}

void signal_error(int e)
{
	error = e;
	ActivateTask(ErrorTask);
}

void check_irq_tos(void)
{
	static char init;
	static EE_ADDR orig[EE_MAX_APP+1];
	unsigned i;

	if (init == 0) {
		for (i = 0; i < EE_MAX_APP + 1U; ++i) {
			orig[i] = EE_as_Application_RAM[i].ISRTOS;
		}
		init = 1;
	}
	for (i = 0; i < EE_MAX_APP + 1U; ++i) {
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
