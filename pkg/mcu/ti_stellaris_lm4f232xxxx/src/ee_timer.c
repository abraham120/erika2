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

/** @file	ee_timer.c
 *  @brief	Timer Driver source file.\n
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#include "mcu/ti_stellaris_lm4f232xxxx/inc/ee_mcuregs.h"
#include "mcu/ti_stellaris_lm4f232xxxx/inc/ee_timer.h"

#define	EE_TIMER_ID_MAX		EE_TIMER_5

#define	EE_TIMER_A_S	0x00000010
#define	EE_TIMER_B_S	0x00000018
#define	EE_TIMER_BOTH_S	EE_TIMER_A_S

#define	EE_TIMER_ID_MASK	0x0000000F

#define	EE_TIMER_HW_MASK	0x00000001

#define	TIMER0_BASE_ADDR	0x40030000
#define	TIMER1_BASE_ADDR	0x40031000
#define	TIMER2_BASE_ADDR	0x40032000
#define	TIMER3_BASE_ADDR	0x40033000
#define	TIMER4_BASE_ADDR	0x40034000
#define	TIMER5_BASE_ADDR	0x40035000

const EE_UREG EE_Timer_Base_Addr[] = {
  TIMER0_BASE_ADDR,
  TIMER1_BASE_ADDR,
  TIMER2_BASE_ADDR,
  TIMER3_BASE_ADDR,
  TIMER4_BASE_ADDR,
  TIMER5_BASE_ADDR
};

#define	WTIMER0_BASE_ADDR	0x40036000
#define	WTIMER1_BASE_ADDR	0x40037000
#define	WTIMER2_BASE_ADDR	0x4004C000
#define	WTIMER3_BASE_ADDR	0x4004D000
#define	WTIMER4_BASE_ADDR	0x4004E000
#define	WTIMER5_BASE_ADDR	0x4004F000

const EE_UREG EE_Timer_Wide_Base_Addr[] = {
  WTIMER0_BASE_ADDR,
  WTIMER1_BASE_ADDR,
  WTIMER2_BASE_ADDR,
  WTIMER3_BASE_ADDR,
  WTIMER4_BASE_ADDR,
  WTIMER5_BASE_ADDR
};

#define	EE_TIMER_CFG_OFS	0x00000000	/* Configuration Register     */
#define	EE_TIMER_TAM_OFS	0x00000004	/* Timer A Mode Register      */
#define	EE_TIMER_TBM_OFS	0x00000008	/* Timer B Mode Register      */
#define	EE_TIMER_CTL_OFS	0x0000000C	/* Control Register	      */

#define	EE_TIMER_IMR_OFS	0x00000018	/* Interrupt Mask Register    */
#define	EE_TIMER_RIS_OFS	0x0000001C	/* Raw Interrupt Status	      */
#define	EE_TIMER_MIS_OFS	0x00000020	/* Masked Interrupt Status    */
#define	EE_TIMER_ICR_OFS	0x00000024	/* Interrupt Clear Register   */

#define	EE_TIMER_TAILR_OFS	0x00000028	/* Timer A Interval Load      */
#define	EE_TIMER_TBILR_OFS	0x0000002C	/* Timer B Interval Load      */

#define	EE_TIMER_TAR_OFS	0x00000048	/* Timer A Register	      */
#define	EE_TIMER_TBR_OFS	0x0000004C	/* Timer B Register	      */

#define	EE_TIMER_CFG_MASK	0x0000000F	/* Configuration Mask	      */

/*
 * Timer Initialization.
 */
EE_TimerErr EE_timer_init(EE_TimerId id, EE_TimerCfg cfg)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Enable Hardware Module Clock Gating Control */
    SYSCTL_RCGCWTIMER_R |= hwmodmask;

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];

  }
  else {

    /* Enable Hardware Module Clock Gating Control */
    SYSCTL_RCGCTIMER_R |= hwmodmask;

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }

  if (!ret) {

    /* Disable Timer/s before programming. */
    EE_HWREG(hwmodba + EE_TIMER_CTL_OFS) &= ~( 
      TIMER_CTL_TAEN | TIMER_CTL_TBEN
    );

    /* Timer Module Configuration Setup */
    EE_HWREG(hwmodba + EE_TIMER_CFG_OFS) = ( cfg & EE_TIMER_CFG_MASK );

    /* Timer A Mode Setup */
    EE_HWREG(hwmodba + EE_TIMER_TAM_OFS) = ( 
      (cfg & EE_TIMER_A) >> EE_TIMER_A_S 
    );

    /* Timer B Mode Setup */
    EE_HWREG(hwmodba + EE_TIMER_TBM_OFS) = ( 
      (cfg & EE_TIMER_B) >> EE_TIMER_B_S
    );

    /* Enable Stall in Debugging Mode */
#ifdef	DEBUG
    EE_HWREG(hwmodba + EE_TIMER_CTL_OFS) |= (
      TIMER_CTL_TASTALL | TIMER_CTL_TBSTALL
    );
#endif

  }

  return ret;
}

/*
 * Timer De-Initialization.
 */
EE_TimerErr EE_timer_deinit(EE_TimerId id)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Disable Hardware Module Clock Gating Control */
      SYSCTL_RCGCWTIMER_R &= ~hwmodmask;

    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Disable Hardware Module Clock Gating Control */
    SYSCTL_RCGCTIMER_R &= ~hwmodmask;

  }
  else ret = EE_TIMER_ERR_INIT;

  return ret;
}

/*
 * Start Timer
 */
EE_TimerErr EE_timer_start(EE_TimerId id)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Start Timer/s. */
    EE_HWREG(hwmodba + EE_TIMER_CTL_OFS) |= (
      ( id >> EE_TIMER_BOTH_S ) & ( TIMER_CTL_TAEN | TIMER_CTL_TBEN )
    );

  }

  return ret;
}

/*
 * Stop Timer
 */
EE_TimerErr EE_timer_stop(EE_TimerId id)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Stop Timer/s. */
    EE_HWREG(hwmodba + EE_TIMER_CTL_OFS) &= ~(
      ( id >> EE_TIMER_BOTH_S ) & ( TIMER_CTL_TAEN | TIMER_CTL_TBEN )
    );

  }

  return ret;
}

/*
 * Timer Enable Interrupt
 */
EE_TimerErr EE_timer_enable_int(EE_TimerId id)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Stop Timer/s. */
    EE_HWREG(hwmodba + EE_TIMER_IMR_OFS) |= (
	( id >> EE_TIMER_BOTH_S ) & ( TIMER_IMR_TATOIM | TIMER_IMR_TBTOIM )
    );

  }

  return ret;
}

/*
 * Timer Disable Interrupt
 */
EE_TimerErr EE_timer_disable_int(EE_TimerId id)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Stop Timer/s. */
    EE_HWREG(hwmodba + EE_TIMER_IMR_OFS) &= ~(
	( id >> EE_TIMER_BOTH_S ) & ( TIMER_IMR_TATOIM | TIMER_IMR_TBTOIM )
    );

  }

  return ret;
}

/*
 * Timer Clear Interrupt
 */
EE_TimerErr EE_timer_clear_int(EE_TimerId id)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Stop Timer/s. */
    EE_HWREG(hwmodba + EE_TIMER_ICR_OFS) |= (
	( id >> EE_TIMER_BOTH_S ) & ( TIMER_ICR_TATOCINT | TIMER_ICR_TBTOCINT )
    );

  }

  return ret;
}

/*
 * Timer Set Period.
 */
EE_TimerErr EE_timer_set_period(EE_TimerId id, EE_UREG period)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Set Timer A period if requested. */
    if (id & EE_TIMER_A) {

      EE_HWREG(hwmodba + EE_TIMER_TAILR_OFS) = period;

    }

    /* Set Timer B period if requested. */
    if (id & EE_TIMER_B) {

      EE_HWREG(hwmodba + EE_TIMER_TBILR_OFS) = period;

    }

  }

  return ret;
}

/*
 * Timer Get Period.
 */
EE_TimerErr EE_timer_get_period(EE_TimerId id, EE_UREG *period)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Get Timer A period if requested. */
    if (id & EE_TIMER_A) {

      (*period) = EE_HWREG(hwmodba + EE_TIMER_TAILR_OFS);

    }

    /* Get Timer B period if requested. */
    else if (id & EE_TIMER_B) {

      (*period) = EE_HWREG(hwmodba + EE_TIMER_TBILR_OFS);

    }

  }

  return ret;
}

/*
 * Timer Get Value.
 */
EE_TimerErr EE_timer_get_value(EE_TimerId id, EE_UREG *value)
{
  register EE_TimerErr	ret = EE_TIMER_ERR_NONE;
  register EE_UREG	hwmodid = id & EE_TIMER_ID_MASK;
  register EE_UREG	hwmodmask = (((EE_UREG)EE_TIMER_HW_MASK) << hwmodid);
  register EE_UREG	hwmodba;

  /* Hardware Module Identifier Validation */
  if ( hwmodid > EE_TIMER_ID_MAX ) ret = EE_TIMER_ERR_ID;

  /* Wide Timer Module Check */
  else if ( id & EE_TIMER_WIDE ) {

    /* Hardware Module Clock Gating Control Check*/
    if ( SYSCTL_RCGCWTIMER_R & hwmodmask ) {

      /* Harware Module Base Address Retrieval. */
      hwmodba = EE_Timer_Wide_Base_Addr[hwmodid];
  
    }
    else ret = EE_TIMER_ERR_INIT;

  }

  /* Hardware Module Clock Gating Control Check*/
  else if ( SYSCTL_RCGCTIMER_R & hwmodmask ) {

    /* Harware Module Base Address Retrieval. */
    hwmodba = EE_Timer_Base_Addr[hwmodid];

  }
  else ret = EE_TIMER_ERR_INIT;

  if (!ret) {

    /* Get Timer A period if requested. */
    if (id & EE_TIMER_A) {

      (*value) = EE_HWREG(hwmodba + EE_TIMER_TAR_OFS);

    }

    /* Get Timer B period if requested. */
    else if (id & EE_TIMER_B) {

      (*value) = EE_HWREG(hwmodba + EE_TIMER_TBR_OFS);

    }

  }

  return ret;
}

