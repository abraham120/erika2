/**
* @file cc2420_hal_.h
* @brief CC2420 Hw Abstraction Layer using Erika OS
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the definition of the hardware abstraction layer used by all the module
* of the CC2420 library which uses the Erika kernel drivers.
*
* \todo Write something about the hal support.
*/
#ifndef __cc2420_hal_ee_h__
#define __cc2420_hal_ee_h__

#if defined __MICROCHIP_DSPIC30__

#ifndef __USE_SPI__
#error "CC2420 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/microchip_dspic/inc/ee_spi.h>

#define CC2420_SPI_PORT_1	EE_SPI_PORT_1
#define CC2420_SPI_PORT_2	EE_SPI_PORT_2

#ifndef CC2420_RESETn
#define CC2420_RESETn		PORTGbits.RG0
#endif

#ifndef CC2420_VREG_EN
#define CC2420_VREG_EN		PORTGbits.RG12
#endif

/*******************************************************************************
                      OLD Gianluca's Board configuration                    

#define CC2420_FIFO		PORTEbits.RE9
#define CC2420_FIFOP		PORTFbits.RF6
#define CC2420_TRIS_FIFO	TRISEbits.TRISE9
#define CC2420_TRIS_FIFOP	TRISFbits.TRISF6

#ifndef CC2420_INTERRUPT_NAME
#define CC2420_INTERRUPT_NAME	_INT0Interrupt
#endif

#ifndef CC2420_INTERRUPT_FLAG
#define CC2420_INTERRUPT_FLAG	IFS0bits.INT0IF
#endif

#ifndef CC2420_INTERRUPT_ENABLE
#define CC2420_INTERRUPT_ENABLE IEC0bits.INT0IE
#endif

#ifndef CC2420_INTERRUPT_PRIORITY
#define CC2420_INTERRUPT_PRIORITY IPC0bits.INT0IP
#endif

#ifndef CC2420_INTERRUPT_EDGE_POLARITY
#define CC2420_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT0EP
#endif

*******************************************************************************/


#ifndef CC2420_FIFO
#define CC2420_FIFO		PORTDbits.RD14
#endif

#ifndef CC2420_FIFOP
#define CC2420_FIFOP		PORTAbits.RA15
#endif

#ifndef CC2420_CCA
#define CC2420_CCA	PORTGbits.RG1
#endif

#ifndef CC2420_SFD
#define CC2420_SFD	PORTDbits.RD13
#endif

/* TODO: TEMP solution adopted for EUROLAB 2009! */
#ifdef __USE_MOTIONBOARD__
#define CC2420_CSn		PORTBbits.RB2
#else
#ifndef CC2420_CSn
#define CC2420_CSn		PORTGbits.RG9
#endif
#endif

#ifndef CC2420_TRIS_RESETn
#define CC2420_TRIS_RESETn	TRISGbits.TRISG0
#endif

#ifndef CC2420_TRIS_VREG_EN
#define CC2420_TRIS_VREG_EN	TRISGbits.TRISG12
#endif

#ifndef CC2420_TRIS_FIFO
#define CC2420_TRIS_FIFO	TRISDbits.TRISD14
#endif

#ifndef CC2420_TRIS_FIFOP
#define CC2420_TRIS_FIFOP	TRISAbits.TRISA15
#endif

#ifndef CC2420_TRIS_CCA
#define CC2420_TRIS_CCA	TRISGbits.TRISG1
#endif

#ifndef CC2420_TRIS_SFD
#define CC2420_TRIS_SFD	TRISDbits.TRISD13
#endif

/* TODO: TEMP solution adopted for EUROLAB 2009! */
#ifdef __USE_MOTIONBOARD__
#define CC2420_TRIS_CSn		TRISBbits.TRISB2
#else
#ifndef CC2420_TRIS_CSn
#define CC2420_TRIS_CSn		TRISGbits.TRISG9
#endif
#endif


#ifndef CC2420_INTERRUPT_NAME
#define CC2420_INTERRUPT_NAME	_INT4Interrupt
#endif

#ifndef CC2420_INTERRUPT_FLAG
#define CC2420_INTERRUPT_FLAG	IFS3bits.INT4IF
#endif

#ifndef CC2420_INTERRUPT_ENABLE
#define CC2420_INTERRUPT_ENABLE IEC3bits.INT4IE
#endif

#ifndef CC2420_INTERRUPT_PRIORITY
#define CC2420_INTERRUPT_PRIORITY IPC13bits.INT4IP
#endif

#ifndef CC2420_INTERRUPT_EDGE_POLARITY
#define CC2420_INTERRUPT_EDGE_POLARITY	 INTCON2bits.INT4EP
#endif

#define CC2420_SET_PIN_IN(PIN) {\
    DSPIC_PIN = 1;\
}

#define CC2420_SET_PIN_OUT(PIN) (DSPIC_PIN = 0)

#define CC2420_SET_INT_POL_HIGHT() (CC2420_INTERRUPT_EDGE_POLARITY = 0)

#define CC2420_SET_INT_POL_LOW() (CC2420_INTERRUPT_EDGE_POLARITY = 1)

#define CC2420_SET_PIN(PIN) ((PIN) = 1)

#define CC2420_CLEAR_PIN(PIN) ((PIN) = 0)

#define CC2420_GET_PIN(PIN) (PIN)

int8_t	cc2420_hal_init(void);
void	cc2420_delay_us(uint16_t delay_count);
int8_t	cc2420_spi_init(uint8_t port);
int8_t	cc2420_spi_close(void);
int8_t	cc2420_spi_put(uint8_t in, uint8_t *out);
int8_t	cc2420_spi_get(uint8_t *out);

COMPILER_INLINE uint8_t cc2420_get_cca(void)
{
	return CC2420_CCA;
}

COMPILER_INLINE uint8_t cc2420_get_sfd(void)
{
	return CC2420_SFD;
}

// TODO: (Nino) Check avr5 or atmega128?
#elif defined __AVR5__

#ifndef __USE_SPI__
#error "CC2420 HAL EE : The SPI module from MCU is required!"
#endif
#include <mcu/atmel_atmega128/inc/ee_spi.h>
#include <mcu/atmel_atmega128/inc/ee_mcuregs.h>
#define CC2420_SPI_PORT_1	EE_SPI_PORT_1
#define CC2420_SPI_PORT_2	EE_SPI_PORT_2

// TODO: (Nino) Change from pic30 to avr5
#ifdef __XBOW_MIB5X0__ // XBOW_MICAz

#ifndef CC2420_RESETn_AVR_PORT
#define CC2420_RESETn_AVR_PORT	PORTA
#endif

#ifndef CC2420_RESETn_AVR_PIN
#define CC2420_RESETn_AVR_PIN	PA6
#endif

#ifndef CC2420_VREG_EN_AVR_PORT
#define CC2420_VREG_EN_AVR_PORT	PORTA
#endif

#ifndef CC2420_VREG_EN_AVR_PIN
#define CC2420_VREG_EN_AVR_PIN	PA5 
#endif

#ifndef CC2420_FIFO_AVR_PORT
#define CC2420_FIFO_AVR_PORT	PORTB
#endif

#ifndef CC2420_FIFO_AVR_PIN
#define CC2420_FIFO_AVR_PIN	PB7
#endif

#ifndef CC2420_FIFOP_AVR_PORT
#define CC2420_FIFOP_AVR_PORT	PORTE
#endif

#ifndef CC2420_FIFOP_AVR_PIN
#define CC2420_FIFOP_AVR_PIN	PE6
#endif

#ifndef CC2420_CCA_AVR_PORT
#define CC2420_CCA_AVR_PORT	PORTD
#endif

#ifndef CC2420_CCA_AVR_PIN
#define CC2420_CCA_AVR_PIN	PD6
#endif

#ifndef CC2420_SFD_AVR_PORT
#define CC2420_SFD_AVR_PORT	PORTD
#endif

#ifndef CC2420_SFD_AVR_PIN
#define CC2420_SFD_AVR_PIN	PD4
#endif

#ifndef CC2420_CSn_AVR_PORT
#define CC2420_CSn_AVR_PORT	PORTB
#endif

#ifndef CC2420_CSn_AVR_PIN
#define CC2420_CSn_AVR_PIN	PB0
#endif

#ifndef CC2420_TRIS_RESETn_AVR_PORT
#define CC2420_TRIS_RESETn_AVR_PORT	DDRA
#endif

#ifndef CC2420_TRIS_RESETn_AVR_PIN
#define CC2420_TRIS_RESETn_AVR_PIN	DDA6
#endif

#ifndef CC2420_TRIS_VREG_EN_AVR_PORT
#define CC2420_TRIS_VREG_EN_AVR_PORT	DDRA
#endif

#ifndef CC2420_TRIS_VREG_EN_AVR_PIN
#define CC2420_TRIS_VREG_EN_AVR_PIN	DDA5
#endif

#ifndef CC2420_TRIS_FIFO_AVR_PORT
#define CC2420_TRIS_FIFO_AVR_PORT	DDRB
#endif

#ifndef CC2420_TRIS_FIFO_AVR_PIN
#define CC2420_TRIS_FIFO_AVR_PIN	DDB7
#endif

#ifndef CC2420_TRIS_FIFOP_AVR_PORT
#define CC2420_TRIS_FIFOP_AVR_PORT	DDRE
#endif

#ifndef CC2420_TRIS_FIFOP_AVR_PIN
#define CC2420_TRIS_FIFOP_AVR_PIN	DDE6
#endif

#ifndef CC2420_TRIS_CCA_AVR_PORT
#define CC2420_TRIS_CCA_AVR_PORT	DDRD
#endif

#ifndef CC2420_TRIS_CCA_AVR_PIN
#define CC2420_TRIS_CCA_AVR_PIN	DDD6
#endif

#ifndef CC2420_TRIS_SFD_AVR_PORT
#define CC2420_TRIS_SFD_AVR_PORT	DDRD
#endif

#ifndef CC2420_TRIS_SFD_AVR_PIN
#define CC2420_TRIS_SFD_AVR_PIN	DDD4
#endif

#ifndef CC2420_TRIS_CSn_AVR_PORT
#define CC2420_TRIS_CSn_AVR_PORT	DDRB
#endif

#ifndef CC2420_TRIS_CSn_AVR_PIN
#define CC2420_TRIS_CSn_AVR_PIN	DDB0
#endif

#ifndef CC2420_INTERRUPT_NAME
#define CC2420_INTERRUPT_NAME	INT6_vect
#endif

#ifndef CC2420_INTERRUPT_FLAG_AVR_PORT
#define CC2420_INTERRUPT_FLAG_AVR_PORT	EIFR
#endif

#ifndef CC2420_INTERRUPT_FLAG_AVR_PIN
#define CC2420_INTERRUPT_FLAG_AVR_PIN	INTF6
#endif

#ifndef CC2420_INTERRUPT_ENABLE_AVR_PORT
#define CC2420_INTERRUPT_ENABLE_AVR_PORT EIMSK
#endif

#ifndef CC2420_INTERRUPT_ENABLE_AVR_PIN
#define CC2420_INTERRUPT_ENABLE_AVR_PIN INT6
#endif


#ifndef CC2420_INTERRUPT_EDGE_POLARITY_AVR_PORT
#define CC2420_INTERRUPT_EDGE_POLARITY_AVR_PORT	 EICRB
#endif
/*
#ifndef CC2420_INTERRUPT_EDGE_POLARITY
#define CC2420_INTERRUPT_EDGE_POLARITY	 //INTCON2bits.INT4EP
#endif
*/
#define CC2420_SET_PIN_IN(PIN) {\
	(*(volatile uint8_t*)(PIN##_AVR_PORT)) &= ~(1<< PIN##_AVR_PIN);\
}

#define CC2420_SET_PIN_OUT(PIN) {\
	(*(volatile uint8_t*)(PIN##_AVR_PORT)) |= (1<< PIN##_AVR_PIN);\
}

#define CC2420_SET_INT_POL_HIGHT() {\
	EE_reg(CC2420_INTERRUPT_EDGE_POLARITY_AVR_PORT) |= 0x30;\
}

#define CC2420_SET_INT_POL_LOW() {\
	EE_reg(CC2420_INTERRUPT_EDGE_POLARITY_AVR_PORT) |= 0x20;\
}

#define CC2420_SET_PIN(PIN) {\
	(*(volatile uint8_t*)(PIN##_AVR_PORT)) |= (1<<PIN##_AVR_PIN);\
	}
#define CC2420_CLEAR_PIN(PIN) {\
	(*(volatile uint8_t*)(PIN##_AVR_PORT)) &= ~(1<<PIN##_AVR_PIN);\
	}

#define CC2420_GET_PIN(PIN)	(((*(volatile uint8_t*)(PIN##_AVR_PORT)) >> PIN##_AVR_PIN) & 0x01)

#endif // End  XBOW_MICAz

int8_t	cc2420_hal_init(void);
void	cc2420_delay_us(uint16_t delay_count);
int8_t	cc2420_spi_init(uint8_t port);
int8_t	cc2420_spi_close(void);
int8_t	cc2420_spi_put(uint8_t in, uint8_t *out);
int8_t	cc2420_spi_get(uint8_t *out);

COMPILER_INLINE uint8_t cc2420_get_cca(void)
{
#ifdef __AVR5__
	return 1; // FIXME: make this work properly!
#else
	return (CC2420_CCA_AVR_PORT & (1 << CC2420_CCA_AVR_PIN)) >> CC2420_CCA_AVR_PIN;
#endif
}

COMPILER_INLINE uint8_t cc2420_get_sfd(void)
{
	return (CC2420_SFD_AVR_PORT & (1 << CC2420_SFD_AVR_PIN)) >> CC2420_SFD_AVR_PIN ;
}

#ifndef CC2420_INTERRUPT_NAME
#define CC2420_INTERRUPT_NAME	irq_cc2420_type2
#endif

/* Discovery board feautiring STM32F407 */
#elif defined __USE_STM32F4_DISCOVERY__

#include "stm32f4xx.h"


#ifndef __USE_STM32F4XX_SPD_SPI__
#error "CC2420 HAL EE : The SPI module from MCU is required!"
#endif

#ifndef __USE_STM32F4XX_SPD_EXTI__
#error "CC2420 HAL EE : The SPI EXTI driver is required!"
#endif

#ifndef __USE_STM32F4XX_SPD_GPIO__
#error "CC2420 HAL EE : The SPI GPIO driver is required!"
#endif

#define CC2420_SPI_PORT_1	1
#define CC2420_SPI_PORT_2	2
#define CC2420_SPI_PORT_3	3


#ifndef CC2420_RESETn_STM_PORT
#define CC2420_RESETn_STM_PORT	GPIOB
#endif

#ifndef CC2420_RESETn_STM_PIN
#define CC2420_RESETn_STM_PIN	GPIO_Pin_5
#endif

#ifndef RCC_AHB1Periph_CC2420_RESETn_STM
#define RCC_AHB1Periph_CC2420_RESETn_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef CC2420_VREG_EN_STM_PORT
#define CC2420_VREG_EN_STM_PORT	GPIOB
#endif

#ifndef CC2420_VREG_EN_STM_PIN
#define CC2420_VREG_EN_STM_PIN	GPIO_Pin_1 
#endif

#ifndef RCC_AHB1Periph_CC2420_VREG_EN_STM
#define RCC_AHB1Periph_CC2420_VREG_EN_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef CC2420_FIFO_STM_PORT
#define CC2420_FIFO_STM_PORT	GPIOB
#endif

#ifndef CC2420_FIFO_STM_PIN
#define CC2420_FIFO_STM_PIN		GPIO_Pin_14
#endif

#ifndef RCC_AHB1Periph_CC2420_FIFO_STM
#define RCC_AHB1Periph_CC2420_FIFO_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef CC2420_FIFOP_STM_PORT
#define CC2420_FIFOP_STM_PORT	GPIOB
#endif

#ifndef CC2420_FIFOP_STM_PIN
#define CC2420_FIFOP_STM_PIN	GPIO_Pin_4
#endif

#ifndef RCC_AHB1Periph_CC2420_FIFOP_STM
#define RCC_AHB1Periph_CC2420_FIFOP_STM	RCC_AHB1Periph_GPIOB
#endif

/* Note: the interrupt line should be coupled with FIFOP pin number. 
 If for instance FIFOP -> PB4 then use EXTI4, 
 if FIFOP -> PC5 then use EXTI5 etc..
 */

#ifndef CC2420_INTERRUPT_LINE
#define CC2420_INTERRUPT_LINE	EXTI_Line4
#endif

#ifndef CC2420_INTERRUPT_SRC
#define CC2420_INTERRUPT_SRC	EXTI_PinSource4
#endif

#ifndef EXTI_PortSource_CC2420_FIFOP_STM_PORT
#define EXTI_PortSource_CC2420_FIFOP_STM_PORT	EXTI_PortSourceGPIOB
#endif

#ifndef CC2420_CCA_STM_PORT
#define CC2420_CCA_STM_PORT	GPIOD
#endif

#ifndef CC2420_CCA_STM_PIN
#define CC2420_CCA_STM_PIN	GPIO_Pin_1
#endif

#ifndef RCC_AHB1Periph_CC2420_CCA_STM
#define RCC_AHB1Periph_CC2420_CCA_STM	RCC_AHB1Periph_GPIOD
#endif

#ifndef CC2420_SFD_STM_PORT
#define CC2420_SFD_STM_PORT	GPIOA
#endif

#ifndef CC2420_SFD_STM_PIN
#define CC2420_SFD_STM_PIN	GPIO_Pin_5
#endif

#ifndef RCC_AHB1Periph_CC2420_SFD_STM
#define RCC_AHB1Periph_CC2420_SFD_STM	RCC_AHB1Periph_GPIOA
#endif

#ifndef CC2420_CSn_STM_PORT
#define CC2420_CSn_STM_PORT	GPIOB
#endif

#ifndef CC2420_CSn_STM_PIN
#define CC2420_CSn_STM_PIN	GPIO_Pin_0
#endif

#ifndef RCC_AHB1Periph_CC2420_CSn_STM
#define RCC_AHB1Periph_CC2420_CSn_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef CC2420_SDO_STM_PORT
#define CC2420_SDO_STM_PORT	GPIOC
#endif

#ifndef CC2420_SDO_STM_PIN
#define CC2420_SDO_STM_PIN	GPIO_Pin_2
#endif

#ifndef RCC_AHB1Periph_CC2420_SDO_STM
#define RCC_AHB1Periph_CC2420_SDO_STM	RCC_AHB1Periph_GPIOC
#endif

#ifndef CC2420_SDO_STM_PIN_SRC
#define CC2420_SDO_STM_PIN_SRC	GPIO_PinSource2
#endif

#ifndef CC2420_SDI_STM_PORT
#define CC2420_SDI_STM_PORT	GPIOC
#endif

#ifndef CC2420_SDI_STM_PIN
#define CC2420_SDI_STM_PIN	GPIO_Pin_3
#endif

#ifndef RCC_AHB1Periph_CC2420_SDI_STM
#define RCC_AHB1Periph_CC2420_SDI_STM	RCC_AHB1Periph_GPIOC
#endif

#ifndef CC2420_SDI_STM_PIN_SRC
#define CC2420_SDI_STM_PIN_SRC	GPIO_PinSource3
#endif

#ifndef CC2420_SCK_STM_PORT
#define CC2420_SCK_STM_PORT	GPIOB
#endif

#ifndef CC2420_SCK_STM_PIN
#define CC2420_SCK_STM_PIN	GPIO_Pin_10
#endif

#ifndef RCC_AHB1Periph_CC2420_SCK_STM
#define RCC_AHB1Periph_CC2420_SCK_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef CC2420_SCK_STM_PIN_SRC
#define CC2420_SCK_STM_PIN_SRC	GPIO_PinSource10
#endif

#define CC2420_SET_PIN_IN(PIN) do {\
	/*Enable PORT clock */\
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_##PIN##_STM, ENABLE);\
	GPIO_InitStructure.GPIO_Pin = PIN##_STM_PIN;\
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;\
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;\
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;\
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
	GPIO_Init(PIN##_STM_PORT, &GPIO_InitStructure);\
} while(0)

#define CC2420_SET_PIN_OUT(PIN) do {\
	/* Enable PORT clock */\
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_##PIN##_STM, ENABLE);\
	GPIO_InitStructure.GPIO_Pin = PIN##_STM_PIN;\
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;\
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;\
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;\
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
	GPIO_Init(PIN##_STM_PORT, &GPIO_InitStructure);\
} while(0)



#define CC2420_SET_PIN(PIN) {\
	GPIO_SetBits(PIN##_STM_PORT, PIN##_STM_PIN);\
}

#define CC2420_CLEAR_PIN(PIN) {\
	GPIO_ResetBits(PIN##_STM_PORT, PIN##_STM_PIN);\
}

#define CC2420_GET_PIN(PIN)	\
	GPIO_ReadInputDataBit(PIN##_STM_PORT, PIN##_STM_PIN)


#define CC2420_SET_ISR_RE() do {\
	/* Enable SYSCFG clock */\
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);\
	/* Configure FIFOP as input floating */\
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;\
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
	GPIO_InitStructure.GPIO_Pin = CC2420_FIFOP_STM_PIN;\
	GPIO_Init(CC2420_FIFOP_STM_PORT, &GPIO_InitStructure);\
	/* Connect EXTI Line0 to FIFOP pin */\
	SYSCFG_EXTILineConfig(EXTI_PortSource##_CC2420_FIFOP_STM_PORT,\
				CC2420_INTERRUPT_SRC);\
	/* Configure EXTI Line */\
	EXTI_InitStructure.EXTI_Line = CC2420_INTERRUPT_LINE;\
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;\
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;\
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;\
	EXTI_Init(&EXTI_InitStructure);\
} while(0)

#define CC2420_CLEAR_ISR(INT_LINE) do {\
	if (EXTI_GetITStatus(INT_LINE) != RESET) {\
	/* Clear the EXTI line pending bit */\
		EXTI_ClearITPendingBit(INT_LINE);\
	}\
} while(0)


int8_t	cc2420_hal_init(void);
void	cc2420_delay_us(uint16_t delay_count);
int8_t	cc2420_spi_init(uint8_t port);
int8_t	cc2420_spi_close(void);
int8_t	cc2420_spi_put(uint8_t in, uint8_t *out);
int8_t	cc2420_spi_get(uint8_t *out);

COMPILER_INLINE uint8_t cc2420_get_cca(void)
{
	return CC2420_GET_PIN(CC2420_CCA);
}

COMPILER_INLINE uint8_t cc2420_get_sfd(void)
{
	return CC2420_GET_PIN(CC2420_SFD);
}


#else

#error "CC2420_HAL: Architecture not supported!"

#endif

#endif /* Header Protection */
