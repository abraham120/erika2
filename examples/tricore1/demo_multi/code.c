#include <stdio.h>
#include <tc1796b/cps.h>

#include "ee.h"
#include "kernel/sem/inc/ee_sem.h"

#define CPU_VECTOR 6

SemType P = STATICSEM(1);
SemType V;

/* Triggers an IRQ */
static void local_int(unsigned int vec) 
{
    EE_hal_disableIRQ();

    CPU_SRC0.reg |= CPU_SRCm_CLRR_MASK;

    CPU_SRCm_t_nonv c = {.reg = 0 };
    c.bits.TOS = 0;
    c.bits.SRPN = vec;
    c.bits.SRE = 1;
    CPU_SRC0 = c;

    EE_tc1_isync();    
    EE_hal_enableIRQ();

    CPU_SRC0.reg |= (1<<14);
    CPU_SRC0.reg |= (1<<15);
}


ISR(cpu_isr) {
    puts("cpu ISR start");
    ActivateTask(Task1);
    puts("cpu ISR resume");
}


TASK(Task0) {
    puts("task 0 start");
    //ActivateTask(Task1);
    local_int(CPU_VECTOR);
    puts("task 0 resume");
    //PostSem(&V);
    puts("task 0 done");
}


TASK(Task1) {
    puts("task 1 start");
    WaitSem(&V);
    puts("task1 resume");
}


int main() 
{
    puts("main start");
    InitSem(V, 0);
    ActivateTask(Task0);
    puts("main resume");
    PostSem(&V);
    puts("main idle");
    while(1);
    return 0;
}
