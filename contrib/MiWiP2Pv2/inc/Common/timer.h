/*********************************************************************
 *
 *                   Timer
 *
 *********************************************************************
 * FileName:        timer.h
 * Processor:       PIC24 /  Daytona
 * Complier:        MPLAB C30/C32
 *
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement:
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its dsPIC30F and PICmicro® Microcontroller is intended 
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip's dsPIC30F and PICmicro Microcontroller products. 
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date      Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * 
 *
 ********************************************************************/

#ifndef _MS_TIMER_HEADER_FILE
#define _MS_TIMER_HEADER_FILE

#ifndef __GENERIC_TYPE_DEFS_H_
#include "GenericTypeDefs.h"
#endif

#if defined(__18CXX)
    #include <delays.h>
    // assumes here that MCU at least run 4MHz to reach 1MIPS, otherwise, it is hard to track
    // the timing
    #define MIPS    ((DWORD)CLOCK_FREQ/(DWORD)4000000)
 
    #define delay_us(x) { BYTE i; for(i = 0; i < MIPS; i++) Nop(); }
    #define delay_ms(x) { BYTE i; for(i = 0; i < MIPS; i++) Delay1KTCYx(x); }

#else
    
    #if defined(__C30__)
        #define INSTRUCTION_CLOCK       (CLOCK_FREQ/2)
    #else
        #define INSTRUCTION_CLOCK       (CLOCK_FREQ)
    #endif
    
    #define delay_us(x)             \
    {                               \
        unsigned long _dcnt;        \
        _dcnt=x*((unsigned long)(0.00001/(1.0/INSTRUCTION_CLOCK)/6));   \
        while(_dcnt--);             \
    }
    
    #define delay_ms(x)             \
    {                               \
        unsigned long _dcnt;        \
        unsigned long _ms;          \
        _ms = x;                    \
        while(_ms)                  \
        {                           \
            _dcnt=((unsigned long)(0.001/(1.0/INSTRUCTION_CLOCK)/6));    \
            while(_dcnt--);         \
            _ms--;                  \
        }                           \
    }
#endif


#endif
