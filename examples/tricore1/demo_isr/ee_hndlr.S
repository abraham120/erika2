/* Jan Kleinsorge, 2010 */

#include "cpu/tricore1/inc/ee_intstub.S"
#include "cpu/tricore1/inc/ee_trapstub.S"

BEGIN_VECTOR_TABLE        
  EE_ISR2_STUB 4 isr2
  EE_ISR1_STUB 5 isr1
END_VECTOR_TABLE

BEGIN_TRAP_TABLE
  EE_TRAP_STUB 1 segfault        
  EE_TRAP_STUB 6 syscall
END_TRAP_TABLE

