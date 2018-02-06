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
 * fake-druid PCLK AUTOSAR WDG (Watchdog) Driver Configuration Source File.
 *
 * Configured for (MCU): Renesas RX210R5F5210x
 *
 * Author: 2013, Gianluca Franchino
 */

/*
 * Wdg_PCLK_Cfg.c has implicit access to the Wdg_PCLK_Cfg.h through the
 * WdgPCLK.h file.
 */
#include "Wdg_PCLK.h"

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
#define	WDG_PCLK_AR_RELEASE_MAJOR_VERSION	4
#define	WDG_PCLK_AR_RELEASE_MINOR_VERSION	0

#if !defined( WDG_PCLK_AR_MAJOR_VERSION ) || \
    ( WDG_PCLK_AR_MAJOR_VERSION != WDG_PCLK_AR_RELEASE_MAJOR_VERSION )
#error	Wdg_PCLK: version mismatch.
#endif
#if	0
/*
 * PCLK WDG External Configuration.
 */
const Wdg_PCLK_ExternalConfigType	WdgPCLKExternalConfiguration = {
		0x00000000U,				/* WdgExternalContainerRef.	      */
};
#endif

/*
 * PCLK WDG Fast Mode Settings.
 */
const Wdg_PCLK_SettingsFastType	WdgPCLKSettingsFast = {
					/* WdgCtl:			      */
#ifdef	__AS_CFG_WDG_PCLK_FAST_MODE_RESET__
		WDG_PCLK_CTL_RST_EN,			/* - Watchdog Reset Enable.	      */
#else
		WDG_PCLK_CTL_NMI_INT,		/* - NMI Watchdog Interrupt.	      */
#endif	/* __AS_CFG_WDG_PCLK_FAST_MODE_RESET__ */
		0x000FU,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_PCLK_FAST_MODE_NOTIFICATION__
		&Wdg_PCLK_Notification_Fast,	/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_PCLK_FAST_MODE_NOTIFICATION__ */
		NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_PCLK_FAST_MODE_NOTIFICATION__ */
};


#if	( WDG_PCLK_DISABLE_ALLOWED == STD_ON )
/*
 * PCLK WDG Off Mode Settings.
 */
const Wdg_PCLK_SettingsOffType		WdgPCLKSettingsOff = {
		0x00000000U,				/* WdgDummy.	*/
};
#endif	/* ( WDG_PCLK_DISABLE_ALLOWED == STD_ON ) */

/*
 * PCLK WDG Slow Mode Settings.
 */
const Wdg_PCLK_SettingsSlowType	WdgPCLKSettingsSlow = {
					/* WdgCtl:			      */
#ifdef	__AS_CFG_WDG_PCLK_SLOW_MODE_RESET__
		WDG_PCLK_CTL_RST_EN,			/* - Watchdog Reset Enable.	      */
#else
		WDG_PCLK_CTL_NMI_INT,		/* - NMI Watchdog Interrupt.	      */
#endif	/* __AS_CFG_WDG_PCLK_SLOW_MODE_RESET__ */
		0x007CU,				/* WdgTimeout.			      */
#ifdef	__AS_CFG_WDG_PCLK_SLOW_MODE_NOTIFICATION__
		&Wdg_PCLK_Notification_Slow,	/* WdgNotificationPtr.		      */
#else	/* __AS_CFG_WDG_PCLK_SLOW_MODE_NOTIFICATION__ */
		NULL_PTR,				/* WdgNotificationPtr.		      */
#endif	/* !__AS_CFG_WDG_PCLK_NOTIFICATION_SLOW__ */
};


/*
 * This container is the base of a multiple configuration set.
 */
const Wdg_PCLK_ConfigType		Wdg_PCLK_Config[] = {
  { /* WDG_PCLK_CONFIG_TEST */
#if	( WDG_PCLK_DISABLE_ALLOWED == STD_ON )
		  WDGIF_OFF_MODE,			/* WdgDefaultMode.		      */
#else	/* ( WDG_PCLK_DISABLE_ALLOWED == STD_ON ) */
		  WDGIF_DEFAULT_MODE,			/* WdgDefaultMode.		      */
#endif	/* !( WDG_PCLK_DISABLE_ALLOWED == STD_ON ) */
#if	0
		  &WdgPCLKExternalConfiguration,	/* WdgExternalConfiguration.*/
#endif
		  &WdgPCLKSettingsFast,		/* WdgSettingsFast.		      */
#if	( WDG_PCLK_DISABLE_ALLOWED == STD_ON )
		  &WdgPCLKSettingsOff,		/* WdgSettingsOff.		      */
#endif	/* ( WDG_PCLK_DISABLE_ALLOWED == STD_ON ) */
		  &WdgPCLKSettingsSlow,		/* WdgSettingsSlow.		      */

  },
};
