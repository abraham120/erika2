/*
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: thumb.c,v 1.4 2006/08/31 17:16:26 pj Exp $
 */

#include "ee.h"

void little_pause(void);

TASK(thread0)
{
    GetResource(MUTEX_sync);

    EE_led_1_on();

    little_pause();

    ActivateTask(thread1);
    
    EE_led_1_off();

    ReleaseResource(MUTEX_sync);
}



TASK(thread1)
{
    EE_led_2_on();
    little_pause();
    EE_led_2_off();

    ActivateTask(thread2);
}



TASK(thread2)
{
    GetResource(MUTEX_sync);

    EE_led_3_on();
    little_pause();
    EE_led_3_off();

    ActivateTask(thread0);

    ReleaseResource(MUTEX_sync);
}



TASK(thread3)
{
    EE_led_4_on();
    little_pause();
    EE_led_4_off();
}
