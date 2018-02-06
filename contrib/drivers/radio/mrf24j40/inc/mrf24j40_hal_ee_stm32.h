/**
* @file mrf24j40_hal_ee_stm32.h
* @brief MRF24J40 Hw Abstraction Layer using Erika OS over ST Microel. STM32
* @author Gianluca Franchino
* @date 2013-10-07
*
* This file is the definition of the hardware abstraction layer used by all the 
* module of the MRF24J40 library which uses the Erika kernel drivers.
*
* \todo Write something about the hal support.
*/

// TODO: Check radio pins.

#ifndef __mrf24j40_hal_ee_stm32_h__
#define __mrf24j40_hal_ee_stm32_h__

#include "stm32f4xx.h"

#ifndef __USE_STM32F4XX_SPD_SPI__
#error "MRF24J40 HAL EE : The SPI module from MCU is required!"
#endif

#ifndef __USE_STM32F4XX_SPD_EXTI__
#error "MRF24J40 HAL EE : The SPI EXTI driver is required!"
#endif

#ifndef __USE_STM32F4XX_SPD_GPIO__
#error "MRF24J40 HAL EE : The SPI GPIO driver is required!"
#endif

#define MRF24J40_SPI_PORT_1	1
#define MRF24J40_SPI_PORT_2	2
#define MRF24J40_SPI_PORT_3	3

#ifndef MRF24J40_RESETn_STM_PORT
#define MRF24J40_RESETn_STM_PORT	GPIOB
#endif

#ifndef MRF24J40_RESETn_STM_PIN
#define MRF24J40_RESETn_STM_PIN	GPIO_Pin_5
#endif

#ifndef RCC_AHB1Periph_MRF24J40_RESETn_STM
#define RCC_AHB1Periph_MRF24J40_RESETn_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef MRF24J40_WAKEUP_STM_PORT
#define MRF24J40_WAKEUP_STM_PORT	GPIOB
#endif

#ifndef MRF24J40_WAKEUP_STM_PIN
#define MRF24J40_WAKEUP_STM_PIN	GPIO_Pin_1
#endif

#ifndef RCC_AHB1Periph_MRF24J40_WAKEUP_STM
#define RCC_AHB1Periph_MRF24J40_WAKEUP_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef MRF24J40_CSn_STM_PORT
#define MRF24J40_CSn_STM_PORT	GPIOB
#endif

#ifndef MRF24J40_CSn_STM_PIN
#define MRF24J40_CSn_STM_PIN	GPIO_Pin_0
#endif

#ifndef RCC_AHB1Periph_MRF24J40_CSn_STM
#define RCC_AHB1Periph_MRF24J40_CSn_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef MRF24J40_VREG_EN_STM_PORT
#define MRF24J40_VREG_EN_STM_PORT	GPIOB
#endif

#ifndef MRF24J40_VREG_EN_STM_PIN
#define MRF24J40_VREG_EN_STM_PIN	GPIO_Pin_1 
#endif

#ifndef RCC_AHB1Periph_MRF24J40_VREG_EN_STM
#define RCC_AHB1Periph_MRF24J40_VREG_EN_STM	RCC_AHB1Periph_GPIOB
#endif
	
#ifndef MRF24J40_SDO_STM_PORT
#define MRF24J40_SDO_STM_PORT	GPIOC
#endif

#ifndef MRF24J40_SDO_STM_PIN
#define MRF24J40_SDO_STM_PIN	GPIO_Pin_2
#endif

#ifndef RCC_AHB1Periph_MRF24J40_SDO_STM
#define RCC_AHB1Periph_MRF24J40_SDO_STM	RCC_AHB1Periph_GPIOC
#endif

#ifndef MRF24J40_SDO_STM_PIN_SRC
#define MRF24J40_SDO_STM_PIN_SRC	GPIO_PinSource2
#endif

#ifndef MRF24J40_SDI_STM_PORT
#define MRF24J40_SDI_STM_PORT	GPIOC
#endif

#ifndef MRF24J40_SDI_STM_PIN
#define MRF24J40_SDI_STM_PIN	GPIO_Pin_3
#endif

#ifndef RCC_AHB1Periph_MRF24J40_SDI_STM
#define RCC_AHB1Periph_MRF24J40_SDI_STM	RCC_AHB1Periph_GPIOC
#endif

#ifndef MRF24J40_SDI_STM_PIN_SRC
#define MRF24J40_SDI_STM_PIN_SRC	GPIO_PinSource3
#endif

#ifndef MRF24J40_SCK_STM_PORT
#define MRF24J40_SCK_STM_PORT	GPIOB
#endif

#ifndef MRF24J40_SCK_STM_PIN
#define MRF24J40_SCK_STM_PIN	GPIO_Pin_10
#endif

#ifndef RCC_AHB1Periph_MRF24J40_SCK_STM
#define RCC_AHB1Periph_MRF24J40_SCK_STM	RCC_AHB1Periph_GPIOB
#endif

#ifndef MRF24J40_SCK_STM_PIN_SRC
#define MRF24J40_SCK_STM_PIN_SRC	GPIO_PinSource10
#endif


/* Note: the interrupt line should be coupled withpin number. 
 * If for instance we use PB4 then the interrupt source is EXTI4, 
 * if PC5 then use EXTI5 etc..
 * Pins available as interrupt pin are: PB4, PB14 and PA5. 
 */

#ifndef MRF24J40_INTERRUPT_STM_PORT
#define MRF24J40_INTERRUPT_STM_PORT	GPIOB
#endif

#ifndef MRF24J40_INTERRUPT_STM_PIN
#define MRF24J40_INTERRUPT_STM_PIN	GPIO_Pin_4
#endif

#ifndef RCC_AHB1Periph_MRF24J40_STM_INTERRUPT
#define RCC_AHB1Periph_MRF24J40_STMINTERRUPT	RCC_AHB1Periph_GPIOB
#endif

#ifndef MRF24J40_INTERRUPT_STM_LINE
#define MRF24J40_INTERRUPT_STM_LINE	EXTI_Line4
#endif

#ifndef MRF24J40_INTERRUPT_STM_SRC
#define MRF24J40_INTERRUPT_STM_SRC	EXTI_PinSource4
#endif

#ifndef EXTI_PortSource_MRF24J40_INT_STM_PORT
#define EXTI_PortSource_MRF24J40_INT_STM_PORT	EXTI_PortSourceGPIOB
#endif

#define MRF24J40_SET_PIN_IN(PIN) do {\
/*Enable PORT clock */\
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_##PIN##_STM, ENABLE);\
GPIO_InitStructure.GPIO_Pin = PIN##_STM_PIN;\
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;\
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;\
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;\
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
GPIO_Init(PIN##_STM_PORT, &GPIO_InitStructure);\
} while(0)

#define MRF24J40_SET_PIN_OUT(PIN) do {\
/* Enable PORT clock */\
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_##PIN##_STM, ENABLE);\
GPIO_InitStructure.GPIO_Pin = PIN##_STM_PIN;\
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;\
GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;\
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;\
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
GPIO_Init(PIN##_STM_PORT, &GPIO_InitStructure);\
} while(0)



#define MRF24J40_SET_PIN(PIN) {\
GPIO_SetBits(PIN##_STM_PORT, PIN##_STM_PIN);\
}

#define MRF24J40_CLEAR_PIN(PIN) {\
GPIO_ResetBits(PIN##_STM_PORT, PIN##_STM_PIN);\
}

#define MRF24J40_GET_PIN(PIN)	\
GPIO_ReadInputDataBit(PIN##_STM_PORT, PIN##_STM_PIN)

#ifdef INT_POLARITY_HIGH

#define MRF24J40_INT_STM_TRIGGER EXTI_Trigger_Rising
#else
#define MRF24J40_INT_STM_TRIGGER EXTI_Trigger_Falling
#endif

#define MRF24J40_SET_ISR_RE() do {\
/* Enable SYSCFG clock */\
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);\
/* Configure INT pin as input floating */\
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;\
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\
GPIO_InitStructure.GPIO_Pin = MRF24J40_INTERRUPT_STM_PIN;\
GPIO_Init(MRF24J40_INTERRUPT_STM_PORT, &GPIO_InitStructure);\
/* Connect EXTI Line0 to FIFOP pin */\
SYSCFG_EXTILineConfig(EXTI_PortSource_MRF24J40_INT_STM_PORT,\
MRF24J40_INTERRUPT_STM_SRC);\
/* Configure EXTI Line */\
EXTI_InitStructure.EXTI_Line = MRF24J40_INTERRUPT_STM_LINE;\
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;\
EXTI_InitStructure.EXTI_Trigger = MRF24J40_INT_STM_TRIGGER;\
EXTI_InitStructure.EXTI_LineCmd = ENABLE;\
EXTI_Init(&EXTI_InitStructure);\
} while(0)

#define MRF24J40_CLEAR_ISR(INT_LINE) do {\
if (EXTI_GetITStatus(INT_LINE) != RESET) {\
	/* Clear the EXTI line pending bit */\
		EXTI_ClearITPendingBit(INT_LINE);\
	}\
} while(0)


#define MRF24J40_HAL_ISR() ISR2(MRF24J40_INTERRUPT_NAME)

int8_t	mrf24j40_hal_init(void);
void	mrf24j40_hal_delay_us(uint16_t delay_count);
int8_t	mrf24j40_hal_spi_init(uint8_t port);
int8_t	mrf24j40_hal_spi_close(void);
int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len);
int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len);

COMPILER_INLINE void mrf24j40_hal_retsetn_high(void)
{
	MRF24J40_SET_PIN(MRF24J40_RESETn);
}

COMPILER_INLINE void mrf24j40_hal_retsetn_low(void)
{
	MRF24J40_CLEAR_PIN(MRF24J40_RESETn);
}

COMPILER_INLINE void mrf24j40_hal_csn_high(void)
{
	MRF24J40_SET_PIN(MRF24J40_CSn);
}

COMPILER_INLINE void mrf24j40_hal_csn_low(void)
{
	MRF24J40_CLEAR_PIN(MRF24J40_CSn);
}

COMPILER_INLINE void mrf24j40_hal_irq_clean(void)
{
	MRF24J40_CLEAR_ISR(MRF24J40_INTERRUPT_STM_LINE);
}

COMPILER_INLINE void mrf24j40_hal_irq_enable(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = MRF24J40_INTERRUPT_STM_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

COMPILER_INLINE void mrf24j40_hal_irq_disable(void)
{
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line = MRF24J40_INTERRUPT_STM_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_LineCmd = DISABLE;
	EXTI_Init(&EXTI_InitStructure);
}

COMPILER_INLINE uint8_t mrf24j40_hal_irq_status(void)
{
	return EXTI_GetITStatus(MRF24J40_INTERRUPT_STM_LINE);
}


#endif /* Header Protection */
