/*
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: code.c,v 1.10 2006/08/31 17:16:26 pj Exp $
 */

#include "ee.h"
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"



/*
 * timer reset value (1 sec)
 *
 * 1 sec = 1000 * 1000 * 1000 nsec
 * timer tick = 50 MHz = 20 nsec
 */
//#define COUNTDOWN ((5 * 1000 * 1000 * 1000) / 20) /* 5 sec */
#define COUNTDOWN ((1 * 1000 * 1000 * 1000) / 20) /* 1 sec */
//#define COUNTDOWN ((100 * 1000 * 1000) / 20) /* 100 msec */
//#define COUNTDOWN ((10 * 1000 * 1000) / 20) /* 10 msec */
//#define COUNTDOWN ((1 * 1000 * 1000) / 20) /* 1 msec */
//#define COUNTDOWN ((100 * 1000) / 20) /* 100 usec */
//#define COUNTDOWN ((10 * 1000) / 20) /* 10 usec, too small! */


/*
 *  a short pause 
 */
//#define LOOP_LENGHT 100000
#define LOOP_LENGHT 40000
//#define LOOP_LENGHT 10000
//#define LOOP_LENGHT 1000
//#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1
void little_pause(void)
{
    int i=0;
    int j=0;
    
    for (i=0; i<LOOP_LENGHT; i++) {
        for(j=0; j<10; j++) {
            /* do nothing */
        }
    }
}

void timer1_handler(void)
{
    /* activate thread */
    ActivateTask(thread3);
}

int timer0_counter=0;

void timer0_handler(void)
{
  /* activate thread */
  timer0_counter = (timer0_counter+1)%16;
  EE_lcd_display(timer0_counter);
}


void main(void)
{
    /* peripherals initialization */
     EE_IC_clear_pending_IRQ();

     EE_IC_set_interrupt_all_as_FIQ(IRQ_TIMER0_MASK);
  
#ifdef __BUTTON_USED__
    EE_IC_enable_external_IRQ(IRQ_EXT0_MASK);	/* button */
    EE_button_init();
#endif
    
#ifdef __LEDS_USED__
    EE_leds_init();
#endif

#ifdef __LCD_USED__
    EE_lcd_init();
#endif

#ifdef __TIMER_USED__		/* defined through __TIMER_?_USED__ */
    EE_timer_init();
#endif

#ifdef __TIMER_0_USED__
    EE_IC_enable_external_IRQ(IRQ_TIMER0_MASK);
#endif

#ifdef __TIMER_1_USED__
    EE_IC_enable_external_IRQ(IRQ_TIMER1_MASK);
#endif

#ifdef __DIP_SWITCH_USED__
    /* do nothing */
#endif

#if defined(__ALLOW_NESTED_IRQ__) && defined(__IRQ_PRIORITY_MASKS__)
     EE_IC_compute_masks(EE_IC_EXTIRQ_masks, *INTMSK);
#endif     




    /* periodic timer start */
    EE_timer_1_set(COUNTDOWN);
    EE_timer_1_start();

    EE_timer_0_set(COUNTDOWN*2);
    EE_timer_0_start();



    /* activate the first thread */
    ActivateTask(thread0);

    for (;;) {}
}
