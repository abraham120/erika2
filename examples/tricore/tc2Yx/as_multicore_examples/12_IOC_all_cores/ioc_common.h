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

#ifndef IOC_COMMON_H
#define IOC_COMMON_H

extern EE_IOC_Buffer EE_SHARED_IDATA EE_ioc_enqueued_buffer[];

/* Dummy typedefs */
/* This typedef is normally defined in Std_Types.h. Added here just to build */
typedef	EE_UINT8	Std_ReturnType;
typedef	EE_UINT8	uint8;
typedef	EE_UINT16	uint16;
typedef	EE_UINT32	uint32;
typedef	EE_INT16	sint16;
/* TODO: take into account that rte knows Autosar primitive types: uint8,
   uint16, etc. Typedefs above have been added just to emulate the availability
   of such types */

#define TYPE_USED           IOC_NON_PRIMITIVE_TYPE  /**< Type used */
#define DATA_LENGTH1        sizeof(EE_ioc_data1[0]) /**< Element dimension */
#define DATA_LENGTH2        sizeof(EE_ioc_data2[0]) /**< Element dimension */
#define DATA_LENGTH3        sizeof(EE_ioc_data3[0]) /**< Element dimension */
#define IOC_SEMANTIC        IOC_QUEUED              /**< Semantic: queued */
#define QUEUED_ELEMENTS_NUM 5U                      /**< Maximum number of
                                                    element in queue **/

/*                            WORKAROUND                           */
/* This will be generated inside eecfg.h by RT-Druid IOC Generator */
#if ( EE_CURRENTCPU == 1 )
#define EE_AS_IOC_HAS_CALLBACKS__
#endif /* EE_CURRENTCPU == 1 */

/* This will be generated inside eecfg.h by RT-Druid IOC Generator */
#if ( EE_CURRENTCPU == 2 )
#define EE_AS_IOC_HAS_CALLBACKS__
#endif /* EE_CURRENTCPU == 2 */

typedef enum {
    BUFF_ID0,
    BUFF_ID1,
    BUFF_ID2,
    NUM_OF_BUFFERS
} buffer_ids;

typedef struct TASKParams3 {
    int a;
    int b;
    char c[10];
} TASKParams3;

__INLINE__ Std_ReturnType __ALWAYS_INLINE__ IocSend_0(TASKParams3 * data)
{
    Std_ReturnType  result;
    EE_FREG         flags = EE_hal_suspendIRQ();

    /* generated only in case of interprocessor comunication */
    EE_as_GetSpinlock(spinlock_1);

    result = IocSend((EE_UINT8)0U, (EE_IOC_DATA_PTR)data);

    /* generated only in case of interprocessor comunication */
    EE_as_ReleaseSpinlock(spinlock_1);

    EE_hal_resumeIRQ(flags);

    /* Call Callback if configured */
    if (EE_ioc_enqueued_buffer[0].callback == IOC_CALLBACK_YES) {
        EE_as_IOC_signal_callbacks( BUFF_ID0 );
    }

    return result;
}

__INLINE__ Std_ReturnType __ALWAYS_INLINE__ IocSend_1(TASKParams3 * data)
{
    Std_ReturnType  result;
    EE_FREG         flags = EE_hal_suspendIRQ();

    /* generated only in case of interprocessor comunication */
    EE_as_GetSpinlock(spinlock_2);

    result = IocSend((EE_UINT8)1U, (EE_IOC_DATA_PTR)data);

    /* generated only in case of interprocessor comunication */
    EE_as_ReleaseSpinlock(spinlock_2);

    EE_hal_resumeIRQ(flags);

    /* Call Callback if configured */
    if (EE_ioc_enqueued_buffer[1].callback == IOC_CALLBACK_YES) {
        EE_as_IOC_signal_callbacks( BUFF_ID1 );
    }

    return result;
}

__INLINE__ Std_ReturnType __ALWAYS_INLINE__ IocSend_2(TASKParams3 * data)
{
    Std_ReturnType  result;
    EE_FREG         flags = EE_hal_suspendIRQ();

    /* generated only in case of interprocessor comunication */
    EE_as_GetSpinlock(spinlock_3);

    result = IocSend((EE_UINT8)2U, (EE_IOC_DATA_PTR)data);

    /* generated only in case of interprocessor comunication */
    EE_as_ReleaseSpinlock(spinlock_3);

    EE_hal_resumeIRQ(flags);

    /* Call Callback if configured */
    if (EE_ioc_enqueued_buffer[2].callback == IOC_CALLBACK_YES) {
        EE_as_IOC_signal_callbacks( BUFF_ID2 );
    }

    return result;
}

__INLINE__ Std_ReturnType __ALWAYS_INLINE__ IocReceive_0(TASKParams3 * data)
{
    Std_ReturnType  result;
    EE_FREG         flags = EE_hal_suspendIRQ();

    /* generated only in case of interprocessor comunication */
    EE_as_GetSpinlock(spinlock_1);

    result = IocReceive((EE_UINT8)0U, (EE_IOC_DATA_PTR)data);

    /* generated only in case of interprocessor comunication */
    EE_as_ReleaseSpinlock(spinlock_1);

    EE_hal_resumeIRQ(flags);

    return result;
}

__INLINE__ Std_ReturnType __ALWAYS_INLINE__ IocReceive_1(TASKParams3 * data)
{
    Std_ReturnType  result;
    EE_FREG         flags = EE_hal_suspendIRQ();

    /* generated only in case of interprocessor comunication */
    EE_as_GetSpinlock(spinlock_2);

    result = IocReceive((EE_UINT8)1U, (EE_IOC_DATA_PTR)data);

    /* generated only in case of interprocessor comunication */
    EE_as_ReleaseSpinlock(spinlock_2);

    EE_hal_resumeIRQ(flags);

    return result;
}

__INLINE__ Std_ReturnType __ALWAYS_INLINE__ IocReceive_2(TASKParams3 * data)
{
    Std_ReturnType  result;
    EE_FREG         flags = EE_hal_suspendIRQ();

    /* generated only in case of interprocessor comunication */
    EE_as_GetSpinlock(spinlock_3);

    result = IocReceive((EE_UINT8)2U, (EE_IOC_DATA_PTR)data);

    /* generated only in case of interprocessor comunication */
    EE_as_ReleaseSpinlock(spinlock_3);

    EE_hal_resumeIRQ(flags);

    return result;
}


#endif
