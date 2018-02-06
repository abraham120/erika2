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

/**
	@file ee_mcuregs.h
	@brief MCU memory mapped registers.
	@author Gianluca Franchino
	@date 2012
 */

#ifndef	__INCLUDE_RENESAS_R5F5210X_MCUREGS_H__
#define	__INCLUDE_RENESAS_R5F5210X_MCUREGS_H__


#if 1

#include "iodefine.h"

#else

#include "cpu/rx210/inc/ee_cpu.h"
#define	CAC	EE_HWREG8(0x8B000)
/*TODO: Put the others register here */


#endif /* #if 1*/

#define SYS_RESC_POR	0x0001U	/**< Power-On Reset */
#define SYS_RESC_LVD0	0x0002U	/**< Voltage Monitoring 0 Reset */
#define SYS_RESC_LVD1	0x0004U	/**< Voltage Monitoring 0 Reset */
#define SYS_RESC_LVD2	0x0008U	/**< Voltage Monitoring 0 Reset */
#define SYS_RESC_IWDT	0x0010U	/**< Independent Watchdog Reset */
#define SYS_RESC_WDT	0x0020U	/**< Watchdog Reset */
#define SYS_RESC_SW	0x0040U	/**< Software Reset */
#define SYS_RESC_DSS	0x0080U	/**< Deep Software Stand-by Reset */
#define SYS_RESC_CWS	0x0100U	/**< Cold (0) / Warm (1) Start Determination */
#define SYS_RESC_EXT	0x0200U	/**< External Reset */

#endif	/* __INCLUDE_RENESAS_R5F5210X_MCUREGS_H__ */
