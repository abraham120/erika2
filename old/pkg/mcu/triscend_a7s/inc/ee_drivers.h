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
 * Author: 2001-2002 Marko Bertogna
 * CVS: $Id: ee_drivers.h,v 1.3 2006/05/14 17:50:30 pj Exp $
 */
 
#ifndef __INCLUDE_TRISCEND_DRIVERS_H__
#define __INCLUDE_TRISCEND_DRIVERS_H__

#include "arm7gnu/triscend_a7s/micro.h"


/*
 * Generic interrupts controlling
 */
 
__INLINE__ void __ALWAYS_INLINE__ EE_icu_init( void )		//Disable All Interrupts
{
    *INT_IRQ_ENABLE_CLEAR_REG = 0x0000ffff;
    *INT_FIQ_ENABLE_CLEAR_REG = 0x0000ffff;
    //in a7hal fa anke la copia di vector su internal sram. La eseguo invece in initdrvs.c
}

__INLINE__ void __ALWAYS_INLINE__ EE_enable_external_IRQ(EE_TYPEIRQ i)
{
    if ( i )
    	*INT_IRQ_ENABLE_REG = (i);
    else 
    	*INT_FIQ_ENABLE_REG = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_disable_external_IRQ(EE_TYPEIRQ i)
{
    if ( i )
    	*INT_IRQ_ENABLE_CLEAR_REG = (i);
    else
     	*INT_FIQ_ENABLE_CLEAR_REG = 1;
}

/*
__INLINE__ void __ALWAYS_INLINE__ EE_accept_external_IRQ(EE_TYPEIRQ i)
{
    *INTPND |= (i);
}

__INLINE__ void __ALWAYS_INLINE__ EE_clear_pending_IRQ(void)	//per me e' sbagliata
{
    *INTPND = 0x00000000;
}
*/



/*
 * Get the CPU clock speed.
 * This function is called to return the CPU clock frequency in Hz.
 * It can be called before or after RAM is initialized
 */
 
__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_clock_getFreq( void )
{
if ( *SYS_CLOCK_CONTROL_REG & (1 << 0) ? 0 : 1 ) return A7HAL_RING_FREQ;
if ( *SYS_CLOCK_CONTROL_REG & (1 << 1) ? 0 : 1 ) return A7HAL_XCLK_FREQ;
return (A7HAL_XTAL_FREQ * PLL_DIV_VALUE) >> PLL_SCALE_VALUE;
}



/*
 * Timers controlling
 */

#ifdef __TIMER_0_USED__

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_init(void)
{
	*TIMER0_CONTROL_REG = 0x00000000;	
	*TIMER0_CLEAR_REG = 0x00000001;
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_start(void)	//ablita timer in periodic mode, ck=bus_ck
{
//    *TIMER0_CONTROL_REG |= (1<<2);		//ck=bus_ck:16
//    *TIMER0_CONTROL_REG |= (1<<3);		//ck=bus_ck:256
	*TIMER0_CONTROL_REG |= 0x000000c0;		// enable timer in periodic mode 
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer0_start( EE_UINT16 count, EE_UREG control )
{
	*TIMER0_LOAD_REG = ( EE_UREG ) count;
	*TIMER0_CONTROL_REG = 0x00000080 | control;
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_stop(void)
{
	*TIMER0_CONTROL_REG &= ~(1<<7);		/* disable timer */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_0_set(EE_UINT16 count_down)
{
	*TIMER0_LOAD_REG = (EE_UREG) count_down;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_timer_0_get(void)
{
    return *TIMER0_VALUE_REG;
}

#endif /* __TIMER_0_USED__ */



#ifdef __TIMER_1_USED__

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_init(void)
{
	*TIMER1_CONTROL_REG = 0x00000000;	
	*TIMER1_CLEAR_REG = 0x00000001;
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_start(void)	//ablita timer in periodic mode, ck=bus_ck
{
//    *TIMER1_CONTROL_REG |= (1<<2);		//ck=bus_ck:16
//    *TIMER1_CONTROL_REG |= (1<<3);		//ck=bus_ck:256
	*TIMER1_CONTROL_REG |= 0x000000c0;		// enable timer in periodic mode 
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer1_start( EE_UINT16 count, EE_UREG control )
{
	*TIMER1_LOAD_REG = ( EE_UREG ) count;
	*TIMER1_CONTROL_REG = 0x00000080 | control;
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_stop(void)
{
        *TIMER1_CONTROL_REG &= ~(1<<7);		/* disable timer */
}

__INLINE__ void __ALWAYS_INLINE__ EE_timer_1_set(EE_UINT16 count_down)
{
	*TIMER1_LOAD_REG = (EE_UREG) count_down;
}

__INLINE__ EE_UINT16 __ALWAYS_INLINE__ EE_timer_1_get(void)
{
    return *TIMER1_VALUE_REG;
}

#endif /* __TIMER_1_USED__ */


/*
 * Watchdog controlling
 */

#ifdef __WATCHDOG_USED__

__INLINE__ void __ALWAYS_INLINE__ EE_watchdog_init(void)
{
	//reset watchdog: clear raw_int e ctrl-->0x0000 (watchdog disabled and no system reset)
	*WATCHDOG_CONTROL_REG = 0x00000002;			   													
   
   //known load value	
	*WATCHDOG_TIMEOUT_VAL_REG = 0x00000000;
}

__INLINE__ void __ALWAYS_INLINE__ EE_watchdog_start(void)	//enable watchdog timer 
{
	*WATCHDOG_CONTROL_REG |= 0x00000001;		
}

__INLINE__ void __ALWAYS_INLINE__ EE_watchdog0_start( EE_UREG count, EE_UREG reset )
{
	*WATCHDOG_CONTROL_REG = 0x00000002;				//reset watchdog	   														
	*WATCHDOG_TIMEOUT_VAL_REG = count;		
    	if (reset) 
		*WATCHDOG_CONTROL_REG = 0x00000005;			//enable watchdog with sys_reset at time_out	
    	else
  		*WATCHDOG_CONTROL_REG = 0x00000001;			//enable watchdog without sys_reset
}

__INLINE__ void __ALWAYS_INLINE__ EE_watchdog_stop(void)
{
	*WATCHDOG_CONTROL_REG &= 0xfffe;		/* disable watchdog */
}

__INLINE__ void __ALWAYS_INLINE__ EE_watchdog_set(EE_UREG count_down)
{
    	*WATCHDOG_TIMEOUT_VAL_REG = count_down;
}

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_watchdog_get(void)
{
    return *WATCHDOG_CURRENT_VAL_REG;
}

#endif /* __WATCHDOG_USED__ */


/*
 * LED controlling
 */

#ifdef __LED_USED__			

__INLINE__ void __ALWAYS_INLINE__ EE_LED_init(void)
{
    *LED_REG = 0xff;	//tutti i segmenti spenti
}

__INLINE__ void __ALWAYS_INLINE__ EE_LED_display(EE_UREG num)
{
    *LED_REG = EE_LED_numeric_display[num];	//definito in initdrvs.c
}

__INLINE__ void __ALWAYS_INLINE__ EE_LED_raw_display( EE_UREG segments )
{
    *LED_REG = segments & 0xff;	//display segments without translation
}

#endif /* __LED_USED__ */



/*
 * DIP switch controlling
 */

#ifdef __DIP_SWITCH_USED__	

__INLINE__ EE_UREG __ALWAYS_INLINE__ EE_dip_switch_get(void)
{
    return *DIP_REG & 0xff;
}

#endif /* __DIP_SWITCH_USED__ */



/* HAL Timer support */

#ifdef __TIME_SUPPORT__

/* Timer size */
typedef EE_UINT16 EE_TIME;
typedef EE_INT16 EE_STIME;

__INLINE__ EE_TIME __ALWAYS_INLINE__ EE_hal_gettime(void)
{
    return 0xffff - EE_timer_0_get();
}

#endif /* __TIME_SUPPORT__ */



#endif
