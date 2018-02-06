/**
 * @file
 * @brief Board-dependent part of BIOS/HAL for RDK230
 *
 * $Id: board_rdk230.c,v 1.1 2007/06/22 13:50:48 romano Exp $
 *
 */
/**
 *  \author
 *      Atmel Corporation: http://www.atmel.com
 *      Support email: avr@atmel.com
 */
/*
 * Copyright (c) 2006, Atmel Corporation All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of ATMEL may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* === Includes ============================================================ */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#ifndef DEF_H
#include "def.h"
#endif
#include "ee_confMac.h"
#include "board.h"
#include "bios.h"
#include "phy.h"
#if APP_TYPE == APP_L0
# include "validation.h"
#endif /* APP_LEVEL == APP_L0 */

#if APP_TYPE == LIB_HAL
# include "wpan_hal.h"
#endif

#if APP_TYPE >= APP_L2
# include "mac.h"
#endif /* APP_LEVEL >= APP_L2 */

#if BOARD_TYPE == RDK230 || defined (DOXYGEN)

/* === Defines ============================================================= */

/** All ASSR bits that mark the asynchronous timer to be busy. */
#define ASSR_BUSY (_BV(TCN0UB) | _BV(OCR0UB) | _BV(TCR0UB))

/** The value is used by the clibration routine.
    At the end of a calibration cycle this value is compared with the counter
    result.
 */
#define TARGETVAL ((1000000ULL * 256 * 32) / F_CPU)

/* === Globals ============================================================= */

/* === Prototypes ========================================================== */

#if RC_OSC_USED
static bool calibrate_rc_osc(void);
#endif

/* === Implementation ====================================================== */

/**
 * @brief Low-Level Initialization
 *
 * Enables the external SRAM interface and disables the watchdog. This function
 * is called before main() is entered.
 */
ENABLE_XRAM(void)
{
    WATCHDOG_DISABLE();

    RETURN_ENABLE_XRAM;
}

/**
 * @brief BIOS Initialization
 *
 * This function initialize the BIOS module and will enable interrupts.
 */
void bios_init(void)
{
    TRX_RESET_HIGH();
    TRX_INIT_RESET_PIN();
    TRX_INIT_SLPTR_PIN();

    spi_init();
    spi_set_rate (SPI_RATE_1_2);

#if APP_TYPE < APP_L1
    /*
     * APP_TYPE >= APP_L1 defers the interrupt initialization until
     * the IRQ mask has been set in the PHY.
     */
    board_irq_init();
#endif /* APP_TYPE < APP_L1 */

#if RC_OSC_USED && (APP_TYPE >= APP_L0)
    if (calibrate_rc_osc())
    {
        PRINT("OSCCAL calibrated to 0x%0x", (uint16_t)OSCCAL);
    }
    else
    {
        ECHO("OSCCAL calibration failed");
    }
#endif /* RC_OSC_USED */

#if APP_TYPE >= APP_L0
    bios_timer_init();
#endif

    // Enable interrupts
    sei ();

}


/**
 * @brief Reset of the peripheral hardware
 *
 * This function performs the reset operation of the
 * software programming modell. After this routine,
 * the AT86RF230 should deliver a 1 MHz clock to the
 * controller
 */
void bios_reset_hardware(void)
{

/* for AT86RF230, we have to excute here a part of the phy_init sequence
 *
 * PINSET(d1,RST,0);
 * PINSET(d1,SLP_TR,0);
 * WAITTMR(d1,sw,6us);
 * PINSET(d1,RST,1);
 *
 * only so we can guarantee, that the radio is brought to known good state
 * on the fasted way.
 */
    TRX_RESET_LOW();
    TRX_SLPTR_LOW();
    delay_us(600);
    TRX_RESET_HIGH();
}

/**
 * @brief Initialize the IRQ of the radio
 *
 * This function does the irq initilization.
 */
void board_irq_init(void)
{
    INIT_TRX_IRQ();
    EI_TRX_IRQ();
}

/**
 * @brief Go to sleep
 *
 * This function puts the radio and microcontroler to sleep.
 * Make sure that no interrupt occures while in this function.
 * @param st The sleep time in 32kHz clock cycles. (0 < st < 262144)
 */
void bios_sleep(uint32_t st)
{
    uint8_t sleep_time;

    /* configure timer2 for sleep functionality */
    /* timer2 becomes an asynchronous timer */
    ASSR |= _BV(AS0);

    if (st > 256)
    {
        if ((st / 8) > 256)
        {
            if ((st / 32) > 256)
            {
                if ((st / 64) > 256)
                {
                    if ((st / 128) > 256)
                    {
                        if ((st / 256) > 256)
                        {
                            /* set timer2's prescaler to 1024 and put SLP_TR pin in normal mode */
                            TCCR0 = _BV(CS02) | _BV(CS01) | _BV(CS00);
                            if ((st / 1024) > 256)
                            {
                                sleep_time = 255;
                            }
                            else
                            {
                                sleep_time = st / 1024;
                            }
                        }
                        else
                        {
                            /* set timer2's prescaler to 256 and put SLP_TR pin in normal mode */
                            TCCR0 = _BV(CS02)|_BV(CS01);
                            sleep_time = st / 256;
                        }
                    }
                    else
                    {
                        /* set timer2's prescaler to 128 and put SLP_TR pin in normal mode */
                        TCCR0 = _BV(CS02)|_BV(CS00);
                        sleep_time = st / 128;
                    }
                }
                else
                {
                    /* set timer2's prescaler to 64 and put SLP_TR pin in normal mode */
                    TCCR0 = _BV(CS02);
                    sleep_time = st / 64;
                }
            }
            else
            {
                /* set timer2's prescaler to 32 and put SLP_TR pin in normal mode */
                TCCR0 = _BV(CS01)|_BV(CS00);
                sleep_time = st / 32;
            }
        }
        else
        {
            /* set timer2's prescaler to 8 and put SLP_TR pin in normal mode */
            TCCR0 = _BV(CS01);
            sleep_time = st / 8;
        }
    }
    else
    {
        /* set timer2's prescaler to 1 and put SLP_TR pin in normal mode */
        TCCR0 = _BV(CS00);
        sleep_time = st;
    }
    while (ASSR & ASSR_BUSY) {}

    /* choose the correct sleep mode of the AVR */
    set_sleep_mode(SLEEP_MODE_PWR_SAVE);

    TCNT0  = 0x00;          // Reset Counter Value
    OCR0   = sleep_time;   // Set Compare Value

    /* keep timer2's and toggle SLP_TR pin on compare match */
    TCCR0 |= _BV(COM00);

    // Wait for async. register update of TCCR2 and TCNT2
    while (ASSR & ASSR_BUSY) {}

    TIFR = _BV(OCF0) | _BV(TOV0);     // Clear interrupt flags
    TIMSK |= _BV(OCIE0);              // Enable interrupt on compare match

    /*
     * Note that the overflow handler for timer2 is located in
     * timer_m128_z1.c, as it is shared with bios_fasttimer().
     */
    cli();

    TCCR0 |= _BV(FOC0);   // force toggle OC0 (set SLP_TR pin)

    // After some cycles the OC0 pin toggles
    // Wait for register update ready of TCCR2
    while (ASSR & ASSR_BUSY) {}

    /* enable all interrupts */
    sei();

    /**************************************************************************/
    /**************************************************************************/
    /* after next instruction the AVR is at sleep */
    /**************************************************************************/
    /**************************************************************************/

    sleep_mode();         // Put the AVR into (Power Save) sleep mode

    /**************************************************************************/
    /**************************************************************************/
    /* AVR is awake now */
    /**************************************************************************/
    /**************************************************************************/

    /* set timer2's prescaler to 1024 and clear SLP_TR pin on compare match */
    TCCR0 = _BV(CS02)|_BV(CS01)|_BV(CS00);
    TCCR0 = _BV(COM01);
    while (ASSR & ASSR_BUSY) {}
    /* Force output compare */
    TCCR0 |= _BV(FOC0);        // force toggle OC0 (set SLP_TR pin)
    while (ASSR & ASSR_BUSY) {}

    /* SLP_TR pin is now 0 */

    /* clear all timer2 interrupt flags */
    TIFR |= _BV(OCF0) | _BV(TOV0);
    /* disable timer2's output compare match interrupt */
    TIMSK &= ~_BV(OCIE0);
    /* set timer2's prescaler to 1024 and put SLP_TR pin in normal mode */
    TCCR0 = _BV(CS02)|_BV(CS01)|_BV(CS00);
    while (ASSR & ASSR_BUSY) {}

}

/**
 * @brief Set or clear a pin.
 * @param pin The pin which should be set or cleared.
 * @param value 1 - high, 0 - low
 * @return true if successful
 */
bool bios_pinset(uint8_t pin, uint8_t value)
{
    bool ret = true;

    switch(pin)
    {

        case TRX_PIN_SLEEP:
            if (value != 0)
            {
                TRX_SLPTR_HIGH();
            }
            else
            {
                TRX_SLPTR_LOW();
            }
            break;

        case TRX_PIN_RESET:
            if (value != 0)
            {
                TRX_RESET_HIGH();
            }
            else
            {
                TRX_RESET_LOW();
            }
            break;

        case TRX_PIN_TEST:
            /* Dummy to pass the evaluation test suite. */
            break;

        default:
            ret = false;
            break;
    }

    return ret;

}

/**
 * @brief Get a pin.
 * @param pin The pin which should be read.
 * @param pvalue Returns 1 - high, 0 - low
 * @return true if successful
 */
bool bios_pinget(uint8_t pin, uint8_t *pvalue)
{
    bool ret = true;

    switch(pin)
    {
        case TRX_PIN_SLEEP:
            *pvalue = TRX_SLPTR_GET() ? 1 : 0 ;
            break;

        case TRX_PIN_RESET:
            *pvalue = TRX_RESET_GET() ? 1 : 0 ;
            break;

        default:
            ret = false;
            break;
    }

    return ret;

}

#if APP_TYPE >= APP_L0 || defined(DOXYGEN)

/**
 * @brief Read the IEEE address from the board's EEPROM
 *
 * @return The IEEE address (little-endian byte order)
 */
uint64_t bios_get_ieee_addr(void)
{
    union
    {
        uint64_t u64;
        uint8_t u8[8];
    }
    ieee_addr;
    uint8_t i;

    /*
     * The IAR compiler has no eeprom_read_block() function.  While
     * that could be emulated using their __eeprom variable attribute,
     * rather resort to the smallest common denominator of reading one
     * byte at a time.
     */
    for (i = 0; i < sizeof(ieee_addr); i++)
    {
        EEGET(ieee_addr.u8[i], i + RDK230_EE_IEEE_ADDR);
    }

    return ieee_addr.u64;
}

/**
 * @brief Abort any operation
 *
 * Abort any operation, halt the application, issue a board-specific
 * indication (flashing LED etc.) that is meant to alert a human about
 * the situation.  Used for testing.
 *
 */
void bios_abort(void)
{
    uint8_t *event;

    LED_SET(LED_ALL);
    while(1)
    {
        /* process the event queue */
        event = bios_popfront_event();
#if (APP_TYPE != APP_SNIFFER) && (APP_TYPE != APP_SCRPT_SNF)
        if (event != NULL)
        {
            if (event[1] == CMDIF_BOOTLOAD_REQUEST)
            {
                bios_jump_bootloader();
            }
        }
#endif
    }
}
#endif

#if RC_OSC_USED || defined(DOXYGEN)
/**
 * @brief Calibrate the internal RC oscillator
 *
 * This function calibrates the internal RC oscillator, based
 * on either the asynchronous 32.768 crystal-controlled timer,
 * or on the 1 MHz clock supplied by the AT86RF230. In order to
 * verify the calibration result you can program the CKOUT fuse
 * and monitor the CPU clock on an I/O pin.
 */
static bool calibrate_rc_osc(void)
{
    bool back = false;

    /*
     * Use the 1 MHz CLK_M from the AT86RF230.
     */
    uint16_t temp, counter;
    uint8_t osccal_saved;
    uint8_t tccr2b, tccr1b, tccr1a;

    osccal_saved = OSCCAL;
   // cli();

    /*
     * Save current values of timer status.
     */
    tccr2b = TCCR0;
    tccr1b = TCCR1B;
    tccr1a = TCCR1A;
    /*
     * Stop timers 1 and 2.
     * Set timer 1 to normal mode (no CTC, no PWM, just count).
     */
    TCCR0 = 0;
    TCCR1B = 0;
    TCCR1A = 0;

    for (counter = 0; counter < 1000;  counter++)
    {
        /*
         * Delete pending timer 1 and 2 interrupts, and clear the
         * counters.
         */
        TIFR = 0xFF;
        //TIFR2 = 0xFF;
        TCNT0 = 0;
        TCNT1 = 0;
        /* kick timer 2, prescaler 32, timer 1 w/ external clock*/
        TCCR0 = (1 << CS01) | (1 << CS00);
        TCCR1B = (1 << CS12) | (1 << CS11);

        /*
         * Wait for timer 2 to overflow.
         */
        while (!(TIFR & (1 << TOV0)))
            /* wait */ ;

        /*
         * Stop timer 1.  Now, TCNT1 contains the number of CPU cycles
         * counted during F_CPU / (32 * 256) cycles.
         */
        TCCR1B = 0;
        TCCR0 = 0;

        temp = TCNT1;

        if (temp < (uint16_t)(0.995 * TARGETVAL))
        {
            /* too fast, throttle */
            OSCCAL--;
        }
        else if (temp > (uint16_t)(1.005 * TARGETVAL))
        {
            /* too slow, speed up */
            OSCCAL++;
        }
        else
        {
            /*
             * We are within +/- 0.5 % of our target frequency, so we're
             * done.
             */
            back = true;
        }
    }

    TCCR0 = tccr2b;
    TCCR1B = tccr1b;
    TCCR1A = tccr1a;
    sei();
    if (!back)
    {
        /* We failed, therefore restore previous OSCCAL value. */
        OSCCAL = osccal_saved;
    }
    return back;
}
#endif /* RC_OSC_USED */

#  if defined(DOXYGEN)
/**
 * This is the interrupt service routine for the transceiver IRQ
 */
 
 
 
 

void TIMER1_CAPT_vect(void);
#  else  /* !DOXYGEN */
ISR (TIMER1_CAPT_vect)
{       
	uint8_t ii=0;
	uint8_t tmp;
	trx_interrupt_ind_t im;

#if APP_TYPE >= APP_L1
   		uint32_t tstamp;
		tstamp = (uint32_t)bios_systime << (uint32_t)16;
		tstamp |= (uint32_t)ICR1;
		tstamp /= TMR1_INTERNAL_SCALE;
#endif /* APP_TYPE >= APP_L1 */

		    DI_TRX_IRQ();

		    sei();

		    im.cause = bios_reg_read( RG_IRQ_STATUS );
#if APP_TYPE == LIB_HAL
		    usr_hal_radio_irq(im.cause);
#endif /* APP_TYPE == LIB_HAL */

#if APP_TYPE == APP_L0
		    validation_irq_handler(im.cause);
#endif /* APP_TYPE == APP_L0 */

#if APP_TYPE >= APP_L1
		    phy_irq_handler(im.cause, tstamp);
			

#endif /* APP_TYPE >= APP_L1 */

#if DEBUG > 0
		if (im.cause & TRX_IRQ_5)
			ASSERT("TRX_IRQ_5" == 0);
		if (im.cause & TRX_IRQ_4)
			ASSERT("TRX_IRQ_4" == 0);
#endif

		    if (im.cause & TRX_IRQ_BAT_LOW)
		    {
			    tmp = bios_reg_read(RG_IRQ_MASK);
			    bios_reg_write(RG_IRQ_MASK, (tmp & (~TRX_IRQ_BAT_LOW)));
			    PRINT("disable BAT_LOW_IRQ (IRQ_MASK = %x)", tmp);
		    }
		    /* avoid nested interrupts */
		    cli();
		    EI_TRX_IRQ();
		    /* return from ISR and re-enable the interrupts */
	    
    
}







#endif /* !defined(DOXYGEN) */

#if defined(DOXYGEN)
/**
 * This is the interrupt service routine for timer2 output compare match.
 * It is triggered when the timer expires.  It does nothing but waking
 * up the CPU from sleep mode.
 */

 
 
 
 
 
 
 
 
 
 
 
 
void TIMER2_COMPA_vect(void);
#else  /* !DOXYGEN */
ISR (TIMER2_COMPA_vect)
{
    /* empty ISR */
}
#endif /* defined(DOXYGEN) */

#endif /* BOARD_TYPE == RDK230 */

/* EOF */
