#ifndef SHARED_H
#define SHARED_H

#include <ee.h>
#include <ee_irq.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

#define SHARED_LEN 9
#define SHARED_LONG_LEN 512
/* If the linker script for shared data is not yet working, pick an address in
 * the upper space of the first core; 4 kB of memory */
extern volatile int EE_SHARED_UDATA shared[SHARED_LONG_LEN];

#define MY_SPINLOCK 0


#endif /* SHARED_H */
