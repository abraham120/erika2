# OSEK COM CCCA example

EEOPT =

EEOPT += __ST10__
#EEOPT += __ARM7GNU__ __EVALUATOR7T__ DEBUG __TIMER_1_USED__


EEOPT += __MONO__ __FP__ __OSEKCOM_CCC1__ __OSEKCOM_HAS_ERRORHOOK__ __EE_OSEKCOM_EXTENDED__

APP_SRCS = initkern.c initosekcom.c testccc1.c

# architecture dependent part
ifeq ($(findstring __EVALUATOR7T__,$(EEOPT)) , __EVALUATOR7T__)
APP_SRCS += e7t_hal.c
endif

ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
APP_SRCS += st10hal.c st10timer.asm st10capcom.c
endif

include $(EEBASE)/config/config.mak
