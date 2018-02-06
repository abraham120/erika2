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
 * Author:  2011,  Giuseppe Serano
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

#include "ee.h"

/* Development error macros. */
#if ( PORT_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(PORT_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(PORT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(PORT_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(PORT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* PORT_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#endif	/* !PORT_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Port Driver
 */
typedef struct
{
  boolean			Init;		/* PORT Driver Initialized? */

  const Port_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Port_GlobalType;


/*
 * Global config
 */
Port_GlobalType Port_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
};

/* GPIO Hardware Channel Unit Mask (Channel Unit = Port Pin) */
#define	HW_CH_UNIT_MASK		0x00000007	/* Mask			*/
#define	HW_CH_UNIT_MASK_SZ_S	0x00000003	/* Mask Size Shift Bits */

/* GPIO Hardware Channel Module Mask (Channel Module = Port) */
#define	HW_CH_MOD_MASK		0x00000078	/* Mask */

/* GPIO Hardware Base Address */
#define	HW_BASE_ADDR		GPIO_PORTA_AHB_DATA_BITS_R

#include "Hardware.h"	/* Hardware Abstraction Header File. */

/*
 * Usefull Port Pin Macros
 */
#define	GPIO_PORT_DATA_BIT_ADDR_MASK	0x00000004

#define	GPIO_PORT_PIN_ADDR(_pin) (uint32)(\
  HW_CH_2_MOD_BASE_ADDR(_pin) +\
  (GPIO_PORT_DATA_BIT_ADDR_MASK << HW_CH_2_UNIT(_pin))\
)

#define	GPIO_SET_PIN(_pin,_val) (\
  EE_HWREG(GPIO_PORT_PIN_ADDR(_pin)) = (_val << HW_CH_2_UNIT(_pin))\
)

#define	GPIO_GET_PIN(_pin) (\
  EE_HWREG(GPIO_PORT_PIN_ADDR(_pin)) >> HW_CH_2_UNIT(_pin)\
)

#define	GPIO_SET_PIN_REG(_pin,_val,_ofs) \
do { \
  if ( _val == STD_OFF ) \
    HW_CH_2_MOD_REG(_pin, _ofs) &= ~((uint32)STD_ON << HW_CH_2_UNIT(_pin)); \
  else \
    HW_CH_2_MOD_REG(_pin, _ofs) |= ((uint32)STD_ON << HW_CH_2_UNIT(_pin)); \
} while(0)

#define	GPIO_SET_PORT_REG(_pin,_val,_ofs)	( \
    HW_CH_2_MOD_REG(_pin, _ofs) = (uint32)_val \
)

#define	GPIO_PORT_DIR_R_OFFSET			0x00000400
#define	GPIO_PORT_AFSEL_R_OFFSET		0x00000420
#define	GPIO_PORT_DR2R_R_OFFSET			0x00000500
#define	GPIO_PORT_DR4R_R_OFFSET			0x00000504
#define	GPIO_PORT_DR8R_R_OFFSET			0x00000508
#define	GPIO_PORT_ODR_R_OFFSET			0x0000050C
#define	GPIO_PORT_PUR_R_OFFSET			0x00000510
#define	GPIO_PORT_PDR_R_OFFSET			0x00000514
#define	GPIO_PORT_SLR_R_OFFSET			0x00000518
#define	GPIO_PORT_DEN_R_OFFSET			0x0000051C
#define	GPIO_PORT_LOCK_R_OFFSET			0x00000520
#define	GPIO_PORT_COMMIT_R_OFFSET		0x00000524
#define	GPIO_PORT_AMSEL_R_OFFSET		0x00000528
#define	GPIO_PORT_CTL_R_OFFSET			0x0000052C

#define	GPIO_SET_PIN_DIR(_pin,_dir)	\
	GPIO_SET_PIN_REG(_pin,_dir,GPIO_PORT_DIR_R_OFFSET)
#define	GPIO_SET_PIN_AFSEL(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_AFSEL_R_OFFSET)
#define	GPIO_SET_PIN_DR2R(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_DR2R_R_OFFSET)
#define	GPIO_SET_PIN_DR4R(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_DR4R_R_OFFSET)
#define	GPIO_SET_PIN_DR8R(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_DR8R_R_OFFSET)
#define	GPIO_SET_PIN_ODR(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_ODR_R_OFFSET)
#define	GPIO_SET_PIN_PUR(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_PUR_R_OFFSET)
#define	GPIO_SET_PIN_PDR(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_PDR_R_OFFSET)
#define	GPIO_SET_PIN_SLR(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_SLR_R_OFFSET)
#define	GPIO_SET_PIN_DEN(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_DEN_R_OFFSET)
#define	GPIO_SET_PIN_AMSEL(_pin,_val)	\
	GPIO_SET_PIN_REG(_pin,_val,GPIO_PORT_AMSEL_R_OFFSET)

/* Port Mux Control Mask Size Shift Bits */
#define	PORT_PIN_HW_CFG_PMC_M_SZ_S	0x00000002

#define	GPIO_SET_PIN_PMC(_pin,_pmc)	\
  EE_HWREG(HW_CH_2_MOD_BASE_ADDR(_pin) + GPIO_PORT_CTL_R_OFFSET) &= ~(\
	PORT_PIN_HW_CFG_PMC_M << (\
		HW_CH_2_UNIT(_pin) << PORT_PIN_HW_CFG_PMC_M_SZ_S\
	)\
  ); \
  EE_HWREG(HW_CH_2_MOD_BASE_ADDR(_pin) + GPIO_PORT_CTL_R_OFFSET) |= (\
	(_pmc & PORT_PIN_HW_CFG_PMC_M) << (\
		HW_CH_2_UNIT(_pin) << PORT_PIN_HW_CFG_PMC_M_SZ_S\
	)\
  )

/* LOCK and COMMIT special masks */
#define	GPIO_UNLOCK_PASSWORD	0x4C4F434BU

#define	GPIO_PORT_UNLOCK(_pin)	\
	GPIO_SET_PORT_REG(_pin, GPIO_UNLOCK_PASSWORD, GPIO_PORT_LOCK_R_OFFSET)

#define	GPIO_ENABLE_PIN_COMMIT(_pin)	( \
	HW_CH_2_MOD_REG(_pin, GPIO_PORT_COMMIT_R_OFFSET) |= \
	((uint32)STD_ON << HW_CH_2_UNIT(_pin)) \
)

#define	GPIO_DISABLE_PIN_COMMIT(_pin)	( \
	HW_CH_2_MOD_REG(_pin, GPIO_PORT_COMMIT_R_OFFSET) &= \
	~((uint32)STD_ON << HW_CH_2_UNIT(_pin)) \
)

/*
 * Port Pin Mode Hardware Configuration.
 */
static void Port_SetPortPinHWMode_Impl(
  Port_PinType			Pin,
  const Port_PinModeConfType *	ConfigPtr
)
{

  register uint32	mode;

  mode = ConfigPtr->PortPinModeHWConfig;

  /* Sets-up Analog Mode Select */
  if ( mode & PORT_PIN_HW_CFG_AMSEL ) {

    GPIO_SET_PIN_DEN(Pin, STD_OFF);

    GPIO_SET_PIN_AMSEL(Pin, STD_ON);

    /* Sets-up Alternate Function Select */

    if ( mode & PORT_PIN_HW_CFG_AFSEL ) {

      GPIO_SET_PIN_AFSEL(Pin, STD_ON);

    }

  }
  else {

    GPIO_SET_PIN_AMSEL(Pin, STD_OFF);

    /* Sets-up Alternate Function Select */
    if ( mode & PORT_PIN_HW_CFG_AFSEL ) {

      GPIO_SET_PIN_PMC(Pin, mode);

      GPIO_SET_PIN_AFSEL(Pin, STD_ON);

    }
    else {

      GPIO_SET_PIN_AFSEL(Pin, STD_OFF);

    }

    /* Sets-up Strenght Drive Select */
    if ( mode & PORT_PIN_HW_CFG_DR2R ) {

      GPIO_SET_PIN_DR2R(Pin, STD_ON);

      GPIO_SET_PIN_SLR(Pin, STD_OFF);

    }
    else if ( mode & PORT_PIN_HW_CFG_DR4R ) {

      GPIO_SET_PIN_DR4R(Pin, STD_ON);

      GPIO_SET_PIN_SLR(Pin, STD_OFF);

    }
    else if ( mode & PORT_PIN_HW_CFG_DR8R ) {

      GPIO_SET_PIN_DR8R(Pin, STD_ON);

      /* Sets-up Slew-rate Control */
      if ( mode & PORT_PIN_HW_CFG_SLR ) {

        GPIO_SET_PIN_SLR(Pin, STD_ON);

      }
      else {

        GPIO_SET_PIN_SLR(Pin, STD_OFF);

      }

    } /* DR8R */

    /* Sets-up Open Drain */
    if ( mode & PORT_PIN_HW_CFG_ODR ) {

      GPIO_SET_PIN_ODR(Pin, STD_ON);

    }
    else {

      GPIO_SET_PIN_ODR(Pin, STD_OFF);

      /* Sets-up Pull-Up */
      if ( mode & PORT_PIN_HW_CFG_PUR ) {

        GPIO_SET_PIN_PUR(Pin, STD_ON);

      }
      else {

        GPIO_SET_PIN_PUR(Pin, STD_OFF);

      }

      /* Sets-up Pull-Down */
      if ( mode & PORT_PIN_HW_CFG_PDR ) {

        GPIO_SET_PIN_PDR(Pin, STD_ON);

      }
      else {

        GPIO_SET_PIN_PDR(Pin, STD_OFF);

      }

    } /* !(Open Drain) */

    /* Sets-up Digital Enable */
    if ( mode & PORT_PIN_HW_CFG_DEN ) {

      GPIO_SET_PIN_DEN(Pin, STD_ON);

    }
    else {

      GPIO_SET_PIN_DEN(Pin, STD_OFF);

    }

  }	/* !(Analog Mode Select) */

}

/* Handle Configuration Lock for special pins */
static void Port_SetPortPinHWMode(
  Port_PinType			Pin,
  const Port_PinModeConfType *	ConfigPtr
)
{
  switch(Pin) {
    case PORT_C_PIN_0:
    case PORT_C_PIN_1:
    case PORT_C_PIN_2:
    case PORT_C_PIN_3:
    case PORT_D_PIN_7:
    case PORT_F_PIN_0:
      /* Unlock the GPIO Port to change COMMIT */
      GPIO_PORT_UNLOCK(Pin);
      /* Enable Pin Configuration changes */
      GPIO_ENABLE_PIN_COMMIT(Pin);
      Port_SetPortPinHWMode_Impl(Pin, ConfigPtr);
      /* Unlock the GPIO Port to change COMMIT */
      GPIO_PORT_UNLOCK(Pin);
      /* Disable Pin Configuration changes */
      GPIO_DISABLE_PIN_COMMIT(Pin);
    break;
    default:
      Port_SetPortPinHWMode_Impl(Pin, ConfigPtr);
  }
}

/*
 * Port Pin Initialization.
 */
static void Port_InitPortPin(
  const Port_PinConfType *	ConfigPtr
)
{
  register uint32 port;
  register uint32 mode;

  /* Sets-up Port Mask */
  port = HW_CH_2_CGC_MASK(ConfigPtr->PortPinId);

  /* Sets Advanced High-Performance Bus Memory Access for the Port Module */
  SYSCTL_GPIOHBCTL_R |= port;

  /* Enables GPIO Port Module in Run-Mode */
  SYSCTL_RCGCGPIO_R |= port;

  /* Does a dummy read to insert a few cycles after enabling the peripheral. */
  /*port = SYSCTL_RCGCGPIO_R;*/

  /* Sets Port Pin Initial Mode. */
  for (mode = 0; mode < ConfigPtr->PortPinModeNumber; mode++) {

    if (
      ConfigPtr->PortPinSupportedModes[mode].PortPinMode ==
      ConfigPtr->PortPinInitialMode
    ) {

      Port_SetPortPinHWMode(
        ConfigPtr->PortPinId,
        &(ConfigPtr->PortPinSupportedModes[mode])
      );

    }

  }

  /* Sets Initial Port Pin Direction */
  GPIO_SET_PIN_DIR(ConfigPtr->PortPinId, ConfigPtr->PortPinDirection);

  /* Sets Initial Port Pin Level Value */
  if (ConfigPtr->PortPinDirection == PORT_PIN_OUT) {

    GPIO_SET_PIN(ConfigPtr->PortPinId, ConfigPtr->PortPinLevelValue);

  }

}

/*
 * Port_Init implementation.
 */
void Port_Init(
  const Port_ConfigType *	ConfigPtr
)
{

  register EE_FREG	flags;
  register Port_PinType	pin;

  VALIDATE( ( ConfigPtr != NULL ), PORT_INIT_SERVICE_ID, PORT_E_PARAM_CONFIG );

  VALIDATE( ( Hw_CheckCore() == E_OK ), PORT_INIT_SERVICE_ID, PORT_E_UNINIT );

  flags = EE_hal_suspendIRQ();

  Port_Global.ConfigPtr = ConfigPtr;
  Port_Global.Init = TRUE;

  for (pin = 0; pin < ConfigPtr->PortNumberOfPortPins; pin++)
  {

    /* Initializes Port Pin. */
    Port_InitPortPin(&(ConfigPtr->PortPins[pin]));

  }

  EE_hal_resumeIRQ(flags);

}

/*
 * Port_SetPinDirection implementation
 */
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )
void Port_SetPinDirection(
  Port_PinType		Pin,
  Port_PinDirectionType	Direction
)
{

  register uint32	p;
  register EE_UREG	f;

  VALIDATE(
    ( Pin < PORT_PINS_NUMBER ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Port_Global.Init,
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_UNINIT,
    f
  );

  /* Pin Look-up */
  for (
    p = 0;
    ( p < Port_Global.ConfigPtr->PortNumberOfPortPins ) &&
    ( Port_Global.ConfigPtr->PortPins[p].PortPinId != Pin );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( p <= Port_Global.ConfigPtr->PortNumberOfPortPins ),
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_PARAM_PIN,
    f
  );

  VALIDATE_IRQ(
    Port_Global.ConfigPtr->PortPins[p].PortPinDirectionChangeable,
    PORT_SET_PIN_DIRECTION_SERVICE_ID,
    PORT_E_DIRECTION_UNCHANGEABLE,
    f
  );

  /* Sets Initial Port Pin Level Value */
  if ( Direction == PORT_PIN_OUT ) {

    GPIO_SET_PIN(
      Port_Global.ConfigPtr->PortPins[p].PortPinId,
      Port_Global.ConfigPtr->PortPins[p].PortPinLevelValue
    );

  }

  GPIO_SET_PIN_DIR(Port_Global.ConfigPtr->PortPins[p].PortPinId, Direction);

  /* Ends Atomic Section. */
  EE_hal_resumeIRQ(f);

}
#endif

/*
 * Port_RefreshPortDirection implementation
 */
void Port_RefreshPortDirection(
  void
)
{

  register EE_FREG	flags;
  register Port_PinType	pin;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Port_Global.Init,
    PORT_REFRESH_PORT_DIRECTION_SERVICE_ID,
    PORT_E_UNINIT,
    flags
  );

  for ( pin = 0; pin < Port_Global.ConfigPtr->PortNumberOfPortPins; pin++ ) {

    if ( !Port_Global.ConfigPtr->PortPins[pin].PortPinDirectionChangeable ) {

      GPIO_SET_PIN_DIR(
        Port_Global.ConfigPtr->PortPins[pin].PortPinId,
        Port_Global.ConfigPtr->PortPins[pin].PortPinDirection
      );

    }

  }

  EE_hal_resumeIRQ(flags);

}

/*
 * Port_SetPinMode implementation
 */
#if ( PORT_SET_PIN_MODE_API == STD_ON )
void Port_SetPinMode(
  Port_PinType		Pin,
  Port_PinModeType	Mode
)
{

  register uint32	p, m;
  register EE_UREG	f;

  VALIDATE(
    ( Pin < PORT_PINS_NUMBER ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_PIN
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Port_Global.Init,
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_UNINIT,
    f
  );

  /* Pin Look-up */
  for (
    p = 0;
    ( p < Port_Global.ConfigPtr->PortNumberOfPortPins ) &&
    ( Port_Global.ConfigPtr->PortPins[p].PortPinId != Pin );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( p < Port_Global.ConfigPtr->PortNumberOfPortPins ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_PIN,
    f
  );

  VALIDATE_IRQ(
    Port_Global.ConfigPtr->PortPins[p].PortPinModeChangeable,
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_MODE_UNCHANGEABLE,
    f
  );

  VALIDATE_IRQ(
    ( Mode < Port_Global.ConfigPtr->PortPins[p].PortPinModeNumber ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_INVALID_MODE,
    f
  );

  /* Pin Modes Look-up */
  for(
    m = 0;
    ( m < Port_Global.ConfigPtr->PortPins[p].PortPinModeNumber ) &&
    ( 
      Port_Global.ConfigPtr->PortPins[p].PortPinSupportedModes[m].PortPinMode !=
      Mode
    );
    m++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( m < Port_Global.ConfigPtr->PortPins[p].PortPinModeNumber ),
    PORT_SET_PIN_MODE_SERVICE_ID,
    PORT_E_PARAM_INVALID_MODE,
    f
  );

  /* Change Port Pin Mode. */
  Port_SetPortPinHWMode(
    Port_Global.ConfigPtr->PortPins[p].PortPinId,
    &(Port_Global.ConfigPtr->PortPins[p].PortPinSupportedModes[m])
  );

  EE_hal_resumeIRQ(f);

}
#endif

