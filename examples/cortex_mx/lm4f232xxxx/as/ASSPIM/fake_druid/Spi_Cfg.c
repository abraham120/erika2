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
 * fake-druid AUTOSAR SPI Handler/Driver Configuration Source File.
 *
 * Configured for (MCU): TI Stellaris LM4F232H5QD
 *
 * Author: 2012, Giuseppe Serano
 */

/*
 * SPI274:	Spi_Cfg.c shall include Spi.h.
 */
#include "Spi.h"

/* 
 * SPI069:	Spi.c shall check if the correct version of Spi.h is included.
 * 		This shall be done by a pre-processor check.
 *
 * SPI369:	The SPI module shall avoid the integration of incompatible files
 * 		by the following pre-processor checks:
 * 		for included (external) header files,
 * 		- <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * 		- <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * 		shall be verified.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	SPI_AR_RELEASE_MAJOR_VERSION	4
#define	SPI_AR_RELEASE_MINOR_VERSION	0

#if !defined( SPI_AR_MAJOR_VERSION ) || \
    ( SPI_AR_MAJOR_VERSION != SPI_AR_RELEASE_MAJOR_VERSION )
#error	Spi_Cfg: version mismatch.
#endif

/*
 * Spi Channels Configurations.
 */

/*
 * TEST Chennels Configuration.
 */
const Spi_ChannelConfigType		Spi_TestChannelConfig[] = {
  {
    SPI_TEST_CHANNEL_0,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_TEST_CHANNEL_0_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_TEST_CHANNEL_0_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_TEST_CHANNEL_0_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  {
    SPI_TEST_CHANNEL_0_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_TEST_CHANNEL_0_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_TEST_CHANNEL_0_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_TEST_CHANNEL_0_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
};

/*
 * Spi External Devices Configurations.
 */

/*
 * TEST External Devices Configuration.
 */
const Spi_ExternalDeviceConfigType	Spi_TestExternalDeviceConfig[] = {
  {
    5E6,				/* SpiBaudrate			      */
    SPI_TEST_CS_0,			/* SpiCsIdentifier		      */
    /* NOTE: TI Stellaris SSI Modules HAVE SPI_LOW Chip-Select Polarity. */
#if	0
    SPI_LOW,				/* SpiCsPolarity		      */
#endif
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    /* NOTE: TI Stellaris SSI Modules MUST handle Chip-Select. */
#if	0
    FALSE,				/* SpiEnableCs			      */
#endif
    SPI_HW_UNIT_3,			/* SpiHwUnit			      */
    SPI_LOW,				/* SpiShiftClockIdleLevel	      */
  /* NOTE: TI Stellaris SSI Modules have FIXED TIMINGS!!! */
#if	0
    0x00000000U,			/* SpiTimeClk2Cs		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_ASYNCHRONOUS,			/* SpiHwUnitSynchronous.	      */
#endif
					/* SpiHwUnitMode:		      */
    SPI_HW_UNIT_MASTER	|		/* - Master			      */
    SPI_HW_UNIT_LOOPBACK,		/* - Loop-back			      */
    TRUE,				/* SpiSysClock.			      */
    DMA_CHANNEL_SPI_3_RX,		/* SpiDmaRxChannel.		      */
    DMA_CHANNEL_SPI_3_TX,		/* SpiDmaTxChannel.		      */
  },
#if	( SPI_LEVEL_DELIVERED == 2 )
  {
    5E6,				/* SpiBaudrate			      */
    SPI_TEST_CS_1,			/* SpiCsIdentifier		      */
    /* NOTE: TI Stellaris SSI Modules HAVE SPI_LOW Chip-Select Polarity. */
#if	0
    SPI_LOW,				/* SpiCsPolarity		      */
#endif
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    /* NOTE: TI Stellaris SSI Modules MUST handle Chip-Select. */
#if	0
    FALSE,				/* SpiEnableCs			      */
#endif
    SPI_HW_UNIT_2,			/* SpiHwUnit			      */
    SPI_LOW,				/* SpiShiftClockIdleLevel	      */
  /* NOTE: TI Stellaris SSI Modules have FIXED TIMINGS!!! */
#if	0
    0x00000000U,			/* SpiTimeClk2Cs		      */
#endif
    SPI_SYNCHRONOUS,			/* SpiHwUnitSynchronous.	      */
					/* SpiHwUnitMode:		      */
    SPI_HW_UNIT_MASTER	|		/* - Master			      */
    SPI_HW_UNIT_LOOPBACK,		/* - Loop-back			      */
    TRUE,				/* SpiSysClock.			      */
    DMA_CHANNEL_SPI_2_RX,		/* SpiDmaRxChannel.		      */
    DMA_CHANNEL_SPI_2_TX,		/* SpiDmaTxChannel.		      */
  },
#endif
};

/*
 * Spi Jobs Configuration.
 */

/*
 * TEST Job 0 Channels List Configuration.
 */
const Spi_ChannelType			Spi_TestJob0ChannelList[] = {
  SPI_TEST_CHANNEL_0,			/* - Test Channel 0.		      */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
const Spi_ChannelType			Spi_TestJob0ChannelEBList[] = {
  SPI_TEST_CHANNEL_0_EB,		/* - Test Channel 0 (EB).	      */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/*
 * TEST Jobs Configuration.
 */
const Spi_JobConfigType			Spi_TestJobConfig[] = {
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_TEST_JOB_0_END_NOTIFICATION__
    &Spi_TestJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_TEST_JOB_0,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_TEST_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_TEST_CS_0,			/* SpiDeviceAssignment.		      */
    &Spi_TestJob0ChannelList[0]		/* SpiChannelList.		      */
  },
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_TEST_JOB_0_END_NOTIFICATION__
    &Spi_TestJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_TEST_JOB_0_EB,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_TEST_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_TEST_CS_0,			/* SpiDeviceAssignment.		      */
    &Spi_TestJob0ChannelEBList[0]	/* SpiChannelList.		      */
  },
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#if	( SPI_LEVEL_DELIVERED == 2 )
  {
#ifdef	__AS_CFG_SPI_TEST_JOB_0_END_NOTIFICATION__
    &Spi_TestJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_TEST_JOB_0_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_TEST_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_TEST_CS_1,			/* SpiDeviceAssignment.		      */
    &Spi_TestJob0ChannelList[0]		/* SpiChannelList.		      */
  },
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) && ( SPI_LEVEL_DELIVERED == 2 ) )
  {
#ifdef	__AS_CFG_SPI_TEST_JOB_0_END_NOTIFICATION__
    &Spi_TestJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_TEST_JOB_0_EB_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_TEST_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_TEST_CS_1,			/* SpiDeviceAssignment.		      */
    &Spi_TestJob0ChannelEBList[0]	/* SpiChannelList.		      */
  },
#endif	/*
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) &&
	 * ( SPI_LEVEL_DELIVERED == 2 )
	 */
};

/*
 * Spi Sequences Configuration.
 */

/*
 * TEST Sequence Job Assignment Configuration.
 */
const Spi_JobType			Spi_TestSeq0JobAssignment[] = {
  SPI_TEST_JOB_0,			/* - Test Job 0.		      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
const Spi_JobType			Spi_TestSeq0EBJobAssignment[] = {
  SPI_TEST_JOB_0_EB,			/* - Test Job 0. (EB)		      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};
#endif

#if	( SPI_LEVEL_DELIVERED == 2 )
const Spi_JobType			Spi_TestSeq0SYNCJobAssignment[] = {
  SPI_TEST_JOB_0_SYNC,			/* - Test Job 0. (Synch)	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};
#endif

#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) && ( SPI_LEVEL_DELIVERED == 2 ) )
const Spi_JobType			Spi_TestSeq0EBSYNCJobAssignment[] = {
  SPI_TEST_JOB_0_EB_SYNC,		/* - Test Job 0. (EB + Sync)	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};
#endif

/*
 * TEST Sequences Configuration.
 */
const Spi_SequenceConfigType		Spi_TestSequenceConfig[] = {
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__
    &Spi_TestSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_TEST_SEQ_0,			/* SpiSequenceId.		      */
    &Spi_TestSeq0JobAssignment[0]	/* SpiJobAssignment.		      */
  },
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__
    &Spi_TestSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_TEST_SEQ_0_EB,			/* SpiSequenceId.		      */
    &Spi_TestSeq0EBJobAssignment[0]	/* SpiJobAssignment.		      */
  },
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#if	( SPI_LEVEL_DELIVERED == 2 )
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__
    &Spi_TestSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
    SPI_TEST_SEQ_0_SYNC,		/* SpiSequenceId.		      */
    &Spi_TestSeq0SYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) && ( SPI_LEVEL_DELIVERED == 2 ) )
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__
    &Spi_TestSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_TEST_SEQ_0_END_NOTIFICATION__ */
    SPI_TEST_SEQ_0_EB_SYNC,		/* SpiSequenceId.		      */
    &Spi_TestSeq0EBSYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) &&
	 * ( SPI_LEVEL_DELIVERED == 2 )
	 */
};

/*
 * This container is the base of a multiple configuration set.
 */
const Spi_ConfigType			Spi_Config[] = {
  {
    SPI_TEST_CHANNELS_NUMBER,		/* SpiMaxChannel.		      */
    SPI_TEST_EXTERNAL_DEVICES_NUMBER,	/* SpiMaxExternalDevice.	      */
    SPI_TEST_JOBS_NUMBER,		/* SpiMaxJob.			      */
    SPI_TEST_SEQUENCES_NUMBER,		/* SpiMaxSequence.		      */
    &Spi_TestChannelConfig[0],		/* SpiChannel.			      */
    &Spi_TestExternalDeviceConfig[0],	/* SpiExternalDevice.		      */
    &Spi_TestJobConfig[0],		/* SpiJob.			      */
    &Spi_TestSequenceConfig[0]		/* SpiSequence.			      */
  },
};
