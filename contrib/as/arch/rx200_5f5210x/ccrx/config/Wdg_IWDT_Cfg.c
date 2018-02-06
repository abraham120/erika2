/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * fake-druid IWDT AUTOSAR WDG (Watchdog) Driver Configuration Source File.
 *
 * Configured for (MCU): Renesas RX210R5F5210x
 *
 * Author: 2013, Gianluca Franchino
 */

/*
 * Wdg_IWDT_Cfg.c has implicit access to the Wdg_IWDT_Cfg.h through the
 * WdgIWDT.h file.
 */
#include "Wdg_IWDT.h"

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
#define	WDG_IWDT_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_IWDT_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_IWDT_AR_MAJOR_VERSION ) || \
    ( WDG_IWDT_AR_MAJOR_VERSION != WDG_IWDT_AR_RELEASE_MAJOR_VERSION )
#error	Wdg_IWDT: version mismatch.
#endif
#if	0
/*
 * IWDT WDG External Configuration.
 */
const Wdg_IWDT_ExternalConfigType	WdgIWDTExternalConfiguration = {
		0x00000000U,				/* WdgExternalContainerRef.	      */
};
#endif

/*
 * IWDT WDG Fast Mode Settings.
 */
const Wdg_IWDT_SettingsFastType	WdgIWDTSettingsFast = {
					/* WdgCtl:			      */
#ifdef	__AS_CFG_WDG_IWDT_FAST_MODE_RESET__
		WDG_IWDT_CTL_RST_EN |			/* - Watchdog Reset Enable.	      */
#else
		WDG_IWDT_CTL_NMI_INT |		/* - NMI Watchdog Interrupt.	      */
#endif	/* __AS_CFG_WDG_IWDT_FAST_MODE_RESET__ */
#ifdef __AS_CFG_WDG_IWDT_FAST_MODE_STOP_ON_SLEEP__
		WDG_IWDT_COUNT_STOP_EN,
#else	
		WDG_IWDT_COUNT_STOP_DIS,
#endif	/*!__AS_CFG_WDG_IWDT_FAST_MODE_STOP_ON_SLEEP__*/
		0x000FU,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_IWDT_FAST_MODE_NOTIFICATION__
		&Wdg_IWDT_Notification_Fast,	/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_IWDT_FAST_MODE_NOTIFICATION__ */
		NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_IWDT_FAST_MODE_NOTIFICATION__ */
};


#if	( WDG_IWDT_DISABLE_ALLOWED == STD_ON )
/*
 * IWDT WDG Off Mode Settings.
 */
const Wdg_IWDT_SettingsOffType		WdgIWDTSettingsOff = {
		0x00000000U,				/* WdgDummy.	*/
};
#endif	/* ( WDG_IWDT_DISABLE_ALLOWED == STD_ON ) */

/*
 * IWDT WDG Slow Mode Settings.
 */
const Wdg_IWDT_SettingsSlowType	WdgIWDTSettingsSlow = {
					/* WdgCtl:			      */
#ifdef	__AS_CFG_WDG_IWDT_SLOW_MODE_RESET__
		WDG_IWDT_CTL_RST_EN |			/* - Watchdog Reset Enable.	      */
#else
		WDG_IWDT_CTL_NMI_INT |		/* - NMI Watchdog Interrupt.	      */
#endif	/* __AS_CFG_WDG_IWDT_SLOW_MODE_RESET__ */
#ifdef __AS_CFG_WDG_IWDT_SLOW_MODE_STOP_ON_SLEEP__
		WDG_IWDT_COUNT_STOP_EN,
#else	
		WDG_IWDT_COUNT_STOP_DIS,
#endif	/*!__AS_CFG_WDG_IWDT_SLOW_MODE_STOP_ON_SLEEP__*/
		0x007CU,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_IWDT_SLOW_MODE_NOTIFICATION__
		&Wdg_IWDT_Notification_Slow,	/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_IWDT_SLOW_MODE_NOTIFICATION__ */
		NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_IWDT_NOTIFICATION_SLOW__ */
};


/*
 * This container is the base of a multiple configuration set.
 */
const Wdg_IWDT_ConfigType		Wdg_IWDT_Config[] = {
  { /* WDG_IWDT_CONFIG_TEST */
#if	( WDG_IWDT_DISABLE_ALLOWED == STD_ON )
		  WDGIF_OFF_MODE,			/* WdgDefaultMode.		      */
#else	/* ( WDG_IWDT_DISABLE_ALLOWED == STD_ON ) */
		  WDGIF_DEFAULT_MODE,			/* WdgDefaultMode.		      */
#endif	/* !( WDG_IWDT_DISABLE_ALLOWED == STD_ON ) */
#if	0
		  &WdgIWDTExternalConfiguration,	/* WdgExternalConfiguration.*/
#endif
		  &WdgIWDTSettingsFast,		/* WdgSettingsFast.		      */
#if	( WDG_IWDT_DISABLE_ALLOWED == STD_ON )
		  &WdgIWDTSettingsOff,		/* WdgSettingsOff.		      */
#endif	/* ( WDG_IWDT_DISABLE_ALLOWED == STD_ON ) */
		  &WdgIWDTSettingsSlow,		/* WdgSettingsSlow.		      */

  },
};
