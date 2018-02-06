#ifndef EE_TEST_H__
#define EE_TEST_H__

#include "ee.h"

#define EE_MAX_ASSERTIONS 40

#define API_START_SEC_CODE
#define API_START_SEC_DATA
#include "MemMap.h"
extern unsigned int assert_count;
void test_assert(int test);
int test_service_protection( StatusType Error );
#define API_STOP_SEC_CODE
#define API_STOP_SEC_DATA
#include "MemMap.h"

__INLINE__ void __ALWAYS_INLINE__ error( void )
{
  /* Do nothing; added a breakpoint on this function to catch errors */
  EE_tc_debug();
}

#endif /* EE_TEST_H__ */
