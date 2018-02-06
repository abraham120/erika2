#ifndef TRUSTED_H
#define TRUSTED_H

#include "ee.h"

StatusType TRUSTED_MyTaskTrustedService(TrustedFunctionIndexType index,
  TrustedFunctionParameterRefType ref);
StatusType TRUSTED_MyIsrTrustedService(TrustedFunctionIndexType index,
  TrustedFunctionParameterRefType ref);

#endif /* TRUSTED_H */
