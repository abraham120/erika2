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
 * Harware Abstraction Source file.
 *
 * Author:  2011,  Giuseppe Serano
 */

#include "Std_Types.h"
#include "Hardware.h"
#include "ee.h"

/*
 * Macro to calculate the effective size of an array.
 */
#ifndef	HW_ARRAY_SIZE
#define	HW_ARRAY_SIZE(_x)	(sizeof(_x)/sizeof((_x)[0]))
#endif

/*
 * Supported Cores Identifitication Numbers:
 * - Bits 31:24	Implementer:
 * 	- 0x41: ARM
 * - Bits 23:20	Variant:	Variant number.
 * 				The r value in the rnpn product revision
 * 				identifier.
 * 	- 0x0: revision 0
 * - Bits 19:16	Constant:
 * 	- Reads as 0xF
 * - Bits 15:4	PartNo: Part number of the processor
 * 	- 0xC24: = Cortex-M4
 * - Bits 3:0	Revision:	Revision number
 * 				The p value in the rnpn product revision
 * 				identifier, indicates patch release.
 * 	- 0x0: = no patch
 * 	- 0x1: = patch 1
 */
#define	HW_CORE_CPUID_CORTEX_M4F	0x410FC240
#define	HW_CORE_CPUID_CORTEX_M4F_R1	0x410FC241

/*
 * Core Informations Container Type
 */
typedef struct {
  char		*Name;		/* Core Name String	  */
  uint32	Id;		/* Core Identifier Number */
} Hw_CoreInfoType;

/*
 * Supported Cores Array
 */
const Hw_CoreInfoType Hw_SupportedCoreArray[] =
{
  {
    "ARM Cortex-M4F",			/* .Name */
    HW_CORE_CPUID_CORTEX_M4F,		/* .Id	 */
  },
    {
    "ARM Cortex-M4F Rev 1",		/* .Name */
    HW_CORE_CPUID_CORTEX_M4F_R1,	/* .Id	 */
  },
};

/*
 * Supported Core Informations Retrieval.
 *
 * Id		Core Idenfier Number.
 * Return	Core Informations Container Pointer.
 */
static const Hw_CoreInfoType * Hw_GetSupportedCoreInfo(
  uint32	Id
)
{
  register uint32			i;
  register const Hw_CoreInfoType	*info = NULL;
  for (i = 0; i < HW_ARRAY_SIZE(Hw_SupportedCoreArray); i++) {
    if (Hw_SupportedCoreArray[i].Id == Id) {
      info = &Hw_SupportedCoreArray[i];
    }
  }
  return info;
}

/*
 * Supported Core Check.
 *
 * Return	E_OK:		Core Supported.
 * 		E_NOT_OK:	Core Not Supported.
 */
Std_ReturnType Hw_CheckCore(
  void
) {
  /* NVIC - System Control Block - Register 64: CPUID */
  register uint32 Id = NVIC_CPUID_R;
  const Hw_CoreInfoType *info = NULL;
  info = Hw_GetSupportedCoreInfo(Id);
  if ( info != NULL )
    return E_OK;
  else
    return E_NOT_OK;
}
