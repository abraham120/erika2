#ifndef INCLUDE_COMMON_H___
#define INCLUDE_COMMON_H___
#include <ee.h>
#include <ee_irq.h>

/* Map macro ISR with correct implementation */
#ifdef EE_ISR_DYNAMIC_TABLE
#define ISR(f)  ISR2(f)
#else /* EE_ISR_DYNAMIC_TABLE */
#define ISR(f)  ISR2_INT(f)
#endif /* EE_ISR_DYNAMIC_TABLE */

#endif /* INCLUDE_COMMON_H___ */
