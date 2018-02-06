#ifndef SHARED_H
#define SHARED_H

#include "ee.h"
#include "ee_irq.h"

/* just a dummy delay */ 
static void mydelay(EE_UINT32 end)
{
    volatile EE_UINT32 i;
    for (i=0; i<end; i++)
        ;
    return;  
}

/* sets and resets a led configuration passed as parameter, leaving the other
 * bits unchanged
 * 
 * Note: led_blink is called both from Task1 and Task2. To avoid race 
 * conditions, we forced the atomicity of the led manipulation using IRQ
 * enabling/disabling. We did not use Resources in this case because the 
 * critical section is -really- small. An example of critical section using 
 * resources can be found in the osek_resource example.
 */
#define LED_ON_TIME_DELTA 10000000U
static void led_blink(enum EE_tc2x5_led_id theled)
{
  DisableAllInterrupts();
  EE_tc2x5_turn_led(theled, EE_TRIBOARD_2X5_LED_ON);
  EnableAllInterrupts();

  mydelay(LED_ON_TIME_DELTA);

  DisableAllInterrupts();
  EE_tc2x5_turn_led(theled, EE_TRIBOARD_2X5_LED_OFF);
  EnableAllInterrupts();
}

#endif /* SHARED_H */
