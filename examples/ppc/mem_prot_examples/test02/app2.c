#include <ee.h>
#include <ee_irq.h>

static char EE_APPLICATION_UDATA(App2) var0;
static int EE_APPLICATION_UDATA(App2) var1;
static int EE_APPLICATION_IDATA(App2) var2 = 0x374a430b;
static char EE_APPLICATION_IDATA(App2) var3 = 0x34;
static int EE_APPLICATION_IDATA(App2) err = 0;
static volatile char EE_APPLICATION_UDATA(App2) state1;
static char EE_APPLICATION_UDATA(App2) state2;

ISR2(App2Isr)
{
	ActivateTask(TrustedTask1);
	if (state2 & 1) {
		ActivateTask(App1Task);
	}
	state2 ^= 1;
}


TASK(App2Task)
{
	while (! (state1 & 1)) {
		/* Wait for App2Ack */
	}
	state1 = 0;
	TerminateTask();
}

TASK(App2Ack)
{
	state1 |= 1;
	TerminateTask();
}


TASK(App2Init)
{
	if (err != 0) {
		err = -1;
	} else if (var3 != 0x34) {
		err = 10;
	} else if (var2 != 0x374a430b) {
		err = 11;
	} else if (var1 != 0) {
		err = 12;
	} else if (var0 != 0) {
		err = 13;
	}
	if (err != 0) {
		ActivateTask(ErrorTask);
	}
	TerminateTask();
}
