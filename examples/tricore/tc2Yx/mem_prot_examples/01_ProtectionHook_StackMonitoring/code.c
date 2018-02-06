#include "test.h"
#include "ee_irq.h"

void really_grab_the_stack ( char * stack_grabber )
{
  /* Just used to force the compiler to allocate stack */
}

int main( void )
{
  StartOS(OSDEFAULTAPPMODE);
  /* Declared __OO_STARTOS_OLD__ in OIL file to the following */
#ifdef EE_TERMINATETASKISR_TEST
  ShutdownOS(E_OK);
#else /* EE_TERMINATETASKISR_TEST */
  error();
#endif /* EE_TERMINATETASKISR_TEST */
  return 0;
}
