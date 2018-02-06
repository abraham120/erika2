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
 * Erika Enterprise - BOARD Driver - Atmel STK600 Implementation File.
 *
 * Author: 2013,  Giuseppe Serano
 */

/* ERIKA Enterprise Internals */
#include "ee_internal.h"

#ifdef	__BOARD_EXTENDED_STATUS__
#define	EE_BOARD_STAT_UNINIT	0x00U
#define	EE_BOARD_STAT_INIT	0x01U
#ifdef	DEBUG
static volatile EE_UREG
#else
static EE_UREG
#endif
EE_Board_Init_Status = EE_BOARD_STAT_UNINIT;
#endif	/* __BOARD_EXTENDED_STATUS__ */

/*
 * EE_Board_Init() Implementation.
 */
#ifdef	__BOARD_EXTENDED_STATUS__
EE_TYPERET
#else
void
#endif
EE_Board_Init(
  EE_TYPEBOARDFLAGS	Flags
)
{

#ifdef	DEBUG
  volatile EE_UREG	flags;
#else
  register EE_UREG	flags;
#endif

#ifdef	__BOARD_EXTENDED_STATUS__

  /* Flags Validation. */
  EE_STK600_VALIDATE_W_RV(
    ( Flags == EE_BOARD_FLAG_DEFAULT ),
    E_BOARD_PARAM_FLAGS
  );

#endif	/* __BOARD_EXTENDED_STATUS__ */

  /* Suspend IRQs */
  flags = EE_hal_suspendIRQ();

#ifdef	__BOARD_EXTENDED_STATUS__

  /* Board Initialization Validation. */
  EE_STK600_VALIDATE_IRQ_W_RV(
    ( EE_Board_Init_Status == EE_BOARD_STAT_UNINIT ),
    E_NOT_OK,
    flags
  );

  EE_Board_Init_Status == EE_BOARD_STAT_INIT;

#endif	/* __BOARD_EXTENDED_STATUS__ */

  /* Resume IRQs */
  EE_hal_resumeIRQ(flags);

#ifdef	__BOARD_EXTENDED_STATUS__
  return E_OK;
#endif

}


/*
 * EE_Board_DeInit() Implementation.
 */
#ifdef	__BOARD_EXTENDED_STATUS__
EE_TYPERET
#else
void
#endif
EE_Board_DeInit(
  EE_TYPEBOARDFLAGS	Flags
)
{

#ifdef	DEBUG
  volatile EE_UREG	flags;
#else
  register EE_UREG	flags;
#endif

#ifdef	__BOARD_EXTENDED_STATUS__

  /* Flags Validation. */
  EE_STK600_VALIDATE_W_RV(
    ( Flags == EE_BOARD_FLAG_DEFAULT ),
    E_BOARD_PARAM_FLAGS
  );

#endif	/* __BOARD_EXTENDED_STATUS__ */

  /* Suspend IRQs */
  flags = EE_hal_suspendIRQ();

#ifdef	__BOARD_EXTENDED_STATUS__

  /* Board De-Initialization Validation. */
  EE_STK600_VALIDATE_IRQ_W_RV(
    ( EE_Board_Init_Status == EE_BOARD_STAT_INIT ),
    E_NOT_OK,
    flags
  );

  EE_Board_Init_Status == EE_BOARD_STAT_UNINIT;

#endif	/* __BOARD_EXTENDED_STATUS__ */

  /* Resume IRQs */
  EE_hal_resumeIRQ(flags);

#ifdef	__BOARD_EXTENDED_STATUS__
  return E_OK;
#endif

}

