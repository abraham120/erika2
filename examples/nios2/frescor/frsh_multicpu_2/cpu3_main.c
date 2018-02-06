#include <stdio.h>
#include <system.h>
#include "ee.h"

TASK(Task4)
{
    static int i;
    printf("%d\n",i++);
    ActivateTask(Task1);
}

int main()
{ 
  EE_trace32_stack_init();
  
  printf("Hello from CPU 3\n");

  frsh_init();
  
  for (;;);

  return 0;
}
