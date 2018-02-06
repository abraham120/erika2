# Author: 2001-2002 Alessandro Colantonio
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 


EEOPT =


# use this if you need gdb symbols
EEOPT += DEBUG



##
## Interrupt handlers config
##

# interrupt handlers can be nested
EEOPT += __ALLOW_NESTED_IRQ__

# stack used only by IRQ handlers
EEOPT += __IRQ_STACK_NEEDED__



##
## Scheduling choice
##

EEOPT += __ARM7GNU__
#EEOPT += __ARM7ADS__

EEOPT += __EVALUATOR7T__
EEOPT += __MULTI__ __EDF__
EEOPT +=  __TIME_SUPPORT__

EEOPT += __ENABLE_THREAD__


##
## Peripheral usage
##

#EEOPT += __BUTTON_USED__	# button
EEOPT += __LCD_USED__
EEOPT += __LEDS_USED__
EEOPT += __TIMER_0_USED__
EEOPT += __TIMER_1_USED__
EEOPT += __DIP_SWITCH_USED__

APP_SRCS = code.c initdrvs.c inithal.c initkern.c timer.c 
THUMB_SRCS = thumb.c

include $(EEBASE)/pkg/cfg/rules.mk
