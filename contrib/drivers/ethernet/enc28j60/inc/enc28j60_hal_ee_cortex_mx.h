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
* @file   enc28j60_hal_ee_cortex_mx.h
* @brief  ENC28J60 driver - HAL for ARM Cortex MX.
* @author Errico Guidieri
* @date   2012
*/

#ifndef __ENC28J60_HAL_EE_CORTEX_MX_H__
#define __ENC28J60_HAL_EE_CORTEX_MX_H__

#if	( \
	!defined(__AUTOSAR_R4_0__)  ||	\
	!defined(__AS_DIO_DRIVER__) ||	\
	( defined(__USE_ETHERNET_IRQ__) && !defined(__AS_ICU_DRIVER__) ) || \
	!defined(__AS_SPI_DRIVER__)	\
)
#error enc28j60 driver for cortex need Autosar SPI MCAL driver!
#endif	/*
	 * 	!defined(__AUTOSAR_R4_0__) ||
	 * 	!defined(__AS_DIO_DRIVER__) ||
	 * 	( 
	 * 		defined(__USE_ETHERNET_IRQ__) &&
	 * 		!defined(__AS_ICU_DRIVER__)
	 * 	) ||
	 * 	!defined(__AS_SPI_DRIVER__)
	 */

/* Types definition */
#include "enc28j60_reg.h"
#include "enc28j60_compiler.h"

/* AS Drivers inclusions */
#include "Dio.h"
#include "Spi.h"
#ifdef	__USE_ETHERNET_IRQ__
#include "Icu.h"
#endif

/* ------------------------------------------------------------------------------- */
/* Macros used into the Ethernet driver functions */
/* ------------------------------------------------------------------------------- */

/* Symbols and macros */
#define EE_ENC28J60_DEVICE_ID     (0x01)
#define EE_ENC28J60_ADDRESS_MASK  (0x1F)
#define ENC28J60_INTERRUPT_NAME() ((void)0U)

/* Exit status for the EE_ETHERNET driver */
#define  ENC28J60_SUCCESS         (0)    /* no error */
#define  ENC28J60_FAILURE         (-19)  /* generic error */
#define  ENC28J60_ERR_SPI_INIT    (-20)  /* error in spi initialization */
#define  ENC28J60_ERR_SPI_READ    (-21)  /* spi read error */
#define  ENC28J60_ERR_SPI_WRITE   (-22)  /* spi write error */
#define  ENC28J60_ERR_DEV_NOINIT  (-23)  /* eth device error */
#define  ENC28J60_ERR_MEM_NULL    (-24)  /* eth null pointer error */

/* ------------------------------------------------------------------------------- */
/* ETHERNET driver functions list */
/* ------------------------------------------------------------------------------- */

/** @brief  enc28j60 driver initialization procedure (Check if SPI Driver is correctly configured) */
int EE_enc28j60_hal_spi_init(void);

/**
  @brief  This function is the ENC28J60 ICU Notification handler
          it takes the role of GPIO interrupt handler.
*/
void Icu_SignalNotification_ENC28J60(void);

/* The handler (Icu_SignalNotification_ENC28J60) is statically configured a compile time and the ISR
   handler is inside to ICU Driver */
#define EE_enc28j60_hal_handler_setup() ((void)0U)
#define EE_enc28j60_hal_handler(level)  ((void)0U)
/**
  @brief  This function sets the task should be called inside the interrupt handler.
*/
void EE_enc28j60_hal_set_rx_task(EE_TID task);

/**
  @brief  This function reads an ETH register.
*/
REG EE_enc28j60_hal_read_ETH_register(BYTE Address);

/**
  @brief  This function reads a MAC/MII register.
*/
REG EE_enc28j60_hal_read_MAC_MII_register(BYTE Address);

/**
  @brief  This function reads a PHY register.
*/
PHYREG EE_enc28j60_hal_read_PHY_register(BYTE Register);

/**
  @brief  This function writes on a generic register.
*/
void EE_enc28j60_hal_write_register(BYTE Address, BYTE Data);

/**
  @brief  This function writes on a PHY register.
*/
void EE_enc28j60_hal_write_PHY_register(BYTE Register, WORD Data);

/**
  @brief  This function reads a byte from the ENC28J60 memory buffer.
*/
BYTE EE_enc28j60_hal_get(void);

/**
  @brief  This function reads an array of bytes from the ENC28J60 memory buffer.
*/
WORD EE_enc28j60_hal_get_array(BYTE *val, WORD len);

/**
  @brief  This function writes a byte to the ENC28J60 memory buffer.
*/
void EE_enc28j60_hal_put(BYTE val);

/**
  @brief  This function writes an array of bytes to the ENC28J60 memory buffer.
*/
void EE_enc28j60_hal_put_array(BYTE *val, WORD len);

/**
  @brief  This function implements a binary OR on a register.
*/
void EE_enc28j60_hal_bit_field_set_register(BYTE Address, BYTE Data);

/**
  @brief  This function implements a binary AND on a register.
*/
void EE_enc28j60_hal_bit_field_clear_register(BYTE Address, BYTE Data);

/**
  @brief  This function send a software reset command.
*/
void EE_enc28j60_hal_software_reset(void);

/**
  @brief  This function resets the device (HW reset).
*/
void EE_enc28j60_hal_hardware_reset(void);

/**
  @brief  This function selects the bank.
*/
void EE_enc28j60_hal_bank_select(WORD Register);


/* INLINE functions */

/**
  @brief  This function reads a MAC register.
*/
__INLINE__ REG __ALWAYS_INLINE__ EE_enc28j60_hal_read_MAC_register(BYTE address)
{
  return EE_enc28j60_hal_read_MAC_MII_register(address);
}

/**
  @brief  This function reads a MII register.
*/
__INLINE__ REG __ALWAYS_INLINE__ EE_enc28j60_hal_read_MII_register(BYTE address)
{
  return EE_enc28j60_hal_read_MAC_MII_register(address);
}

/**
  @brief  This function writes on a ETH register.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_write_ETH_register(BYTE address, BYTE data)
{
  EE_enc28j60_hal_write_register(address, data);
}

/**
  @brief  This function writes on a MAC register.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_write_MAC_register(BYTE address, BYTE data)
{
  EE_enc28j60_hal_write_register(address, data);
}

/**
  @brief  This function writes on a MII register.
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_write_MII_register(BYTE address, BYTE data)
{
  EE_enc28j60_hal_write_register(address, data);
}

/** @brief This function provides, before resetting it,
      the notification status 1 is active 0 is idle   */
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_pending_interrupt(void){
  /* Read the real pin value, not the Icu status. Icu status reset after
     reading as dictated. The Interrupt signal is active-low so I need 
	 to negate the read */
  return !Dio_ReadChannel(DIO_CHANNEL_ENC28J60_INT); 
}

/**
  @brief  This function enables device using reset pin (turn on).
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_enable(void)
{
  /* ENC28J60 Reset Active Low */
  Dio_WriteChannel(DIO_CHANNEL_ENC28J60_RESET, STD_HIGH);
}

/**
  @brief  This function disables device using reset pin (turn off).
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_disable(void)
{
  /* ENC28J60 Reset Active Low */
  Dio_WriteChannel(DIO_CHANNEL_ENC28J60_RESET, STD_LOW);
}


#ifdef	__USE_ETHERNET_IRQ__
/**
  @brief This function enables ENC28J60 reception of interrupts. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_enable_IRQ(void)
{
  Icu_EnableEdgeDetection(ICU_ENC28J60_CHANNEL);
}

/**
  @brief This function disables ENC28J60 reception of interrupts. 
*/
__INLINE__ void __ALWAYS_INLINE__ EE_enc28j60_hal_disable_IRQ(void)
{
  Icu_DisableEdgeDetection(ICU_ENC28J60_CHANNEL);
}

/** @brief This function returns ENC28J60 reception notifications status. */
__INLINE__ int __ALWAYS_INLINE__ EE_enc28j60_hal_IRQ_enabled(void)
{
  /* The following API is not AS standard it has been added as extension for an easy porting of
     enc28j60 driver on top of AS MCAL  */
  return Icu_GetEdgeDetectionStatus(ICU_ENC28J60_CHANNEL);
}
#else	/* !__USE_ETHERNET_IRQ__ */
#define	EE_enc28j60_hal_enable_IRQ()	((void)0)
#define	EE_enc28j60_hal_disable_IRQ()	((void)0)
#define	EE_enc28j60_hal_IRQ_enabled()	((void)0)
#endif	/* !__USE_ETHERNET_IRQ__ */

#endif /* __ENC28J60_HAL_EE_CORTEX_MX_H__ */

