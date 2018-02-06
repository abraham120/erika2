#include <ee.h>
#include "error.h"

#define API_START_SEC_CODE
#include "MemMap.h"

void error(enum err_code code)
{
  /* Do nothing; just add a breakpoint on this function to catch
   * errors */
    EE_tc_debug();
}

int main( void )
{
  StartOS(OSDEFAULTAPPMODE);
  return 0;
}
