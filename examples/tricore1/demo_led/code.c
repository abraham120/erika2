#include <stdio.h>
#include "ee.h"

#include "board/infineon_tc1796b/inc/ee_board.h"
#include "mcu/tc179x/inc/ee_timer.h"
#include "mcu/tc179x/inc/ee_tc179xdefs.h"
#include "mcu/tc179x/inc/ee_stm.h"

#include <tc1796b/stm.h>
#include <tc1796b/port3-struct.h>


#include "cpu/tricore1/inc/ee_cpu.h"


#define STM_VECTOR 5

volatile int num = 0;

PORT3_t *port3 = (PORT3_t *)P3_BASE;

void led_on(int n) {
    if (n < 0)
        port3->OMR.reg = 0xffff0000;
    else
        port3->OMR.reg = (1 << n) << 16;
}

void led_off(int n) {
    if (n < 0)
        port3->OMR.reg = 0x0000ffff;
    else
        port3->OMR.reg = 1 << n;
}

void led_init()
{
    port3->IOCR0.reg = 0x80808080;
    port3->IOCR4.reg = 0x80808080;
    led_off(-1);
}

void delay(unsigned int ms)
{
    EE_UINT32 tps = EE_tc179x_stm_ticks_per_usec();
    EE_UINT32 del = tps * ms * 1000;
    EE_UINT32 now = EE_tc179x_stm_tim0.reg;
    while (EE_tc179x_stm_tim0.reg < now + del);
}


ISR(stm_isr)
{    
    if (++num > 255)
        ActivateTask(Task1);            
    EE_tc179x_stm_set_cmp0(STM_TIM0.reg + 1000000);
}


TASK(Task0)
{   
    while(1) {
        for (int i = 0; i < 8; i++) {
            if (num & (1 << i))
                led_on(i);
            else 
                led_off(i);
        }
    }
}


TASK(Task1)
{
    EE_hal_disableIRQ();
    for (int i = 0; i < 8; i++) {
        delay(100);
        led_off(i);
    }
    num = 0;
    EE_hal_enableIRQ();
}


int main() 
{
    led_init();

    /* Implement Alarms with either cmp0 or cmp1 */
    EE_tc179x_stm_cmp0_init(STM_VECTOR, STM_TIM0.reg + 10000);

    ActivateTask(Task0);

    while(1);

    return 0;
}
