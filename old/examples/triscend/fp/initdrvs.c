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
 * Author: 2001-2002 Marko Bertogna
 * CVS: $Id: initdrvs.c,v 1.2 2006/05/14 18:00:59 pj Exp $
 */

#include "erikahal.h"

extern EE_ADDR __begin;

void init_drivers(void);
void EE_vector2internal(void);
void EE_sdram_init(void);


#ifdef __LED_USED__

/* number <-> segments mapping */
EE_UREG EE_LED_numeric_display[16] = 
   { 0x03, 0x9f, 0x25, 0x0d, 0x99, 0x49, 0x41, 0x1f,	/* 7 */
    0x01, 0x19, 0x11, 0xc1, 0x63, 0x85, 0x61, 0x71	/* 15 */
	};

#endif /* __LED_USED__ */



/*
 * Initialize the SDRAM.
 *
 */
void EE_sdram_init( void )			
{
    unsigned long refresh;
    unsigned long freq;

    freq = EE_clock_getFreq();

    refresh = ( unsigned long ) ( freq / 64000 );

    refresh <<= 16;
    refresh &= 0x0fff0000;

    refresh |= 0x00000003;

    /* Set the SDRAM refresh rate */
    *MSS_SDR_CTRL_REG = refresh;

    /* Read the value back to flush the CSI pipeline */
    refresh = *MSS_SDR_CTRL_REG;

    /*
     * If the clock frequency is greater than 40MHz
     * enable the memory pipeline.
     */
    if ( freq > 40000000 )
	*MSS_CONFIG_REG |= 0x00008000;	//pipeline enable

    /* Enable the DMA buffers */
    *MSS_CONFIG_REG |= 0x00ff0000;	//enable all dma buffers: 4 flash, 4 sdram
}



void EE_vector2internal(void)
{
	 EE_UREG n;
    char *src = ( char * ) &__begin;		//__begin dichiarata globl in start.S
    char *dst = ( char * ) 0xd1030000;
    
		// We only do the copy if SDRAM is aliased to address zero.
    	// To find this out we check the alias enable register.
     
    if( *REMAP_ALIAS_ENABLE_REG & 0x08 )		
    {
        // Copy the vector table to address 0x00000000 
        for ( n = (EE_UREG) &__begin; n < 0x4000; n++ )
  	    		*dst++ = *src++;
        // Make sure the scratch pad is mapped at 0x00000000
        *REMAP_ALIAS_ENABLE_REG |= 0x04;
    }
}



void init_drivers(void)
{
//tutti i driver definiti inline in include/triscend/inline_d.h
//						e dichiarati in	include/triscend/drivers.h

EE_icu_init();				//azzera gli interrupt 
EE_vector2internal();	//copia vector section da SDRAM a internal SRAM (poi aliasata a zero)

#if __UART_USED__
	EE_uart_init();		//richiede a7hal_clock_getFreq e tutte le strutture di uart.c e .h
#endif

#if __WATCHDOG_USED__
	EE_enable_external_IRQ(1<<IRQ_WATCHDOG_BIT);
	EE_watchdog_init();
#endif

#if __TIMER_0_USED__
	EE_enable_external_IRQ(1<<IRQ_TIMER_0_BIT);
	EE_timer_0_init();
#endif

#if __TIMER_1_USED__
	EE_enable_external_IRQ(1<<IRQ_TIMER_1_BIT);
	EE_timer_1_init();
#endif
    
#ifdef __LED_USED__
    EE_LED_init();
#endif

#ifdef __DIP_SWITCH_USED__
    /* do nothing */
#endif


/*
#if A7HAL_USE_DMA
	a7hal_dma_init();	//richiede tutte le struture di dma.c e .h
#endif

#if A7HAL_USE_MPU
	a7hal_mpu_init();	//richiede tutte le strutture di mpu.c e .h e read/writeCPR/CPRSub
#endif
*/
//sdram_init e' invocata da start.S 
//power_init e' simile a icu_init e non uso per ora la funzione low_power (in vector di init.S)

}
