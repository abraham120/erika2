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
 * Author:  2012,  Gianluca Franchino
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
	boolean		Init;		/* PORT Driver Initialized? */

	const Port_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Port_GlobalType;


/*
 * Global config
 */
Port_GlobalType Port_Global =
{
	FALSE,		/* Init		*/
	NULL_PTR,	/* ConfigPtr	*/
};

/* IO Hardware Channel Unit Mask (Channel Unit = Port Pin) */
#define	HW_CH_UNIT_MASK		0x00000007	/* Mask			*/
#define	HW_CH_UNIT_MASK_SZ_S	0x00000003	/* Mask Size Shift Bits */

/* IO Hardware Channel Module Mask (Channel Module = Port) */
#define	HW_CH_MOD_MASK		0x00000078	/* Mask */

#include "Hardware.h"	/* Hardware Abstraction Header File. */

/*
 * Usefull IO Port Pin Macros
 */
#define	IO_PORT_PIN_ADDR(_pin)	(uint32)(\
		HW_CH_2_MOD_BASE_ADDR(_pin)\
)

#define	IO_SET_PIN(_pin,_val) \
	( EE_HWREG8(IO_PORT_PIN_ADDR(_pin)+ HW_IO_PODR_OFFSET) = \
	( EE_HWREG8(IO_PORT_PIN_ADDR(_pin)+ HW_IO_PODR_OFFSET) & \
	(0xFE << HW_CH_2_UNIT(_pin)) ) | (_val  << HW_CH_2_UNIT(_pin)) )

#define	IO_GET_PIN(_pin)	(\
	( EE_HWREG8(IO_PORT_PIN_ADDR(_pin)+ HW_IO_PIDR_OFFSET) >> \
	HW_CH_2_UNIT(_pin) ) & 0x1\
)

#define	IO_PORT_ADDR(_port)	(uint32)(\
	HW_CH_2_MOD_BASE_ADDR(_pin)\
)

#define	IO_SET_PORT(_port, _val)	\
		(EE_HWREG8(IO_PORT_ADDR(_port)+ HW_IO_PODR_OFFSET) = _val)
		
#define	IO_GET_PORT(_port) \
		EE_HWREG8(IO_PORT_ADDR(_port) + HW_IO_PIDR_OFFSET)

#define	IO_SET_PIN_REG(_pin,_val,_ofs) \
do { \
  if ( _val == STD_OFF ) \
	EE_HWREG8(IO_PORT_PIN_ADDR(_pin)+ _ofs) &= \
		~((uint8)STD_ON << HW_CH_2_UNIT(_pin)); \
  else \
    EE_HWREG8(IO_PORT_PIN_ADDR(_pin)+ _ofs) |= \
		((uint8)STD_ON << HW_CH_2_UNIT(_pin)); \
} while(0)

/*#define	IO_SET_PIN_DIR(_pin, _dir)	\
	 (EE_HWREG8(IO_PORT_PIN_ADDR(_pin) + HW_IO_PDR_OFFSET) &= \
		(0xFE << HW_CH_2_UNIT(_pin)) | (_dir  << HW_CH_2_UNIT(_pin)))
*/
#define	IO_SET_PIN_DIR(_pin, _dir) \
	IO_SET_PIN_REG(_pin,_dir, HW_IO_PDR_OFFSET)

#define	IO_SET_PIN_PMR(_pin, _val)	\
	IO_SET_PIN_REG(_pin,_val, HW_IO_PMR_OFFSET)

#define	IO_SET_PIN_PCR(_pin, _val)	\
	IO_SET_PIN_REG(_pin,_val, HW_IO_PCR_OFFSET)

#define	IO_SET_PIN_DSCR(_pin, _val)	\
	IO_SET_PIN_REG(_pin,_val, HW_IO_DSCR_OFFSET)

#define IO_SET_PIN_ODR(_pin, _val) \
		(EE_HWREG8(HW_CH_2_ODR_BASE_ADDR(_pin) +\
				(HW_CH_2_UNIT(_pin) >> (uint32) HW_CH_UNIT_MASK_SZ_S)) = _val)

#define	IO_SET_PFS_REG(_pin, _val)	\
		(EE_HWREG8(HW_PORT_PFS_BASE_ADDR + _pin) = _val)

#define	IO_GET_PFS_REG(_pin, _val)	EE_HWREG8(HW_PORT_PFS_BASE_ADDR + _pin)
/*
#define IO_EN_PWP() \
do {\
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_B0WI_CLEAR; \
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_PFSWE_CLEAR; \
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_B0WI_SET; \
} while(0)

#define IO_DIS_PWP() \
do {\
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_B0WI_CLEAR; \
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_PFSWE_SET; \
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_B0WI_SET; \
} while(0)
*/
#define IO_EN_PWP() \
do {\
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_PFSWE_CLEAR; \
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_B0WI_SET; \
} while(0)

#define IO_DIS_PWP() \
do {\
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_B0WI_CLEAR; \
	EE_HWREG8(HW_PORT_PWPR_ADDR) = HW_PWPR_PFSWE_SET; \
} while(0)


/*
 * Port Pin Mode Hardware Configuration.
 */
/*static void Port_SetPortPinHWMode (Port_PinType	Pin, 
										const Port_PinModeConfType *ConfigPtr)
*/
void Port_SetPortPinHWMode (Port_PinType	Pin, 
										const Port_PinModeConfType *ConfigPtr)
{

	register uint32	mode;

	mode = ConfigPtr->PortPinModeHWConfig;

	/* Sets-up Analog Mode Select */
	if ( mode & PORT_PIN_HW_CFG_ASEL ) {
		IO_DIS_PWP();
		IO_SET_PFS_REG(Pin, HW_PFS_ASEL_SET);
		IO_EN_PWP();
	} else {
	
		/* Set the pin as DIO pin. This is necessary before writing to PFS regs.*/
		IO_SET_PIN_PMR(Pin, STD_OFF);
		
		/* Set Port Pin Function */
		IO_DIS_PWP();
		
		if ( mode & PORT_PIN_HW_CFG_ISEL ) {
			IO_SET_PFS_REG(Pin, (mode & PORT_PIN_HW_CFG_PFS_M) | 
					HW_PFS_ISEL_SET);
		} else {
			IO_SET_PFS_REG(Pin, mode & PORT_PIN_HW_CFG_PFS_M);
		}
		
		IO_EN_PWP();
				
		if (mode & PORT_PIN_HW_CFG_DIO) {
			/* Set the pin as DIO pin. */
			IO_SET_PIN_PMR(Pin, STD_OFF);
		} else {
			/* Set the pin as peripheral pin.*/
			IO_SET_PIN_PMR(Pin, STD_ON);			
		}
		
		/* Sets-up Drive Capacity Register */
		if ( mode & PORT_PIN_HW_CFG_DRVCAP_LOW ) {
			IO_SET_PIN_DSCR(Pin, STD_OFF);
		} else if ( mode & PORT_PIN_HW_CFG_DRVCAP_HIGH ) {
			IO_SET_PIN_DSCR(Pin, STD_ON);
		}
		
		/* Sets-up Input Pull-Up Register */
		if ( mode & PORT_PIN_HW_CFG_PULL_UP ) {
			IO_SET_PIN_PCR(Pin, STD_ON);
		} else {
			IO_SET_PIN_PCR(Pin, STD_OFF);
		}
		/* Sets-up output Open Drain Register */
		if ( mode & PORT_PIN_HW_CFG_OPEN_DRAIN ) {
			IO_SET_PIN_ODR(Pin, STD_ON);
		} else {
			IO_SET_PIN_ODR(Pin, STD_OFF);
		}

	}	/* !(Analog Mode Select) */

}


/*
 * Port Pin Initialization.
 */
static void Port_InitPortPin( const Port_PinConfType *	ConfigPtr)
{
	register uint32 mode;

	/* Sets Port Pin Initial Mode. */
	for (mode = 0; mode < ConfigPtr->PortPinModeNumber; mode++) {
		if ( ConfigPtr->PortPinSupportedModes[mode].PortPinMode ==
										ConfigPtr->PortPinInitialMode) {
			Port_SetPortPinHWMode(ConfigPtr->PortPinId, 
					&(ConfigPtr->PortPinSupportedModes[mode]));

		}
	}
	/* Sets Initial Port Pin Direction */
	IO_SET_PIN_DIR(ConfigPtr->PortPinId, ConfigPtr->PortPinDirection);
	/* Sets Initial Port Pin Level Value */
	if (ConfigPtr->PortPinDirection == PORT_PIN_OUT) {
		IO_SET_PIN(ConfigPtr->PortPinId, ConfigPtr->PortPinLevelValue);
	}
}

/*
 * Port_Init implementation.
 */
void Port_Init(const Port_ConfigType *	ConfigPtr)
{

	register EE_FREG	flags;
	register Port_PinType	pin;

	VALIDATE( ( ConfigPtr != NULL ), PORT_INIT_SERVICE_ID, PORT_E_PARAM_CONFIG);

	flags = EE_hal_suspendIRQ();

	Port_Global.ConfigPtr = ConfigPtr;
	Port_Global.Init = TRUE;

	for (pin = 0; pin < ConfigPtr->PortNumberOfPortPins; pin++) {
		/* Initializes Port Pin. */
		Port_InitPortPin(&(ConfigPtr->PortPins[pin]));
	}

	EE_hal_resumeIRQ(flags);
}

/*
 * Port_SetPinDirection implementation
 */
#if ( PORT_SET_PIN_DIRECTION_API == STD_ON )

void Port_SetPinDirection(Port_PinType	Pin, Port_PinDirectionType	Direction)
{

	register uint32	p;
	register EE_UREG	f;

	VALIDATE( ( Pin < PORT_PINS_NUMBER ), PORT_SET_PIN_DIRECTION_SERVICE_ID,
			PORT_E_PARAM_PIN);
	f = EE_hal_suspendIRQ();
	VALIDATE_IRQ( Port_Global.Init, PORT_SET_PIN_DIRECTION_SERVICE_ID, 
			PORT_E_UNINIT, f);
	/* Pin Look-up */
	for (p = 0; ( p < Port_Global.ConfigPtr->PortNumberOfPortPins ) && 
		( Port_Global.ConfigPtr->PortPins[p].PortPinId != Pin ); p++); 

	VALIDATE_IRQ( ( p <= Port_Global.ConfigPtr->PortNumberOfPortPins ),
			PORT_SET_PIN_DIRECTION_SERVICE_ID, PORT_E_PARAM_PIN, f);

	VALIDATE_IRQ( Port_Global.ConfigPtr->PortPins[p].PortPinDirectionChangeable,
			PORT_SET_PIN_DIRECTION_SERVICE_ID, 
			PORT_E_DIRECTION_UNCHANGEABLE, f);

	/* Sets Initial Port Pin Level Value */
	if ( Direction == PORT_PIN_OUT ) {
		IO_SET_PIN( Port_Global.ConfigPtr->PortPins[p].PortPinId, 
				Port_Global.ConfigPtr->PortPins[p].PortPinLevelValue);
	}

	IO_SET_PIN_DIR(Port_Global.ConfigPtr->PortPins[p].PortPinId, Direction);

	/* Ends Atomic Section. */
	EE_hal_resumeIRQ(f);

}
#endif

/*
 * Port_RefreshPortDirection implementation
 */
void Port_RefreshPortDirection(void)
{

	register EE_FREG	flags;
	register Port_PinType	pin;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Port_Global.Init, PORT_REFRESH_PORT_DIRECTION_SERVICE_ID, 
			PORT_E_UNINIT, flags);

	for ( pin = 0; pin < Port_Global.ConfigPtr->PortNumberOfPortPins; pin++ ) {
		if ( !Port_Global.ConfigPtr->PortPins[pin].PortPinDirectionChangeable ){
			IO_SET_PIN_DIR(Port_Global.ConfigPtr->PortPins[pin].PortPinId, 
					Port_Global.ConfigPtr->PortPins[pin].PortPinDirection);
		}
	}

	EE_hal_resumeIRQ(flags);
}

/*
 * Port_SetPinMode implementation
 */
#if ( PORT_SET_PIN_MODE_API == STD_ON )
void Port_SetPinMode( Port_PinType	Pin, Port_PinModeType	Mode)
{

	register uint32	p, m;
	register EE_UREG	f;

	VALIDATE(( Pin < PORT_PINS_NUMBER ), PORT_SET_PIN_MODE_SERVICE_ID,
			PORT_E_PARAM_PIN);

	f = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Port_Global.Init, PORT_SET_PIN_MODE_SERVICE_ID, 
			PORT_E_UNINIT, f);

	/* Pin Look-up */
	for (p = 0; ( p < Port_Global.ConfigPtr->PortNumberOfPortPins ) && 
				( Port_Global.ConfigPtr->PortPins[p].PortPinId != Pin ); p++);

	VALIDATE_IRQ( ( p < Port_Global.ConfigPtr->PortNumberOfPortPins ), 
			PORT_SET_PIN_MODE_SERVICE_ID, PORT_E_PARAM_PIN, f);

	VALIDATE_IRQ( Port_Global.ConfigPtr->PortPins[p].PortPinModeChangeable,
			PORT_SET_PIN_MODE_SERVICE_ID, PORT_E_MODE_UNCHANGEABLE, f);

	VALIDATE_IRQ( (Mode < Port_Global.ConfigPtr->PortPins[p].PortPinModeNumber),
			PORT_SET_PIN_MODE_SERVICE_ID, PORT_E_PARAM_INVALID_MODE, f);

	/* Pin Modes Look-up */
	for (m = 0; ( m < Port_Global.ConfigPtr->PortPins[p].PortPinModeNumber ) &&
	( Port_Global.ConfigPtr->PortPins[p].PortPinSupportedModes[m].PortPinMode !=
			Mode); m++);

	VALIDATE_IRQ( ( m < Port_Global.ConfigPtr->PortPins[p].PortPinModeNumber ), 
			PORT_SET_PIN_MODE_SERVICE_ID, PORT_E_PARAM_INVALID_MODE, f);

	/* Change Port Pin Mode. */
	Port_SetPortPinHWMode( Port_Global.ConfigPtr->PortPins[p].PortPinId, 
			&(Port_Global.ConfigPtr->PortPins[p].PortPinSupportedModes[m]));
	
	EE_hal_resumeIRQ(f);
}
#endif

