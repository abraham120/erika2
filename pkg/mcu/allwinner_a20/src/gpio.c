#include "mcu/allwinner_a20/inc/gpio.h"

unsigned int SUNXI_PIO_BASE = 0;

void gpio_init(void)
{
	unsigned int PageSize, PageMask,
		     addr_start, addr_offset;

	PageSize = 4096;
	PageMask = (~(PageSize-1));
	addr_start = SW_PORTC_IO_BASE & PageMask;
	addr_offset = SW_PORTC_IO_BASE & ~PageMask;

	SUNXI_PIO_BASE = addr_start + addr_offset;
}

int gpio_cfg_pin(unsigned int pin, unsigned int val)
{
	unsigned int cfg;
	unsigned int bank = GPIO_BANK(pin);
	unsigned int index = GPIO_CFG_INDEX(pin);
	unsigned int offset = GPIO_CFG_OFFSET(pin);

	if (!SUNXI_PIO_BASE)
		return -1;

	struct sunxi_gpio *pio =
		&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];

	cfg = *(&pio->cfg[0] + index);
	cfg &= ~(0xf << offset);
	cfg |= val << offset;

	*(&pio->cfg[0] + index) = cfg;

	return 0;
}

int gpio_output(unsigned int pin, unsigned int val)
{
	unsigned int bank = GPIO_BANK(pin);
	unsigned int num = GPIO_NUM(pin);

	if (!SUNXI_PIO_BASE)
		return -1;

	struct sunxi_gpio *pio =&((struct sunxi_gpio_reg *)SUNXI_PIO_BASE)->gpio_bank[bank];

	if (val)
		*(&pio->dat) |= 1 << num;
	else
		*(&pio->dat) &= ~(1 << num);

	return 0;
}
