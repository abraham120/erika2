#include "shared.h"

#ifdef USE_PRAGMAS

#pragma section EE_SHARED_NOTINIT_BEGIN
#pragma section EE_SHARED_FAST_NOTINIT_BEGIN
EE_TYPEASSERTVALUE EE_assertions[asr_dim];
volatile int send_event;
int result;
#pragma section EE_SHARED_END
#pragma section EE_SHARED_FAST_OR_SLOW_END

#else

EE_TYPEASSERTVALUE EE_SHARED_UDATA EE_assertions[asr_dim];
volatile int EE_SHARED_UDATA send_event;
int EE_SHARED_UDATA result;

#endif
