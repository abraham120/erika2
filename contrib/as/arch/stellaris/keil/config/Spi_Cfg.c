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

#ifdef	__AS_CFG_SPI_LBM__

/*
 * Loop-back Mode Chennels Configuration.
 */
const Spi_ChannelConfigType		Spi_LBMChannelConfig[] = {
  {
    SPI_LBM_CHANNEL_0,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_0_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_0_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_0_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_1,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_1_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_1_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_1_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_2,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_2_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_2_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_2_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_3,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_3_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_3_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_3_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_4,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_4_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_4_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_4_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_5,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_5_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_5_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_5_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_6,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_6_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_6_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_6_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_7,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_7_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_7_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_7_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_8,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_8_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_8_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_8_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_9,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_9_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_9_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_9_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_10,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_10_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_10_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_10_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_11,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_11_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_11_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_11_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_12,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_12_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_12_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_12_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_13,			/* SpiChannelId.		      */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
    SPI_IB,				/* SpiChannelType.		      */
#endif
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_LBM_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_13_DEFAULT_DATA,	/* SpiDefaultData.		      */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 1 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_13_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)
    SPI_LBM_CHANNEL_13_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
#endif
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  {
    SPI_LBM_CHANNEL_0_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_0_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_0_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_0_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_1_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_1_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_1_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_1_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_2_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_2_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_2_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_2_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_3_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_3_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_3_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_3_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_4_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_4_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_4_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_4_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_5_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_5_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_5_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_5_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_6_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_6_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_6_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_6_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_7_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_7_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_7_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_7_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_8_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_8_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_8_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_8_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_9_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_9_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_9_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_9_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_10_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_10_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_10_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_10_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_11_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_11_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_11_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_11_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_12_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_12_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_12_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_12_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
  {
    SPI_LBM_CHANNEL_13_EB,		/* SpiChannelId.		      */
    SPI_EB,				/* SpiChannelType.		      */
  /* NOTE: 8-bit SPI Channel Data Width. */
#if	0
    SPI_TEST_CHANNELS_DATA_WIDTH,	/* SpiDataWidth.		      */
#endif
    SPI_LBM_CHANNEL_13_DEFAULT_DATA,	/* SpiDefaultData.		      */
    SPI_LBM_CHANNEL_13_EB_MAX_LENGTH,	/* SpiEbMaxLength.		      */
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNC_ASYNC,			/* SpiHwUnitSynchronous.	      */
#endif
    SPI_LBM_CHANNEL_13_IB_N_BUFFERS,	/* SpiIbNBuffers.		      */
    /* NOTE: TI Stellaris SSI Modules tranfer starts MSB only!!! */ 
#if	0
    SPI_MSB,				/* SpiTransferStart.		      */
#endif
  },
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
};

#endif	/* __AS_CFG_SPI_LBM__ */

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
    SPI_LOW,				/* SpiCsPolarity		      */
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    FALSE,				/* SpiEnableCs			      */
    0x00U,				/* SpiCsChannelId		      */
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
    SPI_LOW,				/* SpiCsPolarity		      */
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    FALSE,				/* SpiEnableCs			      */
    0x00U,				/* SpiCsChannelId		      */
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

#ifdef	__AS_CFG_SPI_LBM__
/*
 * Loop-back Mode External Devices Configuration.
 */
const Spi_ExternalDeviceConfigType	Spi_LBMExternalDeviceConfig[] = {
  {
    5E6,				/* SpiBaudrate			      */
    SPI_LBM_CS_0,			/* SpiCsIdentifier		      */
    SPI_LOW,				/* SpiCsPolarity		      */
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    FALSE,				/* SpiEnableCs			      */
    0x00U,				/* SpiCsChannelId		      */
    SPI_HW_UNIT_0,			/* SpiHwUnit			      */
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
    DMA_CHANNEL_SPI_0_RX,		/* SpiDmaRxChannel.		      */
    DMA_CHANNEL_SPI_0_TX,		/* SpiDmaTxChannel.		      */
  },
  {
    5E6,				/* SpiBaudrate			      */
    SPI_LBM_CS_1,			/* SpiCsIdentifier		      */
    SPI_LOW,				/* SpiCsPolarity		      */
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    FALSE,				/* SpiEnableCs			      */
    0x00U,				/* SpiCsChannelId		      */
    SPI_HW_UNIT_1,			/* SpiHwUnit			      */
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
    DMA_CHANNEL_SPI_1_RX,		/* SpiDmaRxChannel.		      */
    DMA_CHANNEL_SPI_1_TX,		/* SpiDmaTxChannel.		      */
  },
  {
    5E6,				/* SpiBaudrate			      */
    SPI_LBM_CS_2,			/* SpiCsIdentifier		      */
    SPI_LOW,				/* SpiCsPolarity		      */
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    FALSE,				/* SpiEnableCs			      */
    0x00U,				/* SpiCsChannelId		      */
    SPI_HW_UNIT_2,			/* SpiHwUnit			      */
    SPI_LOW,				/* SpiShiftClockIdleLevel	      */
  /* NOTE: TI Stellaris SSI Modules have FIXED TIMINGS!!! */
#if	0
    0x00000000U,			/* SpiTimeClk2Cs		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,			/* SpiHwUnitSynchronous.	      */
#endif
					/* SpiHwUnitMode:		      */
    SPI_HW_UNIT_MASTER	|		/* - Master			      */
    SPI_HW_UNIT_LOOPBACK,		/* - Loop-back			      */
    TRUE,				/* SpiSysClock.			      */
    DMA_CHANNEL_SPI_2_RX,		/* SpiDmaRxChannel.		      */
    DMA_CHANNEL_SPI_2_TX,		/* SpiDmaTxChannel.		      */
  },
  {
    5E6,				/* SpiBaudrate			      */
    SPI_LBM_CS_3,			/* SpiCsIdentifier		      */
    SPI_LOW,				/* SpiCsPolarity		      */
    SPI_LEADING,			/* SpiDataShiftEdge		      */
    /* NOTE: TI Stellaris SSI Modules MUST handle Chip-Select. */
    FALSE,				/* SpiEnableCs			      */
    0x00U,				/* SpiCsChannelId		      */
    SPI_HW_UNIT_3,			/* SpiHwUnit			      */
    SPI_LOW,				/* SpiShiftClockIdleLevel	      */
  /* NOTE: TI Stellaris SSI Modules have FIXED TIMINGS!!! */
#if	0
    0x00000000U,			/* SpiTimeClk2Cs		      */
#endif
#if	( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,			/* SpiHwUnitSynchronous.	      */
#endif
					/* SpiHwUnitMode:		      */
    SPI_HW_UNIT_MASTER	|		/* - Master			      */
    SPI_HW_UNIT_LOOPBACK,		/* - Loop-back			      */
    TRUE,				/* SpiSysClock.			      */
    DMA_CHANNEL_SPI_3_RX,		/* SpiDmaRxChannel.		      */
    DMA_CHANNEL_SPI_3_TX,		/* SpiDmaTxChannel.		      */
  },
};
#endif	/* __AS_CFG_SPI_LBM__ */

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

#ifdef	__AS_CFG_SPI_LBM__
/*
 * Loop-back Mode Jobs Channels List Configuration.
 */
const Spi_ChannelType			Spi_LBMJob0ChannelList[] = {
  SPI_LBM_CHANNEL_11,			/* - Loop-back Mode Channel 11.	      */
  SPI_LBM_CHANNEL_12,			/* - Loop-back Mode Channel 12.	      */
  SPI_LBM_CHANNEL_13,			/* - Loop-back Mode Channel 13.	      */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

const Spi_ChannelType			Spi_LBMJob1ChannelList[] = {
  SPI_LBM_CHANNEL_0,			/* - Loop-back Mode Channel 0.	      */
  SPI_LBM_CHANNEL_1,			/* - Loop-back Mode Channel 1.	      */
  SPI_LBM_CHANNEL_2,			/* - Loop-back Mode Channel 2.	      */
  SPI_LBM_CHANNEL_3,			/* - Loop-back Mode Channel 3.	      */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

const Spi_ChannelType			Spi_LBMJob2ChannelList[] = {
  SPI_LBM_CHANNEL_4,			/* - Loop-back Mode Channel 4.	      */
  SPI_LBM_CHANNEL_5,			/* - Loop-back Mode Channel 5.	      */
  SPI_LBM_CHANNEL_6,			/* - Loop-back Mode Channel 6.	      */
  SPI_LBM_CHANNEL_7,			/* - Loop-back Mode Channel 7.	      */
  SPI_LBM_CHANNEL_8,			/* - Loop-back Mode Channel 8.	      */
  SPI_LBM_CHANNEL_9,			/* - Loop-back Mode Channel 9.	      */
  SPI_LBM_CHANNEL_10,			/* - Loop-back Mode Channel 10.	      */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

const Spi_ChannelType			Spi_LBMJob3ChannelList[] = {
  SPI_LBM_CHANNEL_2,			/* - Loop-back Mode Channel 2.	      */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
const Spi_ChannelType			Spi_LBMJob0ChannelEBList[] = {
  SPI_LBM_CHANNEL_11_EB,		/* - Loop-back Mode Channel 11 (EB).  */
  SPI_LBM_CHANNEL_12_EB,		/* - Loop-back Mode Channel 12 (EB).  */
  SPI_LBM_CHANNEL_13_EB,		/* - Loop-back Mode Channel 13 (EB).  */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

const Spi_ChannelType			Spi_LBMJob1ChannelEBList[] = {
  SPI_LBM_CHANNEL_0_EB,			/* - Loop-back Mode Channel 0 (EB).   */
  SPI_LBM_CHANNEL_1_EB,			/* - Loop-back Mode Channel 1 (EB).   */
  SPI_LBM_CHANNEL_2_EB,			/* - Loop-back Mode Channel 2 (EB).   */
  SPI_LBM_CHANNEL_3_EB,			/* - Loop-back Mode Channel 3 (EB).   */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

const Spi_ChannelType			Spi_LBMJob2ChannelEBList[] = {
  SPI_LBM_CHANNEL_4_EB,			/* - Loop-back Mode Channel 4 (EB).   */
  SPI_LBM_CHANNEL_5_EB,			/* - Loop-back Mode Channel 5 (EB).   */
  SPI_LBM_CHANNEL_6_EB,			/* - Loop-back Mode Channel 6 (EB).   */
  SPI_LBM_CHANNEL_7_EB,			/* - Loop-back Mode Channel 7 (EB).   */
  SPI_LBM_CHANNEL_8_EB,			/* - Loop-back Mode Channel 8 (EB).   */
  SPI_LBM_CHANNEL_9_EB,			/* - Loop-back Mode Channel 9 (EB).   */
  SPI_LBM_CHANNEL_10_EB,		/* - Loop-back Mode Channel 10 (EB).  */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};

const Spi_ChannelType			Spi_LBMJob3ChannelEBList[] = {
  SPI_LBM_CHANNEL_2_EB,			/* - Loop-back Mode Channel 2 (EB).   */
  SPI_CHANNEL_END_LIST			/* - End List Marker.		      */
};
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

/*
 * Loop-back Mode Jobs Configuration.
 */
const Spi_JobConfigType			Spi_LBMJobConfig[] = {
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_0_END_NOTIFICATION__
    &Spi_LBMJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_0,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_0,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob0ChannelList[0]		/* SpiChannelList.		      */
  },
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_1_END_NOTIFICATION__
    &Spi_LBMJob1EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_1,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_1_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_1,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob1ChannelList[0]		/* SpiChannelList.		      */
  },
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_2_END_NOTIFICATION__
    &Spi_LBMJob2EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_2,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_2_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_0,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob2ChannelList[0]		/* SpiChannelList.		      */
  },
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_3_END_NOTIFICATION__
    &Spi_LBMJob3EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_3,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_3_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_1,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob3ChannelList[0]		/* SpiChannelList.		      */
  },
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_0_END_NOTIFICATION__
    &Spi_LBMJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_0_EB,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_0,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob0ChannelEBList[0]	/* SpiChannelList.		      */
  },
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_1_END_NOTIFICATION__
    &Spi_LBMJob1EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_1_EB,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_1_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_1,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob1ChannelEBList[0]	/* SpiChannelList.		      */
  },
    {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_2_END_NOTIFICATION__
    &Spi_LBMJob2EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_2_EB,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_2_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_0,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob2ChannelEBList[0]	/* SpiChannelList.		      */
  },
    {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#ifdef	__AS_CFG_SPI_LBM_JOB_3_END_NOTIFICATION__
    &Spi_LBMJob3EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_JOB_3_EB,			/* SpiJobId.			      */
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_3_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_CS_1,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob3ChannelEBList[0]	/* SpiChannelList.		      */
  },
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#if	( SPI_LEVEL_DELIVERED == 2 )
  {
#ifdef	__AS_CFG_SPI_LBM_JOB_0_END_NOTIFICATION__
    &Spi_LBMJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_0_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_2,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob0ChannelList[0]		/* SpiChannelList.		      */
  },
  {
#ifdef	__AS_CFG_SPI_LBM_JOB_1_END_NOTIFICATION__
    &Spi_LBMJob1EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_1_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_1_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_3,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob1ChannelList[0]		/* SpiChannelList.		      */
  },
  {
#ifdef	__AS_CFG_SPI_LBM_JOB_2_END_NOTIFICATION__
    &Spi_LBMJob2EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_2_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_2_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_2,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob2ChannelList[0]		/* SpiChannelList.		      */
  },
  {
#ifdef	__AS_CFG_SPI_LBM_JOB_3_END_NOTIFICATION__
    &Spi_LBMJob3EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_3_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_3_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_3,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob3ChannelList[0]		/* SpiChannelList.		      */
  },
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) && ( SPI_LEVEL_DELIVERED == 2 ) )
  {
#ifdef	__AS_CFG_SPI_LBM_JOB_0_END_NOTIFICATION__
    &Spi_LBMJob0EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_0_EB_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_0_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_2,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob0ChannelEBList[0]	/* SpiChannelList.		      */
  },
  {
#ifdef	__AS_CFG_SPI_LBM_JOB_1_END_NOTIFICATION__
    &Spi_LBMJob1EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_1_EB_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_1_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_3,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob1ChannelEBList[0]	/* SpiChannelList.		      */
  },
  {
#ifdef	__AS_CFG_SPI_LBM_JOB_2_END_NOTIFICATION__
    &Spi_LBMJob2EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_2_EB_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_2_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_2,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob2ChannelEBList[0]	/* SpiChannelList.		      */
  },
    {
#ifdef	__AS_CFG_SPI_LBM_JOB_3_END_NOTIFICATION__
    &Spi_LBMJob3EndNotification,	/* SpiJobEndNotification.	      */
#else
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif
    SPI_LBM_JOB_3_EB_SYNC,		/* SpiJobId.			      */
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_LBM_JOB_3_PRI,			/* SpiJobPriority.		      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    SPI_LBM_CS_3,			/* SpiDeviceAssignment.		      */
    &Spi_LBMJob3ChannelEBList[0]	/* SpiChannelList.		      */
  },
#endif	/*
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) &&
	 * ( SPI_LEVEL_DELIVERED == 2 )
	 */
};

#endif	/* __AS_CFG_SPI_LBM__ */

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

#ifdef	__AS_CFG_SPI_LBM__

/*
 * LBM Sequence Job Assignment Configuration.
 */
const Spi_JobType			Spi_LBMSeq0JobAssignment[] = {
  SPI_LBM_JOB_1,			/* - Loop-back Mode Job 1.	      */
  SPI_LBM_JOB_2,			/* - Loop-back Mode Job 2.	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq1JobAssignment[] = {
  SPI_LBM_JOB_0,			/* - Loop-back Mode Job 0.	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq2JobAssignment[] = {
  SPI_LBM_JOB_1,			/* - Loop-back Mode Job 1.	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq3JobAssignment[] = {
  SPI_LBM_JOB_3,			/* - Loop-back Mode Job 3.	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
const Spi_JobType			Spi_LBMSeq0EBJobAssignment[] = {
  SPI_LBM_JOB_1_EB,			/* - Loop-back Mode Job 1. (EB)	      */
  SPI_LBM_JOB_2_EB,			/* - Loop-back Mode Job 2. (EB)	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq1EBJobAssignment[] = {
  SPI_LBM_JOB_0_EB,			/* - Loop-back Mode Job 0. (EB)	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq2EBJobAssignment[] = {
  SPI_LBM_JOB_1_EB,			/* - Loop-back Mode Job 1. (EB)	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq3EBJobAssignment[] = {
  SPI_LBM_JOB_3_EB,			/* - Loop-back Mode Job 3. (EB)	      */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */

#if	( SPI_LEVEL_DELIVERED == 2 )
const Spi_JobType			Spi_LBMSeq0SYNCJobAssignment[] = {
  SPI_LBM_JOB_1_SYNC,			/* - Loop-back Mode Job 1. (Synch)    */
  SPI_LBM_JOB_2_SYNC,			/* - Loop-back Mode Job 2. (Synch)    */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq1SYNCJobAssignment[] = {
  SPI_LBM_JOB_0_SYNC,			/* - Loop-back Mode Job 0. (Synch)    */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq2SYNCJobAssignment[] = {
  SPI_LBM_JOB_1_SYNC,			/* - Loop-back Mode Job 1. (Synch)    */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq3SYNCJobAssignment[] = {
  SPI_LBM_JOB_3_SYNC,			/* - Loop-back Mode Job 3. (Synch)    */
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */

#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) && ( SPI_LEVEL_DELIVERED == 2 ) )
const Spi_JobType			Spi_LBMSeq0EBSYNCJobAssignment[] = {
  SPI_LBM_JOB_1_EB_SYNC,		/* - Loop-back Mode Job 1. (EB + Sync)*/
  SPI_LBM_JOB_2_EB_SYNC,		/* - Loop-back Mode Job 2. (EB + Sync)*/
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq1EBSYNCJobAssignment[] = {
  SPI_LBM_JOB_0_EB_SYNC,		/* - Loop-back Mode Job 0. (EB + Sync)*/
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq2EBSYNCJobAssignment[] = {
  SPI_LBM_JOB_1_EB_SYNC,		/* - Loop-back Mode Job 1. (EB + Sync)*/
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};

const Spi_JobType			Spi_LBMSeq3EBSYNCJobAssignment[] = {
  SPI_LBM_JOB_3_EB_SYNC,		/* - Loop-back Mode Job 3. (EB + Sync)*/
  SPI_JOB_END_LIST			/* - End List Marker.		      */
};
#endif	/*
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) &&
	 * ( SPI_LEVEL_DELIVERED == 2 )
	 */

/*
 * Loop-back Mode Sequences Configuration.
 */
const Spi_SequenceConfigType		Spi_LBMSequenceConfig[] = {
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    TRUE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__
    &Spi_LBMSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_0,			/* SpiSequenceId.		      */
    &Spi_LBMSeq0JobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__
    &Spi_LBMSeq1EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_1,			/* SpiSequenceId.		      */
    &Spi_LBMSeq1JobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__
    &Spi_LBMSeq2EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_2,			/* SpiSequenceId.		      */
    &Spi_LBMSeq2JobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__
    &Spi_LBMSeq3EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_3,			/* SpiSequenceId.		      */
    &Spi_LBMSeq3JobAssignment[0]	/* SpiJobAssignment.		      */
  },
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  {
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    TRUE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__
    &Spi_LBMSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_0_EB,			/* SpiSequenceId.		      */
    &Spi_LBMSeq0EBJobAssignment[0]	/* SpiJobAssignment.		      */
  },
{
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__
    &Spi_LBMSeq1EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_1_EB,			/* SpiSequenceId.		      */
    &Spi_LBMSeq1EBJobAssignment[0]	/* SpiJobAssignment.		      */
  },
{
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__
    &Spi_LBMSeq2EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_2_EB,			/* SpiSequenceId.		      */
    &Spi_LBMSeq2EBJobAssignment[0]	/* SpiJobAssignment.		      */
  },
{
#if	( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__
    &Spi_LBMSeq3EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
#endif	/* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_LBM_SEQ_3_EB,			/* SpiSequenceId.		      */
    &Spi_LBMSeq3EBJobAssignment[0]	/* SpiJobAssignment.		      */
  },
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#if	( SPI_LEVEL_DELIVERED == 2 )
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    TRUE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__
    &Spi_LBMSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
    SPI_LBM_SEQ_0_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq0SYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__
    &Spi_LBMSeq1EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
    SPI_LBM_SEQ_1_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq1SYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__
    &Spi_LBMSeq2EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
    SPI_LBM_SEQ_2_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq2SYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__
    &Spi_LBMSeq3EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
    SPI_LBM_SEQ_3_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq3SYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
#endif	/* ( SPI_LEVEL_DELIVERED == 2 ) */
#if	( ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) && ( SPI_LEVEL_DELIVERED == 2 ) )
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    TRUE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__
    &Spi_LBMSeq0EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_0_END_NOTIFICATION__ */
    SPI_LBM_SEQ_0_EB_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq0EBSYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__
    &Spi_LBMSeq1EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_1_END_NOTIFICATION__ */
    SPI_LBM_SEQ_1_EB_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq1EBSYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__
    &Spi_LBMSeq2EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_2_END_NOTIFICATION__ */
    SPI_LBM_SEQ_2_EB_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq2EBSYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
  {
#if	( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,				/* SpiInterruptibleSequence.	      */
#endif	/* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#ifdef	__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__
    &Spi_LBMSeq3EndNotification,	/* SpiJobEndNotification.	      */
#else	/* __AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
    NULL_PTR,				/* SpiJobEndNotification.	      */
#endif	/* !__AS_CFG_SPI_LBM_SEQ_3_END_NOTIFICATION__ */
    SPI_LBM_SEQ_3_EB_SYNC,		/* SpiSequenceId.		      */
    &Spi_LBMSeq3EBSYNCJobAssignment[0]	/* SpiJobAssignment.		      */
  },
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) &&
	 * ( SPI_LEVEL_DELIVERED == 2 )
	 */
};

#endif	/* __AS_CFG_SPI_LBM__ */

#ifdef __AS_CFG_SPI_ENC28J60__
const Spi_ChannelConfigType Spi_Enc28j60ChannelConfig[] = {
  {
    SPI_ENC28J60_CHANNEL_COMMAND,		/* SpiChannelId.	      */
    SPI_IB,					/* SpiChannelType.	      */
    SPI_ENC28J60_DEFAULT_DATA,			/* SpiDefaultData.	      */
    SPI_ENC28J60_CHANNEL_COMMAND_EB_MAX_LENGTH,	/* SpiEbMaxLength.	      */
#if ( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,				/* SpiHwUnitSynchronous.      */
#endif
    SPI_ENC28J60_CHANNEL_COMMAND_IB_N_BUFFERS,	/* SpiIbNBuffers.	      */
  },
  {
    SPI_ENC28J60_CHANNEL_DUMMY,			/* SpiChannelId.	      */
    SPI_IB,					/* SpiChannelType.	      */
    SPI_ENC28J60_DEFAULT_DATA,			/* SpiDefaultData.	      */
    SPI_ENC28J60_CHANNEL_DUMMY_EB_MAX_LENGTH,	/* SpiEbMaxLength.	      */
#if ( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,				/* SpiHwUnitSynchronous.      */
#endif
    SPI_ENC28J60_CHANNEL_DUMMY_IB_N_BUFFERS,	/* SpiIbNBuffers.	      */
  },
  {
    SPI_ENC28J60_CHANNEL_REG,			/* SpiChannelId.	      */
    SPI_IB,					/* SpiChannelType.	      */
    SPI_ENC28J60_DEFAULT_DATA,			/* SpiDefaultData.	      */
    SPI_ENC28J60_CHANNEL_REG_EB_MAX_LENGTH,	/* SpiEbMaxLength.	      */
#if ( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,				/* SpiHwUnitSynchronous.      */
#endif
    SPI_ENC28J60_CHANNEL_REG_IB_N_BUFFERS,	/* SpiIbNBuffers.	      */
  },
  {
    SPI_ENC28J60_CHANNEL_BUFFER,		/* SpiChannelId.	      */
    SPI_EB,					/* SpiChannelType.	      */
    SPI_ENC28J60_DEFAULT_DATA,			/* SpiDefaultData.	      */
    SPI_ENC28J60_CHANNEL_BUFFER_EB_MAX_LENGTH,	/* SpiEbMaxLength.	      */
#if ( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,				/* SpiHwUnitSynchronous.      */
#endif
    SPI_ENC28J60_CHANNEL_BUFFER_IB_N_BUFFERS,	/* SpiIbNBuffers.	      */
  },
  {
    SPI_ENC28J60_CHANNEL_BUFFER_EXT,		/* SpiChannelId.	      */
    SPI_EB,					/* SpiChannelType.	      */
    SPI_ENC28J60_DEFAULT_DATA,			/* SpiDefaultData.	      */
    SPI_ENC28J60_CHANNEL_BUFFER_EXT_EB_MAX_LENGTH,	/* SpiEbMaxLength.    */
#if ( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,				/* SpiHwUnitSynchronous.      */
#endif
    SPI_ENC28J60_CHANNEL_BUFFER_EXT_IB_N_BUFFERS,	/* SpiIbNBuffers.     */
  }
};

const Spi_ExternalDeviceConfigType  Spi_Enc28j60ExternalDeviceConfig[] = {
  {
    1E6,			/* SpiBaudrate */
    SPI_ENC28J60_CS_0,		/* SpiCsIdentifier */
    SPI_LOW,			/* SpiCsPolarity */
    SPI_LEADING,		/* SpiDataShiftEdge */
    TRUE,			/* SpiEnableCs */
    DIO_CHANNEL_ENC28J60_CS,	/* SpiCsChannelId */
    SPI_HW_UNIT_1,		/* SpiHwUnit */
    SPI_LOW,			/* SpiShiftClockIdleLevel */
#if ( SPI_LEVEL_DELIVERED == 2 )
    SPI_SYNCHRONOUS,		/* SpiHwUnitSynchronous. */
#endif
    SPI_HW_UNIT_MASTER,		/* - Master */
    TRUE,			/* SpiSysClock. */
    DMA_CHANNEL_SPI_1_RX,	/* SpiDmaRxChannel. */
    DMA_CHANNEL_SPI_1_TX,	/* SpiDmaTxChannel. */
  }
};

const Spi_ChannelType Spi_Enc28j60CRChannelList[] = {
  SPI_ENC28J60_CHANNEL_COMMAND,
  SPI_ENC28J60_CHANNEL_REG,
  SPI_CHANNEL_END_LIST
};

const Spi_ChannelType Spi_Enc28j60CRWithDummyChannelList[] = {
  SPI_ENC28J60_CHANNEL_COMMAND,
  SPI_ENC28J60_CHANNEL_DUMMY,
  SPI_ENC28J60_CHANNEL_REG,
  SPI_CHANNEL_END_LIST
};

const Spi_ChannelType Spi_Enc28j60BufferMemoryChannelList[] = {
  SPI_ENC28J60_CHANNEL_COMMAND,
  SPI_ENC28J60_CHANNEL_BUFFER,
  SPI_CHANNEL_END_LIST
};

const Spi_ChannelType Spi_Enc28j60ExtBufferMemoryChannelList[] = {
  SPI_ENC28J60_CHANNEL_COMMAND,
  SPI_ENC28J60_CHANNEL_BUFFER,
  SPI_ENC28J60_CHANNEL_BUFFER_EXT,
  SPI_CHANNEL_END_LIST
};

const Spi_ChannelType Spi_Enc28j60SRChannelList[] = {
  SPI_ENC28J60_CHANNEL_COMMAND,
  SPI_CHANNEL_END_LIST
};

const Spi_JobConfigType Spi_Enc28j60JobConfig[] = {
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_RCR_ETH,                   /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60CRChannelList[0]               /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_RCR_MAC_OR_MII,            /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60CRWithDummyChannelList[0]      /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_RBM,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60BufferMemoryChannelList[0]     /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_WCR,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60CRChannelList[0]               /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_WBM,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60BufferMemoryChannelList[0]     /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_BFS,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60CRChannelList[0]               /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_BFC,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60CRChannelList[0]               /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_SRC,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60SRChannelList[0]               /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_REBM,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60ExtBufferMemoryChannelList[0]  /* SpiChannelList. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
    NULL_PTR,                                   /* SpiJobEndNotification. */
#endif
    SPI_ENC28J60_JOB_WEBM,                       /* SpiJobId. */
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    SPI_ENC28J60_JOB_PRI,                       /* SpiJobPriority. */
#endif  /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_CS_0,                          /* SpiDeviceAssignment. */
    &Spi_Enc28j60ExtBufferMemoryChannelList[0]  /* SpiChannelList. */
  },
};

const Spi_JobType   Spi_Enc28j60SeqRcrEthJobAssignment[] = {
  SPI_ENC28J60_JOB_RCR_ETH,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqRcrMacOrMiiJobAssignment[] = {
  SPI_ENC28J60_JOB_RCR_MAC_OR_MII,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqRbmJobAssignment[] = {
  SPI_ENC28J60_JOB_RBM,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqWcrJobAssignment[] = {
  SPI_ENC28J60_JOB_WCR,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqWbmJobAssignment[] = {
  SPI_ENC28J60_JOB_WBM,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqBfsJobAssignment[] = {
  SPI_ENC28J60_JOB_BFS,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqBfcJobAssignment[] = {
  SPI_ENC28J60_JOB_BFC,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqSrcJobAssignment[] = {
  SPI_ENC28J60_JOB_SRC,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqRebmJobAssignment[] = {
  SPI_ENC28J60_JOB_REBM,
  SPI_JOB_END_LIST      /* - End List Marker. */
};

const Spi_JobType   Spi_Enc28j60SeqWebmJobAssignment[] = {
  SPI_ENC28J60_JOB_WEBM,
  SPI_JOB_END_LIST      /* - End List Marker. */
};


const Spi_SequenceConfigType  Spi_Enc28j60SequenceConfig[] = {
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_RCR_ETH,             /* SpiSequenceId. */
    &Spi_Enc28j60SeqRcrEthJobAssignment[0] /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_RCR_MAC_OR_MII,             /* SpiSequenceId. */
    &Spi_Enc28j60SeqRcrMacOrMiiJobAssignment[0] /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_RBM,                 /* SpiSequenceId. */
    &Spi_Enc28j60SeqRbmJobAssignment[0]   /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_WCR,                 /* SpiSequenceId. */
    &Spi_Enc28j60SeqWcrJobAssignment[0]   /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_WBM,                 /* SpiSequenceId. */
    &Spi_Enc28j60SeqWbmJobAssignment[0]   /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_BFS,                 /* SpiSequenceId. */
    &Spi_Enc28j60SeqBfsJobAssignment[0]   /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_BFC,                 /* SpiSequenceId. */
    &Spi_Enc28j60SeqBfcJobAssignment[0]   /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_SRC,                 /* SpiSequenceId. */
    &Spi_Enc28j60SeqSrcJobAssignment[0]   /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_REBM,                /* SpiSequenceId. */
    &Spi_Enc28j60SeqRebmJobAssignment[0]  /* SpiJobAssignment. */
  },
  {
#if ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) )
#if ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON )
    FALSE,                                /* SpiInterruptibleSequence. */
#endif /* ( SPI_INTERRUPTIBLE_SEQ_ALLOWED == STD_ON ) */
    NULL_PTR,                             /* Spi_SeqEndNotification. */
#endif  /* ( ( SPI_LEVEL_DELIVERED == 1 ) || ( SPI_LEVEL_DELIVERED == 2 ) ) */
    SPI_ENC28J60_SEQ_WEBM,                 /* SpiSequenceId. */
    &Spi_Enc28j60SeqWebmJobAssignment[0]   /* SpiJobAssignment. */
  },
};
#endif /* __AS_CFG_SPI_ENC28J60__ */

/*
 * Internal Buffers.
 */
#if	(\
  ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) || ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )\
)

#ifdef	__AS_CFG_SPI_LBM__
/*
 * Channel 0 Internal Buffers.
 */
Spi_DataType	SpiCh0SrcIb[SPI_CHANNEL_0_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh0DstIb[SPI_CHANNEL_0_MAX_IB_N_BUFFERS];

/*
 * Channel 1 Internal Buffers.
 */
Spi_DataType	SpiCh1SrcIb[SPI_CHANNEL_1_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh1DstIb[SPI_CHANNEL_1_MAX_IB_N_BUFFERS];

/*
 * Channel 2 Internal Buffers.
 */
Spi_DataType	SpiCh2SrcIb[SPI_CHANNEL_2_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh2DstIb[SPI_CHANNEL_2_MAX_IB_N_BUFFERS];

/*
 * Channel 3 Internal Buffers.
 */
Spi_DataType	SpiCh3SrcIb[SPI_CHANNEL_3_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh3DstIb[SPI_CHANNEL_3_MAX_IB_N_BUFFERS];

/*
 * Channel 4 Internal Buffers.
 */
Spi_DataType	SpiCh4SrcIb[SPI_CHANNEL_4_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh4DstIb[SPI_CHANNEL_4_MAX_IB_N_BUFFERS];

/*
 * Channel 5 Internal Buffers.
 */
Spi_DataType	SpiCh5SrcIb[SPI_CHANNEL_5_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh5DstIb[SPI_CHANNEL_5_MAX_IB_N_BUFFERS];

/*
 * Channel 6 Internal Buffers.
 */
Spi_DataType	SpiCh6SrcIb[SPI_CHANNEL_6_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh6DstIb[SPI_CHANNEL_6_MAX_IB_N_BUFFERS];

/*
 * Channel 7 Internal Buffers.
 */
Spi_DataType	SpiCh7SrcIb[SPI_CHANNEL_7_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh7DstIb[SPI_CHANNEL_7_MAX_IB_N_BUFFERS];

/*
 * Channel 8 Internal Buffers.
 */
Spi_DataType	SpiCh8SrcIb[SPI_CHANNEL_8_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh8DstIb[SPI_CHANNEL_8_MAX_IB_N_BUFFERS];

/*
 * Channel 9 Internal Buffers.
 */
Spi_DataType	SpiCh9SrcIb[SPI_CHANNEL_9_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh9DstIb[SPI_CHANNEL_9_MAX_IB_N_BUFFERS];

/*
 * Channel 10 Internal Buffers.
 */
Spi_DataType	SpiCh10SrcIb[SPI_CHANNEL_10_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh10DstIb[SPI_CHANNEL_10_MAX_IB_N_BUFFERS];

/*
 * Channel 11 Internal Buffers.
 */
Spi_DataType	SpiCh11SrcIb[SPI_CHANNEL_11_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh11DstIb[SPI_CHANNEL_11_MAX_IB_N_BUFFERS];

/*
 * Channel 12 Internal Buffers.
 */
Spi_DataType	SpiCh12SrcIb[SPI_CHANNEL_12_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh12DstIb[SPI_CHANNEL_12_MAX_IB_N_BUFFERS];

/*
 * Channel 13 Internal Buffers.
 */
Spi_DataType	SpiCh13SrcIb[SPI_CHANNEL_13_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh13DstIb[SPI_CHANNEL_13_MAX_IB_N_BUFFERS];

#else	/* __AS_CFG_SPI_LBM__ */

/*
 * Channel 0 Internal Buffers.
 */
Spi_DataType	SpiCh0SrcIb[SPI_CHANNEL_0_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh0DstIb[SPI_CHANNEL_0_MAX_IB_N_BUFFERS];

#ifdef	__AS_CFG_SPI_ENC28J60__
/*
 * Channel 1 Internal Buffers.
 */
Spi_DataType	SpiCh1SrcIb[SPI_CHANNEL_1_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh1DstIb[SPI_CHANNEL_1_MAX_IB_N_BUFFERS];

/*
 * Channel 2 Internal Buffers.
 */
Spi_DataType	SpiCh2SrcIb[SPI_CHANNEL_2_MAX_IB_N_BUFFERS];
Spi_DataType	SpiCh2DstIb[SPI_CHANNEL_2_MAX_IB_N_BUFFERS];
#endif	/* __AS_CFG_SPI_ENC28J60__ */

#endif	/* __AS_CFG_SPI_LBM__ */

/*
 * Channel Internal Buffers Arrays.
 */
Spi_DataType * const	SpiChSrcIb[] = {
  &SpiCh0SrcIb[0],
#ifdef	__AS_CFG_SPI_LBM__
  &SpiCh1SrcIb[0],
  &SpiCh2SrcIb[0],
  &SpiCh3SrcIb[0],
  &SpiCh4SrcIb[0],
  &SpiCh5SrcIb[0],
  &SpiCh6SrcIb[0],
  &SpiCh7SrcIb[0],
  &SpiCh8SrcIb[0],
  &SpiCh9SrcIb[0],
  &SpiCh10SrcIb[0],
  &SpiCh11SrcIb[0],
  &SpiCh12SrcIb[0],
  &SpiCh13SrcIb[0],
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#else	/* __AS_CFG_SPI_LBM__ */
#ifdef	__AS_CFG_SPI_ENC28J60__
  &SpiCh1SrcIb[0],
  &SpiCh2SrcIb[0],
  NULL_PTR,
  NULL_PTR,
#else	/* __AS_CFG_SPI_ENC28J60__ */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  NULL_PTR,
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#endif	/* !__AS_CFG_SPI_ENC28J60__ */
#endif	/* !__AS_CFG_SPI_LBM__ */
};

Spi_DataType * const	SpiChDstIb[] = {
  &SpiCh0DstIb[0],
#ifdef	__AS_CFG_SPI_LBM__
  &SpiCh1DstIb[0],
  &SpiCh2DstIb[0],
  &SpiCh3DstIb[0],
  &SpiCh4DstIb[0],
  &SpiCh5DstIb[0],
  &SpiCh6DstIb[0],
  &SpiCh7DstIb[0],
  &SpiCh8DstIb[0],
  &SpiCh9DstIb[0],
  &SpiCh10DstIb[0],
  &SpiCh11DstIb[0],
  &SpiCh12DstIb[0],
  &SpiCh13DstIb[0],
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
  NULL_PTR,
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#else	/* __AS_CFG_SPI_LBM__ */
#ifdef	__AS_CFG_SPI_ENC28J60__
  &SpiCh1DstIb[0],
  &SpiCh2DstIb[0],
  NULL_PTR,
  NULL_PTR,
#else	/* __AS_CFG_SPI_ENC28J60__ */
#if	( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
  NULL_PTR,
#endif	/* ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 ) */
#endif	/* !__AS_CFG_SPI_ENC28J60__ */
#endif	/* !__AS_CFG_SPI_LBM__ */
};
#endif	/* 
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 0 ) ||
	 * ( SPI_CHANNEL_BUFFERS_ALLOWED == 2 )
	 */

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
#ifdef	__AS_CFG_SPI_LBM__
  {
    SPI_LBM_CHANNELS_NUMBER,		/* SpiMaxChannel.		      */
    SPI_LBM_EXTERNAL_DEVICES_NUMBER,	/* SpiMaxExternalDevice.	      */
    SPI_LBM_JOBS_NUMBER,		/* SpiMaxJob.			      */
    SPI_LBM_SEQUENCES_NUMBER,		/* SpiMaxSequence.		      */
    &Spi_LBMChannelConfig[0],		/* SpiChannel.			      */
    &Spi_LBMExternalDeviceConfig[0],	/* SpiExternalDevice.		      */
    &Spi_LBMJobConfig[0],		/* SpiJob.			      */
    &Spi_LBMSequenceConfig[0]		/* SpiSequence.			      */
  },
#endif	/* __AS_CFG_SPI_LBM__ */
#ifdef __AS_CFG_SPI_ENC28J60__
  {
    SPI_ENC28J60_CHANNELS_NUMBER,         /* SpiMaxChannel. */
    SPI_ENC28J60_EXTERNAL_DEVICES_NUMBER, /* SpiMaxExternalDevice. */
    SPI_ENC28J60_JOBS_NUMBER,             /* SpiMaxJob. */
    SPI_ENC28J60_SEQUENCES_NUMBER,        /* SpiMaxSequence. */
    &Spi_Enc28j60ChannelConfig[0],        /* SpiChannel. */
    &Spi_Enc28j60ExternalDeviceConfig[0], /* SpiExternalDevice. */
    &Spi_Enc28j60JobConfig[0],            /* SpiJob. */
    &Spi_Enc28j60SequenceConfig[0]        /* SpiSequence. */
  }
#endif /* __AS_CFG_SPI_ENC28J60__ */
};
