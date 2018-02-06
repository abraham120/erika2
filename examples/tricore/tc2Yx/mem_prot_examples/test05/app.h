#ifndef APP_H
#define APP_H

extern const int cvar1;

#define APP_App2_START_SEC_VAR_NOINIT
#include "MemMap.h"
extern int var2;
#define APP_App2_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

#define APP_TrustedApp_START_SEC_VAR_NOINIT
#include "MemMap.h"
extern EE_UREG gvar;
#define APP_TrustedApp_STOP_SEC_VAR_NOINIT
#include "MemMap.h"

#define APP_App1_START_SEC_DATA
#include "MemMap.h"
extern volatile int counter1;
#define APP_App1_STOP_SEC_DATA
#include "MemMap.h"

#endif /* APP_H */
