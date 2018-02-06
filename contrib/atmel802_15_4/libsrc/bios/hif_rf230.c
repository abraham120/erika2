/**
 * @file
 * @brief Hardware interface functions for AT86RF230.
 *
 * Hardware interface implementation for radio-dependant functions of
 * the AT86RF230 radio chip.
 *
 * $Id: hif_rf230.c,v 1.1 2007/06/22 13:50:48 romano Exp $
 *
 */
/**
 *  \author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2006, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* === Includes ============================================================ */

#include "board.h"
#include "avrtypes.h"
#include "msg_const.h"
#include "msg_types.h"
#include "bios.h"
#ifndef DEF_H
#include "def.h"
#endif


#if RADIO_TYPE == AT86RF230

/* === Globals ============================================================= */

/* === Macros ============================================================== */

#define BIT_SPI_SPR0    (1)   /* spi_set_rate() parameter bit for SPR0 */
#define BIT_SPI_SPR1    (2)   /* spi_set_rate() parameter bit for SPR1 */
#define BIT_SPI_SPI2X   (4)   /* spi_set_rate() parameter bit for SPI2X */
#define SPI_DUMMY_VALUE (0)   /* dummy value, which is sent over SPI, if a
                                 value is read from the transceiver */
/* === Prototypes ========================================================== */


/* === Implementation ====================================================== */

/**
 * @brief
 *    SPI Initialization (RADIO_TYPE == AT86RF230)
 *
 *    Init the Serial Peripherial Interface of the AVR
 *
 */
void spi_init (void)
{
    DDR_SPI  |= _BV(SPI_MOSI) | _BV(SPI_SCK) | _BV(SPI_SS);     // SCK, MOSI, SS output
    DDR_SPI  &=~ _BV(SPI_MISO);                                 // MISO input
    PORT_SPI |= _BV(SPI_SCK) | _BV(SPI_SS);                     // SCK high
    SPCR = SPI_CFG_0;
}


/**
 * @brief
 *    Set SPI-Speed
 *
 *  This function sets the SPI speed and the SPI-Mode to "blocking"
 *
 * @param rate The Speed of the SPI_MOSI
 * rate bits:   0 = SPR0
 *              1 = SPR1
 *              2 = SPI2x
 *         see SPI Chapter in Datasheet
 */
void spi_set_rate (uint8_t rate)
{
    /* erase all SPRn bits */
    SPCR &= ~(_BV(SPR0)|_BV(SPR1));
    SPSR &= ~(_BV(SPI2X));

    /* set them, if needed */
    if (rate & BIT_SPI_SPR0)
    {
        SPCR |= _BV(SPR0);
    }
    if (rate & BIT_SPI_SPR1)
    {
        SPCR |= _BV(SPR1);
    }

    /* finally handle SPI2X */
    if (rate & BIT_SPI_SPI2X)
    {
        SPSR |= _BV(SPI2X);
    }
    else
    {
        SPSR &= ~(_BV(SPI2X));
    }
}

/**
 * @brief Write Register
 *
 * This function write to a transceiver register.
 * @param addr Address of the Register in the Transceiver (Offset) that should be written
 * @param val Byte that will be written into the Register
 */

void bios_reg_write(uint8_t addr, radio_reg_t val)
{
    addr=TRX_CMD_RW | (TRX_CMD_RADDRM & addr);

    SPI_SELN_LOW();

    SPDR = addr;
    SPI_WAITFOR();
    SPDR = val;
    SPI_WAITFOR();

    SPI_SELN_HIGH();
}


/**
 * @brief Read Register
 *
 * This function reads a transceiver register.
 * @param addr Address of the Register in the Transceiver (Offset)
 *             that will be read
 * @return Contents of the Register
 */
uint8_t bios_reg_read(uint8_t addr)
{
    uint8_t val;

    addr=TRX_CMD_RR | (TRX_CMD_RADDRM & addr);

    SPI_SELN_LOW();

    SPDR = addr;
    SPI_WAITFOR();
    SPDR = SPI_DUMMY_VALUE;
    SPI_WAITFOR();
    val = SPDR;

    SPI_SELN_HIGH();

    return val;
}

/**
 * @brief Frame Write
 *
 * This function writes a frame to the transceiver.
 *
 * @param length Number of bytes, that will be written to the frame buffer.
 * @param data   Pointer to an array with the bytes that will be written
 *               to the frame buffer
 */

void bios_frame_write(uint8_t length, uint8_t *data)
{

    ASSERT(length > 0);

    SPI_SELN_LOW();

    SPDR = TRX_CMD_FW;
    SPI_WAITFOR();
    SPDR = length;
    SPI_WAITFOR();
    do
    {
        SPDR = *data++;
        SPI_WAITFOR();
    }
    while (--length > 0);

    SPI_SELN_HIGH();
}

/**
 * @brief Frame Read
 *
 * This function reads a frame from the transceiver.
 *
 * @retval data Pointer to an array that holds the received bytes.
 *              The pointer must be able to store (aMaxPHYPacketSize+2 bytes)
 *              (frame length and LQI value).
 *
 * @return length of the downloaded frame (including the LQI byte if
 *                RADIO_TYPE is AT86RF230)
 */

uint8_t bios_frame_read(uint8_t *data)
{
    uint8_t length, i;

    SPI_SELN_LOW();

    SPDR = TRX_CMD_FR;
    SPI_WAITFOR();

    SPDR = SPI_DUMMY_VALUE;
    SPI_WAITFOR();
    *data++ = length = i = SPDR + 1; /* read length */

    do
    {
        SPDR = SPI_DUMMY_VALUE;
        SPI_WAITFOR();
        *data++ = SPDR;
    }
    while (--i > 0);

    SPI_SELN_HIGH();
    return length;
}

#if APP_TYPE > APP_L0
/**
 * @brief Frame Read and check CRC-16
 *
 * This function reads a frame from the transceiver, and checks the
 * CRC-16 of the received frame.  For failed CRC checks, the length
 * indication of the returned frame will be set to 0.
 *
 * @retval data Pointer to an array that holds the received bytes.
 *              The pointer must be able to store (aMaxPHYPacketSize+2 bytes)
 *              (frame length and LQI value).
 *
 * @return length of the downloaded frame (including the LQI byte [RADIO_TYPE == AT86RF230])
 */

uint8_t bios_frame_crc_read(uint8_t *data)
{
    uint8_t *pdata;
    uint8_t length, i = 0;
    uint16_t crc = 0;

    /* pdata is a working pointer, which is modified. */
    pdata = data;

    SPI_SELN_LOW();

    SPDR = TRX_CMD_FR;
    SPI_WAITFOR();

    SPDR = SPI_DUMMY_VALUE;
    SPI_WAITFOR();

    *pdata = length = SPDR + 1; /* read length and update for LQI read */
    i = length - 1;

    /* ACK timing tuning, it looks but it is fast */
    if (length > 3)
    {
        SPDR = SPI_DUMMY_VALUE;
        pdata++;
        SPI_WAITFOR();
        *pdata = SPDR;   /* read the first byte */
        i--;
        do
        {
            SPDR = SPI_DUMMY_VALUE;
            crc = CRC_CCITT_UPDATE(crc, *pdata);
            pdata++;
            SPI_WAITFOR();
            *pdata = SPDR;
        }
        while (--i > 0);

        /* now read LQI value and update crc with the last frame byte,
           while waiting for the SPI transfer */
        SPDR = SPI_DUMMY_VALUE;
        crc = CRC_CCITT_UPDATE(crc, *pdata);
        pdata++;
        SPI_WAITFOR();
        *pdata = SPDR;

        if (crc != 0)
        {
            length = 0;
        }
    }
    else
    {
        length = 0;
    }
    
    SPI_SELN_HIGH();
    *data = length;
    return length;
}
#endif /* APP_TYPE > APP_L0 */

#if APP_TYPE > APP_L0
/**
 * @brief Frame Length Read (RADIO_TYPE == AT86RF230)
 *
 * This function reads the length of a frame from the transceiver.
 *
 * @return length of the frame to download (including the LQI byte)
 */

uint8_t bios_frame_length_read(void)
{
    uint8_t length = 0;

    SPI_SELN_LOW();

    SPDR = TRX_CMD_FR;
    SPI_WAITFOR();
    SPDR = SPI_DUMMY_VALUE;
    SPI_WAITFOR();
    length = SPDR + 1; /* read length */

    SPI_SELN_HIGH();
    return length;
}
#endif /* APP_TYPE */

/**
 * @brief Write SRAM
 *
 * This function writes into the SRAM of the transceiver.
 *
 * @param addr Address in the TRX's SRAM where the write burst should start
 * @param length Length of the write burst
 * @param data Pointer to an array of bytes that should be written
 */

void bios_sram_write(radio_ram_t addr, uint8_t length, uint8_t *data)
{

    SPI_SELN_LOW();

    SPDR = TRX_CMD_SW;
    SPI_WAITFOR();

    SPDR = addr;
    SPI_WAITFOR();

    do
    {
        SPDR = *data++;
        SPI_WAITFOR();
    }
    while (--length > 0);

    SPI_SELN_HIGH();
}

/**
 * @brief Read SRAM
 *
 * @param addr Address in the TRX's SRAM where the read burst should start
 * @param length Length of the write burst
 * @retval data Pointer to an array of bytes that should be read
 */

void bios_sram_read(radio_ram_t addr, uint8_t length, uint8_t *data)
{

    SPI_SELN_LOW();

    SPDR = TRX_CMD_SR;
    SPI_WAITFOR();
    SPDR = addr;
    SPI_WAITFOR();
    do
    {
        SPDR = SPI_DUMMY_VALUE;
        SPI_WAITFOR();
        *data++ = SPDR;
    }
    while (--length > 0);

    SPI_SELN_HIGH();
}

/**
 * @brief subregister read
 *
 * @param   addr  offset of the register
 * @param   mask  bit mask of the subregister
 * @param   pos   bit position of the subregister
 * @retval  data  pointer where the read and demuxed value is stored
 *
 * @code
 *   pos = 4, mask = 0xf0
 *   register value = 0xA5
 *   *data = 0x0A
 * @endcode
 */

void bios_bit_read(uint8_t addr, radio_reg_t mask, uint8_t pos, radio_reg_t *data)
{
    *data = bios_reg_read(addr);
    *data &= mask;
    *data >>= pos;
}

/**
 * @brief subregister write
 *
 * @param   addr  offset of the register
 * @param   mask  bit mask of the subregister
 * @param   pos   bit position of the subregister
 * @retval  value  data, which is muxed into the register
 *
 * @code
 *   pos = 4, mask = 0xf0
 *   register value = 0xA5 (before operation)
 *   value = 0x05
 *   register value = 0x55 (after operation)
 * @endcode
 *
 */
void bios_bit_write(uint8_t addr, radio_reg_t mask, uint8_t pos, radio_reg_t value)
{

uint8_t tmp;
    tmp = bios_reg_read(addr);
    tmp &= ~mask;
    value <<= pos;
    value &=mask;
    value |= tmp;
    bios_reg_write(addr, value);
}

#endif /* RADIO_TYPE == AT86RF230 */

/* EOF */
