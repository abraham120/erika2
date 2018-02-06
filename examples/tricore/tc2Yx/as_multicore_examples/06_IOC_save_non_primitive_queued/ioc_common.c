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

/*
 * Simple test for IOC
 * Author: 2012 Francesco Esposito
 */
/***************************************************************************
 *
 * Init IOC
 *
 **************************************************************************/
/* To include EE_hal_begin_nested_primitive() and EE_hal_end_nested_primitive */
#include <ee_internal.h>

#include "ioc_common.h"

/*
 * Case of "event" (queued) semantics
 */
TASKParams3 EE_SHARED_UDATA EE_ioc_data[QUEUED_ELEMENTS_NUM];

EE_IOC_Buffer EE_SHARED_IDATA EE_ioc_enqueued_buffer[NUM_OF_BUFFERS] = {
    {0U, 0U, 0U, sizeof(EE_ioc_data), (EE_UINT8*)&EE_ioc_data,
    (EE_UINT8)EE_CBUFF_DATA_ACCEPTED, DATA_LENGTH, IOC_CALLBACK_NOT}
};

EE_TYPECOREID const EE_SHARED_CDATA EE_as_rpc_IOC_channels[] = {
  OS_CORE_ID_1
};

