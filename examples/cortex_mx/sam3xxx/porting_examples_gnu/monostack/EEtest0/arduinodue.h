#include "sam.h"
#include "chip.h"

#include "pio.h"

# define ArduinoDue_LED_Init() { \
  PIOB->PIO_PER  = 1<<27; \
  PIOB->PIO_OER  = 1<<27; \
  PIOB->PIO_CODR = 1<<27; \
}
# define ArduinoDue_LED_On()  { PIOB->PIO_SODR = 1<<27; }
# define ArduinoDue_LED_Off() { PIOB->PIO_CODR = 1<<27; }
# define ArduinoDue_LED_Toggle() { \
    if (PIOB->PIO_ODSR && 1<<27) \
	PIOB->PIO_CODR = 1<<27; \
    else \
	PIOB->PIO_SODR = 1<<27; \
}
 
#ifdef __USE_USER_LED__

#define EE_user_led_init	ArduinoDue_LED_Init
#define EE_user_led_on		ArduinoDue_LED_On
#define EE_user_led_off		ArduinoDue_LED_Off
#define EE_user_led_toggle	ArduinoDue_LED_Toggle

#endif /* __USE_USER_LED__ */