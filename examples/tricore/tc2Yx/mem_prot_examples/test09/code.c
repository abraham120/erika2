#include <ee.h>
#include <ee_irq.h>

void really_grab_the_stack ( char * stack_grabber )
{
  /* Just used to force the compilare to allocate stack */
}

int main( void )
{
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
