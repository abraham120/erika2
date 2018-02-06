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
 * Dma.c Module source file.
 *
 * AUTOSAR-"like" DMA Driver Source File.
 *
 * Author:  2012,  Giuseppe Serano
 */

/*
 * The DMA module shall adhere to the following include file structure:
 * - Dma.c shall include Dma.h, MemMap.h, Det.h and SchM_Dma.h.
 *
 * Comment: Dma.c has implicit access to the Dma_Cfg.h through the Dma.h file.
 */
#include "Dma.h"

/* 
 * Dma.c shall check if the correct version of Dma.h is included.
 * This shall be done by a pre-processor check.
 *
 * The DMA module shall avoid the integration of incompatible files by the
 * following pre-processor checks:
 * 	for included (external) header files,
 * 	- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 	- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 	shall be verified.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	DMA_AR_RELEASE_MAJOR_VERSION	4
#define	DMA_AR_RELEASE_MINOR_VERSION	0

#if !defined( DMA_AR_MAJOR_VERSION ) || \
    ( DMA_AR_MAJOR_VERSION != DMA_AR_RELEASE_MAJOR_VERSION )
#error	Dma: version mismatch.
#endif


#include "Dma_Internal.h"

#include "ee.h"

/* Development error macros. */
#if ( DMA_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(__AS_DEM__)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(DMA_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(DMA_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(DMA_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(DMA_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* DMA_DEV_ERROR_DETECT */

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

#endif	/* !DMA_DEV_ERROR_DETECT */

/*
 * Global config
 */
Dma_GlobalType Dma_Global =
{
  FALSE,		/* Init		*/
  NULL_PTR,		/* ConfigPtr		*/
};

/*
 * The control table used by the uDMA controller.
 *
 * NOTE:	This table must be aligned to a 1024 byte boundary.
 */
Dma_EntryType	DmaControlTable[DMA_CHANNELS_MAX_NUMBER << 1]
		__attribute__ ((aligned(1024)));

static void Dma_ControlTableClear(
  void
)
{
  register uint32	idx;

  for ( idx = 0; idx < DMA_CHANNELS_MAX_NUMBER; idx++ ) {

    /* Reset Primary Control Table Structure Entry. */
    DmaControlTable[idx].DmaSrcEndAddress = 0x00U;
    DmaControlTable[idx].DmaDstEndAddress = 0x00U;
    DmaControlTable[idx].DmaControl = 0x00U;
    DmaControlTable[idx].DmaUnused = 0x00U;

    DmaControlTable[idx + DMA_CHANNELS_MAX_NUMBER] = DmaControlTable[idx];

  }

}

/*
 * Dma_Init implementation. (Non Re-entrant)
 */
void Dma_Init(
  const Dma_ConfigType *	ConfigPtr
)
{

  register EE_FREG		flags;
  register Dma_ChannelType	chidx;

  VALIDATE( ( ConfigPtr != NULL ), DMA_INIT_SERVICE_ID, DMA_E_PARAM_POINTER );

  VALIDATE( ( Hw_CheckCore() == E_OK ), DMA_INIT_SERVICE_ID, DMA_E_UNINIT );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ(
    !Dma_Global.Init,
    DMA_INIT_SERVICE_ID,
    DMA_E_ALREADY_INITIALIZED,
    flags
  );

  Dma_Global.Init = TRUE;
  Dma_Global.ConfigPtr = ConfigPtr;

  /* Enable the µDMA clock */
  SYSCTL_RCGCDMA_R |= SYSCTL_RCGCDMA_R0;

  /* Enable the µDMA controller */
  UDMA_CFG_R |= UDMA_CFG_MASTEN;

  /* Control Table Clear. */
  Dma_ControlTableClear();

  /* Control Table Base Address Setup. */
  UDMA_CTLBASE_R = ( (uint32)DmaControlTable & UDMA_CTLBASE_ADDR_M );

  for ( chidx = 0; chidx < Dma_Global.ConfigPtr->DmaMaxChannel; chidx++ ) {

    /* Channel Assignment Set-up. */
    DMA_CHANNEL_MAP_SET(
      Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId,
      Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelAssignment
    );

  }

  EE_hal_resumeIRQ(flags);

}

#if	( DMA_DE_INIT_API == STD_ON )
/*
 * Dma_DeInit implementation. (Non Re-entrant)
 */
Std_ReturnType Dma_DeInit(
  void
)
{

  register EE_FREG		flags;
  register Std_ReturnType	rv;
  register uint32		state;


  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_DE_INIT_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  rv = E_NOT_OK;

  /* µDMA Status retrieval. */
  state = ( UDMA_STAT_R & UDMA_STAT_STATE_M );

  /* DMA Driver Idle Check */
  if (
    ( state == UDMA_STAT_STATE_IDLE ) ||
    ( state == UDMA_STAT_STATE_DONE )
  ) {

    /* Disable the µDMA controller */
    UDMA_CFG_R &= ~UDMA_CFG_MASTEN;

    SYSCTL_SRDMA_R |= SYSCTL_SRDMA_R0;			/* Start µDMA Reset   */
    SYSCTL_SRDMA_R &= ~SYSCTL_SRDMA_R0;			/* Stop  µDMA Reset   */
    while ( !( SYSCTL_PRDMA_R & SYSCTL_SRDMA_R0 ) );	/* Wait  µDMA Reset   */

    /* Disable the µDMA clock */
    SYSCTL_RCGCDMA_R &= ~SYSCTL_RCGCDMA_R0;

    /* Control Table Clear. */
    Dma_ControlTableClear();

    Dma_Global.ConfigPtr = NULL_PTR;
    Dma_Global.Init = FALSE;

    rv = E_OK;

  }

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif	/* ( DMA_DE_INIT_API == STD_ON ) */

/*
 * Dma_EnableChannel implementation. (Reentrant)
 */
Std_ReturnType Dma_EnableChannel(
  Dma_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register Dma_ChannelType	chidx;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_ENABLE_CHANNEL_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_ENABLE_CHANNEL_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    (
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      !DMA_CHANNEL_STAT(Channel)
    ),
    DMA_ENABLE_CHANNEL_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  DmaControlTable[Channel].DmaUnused = DmaControlTable[Channel].DmaControl;

  DMA_INT_CLR(Channel);

  DMA_ERR_CLR();

  DMA_CHANNEL_ENABLE(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

#if	( DMA_DISABLE_CHANNEL_API == STD_ON )
/*
 * Dma_DisableChannel implementation. (Reentrant)
 */
Std_ReturnType Dma_DisableChannel(
  Dma_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register Dma_ChannelType	chidx;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_DISABLE_CHANNEL_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_DISABLE_CHANNEL_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    (
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      DMA_CHANNEL_STAT(Channel)
    ),
    DMA_DISABLE_CHANNEL_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  DMA_CHANNEL_DISABLE(Channel);

  DmaControlTable[Channel].DmaUnused = DMA_CH_CTRL_CANC;

  EE_hal_resumeIRQ(flags);

  return E_OK;

}
#endif	/* ( DMA_DISABLE_CHANNEL_API == STD_ON ) */

#if	( DMA_STATUS_API == STD_ON )
/*
 * Dma_GetStatus implementation. (Reentrant)
 */
Dma_StatusType Dma_GetStatus(
  void
)
{

  register EE_FREG		flags;
  register Dma_StatusType	rv;
  register uint32		state;

  rv = DMA_UNINIT;

  flags = EE_hal_suspendIRQ();

  if ( Dma_Global.Init ) {

    /* µDMA Status Retrieval. */
    state = ( UDMA_STAT_R & UDMA_STAT_STATE_M );

    /* µDMA Status Check */
    if (
      ( state == UDMA_STAT_STATE_IDLE ) ||
      ( state == UDMA_STAT_STATE_DONE )
    ) {

      rv = DMA_IDLE;

    }
    else {

      rv = DMA_BUSY;

    }

  }

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif	/* ( DMA_STATUS_API == STD_ON ) */

#if	( DMA_CHANNEL_RESULT_API == STD_ON )
/*
 * Dma_GetChannelResult implementation. (Reentrant)
 */
Dma_ChannelResultType Dma_GetChannelResult(
  Dma_ChannelType	Channel
)
{

  register EE_FREG			flags;
  register Dma_ChannelResultType	rv;
  register Dma_ChannelType		chidx;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_GET_CHANNEL_RESULT_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    DMA_CHANNEL_FAILED
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_GET_CHANNEL_RESULT_SERVICE_ID,
    DMA_E_UNINIT,
    DMA_CHANNEL_FAILED,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ),
    DMA_GET_CHANNEL_RESULT_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    DMA_CHANNEL_FAILED,
    flags
  );

  rv = DMA_CHANNEL_OK;

  /* Channel Enabled. */
  if ( DMA_CHANNEL_STAT(Channel) ) {

    if ( 
      DmaControlTable[Channel].DmaUnused != DmaControlTable[Channel].DmaControl
    ) {

      rv = DMA_CHANNEL_PENDING;

    }

  }

  /* Channel Disabled. */
  else {

    /* Channel Disabled by User Check. */
    if ( DmaControlTable[Channel].DmaUnused == DMA_CH_CTRL_CANC ) {

      rv = DMA_CHANNEL_CANCELED;

    }
    else if ( 
      DmaControlTable[Channel].DmaControl & ( 
	UDMA_CHCTL_XFERSIZE_M  | UDMA_CHCTL_XFERMODE_M
      )
    ) {

      rv = DMA_CHANNEL_FAILED;

    }

  }

  DMA_INT_CLR(Channel);

  DMA_ERR_CLR();

  EE_hal_resumeIRQ(flags);

  return rv;

}
#endif	/* ( DMA_CHANNEL_RESULT_API == STD_ON ) */

#if	( DMA_TRANSFER_REQUEST_API == STD_ON )
/*
 * Dma_TransferRequest implementation. (Reentrant)
 */
Std_ReturnType Dma_TransferRequest(
  Dma_ChannelType	Channel
)
{

  register EE_FREG		flags;
  register Dma_ChannelType	chidx;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_TRANSFER_REQUEST_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_TRANSFER_REQUEST_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ),
    DMA_TRANSFER_REQUEST_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    DMA_CHANNEL_STAT(Channel),
    DMA_TRANSFER_REQUEST_SERVICE_ID,
    DMA_E_CHANNEL_STATE,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    (
      DmaControlTable[Channel].DmaUnused == DmaControlTable[Channel].DmaControl
    ),
    DMA_TRANSFER_REQUEST_SERVICE_ID,
    DMA_E_CHANNEL_PENDING,
    E_NOT_OK,
    flags
  );

  DMA_CHANNEL_REQUEST(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}
#endif	/* ( DMA_TRANSFER_REQUEST_API == STD_ON ) */

/*
 * Channel Internal Transfer Size Retrieval.
 * param	TransferSize	Number of Elements to transfer.
 * param	Control		DMA Channel Control Word.
 * return	DMA Channel Internal Transfer Size
 *
 */
static uint32 Dma_GetXferSize(
  Dma_NumberOfElementsType	TransferSize,
  uint32			Control
)
{

  register uint32	bytesize;
  register uint32	size;

  /* DMA Channel Transfer Data Size in Control
   *
   * NOTE:	UDMA_CHCTL_SRCSIZE must be same of UDMA_CHCTL_DSTSIZE!!!
   */
  Control = ( Control & UDMA_CHCTL_SRCSIZE_M ) >> UDMA_CHCTL_SRCSIZE_S;

  /* Transfer Size in bytes */
  bytesize = (uint32)TransferSize << ( sizeof(Dma_DataType) - 1 );

  /* DMA Channel Internal Transfer Size*/
  size = bytesize >> Control;

  /* DMA Channel Internal Transfer Size Check */
  if ( bytesize > ( size << Control ) ) {

    size = DMA_MAX_TRANSFER_SIZE + 1;

  }

  /* DMA Channel Internal Transfer Size minus 1 */
  return size - 1;

}

/*
 * Channel Source End Address Retrieval.
 * param	AddrPtr	Source Address Pointer.
 * param	Control	DMA Channel Control Word.
 * param	Size	DMA Channel Internal Transfer Size.
 * return	Channel Source End Address.
 *
 */
static uint32 Dma_GetSrcEndAddr(
  const Dma_DataType *	AddrPtr,
  uint32		Control,
  uint32		Size
)
{

  register uint32	addr;

  /* DMA Channel Source Increment in Control. */
  Control = Control & UDMA_CHCTL_SRCINC_M;

  addr = (uint32)AddrPtr;

  if ( Control != UDMA_CHCTL_SRCINC_NONE ) {

    addr += ( Size << ( Control >> UDMA_CHCTL_SRCINC_S ) );

  }

  return addr;

}

/*
 * Channel Destination End Address Retrieval.
 * param	AddrPtr	Destination Address Pointer.
 * param	Control	DMA Channel Control Word.
 * param	Size	DMA Channel Internal Transfer Size.
 * return	Channel Source End Address.
 *
 */
static uint32 Dma_GetDstEndAddr(
  const Dma_DataType *	AddrPtr,
  uint32		Control,
  uint32		Size
)
{

  register uint32	addr;

  /* DMA Channel Destination Increment in Control. */
  Control = Control & UDMA_CHCTL_DSTINC_M;

  addr = (uint32)AddrPtr;

  if ( Control != UDMA_CHCTL_DSTINC_NONE ) {

    addr += ( Size << ( Control >> UDMA_CHCTL_DSTINC_S ) );

  }

  return addr;

}

/*
 * Channel Attributes Setup.
 * param	Channel	DMA Channel to be addressed.
 * param	Control	DMA Channel Control Word.
 * return	DMA Channel "purged" Control Word.
 */
static uint32 Dma_SetChannelAttributes(
  Dma_ChannelType	Channel,
  uint32		Control
)
{

  /* Channel Priority Set-up. */
  if ( Control & DMA_CHANNEL_PRIO_HIGH ) {

    DMA_CHANNEL_PRIO_SET(Channel);

  }
  else {

    DMA_CHANNEL_PRIO_CLR(Channel);

  }

  /* Channel Burst Only Set-up. */
  if ( Control & DMA_CHANNEL_BURST_ONLY ) {

    DMA_CHANNEL_BURST_ONLY_SET(Channel);

  }
  else {

    DMA_CHANNEL_BURST_ONLY_CLR(Channel);

  }

  /* Channel Peripher or Software Set-up. */
  if ( Control & DMA_CHANNEL_SOFTWARE ) {

    DMA_CHANNEL_SOFTWARE_SET(Channel);

  }
  else {

    DMA_CHANNEL_SOFTWARE_CLR(Channel);

  }

  Control &= ~( 
    DMA_CHANNEL_PRIO_HIGH | DMA_CHANNEL_BURST_ONLY | DMA_CHANNEL_SOFTWARE
  );

  return Control;

}

/*
 * Dma_TransferSetup implementation. (Reentrant)
 */
Std_ReturnType Dma_TransferSetup(
  Dma_ChannelType		Channel,
  const Dma_DataType *		SrcAddrPtr,
  const Dma_DataType *		DstAddrPtr,
  Dma_NumberOfElementsType	TransferSize
)
{

  register EE_FREG				flags;
  register const Dma_ChannelConfigType *	chcfgptr;
  register uint32				chidx;
  register uint32				chctrl;
  register uint32				chsz;
  register uint32				chdstaddr;
  register uint32				chsrcaddr;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    SrcAddrPtr && DstAddrPtr,
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_POINTER,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    TransferSize,
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_SIZE,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ),
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  VALIDATE_IRQ_W_RV(
    !DMA_CHANNEL_STAT(Channel),
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_CHANNEL_STATE,
    E_NOT_OK,
    flags
  );

  chcfgptr = &Dma_Global.ConfigPtr->DmaChannel[chidx];

  EE_hal_resumeIRQ(flags);

  /*
   * DMA Channel Control Retrieval.
   */
  chctrl = chcfgptr->DmaChannelControl;

  /*
   * DMA Channel Transfer Mode in chidx.
   */
  chidx = chctrl & UDMA_CHCTL_XFERMODE_M;

  VALIDATE_W_RV(
    (
      ( chidx == UDMA_CHCTL_XFERMODE_STOP ) ||
      ( chidx == UDMA_CHCTL_XFERMODE_BASIC ) ||
      ( chidx == UDMA_CHCTL_XFERMODE_AUTO )
    ),
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  /*
   * DMA Channel Internal Transfer Size in chsz.
   */
  chsz = Dma_GetXferSize(TransferSize, chctrl);

  VALIDATE_W_RV(
    ( chsz < DMA_MAX_TRANSFER_SIZE ),
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_SIZE,
    E_NOT_OK
  );

  /*
   * DMA Channel Internal Transfer Size Setup.
   */
  chctrl &= ~UDMA_CHCTL_XFERSIZE_M;
  chctrl |= ( chsz << UDMA_CHCTL_XFERSIZE_S );

  chdstaddr = Dma_GetDstEndAddr(DstAddrPtr, chctrl, chsz);

  VALIDATE_W_RV(
    (
      ( (uint32)DstAddrPtr >= chcfgptr->DmaDstAddrLow ) &&
      ( chdstaddr <= chcfgptr->DmaDstAddrHigh )
    ),
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_ADDRESS,
    E_NOT_OK
  );

  chsrcaddr = Dma_GetSrcEndAddr(SrcAddrPtr, chctrl, chsz);

  VALIDATE_W_RV(
    (
      ( (uint32)SrcAddrPtr >= chcfgptr->DmaSrcAddrLow ) &&
      ( chsrcaddr <= chcfgptr->DmaSrcAddrHigh )
    ),
    DMA_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_ADDRESS,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  chctrl = Dma_SetChannelAttributes(Channel, chctrl);

  /*
   * DMA Channel Destination Address Setup.
   */
  DmaControlTable[Channel].DmaDstEndAddress = chdstaddr;

  /*
   * DMA Channel Source Address Setup.
   */
  DmaControlTable[Channel].DmaSrcEndAddress = chsrcaddr;

  /*
   * DMA Channel Control Setup.
   */
  DmaControlTable[Channel].DmaControl = chctrl;
  DmaControlTable[Channel].DmaUnused = chctrl;

  DMA_CHANNEL_PRIALT_CLR(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

#if	( DMA_PING_PONG_API == STD_ON )
/*
 * Dma_PingPongTransferSetup Implementation. (Reentrant)
 */
Std_ReturnType Dma_PingPongTransferSetup(
  Dma_ChannelType		Channel,
  const Dma_DataType *		PingSrcAddrPtr,
  const Dma_DataType *		PingDstAddrPtr,
  Dma_NumberOfElementsType	PingTransferSize,
  const Dma_DataType *		PongSrcAddrPtr,
  const Dma_DataType *		PongDstAddrPtr,
  Dma_NumberOfElementsType	PongTransferSize
)
{

  register EE_FREG				flags;
  register const Dma_ChannelConfigType *	chcfgptr;
  register uint32				chidx;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_PING_PONG_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( PingSrcAddrPtr && PingDstAddrPtr && PongSrcAddrPtr && PongDstAddrPtr ),
    DMA_PING_PONG_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_POINTER,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( PingTransferSize && PongTransferSize ),
    DMA_PING_PONG_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_SIZE,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_PING_PONG_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ),
    DMA_PING_PONG_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  chcfgptr = &Dma_Global.ConfigPtr->DmaChannel[chidx];

  EE_hal_resumeIRQ(flags);

  /* NOT YET IMPLEMENTED */

  return E_NOT_OK;
}

/*
 * Dma_PingPongTransferUpdate Implementation. (Reentrant)
 */
Std_ReturnType Dma_PingPongTransferUpdate(
  Dma_ChannelType		Channel,
  const Dma_DataType *		SrcAddrPtr,
  const Dma_DataType *		DstAddrPtr,
  Dma_NumberOfElementsType	TransferSize
)
{

  register EE_FREG				flags;
  register const Dma_ChannelConfigType *	chcfgptr;
  register uint32				chidx;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_PING_PONG_TRANSFER_UPDATE_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( SrcAddrPtr && DstAddrPtr ),
    DMA_PING_PONG_TRANSFER_UPDATE_SERVICE_ID,
    DMA_E_PARAM_POINTER,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    TransferSize,
    DMA_PING_PONG_TRANSFER_UPDATE_SERVICE_ID,
    DMA_E_PARAM_SIZE,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_PING_PONG_TRANSFER_UPDATE_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ),
    DMA_PING_PONG_TRANSFER_UPDATE_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  chcfgptr = &Dma_Global.ConfigPtr->DmaChannel[chidx];

  EE_hal_resumeIRQ(flags);

  /* NOT YET IMPLEMENTED */

  return E_NOT_OK;
}

#endif	/* ( DMA_PING_PONG_API == STD_ON ) */


#if	( DMA_SCATTER_GATHER_API == STD_ON )

/*
 * Dma_ScatterGatherEntrySetup implementation. (Reentrant)
 */
Std_ReturnType Dma_ScatterGatherEntrySetup(
  Dma_ChannelType		Channel,
  Dma_EntryType *		EntryPtr,
  const Dma_DataType *		SrcAddrPtr,
  const Dma_DataType *		DstAddrPtr,
  Dma_NumberOfElementsType	TransferSize,
  boolean			LastEntry
)
{

  register EE_FREG				flags;
  register const Dma_ChannelConfigType *	chcfgptr;
  register uint32				chidx;
  register uint32				chctrl;
  register uint32				chsz;
  register uint32				chdstaddr;
  register uint32				chsrcaddr;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( EntryPtr && SrcAddrPtr && DstAddrPtr ),
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_POINTER,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    TransferSize,
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_SIZE,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ),
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  chcfgptr = &Dma_Global.ConfigPtr->DmaChannel[chidx];

  EE_hal_resumeIRQ(flags);

  /*
   * DMA Channel Control Retrieval.
   */
  chctrl = chcfgptr->DmaChannelControl & ~( 
	DMA_CHANNEL_PRIO_HIGH | DMA_CHANNEL_BURST_ONLY | DMA_CHANNEL_SOFTWARE
  );

  /*
   * DMA Channel Transfer Mode in chidx.
   */
  chidx = chctrl & UDMA_CHCTL_XFERMODE_M;

  VALIDATE_W_RV (
    (
      ( chidx == UDMA_CHCTL_XFERMODE_MEM_SG ) ||
      ( chidx == UDMA_CHCTL_XFERMODE_PER_SG )
    ),
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  /*
   * DMA Channel Internal Transfer Size in chsz.
   */
  chsz = Dma_GetXferSize(TransferSize, chctrl);

  VALIDATE_W_RV(
    ( chsz < DMA_MAX_TRANSFER_SIZE ),
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_SIZE,
    E_NOT_OK
  );

  /*
   * DMA Channel Internal Transfer Size Setup.
   */
  chctrl &= ~UDMA_CHCTL_XFERSIZE_M;
  chctrl |= ( chsz << UDMA_CHCTL_XFERSIZE_S );

  chdstaddr = Dma_GetDstEndAddr(DstAddrPtr, chctrl, chsz);

  VALIDATE_W_RV(
    (
      ( (uint32)DstAddrPtr >= chcfgptr->DmaDstAddrLow ) &&
      ( chdstaddr <= chcfgptr->DmaDstAddrHigh )
    ),
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_ADDRESS,
    E_NOT_OK
  );

  chsrcaddr = Dma_GetSrcEndAddr(SrcAddrPtr, chctrl, chsz);

  VALIDATE_W_RV(
    (
      ( (uint32)SrcAddrPtr >= chcfgptr->DmaSrcAddrLow ) &&
      ( chsrcaddr <= chcfgptr->DmaSrcAddrHigh )
    ),
    DMA_SCATTER_GATHER_ENTRY_SETUP_SERVICE_ID,
    DMA_E_PARAM_ADDRESS,
    E_NOT_OK
  );

  if ( LastEntry ) {

    chctrl &= ~UDMA_CHCTL_XFERMODE_M;

    if ( chidx == UDMA_CHCTL_XFERMODE_MEM_SG ) {

      chctrl |= UDMA_CHCTL_XFERMODE_AUTO;

    }
    else {

      chctrl |= UDMA_CHCTL_XFERMODE_BASIC;

    }

  }
  else {

    chctrl |= DMA_CH_SG_ALT_MASK;

  }

  flags = EE_hal_suspendIRQ();

  /*
   * DMA Channel Destination Address Setup.
   */
  EntryPtr->DmaDstEndAddress = chdstaddr;

  /*
   * DMA Channel Source Address Setup.
   */
  EntryPtr->DmaSrcEndAddress = chsrcaddr;

  /*
   * DMA Channel Control Setup.
   */
  EntryPtr->DmaControl = chctrl;
  /* EntryPtr->DmaUnused = chctrl; */

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

/*
 * Dma_ScatterGatherTransferSetup implementation. (Reentrant)
 */
Std_ReturnType Dma_ScatterGatherTransferSetup(
  Dma_ChannelType		Channel,
  const Dma_EntryType *		TablePtr,
  Dma_NumberOfElementsType	TableSize
)
{

  register EE_FREG				flags;
  register const Dma_ChannelConfigType *	chcfgptr;
  register uint32				chidx;
  register uint32				chctrl;

  VALIDATE_W_RV(
    ( Channel < DMA_CHANNELS_MAX_NUMBER ),
    DMA_SCATTER_GATHER_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    TablePtr,
    DMA_SCATTER_GATHER_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_POINTER,
    E_NOT_OK
  );

  VALIDATE_W_RV(
    ( TableSize && ( TableSize <= DMA_MAX_TRANSFER_SIZE ) ),
    DMA_SCATTER_GATHER_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_SIZE,
    E_NOT_OK
  );

  flags = EE_hal_suspendIRQ();

  VALIDATE_IRQ_W_RV(
    Dma_Global.Init,
    DMA_SG_TRANSFERSETUP_SERVICE_ID,
    DMA_E_UNINIT,
    E_NOT_OK,
    flags
  );

  for (
    chidx = 0;
    ( 
      ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ) &&
      ( Dma_Global.ConfigPtr->DmaChannel[chidx].DmaChannelId != Channel )
    );
    chidx++
  ) {
    ;
  }

  VALIDATE_IRQ_W_RV(
    ( chidx < Dma_Global.ConfigPtr->DmaMaxChannel ),
    DMA_SCATTER_GATHER_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK,
    flags
  );

  chcfgptr = &Dma_Global.ConfigPtr->DmaChannel[chidx];

  EE_hal_resumeIRQ(flags);

  /*
   * DMA Channel Control Retrieval.
   */
  chctrl = (
    chcfgptr->DmaChannelControl & ( 
	DMA_CHANNEL_PRIO_HIGH  |
	DMA_CHANNEL_BURST_ONLY |
	DMA_CHANNEL_SOFTWARE   |
	UDMA_CHCTL_XFERMODE_M  |
	UDMA_CHCTL_NXTUSEBURST
    )
  );

  /*
   * DMA Channel Transfer Mode in chidx.
   */
  chidx = chctrl & UDMA_CHCTL_XFERMODE_M;

  VALIDATE_W_RV (
    (
      ( chidx == UDMA_CHCTL_XFERMODE_MEM_SG ) ||
      ( chidx == UDMA_CHCTL_XFERMODE_PER_SG )
    ),
    DMA_SCATTER_GATHER_TRANSFER_SETUP_SERVICE_ID,
    DMA_E_PARAM_CHANNEL,
    E_NOT_OK
  );

  chctrl = Dma_SetChannelAttributes(Channel, chctrl);

  /*
   * DMA Channel Internal Control in chctrl.
   */
  chctrl |= (
    ( ( ( TableSize << DMA_CH_SG_SIZE_S ) - 1 ) << UDMA_CHCTL_XFERSIZE_S ) |
    UDMA_CHCTL_DSTINC_32 | UDMA_CHCTL_DSTSIZE_32 |
    UDMA_CHCTL_SRCINC_32 | UDMA_CHCTL_SRCSIZE_32 |
    UDMA_CHCTL_ARBSIZE_4
  );

  flags = EE_hal_suspendIRQ();

  /*
   * DMA Channel Destination Address Setup.
   */
  DmaControlTable[Channel].DmaDstEndAddress =
  (uint32)&DmaControlTable[Channel + DMA_CHANNELS_MAX_NUMBER].DmaUnused;

  /*
   * DMA Channel Source Address Setup.
   */
  DmaControlTable[Channel].DmaSrcEndAddress =
  (uint32)&TablePtr[TableSize - 1].DmaUnused;

  /*
   * DMA Channel Control Setup.
   */
  DmaControlTable[Channel].DmaControl = chctrl;
  DmaControlTable[Channel].DmaUnused = chctrl;

  DMA_CHANNEL_PRIALT_CLR(Channel);

  EE_hal_resumeIRQ(flags);

  return E_OK;

}

#endif	/* ( DMA_SCATTER_GATHER_API == STD_ON ) */
