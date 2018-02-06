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

/** @file   Port.c
 *  @brief  AUTOSAR PORT Driver Source File.
 *
 *  This file contains AUTOSAR PORT Driver implementation
 *  for Freescale Leopard (MPC5643L) and Codewarrior compiler.
 *
 *  @author Errico Guidieri
 *  @date 2012
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

/* In Order to use Validate Macros in Utility.h I define AS_MODULE_ID */
#define AS_MODULE_ID PORT_MODULE_ID

#include "ee.h"
#include "Hardware.h" /* Hardware Abstraction Header File. */
#include "Utility.h"

/*
 * Global that holds all global data for Port Driver
 */
static struct Port_GlobalType
{
  boolean                 Init;       /* PORT Driver Initialized? */
  const Port_ConfigType   *ConfigPtr; /* Actual Configuration */
} Port_Global = {FALSE, NULL};


/* Used to change PIN Direction */
#define EE_PORT_CLEAR_INPUT_BUFFER_ENABLE   0xFDFFU
#define EE_PORT_CLEAR_OUTPUT_BUFFER_ENABLE  0xFEFFU
static void EE_port_set_pin_direction(const Port_PinType pin_id, const 
    Port_PinDirectionType direction)
{
  if ( direction == PORT_PIN_OUT ) {
    /* Port Pin As Output. */
    SIUL.PCR[pin_id].R = (SIUL_GET_PCR(pin_id) & 
      EE_PORT_CLEAR_INPUT_BUFFER_ENABLE) | PORT_OUTPUT_BUFFER_ENABLE;
  } else {
    /* Port Pin As Input. */
    SIUL.PCR[pin_id].R = (SIUL_GET_PCR(pin_id) & 
      EE_PORT_CLEAR_OUTPUT_BUFFER_ENABLE) | PORT_INPUT_BUFFER_ENABLE;
  }
}

/* There is no smarter way to map Pins to alternate input functions */
static void EE_set_input_multiplexer_register(const Port_PinType
    pin_id, const Port_PinModeType pin_mode)
{
  if(pin_mode != PORT_PIN_MODE_DIO) {
    /* Set Only if PSMI.PDSEL is != from 0 */
    switch(pin_id) {
      case  PORT_A_PIN_9:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[27].B.PADSEL = 1U;
        }
      break;
      case  PORT_A_PIN_10:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[3].B.PADSEL = 1U;
        }
      break;
      case  PORT_A_PIN_11:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[1].B.PADSEL = 1U;
        }
      break;
      case  PORT_A_PIN_12:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[22].B.PADSEL = 1U;
        }
      break;
      case  PORT_A_PIN_13:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[26].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[2].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_3) != 0U ) {
          SIUL.PSMI[16].B.PADSEL = 1U;
        }
      break;
      case  PORT_A_PIN_15:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[14].B.PADSEL = 1U;
        }
      break;
      case  PORT_B_PIN_1:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[33].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_3) != 0U ) {
          SIUL.PSMI[34].B.PADSEL = 1U;
        }
      break;
      case  PORT_B_PIN_7:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[31].B.PADSEL = 1U;
        }
      break;
      case  PORT_B_PIN_8:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[8].B.PADSEL = 2U;
        }
      break;
      case  PORT_B_PIN_14:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[7].B.PADSEL = 2U;
        }
      break;
      case  PORT_C_PIN_10:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[23].B.PADSEL = 1U;
        }
      break;
      case  PORT_C_PIN_11:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[7].B.PADSEL = 1U;
        }
      break;
      case  PORT_C_PIN_14:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[11].B.PADSEL = 1U;
        }
      break;
      case  PORT_C_PIN_15:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[9].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[21].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_3) != 0U ) {
          SIUL.PSMI[0].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_4) != 0U ) {
          SIUL.PSMI[15].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_0:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[10].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[25].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_1:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[11].B.PADSEL = 2U;
        }
      break;
      case  PORT_D_PIN_2:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[12].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_3:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[13].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[23].B.PADSEL = 2U;
        }
      break;
      case  PORT_D_PIN_4:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[14].B.PADSEL = 2U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[27].B.PADSEL = 2U;
        }
      break;
      case  PORT_D_PIN_6:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[30].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[17].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_8:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[13].B.PADSEL = 2U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[19].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_10:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[20].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[35].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_11:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[24].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[36].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_12:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[28].B.PADSEL = 1U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[32].B.PADSEL = 1U;
        }
      break;
      case  PORT_D_PIN_14:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[25].B.PADSEL = 2U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[38].B.PADSEL = 1U;
        }
      break;
      case  PORT_E_PIN_13:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[8].B.PADSEL = 1U;
        }
      break;
      case  PORT_E_PIN_14:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[14].B.PADSEL = 3U;
        }
      break;
      case  PORT_F_PIN_0:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[21].B.PADSEL = 2U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[37].B.PADSEL = 1U;
        } 
      break;
      case  PORT_F_PIN_12:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[12].B.PADSEL = 2U;
        } 
      break;
      case  PORT_F_PIN_13:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[13].B.PADSEL = 3U;
        } 
      break;
      case  PORT_F_PIN_15:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[32].B.PADSEL = 2U;
        } 
      break;
      case  PORT_G_PIN_2:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[29].B.PADSEL = 1U;
        } 
      break;
      case  PORT_G_PIN_3:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[22].B.PADSEL = 2U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[7].B.PADSEL = 3U;
        } 
      break;
      case  PORT_G_PIN_4:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[26].B.PADSEL = 2U;
        }
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_2) != 0U ) {
          SIUL.PSMI[8].B.PADSEL = 3U;
        } 
      break;
      case  PORT_G_PIN_5:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[30].B.PADSEL = 2U;
        } 
      break;
      case  PORT_G_PIN_6:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[23].B.PADSEL = 3U;
        } 
      break;
      case  PORT_G_PIN_7:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[27].B.PADSEL = 3U;
        } 
      break;
      case  PORT_G_PIN_8:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[16].B.PADSEL = 2U;
        } 
      break;
      case  PORT_G_PIN_9:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[17].B.PADSEL = 2U;
        } 
      break;
      case  PORT_G_PIN_10:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[18].B.PADSEL = 1U;
        } 
      break;
      case  PORT_G_PIN_11:
        if ( (pin_mode & PORT_PIN_MODE_ALT_INPUT_1) != 0U ) {
          SIUL.PSMI[19].B.PADSEL = 2U;
        } 
      break;

      default:
        ;
    }
  }
  return;
}

/*
 * Port_Init implementation.
 */
void Port_Init(const Port_ConfigType * ConfigPtr)
{
  /* Flags for Critical Section */
  register EE_FREG f;
  /* Pins Counter */
  register uint32 pin;

  AS_ASSERT( ( ConfigPtr != NULL ), PORT_INIT_SERVICE_ID, PORT_E_PARAM_CONFIG );
  AS_ASSERT( ( Hw_ChipCheck() == E_OK ), PORT_INIT_SERVICE_ID, PORT_E_UNINIT );

  /* Start Critical Section */
  f = EE_hal_suspendIRQ();

  Port_Global.ConfigPtr = ConfigPtr;
  Port_Global.Init = TRUE;

  for (pin = 0U; pin < ConfigPtr->PortNumberOfPortPins; ++pin)
  {
    /* Pin ID to set  */
    register const Port_PinType     pin_id = ConfigPtr->PortPins[pin].PortPinId;
    /* Pin Initial Mode to set  */
    register const Port_PinModeType initial_mode = ConfigPtr->PortPins[pin].
      PortPinInitialMode;
    /* Pin Modes Array */
    register const Port_PinModeConfType * const supported_modes = ConfigPtr->
      PortPins[pin].PortPinSupportedModes;

    /* Pin modes counter */
    register uint32 pin_modes;
    
    for(pin_modes = 0U; pin_modes < ConfigPtr->PortPins[pin].PortPinModeNumber;
        ++pin_modes)
    {
      if(initial_mode == supported_modes[pin_modes].PortPinMode) {

        /* Initializes Port Pin Pad. */
        SIUL.PCR[pin_id].R = supported_modes[pin_modes].
          PortPinModePadConfig;

        if( (ConfigPtr->PortPins[pin].PortPinDirection == PORT_PIN_IN) ) {
          /* Initialize Input Pin */
          EE_set_input_multiplexer_register(pin_id, initial_mode);
        } else if (ConfigPtr->PortPins[pin].
            PortPinLevelValue == PORT_PIN_LEVEL_HIGH) {
          /* Initialize Output Pin High Value */
          SIUL.GPDO[pin_id].R = 1U;
        }
      }
    }
  }

  /* End Critical Section */
  EE_hal_resumeIRQ(f);
}

/*
 * Port_SetPinDirection implementation
 */
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
  register uint32     p;
  register EE_UREG    f;
  register const Port_ConfigType *  cfgptr;

  AS_ASSERT(
    ( Port_Global.Init == TRUE ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_UNINIT
  );

  AS_ASSERT(
    ( Pin < PORT_PINS_NUMBER ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  f = EE_hal_suspendIRQ();
  cfgptr = Port_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  /* Pin Look-up */
  for ( p = 0U; ( p < cfgptr->PortNumberOfPortPins ) &&
      ( cfgptr->PortPins[p].PortPinId != Pin ); ++p );

  AS_ASSERT(
    ( p < cfgptr->PortNumberOfPortPins ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  AS_ASSERT(
    ( cfgptr->PortPins[p].PortPinDirectionChangeable == TRUE ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_DIRECTION_UNCHANGEABLE
  );

  /* Starts Atomic Section. */
  f = EE_hal_suspendIRQ();

  EE_port_set_pin_direction(Pin, Direction);

  /* Ends Atomic Section. */
  EE_hal_resumeIRQ(f);
}
#endif

/*
 * Port_RefreshPortDirection implementation
 */
void Port_RefreshPortDirection(void)
{

  register uint32 pin;

  AS_ASSERT(
    ( Port_Global.Init == TRUE ),
    PORT_REFRESH_PORT_DIRECTION_SERVICE_ID,
    PORT_E_UNINIT
  );

  for ( pin = 0U; pin < Port_Global.ConfigPtr->PortNumberOfPortPins; ++pin )
  {
    if (
      Port_Global.ConfigPtr->PortPins[pin].PortPinDirectionChangeable == FALSE
    ) {
       EE_port_set_pin_direction(Port_Global.ConfigPtr->PortPins[pin].PortPinId,
          Port_Global.ConfigPtr->PortPins[pin].PortPinDirection);
    }
  }
}

/*
 * Port_SetPinMode implementation
 */
#if ( PORT_SET_PIN_MODE_API == STD_ON )
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{

  register uint32     p, m;
  register EE_UREG      f;
  register boolean    init;
  register const Port_ConfigType *  cfgptr;

  f = EE_hal_suspendIRQ();
  init = Port_Global.Init;
  cfgptr = Port_Global.ConfigPtr;
  EE_hal_resumeIRQ(f);

  AS_ASSERT(
    ( init == TRUE ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_UNINIT
  );

  AS_ASSERT(
    ( Pin < PORT_PINS_NUMBER ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  /* Pin Look-up */
  for ( p = 0U; ( p < cfgptr->PortNumberOfPortPins ) &&
    ( cfgptr->PortPins[p].PortPinId != Pin ); ++p );

  AS_ASSERT(
    ( p < cfgptr->PortNumberOfPortPins ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  AS_ASSERT(
    ( cfgptr->PortPins[p].PortPinModeChangeable == TRUE ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_MODE_UNCHANGEABLE
  );

  AS_ASSERT(
    ( Mode < PORT_PIN_MODES_NUMBER ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_INVALID_MODE
  );

  /* Pin Modes Look-up */
  for(m = 0U; ( m < cfgptr->PortPins[p].PortPinModeNumber ) &&
    ( cfgptr->PortPins[p].PortPinSupportedModes[m].PortPinMode != Mode ); ++m);

  AS_ASSERT(
    ( m < cfgptr->PortPins[p].PortPinModeNumber ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_INVALID_MODE
  );

  /* Change Port Pin Mode. (Pad Conf. Register value) */
  SIUL.PCR[cfgptr->PortPins[p].PortPinId].R = cfgptr->PortPins[p].
    PortPinSupportedModes[m].PortPinModePadConfig;

  /* If the new mode is an input mode maybe I need to configure Input
     Multiplexer */
  if( cfgptr->PortPins[p].PortPinDirection == PORT_PIN_IN ) {
    EE_set_input_multiplexer_register(p, cfgptr->PortPins[p].
      PortPinSupportedModes[m].PortPinMode);
  }
}
#endif

