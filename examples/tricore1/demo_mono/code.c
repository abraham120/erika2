#include <stdio.h>
#include "ee.h"

void f0()
{
    puts("f0 start");
    TerminateTask();
    puts("f0 resume");
}

void f1()
{
    puts("f1 start");
    f0();
    puts("f1 resume");
}

void f2()
{
    puts("f2 start");
    f1();
    puts("f2 resume");
}

void f3()
{
    puts("f3 start");
    ActivateTask(Task0);
    f2();
    ActivateTask(Task0);
    puts("f3 resume");
}

void f4()
{
    puts("f4 start");
    f3();
    puts("f4 resume");
}

TASK(Task0)
{
    puts("task0 start");
}

TASK(Task1)
{
    puts("task1 start");
    f4();
    puts("task1 resume");
}

int main() 
{

    puts("main start");
    ActivateTask(Task1);
    ActivateTask(Task0);
    //StartOS(OSDEFAULTAPPMODE);
    puts("main resume");

    while(1);

    return 0;
}
