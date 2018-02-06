/**
* @file cc2420_hal_.c
* @brief CC2420 Hw Abstraction Layer using Erika OS
* @author Gianluca Franchino
* @author Christian Nastasi
* @author Mauro Nino Marinoni
* @date 2009-03-24
*
* This file is the  hardware abstraction layer used by all the module
* of the CC2420 library which uses the Erika kernel drivers.
*
* \todo Write something about the hal support.
*/
#include <cc2420_hal.h>

#if defined __MICROCHIP_DSPIC30__

static uint16_t temp_count COMPILER_ATTRIBUTE_NEAR = 0;

void cc2420_delay_us( uint16_t delay_count )
{
	temp_count = delay_count + 1;
	asm volatile("outer: dec _temp_count");
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");
	asm volatile("do #1500, inner" );
	asm volatile("nop");
	asm volatile("inner: nop");
	asm volatile("bra outer");
	asm volatile("done:");
}

int8_t	cc2420_hal_init(void)
{
	/* Set the IO pins direction */
	CC2420_TRIS_RESETn = 0;
	CC2420_TRIS_VREG_EN = 0;
	CC2420_TRIS_FIFO = 1;
	CC2420_TRIS_FIFOP = 1;
	CC2420_TRIS_CCA = 1;
	CC2420_TRIS_CSn = 0;
	/* Set interrupt registers */
/* TODO: TEMP solution adopted for EUROLAB 2009! */
#ifdef __USE_MOTIONBOARD__
	TRISDbits.TRISD15 = 1; 
	CNEN2bits.CN21IE =1; //RFIEC20 = 1; INT on CN20
	IFS1bits.CNIF = 0; //RFIF = 0;
	IEC1bits.CNIE = 1; //RFIE = 1;
#else
	CC2420_INTERRUPT_FLAG = 0;
	CC2420_INTERRUPT_PRIORITY = 1;
	CC2420_INTERRUPT_EDGE_POLARITY = 0;
	CC2420_INTERRUPT_ENABLE = 1;
#endif /* __USE_MOTIONBOARD__ */
	return 1;
}

static uint8_t spi_port;

int8_t	cc2420_spi_init(uint8_t port)
{
	spi_port = port;
	return EE_spi_init(spi_port);
}

int8_t	cc2420_spi_close(void)
{
	return EE_spi_close(spi_port);
}

int8_t	cc2420_spi_put(uint8_t in, uint8_t *out)
{
	if (out != NULL)
		return EE_spi_rw_byte(spi_port, in, out);
	else
		return EE_spi_write_byte(spi_port, in);
}

int8_t	cc2420_spi_get(uint8_t *out)
{
	uint8_t dummy;

	if (out != NULL)
		return EE_spi_read_byte(spi_port, out);
	else
		return EE_spi_read_byte(spi_port, &dummy);
}

#elif defined __AVR5__

static uint16_t temp_count = 0;

// TODO: (Nino) Change to AVR5
void cc2420_delay_us( uint16_t delay_count )
{
	/*
	temp_count = delay_count +1;
	asm volatile("outer: dec _temp_count");
	asm volatile("cp0 _temp_count");
	asm volatile("bra z, done");
	asm volatile("do #1500, inner" );
	asm volatile("nop");
	asm volatile("inner: nop");
	asm volatile("bra outer");
	asm volatile("done:");
	*/
	volatile uint16_t i;
	i=0;
	while (++i < 10000);
}

// TODO: (Nino) Change to AVR5
int8_t	cc2420_hal_init(void)
{
	
	/* Set the IO pins direction */
	//CC2420_CLEAR_PIN(CC2420_TRIS_RESETn); //CC2420_TRIS_RESETn = 0;
	//CC2420_CLEAR_PIN(CC2420_TRIS_VREG_EN); //CC2420_TRIS_VREG_EN = 0;
	CC2420_SET_PIN_OUT(CC2420_TRIS_RESETn); //CC2420_TRIS_RESETn = 0;
	CC2420_SET_PIN_OUT(CC2420_TRIS_VREG_EN); //CC2420_TRIS_VREG_EN = 0;
	CC2420_SET_PIN_IN(CC2420_TRIS_FIFOP); //CC2420_TRIS_FIFOP = 1;
	CC2420_SET_PIN_IN(CC2420_TRIS_FIFO); //CC2420_TRIS_FIFO = 1;
	CC2420_SET_PIN_IN(CC2420_TRIS_CCA); //CC2420_TRIS_CCA = 1;
	//CC2420_SET_PIN_IN(CC2420_TRIS_SFD); //CC2420_TRIS_CCA = 1;
	CC2420_SET_PIN_OUT(CC2420_TRIS_CSn);//CC2420_TRIS_CSn = 0;
	
	/* Set interrupt registers */
	//C2420_CLEAR_PIN(CC2420_INTERRUPT_FLAG); //CC2420_INTERRUPT_FLAG = 0;	
	(*(volatile uint8_t*)(CC2420_INTERRUPT_FLAG_AVR_PORT)) &= 
	~(1<<CC2420_INTERRUPT_FLAG_AVR_PIN);
	
#ifdef __MICROCHIP_DSPIC30__
	CC2420_INTERRUPT_PRIORITY = 1;
#endif
	CC2420_SET_INT_POL_HIGHT(); //Rising edge 
	//CC2420_SET_INT_POL_LOW(); //Falling edge
	CC2420_SET_PIN(CC2420_INTERRUPT_ENABLE); //CC2420_INTERRUPT_ENABLE = 1;
	
	return 1;
}

//static uint8_t spi_port;

int8_t	cc2420_spi_init(uint8_t port)
{
	//spi_port = port;
	return EE_spi_init();
}

int8_t	cc2420_spi_close(void)
{
	return EE_spi_close();
}

int8_t	cc2420_spi_put(uint8_t in, uint8_t *out)
{
	if (out != NULL)
		return EE_spi_rw_byte(in, out);
	else
		return EE_spi_write_byte(in);
}

int8_t	cc2420_spi_get(uint8_t *out)
{
	uint8_t dummy;

	if (out != NULL)
		return EE_spi_read_byte(out);
	else
		return EE_spi_read_byte(&dummy);
}

/*******************************************************************************/
/*  STM32 Discovery board.													   */
/*******************************************************************************/

#elif defined __STM32__


void cc2420_delay_us( uint16_t delay_count )
{

	volatile uint16_t i;
	
	i=0;
	
	while (++i < 10000);
}



int8_t	cc2420_hal_init(void)
{
	/* Structure used by CC2420_SET_PIN_OUT() and CC2420_SET_PIN_IN(). */
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Structure used by CC2420_SET_ISR_RE() to initialize ext. interr. pins.*/
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	/* Set the IO pins direction */ 
	CC2420_SET_PIN_OUT(CC2420_RESETn);
	CC2420_SET_PIN_OUT(CC2420_VREG_EN);
	CC2420_SET_PIN_IN(CC2420_FIFOP);
	CC2420_SET_PIN_IN(CC2420_FIFO);
	/* FIXME: With the current version of the CC2420 module, the CCA pin is shared with a LCD pin, so
	  we cannot enable this pin when using the LCD of DM-STF4BB board.*/
#ifndef __NOT_USE_CC2420_CCA_PIN__	
	CC2420_SET_PIN_IN(CC2420_CCA);
#endif
#ifndef __NOT_USE_CC2420_SFD_PIN__	
	CC2420_SET_PIN_IN(CC2420_SFD);
#endif	
	CC2420_SET_PIN_OUT(CC2420_CSn);
	
	/* Set interrupt with rising edge mode.*/
	CC2420_SET_ISR_RE();
	

	return 1;
}


static SPI_TypeDef * spi_port;

int8_t	cc2420_spi_init(uint8_t port)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
	
	if (port == CC2420_SPI_PORT_1) {
		/* Enable the SPI periph */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		port = GPIO_AF_SPI1;
		spi_port = SPI1;
	} else if (port == CC2420_SPI_PORT_2) {
		/* Enable the SPI periph */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		port = GPIO_AF_SPI2;
		spi_port = SPI2;
	} else if (port == CC2420_SPI_PORT_3) {
		/* Enable the SPI periph */
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
		port = GPIO_AF_SPI3;
		spi_port = SPI3;
	} else {
		return -1;
	}


	
	/* Enable SCK, SDI, SDO and SCK GPIO clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CC2420_SCK_STM|
						   RCC_AHB1Periph_CC2420_SDI_STM |
						   RCC_AHB1Periph_CC2420_SDO_STM, ENABLE);
	
	GPIO_PinAFConfig(CC2420_SCK_STM_PORT, CC2420_SCK_STM_PIN_SRC, port);
	GPIO_PinAFConfig(CC2420_SDI_STM_PORT, CC2420_SDI_STM_PIN_SRC, port);
	GPIO_PinAFConfig(CC2420_SDO_STM_PORT, CC2420_SDO_STM_PIN_SRC, port);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	/* SPI SCK pin configuration */
	GPIO_InitStructure.GPIO_Pin = CC2420_SCK_STM_PIN;
	GPIO_Init(CC2420_SCK_STM_PORT, &GPIO_InitStructure);
	
	/* SPI  SDO pin configuration */
	GPIO_InitStructure.GPIO_Pin =  CC2420_SDO_STM_PIN;
	GPIO_Init(CC2420_SDO_STM_PORT, &GPIO_InitStructure);
	
	/* SPI MISO pin configuration */
	GPIO_InitStructure.GPIO_Pin = CC2420_SDI_STM_PIN;
	GPIO_Init(CC2420_SDO_STM_PORT, &GPIO_InitStructure);
	
	/* SPI configuration -------------------------------------------------------*/
	SPI_I2S_DeInit(spi_port);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
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
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	
	SPI_Init(spi_port, &SPI_InitStructure);
	/* Enable spi_port  */
	SPI_Cmd(spi_port, ENABLE);

	return 0;
}

int8_t	cc2420_spi_close(void)
{
	SPI_I2S_DeInit(spi_port);
	
	/* Disable SCK, SDI, SDO and SCK GPIO clocks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CC2420_SCK_STM |
						   RCC_AHB1Periph_CC2420_SDI_STM |
						   RCC_AHB1Periph_CC2420_SDO_STM, DISABLE);
	return 0;
}

int8_t	cc2420_spi_put(uint8_t in, uint8_t *out)
{
	/* Wait until the end of an ongoing transmission. */
	while (SPI_I2S_GetFlagStatus(spi_port, SPI_I2S_FLAG_TXE) == RESET); 
	SPI_I2S_SendData(spi_port, (uint16_t) in);
	while (SPI_I2S_GetFlagStatus(spi_port, SPI_I2S_FLAG_RXNE) == RESET);
	
	if (out != NULL) {
		*out = (uint8_t) SPI_I2S_ReceiveData(spi_port);
	} else {
		SPI_I2S_ReceiveData(spi_port);
	}
	return 0;
}

int8_t	cc2420_spi_get(uint8_t *out)
{
	/* Wait until the end of an ongoing transmission. */
	while (SPI_I2S_GetFlagStatus(spi_port, SPI_I2S_FLAG_TXE) == RESET); 
	SPI_I2S_SendData(spi_port, 0x0);
	while (SPI_I2S_GetFlagStatus(spi_port, SPI_I2S_FLAG_RXNE) == RESET); 
	
	if (out != NULL) {
		*out = (uint8_t) SPI_I2S_ReceiveData(spi_port);
	} else {
		SPI_I2S_ReceiveData(spi_port);
	}
			
	return 0;
}



#else

#error "CC2420_HAL: Architecture not supported!"

#endif
