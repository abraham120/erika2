#ifndef EE_TEST_H__
#define EE_TEST_H__

#include "ee.h"

/* (Un)Comment This to change the behaviour of the test */
#define EE_TEST_TASK_IN_EXECUTION_TERMINATION

__INLINE__ void __ALWAYS_INLINE__ error( void )
{
  /* Do nothing; added a breakpoint on this function to catch errors */
  EE_tc_debug();
}
#endif /* EE_TEST_H__ */
