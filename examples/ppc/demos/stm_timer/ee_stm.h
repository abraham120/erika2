#ifndef EE_MCU_MPC5674F_STM_H
#define EE_MCU_MPC5674F_STM_H

#include "mcu/freescale_mpc5674f/inc/ee_mpc5674f.h"

void mpc5674f_stm_freeze_on(void);

void mpc5674f_stm_freeze_off(void);

void mpc5674f_stm_set_prescaler(unsigned int val);

void mpc5674f_stm_select_channel(unsigned int ch);

void mpc5674f_stm_unselect_channel(unsigned int ch);

void mpc5674f_stm_channel_cmp(unsigned int ch, unsigned int val);

void mpc5674f_stm_clear_int(unsigned int ch);

void mpc5674f_stm_set_counter(unsigned int val);

void mpc5674f_stm_enable(void);

void mpc5674f_stm_disable(void);

#endif
