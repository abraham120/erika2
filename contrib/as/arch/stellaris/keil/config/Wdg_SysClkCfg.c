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
 * fake-druid SysClk AUTOSAR WDG (Watchdog) Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2012, Giuseppe Serano
 */

/*
 * Wdg_SysClkCfg.c has implicit access to the Wdg_SysClkCfg.h through the
 * WdgSysClk.h file.
 */
#include "WdgSysClk.h"

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
#define	WDG_SYSCLK_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_SYSCLK_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_SYSCLK_AR_MAJOR_VERSION ) || \
    ( WDG_SYSCLK_AR_MAJOR_VERSION != WDG_SYSCLK_AR_RELEASE_MAJOR_VERSION )
#error	WdgSysClk: version mismatch.
#endif
#if	0
/*
 * SYSCLK WDG External Configuration.
 */
const Wdg_SysClk_ExternalConfigType	WdgSysClkExternalConfiguration = {
  0x00000000U,				/* WdgExternalContainerRef.	      */
};
#endif

/*
 * SYSCLK WDG Fast Mode Settings.
 */
const Wdg_SysClk_SettingsFastType	WdgSysClkSettingsFast = {
					/* WdgCtl:			      */
#ifdef	DEBUG
  WDG_SYSCLK_CTL_DBG_STALL	|	/* - Watchdog Debug Stall.	      */
#endif	/* DEBUG */
#ifdef	__AS_CFG_WDG_SYSCLK_FAST_MODE_RESET__
  WDG_SYSCLK_CTL_RST_EN		|	/* - Watchdog Reset Enable.	      */
#endif	/* __AS_CFG_WDG_SYSCLK_FAST_MODE_RESET__ */
#ifdef	__AS_CFG_WDG_SYSCLK_FAST_MODE_NMI__
  WDG_SYSCLK_CTL_NMI_INT,		/* - NMI Watchdog Interrupt.	      */
#else	/* __AS_CFG_WDG_SYSCLK_FAST_MODE_NMI__ */
  WDG_SYSCLK_CTL_STD_INT,		/* - Standard Watchdog Interrupt.     */
#endif	/* !__AS_CFG_WDG_SYSCLK_FAST_MODE_NMI__ */
  0x0005U,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_SYSCLK_FAST_MODE_NOTIFICATION__
  &Wdg_SysClk_Notification_Fast,	/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_SYSCLK_FAST_MODE_NOTIFICATION__ */
  NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_SYSCLK_FAST_MODE_NOTIFICATION__ */
};

#if	( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON )
/*
 * SYSCLK WDG Off Mode Settings.
 */
const Wdg_SysClk_SettingsOffType		WdgSysClkSettingsOff = {
  0x00000000U,				/* WdgDummy.			      */
};
#endif	/* ( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON ) */

/*
 * SYSCLK WDG Slow Mode Settings.
 */
const Wdg_SysClk_SettingsSlowType	WdgSysClkSettingsSlow = {
					/* WdgCtl:			      */
#ifdef	DEBUG
  WDG_SYSCLK_CTL_DBG_STALL	|	/* - Watchdog Debug Stall.	      */
#endif	/* DEBUG */
#ifdef	__AS_CFG_WDG_SYSCLK_SLOW_MODE_RESET__
  WDG_SYSCLK_CTL_RST_EN		|	/* - Watchdog Reset Enable.	      */
#endif	/* __AS_CFG_WDG_SYSCLK_SLOW_MODE_RESET__ */
#ifdef	__AS_CFG_WDG_SYSCLK_SLOW_MODE_NMI__
  WDG_SYSCLK_CTL_NMI_INT,		/* - NMI Watchdog Interrupt.	      */
#else	/* __AS_CFG_WDG_SYSCLK_SLOW_MODE_NMI__ */
  WDG_SYSCLK_CTL_STD_INT,		/* - Standard Watchdog Interrupt.     */
#endif	/* !__AS_CFG_WDG_SYSCLK_SLOW_MODE_NMI__ */
  0x0014U,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_SYSCLK_SLOW_MODE_NOTIFICATION__
  &Wdg_SysClk_Notification_Slow,		/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_SYSCLK_SLOW_MODE_NOTIFICATION__ */
  NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_SYSCLK_NOTIFICATION_SLOW__ */
};

/*
 * This container is the base of a multiple configuration set.
 */
const Wdg_SysClk_ConfigType		Wdg_SysClk_Config[] = {
  { /* WDG_SYSCLK_CONFIG_TEST */
#if	( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON )
    WDGIF_OFF_MODE,			/* WdgDefaultMode.		      */
#else	/* ( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON ) */
    WDGIF_SLOW_MODE,			/* WdgDefaultMode.		      */
#endif	/* !( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON ) */
#if	0
    &WdgSysClkExternalConfiguration,	/* WdgExternalConfiguration.	      */
#endif
    &WdgSysClkSettingsFast,		/* WdgSettingsFast.		      */
#if	( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON )
    &WdgSysClkSettingsOff,		/* WdgSettingsOff.		      */
#endif	/* ( WDG_SYSCLK_DISABLE_ALLOWED == STD_ON ) */
    &WdgSysClkSettingsSlow,		/* WdgSettingsSlow.		      */
  },
};
