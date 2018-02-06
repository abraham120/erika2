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
 * GPT367:	Gpt.c Module source file.
 *
 * AUTOSAR-"like" GPT Driver Source File.
 *
 * Author:  2011,  Giuseppe Serano
 */

/*
 * GPT293:	Gpt.c shall include Gpt.h.
 *
 * Comment: Gpt.c has implicit access to the Gpt_Cfg.h through the Gpt.h file.
 */
#include "Gpt.h"

/* 
 * GPT256:	The GPT module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files. The imported included files
 * 		shall be checked by preprocessing directives. (BSW004)
 *
 * The following version numbers shall be verified:
 * - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * Where <MODULENAME> is the module abbreviation of the other (external) modules
 * which provide header files included by the GPT module.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	GPT_AR_RELEASE_MAJOR_VERSION	4
#define	GPT_AR_RELEASE_MINOR_VERSION	0

#if !defined( GPT_AR_MAJOR_VERSION ) || \
    ( GPT_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION )
#error	Gpt: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* GPT_DEV_ERROR_DETECT */

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

#endif	/* !GPT_DEV_ERROR_DETECT */

#include "Gpt_Internal.h"

/*
 * Type that holds all global data for Gpt Driver
 */
typedef struct
{

  boolean			Init;		/* GPT Driver Initialized?    */

  const Gpt_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

  uint32			Status;		/* Channel Status	      */

  uint32			Notifications;	/* Channel Notifications      */

} Gpt_GlobalType;


/*
 * Global config
 */
Gpt_GlobalType Gpt_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr	*/
  0x00000000		/* Status	*/
};

/*
 * MCU Global Configuration Reference
 */
typedef struct
{
  boolean			Init;		/* MCU Driver Initialized?    */

  const Mcu_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

  Mcu_ClockType			ClockSetting;	/* Actual Clock Setting	      */

} Mcu_GlobalType;

/*
 * MCU Global Configuration External Reference
 */
extern Mcu_GlobalType Mcu_Global;

/*
 * Gpt Enable Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_EnableChannel(
  Gpt_ChannelType	Channel
)
{

  if ( !GPT_CH_IS_WIDE(Channel) ) {

    SYSCTL_RCGCTIMER_R |= HW_CH_2_CGC_MASK(Channel);

  }
  else if ( GPT_CH_IS_WIDE_NOT_IN_ROW(Channel) ) {

    SYSCTL_RCGCWTIMER_R |= 
    HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GTP_TMR_WIDE_ROW_OFFSET);

  }
  else {

    SYSCTL_RCGCWTIMER_R |=
    HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GPT_INTERNAL_CHANNEL_W_0_A);

  }

}

#if ( GPT_DEINIT_API == STD_ON )
/*
 * Gpt Disable Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_DisableChannel(
  Gpt_ChannelType	Channel
)
{

  if ( !GPT_CH_IS_WIDE(Channel) ) {

    SYSCTL_RCGCTIMER_R &= ~HW_CH_2_CGC_MASK(Channel);

  }
  else if ( GPT_CH_IS_WIDE_NOT_IN_ROW(Channel) ) {

    SYSCTL_RCGCWTIMER_R &= 
    ~HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GTP_TMR_WIDE_ROW_OFFSET);

  }
  else {

    SYSCTL_RCGCWTIMER_R &=
    ~HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GPT_INTERNAL_CHANNEL_W_0_A);

  }

}

/*
 * Gpt Reset Channel
 *
 * param	Channel	Numeric ID of a GPT Channel.
 */
static void Gpt_ResetChannel(
  Gpt_ChannelType	Channel
)
{

  register uint32	mask;

  if ( !GPT_CH_IS_WIDE(Channel) ) {

    mask = HW_CH_2_CGC_MASK(Channel);
    SYSCTL_SRTIMER_R |= mask;			/* Start Channel Module Reset */
    SYSCTL_SRTIMER_R &= ~mask;			/* Stop  Channel Module Reset */
    while ( !( SYSCTL_PRTIMER_R & mask ) );	/* Wait Reset		      */

  }
  else {

    if ( GPT_CH_IS_WIDE_NOT_IN_ROW(Channel) ) {
  
      mask =
      HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GTP_TMR_WIDE_ROW_OFFSET);

    }
    else {

      mask =
      HW_CH_2_CGC_MASK(Channel - (Gpt_ChannelType)GPT_INTERNAL_CHANNEL_W_0_A);

    }
    SYSCTL_SRWTIMER_R |= mask;			/* Start Channel Module Reset */
    SYSCTL_SRWTIMER_R &= ~mask;			/* Stop  Channel Module Reset */
    while ( !( SYSCTL_PRWTIMER_R & mask ) );	/* Wait Reset		      */

  }

}
#endif

/*
 * Gpt Channel Initialization.
 */
static void Gpt_InitGptChannel(
  const Gpt_ChannelConfigType *	ConfigPtr
)
{

  register boolean	joined;
  register boolean	wide;

  /* Gpt Module Disabled? */
  if ( 
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(ConfigPtr->GptChannelId) )
  ) {

    /* Enables Gpt Module in Run-Mode */
    Gpt_EnableChannel(ConfigPtr->GptChannelId);

  }

  /* Turn-on Gpt Unit */
  Gpt_Global.Status |= GPT_CH_2_UNIT_STAT_MASK(ConfigPtr->GptChannelId);

  /* Stop Timer. */
  GPT_TMR_STOP(ConfigPtr->GptChannelId);

  /* Heavy Checks Made Once!!! */
  joined = GPT_CH_IS_JOINED(ConfigPtr->GptChannelId);
  wide = GPT_CH_IS_WIDE(ConfigPtr->GptChannelId);

  /* Configuration Setup */
  /* GPT_SET_CFG(ConfigPtr->GptChannelId, ConfigPtr->GptChannelHWConfig); */
  if ( joined ) {

    GPT_SET_CFG(ConfigPtr->GptChannelId, GPT_CH_HW_CFG_JOIN);

  }
  else {

    GPT_SET_CFG(ConfigPtr->GptChannelId, GPT_CH_HW_CFG_SPLIT);

  }

  /* Mode Setup */
  /* GPT_SET_MODE(ConfigPtr->GptChannelId, ConfigPtr->GptChannelHWMode); */
  if (ConfigPtr->GptChannelMode == GPT_CH_MODE_CONTINUOUS) {

    GPT_SET_MODE(ConfigPtr->GptChannelId, GPT_CH_HW_MODE_PERIODIC);

  }
  else {

    GPT_SET_MODE(ConfigPtr->GptChannelId, GPT_CH_HW_MODE_ONE_SHOT);

  }

  /* Control Setup */
  /* GPT_SET_CTL(ConfigPtr->GptChannelId, ConfigPtr->GptChannelHWCtrl); */
#ifdef	DEBUG
  GPT_SET_CTL(ConfigPtr->GptChannelId, GPT_CH_HW_CTL_STALL);
#endif

  /* Clear Interrupts: cleared by harware initialization */
  /* GPT_INT_CLR(ConfigPtr->GptChannelId, GPT_TMR_INT_ALL); */

  /* Clear Prescaler: cleared by hardware initialization */
  /* GPT_SET_PRESCALER(ConfigPtr->GptChannelId, GPT_HW_TMR_EMPTY_VALUE); */
  
  /* Clear Counter */
  if ( joined && wide ) {

    GPT_SET_COUNTER(ConfigPtr->GptChannelId + 1, GPT_HW_TMR_EMPTY_VALUE);

  }

  GPT_SET_COUNTER(ConfigPtr->GptChannelId, GPT_HW_TMR_EMPTY_VALUE);

}

/*
 * Gpt Channel De-Initialization.
 */
#if ( GPT_DEINIT_API == STD_ON )
static void Gpt_DeInitGptChannel(
  const Gpt_ChannelConfigType *	ConfigPtr
)
{

  /* Gpt Module Disabled? */
  if (
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(ConfigPtr->GptChannelId) )
  ) {

    /* Enables Gpt Module in Run-Mode */
    Gpt_EnableChannel(ConfigPtr->GptChannelId);

  }

  /* Disable Gpt Module in Run-Mode */
  Gpt_ResetChannel(ConfigPtr->GptChannelId);

  /* Turn-off Gpt Unit */
  Gpt_Global.Status &= ~GPT_CH_2_UNIT_STAT_MASK(ConfigPtr->GptChannelId);

  /* Gpt Module Disabled? */
  if (
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(ConfigPtr->GptChannelId) )
  ) {

    /* Disable Gpt Module in Run-Mode */
    Gpt_DisableChannel(ConfigPtr->GptChannelId);

  }

}
#endif

/*
 * Gpt_Init implementation.
 */
void Gpt_Init(
  const Gpt_ConfigType *	ConfigPtr
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE( ( ConfigPtr != NULL), GPT_INIT_SERVICE_ID, GPT_E_PARAM_CONFIG );

  VALIDATE( ( Hw_CheckCore() == E_OK), GPT_INIT_SERVICE_ID, GPT_E_UNINIT );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    !Gpt_Global.Init,
    GPT_INIT_SERVICE_ID,
    GPT_E_ALREADY_INITIALIZED,
    flags
  );

  for (channel = 0; channel < ConfigPtr->GptNumberOfGptChannels; channel++)
  {

    /* Initializes Gpt Channel. */
    Gpt_InitGptChannel(&(ConfigPtr->GptChannels[channel]));

  }

  Gpt_Global.ConfigPtr = ConfigPtr;
  Gpt_Global.Init = TRUE;

  EE_hal_resumeIRQ(flags);

}

#if ( GPT_DEINIT_API == STD_ON )
/*
 * Gpt_DeInit implementation.
 */
void Gpt_DeInit(
  void
)
{

  register EE_FREG	flags;
  register uint32	channel;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_DEINIT_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  for (
    channel = 0;
    channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels;
    channel++
  )
  {

    /* De-Initializes Gpt Channel. */
    Gpt_DeInitGptChannel(&(Gpt_Global.ConfigPtr->GptChannels[channel]));

  }

  Gpt_Global.Init = FALSE;
  Gpt_Global.ConfigPtr = NULL_PTR;

  EE_hal_resumeIRQ(flags);

}
#endif

#if ( \
  ( GPT_TIME_ELAPSED_API == STD_ON ) || ( GPT_TIME_REMAINING_API == STD_ON ) \
)
/*
 * Gpt_GetHWTimeRemaining implementation.
 */
static Gpt_ValueType Gpt_GetHWTimeRemaining(
  Gpt_ChannelType	Channel
)
{

  Gpt_ValueType		rv;
  register boolean	wide;
  register uint32	counter1;
  register uint32	counter2;
  register uint32	prescaler1;
  register uint32	prescaler2;

  wide = GPT_CH_IS_WIDE(Channel);	/* Heavy Check Made Once!!! */

  if ( GPT_CH_IS_JOINED(Channel) ) {

    /* Joined Channel: NO PRESCALERS!!! */
    if ( wide ) {

      do {

	counter1 = GPT_GET_COUNTER(Channel + 1);	/* TMR B 1st Read     */
	prescaler1 = GPT_GET_COUNTER(Channel);		/* TMR A Read	      */
	counter2 = GPT_GET_COUNTER(Channel + 1);	/* TMR B 2nd Read     */

      } while (counter1 != counter2);			/* Consistency Check  */
      
      rv = ((Gpt_ValueType)counter1 << GPT_HW_TMR_JOIN_WIDE_VALUE_S) +
	    (Gpt_ValueType)prescaler1;

    }
    else {

      rv = (Gpt_ValueType)GPT_GET_COUNTER(Channel);

    }

  }
  else if ( wide ) {	/* Wide Channel Not Joined */

    do {

      prescaler2 = GPT_GET_PRESCALER(Channel);	/* Prescaler 1st Read	*/
      counter2 = GPT_GET_COUNTER(Channel);	/* Counter 1st Read	*/
      prescaler1 = GPT_GET_PRESCALER(Channel);	/* Prescaler 2nd Read	*/
      counter1 = GPT_GET_COUNTER(Channel);	/* Counter 2nd Read	*/

      if (
	( prescaler1 == prescaler2 ) &&
	( prescaler1 == GPT_HW_TMR_EMPTY_VALUE )
      ) {	/* Channel Without Prescaler */

	counter2 = counter1;
	rv = (Gpt_ValueType)counter1;

      }
      else {	/* Channel With Prescaler */

	rv = ((Gpt_ValueType)counter1 << GPT_HW_TMR_WIDE_PRESCALER_IN_S) +
	      (Gpt_ValueType)prescaler1;

      }

    } while (counter1 != counter2);	/* Consistency Check	*/

  }
  else {	/* Not Wide Channel Not Joined */

    /* Counter 1st Read	*/
    counter2 = GPT_GET_COUNTER(Channel);
    /* Counter 2nd Read	*/
    counter1 = GPT_GET_COUNTER(Channel);
    prescaler1 =
    (counter1 & GPT_HW_TMR_PRESCALER_OUT_MASK) >> GPT_HW_TMR_PRESCALER_OUT_S;
    prescaler2 =
    (counter2 & GPT_HW_TMR_PRESCALER_OUT_MASK) >> GPT_HW_TMR_PRESCALER_OUT_S;
    counter1 = (counter1 & ~((Gpt_ValueType)GPT_HW_TMR_PRESCALER_OUT_MASK));

    if ( 
      ( prescaler1 == prescaler2 ) &&
      ( prescaler1 == GPT_HW_TMR_EMPTY_VALUE )
    ) {	/* Channel Without Prescaler */

      rv = (Gpt_ValueType)counter1;

    }
    else {	/* Channel With Prescaler */

      rv = ((Gpt_ValueType)counter1 << GPT_HW_TMR_PRESCALER_IN_S) + 
	    (Gpt_ValueType)prescaler1;

    }

  }

  return rv;

}
#endif	/* 
	 * ( GPT_TIME_ELAPSED_API == STD_ON ) ||
	 * ( GPT_TIME_REMAINING_API == STD_ON )
	 */

#if ( GPT_TIME_ELAPSED_API == STD_ON )
/*
 * Gpt_GetHWStartTime implementation.
 */
static Gpt_ValueType Gpt_GetHWStartTime(
  Gpt_ChannelType	Channel
)
{

  Gpt_ValueType		rv;
  register boolean	wide;
  register uint32	counter;
  register uint32	prescaler;

  wide = GPT_CH_IS_WIDE(Channel);	/* Heavy Check Made Once!!! */

  if ( GPT_CH_IS_JOINED(Channel) ) {

    /* Joined Channel: NO PRESCALERS!!! */
    if ( wide ) {

      counter = GPT_GET_START_COUNTER(Channel + 1);	/* TMR B Read	      */
      prescaler = GPT_GET_START_COUNTER(Channel);	/* TMR A Read	      */
      rv = ((Gpt_ValueType)counter << GPT_HW_TMR_JOIN_WIDE_VALUE_S) +
	    (Gpt_ValueType)prescaler;

    }
    else {

      rv = (Gpt_ValueType)GPT_GET_START_COUNTER(Channel);

    }

  }
  else {	/* Splitted Channel */

    prescaler = GPT_GET_START_PRESCALER(Channel);
    counter = GPT_GET_START_COUNTER(Channel);

    if ( prescaler == GPT_HW_TMR_EMPTY_VALUE ) {

      /* NO PRESCALER */
      rv = (Gpt_ValueType)counter;

    }
    else if ( wide ) {

      /* Wide Channel With Prescaler */
      rv = ((Gpt_ValueType)counter << GPT_HW_TMR_WIDE_PRESCALER_IN_S) +
	    (Gpt_ValueType)prescaler;

    }
    else {

      /* Not-Wide Channel With Prescaler */
      rv = ((Gpt_ValueType)counter << GPT_HW_TMR_PRESCALER_IN_S) +
	    (Gpt_ValueType)prescaler;

    }

  }
  
  return rv;

}

/*
 * Gpt_GetTimeElapsed implementation.
 */
Gpt_ValueType Gpt_GetTimeElapsed(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register uint32		channel;

  register Gpt_ValueType	rv;

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Gpt_Global.Init,
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_UNINIT,
    GPT_HW_TMR_EMPTY_VALUE,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ_W_RV(
    ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ),
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_GETTIMEELAPSED_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    GPT_HW_TMR_EMPTY_VALUE,
    flags
  );

  rv = Gpt_GetHWStartTime(Channel) - Gpt_GetHWTimeRemaining(Channel);

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif

#if ( GPT_TIME_REMAINING_API == STD_ON )
/*
 * Gpt_GetTimeRemainig implementation.
 */
Gpt_ValueType Gpt_GetTimeRemaining(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register uint32		channel;

  register Gpt_ValueType	rv;

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Gpt_Global.Init,
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_UNINIT,
    GPT_HW_TMR_EMPTY_VALUE,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ_W_RV(
    ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ),
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_HW_TMR_EMPTY_VALUE,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_GETTIMEREMAINING_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    GPT_HW_TMR_EMPTY_VALUE,
    flags
  );

  rv = Gpt_GetHWTimeRemaining(Channel);

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif

/*
 * Gpt_StartTimer implementation.
 */
void Gpt_StartTimer(
  Gpt_ChannelType	Channel,
  Gpt_ValueType		Value
)
{

  register EE_FREG	flags;
  register uint32	channel;
  register boolean	joined;
  register boolean	wide;

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  /* Heavy Checks Made Once!!! */
  joined = GPT_CH_IS_JOINED(Channel);
  wide = GPT_CH_IS_WIDE(Channel);

  VALIDATE(
    ( 
      (Value > 0) && 
      ( 
	( 
	  joined && wide	/* Joined-Wide Channel: 64 bits	      */
	) || (
	  joined && !wide &&	/* Joined Channel: 32 bits	      */
	  !(Value & GPT_HW_TMR_JOIN_VALUE_MASK)
	) || (
	  !joined && wide &&	/* Splitted-Wide Channel: max 48 bits */
	  !(Value & GPT_HW_TMR_SPLIT_WIDE_VALUE_MASK)
	) || (
	  !joined && !wide &&	/* Splitted Channel: max 24 bits      */
	  !(Value & GPT_HW_TMR_SPLIT_VALUE_MASK)
	)
      )
    ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_PARAM_VALUE
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ(
    ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    flags
  );

  VALIDATE_IRQ(
    ( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    flags
  );

  VALIDATE_IRQ(
    !GPT_TMR_RUNNING(Channel),
    GPT_STARTTIMER_SERVICE_ID,
    GPT_E_BUSY,
    flags
  );

  if ( joined ) {

    /* Joined Channels: NO PRESCALERS!!! */
    if ( wide ) {

      /* Joined-Wide Channel: TMR B Write */
      GPT_SET_COUNTER(
	Channel + 1, ( (uint64)Value >> (uint32)GPT_HW_TMR_JOIN_WIDE_VALUE_S )
      );

    }
    GPT_SET_COUNTER(Channel, Value);

  }
  else if ( wide && (Value & GPT_HW_TMR_WIDE_PRESCALER_OUT_MASK) ) {

    /* Wide Channel With Prescaler */
    GPT_SET_PRESCALER(Channel, ( Value & GPT_HW_TMR_WIDE_PRESCALER_IN_MASK ));
    GPT_SET_COUNTER(Channel, ( Value >> GPT_HW_TMR_WIDE_PRESCALER_IN_S ));

  }
  else if ( !wide && (Value & GPT_HW_TMR_PRESCALER_OUT_MASK) ) {

    /* Not-Wide Channel With Prescaler */
    GPT_SET_PRESCALER(Channel, ( Value & GPT_HW_TMR_PRESCALER_IN_MASK ));
    GPT_SET_COUNTER(Channel, ( Value >> GPT_HW_TMR_PRESCALER_IN_S ));

  }
  else {

    /* Wide or Not-Wide Channel Without Prescaler */
    GPT_SET_PRESCALER(Channel, GPT_HW_TMR_EMPTY_VALUE);
    GPT_SET_COUNTER(Channel, Value);

  }

  /* Time-Out Interrupt Clear*/
  GPT_TMR_TIMEOUT_INT_CLR(Channel);

  /* Start Timer */
  GPT_TMR_START(Channel);

  EE_hal_resumeIRQ(flags);

}

/*
 * Gpt_StopTimer implementation.
 */
void Gpt_StopTimer(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ(
    ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ),
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    flags
  );

  VALIDATE_IRQ(
    ( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_STOPTIMER_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    flags
  );

  /* Stop Timer */
  GPT_TMR_STOP(Channel);

  /* Time-Out Interrupt Clear*/
  GPT_TMR_TIMEOUT_INT_CLR(Channel);

  EE_hal_resumeIRQ(flags);

}

#if ( GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
/*
 * Gpt_EnableNotification implementation.
 */
void Gpt_EnableNotification(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_ENABLENOTIFICATION_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_ENABLENOTIFICATION_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ(
    (
      ( channel <= Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      (
	Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr !=
	NULL_PTR
      )
    ),
    GPT_ENABLENOTIFICATION_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    flags
  );

  /* Gpt Unit Enabled? */
  if ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) )
  {

    /* Enable Time-out Interrupt */
    GPT_TMR_TIMEOUT_INT_EN(Channel);

  }

  /* Turn-on Gpt Unit Notifications*/
  Gpt_Global.Notifications |= GPT_CH_2_UNIT_NOTIF_MASK(Channel);

  EE_hal_resumeIRQ(flags);

}

/*
 * Gpt_DisableNotification implementation.
 */
void Gpt_DisableNotification(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_DISABLENOTIFICATIONS_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_DISABLENOTIFICATIONS_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( 
	Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr !=
	NULL_PTR
      )
    ),
    GPT_DISABLENOTIFICATION_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    flags
  );

  /* Gpt Unit Enabled? */
  if ( (Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel)) )
  {

    /* Disable Time-out Interrupt */
    GPT_TMR_TIMEOUT_INT_DIS(Channel);

  }

  /* Turn-off Gpt Unit Notifications */
  Gpt_Global.Notifications &= ~GPT_CH_2_UNIT_NOTIF_MASK(Channel);

  EE_hal_resumeIRQ(flags);

}
#endif

#if ( \
  ( GPT_REPORT_WAKEUP_SOURCE == STD_ON ) && \
  ( GPT_WAKEUP_FUNCTIONALITY_API == STD_ON ) \
)
/*
 * Gpt_SetMode implementation.
 */
void Gpt_SetMode(
  Gpt_ModeType	Mode
)
{

  register EE_FREG	flags;

  VALIDATE(
    ( ( Mode == GPT_MODE_NORMAL ) || ( Mode == GPT_MODE_SLEEP ) ),
    GPT_SETMODE_SERVICE_ID,
    GPT_E_PARAM_MODE
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE(
    Gpt_Global.Init,
    GPT_SETMODE_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  /* NOT IMPLEMENTED. */

  EE_hal_resumeIRQ(flags);

}

/*
 * Gpt_DisableWakeup implementation.
 */
void Gpt_DisableWakeup(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_DISABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_DISABLEWAKEUP_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < ConfigPtr->GptNumberOfGptChannels ) &&
      ( ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ(
    (
      ( channel < ConfigPtr->GptNumberOfGptChannels ) &&
      ConfigPtr->GptChannels[channel].GptEnableWakeup
    ),
    GPT_DISABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    flags
  );

  /* NOT IMPLEMENTED. */

  EE_hal_resumeIRQ(flags);

}

/*
 * Gpt_EnableWakeup implementation.
 */
void Gpt_EnableWakeup(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE(
    GPT_CH_IS_VALID(Channel),
    GPT_ENABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_ENABLEWAKEUP_SERVICE_ID,
    GPT_E_UNINIT
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      Gpt_Global.ConfigPtr->GptChannels[channel].GptEnableWakeup
    ),
    GPT_ENABLEWAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL
  );

  /* NOT IMPLEMENTED. */

  EE_hal_resumeIRQ(flags);

}

/*
 * Gpt_CheckWakeup implementation.
 */
void Gpt_CheckWakeup(
  EcuM_WakeupSourceType	WakeupSource
)
{

  register EE_FREG	flags;

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    Gpt_Global.Init,
    GPT_CHECKWAKEUP_SERVICE_ID,
    GPT_E_UNINIT,
    flags
  );

  /* NOT IMPLEMENTED. */

  EE_hal_resumeIRQ(flags);

}
#endif

#if ( GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON )
/*
 * Gpt_GoToSleep implementation.
 */
Std_ReturnType Gpt_GoToSleep(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Gpt_Global.Init,
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ_W_RV(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport
    ),
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    ( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_GOTOSLEEP_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Stop Timer. */
  GPT_TMR_STOP(Channel);

  /* Disable Time-out Interrupt */
  GPT_TMR_TIMEOUT_INT_DIS(Channel);

  /* Turn-off Gpt Unit */
  Gpt_Global.Status &= ~GPT_CH_2_UNIT_STAT_MASK(Channel);

  /* Gpt Module Disabled? */
  if (
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(Channel) )
  ) {

    /* Disable Gpt Module in Run-Mode */
    Gpt_DisableChannel(Channel);

  }

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

/*
 * Gpt_Wakeup implementation.
 */
Std_ReturnType Gpt_Wakeup(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG	flags;
  register uint32	channel;

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Gpt_Global.Init,
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ_W_RV(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) ||
      Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport
    ),
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    !( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) ),
    GPT_WAKEUP_SERVICE_ID,
    GPT_E_STATE_TRANSITION,
    E_NOT_OK,
    flags
  );

  /* Gpt Module Disabled? */
  if ( 
    !( Gpt_Global.Status & GPT_CH_2_MOD_STAT_MASK(Channel) )
  ) {

    /* Enables Gpt Module in Run-Mode */
    Gpt_EnableChannel(Channel);

  }

  /* Gpt Notifications Enabled? */
  if ( 
    ( Gpt_Global.Notifications & GPT_CH_2_UNIT_NOTIF_MASK(Channel) )
  ) {

    /* Enable Time-out Interrupt */
    GPT_TMR_TIMEOUT_INT_EN(Channel);

  }

  /* Turn-on Gpt Unit */
  Gpt_Global.Status |= GPT_CH_2_UNIT_STAT_MASK(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

/*
 * Gpt_GetStatus implementation.
 */
Gpt_StatusType Gpt_GetStatus(
  Gpt_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register Gpt_StatusType	rv;
  register uint32		channel;
  register boolean		joined;
  register boolean		wide;

  VALIDATE_W_RV(
    GPT_CH_IS_VALID(Channel),
    GPT_GETSTATUS_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Gpt_Global.Init,
    GPT_GETSTATUS_SERVICE_ID,
    GPT_E_UNINIT,
    GPT_NOT_OK,
    flags
  );

  for (
    channel = 0;
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      ( Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != Channel )
    );
    channel++
  );

  VALIDATE_IRQ_W_RV(
    (
      ( channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) &&
      Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport
    ),
    GPT_GETSTATUS_SERVICE_ID,
    GPT_E_PARAM_CHANNEL,
    GPT_NOT_OK,
    flags
  );

  /* Heavy Checks Made Once!!! */
  joined = GPT_CH_IS_JOINED(Channel);
  wide = GPT_CH_IS_WIDE(Channel);

  if ( 
    !( Gpt_Global.Status & GPT_CH_2_UNIT_STAT_MASK(Channel) )
  ) {

      rv = GPT_CH_SLEEP;

  }
  else if ( GPT_TMR_RUNNING(Channel) ) {

    rv = GPT_CH_RUNNING;

  }
  else if ( GPT_TMR_TIMEOUT(Channel) ) {

    rv = GPT_CH_EXPIRED;

  }
  else if ( GPT_GET_START_COUNTER(Channel) != GPT_HW_TMR_EMPTY_VALUE ) {
  
    rv = GPT_CH_STOPPED;
  }
  else if ( !joined || !wide ) {

    rv = GPT_OPERATIONAL;

  }
  else if ( (GPT_GET_START_COUNTER(Channel + 1) == GPT_HW_TMR_EMPTY_VALUE) ) {

    rv = GPT_OPERATIONAL;

  }
  else {

    rv = GPT_CH_STOPPED;

  }

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif
