/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * This file is a modification of the standalone web server distributed in the
 * Nios II Forum. This demo in particular supports the RAW LWIP API using tasks to 
 *
 * This file is for testing stand-alone (NO_SYS) LWIP
 * using a RAM-based simple file system
 *
 */

#include "system.h"

#include "arch/init.h"
#include "lwip/ip_addr.h"
#include "lwip/tcpip.h"
#include "lwip/netif.h"
#include "netif/lan91c111if.h"

#include "httpd.h"
#include "echo.h"

#include "sys/alt_alarm.h"

/* Include ERIKA Enterprise header files */
#include "ee.h"

/* ---------- IP oriented addresses for ethernet adapter ---------- */
#define IPADDR0 192
#define IPADDR1 168
#define IPADDR2 1
#define IPADDR3 1

#define NETMASK0 255
#define NETMASK1 255
#define NETMASK2 255
#define NETMASK3 0

#define GWADDR0 192
#define GWADDR1 168
#define GWADDR2 1
#define GWADDR3 254

/* This simple function accept as parameter an integer that represents a number 
 * of milliseconds, and returns the number of system ticks needed to have that 
 * elapsed time
 */
static ALT_INLINE alt_u32 ALT_ALWAYS_INLINE ms2ticks(alt_u32 ms)
{
  return ((ms-1)*alt_ticks_per_second())/(1000)+1;
}  

/* Note: The local variables to the main thread has been put global
 */
//0.6.4 struct netif *netif;
struct netif netif;
struct ip_addr ipaddr, netmask, gw;
alt_alarm LWIP_timer_alarm;
alt_avalon_lan91c111_if* dev_list_ptr;

/*
 * This alarm callback is called inside the IRQ handler of the system timer
 * and it is used to activate the task that will execute the LWIP timers.
 * The alarm is a periodic alarm, so it is re-armed to the next period using
 * the return value.
 */
alt_u32 LWIP_timer_alarm_callback (void* arg)
{
  ActivateTask(LWIP_timer_task);
  return ms2ticks(TCP_TMR_INTERVAL);
}


int main(void)
{
  /* as the first thing, let's start ERIKA Enterprise 
   * The StartOS will automatically activate the LWIP_startup_task which is
   * responsible for the LWIP startup
   */
  StartOS(OSDEFAULTAPPMODE);
  
  for (;;);
}

/*
 * This is the LWIP startup task, responsible for the LWIP and http/echo server
 * startup.
 * 
 * There is no need to protect the LWIP calls using GetResource and ReleaseResource
 * because the task has the same priority of the other two LWIP tasks (see the
 * OIL file).
 */
TASK(LWIP_startup_task)
{
  dev_list_ptr =  (alt_avalon_lan91c111_if*)alt_ethernet_device_list.next;

  printf("Example web server using Light-weight IP (LWIP)\n");
  printf("and simple RAM-based file system.\n\n");

/*
 * Initialize lwip
 */
  lwip_init();

  printf ("Setting IP address to: %d.%d.%d.%d\n", IPADDR0, IPADDR1, IPADDR2, IPADDR3);
  printf ("Setting netmask to: %d.%d.%d.%d\n", NETMASK0, NETMASK1, NETMASK2, NETMASK3);
  printf ("Setting gateway address to: %d.%d.%d.%d\n", GWADDR0, GWADDR1, GWADDR2, GWADDR3);
  IP4_ADDR(&ipaddr, IPADDR0, IPADDR1, IPADDR2, IPADDR3);
  IP4_ADDR(&netmask, NETMASK0, NETMASK1, NETMASK2, NETMASK3);
  IP4_ADDR(&gw, GWADDR0, GWADDR1, GWADDR2, GWADDR3);

//0.6.4   netif = netif_add(&ipaddr, &netmask, &gw,
  netif_add(&netif, &ipaddr, &netmask, &gw,
                                          (void*)dev_list_ptr,
                                          lan91c111if_init, 
                                          ip_input);
//0.6.4 netif_set_default(&netif);
  netif_set_default(&netif);
      
  /*
   * Initialize application(s)
   */
  httpd_init();
  echo_init();

  /*
   * The original standalone LWIP example, after the initialization of all the 
   * applications, included a forever loop on the LWIP timers.
   * 
   * The loop is now replaced by:
   * - a periodic alarm that activates the LWIP timers
   * - a forever loop "for(;;)", that is basically the OS "background task"
   */
  alt_alarm_start (&LWIP_timer_alarm, ms2ticks(TCP_TMR_INTERVAL),
                   LWIP_timer_alarm_callback, NULL);
  
  printf("LWIP initialization completed\n");
  
  TerminateTask();
}

/*
 * This task is used to execute the LWIP timers
 */
TASK(LWIP_timer_task) 
{
  static int i=0;
#if IP_REASSEMBLY
  static int j=0;
#endif

  tcp_tmr();
  
  if (++i==50) {
    //etharp_tmr();
    i=0;
  }       

#if IP_REASSEMBLY
  if (++j==4) { 
    /* once every second... Please note that this is not the same 
     * periodicity as in the original example
     */
    ip_reass_timer();
    j=0;
  }       
#endif

  TerminateTask();
}

/* This integer is used to signal that an interrupt have to be serviced, and it 
 * is used to avoid the race condition that appear when the task activate 
 * arrives after the end of lan91c111if_service but before the end of the task
 * Since the piece of code is very small, we decided handle the integer with 
 * interrupt disabled. There is no need to "count" the interrupts, because the 
 * service routine is internally implemented using a while loop that consumes
 * all the pending packets.
 */
static volatile int LWIP_irq_pending_service = 0;

/*
 * This function is called by the modified version of the LAN91c111 interrupt 
 * handler. The function basically activates the service task
 */
void LWIP_irq_callback(void)
{
  /* activate the task only if it is the first pending service request */
  if (!LWIP_irq_pending_service) {
    ActivateTask(LWIP_service_task);
    
    /* this assignment can be done without any interrupt disabling because 
     * interrupts are already disabled! */
    LWIP_irq_pending_service = 1;
  }
}

/*
 * This task is activated when an interrupt arrives from the ethernet card.
 * To avoid too much overhead in activating the task every interrupt, if another 
 * interrupt arrives while the task is still executing, the task is
 * not activated again.
 */ 
TASK(LWIP_service_task) 
{
  alt_irq_context c;
  
  do {
    //0.6.4   lan91c111if_service(netif);
    lan91c111if_service(&netif);
    
    /* Terminate the task only if it is the latest request.
     * note that the task is terminated with irq disabled to avoid the race 
     * condition mentioned earlier. 
     * IRQ will be reenabled automatically by the OS at the next context switch.
     */
    c = alt_irq_disable_all();
    if (!LWIP_irq_pending_service)
      TerminateTask();
    LWIP_irq_pending_service=0;
    alt_irq_enable_all(c);
  } while (1);  
}


/*
 * FINAL IMPORTANT NOTE: when writing application tasks
 * that directly calls the LWIP RAW interface, remember to take care of the 
 * race conditions between the LWIP tasks and the application tasks. Please
 * refer to the tutorial PDF file for more information.
 *
 * In this example, a way to solve the race condition is to give the LWIP 
 * tasks the highest priority in the system, and to protect the (lower priority) 
 * application tasks directly using the LWIP functions (e.g. to bind, listen, accept 
 * connections; the callbacks do not need to be protected because they are 
 * called inside the LWIP tasks) with an explicit call to 
 * GetResource(LWIP_mutex) and ReleaseResource(LWIP_mutex) (where LWIP_mutex
 * is the name of the resource defined in the OIL file).
 */
