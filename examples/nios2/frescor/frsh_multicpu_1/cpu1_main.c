#include <stdio.h>
#include <system.h>
#include "ee.h"

/*
 * For details about this file, please look at cpu0_startup.c
 */

int main()
{ 
  EE_trace32_stack_init();
  
  printf("Hello from CPU 1\n");
  printf("Press Button 1 or 2 to activate the tasks\n");

  frsh_init();
  
  for (;;);

  return 0;
}
