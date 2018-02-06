#include <ee.h>
#include <ee_irq.h>
#include "app.h"
#include "error.h"

#ifdef USE_PRAGMAS
#pragma section BSS_APP2 "ee_bss_App2" "ee_bss_App2"
#pragma use_section BSS_APP2 myid
#pragma use_section BSS_APP2 var2

#pragma section DATA_APP1 "ee_data_App1" "ee_data_App1"
#pragma use_section DATA_APP1 counter1

int var2;
static ApplicationType myid;
#else
int EE_APPLICATION_UDATA(App2) var2;
static ApplicationType EE_APPLICATION_UDATA(App2) myid;
#endif

ISR2(App2Isr)
{
	ApplicationType id;
	ISRType isr;
	int locvar;
	AccessType perm;
	ActivateTask(App2Task);
	id = GetApplicationID();
	if (id != myid) {
		error(err_wrong_isr_app);
	}
	isr = GetISRID();
	perm = CheckISRMemoryAccess(isr, &locvar, sizeof(locvar));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_loc_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_loc_nowrite);
	}
	if (! OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_loc_nostack);
	}
	perm = CheckTaskMemoryAccess(App1Task, &locvar, sizeof(locvar));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckISRMemoryAccess(isr, &gvar, sizeof(gvar));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckISRMemoryAccess(isr, &EE_stkfirst, sizeof(EE_stkfirst));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckTaskMemoryAccess(App1Task, (MemoryStartAddressType)&counter1,
		sizeof(counter1));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckISRMemoryAccess(isr, (MemoryStartAddressType)&counter1,
		sizeof(counter1));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckISRMemoryAccess(isr, &var2, sizeof(var2));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckISRMemoryAccess(isr, error, 1U);
	if (! OSMEMORY_IS_EXECUTABLE(perm)) {
		error(err_perm_code_noexec);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_code_stack);
	}
}

TASK(App2Init)
{
	ISRType isr;
	myid = GetApplicationID();
	if (myid == INVALID_OSAPPLICATION) {
		error(err_invalid_task_app);
	}
	isr = GetISRID();
	if (isr != INVALID_ISR) {
		error(err_notinvalid_isr);
	}
	TerminateTask();
}

TASK(App2Task)
{
	ApplicationType id;
	int locvar;
	AccessType perm;
	id = GetApplicationID();
	if (id != myid) {
		error(err_wrong_isr_app);
	}
	perm = CheckTaskMemoryAccess(App2Task, &locvar, sizeof(locvar));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_loc_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_loc_nowrite);
	}
	if (! OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_loc_nostack);
	}
	perm = CheckTaskMemoryAccess(App1Task, &locvar, sizeof(locvar));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckTaskMemoryAccess(App2Task, (MemoryStartAddressType)&cvar1,
		sizeof(cvar1));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckTaskMemoryAccess(App2Task, &EE_stkfirst, sizeof(EE_stkfirst));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckTaskMemoryAccess(App1Task, (MemoryStartAddressType)&counter1,
		sizeof(counter1));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckTaskMemoryAccess(App2Task, (MemoryStartAddressType)&counter1,
		sizeof(counter1));
	if (OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_othapp_write);
	}
	perm = CheckTaskMemoryAccess(App2Task, &var2, sizeof(var2));
	if (! OSMEMORY_IS_READABLE(perm)) {
		error(err_perm_glob_noread);
	}
	if (! OSMEMORY_IS_WRITEABLE(perm)) {
		error(err_perm_glob_nowrite);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_glob_stack);
	}
	perm = CheckTaskMemoryAccess(App2Task, error, 1U);
	if (! OSMEMORY_IS_EXECUTABLE(perm)) {
		error(err_perm_code_noexec);
	}
	if (OSMEMORY_IS_STACKSPACE(perm)) {
		error(err_perm_code_stack);
	}
	TerminateTask();
}
