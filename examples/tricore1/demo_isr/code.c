#include "ee.h"
#include "cpu/tricore1/inc/ee_trap.h"
#include "cpu/tricore1/inc/ee_int.h"

#include <stdio.h>
#include <tc1796b/cps.h>

#define VECTOR_ISR1 5
#define VECTOR_ISR2 4

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


ISR1(isr1)
{
    puts("isr1");
    char *p = (char *)0x0;
    *p = 'x';
}


ISR(isr2)
{
    puts("isr2");
    local_int(VECTOR_ISR1);
}


TSR(syscall) 
{    
    printf("syscall %d\n", EE_tin);
    ActivateTask(Task0);
}


TSR(segfault)
{
    puts("segfault");
    while(1);
}


TASK(Task0)
{
    puts("task0");
    local_int(VECTOR_ISR2);
}


TASK(Task1)
{
    puts("task1");
    asm("syscall 42");
}


int main() 
{

    ActivateTask(Task1);
    puts("idle");
    while(1);

    return 0;
}
