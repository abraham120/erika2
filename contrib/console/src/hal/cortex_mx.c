/** 
* @file pic30.c
* @brief PIC30 Hardware Abstraction Layer implementation.
* @author Errico Guidieri
* @date 2012-07
*/

#ifdef USE_CONSOLE

#include "hal/cortex_mx.h"

/* ************************************************************************** */
/*                           HAL Functions Definition                         */
/* ************************************************************************** */
#ifdef USE_CONSOLE_SERIAL

#if ( \
  !defined(__AUTOSAR_R4_0__)	|| \
  !defined(__AS_SCI_DRIVER__)	|| \
  !defined(SCI_CHANNEL_4)	   \
)
#error "CONSOLE_SERIAL ERROR: AUTOSAR SCI Driver is required!"
#endif

int8_t console_serial_hal_open(uint8_t port, uint32_t bdr, uint16_t flags)
{
	return 1; /*  TODO add Sci check */
}

int8_t console_serial_hal_close(uint8_t port) 
{
	return 1;
}

int8_t console_serial_hal_write(uint8_t port, const uint8_t *mesg,
    uint16_t length)
{
  uint32 i;
  uint8 rx;
  Sci_StatusType st;
  for(i = 0U; i < length; ++i) {
	/* To eventually handle errors in rx */
    st = Sci_GetStatus(SCI_CHANNEL_4);
    while ((st != SCI_OPERATIONAL) && (st != SCI_TX_OK)) {
	  Sci_ReadRxData(SCI_CHANNEL_4, &rx);
	  st = Sci_GetStatus(SCI_CHANNEL_4);
	}
    Sci_WriteTxData(SCI_CHANNEL_4, mesg[i]);
  }
  return 1;
}

int8_t  console_serial_hal_read(uint8_t port, uint8_t *mesg, uint16_t length, 
				uint16_t *read)
{
  uint32 i;
  Std_ReturnType st;
  for(i = 0U; i < length; ++i) {
	  st=Sci_ReadRxData(SCI_CHANNEL_4, &mesg[i]);
	  if(st == E_NOT_OK) {
		return -1;
	  }
  }
  return 1;
}


#endif /* USE_CONSOLE_SERIAL */

#endif /* USE_CONSOLE */
