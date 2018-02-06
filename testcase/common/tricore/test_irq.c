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
 * IRQ functions used in test cases for TriCore 1.6.1
 * Author: 2012 Errico Guidieri
 */

#include <ee_irq.h>
#include "../test_common.h"

typedef volatile Ifx_SRC_SRCR *p_SRC_reg;

static p_SRC_reg test_get_irq_register(unsigned int irq) {
  switch(irq) {
    case 3:
      return &SRC_GPSR03;
    case 2:
      return &SRC_GPSR02;
    case 1:
      return &SRC_GPSR01;
    case 0:
    default:
      return &SRC_GPSR00;
  }
}

/* Setup an IRQ source */
void test_setup_irq(unsigned int irq, SoftIRQHandler handler,
    unsigned int priority) {
  register p_SRC_reg p_src_reg = test_get_irq_register(irq);
  p_src_reg->U = (1U << 10U) | priority;
  EE_tc_dsync();
}

void test_fire_irq(unsigned int irq)
{
  /* Workaround to assure IRQ generation ( I don't know why but
     sometimes dsync followed by isync is not enough ) */
  volatile EE_UINT32 intsource;
  register p_SRC_reg p_src_reg = test_get_irq_register(irq);
  p_src_reg->U |= (1U << 26U);
  EE_tc_dsync();
  intsource = p_src_reg->U;
  EE_tc_isync();
}

