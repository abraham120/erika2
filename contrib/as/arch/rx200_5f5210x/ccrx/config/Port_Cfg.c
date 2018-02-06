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
 * fake-druid AUTOSAR PORT Driver Configuration Source File.
 *
 *  Configured for (MCU): Renesas RX210R5F5210x
 *
 *  @author	Gianluca Franchino
 *  @date	2012
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
 * 	PORT_1_PIN_4,
 * 	PORT_1_PIN_5,
 * 	PORT_1_PIN_6,
 * 	PORT_1_PIN_7
 * Modes Configuration Container.
 */
const Port_PinModeConfType Port1Pin0To4Conf[] = {
		{ /* USER LEDS */
		  PORT_PIN_MODE_DIO,			/* Port pin mode: digital I/O	*/
		  PORT_PIN_HW_CFG_DIO |			/* Digital I/O pin  */
		  PORT_PIN_HW_CFG_DRVCAP_HIGH	/* 8-mA Drive Select  */
		}
};

/*
 * Port Pins:
 * 	PORT_3_PIN_1
 * 	PORT_3_PIN_3,
 * 	PORT_3_PIN_4,
 * Modes Configuration Container.
 */
const Port_PinModeConfType Port3Pin1_3_4Conf[] = {
		{ /* SWITCH2 and SWITCH3 */
		  PORT_PIN_MODE_ISEL,		/* Port pin mode: IRQ */
		  PORT_PIN_HW_CFG_DIO |		/* Digital I/O pin  */
		  PORT_PIN_HW_CFG_ISEL		/* Select as IRQ pin  */
		}
};

/*
 * Port Pins:
 * 	TXDx of SCIx
 * Modes Configuration Container.
 */
const Port_PinModeConfType PortTXDPinConf[] = {
	{ /* SCI TXDx*/
		PORT_PIN_MODE_SCI,		/* Port pin mode: SCI */
		PORT_PIN_PFS_TXD		/* Select as TX pin  */
	}
};

/*
 * Port Pins:
 * 	RXDx of SCIx
 * Modes Configuration Container.
 */
const Port_PinModeConfType PortRXDPinConf[] = {
	{ /* SCI RXDx*/
		PORT_PIN_MODE_SCI,		/* Port pin mode: SCI */
		PORT_PIN_PFS_RXD		/* Select as RX pin  */
	}
};

/*
 * DIO Port Pins Configuration.
 */
const Port_PinConfType DIOPortPins[] = {
		{ /* USER LED0 */
			PORT_PIN_OUT,			/* PortPinDirection		      	*/
			FALSE,					/* PortPinDirectionChangeable	*/
			PORT_1_PIN_4,			/* PortPinId			      	*/
			PORT_PIN_MODE_DIO,		/* PortPinInitialMode			*/
			PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue			*/
			0x00000001,				/* PortPinModeNumber			*/
			&Port1Pin0To4Conf[0],	/* PortPinSupportedModes		*/
			FALSE					/* PortPinModeChangeable		*/
		},
		{ /* USER LED1 */
			PORT_PIN_OUT,			/* PortPinDirection			 	*/
			FALSE,					/* PortPinDirectionChangeable	*/
			PORT_1_PIN_5,			/* PortPinId					*/
			PORT_PIN_MODE_DIO,		/* PortPinInitialMode			*/
			PORT_PIN_LEVEL_LOW,		/* PortPinLevelValue			*/
			0x00000001,				/* PortPinModeNumber			*/
			&Port1Pin0To4Conf[0],	/* PortPinSupportedModes		*/
			FALSE					/* PortPinModeChangeable		*/
		},
		{ /* USER LED2 */
			PORT_PIN_OUT,			/* PortPinDirection				*/
			FALSE,					/* PortPinDirectionChangeable	*/
			PORT_1_PIN_6,			/* PortPinId					*/
			PORT_PIN_MODE_DIO,		/* PortPinInitialMode			*/
			PORT_PIN_LEVEL_LOW,		/* PortPinLevelValue			*/
			0x00000001,				/* PortPinModeNumber			*/
			&Port1Pin0To4Conf[0],	/* PortPinSupportedModes		*/
			FALSE					/* PortPinModeChangeable		*/
	  },
	  { /* USER LED3 */
			PORT_PIN_OUT,			/* PortPinDirection				*/
			FALSE,					/* PortPinDirectionChangeable	*/
			PORT_1_PIN_7,			/* PortPinId					*/
			PORT_PIN_MODE_DIO,		/* PortPinInitialMode			*/
			PORT_PIN_LEVEL_LOW,		/* PortPinLevelValue			*/
			0x00000001,				/* PortPinModeNumber			*/
			&Port1Pin0To4Conf[0],	/* PortPinSupportedModes		*/
			FALSE					/* PortPinModeChangeable		*/
	  }
};

/*
 * IRQ Port Pins Configuration.
 */
const Port_PinConfType IRQPortPins[] = {
		{ /* USER SWITCH 1 */
			PORT_PIN_IN,			/* PortPinDirection				*/
		    FALSE,					/* PortPinDirectionChangeable	*/
		    PORT_3_PIN_1,			/* PortPinId					*/
		    PORT_PIN_MODE_ISEL,		/* PortPinInitialMode			*/
		    PORT_PIN_LEVEL_LOW,		/* PortPinLevelValue			*/
		    0x00000001,				/* PortPinModeNumber			*/
		    &Port3Pin1_3_4Conf[0],	/* PortPinSupportedModes		*/
		    FALSE					/* PortPinModeChangeable		*/
		},
		{ /* USER SWITCH 2 */
		    PORT_PIN_IN,			/* PortPinDirection				*/
		    FALSE,					/* PortPinDirectionChangeable	*/
		    PORT_3_PIN_3,			/* PortPinId					*/
		    PORT_PIN_MODE_ISEL,		/* PortPinInitialMode			*/
		    PORT_PIN_LEVEL_LOW,		/* PortPinLevelValue			*/
		    0x00000001,				/* PortPinModeNumber			*/
		    &Port3Pin1_3_4Conf[0],	/* PortPinSupportedModes		*/
		    FALSE					/* PortPinModeChangeable		*/
		},
		{ /* USER SWITCH 3  */
			PORT_PIN_IN,			/* PortPinDirection				*/
			FALSE,					/* PortPinDirectionChangeable	*/
		    PORT_3_PIN_4,			/* PortPinId					*/
		    PORT_PIN_MODE_ISEL,		/* PortPinInitialMode			*/
		    PORT_PIN_LEVEL_LOW,		/* PortPinLevelValue			*/
		    0x00000001,				/* PortPinModeNumber			*/
		    &Port3Pin1_3_4Conf[0],	/* PortPinSupportedModes		*/
		    FALSE					/* PortPinModeChangeable		*/
		}
};

/*
 * SCI Port Pins Configuration.
 */
const Port_PinConfType SCIPortPins[] = {
	{
		PORT_PIN_OUT,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable 	*/
		PORT_2_PIN_0,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		  	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortTXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable	   	*/
	},
	{
		PORT_PIN_IN,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable	*/
		PORT_2_PIN_1,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortRXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable		*/
	},
	{
		PORT_PIN_OUT,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable 	*/
		PORT_2_PIN_6,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortTXDPinConf[0],		/* PortPinSupportedModes	  	*/
		FALSE					/* PortPinModeChangeable	  	*/
	},
	{
		PORT_PIN_IN,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable	*/
		PORT_3_PIN_0,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortRXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable	   	*/
	},
#if 0	
	{
		PORT_PIN_OUT,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable 	*/
		PORT_A_PIN_2,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortTXDPinConf[0],		/* PortPinSupportedModes	  	*/
		FALSE					/* PortPinModeChangeable	  	*/
	},
	{
		PORT_PIN_IN,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable	*/
		PORT_A_PIN_4,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortRXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable	   	*/
	},
	{
		PORT_PIN_OUT,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable 	*/
		PORT_3_PIN_3,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortTXDPinConf[0],		/* PortPinSupportedModes	  	*/
		FALSE					/* PortPinModeChangeable	  	*/
	},
	{
		PORT_PIN_IN,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable	*/
		PORT_3_PIN_2,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortRXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable	   	*/
	},
	{
		PORT_PIN_OUT,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable 	*/
		PORT_C_PIN_6,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortTXDPinConf[0],		/* PortPinSupportedModes	  	*/
		FALSE					/* PortPinModeChangeable	  	*/
	},
	{
		PORT_PIN_IN,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable	*/
		PORT_C_PIN_7,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortRXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable	   	*/
	},
#endif
	{
		PORT_PIN_OUT,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable 	*/
		PORT_C_PIN_3,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortTXDPinConf[0],		/* PortPinSupportedModes	  	*/
		FALSE					/* PortPinModeChangeable	  	*/
	},
	{
		PORT_PIN_IN,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable	*/
		PORT_C_PIN_2,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortRXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable	   	*/
	},
#if 0
	{
		PORT_PIN_OUT,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable 	*/
		PORT_E_PIN_2,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortTXDPinConf[0],		/* PortPinSupportedModes	  	*/
		FALSE					/* PortPinModeChangeable	  	*/
	},
	{
		PORT_PIN_IN,			/* PortPinDirection		      	*/
		FALSE,					/* PortPinDirectionChangeable	*/
		PORT_E_PIN_1,			/* PortPinId			      	*/
		PORT_PIN_MODE_SCI,		/* PortPinInitialMode		   	*/
		PORT_PIN_LEVEL_HIGH,	/* PortPinLevelValue		   	*/
		0x00000001,				/* PortPinModeNumber		   	*/
		&PortRXDPinConf[0],		/* PortPinSupportedModes	   	*/
		FALSE					/* PortPinModeChangeable	   	*/
	}
#endif
};


/*
 * PORT121:	This container is the base of a multiple configuration set.
 */
const Port_ConfigType Port_Config[] = {
		{ /* PORT_CONFIG_DIO */
			4U,		/* PortNumberOfPortPins	*/
			&DIOPortPins[0]	/* PortPins		*/
		},
		{ /* PORT_CONFIG_IRQ */
			3U,		/* PortNumberOfPortPins	*/
			&IRQPortPins[0]	/* PortPins		*/
		},
		{
#if 0
			14U, /* PortNumberOfPortPins	*/
#else
			6U, /* PortNumberOfPortPins	*/
#endif
			&SCIPortPins[0] /*PortPins */
		}
};

