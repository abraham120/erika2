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

/** 
	@file ee_gpio.c
	@brief GPIO library source file. 
	@author Dario Di Stefano
	@date 2010
*/

#include "mcu/mico32/inc/ee_gpio.h"


/******************************************************************************/
/*                             Global Variables                               */
/******************************************************************************/
#ifdef EE_GPIO1_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO1_NAME_UC, EE_GPIO1_NAME_LC)
#endif

#ifdef EE_GPIO2_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO2_NAME_UC, EE_GPIO2_NAME_LC)
#endif

#ifdef EE_GPIO3_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO3_NAME_UC, EE_GPIO3_NAME_LC)
#endif

#ifdef EE_GPIO4_NAME_UC
DEFINE_STRUCT_GPIO(EE_GPIO4_NAME_UC, EE_GPIO4_NAME_LC)
#endif


/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#if defined(__USE_GPIO_IRQ__) || defined(__USE_ETHERNET_IRQ__) || defined(__USE_ZIGBEE_IRQ__)
/* GPIO common handler */
void EE_gpio_common_handler(int level)
{
    EE_gpio_st *gpio_sp = EE_get_gpio_st_from_level(level);
    MicoGPIO_t *gp = gpio_sp->base; 
	
    /* Save edgeCpature register */
    gpio_sp->flag = EE_hal_gpio_read_edgeCapture(gp);
    /* Clear edgeCpature register */
    EE_hal_gpio_write_edgeCapture(gp, ~gpio_sp->flag);
    /* Call user callback */
    if( gpio_sp->cbk != EE_NULL_CBK )
        gpio_sp->cbk();

    return;	
}
#endif
