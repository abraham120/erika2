#include <stdio.h>
#include <system.h>
#include "ee.h"

TASK(Task3)
{
    static int i;
    printf("%d\n",i++);
    ActivateTask(Task4);
}

/*
 * For details about this file, please look at cpu0_startup.c
 */

int main()
{ 
  EE_trace32_stack_init();    
    
  printf("Hello from CPU 2\n");

  frsh_init();
  
  for (;;);

  return 0;
}
