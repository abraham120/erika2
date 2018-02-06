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
* @file     spi_flash_mico32.h
* @brief    SPI flash driver. Mico32 functions.
* @author   Bernardo Dal Seno
* @author   Dario Di Stefano
* @date     2010
*/ 

#ifndef SPI_FLASH_MICO32_H
#define SPI_FLASH_MICO32_H

#include <ee.h>
/* Platform configuration */
#include <system_conf.h>
#include <MicoSPIFlash.h>

struct spi_flash_cmd {
    volatile unsigned int cmd0;    /* left aligned */
    volatile unsigned int cmd1;    /* if cmd_len > 4; msb of cmd, right aligned */
    volatile unsigned int cmd_len; /* Length: 1-8 */
    volatile unsigned int ret_len; /* Length: 0-4 */
    volatile unsigned int ret;
    volatile unsigned int do_cmd;
};

/**
 * @brief SPI-flash driver function for Mico32 to write max 4 bytes. 
 *
 * The function can be used to write bytes to memory location within the SPI flash. 
 * @param crl_base Base address of the controller of the SPI-Flash.
 * @param data Data to be written.
 * @param len Number of bytes to be written.  
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_short_write(unsigned ctrl_base, EE_UINT32 data, EE_UREG len)
{
    struct spi_flash_cmd * const cmd_ctrl =
        (struct spi_flash_cmd *)(ctrl_base + 0x40);
    cmd_ctrl->cmd0 = data << (8 * (4 - len));
    cmd_ctrl->cmd_len = len;
    cmd_ctrl->ret_len = 0;
    cmd_ctrl->do_cmd = 1;
}

/**
 * @brief SPI-flash driver function for Mico32 to write max 8 bytes. 
 *
 * The function can be used to write bytes to memory location within the SPI flash. 
 * @param crl_base Base address of the controller of the SPI-Flash.
 * @param data1 MSW of data to be written.
 * @param data2 LSW of data to be written.
 * @param len Number of bytes to be written.  
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_long_write(unsigned ctrl_base, EE_UINT32 data1, EE_UINT32 data2, EE_UREG len)
{
    struct spi_flash_cmd * const cmd_ctrl =
        (struct spi_flash_cmd *)(ctrl_base + 0x40);
    cmd_ctrl->cmd0 = data2;
    cmd_ctrl->cmd1 = data1;
    cmd_ctrl->cmd_len = len;
    cmd_ctrl->ret_len = 0;
    cmd_ctrl->do_cmd = 1;
}

/**
 * @brief SPI-flash driver function for Mico32 to write max 8 bytes. 
 *
 * The function can be used to write bytes to memory location within the SPI flash. 
 * @param crl_base Base address of the controller of the SPI-Flash.
 * @param data Array of data to be written.
 * @param len Number of bytes to be written.  
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_write(unsigned ctrl_base, const void *data, unsigned len)
{
    const EE_UINT8 *buf = data;
    EE_UINT32 data1, data2;
    unsigned l;
    data1 = buf[0];
    for (l = 1; l < len && l < 4; ++l)
        data1 = (data1 << 8) | buf[l];
    if (len > 4) {
        data2 = buf[4];
        for (l = 5; l < len && l < 8; ++l)
            data2 = (data2 << 8) | buf[l];
        spiflash_long_write(ctrl_base, data1, data2, len);
    } else {
        spiflash_short_write(ctrl_base, data1, len);
    }
}

#endif /* SPI_FLASH_MICO32_H */
