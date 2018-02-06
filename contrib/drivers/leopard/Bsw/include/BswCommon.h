/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
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
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

#ifndef _BSWCOMMON_H_
#define _BSWCOMMON_H_

#include "eecfg.h"
#include "ApplCfg.h"
#include <string.h>
#include "Std_Types.h"

#ifdef UNIT_TEST
    #include <stdio.h>
#endif

// Task periods (unit: msec)
#define TASK_CAN_TX_TASK_PERIOD     (1)
#define TASK_5MSEC_TASK_PERIOD      (5)
#define TASK_20MSEC_TASK_PERIOD     (20)

#ifdef NULL
#undef NULL
#endif
#define NULL                ((void *)0L)

#ifdef FALSE
#undef FALSE
#endif
#define FALSE                ((boolean)0)

#ifdef TRUE
#undef TRUE
#endif
#define TRUE                ((boolean)1)

/* Data type limits - taken from Codewarrior */
// todo: non userei USHRT_MAX (e USHRT_MAX) visto che stiamo usando i tipi uint16 e simili
// I limiti Freescale sono in ./Freescale/CW MCU v10.2/MCU/PA_Support/ewl/EWL_C/include/climits
// #define MAX_UINT16 USHRT_MAX
#define MAX_UINT8           (0xFF)
#define MAX_INT16           (0x7FFF)
#define MAX_UINT16          (0xFFFF)
#define MAX_UINT32          (0xFFFFFFFF)

// Values used to identify non-valid data
#define NOT_VALID_INT16     (0x7FFF)
#define NOT_VALID_INT32     (0x7FFFFFFF)
#define NOT_VALID_INT8      (0x7F)
#define NOT_VALID_UINT8     (0xFF)

// Values for StdReturnType
#define STD_OK                      ((StdReturnType) 0x00)      ///< The routine terminates without errors.
#define STD_NO_DATA                 ((StdReturnType) 0x01)      ///< The requested data are not present.
#define STD_BUSY                    ((StdReturnType) 0x02)      ///< The routine cannot do the job because some resource is occupied.
#define STD_ILLEGAL                 ((StdReturnType) 0x03)      ///< The request contains not valid data,
#define STD_NOT_COMPLETE            ((StdReturnType) 0x04)      ///< The routine worked fine, but the job is not completed. This is not an error, this is a status.
#define STD_NOT_INITIALIZED         ((StdReturnType) 0x05)      ///< The routine cannot do the job because the resource is not initialized.
#define STD_WRONG_SEQUENCE          ((StdReturnType) 0x06)      ///< The routine has been called with a wrong sequence.
#define STD_NOTHING_TO_DO           ((StdReturnType) 0x07)      ///< The requested service is not necessary. This is not an error, it's just an information for the caller.
#define STD_ABORT_PREVIUOS          ((StdReturnType) 0x08)      ///< The routine worked fine, but, in order to complete the current job, the previous job has been aborted.
#define STD_NOT_OK                  ((StdReturnType) 0x99)      ///< Generic error.

#define CALIBRATIONS_SECTION(s)     __declspec(section s) \
                                    __attribute__ ((aligned (8))) \
                                    __attribute__((force_export))

// Used for bootloader input data
#define BOOTLOADER_DATA_SECTION(s)  __declspec(section s) \
                                    __attribute__((force_export))

typedef uint8         StdReturnType;    // Generic return type - Autosar reference: Std_ReturnType

/// Type for the initialization state of the component
typedef enum
{
    COMPONENT_STATE_NOT_INIZIALIZED,
    COMPONENT_STATE_INIZIALIZED,
    COMPONENT_STATE_DATA_LOADED,
    COMPONENT_STATE_SHUTDOWN            ///< The component is shutting down
} InitializationStateType;

#endif      // _BSWCOMMON_H_

