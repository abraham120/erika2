#ifndef EE_MCU_MPC5643L_STM_H
#define EE_MCU_MPC5643L_STM_H

#include <cpu/common/inc/ee_stdint.h>
#include "mcu/freescale_mpc5643l/inc/MPC5643L.h"

void mpc5643l_stm_freeze_on(void);

void mpc5643l_stm_freeze_off(void);

void mpc5643l_stm_set_prescaler(unsigned int val);

void mpc5643l_stm_select_channel(unsigned int ch);

void mpc5643l_stm_unselect_channel(unsigned int ch);

void mpc5643l_stm_channel_cmp(unsigned int ch, unsigned int val);

void mpc5643l_stm_clear_int(unsigned int ch);

void mpc5643l_stm_set_counter(unsigned int val);

void mpc5643l_stm_enable(void);

void mpc5643l_stm_disable(void);

#endif
