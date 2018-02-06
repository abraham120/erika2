
#include "spi_flash_sw.h"

MicoGPIO_t* spi_flash = (MicoGPIO_t*)GPIO_FLASH_BASE_ADDRESS;
EE_gpio_st  spi_gpio_sp;

unsigned char sflash_byte_sw(unsigned char data)
{
	unsigned char i, data_in = 0;
	
	for(i = 0; i < 8; i++) {
		
		SPI_CLK_LOW();
				
		// SPI_IN is valid on falling SPI_CLK
		data_in <<= 1;
		if (SPI_SDI()) {
			data_in |= 0x01;
		} else {
			// Nothing
		}

		// SPI_OUT is valid on rising SPI_CLK
		if (data & 0x80) {
			SPI_SDO_HIGH();
		} else {
			SPI_SDO_LOW();
		}
		data <<= 1;

		SPI_CLK_HIGH();
	}
	
	return data_in;
}

void sflash_init_sw(void)
{
	spi_gpio_sp.data_copy = 0;
	// SPI MODE 3
	SPI_CLK_HIGH();
	SPI_CS_DIS();
} 

void sflash_block_disable(void)
{
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_EWSR);
	SPI_CS_DIS();
	
	sflash_byte_sw(0x00);
	
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_WRSR);
	sflash_byte_sw(0x00);
	SPI_CS_DIS();
}

unsigned int sflash_get_id(void)
{
	unsigned int id;

	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_RDID);
	id  = sflash_byte_sw(0x00) << 16;
	id |= sflash_byte_sw(0x00) <<  8;
	id |= sflash_byte_sw(0x00);
	SPI_CS_DIS();

	return id;
}

void sflash_wait_free(void)
{
	unsigned char value;
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_RDSR);
	do {
		value = sflash_byte_sw(0x00);
		myprintf("%.2x ", value);
	} while(value & SFLASH_STATUS_BUSY);
	SPI_CS_DIS();
}

void sflash_enable_wr(void)
{
	// enable write
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_WREN);
	SPI_CS_DIS();
}

void sflash_disable_wr(void)
{
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_WRDI);
	SPI_CS_DIS();
}

void sflash_chip_erase(void)
{
	sflash_enable_wr();
	sflash_byte_sw(0x00);
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_ERASE);
	SPI_CS_DIS();
	sflash_byte_sw(0x00);
	sflash_wait_free();
}

void sflash_read_data(unsigned int address, unsigned int num, unsigned char *data)
{
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_READ);
	sflash_byte_sw(address >> 16);
	sflash_byte_sw(address >>  8);
	sflash_byte_sw(address);
	while(num--) {
		*data++ = sflash_byte_sw(0x00);
	}
	SPI_CS_DIS();
}

void sflash_write_byte(unsigned int address, unsigned char data)
{
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_WREN);
	SPI_CS_DIS();
	
	sflash_byte_sw(0x00);

	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_WRBYTE);
	sflash_byte_sw(address >> 16);
	sflash_byte_sw(address >> 8);
	sflash_byte_sw(address);
	sflash_byte_sw(data);
	SPI_CS_DIS();

	sflash_byte_sw(0x00);
	sflash_wait_free();
	sflash_byte_sw(0x00);	

	sflash_disable_wr();
}

void sflash_write_aai(unsigned int address, int num, unsigned char *data)
{
	unsigned int i = 0;
	
	//SPI_CS_ENB();
	//sflash_byte_sw(SFLASH_CMD_EBSY);
	//SPI_CS_DIS();
	//sflash_byte_sw(0x00);
	sflash_enable_wr();
	sflash_byte_sw(0x00);
	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_AAI);
	sflash_byte_sw(address >> 16);
	sflash_byte_sw(address >>  8);
	sflash_byte_sw(address);
	sflash_byte_sw(data[i++]);
	sflash_byte_sw(data[i++]);
	num -= 2;
	SPI_CS_DIS();
	while(num > 0) {
		sflash_byte_sw(0x00);
		SPI_CS_ENB();
		sflash_byte_sw(SFLASH_CMD_AAI);
		sflash_byte_sw(data[i++]);
		sflash_byte_sw(data[i++]);
		SPI_CS_DIS();
		num -= 2;
	}
	sflash_byte_sw(0x00);
	sflash_disable_wr();
	sflash_byte_sw(0x00);
	sflash_wait_free();
	sflash_byte_sw(0x00);	
	
}

void sflash_page_write_data(unsigned int address, unsigned int num, unsigned char *data)
{
	unsigned int i;

	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_WREN);
	SPI_CS_DIS();
	
	sflash_byte_sw(0x00);

	SPI_CS_ENB();
	sflash_byte_sw(SFLASH_CMD_PAGEPROG);
	sflash_byte_sw(address >> 16);
	sflash_byte_sw(address >> 8);
	sflash_byte_sw(address);
	for(i = 0; i < num; i++)
		sflash_byte_sw(*data++);
	SPI_CS_DIS();

	sflash_byte_sw(0x00);
	sflash_wait_free();
	sflash_byte_sw(0x00);	
}
