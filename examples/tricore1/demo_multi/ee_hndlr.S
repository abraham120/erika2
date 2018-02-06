/* Jan Kleinsorge, 2010 */

#include "cpu/tricore1/inc/ee_intstub.S"

BEGIN_VECTOR_TABLE        
  EE_ISR2_STUB 6 cpu_isr
END_VECTOR_TABLE
