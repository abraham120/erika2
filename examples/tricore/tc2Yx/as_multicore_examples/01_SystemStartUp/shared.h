#ifndef SHARED_H
#define SHARED_H

#include <ee.h>
#include <ee_irq.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

#define ASSERT_LENGTH 20U
extern EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];

extern void test_assert(int test);

#if defined(TEST_ERROR_CONF) && (!defined(TEST_SLAVE1_APPMODE))
#define TEST_SLAVE1_APPMODE OSDEFAULTAPPMODE
#endif /* TEST_ERROR_CONF && !TEST_SLAVE1_APPMODE */

#endif /* SHARED_H */
