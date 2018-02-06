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
 * AUTOSAR-"like" SCI Driver Source File.
 *
 * Author:  2011,  Giuseppe Serano
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
typedef struct
{
  boolean			Init;		/* SCI Driver Initialized? */

  const Sci_ConfigType *	ConfigPtr;	/* Actual Configuration */

} Sci_GlobalType;


/*
 * Global config
 */
Sci_GlobalType Sci_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
};

/*
 * MCU Global Configuration Reference
 */
typedef struct
{
  boolean			Init;		/* MCU Driver Initialized? */

  const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration */

  Mcu_ClockType			ClockSetting;	/* Actual Clock Setting */

} Mcu_GlobalType;
extern Mcu_GlobalType Mcu_Global;

#include "Sci_Internal.h"

/*
 * Usefull Sci Channel Macros
 */
#define	SCI_PIOSC_FREQ	1.6E7

#define	SCI_CLK_DIV_HIGH_SPEED	8	/* High-Speed Clock Divisor.	 */
#define	SCI_CLK_DIV_LOW_SPEED	16	/* Low-Speed Clock Divisor.	 */

/* Clock Control */
#define	SCI_CH_SYSCLK	0x000000000	/* System Clock			 */
#define	SCI_CH_PIOSC	0x000000001	/* Precision Internal Oscillator */


/*
 * Sci Channel Initialization.
 */
static void Sci_InitSciChannel(
  const Sci_ChannelConfigType *	ConfigPtr
)
{

  register float32	brd;	/* Baud-Rate Divisor	*/
  register float32	clk;	/* Clock Frequency	*/

  /* Enables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R |= HW_CH_2_CGC_MASK(ConfigPtr->SciChannelId);

  /* Disables Channel */
  UART_DISABLE(ConfigPtr->SciChannelId);

  /* Flushes Fifo */
  UART_FIFO_FLUSH(ConfigPtr->SciChannelId);

  /* Waits end of transmission/reception */
  while(
    UART_BUSY(ConfigPtr->SciChannelId) ||
    !UART_TX_FIFO_EMPTY(ConfigPtr->SciChannelId) ||
    !UART_RX_FIFO_EMPTY(ConfigPtr->SciChannelId)
  ) {
    ;
  }

  /* Clear Errors */
  UART_RX_ERR_CLR(ConfigPtr->SciChannelId);

  /* UART Baud Clock Source */
  if ( ConfigPtr->SciSysClock ) {

    UART_CLK_SYS(ConfigPtr->SciChannelId);

    clk =	Mcu_Global.ConfigPtr->McuClockSettingConfig[
			Mcu_Global.ClockSetting
		].McuClockReferencePointFrequency;

  }
  else {

    UART_CLK_PIOSC(ConfigPtr->SciChannelId);

    clk = SCI_PIOSC_FREQ;

  }

  /* Baud-Rate Divisor computation waiting the peripheral to enable. */
  if ( ConfigPtr->SciSysCtrl & SCI_CH_HW_HIGH_SPEED ) {

    /* Clock Divider: 8 */
    brd = UART_BRD(ConfigPtr->SciChannelBaudRate, clk, SCI_CLK_DIV_HIGH_SPEED);

  }
  else {

    /* Clock Divider: 16 */
    brd = UART_BRD(ConfigPtr->SciChannelBaudRate, clk, SCI_CLK_DIV_LOW_SPEED);

  }

  /* Integer Baud-Rate Divisor Sets-Up */
  UART_SET_IBRD(ConfigPtr->SciChannelId, (uint32) brd);

  /* Fractional Baud-Rate Divisor Sets-Up */
  UART_SET_FBRD(
    ConfigPtr->SciChannelId, (uint32) ((brd - ((uint32) brd)) * 64 + 0.5)
  );

  /* Line Control Sets-Up */
  UART_SET_LINE_CTRL(ConfigPtr->SciChannelId, ConfigPtr->SciLineCtrl);

  /* System Control Sets-Up */
  UART_SET_SYS_CTRL(
    ConfigPtr->SciChannelId, (ConfigPtr->SciSysCtrl & ~SCI_CH_HW_ENABLE)
  );

  /* Clear Interrupt */
  UART_INT_CLEAR(ConfigPtr->SciChannelId, UART_INT_ALL);

  /* Enables Channel */
  UART_ENABLE(ConfigPtr->SciChannelId);

}

/*
 * Sci Channel De-Initialization.
 */
#if ( SCI_DEINIT_API == STD_ON )
static void Sci_DeInitSciChannel(
  const Sci_ChannelConfigType *	ConfigPtr
)
{

  register uint32	mask = HW_CH_2_CGC_MASK(ConfigPtr->SciChannelId);

  /* Enables Sci Module in Run-Mode */
  if ( !( SYSCTL_RCGCUART_R & mask ) ) {

    SYSCTL_RCGCUART_R |= mask;

  }

  SYSCTL_SRUART_R |= mask;			/* Start Channel Module Reset */
  SYSCTL_SRUART_R &= ~mask;			/* Stop  Channel Module Reset */
  while ( !( SYSCTL_PRUART_R & mask ) );	/* Wait Reset		      */

  /* Disables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R &= ~(mask);

}
#endif

/*
 * Sci_Init implementation.
 */
void Sci_Init(
  const Sci_ConfigType *	ConfigPtr
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE( ( ConfigPtr != NULL ), SCI_INIT_SERVICE_ID, SCI_E_PARAM_POINTER );

  VALIDATE( ( Hw_CheckCore() == E_OK ), SCI_INIT_SERVICE_ID, SCI_E_UNINIT );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    !Sci_Global.Init,
    SCI_INIT_SERVICE_ID,
    SCI_E_ALREADY_INITIALIZED,
    flags
  );

  Sci_Global.ConfigPtr = ConfigPtr;
  Sci_Global.Init = TRUE;

  for (channel = 0; channel < ConfigPtr->SciNumberOfSciChannels; channel++)
  {

    /* Initializes Sci Channel. */
    Sci_InitSciChannel(&(ConfigPtr->SciChannels[channel]));

  }

  EE_hal_resumeIRQ(flags);

}

/*
 * Sci_WriteTxData implementation.
 */
Std_ReturnType Sci_WriteTxData(
  Sci_ChannelType	Channel,
  uint8			Data
)
{

  register EE_FREG		flags;
  register uint8_least		ChIdx;
  register Std_ReturnType	rv;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_WRITETXDATA_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  if (UART_TX_FIFO_FULL(Channel)) {

    rv = E_NOT_OK;

  }
  else {

    UART_TX_DATA(Channel, (uint32) Data);

    rv = E_OK;

  }

  EE_hal_resumeIRQ(flags);

  return rv;

}

/*
 * Sci_ReadRxData implementation.
 */
Std_ReturnType Sci_ReadRxData(
  Sci_ChannelType	Channel,
  uint8 *		DataPtr
)
{

  register EE_FREG		flags;
  register uint8_least		ChIdx;
  register Std_ReturnType	rv;
  register uint32		rx;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( DataPtr != NULL_PTR ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_PARAM_POINTER,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_READRXDATA_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  if (UART_RX_FIFO_EMPTY(Channel)) {

    rv = E_NOT_OK;

  }
  else {

    rx = UART_RX_DATA(Channel);
    (*DataPtr) = (uint8) rx;

    rv = E_OK;

  }

  EE_hal_resumeIRQ(flags);

  return rv;

}

#if ( SCI_NOTIFICATIONS_API == STD_ON )
/*
 * Sci_EnableNotifications implementation.
 */
void Sci_EnableNotifications(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;

  VALIDATE(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Sci_Global.Init,
    SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_UNINIT,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_ENABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    flags
  );

  if ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ) {

    UART_INT_ENABLE(
      Channel, UART_INT_TX | UART_INT_RX | UART_INT_RT | UART_INT_RX_ERR
    );

  }

  EE_hal_resumeIRQ(flags);

}

/*
 * Sci_DisableNotifications implementation.
 */
void Sci_DisableNotifications(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;

  VALIDATE(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_DISABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Sci_Global.Init,
    SCI_DISABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_UNINIT,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_DISABLE_NOTIFICATIONS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    flags
  );

  if ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ) {

    UART_INT_DISABLE(
      Channel, UART_INT_TX | UART_INT_RX | UART_INT_RT | UART_INT_RX_ERR
    );

  }

  EE_hal_resumeIRQ(flags);

}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_GoToSleep implementation.
 */
Std_ReturnType Sci_GoToSleep(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;
  register uint32	mask;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  mask = HW_CH_2_CGC_MASK(Channel);

  VALIDATE_IRQ_W_RV(
    ( SYSCTL_RCGCUART_R & mask ),
    SCI_GOTOSLEEP_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Disables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R &= ~mask;

  EE_hal_resumeIRQ(flags);

  return E_OK;

}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_Wakeup implementation.
 */
Std_ReturnType Sci_Wakeup(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;
  register uint32	mask;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  mask = HW_CH_2_CGC_MASK(Channel);

  VALIDATE_IRQ_W_RV(
    !( SYSCTL_RCGCUART_R & mask ),
    SCI_WAKEUP_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Enables Sci Module in Run-Mode */
  SYSCTL_RCGCUART_R |= mask;

  EE_hal_resumeIRQ(flags);

  return E_OK;

}
#endif

/*
 * Sci_GetStatus implementation.
 */
Sci_StatusType Sci_GetStatus(
  Sci_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register Sci_StatusType	ret;
  register uint8_least		ChIdx;
  register uint32		ris, mis;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    SCI_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_UNINIT,
    SCI_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_GETSTATUS_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    SCI_NOT_OK,
    flags
  );

  if ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ) {

    ris = UART_RIS(Channel);
    mis = UART_MIS(Channel);

    if ( ( ris & UART_INT_RT ) || ( mis & UART_INT_RT ) ) {

      ret = SCI_RX_ERROR;

    }
    else if (!UART_RX_FIFO_EMPTY(Channel)) {

      if (UART_RX_ERR(Channel)) {

        ret = SCI_RX_ERROR;

      }
      else {

        ret = SCI_RX_OK;

      }

    }
    else if (UART_BUSY(Channel)) {

      ret = SCI_TX_BUSY;

    }
    else if ( ( ris & UART_INT_TX ) || ( ris & UART_INT_TX ) ) {

      ret = SCI_TX_OK;

    }
    else {

      ret = SCI_OPERATIONAL;

    }

  }
  else {

    ret = SCI_CH_SLEEP;

  }

  EE_hal_resumeIRQ(flags);

  return ret;

}

#if ( SCI_DEINIT_API == STD_ON )
/*
 * Sci_DeInit implementation.
 */
void Sci_DeInit(
  void
)
{

  register EE_FREG	flags;
  register uint32	channel;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ( Sci_Global.Init, SCI_DEINIT_SERVICE_ID, SCI_E_UNINIT, flags );

  for (
    channel = 0;
    channel < Sci_Global.ConfigPtr->SciNumberOfSciChannels;
    channel++
  )
  {

    /* De-Initializes Sci Channel. */
    Sci_DeInitSciChannel(&(Sci_Global.ConfigPtr->SciChannels[channel]));

  }

  EE_hal_resumeIRQ(flags);

}
#endif

#if ( SCI_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Sci_CheckWakeup implementation.
 */
Std_ReturnType Sci_CheckWakeup(
  Sci_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register uint8_least		ChIdx;
  register Std_ReturnType	rv;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_CHECKWAKEUP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_CHECKWAKEUP_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_CHECKWAKEUP_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  rv = E_NOT_OK;

  if ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ) {

    rv =  E_OK;

  }

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif

/*
 * Sci_DisableTx implementation.
 */
Std_ReturnType Sci_DisableTx(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_DISABLETX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Waits end of transmission/reception */
  while( UART_BUSY(Channel) ) {
    ;
  }

  while ( !UART_RX_FIFO_EMPTY(Channel) ) {

    UART_RX_DATA(Channel);

  }

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Disable TX */
  UART_DISABLE_TX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

/*
 * Sci_EnableTx implementation.
 */
Std_ReturnType Sci_EnableTx(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_ENABLETX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Waits end of transmission/reception */
  while( UART_BUSY(Channel) ) {
    ;
  }

  while ( !UART_RX_FIFO_EMPTY(Channel) ) {

    UART_RX_DATA(Channel);

  }

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Enable TX */
  UART_ENABLE_TX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

/*
 * Sci_DisableRx implementation.
 */
Std_ReturnType Sci_DisableRx(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_DISABLERX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Waits end of transmission/reception */
  while( UART_BUSY(Channel) ) {
    ;
  }

  while ( !UART_RX_FIFO_EMPTY(Channel) ) {

    UART_RX_DATA(Channel);

  }

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Disable RX */
  UART_DISABLE_RX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

/*
 * Sci_EnableRx implementation.
 */
Std_ReturnType Sci_EnableRx(
  Sci_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint8_least	ChIdx;

  VALIDATE_W_RV(
    ( Channel < SCI_CHANNELS_NUMBER ),
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Sci_Global.Init,
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    ChIdx = 0;
    (
      ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ) &&
      ( Sci_Global.ConfigPtr->SciChannels[ChIdx].SciChannelId != Channel )
    );
    ChIdx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( ChIdx < Sci_Global.ConfigPtr->SciNumberOfSciChannels ),
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_INVALID_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( SYSCTL_RCGCUART_R & HW_CH_2_CGC_MASK(Channel) ),
    SCI_ENABLERX_SERVICE_ID,
    SCI_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Disables Channel */
  UART_DISABLE(Channel);

  /* Waits end of transmission/reception */
  while( UART_BUSY(Channel) ) {
    ;
  }

  while ( !UART_RX_FIFO_EMPTY(Channel) ) {

    UART_RX_DATA(Channel);

  }

  /* Flushes Fifo */
  UART_FIFO_FLUSH(Channel);

  /* Enable RX */
  UART_ENABLE_RX(Channel);

  /* Enables Channel */
  UART_ENABLE(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}
