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
 * version 2 along with ERIKA Enerprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
 
#ifndef	__DRIVER_H__
#define	__DRIVER_H__

extern void EE_UART1_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode);
extern void EE_UART1_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode);
extern EE_INT8 EE_UART1_Send(unsigned char data);
extern EE_INT8 EE_UART1_Receive(unsigned char* data);

extern void EE_UART2_Init(EE_UINT32 baud, EE_UINT16 byteformat, EE_UINT16 mode);
extern void EE_UART2_SetCallback(EE_INT8 (*RxFunc)(EE_UINT8 data), EE_INT8 (*TxFunc)(EE_UINT8 data), EE_UINT8 rxmode, EE_UINT8 txmode);
extern EE_INT8 EE_UART2_Send(unsigned char data);
extern EE_INT8 EE_UART2_Receive(unsigned char* data);

extern void	T1_program();
extern void	T1_clear();
#endif
