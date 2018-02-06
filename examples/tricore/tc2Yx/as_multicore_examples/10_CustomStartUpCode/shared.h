#ifndef SHARED_H
#define SHARED_H

#include <ee_os.h>
/* Assertions */
#include "test/assert/inc/ee_assert.h"

#ifndef FALSE
#define FALSE 0U
#endif /* FALSE */

#define TEST_WAIT 1000000U

#define ASSERT_LENGTH 20U
EE_TYPEASSERTVALUE EE_assertions[ASSERT_LENGTH];

static int assert_count = EE_ASSERT_NIL;
void test_assert (int test )
{
  register int next_assert;
  /* Shared I need critical section I reuse CORE 0 Spinlock */
  EE_TYPESPIN spinlock_id = EE_as_core_spinlocks[OS_CORE_ID_MASTER];
  EE_hal_spin_in( spinlock_id );
  next_assert = (assert_count == EE_ASSERT_NIL) ? 1 : assert_count + 1;
  EE_assert(next_assert, test, EE_ASSERT_NIL);
  assert_count = next_assert;
  EE_hal_spin_out( spinlock_id );
}

#endif /* SHARED_H */
