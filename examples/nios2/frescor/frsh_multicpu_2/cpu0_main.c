/* Altera Includes */ 
#include "system.h"
#include <altera_avalon_pio_regs.h>
#include <stdio.h>
#include "sys/alt_alarm.h"
#include "altera_avalon_timer_regs.h"
#include "ee.h"


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
  ActivateTask(Task1);  
  ActivateTask(Task2);  
  ActivateTask(Task3);  
  ActivateTask(Task4);  
  
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


alt_u32 myalarm_callback (void* arg)
{
  ActivateTask(Task2);  
  ActivateTask(Task3);  
  return 10;
}


alt_alarm myalarm;
void vai_alarm(void)
{
  alt_alarm_start (&myalarm, 1, 
                   myalarm_callback, NULL);
}


TASK(Task1)
{
    static int i;
    printf("%d\n",i++);
    IOWR_ALTERA_AVALON_PIO_DATA(LED_PIO_BASE, i & 0xff);
    ActivateTask(Task2);
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

  init_button_pio_0();
  
  /* program the conter timer */
  frsh_init();

  ActivateTask(Task1);

  for (;;);
  
  return 0;
  
  
}
