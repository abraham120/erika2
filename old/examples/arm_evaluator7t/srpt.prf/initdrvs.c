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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: initdrvs.c,v 1.3 2005/03/11 11:05:31 pj Exp $
 */

#include "code.h"
#include "ee.h"
#include "mcu/samsung_ks32c50100/inc/ee_ic.h"


void init_drivers(void)
{
    EE_IC_clear_pending_IRQ();

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

    /* for hal_gettime() */
#ifdef __TIME_SUPPORT__
    EE_timer_0_set(0xffffffff);
    EE_timer_0_start();
#endif
    
}

