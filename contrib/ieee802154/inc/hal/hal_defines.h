/*************************************************************************
*
* Project: ERIKA Enterprise and Open-ZB 
*          ZigBee compliant network stack for ERIKA Enterprise
*
* Coordinators:
*   Giuseppe Lipari    	<lipari@sssup.it>
*   Eduardo Tovar       <emt@dei.isep.ipp.pt>
*   Mario Alves	        <mjs@isep.ipp.pt>
*
* Authors:
*   Andre Cunha            <andreribeirocunha@gmail.com>
*   Mangesh Chitnis        <m.chitnis@sssup.it>
*   Antonio Romano         <a.romano@sssup.it>
*   Ricardo Severino       <rars@isep.ipp.pt>
*   Paolo Pagano           <p.pagano@sssup.it>
*   Christian Nastasi      <nastasichr@gmail.com>
*
* ReTiS Lab (CEIIC, Scuola Superiore S.Anna - Pisa - Italy)
* IPP-Hurray (Polytechnique Institute of Porto - Portugal)
*
* http://retis.sssup.it
* http://www.hurray.isep.ipp.pt
*
*************************************************************************
*
* Copyright (C) 2008 Andre Cunha, Mangesh Chitnis 
*                    Antonio Romano, Ricardo Severino
*                    Paolo Pagano, Christian Nastasi
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*************************************************************************
*
* CVS: 
*
* $Id: hal_defines.h,v 1.1 2008/07/04 09:45:45 chris Exp $
* $Log: hal_defines.h,v $
* Revision 1.1  2008/07/04 09:45:45  chris
* Change hal.def in hal_defines.h
*
*
*************************************************************************/

#ifndef _hal_defines_h_
#define _hal_defines_h_


//#define DEVICE_TYPE_END_DEVICE
//#define DEVICE_TYPE_COORDINATOR

#define UART1 0
#define UART2 1

#define RADIO_SPI1 0
#define RADIO_SPI2 1

#define BAUDRATE 115200

#define BUFFER_SIZE 127  

#define PA_MAXIMUM	0xFF

#ifndef __USE_DEMOBOARD__

#ifndef CONSOLE_PORT 
#define CONSOLE_PORT UART1
#endif

#define RESETn	PORTGbits.RG0
#define VREG_EN	PORTGbits.RG12
#define FIFO	PORTEbits.RE9
#define FIFOP	PORTFbits.RF6
#define CSn	PORTGbits.RG9
#define CCA	PORTGbits.RG1
#define SFD PORTEbits.RE8

#define TRIS_RESETn	TRISGbits.TRISG0
#define TRIS_VREG_EN TRISGbits.TRISG12
#define TRIS_FIFO	TRISEbits.TRISE9
#define TRIS_FIFOP	TRISFbits.TRISF6
#define TRIS_CSn	TRISGbits.TRISG9
#define TRIS_CCA	TRISGbits.TRISG1
#define TRIS_SFD 	TRISEbits.TRISE8

#else

#define CONSOLE_PORT UART2

#define RESETn	PORTGbits.RG0
#define VREG_EN	PORTGbits.RG12
#define FIFO	PORTDbits.RD14
#define FIFOP	PORTAbits.RA15
#define CSn	PORTGbits.RG9
#define CCA	PORTGbits.RG1
#define SFD PORTDbits.RD13

#define TRIS_RESETn	TRISGbits.TRISG0
#define TRIS_VREG_EN	TRISGbits.TRISG12
#define TRIS_FIFO	TRISDbits.TRISD14
#define TRIS_FIFOP	TRISAbits.TRISA15
#define TRIS_CSn	TRISGbits.TRISG9
#define TRIS_CCA	TRISGbits.TRISG1
#define TRIS_SFD 	TRISDbits.TRISD13

#endif

#endif
