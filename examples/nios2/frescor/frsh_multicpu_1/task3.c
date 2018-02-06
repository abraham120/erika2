#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "altera_avalon_timer_regs.h"
#include "ee.h"

#define ONEMILLION 1000000

int task3_counter; 

TASK(mytask3)
{
    int i;
    printf("task3: %d\n", task3_counter++);
    for (i=0; i<ONEMILLION/32; i++);
}
