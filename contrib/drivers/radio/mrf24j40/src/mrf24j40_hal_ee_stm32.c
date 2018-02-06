/**
* @file mrf24j40_hal_ee_stm32.c
* @brief MRF24J40 Hw Abstraction Layer using Erika OS over microchip dsPIC
* @author Gianluca Franchino
* @date 2013-10-08
*
* This file is the  hardware abstraction layer used by all the module
* of the MRF24J40 library which uses the Erika kernel drivers.
*
* \todo Write something about the hal support.
*/
#include <mrf24j40_hal.h>

#ifdef __STM32__



//static uint16_t temp_count = 0;

void mrf24j40_hal_delay_us( uint16_t delay_count )
{
	/*
	temp_count = delay_count +1;
	asm volatile("outer: dec _temp_count");
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");

	#ifdef __EE_MINIFLEX__ // Fcy=16MHz, Tcy =62,5 ns 
	asm volatile("mov #600, w0");
	asm volatile("inner: dec w0, w0");
	asm volatile("cp0 w0");
	asm volatile("bra nz, inner");
	#else
	asm volatile("do #1500, inner" );
	asm volatile("nop");
	asm volatile("inner: nop");
	#endif

	asm volatile("bra outer");
	asm volatile("done:");
	 */
	
	/*
	 *FIXME: write the correct version
	 */
	volatile uint16_t i;
	i=0;
	while (++i < 30000);
}



int8_t	mrf24j40_hal_init(void)
{
	/* Structure used by MRF24J40_SET_PIN_OUT() and MRF24J40_SET_PIN_IN(). */
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Structure used by MRF24J40_SET_ISR_RE() to initialize ext. interr. pins.*/
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	/* Set the IO pins direction */ 
	MRF24J40_SET_PIN_OUT(MRF24J40_RESETn);
	MRF24J40_SET_PIN_OUT(MRF24J40_VREG_EN);
	MRF24J40_SET_PIN_OUT(MRF24J40_WAKEUP);
	MRF24J40_SET_PIN_OUT(MRF24J40_CSn);
	
	/* Set interrupt with rising edge mode.*/
	MRF24J40_SET_ISR_RE();
	
	
	return 1;
}


static SPI_TypeDef * spi_port;

int8_t	mrf24j40_hal_spi_init(uint8_t port)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	if (port == MRF24J40_SPI_PORT_1) {
		/* Enable the SPI periph */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		port = GPIO_AF_SPI1;
		spi_port = SPI1;
	} else if (port == MRF24J40_SPI_PORT_2) {
		/* Enable the SPI periph */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		port = GPIO_AF_SPI2;
		spi_port = SPI2;
	} else if (port == MRF24J40_SPI_PORT_3) {
		/* Enable the SPI periph */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
		port = GPIO_AF_SPI3;
		spi_port = SPI3;
	} else {
		return -1;
	}
	
	/* Enable SCK, SDI, SDO and SCK GPIO clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_MRF24J40_SCK_STM|
						   RCC_AHB1Periph_MRF24J40_SDI_STM |
						   RCC_AHB1Periph_MRF24J40_SDO_STM, ENABLE);
	
	GPIO_PinAFConfig(MRF24J40_SCK_STM_PORT, MRF24J40_SCK_STM_PIN_SRC, port);
	GPIO_PinAFConfig(MRF24J40_SDI_STM_PORT, MRF24J40_SDI_STM_PIN_SRC, port);
	GPIO_PinAFConfig(MRF24J40_SDO_STM_PORT, MRF24J40_SDO_STM_PIN_SRC, port);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = MRF24J40_SCK_STM_PIN;
	GPIO_Init(MRF24J40_SCK_STM_PORT, &GPIO_InitStructure);
	
	/* SPI  SDO pin configuration */
	GPIO_InitStructure.GPIO_Pin =  MRF24J40_SDO_STM_PIN;
	GPIO_Init(MRF24J40_SDO_STM_PORT, &GPIO_InitStructure);
	
	/* SPI MISO pin configuration */
	GPIO_InitStructure.GPIO_Pin = MRF24J40_SDI_STM_PIN;
	GPIO_Init(MRF24J40_SDO_STM_PORT, &GPIO_InitStructure);
	
	/* SPI configuration -------------------------------------------------------*/
	SPI_I2S_DeInit(spi_port);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	/* 
	 *	Note, this configuration assumes:
	 *	HCLK = 168000000 Hz,
	 *	APB1 Prescaler = 4,
	 *	APB2 Prescaler = 2.
	 *	It means that the clock for baudrate generation (fPCLK) is 42 MHz for 
	 *	SPI1 and 84 MHz for SPI2 and SPI3. 
	 *	The SPI clock freq. is:
	 *					fSCK = fPCLK/SPI_InitStructure.SPI_BaudRatePrescaler,
	 *	thus for SPI1 fSCK = 42 / 16 = 2.625 MHz. For SPI2 and SPI3 
	 *	fSCK = 84 / 32 = 2.625 MHz.
	 */
	if (spi_port == SPI1)
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	else
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	//SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	
	SPI_Init(spi_port, &SPI_InitStructure);
	/* Enable spi_port  */
	SPI_Cmd(spi_port, ENABLE);
	
	return 0;
}

int8_t	mrf24j40_spi_close(void)
{
	SPI_I2S_DeInit(spi_port);
	
	/* Disable SCK, SDI, SDO and SCK GPIO clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_MRF24J40_SCK_STM |
						   RCC_AHB1Periph_MRF24J40_SDI_STM |
						   RCC_AHB1Periph_MRF24J40_SDO_STM, DISABLE);
	return 0;
}

int8_t	mrf24j40_hal_spi_write(uint8_t *data, uint16_t len)
{
	
	uint16_t i;

	for (i = 0; i < len; i++) {
		/* Wait until the end of an ongoing transmission. */
		while (SPI_I2S_GetFlagStatus(spi_port, SPI_I2S_FLAG_TXE) == RESET); 
		//SPI_I2S_SendData(spi_port, (uint16_t) data[i]);
		SPI_I2S_SendData(spi_port, (uint16_t) 0xAA);
	}
	
	return 1;
}

int8_t	mrf24j40_hal_spi_read(uint8_t *data, uint16_t len)
{
	uint16_t i;

	for (i = 0; i < len; i++) {
		/* Wait until the end of an ongoing transmission. */
		//while (SPI_I2S_GetFlagStatus(spi_port, SPI_I2S_FLAG_TXE) == RESET); 
		SPI_I2S_SendData(spi_port, 0x0000);
		while (SPI_I2S_GetFlagStatus(spi_port, SPI_I2S_FLAG_RXNE) == RESET); 
		data[i] = (uint8_t) SPI_I2S_ReceiveData(spi_port);
	}
	return 1;
}

#else

#error "MRF24J40_HAL: Architecture not supported!"

#endif
