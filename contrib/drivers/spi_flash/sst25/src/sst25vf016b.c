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
* @file     sst25vf016b.c
* @brief    SPI flash sst25vf016b driver.
* @author   Bernardo Dal Seno
* @author   Dario Di Stefano
* @date     2010
*/ 

#ifdef __USE_SST25VF016B__

#include <ee.h>
#include "ee_spi_flash.h"

void sst25vf016b_flash_write_buffer(unsigned id, EE_UINT32 addr,
    const void *data, EE_UREG len)
{
    unsigned k;
    const EE_UINT8 *bdata = data;

    k = 0;
    if (len >= 2) {
        /* Fast write: due bytes at a time */
        spiflash_write_enable(id);
        spiflash_long_write(id, (SPI_FLASH_CMD_AAI << 8) | ((addr >> 16)&0xFF), 
                             (addr << 16) | ((EE_UINT32)bdata[0] << 8) | bdata[1], 6);
        spiflash_wait_until_ready(id);
        for (k = 2; k <= len-2; k+=2) {
            spiflash_short_write(id, (SPI_FLASH_CMD_AAI << 16)
                | ((EE_UINT32)bdata[k] << 8) | bdata[k+1], 3);
            spiflash_wait_until_ready(id);
        }
        spiflash_write_disable(id);    /* End the AAI sequence */
        spiflash_wait_until_ready(id);
    }
    /* An odd final byte must be written separately */
    if (k < len) {
        spiflash_write_enable(id);
        spiflash_long_write(id, SPI_FLASH_CMD_WR_BYTE, ((addr + k) << 8) | bdata[k], 5);
        spiflash_wait_until_ready(id);
    }
}

#endif
