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
* @file     spi_flash_generic.h
* @brief    SPI flash driver. Generic functions.
* @author   Bernardo Dal Seno
* @author   Dario Di Stefano
* @author   Salvatore Marrapese
* @date     2010
*/ 

#ifndef SPI_FLASH_GENERIC_H
#define SPI_FLASH_GENERIC_H

#ifdef __LM32__
#include "spi_flash_mico32.h"
#endif

/* ========================= Flash library ========================== */
/**
 * Function to read the busy bit of the status register of the SPI-Flash memory
 */
__INLINE__ int __ALWAYS_INLINE__ spiflash_is_busy(EE_UINT8 status)
{
    return (status & SPI_FLASH_BUSY_MASK) ? 1 : 0;
}

/**
 * Function to read the protection bit of the status register of the SPI-Flash memory
 */
__INLINE__ int __ALWAYS_INLINE__ spiflash_is_protected(EE_UINT8 status)
{
    return (status & SPI_FLASH_BP_MASK) ? 1 : 0;
}

/**
 * Function to return the unprotected status of the SPI-Flash memory
 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ spiflash_unprotected_status(EE_UINT8 status)
{
    return status & ~(SPI_FLASH_BP_MASK|SPI_FLASH_BPL_MASK);
}

/**
 * Function to get the status register of the SPI-Flash memory
 */
__INLINE__ EE_UINT8 __ALWAYS_INLINE__ spiflash_get_status_reg(unsigned id)
{
	#ifdef __USE_DIAMOND__
	EE_UINT32 temp;
	MICO_SPI_STATUS_READ(id, temp);
	return temp;
	#else
	return SPI_CMD_STATUS_READ(id);
	#endif
}

/**
 * Function to wait until SPI-Flash memory is ready
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_wait_until_ready(unsigned id)
{
    EE_UINT8 s;
    do {
        s = spiflash_get_status_reg(id);
    } while(spiflash_is_busy(s));
}

/**
 * Function to write the status register of the SPI-Flash memory
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_write_status(unsigned id, EE_UINT8 status)
{
    EE_UINT8 cmd_wr_sr[] = { SPI_FLASH_CMD_WR_SR, status};                /* Write-Status-Register */
    spiflash_write(id, cmd_wr_sr, sizeof(cmd_wr_sr));
}

/**
 * Function to change the status register of the SPI-Flash memory
 * to unprotected
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_maybe_unprotect(unsigned id)
{
    const EE_UINT8 cmd_e_w_sr[] = { SPI_FLASH_CMD_EN_WR_SR };       /* Enable-Write-Status-Register */
    EE_UINT8 sr = spiflash_get_status_reg(id);
    if (spiflash_is_protected(sr)) {
        spiflash_write(id, cmd_e_w_sr, sizeof(cmd_e_w_sr));
        spiflash_write_status(id, spiflash_unprotected_status(sr));
    }
}

/**
 * Function to enable write
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_write_enable(unsigned id)
{
	#ifdef __USE_DIAMOND__
	MICO_SPI_WRITE_ENABLE(id);
	#else
    const EE_UINT8 cmd_w_en[] = { SPI_FLASH_CMD_WRITE_EN };         /* Write-Enable */
    spiflash_maybe_unprotect(id);
    spiflash_write(id, cmd_w_en, sizeof(cmd_w_en));
	#endif
}

/**
 * Function to disable write
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_write_disable(unsigned id)
{
	#ifdef __USE_DIAMOND__
	MICO_SPI_WRITE_DISABLE(id);
	#else
    const EE_UINT8 cmd_w_dis[] = { SPI_FLASH_CMD_WRITE_DIS };       /* Write-Disable */
    spiflash_write(id, cmd_w_dis, sizeof(cmd_w_dis));
	#endif
}

/**
 * Function to erase chip (all bytes to 0xFF)
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_erase_chip(unsigned id)
{
	#ifdef __USE_DIAMOND__
	MICO_SPI_CHIP_ERASE(id);
	#else
    const EE_UINT8 cmd_ch_erase[] = { SPI_FLASH_CMD_CHIP_ERASE };   /* Chip-Erase */
    spiflash_write_enable(id);
    spiflash_write(id, cmd_ch_erase, sizeof(cmd_ch_erase));
	#endif
    spiflash_wait_until_ready(id);
}

/**
 * Function to erase a sector (4 KB)
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_erase_sector(unsigned id, EE_UINT32 addr)
{
	#ifdef __USE_DIAMOND__
	MICO_SPI_BLOCK_ERASE_TYPE1(id, addr);
	#else
    spiflash_write_enable(id);
    spiflash_short_write(id,
        ((EE_UINT32)(SPI_FLASH_CMD_SECTOR_ERASE) << 24) | addr, 4);
    spiflash_wait_until_ready(id);
	#endif
}

/**
 * Function to erase a block (32 KB)
 */
__INLINE__ void __ALWAYS_INLINE__ spiflash_erase_block(unsigned id, EE_UINT32 addr)
{
	#ifdef __USE_DIAMOND__
	MICO_SPI_BLOCK_ERASE_TYPE2(id, addr);
	#else
    spiflash_write_enable(id);
    spiflash_short_write(id,
        ((EE_UINT32)(SPI_FLASH_CMD_BLOCK_ERASE) << 24) | addr, 4);
	#endif
    spiflash_wait_until_ready(id);
}


/**
 * @brief Erase a sector-aligned segment.
 *
 * This function erases a Flash segment by erasing a sequence of
 * blocks and/or sectors (the fastest combination is selected).  The segment
 * must be aligned to sector bounderies.
 * @param id    Used to identify the Flash SPI port; architecture-dependent.
 * @param addr  Address of the first byte of the segment.  It must be aligned to
 * a sector (SPI_FLASH_SECTOR_SIZE bytes).
 * @param len   Length of the segment.  It must be a multiple of
 * SPI_FLASH_SECTOR_SIZE.
 */
void spiflash_erase(unsigned id, EE_UINT32 addr, EE_UINT32 len);

    
#ifndef spiflash_write_buffer
#error "SPI-Flash error: spiflash_write_buffer not defined!"
#else
void spiflash_write_buffer(unsigned id, EE_UINT32 addr,
    const void *data, EE_UREG len);
#endif




#endif /* SPI_FLASH_GENERIC_H */
