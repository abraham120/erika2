#include <ee.h>
#include <ee_irq.h>
#include "error.h"
#include "app.h"

void error(enum err_code code)
{
  /* Do nothing; you should add a breakpoint on this function to catch
   * errors */
  EE_tc_debug();
}

int main( void )
{
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
