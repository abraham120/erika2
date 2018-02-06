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

/*
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: ee_mcuregs.h,v 1.3 2005/03/10 10:00:01 pj Exp $
 */

#include "cpu/arm7tdmi/inc/ee_cpu.h"

#ifndef __INCLUDE_MCU_SAMSUNG_KS32C50100_MCUREGS__
#define __INCLUDE_MCU_SAMSUNG_KS32C50100_MCUREGS__

/* base I/O address */
#define SYSCFG_BASE    0x03FF0000	

/* System Manager registers */

#define SYSCFG ((volatile EE_ADDR)(SYSCFG_BASE + 0x0000)) /* R/W System configuration register */

#define CLKCON ((volatile EE_ADDR)(SYSCFG_BASE + 0x3000)) /* R/W Clock control register */
#define EXTACON0 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3008)) /* R/W External I/O timing register 1 */
#define EXTACON1 ((volatile EE_ADDR)(SYSCFG_BASE + 0x300C)) /* R/W External I/O timing register 2 */
#define EXTDBWTH ((volatile EE_ADDR)(SYSCFG_BASE + 0x3010)) /* R/W Data bus width for each memory bank */
#define ROMCON0 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3014)) /* R/W ROM/SRAM/Flash bank 0 control register  */
#define ROMCON1 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3018)) /* R/W ROM/SRAM/Flash bank 1 control register */
#define ROMCON2 ((volatile EE_ADDR)(SYSCFG_BASE + 0x301C)) /* R/W ROM/SRAM/Flash bank 2 control register */
#define ROMCON3 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3020)) /* R/W ROM/SRAM/Flash bank 3 control register */
#define ROMCON4 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3024)) /* R/W ROM/SRAM/Flash bank 4 control register */
#define ROMCON5 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3028)) /* R/W ROM/SRAM/Flash bank 5 control register */
#define DRAMCON0 ((volatile EE_ADDR)(SYSCFG_BASE + 0x302C)) /* R/W DRAM bank 0 control register */
#define DRAMCON1 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3030)) /* R/W DRAM bank 1 control register */
#define DRAMCON2 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3034)) /* R/W DRAM bank 2 control register */
#define DRAMCON3 ((volatile EE_ADDR)(SYSCFG_BASE + 0x3038)) /* R/W DRAM bank 3 control register */
#define REFEXTCON ((volatile EE_ADDR)(SYSCFG_BASE + 0x303C)) /* R/W Refresh and external I/O control register */

/* Ethernet (BDMA) */

#define BDMATXCON ((volatile EE_ADDR)(SYSCFG_BASE + 0x9000)) /* R/W Buffered DMA receive control register */
#define BDMARXCON ((volatile EE_ADDR)(SYSCFG_BASE + 0x9004)) /* R/W Buffered DMA transmit control register */
#define BDMATXPTR ((volatile EE_ADDR)(SYSCFG_BASE + 0x9008)) /* Transmit trame descriptor start address */
#define BDMARXPTR ((volatile EE_ADDR)(SYSCFG_BASE + 0x900C)) /* Receive frame descriptor start address */
#define BDMARXLSZ ((volatile EE_ADDR)(SYSCFG_BASE + 0x9010)) /* Receive frame maximum size Undefined */
#define BDMASTAT ((volatile EE_ADDR)(SYSCFG_BASE + 0x9014)) /* R/W Buffered DMA status */
#define CAM_BASE ((volatile EE_ADDR)(SYSCFG_BASE + 0x9100)) /* to 0x917C W CAM content (32 words) */
#define BDMATXBUF_BASE ((volatile EE_ADDR)(SYSCFG_BASE + 0x9200)) /* to 0x92FC R/W BDMA Tx buffer (64 words) for test mode addressing */
#define BDMARXBUF_BASE ((volatile EE_ADDR)(SYSCFG_BASE + 0x9800)) /* to 0x99FC R/W BDMA Rx buffer (64 words) for test mode addressing */

/* Ethernet (MAC) */

#define MACON ((volatile EE_ADDR)(SYSCFG_BASE + 0xA000)) /* R/W Ethernet MAC control register */
#define CAMCON ((volatile EE_ADDR)(SYSCFG_BASE + 0xA004)) /* R/W CAM control register */
#define MACTXCON ((volatile EE_ADDR)(SYSCFG_BASE + 0xA008)) /* R/W MAC transmit control register */
#define MACTXSTAT ((volatile EE_ADDR)(SYSCFG_BASE + 0xA00C)) /* R/W MAC transmit status register */
#define MACRXCON ((volatile EE_ADDR)(SYSCFG_BASE + 0xA010)) /* R/W MAC receive control register */
#define MACRXSTAT ((volatile EE_ADDR)(SYSCFG_BASE + 0xA014)) /* R/W MAC receive status register */
#define STADATA ((volatile EE_ADDR)(SYSCFG_BASE + 0xA018)) /* R/W Station management data */
#define STACON ((volatile EE_ADDR)(SYSCFG_BASE + 0xA01C)) /* R/W Station management control and address */
#define CAMEN ((volatile EE_ADDR)(SYSCFG_BASE + 0xA028)) /* R/W CAM enable register */
#define EMISSCNT ((volatile EE_ADDR)(SYSCFG_BASE + 0xA03C)) /* R/W Missed error count register */
#define EPZCNT ((volatile EE_ADDR)(SYSCFG_BASE + 0xA040)) /* R Pause count register */
#define ERMPZCNT ((volatile EE_ADDR)(SYSCFG_BASE + 0xA044)) /* R Remote pause count register */
#define ETXSTAT ((volatile EE_ADDR)(SYSCFG_BASE + 0x9040)) /* R Transmit control frame status */


/* HDLC Channel A  */
#define HMODE_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7000)) /* R/W HDLC mode register */
#define HCON_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7004)) /* R/W HDLC control register */
#define HSTAT_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7008)) /* R/W HDLC status register */
#define HINTEN_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x700c)) /* R/W HDLC interrupt enable register */
#define HTXFIFOC_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7010)) /* W TxFIFO frame continue register */
#define HTXFIFOT_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7014)) /* W TxFIFO frame terminate register */
#define HRXFIFO_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7018)) /* R HDLC RxFIFO entry register */
#define HBRGTC_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x701c)) /* R/W HDLC Baud rate generate time constant */
#define HPRMB_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7020)) /* R/W HDLC Preamble Constant */
#define HSAR0_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7024)) /* R/W HDLC station address 0 */
#define HSAR1_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7028)) /* R/W HDLC station address 1 */
#define HSAR2_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x702c)) /* R/W HDLC station address 2 */
#define HSAR3_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7030)) /* R/W HDLC station address 3 */
#define HMASK_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7034)) /* R/W HDLC mask register */
#define HDMATXPTR_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7038)) /* R/W DMA Tx buffer descriptor pointer */
#define HDMARXPTR_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x703c)) /* R/W DMA Rx buffer descriptor pointer */
#define HMFLR_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7040)) /* R/W Maximum frame length register */
#define HRBSR_A ((volatile EE_ADDR)(SYSCFG_BASE + 0x7044)) /* R/W DMA receive buffer size register */

/* HDLC Channel B */
#define HMODE_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8000)) /* R/W HDLC mode register */
#define HCON_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8004)) /* R/W HDLC control register */
#define HSTAT_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8008)) /* R/W HDLC status register */
#define HINTEN_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x800C)) /* R/W HDLC interrupt enable register */
#define HTXFIFOC_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8010)) /* W TxFIFO frame continue register */
#define HTXFIFOT_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8014)) /* W TxFIFO frame terminate register */
#define HRXFIFO_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8018)) /* R HDLC RxFIFO entry register */
#define HBRGTC_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x801C)) /* R/W HDLC Baud rate generate time constant */
#define HPRMB_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8020)) /* R/W HDLC Preamble Constant */
#define HSAR0_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8024)) /* R/W HDLC station address 0 */
#define HSAR1_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8028)) /* R/W HDLC station address 1 */
#define HSAR2_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x802c)) /* R/W HDLC station address 2 */
#define HSAR3_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8030)) /* R/W HDLC station address 3 */
#define HMASK_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8034)) /* R/W HDLC mask register */
#define HDMATXPTR_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8038)) /* R/W DMA Tx buffer descriptor pointer */
#define HDMARXPTR_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x803c)) /* R/W DMA Rx buffer descriptor pointer */
#define HMFLR_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8040)) /* R/W Maximum frame length register */
#define HRBSR_B ((volatile EE_ADDR)(SYSCFG_BASE + 0x8044)) /* R/W DMA receive buffer size register */

/* I/O Ports */
#define IOPMOD ((volatile EE_ADDR)(SYSCFG_BASE + 0x5000)) /* R/W I/O port mode register */
#define IOPCON ((volatile EE_ADDR)(SYSCFG_BASE + 0x5004)) /* R/W I/O port control register */
#define IOPDATA ((volatile EE_ADDR)(SYSCFG_BASE + 0x5008)) /* R/W Input port data register */

/* Interrupt Controller */
#define INTMOD ((volatile EE_ADDR)(SYSCFG_BASE + 0x4000)) /* R/W Interrupt mode register */
#define INTPND ((volatile EE_ADDR)(SYSCFG_BASE + 0x4004)) /* R/W Interrupt pending register */
#define INTMSK ((volatile EE_ADDR)(SYSCFG_BASE + 0x4008)) /* R/W Interrupt mask register */
#define INTPRI0 ((volatile EE_ADDR)(SYSCFG_BASE + 0x400C)) /* R/W Interrupt priority register 0 */
#define INTPRI1 ((volatile EE_ADDR)(SYSCFG_BASE + 0x4010)) /* R/W Interrupt priority register 1 */
#define INTPRI2 ((volatile EE_ADDR)(SYSCFG_BASE + 0x4014)) /* R/W Interrupt priority register 2 */
#define INTPRI3 ((volatile EE_ADDR)(SYSCFG_BASE + 0x4018)) /* R/W Interrupt priority register 3 */
#define INTPRI4 ((volatile EE_ADDR)(SYSCFG_BASE + 0x401C)) /* R/W Interrupt priority register 4 */
#define INTPRI5 ((volatile EE_ADDR)(SYSCFG_BASE + 0x4020)) /* R/W Interrupt priority register 5 */
#define INTOFFSET ((volatile EE_ADDR)(SYSCFG_BASE + 0x4024)) /* R Interrupt offset address register */
#define INTOSET_FIQ ((volatile EE_ADDR)(SYSCFG_BASE + 0x4030)) /* R FIQ interrupt offset register */
#define INTOSET_IRQ ((volatile EE_ADDR)(SYSCFG_BASE + 0x4034)) /* R IRQ interrupt offset register */

/* I2C Bus */
#define IICCON ((volatile EE_ADDR)(SYSCFG_BASE + 0xF000)) /* R/W I2C bus control status register */
#define IICBUF ((volatile EE_ADDR)(SYSCFG_BASE + 0xF004)) /* R/W I2C bus shift buffer register */
#define IICPS ((volatile EE_ADDR)(SYSCFG_BASE + 0xF008)) /* R/W I2C bus prescaler register */
#define IICCOUNT ((volatile EE_ADDR)(SYSCFG_BASE + 0xF00C)) /* R I2C bus prescaler counter register */

/* GDMA */
#define GDMACON0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xB000)) /* R/W GDMA channel 0 control register */
#define GDMACON1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xC000)) /* R/W GDMA channel 1 control register */
#define GDMASRC0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xB004)) /* R/W GDMA source address register 0 */
#define GDMADST0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xB008)) /* R/W GDMA destination address register 0 */
#define GDMASRC1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xC004)) /* R/W GDMA source address register 1 */
#define GDMADST1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xC008)) /* R/W GDMA destination address register 1 */
#define GDMACNT0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xB00C)) /* R/W GDMA channel 0 transfer count register */
#define GDMACNT1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xC00C)) /* R/W GDMA channel 1 transfer count register */

/* UART */
#define ULCON0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xD000)) /* R/W UART channel 0 line control register */
#define ULCON1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xE000)) /* R/W UART channel 1 line control register */
#define UCON0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xD004)) /* R/W UART channel 0 control register */
#define UCON1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xE004)) /* R/W UART channel 1 control register */
#define USTAT0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xD008)) /* R UART channel 0 status register */
#define USTAT1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xE008)) /* R UART channel 1 status register */
#define UTXBUF0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xD00C)) /* W UART channel 0 transmit holding register */
#define UTXBUF1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xE00C)) /* W UART channel 1 transmit holding register */
#define URXBUF0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xD010)) /* R UART channel 0 receive buffer register */
#define URXBUF1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xE010)) /* R UART channel 1 receive buffer register */
#define UBRDIV0 ((volatile EE_ADDR)(SYSCFG_BASE + 0xD014)) /* R/W Baud rate divisor register */
#define UBRDIV1 ((volatile EE_ADDR)(SYSCFG_BASE + 0xE014)) /* R/W Baud rate divisor register 1 */

/* Timers */
#define TMOD ((volatile EE_ADDR)(SYSCFG_BASE + 0x6000)) /* R/W Timer mode register */
#define TDATA0 ((volatile EE_ADDR)(SYSCFG_BASE + 0x6004)) /* Timer 0 data register */
#define TDATA1 ((volatile EE_ADDR)(SYSCFG_BASE + 0x6008)) /* Timer 1 data register */
#define TCNT0 ((volatile EE_ADDR)(SYSCFG_BASE + 0x600C)) /* Timer 0 count register */
#define TCNT1 ((volatile EE_ADDR)(SYSCFG_BASE + 0x6010)) /* Timer 1 count register */










/*************************************************************************
 External IRQ #0
 *************************************************************************/

#define IO_ENABLE_EXT0 (1<<4)	   /* bit 4 of IOPMOD = 1 ==> enable */
#define IO_ACTIVE_HIGH_EXT0 (1<<3) /* bit 3 of IOPMOD = 1 ==> active high */
#define IO_RISING_EDGE_EXT0 (1<<0) /* bit 1+0 of IOPMOD = 01 ==>
				    * rising edge detection */





#endif
