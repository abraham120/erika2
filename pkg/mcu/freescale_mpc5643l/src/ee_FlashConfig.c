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
 * MPC5643L Flash Configuration Source File
 *         2012 Francesco Esposito
 */

#include "mcu/freescale_mpc5643l/inc/ee_FlashConfig.h"

const unsigned int mem_write_code [] = {
#if defined (__VLE__)
        /* for processors which support VLE only or for 'VLE on' option
         * 1) stw r3,(0)r4 machine code: writes r3 contents to addr
         * in r4 then se_nop
         * 2) mbar machine code: ensure prior store completed
         * 2) blr machine code: branches to return address in link register
         */
        0xD0344400,
        0x7C0006AC,
        0x44000004 
#else
        /*
         * stw r3,(0)r4 machine code: writes r3 contents to addr in r4
         * mbar machine code: ensure prior store completed
         * blr machine code: branches to return address in link register
         */
        0x90640000,
        0x7C0006AC,
        0x4E800020
#endif // __option(vle)
        };

void FlashConfig(void)
{
    typedef void (*mem_write_code_ptr_t)(unsigned int, unsigned int);

    /*
     * cast mem_write_code as func ptr
     * de-references func ptr, i.e. converts to func
     * which passes integer (in r3)
     */
    (*((mem_write_code_ptr_t)mem_write_code))
    (FLASH_DATA,
    (unsigned int)&FLASH_REG);
}


