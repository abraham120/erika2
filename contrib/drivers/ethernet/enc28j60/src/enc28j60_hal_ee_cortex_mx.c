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
* @file   enc28j60_hal_ee_cortex_mx.C
* @brief  ENC28J60 driver - HAL for ARM Cortex MX.
* @author Errico Guidieri
* @date   2012
*/ 

#include "enc28j60.h"
#include "enc28j60_time_debug.h"

#include <ee.h>

/* ---------------------- Global variables --------------------------------- */
EE_TID ee_enc28j60_task = EE_NIL;

void EE_enc28j60_hal_set_rx_task(EE_TID task) {
  ee_enc28j60_task = task;
}

/* ---------------------- Ethernet interrupt handler ------------------------- */

/* This function is the ENC28J60 ICU Notification handler
   it takes the role of GPIO interrupt handler.
 */

void Icu_SignalNotification_ENC28J60(void)
{
  EE_enc28j60_hal_disable_IRQ();
  /* Called task should re-enable IRQs */
  if( ee_enc28j60_task >= 0)
    ActivateTask(ee_enc28j60_task);
}

/* ---------------------- Ethernet Library functions ------------------------- */
static void EE_enc28j60_hal_delay_us(unsigned int delay_count)
{
  EE_systick_delay_us(delay_count);
}

int EE_enc28j60_hal_spi_init(void) {
  /* Force hardware reset on enc28j60 */
  EE_enc28j60_hal_hardware_reset();
  return (Spi_GetStatus() == SPI_UNINIT)?
    ENC28J60_FAILURE:
    ENC28J60_SUCCESS;
}


BYTE EE_enc28j60_hal_get()
{
  const BYTE read_mem = ENC28J60_RBM;
  BYTE Result;
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &read_mem);
  Spi_SetupEB(SPI_ENC28J60_CHANNEL_BUFFER, NULL_PTR, &Result, sizeof(Result));
  Spi_SyncTransmit(SPI_ENC28J60_SEQ_RBM);
  return Result;
}//end MACGet


WORD EE_enc28j60_hal_get_array(BYTE *val, WORD len)
{
  const BYTE read_mem = ENC28J60_RBM;
  //BIBO, TODO: in the Microchip driver at this
  // point the interrupts are not disabled. Is this
  // approach the right one ??
  /* EE_cortex_mx_disableIRQ(); */
  EE_enc28j60_write_timestamp(ENC28J60_START_GET_ARRAY);
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &read_mem);
  if ( len > SPI_ENC28J60_CHANNEL_BUFFER_SIZE ) {
    Spi_SetupEB(
      SPI_ENC28J60_CHANNEL_BUFFER,
      NULL_PTR,
      val,
      SPI_ENC28J60_CHANNEL_BUFFER_SIZE
    );
    Spi_SetupEB(
      SPI_ENC28J60_CHANNEL_BUFFER_EXT,
      NULL_PTR,
      ( val + SPI_ENC28J60_CHANNEL_BUFFER_SIZE ),
      ( len - SPI_ENC28J60_CHANNEL_BUFFER_SIZE )
    );
    Spi_SyncTransmit(SPI_ENC28J60_SEQ_REBM);
  }
  else {
    Spi_SetupEB(SPI_ENC28J60_CHANNEL_BUFFER, NULL_PTR, val, len);
    Spi_SyncTransmit(SPI_ENC28J60_SEQ_RBM);
  }
  EE_enc28j60_write_timestamp(ENC28J60_END_GET_ARRAY);
  return len;
}//end MACGetArray

void EE_enc28j60_hal_put(BYTE val)
{
  const BYTE write_mem = ENC28J60_WBM;
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &write_mem);
  Spi_SetupEB(SPI_ENC28J60_CHANNEL_BUFFER, &val, NULL_PTR, sizeof(val));
  Spi_SyncTransmit(SPI_ENC28J60_SEQ_WBM);
}//end MACPut


void EE_enc28j60_hal_put_array(BYTE *val, WORD len)
{
  const BYTE write_mem = ENC28J60_WBM;
  EE_enc28j60_write_timestamp(ENC28J60_START_PUT_ARRAY);
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &write_mem);
  if ( len > SPI_ENC28J60_CHANNEL_BUFFER_SIZE ) {
    Spi_SetupEB(
      SPI_ENC28J60_CHANNEL_BUFFER,
      val,
      NULL_PTR,
      SPI_ENC28J60_CHANNEL_BUFFER_SIZE
    );
    Spi_SetupEB(
      SPI_ENC28J60_CHANNEL_BUFFER_EXT,
      ( val + SPI_ENC28J60_CHANNEL_BUFFER_SIZE ),
      NULL_PTR,
      ( len - SPI_ENC28J60_CHANNEL_BUFFER_SIZE )
    );
    Spi_SyncTransmit(SPI_ENC28J60_SEQ_WEBM);
  }
  else {
    Spi_SetupEB(SPI_ENC28J60_CHANNEL_BUFFER, val, NULL_PTR, len);
    Spi_SyncTransmit(SPI_ENC28J60_SEQ_WBM);
  }
  EE_enc28j60_write_timestamp(ENC28J60_END_PUT_ARRAY); 
}//end MACPutArray

void EE_enc28j60_hal_software_reset(void)
{
  const BYTE software_reset = ENC28J60_SR;
  // Note: The power save feature may prevent the reset from executing, so
  // we must make sure that the device is not in power save before issuing
  // a reset.
  EE_enc28j60_hal_bit_field_clear_register(ECON2, ECON2_PWRSV);
  // Give some opportunity for the regulator to reach normal regulation and
  // have all clocks running
  EE_enc28j60_hal_delay_us(1000U);
  // Execute the System Reset command
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &software_reset);
  Spi_SyncTransmit(SPI_ENC28J60_SEQ_SRC);
  // Wait for the oscillator start up timer and PHY to become ready
  EE_enc28j60_hal_delay_us(1000U);
}//end SendSystemReset

void EE_enc28j60_hal_hardware_reset(void)
{
  /* Real hardware reset */
  EE_enc28j60_hal_disable();
  EE_enc28j60_hal_delay_us(1000U);
  EE_enc28j60_hal_enable();
}

REG EE_enc28j60_hal_read_ETH_register(BYTE Address)
{
  const BYTE read_eth = ENC28J60_RCR | Address;
  REG reg_value;

  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &read_eth);
  Spi_SyncTransmit(SPI_ENC28J60_SEQ_RCR_ETH);
  Spi_ReadIB(SPI_ENC28J60_CHANNEL_REG, &reg_value.Val);
  
  return reg_value;
}//end ReadETHReg

REG EE_enc28j60_hal_read_MAC_MII_register(BYTE Address)
{
  const BYTE read_mac_or_mii = ENC28J60_RCR | Address;
  REG reg_value;

  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &read_mac_or_mii);
  Spi_SyncTransmit(SPI_ENC28J60_SEQ_RCR_MAC_OR_MII);
  Spi_ReadIB(SPI_ENC28J60_CHANNEL_REG, &reg_value.Val);

  return reg_value;
}//end ReadMACReg

PHYREG EE_enc28j60_hal_read_PHY_register(BYTE Register)
{
  PHYREG Result;

  // Set the right address and start the register read operation
  BankSel(MIREGADR);
  WriteReg((BYTE)MIREGADR, Register);
  WriteReg((BYTE)MICMD, MICMD_MIIRD);

  // Loop to wait until the PHY register has been read through the MII
  // This requires 10.24us
  BankSel(MISTAT);
  while(ReadMACReg((BYTE)MISTAT).Val & MISTAT_BUSY);
  
  // Stop reading
  BankSel(MIREGADR);
  WriteReg((BYTE)MICMD, 0x00);
  Result.VAL.byte.LB = ReadMACReg((BYTE)MIRDL).Val;
  Result.VAL.byte.HB = ReadMACReg((BYTE)MIRDH).Val;
  BankSel(ERDPTL);    // Return to Bank 0
  
  return Result;
}//end ReadPHYReg

void EE_enc28j60_hal_write_register(BYTE Address, BYTE Data)
{

  const BYTE write_cr = ENC28J60_WCR | Address;
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &write_cr);
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_REG, &Data);

  Spi_SyncTransmit(SPI_ENC28J60_SEQ_WCR);
}//end WriteReg

void EE_enc28j60_hal_bit_field_clear_register(BYTE Address, BYTE Data)
{
  const BYTE bit_field_clear = ENC28J60_BFC | Address;
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &bit_field_clear);
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_REG, &Data);

  Spi_SyncTransmit(SPI_ENC28J60_SEQ_BFC);
}//end BFCReg

void EE_enc28j60_hal_bit_field_set_register(BYTE Address, BYTE Data)
{
  const BYTE bit_field_set = ENC28J60_BFS | Address;
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_COMMAND, &bit_field_set);
  Spi_WriteIB(SPI_ENC28J60_CHANNEL_REG, &Data);

  Spi_SyncTransmit(SPI_ENC28J60_SEQ_BFS);

}//end BFSReg

void EE_enc28j60_hal_write_PHY_register(BYTE Register, WORD Data)
{
  // Write the register address
  BankSel(MIREGADR);
  WriteReg((BYTE)MIREGADR, Register);

  // Write the data
  // Order is important: write low byte first, high byte last
  WriteReg((BYTE)MIWRL, ((WORD_VAL*)&Data)->byte.LB);
  WriteReg((BYTE)MIWRH, ((WORD_VAL*)&Data)->byte.HB);
  
  // Wait until the PHY register has been written
  BankSel(MISTAT);
  
  while(ReadMACReg((BYTE)MISTAT).Val & MISTAT_BUSY);

  BankSel(ERDPTL);    // Return to Bank 0
}//end WritePHYReg

void EE_enc28j60_hal_bank_select(WORD Register)
{
  BFCReg(ECON1, ECON1_BSEL1 | ECON1_BSEL0);
  BFSReg(ECON1, ((WORD_VAL*)&Register)->byte.HB);
  
}//end BankSel

void EE_enc28j60_hal_set_clkout(BYTE NewConfig)
{
  BankSel(ECOCON);
  WriteReg((BYTE)ECOCON, NewConfig);
  BankSel(ERDPTL);
}//end SetCLKOUT

BYTE EE_enc28j60_hal_get_clkout(void)
{
  BYTE i;

  BankSel(ECOCON);
  i = ReadETHReg((BYTE)ECOCON).Val;
  BankSel(ERDPTL);
  return i;
}//end GetCLKOUT
