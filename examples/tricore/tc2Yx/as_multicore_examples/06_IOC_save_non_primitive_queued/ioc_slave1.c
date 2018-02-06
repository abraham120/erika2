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
#include "test/assert/inc/ee_assert.h"

/* To include auto-generated IOC inline functions */
#include "ioc_common.h"

/* assertion data and declarations */
extern EE_TYPEASSERTVALUE EE_assertions[];

/* Result */
static Std_ReturnType result = 0x0;

TASKParams3 dummy_data_slave_callback;

/* defined by the user for receiving core/OS-Application */
void XXX_IocReceiveCB_0(void);

void XXX_IocReceiveCB_0(void)
{
    /* 22 is the last test performed by slave1.c module */
    EE_UINT32 i = 22;

    /*
     * It is recommended to empty the IOC internal
     * queues within the pull callback function (according
     * with sequence diagram shown in 9.6.3 of Autosar SWS OS).
     */
    result = IocReceive_0(&dummy_data_slave_callback);
    while (result == IOC_E_OK) {
        EE_assert(i+1, (result==IOC_E_OK), i);
        i++;
        result = IocReceive_0(&dummy_data_slave_callback);
    }

    /*
     * Notice that at the 4-th attempt to read buffer content, the buffer
     * is find empty since master core has written only three elements
     * into it (look at TaskSend5 in master core)
     */
    EE_assert(26, (result==IOC_E_NO_DATA), 25);

    EE_assert_range(0,1, 26);
    EE_assert_last();
}

/* Generated Standard function that collect the callback sequence */
void EE_as_IOC_callback_sequence ( void )
{
    /* calback configured by the user */
    XXX_IocReceiveCB_0();

    // Followed by a list of user-defined callback for each buffer
    //XXX_IocReceiveCB_1();
    //YYY_IocreceiveCB_0();
}

