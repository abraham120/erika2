#include "common.h"

static volatile int EE_APPLICATION_UDATA(App1) state1;

ISR(App1Isr)
{
	if (! (state1 & 1)) {
		ActivateTask(App1Task);
	}
	state1 ^= 1;
}


TASK(App1Task)
{
	while (state1 & 1) {
		/* Wait for the next ISR invocation */
	}
	TerminateTask();
}
