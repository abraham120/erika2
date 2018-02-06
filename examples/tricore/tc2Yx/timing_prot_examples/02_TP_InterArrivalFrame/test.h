#ifndef EE_TEST_H__
#define EE_TEST_H__

#include "ee.h"
#include "ee_internal.h"

#define EE_MAX_ASSERTIONS 25

#define EE_TEST_FINISHED_WITH_TP_ERROR

#ifdef EE_SUPPORT_MEMMAP_H
#define API_START_SEC_CODE
#define API_START_SEC_DATA
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

extern unsigned int volatile assert_count;
void test_assert(int test);
int test_service_protection( StatusType Error );

#ifdef EE_SUPPORT_MEMMAP_H
#define API_STOP_SEC_CODE
#define API_STOP_SEC_DATA
#include "MemMap.h"
#endif /* EE_SUPPORT_MEMMAP_H */

__INLINE__ void __ALWAYS_INLINE__ error( void )
{
  /* Do nothing; added a breakpoint on this function to catch errors */
  EE_tc_debug();
}

#endif /* EE_TEST_H__ */
