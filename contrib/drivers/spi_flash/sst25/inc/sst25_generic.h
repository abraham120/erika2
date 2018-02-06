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
* @file     sst25_generic.h
* @brief    SPI flash driver. Generic functions.
* @author   Bernardo Dal Seno
* @author   Dario Di Stefano
* @date     2010
*/ 

#ifndef SPI_FLASH_SST25_GENERIC_H
#define SPI_FLASH_SST25_GENERIC_H

#define SPI_FLASH_BUSY_MASK       1
#define SPI_FLASH_WEL_MASK        2
#define SPI_FLASH_BP0_MASK        4
#define SPI_FLASH_BP1_MASK        8
#define SPI_FLASH_BP2_MASK        16
#define SPI_FLASH_BP3_MASK        32
#define SPI_FLASH_AAI_MASK        64
#define SPI_FLASH_BPL_MASK        128

/* Default macros like SST25VF016B */
#ifndef SPI_FLASH_CMD_WR_BYTE
#define SPI_FLASH_CMD_WR_BYTE      0x02
#endif
#ifndef SPI_FLASH_CMD_AAI
#define SPI_FLASH_CMD_AAI          0xAD
#endif
#ifndef SPI_FLASH_CMD_WRITE_EN
#define SPI_FLASH_CMD_WRITE_EN     0x06
#endif
#ifndef SPI_FLASH_CMD_WRITE_DIS
#define SPI_FLASH_CMD_WRITE_DIS    0x04
#endif
#ifndef SPI_FLASH_CMD_GET_ID
#define SPI_FLASH_CMD_GET_ID       0x90
#endif
#ifndef SPI_FLASH_CMD_EN_WR_SR
#define SPI_FLASH_CMD_EN_WR_SR     0x50
#endif
#ifndef SPI_FLASH_CMD_WR_SR
#define SPI_FLASH_CMD_WR_SR        0x01
#endif
#ifndef SPI_FLASH_CMD_RD_SR
#define SPI_FLASH_CMD_RD_SR        0x05
#endif
#ifndef SPI_FLASH_CMD_CHIP_ERASE
#define SPI_FLASH_CMD_CHIP_ERASE   0x60
#endif
#ifndef SPI_FLASH_CMD_4K_ERASE
#define SPI_FLASH_CMD_4K_ERASE     0x20
#endif
#ifndef SPI_FLASH_CMD_32K_ERASE
#define SPI_FLASH_CMD_32K_ERASE    0x52
#endif
#ifndef SPI_FLASH_BP_MASK
#define SPI_FLASH_BP_MASK         (SPI_FLASH_BP0_MASK|SPI_FLASH_BP1_MASK|SPI_FLASH_BP2_MASK|SPI_FLASH_BP3_MASK)
#endif
#ifndef spiflash_write_buffer
#define spiflash_write_buffer    sst25_generic_flash_write_buffer
void sst25_generic_flash_write_buffer(unsigned id, EE_UINT32 addr,
    const void *data, EE_UREG len);
#endif

#define SPI_FLASH_SECTOR_SIZE   (4U * 1024U)
#define SPI_FLASH_BLOCK_SIZE    (32U * 1024U)
#define SPI_FLASH_CMD_SECTOR_ERASE      SPI_FLASH_CMD_4K_ERASE
#define SPI_FLASH_CMD_BLOCK_ERASE       SPI_FLASH_CMD_32K_ERASE

#include "spi_flash_generic.h"

#endif /* SPI_FLASH_SST25_GENERIC_H */
