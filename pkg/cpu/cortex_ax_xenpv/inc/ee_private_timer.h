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
 * Author: 2013 Bruno Morelli
 */

#ifndef EE_PRIVATE_TIMER_H__
#define EE_PRIVATE_TIMER_H__

#include "cpu/cortex_ax_xenpv/inc/ee_cax_utils.h"

#define EE_PRIVATE_TIMER_BASE              (EE_ARM_PERIPHBASE + 0x0600)
#define EE_PRIVATE_TIMER_LOAD_REG          (EE_PRIVATE_TIMER_BASE + 0x00)
#define EE_PRIVATE_TIMER_COUNTER_REG       (EE_PRIVATE_TIMER_BASE + 0x04)
#define EE_PRIVATE_TIMER_CTRL_REG          (EE_PRIVATE_TIMER_BASE + 0x08)
#define EE_PRIVATE_TIMER_INTSTATUS_REG     (EE_PRIVATE_TIMER_BASE + 0x0C)

#define EE_PRIVATE_TIMER_CTRL_EN_MASK      (1U << 0)
#define EE_PRIVATE_TIMER_CTRL_PRE_MASK     (0xFFU << 8)

/* modes */
#define EE_PRIVATE_TIMER_MODES_MASK        (0x03U << 1)
#define EE_PRIVATE_TIMER_INT               (1U << 2)
#define EE_PRIVATE_TIMER_AUTORELOAD        (1U << 1)


/*
 * TODO: handle of Private Timer Interrupt Status Register
 */

__INLINE__ void __ALWAYS_INLINE__ EE_private_timer_enable(EE_UINT32 mode)
{
  /* writel(0x01U, EE_PRIVATE_TIMER_INTSTATUS_REG); */
  EE_UINT32 mask = (EE_PRIVATE_TIMER_MODES_MASK
                    | EE_PRIVATE_TIMER_CTRL_EN_MASK);
  EE_UINT32 reg = (readl(EE_PRIVATE_TIMER_CTRL_REG)) & ~mask;
  reg |= ((mode | 1U) & mask);
  writel(reg, EE_PRIVATE_TIMER_CTRL_REG);
}

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_private_timer_get_counter(void)
{
	return readl(EE_PRIVATE_TIMER_COUNTER_REG);
}
__INLINE__ void __ALWAYS_INLINE__ EE_private_timer_disable(void)
{
  writel((readl(EE_PRIVATE_TIMER_CTRL_REG) & ~EE_PRIVATE_TIMER_CTRL_EN_MASK),
         EE_PRIVATE_TIMER_CTRL_REG);
}

__INLINE__ void __ALWAYS_INLINE__ EE_private_timer_set_prescaler(EE_UINT32 pre)
{
/*
 * timer interval = ((prescaler + 1) * (load val + 1)) / periph_clk
 */
	EE_UINT32 reg = (pre << 8) & EE_PRIVATE_TIMER_CTRL_PRE_MASK;
	reg = reg | (readl(EE_PRIVATE_TIMER_CTRL_REG) & ~EE_PRIVATE_TIMER_CTRL_PRE_MASK);
	writel(reg, EE_PRIVATE_TIMER_CTRL_REG);
}

__INLINE__ void __ALWAYS_INLINE__ EE_private_timer_set_load(EE_UINT32 load)
{
	writel(load, EE_PRIVATE_TIMER_LOAD_REG);
}

#endif /* EE_PRIVATE_TIMER_H__ */
