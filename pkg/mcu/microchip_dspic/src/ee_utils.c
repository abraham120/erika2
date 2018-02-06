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

#include "ee.h"
#include "ee_irq.h"
 
 
#if defined(__dsPIC33F__)

#include "mcu/microchip_dspic/inc/ee_utils.h"

#define EE_OSC_FRC_PLL 1
#define EE_OSC_PRI_PLL 3

#define EE_MAX_FOSC 80000000UL

static EE_UINT8 EE_check_clock_switch_enabled(void)
{
    static EE_UINT16 const clockSwitchDisabled  = 0x0080U;
    static EE_UINT16 const clockMonitorDisabled = 0x0040U;    
    EE_UINT16 foscr = EE_read_fosc();
    return !(foscr & clockSwitchDisabled) && (foscr & clockMonitorDisabled) && !OSCCONbits.CLKLOCK;
}

static void EE_set_system_clock_pll(EE_UINT32 fosc, EE_UINT32 fin, EE_UINT8 nosc)
{
    /* M = (N1 * N2) * Fosc / Fin */
    EE_UINT32 M = (fosc * 4U + fin / 2U) / fin;

    OSCTUN = 0;     /* FRC  Oscillator Tuning Register. 0 => center frequency nominal FRC frequency (7,37 MHz) */
    PLLFBD = M - 2; /* M PLL Feedback Divisor VCO output. Symbol eq PLLFDB. (register with an offset equal to 2) */
	CLKDIV = 0x3000;              /* DOZE not enabled => Processor clock/peripheral clock ratio forced to 1:1 */
	                              /* N1=2 */
								  /* N2=2 */
								  /* FRC is not post scaled (I don't need it) */
	
    __builtin_write_OSCCONH(nosc); /* New Oscillator Selection bits */
    __builtin_write_OSCCONL(0x01); /* Initiate Clock Switch OSWEN: Oscillator Switch Enable bit*/

    while (OSCCONbits.COSC != nosc) {
        /* Wait for Clock switch to occur */
    }
    while (!OSCCONbits.LOCK) {
        /* Wait for PLL to lock */
    }
}

/* Imposta il clock di istruzione del dspic. Range [8,40] Mhz
 * vedi pag 147 data sheet dsPic
 *
 * e.g with Fcy = 40 e N1 = N2 = 2;
 * Fin:  frequenza oscillatore primario. Nel nostro caso FRC interno = 7.37 MHz
 * Fosc = Fin*M/(N1*N2),    --> Oscillator frequency / PLL output
 * Fcy  = Fosc/2             --> Device operating frequency
 * Fosc = 7.37M*43(2*2) =~ 80Mhz for 7.37M input clock
 */
EE_INT16 EE_set_system_clock(EE_UINT32 fosc)
{
    EE_INT16 error = 0;
    EE_UINT8 const currentOsc      = OSCCONbits.COSC;
    EE_UINT8 const programmableOsc = (currentOsc == EE_OSC_FRC_PLL) || (currentOsc == EE_OSC_PRI_PLL);
    if( !programmableOsc && !EE_check_clock_switch_enabled() )
        /* Impossible to execute clock switch */
        error = EE_UTILS_ERR_NO_CLOCK_SWITCH;

    if(!error) {
        /* Input out of range correction */
        if (fosc < EE_PIC30_FRC_OSC_FREQ) {
            fosc = EE_PIC30_FRC_OSC_FREQ;
        } else if (fosc > EE_MAX_FOSC) {
            fosc = EE_MAX_FOSC;
        }
        
        /* check the actual oscillator */
        switch (currentOsc) { 
            case 0: /* FNOSC_FRC */
            case EE_OSC_FRC_PLL: /* FNOSC_FRCPLL */
                EE_set_system_clock_pll(fosc, EE_PIC30_FRC_OSC_FREQ, EE_OSC_FRC_PLL);
            break;
            case 2: /* FNOSC_PRI */
            case EE_OSC_PRI_PLL: /* FNOSC_PRIPLL */
                EE_set_system_clock_pll(fosc, EE_PIC30_PRI_OSC_FREQ, EE_OSC_PRI_PLL);
            break;
            case 4: /* FNOSC_SOSC */
            case 5: /* FNOSC_LPRC */
            case 6: /* FNOSC_FRCDIV16 */
            case 7: /* FNOSC_LPRCDIVN */
                /* TODO add all possible oscillator sources */
                error =  EE_UTILS_ERR_UNKNOWN_CLOCK_SOURCE;
        }
    }
    return error;
}

static EE_INT32 EE_get_system_clock_pll(EE_UINT32 fin)
{
    /* CLKDIVbits.PLLPOST = 0x2 is a reserved value */
    static EE_UINT16 const valuesN1[] = {2, 4, 0, 8};
    EE_UINT16 M  = PLLFBDbits.PLLDIV + 2U;
    EE_UINT16 indexN1 = CLKDIVbits.PLLPOST;
    EE_UINT16 N2 = CLKDIVbits.PLLPRE + 2U;
    EE_UINT16 N  = valuesN1[indexN1] * N2;

    EE_UINT32 fosc = 0;
    if(N > 0)
        /* Fosc = M * Fin / (N1 * N2) */
        fosc = ((EE_INT32)M * fin + N / 2U) / N;
    return fosc;
}

EE_UINT32 EE_get_system_clock(void)
{
    EE_UINT32  fosc = 0;
    EE_UINT16 frcPostscaler = 1 << CLKDIVbits.FRCDIV;
    EE_UINT32 frcFin = EE_PIC30_FRC_OSC_FREQ / frcPostscaler;
    /* check the actual oscillator */
    switch (OSCCONbits.COSC) { 
        case 0: /* FNOSC_FRC */
            fosc = EE_PIC30_FRC_OSC_FREQ;
        break;
        case 1: /* FNOSC_FRCPLL */
            fosc = EE_get_system_clock_pll(frcFin);
        break;
        case 2: /* FNOSC_PRI */
            fosc = EE_PIC30_PRI_OSC_FREQ;
        break;
        case 3: /* FNOSC_PRIPLL */
            fosc = EE_get_system_clock_pll(EE_PIC30_PRI_OSC_FREQ);
        break;
        case 6: /* FNOSC_FRCDIV16 */
            fosc = frcFin;
        break;
        case 4: /* FNOSC_SOSC */
        case 5: /* FNOSC_LPRC */
        case 7: /* FNOSC_LPRCDIVN */
            /* TODO add all possible oscillator sources */
            fosc = EE_UTILS_ERR_UNKNOWN_CLOCK_SOURCE;
            break;
    }
    return fosc;
}

EE_UINT32 EE_get_peripheral_clock(void)
{
    EE_UINT32 fosc = EE_get_system_clock();
    /* fosc >= 0 => no error happened  */
    if (fosc >= 0)
        fosc /= 2U;
    return fosc;
}

EE_UINT32 EE_get_cpu_mips(void)
{
    EE_UINT16 dozeRatio = 1;
    EE_UINT32 mips = EE_get_system_clock();
    /* mips >= 0 => no error happened  */
    if(mips >= 0) {
        if(CLKDIVbits.DOZEN)
            dozeRatio = 1 << CLKDIVbits.DOZE;
        mips /= (2 * dozeRatio * 1000000UL);
    }
    return  mips;
}
#endif /* __dsPIC33F__ */
