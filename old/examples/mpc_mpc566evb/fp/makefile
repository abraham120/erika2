# Rules Usage: all (build into the out dir), clean (remove the out dir) 

EEOPT =

# use this if you need gdb symbols
EEOPT += DEBUG

##
## Interrupt handlers config
##

# enable enhanced interrupt control
#EEOPT += __ENHANCED_IRQ__

# interrupt handlers can be nested
#EEOPT += __ALLOW_NESTED_IRQ__

# stack used only by IRQ handlers. It is incompatible with __MONO__!!!
#EEOPT += __IRQ_STACK_NEEDED__

##
## Scheduling choice
##

EEOPT += __MPC5XX__
EEOPT += __MPC566EVB__
#EEOPT += __MULTI__ __FP__
EEOPT += __MONO__ __FP__

#EEOPT += __ENABLE_THREAD__

## 
## Debugugging System
##
#EEOPT += __LAUTERBACH_SIM__
#EEOPT +=

##
## Peripheral usage
##

#EEOPT += __EXT0_USED__	# button
#EEOPT += __LCD_USED__
#EEOPT += __LEDS_USED__
#EEOPT += __PIT_USED__
#EEOPT += __RT_CLOCK_USED__ 
#EEOPT += __DIP_SWITCH_USED__

##
## IRQ Level for Internal Interface
##


APP_SRCS = code.c initdrvs.c inithal.c initkern.c
#APP_SRCS =

include $(EEBASE)/pkg/cfg/rules.mk

