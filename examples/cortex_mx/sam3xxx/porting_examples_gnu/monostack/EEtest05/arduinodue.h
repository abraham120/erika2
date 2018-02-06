#include "sam.h"
#include "chip.h"

#include "pio.h"

/* Support for ArduinoDue System LED */
#ifdef __USE_USER_LED__

# define EE_user_led_init() { \
  PIOB->PIO_PER  = 1<<27; \
  PIOB->PIO_OER  = 1<<27; \
  PIOB->PIO_CODR = 1<<27; \
}
# define EE_user_led_on()  { PIOB->PIO_SODR = 1<<27; }
# define EE_user_led_off() { PIOB->PIO_CODR = 1<<27; }
# define EE_user_led_toggle() { \
    if (PIOB->PIO_ODSR && 1<<27) \
	PIOB->PIO_CODR = 1<<27; \
    else \
	PIOB->PIO_SODR = 1<<27; \
}

#endif /* __USE_USER_LED__ */
