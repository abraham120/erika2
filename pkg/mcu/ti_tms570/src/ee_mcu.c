 /**
    @file ee_mcu.c
    @brief  Mcu Functions
    @author Christoph Kreuzberger
    @date 2014
  */

#include "ee.h"


void EE_mcu_init(void)
{

#ifdef	__CORTEX_RX__
  /* Initialize Error Signaling Module */
  esmInit();
  _enable_interrupts();
  rtiInit();

#ifdef __USE_DISPLAY__
  EMIF_Init();
  GLCD_Init();
#endif /*__USE_GLCD__*/


#if defined(__USE_GIO__) || defined(__USE_LEDS__)
  gioInit();
#endif

#if defined(__USE_HET__) || defined(__USE_LEDS__)
  hetInit();
#endif

#ifdef __USE_ADC__
  adcInit();
#endif

#ifdef __USE_CAN__
  canInit();
#endif

#ifdef __USE_LIN__
  linInit();
#endif

#ifdef __USE_SCI__
  sciInit();
#endif

#ifdef __USE_SPI__
  spiInit();
#endif



#endif	/* __CORTEX_RX__ */

}
