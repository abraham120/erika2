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

#ifdef	__AS_CFG_PORT_ICU__
const Port_PinModeConfType PortPinsICUConf[] = {
  {
    PORT_PIN_MODE_ICU,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN	  |	/* Digital Enable + Pull-up.		      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_PIN_HW_CFG_PUR	  |	/* Pull-Up Select.			      */
    PORT_M_PMC_ICU		/* Port M ICU Mux Control.		      */
  }
};
#endif	/* __AS_CFG_PORT_ICU__ */

#ifdef	__AS_CFG_PORT_ICU_ARISTON_TESTS__
const Port_PinModeConfType PortPinsAristonTestsICUConf[] = {
  {
    PORT_PIN_MODE_ICU,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN	  |	/* Digital Enable + Pull-up.		      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_PIN_HW_CFG_PUR	  |	/* Pull-Up Select.			      */
    PORT_F_PMC_ICU		/* Port F ICU Mux Control.		      */
  }
};
#endif	/* __AS_CFG_PORT_ICU_ARISTON_TESTS__ */

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
 * Port Pins:PORT_D_PIN_6 Modes Configuration Container.
 */
const Port_PinModeConfType PortDPin6Conf[] = {
  {
    PORT_PIN_MODE_DIO,				/* Port pin mode.	      */
    PORT_PIN_HW_CFG_DEN				/* Digital Enable.	      */
  }
};

/*
 * Port Pin: PORT_C_PIN_4 Modes Configuration Container.
 */
const Port_PinModeConfType PortCPin4Conf[] = {
  {
    PORT_PIN_MODE_SCI,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_PIN_HW_CFG_PUR |	/* Pull-Up Select			      */
    PORT_C_PIN_4_PMC_SCI_4_RX	/* Port C UART4 Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_C_PIN_5 Modes Configuration Container.
 */
const Port_PinModeConfType PortCPin5Conf[] = {
  {
    PORT_PIN_MODE_SCI,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_C_PIN_5_PMC_SCI_4_TX	/* Port C UART4 Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_F_PIN_0 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin0Conf[] = {
  {
    PORT_PIN_MODE_SPI,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_PIN_HW_CFG_PUR |	/* Pull-Up Select			      */
    PORT_F_PIN_0_PMC_SPI_1_RX	/* Port F SSI1 Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_F_PIN_1 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin1Conf[] = {
  {
    PORT_PIN_MODE_SPI,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_F_PIN_1_PMC_SPI_1_TX	/* Port F SSI1 Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_F_PIN_2 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin2Conf[] = {
  {
    PORT_PIN_MODE_SPI,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_F_PIN_2_PMC_SPI_1_CLK	/* Port F SSI1 Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_F_PIN_3 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin3Conf[] = {
  {
    PORT_PIN_MODE_DIO,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN		/* Digital Enable.			      */
  }
};

/*
 * Port Pin: PORT_F_PIN_4 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin4Conf[] = {
  {
    PORT_PIN_MODE_DIO,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN		/* Digital Enable.			      */
  }
};

/*
 * Port Pin: PORT_F_PIN_5 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin5Conf[] = {
  {
    PORT_PIN_MODE_DIO,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_PUR		/* Pull-Up Select			      */
  }
};

/*
 * Port Pin: PORT_F_PIN_6 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin6Conf[] = {
  {
    PORT_PIN_MODE_DIO,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_PUR		/* Pull-Up Select			      */
  }
};

/*
 * Port Pin: PORT_F_PIN_7 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin7Conf[] = {
  {
    PORT_PIN_MODE_DIO,		/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN		/* Digital Enable.			      */
  }
};

#ifdef	__AS_CFG_PORT_KEIL_ULINK_PRO__

/*
 * Port Pin: PORT_F_PIN_0 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin0TRD2Conf[] = {
  {
    PORT_PIN_MODE_TRACE,	/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_F_PIN_0_PMC_TRACE_TRD2	/* Port F Trace Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_F_PIN_1 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin1TRD1Conf[] = {
  {
    PORT_PIN_MODE_TRACE,	/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_F_PIN_1_PMC_TRACE_TRD1	/* Port F Trace Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_F_PIN_2 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin2TRD0Conf[] = {
  {
    PORT_PIN_MODE_TRACE,	/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_F_PIN_2_PMC_TRACE_TRD0	/* Port F Trace Mux Control.		      */
  }
};

/*
 * Port Pin: PORT_F_PIN_3 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin3TRCLKConf[] = {
  {
    PORT_PIN_MODE_TRACE,		/* Port pin mode.		      */
    PORT_PIN_HW_CFG_DEN |		/* Digital Enable.		      */
    PORT_PIN_HW_CFG_AFSEL |		/* Alternate Function Select.	      */
    PORT_F_PIN_3_PMC_TRACE_TRCLK	/* Port F Trace Mux Control.	      */
  }
};

/*
 * Port Pin: PORT_F_PIN_4 Modes Configuration Container.
 */
const Port_PinModeConfType PortFPin4TRD3Conf[] = {
  {
    PORT_PIN_MODE_TRACE,	/* Port pin mode.			      */
    PORT_PIN_HW_CFG_DEN |	/* Digital Enable.			      */
    PORT_PIN_HW_CFG_AFSEL |	/* Alternate Function Select.		      */
    PORT_F_PIN_4_PMC_TRACE_TRD3	/* Port F Trace Mux Control.		      */
  }
};

#endif	/* __AS_CFG_PORT_KEIL_ULINK_PRO__ */

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
 * SCI Port Pins Configuration.
 */
const Port_PinConfType SCIPortPins[] = {
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin4Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_5,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin5Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* USER DIO OUTPUT */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_D_PIN_6,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortDPin6Conf[0],			/* PortPinSupportedModes	      */
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
 * SPI Microchip ENC28J60 Port Pins Configuration.
 */
const Port_PinConfType SPIENC28J60PortPins[] = {
  { /* SSI1 RX */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_0,			/* PortPinId			      */
    PORT_PIN_MODE_SPI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin0Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* SSI1 TX */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_1,			/* PortPinId			      */
    PORT_PIN_MODE_SPI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin1Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* SSI1 CLK */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_2,			/* PortPinId			      */
    PORT_PIN_MODE_SPI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin2Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* SSI1 CS */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_3,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin3Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* RST */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin4Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* INT */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_5,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin5Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* WOL */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_6,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin6Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* CLK */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_7,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin7Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
   {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin4Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_5,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin5Conf[0],			/* PortPinSupportedModes	      */
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

#ifdef	__AS_CFG_PORT_ICU__
/*
 * ICU Port Pins Configuration.
 */
const Port_PinConfType ICUPortPins[] = {
  { /* T4 CCP0 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_0,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsICUConf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* T4 CCP1 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_1,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsICUConf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* T5 CCP0 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_2,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsICUConf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* T5 CCP1 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_3,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsICUConf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* WT5 CCP0 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_D_PIN_6,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsICUConf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* WT5 CCP1 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_D_PIN_7,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsICUConf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin4Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_5,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin5Conf[0],			/* PortPinSupportedModes	      */
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
#endif	/* __AS_CFG_PORT_ICU__ */

#ifdef	__AS_CFG_PORT_ICU_ARISTON_TESTS__
/*
 * Ariston Tests ICU Port Pins Configuration.
 */
const Port_PinConfType AristonTestsICUPortPins[] = {
  { /* T2 CCP0 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsAristonTestsICUConf[0],	/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* T2 CCP1 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_5,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsAristonTestsICUConf[0],	/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
    { /* T3 CCP0 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_6,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsAristonTestsICUConf[0],	/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* T3 CCP1 */
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_7,			/* PortPinId			      */
    PORT_PIN_MODE_ICU,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortPinsAristonTestsICUConf[0],	/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_0,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_1,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_2,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_3,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_M_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_DIO,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortMPin0To4Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_IN,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin4Conf[0],			/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  {
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_C_PIN_5,			/* PortPinId			      */
    PORT_PIN_MODE_SCI,			/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_HIGH,		/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortCPin5Conf[0],			/* PortPinSupportedModes	      */
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
#endif	/* __AS_CFG_PORT_ICU_ARISTON_TESTS__ */

#ifdef	__AS_CFG_PORT_KEIL_ULINK_PRO__
/*
 * KEIL ULINK Pro Port Pins Configuration.
 */
const Port_PinConfType KeilULinkProPortPins[] = {
  { /* TRACE TRD2 */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_0,			/* PortPinId			      */
    PORT_PIN_MODE_TRACE,		/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin0TRD2Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* TRACE TRD1 */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_1,			/* PortPinId			      */
    PORT_PIN_MODE_TRACE,		/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin1TRD1Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* TRACE TRD0 */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_2,			/* PortPinId			      */
    PORT_PIN_MODE_TRACE,		/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin2TRD0Conf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* TRACE TRCLK */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_3,			/* PortPinId			      */
    PORT_PIN_MODE_TRACE,		/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin3TRCLKConf[0],		/* PortPinSupportedModes	      */
    FALSE				/* PortPinModeChangeable	      */
  },
  { /* TRACE TRD3 */
    PORT_PIN_OUT,			/* PortPinDirection		      */
    FALSE,				/* PortPinDirectionChangeable	      */
    PORT_F_PIN_4,			/* PortPinId			      */
    PORT_PIN_MODE_TRACE,		/* PortPinInitialMode		      */
    PORT_PIN_LEVEL_LOW,			/* PortPinLevelValue		      */
    0x00000001,				/* PortPinModeNumber		      */
    &PortFPin4TRD3Conf[0],		/* PortPinSupportedModes	      */
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
#endif	/* __AS_CFG_PORT_KEIL_ULINK_PRO__ */


/*
 * PORT121:	This container is the base of a multiple configuration set.
 */
const Port_ConfigType Port_Config[] = {
  { /* PORT_CONFIG_DIO */
    6U,		/* PortNumberOfPortPins	*/
    &DIOPortPins[0]	/* PortPins		*/
  },
  { /* PORT_CONFIG_SCI */
    4U,		/* PortNumberOfPortPins	*/
    &SCIPortPins[0]	/* PortPins		*/
  },
  { /* PORT_CONFIG_SPI_ENC28J60 */
    11U,			/* PortNumberOfPortPins	*/
    &SPIENC28J60PortPins[0]	/* PortPins		*/
  },
#ifdef	__AS_CFG_PORT_ICU__
  { /* PORT_CONFIG_ICU */
    10U,			/* PortNumberOfPortPins	*/
    &ICUPortPins[0]		/* PortPins		*/
  },
#endif
#ifdef	__AS_CFG_PORT_ICU_ARISTON_TESTS__
  { /* PORT_CONFIG_ARISTON_TESTS_ICU */
    12U,			/* PortNumberOfPortPins	*/
    &AristonTestsICUPortPins[0]	/* PortPins		*/
  },
#endif
#ifdef	__AS_CFG_PORT_KEIL_ULINK_PRO__
  { /* PORT_CONFIG_KEIL_ULINK_PRO */
    6U,			/* PortNumberOfPortPins	*/
    &KeilULinkProPortPins[0]	/* PortPins		*/
  },
#endif	/* __AS_CFG_PORT_KEIL_ULINK_PRO__ */
};
