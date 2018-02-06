#include "ee_stm.h"

void mpc5674f_stm_freeze_on(void)
{
        STM.CR.B.FRZ = 1;
}

void mpc5674f_stm_freeze_off(void)
{
        STM.CR.B.FRZ = 0;
}

void mpc5674f_stm_set_prescaler(unsigned int val)
{
        STM.CR.B.CPS = val-1;
}

void mpc5674f_stm_select_channel(unsigned int ch)
{
        if (ch == 0) {
                STM.CCR0.B.CEN = 1;
        }
        else if (ch == 1) {
                STM.CCR1.B.CEN = 1;
        }
        else if (ch == 2) {
                STM.CCR2.B.CEN = 1;
        }
        else if (ch == 3) {
                STM.CCR3.B.CEN = 1;
        }
}

void mpc5674f_stm_unselect_channel(unsigned int ch)
{
        if (ch == 0) {
                STM.CCR0.B.CEN = 0;
        }
        else if (ch == 1) {
                STM.CCR1.B.CEN = 0;
        }
        else if (ch == 2) {
                STM.CCR2.B.CEN = 0;
        }
        else if (ch == 3) {
                STM.CCR3.B.CEN = 0;
        }
}

void mpc5674f_stm_channel_cmp(unsigned int ch, unsigned int val)
{
        if (ch == 0) {
                STM.CMP0.R = val;
        }
        else if (ch == 1) {
                STM.CMP1.R = val;
        }
        else if (ch == 2) {
                STM.CMP2.R = val;
        }
        else if (ch == 3) {
                STM.CMP3.R = val;
        }
}

void mpc5674f_stm_clear_int(unsigned int ch)
{
        if (ch == 0) {
                STM.CIR0.B.CIF = 1;
        }
        else if (ch == 1) {
                STM.CIR1.B.CIF = 1;
        }
        else if (ch == 2) {
                STM.CIR2.B.CIF = 1;
        }
        else if (ch == 3) {
                STM.CIR3.B.CIF = 1;
        }
}

void mpc5674f_stm_set_counter(unsigned int val)
{
        STM.CNT.R = val;
}

void mpc5674f_stm_enable(void)
{
        STM.CR.B.TEN = 1;
}

void mpc5674f_stm_disable(void)
{
        STM.CR.B.TEN = 0;
}

