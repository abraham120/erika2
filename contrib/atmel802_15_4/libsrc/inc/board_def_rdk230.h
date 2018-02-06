/**
 * @file
 * \brief macros and defines AT86RF230 reference design kit.
 *
 * Not quite identical to EMU230, the hardware pinout differs.  The most
 * notable difference is the IRQ is routed to PD4 (ICP1), and the MCU
 * is an ATmega1281.
 *
 * $Id: board_def_rdk230.h,v 1.1 2007/06/22 13:50:48 romano Exp $
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

#ifndef BOARD_DEF_RDK230_H
#define BOARD_DEF_RDK230_H

/* === Includes ============================================================== */
#ifndef DEF_H
#include "def.h"
#endif

/** before we include avrtypes.h, we have to define F_CPU, because avrtypes.h
 * includes <util/delay.h> which needs F_CPU
 */
#define F_CPU                (8000000UL)

#include <stdbool.h>

#include "avrtypes.h"
#include "rf230.h"
#include "phy230_registermap.h"

/* === Externals ============================================================= */

/* === Types ================================================================= */

/* === Macros ================================================================ */
#define BOARD_NAME           "RDK230"  /** name of the board */

#define CPU_TYPE             M128     /** rdk230 use ATMega128 as controller */
#define RADIO_TYPE           AT86RF230  /** rdk230 use AT86RF230 as radio */
#define RF_BAND              BAND_2400  /** AT86RF230 operates in the 2.4GHz band */
#define RC_OSC_USED          true       /** enable code for internal oscillator */

#define XRAM_BASEADDR     (0)           /** rdk230 has no external RAM */
#define XRAM_SIZE         (0)           /** rdk230 has no external RAM */
#define XRAM_ENABLE()     XMCRA |= _BV(SRE); XMCRB = _BV(XMBK) /** XRAM enable */
#define XRAM_DISABLE()    XMCRA &= ~_BV(SRE)    /** XRAM disable */

/** watchdog disable */
#define WATCHDOG_DISABLE() {\
        wdt_reset(); \
        MCUCSR &= ~_BV(WDRF); \
        WDTCR = _BV(WDCE) | _BV(WDE); \
        WDTCR = 0; \
}

#define SYMBOL_PERIOD   (16)    /** symbol period in 2.4GHz-band is 16 us*/

/** the data rate of the radio in symbol periods per Byte */
#define RADIO_RATE_SP(x) (2 * x)

/** the data rate of the SPI in symbol periods per Byte */
#define SPI_RATE_SP(x) (x / 8)

#define TRX_RAM_SIZE     RF230_RAM_SIZE  /** RAM size of radio */

#define QUEUE_SIZE       (1*1024)   /**< size of the message queue */

/** initialize the interrupt of the transceiver */
#define INIT_TRX_IRQ() { TCCR1B |= _BV(ICES1); TIFR = _BV(ICF1); /* clear pending interrupt */}

/** disable the interrupt of the tranceiver */
#define DI_TRX_IRQ() { TIMSK &= ~_BV(TICIE1);}

/** enable the interrupt of the tranceiver */
#define EI_TRX_IRQ() { TIMSK |= _BV(TICIE1);}

/** mask for SLPTR pin */
#define TRX_SLPTR_MASK (0x10)

/** set the SLPTR pin high */
#define TRX_SLPTR_HIGH() (PORTB |= TRX_SLPTR_MASK)

/** set the SLPTR pin low */
#define TRX_SLPTR_LOW()  (PORTB &= ~TRX_SLPTR_MASK)

/** read the SLPTR pin */
#define TRX_SLPTR_GET()  (PINB & TRX_SLPTR_MASK)

/** mask for RESET pin */
#define TRX_RESET_MASK (0x20)

/** Initialize the RESET pin to become an output */
#define TRX_INIT_RESET_PIN() (DDRB  |= TRX_RESET_MASK)

/** Initialize the SLPTR pin to become an output */
#define TRX_INIT_SLPTR_PIN() (DDRB  |= TRX_SLPTR_MASK)

/** set the RESET pin high */
#define TRX_RESET_HIGH() (PORTB |= TRX_RESET_MASK)

/** set the RESET pin low */
#define TRX_RESET_LOW()  (PORTB &= ~TRX_RESET_MASK)

/** read the RESET pin */
#define TRX_RESET_GET()  (PINB & TRX_RESET_MASK)

    /** The maximum size of the timer queue */
#define MAX_TIMER_QUEUE_SIZE (32)

#define LED_D1  (_BV(2))
#define LED_D2  (_BV(3))
#define LED_D3  (_BV(4))
#define LED_ALL (LED_D1 | LED_D2 | LED_D3)

#define LED_PORT PORTE

#define LED_INIT() do \
{ \
                      PORTE = 0; \
                      DDRE = 0xff; \
} while (0)

#define LED_SET(led) do { (LED_PORT) |= (led); } while (0)
#define LED_CLR(led) do { (LED_PORT) &= ~(led); } while (0)

#define SPI_CFG_0 (_BV(SPE)  | _BV(MSTR) )

#define SPI_RATE_1_2      (4)
#define SPI_RATE_1_4      (0)
#define SPI_RATE_1_8      (5)
#define SPI_RATE_1_16     (1)
#define SPI_RATE_1_32     (6)
#define SPI_RATE_1_64     (2)
#define SPI_RATE_1_128    (3)

#define DDR_SPI  DDRB                   // SPI on PortB
#define PORT_SPI PORTB                  // SPI on PortB
#define SPI_SS   0                      // /SS on  PB0
#define SPI_MOSI 2                      // MOSI on PB2
#define SPI_MISO 3                      // MISI on PB3
#define SPI_SCK  1                      // SCK on PB1

#define SPI_SELN_LOW()       uint8_t sreg = SREG; cli(); PORTB &=~0x01
#define SPI_SELN_HIGH()      PORTB |= 0x01; SREG = sreg

#define SPI_WAITFOR() do { while ((SPSR & (1 << SPIF)) == 0) ; } while(0)

#if CTRL_IF == UART_NONE
# define HAS_USB         (0)
#elif CTRL_IF == UART1
  /* Use UART1 - default application uart */
# define HAS_USB         (0)
# define UDR UDR1
# define USART_RX_vect USART1_RX_vect
# define USART_TX_vect USART1_TX_vect
# define UBRRH UBRR1H
# define UBRRL UBRR1L
# define UCSRA UCSR1A
# define UCSRB UCSR1B
# define UCSRC UCSR1C
# define TXENx TXEN1
# define RXENx RXEN1
# define TXCx  TXC1
# define RXCx  RXC1
# define UCSRA_CFG UART_CFG0_A
#elif CTRL_IF == UART0
  /* Use UART0 - for debugging RDK230 */
# define HAS_USB         (0)
# define UDR UDR0
# define USART_RX_vect USART0_RX_vect
# define USART_TX_vect USART0_TX_vect
# define UBRRH UBRR0H
# define UBRRL UBRR0L
# define UCSRA UCSR0A
# define UCSRB UCSR0B
# define UCSRC UCSR0C
# define TXENx TXEN0
# define RXENx RXEN0
# define TXCx  TXC0
# define RXCx  RXC0
# define UCSRA_CFG UART_CFG0_A
#elif CTRL_IF == USB_FT245
# define HAS_USB         (1)
# define USB_PORT        PORTE
# define USB_DDR         DDRE
# define USB_PIN         PINE
# define USB_RXF         0x80  // PE7
# define USB_TXE         0x40  // PE6
# define USB_FIFO_AD     0xF000
#else
# error "Invalid CTRL_IF"
#endif
/*
 * With F_CPU = 4 MHz, and a prescaler of 64, timer1 runs exactly at
 * symbol rate.
 */
#if (F_CPU == (8000000UL))
#   if (RC_OSC_USED && APP_TYPE != APP_L0)
#      define TMR1_CFG_B ((1 << CS12) | (1 << CS11) | (1 << CS10))   // external clocking
#      define TMR1_INTERNAL_SCALE (16) /* post-scaling needed */
#      define TMR1_INTERNAL_MASK  (0x0fffffff)
#   else /* !RC_OSC_USED || APP_TYPE == APP_L0 */
#      define TMR1_CFG_B ((1 << CS11) | (1 << CS10)) /* pre-scaler 64 */
#      define TMR1_INTERNAL_SCALE (2) /* post-scaling needed */
#      define TMR1_INTERNAL_MASK  (0xefffffff)
#   endif /* RC_OSC_USED */
#elif (F_CPU == (1000000UL))
#   define TMR1_CFG_B (1 << CS11)
#   define TMR1_INTERNAL_SCALE (2) /* post-scaling needed */
#   define TMR1_INTERNAL_MASK       (0xefffffff)
#elif (F_CPU == (4000000UL))
#   define TMR1_CFG_B ((1 << CS11) | (1 << CS10))
#   define TMR1_INTERNAL_SCALE (1) /* no post-scaling needed */
#   define TMR1_INTERNAL_MASK       (0xffffffff)
#else
#   error "Unexpected F_CPU value"
#endif
/* Boot loader definitions */
#define BOOTADDR 0x1f800     /* byte address */

#define UART_BAUD_1MHz_4k8     25   // UPD:  0.2%
#define UART_BAUD_1MHz_9k6     12   // UPD:  0.2%
#define UART_BAUD_4MHz_9k6     51   // UPD:  0.2%
#define UART_BAUD_8MHz_9k6    103   // UPD:  0.2%

#if (F_CPU == (8000000UL))
#   define UART_BAUD_DEFAULT UART_BAUD_8MHz_9k6
#elif (F_CPU == (1000000UL))
#   define UART_BAUD_DEFAULT UART_BAUD_1MHz_9k6
#elif (F_CPU == (4000000UL))
#   define UART_BAUD_DEFAULT UART_BAUD_4MHz_9k6
#endif

#define UART_BUFFER_SIZE     (257)
/** The number of bytes that could be buffered for UART transmission. Its value
 *  should be a power of 2 for optimal controller usage. */
#define UART_TX_QUEUE_SIZE   (512)

/** A UART state that expects a \ref SOT to be received as the next character. */
#define UART_RX_STATE_SOT    (1)
/** A UART state that expects the length to be received as the next character. */
#define UART_RX_STATE_LENGTH (2)
/** A UART state that expects the next data character to be received. */
#define UART_RX_STATE_DATA   (3)
/** A UART state that expects a \ref EOT to be received as the next character. */
#define UART_RX_STATE_EOT    (4)

/** A UART state that expects a \ref SOT to be transmitted as the next character. */
#define UART_TX_STATE_SOT    (1)
/** A UART state that expects the length to be transmitted as the next character. */
#define UART_TX_STATE_LENGTH (2)
/** A UART state that expects the next data character to be transmitted. */
#define UART_TX_STATE_DATA   (3)
/** A UART state that expects a \ref EOT to be transmitted as the next character. */
#define UART_TX_STATE_EOT    (4)

#define UART_CFG0_A (_BV(U2X0))     // faster async mode (uart clock divider=8, instead of 16)
#define UART_CFG0_B (_BV(RXCIE0)|_BV(TXCIE0)|_BV(RXEN0)|_BV(TXEN0))
#define UART_CFG0_C (_BV(UCSZ01)|_BV(UCSZ00))




/* EEPROM layout */

#define RDK230_EE_IEEE_ADDR   (0) /**< IEEE address of board in EEPROM */

/* === Prototypes ============================================================ */

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*BOARD_DEF_RDK230_H*/
/* EOF */
