/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
	@file ee_vtable_ccrx.c
	@brief Interrupt Vector Table for use with Renesas HEW.
	@author Gianluca Franchino
	@date 2012
	@author Giuseppe Serano
	@date 2013
 */

#include "ee.h"

/*
 * This is the code that gets called when the processor receives an unexpected
 * interrupt.  This simply enters an infinite loop, preserving the system state
 * for examination by a debugger.
 */
void EE_rx200_default_ISR(void)
{
    /* Go into an infinite loop.*/
    while(1)
    {
    }
}

/*
 * Interrupt Handlers: OLD VERSION!!!
 */

#ifdef EE_RX200_BUSERR_ISR
extern void EE_RX200_BUSERR_ISR(void);	//The BUS error handler
#endif 

#ifdef EE_RX200_FIFERR_ISR
extern void EE_RX200_FIFERR_ISR(void);	//The FLASH interface handler
#endif 

#ifdef EE_RX200_FRDYI_ISR
extern void EE_RX200_FRDYI_ISR(void);	//The FLASH READY handler
#endif

#ifdef EE_RX200_SWINT_ISR
extern void EE_RX200_SWINT_ISR(void);	//The Software Interr. handler
#endif 

#ifdef EE_RX200_CMI0_ISR
extern void EE_RX200_CMI0_ISR(void);	//The Compare Match 0 handler
#endif 

#ifdef EE_RX200_CMI1_ISR
extern void EE_RX200_CMI1_ISR(void);	//The Compare Match 1 handler
#endif 

#ifdef EE_RX200_CMI2_ISR
extern void EE_RX200_CMI2_ISR(void);	//The Compare Match 2 handler
#endif

#ifdef EE_RX200_CMI3_ISR
extern void EE_RX200_CMI3_ISR(void);	//The Compare Match 3 handler
#endif

#ifdef EE_RX200_FERRF_ISR
extern void EE_RX200_FERRF_ISR(void);	//The Freq. Err. Interr. handler
#endif 

#ifdef EE_RX200_MENDF_ISR
extern void EE_RX200_MENDF_ISR(void);	//The Measur. End Interr. handler
#endif 

#ifdef EE_RX200_OVFF_ISR
extern void EE_RX200_OVFF_ISR(void);	//The Overflow Interr. handler
#endif

#ifdef EE_RX200_SPEI0_ISR
extern void EE_RX200_SPEI0_ISR(void);	//The SCI Error handler
#endif 

#ifdef EE_RX200_SPRIO_ISR
extern void EE_RX200_SPRIO_ISR(void);	//The  SCI RX Interr. handler
#endif 

#ifdef EE_RX200_SPTIO_ISR
extern void EE_RX200_SPTIO_ISR(void);	//The SCI TX Interr. handler
#endif

#ifdef EE_RX200_SPIIO_ISR
extern void EE_RX200_SPIIO_ISR(void);	//The SCI IO Interr. handler
#endif

#ifdef EE_RX200_DOPCF_ISR
extern void EE_RX200_DOPCF_ISR(void);	//The Data oper. circuit Interr. handler
#endif

#ifdef EE_RX200_COMPB0_ISR
extern void EE_RX200_COMPB0_ISR(void);	//The Comparator B0 Interr. handler
#endif

#ifdef EE_RX200_COMPB1_ISR
extern void EE_RX200_COMPB1_ISR(void);	//The Comparator B1 Interr. handler
#endif

#ifdef EE_RX200_COUNTUP_ISR
extern void EE_RX200_COUNTUP_ISR(void);	//The RTC Countup Interr. handler
#endif

#ifdef EE_RX200_IRQ0_ISR
extern void EE_RX200_IRQ0_ISR(void);	//The IRQ0 Interr. handler
#endif

#ifdef EE_RX200_IRQ1_ISR
extern void EE_RX200_IRQ1_ISR(void);	//The IRQ1 Interr. handler
#endif

#ifdef EE_RX200_IRQ2_ISR
extern void EE_RX200_IRQ2_ISR(void);	//The IRQ2 Interr. handler
#endif

#ifdef EE_RX200_IRQ3_ISR
extern void EE_RX200_IRQ3_ISR(void);	//The IRQ3 Interr. handler
#endif

#ifdef EE_RX200_IRQ4_ISR
extern void EE_RX200_IRQ4_ISR(void);	//The IRQ4 Interr. handler
#endif

#ifdef EE_RX200_IRQ5_ISR
extern void EE_RX200_IRQ5_ISR(void);	//The IRQ5 Interr. handler
#endif

#ifdef EE_RX200_IRQ6_ISR
extern void EE_RX200_IRQ6_ISR(void);	//The IRQ6 Interr. handler
#endif

#ifdef EE_RX200_IRQ7_ISR
extern void EE_RX200_IRQ7_ISR(void);	//The IRQ7 Interr. handler
#endif

#ifdef EE_RX200_LVDI1_COMP1_ISR
extern void EE_RX200_LVDI1_COMP1_ISR(void);	//The LVD1/COMPA1. Interr. handler
#endif

#ifdef EE_RX200_LVDI2_COMP2_ISR
extern void EE_RX200_LVDI2_COMP2_ISR(void);	//The LVD2/COMPA2. Interr. handler
#endif

#ifdef EE_RX200_ALM_ISR
extern void EE_RX200_ALM_ISR(void);	//The RTC Alarm Interr. handler
#endif

#ifdef EE_RX200_PRD_ISR
extern void EE_RX200_PRD_ISR(void);	//The RTC Periodic Interr. handler
#endif

#ifdef EE_RX200_S12ADI0_ISR
extern void EE_RX200_S12ADI0_ISR(void);	//The 12-bit ADC scan end int. handler
#endif

#ifdef EE_RX200_GBADI_ISR
extern void EE_RX200_GBADI_ISR(void);	//The 12-bit ADC group B scan end 
#endif									//int handler

#ifdef EE_RX200_ELSR18I_ISR
extern void EE_RX200_ELSR18I_ISR(void);	//Event link SR18 int. handler
#endif

#ifdef EE_RX200_ELSR19I_ISR
extern void EE_RX200_ELSR19I_ISR(void);	//Event link SR19 int. handler
#endif

#ifdef EE_RX200_TGIA0_ISR
extern void EE_RX200_TGIA0_ISR(void);	//The MTU0.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB0_ISR
extern void EE_RX200_TGIB0_ISR(void);	//The MTU0.TGRB input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIC0_ISR
extern void EE_RX200_TGIC0_ISR(void);	//The MTU0.TGRC input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGID0_ISR
extern void EE_RX200_TGID0_ISR(void);	//The MTU0.TGRD input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TCIV0_ISR
extern void EE_RX200_TCIV0_ISR(void);	//The MTU0.TCNT overflow int. handler
#endif									

#ifdef EE_RX200_TGIE0_ISR
extern void EE_RX200_TGIE0_ISR(void);	//MTU0.TGRE compare match int. handler
#endif

#ifdef EE_RX200_TGIF0_ISR
extern void EE_RX200_TGIF0_ISR(void);	//MTU0.TGRF compare match int. handler
#endif	

#ifdef EE_RX200_TGIA1_ISR
extern void EE_RX200_TGIA1_ISR(void);	//The MTU1.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB1_ISR
extern void EE_RX200_TGIB1_ISR(void);	//The MTU1.TGRB input capture/comp match
#endif

#ifdef EE_RX200_TCIV1_ISR
extern void EE_RX200_TCIV1_ISR(void);	//The MTU1.TCNT overflow int. handler
#endif

#ifdef EE_RX200_TCIU1_ISR
extern void EE_RX200_TCIU1_ISR(void);	//The MTU1.TCNT undeflow int. handler
#endif

#ifdef EE_RX200_TGIA2_ISR
extern void EE_RX200_TGIA2_ISR(void);	//The MTU2.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB2_ISR
extern void EE_RX200_TGIB2_ISR(void);	//The MTU2.TGRB input capture/comp match
#endif

#ifdef EE_RX200_TCIV2_ISR
extern void EE_RX200_TCIV2_ISR(void);	//The MTU2.TCNT overflow int. handler
#endif

#ifdef EE_RX200_TCIU2_ISR
extern void EE_RX200_TCIU2_ISR(void);	//The MTU2.TCNT undeflow int. handler
#endif

#ifdef EE_RX200_TGIA3_ISR
extern void EE_RX200_TGIA3_ISR(void);	//The MTU3.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB3_ISR
extern void EE_RX200_TGIB3_ISR(void);	//The MTU3.TGRB input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIC3_ISR
extern void EE_RX200_TGIC3_ISR(void);	//The MTU3.TGRC input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGID3_ISR
extern void EE_RX200_TGID3_ISR(void);	//The MTU3.TGRD input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TCIV3_ISR
extern void EE_RX200_TCIV3_ISR(void);	//The MTU3.TCNT overflow int. handler
#endif									

#ifdef EE_RX200_TGIA4_ISR
extern void EE_RX200_TGIA4_ISR(void);	//The MTU4.TGRA  input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIB4_ISR
extern void EE_RX200_TGIB4_ISR(void);	//The MTU4.TGRB input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGIC4_ISR
extern void EE_RX200_TGIC4_ISR(void);	//The MTU4.TGRC input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TGID4_ISR
extern void EE_RX200_TGID4_ISR(void);	//The MTU4.TGRD input capture/comp match
#endif									//int. handler

#ifdef EE_RX200_TCIV4_ISR
extern void EE_RX200_TCIV4_ISR(void);	//The MTU4.TCNT overflow int. handler
#endif

#ifdef EE_RX200_TGIU5_ISR
extern void EE_RX200_TGIU5_ISR(void);	//The MTU5.TGRU input capture/comp 
#endif									//match ISR

#ifdef EE_RX200_TGIV5_ISR
extern void EE_RX200_TGIV5_ISR(void);	//The MTU5.TGRV input capture/comp 
#endif									//match ISR

#ifdef EE_RX200_TCIW5_ISR
extern void EE_RX200_TCIW5_ISR(void);	//The MTU5.TGRW input capture/comp 
#endif									//match ISR

#ifdef EE_RX200_OEI1_ISR
extern void EE_RX200_OEI1_ISR(void);	//The Port Output 1 (POE1) int. handler.
#endif

#ifdef EE_RX200_OEI2_ISR
extern void EE_RX200_OEI2_ISR(void);	//The Port Output 2 (POE2) int. handler.
#endif

#ifdef EE_RX200_CMIA0_ISR
extern void EE_RX200_CMIA0_ISR(void);	//The TMR0 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB0_ISR
extern void EE_RX200_CMIB0_ISR(void);	//The TMR0 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI0_ISR
extern void EE_RX200_OVI0_ISR(void);	//The TMR0 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_CMIA1_ISR
extern void EE_RX200_CMIA1_ISR(void);	//The TMR1 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB1_ISR
extern void EE_RX200_CMIB1_ISR(void);	//The TMR1 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI1_ISR
extern void EE_RX200_OVI1_ISR(void);	//The TMR1 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_CMIA2_ISR
extern void EE_RX200_CMIA2_ISR(void);	//The TMR2 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB2_ISR
extern void EE_RX200_CMIB2_ISR(void);	//The TMR2 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI2_ISR
extern void EE_RX200_OVI2_ISR(void);	//The TMR2 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_CMIA3_ISR
extern void EE_RX200_CMIA3_ISR(void);	//The TMR3 compare match A int. handler.
#endif									

#ifdef EE_RX200_CMIB3_ISR
extern void EE_RX200_CMIB3_ISR(void);	//The TMR3 compare match B int. handler.
#endif

#ifdef EE_RX200_OVI3_ISR
extern void EE_RX200_OVI3_ISR(void);	//The TMR3 TCNT overflow int. handler.
#endif

#ifdef EE_RX200_DMAC0I_ISR
extern void EE_RX200_DMAC0I_ISR(void);	//The DMAC channel 0 transfer end ISR.
#endif

#ifdef EE_RX200_DMAC1I_ISR
extern void EE_RX200_DMAC1I_ISR(void);	//The DMAC channel 1 transfer end ISR.
#endif									

#ifdef EE_RX200_DMAC2I_ISR
extern void EE_RX200_DMAC2I_ISR(void);	//The DMAC channel 2 transfer end ISR.
#endif

#ifdef EE_RX200_DMAC3I_ISR
extern void EE_RX200_DMAC3I_ISR(void);	//The DMAC channel 3 transfer end ISR.
#endif

#ifdef EE_RX200_ERI0_ISR
extern void EE_RX200_ERI0_ISR(void);	//The SCI0 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI0_ISR
extern void EE_RX200_RXI0_ISR(void);	//The SCI0 RX int. handler.
#endif									

#ifdef EE_RX200_TXI0_ISR
extern void EE_RX200_TXI0_ISR(void);	//The SCI0 TX empty int. handler.
#endif

#ifdef EE_RX200_TEI0_ISR
extern void EE_RX200_TEI0_ISR(void);	//The SCI0 TX end int. handler.
#endif

#ifdef EE_RX200_ERI1_ISR
extern void EE_RX200_ERI1_ISR(void);	//The SCI1 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI1_ISR
extern void EE_RX200_RXI1_ISR(void);	//The SCI1 RX int. handler.
#endif									

#ifdef EE_RX200_TXI1_ISR
extern void EE_RX200_TXI1_ISR(void);	//The SCI1 TX int. handler.
#endif

#ifdef EE_RX200_TEI1_ISR
extern void EE_RX200_TEI1_ISR(void);	//The SCI1 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI5_ISR
extern void EE_RX200_ERI5_ISR(void);	//The SCI5 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI5_ISR
extern void EE_RX200_RXI5_ISR(void);	//The SCI5 RX int. handler.
#endif									

#ifdef EE_RX200_TXI5_ISR
extern void EE_RX200_TXI5_ISR(void);	//The SCI5 TX int. handler.
#endif

#ifdef EE_RX200_TEI5_ISR
extern void EE_RX200_TEI5_ISR(void);	//The SCI5 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI6_ISR
extern void EE_RX200_ERI6_ISR(void);	//The SCI6 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI6_ISR
extern void EE_RX200_RXI6_ISR(void);	//The SCI6 RX int. handler.
#endif									

#ifdef EE_RX200_TXI6_ISR
extern void EE_RX200_TXI6_ISR(void);	//The SCI6 TX int. handler.
#endif

#ifdef EE_RX200_TEI6_ISR
extern void EE_RX200_TEI6_ISR(void);	//The SCI6 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI8_ISR
extern void EE_RX200_ERI8_ISR(void);	//The SCI8 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI8_ISR
extern void EE_RX200_RXI8_ISR(void);	//The SCI8 RX int. handler.
#endif									

#ifdef EE_RX200_TXI8_ISR
extern void EE_RX200_TXI8_ISR(void);	//The SCI8 TX int. handler.
#endif

#ifdef EE_RX200_TEI8_ISR
extern void EE_RX200_TEI8_ISR(void);	//The SCI8 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI9_ISR
extern void EE_RX200_ERI9_ISR(void);	//The SCI9 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI9_ISR
extern void EE_RX200_RXI9_ISR(void);	//The SCI9 RX int. handler.
#endif									

#ifdef EE_RX200_TXI9_ISR
extern void EE_RX200_TXI9_ISR(void);	//The SCI9 TX int. handler.
#endif

#ifdef EE_RX200_TEI9_ISR
extern void EE_RX200_TEI9_ISR(void);	//The SCI9 TX empty int. handler.
#endif

#ifdef EE_RX200_ERI12_ISR
extern void EE_RX200_ERI12_ISR(void);	//The SCI12 Receive Error int. handler.
#endif

#ifdef EE_RX200_RXI12_ISR
extern void EE_RX200_RXI12_ISR(void);	//The SCI12 RX int. handler.
#endif									

#ifdef EE_RX200_TXI12_ISR
extern void EE_RX200_TXI12_ISR(void);	//The SCI12 TX int. handler.
#endif

#ifdef EE_RX200_TEI12_ISR
extern void EE_RX200_TEI12_ISR(void);	//The SCI12 TX empty int. handler.
#endif
/* Extended Serial Mode Control Interrupt handlers (SCI12) */
#ifdef EE_RX200_SCIX0_ISR
extern void EE_RX200_SCIX0_ISR(void);	
#endif

#ifdef EE_RX200_SCIX1_ISR
extern void EE_RX200_SCIX1_ISR(void);	
#endif									

#ifdef EE_RX200_SCIX2_ISR
extern void EE_RX200_SCIX2_ISR(void);
#endif

#ifdef EE_RX200_SCIX3_ISR
extern void EE_RX200_SCIX3_ISR(void);
#endif

#ifdef EE_RX200_EEI0_ISR
extern void EE_RX200_EEI0_ISR(void);	//The RIIC0 Event/Error int. handler.
#endif

#ifdef EE_RX200_RXI0_ISR
extern void EE_RX200_RXI0_ISR(void);	//The RIIC0 Receive Data Full int. handler.
#endif									

#ifdef EE_RX200_TXI0_ISR
extern void EE_RX200_TXI0_ISR(void);	//The RIIC0 TX end int. handler.
#endif

#ifdef EE_RX200_TEI0_ISR
extern void EE_RX200_TEI0_ISR(void);	//The RIIC0 TX data empty int. handler.
#endif

/*
 * Interrupt Handlers: NEW VERSION!!!
 */

/*
 * Bus-error interrupt.
 */
#ifdef	EE_RX200_BSC_BUSERR_ISR
extern void EE_RX200_BSC_BUSERR_ISR(void);
#endif	/* EE_RX200_BSC_BUSERR_ISR */


/*
 * Flash interface error interrupt.
 */
#ifdef	EE_RX200_FCU_FIFERR_ISR
extern void EE_RX200_FCU_FIFERR_ISR(void);
#endif	/* EE_RX200_FCU_FIFERR_ISR */

/*
 * Flash READY interrupt.
 */
#ifdef	EE_RX200_FCU_FRDYI_ISR
extern void EE_RX200_FCU_FRDYI_ISR(void);
#endif	/* EE_RX200_FCU_FRDYI_ISR */

/*
 * Software interrupt.
 */
#ifdef	EE_RX200_ICU_SWINT_ISR
extern void EE_RX200_ICU_SWINT_ISR(void);
#endif	/* EE_RX200_ICU_SWINT_ISR */

/*
 * Compare Match 0 interrupt.
 */
#ifdef	EE_RX200_CMT0_CMI0_ISR
extern void EE_RX200_CMT0_CMI0_ISR(void);
#endif	/* EE_RX200_CMT0_CMI0_ISR */

/*
 * Compare Match 1 interrupt.
 */
#ifdef	EE_RX200_CMT1_CMI1_ISR
extern void EE_RX200_CMT1_CMI1_ISR(void);
#endif	/* EE_RX200_CMT1_CMI1_ISR */

/*
 * Compare Match 2 interrupt.
 */
#ifdef	EE_RX200_CMT2_CMI2_ISR
extern void EE_RX200_CMT2_CMI2_ISR(void);
#endif	/* EE_RX200_CMT2_CMI2_ISR */

/*
 * Compare Match 3 interrupt.
 */
#ifdef	EE_RX200_CMT3_CMI3_ISR
extern void EE_RX200_CMT3_CMI3_ISR(void);
#endif	/* EE_RX200_CMT3_CMI3_ISR */

/*
 * Frequency Error interrupt.
 */
#ifdef	EE_RX200_CAC_FERRF_ISR
extern void EE_RX200_CAC_FERRF_ISR(void);
#endif	/* EE_RX200_CAC_FERRF_ISR */

/*
 * Measurement End interrupt.
 */
#ifdef	EE_RX200_CAC_MENDF_ISR
extern void EE_RX200_CAC_MENDF_ISR(void);
#endif	/* EE_RX200_CAC_MENDF_ISR */

/*
 * Overflow interrupt.
 */
#ifdef	EE_RX200_CAC_OVFF_ISR
extern void EE_RX200_CAC_OVFF_ISR(void);
#endif	/* EE_RX200_CAC_OVFF_ISR */

/*
 * RSPI Errors interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPEI0_ISR
extern void EE_RX200_RSPI0_SPEI0_ISR(void);
#endif	/* EE_RX200_RSPI0_SPEI0_ISR */

/*
 * Receive Buffer Full interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPRI0_ISR
extern void EE_RX200_RSPI0_SPRI0_ISR(void);
#endif	/* EE_RX200_RSPI0_SPRI0_ISR */

/*
 * Transmit Buffer Full interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPTI0_ISR
extern void EE_RX200_RSPI0_SPTI0_ISR(void);
#endif	/* EE_RX200_RSPI0_SPTI0_ISR */

/*
 * RSPI Idle interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPII0_ISR
extern void EE_RX200_RSPI0_SPII0_ISR(void);
#endif	/* EE_RX200_RSPI0_SPII0_ISR */

/*
 * Data Operation Circuit interrupt.
 */
#ifdef	EE_RX200_DOC_DOPCF_ISR
extern void EE_RX200_DOC_DOPCF_ISR(void);
#endif	/* EE_RX200_DOC_DOPCF_ISR */

/*
 * Comparator B0 interrupt.
 */
#ifdef	EE_RX200_CMPB_CMPB0_ISR
extern void EE_RX200_CMPB_CMPB0_ISR(void);
#endif	/* EE_RX200_CMPB_CMPB0_ISR */

/*
 * Comparator B1 interrupt.
 */
#ifdef	EE_RX200_CMPB_CMPB1_ISR
extern void EE_RX200_CMPB_CMPB1_ISR(void);
#endif	/* EE_RX200_CMPB_CMPB1_ISR */

/*
 * RTC Count Up interrupt.
 */
#ifdef	EE_RX200_RTC_CUP_ISR
extern void EE_RX200_RTC_CUP_ISR(void);
#endif	/* EE_RX200_RTC_CUP_ISR */

/*
 * IRQ0 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ0_ISR
extern void EE_RX200_ICU_IRQ0_ISR(void);
#endif	/* EE_RX200_ICU_IRQ0_ISR */

/*
 * IRQ1 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ1_ISR
extern void EE_RX200_ICU_IRQ1_ISR(void);
#endif	/* EE_RX200_ICU_IRQ1_ISR */

/*
 * IRQ2 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ2_ISR
extern void EE_RX200_ICU_IRQ2_ISR(void);
#endif	/* EE_RX200_ICU_IRQ2_ISR */

/*
 * IRQ3 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ3_ISR
extern void EE_RX200_ICU_IRQ3_ISR(void);
#endif	/* EE_RX200_ICU_IRQ3_ISR */

/*
 * IRQ4 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ4_ISR
extern void EE_RX200_ICU_IRQ4_ISR(void);
#endif	/* EE_RX200_ICU_IRQ4_ISR */

/*
 * IRQ5 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ5_ISR
extern void EE_RX200_ICU_IRQ5_ISR(void);
#endif	/* EE_RX200_ICU_IRQ5_ISR */

/*
 * IRQ6 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ6_ISR
extern void EE_RX200_ICU_IRQ6_ISR(void);
#endif	/* EE_RX200_ICU_IRQ6_ISR */

/*
 * IRQ7 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ7_ISR
extern void EE_RX200_ICU_IRQ7_ISR(void);
#endif	/* EE_RX200_ICU_IRQ7_ISR */

/*
 * LVD1/CMPA1 interrupt.
 */
#ifdef	EE_RX200_LVD1_CMPA1_ISR
extern void EE_RX200_LVD1_CMPA1_ISR(void);
#endif	/* EE_RX200_LVD1_CMPA1_ISR */

/*
 * LVD2/CMPA2 interrupt.
 */
#ifdef	EE_RX200_LVD2_CMPA2_ISR
extern void EE_RX200_LVD2_CMPA2_ISR(void);
#endif	/* EE_RX200_LVD2_CMPA2_ISR */

/*
 * RTC Alarm interrupt.
 */
#ifdef	EE_RX200_RTC_ALM_ISR
extern void EE_RX200_RTC_ALM_ISR(void);
#endif	/* EE_RX200_RTC_ALM_ISR */

/*
 * RTC Periodic interrupt.
 */
#ifdef	EE_RX200_RTC_PRD_ISR
extern void EE_RX200_RTC_PRD_ISR(void);
#endif	/* EE_RX200_RTC_PRD_ISR */

/*
 * ADC Scan End interrupt.
 */
#ifdef	EE_RX200_S12AD_S12ADI0_ISR
extern void EE_RX200_S12AD_S12ADI0_ISR(void);
#endif	/* EE_RX200_S12AD_S12ADI0_ISR */

/*
 * ADC Group B Scan End interrupt.
 */
#ifdef	EE_RX200_S12AD_GBADI_ISR
extern void EE_RX200_S12AD_GBADI_ISR(void);
#endif	/* EE_RX200_S12AD_GBADI_ISR */

/*
 * Event Link SR18 interrupt.
 */
#ifdef	EE_RX200_ELC_ELSR18I_ISR
extern void EE_RX200_ELC_ELSR18I_ISR(void);
#endif	/* EE_RX200_ELC_ELSR18I_ISR */

/*
 * Event Link SR19 interrupt.
 */
#ifdef	EE_RX200_ELC_ELSR19I_ISR
extern void EE_RX200_ELC_ELSR19I_ISR(void);
#endif	/* EE_RX200_ELC_ELSR19I_ISR */

/*
 * MTU0 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIA0_ISR
extern void EE_RX200_MTU0_TGIA0_ISR(void);
#endif	/* EE_RX200_MTU0_TGIA0_ISR */

/*
 * MTU0 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIB0_ISR
extern void EE_RX200_MTU0_TGIB0_ISR(void);
#endif	/* EE_RX200_MTU0_TGIB0_ISR */

/*
 * MTU0 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIC0_ISR
extern void EE_RX200_MTU0_TGIC0_ISR(void);
#endif	/* EE_RX200_MTU0_TGIC0_ISR */

/*
 * MTU0 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGID0_ISR
extern void EE_RX200_MTU0_TGID0_ISR(void);
#endif	/* EE_RX200_MTU0_TGID0_ISR */

/*
 * MTU0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU0_TCIV0_ISR
extern void EE_RX200_MTU0_TCIV0_ISR(void);
#endif	/* EE_RX200_MTU0_TCIV0_ISR */

/*
 * MTU0 TGRE Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIE0_ISR
extern void EE_RX200_MTU0_TGIE0_ISR(void);
#endif	/* EE_RX200_MTU0_TGIE0_ISR */

/*
 * MTU0 TGRF Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIF0_ISR
extern void EE_RX200_MTU0_TGIF0_ISR(void);
#endif	/* EE_RX200_MTU0_TGIF0_ISR */

/*
 * MTU1 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU1_TGIA1_ISR
extern void EE_RX200_MTU1_TGIA1_ISR(void);
#endif	/* EE_RX200_MTU1_TGIA1_ISR */

/*
 * MTU1 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU1_TGIB1_ISR
extern void EE_RX200_MTU1_TGIB1_ISR(void);
#endif	/* EE_RX200_MTU1_TGIB1_ISR */

/*
 * MTU1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU1_TCIV1_ISR
extern void EE_RX200_MTU1_TCIV1_ISR(void);
#endif	/* EE_RX200_MTU1_TCIV1_ISR */

/*
 * MTU1 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_MTU1_TCIU1_ISR
extern void EE_RX200_MTU1_TCIU1_ISR(void);
#endif	/* EE_RX200_MTU1_TCIU1_ISR */

/*
 * MTU2 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU2_TGIA2_ISR
extern void EE_RX200_MTU2_TGIA2_ISR(void);
#endif	/* EE_RX200_MTU2_TGIA2_ISR */

/*
 * MTU2 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU2_TGIB2_ISR
extern void EE_RX200_MTU2_TGIB2_ISR(void);
#endif	/* EE_RX200_MTU2_TGIB2_ISR */

/*
 * MTU2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU2_TCIV2_ISR
extern void EE_RX200_MTU2_TCIV2_ISR(void);
#endif	/* EE_RX200_MTU2_TCIV2_ISR */

/*
 * MTU2 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_MTU2_TCIU2_ISR
extern void EE_RX200_MTU2_TCIU2_ISR(void);
#endif	/* EE_RX200_MTU2_TCIU2_ISR */

/*
 * MTU3 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIA3_ISR
extern void EE_RX200_MTU3_TGIA3_ISR(void);
#endif	/* EE_RX200_MTU3_TGIA3_ISR */

/*
 * MTU3 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIB3_ISR
extern void EE_RX200_MTU3_TGIB3_ISR(void);
#endif	/* EE_RX200_MTU3_TGIB3_ISR */

/*
 * MTU3 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIC3_ISR
extern void EE_RX200_MTU3_TGIC3_ISR(void);
#endif	/* EE_RX200_MTU3_TGIC3_ISR */

/*
 * MTU3 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGID3_ISR
extern void EE_RX200_MTU3_TGID3_ISR(void);
#endif	/* EE_RX200_MTU3_TGID3_ISR */

/*
 * MTU3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU3_TCIV3_ISR
extern void EE_RX200_MTU3_TCIV3_ISR(void);
#endif	/* EE_RX200_MTU3_TCIV3_ISR */

/*
 * MTU4 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIA4_ISR
extern void EE_RX200_MTU4_TGIA4_ISR(void);
#endif	/* EE_RX200_MTU4_TGIA4_ISR */

/*
 * MTU4 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIB4_ISR
extern void EE_RX200_MTU4_TGIB4_ISR(void);
#endif	/* EE_RX200_MTU4_TGIB4_ISR */

/*
 * MTU4 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIC4_ISR
extern void EE_RX200_MTU4_TGIC4_ISR(void);
#endif	/* EE_RX200_MTU4_TGIC4_ISR */

/*
 * MTU4 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGID4_ISR
extern void EE_RX200_MTU4_TGID4_ISR(void);
#endif	/* EE_RX200_MTU4_TGID4_ISR */

/*
 * MTU4 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU4_TCIV4_ISR
extern void EE_RX200_MTU4_TCIV4_ISR(void);
#endif	/* EE_RX200_MTU4_TCIV4_ISR */

/*
 * MTU5 TGRU Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIU5_ISR
extern void EE_RX200_MTU5_TGIU5_ISR(void);
#endif	/* EE_RX200_MTU5_TGIU5_ISR */

/*
 * MTU5 TGRV Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIV5_ISR
extern void EE_RX200_MTU5_TGIV5_ISR(void);
#endif	/* EE_RX200_MTU5_TGIV5_ISR */

/*
 * MTU5 TGRW Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIW5_ISR
extern void EE_RX200_MTU5_TGIW5_ISR(void);
#endif	/* EE_RX200_MTU5_TGIW5_ISR */

/*
 * TPU0 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0A_ISR
extern void EE_RX200_TPU0_TGI0A_ISR(void);
#endif	/* EE_RX200_TPU0_TGI0A_ISR */

/*
 * TPU0 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0B_ISR
extern void EE_RX200_TPU0_TGI0B_ISR(void);
#endif	/* EE_RX200_TPU0_TGI0B_ISR */

/*
 * TPU0 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0C_ISR
extern void EE_RX200_TPU0_TGI0C_ISR(void);
#endif	/* EE_RX200_TPU0_TGI0C_ISR */

/*
 * TPU0 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0D_ISR
extern void EE_RX200_TPU0_TGI0D_ISR(void);
#endif	/* EE_RX200_TPU0_TGI0D_ISR */

/*
 * TPU0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU0_TCI0V_ISR
extern void EE_RX200_TPU0_TCI0V_ISR(void);
#endif	/* EE_RX200_TPU0_TCI0V_ISR */

/*
 * TPU1 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU1_TGI1A_ISR
extern void EE_RX200_TPU1_TGI1A_ISR(void);
#endif	/* EE_RX200_TPU1_TGI1A_ISR */

/*
 * TPU1 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU1_TGI1B_ISR
extern void EE_RX200_TPU1_TGI1B_ISR(void);
#endif	/* EE_RX200_TPU1_TGI1B_ISR */

/*
 * TPU1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU1_TCI1V_ISR
extern void EE_RX200_TPU1_TCI1V_ISR(void);
#endif	/* EE_RX200_TPU1_TCI1V_ISR */

/*
 * TPU1 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU1_TCI1U_ISR
extern void EE_RX200_TPU1_TCI1U_ISR(void);
#endif	/* EE_RX200_TPU1_TCI1U_ISR */

/*
 * TPU2 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU2_TGI2A_ISR
extern void EE_RX200_TPU2_TGI2A_ISR(void);
#endif	/* EE_RX200_TPU2_TGI2A_ISR */

/*
 * TPU2 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU2_TGI2B_ISR
extern void EE_RX200_TPU2_TGI2B_ISR(void);
#endif	/* EE_RX200_TPU2_TGI2B_ISR */

/*
 * TPU2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU2_TCI2V_ISR
extern void EE_RX200_TPU2_TCI2V_ISR(void);
#endif	/* EE_RX200_TPU2_TCI2V_ISR */

/*
 * TPU2 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU2_TCI2U_ISR
extern void EE_RX200_TPU2_TCI2U_ISR(void);
#endif	/* EE_RX200_TPU2_TCI2U_ISR */

/*
 * TPU3 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3A_ISR
extern void EE_RX200_TPU3_TGI3A_ISR(void);
#endif	/* EE_RX200_TPU3_TGI3A_ISR */

/*
 * TPU3 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3B_ISR
extern void EE_RX200_TPU3_TGI3B_ISR(void);
#endif	/* EE_RX200_TPU3_TGI3B_ISR */

/*
 * TPU3 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3C_ISR
extern void EE_RX200_TPU3_TGI3C_ISR(void);
#endif	/* EE_RX200_TPU3_TGI3C_ISR */

/*
 * TPU3 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3D_ISR
extern void EE_RX200_TPU3_TGI3D_ISR(void);
#endif	/* EE_RX200_TPU3_TGI3D_ISR */

/*
 * TPU3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU0_TCI0V_ISR
extern void EE_RX200_TPU0_TCI0V_ISR(void);
#endif	/* EE_RX200_TPU0_TCI0V_ISR */

/*
 * TPU4 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU4_TGI4A_ISR
extern void EE_RX200_TPU4_TGI4A_ISR(void);
#endif	/* EE_RX200_TPU4_TGI4A_ISR */

/*
 * TPU4 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU4_TGI4B_ISR
extern void EE_RX200_TPU4_TGI4B_ISR(void);
#endif	/* EE_RX200_TPU4_TGI4B_ISR */

/*
 * TPU4 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU4_TCI4V_ISR
extern void EE_RX200_TPU4_TCI4V_ISR(void);
#endif	/* EE_RX200_TPU4_TCI4V_ISR */

/*
 * TPU4 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU4_TCI4U_ISR
extern void EE_RX200_TPU4_TCI4U_ISR(void);
#endif	/* EE_RX200_TPU4_TCI4U_ISR */

/*
 * TPU5 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU5_TGI5A_ISR
extern void EE_RX200_TPU5_TGI5A_ISR(void);
#endif	/* EE_RX200_TPU5_TGI5A_ISR */

/*
 * TPU5 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU5_TGI5B_ISR
extern void EE_RX200_TPU5_TGI5B_ISR(void);
#endif	/* EE_RX200_TPU5_TGI5B_ISR */

/*
 * TPU5 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU5_TCI5V_ISR
extern void EE_RX200_TPU5_TCI5V_ISR(void);
#endif	/* EE_RX200_TPU5_TCI5V_ISR */

/*
 * TPU5 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU5_TCI5U_ISR
extern void EE_RX200_TPU5_TCI5U_ISR(void);
#endif	/* EE_RX200_TPU5_TCI5U_ISR */

/*
 * Port Output 1 interrupt.
 */
#ifdef	EE_RX200_POE_OEI1_ISR
extern void EE_RX200_POE_OEI1_ISR(void);
#endif	/* EE_RX200_POE_OEI1_ISR */

/*
 * Port Output 2 interrupt.
 */
#ifdef	EE_RX200_POE_OEI2_ISR
extern void EE_RX200_POE_OEI2_ISR(void);
#endif	/* EE_RX200_POE_OEI2_ISR */

/*
 * TMR0 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR0_CMIA0_ISR
extern void EE_RX200_TMR0_CMIA0_ISR(void);
#endif	/* EE_RX200_TMR0_CMIA0_ISR */

/*
 * TMR0 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR0_CMIB0_ISR
extern void EE_RX200_TMR0_CMIB0_ISR(void);
#endif	/* EE_RX200_TMR0_CMIB0_ISR */

/*
 * TMR0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR0_OVI0_ISR
extern void EE_RX200_TMR0_OVI0_ISR(void);
#endif	/* EE_RX200_TMR0_OVI0_ISR */

/*
 * TMR1 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR1_CMIA1_ISR
extern void EE_RX200_TMR1_CMIA1_ISR(void);
#endif	/* EE_RX200_TMR1_CMIA1_ISR */

/*
 * TMR1 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR1_CMIB1_ISR
extern void EE_RX200_TMR1_CMIB1_ISR(void);
#endif	/* EE_RX200_TMR1_CMIB1_ISR */

/*
 * TMR1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR1_OVI1_ISR
extern void EE_RX200_TMR1_OVI1_ISR(void);
#endif	/* EE_RX200_TMR1_OVI1_ISR */

/*
 * TMR2 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR2_CMIA2_ISR
extern void EE_RX200_TMR2_CMIA2_ISR(void);
#endif	/* EE_RX200_TMR2_CMIA2_ISR */

/*
 * TMR2 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR2_CMIB2_ISR
extern void EE_RX200_TMR2_CMIB2_ISR(void);
#endif	/* EE_RX200_TMR2_CMIB2_ISR */

/*
 * TMR2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR2_OVI2_ISR
extern void EE_RX200_TMR2_OVI2_ISR(void);
#endif	/* EE_RX200_TMR2_OVI2_ISR */

/*
 * TMR3 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR3_CMIA3_ISR
extern void EE_RX200_TMR3_CMIA3_ISR(void);
#endif	/* EE_RX200_TMR3_CMIA3_ISR */

/*
 * TMR3 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR3_CMIB3_ISR
extern void EE_RX200_TMR3_CMIB3_ISR(void);
#endif	/* EE_RX200_TMR3_CMIB3_ISR */

/*
 * TMR3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR3_OVI3_ISR
extern void EE_RX200_TMR3_OVI3_ISR(void);
#endif	/* EE_RX200_TMR3_OVI3_ISR */

/*
 * TMR3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR3_OVI3_ISR
extern void EE_RX200_TMR3_OVI3_ISR(void);
#endif	/* EE_RX200_TMR3_OVI3_ISR */

/*
 * SCI2 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI2_ERI2_ISR
extern void EE_RX200_SCI2_ERI2_ISR(void);
#endif	/* EE_RX200_SCI2_ERI2_ISR */

/*
 * SCI2 RX interrupt.
 */
#ifdef	EE_RX200_SCI2_RXI2_ISR
extern void EE_RX200_SCI2_RXI2_ISR(void);
#endif	/* EE_RX200_SCI2_RXI2_ISR */

/*
 * SCI2 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI2_TXI2_ISR
extern void EE_RX200_SCI2_TXI2_ISR(void);
#endif	/* EE_RX200_SCI2_TXI2_ISR */

/*
 * SCI2 TX End interrupt.
 */
#ifdef	EE_RX200_SCI2_TEI2_ISR
extern void EE_RX200_SCI2_TEI2_ISR(void);
#endif	/* EE_RX200_SCI2_TEI2_ISR */

/*
 * SCI3 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI3_ERI3_ISR
extern void EE_RX200_SCI3_ERI3_ISR(void);
#endif	/* EE_RX200_SCI3_ERI3_ISR */

/*
 * SCI3 RX interrupt.
 */
#ifdef	EE_RX200_SCI3_RXI3_ISR
extern void EE_RX200_SCI3_RXI3_ISR(void);
#endif	/* EE_RX200_SCI3_RXI3_ISR */

/*
 * SCI3 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI3_TXI3_ISR
extern void EE_RX200_SCI3_TXI3_ISR(void);
#endif	/* EE_RX200_SCI3_TXI3_ISR */

/*
 * SCI3 TX End interrupt.
 */
#ifdef	EE_RX200_SCI3_TEI3_ISR
extern void EE_RX200_SCI3_TEI3_ISR(void);
#endif	/* EE_RX200_SCI3_TEI3_ISR */

/*
 * SCI4 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI4_ERI4_ISR
extern void EE_RX200_SCI4_ERI4_ISR(void);
#endif	/* EE_RX200_SCI4_ERI4_ISR */

/*
 * SCI4 RX interrupt.
 */
#ifdef	EE_RX200_SCI4_RXI4_ISR
extern void EE_RX200_SCI4_RXI4_ISR(void);
#endif	/* EE_RX200_SCI4_RXI4_ISR */

/*
 * SCI4 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI4_TXI4_ISR
extern void EE_RX200_SCI4_TXI4_ISR(void);
#endif	/* EE_RX200_SCI4_TXI4_ISR */

/*
 * SCI4 TX End interrupt.
 */
#ifdef	EE_RX200_SCI4_TEI4_ISR
extern void EE_RX200_SCI4_TEI4_ISR(void);
#endif	/* EE_RX200_SCI4_TEI4_ISR */

/*
 * DMAC channel 0 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC0I_ISR
extern void EE_RX200_DMAC_DMAC0I_ISR(void);
#endif	/* EE_RX200_DMAC_DMAC0I_ISR */

/*
 * DMAC channel 1 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC1I_ISR
extern void EE_RX200_DMAC_DMAC1I_ISR(void);
#endif	/* EE_RX200_DMAC_DMAC1I_ISR */

/*
 * DMAC channel 2 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC2I_ISR
extern void EE_RX200_DMAC_DMAC2I_ISR(void);
#endif	/* EE_RX200_DMAC_DMAC2I_ISR */

/*
 * DMAC channel 3 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC3I_ISR
extern void EE_RX200_DMAC_DMAC3I_ISR(void);
#endif	/* EE_RX200_DMAC_DMAC3I_ISR */

/*
 * SCI7 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI7_ERI7_ISR
extern void EE_RX200_SCI7_ERI7_ISR(void);
#endif	/* EE_RX200_SCI7_ERI7_ISR */

/*
 * SCI7 RX interrupt.
 */
#ifdef	EE_RX200_SCI7_RXI7_ISR
extern void EE_RX200_SCI7_RXI7_ISR(void);
#endif	/* EE_RX200_SCI7_RXI7_ISR */

/*
 * SCI7 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI7_TXI7_ISR
extern void EE_RX200_SCI7_TXI7_ISR(void);
#endif	/* EE_RX200_SCI7_TXI7_ISR */

/*
 * SCI7 TX End interrupt.
 */
#ifdef	EE_RX200_SCI7_TEI7_ISR
extern void EE_RX200_SCI7_TEI7_ISR(void);
#endif	/* EE_RX200_SCI7_TEI7_ISR */

/*
 * SCI10 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI10_ERI10_ISR
extern void EE_RX200_SCI10_ERI10_ISR(void);
#endif	/* EE_RX200_SCI10_ERI10_ISR */

/*
 * SCI10 RX interrupt.
 */
#ifdef	EE_RX200_SCI10_RXI10_ISR
extern void EE_RX200_SCI10_RXI10_ISR(void);
#endif	/* EE_RX200_SCI10_RXI10_ISR */

/*
 * SCI10 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI10_TXI10_ISR
extern void EE_RX200_SCI10_TXI10_ISR(void);
#endif	/* EE_RX200_SCI10_TXI10_ISR */

/*
 * SCI10 TX End interrupt.
 */
#ifdef	EE_RX200_SCI10_TEI10_ISR
extern void EE_RX200_SCI10_TEI10_ISR(void);
#endif	/* EE_RX200_SCI10_TEI10_ISR */

/*
 * SCI0 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI0_ERI0_ISR
extern void EE_RX200_SCI0_ERI0_ISR(void);
#endif	/* EE_RX200_SCI0_ERI0_ISR */

/*
 * SCI0 RX interrupt.
 */
#ifdef	EE_RX200_SCI0_RXI0_ISR
extern void EE_RX200_SCI0_RXI0_ISR(void);
#endif	/* EE_RX200_SCI0_RXI0_ISR */

/*
 * SCI0 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI0_TXI0_ISR
extern void EE_RX200_SCI0_TXI0_ISR(void);
#endif	/* EE_RX200_SCI0_TXI0_ISR */

/*
 * SCI0 TX End interrupt.
 */
#ifdef	EE_RX200_SCI0_TEI0_ISR
extern void EE_RX200_SCI0_TEI0_ISR(void);
#endif	/* EE_RX200_SCI0_TEI0_ISR */

/*
 * SCI1 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI1_ERI1_ISR
extern void EE_RX200_SCI1_ERI1_ISR(void);
#endif	/* EE_RX200_SCI1_ERI1_ISR */

/*
 * SCI1 RX interrupt.
 */
#ifdef	EE_RX200_SCI1_RXI1_ISR
extern void EE_RX200_SCI1_RXI1_ISR(void);
#endif	/* EE_RX200_SCI1_RXI1_ISR */

/*
 * SCI1 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI1_TXI1_ISR
extern void EE_RX200_SCI1_TXI1_ISR(void);
#endif	/* EE_RX200_SCI1_TXI1_ISR */

/*
 * SCI1 TX End interrupt.
 */
#ifdef	EE_RX200_SCI1_TEI1_ISR
extern void EE_RX200_SCI1_TEI1_ISR(void);
#endif	/* EE_RX200_SCI1_TEI1_ISR */

/*
 * SCI5 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI5_ERI5_ISR
extern void EE_RX200_SCI5_ERI5_ISR(void);
#endif	/* EE_RX200_SCI5_ERI5_ISR */

/*
 * SCI5 RX interrupt.
 */
#ifdef	EE_RX200_SCI5_RXI5_ISR
extern void EE_RX200_SCI5_RXI5_ISR(void);
#endif	/* EE_RX200_SCI5_RXI5_ISR */

/*
 * SCI5 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI5_TXI5_ISR
extern void EE_RX200_SCI5_TXI5_ISR(void);
#endif	/* EE_RX200_SCI5_TXI5_ISR */

/*
 * SCI5 TX End interrupt.
 */
#ifdef	EE_RX200_SCI5_TEI5_ISR
extern void EE_RX200_SCI5_TEI5_ISR(void);
#endif	/* EE_RX200_SCI5_TEI5_ISR */

/*
 * SCI6 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI6_ERI6_ISR
extern void EE_RX200_SCI6_ERI6_ISR(void);
#endif	/* EE_RX200_SCI6_ERI6_ISR */

/*
 * SCI6 RX interrupt.
 */
#ifdef	EE_RX200_SCI6_RXI6_ISR
extern void EE_RX200_SCI6_RXI6_ISR(void);
#endif	/* EE_RX200_SCI6_RXI6_ISR */

/*
 * SCI6 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI6_TXI6_ISR
extern void EE_RX200_SCI6_TXI6_ISR(void);
#endif	/* EE_RX200_SCI6_TXI6_ISR */

/*
 * SCI6 TX End interrupt.
 */
#ifdef	EE_RX200_SCI6_TEI6_ISR
extern void EE_RX200_SCI6_TEI6_ISR(void);
#endif	/* EE_RX200_SCI6_TEI6_ISR */

/*
 * SCI8 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI8_ERI8_ISR
extern void EE_RX200_SCI8_ERI8_ISR(void);
#endif	/* EE_RX200_SCI8_ERI8_ISR */

/*
 * SCI8 RX interrupt.
 */
#ifdef	EE_RX200_SCI8_RXI8_ISR
extern void EE_RX200_SCI8_RXI8_ISR(void);
#endif	/* EE_RX200_SCI8_RXI8_ISR */

/*
 * SCI8 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI8_TXI8_ISR
extern void EE_RX200_SCI8_TXI8_ISR(void);
#endif	/* EE_RX200_SCI8_TXI8_ISR */

/*
 * SCI8 TX End interrupt.
 */
#ifdef	EE_RX200_SCI8_TEI8_ISR
extern void EE_RX200_SCI8_TEI8_ISR(void);
#endif	/* EE_RX200_SCI8_TEI8_ISR */

/*
 * SCI9 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI9_ERI9_ISR
extern void EE_RX200_SCI9_ERI9_ISR(void);
#endif	/* EE_RX200_SCI9_ERI9_ISR */

/*
 * SCI9 RX interrupt.
 */
#ifdef	EE_RX200_SCI9_RXI9_ISR
extern void EE_RX200_SCI9_RXI9_ISR(void);
#endif	/* EE_RX200_SCI9_RXI9_ISR */

/*
 * SCI9 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI9_TXI9_ISR
extern void EE_RX200_SCI9_TXI9_ISR(void);
#endif	/* EE_RX200_SCI9_TXI9_ISR */

/*
 * SCI9 TX End interrupt.
 */
#ifdef	EE_RX200_SCI9_TEI9_ISR
extern void EE_RX200_SCI9_TEI9_ISR(void);
#endif	/* EE_RX200_SCI9_TEI9_ISR */

/*
 * SCI12 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI12_ERI12_ISR
extern void EE_RX200_SCI12_ERI12_ISR(void);
#endif	/* EE_RX200_SCI12_ERI12_ISR */

/*
 * SCI12 RX interrupt.
 */
#ifdef	EE_RX200_SCI12_RXI12_ISR
extern void EE_RX200_SCI12_RXI12_ISR(void);
#endif	/* EE_RX200_SCI12_RXI12_ISR */

/*
 * SCI12 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI12_TXI12_ISR
extern void EE_RX200_SCI12_TXI12_ISR(void);
#endif	/* EE_RX200_SCI12_TXI12_ISR */

/*
 * SCI12 TX End interrupt.
 */
#ifdef	EE_RX200_SCI12_TEI12_ISR
extern void EE_RX200_SCI12_TEI12_ISR(void);
#endif	/* EE_RX200_SCI12_TEI12_ISR */

/*
 * SCI12 Extended Serial Mode Control 0 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX0_ISR
extern void EE_RX200_SCI12_SCIX0_ISR(void);
#endif	/* EE_RX200_SCI12_SCIX0_ISR */

/*
 * SCI12 Extended Serial Mode Control 1 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX1_ISR
extern void EE_RX200_SCI12_SCIX1_ISR(void);
#endif	/* EE_RX200_SCI12_SCIX1_ISR */

/*
 * SCI12 Extended Serial Mode Control 2 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX2_ISR
extern void EE_RX200_SCI12_SCIX2_ISR(void);
#endif	/* EE_RX200_SCI12_SCIX2_ISR */

/*
 * SCI12 Extended Serial Mode Control 3 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX3_ISR
extern void EE_RX200_SCI12_SCIX3_ISR(void);
#endif	/* EE_RX200_SCI12_SCIX3_ISR */

/*
 * RIIC0 Event/Error interrupt.
 */
#ifdef	EE_RX200_RIIC0_EEI0_ISR
extern void EE_RX200_RIIC0_EEI0_ISR(void);
#endif	/* EE_RX200_RIIC0_EEI0_ISR */

/*
 * RIIC0 Receive Data Full interrupt.
 */
#ifdef	EE_RX200_RIIC0_RXI0_ISR
extern void EE_RX200_RIIC0_RXI0_ISR(void);
#endif	/* EE_RX200_RIIC0_RXI0_ISR */

/*
 * RIIC0 TX End interrupt.
 */
#ifdef	EE_RX200_RIIC0_TXI0_ISR
extern void EE_RX200_RIIC0_TXI0_ISR(void);
#endif	/* EE_RX200_RIIC0_TXI0_ISR */

/*
 * RIIC0 TX Data Empty interrupt.
 */
#ifdef	EE_RX200_RIIC0_TEI0_ISR
extern void EE_RX200_RIIC0_TEI0_ISR(void);
#endif	/* EE_RX200_RIIC0_TEI0_ISR */


/*
 * SCI11 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI11_ERI11_ISR
extern void EE_RX200_SCI11_ERI11_ISR(void);
#endif	/* EE_RX200_SCI11_ERI11_ISR */

/*
 * SCI11 RX interrupt.
 */
#ifdef	EE_RX200_SCI11_RXI11_ISR
extern void EE_RX200_SCI11_RXI11_ISR(void);
#endif	/* EE_RX200_SCI11_RXI11_ISR */

/*
 * SCI11 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI11_TXI11_ISR
extern void EE_RX200_SCI11_TXI11_ISR(void);
#endif	/* EE_RX200_SCI11_TXI11_ISR */

/*
 * SCI11 TX End interrupt.
 */
#ifdef	EE_RX200_SCI11_TEI11_ISR
extern void EE_RX200_SCI11_TEI11_ISR(void);
#endif	/* EE_RX200_SCI11_TEI11_ISR */

#pragma section C C$VECT

/*
 * ISR Initialization.
 */
void EE_rx200_init_isr(void)
{

/*
 * Bus-error interrupt.
 */
#ifdef	EE_RX200_BSC_BUSERR_ISR
#ifdef	EE_RX200_BSC_BUSERR_ISR_PRI
  EE_RX200_ICU_IPR_BSC_BUSERR = EE_RX200_BSC_BUSERR_ISR_PRI;
#endif	/* EE_RX200_BSC_BUSERR_ISR_PRI */
  EE_RX200_ICU_IER_BSC_BUSERR |= EE_RX200_ICU_BSC_BUSERR_MASK;
#endif	/* EE_RX200_BSC_BUSERR_ISR */


/*
 * Flash interface error interrupt.
 */
#ifdef	EE_RX200_FCU_FIFERR_ISR
#ifdef	EE_RX200_FCU_FIFERR_ISR_PRI
  EE_RX200_ICU_IPR_FCU_FIFERR = EE_RX200_FCU_FIFERR_ISR_PRI;
#endif	/* EE_RX200_FCU_FIFERR_ISR_PRI */
  EE_RX200_ICU_IER_FCU_FIFERR |= EE_RX200_ICU_FCU_FIFERR_MASK;
#endif	/* EE_RX200_FCU_FIFERR_ISR */

/*
 * Flash READY interrupt.
 */
#ifdef	EE_RX200_FCU_FRDYI_ISR
#ifdef	EE_RX200_FCU_FRDYI_ISR_PRI
  EE_RX200_ICU_IPR_FCU_FRDYI = EE_RX200_FCU_FRDYI_ISR_PRI;
#endif	/* EE_RX200_FCU_FRDYI_ISR_PRI */
  EE_RX200_ICU_IER_FCU_FRDYI |= EE_RX200_ICU_FCU_FRDYI_MASK;
#endif	/* EE_RX200_FCU_FRDYI_ISR */

/*
 * Software interrupt.
 */
#ifdef	EE_RX200_ICU_SWINT_ISR
#ifdef	EE_RX200_ICU_SWINT_ISR_PRI
  EE_RX200_ICU_IPR_ICU_SWINT = EE_RX200_ICU_SWINT_ISR_PRI;
#endif	/* EE_RX200_ICU_SWINT_ISR_PRI */
  EE_RX200_ICU_IER_ICU_SWINT |= EE_RX200_ICU_ICU_SWINT_MASK;
#endif	/* EE_RX200_ICU_SWINT_ISR */

/*
 * Compare Match 0 interrupt.
 */
#ifdef	EE_RX200_CMT0_CMI0_ISR
#ifdef	EE_RX200_CMT0_CMI0_ISR_PRI
  EE_RX200_ICU_IPR_CMT0_CMI0 = EE_RX200_CMT0_CMI0_ISR_PRI;
#endif	/* EE_RX200_CMT0_CMI0_ISR_PRI */
  EE_RX200_ICU_IER_CMT0_CMI0 |= EE_RX200_ICU_CMT0_CMI0_MASK;
#endif	/* EE_RX200_CMT0_CMI0_ISR */

/*
 * Compare Match 1 interrupt.
 */
#ifdef	EE_RX200_CMT1_CMI1_ISR
#ifdef	EE_RX200_CMT1_CMI1_ISR_PRI
  EE_RX200_ICU_IPR_CMT1_CMI1 = EE_RX200_CMT1_CMI1_ISR_PRI;
#endif	/* EE_RX200_CMT1_CMI0_ISR_PRI */
  EE_RX200_ICU_IER_CMT1_CMI1 |= EE_RX200_ICU_CMT1_CMI1_MASK;
#endif	/* EE_RX200_CMT1_CMI1_ISR */

/*
 * Compare Match 2 interrupt.
 */
#ifdef	EE_RX200_CMT2_CMI2_ISR
#ifdef	EE_RX200_CMT2_CMI2_ISR_PRI
  EE_RX200_ICU_IPR_CMT2_CMI2 = EE_RX200_CMT2_CMI2_ISR_PRI;
#endif	/* EE_RX200_CMT2_CMI2_ISR_PRI */
  EE_RX200_ICU_IER_CMT2_CMI2 |= EE_RX200_ICU_CMT2_CMI2_MASK;
#endif	/* EE_RX200_CMT2_CMI2_ISR */

/*
 * Compare Match 3 interrupt.
 */
#ifdef	EE_RX200_CMT3_CMI3_ISR
#ifdef	EE_RX200_CMT3_CMI3_ISR_PRI
  EE_RX200_ICU_IPR_CMT3_CMI3 = EE_RX200_CMT3_CMI3_ISR_PRI;
#endif	/* EE_RX200_CMT3_CMI3_ISR_PRI */
  EE_RX200_ICU_IER_CMT3_CMI3 |= EE_RX200_ICU_CMT3_CMI3_MASK;
#endif	/* EE_RX200_CMT3_CMI3_ISR */

/*
 * Frequency Error interrupt.
 */
#ifdef	EE_RX200_CAC_FERRF_ISR
#ifdef	EE_RX200_CAC_FERRF_ISR_PRI
  EE_RX200_ICU_IPR_CAC_FERRF = EE_RX200_CAC_FERRF_ISR_PRI;
#endif	/* EE_RX200_CAC_FERRF_ISR_PRI */
  EE_RX200_ICU_IER_CAC_FERRF |= EE_RX200_ICU_CAC_FERRF_MASK;
#endif	/* EE_RX200_CAC_FERRF_ISR */

/*
 * Measurement End interrupt.
 */
#ifdef	EE_RX200_CAC_MENDF_ISR
#ifdef	EE_RX200_CAC_MENDF_ISR_PRI
  EE_RX200_ICU_IPR_CAC_MENDF = EE_RX200_CAC_MENDF_ISR_PRI;
#endif	/* EE_RX200_CAC_MENDF_ISR_PRI */
  EE_RX200_ICU_IER_CAC_MENDF |= EE_RX200_ICU_CAC_MENDF_MASK;
#endif	/* EE_RX200_CAC_MENDF_ISR */

/*
 * Overflow interrupt.
 */
#ifdef	EE_RX200_CAC_OVFF_ISR
#ifdef	EE_RX200_CAC_OVFF_ISR_PRI
  EE_RX200_ICU_IPR_CAC_OVFF = EE_RX200_CAC_OVFF_ISR_PRI;
#endif	/* EE_RX200_CAC_OVFF_ISR_PRI */
  EE_RX200_ICU_IER_CAC_OVFF |= EE_RX200_ICU_CAC_OVFF_MASK;
#endif	/* EE_RX200_CAC_OVFF_ISR */

/*
 * RSPI Errors interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPEI0_ISR
#ifdef	EE_RX200_RSPI0_SPEI0_ISR_PRI
  EE_RX200_ICU_IPR_RSPI0_SPEI0 = EE_RX200_RSPI0_SPEI0_ISR_PRI;
#endif	/* EE_RX200_RSPI0_SPEI0_ISR_PRI */
  EE_RX200_ICU_IER_RSPI0_SPEI0 |= EE_RX200_ICU_RSPI0_SPEI0_MASK;
#endif	/* EE_RX200_RSPI0_SPEI0_ISR */

/*
 * Receive Buffer Full interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPRI0_ISR
#ifdef	EE_RX200_RSPI0_SPRI0_ISR_PRI
  EE_RX200_ICU_IPR_RSPI0_SPRI0 = EE_RX200_RSPI0_SPRI0_ISR_PRI;
#endif	/* EE_RX200_RSPI0_SPRI0_ISR_PRI */
  EE_RX200_ICU_IER_RSPI0_SPRI0 |= EE_RX200_ICU_RSPI0_SPRI0_MASK;
#endif	/* EE_RX200_RSPI0_SPRI0_ISR */

/*
 * Transmit Buffer Full interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPTI0_ISR
#ifdef	EE_RX200_RSPI0_SPTI0_ISR_PRI
  EE_RX200_ICU_IPR_RSPI0_SPTI0 = EE_RX200_RSPI0_SPTI0_ISR_PRI;
#endif	/* EE_RX200_RSPI0_SPTI0_ISR_PRI */
  EE_RX200_ICU_IER_RSPI0_SPTI0 |= EE_RX200_ICU_RSPI0_SPTI0_MASK;
#endif	/* EE_RX200_RSPI0_SPTI0_ISR */

/*
 * RSPI Idle interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPII0_ISR
#ifdef	EE_RX200_RSPI0_SPII0_ISR_PRI
  EE_RX200_ICU_IPR_RSPI0_SPII0 = EE_RX200_RSPI0_SPII0_ISR_PRI;
#endif	/* EE_RX200_RSPI0_SPII0_ISR_PRI */
  EE_RX200_ICU_IER_RSPI0_SPII0 |= EE_RX200_ICU_RSPI0_SPII0_MASK;
#endif	/* EE_RX200_RSPI0_SPII0_ISR */

/*
 * Data Operation Circuit interrupt.
 */
#ifdef	EE_RX200_DOC_DOPCF_ISR
#ifdef	EE_RX200_DOC_DOPCF_ISR_PRI
  EE_RX200_ICU_IPR_DOC_DOPCF = EE_RX200_DOC_DOPCF_ISR_PRI;
#endif	/* EE_RX200_DOC_DOPCF_ISR_PRI */
  EE_RX200_ICU_IER_DOC_DOPCF |= EE_RX200_ICU_DOC_DOPCF_MASK;
#endif	/* EE_RX200_DOC_DOPCF_ISR */

/*
 * Comparator B0 interrupt.
 */
#ifdef	EE_RX200_CMPB_CMPB0_ISR
#ifdef	EE_RX200_CMPB_CMPB0_ISR_PRI
  EE_RX200_ICU_IPR_CMPB_CMPB0 = EE_RX200_CMPB_CMPB0_ISR_PRI;
#endif	/* EE_RX200_CMPB_CMPB0_ISR_PRI */
  EE_RX200_ICU_IER_CMPB_CMPB0 |= EE_RX200_ICU_CMPB_CMPB0_MASK;
#endif	/* EE_RX200_CMPB_CMPB0_ISR */

/*
 * Comparator B1 interrupt.
 */
#ifdef	EE_RX200_CMPB_CMPB1_ISR
#ifdef	EE_RX200_CMPB_CMPB1_ISR_PRI
  EE_RX200_ICU_IPR_CMPB_CMPB1 = EE_RX200_CMPB_CMPB1_ISR_PRI;
#endif	/* EE_RX200_CMPB_CMPB1_ISR_PRI */
  EE_RX200_ICU_IER_CMPB_CMPB1 |= EE_RX200_ICU_CMPB_CMPB1_MASK;
#endif	/* EE_RX200_CMPB_CMPB1_ISR */

/*
 * RTC Count Up interrupt.
 */
#ifdef	EE_RX200_RTC_CUP_ISR
#ifdef	EE_RX200_RTC_CUP_ISR_PRI
  EE_RX200_ICU_IPR_RTC_CUP = EE_RX200_RTC_CUP_ISR_PRI;
#endif	/* EE_RX200_RTC_CUP_ISR_PRI */
  EE_RX200_ICU_IER_RTC_CUP |= EE_RX200_ICU_RTC_CUP_MASK;
#endif	/* EE_RX200_RTC_CUP_ISR */

/*
 * IRQ0 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ0_ISR
#ifdef	EE_RX200_ICU_IRQ0_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ0 = EE_RX200_ICU_IRQ0_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ0_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ0 |= EE_RX200_ICU_ICU_IRQ0_MASK;
#endif	/* EE_RX200_ICU_IRQ0_ISR */

/*
 * IRQ1 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ1_ISR
#ifdef	EE_RX200_ICU_IRQ1_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ1 = EE_RX200_ICU_IRQ1_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ1_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ1 |= EE_RX200_ICU_ICU_IRQ1_MASK;
#endif	/* EE_RX200_ICU_IRQ1_ISR */

/*
 * IRQ2 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ2_ISR
#ifdef	EE_RX200_ICU_IRQ2_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ2 = EE_RX200_ICU_IRQ2_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ2_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ2 |= EE_RX200_ICU_ICU_IRQ2_MASK;
#endif	/* EE_RX200_ICU_IRQ2_ISR */

/*
 * IRQ3 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ3_ISR
#ifdef	EE_RX200_ICU_IRQ3_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ3 = EE_RX200_ICU_IRQ3_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ3_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ3 |= EE_RX200_ICU_ICU_IRQ3_MASK;
#endif	/* EE_RX200_ICU_IRQ3_ISR */

/*
 * IRQ4 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ4_ISR
#ifdef	EE_RX200_ICU_IRQ4_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ4 = EE_RX200_ICU_IRQ4_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ4_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ4 |= EE_RX200_ICU_ICU_IRQ4_MASK;
#endif	/* EE_RX200_ICU_IRQ4_ISR */

/*
 * IRQ5 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ5_ISR
#ifdef	EE_RX200_ICU_IRQ5_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ5 = EE_RX200_ICU_IRQ5_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ5_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ5 |= EE_RX200_ICU_ICU_IRQ5_MASK;
#endif	/* EE_RX200_ICU_IRQ5_ISR */

/*
 * IRQ6 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ6_ISR
#ifdef	EE_RX200_ICU_IRQ6_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ6 = EE_RX200_ICU_IRQ6_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ6_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ6 |= EE_RX200_ICU_ICU_IRQ6_MASK;
#endif	/* EE_RX200_ICU_IRQ6_ISR */

/*
 * IRQ7 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ7_ISR
#ifdef	EE_RX200_ICU_IRQ7_ISR_PRI
  EE_RX200_ICU_IPR_ICU_IRQ7 = EE_RX200_ICU_IRQ7_ISR_PRI;
#endif	/* EE_RX200_ICU_IRQ7_ISR_PRI */
  EE_RX200_ICU_IER_ICU_IRQ7 |= EE_RX200_ICU_ICU_IRQ7_MASK;
#endif	/* EE_RX200_ICU_IRQ7_ISR */

/*
 * LVD1/CMPA1 interrupt.
 */
#ifdef	EE_RX200_LVD1_CMPA1_ISR
#ifdef	EE_RX200_LVD1_CMPA1_ISR_PRI
  EE_RX200_ICU_IPR_LVD1_CMPA1 = EE_RX200_LVD1_CMPA1_ISR_PRI;
#endif	/* EE_RX200_LVD1_CMPA1_ISR_PRI */
  EE_RX200_ICU_IER_LVD1_CMPA1 |= EE_RX200_ICU_LVD1_CMPA1_MASK;
#endif	/* EE_RX200_LVD1_CMPA1_ISR */

/*
 * LVD2/CMPA2 interrupt.
 */
#ifdef	EE_RX200_LVD2_CMPA2_ISR
#ifdef	EE_RX200_LVD2_CMPA2_ISR_PRI
  EE_RX200_ICU_IPR_LVD2_CMPA2 = EE_RX200_LVD2_CMPA2_ISR_PRI;
#endif	/* EE_RX200_LVD2_CMPA2_ISR_PRI */
  EE_RX200_ICU_IER_LVD2_CMPA2 |= EE_RX200_ICU_LVD2_CMPA2_MASK;
#endif	/* EE_RX200_LVD2_CMPA2_ISR */

/*
 * RTC Alarm interrupt.
 */
#ifdef	EE_RX200_RTC_ALM_ISR
#ifdef	EE_RX200_RTC_ALM_ISR_PRI
  EE_RX200_ICU_IPR_RTC_ALM = EE_RX200_RTC_ALM_ISR_PRI;
#endif	/* EE_RX200_RTC_ALM_ISR_PRI */
  EE_RX200_ICU_IER_RTC_ALM |= EE_RX200_ICU_RTC_ALM_MASK;
#endif	/* EE_RX200_RTC_ALM_ISR */

/*
 * RTC Periodic interrupt.
 */
#ifdef	EE_RX200_RTC_PRD_ISR
#ifdef	EE_RX200_RTC_PRD_ISR_PRI
  EE_RX200_ICU_IPR_RTC_PRD = EE_RX200_RTC_PRD_ISR_PRI;
#endif	/* EE_RX200_RTC_PRD_ISR_PRI */
  EE_RX200_ICU_IER_RTC_PRD |= EE_RX200_ICU_RTC_PRD_MASK;
#endif	/* EE_RX200_RTC_PRD_ISR */

/*
 * ADC Scan End interrupt.
 */
#ifdef	EE_RX200_S12AD_S12ADI0_ISR
#ifdef	EE_RX200_S12AD_S12ADI0_ISR_PRI
  EE_RX200_ICU_IPR_S12AD_S12ADI0 = EE_RX200_S12AD_S12ADI0_ISR_PRI;
#endif	/* EE_RX200_S12AD_S12ADI0_ISR_PRI */
  EE_RX200_ICU_IER_S12AD_S12ADI0 |= EE_RX200_ICU_S12AD_S12ADI0_MASK;
#endif	/* EE_RX200_S12AD_S12ADI0_ISR */

/*
 * ADC Group B Scan End interrupt.
 */
#ifdef	EE_RX200_S12AD_GBADI_ISR
#ifdef	EE_RX200_S12AD_GBADI_ISR_PRI
  EE_RX200_ICU_IPR_S12AD_GBADI = EE_RX200_S12AD_GBADI_ISR_PRI;
#endif	/* EE_RX200_S12AD_GBADI_ISR_PRI */
  EE_RX200_ICU_IER_S12AD_GBADI |= EE_RX200_ICU_S12AD_GBADI_MASK;
#endif	/* EE_RX200_S12AD_GBADI_ISR */

/*
 * Event Link SR18 interrupt.
 */
#ifdef	EE_RX200_ELC_ELSR18I_ISR
#ifdef	EE_RX200_ELC_ELSR18I_ISR_PRI
  EE_RX200_ICU_IPR_ELC_ELSR18I = EE_RX200_ELC_ELSR18I_ISR_PRI;
#endif	/* EE_RX200_ELC_ELSR18I_ISR_PRI */
  EE_RX200_ICU_IER_ELC_ELSR18I |= EE_RX200_ICU_ELC_ELSR18I_MASK;
#endif	/* EE_RX200_ELC_ELSR18I_ISR */

/*
 * Event Link SR19 interrupt.
 */
#ifdef	EE_RX200_ELC_ELSR19I_ISR
#ifdef	EE_RX200_ELC_ELSR19I_ISR_PRI
  EE_RX200_ICU_IPR_ELC_ELSR19I = EE_RX200_ELC_ELSR19I_ISR_PRI;
#endif	/* EE_RX200_ELC_ELSR19I_ISR_PRI */
  EE_RX200_ICU_IER_ELC_ELSR19I |= EE_RX200_ICU_ELC_ELSR19I_MASK;
#endif	/* EE_RX200_ELC_ELSR19I_ISR */

/*
 * MTU0 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIA0_ISR
#ifdef	EE_RX200_MTU0_TGIA0_ISR_PRI
  EE_RX200_ICU_IPR_MTU0_TGIA0 = EE_RX200_MTU0_TGIA0_ISR_PRI;
#endif	/* EE_RX200_MTU0_TGIA0_ISR_PRI */
  EE_RX200_ICU_IER_MTU0_TGIA0 |= EE_RX200_ICU_MTU0_TGIA0_MASK;
#endif	/* EE_RX200_MTU0_TGIA0_ISR */

/*
 * MTU0 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIB0_ISR
#ifdef	EE_RX200_MTU0_TGIB0_ISR_PRI
  EE_RX200_ICU_IPR_MTU0_TGIB0 = EE_RX200_MTU0_TGIB0_ISR_PRI;
#endif	/* EE_RX200_MTU0_TGIB0_ISR_PRI */
  EE_RX200_ICU_IER_MTU0_TGIB0 |= EE_RX200_ICU_MTU0_TGIB0_MASK;
#endif	/* EE_RX200_MTU0_TGIB0_ISR */

/*
 * MTU0 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIC0_ISR
#ifdef	EE_RX200_MTU0_TGIC0_ISR_PRI
  EE_RX200_ICU_IPR_MTU0_TGIC0 = EE_RX200_MTU0_TGIC0_ISR_PRI;
#endif	/* EE_RX200_MTU0_TGIC0_ISR_PRI */
  EE_RX200_ICU_IER_MTU0_TGIC0 |= EE_RX200_ICU_MTU0_TGIC0_MASK;
#endif	/* EE_RX200_MTU0_TGIC0_ISR */

/*
 * MTU0 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGID0_ISR
#ifdef	EE_RX200_MTU0_TGID0_ISR_PRI
  EE_RX200_ICU_IPR_MTU0_TGID0 = EE_RX200_MTU0_TGID0_ISR_PRI;
#endif	/* EE_RX200_MTU0_TGID0_ISR_PRI */
  EE_RX200_ICU_IER_MTU0_TGID0 |= EE_RX200_ICU_MTU0_TGID0_MASK;
#endif	/* EE_RX200_MTU0_TGID0_ISR */

/*
 * MTU0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU0_TCIV0_ISR
#ifdef	EE_RX200_MTU0_TCIV0_ISR_PRI
  EE_RX200_ICU_IPR_MTU0_TCIV0 = EE_RX200_MTU0_TCIV0_ISR_PRI;
#endif	/* EE_RX200_MTU0_TCIV0_ISR_PRI */
  EE_RX200_ICU_IER_MTU0_TCIV0 |= EE_RX200_ICU_MTU0_TCIV0_MASK;
#endif	/* EE_RX200_MTU0_TCIV0_ISR */

/*
 * MTU0 TGRE Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIE0_ISR
#ifdef	EE_RX200_MTU0_TGIE0_ISR_PRI
  EE_RX200_ICU_IPR_MTU0_TGIE0 = EE_RX200_MTU0_TGIE0_ISR_PRI;
#endif	/* EE_RX200_MTU0_TGIE0_ISR_PRI */
  EE_RX200_ICU_IER_MTU0_TGIE0 |= EE_RX200_ICU_MTU0_TGIE0_MASK;
#endif	/* EE_RX200_MTU0_TGIE0_ISR */

/*
 * MTU0 TGRF Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIF0_ISR
#ifdef	EE_RX200_MTU0_TGIF0_ISR_PRI
  EE_RX200_ICU_IPR_MTU0_TGIF0 = EE_RX200_MTU0_TGIF0_ISR_PRI;
#endif	/* EE_RX200_MTU0_TGIF0_ISR_PRI */
  EE_RX200_ICU_IER_MTU0_TGIF0 |= EE_RX200_ICU_MTU0_TGIF0_MASK;
#endif	/* EE_RX200_MTU0_TGIF0_ISR */

/*
 * MTU1 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU1_TGIA1_ISR
#ifdef	EE_RX200_MTU1_TGIA1_ISR_PRI
  EE_RX200_ICU_IPR_MTU1_TGIA1 = EE_RX200_MTU1_TGIA1_ISR_PRI;
#endif	/* EE_RX200_MTU1_TGIA1_ISR_PRI */
  EE_RX200_ICU_IER_MTU1_TGIA1 |= EE_RX200_ICU_MTU1_TGIA1_MASK;
#endif	/* EE_RX200_MTU1_TGIA1_ISR */

/*
 * MTU1 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU1_TGIB1_ISR
#ifdef	EE_RX200_MTU1_TGIB1_ISR_PRI
  EE_RX200_ICU_IPR_MTU1_TGIB1 = EE_RX200_MTU1_TGIB1_ISR_PRI;
#endif	/* EE_RX200_MTU1_TGIB1_ISR_PRI */
  EE_RX200_ICU_IER_MTU1_TGIB1 |= EE_RX200_ICU_MTU1_TGIB1_MASK;
#endif	/* EE_RX200_MTU1_TGIB1_ISR */

/*
 * MTU1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU1_TCIV1_ISR
#ifdef	EE_RX200_MTU1_TCIV1_ISR_PRI
  EE_RX200_ICU_IPR_MTU1_TCIV1 = EE_RX200_MTU1_TCIV1_ISR_PRI;
#endif	/* EE_RX200_MTU1_TCIV1_ISR_PRI */
  EE_RX200_ICU_IER_MTU1_TCIV1 |= EE_RX200_ICU_MTU1_TCIV1_MASK;
#endif	/* EE_RX200_MTU1_TCIV1_ISR */

/*
 * MTU1 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_MTU1_TCIU1_ISR
#ifdef	EE_RX200_MTU1_TCIU1_ISR_PRI
  EE_RX200_ICU_IPR_MTU1_TCIU1 = EE_RX200_MTU1_TCIU1_ISR_PRI;
#endif	/* EE_RX200_MTU1_TCIU1_ISR_PRI */
  EE_RX200_ICU_IER_MTU1_TCIU1 |= EE_RX200_ICU_MTU1_TCIU1_MASK;
#endif	/* EE_RX200_MTU1_TCIU1_ISR */

/*
 * MTU2 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU2_TGIA2_ISR
#ifdef	EE_RX200_MTU2_TGIA2_ISR_PRI
  EE_RX200_ICU_IPR_MTU2_TGIA2 = EE_RX200_MTU2_TGIA2_ISR_PRI;
#endif	/* EE_RX200_MTU2_TGIA2_ISR_PRI */
  EE_RX200_ICU_IER_MTU2_TGIA2 |= EE_RX200_ICU_MTU2_TGIA2_MASK;
#endif	/* EE_RX200_MTU2_TGIA2_ISR */

/*
 * MTU2 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU2_TGIB2_ISR
#ifdef	EE_RX200_MTU2_TGIB2_ISR_PRI
  EE_RX200_ICU_IPR_MTU2_TGIB2 = EE_RX200_MTU2_TGIB2_ISR_PRI;
#endif	/* EE_RX200_MTU2_TGIB2_ISR_PRI */
  EE_RX200_ICU_IER_MTU2_TGIB2 |= EE_RX200_ICU_MTU2_TGIB2_MASK;
#endif	/* EE_RX200_MTU2_TGIB2_ISR */

/*
 * MTU2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU2_TCIV2_ISR
#ifdef	EE_RX200_MTU2_TCIV2_ISR_PRI
  EE_RX200_ICU_IPR_MTU2_TCIV2 = EE_RX200_MTU2_TCIV2_ISR_PRI;
#endif	/* EE_RX200_MTU2_TCIV2_ISR_PRI */
  EE_RX200_ICU_IER_MTU2_TCIV2 |= EE_RX200_ICU_MTU2_TCIV2_MASK;
#endif	/* EE_RX200_MTU2_TCIV2_ISR */

/*
 * MTU2 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_MTU2_TCIU2_ISR
#ifdef	EE_RX200_MTU2_TCIU2_ISR_PRI
  EE_RX200_ICU_IPR_MTU2_TCIU2 = EE_RX200_MTU2_TCIU2_ISR_PRI;
#endif	/* EE_RX200_MTU2_TCIU2_ISR_PRI */
  EE_RX200_ICU_IER_MTU2_TCIU2 |= EE_RX200_ICU_MTU2_TCIU2_MASK;
#endif	/* EE_RX200_MTU2_TCIU2_ISR */

/*
 * MTU3 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIA3_ISR
#ifdef	EE_RX200_MTU3_TGIA3_ISR_PRI
  EE_RX200_ICU_IPR_MTU3_TGIA3 = EE_RX200_MTU3_TGIA3_ISR_PRI;
#endif	/* EE_RX200_MTU3_TGIA3_ISR_PRI */
  EE_RX200_ICU_IER_MTU3_TGIA3 |= EE_RX200_ICU_MTU3_TGIA3_MASK;
#endif	/* EE_RX200_MTU3_TGIA3_ISR */

/*
 * MTU3 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIB3_ISR
#ifdef	EE_RX200_MTU3_TGIB3_ISR_PRI
  EE_RX200_ICU_IPR_MTU3_TGIB3 = EE_RX200_MTU3_TGIB3_ISR_PRI;
#endif	/* EE_RX200_MTU3_TGIB3_ISR_PRI */
  EE_RX200_ICU_IER_MTU3_TGIB3 |= EE_RX200_ICU_MTU3_TGIB3_MASK;
#endif	/* EE_RX200_MTU3_TGIB3_ISR */

/*
 * MTU3 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIC3_ISR
#ifdef	EE_RX200_MTU3_TGIC3_ISR_PRI
  EE_RX200_ICU_IPR_MTU3_TGIC3 = EE_RX200_MTU3_TGIC3_ISR_PRI;
#endif	/* EE_RX200_MTU3_TGIC3_ISR_PRI */
  EE_RX200_ICU_IER_MTU3_TGIC3 |= EE_RX200_ICU_MTU3_TGIC3_MASK;
#endif	/* EE_RX200_MTU3_TGIC3_ISR */

/*
 * MTU3 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGID3_ISR
#ifdef	EE_RX200_MTU3_TGID3_ISR_PRI
  EE_RX200_ICU_IPR_MTU3_TGID3 = EE_RX200_MTU3_TGID3_ISR_PRI;
#endif	/* EE_RX200_MTU3_TGID3_ISR_PRI */
  EE_RX200_ICU_IER_MTU3_TGID3 |= EE_RX200_ICU_MTU3_TGID3_MASK;
#endif	/* EE_RX200_MTU3_TGID3_ISR */

/*
 * MTU3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU3_TCIV3_ISR
#ifdef	EE_RX200_MTU3_TCIV3_ISR_PRI
  EE_RX200_ICU_IPR_MTU3_TCIV3 = EE_RX200_MTU3_TCIV3_ISR_PRI;
#endif	/* EE_RX200_MTU3_TCIV3_ISR_PRI */
  EE_RX200_ICU_IER_MTU3_TCIV3 |= EE_RX200_ICU_MTU3_TCIV3_MASK;
#endif	/* EE_RX200_MTU3_TCIV3_ISR */

/*
 * MTU4 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIA4_ISR
#ifdef	EE_RX200_MTU4_TGIA4_ISR_PRI
  EE_RX200_ICU_IPR_MTU4_TGIA4 = EE_RX200_MTU4_TGIA4_ISR_PRI;
#endif	/* EE_RX200_MTU4_TGIA4_ISR_PRI */
  EE_RX200_ICU_IER_MTU4_TGIA4 |= EE_RX200_ICU_MTU4_TGIA4_MASK;
#endif	/* EE_RX200_MTU4_TGIA4_ISR */

/*
 * MTU4 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIB4_ISR
#ifdef	EE_RX200_MTU4_TGIB4_ISR_PRI
  EE_RX200_ICU_IPR_MTU4_TGIB4 = EE_RX200_MTU4_TGIB4_ISR_PRI;
#endif	/* EE_RX200_MTU4_TGIB4_ISR_PRI */
  EE_RX200_ICU_IER_MTU4_TGIB4 |= EE_RX200_ICU_MTU4_TGIB4_MASK;
#endif	/* EE_RX200_MTU4_TGIB4_ISR */

/*
 * MTU4 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIC4_ISR
#ifdef	EE_RX200_MTU4_TGIC4_ISR_PRI
  EE_RX200_ICU_IPR_MTU4_TGIC4 = EE_RX200_MTU4_TGIC4_ISR_PRI;
#endif	/* EE_RX200_MTU4_TGIC4_ISR_PRI */
  EE_RX200_ICU_IER_MTU4_TGIC4 |= EE_RX200_ICU_MTU4_TGIC4_MASK;
#endif	/* EE_RX200_MTU4_TGIC4_ISR */

/*
 * MTU4 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGID4_ISR
#ifdef	EE_RX200_MTU4_TGID4_ISR_PRI
  EE_RX200_ICU_IPR_MTU4_TGID4 = EE_RX200_MTU4_TGID4_ISR_PRI;
#endif	/* EE_RX200_MTU4_TGID4_ISR_PRI */
  EE_RX200_ICU_IER_MTU4_TGID4 |= EE_RX200_ICU_MTU4_TGID4_MASK;
#endif	/* EE_RX200_MTU4_TGID4_ISR */

/*
 * MTU4 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU4_TCIV4_ISR
#ifdef	EE_RX200_MTU4_TCIV4_ISR_PRI
  EE_RX200_ICU_IPR_MTU4_TCIV4 = EE_RX200_MTU4_TCIV4_ISR_PRI;
#endif	/* EE_RX200_MTU4_TCIV4_ISR_PRI */
  EE_RX200_ICU_IER_MTU4_TCIV4 |= EE_RX200_ICU_MTU4_TCIV4_MASK;
#endif	/* EE_RX200_MTU4_TCIV4_ISR */

/*
 * MTU5 TGRU Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIU5_ISR
#ifdef	EE_RX200_MTU5_TGIU5_ISR_PRI
  EE_RX200_ICU_IPR_MTU5_TGIU5 = EE_RX200_MTU5_TGIU5_ISR_PRI;
#endif	/* EE_RX200_MTU5_TGIU5_ISR_PRI */
  EE_RX200_ICU_IER_MTU5_TGIU5 |= EE_RX200_ICU_MTU5_TGIU5_MASK;
#endif	/* EE_RX200_MTU5_TGIU5_ISR */

/*
 * MTU5 TGRV Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIV5_ISR
#ifdef	EE_RX200_MTU5_TGIV5_ISR_PRI
  EE_RX200_ICU_IPR_MTU5_TGIV5 = EE_RX200_MTU5_TGIV5_ISR_PRI;
#endif	/* EE_RX200_MTU5_TGIV5_ISR_PRI */
  EE_RX200_ICU_IER_MTU5_TGIV5 |= EE_RX200_ICU_MTU5_TGIV5_MASK;
#endif	/* EE_RX200_MTU5_TGIV5_ISR */

/*
 * MTU5 TGRW Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIW5_ISR
#ifdef	EE_RX200_MTU5_TGIW5_ISR_PRI
  EE_RX200_ICU_IPR_MTU5_TGIW5 = EE_RX200_MTU5_TGIW5_ISR_PRI;
#endif	/* EE_RX200_MTU5_TGIW5_ISR_PRI */
  EE_RX200_ICU_IER_MTU5_TGIW5 |= EE_RX200_ICU_MTU5_TGIW5_MASK;
#endif	/* EE_RX200_MTU5_TGIW5_ISR */

/*
 * TPU0 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0A_ISR
#ifdef	EE_RX200_TPU0_TGI0A_ISR_PRI
  EE_RX200_ICU_IPR_TPU0_TGI0A = EE_RX200_TPU0_TGI0A_ISR_PRI;
#endif	/* EE_RX200_TPU0_TGI0A_ISR_PRI */
  EE_RX200_ICU_IER_TPU0_TGI0A |= EE_RX200_ICU_TPU0_TGI0A_MASK;
#endif	/* EE_RX200_TPU0_TGI0A_ISR */

/*
 * TPU0 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0B_ISR
#ifdef	EE_RX200_TPU0_TGI0B_ISR_PRI
  EE_RX200_ICU_IPR_TPU0_TGI0B = EE_RX200_TPU0_TGI0B_ISR_PRI;
#endif	/* EE_RX200_TPU0_TGI0B_ISR_PRI */
  EE_RX200_ICU_IER_TPU0_TGI0B |= EE_RX200_ICU_TPU0_TGI0B_MASK;
#endif	/* EE_RX200_TPU0_TGI0B_ISR */

/*
 * TPU0 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0C_ISR
#ifdef	EE_RX200_TPU0_TGI0C_ISR_PRI
  EE_RX200_ICU_IPR_TPU0_TGI0C = EE_RX200_TPU0_TGI0C_ISR_PRI;
#endif	/* EE_RX200_TPU0_TGI0C_ISR_PRI */
  EE_RX200_ICU_IER_TPU0_TGI0C |= EE_RX200_ICU_TPU0_TGI0C_MASK;
#endif	/* EE_RX200_TPU0_TGI0C_ISR */

/*
 * TPU0 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0D_ISR
#ifdef	EE_RX200_TPU0_TGI0D_ISR_PRI
  EE_RX200_ICU_IPR_TPU0_TGI0D = EE_RX200_TPU0_TGI0D_ISR_PRI;
#endif	/* EE_RX200_TPU0_TGI0D_ISR_PRI */
  EE_RX200_ICU_IER_TPU0_TGI0D |= EE_RX200_ICU_TPU0_TGI0D_MASK;
#endif	/* EE_RX200_TPU0_TGI0D_ISR */

/*
 * TPU0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU0_TCI0V_ISR
#ifdef	EE_RX200_TPU0_TCI0V_ISR_PRI
  EE_RX200_ICU_IPR_TPU0_TCI0V = EE_RX200_TPU0_TCI0V_ISR_PRI;
#endif	/* EE_RX200_TPU0_TCI0V_ISR_PRI */
  EE_RX200_ICU_IER_TPU0_TCI0V |= EE_RX200_ICU_TPU0_TCI0V_MASK;
#endif	/* EE_RX200_TPU0_TCI0V_ISR */

/*
 * TPU1 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU1_TGI1A_ISR
#ifdef	EE_RX200_TPU1_TGI1A_ISR_PRI
  EE_RX200_ICU_IPR_TPU1_TGI1A = EE_RX200_TPU1_TGI1A_ISR_PRI;
#endif	/* EE_RX200_TPU1_TGI1A_ISR_PRI */
  EE_RX200_ICU_IER_TPU1_TGI1A |= EE_RX200_ICU_TPU1_TGI1A_MASK;
#endif	/* EE_RX200_TPU1_TGI1A_ISR */

/*
 * TPU1 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU1_TGI1B_ISR
#ifdef	EE_RX200_TPU1_TGI1B_ISR_PRI
  EE_RX200_ICU_IPR_TPU1_TGI1B = EE_RX200_TPU1_TGI1B_ISR_PRI;
#endif	/* EE_RX200_TPU1_TGI1B_ISR_PRI */
  EE_RX200_ICU_IER_TPU1_TGI1B |= EE_RX200_ICU_TPU1_TGI1B_MASK;
#endif	/* EE_RX200_TPU1_TGI1B_ISR */

/*
 * TPU1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU1_TCI1V_ISR
#ifdef	EE_RX200_TPU1_TCI1V_ISR_PRI
  EE_RX200_ICU_IPR_TPU1_TCI1V = EE_RX200_TPU1_TCI1V_ISR_PRI;
#endif	/* EE_RX200_TPU1_TCI1V_ISR_PRI */
  EE_RX200_ICU_IER_TPU1_TCI1V |= EE_RX200_ICU_TPU1_TCI1V_MASK;
#endif	/* EE_RX200_TPU1_TCI1V_ISR */

/*
 * TPU1 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU1_TCI1U_ISR
#ifdef	EE_RX200_TPU1_TCI1U_ISR_PRI
  EE_RX200_ICU_IPR_TPU1_TCI1U = EE_RX200_TPU1_TCI1U_ISR_PRI;
#endif	/* EE_RX200_TPU1_TCI1U_ISR_PRI */
  EE_RX200_ICU_IER_TPU1_TCI1U |= EE_RX200_ICU_TPU1_TCI1U_MASK;
#endif	/* EE_RX200_TPU1_TCI1U_ISR */

/*
 * TPU2 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU2_TGI2A_ISR
#ifdef	EE_RX200_TPU2_TGI2A_ISR_PRI
  EE_RX200_ICU_IPR_TPU2_TGI2A = EE_RX200_TPU2_TGI2A_ISR_PRI;
#endif	/* EE_RX200_TPU2_TGI2A_ISR_PRI */
  EE_RX200_ICU_IER_TPU2_TGI2A |= EE_RX200_ICU_TPU2_TGI2A_MASK;
#endif	/* EE_RX200_TPU2_TGI2A_ISR */

/*
 * TPU2 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU2_TGI2B_ISR
#ifdef	EE_RX200_TPU2_TGI2B_ISR_PRI
  EE_RX200_ICU_IPR_TPU2_TGI2B = EE_RX200_TPU2_TGI2B_ISR_PRI;
#endif	/* EE_RX200_TPU2_TGI2B_ISR_PRI */
  EE_RX200_ICU_IER_TPU2_TGI2B |= EE_RX200_ICU_TPU2_TGI2B_MASK;
#endif	/* EE_RX200_TPU2_TGI2B_ISR */

/*
 * TPU2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU2_TCI2V_ISR
#ifdef	EE_RX200_TPU2_TCI2V_ISR_PRI
  EE_RX200_ICU_IPR_TPU2_TCI2V = EE_RX200_TPU2_TCI2V_ISR_PRI;
#endif	/* EE_RX200_TPU2_TCI2V_ISR_PRI */
  EE_RX200_ICU_IER_TPU2_TCI2V |= EE_RX200_ICU_TPU2_TCI2V_MASK;
#endif	/* EE_RX200_TPU2_TCI2V_ISR */

/*
 * TPU2 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU2_TCI2U_ISR
#ifdef	EE_RX200_TPU2_TCI2U_ISR_PRI
  EE_RX200_ICU_IPR_TPU2_TCI2U = EE_RX200_TPU2_TCI2U_ISR_PRI;
#endif	/* EE_RX200_TPU2_TCI2U_ISR_PRI */
  EE_RX200_ICU_IER_TPU2_TCI2U |= EE_RX200_ICU_TPU2_TCI2U_MASK;
#endif	/* EE_RX200_TPU2_TCI2U_ISR */

/*
 * TPU3 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3A_ISR
#ifdef	EE_RX200_TPU3_TGI3A_ISR_PRI
  EE_RX200_ICU_IPR_TPU3_TGI3A = EE_RX200_TPU3_TGI3A_ISR_PRI;
#endif	/* EE_RX200_TPU3_TGI3A_ISR_PRI */
  EE_RX200_ICU_IER_TPU3_TGI3A |= EE_RX200_ICU_TPU3_TGI3A_MASK;
#endif	/* EE_RX200_TPU3_TGI3A_ISR */

/*
 * TPU3 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3B_ISR
#ifdef	EE_RX200_TPU3_TGI3B_ISR_PRI
  EE_RX200_ICU_IPR_TPU3_TGI3B = EE_RX200_TPU3_TGI3B_ISR_PRI;
#endif	/* EE_RX200_TPU3_TGI3B_ISR_PRI */
  EE_RX200_ICU_IER_TPU3_TGI3B |= EE_RX200_ICU_TPU3_TGI3B_MASK;
#endif	/* EE_RX200_TPU3_TGI3B_ISR */

/*
 * TPU3 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3C_ISR
#ifdef	EE_RX200_TPU3_TGI3C_ISR_PRI
  EE_RX200_ICU_IPR_TPU3_TGI3C = EE_RX200_TPU3_TGI3C_ISR_PRI;
#endif	/* EE_RX200_TPU3_TGI3C_ISR_PRI */
  EE_RX200_ICU_IER_TPU3_TGI3C |= EE_RX200_ICU_TPU3_TGI3C_MASK;
#endif	/* EE_RX200_TPU3_TGI3C_ISR */

/*
 * TPU3 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3D_ISR
#ifdef	EE_RX200_TPU3_TGI3D_ISR_PRI
  EE_RX200_ICU_IPR_TPU3_TGI3D = EE_RX200_TPU3_TGI3D_ISR_PRI;
#endif	/* EE_RX200_TPU3_TGI3D_ISR_PRI */
  EE_RX200_ICU_IER_TPU3_TGI3D |= EE_RX200_ICU_TPU3_TGI3D_MASK;
#endif	/* EE_RX200_TPU3_TGI3D_ISR */

/*
 * TPU3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU0_TCI0V_ISR
#ifdef	EE_RX200_TPU0_TCI0V_ISR_PRI
  EE_RX200_ICU_IPR_TPU0_TCI0V = EE_RX200_TPU0_TCI0V_ISR_PRI;
#endif	/* EE_RX200_TPU0_TCI0V_ISR_PRI */
  EE_RX200_ICU_IER_TPU0_TCI0V |= EE_RX200_ICU_TPU0_TCI0V_MASK;
#endif	/* EE_RX200_TPU0_TCI0V_ISR */

/*
 * TPU4 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU4_TGI4A_ISR
#ifdef	EE_RX200_TPU4_TGI4A_ISR_PRI
  EE_RX200_ICU_IPR_TPU4_TGI4A = EE_RX200_TPU4_TGI4A_ISR_PRI;
#endif	/* EE_RX200_TPU4_TGI4A_ISR_PRI */
  EE_RX200_ICU_IER_TPU4_TGI4A |= EE_RX200_ICU_TPU4_TGI4A_MASK;
#endif	/* EE_RX200_TPU4_TGI4A_ISR */

/*
 * TPU4 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU4_TGI4B_ISR
#ifdef	EE_RX200_TPU4_TGI4B_ISR_PRI
  EE_RX200_ICU_IPR_TPU4_TGI4B = EE_RX200_TPU4_TGI4B_ISR_PRI;
#endif	/* EE_RX200_TPU4_TGI4B_ISR_PRI */
  EE_RX200_ICU_IER_TPU4_TGI4B |= EE_RX200_ICU_TPU4_TGI4B_MASK;
#endif	/* EE_RX200_TPU4_TGI4B_ISR */

/*
 * TPU4 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU4_TCI4V_ISR
#ifdef	EE_RX200_TPU4_TCI4V_ISR_PRI
  EE_RX200_ICU_IPR_TPU4_TCI4V = EE_RX200_TPU4_TCI4V_ISR_PRI;
#endif	/* EE_RX200_TPU4_TCI4V_ISR_PRI */
  EE_RX200_ICU_IER_TPU4_TCI4V |= EE_RX200_ICU_TPU4_TCI4V_MASK;
#endif	/* EE_RX200_TPU4_TCI4V_ISR */

/*
 * TPU4 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU4_TCI4U_ISR
#ifdef	EE_RX200_TPU4_TCI4U_ISR_PRI
  EE_RX200_ICU_IPR_TPU4_TCI4U = EE_RX200_TPU4_TCI4U_ISR_PRI;
#endif	/* EE_RX200_TPU4_TCI4U_ISR_PRI */
  EE_RX200_ICU_IER_TPU4_TCI4U |= EE_RX200_ICU_TPU4_TCI4U_MASK;
#endif	/* EE_RX200_TPU4_TCI4U_ISR */

/*
 * TPU5 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU5_TGI5A_ISR
#ifdef	EE_RX200_TPU5_TGI5A_ISR_PRI
  EE_RX200_ICU_IPR_TPU5_TGI5A = EE_RX200_TPU5_TGI5A_ISR_PRI;
#endif	/* EE_RX200_TPU5_TGI5A_ISR_PRI */
  EE_RX200_ICU_IER_TPU5_TGI5A |= EE_RX200_ICU_TPU5_TGI5A_MASK;
#endif	/* EE_RX200_TPU5_TGI5A_ISR */

/*
 * TPU5 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU5_TGI5B_ISR
#ifdef	EE_RX200_TPU5_TGI5B_ISR_PRI
  EE_RX200_ICU_IPR_TPU5_TGI5B = EE_RX200_TPU5_TGI5B_ISR_PRI;
#endif	/* EE_RX200_TPU5_TGI5B_ISR_PRI */
  EE_RX200_ICU_IER_TPU5_TGI5B |= EE_RX200_ICU_TPU5_TGI5B_MASK;
#endif	/* EE_RX200_TPU5_TGI5B_ISR */

/*
 * TPU5 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU5_TCI5V_ISR
#ifdef	EE_RX200_TPU5_TCI5V_ISR_PRI
  EE_RX200_ICU_IPR_TPU5_TCI5V = EE_RX200_TPU5_TCI5V_ISR_PRI;
#endif	/* EE_RX200_TPU5_TCI5V_ISR_PRI */
  EE_RX200_ICU_IER_TPU5_TCI5V |= EE_RX200_ICU_TPU5_TCI5V_MASK;
#endif	/* EE_RX200_TPU5_TCI5V_ISR */

/*
 * TPU5 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU5_TCI5U_ISR
#ifdef	EE_RX200_TPU5_TCI5U_ISR_PRI
  EE_RX200_ICU_IPR_TPU5_TCI5U = EE_RX200_TPU5_TCI5U_ISR_PRI;
#endif	/* EE_RX200_TPU5_TCI5U_ISR_PRI */
  EE_RX200_ICU_IER_TPU5_TCI5U |= EE_RX200_ICU_TPU5_TCI5U_MASK;
#endif	/* EE_RX200_TPU5_TCI5U_ISR */

/*
 * Port Output 1 interrupt.
 */
#ifdef	EE_RX200_POE_OEI1_ISR
#ifdef	EE_RX200_POE_OEI1_ISR_PRI
  EE_RX200_ICU_IPR_POE_OEI1 = EE_RX200_POE_OEI1_ISR_PRI;
#endif	/* EE_RX200_POE_OEI1_ISR_PRI */
  EE_RX200_ICU_IER_POE_OEI1 |= EE_RX200_ICU_POE_OEI1_MASK;
#endif	/* EE_RX200_POE_OEI1_ISR */

/*
 * Port Output 2 interrupt.
 */
#ifdef	EE_RX200_POE_OEI2_ISR
#ifdef	EE_RX200_POE_OEI2_ISR_PRI
  EE_RX200_ICU_IPR_POE_OEI2 = EE_RX200_POE_OEI2_ISR_PRI;
#endif	/* EE_RX200_POE_OEI2_ISR_PRI */
  EE_RX200_ICU_IER_POE_OEI2 |= EE_RX200_ICU_POE_OEI2_MASK;
#endif	/* EE_RX200_POE_OEI2_ISR */

/*
 * TMR0 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR0_CMIA0_ISR
#ifdef	EE_RX200_TMR0_CMIA0_ISR_PRI
  EE_RX200_ICU_IPR_TMR0_CMIA0 = EE_RX200_TMR0_CMIA0_ISR_PRI;
#endif	/* EE_RX200_TMR0_CMIA0_ISR_PRI */
  EE_RX200_ICU_IER_TMR0_CMIA0 |= EE_RX200_ICU_TMR0_CMIA0_MASK;
#endif	/* EE_RX200_TMR0_CMIA0_ISR */

/*
 * TMR0 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR0_CMIB0_ISR
#ifdef	EE_RX200_TMR0_CMIB0_ISR_PRI
  EE_RX200_ICU_IPR_TMR0_CMIB0 = EE_RX200_TMR0_CMIB0_ISR_PRI;
#endif	/* EE_RX200_TMR0_CMIB0_ISR_PRI */
  EE_RX200_ICU_IER_TMR0_CMIB0 |= EE_RX200_ICU_TMR0_CMIB0_MASK;
#endif	/* EE_RX200_TMR0_CMIB0_ISR */

/*
 * TMR0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR0_OVI0_ISR
#ifdef	EE_RX200_TMR0_OVI0_ISR_PRI
  EE_RX200_ICU_IPR_TMR0_OVI0 = EE_RX200_TMR0_OVI0_ISR_PRI;
#endif	/* EE_RX200_TMR0_OVI0_ISR_PRI */
  EE_RX200_ICU_IER_TMR0_OVI0 |= EE_RX200_ICU_TMR0_OVI0_MASK;
#endif	/* EE_RX200_TMR0_OVI0_ISR */

/*
 * TMR1 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR1_CMIA1_ISR
#ifdef	EE_RX200_TMR1_CMIA1_ISR_PRI
  EE_RX200_ICU_IPR_TMR1_CMIA1 = EE_RX200_TMR1_CMIA1_ISR_PRI;
#endif	/* EE_RX200_TMR1_CMIA1_ISR_PRI */
  EE_RX200_ICU_IER_TMR1_CMIA1 |= EE_RX200_ICU_TMR1_CMIA1_MASK;
#endif	/* EE_RX200_TMR1_CMIA1_ISR */

/*
 * TMR1 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR1_CMIB1_ISR
#ifdef	EE_RX200_TMR1_CMIB1_ISR_PRI
  EE_RX200_ICU_IPR_TMR1_CMIB1 = EE_RX200_TMR1_CMIB1_ISR_PRI;
#endif	/* EE_RX200_TMR1_CMIB1_ISR_PRI */
  EE_RX200_ICU_IER_TMR1_CMIB1 |= EE_RX200_ICU_TMR1_CMIB1_MASK;
#endif	/* EE_RX200_TMR1_CMIB1_ISR */

/*
 * TMR1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR1_OVI1_ISR
#ifdef	EE_RX200_TMR1_OVI1_ISR_PRI
  EE_RX200_ICU_IPR_TMR1_OVI1 = EE_RX200_TMR1_OVI1_ISR_PRI;
#endif	/* EE_RX200_TMR1_OVI1_ISR_PRI */
  EE_RX200_ICU_IER_TMR1_OVI1 |= EE_RX200_ICU_TMR1_OVI1_MASK;
#endif	/* EE_RX200_TMR1_OVI1_ISR */

/*
 * TMR2 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR2_CMIA2_ISR
#ifdef	EE_RX200_TMR2_CMIA2_ISR_PRI
  EE_RX200_ICU_IPR_TMR2_CMIA2 = EE_RX200_TMR2_CMIA2_ISR_PRI;
#endif	/* EE_RX200_TMR2_CMIA2_ISR_PRI */
  EE_RX200_ICU_IER_TMR2_CMIA2 |= EE_RX200_ICU_TMR2_CMIA2_MASK;
#endif	/* EE_RX200_TMR2_CMIA2_ISR */

/*
 * TMR2 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR2_CMIB2_ISR
#ifdef	EE_RX200_TMR2_CMIB2_ISR_PRI
  EE_RX200_ICU_IPR_TMR2_CMIB2 = EE_RX200_TMR2_CMIB2_ISR_PRI;
#endif	/* EE_RX200_TMR2_CMIB2_ISR_PRI */
  EE_RX200_ICU_IER_TMR2_CMIB2 |= EE_RX200_ICU_TMR2_CMIB2_MASK;
#endif	/* EE_RX200_TMR2_CMIB2_ISR */

/*
 * TMR2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR2_OVI2_ISR
#ifdef	EE_RX200_TMR2_OVI2_ISR_PRI
  EE_RX200_ICU_IPR_TMR2_OVI2 = EE_RX200_TMR2_OVI2_ISR_PRI;
#endif	/* EE_RX200_TMR2_OVI2_ISR_PRI */
  EE_RX200_ICU_IER_TMR2_OVI2 |= EE_RX200_ICU_TMR2_OVI2_MASK;
#endif	/* EE_RX200_TMR2_OVI2_ISR */

/*
 * TMR3 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR3_CMIA3_ISR
#ifdef	EE_RX200_TMR3_CMIA3_ISR_PRI
  EE_RX200_ICU_IPR_TMR3_CMIA3 = EE_RX200_TMR3_CMIA3_ISR_PRI;
#endif	/* EE_RX200_TMR3_CMIA3_ISR_PRI */
  EE_RX200_ICU_IER_TMR3_CMIA3 |= EE_RX200_ICU_TMR3_CMIA3_MASK;
#endif	/* EE_RX200_TMR3_CMIA3_ISR */

/*
 * TMR3 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR3_CMIB3_ISR
#ifdef	EE_RX200_TMR3_CMIB3_ISR_PRI
  EE_RX200_ICU_IPR_TMR3_CMIB3 = EE_RX200_TMR3_CMIB3_ISR_PRI;
#endif	/* EE_RX200_TMR3_CMIB3_ISR_PRI */
  EE_RX200_ICU_IER_TMR3_CMIB3 |= EE_RX200_ICU_TMR3_CMIB3_MASK;
#endif	/* EE_RX200_TMR3_CMIB3_ISR */

/*
 * TMR3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR3_OVI3_ISR
#ifdef	EE_RX200_TMR3_OVI3_ISR_PRI
  EE_RX200_ICU_IPR_TMR3_OVI3 = EE_RX200_TMR3_OVI3_ISR_PRI;
#endif	/* EE_RX200_TMR3_OVI3_ISR_PRI */
  EE_RX200_ICU_IER_TMR3_OVI3 |= EE_RX200_ICU_TMR3_OVI3_MASK;
#endif	/* EE_RX200_TMR3_OVI3_ISR */

/*
 * TMR3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR3_OVI3_ISR
#ifdef	EE_RX200_TMR3_OVI3_ISR_PRI
  EE_RX200_ICU_IPR_TMR3_OVI3 = EE_RX200_TMR3_OVI3_ISR_PRI;
#endif	/* EE_RX200_TMR3_OVI3_ISR_PRI */
  EE_RX200_ICU_IER_TMR3_OVI3 |= EE_RX200_ICU_TMR3_OVI3_MASK;
#endif	/* EE_RX200_TMR3_OVI3_ISR */

/*
 * SCI2 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI2_ERI2_ISR
#ifdef	EE_RX200_SCI2_ERI2_ISR_PRI
  EE_RX200_ICU_IPR_SCI2_ERI2 = EE_RX200_SCI2_ERI2_ISR_PRI;
#endif	/* EE_RX200_SCI2_ERI2_ISR_PRI */
  EE_RX200_ICU_IER_SCI2_ERI2 |= EE_RX200_ICU_SCI2_ERI2_MASK;
#endif	/* EE_RX200_SCI2_ERI2_ISR */

/*
 * SCI2 RX interrupt.
 */
#ifdef	EE_RX200_SCI2_RXI2_ISR
#ifdef	EE_RX200_SCI2_RXI2_ISR_PRI
  EE_RX200_ICU_IPR_SCI2_RXI2 = EE_RX200_SCI2_RXI2_ISR_PRI;
#endif	/* EE_RX200_SCI2_RXI2_ISR_PRI */
  EE_RX200_ICU_IER_SCI2_RXI2 |= EE_RX200_ICU_SCI2_RXI2_MASK;
#endif	/* EE_RX200_SCI2_RXI2_ISR */

/*
 * SCI2 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI2_TXI2_ISR
#ifdef	EE_RX200_SCI2_TXI2_ISR_PRI
  EE_RX200_ICU_IPR_SCI2_TXI2 = EE_RX200_SCI2_TXI2_ISR_PRI;
#endif	/* EE_RX200_SCI2_TXI2_ISR_PRI */
  EE_RX200_ICU_IER_SCI2_TXI2 |= EE_RX200_ICU_SCI2_TXI2_MASK;
#endif	/* EE_RX200_SCI2_TXI2_ISR */

/*
 * SCI2 TX End interrupt.
 */
#ifdef	EE_RX200_SCI2_TEI2_ISR
#ifdef	EE_RX200_SCI2_TEI2_ISR_PRI
  EE_RX200_ICU_IPR_SCI2_TEI2 = EE_RX200_SCI2_TEI2_ISR_PRI;
#endif	/* EE_RX200_SCI2_TEI2_ISR_PRI */
  EE_RX200_ICU_IER_SCI2_TEI2 |= EE_RX200_ICU_SCI2_TEI2_MASK;
#endif	/* EE_RX200_SCI2_TEI2_ISR */

/*
 * SCI3 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI3_ERI3_ISR
#ifdef	EE_RX200_SCI3_ERI3_ISR_PRI
  EE_RX200_ICU_IPR_SCI3_ERI3 = EE_RX200_SCI3_ERI3_ISR_PRI;
#endif	/* EE_RX200_SCI3_ERI3_ISR_PRI */
  EE_RX200_ICU_IER_SCI3_ERI3 |= EE_RX200_ICU_SCI3_ERI3_MASK;
#endif	/* EE_RX200_SCI3_ERI3_ISR */

/*
 * SCI3 RX interrupt.
 */
#ifdef	EE_RX200_SCI3_RXI3_ISR
#ifdef	EE_RX200_SCI3_RXI3_ISR_PRI
  EE_RX200_ICU_IPR_SCI3_RXI3 = EE_RX200_SCI3_RXI3_ISR_PRI;
#endif	/* EE_RX200_SCI3_RXI3_ISR_PRI */
  EE_RX200_ICU_IER_SCI3_RXI3 |= EE_RX200_ICU_SCI3_RXI3_MASK;
#endif	/* EE_RX200_SCI3_RXI3_ISR */

/*
 * SCI3 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI3_TXI3_ISR
#ifdef	EE_RX200_SCI3_TXI3_ISR_PRI
  EE_RX200_ICU_IPR_SCI3_TXI3 = EE_RX200_SCI3_TXI3_ISR_PRI;
#endif	/* EE_RX200_SCI3_TXI3_ISR_PRI */
  EE_RX200_ICU_IER_SCI3_TXI3 |= EE_RX200_ICU_SCI3_TXI3_MASK;
#endif	/* EE_RX200_SCI3_TXI3_ISR */

/*
 * SCI3 TX End interrupt.
 */
#ifdef	EE_RX200_SCI3_TEI3_ISR
#ifdef	EE_RX200_SCI3_TEI3_ISR_PRI
  EE_RX200_ICU_IPR_SCI3_TEI3 = EE_RX200_SCI3_TEI3_ISR_PRI;
#endif	/* EE_RX200_SCI3_TEI3_ISR_PRI */
  EE_RX200_ICU_IER_SCI3_TEI3 |= EE_RX200_ICU_SCI3_TEI3_MASK;
#endif	/* EE_RX200_SCI3_TEI3_ISR */

/*
 * SCI4 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI4_ERI4_ISR
#ifdef	EE_RX200_SCI4_ERI4_ISR_PRI
  EE_RX200_ICU_IPR_SCI4_ERI4 = EE_RX200_SCI4_ERI4_ISR_PRI;
#endif	/* EE_RX200_SCI4_ERI4_ISR_PRI */
  EE_RX200_ICU_IER_SCI4_ERI4 |= EE_RX200_ICU_SCI4_ERI4_MASK;
#endif	/* EE_RX200_SCI4_ERI4_ISR */

/*
 * SCI4 RX interrupt.
 */
#ifdef	EE_RX200_SCI4_RXI4_ISR
#ifdef	EE_RX200_SCI4_RXI4_ISR_PRI
  EE_RX200_ICU_IPR_SCI4_RXI4 = EE_RX200_SCI4_RXI4_ISR_PRI;
#endif	/* EE_RX200_SCI4_RXI4_ISR_PRI */
  EE_RX200_ICU_IER_SCI4_RXI4 |= EE_RX200_ICU_SCI4_RXI4_MASK;
#endif	/* EE_RX200_SCI4_RXI4_ISR */

/*
 * SCI4 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI4_TXI4_ISR
#ifdef	EE_RX200_SCI4_TXI4_ISR_PRI
  EE_RX200_ICU_IPR_SCI4_TXI4 = EE_RX200_SCI4_TXI4_ISR_PRI;
#endif	/* EE_RX200_SCI4_TXI4_ISR_PRI */
  EE_RX200_ICU_IER_SCI4_TXI4 |= EE_RX200_ICU_SCI4_TXI4_MASK;
#endif	/* EE_RX200_SCI4_TXI4_ISR */

/*
 * SCI4 TX End interrupt.
 */
#ifdef	EE_RX200_SCI4_TEI4_ISR
#ifdef	EE_RX200_SCI4_TEI4_ISR_PRI
  EE_RX200_ICU_IPR_SCI4_TEI4 = EE_RX200_SCI4_TEI4_ISR_PRI;
#endif	/* EE_RX200_SCI4_TEI4_ISR_PRI */
  EE_RX200_ICU_IER_SCI4_TEI4 |= EE_RX200_ICU_SCI4_TEI4_MASK;
#endif	/* EE_RX200_SCI4_TEI4_ISR */

/*
 * DMAC channel 0 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC0I_ISR
#ifdef	EE_RX200_DMAC_DMAC0I_ISR_PRI
  EE_RX200_ICU_IPR_DMAC_DMAC0I = EE_RX200_DMAC_DMAC0I_ISR_PRI;
#endif	/* EE_RX200_DMAC_DMAC0I_ISR_PRI */
  EE_RX200_ICU_IER_DMAC_DMAC0I |= EE_RX200_ICU_DMAC_DMAC0I_MASK;
#endif	/* EE_RX200_DMAC_DMAC0I_ISR */

/*
 * DMAC channel 1 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC1I_ISR
#ifdef	EE_RX200_DMAC_DMAC1I_ISR_PRI
  EE_RX200_ICU_IPR_DMAC_DMAC1I = EE_RX200_DMAC_DMAC1I_ISR_PRI;
#endif	/* EE_RX200_DMAC_DMAC1I_ISR_PRI */
  EE_RX200_ICU_IER_DMAC_DMAC1I |= EE_RX200_ICU_DMAC_DMAC1I_MASK;
#endif	/* EE_RX200_DMAC_DMAC1I_ISR */

/*
 * DMAC channel 2 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC2I_ISR
#ifdef	EE_RX200_DMAC_DMAC2I_ISR_PRI
  EE_RX200_ICU_IPR_DMAC_DMAC2I = EE_RX200_DMAC_DMAC2I_ISR_PRI;
#endif	/* EE_RX200_DMAC_DMAC2I_ISR_PRI */
  EE_RX200_ICU_IER_DMAC_DMAC2I |= EE_RX200_ICU_DMAC_DMAC2I_MASK;
#endif	/* EE_RX200_DMAC_DMAC2I_ISR */

/*
 * DMAC channel 3 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC3I_ISR
#ifdef	EE_RX200_DMAC_DMAC3I_ISR_PRI
  EE_RX200_ICU_IPR_DMAC_DMAC3I = EE_RX200_DMAC_DMAC3I_ISR_PRI;
#endif	/* EE_RX200_DMAC_DMAC3I_ISR_PRI */
  EE_RX200_ICU_IER_DMAC_DMAC3I |= EE_RX200_ICU_DMAC_DMAC3I_MASK;
#endif	/* EE_RX200_DMAC_DMAC3I_ISR */

/*
 * SCI7 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI7_ERI7_ISR
#ifdef	EE_RX200_SCI7_ERI7_ISR_PRI
  EE_RX200_ICU_IPR_SCI7_ERI7 = EE_RX200_SCI7_ERI7_ISR_PRI;
#endif	/* EE_RX200_SCI7_ERI7_ISR_PRI */
  EE_RX200_ICU_IER_SCI7_ERI7 |= EE_RX200_ICU_SCI7_ERI7_MASK;
#endif	/* EE_RX200_SCI7_ERI7_ISR */

/*
 * SCI7 RX interrupt.
 */
#ifdef	EE_RX200_SCI7_RXI7_ISR
#ifdef	EE_RX200_SCI7_RXI7_ISR_PRI
  EE_RX200_ICU_IPR_SCI7_RXI7 = EE_RX200_SCI7_RXI7_ISR_PRI;
#endif	/* EE_RX200_SCI7_RXI7_ISR_PRI */
  EE_RX200_ICU_IER_SCI7_RXI7 |= EE_RX200_ICU_SCI7_RXI7_MASK;
#endif	/* EE_RX200_SCI7_RXI7_ISR */

/*
 * SCI7 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI7_TXI7_ISR
#ifdef	EE_RX200_SCI7_TXI7_ISR_PRI
  EE_RX200_ICU_IPR_SCI7_TXI7 = EE_RX200_SCI7_TXI7_ISR_PRI;
#endif	/* EE_RX200_SCI7_TXI7_ISR_PRI */
  EE_RX200_ICU_IER_SCI7_TXI7 |= EE_RX200_ICU_SCI7_TXI7_MASK;
#endif	/* EE_RX200_SCI7_TXI7_ISR */

/*
 * SCI7 TX End interrupt.
 */
#ifdef	EE_RX200_SCI7_TEI7_ISR
#ifdef	EE_RX200_SCI7_TEI7_ISR_PRI
  EE_RX200_ICU_IPR_SCI7_TEI7 = EE_RX200_SCI7_TEI7_ISR_PRI;
#endif	/* EE_RX200_SCI7_TEI7_ISR_PRI */
  EE_RX200_ICU_IER_SCI7_TEI7 |= EE_RX200_ICU_SCI7_TEI7_MASK;
#endif	/* EE_RX200_SCI7_TEI7_ISR */

/*
 * SCI10 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI10_ERI10_ISR
#ifdef	EE_RX200_SCI10_ERI10_ISR_PRI
  EE_RX200_ICU_IPR_SCI10_ERI10 = EE_RX200_SCI10_ERI10_ISR_PRI;
#endif	/* EE_RX200_SCI10_ERI10_ISR_PRI */
  EE_RX200_ICU_IER_SCI10_ERI10 |= EE_RX200_ICU_SCI10_ERI10_MASK;
#endif	/* EE_RX200_SCI10_ERI10_ISR */

/*
 * SCI10 RX interrupt.
 */
#ifdef	EE_RX200_SCI10_RXI10_ISR
#ifdef	EE_RX200_SCI10_RXI10_ISR_PRI
  EE_RX200_ICU_IPR_SCI10_RXI10 = EE_RX200_SCI10_RXI10_ISR_PRI;
#endif	/* EE_RX200_SCI10_RXI10_ISR_PRI */
  EE_RX200_ICU_IER_SCI10_RXI10 |= EE_RX200_ICU_SCI10_RXI10_MASK;
#endif	/* EE_RX200_SCI10_RXI10_ISR */

/*
 * SCI10 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI10_TXI10_ISR
#ifdef	EE_RX200_SCI10_TXI10_ISR_PRI
  EE_RX200_ICU_IPR_SCI10_TXI10 = EE_RX200_SCI10_TXI10_ISR_PRI;
#endif	/* EE_RX200_SCI10_TXI10_ISR_PRI */
  EE_RX200_ICU_IER_SCI10_TXI10 |= EE_RX200_ICU_SCI10_TXI10_MASK;
#endif	/* EE_RX200_SCI10_TXI10_ISR */

/*
 * SCI10 TX End interrupt.
 */
#ifdef	EE_RX200_SCI10_TEI10_ISR
#ifdef	EE_RX200_SCI10_TEI10_ISR_PRI
  EE_RX200_ICU_IPR_SCI10_TEI10 = EE_RX200_SCI10_TEI10_ISR_PRI;
#endif	/* EE_RX200_SCI10_TEI10_ISR_PRI */
  EE_RX200_ICU_IER_SCI10_TEI10 |= EE_RX200_ICU_SCI10_TEI10_MASK;
#endif	/* EE_RX200_SCI10_TEI10_ISR */

/*
 * SCI0 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI0_ERI0_ISR
#ifdef	EE_RX200_SCI0_ERI0_ISR_PRI
  EE_RX200_ICU_IPR_SCI0_ERI0 = EE_RX200_SCI0_ERI0_ISR_PRI;
#endif	/* EE_RX200_SCI0_ERI0_ISR_PRI */
  EE_RX200_ICU_IER_SCI0_ERI0 |= EE_RX200_ICU_SCI0_ERI0_MASK;
#endif	/* EE_RX200_SCI0_ERI0_ISR */

/*
 * SCI0 RX interrupt.
 */
#ifdef	EE_RX200_SCI0_RXI0_ISR
#ifdef	EE_RX200_SCI0_RXI0_ISR_PRI
  EE_RX200_ICU_IPR_SCI0_RXI0 = EE_RX200_SCI0_RXI0_ISR_PRI;
#endif	/* EE_RX200_SCI0_RXI0_ISR_PRI */
  EE_RX200_ICU_IER_SCI0_RXI0 |= EE_RX200_ICU_SCI0_RXI0_MASK;
#endif	/* EE_RX200_SCI0_RXI0_ISR */

/*
 * SCI0 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI0_TXI0_ISR
#ifdef	EE_RX200_SCI0_TXI0_ISR_PRI
  EE_RX200_ICU_IPR_SCI0_TXI0 = EE_RX200_SCI0_TXI0_ISR_PRI;
#endif	/* EE_RX200_SCI0_TXI0_ISR_PRI */
  EE_RX200_ICU_IER_SCI0_TXI0 |= EE_RX200_ICU_SCI0_TXI0_MASK;
#endif	/* EE_RX200_SCI0_TXI0_ISR */

/*
 * SCI0 TX End interrupt.
 */
#ifdef	EE_RX200_SCI0_TEI0_ISR
#ifdef	EE_RX200_SCI0_TEI0_ISR_PRI
  EE_RX200_ICU_IPR_SCI0_TEI0 = EE_RX200_SCI0_TEI0_ISR_PRI;
#endif	/* EE_RX200_SCI0_TEI0_ISR_PRI */
  EE_RX200_ICU_IER_SCI0_TEI0 |= EE_RX200_ICU_SCI0_TEI0_MASK;
#endif	/* EE_RX200_SCI0_TEI0_ISR */

/*
 * SCI1 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI1_ERI1_ISR
#ifdef	EE_RX200_SCI1_ERI1_ISR_PRI
  EE_RX200_ICU_IPR_SCI1_ERI1 = EE_RX200_SCI1_ERI1_ISR_PRI;
#endif	/* EE_RX200_SCI1_ERI1_ISR_PRI */
  EE_RX200_ICU_IER_SCI1_ERI1 |= EE_RX200_ICU_SCI1_ERI1_MASK;
#endif	/* EE_RX200_SCI1_ERI1_ISR */

/*
 * SCI1 RX interrupt.
 */
#ifdef	EE_RX200_SCI1_RXI1_ISR
#ifdef	EE_RX200_SCI1_RXI1_ISR_PRI
  EE_RX200_ICU_IPR_SCI1_RXI1 = EE_RX200_SCI1_RXI1_ISR_PRI;
#endif	/* EE_RX200_SCI1_RXI1_ISR_PRI */
  EE_RX200_ICU_IER_SCI1_RXI1 |= EE_RX200_ICU_SCI1_RXI1_MASK;
#endif	/* EE_RX200_SCI1_RXI1_ISR */

/*
 * SCI1 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI1_TXI1_ISR
#ifdef	EE_RX200_SCI1_TXI1_ISR_PRI
  EE_RX200_ICU_IPR_SCI1_TXI1 = EE_RX200_SCI1_TXI1_ISR_PRI;
#endif	/* EE_RX200_SCI1_TXI1_ISR_PRI */
  EE_RX200_ICU_IER_SCI1_TXI1 |= EE_RX200_ICU_SCI1_TXI1_MASK;
#endif	/* EE_RX200_SCI1_TXI1_ISR */

/*
 * SCI1 TX End interrupt.
 */
#ifdef	EE_RX200_SCI1_TEI1_ISR
#ifdef	EE_RX200_SCI1_TEI1_ISR_PRI
  EE_RX200_ICU_IPR_SCI1_TEI1 = EE_RX200_SCI1_TEI1_ISR_PRI;
#endif	/* EE_RX200_SCI1_TEI1_ISR_PRI */
  EE_RX200_ICU_IER_SCI1_TEI1 |= EE_RX200_ICU_SCI1_TEI1_MASK;
#endif	/* EE_RX200_SCI1_TEI1_ISR */

/*
 * SCI5 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI5_ERI5_ISR
#ifdef	EE_RX200_SCI5_ERI5_ISR_PRI
  EE_RX200_ICU_IPR_SCI5_ERI5 = EE_RX200_SCI5_ERI5_ISR_PRI;
#endif	/* EE_RX200_SCI5_ERI5_ISR_PRI */
  EE_RX200_ICU_IER_SCI5_ERI5 |= EE_RX200_ICU_SCI5_ERI5_MASK;
#endif	/* EE_RX200_SCI5_ERI5_ISR */

/*
 * SCI5 RX interrupt.
 */
#ifdef	EE_RX200_SCI5_RXI5_ISR
#ifdef	EE_RX200_SCI5_RXI5_ISR_PRI
  EE_RX200_ICU_IPR_SCI5_RXI5 = EE_RX200_SCI5_RXI5_ISR_PRI;
#endif	/* EE_RX200_SCI5_RXI5_ISR_PRI */
  EE_RX200_ICU_IER_SCI5_RXI5 |= EE_RX200_ICU_SCI5_RXI5_MASK;
#endif	/* EE_RX200_SCI5_RXI5_ISR */

/*
 * SCI5 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI5_TXI5_ISR
#ifdef	EE_RX200_SCI5_TXI5_ISR_PRI
  EE_RX200_ICU_IPR_SCI5_TXI5 = EE_RX200_SCI5_TXI5_ISR_PRI;
#endif	/* EE_RX200_SCI5_TXI5_ISR_PRI */
  EE_RX200_ICU_IER_SCI5_TXI5 |= EE_RX200_ICU_SCI5_TXI5_MASK;
#endif	/* EE_RX200_SCI5_TXI5_ISR */

/*
 * SCI5 TX End interrupt.
 */
#ifdef	EE_RX200_SCI5_TEI5_ISR
#ifdef	EE_RX200_SCI5_TEI5_ISR_PRI
  EE_RX200_ICU_IPR_SCI5_TEI5 = EE_RX200_SCI5_TEI5_ISR_PRI;
#endif	/* EE_RX200_SCI5_TEI5_ISR_PRI */
  EE_RX200_ICU_IER_SCI5_TEI5 |= EE_RX200_ICU_SCI5_TEI5_MASK;
#endif	/* EE_RX200_SCI5_TEI5_ISR */

/*
 * SCI6 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI6_ERI6_ISR
#ifdef	EE_RX200_SCI6_ERI6_ISR_PRI
  EE_RX200_ICU_IPR_SCI6_ERI6 = EE_RX200_SCI6_ERI6_ISR_PRI;
#endif	/* EE_RX200_SCI6_ERI6_ISR_PRI */
  EE_RX200_ICU_IER_SCI6_ERI6 |= EE_RX200_ICU_SCI6_ERI6_MASK;
#endif	/* EE_RX200_SCI6_ERI6_ISR */

/*
 * SCI6 RX interrupt.
 */
#ifdef	EE_RX200_SCI6_RXI6_ISR
#ifdef	EE_RX200_SCI6_RXI6_ISR_PRI
  EE_RX200_ICU_IPR_SCI6_RXI6 = EE_RX200_SCI6_RXI6_ISR_PRI;
#endif	/* EE_RX200_SCI6_RXI6_ISR_PRI */
  EE_RX200_ICU_IER_SCI6_RXI6 |= EE_RX200_ICU_SCI6_RXI6_MASK;
#endif	/* EE_RX200_SCI6_RXI6_ISR */

/*
 * SCI6 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI6_TXI6_ISR
#ifdef	EE_RX200_SCI6_TXI6_ISR_PRI
  EE_RX200_ICU_IPR_SCI6_TXI6 = EE_RX200_SCI6_TXI6_ISR_PRI;
#endif	/* EE_RX200_SCI6_TXI6_ISR_PRI */
  EE_RX200_ICU_IER_SCI6_TXI6 |= EE_RX200_ICU_SCI6_TXI6_MASK;
#endif	/* EE_RX200_SCI6_TXI6_ISR */

/*
 * SCI6 TX End interrupt.
 */
#ifdef	EE_RX200_SCI6_TEI6_ISR
#ifdef	EE_RX200_SCI6_TEI6_ISR_PRI
  EE_RX200_ICU_IPR_SCI6_TEI6 = EE_RX200_SCI6_TEI6_ISR_PRI;
#endif	/* EE_RX200_SCI6_TEI6_ISR_PRI */
  EE_RX200_ICU_IER_SCI6_TEI6 |= EE_RX200_ICU_SCI6_TEI6_MASK;
#endif	/* EE_RX200_SCI6_TEI6_ISR */

/*
 * SCI8 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI8_ERI8_ISR
#ifdef	EE_RX200_SCI8_ERI8_ISR_PRI
  EE_RX200_ICU_IPR_SCI8_ERI8 = EE_RX200_SCI8_ERI8_ISR_PRI;
#endif	/* EE_RX200_SCI8_ERI8_ISR_PRI */
  EE_RX200_ICU_IER_SCI8_ERI8 |= EE_RX200_ICU_SCI8_ERI8_MASK;
#endif	/* EE_RX200_SCI8_ERI8_ISR */

/*
 * SCI8 RX interrupt.
 */
#ifdef	EE_RX200_SCI8_RXI8_ISR
#ifdef	EE_RX200_SCI8_RXI8_ISR_PRI
  EE_RX200_ICU_IPR_SCI8_RXI8 = EE_RX200_SCI8_RXI8_ISR_PRI;
#endif	/* EE_RX200_SCI8_RXI8_ISR_PRI */
  EE_RX200_ICU_IER_SCI8_RXI8 |= EE_RX200_ICU_SCI8_RXI8_MASK;
#endif	/* EE_RX200_SCI8_RXI8_ISR */

/*
 * SCI8 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI8_TXI8_ISR
#ifdef	EE_RX200_SCI8_TXI8_ISR_PRI
  EE_RX200_ICU_IPR_SCI8_TXI8 = EE_RX200_SCI8_TXI8_ISR_PRI;
#endif	/* EE_RX200_SCI8_TXI8_ISR_PRI */
  EE_RX200_ICU_IER_SCI8_TXI8 |= EE_RX200_ICU_SCI8_TXI8_MASK;
#endif	/* EE_RX200_SCI8_TXI8_ISR */

/*
 * SCI8 TX End interrupt.
 */
#ifdef	EE_RX200_SCI8_TEI8_ISR
#ifdef	EE_RX200_SCI8_TEI8_ISR_PRI
  EE_RX200_ICU_IPR_SCI8_TEI8 = EE_RX200_SCI8_TEI8_ISR_PRI;
#endif	/* EE_RX200_SCI8_TEI8_ISR_PRI */
  EE_RX200_ICU_IER_SCI8_TEI8 |= EE_RX200_ICU_SCI8_TEI8_MASK;
#endif	/* EE_RX200_SCI8_TEI8_ISR */

/*
 * SCI9 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI9_ERI9_ISR
#ifdef	EE_RX200_SCI9_ERI9_ISR_PRI
  EE_RX200_ICU_IPR_SCI9_ERI9 = EE_RX200_SCI9_ERI9_ISR_PRI;
#endif	/* EE_RX200_SCI9_ERI9_ISR_PRI */
  EE_RX200_ICU_IER_SCI9_ERI9 |= EE_RX200_ICU_SCI9_ERI9_MASK;
#endif	/* EE_RX200_SCI9_ERI9_ISR */

/*
 * SCI9 RX interrupt.
 */
#ifdef	EE_RX200_SCI9_RXI9_ISR
#ifdef	EE_RX200_SCI9_RXI9_ISR_PRI
  EE_RX200_ICU_IPR_SCI9_RXI9 = EE_RX200_SCI9_RXI9_ISR_PRI;
#endif	/* EE_RX200_SCI9_RXI9_ISR_PRI */
  EE_RX200_ICU_IER_SCI9_RXI9 |= EE_RX200_ICU_SCI9_RXI9_MASK;
#endif	/* EE_RX200_SCI9_RXI9_ISR */

/*
 * SCI9 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI9_TXI9_ISR
#ifdef	EE_RX200_SCI9_TXI9_ISR_PRI
  EE_RX200_ICU_IPR_SCI9_TXI9 = EE_RX200_SCI9_TXI9_ISR_PRI;
#endif	/* EE_RX200_SCI9_TXI9_ISR_PRI */
  EE_RX200_ICU_IER_SCI9_TXI9 |= EE_RX200_ICU_SCI9_TXI9_MASK;
#endif	/* EE_RX200_SCI9_TXI9_ISR */

/*
 * SCI9 TX End interrupt.
 */
#ifdef	EE_RX200_SCI9_TEI9_ISR
#ifdef	EE_RX200_SCI9_TEI9_ISR_PRI
  EE_RX200_ICU_IPR_SCI9_TEI9 = EE_RX200_SCI9_TEI9_ISR_PRI;
#endif	/* EE_RX200_SCI9_TEI9_ISR_PRI */
  EE_RX200_ICU_IER_SCI9_TEI9 |= EE_RX200_ICU_SCI9_TEI9_MASK;
#endif	/* EE_RX200_SCI9_TEI9_ISR */

/*
 * SCI12 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI12_ERI12_ISR
#ifdef	EE_RX200_SCI12_ERI12_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_ERI12 = EE_RX200_SCI12_ERI12_ISR_PRI;
#endif	/* EE_RX200_SCI12_ERI12_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_ERI12 |= EE_RX200_ICU_SCI12_ERI12_MASK;
#endif	/* EE_RX200_SCI12_ERI12_ISR */

/*
 * SCI12 RX interrupt.
 */
#ifdef	EE_RX200_SCI12_RXI12_ISR
#ifdef	EE_RX200_SCI12_RXI12_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_RXI12 = EE_RX200_SCI12_RXI12_ISR_PRI;
#endif	/* EE_RX200_SCI12_RXI12_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_RXI12 |= EE_RX200_ICU_SCI12_RXI12_MASK;
#endif	/* EE_RX200_SCI12_RXI12_ISR */

/*
 * SCI12 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI12_TXI12_ISR
#ifdef	EE_RX200_SCI12_TXI12_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_TXI12 = EE_RX200_SCI12_TXI12_ISR_PRI;
#endif	/* EE_RX200_SCI12_TXI12_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_TXI12 |= EE_RX200_ICU_SCI12_TXI12_MASK;
#endif	/* EE_RX200_SCI12_TXI12_ISR */

/*
 * SCI12 TX End interrupt.
 */
#ifdef	EE_RX200_SCI12_TEI12_ISR
#ifdef	EE_RX200_SCI12_TEI12_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_TEI12 = EE_RX200_SCI12_TEI12_ISR_PRI;
#endif	/* EE_RX200_SCI12_TEI12_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_TEI12 |= EE_RX200_ICU_SCI12_TEI12_MASK;
#endif	/* EE_RX200_SCI12_TEI12_ISR */

/*
 * SCI12 Extended Serial Mode Control 0 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX0_ISR
#ifdef	EE_RX200_SCI12_SCIX0_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_SCIX0 = EE_RX200_SCI12_SCIX0_ISR_PRI;
#endif	/* EE_RX200_SCI12_SCIX0_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_SCIX0 |= EE_RX200_ICU_SCI12_SCIX0_MASK;
#endif	/* EE_RX200_SCI12_SCIX0_ISR */

/*
 * SCI12 Extended Serial Mode Control 1 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX1_ISR
#ifdef	EE_RX200_SCI12_SCIX1_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_SCIX1 = EE_RX200_SCI12_SCIX1_ISR_PRI;
#endif	/* EE_RX200_SCI12_SCIX1_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_SCIX1 |= EE_RX200_ICU_SCI12_SCIX1_MASK;
#endif	/* EE_RX200_SCI12_SCIX1_ISR */

/*
 * SCI12 Extended Serial Mode Control 2 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX2_ISR
#ifdef	EE_RX200_SCI12_SCIX2_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_SCIX2 = EE_RX200_SCI12_SCIX2_ISR_PRI;
#endif	/* EE_RX200_SCI12_SCIX2_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_SCIX2 |= EE_RX200_ICU_SCI12_SCIX2_MASK;
#endif	/* EE_RX200_SCI12_SCIX2_ISR */

/*
 * SCI12 Extended Serial Mode Control 3 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX3_ISR
#ifdef	EE_RX200_SCI12_SCIX3_ISR_PRI
  EE_RX200_ICU_IPR_SCI12_SCIX3 = EE_RX200_SCI12_SCIX3_ISR_PRI;
#endif	/* EE_RX200_SCI12_SCIX3_ISR_PRI */
  EE_RX200_ICU_IER_SCI12_SCIX3 |= EE_RX200_ICU_SCI12_SCIX3_MASK;
#endif	/* EE_RX200_SCI12_SCIX3_ISR */

/*
 * RIIC0 Event/Error interrupt.
 */
#ifdef	EE_RX200_RIIC0_EEI0_ISR
#ifdef	EE_RX200_RIIC0_EEI0_ISR_PRI
  EE_RX200_ICU_IPR_RIIC0_EEI0 = EE_RX200_RIIC0_EEI0_ISR_PRI;
#endif	/* EE_RX200_RIIC0_EEI0_ISR_PRI */
  EE_RX200_ICU_IER_RIIC0_EEI0 |= EE_RX200_ICU_RIIC0_EEI0_MASK;
#endif	/* EE_RX200_RIIC0_EEI0_ISR */

/*
 * RIIC0 Receive Data Full interrupt.
 */
#ifdef	EE_RX200_RIIC0_RXI0_ISR
#ifdef	EE_RX200_RIIC0_RXI0_ISR_PRI
  EE_RX200_ICU_IPR_RIIC0_RXI0 = EE_RX200_RIIC0_RXI0_ISR_PRI;
#endif	/* EE_RX200_RIIC0_RXI0_ISR_PRI */
  EE_RX200_ICU_IER_RIIC0_RXI0 |= EE_RX200_ICU_RIIC0_RXI0_MASK;
#endif	/* EE_RX200_RIIC0_RXI0_ISR */

/*
 * RIIC0 TX End interrupt.
 */
#ifdef	EE_RX200_RIIC0_TXI0_ISR
#ifdef	EE_RX200_RIIC0_TXI0_ISR_PRI
  EE_RX200_ICU_IPR_RIIC0_TXI0 = EE_RX200_RIIC0_TXI0_ISR_PRI;
#endif	/* EE_RX200_RIIC0_TXI0_ISR_PRI */
  EE_RX200_ICU_IER_RIIC0_TXI0 |= EE_RX200_ICU_RIIC0_TXI0_MASK;
#endif	/* EE_RX200_RIIC0_TXI0_ISR */

/*
 * RIIC0 TX Data Empty interrupt.
 */
#ifdef	EE_RX200_RIIC0_TEI0_ISR
#ifdef	EE_RX200_RIIC0_TEI0_ISR_PRI
  EE_RX200_ICU_IPR_RIIC0_TEI0 = EE_RX200_RIIC0_TEI0_ISR_PRI;
#endif	/* EE_RX200_RIIC0_TEI0_ISR_PRI */
  EE_RX200_ICU_IER_RIIC0_TEI0 |= EE_RX200_ICU_RIIC0_TEI0_MASK;
#endif	/* EE_RX200_RIIC0_TEI0_ISR */


/*
 * SCI11 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI11_ERI11_ISR
#ifdef	EE_RX200_SCI11_ERI11_ISR_PRI
  EE_RX200_ICU_IPR_SCI11_ERI11 = EE_RX200_SCI11_ERI11_ISR_PRI;
#endif	/* EE_RX200_SCI11_ERI11_ISR_PRI */
  EE_RX200_ICU_IER_SCI11_ERI11 |= EE_RX200_ICU_SCI11_ERI11_MASK;
#endif	/* EE_RX200_SCI11_ERI11_ISR */

/*
 * SCI11 RX interrupt.
 */
#ifdef	EE_RX200_SCI11_RXI11_ISR
#ifdef	EE_RX200_SCI11_RXI11_ISR_PRI
  EE_RX200_ICU_IPR_SCI11_RXI11 = EE_RX200_SCI11_RXI11_ISR_PRI;
#endif	/* EE_RX200_SCI11_RXI11_ISR_PRI */
  EE_RX200_ICU_IER_SCI11_RXI11 |= EE_RX200_ICU_SCI11_RXI11_MASK;
#endif	/* EE_RX200_SCI11_RXI11_ISR */

/*
 * SCI11 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI11_TXI11_ISR
#ifdef	EE_RX200_SCI11_TXI11_ISR_PRI
  EE_RX200_ICU_IPR_SCI11_TXI11 = EE_RX200_SCI11_TXI11_ISR_PRI;
#endif	/* EE_RX200_SCI11_TXI11_ISR_PRI */
  EE_RX200_ICU_IER_SCI11_TXI11 |= EE_RX200_ICU_SCI11_TXI11_MASK;
#endif	/* EE_RX200_SCI11_TXI11_ISR */

/*
 * SCI11 TX End interrupt.
 */
#ifdef	EE_RX200_SCI11_TEI11_ISR
#ifdef	EE_RX200_SCI11_TEI11_ISR_PRI
  EE_RX200_ICU_IPR_SCI11_TEI11 = EE_RX200_SCI11_TEI11_ISR_PRI;
#endif	/* EE_RX200_SCI11_TEI11_ISR_PRI */
  EE_RX200_ICU_IER_SCI11_TEI11 |= EE_RX200_ICU_SCI11_TEI11_MASK;
#endif	/* EE_RX200_SCI11_TEI11_ISR */

}	/* EE_rx210_init_isr_prios() */

/*
 * Allocate EE_rx200_vtable into Relocatable Vector Table section.
 */ 
 

void* const EE_rx200_vtable[] =
{
	EE_rx200_default_ISR,			/* Reserved - brk()/BRK */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_BUSERR_ISR
	EE_RX200_BUSERR_ISR,
#else
/*
 * Bus-error interrupt.
 */
#ifdef	EE_RX200_BSC_BUSERR_ISR
	(void *) EE_RX200_BSC_BUSERR_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_BSC_BUSERR_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_FIFERR_ISR
	(void *) EE_RX200_FIFERR_ISR,
#else
/*
 * Flash interface error interrupt.
 */
#ifdef	EE_RX200_FCU_FIFERR_ISR
	(void *) EE_RX200_FCU_FIFERR_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_FCU_FIFERR_ISR */
#endif
	0,					/* Reserved */
#ifdef EE_RX200_FRDYI_ISR
	(void *) EE_RX200_FRDYI_ISR,	//The FLASH READY handler
#else
/*
 * Flash READY interrupt.
 */
#ifdef	EE_RX200_FCU_FRDYI_ISR
	(void *) EE_RX200_FCU_FRDYI_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_FCU_FRDYI_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_SWINT_ISR
	(void *) EE_RX200_SWINT_ISR, //The Software Interr. handler
#else
/*
 * Software interrupt.
 */
#ifdef	EE_RX200_ICU_SWINT_ISR
	(void *) EE_RX200_ICU_SWINT_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_SWINT_ISR */
#endif	
#ifdef EE_RX200_CMI0_ISR
	(void *) EE_RX200_CMI0_ISR, //The Compare Match 0 handler
#else
/*
 * Compare Match 0 interrupt.
 */
#ifdef	EE_RX200_CMT0_CMI0_ISR
	(void *) EE_RX200_CMT0_CMI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CMT0_CMI0_ISR */
#endif
#ifdef EE_RX200_CMI1_ISR
	(void *) EE_RX200_CMI1_ISR, //The Compare Match 1 handler
#else
/*
 * Compare Match 1 interrupt.
 */
#ifdef	EE_RX200_CMT1_CMI1_ISR
	(void *) EE_RX200_CMT1_CMI1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CMT1_CMI1_ISR */
#endif
#ifdef EE_RX200_CMI2_ISR
	(void *) EE_RX200_CMI2_ISR, //The Compare Match 2 handler
#else
/*
 * Compare Match 2 interrupt.
 */
#ifdef	EE_RX200_CMT2_CMI2_ISR
	(void *) EE_RX200_CMT2_CMI2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CMT2_CMI2_ISR */
#endif
#ifdef EE_RX200_CMI3_ISR
	(void *) EE_RX200_CMI3_ISR, //The Compare Match 3 handler
#else
/*
 * Compare Match 3 interrupt.
 */
#ifdef	EE_RX200_CMT3_CMI3_ISR
	(void *) EE_RX200_CMT3_CMI3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CMT3_CMI3_ISR */
#endif
#ifdef EE_RX200_FERRF_ISR
	(void *) EE_RX200_FERRF_ISR, //The Freq. Err. Interr. handler
#else
/*
 * Frequency Error interrupt.
 */
#ifdef	EE_RX200_CAC_FERRF_ISR
	(void *) EE_RX200_CAC_FERRF_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CAC_FERRF_ISR */
#endif
#ifdef EE_RX200_MENDF_ISR
	(void *) EE_RX200_MENDF_ISR, //The Measur. End Interr. handler
#else
/*
 * Measurement End interrupt.
 */
#ifdef	EE_RX200_CAC_MENDF_ISR
	(void *) EE_RX200_CAC_MENDF_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CAC_MENDF_ISR */
#endif
#ifdef EE_RX200_OVFF_ISR
	(void *) EE_RX200_OVFF_ISR, //The Overflow Interr. handler
#else
/*
 * Overflow interrupt.
 */
#ifdef	EE_RX200_CAC_OVFF_ISR
	(void *) EE_RX200_CAC_OVFF_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CAC_OVFF_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_SPEI0_ISR
	(void *) EE_RX200_SPEI0_ISR, //The SCI Error handler
#else
/*
 * RSPI Errors interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPEI0_ISR
	(void *) EE_RX200_RSPI0_SPEI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RSPI0_SPEI0_ISR */

#endif	
#ifdef EE_RX200_SPRIO_ISR
	(void *) EE_RX200_SPRIO_ISR, //The  SCI RX Interr. handler
#else
/*
 * Receive Buffer Full interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPRI0_ISR
	(void *) EE_RX200_RSPI0_SPRI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RSPI0_SPRI0_ISR */

#endif
#ifdef EE_RX200_SPTIO_ISR
	(void *) EE_RX200_SPTIO_ISR, //The  SCI RX Interr. handler
#else
/*
 * Transmit Buffer Full interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPTI0_ISR
	(void *) EE_RX200_RSPI0_SPTI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RSPI0_SPTI0_ISR */
#endif
#ifdef EE_RX200_SPIIO_ISR
	(void *) EE_RX200_SPIIO_ISR, //The SCI IO Interr. handler
#else
/*
 * RSPI Idle interrupt.
 */
#ifdef	EE_RX200_RSPI0_SPII0_ISR
	(void *) EE_RX200_RSPI0_SPII0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RSPI0_SPII0_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_DOPCF_ISR
	(void *) EE_RX200_DOPCF_ISR, //The Data oper. circuit Interr. handler
#else
/*
 * Data Operation Circuit interrupt.
 */
#ifdef	EE_RX200_DOC_DOPCF_ISR
	(void *) EE_RX200_DOC_DOPCF_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_DOC_DOPCF_ISR */
#endif
#ifdef EE_RX200_COMPB0_ISR
	(void *) EE_RX200_COMPB0_ISR,	//The Comparator B0 Interr. handler
#else
/*
 * Comparator B0 interrupt.
 */
#ifdef	EE_RX200_CMPB_CMPB0_ISR
	(void *) EE_RX200_CMPB_CMPB0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CMPB_CMPB0_ISR */
#endif
#ifdef EE_RX200_COMPB1_ISR
	(void *) EE_RX200_COMPB1_ISR,	//The Comparator B1 Interr. handler
#else
/*
 * Comparator B1 interrupt.
 */
#ifdef	EE_RX200_CMPB_CMPB1_ISR
	(void *) EE_RX200_CMPB_CMPB1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_CMPB_CMPB1_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_COUNTUP_ISR
	(void *) EE_RX200_COUNTUP_ISR,	//The RTC Countup Interr. handler
#else
/*
 * RTC Count Up interrupt.
 */
#ifdef	EE_RX200_RTC_CUP_ISR
	(void *) EE_RX200_RTC_CUP_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RTC_CUP_ISR */
#endif
#ifdef EE_RX200_IRQ0_ISR
	(void *) EE_RX200_IRQ0_ISR,	//The IRQ0 Interr. handler
#else
/*
 * IRQ0 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ0_ISR
	(void *) EE_RX200_ICU_IRQ0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ0_ISR */
#endif
#ifdef EE_RX200_IRQ1_ISR
	(void *) EE_RX200_IRQ1_ISR,	//The IRQ1 Interr. handler
#else
/*
 * IRQ1 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ1_ISR
	(void *) EE_RX200_ICU_IRQ1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ1_ISR */
#endif
#ifdef EE_RX200_IRQ2_ISR
	(void *) EE_RX200_IRQ2_ISR,	//The IRQ2 Interr. handler
#else
/*
 * IRQ2 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ2_ISR
	(void *) EE_RX200_ICU_IRQ2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ2_ISR */
#endif
#ifdef EE_RX200_IRQ3_ISR
	(void *) EE_RX200_IRQ3_ISR,	//The IRQ3 Interr. handler
#else
/*
 * IRQ3 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ3_ISR
	(void *) EE_RX200_ICU_IRQ3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ3_ISR */
#endif
#ifdef EE_RX200_IRQ4_ISR
	(void *) EE_RX200_IRQ4_ISR,	//The IRQ4 Interr. handler
#else
/*
 * IRQ4 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ4_ISR
	(void *) EE_RX200_ICU_IRQ4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ4_ISR */
#endif
#ifdef EE_RX200_IRQ5_ISR
	(void *) EE_RX200_IRQ5_ISR,	//The IRQ5 Interr. handler
#else
/*
 * IRQ5 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ5_ISR
	(void *) EE_RX200_ICU_IRQ5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ5_ISR */
#endif
#ifdef EE_RX200_IRQ6_ISR
	(void *) EE_RX200_IRQ6_ISR,	//The IRQ6 Interr. handler
#else
/*
 * IRQ6 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ6_ISR
	(void *) EE_RX200_ICU_IRQ6_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ6_ISR */
#endif
#ifdef EE_RX200_IRQ7_ISR
	(void *) EE_RX200_IRQ7_ISR,	//The IRQ7 Interr. handler
#else
/*
 * IRQ7 interrupt.
 */
#ifdef	EE_RX200_ICU_IRQ7_ISR
	(void *) EE_RX200_ICU_IRQ7_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ICU_IRQ7_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_LVDI1_COMP1_ISR
	(void *) EE_RX200_LVDI1_COMP1_ISR,	//The LVD1/COMPA1. Interr. handler
#else
/*
 * LVD1/CMPA1 interrupt.
 */
#ifdef	EE_RX200_LVD1_CMPA1_ISR
	(void *) EE_RX200_LVD1_CMPA1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_LVD1_CMPA1_ISR */
#endif
#ifdef EE_RX200_LVDI2_COMP2_ISR
	(void *) EE_RX200_LVDI2_COMP2_ISR,	//The LVD2/COMPA2. Interr. handler
#else
/*
 * LVD2/CMPA2 interrupt.
 */
#ifdef	EE_RX200_LVD2_CMPA2_ISR
	(void *) EE_RX200_LVD2_CMPA2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_LVD2_CMPA2_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_ALM_ISR
	(void *) EE_RX200_ALM_ISR,	//The RTC Alarm Interr. handler
#else
/*
 * RTC Alarm interrupt.
 */
#ifdef	EE_RX200_RTC_ALM_ISR
	(void *) EE_RX200_RTC_ALM_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RTC_ALM_ISR */
#endif
#ifdef EE_RX200_PRD_ISR
	(void *) EE_RX200_PRD_ISR,	//The RTC Periodic Interr. handler
#else
/*
 * RTC Periodic interrupt.
 */
#ifdef	EE_RX200_RTC_PRD_ISR
	(void *) EE_RX200_RTC_PRD_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RTC_PRD_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_S12ADI0_ISR
	(void *) EE_RX200_S12ADI0_ISR,	//The 12-bit ADC scan end int. handler
#else
/*
 * ADC Scan End interrupt.
 */
#ifdef	EE_RX200_S12AD_S12ADI0_ISR
	(void *) EE_RX200_S12AD_S12ADI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_S12AD_S12ADI0_ISR */
#endif
#ifdef EE_RX200_GBADI_ISR
	(void *) EE_RX200_GBADI_ISR,	//The 12-bit ADC group B scan end int. handler
#else
/*
 * ADC Group B Scan End interrupt.
 */
#ifdef	EE_RX200_S12AD_GBADI_ISR
	(void *) EE_RX200_S12AD_GBADI_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_S12AD_GBADI_ISR */

#endif
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_ELSR18I_ISR
	(void *) EE_RX200_ELSR18I_ISR,	//Event link SR18 int. handler
#else
/*
 * Event Link SR18 interrupt.
 */
#ifdef	EE_RX200_ELC_ELSR18I_ISR
	(void *) EE_RX200_ELC_ELSR18I_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ELC_ELSR18I_ISR */
#endif
#ifdef EE_RX200_ELSR19I_ISR
	(void *) EE_RX200_ELSR19I_ISR,	//Event link SR19 int. handler
#else
/*
 * Event Link SR19 interrupt.
 */
#ifdef	EE_RX200_ELC_ELSR19I_ISR
	(void *) EE_RX200_ELC_ELSR19I_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_ELC_ELSR19I_ISR */

#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_TGIA0_ISR
	(void *) EE_RX200_TGIA0_ISR,	//The MTU0.TGRA  input capture/comp match
#else
/*
 * MTU0 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIA0_ISR
	(void *) EE_RX200_MTU0_TGIA0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU0_TGIA0_ISR */
#endif
#ifdef EE_RX200_TGIB0_ISR
	(void *) EE_RX200_TGIB0_ISR,	//The MTU0.TGRB input capture/comp match
#else
/*
 * MTU0 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIB0_ISR
	(void *) EE_RX200_MTU0_TGIB0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU0_TGIB0_ISR */
#endif
#ifdef EE_RX200_TGIC0_ISR
	(void *) EE_RX200_TGIC0_ISR,	//The MTU0.TGRC input capture/comp match
#else
/*
 * MTU0 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIC0_ISR
	(void *) EE_RX200_MTU0_TGIC0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU0_TGIC0_ISR */
#endif
#ifdef EE_RX200_TGID0_ISR
	(void *) EE_RX200_TGID0_ISR,	//The MTU0.TGRD input capture/comp match
#else
/*
 * MTU0 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGID0_ISR
	(void *) EE_RX200_MTU0_TGID0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU0_TGID0_ISR */

#endif
#ifdef EE_RX200_TCIV0_ISR
	(void *) EE_RX200_TCIV0_ISR,	//The MTU0.TCNT overflow int. handler
#else
/*
 * MTU0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU0_TCIV0_ISR
	(void *) EE_RX200_MTU0_TCIV0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU0_TCIV0_ISR */
#endif
#ifdef EE_RX200_TGIE0_ISR
	(void *) EE_RX200_TGIE0_ISR,	//MTU0.TGRE compare match int. handler
#else
/*
 * MTU0 TGRE Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIE0_ISR
	(void *) EE_RX200_MTU0_TGIE0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU0_TGIE0_ISR */
#endif
#ifdef EE_RX200_TGIF0_ISR
	(void *) EE_RX200_TGIF0_ISR,	//MTU0.TGRF compare match int. handler
#else
/*
 * MTU0 TGRF Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU0_TGIF0_ISR
	(void *) EE_RX200_MTU0_TGIF0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU0_TGIF0_ISR */
#endif	
#ifdef EE_RX200_TGIA1_ISR
	(void *) EE_RX200_TGIA1_ISR,	//The MTU1.TGRA  input capture/comp match
#else
/*
 * MTU1 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU1_TGIA1_ISR
	(void *) EE_RX200_MTU1_TGIA1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU1_TGIA1_ISR */
#endif
#ifdef EE_RX200_TGIB1_ISR
	(void *) EE_RX200_TGIB1_ISR,	//The MTU1.TGRB input capture/comp match
#else
/*
 * MTU1 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU1_TGIB1_ISR
	(void *) EE_RX200_MTU1_TGIB1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU1_TGIB1_ISR */
#endif
#ifdef EE_RX200_TCIV1_ISR
	(void *) EE_RX200_TCIV1_ISR,	//The MTU1.TCNT overflow int. handler
#else
/*
 * MTU1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU1_TCIV1_ISR
	(void *) EE_RX200_MTU1_TCIV1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU1_TCIV1_ISR */
#endif
#ifdef EE_RX200_TCIU1_ISR
	(void *) EE_RX200_TCIU1_ISR,	//The MTU1.TCNT undeflow int. handler
#else
/*
 * MTU1 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_MTU1_TCIU1_ISR
	(void *) EE_RX200_MTU1_TCIU1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU1_TCIU1_ISR */
#endif
#ifdef EE_RX200_TGIA2_ISR
	(void *) EE_RX200_TGIA2_ISR,	//The MTU2.TGRA  input capture/comp match
#else
/*
 * MTU2 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU2_TGIA2_ISR
	(void *) EE_RX200_MTU2_TGIA2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU2_TGIA2_ISR */
#endif
#ifdef EE_RX200_TGIB2_ISR
	(void *) EE_RX200_TGIB2_ISR,	//The MTU2.TGRB input capture/comp match
#else
/*
 * MTU2 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU2_TGIB2_ISR
	(void *) EE_RX200_MTU2_TGIB2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU2_TGIB2_ISR */
#endif
#ifdef EE_RX200_TCIV2_ISR
	(void *) EE_RX200_TCIV2_ISR,	//The MTU2.TCNT overflow int. handler
#else
/*
 * MTU2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU2_TCIV2_ISR
	(void *) EE_RX200_MTU2_TCIV2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU2_TCIV2_ISR */
#endif
#ifdef EE_RX200_TCIU2_ISR
	(void *) EE_RX200_TCIU2_ISR,	//The MTU2.TCNT undeflow int. handler
#else
/*
 * MTU2 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_MTU2_TCIU2_ISR
	(void *) EE_RX200_MTU2_TCIU2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU2_TCIU2_ISR */
#endif
#ifdef EE_RX200_TGIA3_ISR
	(void *) EE_RX200_TGIA3_ISR,	//The MTU3.TGRA  input capture/comp match
#else
/*
 * MTU3 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIA3_ISR
	(void *) EE_RX200_MTU3_TGIA3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU3_TGIA3_ISR */
#endif
#ifdef EE_RX200_TGIB3_ISR
	(void *) EE_RX200_TGIB3_ISR,	//The MTU3.TGRB input capture/comp match
#else
/*
 * MTU3 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIB3_ISR
	(void *) EE_RX200_MTU3_TGIB3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU3_TGIB3_ISR */
#endif
#ifdef EE_RX200_TGIC3_ISR
	(void *) EE_RX200_TGIC3_ISR,	//The MTU3.TGRC input capture/comp match
#else
/*
 * MTU3 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGIC3_ISR
	(void *) EE_RX200_MTU3_TGIC3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU3_TGIC3_ISR */
#endif
#ifdef EE_RX200_TGID3_ISR
	(void *) EE_RX200_TGID3_ISR,	//The MTU3.TGRD input capture/comp match
#else
/*
 * MTU3 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU3_TGID3_ISR
	(void *) EE_RX200_MTU3_TGID3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU3_TGID3_ISR */
#endif	
#ifdef EE_RX200_TCIV3_ISR
	(void *) EE_RX200_TCIV3_ISR,	//The MTU3.TCNT overflow int. handler
#else
/*
 * MTU3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU3_TCIV3_ISR
	(void *) EE_RX200_MTU3_TCIV3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU3_TCIV3_ISR */
#endif
#ifdef EE_RX200_TGIA4_ISR
	(void *) EE_RX200_TGIA4_ISR,	//The MTU4.TGRA  input capture/comp match
#else
/*
 * MTU4 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIA4_ISR
	(void *) EE_RX200_MTU4_TGIA4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU4_TGIA4_ISR */
#endif
#ifdef EE_RX200_TGIB4_ISR
	(void *) EE_RX200_TGIB4_ISR,	//The MTU4.TGRB input capture/comp match
#else
/*
 * MTU4 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIB4_ISR
	(void *) EE_RX200_MTU4_TGIB4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU4_TGIB4_ISR */
#endif
#ifdef EE_RX200_TGIC4_ISR
	(void *) EE_RX200_TGIC4_ISR,	//The MTU4.TGRC input capture/comp match
#else
/*
 * MTU4 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGIC4_ISR
	(void *) EE_RX200_MTU4_TGIC4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU4_TGIC4_ISR */
#endif
#ifdef EE_RX200_TGID4_ISR
	(void *) EE_RX200_TGID4_ISR,	//The MTU4.TGRD input capture/comp match
#else
/*
 * MTU4 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU4_TGID4_ISR
	(void *) EE_RX200_MTU4_TGID4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU4_TGID4_ISR */
#endif
#ifdef EE_RX200_TCIV4_ISR
	(void *) EE_RX200_TCIV4_ISR,	//The MTU4.TCNT overflow int. handler
#else
/*
 * MTU4 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_MTU4_TCIV4_ISR
	(void *) EE_RX200_MTU4_TCIV4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU4_TCIV4_ISR */
#endif
#ifdef EE_RX200_TGIU5_ISR
	(void *) EE_RX200_TGIU5_ISR,	//The MTU5.TGRU input capture/comp 
#else
/*
 * MTU5 TGRU Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIU5_ISR
	(void *) EE_RX200_MTU5_TGIU5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU5_TGIU5_ISR */
#endif
#ifdef EE_RX200_TGIV5_ISR
	(void *) EE_RX200_TGIV5_ISR,	//The MTU5.TGRV input capture/comp 
#else
/*
 * MTU5 TGRV Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIV5_ISR
	(void *) EE_RX200_MTU5_TGIV5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU5_TGIV5_ISR */
#endif	
#ifdef EE_RX200_TCIW5_ISR
	(void *) EE_RX200_TCIW5_ISR,	//The MTU5.TGRW input capture/comp 
#else
/*
 * MTU5 TGRW Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_MTU5_TGIW5_ISR
	(void *) EE_RX200_MTU5_TGIW5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_MTU5_TGIW5_ISR */
#endif
/*
 * TPU0 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0A_ISR
	(void *) EE_RX200_TPU0_TGI0A_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU0_TGI0A_ISR */
/*
 * TPU0 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0B_ISR
	(void *) EE_RX200_TPU0_TGI0B_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU0_TGI0B_ISR */
/*
 * TPU0 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0C_ISR
	(void *) EE_RX200_TPU0_TGI0C_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU0_TGI0C_ISR */
/*
 * TPU0 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU0_TGI0D_ISR
	(void *) EE_RX200_TPU0_TGI0D_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU0_TGI0D_ISR */
/*
 * TPU0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU0_TCI0V_ISR
	(void *) EE_RX200_TPU0_TCI0V_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU0_TCI0V_ISR */
/*
 * TPU1 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU1_TGI1A_ISR
	(void *) EE_RX200_TPU1_TGI1A_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU1_TGI1A_ISR */
/*
 * TPU1 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU1_TGI1B_ISR
	(void *) EE_RX200_TPU1_TGI1B_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU1_TGI1B_ISR */
/*
 * TPU1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU1_TCI1V_ISR
	(void *) EE_RX200_TPU1_TCI1V_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU1_TCI1V_ISR */
/*
 * TPU1 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU1_TCI1U_ISR
	(void *) EE_RX200_TPU1_TCI1U_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU1_TCI1U_ISR */
/*
 * TPU2 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU2_TGI2A_ISR
	(void *) EE_RX200_TPU2_TGI2A_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU2_TGI2A_ISR */
/*
 * TPU2 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU2_TGI2B_ISR
	(void *) EE_RX200_TPU2_TGI2B_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU2_TGI2B_ISR */
/*
 * TPU2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU2_TCI2V_ISR
	(void *) EE_RX200_TPU2_TCI2V_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU2_TCI2V_ISR */
/*
 * TPU2 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU2_TCI2U_ISR
	(void *) EE_RX200_TPU2_TCI2U_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU2_TCI2U_ISR */
/*
 * TPU3 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3A_ISR
	(void *) EE_RX200_TPU3_TGI3A_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU3_TGI3A_ISR */
/*
 * TPU3 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3B_ISR
	(void *) EE_RX200_TPU3_TGI3B_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU3_TGI3B_ISR */
/*
 * TPU3 TGRC Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3C_ISR
	(void *) EE_RX200_TPU3_TGI3C_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU3_TGI3C_ISR */
/*
 * TPU3 TGRD Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU3_TGI3D_ISR
	(void *) EE_RX200_TPU3_TGI3D_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU3_TGI3D_ISR */
/*
 * TPU3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU0_TCI0V_ISR
	(void *) EE_RX200_TPU0_TCI0V_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU0_TCI0V_ISR */
/*
 * TPU4 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU4_TGI4A_ISR
	(void *) EE_RX200_TPU4_TGI4A_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU4_TGI4A_ISR */
/*
 * TPU4 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU4_TGI4B_ISR
	(void *) EE_RX200_TPU4_TGI4B_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU4_TGI4B_ISR */
/*
 * TPU4 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU4_TCI4V_ISR
	(void *) EE_RX200_TPU4_TCI4V_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU4_TCI4V_ISR */
/*
 * TPU4 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU4_TCI4U_ISR
	(void *) EE_RX200_TPU4_TCI4U_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU4_TCI4U_ISR */
/*
 * TPU5 TGRA Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU5_TGI5A_ISR
	(void *) EE_RX200_TPU5_TGI5A_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU5_TGI5A_ISR */
/*
 * TPU5 TGRB Input Capture/Compare Match interrupt.
 */
#ifdef	EE_RX200_TPU5_TGI5B_ISR
	(void *) EE_RX200_TPU5_TGI5B_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU5_TGI5B_ISR */
/*
 * TPU5 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TPU5_TCI5V_ISR
	(void *) EE_RX200_TPU5_TCI5V_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU5_TCI5V_ISR */
/*
 * TPU5 Counter Underflow interrupt.
 */
#ifdef	EE_RX200_TPU5_TCI5U_ISR
	(void *) EE_RX200_TPU5_TCI5U_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TPU5_TCI5U_ISR */
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_OEI1_ISR
	(void *) EE_RX200_OEI1_ISR,	//The Port Output 1 (POE1) int. handler.
#else
/*
 * Port Output 1 interrupt.
 */
#ifdef	EE_RX200_POE_OEI1_ISR
	(void *) EE_RX200_POE_OEI1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_POE_OEI1_ISR */
#endif
#ifdef EE_RX200_OEI2_ISR
	(void *) EE_RX200_OEI2_ISR,	//The Port Output 2 (POE2) int. handler.
#else
/*
 * Port Output 2 interrupt.
 */
#ifdef	EE_RX200_POE_OEI2_ISR
	(void *) EE_RX200_POE_OEI2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_POE_OEI2_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
#ifdef EE_RX200_CMIA0_ISR
	(void*) EE_RX200_CMIA0_ISR,	//The TMR0 compare match A int. handler.
#else
/*
 * TMR0 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR0_CMIA0_ISR
	(void *) EE_RX200_TMR0_CMIA0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR0_CMIA0_ISR */
#endif
#ifdef EE_RX200_CMIB0_ISR
	(void *) EE_RX200_CMIB0_ISR,	//The TMR0 compare match B int. handler.
#else
/*
 * TMR0 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR0_CMIB0_ISR
	(void *) EE_RX200_TMR0_CMIB0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR0_CMIB0_ISR */
#endif
#ifdef EE_RX200_OVI0_ISR
	(void *) EE_RX200_OVI0_ISR,	//The TMR0 TCNT overflow int. handler.
#else
/*
 * TMR0 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR0_OVI0_ISR
	(void *) EE_RX200_TMR0_OVI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR0_OVI0_ISR */
#endif
#ifdef EE_RX200_CMIA1_ISR
	(void *) EE_RX200_CMIA1_ISR,	//The TMR1 compare match A int. handler.
#else
/*
 * TMR1 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR1_CMIA1_ISR
	(void *) EE_RX200_TMR1_CMIA1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR1_CMIA1_ISR */
#endif
#ifdef EE_RX200_CMIB1_ISR
	(void *) EE_RX200_CMIB1_ISR,	//The TMR1 compare match B int. handler.
#else
/*
 * TMR1 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR1_CMIB1_ISR
	(void *) EE_RX200_TMR1_CMIB1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR1_CMIB1_ISR */
#endif
#ifdef EE_RX200_OVI1_ISR
	(void *) EE_RX200_OVI1_ISR,	//The TMR1 TCNT overflow int. handler.
#else
/*
 * TMR1 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR1_OVI1_ISR
	(void *) EE_RX200_TMR1_OVI1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR1_OVI1_ISR */
#endif
#ifdef EE_RX200_CMIA2_ISR
	(void *) EE_RX200_CMIA2_ISR,	//The TMR2 compare match A int. handler.
#else
/*
 * TMR2 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR2_CMIA2_ISR
	(void *) EE_RX200_TMR2_CMIA2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR2_CMIA2_ISR */
#endif
#ifdef EE_RX200_CMIB2_ISR
	(void *) EE_RX200_CMIB2_ISR,	//The TMR2 compare match B int. handler.
#else
/*
 * TMR2 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR2_CMIB2_ISR
	(void *) EE_RX200_TMR2_CMIB2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR2_CMIB2_ISR */
#endif
#ifdef EE_RX200_OVI2_ISR
	(void *) EE_RX200_OVI2_ISR,	//The TMR2 TCNT overflow int. handler.
#else
/*
 * TMR2 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR2_OVI2_ISR
	(void *) EE_RX200_TMR2_OVI2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR2_OVI2_ISR */
#endif
#ifdef EE_RX200_CMIA3_ISR
	(void *) EE_RX200_CMIA3_ISR,	//The TMR3 compare match A int. handler.
#else
/*
 * TMR3 TCORA Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR3_CMIA3_ISR
	(void *) EE_RX200_TMR3_CMIA3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR3_CMIA3_ISR */
#endif
#ifdef EE_RX200_CMIB3_ISR
	(void *) EE_RX200_CMIB3_ISR,	//The TMR3 compare match B int. handler.
#else
    /*
 * TMR3 TCORB Compare Match interrupt.
 */
#ifdef	EE_RX200_TMR3_CMIB3_ISR
	(void *) EE_RX200_TMR3_CMIB3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR3_CMIB3_ISR */
#endif
#ifdef EE_RX200_OVI3_ISR
	(void *) EE_RX200_OVI3_ISR,	//The TMR3 TCNT overflow int. handler.
#else
/*
 * TMR3 Counter Overflow interrupt.
 */
#ifdef	EE_RX200_TMR3_OVI3_ISR
	(void *) EE_RX200_TMR3_OVI3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_TMR3_OVI3_ISR */
#endif
/*
 * SCI2 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI2_ERI2_ISR
	(void *) EE_RX200_SCI2_ERI2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI2_ERI2_ISR */
/*
 * SCI2 RX interrupt.
 */
#ifdef	EE_RX200_SCI2_RXI2_ISR
	(void *) EE_RX200_SCI2_RXI2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI2_RXI2_ISR */
/*
 * SCI2 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI2_TXI2_ISR
	(void *) EE_RX200_SCI2_TXI2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI2_TXI2_ISR */
/*
 * SCI2 TX End interrupt.
 */
#ifdef	EE_RX200_SCI2_TEI2_ISR
	(void *) EE_RX200_SCI2_TEI2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI2_TEI2_ISR */
/*
 * SCI3 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI3_ERI3_ISR
	(void *) EE_RX200_SCI3_ERI3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI3_ERI3_ISR */
/*
 * SCI3 RX interrupt.
 */
#ifdef	EE_RX200_SCI3_RXI3_ISR
	(void *) EE_RX200_SCI3_RXI3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI3_RXI3_ISR */
/*
 * SCI3 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI3_TXI3_ISR
	(void *) EE_RX200_SCI3_TXI3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI3_TXI3_ISR */
/*
 * SCI3 TX End interrupt.
 */
#ifdef	EE_RX200_SCI3_TEI3_ISR
	(void *) EE_RX200_SCI3_TEI3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI3_TEI3_ISR */
/*
 * SCI4 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI4_ERI4_ISR
	(void *) EE_RX200_SCI4_ERI4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI4_ERI4_ISR */
/*
 * SCI4 RX interrupt.
 */
#ifdef	EE_RX200_SCI4_RXI4_ISR
	(void *) EE_RX200_SCI4_RXI4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI4_RXI4_ISR */
/*
 * SCI4 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI4_TXI4_ISR
	(void *) EE_RX200_SCI4_TXI4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI4_TXI4_ISR */
/*
 * SCI4 TX End interrupt.
 */
#ifdef	EE_RX200_SCI4_TEI4_ISR
	(void *) EE_RX200_SCI4_TEI4_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI4_TEI4_ISR */
#ifdef EE_RX200_DMAC0I_ISR
	(void *) EE_RX200_DMAC0I_ISR,	//The DMAC channel 0 transfer end ISR.
#else
/*
 * DMAC channel 0 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC0I_ISR
	(void *) EE_RX200_DMAC_DMAC0I_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_DMAC_DMAC0I_ISR */
#endif
#ifdef EE_RX200_DMAC1I_ISR
	(void *) EE_RX200_DMAC1I_ISR,	//The DMAC channel 1 transfer end ISR.
#else
/*
 * DMAC channel 1 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC1I_ISR
	(void *) EE_RX200_DMAC_DMAC1I_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_DMAC_DMAC1I_ISR */
#endif
#ifdef EE_RX200_DMAC2I_ISR
	(void *) EE_RX200_DMAC2I_ISR,	//The DMAC channel 2 transfer end ISR.
#else
/*
 * DMAC channel 2 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC2I_ISR
	(void *) EE_RX200_DMAC_DMAC2I_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_DMAC_DMAC2I_ISR */
#endif
#ifdef EE_RX200_DMAC3I_ISR
	(void *) EE_RX200_DMAC3I_ISR,	//The DMAC channel 3 transfer end ISR.
#else
/*
 * DMAC channel 3 transfer end interrupt.
 */
#ifdef	EE_RX200_DMAC_DMAC3I_ISR
	(void *) EE_RX200_DMAC_DMAC3I_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_DMAC_DMAC3I_ISR */
#endif
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
	0,					/* Reserved */
/*
 * SCI7 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI7_ERI7_ISR
	(void *) EE_RX200_SCI7_ERI7_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI7_ERI7_ISR */
/*
 * SCI7 RX interrupt.
 */
#ifdef	EE_RX200_SCI7_RXI7_ISR
	(void *) EE_RX200_SCI7_RXI7_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI7_RXI7_ISR */
/*
 * SCI7 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI7_TXI7_ISR
	(void *) EE_RX200_SCI7_TXI7_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI7_TXI7_ISR */
/*
 * SCI7 TX End interrupt.
 */
#ifdef	EE_RX200_SCI7_TEI7_ISR
	(void *) EE_RX200_SCI7_TEI7_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI7_TEI7_ISR */
/*
 * SCI10 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI10_ERI10_ISR
	(void *) EE_RX200_SCI10_ERI10_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI10_ERI10_ISR */
/*
 * SCI10 RX interrupt.
 */
#ifdef	EE_RX200_SCI10_RXI10_ISR
	(void *) EE_RX200_SCI10_RXI10_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI10_RXI10_ISR */
/*
 * SCI10 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI10_TXI10_ISR
	(void *) EE_RX200_SCI10_TXI10_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI10_TXI10_ISR */
/*
 * SCI10 TX End interrupt.
 */
#ifdef	EE_RX200_SCI10_TEI10_ISR
	(void *) EE_RX200_SCI10_TEI10_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI10_TEI10_ISR */
#ifdef EE_RX200_ERI0_ISR
	(void *) EE_RX200_ERI0_ISR,	//The SCI0 Receive Error int. handler.
#else
/*
 * SCI0 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI0_ERI0_ISR
	(void *) EE_RX200_SCI0_ERI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI0_ERI0_ISR */
#endif
#ifdef EE_RX200_RXI0_ISR
	(void *) EE_RX200_RXI0_ISR,	//The SCI0 RX int. handler.
#else
/*
 * SCI0 RX interrupt.
 */
#ifdef	EE_RX200_SCI0_RXI0_ISR
	(void *) EE_RX200_SCI0_RXI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI0_RXI0_ISR */
#endif
#ifdef EE_RX200_TXI0_ISR
	(void *) EE_RX200_TXI0_ISR,	//The SCI0 TX empty int. handler.
#else
/*
 * SCI0 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI0_TXI0_ISR
	(void *) EE_RX200_SCI0_TXI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI0_TXI0_ISR */
#endif
#ifdef EE_RX200_TEI0_ISR
	(void *) EE_RX200_TEI0_ISR,	//The SCI0 TX end int. handler.
#else
/*
 * SCI0 TX End interrupt.
 */
#ifdef	EE_RX200_SCI0_TEI0_ISR
	(void *) EE_RX200_SCI0_TEI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI0_TEI0_ISR */
#endif
#ifdef EE_RX200_ERI1_ISR
	(void *) EE_RX200_ERI1_ISR,	//The SCI1 Receive Error int. handler.
#else
/*
 * SCI1 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI1_ERI1_ISR
	(void *) EE_RX200_SCI1_ERI1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI1_ERI1_ISR */
#endif
#ifdef EE_RX200_RXI1_ISR
	(void *) EE_RX200_RXI1_ISR,	//The SCI1 RX int. handler.
#else
/*
 * SCI1 RX interrupt.
 */
#ifdef	EE_RX200_SCI1_RXI1_ISR
	(void *) EE_RX200_SCI1_RXI1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI1_RXI1_ISR */
#endif
#ifdef EE_RX200_TXI1_ISR
	(void *) EE_RX200_TXI1_ISR,	//The SCI1 TX int. handler.
#else
/*
 * SCI1 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI1_TXI1_ISR
	(void *) EE_RX200_SCI1_TXI1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI1_TXI1_ISR */
#endif
#ifdef EE_RX200_TEI1_ISR
	(void *) EE_RX200_TEI1_ISR,	//The SCI1 TX empty int. handler.
#else
/*
 * SCI1 TX End interrupt.
 */
#ifdef	EE_RX200_SCI1_TEI1_ISR
	(void *) EE_RX200_SCI1_TEI1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI1_TEI1_ISR */
#endif
#ifdef EE_RX200_ERI5_ISR
	(void *) EE_RX200_ERI5_ISR,	//The SCI5 Receive Error int. handler.
#else
/*
 * SCI5 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI5_ERI5_ISR
	(void *) EE_RX200_SCI5_ERI5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI5_ERI5_ISR */
#endif
#ifdef EE_RX200_RXI5_ISR
	(void *) EE_RX200_RXI5_ISR,	//The SCI5 RX int. handler.
#else
/*
 * SCI5 RX interrupt.
 */
#ifdef	EE_RX200_SCI5_RXI5_ISR
	(void *) EE_RX200_SCI5_RXI5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI5_RXI5_ISR */
#endif
#ifdef EE_RX200_TXI5_ISR
	(void *) EE_RX200_TXI5_ISR,	//The SCI5 TX int. handler.
#else
/*
 * SCI5 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI5_TXI5_ISR
	(void *) EE_RX200_SCI5_TXI5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI5_TXI5_ISR */
#endif
#ifdef EE_RX200_TEI5_ISR
	(void *) EE_RX200_TEI5_ISR,	//The SCI5 TX empty int. handler.
#else
/*
 * SCI5 TX End interrupt.
 */
#ifdef	EE_RX200_SCI5_TEI5_ISR
	(void *) EE_RX200_SCI5_TEI5_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI5_TEI5_ISR */
#endif
#ifdef EE_RX200_ERI6_ISR
	(void *) EE_RX200_ERI6_ISR,	//The SCI6 Receive Error int. handler.
#else
/*
 * SCI6 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI6_ERI6_ISR
	(void *) EE_RX200_SCI6_ERI6_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI6_ERI6_ISR */
#endif
#ifdef EE_RX200_RXI6_ISR
	(void *) EE_RX200_RXI6_ISR,	//The SCI6 RX int. handler.
#else
/*
 * SCI6 RX interrupt.
 */
#ifdef	EE_RX200_SCI6_RXI6_ISR
	(void *) EE_RX200_SCI6_RXI6_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI6_RXI6_ISR */
#endif
#ifdef EE_RX200_TXI6_ISR
	(void *) EE_RX200_TXI6_ISR,	//The SCI6 TX int. handler.
#else
/*
 * SCI6 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI6_TXI6_ISR
	(void *) EE_RX200_SCI6_TXI6_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI6_TXI6_ISR */
#endif
#ifdef EE_RX200_TEI6_ISR
	(void *) EE_RX200_TEI6_ISR,	//The SCI6 TX empty int. handler.
#else
/*
 * SCI6 TX End interrupt.
 */
#ifdef	EE_RX200_SCI6_TEI6_ISR
	(void *) EE_RX200_SCI6_TEI6_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI6_TEI6_ISR */
#endif
#ifdef EE_RX200_ERI8_ISR
	(void *) EE_RX200_ERI8_ISR,	//The SCI8 Receive Error int. handler.
#else
/*
 * SCI8 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI8_ERI8_ISR
	(void *) EE_RX200_SCI8_ERI8_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI8_ERI8_ISR */
#endif
#ifdef EE_RX200_RXI8_ISR
	(void *) EE_RX200_RXI8_ISR,	//The SCI8 RX int. handler.
#else
/*
 * SCI8 RX interrupt.
 */
#ifdef	EE_RX200_SCI8_RXI8_ISR
	(void *) EE_RX200_SCI8_RXI8_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI8_RXI8_ISR */
#endif
#ifdef EE_RX200_TXI8_ISR
	(void *) EE_RX200_TXI8_ISR,	//The SCI8 TX int. handler.
#else
/*
 * SCI8 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI8_TXI8_ISR
	(void *) EE_RX200_SCI8_TXI8_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI8_TXI8_ISR */
#endif
#ifdef EE_RX200_TEI8_ISR
	(void *) EE_RX200_TEI8_ISR,	//The SCI8 TX empty int. handler.
#else
/*
 * SCI8 TX End interrupt.
 */
#ifdef	EE_RX200_SCI8_TEI8_ISR
	(void *) EE_RX200_SCI8_TEI8_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI8_TEI8_ISR */
#endif
#ifdef  EE_RX200_ERI9_ISR
	(void *) EE_RX200_ERI9_ISR,	//The SCI9 Receive Error int. handler.
#else
/*
 * SCI9 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI9_ERI9_ISR
	(void *) EE_RX200_SCI9_ERI9_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI9_ERI9_ISR */
#endif
#ifdef EE_RX200_RXI9_ISR
	 (void *) EE_RX200_RXI9_ISR,	//The SCI9 RX int. handler.
#else
/*
 * SCI9 RX interrupt.
 */
#ifdef	EE_RX200_SCI9_RXI9_ISR
	(void *) EE_RX200_SCI9_RXI9_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI9_RXI9_ISR */
#endif
#ifdef EE_RX200_TXI9_ISR
	(void *) EE_RX200_TXI9_ISR,	//The SCI9 TX int. handler.
#else
/*
 * SCI9 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI9_TXI9_ISR
	(void *) EE_RX200_SCI9_TXI9_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI9_TXI9_ISR */
#endif
#ifdef EE_RX200_TEI9_ISR
	(void *) EE_RX200_TEI9_ISR,	//The SCI9 TX empty int. handler.
#else
/*
 * SCI9 TX End interrupt.
 */
#ifdef	EE_RX200_SCI9_TEI9_ISR
	(void *) EE_RX200_SCI9_TEI9_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI9_TEI9_ISR */
#endif
#ifdef EE_RX200_ERI12_ISR
	(void *) EE_RX200_ERI12_ISR,	//The SCI12 Receive Error int. handler.
#else
/*
 * SCI12 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI12_ERI12_ISR
	(void *) EE_RX200_SCI12_ERI12_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_ERI12_ISR */
#endif
#ifdef EE_RX200_RXI12_ISR
	(void *) EE_RX200_RXI12_ISR,	//The SCI12 RX int. handler.
#else
/*
 * SCI12 RX interrupt.
 */
#ifdef	EE_RX200_SCI12_RXI12_ISR
	(void *) EE_RX200_SCI12_RXI12_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_RXI12_ISR */
#endif
#ifdef EE_RX200_TXI12_ISR
	(void *) EE_RX200_TXI12_ISR,	//The SCI12 TX int. handler.
#else
/*
 * SCI12 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI12_TXI12_ISR
	(void *) EE_RX200_SCI12_TXI12_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_TXI12_ISR */
#endif
#ifdef EE_RX200_TEI12_ISR
	(void *) EE_RX200_TEI12_ISR,	//The SCI12 TX empty int. handler.
#else
/*
 * SCI12 TX End interrupt.
 */
#ifdef	EE_RX200_SCI12_TEI12_ISR
	(void *) EE_RX200_SCI12_TEI12_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_TEI12_ISR */
#endif
// Extended Serial Mode Control Interrupt handlers (SCI12)
#ifdef EE_RX200_SCIX0_ISR
	(void *) EE_RX200_SCIX0_ISR,	
#else
/*
 * SCI12 Extended Serial Mode Control 0 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX0_ISR
	(void *) EE_RX200_SCI12_SCIX0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_SCIX0_ISR */
#endif
#ifdef EE_RX200_SCIX1_ISR
	(void *) EE_RX200_SCIX1_ISR,	
#else
/*
 * SCI12 Extended Serial Mode Control 1 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX1_ISR
	(void *) EE_RX200_SCI12_SCIX1_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_SCIX1_ISR */
#endif
#ifdef EE_RX200_SCIX2_ISR
	(void *) EE_RX200_SCIX2_ISR,
#else
/*
 * SCI12 Extended Serial Mode Control 2 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX2_ISR
	(void *) EE_RX200_SCI12_SCIX2_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_SCIX2_ISR */
#endif
#ifdef EE_RX200_SCIX3_ISR
	(void *) EE_RX200_SCIX3_ISR,
#else
/*
 * SCI12 Extended Serial Mode Control 3 interrupt.
 */
#ifdef	EE_RX200_SCI12_SCIX3_ISR
	(void *) EE_RX200_SCI12_SCIX3_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI12_SCIX3_ISR */
#endif
#ifdef EE_RX200_EEI0_ISR
	(void *) EE_RX200_EEI0_ISR,	//The RIIC0 Event/Error int. handler.
#else
/*
 * RIIC0 Event/Error interrupt.
 */
#ifdef	EE_RX200_RIIC0_EEI0_ISR
	(void *) EE_RX200_RIIC0_EEI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RIIC0_EEI0_ISR */
#endif
#ifdef EE_RX200_RXI0_ISR
	(void *) EE_RX200_RXI0_ISR,	//The RIIC0 Receive Data Full int. handler.
#else
/*
 * RIIC0 Receive Data Full interrupt.
 */
#ifdef	EE_RX200_RIIC0_RXI0_ISR
	(void *) EE_RX200_RIIC0_RXI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RIIC0_RXI0_ISR */
#endif
#ifdef EE_RX200_TXI0_ISR
	(void *) EE_RX200_TXI0_ISR,	//The RIIC0 TX end int. handler.
#else
/*
 * RIIC0 TX End interrupt.
 */
#ifdef	EE_RX200_RIIC0_TXI0_ISR
	(void *) EE_RX200_RIIC0_TXI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RIIC0_TXI0_ISR */
#endif
#ifdef EE_RX200_TEI0_ISR
	(void *) EE_RX200_TEI0_ISR,	//The RIIC0 TX data empty int. handler.
#else
/*
 * RIIC0 TX Data Empty interrupt.
 */
#ifdef	EE_RX200_RIIC0_TEI0_ISR
	(void *) EE_RX200_RIIC0_TEI0_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_RIIC0_TEI0_ISR */
#endif
/*
 * SCI11 RX Error interrupt.
 */
#ifdef	EE_RX200_SCI11_ERI11_ISR
	(void *) EE_RX200_SCI11_ERI11_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI11_ERI11_ISR */
/*
 * SCI11 RX interrupt.
 */
#ifdef	EE_RX200_SCI11_RXI11_ISR
	(void *) EE_RX200_SCI11_RXI11_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI11_RXI11_ISR */
/*
 * SCI11 TX Empty interrupt.
 */
#ifdef	EE_RX200_SCI11_TXI11_ISR
	(void *) EE_RX200_SCI11_TXI11_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI11_TXI11_ISR */
/*
 * SCI11 TX End interrupt.
 */
#ifdef	EE_RX200_SCI11_TEI11_ISR
	(void *) EE_RX200_SCI11_TEI11_ISR,
#else
	EE_rx200_default_ISR,
#endif	/* EE_RX200_SCI11_TEI11_ISR */
	0,					/* Reserved */
	0					/* Reserved */
};
