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
	@file ee_buffer.c
	@brief Buffer library source file. 
	@author Dario Di Stefano
	@date 2010
*/

#include "mcu/mico32/inc/ee_buffer.h"

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/

/* This functions initializes the buffer */
int EE_buffer_init(EE_buffer *buf, int msgsize, int bufsize, EE_UINT8 *vet)
{
	unsigned int intst;
  
	intst = EE_mico32_disableIRQ();				
	buf->g = 0;
  	buf->p = 0;
  	buf->counter = 0;
  	buf->msg_size = msgsize;
  	buf->buf_size = bufsize;
  	buf->data = vet;
	if (EE_mico32_are_IRQs_enabled(intst))		
        EE_mico32_enableIRQ();
        
  	// All done!!!
  	return EE_BUF_OK;	  	
}

/* This functions verifies if the buffer is empty */
int EE_buffer_isempty(EE_buffer *buf)
{
	int retvalue;
	unsigned int intst;
	
	intst = EE_mico32_disableIRQ();				
	if((buf->g == buf->p) && (buf->counter==0))
		retvalue = 1;
	else
		retvalue = 0; 	
	if (EE_mico32_are_IRQs_enabled(intst))		
        EE_mico32_enableIRQ();
	
	return retvalue;	
}

/* This functions verifies if the buffer is full */
int EE_buffer_isfull(EE_buffer *buf)
{
	int retvalue;
	unsigned int intst;
	
	intst = EE_mico32_disableIRQ();				
	if((buf->g == buf->p) && (buf->counter==buf->buf_size))
		retvalue = 1;
	else
		retvalue = 0;
	if (EE_mico32_are_IRQs_enabled(intst))		
        EE_mico32_enableIRQ();
		
	return retvalue;	
}

/* This functions puts a message in the buffer (push in queue) */
int EE_buffer_putmsg(EE_buffer *buf, EE_UINT8* msg)
{
	int retvalue;
	int i=0;
	unsigned int intst;
	
	if(msg==NULL)
		return EE_BUF_ERR_NULL;
	
	intst = EE_mico32_disableIRQ();				
	if((buf->g == buf->p) && (buf->counter==buf->buf_size))
		retvalue = EE_BUF_ERR_FULL;
	else
	{ 	
		for(i=0;i<(buf->msg_size);i++)	
    		buf(buf->p,i) = msg[i];				
    	buf->p++;
    	if(buf->p == buf->buf_size)
    		buf->p = 0;							
    	buf->counter++;
    	retvalue = EE_BUF_OK;
	}
    if (EE_mico32_are_IRQs_enabled(intst))		
        EE_mico32_enableIRQ();
    
  	return retvalue;
}

/* This functions extracts a message from the buffer (pull from the queue) */
int EE_buffer_getmsg(EE_buffer *buf, EE_UINT8* msg)
{
	int retvalue;
	int i=0;
	unsigned int intst;
	
	if(msg==NULL)
		return EE_BUF_ERR_NULL;
	
	intst = EE_mico32_disableIRQ();				
	if((buf->g == buf->p) && (buf->counter==0)) 
		retvalue = EE_BUF_ERR_EMPTY; 
	else
	{	
  		for(i=0;i<(buf->msg_size);i++)	
    		msg[i] = buf(buf->g,i);				
  		buf->g++;
  		if(buf->g == buf->buf_size)
  			buf->g = 0;							
  		buf->counter--;
  		retvalue = EE_BUF_OK;
	}
  	if (EE_mico32_are_IRQs_enabled(intst))		
        EE_mico32_enableIRQ();
  	
  	return retvalue;
}


