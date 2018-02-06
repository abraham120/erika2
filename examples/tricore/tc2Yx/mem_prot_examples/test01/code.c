#include "ee.h"

int main( void )
{
  /* EE_tc27x_stm_set_sr0(1000U, EE_ISR2_ID_TrustedIsr); */
  /* EE_tc27x_stm_set_sr1(3000U, EE_ISR2_ID_App1Isr); */

  StartOS(OSDEFAULTAPPMODE);
  
  return 0;
}
