#ifndef EE_TEST_H__
#define EE_TEST_H__

#include "ee.h"

#define EE_MAX_ASSERTIONS 50

#define EE_TEST_FINISHED_WITH_TP_ERROR

extern unsigned int volatile assert_count;
void test_assert(int test);
int test_service_protection( StatusType Error );

__INLINE__ void __ALWAYS_INLINE__ error( void )
{
  /* Do nothing; added a breakpoint on this function to catch errors */
  EE_tc_debug();
}

#endif /* EE_TEST_H__ */
