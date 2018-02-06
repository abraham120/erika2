#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "altera_avalon_timer_regs.h"
#include "ee.h"

#define ONEMILLION 1000000

int task0_counter; 

TASK(mytask0)
{
    int i;
    printf("task0: %d\n", task0_counter++);
    for (i=0; i<ONEMILLION/32; i++);
}
