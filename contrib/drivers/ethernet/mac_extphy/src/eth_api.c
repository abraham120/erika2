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
* @file 	eth_api.c
* @brief 	MAC layer configuration and external API.
* @author 	Dario Di Stefano
* @date 	2011
*/ 

#include "eth_api.h"
#include "string.h"

/* ---------------------- Global variables --------------------------------- */
/**
 * ETH driver structure.
 */
volatile EE_eth_st ee_eth_st = {
	.irqf = 0,
	.task= -1 }; 
	
/**
 * To store MAC address.
 */
MAC_ADDR ee_myMACaddress; 

/* 	This function initializes the MAC layer and PHY device. */
void EE_eth_init(MAC_ADDR myMACaddress)
{
	int dbg_res;
	
	/* Console initialization */
	if( EE_extphy_debug_init() == ETHEXTPHY_DEBUG_OK)
		dbg_res = EE_extphy_dbg_print("ETHEXTPHY_DEBUG: console initialized!\n");
	
	/* PHY hw initialization */
	EE_phy_on();
	/* MAC layer initialization */
    //TickInit();
	MACInit(myMACaddress);
	dbg_res = EE_extphy_dbg_print("ETHEXTPHY_DEBUG: MAC layer initialized!\n");
}
    
/**
	This function enables ETHERNET reception interrupts. 
*/
int EE_eth_clear_irq_flag(void)
{
	int flags = EE_ETH_READ_INT_EVENTS();    // read the interrupt flags (requests)
	EE_ETH_ACK_INT_FLAGS(flags);             // Acknowledge interrupts flags
	EE_ETH_INT_FLAG_CLR();                   // Be sure to clear the Ethernet Controller Interrupt
	return flags;
}

/**
	This function enables ETHERNET reception interrupts. 
*/
void EE_eth_init_IRQ(void)
{
	EE_ETH_ENABLE_INT_EVENTS(EE_ETH_INT_EVENTS);               // enable the interrupt events
	EE_ETH_SET_PRIORITY(EE_ETH_INT_PRIO, EE_ETH_INT_SUBPRIO);  // Set priority and sub-priority 
}

/**
	This function enables ETHERNET reception interrupts. 
*/
void EE_eth_enable_IRQ(void)
{
	EE_ETH_INT_FLAG_CLR();                                     // Be sure to clear the Ethernet Controller Interrupt
	EE_ETH_INT_ENABLE();                                       // enable the Ethernet Controller interrupt
}

/**
	This function disables ETHERNET reception interrupts. 
*/
void EE_eth_disable_IRQ(void)
{
	EE_ETH_INT_DISABLE();                                      // Disable the Ethernet Controller interrupt
	EE_ETH_INT_FLAG_CLR();                                     // Be sure to clear the Ethernet Controller Interrupt
}

/**
	This function provides, before resetting it, the status of the pending 
	interrupt flag
*/
int EE_eth_pending_interrupt(void){ 
	return EE_ETH_READ_PENDINT_FLAG();      // Read pending interrupts/packets flag
}

/* Ethernet interrupt handler */
EE_ETH_HAL_HANDLER(){
	EE_eth_disable_IRQ();
	/* Clear IRQ flags and IRQ status flags */
	EE_eth_clear_irq_flag();
	/* Set the internal irqf to "interrupt occured" value  */
	EE_eth_irq_int_write(EE_ETH_IRQ_PENDING); 
	/* Called task should re-enable IRQs after that all packets are read
	and interrupt flag is cleared */
	if ( ee_eth_st.task != ((EE_TID)-1) ){
		ActivateTask(ee_eth_st.task);
	}
}



