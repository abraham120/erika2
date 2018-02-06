/*********************************************************************
 *
 *                  Generic Typedef's
 *
 *********************************************************************
 * FileName:        generic.h
 * Dependencies:
 * Processor:       PIC18
 * Complier:        MCC18 v1.00.50 or higher
 *                  HITECH PICC-18 V8.10PL1 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
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
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Nilesh Rajbharti     7/12/04 Rel 0.9
 * Nilesh Rajbharti     11/1/04 Pre-release version
 * DF/KO                04/29/05 Microchip ZigBee Stack v1.0-2.0
 * DF/KO                07/18/05 Microchip ZigBee Stack v1.0-3.0
 * DF/KO                07/27/05 Microchip ZigBee Stack v1.0-3.1
 * DF/KO                01/09/06 Microchip ZigBee Stack v1.0-3.5
 * DF/KO                08/31/06 Microchip ZigBee Stack v1.0-3.6
 ********************************************************************/
#ifndef _GENERIC_H_
#define _GENERIC_H_

//gfranchi
//#include "Compiler.h"

#define DisInterrupt()  __asm__ volatile("disi #0x3FFF")
#define EnInterrupt()   __asm__ volatile("disi #0x0000")

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;

typedef unsigned char BYTE;                 // 8-bit

typedef unsigned short WORD;            // 16-bit

//typedef unsigned short long SWORD;          // 24-bit

typedef unsigned long DWORD;                    // 32-bit
//end gfranchi

//gfranchi
#define CLRWDT() ClrWdt()
//end gfranchi
typedef union _BYTE_VAL
{
    struct
    {
        unsigned int b0:1;
        unsigned int b1:1;
        unsigned int b2:1;
        unsigned int b3:1;
        unsigned int b4:1;
        unsigned int b5:1;
        unsigned int b6:1;
        unsigned int b7:1;
    } bits;
    BYTE Val;
} BYTE_VAL;

typedef union _WORD_VAL
{
    BYTE v[2];
    WORD Val;
    struct
    {
        BYTE LSB;
        BYTE MSB;
    } byte;
} WORD_VAL;

#define LSB(a)          ((a).v[0])
#define MSB(a)          ((a).v[1])

typedef union _DWORD_VAL
{
    DWORD Val;
    struct
    {
        BYTE LOLSB;
        BYTE LOMSB;
        BYTE HILSB;
        BYTE HIMSB;
    } byte;
    struct
    {
        WORD LSW;
        WORD MSW;
    } word;
    BYTE v[4];
    struct
    {
        unsigned int b0:1;
        unsigned int b1:1;
        unsigned int b2:1;
        unsigned int b3:1;
        unsigned int b4:1;
        unsigned int b5:1;
        unsigned int b6:1;
        unsigned int b7:1;
        unsigned int b8:1;
        unsigned int b9:1;
        unsigned int b10:1;
        unsigned int b11:1;
        unsigned int b12:1;
        unsigned int b13:1;
        unsigned int b14:1;
        unsigned int b15:1;
        unsigned int b16:1;
        unsigned int b17:1;
        unsigned int b18:1;
        unsigned int b19:1;
        unsigned int b20:1;
        unsigned int b21:1;
        unsigned int b22:1;
        unsigned int b23:1;
        unsigned int b24:1;
        unsigned int b25:1;
        unsigned int b26:1;
        unsigned int b27:1;
        unsigned int b28:1;
        unsigned int b29:1;
        unsigned int b30:1;
        unsigned int b31:1;
    } bits;
} DWORD_VAL;
#define LOWER_LSB(a)    ((a).v[0])
#define LOWER_MSB(a)    ((a).v[1])
#define UPPER_LSB(a)    ((a).v[2])
#define UPPER_MSB(a)    ((a).v[3])


#endif