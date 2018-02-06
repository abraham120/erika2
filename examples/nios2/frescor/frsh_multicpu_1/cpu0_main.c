#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "altera_avalon_timer_regs.h"
#include "ee.h"

/* 
 * This data is local to cpu0. 
 * The scope of the symbol is cpu0 ONLY, which means:
 * - other cpus cannot access this data
 * - other cpus can have data having the same name
 * 
 * This variable is just an example, it is not used 
 * in the rest of the application
 */
int a_local_counter;


/*
 * Handle button_pio interrupts activates the three tasks in the system.
 * Note that the tasks are activated regardless of their placement
 * on a particular CPU.
 */
static void handle_button_interrupts_cpu0(void* context, alt_u32 id)
{
  /* used to acknowledge (using leds) that an interrupt arrived */
  static int led_counter=0;
  
  /* Activate the three tasks */
  ActivateTask(mytask0);  
  ActivateTask(mytask1);  
  ActivateTask(mytask2);  
  ActivateTask(mytask3);  

  /* display the counter value on the leds */  
  led_counter = (led_counter+1)%256;
  IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, led_counter);
  
  /* Reset the Button's edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0);
}

/* Initialize the button_pio. */
static void init_button_pio_0()
{
  /* Enable all 2 button interrupts. */
  IOWR_ALTERA_AVALON_PIO_IRQ_MASK(BUTTON_PIO_BASE, 0x3);
  /* Reset the edge capture register. */
  IOWR_ALTERA_AVALON_PIO_EDGE_CAP(BUTTON_PIO_BASE, 0x0);
  /* Register the interrupt handler. */
  alt_irq_register( BUTTON_PIO_IRQ, NULL, handle_button_interrupts_cpu0 ); 
}

/* defined into cover.c */
void Test0(void);
void Test1(void);
void Test2(void);
void Test3(void);


alt_u32 myalarm_callback (void* arg)
{
  ActivateTask(mytask2);  
  ActivateTask(mytask3);  
  return 10;
}


alt_alarm myalarm;
void alarm_go(void)
{
  alt_alarm_start (&myalarm, 1, 
                   myalarm_callback, NULL);
}


int main()
{ 
  /* 
   * CPU 0
   * Initialization part
   */
  
  /* set the stack space to a known pattern, to allow stack statistics by
   * Lauterbach Trace32 */
  EE_trace32_stack_init();

  printf("Hello from CPU 0!\n");
  printf("Press a button to activate the tasks\n");
  
  init_button_pio_0();
  
  /* program the conter timer */
  frsh_init();

  alarm_go();

  /* Background activities, none in this demo! */
  for (;;);
  
  return 0;
  
  
}
