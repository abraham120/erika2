/* Jan Kleinsorge, 2010 */

#include "cpu/tricore1/inc/ee_intstub.S"
#include "cpu/tricore1/inc/ee_trapstub.S"

BEGIN_VECTOR_TABLE        
  EE_ISR2_STUB 5 stm_isr
END_VECTOR_TABLE

BEGIN_TRAP_TABLE
END_TRAP_TABLE
