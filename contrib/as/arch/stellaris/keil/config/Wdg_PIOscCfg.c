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
 * fake-druid PIOsc AUTOSAR WDG (Watchdog) Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2012, Giuseppe Serano
 */

/*
 * Wdg_PIOscCfg.c has implicit access to the Wdg_PIOscCfg.h through the
 * WdgPIOsc.h file.
 */
#include "WdgPIOsc.h"

/* 
 * WDG087:	The Wdg module shall avoid the integration of incompatible files
 * 		by the following pre-processor checks:
 * 		For included (external) header files:
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		shall be verified.
 * 		If the values are not identical to the values expected by the
 * 		Wdg module, an error shall be reported. (BSW167, BSW004)
 */
#define	WDG_PIOSC_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_PIOSC_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_PIOSC_AR_MAJOR_VERSION ) || \
    ( WDG_PIOSC_AR_MAJOR_VERSION != WDG_PIOSC_AR_RELEASE_MAJOR_VERSION )
#error	WdgPIOsc: version mismatch.
#endif

#if	0
/*
 * PIOSC WDG External Configuration.
 */
const Wdg_PIOsc_ExternalConfigType	WdgPIOscExternalConfiguration = {
  0x00000000U,				/* WdgExternalContainerRef.	      */
};
#endif

/*
 * PIOSC WDG Fast Mode Settings.
 */
const Wdg_PIOsc_SettingsFastType	WdgPIOscSettingsFast = {
					/* WdgCtl:			      */
#ifdef	DEBUG
  WDG_PIOSC_CTL_DBG_STALL	|	/* - Watchdog Debug Stall.	      */
#endif	/* DEBUG */
#ifdef	__AS_CFG_WDG_PIOSC_FAST_MODE_RESET__
  WDG_PIOSC_CTL_RST_EN		|	/* - Watchdog Reset Enable.	      */
#endif	/* __AS_CFG_WDG_PIOSC_FAST_MODE_RESET__ */
#ifdef	__AS_CFG_WDG_PIOSC_FAST_MODE_NMI__
  WDG_PIOSC_CTL_NMI_INT,		/* - NMI Watchdog Interrupt.	      */
#else	/* __AS_CFG_WDG_PIOSC_FAST_MODE_NMI__ */
  WDG_PIOSC_CTL_STD_INT,		/* - Standard Watchdog Interrupt.     */
#endif	/* !__AS_CFG_WDG_PIOSC_FAST_MODE_NMI__ */
  0x0005U,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_PIOSC_FAST_MODE_NOTIFICATION__
  &Wdg_PIOsc_Notification_Fast,		/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_PIOSC_FAST_MODE_NOTIFICATION__ */
  NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_PIOSC_FAST_MODE_NOTIFICATION__ */
};

#if	( WDG_PIOSC_DISABLE_ALLOWED == STD_ON )
/*
 * PIOSC WDG Off Mode Settings.
 */
const Wdg_PIOsc_SettingsOffType		WdgPIOscSettingsOff = {
  0x00000000U,				/* WdgDummy.			      */
};
#endif	/* ( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */

/*
 * PIOSC WDG Slow Mode Settings.
 */
const Wdg_PIOsc_SettingsSlowType	WdgPIOscSettingsSlow = {
					/* WdgCtl:			      */
#ifdef	DEBUG
  WDG_PIOSC_CTL_DBG_STALL	|	/* - Watchdog Debug Stall.	      */
#endif	/* DEBUG */
#ifdef	__AS_CFG_WDG_PIOSC_SLOW_MODE_RESET__
  WDG_PIOSC_CTL_RST_EN		|	/* - Watchdog Reset Enable.	      */
#endif	/* __AS_CFG_WDG_PIOSC_SLOW_MODE_RESET__ */
#ifdef	__AS_CFG_WDG_PIOSC_SLOW_MODE_NMI__
  WDG_PIOSC_CTL_NMI_INT,		/* - NMI Watchdog Interrupt.	      */
#else	/* __AS_CFG_WDG_PIOSC_SLOW_MODE_NMI__ */
  WDG_PIOSC_CTL_STD_INT,		/* - Standard Watchdog Interrupt.     */
#endif	/* !__AS_CFG_WDG_PIOSC_SLOW_MODE_NMI__ */
  0x0014U,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_PIOSC_SLOW_MODE_NOTIFICATION__
  &Wdg_PIOsc_Notification_Slow,		/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_PIOSC_SLOW_MODE_NOTIFICATION__ */
  NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_PIOSC_NOTIFICATION_SLOW__ */
};

/*
 * This container is the base of a multiple configuration set.
 */
const Wdg_PIOsc_ConfigType		Wdg_PIOsc_Config[] = {
  { /* WDG_PIOSC_CONFIG_TEST */
#if	( WDG_PIOSC_DISABLE_ALLOWED == STD_ON )
    WDGIF_OFF_MODE,			/* WdgDefaultMode.		      */
#else	/* ( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */
    WDGIF_SLOW_MODE,			/* WdgDefaultMode.		      */
#endif	/* !( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */
#if	0
    &WdgPIOscExternalConfiguration,	/* WdgExternalConfiguration.	      */
#endif
    &WdgPIOscSettingsFast,		/* WdgSettingsFast.		      */
#if	( WDG_PIOSC_DISABLE_ALLOWED == STD_ON )
    &WdgPIOscSettingsOff,		/* WdgSettingsOff.		      */
#endif	/* ( WDG_PIOSC_DISABLE_ALLOWED == STD_ON ) */
    &WdgPIOscSettingsSlow,		/* WdgSettingsSlow.		      */
  },
};
