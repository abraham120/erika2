/**
* @file mrf24j40_hal_ee_dspic.h
* @brief MRF24J40 Hw Abstraction Layer using Erika OS over Microchip dsPIC
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the MRF24J40 library which uses the Erika kernel drivers.
*
* \todo Write something about the hal support.
*/

// TODO: Check radio pins.

#ifndef __mrf24j40_hal_ee_dspic_h__
#define __mrf24j40_hal_ee_dspic_h__

#ifndef __USE_SPI__
#error "MRF24J40 HAL EE : The SPI module from MCU is required!"
#endif

#include <mcu/microchip_dspic/inc/ee_spi.h>
#include <cpu/pic30/inc/ee_irqstub.h>

#define MRF24J40_SPI_PORT_1	EE_SPI_PORT_1
#define MRF24J40_SPI_PORT_2	EE_SPI_PORT_2

#ifndef MRF24J40_RESETn

#if defined (__EE_MOODLIGHT_BRD__)
#define MRF24J40_RESETn	PORTGbits.RG13
#elif defined (__EE_USB2SSI_BRD__)
#define MRF24J40_RESETn	PORTCbits.RC13
#elif defined (__EE_MINIFLEX__)
#define MRF24J40_RESETn	PORTAbits.RA7
#else
#define MRF24J40_RESETn	PORTGbits.RG0
#endif

#endif

#if !defined(__EE_MINIFLEX__) && !defined(__EE_MOODLIGHT_BRD__) && !defined(__EE_USB2SSI_BRD__)

#ifndef MRF24J40_VREG_EN
#define MRF24J40_VREG_EN	PORTGbits.RG12
#endif

#endif


#ifndef MRF24J40_FIFO

//#ifndef __EE_MINIFLEX__

#if defined (__USE_DEMOBOARD__) || defined (__USE_MOTIONBOARD__)	/* Demoboard defaults */
#define MRF24J40_FIFO		PORTDbits.RD14
#else				/* Gianluca's board default*/
#define MRF24J40_FIFO		PORTEbits.RE9
#endif

//#endif

#endif

#ifndef MRF24J40_FIFOP
#ifndef __EE_MINIFLEX__
#if defined (__USE_DEMOBOARD__) || defined (__USE_MOTIONBOARD__) /* Demoboard defaults */
#define MRF24J40_FIFOP		PORTAbits.RA15
#else				/* Gianluca's board default*/
#define MRF24J40_FIFOP		PORTFbits.RF6
#endif
#else
#define MRF24J40_FIFOP		PORTBbits.RB7 //Miniflex conf.
#endif
#endif

#ifndef MRF24J40_CSn

#if defined (__EE_MOODLIGHT_BRD__)
#define MRF24J40_CSn	PORTGbits.RG15
#elif defined (__EE_USB2SSI_BRD__)
#define MRF24J40_CSn	PORTFbits.RF12
#elif defined (__EE_MINIFLEX__)
#define MRF24J40_CSn	PORTCbits.RC4
#else
#define MRF24J40_CSn	PORTGbits.RG9
#endif

#endif

#ifndef MRF24J40_TRIS_RESETn

#if defined (__EE_MOODLIGHT_BRD__)
#define MRF24J40_TRIS_RESETn	TRISGbits.TRISG13
#elif defined (__EE_USB2SSI_BRD__)
#define MRF24J40_TRIS_RESETn	TRISCbits.TRISC13
#elif defined (__EE_MINIFLEX__)
#define MRF24J40_TRIS_RESETn	TRISAbits.TRISA7
#else
#define MRF24J40_TRIS_RESETn	TRISGbits.TRISG0
#endif

#endif

#ifndef MRF24J40_TRIS_VREG_EN
#if !defined(__EE_MINIFLEX__) && !defined(__EE_MOODLIGHT_BRD__) && !defined(__EE_USB2SSI_BRD__)
#define MRF24J40_TRIS_VREG_EN	TRISGbits.TRISG12
#endif
#endif

#ifndef MRF24J40_TRIS_FIFO
#ifndef __EE_MINIFLEX__
#if defined (__USE_DEMOBOARD__) || defined (__USE_MOTIONBOARD__)	/* Demoboard defaults */
#define MRF24J40_TRIS_FIFO	TRISDbits.TRISD14
#else				/* Gianluca's board default*/
#define MRF24J40_TRIS_FIFO	TRISEbits.TRISE9
#endif
#endif
#endif

#ifndef MRF24J40_TRIS_FIFOP
#ifndef __EE_MINIFLEX__
#if defined (__USE_DEMOBOARD__) || defined (__USE_MOTIONBOARD__) /* Demoboard defaults */
#define MRF24J40_TRIS_FIFOP	TRISAbits.TRISA15
#else				/* Gianluca's board default*/
#define MRF24J40_TRIS_FIFOP	TRISFbits.TRISF6
#endif
#else	/* MiniFlex board default*/
#define MRF24J40_TRIS_FIFOP	TRISBbits.TRISB7
#endif
#endif

#ifndef MRF24J40_TRIS_INTERRUPT_PIN

#if defined (__EE_MOODLIGHT_BRD__) || defined (__EE_USB2SSI_BRD__)
#define MRF24J40_TRIS_INTERRUPT_PIN TRISDbits.TRISD0
#endif

#endif

#ifndef MRF24J40_TRIS_CSn

#if defined (__EE_MOODLIGHT_BRD__)
#define MRF24J40_TRIS_CSn	TRISGbits.TRISG15
#elif defined (__EE_USB2SSI_BRD__)
#define MRF24J40_TRIS_CSn	TRISFbits.TRISF12
#elif defined (__EE_MINIFLEX__)
#define MRF24J40_TRIS_CSn	TRISCbits.TRISC4
#else
#define MRF24J40_TRIS_CSn	TRISGbits.TRISG9
#endif

#endif

#if defined (__USE_DEMOBOARD__) //|| defined (__USE_MOTIONBOARD__) /* Demoboard defaults */

#ifndef MRF24J40_INTERRUPT_NAME
#define MRF24J40_INTERRUPT_NAME	_INT4Interrupt
#endif

#ifndef MRF24J40_INTERRUPT_FLAG
#define MRF24J40_INTERRUPT_FLAG	IFS3bits.INT4IF
#endif

#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE IEC3bits.INT4IE
#endif

#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY IPC13bits.INT4IP
#endif

#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT4EP
#endif

#endif

#if defined (__USE_MOTIONBOARD__)

#ifndef MRF24J40_INTERRUPT_NAME
#define MRF24J40_INTERRUPT_NAME	_IC8Interrupt
#endif

#ifndef MRF24J40_INTERRUPT_FLAG
#define MRF24J40_INTERRUPT_FLAG	IFS1bits.IC8IF
#endif

#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE IEC1bits.IC8IE
#endif

#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY IPC5bits.IC8IP
#endif
/*
#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT4EP
#endif
*/
#endif


#if defined (__EE_MOODLIGHT_BRD__) || defined (__EE_USB2SSI_BRD__)

#ifndef MRF24J40_INTERRUPT_NAME
#define MRF24J40_INTERRUPT_NAME	_INT0Interrupt
#endif

#ifndef MRF24J40_INTERRUPT_FLAG
#define MRF24J40_INTERRUPT_FLAG	IFS0bits.INT0IF
#endif

#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE IEC0bits.INT0IE
#endif

#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY IPC0bits.INT0IP
#endif

#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT0EP
#endif

#endif


//#else /* Gianluca's board and MiniFlex default*/
#if defined (__EE_MINIFLEX__) || (!defined (__USE_DEMOBOARD__) && !defined (__USE_MOTIONBOARD__))
#ifndef MRF24J40_INTERRUPT_NAME
#define MRF24J40_INTERRUPT_NAME	_INT0Interrupt
#endif

#ifndef MRF24J40_INTERRUPT_FLAG
#define MRF24J40_INTERRUPT_FLAG	IFS0bits.INT0IF
#endif

#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE IEC0bits.INT0IE
#endif

#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY IPC0bits.INT0IP
#endif

#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT0EP
#endif

#endif	
/* End default booard selection for ISR */

#define MRF24J40_HAL_ISR() ISR2(MRF24J40_INTERRUPT_NAME)

int8_t	mrf24j40_hal_init(void);
void	mrf24j40_hal_delay_us(uint16_t delay_count);
int8_t	mrf24j40_hal_spi_init(uint8_t port);
int8_t	mrf24j40_hal_spi_close(void);
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);

COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
{
	MRF24J40_RESETn = 1;
}

COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
{
	MRF24J40_RESETn = 0;
}

COMPILER_INLINE void mrf24j40_hal_csn_high(void)
{
	MRF24J40_CSn = 1;
}

COMPILER_INLINE void mrf24j40_hal_csn_low(void)
{
	MRF24J40_CSn = 0;
}

COMPILER_INLINE void mrf24j40_hal_irq_clean(void)
{
	MRF24J40_INTERRUPT_FLAG = 0;
}

COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	MRF24J40_INTERRUPT_ENABLE = 1;
}

COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	MRF24J40_INTERRUPT_ENABLE = 0;
}

COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return MRF24J40_INTERRUPT_ENABLE;
}


#endif /* Header Protection */
