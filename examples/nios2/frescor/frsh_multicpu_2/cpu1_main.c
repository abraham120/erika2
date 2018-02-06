#include <stdio.h>
#include <system.h>
#include "ee.h"

TASK(Task2)
{
    static int i;
    printf("%d\n",i++);
    ActivateTask(Task3);
}

int main()
{ 
  EE_trace32_stack_init();
  
  printf("Hello from CPU 1\n");

  frsh_init();
  
  for (;;);

  return 0;
}
