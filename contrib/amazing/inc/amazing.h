#ifndef __AMAZING_H__
#define __AMAZING_H__

#ifndef __USE_TOUCH__
#error AMAZING: this functionality requires TOUCH support.
#endif

#ifndef __USE_PWM__
#error AMAZING: this functionality requires PWM support.
#endif

#ifdef CONFIG_AMAZING_UART_DEBUG

#ifdef __USE_UART__
#include "mcu/microchip_dspic/inc/ee_uart.h"
#else
#error CONFIG_AMAZING_UART_DEBUG: this functionality requires UART support.
#endif

#endif

#ifdef CONFIG_AMAZING_UART_DEBUG_TUNING

#ifdef __USE_UART__
#include "mcu/microchip_dspic/inc/ee_uart.h"
#else
#error CONFIG_AMAZING_UART_DEBUG: this functionality requires UART support.
#endif

#endif

void amazing_reset_body(void);
void amazing_tuner_body(EE_UINT16,EE_UINT16);

#endif // __AMAZING_H__
