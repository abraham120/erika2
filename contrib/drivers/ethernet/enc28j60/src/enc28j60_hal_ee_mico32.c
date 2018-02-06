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
 
/** 
* @file 	enc28j60_hal_ee_mico32.c
* @brief 	ENC28J60 driver - HAL for Lattice Mico32
* @author 	Dario Di Stefano
* @date 	2010
*/ 

#include "enc28j60.h"
#include "enc28j60_debug.h"
#include "enc28j60_time_debug.h"

/* ---------------------- Global variables --------------------------------- */
EE_enc28j60_st ee_enc28j60_st = {
	.base= (MicoGPIO_t* )EE_ENC28J60_BASE_ADDRESS,
	.irqf= EE_ENC28J60_IRQ, 
	.task= -1 };
	
/* ---------------------- Ethernet interrupt handler ------------------------- */

/**
 * The PKTIF bit can only be cleared by the host controller
 * or by a Reset condition. In order to clear PKTIF, the
 * EPKTCNT register must be decremented to 0. If the last
 * data packet in the receive buffer is processed,
 * EPKTCNT will become zero and the PKTIF bit will
 * automatically be cleared.
*/

/* This function is the ENC28J60 interrupt handler */
void EE_enc28j60_hal_handler(int level)
{
	EE_enc28j60_disable_IRQ();
	
	/* Clear GPIO irq pending flag */
	EE_gpio_common_handler(level);
	
	/* Called task should re-enable IRQs */
	if( ee_enc28j60_st.task >= 0)
		 ActivateTask(ee_enc28j60_st.task);	
		 
	return;
}

/* ---------------------- Ethernet Library functions ------------------------- */

/* This function implements a delay in micro-seconds */
void EE_enc28j60_hal_delay_us(unsigned int delay_count)
{
	MicoSleepMicroSecs((unsigned int)delay_count);
}

/* This function implements a delay in milli-seconds */
void EE_enc28j60_hal_delay_ms(unsigned int delay_count)
{
	MicoSleepMilliSecs((unsigned int)delay_count);
}

/* This function reads a byte from ENC28J60 buffer memory (for MAC layer) */
BYTE EE_enc28j60_hal_get()
{
	BYTE Result;
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_byte(ENC28J60_RBM);
	Result = EE_enc28j60_hal_read_byte();
	EE_enc28j60_hal_chip_unselect();
	return Result;
}//end MACGet

/* This function reads an array of bytes from ENC28J60 buffer memory (for MAC layer) */
WORD EE_enc28j60_hal_get_array(BYTE *val, WORD len)
{
	WORD num;
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_byte(ENC28J60_RBM);
	EE_enc28j60_write_timestamp(ENC28J60_START_GET_ARRAY);
	num = EE_enc28j60_hal_read_buffer(val, len);
	EE_enc28j60_write_timestamp(ENC28J60_END_GET_ARRAY);
	EE_enc28j60_hal_chip_unselect();
    return num;
}//end MACGetArray

/* This function writes a byte to ENC28J60 buffer memory (for MAC layer) */
void EE_enc28j60_hal_put(BYTE val)
{
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_16(ENC28J60_WBM, val);
	EE_enc28j60_hal_chip_unselect();
}//end MACPut

/* This function writes an array of bytes to ENC28J60 buffer memory (for MAC layer) */
void EE_enc28j60_hal_put_array(BYTE *val, WORD len)
{
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_byte(ENC28J60_WBM);
	EE_enc28j60_write_timestamp(ENC28J60_START_PUT_ARRAY);
	EE_enc28j60_hal_write_buffer(val, len);
	EE_enc28j60_write_timestamp(ENC28J60_END_PUT_ARRAY);
	EE_enc28j60_hal_chip_unselect();
}//end MACPutArray

/* This function implements a sw reset */
void EE_enc28j60_hal_software_reset(void)
{
	// Note: The power save feature may prevent the reset from executing, so
    // we must make sure that the device is not in power save before issuing
    // a reset.
	EE_enc28j60_hal_bit_field_clear_register(ECON2, ECON2_PWRSV);
    // Give some opportunity for the regulator to reach normal regulation and
    // have all clocks running
    EE_enc28j60_hal_delay_us(1000);
	// Execute the System Reset command
	EE_enc28j60_hal_write_byte(ENC28J60_SR);
    // Wait for the oscillator start up timer and PHY to become ready
    EE_enc28j60_hal_delay_us(1000);
}//end SendSystemReset

/* This function implements a hw reset */
void EE_enc28j60_hal_hardware_reset(void)
{
	EE_enc28j60_hal_disable();
	EE_enc28j60_hal_delay_us(1000);
	EE_enc28j60_hal_enable();
}

/* This function reads a ENC28J60 ETH type register */
REG EE_enc28j60_hal_read_ETH_register(BYTE Address)
{
    REG r;
	
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_byte(ENC28J60_RCR | Address);
	r.Val = EE_enc28j60_hal_read_byte();
	EE_enc28j60_hal_chip_unselect();
	
    return r;
}//end ReadETHReg

/* This function reads a ENC28J60 MAC type or MII type register */
REG EE_enc28j60_hal_read_MAC_MII_register(BYTE Address)
{
    REG r;
	
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_byte(ENC28J60_RCR | Address);
	EE_enc28j60_hal_read_byte();
	r.Val = EE_enc28j60_hal_read_byte();
	EE_enc28j60_hal_chip_unselect();
	
    return r;
}//end ReadMACReg

/* This function reads a ENC28J60 PHY type register */
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

/* This function writes on a specified ENC28J60 register */
void EE_enc28j60_hal_write_register(BYTE Address, BYTE Data)
{
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_16(ENC28J60_WCR | Address, Data);
	EE_enc28j60_hal_chip_unselect();
}//end WriteReg

/* This function implements a binary AND on a ENC28J60 register using a mask */
void EE_enc28j60_hal_bit_field_clear_register(BYTE Address, BYTE Data)
{
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_16(ENC28J60_BFC | Address, Data);
	EE_enc28j60_hal_chip_unselect();
}//end BFCReg

/* This function implements a binary OR on a ENC28J60 register using a mask */
void EE_enc28j60_hal_bit_field_set_register(BYTE Address, BYTE Data)
{
	EE_enc28j60_hal_set_slave(EE_ENC28J60_DEVICE_ID);	
	EE_enc28j60_hal_chip_select();
	EE_enc28j60_hal_write_16(ENC28J60_BFS | Address, Data);
	EE_enc28j60_hal_chip_unselect();
}//end BFSReg

/* This function writes on a ENC28J60 PHY type register */
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

/* This function selects the bank */
void EE_enc28j60_hal_bank_select(WORD Register)
{
	BFCReg(ECON1, ECON1_BSEL1 | ECON1_BSEL0);
    BFSReg(ECON1, ((WORD_VAL*)&Register)->byte.HB);
	
}//end BankSel

/* This function sets CLKOUT */
void EE_enc28j60_hal_set_clkout(BYTE NewConfig)
{
    BankSel(ECOCON);
    WriteReg((BYTE)ECOCON, NewConfig);
    BankSel(ERDPTL);
}//end SetCLKOUT

/* This function gets CLKOUT */
BYTE EE_enc28j60_hal_get_clkout(void)
{
    BYTE i;

    BankSel(ECOCON);
    i = ReadETHReg((BYTE)ECOCON).Val;
    BankSel(ERDPTL);
    return i;
}//end GetCLKOUT



