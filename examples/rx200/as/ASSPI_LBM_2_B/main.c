/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013	Evidence Srl
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
 * module.	An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.	If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Simple project to test the AUTOSAR SPI Handler/Driver:
 * - 1 Sequence
 * - 2 Jobs
 *   - 4 Channels 
 *   - 7 Channels
 * - 3 SCI Hardware Units
 *	 - Loop-back Mode (MOSI and MISO pins connected by a wire)
 *	 - 2 Units Asynchronous
 *	 - 1 Units Synchronous
 * - Write/AsyncTransmit/Read (IB)
 *	 - Interrupt Mode
 *	 - Polling Mode
 * - Setup/AsyncTransmit (EB)
 *	 - Interrupt Mode
 *	 - Polling Mode
 * - Write/SyncTransmit/Read (IB)
 * - Setup/SyncTransmit (EB)
 *
 * Author: 2013	 Gianluca Franchino
 */

#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Spi.h"
#include "test/assert/inc/ee_assert.h"

#include <string.h>

/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,					/*	0 */
	EE_ASSERT_INIT,						/*	1 */
	EE_ASSERT_VERSION,					/*	2 */
	EE_ASSERT_CLOCK_INIT,				/*	3 */
	EE_ASSERT_SPI_INIT,					/*	4 */
	EE_ASSERT_SPI_UNINIT,				/*	5 */
	EE_ASSERT_SPI_INTERRUPT_MODE,		/*	6 */
	EE_ASSERT_SPI_INT_WRITE_IB_0,		/*  7 */
	EE_ASSERT_SPI_INT_WRITE_IB_1,		/*  8 */
	EE_ASSERT_SPI_INT_WRITE_IB_2,		/*  9 */
	EE_ASSERT_SPI_INT_WRITE_IB_3,		/*  10 */
	EE_ASSERT_SPI_INT_WRITE_IB_4,		/*  11 */
	EE_ASSERT_SPI_INT_WRITE_IB_5,		/*  12 */
	EE_ASSERT_SPI_INT_WRITE_IB_6,		/*  13 */
	EE_ASSERT_SPI_INT_WRITE_IB_7,		/*  14 */
	EE_ASSERT_SPI_INT_WRITE_IB_8,		/*  15 */
	EE_ASSERT_SPI_INT_WRITE_IB_9,		/*  16 */
	EE_ASSERT_SPI_INT_WRITE_IB_10,		/*  17 */
	EE_ASSERT_SPI_INT_ASYNC_TX,			/*  18 */
	EE_ASSERT_SPI_INT_JOB_END,			/*  19 */
	EE_ASSERT_SPI_INT_JOB_OK,			/*  20 */
	EE_ASSERT_SPI_INT_SEQ_END,			/*  21 */
	EE_ASSERT_SPI_INT_SEQ_OK,			/*  22 */
	EE_ASSERT_SPI_INT_READ_IB_0,		/*  23 */
	EE_ASSERT_SPI_INT_READ_IB_1,		/*  24 */
	EE_ASSERT_SPI_INT_READ_IB_2,		/*  25 */
	EE_ASSERT_SPI_INT_READ_IB_3,		/*  26 */
	EE_ASSERT_SPI_INT_READ_IB_4,		/*  27 */
	EE_ASSERT_SPI_INT_READ_IB_5,		/*  28 */
	EE_ASSERT_SPI_INT_READ_IB_6,		/*  29 */
	EE_ASSERT_SPI_INT_READ_IB_7,		/*  30 */
	EE_ASSERT_SPI_INT_READ_IB_8,		/*  31 */
	EE_ASSERT_SPI_INT_READ_IB_9,		/*  32 */
	EE_ASSERT_SPI_INT_READ_IB_10,		/*  33 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_0,	/*  34 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_1,	/*  35 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_2,	/*  36 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_3,	/*  37 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_4,	/*  38 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_5,	/*  39 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_6,	/*  40 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_7,	/*  41 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_8,	/*  42 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_9,	/*  43 */
	EE_ASSERT_SPI_INT_READ_VALIDATE_10,	/*  44 */
	EE_ASSERT_SPI_POLLING_MODE,			/*  45 */
	EE_ASSERT_SPI_POLL_WRITE_IB_0,		/*  46 */
	EE_ASSERT_SPI_POLL_WRITE_IB_1,		/*  47 */
	EE_ASSERT_SPI_POLL_WRITE_IB_2,		/*  48 */
	EE_ASSERT_SPI_POLL_WRITE_IB_3,		/*  49 */
	EE_ASSERT_SPI_POLL_WRITE_IB_4,		/*  50 */
	EE_ASSERT_SPI_POLL_WRITE_IB_5,		/*  51 */
	EE_ASSERT_SPI_POLL_WRITE_IB_6,		/*  52 */
	EE_ASSERT_SPI_POLL_WRITE_IB_7,		/*  53 */
	EE_ASSERT_SPI_POLL_WRITE_IB_8,		/*  54 */
	EE_ASSERT_SPI_POLL_WRITE_IB_9,		/*  55 */
	EE_ASSERT_SPI_POLL_WRITE_IB_10,		/*  56 */
	EE_ASSERT_SPI_POLL_ASYNC_TX,		/*  57 */
	EE_ASSERT_SPI_POLL_JOB_END,			/*  58 */
	EE_ASSERT_SPI_POLL_JOB_OK,			/*  59 */
	EE_ASSERT_SPI_POLL_SEQ_END,			/*  60 */
	EE_ASSERT_SPI_POLL_SEQ_OK,			/*  61 */
	EE_ASSERT_SPI_POLL_READ_IB_0,		/*  62 */
	EE_ASSERT_SPI_POLL_READ_IB_1,		/*  63 */
	EE_ASSERT_SPI_POLL_READ_IB_2,		/*  64 */
	EE_ASSERT_SPI_POLL_READ_IB_3,		/*  65 */
	EE_ASSERT_SPI_POLL_READ_IB_4,		/*  66 */
	EE_ASSERT_SPI_POLL_READ_IB_5,		/*  67 */
	EE_ASSERT_SPI_POLL_READ_IB_6,		/*  68 */
	EE_ASSERT_SPI_POLL_READ_IB_7,		/*  69 */
	EE_ASSERT_SPI_POLL_READ_IB_8,		/*  70 */
	EE_ASSERT_SPI_POLL_READ_IB_9,		/*  71 */
	EE_ASSERT_SPI_POLL_READ_IB_10,		/*  72 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_0,	/*  73 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_1,	/*  74 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_2,	/*  75 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_3,	/*  76 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_4,	/*  77 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_5,	/*  78 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_6,	/*  79 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_7,	/*  80 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_8,	/*  81 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_9,	/*  82 */
	EE_ASSERT_SPI_POLL_READ_VALIDATE_10,/*  83 */
	EE_ASSERT_SPI_EB_INT_MODE,			/*  84 */
	EE_ASSERT_SPI_EB_INT_SETUP_0,		/*  85 */
	EE_ASSERT_SPI_EB_INT_SETUP_1,		/*  86 */
	EE_ASSERT_SPI_EB_INT_SETUP_2,		/*  87 */
	EE_ASSERT_SPI_EB_INT_SETUP_3,		/*  88 */
	EE_ASSERT_SPI_EB_INT_SETUP_4,		/*  89 */
	EE_ASSERT_SPI_EB_INT_SETUP_5,		/*  90 */
	EE_ASSERT_SPI_EB_INT_SETUP_6,		/*  91 */
	EE_ASSERT_SPI_EB_INT_SETUP_7,		/*  92 */
	EE_ASSERT_SPI_EB_INT_SETUP_8,		/*  93 */
	EE_ASSERT_SPI_EB_INT_SETUP_9,		/*  94 */
	EE_ASSERT_SPI_EB_INT_SETUP_10,		/*  95 */
	EE_ASSERT_SPI_EB_INT_ASYNC_TX,		/*  96 */
	EE_ASSERT_SPI_EB_INT_JOB_END,		/*  97 */
	EE_ASSERT_SPI_EB_INT_JOB_OK,		/*  98 */
	EE_ASSERT_SPI_EB_INT_SEQ_END,		/*  99 */
	EE_ASSERT_SPI_EB_INT_SEQ_OK,		/* 100 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_0,	/* 101 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_1,	/* 102 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_2,	/* 103 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_3,	/* 104 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_4,	/* 105 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_5,	/* 106 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_6,	/* 107 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_7,	/* 108 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_8,	/* 109 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_9,	/* 110 */
	EE_ASSERT_SPI_EB_INT_VALIDATE_10,	/* 111 */
	EE_ASSERT_SPI_EB_POLL_MODE,			/* 112 */
	EE_ASSERT_SPI_EB_POLL_SETUP_0,		/* 113 */
	EE_ASSERT_SPI_EB_POLL_SETUP_1,		/* 114 */
	EE_ASSERT_SPI_EB_POLL_SETUP_2,		/* 115 */
	EE_ASSERT_SPI_EB_POLL_SETUP_3,		/* 116 */
	EE_ASSERT_SPI_EB_POLL_SETUP_4,		/* 117 */
	EE_ASSERT_SPI_EB_POLL_SETUP_5,		/* 118 */
	EE_ASSERT_SPI_EB_POLL_SETUP_6,		/* 119 */
	EE_ASSERT_SPI_EB_POLL_SETUP_7,		/* 120 */
	EE_ASSERT_SPI_EB_POLL_SETUP_8,		/* 121 */
	EE_ASSERT_SPI_EB_POLL_SETUP_9,		/* 122 */
	EE_ASSERT_SPI_EB_POLL_SETUP_10,		/* 123 */
	EE_ASSERT_SPI_EB_POLL_ASYNC_TX,		/* 124 */
	EE_ASSERT_SPI_EB_POLL_JOB_END,		/* 125 */
	EE_ASSERT_SPI_EB_POLL_JOB_OK,		/* 126 */
	EE_ASSERT_SPI_EB_POLL_SEQ_END,		/* 127 */
	EE_ASSERT_SPI_EB_POLL_SEQ_OK,		/* 128 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_0,	/* 129 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_1,	/* 130 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_2,	/* 131 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_3,	/* 132 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_4,	/* 133 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_5,	/* 134 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_6,	/* 135 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_7,	/* 136 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_8,	/* 137 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_9,	/* 138 */
	EE_ASSERT_SPI_EB_POLL_VALIDATE_10,	/* 139 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_0,		/* 140 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_1,		/* 141 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_2,		/* 142 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_3,		/* 143 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_4,		/* 140 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_5,		/* 141 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_6,		/* 142 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_7,		/* 143 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_8,		/* 144 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_9,		/* 145 */
	EE_ASSERT_SPI_SYNC_WRITE_IB_10,		/* 146 */
	EE_ASSERT_SPI_SYNC_TX,				/* 147 */
	EE_ASSERT_SPI_SYNC_JOB_1_OK,		/* 148 */
	EE_ASSERT_SPI_SYNC_JOB_2_OK,		/* 149 */
	EE_ASSERT_SPI_SYNC_SEQ_OK,			/* 150 */
	EE_ASSERT_SPI_SYNC_READ_IB_0,		/* 151 */
	EE_ASSERT_SPI_SYNC_READ_IB_1,		/* 152 */
	EE_ASSERT_SPI_SYNC_READ_IB_2,		/* 152 */
	EE_ASSERT_SPI_SYNC_READ_IB_3,		/* 153 */
	EE_ASSERT_SPI_SYNC_READ_IB_4,		/* 154 */
	EE_ASSERT_SPI_SYNC_READ_IB_5,		/* 155 */
	EE_ASSERT_SPI_SYNC_READ_IB_6,		/* 156 */
	EE_ASSERT_SPI_SYNC_READ_IB_7,		/* 157 */
	EE_ASSERT_SPI_SYNC_READ_IB_8,		/* 158 */
	EE_ASSERT_SPI_SYNC_READ_IB_9,		/* 159 */
	EE_ASSERT_SPI_SYNC_READ_IB_10,		/* 160 */
	EE_ASSERT_SPI_SYNC_VALIDATE_0,		/* 161 */
	EE_ASSERT_SPI_SYNC_VALIDATE_1,		/* 162 */
	EE_ASSERT_SPI_SYNC_VALIDATE_2,		/* 163 */
	EE_ASSERT_SPI_SYNC_VALIDATE_3,		/* 164 */
	EE_ASSERT_SPI_SYNC_VALIDATE_4,		/* 165 */
	EE_ASSERT_SPI_SYNC_VALIDATE_5,		/* 166 */
	EE_ASSERT_SPI_SYNC_VALIDATE_6,		/* 167 */
	EE_ASSERT_SPI_SYNC_VALIDATE_7,		/* 168 */
	EE_ASSERT_SPI_SYNC_VALIDATE_8,		/* 169 */
	EE_ASSERT_SPI_SYNC_VALIDATE_9,		/* 170 */
	EE_ASSERT_SPI_SYNC_VALIDATE_10,		/* 171 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_0,		/* 172 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_1,		/* 173 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_2,		/* 174 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_3,		/* 175 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_4,		/* 176 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_5,		/* 177 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_6,		/* 178 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_7,		/* 179 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_8,		/* 180 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_9,		/* 181 */
	EE_ASSERT_SPI_EB_SYNC_SETUP_10,		/* 182 */
	EE_ASSERT_SPI_EB_SYNC_TX,			/* 183 */
	EE_ASSERT_SPI_EB_SYNC_JOB_1_OK,		/* 184 */
	EE_ASSERT_SPI_EB_SYNC_JOB_2_OK,		/* 185 */
	EE_ASSERT_SPI_EB_SYNC_SEQ_OK,		/* 186 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_0,	/* 187 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_1,	/* 188 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_2,	/* 189 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_3,	/* 190 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_4,	/* 191 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_5,	/* 192 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_6,	/* 193 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_7,	/* 194 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_8,	/* 195 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_9,	/* 196 */
	EE_ASSERT_SPI_EB_SYNC_VALIDATE_10,	/* 197 */
	EE_ASSERT_SPI_DEINIT,				/* 198*/
	EE_ASSERT_DIM
};


EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int test = 0;

/* counter */
volatile int counter = 0;

/*
 * TASK Job Error.
 */
TASK(TaskJobError)
{
	counter++;
}

/*
 * TASK Job Ok.
 */
TASK(TaskJobOk)
{

	switch (test) {
		case 0:
			EE_assert(EE_ASSERT_SPI_INT_JOB_OK, TRUE, 
					EE_ASSERT_SPI_INT_JOB_END);
			break;
		case 1:
			EE_assert(EE_ASSERT_SPI_POLL_JOB_OK, TRUE, 
					EE_ASSERT_SPI_POLL_JOB_END);
			break;
		case 2:
			EE_assert(EE_ASSERT_SPI_EB_INT_JOB_OK, TRUE, 
					EE_ASSERT_SPI_EB_INT_JOB_END);
			break;
		case 3:
			EE_assert(EE_ASSERT_SPI_EB_POLL_JOB_OK, TRUE, 
					EE_ASSERT_SPI_EB_POLL_JOB_END);
			break;
	}
}

/*
 * LBM Job 1 End Notification.
 */
void Spi_LBMJob1EndNotification()
{

	switch (test) {
	case 0: 
		EE_assert(EE_ASSERT_SPI_INT_JOB_END, TRUE, EE_ASSERT_SPI_INT_WRITE_IB_3);
		if (Spi_GetJobResult(SPI_LBM_JOB_1) == SPI_JOB_OK) { 
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_JOB_END, TRUE, EE_ASSERT_SPI_POLL_ASYNC_TX);
		if (Spi_GetJobResult(SPI_LBM_JOB_1) == SPI_JOB_OK) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		} 
		break;	
	case 2: 
		EE_assert(EE_ASSERT_SPI_EB_INT_JOB_END, TRUE, EE_ASSERT_SPI_EB_INT_SETUP_3);
		if (Spi_GetJobResult(SPI_LBM_JOB_1_EB) == SPI_JOB_OK) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_JOB_END, TRUE, 
				EE_ASSERT_SPI_EB_POLL_ASYNC_TX);
		if (Spi_GetJobResult(SPI_LBM_JOB_1_EB) == SPI_JOB_OK) {
			ActivateTask(TaskJobOk);
		} else {
			ActivateTask(TaskJobError);
		}
		break;
	}
}

/*
 * TASK Sequence Error
 */
TASK(TaskSeqError)
{

  counter++;

}

/*
 * TASK Sequence Ok
 */
TASK(TaskSeqOk)
{

	switch (test) {
	case 0:
		EE_assert(EE_ASSERT_SPI_INT_SEQ_OK, TRUE, EE_ASSERT_SPI_INT_SEQ_END);
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_SEQ_OK, TRUE, EE_ASSERT_SPI_POLL_SEQ_END);
		break;
	case 2:
		EE_assert(EE_ASSERT_SPI_EB_INT_SEQ_OK, TRUE, 
				EE_ASSERT_SPI_EB_INT_SEQ_END);
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_SEQ_OK, TRUE, 
				EE_ASSERT_SPI_EB_POLL_SEQ_END);
		break;
  }

}

/*
 * LBM Sequence 0 End Notification.
 */
void Spi_LBMSeq0EndNotification()
{

	switch (test) {
	case 0:
		EE_assert(EE_ASSERT_SPI_INT_SEQ_END, 
			( Spi_GetJobResult(SPI_LBM_JOB_2) == SPI_JOB_OK ), 
			EE_ASSERT_SPI_INT_JOB_END);
		if (Spi_GetSequenceResult(SPI_LBM_SEQ_0) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 1:
		EE_assert(EE_ASSERT_SPI_POLL_SEQ_END, 
			( Spi_GetJobResult(SPI_LBM_JOB_2) == SPI_JOB_OK ), 
			EE_ASSERT_SPI_POLL_JOB_END);
		if (Spi_GetSequenceResult(SPI_LBM_SEQ_0) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 2:
		EE_assert(EE_ASSERT_SPI_EB_INT_SEQ_END, 
			( Spi_GetJobResult(SPI_LBM_JOB_2_EB) == SPI_JOB_OK ), 
			EE_ASSERT_SPI_EB_INT_JOB_END);
		if (Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB) == SPI_SEQ_OK) {
			ActivateTask(TaskSeqOk);
		} else {
			ActivateTask(TaskSeqError);
		}
		break;
	case 3:
		EE_assert(EE_ASSERT_SPI_EB_POLL_SEQ_END, 
		( Spi_GetJobResult(SPI_LBM_JOB_2_EB) == SPI_JOB_OK ), 
				EE_ASSERT_SPI_EB_POLL_JOB_END);
	  if (Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB) == SPI_SEQ_OK) {
		  ActivateTask(TaskSeqOk);
	  } else {
		  ActivateTask(TaskSeqError);
	  }
	  break;
	}
}


#define	SPI_TX_RX_DATA_NULL	0x00U

#define	SPI_CHANNEL_NUMBER	0x0BU

#if	0	/* Not-Optimized Code. */
Spi_DataType rx[SPI_CHANNEL_NUMBER][SPI_IB_MAX_N_BUFFERS],
		tx[SPI_CHANNEL_NUMBER][SPI_IB_MAX_N_BUFFERS];
#else	/* Optimized Code. */
Spi_DataType rx[SPI_CHANNEL_NUMBER][SPI_CHANNEL_13_MAX_IB_N_BUFFERS],
		tx[SPI_CHANNEL_NUMBER][SPI_CHANNEL_13_MAX_IB_N_BUFFERS];
#endif	/* Optimized Code. */

void setup_buff(void)
{

	Spi_NumberOfDataType i, j;

	for (i = 0; i < SPI_CHANNEL_NUMBER; i++) {

#if	0	/* Not-Optimized Code. */
		for (j = 0; j < SPI_IB_MAX_N_BUFFERS; j++) {
#else	/* Optimized Code. */
		for (j = 0; j < SPI_CHANNEL_13_MAX_IB_N_BUFFERS; j++) {
#endif	/* Optimized Code. */
			rx[i][j] = SPI_TX_RX_DATA_NULL;
			tx[i][j] = counter + test + i + j;
		}
	}
}


boolean cmp_buff(Spi_NumberOfDataType idx)
{

	Spi_NumberOfDataType	i;
	boolean		rv = TRUE;

	for (i = 0; i < ( idx + 1 ); i++) {

		if ( rx[idx][i] != tx[idx][i] ) {

			rv = FALSE;
		}

	}

	return rv;
}


/*
 * MAIN TASK
 */
int main(void)
{
	Std_VersionInfoType	version;
	Dio_PortLevelType	lvl;

	counter = 0;

	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	Spi_GetVersionInfo(&version);

	EE_assert(EE_ASSERT_VERSION, 
			((version.vendorID == 0) && 
					(version.moduleID == 83) && 
					(version.sw_major_version == 1) && 
					(version.sw_minor_version == 0) && 
					(version.sw_patch_version == 0)), 
					EE_ASSERT_INIT);

	Mcu_Init(MCU_CONFIG_DEFAULT_PTR);
	
	if (Mcu_InitClock(MCU_CLK_MODE_HOCO40_I1_B2) == E_NOT_OK) {
		/* Clock Initialization Error. */
		Mcu_PerformReset();
	}
	
	EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);

	Port_Init(PORT_CONFIG_DEFAULT_PTR);

	Dio_Init(DIO_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_SPI_UNINIT, ( Spi_GetStatus() == SPI_UNINIT ), 
			EE_ASSERT_CLOCK_INIT);
	
	/*Configure the pins of SCI modules */
	Port_Init(PORT_CONFIG_SCI_PTR);

	Spi_Init(SPI_CONFIG_LBM_PTR);

	EE_assert(EE_ASSERT_SPI_INIT, ( Spi_GetStatus() == SPI_IDLE ), 
			EE_ASSERT_INIT);

	test = 0;

	EE_assert(EE_ASSERT_SPI_INTERRUPT_MODE, 
			( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ), 
			EE_ASSERT_SPI_INIT);

	setup_buff();

	EE_assert(EE_ASSERT_SPI_INT_WRITE_IB_0, 
			( Spi_WriteIB(SPI_LBM_CHANNEL_0, tx[0]) == E_OK ), 
			EE_ASSERT_SPI_INTERRUPT_MODE);


	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_1,
		( Spi_WriteIB(SPI_LBM_CHANNEL_1, tx[1]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_0
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_2,
		( Spi_WriteIB(SPI_LBM_CHANNEL_2, tx[2]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_1
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_3,
		( Spi_WriteIB(SPI_LBM_CHANNEL_3, tx[3]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_2
	);


	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_4,
		( Spi_WriteIB(SPI_LBM_CHANNEL_4, tx[4]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_3
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_5,
		( Spi_WriteIB(SPI_LBM_CHANNEL_5, tx[5]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_4
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_6,
		( Spi_WriteIB(SPI_LBM_CHANNEL_6, tx[6]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_5
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_7,
		( Spi_WriteIB(SPI_LBM_CHANNEL_7, tx[7]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_6
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_8,
		( Spi_WriteIB(SPI_LBM_CHANNEL_8, tx[8]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_7
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_9,
		( Spi_WriteIB(SPI_LBM_CHANNEL_9, tx[9]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_8
	);

	EE_assert(
		EE_ASSERT_SPI_INT_WRITE_IB_10,
		( Spi_WriteIB(SPI_LBM_CHANNEL_10, tx[10]) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_9
	);
	
	EE_assert(
		EE_ASSERT_SPI_INT_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_0) == E_OK ),
		EE_ASSERT_SPI_INT_WRITE_IB_10
	);

	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_0) == SPI_SEQ_PENDING ) {
	;
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_0) == SPI_SEQ_OK ) {

		EE_assert(
			EE_ASSERT_SPI_INT_READ_IB_0,
			( Spi_ReadIB(SPI_LBM_CHANNEL_0, rx[0]) == E_OK ),
			EE_ASSERT_SPI_INT_SEQ_OK
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_1,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_1, rx[1]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_0
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_2,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx[2]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_1
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_3,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_3, rx[3]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_2
		);
		
		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_4,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_4, rx[4]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_3
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_5,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_5, rx[5]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_4
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_6,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_6, rx[6]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_5
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_7,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_7, rx[7]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_6
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_8,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_8, rx[8]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_7
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_9,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_9, rx[9]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_8
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_IB_10,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_10, rx[10]) == E_OK ),
		  EE_ASSERT_SPI_INT_READ_IB_9
		);		

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_INT_READ_IB_10
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_2
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_4,
		  cmp_buff(4),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_3
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_5,
		  cmp_buff(5),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_4
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_6,
		  cmp_buff(6),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_5
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_7,
		  cmp_buff(7),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_6
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_8,
		  cmp_buff(8),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_7
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_9,
		  cmp_buff(9),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_8
		);

		EE_assert(
		  EE_ASSERT_SPI_INT_READ_VALIDATE_10,
		  cmp_buff(10),
		  EE_ASSERT_SPI_INT_READ_VALIDATE_9
		);

	}

	test++;

	EE_assert(
	EE_ASSERT_SPI_POLLING_MODE,
	( Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK ),
	EE_ASSERT_SPI_INT_READ_VALIDATE_10
	);

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_0,
		( Spi_WriteIB(SPI_LBM_CHANNEL_0, tx[0]) == E_OK ),
		EE_ASSERT_SPI_POLLING_MODE
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_1,
		( Spi_WriteIB(SPI_LBM_CHANNEL_1, tx[1]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_0
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_2,
		( Spi_WriteIB(SPI_LBM_CHANNEL_2, tx[2]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_1
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_3,
		( Spi_WriteIB(SPI_LBM_CHANNEL_3, tx[3]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_2
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_4,
		( Spi_WriteIB(SPI_LBM_CHANNEL_4, tx[4]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_3
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_5,
		( Spi_WriteIB(SPI_LBM_CHANNEL_5, tx[5]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_4
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_6,
		( Spi_WriteIB(SPI_LBM_CHANNEL_6, tx[6]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_5
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_7,
		( Spi_WriteIB(SPI_LBM_CHANNEL_7, tx[7]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_6
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_8,
		( Spi_WriteIB(SPI_LBM_CHANNEL_8, tx[8]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_7
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_9,
		( Spi_WriteIB(SPI_LBM_CHANNEL_9, tx[9]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_8
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_WRITE_IB_10,
		( Spi_WriteIB(SPI_LBM_CHANNEL_10, tx[10]) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_9
	);

	EE_assert(
		EE_ASSERT_SPI_POLL_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_0) == E_OK ),
		EE_ASSERT_SPI_POLL_WRITE_IB_10
	);


	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_0) == SPI_SEQ_PENDING ) {

		Spi_MainFunction_Handling();
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_0) == SPI_SEQ_OK ) {

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_0,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_0, rx[0]) == E_OK ),
		  EE_ASSERT_SPI_POLL_SEQ_OK
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_1,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_1, rx[1]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_0
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_2,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx[2]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_1
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_3,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_3, rx[3]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_2
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_4,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_4, rx[4]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_3
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_5,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_5, rx[5]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_4
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_6,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_6, rx[6]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_5
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_7,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_7, rx[7]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_6
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_8,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_8, rx[8]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_7
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_9,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_9, rx[9]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_8
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_IB_10,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_10, rx[10]) == E_OK ),
		  EE_ASSERT_SPI_POLL_READ_IB_9
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_POLL_READ_IB_10
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_2
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_4,
		  cmp_buff(4),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_3
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_5,
		  cmp_buff(5),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_4
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_6,
		  cmp_buff(6),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_5
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_7,
		  cmp_buff(7),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_6
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_8,
		  cmp_buff(8),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_7
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_9,
		  cmp_buff(9),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_8
		);

		EE_assert(
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_10,
		  cmp_buff(10),
		  EE_ASSERT_SPI_POLL_READ_VALIDATE_9
		);

	}

	test++;

	EE_assert(
		EE_ASSERT_SPI_EB_INT_MODE,
		( Spi_SetAsyncMode(SPI_INTERRUPT_MODE) == E_OK ),
		EE_ASSERT_SPI_POLL_READ_VALIDATE_10
	);

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_0,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_0_EB, tx[0], rx[0], 1)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_MODE
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_1,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_1_EB, tx[1], rx[1], 2)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_0
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_2,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_2_EB, tx[2], rx[2], 3)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_1
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_3,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_3_EB, tx[3], rx[3], 4)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_2
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_4,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_4_EB, tx[4], rx[4], 5)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_3
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_5,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_5_EB, tx[5], rx[5], 6)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_4
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_6,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_6_EB, tx[6], rx[6], 7)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_5
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_7,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_7_EB, tx[7], rx[7], 8)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_6
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_8,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_8_EB, tx[8], rx[8], 9)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_7
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_9,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_9_EB, tx[9], rx[9], 10)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_8
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_SETUP_10,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_10_EB, tx[10], rx[10], 11)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_INT_SETUP_9
	);

	EE_assert(
		EE_ASSERT_SPI_EB_INT_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_0_EB) == E_OK ),
		EE_ASSERT_SPI_EB_INT_SETUP_10
	);
	
	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB) == SPI_SEQ_PENDING ) {
	;
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB) == SPI_SEQ_OK ) {

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_EB_INT_ASYNC_TX
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_2
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_4,
		  cmp_buff(4),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_3
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_5,
		  cmp_buff(5),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_4
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_6,
		  cmp_buff(6),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_5
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_7,
		  cmp_buff(7),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_6
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_8,
		  cmp_buff(8),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_7
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_9,
		  cmp_buff(9),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_8
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_INT_VALIDATE_10,
		  cmp_buff(10),
		  EE_ASSERT_SPI_EB_INT_VALIDATE_9
		);

	}

	test++;
  
	EE_assert(
		EE_ASSERT_SPI_EB_POLL_MODE,
		( Spi_SetAsyncMode(SPI_POLLING_MODE) == E_OK ),
		EE_ASSERT_SPI_EB_INT_VALIDATE_10
	);
	
	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_0,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_0_EB, tx[0], rx[0], 1)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_MODE
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_1,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_1_EB, tx[1], rx[1], 2)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_0
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_2,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_2_EB, tx[2], rx[2], 3)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_1
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_3,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_3_EB, tx[3], rx[3], 4)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_2
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_4,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_4_EB, tx[4], rx[4], 5)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_3
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_5,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_5_EB, tx[5], rx[5], 6)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_4
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_6,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_6_EB, tx[6], rx[6], 7)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_5
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_7,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_7_EB, tx[7], rx[7], 8)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_6
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_8,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_8_EB, tx[8], rx[8], 9)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_7
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_9,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_9_EB, tx[9], rx[9], 10)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_8
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_SETUP_10,
		(
		  Spi_SetupEB(SPI_LBM_CHANNEL_10_EB, tx[10], rx[10], 11)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_POLL_SETUP_9
	);

	EE_assert(
		EE_ASSERT_SPI_EB_POLL_ASYNC_TX,
		( Spi_AsyncTransmit(SPI_LBM_SEQ_0_EB) == E_OK ),
		EE_ASSERT_SPI_EB_POLL_SETUP_10
	);

	while ( Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB) == SPI_SEQ_PENDING ) {

	Spi_MainFunction_Handling();
	}

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB) == SPI_SEQ_OK ) {

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_EB_POLL_ASYNC_TX
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_2
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_4,
		  cmp_buff(4),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_3
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_5,
		  cmp_buff(5),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_4
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_6,
		  cmp_buff(6),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_5
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_7,
		  cmp_buff(7),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_6
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_8,
		  cmp_buff(8),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_7
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_9,
		  cmp_buff(9),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_8
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_10,
		  cmp_buff(10),
		  EE_ASSERT_SPI_EB_POLL_VALIDATE_9
		);
	}

	test++;

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_0,
		( Spi_WriteIB(SPI_LBM_CHANNEL_0, tx[0]) == E_OK ),
		EE_ASSERT_SPI_EB_POLL_VALIDATE_10
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_1,
		( Spi_WriteIB(SPI_LBM_CHANNEL_1, tx[1]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_0
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_2,
		( Spi_WriteIB(SPI_LBM_CHANNEL_2, tx[2]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_1
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_3,
		( Spi_WriteIB(SPI_LBM_CHANNEL_3, tx[3]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_2
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_4,
		( Spi_WriteIB(SPI_LBM_CHANNEL_4, tx[4]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_3
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_5,
		( Spi_WriteIB(SPI_LBM_CHANNEL_5, tx[5]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_4
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_6,
		( Spi_WriteIB(SPI_LBM_CHANNEL_6, tx[6]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_5
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_7,
		( Spi_WriteIB(SPI_LBM_CHANNEL_7, tx[7]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_6
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_8,
		( Spi_WriteIB(SPI_LBM_CHANNEL_8, tx[8]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_7
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_9,
		( Spi_WriteIB(SPI_LBM_CHANNEL_9, tx[9]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_8
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_WRITE_IB_10,
		( Spi_WriteIB(SPI_LBM_CHANNEL_10, tx[10]) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_9
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_TX,
		( Spi_SyncTransmit(SPI_LBM_SEQ_0_SYNC) == E_OK ),
		EE_ASSERT_SPI_SYNC_WRITE_IB_10
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_JOB_1_OK,
		( Spi_GetJobResult(SPI_LBM_JOB_1_SYNC) == SPI_JOB_OK ),
		EE_ASSERT_SPI_SYNC_TX
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_JOB_2_OK,
		( Spi_GetJobResult(SPI_LBM_JOB_2_SYNC) == SPI_JOB_OK ),
		EE_ASSERT_SPI_SYNC_JOB_1_OK
	);

	EE_assert(
		EE_ASSERT_SPI_SYNC_SEQ_OK,
		( Spi_GetSequenceResult(SPI_LBM_SEQ_0_SYNC) == SPI_SEQ_OK ),
		EE_ASSERT_SPI_SYNC_JOB_2_OK
	);

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_0_SYNC) == SPI_SEQ_OK ) {

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_0,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_0, rx[0]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_SEQ_OK
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_1,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_1, rx[1]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_0
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_2,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_2, rx[2]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_1
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_3,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_3, rx[3]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_2
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_4,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_4, rx[4]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_3
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_5,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_5, rx[5]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_4
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_6,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_6, rx[6]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_5
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_7,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_7, rx[7]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_6
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_8,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_8, rx[8]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_7
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_9,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_9, rx[9]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_8
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_READ_IB_10,
		  ( Spi_ReadIB(SPI_LBM_CHANNEL_10, rx[10]) == E_OK ),
		  EE_ASSERT_SPI_SYNC_READ_IB_9
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_SYNC_READ_IB_10
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_SYNC_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_SYNC_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_SYNC_VALIDATE_2
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_4,
		  cmp_buff(4),
		  EE_ASSERT_SPI_SYNC_VALIDATE_3
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_5,
		  cmp_buff(5),
		  EE_ASSERT_SPI_SYNC_VALIDATE_4
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_6,
		  cmp_buff(6),
		  EE_ASSERT_SPI_SYNC_VALIDATE_5
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_7,
		  cmp_buff(7),
		  EE_ASSERT_SPI_SYNC_VALIDATE_6
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_8,
		  cmp_buff(8),
		  EE_ASSERT_SPI_SYNC_VALIDATE_7
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_9,
		  cmp_buff(9),
		  EE_ASSERT_SPI_SYNC_VALIDATE_8
		);

		EE_assert(
		  EE_ASSERT_SPI_SYNC_VALIDATE_10,
		  cmp_buff(10),
		  EE_ASSERT_SPI_SYNC_VALIDATE_9
		);

	}

	test++;

	setup_buff();

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_0,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_0_EB, tx[0], rx[0], 1)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_SYNC_VALIDATE_10
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_1,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_1_EB, tx[1], rx[1], 2)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_0
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_2,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_2_EB, tx[2], rx[2], 3)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_1
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_3,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_3_EB, tx[3], rx[3], 4)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_2
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_4,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_4_EB, tx[4], rx[4], 5)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_3
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_5,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_5_EB, tx[5], rx[5], 6)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_4
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_6,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_6_EB, tx[6], rx[6], 7)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_5
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_7,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_7_EB, tx[7], rx[7], 8)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_6
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_8,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_8_EB, tx[8], rx[8], 9)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_7
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_9,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_9_EB, tx[9], rx[9], 10)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_8
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SETUP_10,
		( 
		  Spi_SetupEB(SPI_LBM_CHANNEL_10_EB, tx[10], rx[10], 11)
		  ==
		  E_OK
		),
		EE_ASSERT_SPI_EB_SYNC_SETUP_9
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_TX,
		( Spi_SyncTransmit(SPI_LBM_SEQ_0_EB_SYNC) == E_OK ),
		EE_ASSERT_SPI_EB_SYNC_SETUP_10
	);

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_JOB_1_OK,
		( Spi_GetJobResult(SPI_LBM_JOB_1_EB_SYNC) == SPI_JOB_OK ),
		EE_ASSERT_SPI_EB_SYNC_TX
	);

  EE_assert(
    EE_ASSERT_SPI_EB_SYNC_JOB_2_OK,
    ( Spi_GetJobResult(SPI_LBM_JOB_2_EB_SYNC) == SPI_JOB_OK ),
    EE_ASSERT_SPI_EB_SYNC_JOB_1_OK
  );

	EE_assert(
		EE_ASSERT_SPI_EB_SYNC_SEQ_OK,
		( Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB_SYNC) == SPI_SEQ_OK ),
		EE_ASSERT_SPI_EB_SYNC_JOB_2_OK
	);

	if ( Spi_GetSequenceResult(SPI_LBM_SEQ_0_EB_SYNC) == SPI_SEQ_OK ) {

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_0,
		  cmp_buff(0),
		  EE_ASSERT_SPI_EB_SYNC_SEQ_OK
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_1,
		  cmp_buff(1),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_0
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_2,
		  cmp_buff(2),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_1
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_3,
		  cmp_buff(3),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_2
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_4,
		  cmp_buff(4),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_3
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_5,
		  cmp_buff(5),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_4
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_6,
		  cmp_buff(6),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_5
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_7,
		  cmp_buff(7),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_6
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_8,
		  cmp_buff(8),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_7
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_9,
		  cmp_buff(9),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_8
		);

		EE_assert(
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_10,
		  cmp_buff(10),
		  EE_ASSERT_SPI_EB_SYNC_VALIDATE_9
		);
	}
  
	EE_assert(
		EE_ASSERT_SPI_DEINIT,
		( Spi_DeInit() == E_OK ),
		EE_ASSERT_SPI_EB_SYNC_VALIDATE_10
	);

	EE_assert_range(
		EE_ASSERT_FIN,
		( Spi_GetStatus() == SPI_UNINIT ),
		EE_ASSERT_SPI_DEINIT
	);

	result = EE_assert_last();

	/* Forever loop: background activities (if any) should go here */
	for (;result == 1;) {
		while (counter % 100000) counter++;
		
		lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED_0);
		
		if (lvl & 0x00000001)
			Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000000);
		else 
			Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000001);

		counter++;
	}

}