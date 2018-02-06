#include "test.h"
#include "ee_irq.h"
#include "test_irq.h"

void really_grab_the_stack ( char * stack_grabber )
{
  /* Just used to force the compiler to allocate stack */
}

int main( void )
{
  test_setup_irq(EE_ISR2_ID_App1Isr1);
  test_setup_irq(EE_ISR2_ID_App2Isr2);
  test_setup_irq(EE_ISR2_ID_App1Isr3);

  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
