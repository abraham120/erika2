
#ifndef _SFLASH_H_
#define _SFLASH_H_

#include <ee.h>
#include <MicoGPIO.h>
#include <system_conf.h>

#define SFLASH_STATUS_BUSY 0x01

#define SFLASH_CMD_RDID        0x9F
#define SFLASH_CMD_RDSR        0x05
#define SFLASH_CMD_WREN        0x06
#define SFLASH_CMD_WRDI        0x04
#define SFLASH_CMD_ERASE       0x60
#define SFLASH_CMD_READ        0x03
#define SFLASH_CMD_EWSR        0x50
#define SFLASH_CMD_WRSR        0x01
#define SFLASH_CMD_WRBYTE      0x02
#define SFLASH_CMD_PAGEPROG    0x02
#define SFLASH_CMD_EBSY        0x70
#define SFLASH_CMD_AAI         0xAD

#define SPI_CS_DIS()    EE_hal_gpio_output_write_bit_data(spi_flash, 1, 0, &spi_gpio_sp)
//#define SPI_CS_DIS()    EE_hal_gpio_write_bit_data(spi_flash, 1, 0)
#define SPI_CS_ENB()    EE_hal_gpio_output_write_bit_data(spi_flash, 0, 0, &spi_gpio_sp)
//#define SPI_CS_ENB()    EE_hal_gpio_write_bit_data(spi_flash, 0, 0)
#define SPI_CLK_HIGH()   EE_hal_gpio_output_write_bit_data(spi_flash, 1, 1, &spi_gpio_sp)
//#define SPI_CLK_HIGH()  EE_hal_gpio_write_bit_data(spi_flash, 1, 1)
#define SPI_CLK_LOW()   EE_hal_gpio_output_write_bit_data(spi_flash, 0, 1, &spi_gpio_sp)
//#define SPI_CLK_LOW()   EE_hal_gpio_write_bit_data(spi_flash, 0, 1)
#define SPI_SDO_HIGH()   EE_hal_gpio_output_write_bit_data(spi_flash, 1, 2, &spi_gpio_sp)
//#define SPI_SDO_HIGH()  EE_hal_gpio_write_bit_data(spi_flash, 1, 2)
#define SPI_SDO_LOW()   EE_hal_gpio_output_write_bit_data(spi_flash, 0, 2, &spi_gpio_sp)
//#define SPI_SDO_LOW()   EE_hal_gpio_write_bit_data(spi_flash, 0, 2)
#define SPI_SDI()       (EE_hal_gpio_read_data(spi_flash) & 0x000000FF)

/**
*/
void sflash_init_sw(void);

/**
*/
unsigned int sflash_get_id(void);

/**
*/
void sflash_chip_erase(void);

/**
*/
void sflash_read_data(unsigned int address, unsigned int num, unsigned char *data);

/**
*/
void sflash_write_byte(unsigned int address, unsigned char data);

/**
*/
void sflash_block_disable(void);

/**
*/
void sflash_write_aai(unsigned int address, int num, unsigned char *data);

#endif
