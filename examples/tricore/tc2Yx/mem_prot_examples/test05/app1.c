#include <ee.h>
#include <ee_irq.h>
#include "error.h"
#include "app.h"

/* Just to check accesses to .rodata */
int const cvar1 = -1;

#define APP_App1_START_SEC_CODE

#define APP_App1_START_SEC_VAR_NOINIT
#include "MemMap.h"
static ApplicationType myid;
#define APP_App1_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

#define APP_App1_START_SEC_DATA
#include "MemMap.h"
volatile int counter1 = 110100;
#define APP_App1_STOP_SEC_DATA
#include "MemMap.h"

ISR2(App1Isr)
{
  ISRType isr;
  int locvar;
  AccessType perm;
  ApplicationType id;
  ActivateTask(App1Task);
  id = GetApplicationID();
  if (id != myid) {
    error(err_wrong_isr_app);
  }
  isr = GetISRID();
  perm = CheckISRMemoryAccess(isr, &locvar, sizeof(locvar));
  if ( !OSMEMORY_IS_READABLE(perm) ) {
    error(err_perm_loc_noread);
  }
  if ( !OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_loc_nowrite);
  }
  if ( !OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_loc_nostack);
  }
  perm = CheckTaskMemoryAccess(App2Task, &locvar, sizeof(locvar));
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_othapp_write);
  }
  perm = CheckISRMemoryAccess(isr, (MemoryStartAddressType)&cvar1,
    sizeof(cvar1));
  if ( !OSMEMORY_IS_READABLE(perm) ) {
    error(err_perm_const_noread);
  }
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_const_write);
  }
  if ( OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_const_stack);
  }
  perm = CheckTaskMemoryAccess(App2Task, (MemoryStartAddressType)&cvar1,
    sizeof(cvar1));
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_othapp_write);
  }
  perm = CheckISRMemoryAccess(isr, (MemoryStartAddressType)&counter1,
    sizeof(counter1));
  if ( !OSMEMORY_IS_READABLE(perm) ) {
    error(err_perm_glob_noread);
  }
  if ( !OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_glob_nowrite);
  }
  if ( OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_glob_stack);
  }
  perm = CheckISRMemoryAccess(isr, &var2, sizeof(var2));
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_othapp_write);
  }
  if ( OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_glob_stack);
  }
  perm = CheckISRMemoryAccess(isr, error, 1U);
  if ( !OSMEMORY_IS_EXECUTABLE(perm) ) {
    error(err_perm_code_noexec);
  }
  if ( OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_code_stack);
  }
}

TASK(App1Init)
{
  myid = GetApplicationID();
  if (myid == INVALID_OSAPPLICATION) {
    error(err_invalid_task_app);
  }
}

TASK(App1Task)
{
  ApplicationType id;
  int locvar;
  AccessType perm;
  id = GetApplicationID();
  if (id != myid) {
    error(err_wrong_task_app);
  }
  perm = CheckTaskMemoryAccess(App1Task, &locvar, sizeof(locvar));
  if ( !OSMEMORY_IS_READABLE(perm) ) {
    error(err_perm_loc_noread);
  }
  if ( !OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_loc_nowrite);
  }
  if ( !OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_loc_nostack);
  }
  perm = CheckTaskMemoryAccess(App2Task, &locvar, sizeof(locvar));
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_othapp_write);
  }
  perm = CheckTaskMemoryAccess(App1Task, (MemoryStartAddressType)&cvar1,
    sizeof(cvar1));
  if ( !OSMEMORY_IS_READABLE(perm) ) {
    error(err_perm_const_noread);
  }
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_const_write);
  }
  if ( OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_const_stack);
  }
  perm = CheckTaskMemoryAccess(App2Task, (MemoryStartAddressType)&cvar1,
    sizeof(cvar1));
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_othapp_write);
  }
  perm = CheckTaskMemoryAccess(App1Task, (MemoryStartAddressType)&counter1,
    sizeof(counter1));
  if ( !OSMEMORY_IS_READABLE(perm) ) {
    error(err_perm_glob_noread);
  }
  if ( !OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_glob_nowrite);
  }
  if ( OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_glob_stack);
  }
  perm = CheckTaskMemoryAccess(App1Task, &var2, sizeof(var2));
  if ( OSMEMORY_IS_WRITEABLE(perm) ) {
    error(err_perm_othapp_write);
  }
  if ( OSMEMORY_IS_STACKSPACE(perm) ) {
    error(err_perm_glob_stack);
  }
  perm = CheckTaskMemoryAccess(App1Task, error, 1U);
  if ( !OSMEMORY_IS_EXECUTABLE(perm) ) {
    error(err_perm_code_noexec);
  }
  if (OSMEMORY_IS_STACKSPACE(perm)) {
    error(err_perm_code_stack);
  }
  TerminateTask();
}
