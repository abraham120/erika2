#ifndef __ERIKA_GPIO__
#define __ERIKA_GPIO__

/* From SUNXI GPIOLIB */

#define SW_PORTC_IO_BASE 0x01c20800

#define GPIO_BANK(pin)  ((pin) >> 5)
#define GPIO_NUM(pin)   ((pin) & 0x1F)
#define GPIO_CFG_INDEX(pin)     (((pin) & 0x1F) >> 3)
#define GPIO_CFG_OFFSET(pin)    ((((pin) & 0x1F) & 0x7) << 2)

#define INPUT   0
#define OUTPUT  1

#define HIGH    1
#define LOW     0

/* gpio interrupt control */
struct sunxi_gpio_int {
    unsigned int cfg[3];
    unsigned int ctl;
    unsigned int sta;
    unsigned int deb;
};

struct sunxi_gpio {
    unsigned int cfg[4];
    unsigned int dat;
    unsigned int drv[2];
    unsigned int pull[2];
};

struct sunxi_gpio_reg {
    struct sunxi_gpio gpio_bank[9];
    unsigned char res[0xbc];
    struct sunxi_gpio_int gpio_int;
};

/* GPIO bank sizes */
#define SUNXI_GPIO_A_NR         (32)
#define SUNXI_GPIO_B_NR         (32)
#define SUNXI_GPIO_C_NR         (32)
#define SUNXI_GPIO_D_NR         (32)
#define SUNXI_GPIO_E_NR         (32)
#define SUNXI_GPIO_F_NR         (32)
#define SUNXI_GPIO_G_NR         (32)
#define SUNXI_GPIO_H_NR         (32)
#define SUNXI_GPIO_I_NR         (32)

#define SUNXI_GPIO_NEXT(__gpio) ((__gpio##_START)+(__gpio##_NR)+0)

enum sunxi_gpio_number {
    SUNXI_GPIO_A_START = 0,
    SUNXI_GPIO_B_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_A), //32
    SUNXI_GPIO_C_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_B), //64
    SUNXI_GPIO_D_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_C), //96
    SUNXI_GPIO_E_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_D), //128
    SUNXI_GPIO_F_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_E), //160
    SUNXI_GPIO_G_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_F), //192
    SUNXI_GPIO_H_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_G), //224
    SUNXI_GPIO_I_START = SUNXI_GPIO_NEXT(SUNXI_GPIO_H)  //256
};

#define SUNXI_GPD(_nr) (SUNXI_GPIO_D_START + (_nr))
#define PD1    SUNXI_GPD(1)
#define PD12    SUNXI_GPD(12)

void gpio_init(void);
int gpio_cfg_pin(unsigned int pin, unsigned int val);
int gpio_output(unsigned int pin, unsigned int val);

#endif /* __ERIKA_GPIO__ */
