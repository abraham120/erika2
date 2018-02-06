#ifndef SHARED_H
#define SHARED_H

#include <ee.h>

#define SHARED_LONG_LEN 32

/* If the linker script for shared data is not yet working, pick an address in
 * the upper space of the first core; 4 kB of memory */
#ifdef __MSRP__

#ifdef USE_PRAGMAS
#pragma section EE_SHARED_NOTINIT_BEGIN
#pragma section EE_SHARED_SLOW_NOTINIT_BEGIN
extern volatile int shared_data[SHARED_LONG_LEN];
#pragma section EE_SHARED_END
#pragma section EE_SHARED_FAST_OR_SLOW_END
#else
extern volatile int EE_SHARED_UDATA shared_data[SHARED_LONG_LEN];
#endif
#else
extern volatile int shared_data[SHARED_LONG_LEN];
#endif

#define MY_SPINLOCK 2


#endif /* SHARED_H */
