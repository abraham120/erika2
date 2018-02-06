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

/******************************************************************************
*                                                                             *
* License Agreement                                                           *
*                                                                             *
* Copyright (c) 2003 Altera Corporation, San Jose, California, USA.           *
* All rights reserved.                                                        *
*                                                                             *
* Permission is hereby granted, free of charge, to any person obtaining a     *
* copy of this software and associated documentation files (the "Software"),  *
* to deal in the Software without restriction, including without limitation   *
* the rights to use, copy, modify, merge, publish, distribute, sublicense,    *
* and/or sell copies of the Software, and to permit persons to whom the       *
* Software is furnished to do so, subject to the following conditions:        *
*                                                                             *
* The above copyright notice and this permission notice shall be included in  *
* all copies or substantial portions of the Software.                         *
*                                                                             *
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  *
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    *
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER      *
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     *
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER         *
* DEALINGS IN THE SOFTWARE.                                                   *
*                                                                             *
* This agreement shall be governed in all respects by the laws of the State   *
* of California and by the laws of the United States of America.              *
*                                                                             *
* Altera does not recommend, suggest or require that this reference design    *
* file be used in conjunction or combination with any other product.          *
*                                                                             *
* altera_avalon_lan91c111.c - ethernet interface for the the Lan91C111        *
* on the Nios boards.                                                         *
*                                                                             *
* Author PRR                                                                  *
*                                                                             *
******************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "alt_types.h"
#include "altera_avalon_lan91c111_regs.h"
#include "system.h"
#include "sys/alt_irq.h"
#include "altera_avalon_lan91c111.h"

/* 
* Prototypes
*/

// Added by Evidence Srl
void LWIP_irq_callback(void);


/*
* alt_avalon_lan91c111_irq
*
* The Interrupt handler
*/
static void alt_avalon_lan91c111_irq(void* context, alt_u32 interrupt)
{
  alt_u8  irq_status;
  alt_u8  irq_msk;
  alt_avalon_lan91c111_if *dev =  (alt_avalon_lan91c111_if *)context;

  irq_status = IORD_ALTERA_AVALON_LAN91C111_IST(dev->base_addr);

  /*
   *  Rx Overrun, clear the interrupt and increment the stats counter
   */
  if(irq_status & ALTERA_AVALON_LAN91C111_INT_RX_OVRN_INT_MSK)
  {
    //printf("drop (ovr)\n");
    dev->stat_link_drop++;
    IOWR_ALTERA_AVALON_LAN91C111_ACK(dev->base_addr, 
                            ALTERA_AVALON_LAN91C111_INT_RX_OVRN_INT_MSK);
  }

  /*
   *  Packet to Receive
   * 
   *  signal the thread which will read the data and disable interrupts
   *
   */
  irq_msk = IORD_ALTERA_AVALON_LAN91C111_MSK(dev->base_addr); 

  if((irq_status & ALTERA_AVALON_LAN91C111_INT_RCV_INT_MSK) && 
      (irq_msk & ALTERA_AVALON_LAN91C111_INT_RCV_INT_MSK))
  {
    irq_msk &= ~ALTERA_AVALON_LAN91C111_INT_RCV_INT_MSK;
    IOWR_ALTERA_AVALON_LAN91C111_MSK(dev->base_addr, irq_msk);
#if 0
    sys_mbox_post(rx_mbox, &dev->ethernet_dev_list.dev);
#endif
    // Added by Evidence Srl
    LWIP_irq_callback();
  }
  return;
}

/*
* alt_avalon_lan91c111_rx
* Handle all the receives
*/
void alt_avalon_lan91c111_rx( alt_avalon_lan91c111_if *dev, if_input_t ifInput() )
{
  alt_u8  irq_msk;
  alt_u8  irq_status;
  
//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("lan91c111_rx()"));

  irq_status = IORD_ALTERA_AVALON_LAN91C111_IST(dev->base_addr);
  while(irq_status & ALTERA_AVALON_LAN91C111_INT_RCV_INT_MSK)
  {
    /* Call the network interface's input handler */
    ifInput(dev->ethernet_dev_list.dev.network);
    irq_status = IORD_ALTERA_AVALON_LAN91C111_IST(dev->base_addr);
  }
  
  /* Re-enable RX interrupts */
  irq_msk = IORD_ALTERA_AVALON_LAN91C111_MSK(dev->base_addr); 
  irq_msk |= ALTERA_AVALON_LAN91C111_INT_RCV_INT_MSK;
  IOWR_ALTERA_AVALON_LAN91C111_MSK(dev->base_addr, irq_msk);
}

/*
* Clock one bit of data to the PHY
*/
static void clock_phy_bit(alt_avalon_lan91c111_if* dev, const unsigned value)
{
  IOWR_ALTERA_AVALON_LAN91C111_MGMT(dev->base_addr, value);
  IOWR_ALTERA_AVALON_LAN91C111_MGMT(dev->base_addr, value |
                                    ALTERA_AVALON_LAN91C111_MGMT_MCLK_MSK);
}

/*
* Read a PHY register, this involves manually clocking lots
* of data.
*/
static alt_u16 read_phy_register(alt_avalon_lan91c111_if* dev, 
                                 const unsigned phy_register)
{
  alt_u16 register_value;
  alt_u16 old_bank;
  alt_u16 mgmt_value;
  int i;

//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("read_phy_register (%d)=", phy_register));

  /*
  * Swap to bank 3
  */
  old_bank = IORD_ALTERA_AVALON_LAN91C111_BSR(dev->base_addr);
  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr,3);

  mgmt_value = IORD_ALTERA_AVALON_LAN91C111_MGMT( dev->base_addr);
  mgmt_value &= 0xfff0;

  /* Output an Idle of 32 1's */
  for(i=0;i<32;i++)
  {
    clock_phy_bit(dev, mgmt_value | 
                                  ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                  ALTERA_AVALON_LAN91C111_MGMT_MDO_MSK );
  }

  /* Ouput 01 which marks the change of cycle */
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDO_MSK );
  
  /* Output the command, 10 = read */
  clock_phy_bit(dev, mgmt_value |
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDO_MSK );
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );

  /* Output the PHY address, 0 is the internal PHY */
  for(i=0;i<5;i++) 
  {
    clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );
  }

  /* Write the Register Address, MSB first */
  for(i=4;i>=0;i--) 
  {
    clock_phy_bit(dev, mgmt_value | 
                                  ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                  ((phy_register >> i) & 0x1));
  }

  /* 
  * The datasheet says we output Z0 here, however Application Note 79 mentions a chip bug
  * which configuring the Nat Semi in built PHY we only output Z, if using an off chip PHY
  * uncomment the second line
  */
  clock_phy_bit(dev, mgmt_value);
  /*
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );
  */

  register_value = 0;

  /* Read in the data */
  for(i=15;i>=0;i--) 
  {
    clock_phy_bit(dev, mgmt_value);
    register_value |= 
      ((IORD_ALTERA_AVALON_LAN91C111_MGMT(dev->base_addr) 
       & ALTERA_AVALON_LAN91C111_MGMT_MDI_MSK) >> 1) << i;
  }

  /* Output the Turnaround bit */
  clock_phy_bit(dev, mgmt_value);

  IOWR_ALTERA_AVALON_LAN91C111_MGMT(dev->base_addr, mgmt_value);

  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr,old_bank);

//  DEBUGF(NETIF_DEBUG | DBG_TRACE, (" %#x\n", register_value));
  return register_value;
}

/*
* Write to a PHY register, this involves manually clocking out lots
* of data.
*/
static void write_phy_register(alt_avalon_lan91c111_if* dev, 
                        const unsigned phy_register,
                        const alt_u16 value)
{
  alt_u16 old_bank;
  alt_u16 mgmt_value;
  int i;

//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("write_phy_register (%d, %#x)\n", phy_register, value));

  /*
  * Swap to bank 3, if this code is ever changed to run with interrups we will
  * need a critical section here
  */
  old_bank = IORD_ALTERA_AVALON_LAN91C111_BSR(dev->base_addr);
  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr,3);

  mgmt_value = IORD_ALTERA_AVALON_LAN91C111_MGMT(dev->base_addr);
  mgmt_value &= 0xfff0;

  /* Output an Idle of 32 1's */
  for(i=0;i<32;i++) 
  {
    clock_phy_bit(dev, mgmt_value | 
                                  ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                  ALTERA_AVALON_LAN91C111_MGMT_MDO_MSK );
  }

  /* Ouput 01 which marks the change of cycle */
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDO_MSK );
  
  /* Output the command, 01 = write */
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDO_MSK );


  /* Output the PHY address, 0 is the internal PHY */
  for(i=0;i<5;i++) 
  {
    clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );
  }

  /* Write the Register Address, MSB first */
  for(i=4;i>=0;i--) 
  {
    clock_phy_bit(dev, mgmt_value | 
                                  ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                  ((phy_register >> i) & 0x1));
  }

  /* Write 10 to the turnaround bit */
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDO_MSK );
  clock_phy_bit(dev, mgmt_value | 
                                    ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK );

  /* Now write the data MSB first */
  for(i=15;i>=0;i--) 
  {
    clock_phy_bit(dev, mgmt_value | 
                                  ALTERA_AVALON_LAN91C111_MGMT_MDOE_MSK |
                                  ((value >> i) & 0x1));
  }

  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr,old_bank);

  return;  
}

/*
* configure_phy 
*
* reset the PHY and auto negotiate for the link capabilities
*
*/
static int configure_phy(alt_avalon_lan91c111_if *dev)
{
  int timeout, i;
  alt_u16 value, old_value;
  int ret_code = 0;

//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("configure_phy()\n"));

  /* Read the ID register let's just check we've detected the correct PHY */
  value = read_phy_register(dev, 
                            ALTERA_AVALON_LAN91C111_PHY_ID1_REG);
  if (value != ALTERA_AVALON_LAN91C111_PHY_COMPANY_ID) 
  {
    ret_code = -EIO;
    goto exit;
  }

  value = read_phy_register(dev, 
                            ALTERA_AVALON_LAN91C111_PHY_ID2_REG);
  if ((value & 0xfff0) != ALTERA_AVALON_LAN91C111_PHY_MFCT_ID ) 
  {
    ret_code = -EIO;
    goto exit;
  }

  /* Reset the PHY */
  write_phy_register( dev, 
                      ALTERA_AVALON_LAN91C111_PHY_CONTROL_REG, 
                      ALTERA_AVALON_LAN91C111_PHY_CONTROL_RST_MSK);

  /* Spec says wait 50 mS */
  usleep(50000);

  /* Let's just check  it's out of reset */
  value = read_phy_register(dev, 
                            ALTERA_AVALON_LAN91C111_PHY_CONTROL_REG);

  if (value & ALTERA_AVALON_LAN91C111_PHY_CONTROL_RST_MSK) 
  {
    ret_code = -EIO;
    goto exit;
  }

  /* Turn off Auto negotiation til we're ready for it */
  write_phy_register( dev, 
                      ALTERA_AVALON_LAN91C111_PHY_CONTROL_REG , 0);

  /* 
   * We'll auto negotiate the capabilities thanks orange LED for packet Rx, 
   * green LED for Tx 
   */
  IOWR_ALTERA_AVALON_LAN91C111_BSR(dev->base_addr, 0); 
  IOWR_ALTERA_AVALON_LAN91C111_RPCR(dev->base_addr,
                                    ALTERA_AVALON_LAN91C111_RPCR_ANEG_MSK |
                                    ALTERA_AVALON_LAN91C111_RPCR_LS2A_MSK | 
                                    ALTERA_AVALON_LAN91C111_RPCR_LS1A_MSK |                                     
                                    ALTERA_AVALON_LAN91C111_RPCR_LS2B_MSK | 
                                    ALTERA_AVALON_LAN91C111_RPCR_LS1B_MSK | 
                                    ALTERA_AVALON_LAN91C111_RPCR_LS0B_MSK ); 

  /* Start the Auto Negotiation process */
  /* Try to negotiate, we have a go at this five times if it fails */
  i = 5;
  do 
  {
    write_phy_register( dev, 
                        ALTERA_AVALON_LAN91C111_PHY_CONTROL_REG, 
                        ALTERA_AVALON_LAN91C111_PHY_CONTROL_ANEG_EN_MSK | 
                        ALTERA_AVALON_LAN91C111_PHY_CONTROL_ANEG_RST_MSK);

    /* This may take a few seconds */
    timeout = 20;

    do 
    {
      value = read_phy_register(dev, ALTERA_AVALON_LAN91C111_PHY_STATUS_REG);
      timeout --;
      usleep(500000);
    }while (!(value & ALTERA_AVALON_LAN91C111_PHY_STATUS_ANEG_ACK_MSK)  
              && (timeout > 0));

    i --;
  }
  while( (i != 0) && (timeout == 0));

  if (timeout == 0)
  {
    ret_code = -EIO;
    goto exit;
  }

  if (value & ALTERA_AVALON_LAN91C111_PHY_STATUS_REM_FLT_MSK) 
  {
    /* 
     * We may wish to come up with a sensible default here, 
     *set to 10MBits, CSMA?
     */
    ret_code = -EIO;
    goto exit;
  }

  /* 
   * Find out what we've negotiated so that we can configure the MAC 
   * takes a few reads to stabilise
   */

  old_value = read_phy_register(dev, 
                            ALTERA_AVALON_LAN91C111_PHY_INT_STATUS_REG);
  value = read_phy_register(dev, 
                            ALTERA_AVALON_LAN91C111_PHY_INT_STATUS_REG);

  while(value != old_value)
  {
    old_value = value;
    value = read_phy_register(dev, 
                            ALTERA_AVALON_LAN91C111_PHY_INT_STATUS_REG);
  }

  if (value & ALTERA_AVALON_LAN91C111_PHY_INT_SPDDET_MSK) 
  {
//    DEBUGF(NETIF_DEBUG | DBG_TRACE, ("100MBits/s\n"));
  }
  else 
  {
//    DEBUGF(NETIF_DEBUG | DBG_TRACE, ("10MBits/s\n"));
  }

  if (value & ALTERA_AVALON_LAN91C111_PHY_INT_DPLXDET_MSK) 
  {
//    DEBUGF(NETIF_DEBUG | DBG_TRACE, ("Full Duplex\n"));

    /* Set the MAC for Full Duplex */
    value = IORD_ALTERA_AVALON_LAN91C111_TCR(dev->base_addr);
    value |= ALTERA_AVALON_LAN91C111_TCR_SWFDUP_MSK;
    IOWR_ALTERA_AVALON_LAN91C111_TCR(dev->base_addr,value);
  }
  else 
  {
//    DEBUGF(NETIF_DEBUG | DBG_TRACE, ("Half Duplex\n"));
  }

exit:
//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("configure_phy() exit = %d\n", ret_code));

  return ret_code;
}

/*-----------------------------------------------------------------------------------*
 *
 * reset_device(alt_avalon_lan91c111_if *dev):
 *
 * Reset the device and get it into a known state
 *
 * 
 *-----------------------------------------------------------------------------------*/
static int reset_device(alt_avalon_lan91c111_if *dev)
{
  alt_u16 register_value;
  alt_u16 chip_id;
  int   ret_code = 0;

//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("reset_device()\n"));

  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr, 3);
  chip_id = IORD_ALTERA_AVALON_LAN91C111_REV(dev->base_addr);

  if (( chip_id & ALTERA_AVALON_LAN91C111_CHIP_ID) != 
                  ALTERA_AVALON_LAN91C111_CHIP_ID ) 
  {
//    DEBUGF(NETIF_DEBUG | DBG_TRACE, ("Not an SMC91C111 chip\n"));
    ret_code = -EIO;
    goto exit;
  }

  /* Bank 0 */
  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr, 0);
  IOWR_ALTERA_AVALON_LAN91C111_RCR( dev->base_addr, 
                                ALTERA_AVALON_LAN91C111_RCR_SOFTRST_OFST);

  /* a very generous reset pulse */
  usleep(1000);

  IOWR_ALTERA_AVALON_LAN91C111_RCR(dev->base_addr, 0);

  /* This should be plenty of time for the device to settle */
  usleep(5000);

	/* Reset the MMU */
  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr, 2);
  IOWR_ALTERA_AVALON_LAN91C111_MMUCR( dev->base_addr,
                                  ALTERA_AVALON_LAN91C111_MMUCR_RESET_MSK);

  do {
    register_value = IORD_ALTERA_AVALON_LAN91C111_MMUCR(dev->base_addr);
  }while(register_value & ALTERA_AVALON_LAN91C111_MMUCR_BUSY_MSK);

exit:
//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("reset_device() exit = %d\n", ret_code));

  return ret_code;

}


/*
* set_mac_address
*
* Configure the MAC address of the SMSC chip
*/
static int set_mac_address(alt_avalon_lan91c111_if* dev)
{
  IOWR_ALTERA_AVALON_LAN91C111_BSR(dev->base_addr, 1);
  IOWR_ALTERA_AVALON_LAN91C111_IAR0(dev->base_addr, dev->hwaddr[0]);
  IOWR_ALTERA_AVALON_LAN91C111_IAR1(dev->base_addr, dev->hwaddr[1]);
  IOWR_ALTERA_AVALON_LAN91C111_IAR2(dev->base_addr, dev->hwaddr[2]);
  IOWR_ALTERA_AVALON_LAN91C111_IAR3(dev->base_addr, dev->hwaddr[3]);
  IOWR_ALTERA_AVALON_LAN91C111_IAR4(dev->base_addr, dev->hwaddr[4]);
  IOWR_ALTERA_AVALON_LAN91C111_IAR5(dev->base_addr, dev->hwaddr[5]);
  return 0;
}


/*
* allocate_tx_packet
*
* Allocate (within the device) the one packet we will use for all transmissions
*/
static int allocate_tx_packet( alt_avalon_lan91c111_if *dev )
{
  alt_u16 value;
  alt_u8 byte_value;
  int timeout;
  int ret_code = 0;

//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("allocate_tx_packet()\n"));

  IOWR_ALTERA_AVALON_LAN91C111_BSR(dev->base_addr, 2);
  value = IORD_ALTERA_AVALON_LAN91C111_MMUCR(dev->base_addr);
  value |= ALTERA_AVALON_LAN91C111_MMUCR_ALLOC_MSK;
  IOWR_ALTERA_AVALON_LAN91C111_MMUCR(dev->base_addr, value);

  /* Wait for the command to complete */
  timeout = 10;
  do 
  {
    byte_value = IORD_ALTERA_AVALON_LAN91C111_IST(dev->base_addr);
    usleep(100000);
    timeout --;
  }
  while((!(byte_value & ALTERA_AVALON_LAN91C111_INT_ALLOC_INT_MSK)) && 
        (timeout > 0));

  if (timeout == 0) 
  {
    ret_code = -EIO;
    goto exit;
  }

  /* Save the allocated packet number for future use */
  byte_value = IORD_ALTERA_AVALON_LAN91C111_ARR(dev->base_addr);

  if (byte_value & ALTERA_AVALON_LAN91C111_ARR_FAILED_MSK) 
  {
    ret_code = -EIO;
    goto exit;
  }

  dev->tx_packet_no = byte_value & ~ALTERA_AVALON_LAN91C111_ARR_FAILED_MSK;


exit:
//  DEBUGF(NETIF_DEBUG | DBG_TRACE, ("allocate_tx_packet() exit = %d\n", ret_code));
  return ret_code;

}


/*-----------------------------------------------------------------------------------*
 *
 * low_level_init():
 *
 *-----------------------------------------------------------------------------------*/
int alt_avalon_lan91c111_init(alt_avalon_lan91c111_if *dev)
{
  int ret_code;

  if (dev->bus_width != 32)
  {
    printf("This driver doesn't support the Ethernet add on card at present\n");
    ret_code = -EIO;
    goto exit;
  }

  ret_code = reset_device(dev);
  if (ret_code != 0) 
  {
    goto exit;
  }

  ret_code = set_mac_address(dev);
  if (ret_code != 0) 
  {
    goto exit;
  }

  ret_code = configure_phy(dev);
  if (ret_code != 0) 
  {
    goto exit;
  }

  ret_code = allocate_tx_packet(dev);
  if (ret_code != 0) 
  {
    goto exit;
  }

#if 0
  ALT_SEM_CREATE(dev->semaphore, 1);
  if (dev->semaphore == NULL)
  {
    ret_code = -ENOMEM;
    goto exit;
  }
#endif

  /* Turn on Rx & Tx */
  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr, 0);
  IOWR_ALTERA_AVALON_LAN91C111_RCR( dev->base_addr,
                                    ALTERA_AVALON_LAN91C111_RCR_STRIP_CRC_MSK | 
                                    ALTERA_AVALON_LAN91C111_RCR_RXEN_MSK);
  IOWR_ALTERA_AVALON_LAN91C111_TCR( dev->base_addr,
                                    ALTERA_AVALON_LAN91C111_TCR_TXENA_MSK |
                                    ALTERA_AVALON_LAN91C111_TCR_PAD_EN_MSK);

  /* 
  * From this point on we don't change banks again, bank 2 is all that's needed 
  * for Rx, TX and interrupt handling
  */
  IOWR_ALTERA_AVALON_LAN91C111_BSR( dev->base_addr, 2);

  /*
  * Let's make sure no interupts are enabled
  */
  IOWR_ALTERA_AVALON_LAN91C111_MSK(dev->base_addr, 0);

  /*
   *  Install ISR and turn on interrupts
   *  
   *  If you're counting stats then we also turn on the RCV_OVRN 
   *  interrupt and increment the error counter for each interrupt
   *  
   */
  if (alt_irq_register ( dev->irq, dev, alt_avalon_lan91c111_irq))
  {
    ret_code = -EIO;
    goto exit;
  }
  else
  {
    IOWR_ALTERA_AVALON_LAN91C111_MSK(dev->base_addr, 
                            ALTERA_AVALON_LAN91C111_INT_RCV_INT_MSK |
                            ALTERA_AVALON_LAN91C111_INT_RX_OVRN_INT_MSK);
  }

exit:

  return ret_code;
}

/*-----------------------------------------------------------------------------------* 
 *
 * low_level_output():
 *
 * Should do the actual transmission of the packet. The packet is
 * contained in the buf that is passed to the function.
 * 
 * This funciton should be changed to use all the available transmit
 * packets in the Lan91C111
 *-----------------------------------------------------------------------------------*/

int alt_avalon_lan91c111_output(alt_avalon_lan91c111_if *dev, void *buffer, alt_u32 length)
{
  alt_u8 irq_value;
  alt_u16 mmu_status;
  alt_u32 remainder;
  alt_u32 len = length;
  void *buf = buffer;

  /* Wait for the last Tx to complete */
  do 
  {
    irq_value = IORD_ALTERA_AVALON_LAN91C111_IST(dev->base_addr);
  }while(!(irq_value & ALTERA_AVALON_LAN91C111_INT_TX_EMPTY_INT_MSK));

  /* Clear the interrupt */
  IOWR_ALTERA_AVALON_LAN91C111_ACK( dev->base_addr, 
                                    ALTERA_AVALON_LAN91C111_INT_TX_EMPTY_INT_MSK);


  /* Always re-use the same packet */
  IOWR_ALTERA_AVALON_LAN91C111_PNR( dev->base_addr, 
                                    dev->tx_packet_no);
  IOWR_ALTERA_AVALON_LAN91C111_PTR( dev->base_addr,
                                    ALTERA_AVALON_LAN91C111_PTR_AUTO_INCR_MSK);

  /* The status word */
  IOWR_ALTERA_AVALON_LAN91C111_DATA_HW( dev->base_addr, 0);

  /* 
  * The byte count including the 6 control bytes 
  *
  * Bit odd this, but the length is always written as even, if the frame is an odd length
  * then the byte is written as one of the control words and an appropriate bit is set
  *
  */
  IOWR_ALTERA_AVALON_LAN91C111_DATA_HW( dev->base_addr, ((length & ~1) + 6));

  /* 
  * Write buffer of data to the device
  *
  * Nios requires accesses to be aligned on the correct boundary
  * 
  */
  while ((int)buf & 3)
  {
    IOWR_ALTERA_AVALON_LAN91C111_DATA_BYTE( dev->base_addr, *((alt_u8*)buf)++);
    len--;
  }

  remainder = len & 3;

  /* Write out the 32 bit values */
  len>>=2;
  while (len & ~7)        /* Write 8-tuples of 32 bit values */
  {
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    len-=8;
  }
  while (len) 
  {
    IOWR_ALTERA_AVALON_LAN91C111_DATA_WORD( dev->base_addr, *((alt_u32*)buf)++);
    len--;
  }

  while (remainder)
  {
    IOWR_ALTERA_AVALON_LAN91C111_DATA_BYTE( dev->base_addr, *((alt_u8*)buf)++);
    remainder--;
  }

  if (length & 1) 
  {
    IOWR_ALTERA_AVALON_LAN91C111_DATA_BYTE( dev->base_addr,
                                ALTERA_AVALON_LAN91C111_CONTROL_ODD_MSK);
  }
  else 
  {
    IOWR_ALTERA_AVALON_LAN91C111_DATA_HW( dev->base_addr, 0);
  }

  /* 
  * Accesses to the MMUCR have to be protected with a semaphore as it's possible 
  * that we could wait for this register not to be busy and in between our read 
  * and the write an interrupt could occur which causes the scheduler to run and
  * the ethernet_rx thread could be run!
  */

#if 0
  ALT_SEM_PEND(dev->semaphore, 1);
#endif

  /* Wait for any pending commands to complete */
  do 
  {
    mmu_status = IORD_ALTERA_AVALON_LAN91C111_MMUCR(dev->base_addr);
  }while (mmu_status & ALTERA_AVALON_LAN91C111_MMUCR_BUSY_MSK);

  /* Queue the packet */
  IOWR_ALTERA_AVALON_LAN91C111_MMUCR( dev->base_addr,
                                  ALTERA_AVALON_LAN91C111_MMUCR_ENQUEUE_MSK);
#if 0
  ALT_SEM_POST(dev->semaphore);
#endif

  return 0;
}

/*-----------------------------------------------------------------------------------* 
 *
 * low_level_input():
 *
 * Transfer the bytes of the incoming packet from the interface into a buffer
 * allocated by a callback to the caller,  returning the pointer to the packet.
 *
 * Caller must define a "get buffer" routine using its memory allocation
 * scheme, and pass the pointer in the call.
 *
 *-----------------------------------------------------------------------------------*/
void* alt_avalon_lan91c111_input(alt_avalon_lan91c111_if *dev, if_getbuf_t ifGetbuf())
{
  alt_u32 status;
  alt_u16 packet_number, mmu_status;
  alt_u32 length, remainder, len;
  void* ret_buf = 0;
  void* buf;

  packet_number = IORD_ALTERA_AVALON_LAN91C111_RX_FIFO(dev->base_addr);

  if ( packet_number & ALTERA_AVALON_LAN91C111_RX_FIFO_REMPTY_MSK ) 
  {
    return 0;
  }

  IOWR_ALTERA_AVALON_LAN91C111_PTR( dev->base_addr,
                                    ALTERA_AVALON_LAN91C111_PTR_READ_MSK |
                                    ALTERA_AVALON_LAN91C111_PTR_AUTO_INCR_MSK |
                                    ALTERA_AVALON_LAN91C111_PTR_RCV_MSK);

  /* The first two half-words are status and byte count */
  status = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
  length = (status & 0xffff0000ul) >> 16;
  status &= 0xffff;

  /* We've already read two of the words */
  length -= 4;

  if (status & (ALTERA_AVALON_LAN91C111_RS_TOO_SHORT_MSK | 
                ALTERA_AVALON_LAN91C111_RS_TOO_LONG_MSK | 
                ALTERA_AVALON_LAN91C111_RS_BAD_CRC_MSK | 
                ALTERA_AVALON_LAN91C111_RS_ALGN_ERR_MSK))  
  {
    //printf("drop (err)\n");
    dev->stat_link_drop++;
  }
  else 
  {
    buf = ret_buf = ifGetbuf(length);
    if (!buf)
    {
      //printf("drop (mem)\n");
      dev->stat_link_drop++;   /* No buffer - drop it */
    }
    else 
    {
      len = length;
      while ((int)buf & 3)   /* align the buffer */
      {
        *((alt_u8*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_BYTE(dev->base_addr);
        len--;
      }
      remainder = len & 3;
      len>>=2;
      while (len & ~7)       /* Read 8-tuples of 32 bit values */
      {
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        len-=8;
      }
      while (len)            /* Read the 32 bit values */
      {
        *((alt_u32*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_WORD(dev->base_addr);
        len--;
      }
      while (remainder)      /* Read any remainder bytes */
      {
        *((alt_u8*)buf)++ = IORD_ALTERA_AVALON_LAN91C111_DATA_BYTE(dev->base_addr);
        remainder--;
      }
    }
  }

#if 0
  ALT_SEM_PEND(dev->semaphore, 1);
#endif

  /* Wait for any pending commands to complete */
  do 
  {
    mmu_status = IORD_ALTERA_AVALON_LAN91C111_MMUCR(dev->base_addr);
  }while (mmu_status & ALTERA_AVALON_LAN91C111_MMUCR_BUSY_MSK);

  /* Just get rid of the packet */
  IOWR_ALTERA_AVALON_LAN91C111_MMUCR(dev->base_addr,
            ALTERA_AVALON_LAN91C111_MMUCR_REMOVE_RELEASE_MSK);

#if 0
  ALT_SEM_POST(dev->semaphore);
#endif

  return ret_buf;  
}


