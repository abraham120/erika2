/** @file
 * @brief Compatibility definitions for compilers (IAR, GCC)
 *
 * This file contains AVR type definitions that enable Atmel's 802.15.4
 * contains compiler conditional subsystems for AVR functions such as:
 * interrupts, sleep mode, USARTs, etc.
 *
 * \note Before including avrtypes.h, \c F_CPU has to be defined,
 * because avrtypes.h includes <util/delay.h> (for AVR-GCC/avr-libc)
 * which needs \c F_CPU.  This is done by including board.h right 
 * before avrtypes.h.
 *
 * $Id: avrtypes.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE EXPRESSLY AND
 * SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef AVRTYPES_H
#define AVRTYPES_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

#include <stdlib.h>
#include <stdint.h>

/*
 * The if defined(__ICCAVR__) section below applies to the IAR compiler.
 */
#if defined(__ICCAVR__)

# include <ioavr.h>
# include <intrinsics.h>
# include <pgmspace.h>

/*
 * Map AVR names from IAR to GCC.
 */
# include "mcu_types.h"

/*
 * The elif defined(__GNUC__) section below applies to the GNUC compiler.
 */
#elif defined(__GNUC__)

# include <avr/io.h>
# include <avr/eeprom.h>
# include <avr/interrupt.h>
# include <avr/pgmspace.h>
# include <avr/sleep.h>
# include <avr/wdt.h>

# include <util/crc16.h>
# include <util/delay.h>

/*
 * The else section below applies to unsupported compiler. This is where support
 * for compilers other than IAR and GNUC would be placed.
 */
#else
# error Unsupported compiler
#endif /* compiler selection */


/* === Externals ============================================================= */

/* === Macros ================================================================ */

#ifndef _BV
/** bit value -- compute the bitmask for a bit position */
# define _BV(x) (1 << (x))
#endif

/** This macro saves the irq status and is typically used before cli(). */
#define save_irq_status() (sreg = SREG)
/** This macro must be used together with save_irq_status() and it will
restore the content of the irq status. */
#define restore_irq_status() (SREG = sreg)

/*
 * This block contains just the documentation for all
 * compiler-dependent macros.
 */
#if defined(DOXYGEN)

/** Start an interrupt handler for vector \c vec. */
#define ISR(vec)

/** Globally enable interrupts. */
#define sei()
/** Globally disable interrupts. */
#define cli()
/** Read contents of EEPROM cell \c addr into variable \c var. */
#define EEGET(var, addr)
/** Null operation: just waste one CPU cycle. */
#define nop()
/** Clear (i.e. reset to 0) the watchdog timer. */
#define wdt_reset()

/** Put the CPU to sleep, according to the sleep mode selected with \c set_sleep_mode. */
#define sleep_mode()
/** Enter idle sleep mode: turn off the CPU, but keep all clocks running. */
#define SLEEP_MODE_IDLE
/** Stop the CPU but keep the ADC running. */
#define SLEEP_MODE_ADC
/** Stop the CPU and all oscillators. */
#define SLEEP_MODE_PWR_DOWN
/** Stop the CPU and all oscillators but the asynchronous one. */
#define SLEEP_MODE_PWR_SAVE
/** Stop the CPU but keep the external oscillator running. */
#define SLEEP_MODE_STANDBY
/** Like power-save mode but keep the external oscillator running. */
#define SLEEP_MODE_EXT_STANDBY
/** All sleep mode bits. */
#define SLEEP_MODE_MASK
/** Set the sleep mode to enter upon the next \c sleep_mode call. */
#define set_sleep_mode(x)

/* program memory space abstraction */
/** Declare object \c x to be placed into flash ROM. */
#define FLASH_DECLARE(x)
/** Declare string \c x to be placed into flash ROM. */
#define FLASH_STRING(x)
/** Type of a string that is located in flash ROM. */
#define FLASH_STRING_T
/** Read one byte at address \c x from flash ROM. */
#define PGM_READ_BYTE(x)
/** Read two bytes at address \c x from flash ROM. */
#define PGM_READ_WORD(x)
/** Read a block of \c len bytes at address \c src from flash ROM to RAM address \c dst. */
#define PGM_READ_BLOCK(dst, src, len)
/** Determine the string length of a string locatend in flash ROM at address \c x. */
#define PGM_STRLEN(x)
/** Copy a string from flash ROM at address \c src to RAM address \c dst. */
#define PGM_STRCPY(dst, src)
/** Set to one if the compilation environment supports a vsnprintf_P() function
 *  (like vsnprintf() but with the format string in flash ROM). */
#define HAS_PGM_VSNPRINTF
/** Define the function to use for printing a string with the format string in
 *  flash ROM, parameters are similar to vsnprintf(). */
#define PGM_VSNPRINTF(dst, n, fmt, ap)
/** Define this to the percent format specifier used to indicate a string that
 *  is located in flash ROM rather than in RAM.  Do not define this macro if
 *  the compilation environment does not support taking arguments from flash
 *  ROM in printf()-like functions. */
#define PRINTF_FLASH_STRING

/** Update the 16-bit CCITT \c crc from the next \c data byte, returning
 *  the new CRC. */
#define CRC_CCITT_UPDATE(crc, data)

/** Attribute to apply to struct tags in order to force it into an 8-bit
 *  alignment. */
#define ALIGN8BIT

/** Attribute to apply to an enum declaration to force it into the smallest
 *  type size required to represent all values. */
#define SHORTENUM

/** The name of a low-level initialization function that is run before
 *  initializing main(). */
#define ENABLE_XRAM(void)

/** The return value to be returned by ENABLE_XRAM(), if any. */
#define RETURN_ENABLE_XRAM

/**
   Perform a delay of \c us microseconds.

   The macro F_CPU is supposed to be defined to a
   constant defining the CPU clock frequency (in Hertz).

   The maximal possible delay is 262.14 ms / F_CPU in MHz.

   \note For the IAR compiler, currently F_CPU must be a
   multiple of 1000000UL (1 MHz).
 */
extern void delay_us(double us);

#endif /* defined(DOXYGEN) */


#if defined(__ICCAVR__)

/*
 * Map interrupt vectors.
 */
#if defined(__ATmega128__)
/*
 * ATmega128 vector names are misspelled wrt. the data sheets and XML
 * files.  Map them to their canonical names.
 */
#  define USART0_RX_vect USART0_RXC_vect
#  define USART0_TX_vect USART0_TXC_vect
#  define USART1_RX_vect USART1_RXC_vect
#  define USART1_TX_vect USART1_TXC_vect
#endif /* defined(__ATmega128__) */


/*
 * Some preprocessor magic to allow for a header file abstraction of
 * interrupt service routine declarations for the IAR compiler.  This
 * requires the use of the C99 _Pragma() directive (rather than the
 * old #pragma one that could not be used as a macro replacement), as
 * well as two different levels of preprocessor concetanations in
 * order to do both, assign the correct interrupt vector name, as well
 * as construct a unique function name for the ISR.
 *
 * Do *NOT* try to reorder the macros below, or you'll suddenly find
 * out about all kinds of IAR bugs...
 */
#define PRAGMA(x) _Pragma( #x )
#define ISR(vec) PRAGMA( vector=vec ) __interrupt void handler_##vec(void)

#define sei() __enable_interrupt()
#define cli() __disable_interrupt()
#define EEGET(var, addr) __EEGET(var, addr)
#define nop() __no_operation()
#define wdt_reset() __watchdog_reset()

#define sleep_mode() do { MCUCR |= (1 << SE); __sleep(); MCUCR &= ~(1 << SE); } while (0)
#define SLEEP_MODE_IDLE         0
#define SLEEP_MODE_ADC          (1 << SM0)
#define SLEEP_MODE_PWR_DOWN     (1 << SM1)
#define SLEEP_MODE_PWR_SAVE     ((1 << SM0) | (1 << SM1))
#define SLEEP_MODE_STANDBY      ((1 << SM1) | (1 << SM2))
#define SLEEP_MODE_EXT_STANDBY  ((1 << SM0) | (1 << SM1) | (1 << SM2))
#define SLEEP_MODE_MASK         ((1 << SM0) | (1 << SM1) | (1 << SM2))
#define set_sleep_mode(x) do { MCUCR = (MCUCR & ~SLEEP_MODE_MASK) | (x); } while (0)

/* program memory space abstraction */
#define FLASH_DECLARE(x) __flash x
#define FLASH_STRING(x) ((__flash const char *)(x))
#define FLASH_STRING_T  char const __flash *
#define PGM_READ_BYTE(x) *(x)
#define PGM_READ_WORD(x) *(x)
#define PGM_READ_BLOCK(dst, src, len) memcpy_P((dst), (src), (len))
#define PGM_STRLEN(x) strlen_P(x)
#define PGM_STRCPY(dst, src) strcpy_P((dst), (src))
/* IAR has no vsnprintf_P(), and no %S format. */
#define HAS_PGM_VSNPRINTF 0
#define PGM_VSNPRINTF(dst, n, fmt, ap) vsnprintf((dst), (n), (fmt), (ap))
#undef PRINTF_FLASH_STRING

#define CRC_CCITT_UPDATE(crc, data) crc_ccitt_update(crc, data)

#define ALIGN8BIT /**/
#define SHORTENUM /**/

#define ENABLE_XRAM(void) \
char __low_level_init(void)
#define RETURN_ENABLE_XRAM return 1

#define delay_us(us)   __delay_cycles((F_CPU/1000000UL) * us)

#endif /* defined(__ICCAVR__) */

#if defined(__GNUC__)

#define nop() do { __asm__ __volatile__ ("nop"); } while (0)
#define CRC_CCITT_UPDATE(crc, data) _crc_ccitt_update(crc, data)
#define EEGET(var, addr) (var) = eeprom_read_byte ((uint8_t *)(addr))
#define ALIGN8BIT /* AVR-GCC uses an 8-bit alignment anyway */
#define SHORTENUM __attribute__ ((packed))

/* program memory space abstraction */
#define FLASH_DECLARE(x) const x __attribute__((__progmem__))
#define FLASH_STRING(x) PSTR(x)
#define FLASH_STRING_T  PGM_P
#define PGM_READ_BYTE(x) pgm_read_byte(x)
#define PGM_READ_WORD(x) pgm_read_word(x)
#define PGM_READ_BLOCK(dst, src, len) memcpy_P((dst), (src), (len))
#define PGM_STRLEN(x) strlen_P(x)
#define PGM_STRCPY(dst, src) strcpy_P((dst), (src))
/* avr-libc has vsnprintf_P(), and %S. */
#define HAS_PGM_VSNPRINTF 1
#define PGM_VSNPRINTF(dst, n, fmt, ap) vsnprintf_P((dst), (n), (fmt), (ap))
#define PRINTF_FLASH_STRING "%S"

#define ENABLE_XRAM(void) \
void xram_init(void) __attribute__((naked)) __attribute((section(".init3")));\
void xram_init(void)
#define RETURN_ENABLE_XRAM /**/

#endif /* defined(__GNUC__) */


/* === Types ================================================================= */

/* === Prototypes ============================================================ */

#if defined(__GNUC__)
static inline void delay_us(double us) __attribute__((always_inline));
static inline void
delay_us(double us)
{
    /*
     * If us is sufficiently low to be handled by _delay_loop_1(),
     * use this one as it is more accurate for small values.
     *
     * Math behind it: divide F_CPU by the number of clock ticks
     * per _delay_loop_N cycle (3 or 4 ticks per cycle), and by
     * 1E6 to accomodate for the microsecond scaling.
     */
    if (F_CPU / 3E6 * us < 255)
    {
        uint8_t ticks8 = F_CPU / 3E6 * us;

        _delay_loop_1(ticks8);
    }
    else
    {
        uint16_t ticks16 = F_CPU / 4E6 * us;

        _delay_loop_2(ticks16);
    }
}
#endif /* defined(__GNUC__) */

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__ICCAVR__)
/* Internal helper function for CRC_CCITT_UPDATE. */
uint16_t crc_ccitt_update (uint16_t crc, uint8_t data);
#endif /* __ICCAVR__ */

#ifdef cplusplus
} /* extern "C" */
#endif


#endif /* AVRTYPES_H */
/* EOF */
