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
	@file ee_spi.c
	@brief SPI library source file.
	@author Dario Di Stefano
	@date 2010
*/
#include <ee_irq.h>
#include "mcu/mico32/inc/ee_spi.h"

/******************************************************************************/
/*                              Global Variables                              */
/******************************************************************************/
/* Vectors and SPI structures definitions */

#ifdef __USE_SPI_IRQ__

#ifdef EE_SPI1_NAME_UC
DEFINE_VET_SPI(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
DEFINE_STRUCT_SPI(EE_SPI1_NAME_UC, EE_SPI1_NAME_LC)
#endif

#ifdef EE_SPI2_NAME_UC
DEFINE_VET_SPI(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
DEFINE_STRUCT_SPI(EE_SPI2_NAME_UC, EE_SPI2_NAME_LC)
#endif

#endif //#ifdef __USE_SPI_IRQ__

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#ifdef __USE_SPI_IRQ__

/* SPI Interrupt common handler */
void EE_spi_common_handler(int level)
{
	unsigned int uiValue;
	
	EE_spi_st *spisp = EE_get_spi_st_from_level(level);
	MicoSPI_t *spic = spisp->base; 
	
	uiValue = spic->status;
	
	/* received new data */
	if(uiValue & EE_SPI_STATUS_RX_RDY_MASK)
	{
        if(spic->control & EE_SPI_CTL_RX_INTR_EN_MASK)
            ;
    }
    
	/* transmitter's ready to accept new data */
    if(uiValue & EE_SPI_STATUS_TX_RDY_MASK)
	{
        if(spic->control & EE_SPI_CTL_TX_INTR_EN_MASK)
            ;
    }
    
	return;	
}

#endif //#ifdef __USE_SPI_IRQ__

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/	

/* This function reads a byte (in polling mode) */
int EE_hal_spi_read_byte_polling(MicoSPI_t *spic)
{
	EE_UINT8 dummy;

	/* wait the end of previous transmission */
	while(!EE_spi_tmt_ready(spic->status))		
		;
	/* clean overrun and reception ready flags */
	dummy = spic->rx;
	
	/* send a dummy byte on spi bus */
	spic->tx = dummy;		
	/* wait data to be received */
	while(!EE_spi_rx_ready(spic->status))
		;
	return spic->rx;
}

/* This function reads an array of bytes (in polling mode) */
int EE_hal_spi_read_buffer_polling(MicoSPI_t *spic, void *data, int len)
{
	int i;
	EE_UINT8 *buf = data;  
	EE_UINT8 dummy;

	/* wait the end of previous transmission */
	while(!EE_spi_tmt_ready(spic->status))		
		;
	/* clean overrun and reception ready flags */
	dummy = spic->rx;
	
	for(i=0; i<len; i++)
	{
		/* send a dummy byte on spi bus */
		spic->tx = dummy;
		/* wait data to be received */
		while(!EE_spi_rx_ready(spic->status))
			;
		buf[i] = spic->rx;
	}		
	return len;
}

/* This function writes an array of bytes (in polling mode) */
int EE_hal_spi_write_buffer_polling(MicoSPI_t *spic, const void *data, int len)
{
	int i;
	const EE_UINT8 *buf = data;   
	EE_UINT8 preload;
	
	for(i=0; i<len; i++)
	{
		/* pre-load for speed optimization */
		preload = buf[i];
		while(!EE_spi_tx_ready(spic->status))		
			;
		spic->tx = preload;
	}
	return len;	

}	

/* This function writes a byte (in polling mode) */
int EE_hal_spi_write_byte_polling(MicoSPI_t *spic, EE_UINT8 data)
{
	while(!EE_spi_tx_ready(spic->status))		
		;
	spic->tx = data;
		
	return 1;
}		
			
			
#ifndef __USE_SPI_IRQ__

/* This function configures the spi controller (in polling mode) */
int EE_hal_spi_config(MicoSPI_t* spic, int settings)
{
	EE_hal_spi_disable(spic);
	/* if master, deselect all slaves */									
    spic->sSelect = 0;
	spic->control = settings & EE_SPI_CTL_ALL_INTR_DIS_MASK;	
	
	return EE_SPI_OK;
}

/* This function sets SPI operating mode (in polling mode, mode available are blocking or non-blocking) */
int EE_hal_spi_set_ISR_mode(MicoSPI_t* spic, int irqf, int mode)
{
	mico32_disable_irq(irqf);
	
	return EE_SPI_OK;
}

#else

/* This function configures the spi controller (in interrupt mode) */
int EE_hal_spi_config(EE_spi_st* spisp, int settings)
{
	MicoSPI_t *spic = spisp->base; 
	
	EE_hal_spi_disable(spisp);
	/* if master, deselect all slaves */							
    spic->sSelect = 0;
	spic->control = settings;	
	
	return EE_SPI_OK;
}

/* This function sets the SPI operating mode */
int EE_hal_spi_set_ISR_mode(EE_spi_st* spisp, int mode)
{
	int ret = EE_SPI_OK;
	int old_mode;
	unsigned int intst;
	
	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	/* Register IRQ handler */
	EE_hal_spi_handler_setup(spisp);
	/* FSM */
	old_mode = spisp->mode;
	if(old_mode == mode)
		ret = EE_SPI_OK;
	else
	{	
		spisp->mode = mode; 	
		/* Buffer initialization */
		if (EE_spi_need_init_rx_buf(old_mode, mode))
			EE_buffer_init(&spisp->rxbuf, EE_SPI_MSGSIZE, EE_SPI_BUFSIZE, spisp->rxbuf.data);
		if (EE_spi_need_init_tx_buf(old_mode, mode))
			EE_buffer_init(&spisp->txbuf, EE_SPI_MSGSIZE, EE_SPI_BUFSIZE, spisp->txbuf.data);
		/* IRQ settings */
		if(EE_spi_need_enable_int(mode))
		{
			mico32_enable_irq(spisp->irqf);
			EE_hal_spi_enable_IRQ(spisp);
		}
		else
		{
			EE_hal_spi_disable_IRQ(spisp);
			mico32_disable_irq(spisp->irqf);
		}
	}		
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();

	return ret;
}

/* This function is used to set rx callback */
int EE_hal_spi_set_rx_ISR_callback(EE_spi_st* spisp, EE_ISR_callback isr_rx_callback)
{
	spisp->rxcbk = isr_rx_callback;
	
	return EE_SPI_OK;
}

/* This function is used to set tx callback */
int EE_hal_spi_set_tx_ISR_callback(EE_spi_st* spisp, EE_ISR_callback isr_tx_callback)															
{
	spisp->txcbk = isr_tx_callback;
	
	return EE_SPI_OK;
}

/* This function is used to send a byte on the bus (not yet supported) */
int EE_hal_spi_write_byte_irq(EE_spi_st* spisp, EE_UINT8 data)	// ATT! data is a message (packet)
{
	//MicoSPI_t *spic = spisp->base; 
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);
	// to do...
	// EE_spi_clear_SSO(spic->control);
	
	return 0;
}	
	
/* This function is used to read a byte from the bus (not yet supported) */
int EE_hal_spi_read_byte_irq(EE_spi_st* spisp)					// ATT! adddata is a pointer to message (packet)
{
	//MicoSPI_t *spic = spisp->base; 
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);
	// to do...
	// EE_spi_clear_SSO(spic->control);
	
	return 0;
}
	
/* This function is used to send an array of byte on the spi bus (not yet supported) */	
int EE_hal_spi_write_buffer_irq(EE_spi_st* spisp, EE_UINT8* data, int len)	// ATT! data is a vector of messages (packets)
{
	//MicoSPI_t *spic = spisp->base; 
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);
	// to do...
	// EE_spi_clear_SSO(spic->control);
	
	return 0;
}

/* This function is used to reads an array of byte on the spi bus (not yet supported) */	
int EE_hal_spi_read_buffer_irq(EE_spi_st* spisp, EE_UINT8* data, int len)	// ATT! data is a vector of messages (packets)
{
	//MicoSPI_t *spic = spisp->base; 
	// EE_hal_spi_set_slave(spic, device);	
	// EE_spi_set_SSO(spic->control);
	// to do...
	// EE_spi_clear_SSO(spic->control);
	
	return 0;
}	

/* This function reads the code of the last error condition recorded (not yet supported) */
int EE_hal_spi_return_error(EE_spi_st* spisp)
{
	return spisp->err;
}
	
#endif //#ifdef __USE_SPI_IRQ__







