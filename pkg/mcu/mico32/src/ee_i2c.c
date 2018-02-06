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
	@file ee_i2c.c
	@brief I2C library source file. 
	@author Dario Di Stefano
	@date 2010
*/

#include "mcu/mico32/inc/ee_i2c.h"

/******************************************************************************/
/*                              Global Variables                              */
/******************************************************************************/
/* Vectors and I2C structures definitions */

#ifdef __USE_I2C_IRQ__

#ifdef EE_I2C1_NAME_UC
DEFINE_VET_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
DEFINE_STRUCT_I2C(EE_I2C1_NAME_UC, EE_I2C1_NAME_LC)
#endif

#ifdef EE_I2C2_NAME_UC
DEFINE_VET_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
DEFINE_STRUCT_I2C(EE_I2C2_NAME_UC, EE_I2C2_NAME_LC)
#endif

#endif //#ifdef __USE_I2C_IRQ__

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
// ...

/******************************************************************************/
/*                              ISRs                                          */
/******************************************************************************/
#ifdef __USE_I2C_IRQ__

/* SPI Interrupt common handler */
void EE_i2c_common_handler(int level)
{
	unsigned int uiValue;
	
	EE_i2c_st *i2csp = EE_get_i2c_st_from_level(level);
	OCI2CMDev_t* i2cc = i2csp->base; 
	
	uiValue = i2cc->StatusCommand;
	
	/* received new data */
	if(uiValue & EE_I2C_STATUS_RX_RDY_MASK)
	{
        if(i2cc->Control & EE_I2C_CTL_RX_INTR_EN_MASK)
            ;
    }
    
	/* transmitter's ready to accept new data */
    if(uiValue & EE_I2C_STATUS_TX_RDY_MASK)
	{
        if(i2cc->Control & EE_I2C_CTL_TX_INTR_EN_MASK)
            ;
    }
    
	return;	
}

#endif //#ifdef __USE_I2C_IRQ__

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
/* This function is used to turn off I2C controller */
int EE_hal_i2c_disable(OCI2CMDev_t* i2cc)
{
	/* Clear the ‘EN’ bit only when no transfer is in progress, i.e. after a STOP
	   command, or when the command register has the STO bit set. When halted during a
	   transfer, the core can hang the I2C bus.  
	*/	
	EE_hal_i2c_stop(i2cc);
	
	i2cc->Control &= ~OCI2CM_CTL_CORE_ENABLE; 
	
	return EE_I2C_OK;
}

/* This function is used to send a start (or a repeated start) condition on the bus */
int EE_hal_i2c_start(OCI2CMDev_t* i2cc)		//note: all read/write functions issue a start...this function can be removed??? 
{
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);

    i2cc->StatusCommand = OCI2CM_CMD_START;

    /*
     * see if arbitration was lost; return 0 if arbitration
     * wasn't lost i.e. start was successful
     */
    if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
		return EE_I2C_ERR_ARB_LOST;
	else
    	return EE_I2C_OK;
}

/* This function is used to send a stop condition on the bus */
int EE_hal_i2c_stop(OCI2CMDev_t* i2cc)		//note: stop condition manual or not???
{
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);

    i2cc->StatusCommand = OCI2CM_CMD_STOP;

    return EE_I2C_OK;
}
		
/* This function is used to write a byte (in polling mode) */		
int EE_hal_i2c_write_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data)
{
	int ret;

	while( !EE_hal_i2c_idle(i2cc) )
		;
	/* load address, set-up a write to write the device address out to the bus */
	i2cc->Data = (device & ~EE_I2C_RW_MASK);
	/* initiate a start (repeated) and write out the address */
	i2cc->StatusCommand = (OCI2CM_CMD_START | OCI2CM_CMD_WRITE);
	/* wait for transfer to complete */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
	/* check if ack is received */
	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
		ret = EE_I2C_ERR_DEV_ACK;
	else
	{
		/* load address, set-up a write to write the address out to the bus */
		i2cc->Data = (unsigned int)address;
		/* write the data out to the bus */
		i2cc->StatusCommand = OCI2CM_CMD_WRITE;
		/* wait for transfer to complete */
		EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
		/* check if ack is received */
		if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
			ret = EE_I2C_ERR_ADD_ACK;
		else
		{
	  		/* load data in register */
	    	i2cc->Data = (unsigned int)data;
	    	/* write the data out to the bus */
	    	i2cc->StatusCommand = OCI2CM_CMD_WRITE;
	    	/* wait for current transfer to complete */
	    	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
	    	/* check for ack  and if arb was lost during this transaction */
	    	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
	        	ret = EE_I2C_ERR_DATA_ACK;
	    	else if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
				ret = EE_I2C_ERR_ARB_LOST;
			else
				ret = EE_I2C_OK;
		}
	}
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
	
	return ret;	
}

/* This function is used to read a byte (in polling mode) */	
int EE_hal_i2c_read_byte_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address)
{
	int ret;

	while( !EE_hal_i2c_idle(i2cc) )
		;
	/* load device address, set-up a write to write the device address out to the bus */
	i2cc->Data = (device & ~EE_I2C_RW_MASK);					// AFTER WRITE
	/* initiate a start (repeated) and write out the address */
	i2cc->StatusCommand = (OCI2CM_CMD_START | OCI2CM_CMD_WRITE);
	/* wait for transfer to complete */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
	/* check if ack is received */
	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
		ret = EE_I2C_ERR_DEV_ACK;
	else
	{
		/* load address, set-up a write to write the address out to the bus */
		i2cc->Data = (unsigned int)address;
		/* write the data out to the bus */
		i2cc->StatusCommand = OCI2CM_CMD_WRITE;
		/* wait for transfer to complete */
		EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
		/* check if ack is received */
		if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
			ret = EE_I2C_ERR_ADD_ACK;
		else
		{
			/* load device address, set-up a write to write the device address out to the bus */
			i2cc->Data = (device | EE_I2C_RW_MASK );			// AFTER READ
			/* initiate a start (repeated) and write out the address */
			i2cc->StatusCommand = (OCI2CM_CMD_START | OCI2CM_CMD_WRITE);
			/* wait for transfer to complete */
			EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
			/* check if ack is received */
			if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
				ret = EE_I2C_ERR_DEV_ACK;
			else
			{
				/* issue a read with a NACK */
	   			i2cc->StatusCommand = (OCI2CM_CMD_READ | OCI2CM_CMD_NACK);
	   			/* wait till transfer is in progress */
	   			EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
	   			/* read data */
	   			ret = i2cc->Data;
	   			/* check for ack  and if arb was lost during this transaction */
	   			if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
		       	 	ret = EE_I2C_ERR_ARB_LOST;
			}
		}
	}
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
		
	return ret;
}

/* This function is used to write a buffer (in polling mode) */	
int EE_hal_i2c_write_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *data, int len)
{
	int i;
	int ret;
	
	while( !EE_hal_i2c_idle(i2cc) )
		;
	/* load device address, set-up a write to write the device address out to the bus */
    i2cc->Data = (device & ~EE_I2C_RW_MASK);			// AFTER WRITE
    /* initiate a start (repeated) and write out the address */
    i2cc->StatusCommand = (OCI2CM_CMD_START | OCI2CM_CMD_WRITE);
    /* wait for transfer to complete */
    EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    /* check if ack is received */
    if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
       	ret = EE_I2C_ERR_DEV_ACK;
    else
    {
		/* load device address, set-up a write to write the device address out to the bus */
    	i2cc->Data = (unsigned int)address;
    	/* initiate a start (repeated) and write out the address */
    	i2cc->StatusCommand = OCI2CM_CMD_WRITE;
    	/* wait for transfer to complete */
    	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    	/* check if ack is received */
    	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
       		ret = EE_I2C_ERR_ADD_ACK;
       	else
       	{
    		/* transfer the bytes */
    		for ( i = 0; i < len; i++)
    		{
        		/* load data in register */
        		i2cc->Data = (unsigned int)(data[i]);
        		/* write the data out to the bus  */
        		i2cc->StatusCommand = OCI2CM_CMD_WRITE;
        		/* wait for current transfer to complete */
        		EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
        		/* check for ack */
        		if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
           			ret = EE_I2C_ERR_DATA_ACK;
    		}
    		/* see if arbitration was lost during this transaction */
    		if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
        		ret = EE_I2C_ERR_ARB_LOST;
    		else	
        		ret = EE_I2C_OK;
		}
	}
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
    
	// All done!!!
	return ret;
}	

/* This function is used to read a buffer (in polling mode) */	
int EE_hal_i2c_read_buffer_polling(OCI2CMDev_t* i2cc, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len)
{
	int i;
	int ret;

	while( !EE_hal_i2c_idle(i2cc) )
		;
	/* load device address, set-up a write to write the device address out to the bus */
	i2cc->Data = (device & ~EE_I2C_RW_MASK);			// AFTER WRITE 
	/* initiate a start (repeated) and write out the address */
	i2cc->StatusCommand = (OCI2CM_CMD_START | OCI2CM_CMD_WRITE);
	/* wait for transfer to complete */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
	/* check if ack is received */
	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
		ret = EE_I2C_ERR_DEV_ACK;
	else
	{
		/* load device address, set-up a write to write the device address out to the bus */
    	i2cc->Data = (unsigned int)address;
    	/* initiate a start (repeated) and write out the address */
    	i2cc->StatusCommand = OCI2CM_CMD_WRITE;
    	/* wait for transfer to complete */
    	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    	/* check if ack is received */
    	if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
       		ret = EE_I2C_ERR_ADD_ACK;
       	else
       	{
			/* load device address, set-up a write to write the device address out to the bus */
			i2cc->Data = (device | EE_I2C_RW_MASK);		// AFTER READ
			/* initiate a start (repeated) and write out the address */
			i2cc->StatusCommand = (OCI2CM_CMD_START | OCI2CM_CMD_WRITE);
			/* wait for transfer to complete */
			EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
			/* check if ack is received */
			if( i2cc->StatusCommand & OCI2CM_STATUS_RX_ACK )
				ret = EE_I2C_ERR_DEV_ACK;
			else
			{
				/* begin reading data */
		   		for (i = 0; i < len; i++)
		   		{
		       		/* read data; send ACK on all reads except the last one */
		       		if( i == (len - 1) )
		           		i2cc->StatusCommand = (OCI2CM_CMD_READ|OCI2CM_CMD_NACK);
		       		else
		           		i2cc->StatusCommand = (OCI2CM_CMD_READ|OCI2CM_CMD_ACK);	
		       		/* wait while transfer is in progress */
		       		EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
		       		/* read data */
		       		data[i] = (EE_UINT8)(i2cc->Data);
				}
				/* check for ack  and if arb was lost during this transaction */
				if( i2cc->StatusCommand & OCI2CM_STATUS_ARB_LOST )
					ret = EE_I2C_ERR_ARB_LOST;
				else
	        		ret = EE_I2C_OK;	// return the number of bytes received... 
			}
		}
	}
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
		
	// All done!!!
	return ret;
}
															
#ifndef __USE_I2C_IRQ__

/* This function is used to configure i2c controller (in polling mode) */	
int EE_hal_i2c_config(OCI2CMDev_t* i2cc, int baudrate, int settings)
{
	int prescale;
	
	EE_hal_i2c_disable(i2cc);		 
	EE_hal_i2c_disable_IRQ(i2cc);                       
	prescale = ((MICO32_CPU_CLOCK_MHZ/(5*baudrate)-1));
	i2cc->PrescaleLo = prescale & 0xff;                               
    i2cc->PrescaleHi = prescale >> 8;                                          
    i2cc->Data = 0;                                               
    i2cc->StatusCommand = 0;   
	EE_hal_i2c_enable(i2cc);	
	
	// All done!!!
	return EE_I2C_OK;

}

/* This function is used to set i2c controller operating mode (in polling mode) */
int EE_hal_i2c_set_mode(OCI2CMDev_t* i2cc, int mode)
{
	int ret = EE_I2C_OK;
	
	// to do...
    
	return ret;
}

#else

/* This function is used to configure i2c controller (in interrupt mode) (not yet supported) */	
int EE_hal_i2c_config(EE_i2c_st* i2csp, int baudrate, int setttings)
{
	OCI2CMDev_t *i2cc = i2csp->base; 
	
	/* disable core */
	EE_hal_i2c_disable(i2cc);		 
	/* disable interrupts */
	EE_hal_i2c_disable_IRQ(i2cc);
	///* Register IRQ handler */
	//EE_hal_i2c_handler_setup(i2csp);
	/* Load Prescaler LSB */                       
	i2cc->PrescaleLo = ((MICO32_CPU_CLOCK_MHZ/(5*baudrate)-1));  
	/* Load Prescaler MSB */                                  
    i2cc->PrescaleHi = 0;   
	/* Clear Tx Data */                                         
    i2cc->Data = 0;     
	/* Clear out all commands */                                              
    i2cc->StatusCommand = 0;   
	/* enable core */
	EE_hal_i2c_enable(i2cc);	
	
	// All done!!!
	return EE_I2C_OK;

}

/* This function is used to set i2c controller operating mode (in interrupt mode) (not yet supported) */
int EE_hal_i2c_set_mode(EE_i2c_st* i2csp, int mode)
{
	int ret = EE_I2C_OK;
	int old_mode;
	unsigned int intst;
	
	OCI2CMDev_t *i2cc = i2csp->base; 

	/* Disble IRQ */
	intst = EE_mico32_disableIRQ();
	/* Register IRQ handler */
	EE_hal_i2c_handler_setup(i2csp);
	/* FSM */
	old_mode = i2csp->mode;
	if(old_mode == mode)
		ret = EE_I2C_OK;
	else
	{	
		i2csp->mode = mode; 	
		/* Buffer initialization */
		if (EE_i2c_need_init_rx_buf(old_mode, mode))
			EE_buffer_init(&i2csp->rxbuf, EE_I2C_MSGSIZE, EE_I2C_BUFSIZE, i2csp->rxbuf.data);
		if (EE_i2c_need_init_tx_buf(old_mode, mode))
			EE_buffer_init(&i2csp->txbuf, EE_I2C_MSGSIZE, EE_I2C_BUFSIZE, i2csp->txbuf.data);
		/* IRQ settings */
		if(EE_i2c_need_enable_int(mode))
		{
			mico32_enable_irq(i2csp->irqf);
			i2cc->Control |= OCI2CM_CTL_INT_ENABLE;
		}
		else
		{
			i2cc->Control &= ~OCI2CM_CTL_INT_ENABLE;
			mico32_disable_irq(i2csp->irqf);
		}
	}		
	/* Enable IRQ */
	if (EE_mico32_are_IRQs_enabled(intst))
        EE_mico32_enableIRQ();

	return ret;
}

/* This function is used to set rx callback (not yet supported) */
int EE_hal_i2c_set_rx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_rx_callback)
{
	i2csp->rxcbk = isr_rx_callback;
	
	return EE_I2C_OK;
}

/* This function is used to set tx callback (not yet supported) */
int EE_hal_i2c_set_tx_callback(EE_i2c_st* i2csp, EE_ISR_callback isr_tx_callback)															
{
	i2csp->txcbk = isr_tx_callback;
	
	return EE_I2C_OK;
}

/* This function is used to send a byte on the bus (not yet supported) */
int EE_hal_i2c_write_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 data)	// ATT! data is a message (packet)
{
	int ret = EE_I2C_OK;
	OCI2CMDev_t *i2cc = i2csp->base; 
	
	while( !EE_hal_i2c_idle(i2cc) )
		;
		
	// to do...
	
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
    
	// All done!!!
	return ret;
}	
	
/* This function is used to read a byte from the bus (not yet supported) */
int EE_hal_i2c_read_byte_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address)			// ATT! adddata is a pointer to message (packet)
{
	int ret = EE_I2C_OK;
	OCI2CMDev_t *i2cc = i2csp->base; 
	
	while( !EE_hal_i2c_idle(i2cc) )
		;
	// to do...
	
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
    
	// All done!!!
	return ret;
}
	
/* This function is used to write an array of bytes on the bus (not yet supported) */	
int EE_hal_i2c_write_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, const EE_UINT8 *data, int len)	// ATT! data is a vector of messages (packets)
{
	int ret = EE_I2C_OK;
	OCI2CMDev_t *i2cc = i2csp->base; 
	
	while( !EE_hal_i2c_idle(i2cc) )
		;
	// to do...
	
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
    
	// All done!!!
	return ret;
}

/* This function is used to read an array of bytes (not yet supported) */
int EE_hal_i2c_read_buffer_irq(EE_i2c_st* i2csp, EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data, int len)	// ATT! data is a vector of messages (packets)
{
	int ret = EE_I2C_OK;
	OCI2CMDev_t *i2cc = i2csp->base; 
	
	while( !EE_hal_i2c_idle(i2cc) )
		;
	// to do...
	
	/* stop signal */
	EE_i2c_pend_for_TIP_done(i2cc->StatusCommand);
    i2cc->StatusCommand = OCI2CM_CMD_STOP;
    
	// All done!!!
	return ret;
}	

/* This function is used to read the code of the last error condition recorded (not yet supported) */
int EE_hal_i2c_return_error(EE_i2c_st* i2csp)
{
	return i2csp->err;
}
	
#endif //#ifdef __USE_I2C_IRQ__
