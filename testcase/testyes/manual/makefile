EEOPT =

ifeq ($(thearch),e7t_manual)

EEOPT += DEBUG __ASSERT__

EEOPT += __ARM7GNU__ __MULTI__ __EVALUATOR7T__
#__ALLOW_NESTED_IRQ__
#EEOPT += __TIME_SUPPORT__ 
#__TIMER_0_USED__

APP_SRCS = code.c inithal.c initkern.c
THUMB_SRCS =

endif

ifeq ($(thearch),st10_manual)

EEOPT += __ASSERT__

EEOPT += __ST10__ __MONO__

APP_SRCS = code.c initst10.c initkern.c

endif


EEOPT += __FP__

include $(EEBASE)/pkg/cfg/rules.mk
