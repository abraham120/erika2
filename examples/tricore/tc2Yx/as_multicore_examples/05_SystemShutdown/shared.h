#ifndef SHARED_H
#define SHARED_H

#include <ee.h>
#include <ee_irq.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#define TEST_WAIT 1000000U

extern void test_assert( int test );

#endif /* SHARED_H */
