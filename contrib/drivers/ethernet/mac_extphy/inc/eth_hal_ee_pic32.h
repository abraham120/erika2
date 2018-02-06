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
 

/** 
* @file 	eth_hal_ee_pic32.h
* @brief 	Ethernet driver abstraction for pic32 
            (MAC layer can be found in "ETHPIC32IntMac.c")
* @author 	Dario Di Stefano
* @date 	2011
*/ 

#ifndef __ETH_HAL_EE_PIC32_H__
#define __ETH_HAL_EE_PIC32_H__

/* Needed header files */
#include "cpu/pic32/inc/ee_internal.h"
#include "cpu/pic32/inc/ee_irqstub.h"
#include <cpu/pic32/inc/ee_utils.h>

/* Types definition */
#include "eth_compiler.h"

/* ---------------------------------------------------------------------------*/
/* Macros used into the Ethernet driver functions */
/* ---------------------------------------------------------------------------*/

#define EMAC_TX_DESCRIPTORS		2		// number of the TX descriptors to be created
#define EMAC_RX_DESCRIPTORS		8		// number of the RX descriptors and RX buffers to be created 
#define	EMAC_RX_BUFF_SIZE		1536	// size of a RX buffer. should be multiple of 16
										// this is the size of all receive buffers processed by the ETHC
										// The size should be enough to accomodate any network received packet
										// If the packets are larger, they will have to take multiple RX buffers
										// The current implementation does not handle this situation right now and the packet is discarded.

#define MAC_TX_BUFFER_SIZE		(1500ul)
#define MAC_IP      			(0x00u)
#define MAC_UNKNOWN 			(0xFFu)
// Base RAM and ROM pointer types
#define PTR_BASE				DWORD
#define ROM_PTR_BASE			DWORD

// All TICKS are stored as 32-bit unsigned integers.
#define EE_eth_get_peripheral_clock()		EE_get_peripheral_clock()		// Internal core clock drives timer with 1:256 prescaler
#define EE_eth_get_core_timer_value()		EE_pic32_get_core_timer_value()	// read core timer
#define GetSystemClock()					EE_get_system_clock()

/* Exit status for the EE_ETHERNET driver */
#define	EE_ETH_SUCCESS             (0)      /* no error */
#define	EE_ETH_FAILURE             (-19)    /* generic error */
#define	EE_ETH_ERR_SPI_INIT        (-20)    /* error in spi initialization */
#define	EE_ETH_ERR_SPI_READ        (-21)    /* spi read error */
#define	EE_ETH_ERR_SPI_WRITE       (-22)    /* spi write error */
#define	EE_ETH_ERR_DEV_NOINIT      (-23)    /* eth device error */
#define	EE_ETH_ERR_MEM_NULL        (-24)    /* eth null pointer error */

/* ISR handler for the external Interrupt */
#define EE_ETH_HAL_HANDLER()  ISR2(_ETH_VECTOR) 

#ifndef EE_ETH_INT_PRIO
#define EE_ETH_INT_PRIO         5
#endif
#ifndef EE_ETH_INT_SUBPRIO
#define EE_ETH_INT_SUBPRIO      2
#endif

#define EE_ETH_READ_PENDINT_FLAG()   ETHIRQbits.RXDONE        // Pending isr flag 
#define EE_ETH_READ_INT_EVENTS()     ETHIRQ
#define EE_ETH_INT_DISABLE()         IEC1CLR=0x10000000       // disable Ethernet interrupts
#define EE_ETH_INT_ENABLE()          IEC1SET=0x10000000       // enable the Ethernet Controller interrupt
#define EE_ETH_INT_ENABLE_GET()      IEC1bits.ETHIE
#define EE_ETH_INT_FLAG_CLR()        IFS1CLR=0x10000000       // Be sure to clear the Ethernet Controller Interrupt
#define EE_ETH_ACK_INT_FLAGS(f)      ETHIRQCLR=f
#define EE_ETH_ENABLE_INT_EVENTS(e)  ETHIENSET=e
#define EE_ETH_INT_EVENTS            (0x00000080)             // In ISR mode use RXDONE interrupts
#define EE_ETH_SET_PRIORITY(prio,subprio)     { EE_ETH_INT_DISABLE();             \
                                                IPC12CLR = 0x0000001f;            \
                                                IPC12SET = (prio << 2) | subprio; }

#endif /* __ETH_HAL_EE_PIC32_H__ */

