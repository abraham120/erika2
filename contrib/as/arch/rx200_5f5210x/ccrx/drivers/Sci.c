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
 * AUTOSAR-"like" SCI Driver Source File.
 *
 * Author:  2013,  Gianluca Franchino
 */

#define	SCI_AR_RELEASE_MAJOR_VERSION	4
#define	SCI_AR_RELEASE_MINOR_VERSION	0

#include "Sci.h"

/*
 * For included (external) header files:
 * - <MODULENAME>_AR_ RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_ RELEASE_MINOR_VERSION
 * shall be verified.
 */
#if !defined( SCI_AR_MAJOR_VERSION ) || \
    ( SCI_AR_MAJOR_VERSION != SCI_AR_RELEASE_MAJOR_VERSION )
#error	Sci: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( SCI_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(SCI_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(SCI_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(SCI_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(SCI_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* SCI_DEV_ERROR_DETECT */

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

#endif	/* !SCI_DEV_ERROR_DETECT */

/*
 * Type that holds all global data for Sci Driver
 */
typedef struct {
	
  boolean			Init;		/* SCI Driver Initialized? */

  const Sci_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Sci_GlobalType;


/*
 * Global config
 */
Sci_GlobalType Sci_Global = {
		
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
  
};

/*
 * MCU Global Configuration Reference
 */
typedef struct {
	
  boolean			Init;		/* MCU Driver Initialized? */

  const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration */

  Mcu_ClockType			ClockSetting;	/* Actual Clock Setting */

} Mcu_GlobalType;

extern Mcu_GlobalType Mcu_Global;

#include "Sci_Internal.h"

/*
 * Usefull Sci Channel Macros
 */
#define	SCI_EXT_OSC_FREQ	1.6E7
#define	SCI_CLK_DIV_HIGH_SPEED	32	/* High-Speed Clock Divisor.	 */
#define	SCI_CLK_DIV_LOW_SPEED	64	/* Low-Speed Clock Divisor.	 */
#define SCI_CLK_DIV_MASK	0x3		/*Mask used to get PCLK divider bits.*/

/** @brief	Enable Sci channel interrupts in the Interrupt Control Unit (ICU).
 *	@param  _ch SCI Channel Identifier.
 *  
 */
static void Sci_EnableICU(Sci_ChannelType _ch)
{
	switch (_ch) {
	case SCI_CHANNEL_0:
		/*Enable Rx Error and Rx interrupts.*/
		EE_HWREG8(HW_ICU_IER_SCI0_ERX) = EE_HWREG8(HW_ICU_IER_SCI0_ERX) | 
							(HW_ICU_SCI0_IER_ER_MASK | HW_ICU_SCI0_IER_RX_MASK);
		/*Enable Tx End interrupt.*/
		EE_HWREG8(HW_ICU_IER_SCI0_TX) = EE_HWREG8(HW_ICU_IER_SCI0_TX) | 
										HW_ICU_SCI0_IER_TX_MASK;
		/*Set IRQ priority*/
		EE_HWREG8(HW_ICU_IPR_SCI0) = HW_IPR_PRI_LEVEL_1;
		break;
	case SCI_CHANNEL_1:
		EE_HWREG8(HW_ICU_IER_SCI1_ERX) = EE_HWREG8(HW_ICU_IER_SCI1_ERX) | 
							(HW_ICU_SCI1_IER_ER_MASK | HW_ICU_SCI1_IER_RX_MASK);
		EE_HWREG8(HW_ICU_IER_SCI1_TX) = EE_HWREG8(HW_ICU_IER_SCI1_TX) | 
										HW_ICU_SCI1_IER_TX_MASK;
		EE_HWREG8(HW_ICU_IPR_SCI1) = HW_IPR_PRI_LEVEL_1;
		break;
	case SCI_CHANNEL_5:
		EE_HWREG8(HW_ICU_IER_SCI5_ERX) = EE_HWREG8(HW_ICU_IER_SCI5_ERX) | 
							(HW_ICU_SCI5_IER_ER_MASK | HW_ICU_SCI5_IER_RX_MASK);
		EE_HWREG8(HW_ICU_IER_SCI5_TX) = EE_HWREG8(HW_ICU_IER_SCI5_TX) | 
										HW_ICU_SCI5_IER_TX_MASK;
		EE_HWREG8(HW_ICU_IPR_SCI5) = HW_IPR_PRI_LEVEL_1;
		break;
	case SCI_CHANNEL_6:
		EE_HWREG8(HW_ICU_IER_SCI6_ERX) = EE_HWREG8(HW_ICU_IER_SCI6_ERX) | 
							(HW_ICU_SCI6_IER_ER_MASK | HW_ICU_SCI6_IER_RX_MASK);
		EE_HWREG8(HW_ICU_IER_SCI6_TX) = EE_HWREG8(HW_ICU_IER_SCI6_TX) | 
										HW_ICU_SCI6_IER_TX_MASK;
		EE_HWREG8(HW_ICU_IPR_SCI6) = HW_IPR_PRI_LEVEL_1;
		break;
	case SCI_CHANNEL_8:
		EE_HWREG8(HW_ICU_IER_SCI8_ERX) = EE_HWREG8(HW_ICU_IER_SCI8_ERX) | 
							(HW_ICU_SCI8_IER_ER_MASK | HW_ICU_SCI8_IER_RX_MASK);
		EE_HWREG8(HW_ICU_IER_SCI8_TX) = EE_HWREG8(HW_ICU_IER_SCI8_TX) | 
										HW_ICU_SCI8_IER_TX_MASK;
		EE_HWREG8(HW_ICU_IPR_SCI8) = HW_IPR_PRI_LEVEL_1;
		break;
	case SCI_CHANNEL_9:
		EE_HWREG8(HW_ICU_IER_SCI9_ERX) = EE_HWREG8(HW_ICU_IER_SCI9_ERX) | 
							(HW_ICU_SCI9_IER_ER_MASK | HW_ICU_SCI9_IER_RX_MASK);
		EE_HWREG8(HW_ICU_IER_SCI9_TX) = EE_HWREG8(HW_ICU_IER_SCI9_TX) | 
										HW_ICU_SCI9_IER_TX_MASK;
		EE_HWREG8(HW_ICU_IPR_SCI9) = HW_IPR_PRI_LEVEL_1;
		break;
	case SCI_CHANNEL_12:
		EE_HWREG8(HW_ICU_IER_SCI12_ERX) = EE_HWREG8(HW_ICU_IER_SCI12_ERX) | 
											HW_ICU_SCI12_IER_RX_MASK;
		EE_HWREG8(HW_ICU_IER_SCI12_TX) = EE_HWREG8(HW_ICU_IER_SCI12_TX) | 
											HW_ICU_SCI12_IER_TX_MASK;
		EE_HWREG8(HW_ICU_IPR_SCI12) = HW_IPR_PRI_LEVEL_1;
		break;
	}
}

/** @brief	Disable Sci channel interrupts in the Interrupt Control Unit (ICU).
 *	@param  _ch SCI Channel Identifier.
 *  
 */
static void Sci_DisableICU(Sci_ChannelType _ch)
{
	switch (_ch) {
	case SCI_CHANNEL_0:
		/*Disable Rx Error and Rx interrupts.*/
		EE_HWREG8(HW_ICU_IER_SCI0_ERX) = EE_HWREG8(HW_ICU_IER_SCI0_ERX) & 
				(~(HW_ICU_SCI0_IER_ER_MASK | HW_ICU_SCI0_IER_RX_MASK));
		/*Disable Tx End interrupts.*/
		EE_HWREG8(HW_ICU_IER_SCI0_TX) = EE_HWREG8(HW_ICU_IER_SCI0_TX) & 
				(~HW_ICU_SCI0_IER_TX_MASK);
		break;
	case SCI_CHANNEL_1:
		EE_HWREG8(HW_ICU_IER_SCI1_ERX) = EE_HWREG8(HW_ICU_IER_SCI1_ERX) & 
				(~(HW_ICU_SCI1_IER_ER_MASK | HW_ICU_SCI1_IER_RX_MASK));
		EE_HWREG8(HW_ICU_IER_SCI1_TX) = EE_HWREG8(HW_ICU_IER_SCI1_TX) & 
				(~HW_ICU_SCI1_IER_TX_MASK);
		break;
	case SCI_CHANNEL_5:
		EE_HWREG8(HW_ICU_IER_SCI5_ERX) = EE_HWREG8(HW_ICU_IER_SCI5_ERX) & 
				(~(HW_ICU_SCI5_IER_ER_MASK | HW_ICU_SCI5_IER_RX_MASK));
		EE_HWREG8(HW_ICU_IER_SCI5_TX) = EE_HWREG8(HW_ICU_IER_SCI5_TX) &
				(~HW_ICU_SCI5_IER_TX_MASK);
		break;
	case SCI_CHANNEL_6:
		EE_HWREG8(HW_ICU_IER_SCI6_ERX) = EE_HWREG8(HW_ICU_IER_SCI6_ERX) & 
				(~(HW_ICU_SCI6_IER_ER_MASK | HW_ICU_SCI6_IER_RX_MASK));
		EE_HWREG8(HW_ICU_IER_SCI6_TX) = EE_HWREG8(HW_ICU_IER_SCI6_TX) & 
				(~HW_ICU_SCI6_IER_TX_MASK);
		break;
	case SCI_CHANNEL_8:
		EE_HWREG8(HW_ICU_IER_SCI8_ERX) = EE_HWREG8(HW_ICU_IER_SCI8_ERX) & 
				(~(HW_ICU_SCI8_IER_ER_MASK | HW_ICU_SCI8_IER_RX_MASK));
		EE_HWREG8(HW_ICU_IER_SCI8_TX) = EE_HWREG8(HW_ICU_IER_SCI8_TX) & 
				(~HW_ICU_SCI8_IER_TX_MASK);
		break;
	case SCI_CHANNEL_9:
		EE_HWREG8(HW_ICU_IER_SCI9_ERX) = EE_HWREG8(HW_ICU_IER_SCI9_ERX) & 
				(~(HW_ICU_SCI9_IER_ER_MASK | HW_ICU_SCI9_IER_RX_MASK));
		EE_HWREG8(HW_ICU_IER_SCI9_TX) = EE_HWREG8(HW_ICU_IER_SCI9_TX) & 
				(~HW_ICU_SCI9_IER_TX_MASK);
		break;
	case SCI_CHANNEL_12:
		EE_HWREG8(HW_ICU_IER_SCI12_ERX) = EE_HWREG8(HW_ICU_IER_SCI12_ERX) & 
				(~(HW_ICU_SCI12_IER_ER_MASK | HW_ICU_SCI12_IER_RX_MASK));
		EE_HWREG8(HW_ICU_IER_SCI12_TX) = EE_HWREG8(HW_ICU_IER_SCI12_TX) & 
				(~HW_ICU_SCI12_IER_TX_MASK);
		break;
	}
}


/*
 * Sci Channel Initialization.
 * 
 * TODO: Support Serial Extended Mode.
 * TODO: Support Smart Card Interface.
 */
static void Sci_InitSciChannel(const Sci_ChannelConfigType * ConfigPtr)
{
	register uint8		brd;	/* Baud-Rate Divisor	*/
	register float32	pclk;	/* Clock Frequency	*/
	
	/* Enables Sci Module in Run-Mode */
	Sci_EnableChannel(ConfigPtr->SciChannelId);
	
	/* Reset UART Control Registers.*/
	UART_RESET(ConfigPtr->SciChannelId);
	
	/* UART set mode, parity mode , data length, clock divisor, etc. */
	UART_SET_MODE(ConfigPtr->SciChannelId, ConfigPtr->SciModeCtrl);
	
	/* UART Baud Clock Source */
	if ( ConfigPtr->SciSysClock ) {
		/* Put UART clock on SCKn pin?*/
		if (ConfigPtr->SciSysCtrl &  SCI_CH_HW_OUPUT_CLK) {
			UART_CLK_SYS_OUTPUT(ConfigPtr->SciChannelId);
		} else {
			UART_CLK_SYS_NO_OUTPUT(ConfigPtr->SciChannelId);
		}

		pclk =	Mcu_Global.ConfigPtr->McuClockSettingConfig[
		      	       Mcu_Global.ClockSetting].McuClockReferencePointFrequency;
		pclk = pclk / UART_GET_PCKB_DIV(
				Mcu_Global.ConfigPtr->McuClockSettingConfig[
				        Mcu_Global.ClockSetting].McuRunModeClockConfiguration2);
	} else {
		/* Set external clock or TMR. */
		UART_CLK_EXT_OSC(ConfigPtr->SciChannelId);
		pclk = SCI_EXT_OSC_FREQ;
	}
	
	if (ConfigPtr->SciSysCtrl &  SCI_CH_HW_RTS_CTS_EN) {
		UART_SET_RTS_CTS(ConfigPtr->SciChannelId);
	}
	
	/* Baud-Rate Divisor computation waiting the peripheral to enable. */
	if ( ConfigPtr->SciSysCtrl & SCI_CH_HW_HIGH_SPEED ) {
		/* Clock Base Divider: 8 */
		UART_SET_8_BIT_BASE_CK(ConfigPtr->SciChannelId);
		
		brd = UART_BRD(ConfigPtr->SciChannelBaudRate, 
				pclk, 
				(ConfigPtr->SciModeCtrl & SCI_CLK_DIV_MASK), 
				SCI_CLK_DIV_HIGH_SPEED);
		
		if (ConfigPtr->SciSysCtrl & SCI_CH_HW_DNF_EN ) {
			UART_EN_DFN(ConfigPtr->SciChannelId);
		}
	} else {
		/* Clock Divider: 16 */
		brd = UART_BRD(ConfigPtr->SciChannelBaudRate, 
				pclk,
				(ConfigPtr->SciModeCtrl & SCI_CLK_DIV_MASK),
				SCI_CLK_DIV_LOW_SPEED);		
	}
	
	/*UART Baud Rate Setup*/
	UART_SET_BRD(ConfigPtr->SciChannelId, brd);
	
	/* Enable SCI interrupts in the ICU) */
	Sci_EnableICU(ConfigPtr->SciChannelId);
	
	/* UART Set Serial Control Reg.*/
	UART_SET_SCR(ConfigPtr->SciChannelId, ConfigPtr->SciSysCtrl & 
			(UART_CH_HW_RX | UART_CH_HW_TX));
}

/*
 * Sci Channel De-Initialization.
 */
#if ( SCI_DEINIT_API == STD_ON )
static void Sci_DeInitSciChannel(const Sci_ChannelConfigType * ConfigPtr)
{
	  /* Enable Sci Module in Run-Mode */
	if ( !Sci_IsChannelEnabled(ConfigPtr->SciChannelId) ) {
		/* Enable Sci Module in Run-Mode */
		Sci_EnableChannel(ConfigPtr->SciChannelId);
	}
	/*Wait until the end of last TX.*/
	while (!UART_TX_ENDED(ConfigPtr->SciChannelId));
	
	/* Reset UART Control Register.*/
	UART_RESET(ConfigPtr->SciChannelId);

	/* Disable SCI interrupts in the ICU) */
	Sci_DisableICU(ConfigPtr->SciChannelId);
	
	/* Enable Sci Module in Run-Mode */
	Sci_DisableChannel(ConfigPtr->SciChannelId);
}
#endif

/*
 * Sci_Init implementation.
 */
void Sci_Init(const Sci_ConfigType *	ConfigPtr)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE( ( ConfigPtr != NULL ), SCI_INIT_SERVICE_ID, SCI_E_PARAM_POINTER );

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(!Sci_Global.Init, SCI_INIT_SERVICE_ID, 
			SCI_E_ALREADY_INITIALIZED, flags);

	Sci_Global.ConfigPtr = ConfigPtr;
	Sci_Global.Init = TRUE;

	for (channel = 0; channel < ConfigPtr->SciNumberOfSciChannels; channel++) {
		/* Initializes Sci Channel. */
		Sci_InitSciChannel(&(ConfigPtr->SciChannels[channel]));
	}

	EE_hal_resumeIRQ(flags);

}

/*
 * Sci_WriteTxData implementation.
 */
Std_ReturnType Sci_WriteTxData( Sci_ChannelType	Channel, uint8	Data)
{
	register EE_FREG		flags;
	register uint8_least		ChIdx;
	register Std_ReturnType	rv;

	VALIDATE_W_RV( ( Channel < SCI_CHANNELS_NUMBER ), 
			SCI_WRITETXDATA_SERVICE_ID, 
			SCI_E_INVALID_CHANNEL, 
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init, 
			SCI_WRITETXDATA_SERVICE_ID, 
			SCI_E_UNINIT, 
			E_NOT_OK,
			flags);

	for (ChIdx = 0;( 
			( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
			( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel)
	); ChIdx++) { ;}
	  
	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ), 
			SCI_WRITETXDATA_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK, 
			flags);
	
	VALIDATE_IRQ_W_RV(
			( Sci_IsChannelEnabled(Channel) ),
			SCI_WRITETXDATA_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);
		
	if ( UART_TX_ENDED(Channel) ) {
		
		UART_TX_DATA(Channel, (uint32) Data);
		
		rv = E_OK;
	
	} else {
		
		rv = E_NOT_OK;
	}

	EE_hal_resumeIRQ(flags);

	return rv;
	

}

/*
 * Sci_ReadRxData implementation.
 */
Std_ReturnType Sci_ReadRxData(Sci_ChannelType	Channel, uint8* DataPtr)
{	
	register EE_FREG		flags;
	register uint8_least		ChIdx;
	register Std_ReturnType	rv;

	VALIDATE_W_RV( ( Channel < SCI_CHANNELS_NUMBER ),
			SCI_READRXDATA_SERVICE_ID,
			SCI_E_INVALID_CHANNEL, 
			E_NOT_OK);

	VALIDATE_W_RV( ( DataPtr != NULL_PTR ), 
			SCI_READRXDATA_SERVICE_ID, 
			SCI_E_PARAM_POINTER, 
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_READRXDATA_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}
	
	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_READRXDATA_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);

	VALIDATE_IRQ_W_RV(( Sci_IsChannelEnabled(Channel) ),
			SCI_READRXDATA_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);

	if (UART_RX_ERR(Channel)) {
		
		rv = E_NOT_OK;		
	
	} else {

		(*DataPtr) = (uint8) UART_RX_DATA(Channel);
		
	    rv = E_OK;
	}

	EE_hal_resumeIRQ(flags);

	return rv;
  
}

#if ( SCI_NOTIFICATIONS_API == STD_ON )
/*
 * Sci_EnableNotifications implementation.
 */
void Sci_EnableNotifications(Sci_ChannelType	Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
			SCI_E_INVALID_CHANNEL);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Sci_Global.Init, 
			SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
			SCI_E_UNINIT,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			flags);

	if ( Sci_IsChannelEnabled(Channel) ) {
		
		UART_INT_ENABLE(Channel, (UART_INT_TX_START | UART_INT_RX_ER));
	}

	EE_hal_resumeIRQ(flags);
}

/*
 * Sci_DisableNotifications implementation.
 */
void Sci_DisableNotifications(Sci_ChannelType	Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_DISABLE_NOTIFICATIONS_SERVICE_ID,
			SCI_E_INVALID_CHANNEL);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Sci_Global.Init,
			SCI_DISABLE_NOTIFICATIONS_SERVICE_ID,
			SCI_E_UNINIT,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_DISABLE_NOTIFICATIONS_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			flags);

	if ( Sci_IsChannelEnabled(Channel) ) {

	    UART_INT_DISABLE(Channel, UART_INT_ALL);
	
	}

	EE_hal_resumeIRQ(flags);
}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_GoToSleep implementation.
 */
Std_ReturnType Sci_GoToSleep(Sci_ChannelType	Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_GOTOSLEEP_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_GOTOSLEEP_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_GOTOSLEEP_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);


	VALIDATE_IRQ_W_RV(( Sci_IsChannelEnabled(Channel) ),
			SCI_GOTOSLEEP_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);

	/* Disables Sci Module in Run-Mode */
	Sci_DisableChannel(Channel);

	EE_hal_resumeIRQ(flags);

	return E_OK;
}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_Wakeup implementation.
 */
Std_ReturnType Sci_Wakeup(Sci_ChannelType	Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_WAKEUP_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_WAKEUP_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_WAKEUP_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);


	VALIDATE_IRQ_W_RV(!( Sci_IsChannelEnabled(Channel) ),
			SCI_WAKEUP_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);

	/* Enables Sci Module in Run-Mode */
	Sci_EnableChannel(Channel);

	EE_hal_resumeIRQ(flags);

	return E_OK;
}
#endif

/*
 * Sci_GetStatus implementation.
 */
Sci_StatusType Sci_GetStatus(Sci_ChannelType Channel)
{
	register EE_FREG		flags;
	register Sci_StatusType	ret;
	register uint8_least	ChIdx;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_GETSTATUS_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			SCI_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_GETSTATUS_SERVICE_ID,
			SCI_E_UNINIT,
			SCI_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_GETSTATUS_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);

	if ( Sci_IsChannelEnabled(Channel) ) {
		
		if ( UART_RX_ERR(Channel) ) {

			ret = SCI_RX_ERROR;

	    } else if (!UART_TX_ENDED(Channel)) {

	    	ret = SCI_TX_BUSY;

	    } else {

	      ret = SCI_OPERATIONAL;
	    }

	} else {

	    ret = SCI_CH_SLEEP;

	}

	EE_hal_resumeIRQ(flags);

	return ret;
}

#if ( SCI_DEINIT_API == STD_ON )
/*
 * Sci_DeInit implementation.
 */
void Sci_DeInit(void)
{

	register EE_FREG	flags;
	register uint32	channel;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ( Sci_Global.Init, SCI_DEINIT_SERVICE_ID, SCI_E_UNINIT, flags );

	for (channel = 0; channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels;
			channel++) {

		/* De-Initializes Sci Channel. */
		Sci_DeInitSciChannel(&(Sci_Global.ConfigPtr->SciChannels[channel]));
	}

	Sci_Global.ConfigPtr = NULL;
	Sci_Global.Init = FALSE;
	
	EE_hal_resumeIRQ(flags);

}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_CheckWakeup implementation.
 */
Std_ReturnType Sci_CheckWakeup(Sci_ChannelType	Channel)
{
	register EE_FREG		flags;
	register uint8_least		ChIdx;
	register Std_ReturnType	rv;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_CHECKWAKEUP_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_CHECKWAKEUP_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_CHECKWAKEUP_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);

	rv = E_NOT_OK;

	if ( Sci_IsChannelEnabled(Channel) ) {

		rv =  E_OK;

	}

	EE_hal_resumeIRQ(flags);

	return rv;
}
#endif

/*
 * Sci_DisableTx implementation.
 */
Std_ReturnType Sci_DisableTx(Sci_ChannelType Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_DISABLETX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_DISABLETX_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_DISABLETX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);

	VALIDATE_IRQ_W_RV(( Sci_IsChannelEnabled(Channel) ),
			SCI_DISABLETX_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);


	/* Waits end of transmission */
	while( !UART_TX_ENDED(Channel) ) { ; }

	/* Disable TX */
	UART_DISABLE_TX(Channel);

	EE_hal_resumeIRQ(flags);

	return E_OK;
}

/*
 * Sci_EnableTx implementation.
 */
Std_ReturnType Sci_EnableTx(Sci_ChannelType	Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_ENABLETX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_ENABLETX_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_ENABLETX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);

	VALIDATE_IRQ_W_RV(( Sci_IsChannelEnabled(Channel) ),
			SCI_ENABLETX_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);
	/* Enable TX */
	UART_ENABLE_TX(Channel);

	EE_hal_resumeIRQ(flags);

	return E_OK;
}

/*
 * Sci_DisableRx implementation.
 */
Std_ReturnType Sci_DisableRx(Sci_ChannelType	Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_DISABLERX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_DISABLERX_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_DISABLERX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);

	VALIDATE_IRQ_W_RV(( Sci_IsChannelEnabled(Channel) ),
			SCI_DISABLERX_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);

	/* Disable RX */
	UART_DISABLE_RX(Channel);

	EE_hal_resumeIRQ(flags);

	return E_OK;	
}

/*
 * Sci_EnableRx implementation.
 */
Std_ReturnType Sci_EnableRx(Sci_ChannelType	Channel)
{
	register EE_FREG	flags;
	register uint8_least	ChIdx;

	VALIDATE_W_RV(( Channel < SCI_CHANNELS_NUMBER ),
			SCI_ENABLERX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Sci_Global.Init,
			SCI_ENABLERX_SERVICE_ID,
			SCI_E_UNINIT,
			E_NOT_OK,
			flags);

	for (ChIdx = 0;
	    (
	      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
	      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
	    );
	    ChIdx++) {;}

	VALIDATE_IRQ_W_RV(( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
			SCI_ENABLERX_SERVICE_ID,
			SCI_E_INVALID_CHANNEL,
			E_NOT_OK,
			flags);

	VALIDATE_IRQ_W_RV(( Sci_IsChannelEnabled(Channel) ),
			SCI_ENABLERX_SERVICE_ID,
			SCI_E_STATE_TRANSITION,
			E_NOT_OK,
			flags);
	/* Enable RX */
	UART_ENABLE_RX(Channel);

	EE_hal_resumeIRQ(flags);

	return E_OK;

}
