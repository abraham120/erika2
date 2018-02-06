/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: ee_mcuregs.h,v 1.3 2005/03/10 10:00:01 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_cpu.h"

#ifndef __INCLUDE_MCU_UNIBO_MPARM_MCUREGS__
#define __INCLUDE_MCU_UNIBO_MPARM_MCUREGS__

/*************************************************************************
Platform memory mappings (Constants)
 *************************************************************************/

// Private memories
#define PRIVATE_BASE       0x00000000
#define PRIVATE_SPACING    0x01000000   // 16 MB
#define PRIVATE_SIZE       0x00c00000   // 12 MB
// Instruction cache memories
// Please notice: they must reside in "low" memory because they must be
// accessible by jumps with compact offset
#define ISCRATCH_BASE      0x00c00000   // 12 MB
// Shared memories
#define SHARED_BASE        0x19000000
#define SHARED_SPACING     0x00100000   // 1 MB
#define SHARED_SIZE        0x00100000   // 1 MB
// Semaphore memories
#define SEMAPHORE_BASE     0x20000000
#define SEMAPHORE_SPACING  0x00004000   // 16 kB
#define SEMAPHORE_SIZE     0x00004000   // 16 kB
// Interrupt slaves
#define INTERRUPT_BASE     0x21000000
#define INTERRUPT_SPACING  0x00000150   // 336 B
#define INTERRUPT_SIZE     0x00000150   // 336 B
// Core-associated slaves and scratchpad memories
#define CORESLAVE_BASE     0x22000000
#define CORESLAVE_SPACING  0x00020000   // 128 kB
#define CORESLAVE_SIZE     0x00015000   //  84 kB
// FFT devices
#define FFT_BASE           0x23000000
#define FFT_SPACING        0x00000010   //  16 B
#define FFT_SIZE           0x00000010   //  16 B
// Storage slaves
#define STORAGE_BASE       0x24000000
#define STORAGE_SPACING    0x02000000   // 32 MB
#define STORAGE_SIZE       0x02000000   // 32 MB
// Frequency scaling devices
#define FREQ_BASE          0x50000000
#define FREQ_SPACING       0x00000200   // 512 B
#define FREQ_SIZE          0x00000200   // 512 B
// DMA devices
#define INTERNAL_DMA_BASE  0x60000000
#define INTERNAL_MAX_OBJ            9  // Maximum number of objects managed by the dma
#define INTERNAL_DIM_BURST          4  // Length of a burst transfer made by the dma
#define INTERNAL_DMA_SIZE  (7*4*INTERNAL_MAX_OBJ+4)
// "Smart" (DMA-paired) memories
#define SMARTMEM_MAX_CONF           1
#define SMARTMEM_BASE      0x70000000
#define SMARTMEM_SPACING   0x02000000   // 32 MB 
#define SMARTMEM_MAX_OBJ            4   // Maximum number of objects managed by the dma
#define SMARTMEM_DIM_BURST          8   // Length of a burst transfer made by the dma
// DRAM-associated DMA
#define DRAMDMA_BASE       0x75000000
#define DRAMDMA_SPACING    0x00100000   // 1 MB 
#define DRAMDMA_MAX_OBJ             4   // Maximum number of objects managed by the dma
#define DRAM_BASE          0x76000000
#define DRAM_SIZE          0x00800000   // 8MB (8MB, 16MB, 32MB, 64MB allowed)
// Simulation support
#define SIMSUPPORT_BASE    0x7f000000
#define SIMSUPPORT_SIZE    0x00100000   // 1 MB
// LX private memories
#define PRIVATE_LX_BASE    0x08000000                               
#define PRIVATE_LX_SPACING 0x01000000   // 16 MB
#define PRIVATE_LX_SIZE    0x01000000   // 16 MB
// Internal devices
#define INTERNAL_BASE      0x90000000



/* Interrupt Controller */
#define INTPND ((volatile EE_ADDR)(0x90050000)) /* R/W Interrupt pending register */
#define INTMSK ((volatile EE_ADDR)(0x90050004)) /* R/W Interrupt mask register */
#define INTMOD ((volatile EE_ADDR)(0x90050008)) /* R/W Interrupt mode register (level for FIQ/IRQ distinguisher) */

/* Timers */
#define SWARM_TIMER_INTEN	((volatile EE_ADDR)(0x9000001C))
#define SWARM_TIMER_MATCH0	((volatile EE_ADDR)(0x90000000))	// modified by Francesco Esposito
#define SWARM_TIMER_MATCH1	((volatile EE_ADDR)(0x90000004))	// modified by Francesco Esposito
#define SWARM_TIMER_MATCH2	((volatile EE_ADDR)(0x90000008))	// modified by Francesco Esposito
#define SWARM_TIMER_MATCH3	((volatile EE_ADDR)(0x9000000c))	// modified by Francesco Esposito
#define SWARM_TIMER_CNT		((volatile EE_ADDR)(0x90000010))	// modified by Francesco Esposito
#define SWARM_TIMER_STATUS  	((volatile EE_ADDR)(0x90000014))	// modified by Francesco Esposito
#define SWARM_TIMER_WDOG    	((volatile EE_ADDR)(0x90000018))	// modified by Francesco Esposito

#endif
