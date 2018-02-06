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

/**

*/

#include "ee_internal.h"

void EE_rh850_clock_init(void)
{
	/* Prepare MainOsc */
  MOSCC=GAIN;                                     /* Set MainOSC gain  */
  MOSCST=0xFFFF;                                  /* Set MainOSC stabilization time to max (8,19 ms) */
  protected_write(PROTCMD0,PROTS0,MOSCE,0x01u);   /* Trigger Enable (protected write) */
  while ((MOSCS&0x04u) != 0x04u);                 /* Wait for active MainOSC */

  if((PLLS&0x04u) != 0x04u)                       /* Check if PLL needs to be started */
  {
    /* Prepare PLL */
    PLLC=PllcValue;                             /* 80MHz PLL */
    protected_write(PROTCMD1,PROTS1,PLLE,0x01u);  /* Enable PLL */
    while((PLLS&0x04u) != 0x04u){}                /* Wait for active PLL */
  }
  
  /* CPU Clock divider = PLL0/1 */
  protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKD_CTL,0x01u);
  while(CKSC_CPUCLKD_ACT!=0x01u);

  /* PLL0 -> CPU Clock */ 
  protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKS_CTL,0x03u);
  while(CKSC_CPUCLKS_ACT!=0x03u);
  
  /* Set Peripheral CLK2 to 40 MHZ (PPLL2) */
  protected_write(PROTCMD1,PROTS1,CKSC_IPERI2S_CTL,0x02u);
  while(CKSC_IPERI2S_ACT!=0x02u);
}