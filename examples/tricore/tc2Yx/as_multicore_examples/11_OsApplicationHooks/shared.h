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

void test_assert ( int test );

extern EE_BIT volatile slave2_app_startup_flag;
extern EE_BIT volatile slave2_app_shutdown_flag;

#endif /* SHARED_H */
