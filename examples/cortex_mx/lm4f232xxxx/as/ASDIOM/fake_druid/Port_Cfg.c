/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * fake-druid AUTOSAR PORT Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2011, Giuseppe Serano
 */

#define	PORT_AR_RELEASE_MAJOR_VERSION	4
#define	PORT_AR_RELEASE_MINOR_VERSION	0

#include "Port.h"

/*
 * PORT114:	For included (external) header files:
 * 		- <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * 		shall be verified.
 */
#if !defined( PORT_AR_MAJOR_VERSION ) || \
    ( PORT_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION )
#error	Port: version mismatch.
#endif

/*
 * Port Pins:
 * 	PORT_M_PIN_0,
 * 	PORT_M_PIN_1,
 * 	PORT_M_PIN_2,
 * 	PORT_M_PIN_3,
 * 	PORT_M_PIN_4
 * Modes Configuration Container.
 */
const Port_PinModeConfType PortMPin0To4Conf[] = {
  { /* USER SWITCHES */
    PORT_PIN_MODE_DIO,				/* Port pin mode.	      */
    PORT_PIN_HW_CFG_DEN | PORT_PIN_HW_CFG_PUR	/* Digital Enable + Pull-up.  */
  }
};

/*
 * Port Pin:PORT_G_PIN_2 Modes Configuration Container.
 */
const Port_PinModeConfType PortGPin2Conf[] = {
  { /* USER LED */
    PORT_PIN_MODE_DIO,			/* Port pin mode.		      */
    PORT_PIN_HW_CFG_DEN			/* Digital Enable.		      */
  }
};

/*
 * DIO Port Pins Configuration.
 */
const Port_PinConfType DIOPortPins[] = {
  { /* USER SWITCH 1 (UP) */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_0,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* USER SWITCH 2 (DOWN) */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_1,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* USER SWITCH 3 (LEFT) */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_2,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* USER SWITCH 4 (RIGHT) */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_3,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* USER SWITCH 5 (SELECT/WAKE) */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* USER LED */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_G_PIN_2,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortGPin2Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  }
};

/*
 * PORT121:	This container is the base of a multiple configuration set.
 */
const Port_ConfigType Port_Config[] = {
  { /* PORT_CONFIG_DIO */
    0x00000006,		/* PortNumberOfPortPins	*/
    &DIOPortPins[0]	/* PortPins		*/
  },
};
