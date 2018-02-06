#include "common.h"

static char EE_APPLICATION_UDATA(App2) var0;
static int EE_APPLICATION_UDATA(App2) var1;
static int EE_APPLICATION_IDATA(App2) var2 = 0x374a430b;
static char EE_APPLICATION_IDATA(App2) var3 = 0x34;
static int EE_APPLICATION_IDATA(App2) err = 0;

ISR(App2Isr)
{
}


TASK(App2Task)
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
	/* Don't call TerminateTask() and see what happens */
}
