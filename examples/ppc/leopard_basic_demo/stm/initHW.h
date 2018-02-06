#ifndef EE_MCU_MPC5643L_INITHW_H
#define EE_MCU_MPC5643L_INITHW_H

#include <cpu/common/inc/ee_stdint.h>
#include "mcu/freescale_mpc5643l/inc/MPC5643L.h"

#define FCCU_NCFK_KEY 0xAB3498FE
#define FCCU_CFK_KEY  0x618B7A50

void initHW(void);

void InitSysclk(void);

void InitModesAndClks(void) ;

void InitPeriClkGen(void);

void DisableWatchdog(void);

void InitGPIO(void);

void ClearNCF(void);

void ClearCF(void);

void ClearFails(void);

#endif
