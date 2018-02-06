#ifndef TRUSTED_H
#define TRUSTED_H

#define APP_AppCore1Trusted_START_SEC_CODE
#include "MemMap.h"
/* User inteface */
StatusType TRUSTED_SignalShutdown (TrustedFunctionIndexType index,
  TrustedFunctionParameterRefType ref);
#define  APP_AppCore1Trusted_STOP_SEC_CODE
#include "MemMap.h"

#define API_START_SEC_CODE
#include "MemMap.h"
StatusType CallSignalShutdown ( void );
#define API_STOP_SEC_CODE
#include "MemMap.h"

#endif /* TRUSTED_H */
