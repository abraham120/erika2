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

 /** @file   ee_tc27x_cstart.c
  *  @brief  The system startup code
  *
  *  The system startup code initializes the processor's registers
  *  and the application C variables.
  *  Has been created starting from cstart.c TASKING start-up code and has
  *  been custumed to compile with HIGHTEC GNUC compiler (v4.6.1.2) too.
  *  We used TASKING 4.0r1 as compiler and you can find the
  *  documentation pdf file for compiler at:
  *  http://www.tasking.com/support/tricore/tc_user_guide_v4.0.pdf
  *  In following comments, sometime, paragraph reference of this document
  *  are added. 
  *  For HIGHTEC documentation visit site: http://www.hightec-rt.com/
  *
  *  @author Errico Guidieri
  *  @date 2012
  */

#include <stdlib.h>

#include "ee.h"

/* Multicore ENDINIT Support */
#ifdef EE_MASTER_CPU
#define EE_WDTCPUCON0   SCU_WDTCPU0CON0
#define EE_WDTCPUCON1   SCU_WDTCPU0CON1
#elif (EE_CURRENTCPU == 1)
#define EE_WDTCPUCON0   SCU_WDTCPU1CON0
#define EE_WDTCPUCON1   SCU_WDTCPU1CON1
#elif (EE_CURRENTCPU == 2)
#define EE_WDTCPUCON0   SCU_WDTCPU2CON0
#define EE_WDTCPUCON1   SCU_WDTCPU2CON1
#else
#error Unknown CPU ID
#endif

/**************************************************************************
 *
 * FUNCTION:     endinit_set
 *
 * DESCRIPTION:  Sets or Clears the ENDINIT bit in the WDT_CON0 register
 *               in order to enabled or disable the write-protection for
 *               registers protected via the EndInit feature
 *               (ie. BTV, BIV, ISP, PCON0, DCON0).
 *
 *************************************************************************/
__INLINE__ void __ALWAYS_INLINE__  tc27x_endinit_set( EE_tc_endinit_t
  endinit_value )
{
  unsigned int wdt_con0;
  /*
   * 1st step: Password access (create password and send to WDT_CON0)
   */
  wdt_con0 = EE_WDTCPUCON0.U;

  wdt_con0 &= 0xFFFFFF01U;    /* clear WDTLCK, WDTHPW0, WDTHPW1 */
  wdt_con0 |= 0xF1U;          /* set WDTHPW1 to 0xF  1 must be written to
                                 ENDINIT for password access 
                                (but this will not actually modify the bit) */
  EE_WDTCPUCON0.U = wdt_con0;

  /*
   * 2nd step: Modify access, set the bit ENDINIT to 1 or 0 to allow access to
   *           registers: WDT_CON1, BTV, BIV, ISP and mod_CLC
   */
  wdt_con0 &= 0xFFFFFFF0U;            /* clear WDTHPW0, WDTLCK, ENDINIT  */
  /* WDTHPW0=0, WDTLCK=1, ENDINIT=endinit_value */
  wdt_con0 |= 0x02U | endinit_value;
  EE_tc_isync();
  EE_WDTCPUCON0.U = wdt_con0;

  EE_WDTCPUCON0.U;                  /* read is required */
}


extern void _exit ( int status );

/* Utility macros to set registers: */
#define tc27x_setareg2(areg,val) \
  { __asm volatile (" movh.a\t %%"#areg",hi:"#val"\n\tlea\t %%"#areg",\
  [%%"#areg"]lo:"#val"" : : : "memory"); }
#define tc27x_setareg(areg,val) tc27x_setareg2(areg,val)


__asm ("\t .weak _SMALL_DATA3_,_SMALL_DATA4_");

extern EE_UINT32  __USTACK[];      /* user stack end */
extern void *     _SMALL_DATA_;    /* centre of A0 addressable area */
extern void *     _SMALL_DATA2_;   /* centre of A1 addressable area */

extern void EE_tc_interrupt_table( void );   /* interrupt table from ERIKA */

/* passed to exit libc function */
extern int main( void );

/* start-up functions */
void tc27x_start( void );

/* This MUST be inline because you cannot make a real function call
   before initialize CSAs lists */
__INLINE__ void __ALWAYS_INLINE__ tc27x_csa_init( void );

/*******************************************************************************
 * _START() - Startup Code
 ******************************************************************************/
#pragma section ".startup_code" ax 4
void _RESET (void)
{
  __asm (".global _START");
  __asm (".word 0x00000000");
  __asm (".word 0xb3590070");
  __asm (".word 0x00000000");
  __asm (".word 0x00000000");
  __asm (".word 0x00000000");
  __asm (".word 0x00000000");
  __asm (".word 0x791eb864");
  __asm (".word 0x86e1479b");
  /* we must make a jump to cached segment, why trap_tab follow */
  __asm ("_START: ja tc27x_start");
}

/* we switch to normal region */
#pragma section

/*******************************************************************************
 * @brief startup code
 ******************************************************************************/
#define TC_START_PSW_ISP     0x00000980U

void tc27x_start( void )
{
  /* Load user stack pointer. First thing to do */
  EE_ADDR const sp = (EE_ADDR)((EE_UINT32)(__USTACK) & EE_STACK_ALIGN);
  EE_tc_set_SP(sp);

  /* Do a dsync before changing any of the csfr values, thus any previous
   * background state gets flushed first. Required for applications that jump
   * to the reset address.
   */
  EE_tc_dsync();

  /* clear PSW.IS */
  EE_tc_set_psw(TC_START_PSW_ISP);

  /* Set the PCXS and PCXO to its reset value in case of a warm start */
  EE_UREG pcxi = EE_tc_get_pcxi();
  pcxi &= 0xFFF00000U;
  EE_tc_set_pcxi(pcxi);

  /*
   * Clear the ENDINIT bit in the WDT_CON0 register in order
   * to disable the write-protection for registers protected
   * via the EndInit feature (for example: WDT_CON1).
   */
  tc27x_endinit_set(EE_TC_ENDINIT_DISABLE);

  /*
   * Disable the Watchdog if requested. Watchdog is enabled by default.
   * The Watchdog is disabled after ENDINIT is set by endinit_set().
   */
  EE_WDTCPUCON1.U |= 0x8;

  /*
   * Load Base Address of Interrupt Vector Table.
   * Disable this if not started from RESET vector. (E.g.
   * ROM monitors require to keep in control of vectors)
   */
  __mtcr(EE_CPU_REG_BIV, (EE_UINT32)EE_tc_interrupt_table);

  /*
   * PCON0 configuration.
   */
  __mtcr(EE_CPU_REG_PCON0, 0U);

  /*
   * DCON0 configuration.
   */
  __mtcr(EE_CPU_REG_DCON0, 0U);

  /*
   * Inititialize global address registers a0/a1 to support
   * __a0/__a1 storage qualifiers of the C compiler.
   */
  tc27x_setareg(a0, _SMALL_DATA_);

  tc27x_setareg(a1, _SMALL_DATA2_);

  /* Setup the context save area linked list. This MUST be inline because
     you cannot make a real function call before initialize CSAs lists */
  tc27x_csa_init();

  /*
   * Set the ENDINIT bit in the WDT_CON0 register again
   * to enable the write-protection.
   */
  tc27x_endinit_set(EE_TC_ENDINIT_ENABLE);

  /*
   * Call C main program.
   */
  _exit( main() );
}

/**************************************************************************
 *
 * FUNCTION:     EE_tc27x_csa_init
 *
 * DESCRIPTION: Setup the context save area linked list. This MUST be
 *              inline because you cannot make a real function call before
 *              initialize CSAs lists
 *
 *************************************************************************/
__INLINE__ void __ALWAYS_INLINE__ tc27x_csa_init( void )
{
  /* Context Save Area base */
  extern EE_CSA __CSA_BEGIN[];
  /* Context Save Area end  */
  extern EE_CSA __CSA_END[];

  /* Nr of CSAs in area 1      */
  EE_UINT32 const no_of_csas = __CSA_END - __CSA_BEGIN;
  /* Current CSA segment (I handle only one segment) */
  EE_UINT32 const pcxi_seg = (((EE_UINT32)__CSA_END >> 28U) & 0xFU) << 16U;
  /* for cycle index */
  EE_UINT32 i;
  /* Current CSA offset (I handle only one segment) */
  EE_UINT32 pcxi_o;
  /* Previous Context Pointer (CSA Link Word) */
  EE_UINT32 pcxi_val;
  /*  This variable hold the number of CSA that I have to leave free to
      handle FCD trap 3 are needed by this trap and 3 more are needed for
      potential nested asynchronus trap.
      To handle a trap 3 CSA are needed because class trap handler entry
      call TNI switch routine that call TNI sub-handler.
  */
  EE_UINT32 fcd_needed_csa = 6U;
  /* Current CSA pointer */
  EE_CSA * csa;

  /* IMPORTANT:
     I initialize the Free Context List in direct order.
     So I will end with a list that will grow toward smaller addresses.
   */
  for (i = 0U, pcxi_val = 0U; i < no_of_csas; ++i)
  {
    /* Get th current CSA pointer */
    csa = &__CSA_BEGIN[i];
    /* Store in current CSA previous pointer
       (null pointer in last CSA = first time!) */
    csa->next.reg = pcxi_val;
    /* Evaluate the CSA Segment Offset */
    pcxi_o = (((EE_UINT32)csa >> 6U) & 0xFFFFU);
    /* Compose pcxi_seg and pcxi_o in the pcxi_val to be stored in next CSA */
    pcxi_val = pcxi_seg | pcxi_o;

    /* Check if you have to populate LCX that point to the 'almost empty'
       position  */
    if (--fcd_needed_csa == 0U)
    {
      __mtcr(EE_CPU_REG_LCX, pcxi_val);
    }
  }
  /* Initialize the HEAD of Free Context List */
  EE_tc_set_fcx(pcxi_val);
}

