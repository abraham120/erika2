/********************************************************************
* FileName:		HardwareProfile.h
* Dependencies:
* Processor:	PIC18, PIC24F, PIC24H, dsPIC30, dsPIC33
*               tested with 18F4620, dsPIC33FJ256GP710
* Hardware:		PICDEM Z, Explorer 16
* Complier:     Microchip C18 v3.04 or higher
*				Microchip C30 v2.03 or higher
* Company:		Microchip Technology, Inc.
*
* Copyright and Disclaimer Notice
*
* Copyright © 2007-2008 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy and distribute
* Software only when embedded on a Microchip microcontroller or digital
* signal controller and used with a Microchip radio frequency transceiver,
* which are integrated into your product or third party product (pursuant
* to the terms in the accompanying license agreement).
*
* You should refer to the license agreement accompanying this Software for
* additional information regarding your rights and obligations.
*
* SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
* KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
* WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A
* PARTICULAR PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE
* LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY,
* CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY
* DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO
* ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES,
* LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
* TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT
* NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*
*********************************************************************
* File Description:
*
*  This file defines functions used for demo board hardware
*
* Change History:
*  Rev   Date         Author    Description
*  1.0   2/15/2009    yfy       Initial revision
*  2.0   4/15/2009    yfy       MiMAC and MiApp revision
********************************************************************/

/********************************************************************
* Some parts of the file have been either modified or added to add
* the support for the MiniFlex and Flex Demoboard. The modified/added part
* are identified by the mark GF.
* Author:
*        Gianluca Franchino
*        CEIICP, Scuola Superiore Sant'Anna
*        Pisa, Italy.
* Starting date: March 10th 2010.
*/

#ifndef _HARDWARE_PROFILE_H
    #define _HARDWARE_PROFILE_H

    #include "GenericTypeDefs.h"
    #include "ConfigApp.h"

	#if defined(MINIFLEX)
	#include "ee_spi.h"
	#endif

    BYTE ButtonPressed(void);
    void BoardInit(void);

    void LCDDisplay(char *, BYTE, BOOL);
    void LCDTRXCount(BYTE, BYTE);

    //#define PICDEMZ
    //#define PIC18_EXPLORER
    //#define EXPLORER16

	// Start GF
	//#define FLEX_DEMOBOARD
	#define MINIFLEX
	// End GF

    #if defined(PIC18_EXPLORER)
        #define CLOCK_FREQ 10000000

        // Transceiver Configuration
        #if defined(MRF49XA)
            #define RFIF INTCON3bits.INT3IF
            #define RFIE INTCON3bits.INT3IE
            #define PHY_CS LATCbits.LATC2
            #define PHY_CS_TRIS TRISCbits.TRISC2
            #define RF_INT_PIN  PORTBbits.RB3
            #define RF_INT_TRIS TRISBbits.TRISB3
            #define nFSEL       LATEbits.LATE3
            #define nFSEL_TRIS  TRISEbits.TRISE3
            #define FINT		PORTBbits.RB4
            #define FINT_TRIS   TRISBbits.TRISB4
        #else
            #define RFIF INTCON3bits.INT1IF
            #define RFIE INTCON3bits.INT1IE
            #define PHY_CS LATBbits.LATB3
            #define PHY_CS_TRIS TRISBbits.TRISB3
            #define RF_INT_PIN  PORTBbits.RB1
            #define RF_INT_TRIS TRISBbits.TRISB1

            #define PHY_WAKE LATBbits.LATB4
            #define PHY_WAKE_TRIS TRISBbits.TRISB4
        #endif

        #define SPI_SDI     PORTCbits.RC4
        #define SDI_TRIS    TRISCbits.TRISC4
        #define SPI_SDO     LATCbits.LATC5
        #define SDO_TRIS    TRISCbits.TRISC5
        #define SPI_SCK     LATCbits.LATC3
        #define SCK_TRIS    TRISCbits.TRISC3

        #define PHY_RESETn LATBbits.LATB5
        #define PHY_RESETn_TRIS TRISBbits.TRISB5

        #define PUSH_BUTTON_1   PORTBbits.RB0
        #define BUTTON_1_TRIS   TRISBbits.TRISB0
        #define PUSH_BUTTON_2   PORTAbits.RA5
        #define BUTTON_2_TRIS   TRISAbits.TRISA5


        #define LED_1       LATDbits.LATD7
        #define LED_1_TRIS  TRISDbits.TRISD7
        #define LED_2       LATDbits.LATD6
        #define LED_2_TRIS  TRISDbits.TRISD6

        #define TMRL TMR0L

    #endif


    #if defined(EXPLORER16)

        #if defined(__PIC32MX__)
            #define CLOCK_FREQ 64000000
            #define RFIF IFS0bits.INT1IF
            #define RFIE IEC0bits.INT1IE
        #else
            #define CLOCK_FREQ 8000000
            #define RFIF IFS1bits.INT1IF
            #define RFIE IEC1bits.INT1IE
        #endif

        #if defined(__PIC24F__) || defined(__PIC32MX__)
            #define RF_INT_PIN PORTEbits.RE8
            #define RF_INT_TRIS TRISEbits.TRISE8
        #elif defined(__dsPIC33F__) || defined(__PIC24H__)
            #define RF_INT_PIN PORTAbits.RA12
            #define RF_INT_TRIS TRISAbits.TRISA12
        #endif

        #define TMRL TMR2
    // Transceiver Configuration
        #define PHY_CS LATBbits.LATB2
        #define PHY_CS_TRIS TRISBbits.TRISB2
        #define PHY_RESETn LATGbits.LATG2
        #define PHY_RESETn_TRIS TRISGbits.TRISG2

        #define SPI_SDI     PORTFbits.RF7
        #define SDI_TRIS    TRISFbits.TRISF7
        #define SPI_SDO     LATFbits.LATF8
        #define SDO_TRIS    TRISFbits.TRISF8
        #define SPI_SCK     LATFbits.LATF6
        #define SCK_TRIS    TRISFbits.TRISF6

        #if defined(MRF49XA)
            #define nFSEL       LATBbits.LATB1
            #define nFSEL_TRIS  TRISBbits.TRISB1
            #define FINT		PORTEbits.RE9
            #define FINT_TRIS   TRISEbits.TRISE9
        #else
            #define PHY_WAKE LATGbits.LATG3
            #define PHY_WAKE_TRIS TRISGbits.TRISG3
        #endif

        #define PUSH_BUTTON_1 PORTDbits.RD6
        #define PUSH_BUTTON_2 PORTDbits.RD7
        #define LED_1 LATAbits.LATA7
        #define LED_2 LATAbits.LATA6

        #define BUTTON_1_TRIS TRISDbits.TRISD6
        #define BUTTON_2_TRIS TRISDbits.TRISD7
        #define LED_1_TRIS TRISAbits.TRISA7
        #define LED_2_TRIS TRISAbits.TRISA6


        #define EE_nCS_TRIS     TRISFbits.TRISF1
        #define EE_nCS          LATFbits.LATF1

    #endif




    #if defined(PICDEMZ)
        #define CLOCK_FREQ 16000000

        // Transceiver Configuration
        #define RFIF INTCONbits.INT0IF
        #define RFIE INTCONbits.INT0IE
        #define PHY_CS LATCbits.LATC0
        #define PHY_CS_TRIS TRISCbits.TRISC0
        #define PHY_RESETn LATCbits.LATC2
        #define PHY_RESETn_TRIS TRISCbits.TRISC2
        #define PHY_WAKE LATCbits.LATC1
        #define PHY_WAKE_TRIS TRISCbits.TRISC1

        #define PUSH_BUTTON_1 PORTBbits.RB5
        #define PUSH_BUTTON_2 PORTBbits.RB4
        #define LED_1 LATAbits.LATA0
        #define LED_2 LATAbits.LATA1

        #define BUTTON_1_TRIS TRISBbits.TRISB5
        #define BUTTON_2_TRIS TRISBbits.TRISB4
        #define LED_1_TRIS TRISAbits.TRISA0
        #define LED_2_TRIS TRISAbits.TRISA1

        #define RF_INT_PIN PORTBbits.RB0
        #define RF_INT_TRIS TRISBbits.TRISB0

        #define SPI_SDI     PORTCbits.RC4
        #define SDI_TRIS    TRISCbits.TRISC4
        #define SPI_SDO     LATCbits.LATC5
        #define SDO_TRIS    TRISCbits.TRISC5
        #define SPI_SCK     LATCbits.LATC3
        #define SCK_TRIS    TRISCbits.TRISC3

        #define TMRL TMR0L
    #endif

//Start GF
 	#if defined(__EE_MINIFLEX__)
		#if !defined(__PIC24F__)
			#define __PIC24F__
		#endif

		#if !defined(__PIC24F__)
			#error "MINIFLEX defined without selecting the correct MCU (__PIC24F__)"
		#endif

 /*       #if defined(__PIC32MX__)
            #define CLOCK_FREQ 64000000
            #define RFIF IFS0bits.INT1IF
            #define RFIE IEC0bits.INT1IE
        #else
            #define CLOCK_FREQ 8000000
            #define RFIF IFS1bits.INT1IF
            #define RFIE IEC1bits.INT1IE
        #endif

        #if defined(__PIC24F__) || defined(__PIC32MX__)
            #define RF_INT_PIN PORTEbits.RE8
            #define RF_INT_TRIS TRISEbits.TRISE8
        #elif defined(__dsPIC33F__) || defined(__PIC24H__)
            #define RF_INT_PIN PORTAbits.RA12
            #define RF_INT_TRIS TRISAbits.TRISA12
        #endif
*/
		#define CLOCK_FREQ 16000000 //GF check the PIC24J32GA004 datasheet out for the correct value
        #define RFIF IFS0bits.INT0IF
        #define RFIE IEC0bits.INT0IE
        #define RF_INT_PIN PORTBbits.RB7
        #define RF_INT_TRIS TRISBbits.TRISB7
        #define TMRL TMR2
    // Transceiver Configuration
        #define PHY_CS LATCbits.LATC4
        #define PHY_CS_TRIS TRISCbits.TRISC4
        #define PHY_RESETn LATAbits.LATA7
        #define PHY_RESETn_TRIS TRISAbits.TRISA7

        #define SPI_SDI     PORTCbits.RC7
        #define SDI_TRIS    TRISCbits.TRISC7
        #define SPI_SDO     LATCbits.LATC6
        #define SDO_TRIS    TRISCbits.TRISC6
        #define SPI_SCK     LATCbits.LATC5
        #define SCK_TRIS    TRISCbits.TRISC5

        #define PHY_WAKE LATAbits.LATA8
        #define PHY_WAKE_TRIS TRISAbits.TRISA8


        //#define PUSH_BUTTON_1 PORTDbits.RD6
        //#define PUSH_BUTTON_2 PORTDbits.RD7
        #define SYSTEM_LED LATAbits.LATA10
        //#define LED_2 LATAbits.LATA6

        //#define BUTTON_1_TRIS TRISDbits.TRISD6
        //#define BUTTON_2_TRIS TRISDbits.TRISD7
        #define SYSTEM_LED_TRIS TRISAbits.TRISA10
        //#define LED_2_TRIS TRISAbits.TRISA6

        //#define EE_nCS_TRIS     TRISFbits.TRISF1
        //#define EE_nCS          LATFbits.LATF1

		#ifdef __EE_MINIFLEX__
		#include "mcu/microchip_dspic/inc/ee_spi.h"
			#define SPIPut(a) EE_spi_write_byte(EE_SPI_PORT_1, a) //dsPIC33F_radio_spi_put(a)
			//#define SPIGet() dsPIC33F_radio_spi_get() //dsPIC33F_radio_spi_get()
			static inline unsigned char SPIGet()
			{
				unsigned char data = 0;
				EE_spi_read_byte(EE_SPI_PORT_1, &data);
				return data;
			}
		#endif

    #endif
//End GF

#endif
