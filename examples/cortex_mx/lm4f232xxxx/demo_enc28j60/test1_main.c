/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2012  Evidence Srl
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
 
/** @file	test1_main.c
 *  @brief	ENC28J60 driver function test
 *  		(eth mac mii read and write, bank selection).
 *
 *  User can use this demo to test if SPI communication works fine.
 *  The demo uses eth, mac, mii read/write and bank selection functions of the 
 *  ENC28J60 library.
 *  The demo requires a RS232 serial connection.
 *  The demo requires a SPI bus to communicate with the device.
 *
 *  @author    Dario Di Stefano
 *  @author    Errico Guidieri
 *  @author    Giuseppe Serano
 *  @date      2012
 */

/* RT-Kernel */
#include <ee.h>
/* Other libraries */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
/* AS MCAL */
#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#if	0
#include "Icu.h"
#endif
#include "Sci.h"
#include "Spi.h"

/* enc28j60 driver */
#include "enc28j60.h"

#define MAX_CHARS 128

/* A printf-like function */
static void EE_uart_send_buffer(const char * const str, size_t len) {
  size_t i;
  uint8 rx;
  Sci_StatusType st;
  for(i = 0U; i < len; ++i) {
  	/* To eventually handle errors in rx */
    st = Sci_GetStatus(SCI_CHANNEL_4);
    while ((st != SCI_OPERATIONAL) && (st != SCI_TX_OK)) {
	  Sci_ReadRxData(SCI_CHANNEL_4, &rx);
	  st = Sci_GetStatus(SCI_CHANNEL_4);
	}
    Sci_WriteTxData(SCI_CHANNEL_4, str[i]);
  }
}

/* This function is used to send info by serial interface. */
void myprintf(const char *format, ...)
{
  char str[MAX_CHARS];
  
  va_list args;
  va_start( args, format );
  vsnprintf(str, MAX_CHARS, format, args);
  va_end( args );
  EE_uart_send_buffer(str, strlen(str));
}

#define BANK0 0
#define BANK1 1
#define BANK2 2
#define BANK3 3

TASK(myTask1)
{
  EE_UINT8 data;
  EE_UINT8 mask;
  EE_UINT32 phy_data;

  /* Make the LED blink */
  Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_HIGH);

  /* ---------------------------------------------------------------- */
  /* BANK SELECTION */
  EE_enc28j60_bank_select(ECON1);
  myprintf("\nWrite bank: %d\n",      BANK0);
  myprintf("\nRead ECON1: %d\n",      EE_enc28j60_read_ETH_register(ECON1).Val);
  myprintf("\nRead ERXSTL:%d\n",      EE_enc28j60_read_ETH_register(ERXSTL).Val);
  myprintf("\nRead EDMADSTL:%d\n",    EE_enc28j60_read_ETH_register(EDMADSTL).Val);

  /* ---------------------------------------------------------------- */
  /* ETH */
  data = 0x09;
  EE_enc28j60_write_register(ETXNDL, data);
  myprintf("\nWrite ETXNDL:%d\n", data);
  myprintf("\nRead ETXNDL:%d\n", EE_enc28j60_read_ETH_register(ETXNDL).Val);
  mask = 0x0A; 
  EE_enc28j60_bit_field_clear_register(ETXNDL, mask); /* BFC */
  myprintf("\nBFC, ETXNDL expected:%d\n", data & ~mask);
  myprintf("\nRead ETXNDL:%d\n", EE_enc28j60_read_ETH_register(ETXNDL).Val);
  mask = 0x08;
  EE_enc28j60_bit_field_set_register(ETXNDL, mask); /* BFS */
  myprintf("\nBFS, ETXNDL expected:%d\n", data);
  myprintf("\nRead ETXNDL:%d\n", EE_enc28j60_read_ETH_register(ETXNDL).Val);

  /* ---------------------------------------------------------------- */
  /* BANK SELECTION */
  EE_enc28j60_bank_select(MACLCON1);
  myprintf("\nWrite bank:%d\n", BANK2);
  myprintf("\nRead ECON1:%d\n", EE_enc28j60_read_ETH_register(ECON1).Val);

  /* ---------------------------------------------------------------- */
  /* MAC */
  data = 0x02;
  EE_enc28j60_write_register((BYTE)MACLCON1, data);
  myprintf("\nWrite MACLCON1:%d\n", data);
  myprintf("\nRead MACLCON1:%d\n", EE_enc28j60_read_MAC_MII_register((BYTE)MACLCON1).Val);

  /* ---------------------------------------------------------------- */
  /* MII */
  data = 0x03;
  EE_enc28j60_write_register((BYTE)MIREGADR, data);
  myprintf("\nWrite MIREGADR:%d\n", data);
  myprintf("\nRead MIREGADR:%d\n", EE_enc28j60_read_MAC_MII_register((BYTE)MIREGADR).Val);

  /* ---------------------------------------------------------------- */
  /* PHY */
  phy_data = 0x3332;

  EE_enc28j60_write_PHY_register(PHLCON, phy_data);
  myprintf("\nWrite PHLCON:%x\n", phy_data);
  myprintf("\nRead PHLCON:%x\n", EE_enc28j60_read_PHY_register((BYTE)PHLCON).Val);

  /* ----------------------------------------------------------------- */
  /* MEMORY READ */

  /* Make the LED blink */
  Dio_WriteChannel(DIO_CHANNEL_USER_LED, STD_LOW);
}

/*
 * MAIN TASK
 */
int main(void)
{
  Mcu_Init(MCU_CONFIG_DEFAULT_PTR);
  /* 50 MHz Clock  */

  if ( Mcu_InitClock(MCU_CLOCK_MODE_MOSC_4_PLL) == E_NOT_OK ) {

    Mcu_PerformReset();

  }

  while ( Mcu_GetPllStatus() != MCU_PLL_LOCKED );

  Mcu_DistributePllClock();

  /* Initialize all AS MCAL */
  Port_Init(PORT_CONFIG_SPI_ENC28J60_PTR);
  Dio_Init(DIO_CONFIG_ENC28J60_PTR);
  Sci_Init(SCI_CONFIG_DEFAULT_PTR);
  Dma_Init(DMA_CONFIG_SPI_PTR);
  Spi_Init(SPI_CONFIG_ENC28J60_PTR);
#if	0
  Icu_Init(ICU_CONFIG_ENC28J60_PTR);
  Icu_EnableNotification(ICU_ENC28J60_CHANNEL);
#endif

  StartOS(OSDEFAULTAPPMODE);

  return 0;
}

