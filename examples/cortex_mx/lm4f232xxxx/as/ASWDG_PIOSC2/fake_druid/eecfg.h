/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * fake-druid eecfg.h
 *
 * Author: 2012  Giuseppe Serano
 */
#ifndef __EECFG_H__
#define __EECFG_H__



#define RTDRUID_CONFIGURATOR_NUMBER 1276



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 1
    #define BackgroundTask 0

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__
#define __AUTOSAR_R4_0__
#define __AS_DIO_DRIVER__
#define __AS_MCU_DRIVER__
#define __AS_PORT_DRIVER__
#define __AS_SCI_DRIVER__
#define __AS_CFG_SCI_WDG_PIOSC_TESTS__
#define __AS_WDG_PIOSC_DRIVER__
#define __AS_CFG_WDG_PIOSC_VERSION_INFO_API__
#define __AS_CFG_WDG_PIOSC_DISABLE_ALLOWED__
#define __AS_CFG_WDG_PIOSC_NMI_ISR__
#define __AS_CFG_WDG_PIOSC_FAST_MODE_NMI__
#define __AS_CFG_WDG_PIOSC_FAST_MODE_RESET__
#define __AS_CFG_WDG_PIOSC_FAST_MODE_NOTIFICATION__
#define __ADD_LIBS__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __STELLARIS__
#define __LM4F232xxxx__
#define __CORTEX_MX__
#define __CORTEX_M4__
#define __KEIL__
#define __OO_BCC1__
#define __OO_EXTENDED_STATUS__
#define __MONO__
#define __OO_NO_ALARMS__
#define __OO_NO_RESOURCES__
#define __OO_AUTOSTART_TASK__
#define __ALLOW_NESTED_IRQ__

#endif




/***************************************************************************
 *
 * ISR definition
 *
 **************************************************************************/
#define EE_CORTEX_MX_NMI_ISR Wdg_PIOsc_ISR
#define EE_CORTEX_MX_NMI_ISR_PRI EE_ISR_PRI_1


#endif

