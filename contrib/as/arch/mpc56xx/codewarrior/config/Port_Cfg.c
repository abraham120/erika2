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

/** @file   Port_Cfg.c
 *  @brief  fake-druid AUTOSAR PORT Driver Configuration Source File.
 *
 *  Configured for (MCU): Freescale MPC5643L (Leopard)
 *
 *  @author Errico Guidieri
 *  @date   2012
 */

#define PORT_AR_RELEASE_MAJOR_VERSION 4
#define PORT_AR_RELEASE_MINOR_VERSION 0

#include "Port.h"

/*
 * PORT114: For included (external) header files:
 *    - <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 *    - <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 *    shall be verified.
 */
#if !defined( PORT_AR_MAJOR_VERSION ) || \
    ( PORT_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION )
#error  Port: version mismatch.
#endif

/*
 * Port Pins:PORT_B_PIN_6 Modes Configuration Container.
 */
const Port_PinModeConfType PortBPin6Conf[] = {
  {
    PORT_B_PIN_6_OUT_CLOCK,                     /* Port pin mode.     */
    PORT_OUTPUT_ASSIGNMENT_ALT_MODE_1 |         /* Alt. Mode 1        */
    PORT_OUTPUT_BUFFER_ENABLE |                 /* Port Output Buffer */
    PORT_SLEW_RATE_CONTROL,                     /* Slew Rate High     */
  }
};

/*
 * Port Pins:PORT_B_PIN_7 Modes Configuration Container.
 */
const Port_PinModeConfType PortBPin7Conf[] = {
  {
    PORT_B_PIN_7_IN_ADC0_0,                     /* Port pin mode.     */
    PORT_ANALOG_PAD_CONTROL                     /* Port Analog Input  */
  }
};

/*
 * Port Pins:PORT_B_PIN_8 Modes Configuration Container.
 */
const Port_PinModeConfType PortBPin8Conf[] = {
  {
    PORT_B_PIN_8_IN_ADC0_1,                     /* Port pin mode.     */
    PORT_ANALOG_PAD_CONTROL                     /* Port Analog Input  */
  }
};

/*
 * Port Pins:PORT_C_PIN_1 Modes Configuration Container.
 */
const Port_PinModeConfType PortCPin1Conf[] = {
  {
    PORT_C_PIN_1_IN_ADC0_2,                     /* Port pin mode.     */
    PORT_ANALOG_PAD_CONTROL                     /* Port Analog Input  */
  }
};

/*
 * Port Pins:PORT_C_PIN_14 Modes Configuration Container.
 */
const Port_PinModeConfType PortCPin14Conf[] = {
  {
    PORT_C_PIN_14_OUT_CTU_0_EXT_TGR,            /* Port pin mode.     */
    PORT_OUTPUT_ASSIGNMENT_ALT_MODE_2 |         /* Alt. Mode 2        */
    PORT_OUTPUT_BUFFER_ENABLE |                 /* Port Output Buffer */
    PORT_SLEW_RATE_CONTROL                      /* Slew Rate High     */
  }
};

/*
 * Port Pins:PORT_C_PIN_15 Modes Configuration Container.
 */
const Port_PinModeConfType  PortCPin15Conf[] = {
  {
    PORT_C_PIN_15_FLEXPWM0_A1,                  /* Port pin mode.     */
    PORT_OUTPUT_ASSIGNMENT_ALT_MODE_3 |         /* Alt. Mode 3        */
    PORT_OUTPUT_BUFFER_ENABLE                   /* Port Output Buffer */
  }
};

/*
 * Port Pins:PORT_D_PIN_4 Modes Configuration Container.
 */
const Port_PinModeConfType PortDPin4Conf[] = {
  {
    PORT_PIN_MODE_DIO,                          /* Port pin mode.     */
    PORT_OUTPUT_BUFFER_ENABLE |                 /* Port Output Buffer */
    PORT_SLEW_RATE_CONTROL                      /* Slew Rate High     */
  }
};

/*
 * Port Pins:PORT_D_PIN_5 Modes Configuration Container.
 */
const Port_PinModeConfType PortDPin5Conf[] = {
  {
    PORT_PIN_MODE_DIO,                          /* Port pin mode.     */
    PORT_OUTPUT_BUFFER_ENABLE                 /* Port Output Buffer */
  }
};

/*
 * Port Pins:PORT_D_PIN_6 Modes Configuration Container.
 */
const Port_PinModeConfType PortDPin6Conf[] = {
  {
    PORT_PIN_MODE_DIO,                          /* Port pin mode.     */
    PORT_OUTPUT_BUFFER_ENABLE                   /* Port Output Buffer */
  }
};

/*
 * Port Pins:PORT_D_PIN_7 Modes Configuration Container.
 */
const Port_PinModeConfType PortDPin7Conf[] = {
  {
    PORT_PIN_MODE_DIO,                          /* Port pin mode.     */
    PORT_OUTPUT_BUFFER_ENABLE                   /* Port Output Buffer */
  }
};

/*
 * Port Pins:PORT_D_PIN_10 Modes Configuration Container.
 */
const Port_PinModeConfType  PortDPin10Conf[] = {
  {
    PORT_D_PIN_10_FLEXPWM0_A0,                  /* Port pin mode.     */
    PORT_OUTPUT_ASSIGNMENT_ALT_MODE_1 |         /* Alt. Mode 1        */
    PORT_OUTPUT_BUFFER_ENABLE                   /* Port Output Buffer */
  }
};

/*
 * Port Pins:PORT_D_PIN_11 Modes Configuration Container.
 */
const Port_PinModeConfType  PortDPin11Conf[] = {
  {
    PORT_D_PIN_11_FLEXPWM0_B0,                  /* Port pin mode.     */
    PORT_OUTPUT_ASSIGNMENT_ALT_MODE_1 |         /* Alt. Mode 1        */
    PORT_OUTPUT_BUFFER_ENABLE                   /* Port Output Buffer */
  }
};

/*
 * Port Pins:PORT_G_PIN_3 Modes Configuration Container.
 */
const Port_PinModeConfType  PortGPin3Conf[] = {
  {
    PORT_G_PIN_3_FLEXPWM0_A2,                  /* Port pin mode.     */
    PORT_OUTPUT_ASSIGNMENT_ALT_MODE_1 |        /* Alt. Mode 1        */
    PORT_OUTPUT_BUFFER_ENABLE                  /* Port Output Buffer */
  }
};

/*
 * Demo Port Pins Configuration.
 */
const Port_PinConfType DemoPortPins[] = {
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_B_PIN_6,                 /* PortPinId                    */
    PORT_B_PIN_6_OUT_CLOCK,       /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortBPin6Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_IN,                  /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_B_PIN_7,                 /* PortPinId                    */
    PORT_B_PIN_7_IN_ADC0_0,       /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortBPin7Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_IN,                  /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_B_PIN_8,                 /* PortPinId                    */
    PORT_B_PIN_8_IN_ADC0_1,       /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortBPin8Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_IN,                  /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_C_PIN_1,                 /* PortPinId                    */
    PORT_C_PIN_1_IN_ADC0_2,       /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortCPin1Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                     /* PortPinDirection             */
    FALSE,                            /* PortPinDirectionChangeable   */
    PORT_C_PIN_14,                    /* PortPinId                    */
    PORT_C_PIN_14_OUT_CTU_0_EXT_TGR,  /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,               /* PortPinLevelValue            */
    1U,                               /* PortPinModeNumber            */
    &PortCPin14Conf[0],               /* PortPinSupportedModes        */
    FALSE                             /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_C_PIN_15,                /* PortPinId                    */
    PORT_C_PIN_15_FLEXPWM0_A1,    /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortCPin15Conf[0],           /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_D_PIN_4,                 /* PortPinId                    */
    PORT_PIN_MODE_DIO,            /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortDPin4Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_D_PIN_5,                 /* PortPinId                    */
    PORT_PIN_MODE_DIO,            /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortDPin5Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    TRUE,                         /* PortPinDirectionChangeable   */
    PORT_D_PIN_6,                 /* PortPinId                    */
    PORT_PIN_MODE_DIO,            /* PortPinInitialMode           */
    PORT_PIN_LEVEL_HIGH,          /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortDPin6Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    TRUE,                         /* PortPinDirectionChangeable   */
    PORT_D_PIN_7,                 /* PortPinId                    */
    PORT_PIN_MODE_DIO,            /* PortPinInitialMode           */
    PORT_PIN_LEVEL_HIGH,          /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortDPin7Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_D_PIN_10,                /* PortPinId                    */
    PORT_D_PIN_10_FLEXPWM0_A0,    /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortDPin10Conf[0],           /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  },
  {
    PORT_PIN_OUT,                 /* PortPinDirection             */
    FALSE,                        /* PortPinDirectionChangeable   */
    PORT_G_PIN_3,                 /* PortPinId                    */
    PORT_G_PIN_3_FLEXPWM0_A2,     /* PortPinInitialMode           */
    PORT_PIN_LEVEL_LOW,           /* PortPinLevelValue            */
    1U,                           /* PortPinModeNumber            */
    &PortGPin3Conf[0],            /* PortPinSupportedModes        */
    FALSE                         /* PortPinModeChangeable        */
  }
};


/*
 * PORT121: This container is the base of a multiple configuration set.
 */
const Port_ConfigType Port_Config[] = {
  {
    11U,                /* PortNumberOfPortPins */
    &DemoPortPins[0]    /* PortPins   */
  }
};
