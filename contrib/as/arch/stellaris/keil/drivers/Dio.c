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

#define	DIO_AR_RELEASE_MAJOR_VERSION	4
#define	DIO_AR_RELEASE_MINOR_VERSION	0

#include "Dio.h"

/*
 * DIO106:	The DIO module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files.
 * 		The imported included files shall be checked by preprocessing
 * 		directives.
 * 		The following version numbers shall be verified:
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		Where <MODULENAME> is the module short name of the other
 * 		(external) modules which provide header files included by DIO
 * 		module.
 * 		If the values are not identical to the expected values, an
 * 		error shall be reported.
 */
#if !defined( DIO_AR_MAJOR_VERSION ) || \
    ( DIO_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION )
#error	Dio: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( DIO_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(DIO_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* DIO_DEV_ERROR_DETECT */

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

#endif	/* !DIO_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Dio
 */
typedef struct
{
  boolean			Init;		/* PORT Driver Initialized? */

  const Dio_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Dio_GlobalType;


/*
 * Global config
 */
Dio_GlobalType Dio_Global =
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
 * Usefull GPIO Port Pin Macros
 */
#define	GPIO_PORT_DATA_BIT_ADDR_MASK	0x00000004

#define	GPIO_PORT_PIN_ADDR(_pin)	(uint32)(\
  HW_CH_2_MOD_BASE_ADDR(_pin) +\
  (GPIO_PORT_DATA_BIT_ADDR_MASK << HW_CH_2_UNIT(_pin))\
)

#define	GPIO_SET_PIN(_pin,_val)	(\
  EE_HWREG(GPIO_PORT_PIN_ADDR(_pin)) = (_val << HW_CH_2_UNIT(_pin)) \
)

#define	GPIO_GET_PIN(_pin)	(\
  EE_HWREG(GPIO_PORT_PIN_ADDR(_pin)) >> HW_CH_2_UNIT(_pin) \
)

/*
 * Usefull GPIO Port Macros
 */
#define	GPIO_PORT_DATA_ADDRESS_MASK	0x000003FC

#define	GPIO_PORT_ADDR(_port)	(uint32)( \
  (uint32)HW_BASE_ADDR + \
  ((uint32)_port << (uint32)HW_MOD_ADDR_S) + \
  (uint32)GPIO_PORT_DATA_ADDRESS_MASK \
)

#define	GPIO_SET_PORT(_port, _val)	(EE_HWREG(GPIO_PORT_ADDR(_port)) = _val)

#define	GPIO_GET_PORT(_port)		EE_HWREG(GPIO_PORT_ADDR(_port))

/*
 * Dio_ReadChannel implementation
 */
Dio_LevelType Dio_ReadChannel(
  Dio_ChannelType	ChannelId
)
{

  register uint32		p, c;
  register EE_UREG		f;
  register Dio_LevelType	lvl;

  VALIDATE_W_RV(
    ( ChannelId < DIO_CHANNELS_NUMBER ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dio_Global.Init,
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW,
    f
  );

  /* Port Look-up. */
  c = HW_CH_2_MOD(ChannelId);
  for (
    p = 0;
    (
      ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ) &&
      ( c != Dio_Global.ConfigPtr->DioPorts[p].DioPortId )
    );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW,
    f
  );

  /* Channel Look-up. */
  for (
    c = 0;
    (
      ( c < Dio_Global.ConfigPtr->DioPorts[p].DioNumberOfChannels ) &&
      ( ChannelId != Dio_Global.ConfigPtr->DioPorts[p].DioChannels[c] )
    );
    c++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( c < Dio_Global.ConfigPtr->DioPorts[p].DioNumberOfChannels ),
    DIO_READCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW,
    f
  );

  lvl = GPIO_GET_PIN(ChannelId);

  EE_hal_resumeIRQ(f);

  return lvl;

}

/*
 * Dio_WriteChannel implementation
 */
void Dio_WriteChannel(
  Dio_ChannelType	ChannelId,
  Dio_LevelType		Level
)
{

  register uint32	p, c;
  register EE_UREG	f;

  VALIDATE(
    ( ChannelId < DIO_CHANNELS_NUMBER ),
    DIO_WRITECHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ( Dio_Global.Init, DIO_WRITECHANNEL_ID, DIO_E_PARAM_CONFIG, f );

  /* Port Look-up. */
  c = HW_CH_2_MOD(ChannelId);
  for (
    p = 0;
    (
      ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ) &&
      ( c != Dio_Global.ConfigPtr->DioPorts[p].DioPortId )
    );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ),
    DIO_WRITECHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    f
  );

  /* Channel Look-up. */
  for (
    c = 0;
    (
      ( c < Dio_Global.ConfigPtr->DioPorts[p].DioNumberOfChannels ) &&
      ( ChannelId != Dio_Global.ConfigPtr->DioPorts[p].DioChannels[c] )
    );
    c++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( c < Dio_Global.ConfigPtr->DioPorts[p].DioNumberOfChannels ),
    DIO_WRITECHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    f
  );

  GPIO_SET_PIN(ChannelId, Level);

  EE_hal_resumeIRQ(f);

}

/*
 * Dio_ReadPort implementation
 */
Dio_PortLevelType Dio_ReadPort(
  Dio_PortType		PortId
)
{

  register uint32		p;
  register EE_UREG		f;
  register Dio_PortLevelType	lvl;

  VALIDATE_W_RV(
    ( PortId < DIO_PORTS_NUMBER ),
    DIO_READPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dio_Global.Init,
    DIO_READPORT_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW,
    f
  );

  /* Port Look-up. */
  for (
    p = 0;
    (
      ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ) &&
      ( PortId != Dio_Global.ConfigPtr->DioPorts[p].DioPortId )
    );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ),
    DIO_READPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW,
    f
  );

  lvl = GPIO_GET_PORT(PortId);

  EE_hal_resumeIRQ(f);

  return lvl;

}

/*
 * Dio_WritePort implementation
 */
void Dio_WritePort(
  Dio_PortType		PortId,
  Dio_PortLevelType	Level
)
{

  register uint32	p;
  register EE_UREG	f;

  VALIDATE(
    ( PortId < DIO_PORTS_NUMBER ),
    DIO_WRITEPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ( Dio_Global.Init, DIO_WRITEPORT_ID, DIO_E_PARAM_CONFIG, f );

  /* Port Look-up. */
  for (
    p = 0;
    (
      ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ) &&
      ( PortId != Dio_Global.ConfigPtr->DioPorts[p].DioPortId )
    );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ),
    DIO_WRITEPORT_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    f
  );


  GPIO_SET_PORT(PortId, Level);

  EE_hal_resumeIRQ(f);

}

/*
 * Dio_ReadChannelGroup implementation
 */
Dio_PortLevelType Dio_ReadChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr
)
{

  register uint32		p;
  register EE_UREG		f;
  register Dio_PortLevelType	lvl;

  VALIDATE_W_RV(
    ( ChannelGroupIdPtr != NULL_PTR ),
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_POINTER,
    STD_LOW
  );

  VALIDATE_W_RV(
    ( ChannelGroupIdPtr->port < DIO_PORTS_NUMBER ),
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dio_Global.Init,
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW,
    f
  );

  /* Port Look-up. */
  for (
    p = 0;
    (
      ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ) &&
      ( ChannelGroupIdPtr->port != Dio_Global.ConfigPtr->DioPorts[p].DioPortId )
    );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ),
    DIO_READCHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    STD_LOW,
    f
  );

  lvl = (
    ( GPIO_GET_PORT(ChannelGroupIdPtr->port) &  ChannelGroupIdPtr->mask ) >>
    ChannelGroupIdPtr->offset
  );

  EE_hal_resumeIRQ(f);

  return lvl;

}

/*
 * Dio_WriteChannelGroup implementation
 */
void Dio_WriteChannelGroup(
  const Dio_ChannelGroupType*	ChannelGroupIdPtr,
  Dio_PortLevelType		Level
)
{

  register uint32	p;
  register EE_UREG	f;

  VALIDATE(
    ( ChannelGroupIdPtr != NULL_PTR ),
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_POINTER
  );

  VALIDATE(
    ( ChannelGroupIdPtr->port < DIO_PORTS_NUMBER ),
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID
  );


  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Dio_Global.Init,
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_CONFIG,
    f
  );

  /* Port Look-up. */
  for (
    p = 0;
    (
      ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ) &&
      ( ChannelGroupIdPtr->port != Dio_Global.ConfigPtr->DioPorts[p].DioPortId )
    );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ),
    DIO_WRITECHANNELGROUP_ID,
    DIO_E_PARAM_INVALID_PORT_ID,
    f
  );

  GPIO_SET_PORT(
    ChannelGroupIdPtr->port,
    ((Level << ChannelGroupIdPtr->offset) & ChannelGroupIdPtr->mask)
  );

  EE_hal_resumeIRQ(f);

}

/*
 * Dio_Init implementation.
 */
void Dio_Init(
  const Dio_ConfigType *	ConfigPtr
)
{

  register EE_FREG	flags;

  VALIDATE( ( ConfigPtr != NULL), DIO_INIT_ID, DIO_E_PARAM_CONFIG );

  VALIDATE(
    ( Hw_CheckCore() == E_OK), DIO_INIT_ID, DIO_E_PARAM_CONFIG
  );

  flags = EE_hal_suspendIRQ();
  Dio_Global.ConfigPtr = ConfigPtr;
  Dio_Global.Init = TRUE;
  EE_hal_resumeIRQ(flags);

}

/*
 * Dio_FlipChannel implementation
 */
#if ( DIO_FLIP_CHANNEL_API == STD_ON )
Dio_LevelType Dio_FlipChannel(
  Dio_ChannelType		ChannelId
)
{
  register uint32		p, c;
  register EE_UREG		f;
  register Dio_LevelType	lvl;

  VALIDATE_W_RV(
    ( ChannelId < DIO_CHANNELS_NUMBER ),
    DIO_FLIPCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW
  );

  f = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dio_Global.Init,
    DIO_FLIPCHANNEL_ID,
    DIO_E_PARAM_CONFIG,
    STD_LOW,
    f
  );

  /* Port Look-up. */
  c = HW_CH_2_MOD(ChannelId);
  for (
    p = 0;
    (
      ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ) &&
      ( c != Dio_Global.ConfigPtr->DioPorts[p].DioPortId )
    );
    p++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( p < Dio_Global.ConfigPtr->DioNumberOfPorts ),
    DIO_FLIPCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW,
    f
  );

  /* Channel Look-up. */
  for (
    c = 0;
    (
      ( c < Dio_Global.ConfigPtr->DioPorts[p].DioNumberOfChannels ) &&
      ( ChannelId != Dio_Global.ConfigPtr->DioPorts[p].DioChannels[c] )
    );
    c++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( c < Dio_Global.ConfigPtr->DioPorts[p].DioNumberOfChannels ),
    DIO_FLIPCHANNEL_ID,
    DIO_E_PARAM_INVALID_CHANNEL_ID,
    STD_LOW,
    f
  );

  lvl = GPIO_GET_PIN(ChannelId);

  if ( lvl == STD_LOW ) {

    GPIO_SET_PIN(ChannelId, STD_HIGH);

  }
  else {

    GPIO_SET_PIN(ChannelId, STD_LOW);

  }

  EE_hal_resumeIRQ(f);

  return lvl;

  }
#endif
