# PSA example

EEOPT += __ST10__

EEOPT += __MONO__ __FP__ __DLC_STANDARD__ __PSA_MASTER__ __MUTEX_NOT_OPTIMIZED__ _ALARMS__

APP_SRCS = initkern.c initcom.c main.c

# architecture dependent part
ifeq ($(findstring __EVALUATOR7T__,$(EEOPT)) , __EVALUATOR7T__)
APP_SRCS += e7t_hal.c
endif

ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
APP_SRCS += st10hal.c st10timer.asm st10capcom.c
endif

include $(EEBASE)/config/config.mak
