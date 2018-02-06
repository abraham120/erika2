# Rules Usage: all (build into the out dir), clean (remove the out dir) 


EEOPT =



# use this if you need gdb symbols
EEOPT += DEBUG


##
## Interrupt handlers config
##

# interrupt handlers can be nested
EEOPT += __ALLOW_NESTED_IRQ__

# stack used only by IRQ handlers. It is incompatible with __MONO__!!!
#EEOPT += __IRQ_STACK_NEEDED__



##
## Scheduling choice
##

EEOPT += __TRICORE1__

EEOPT += __TC1775B__

#EEOPT += __MULTI__ __FP__
EEOPT += __MONO__ __FP__
#EEOPT +=  __TIME_SUPPORT__ __TIMER_0_USED__

EEOPT += __ENABLE_THREAD__

APP_SRCS = code.c inithal.c initkern.c
THUMB_SRCS = thumb.c

include $(EEBASE)/pkg/cfg/rules.mk
