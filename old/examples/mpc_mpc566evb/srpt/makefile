# Rules Usage: all (build into the out dir), clean (remove the out dir) 


ERIKAOPT =


# use this if you need gdb symbols
ERIKAOPT += DEBUG


##
## Interrupt handlers config
##

# interrupt handlers can be nested
ERIKAOPT += __ALLOW_NESTED_IRQ__

# stack used only by IRQ handlers
ERIKAOPT += __IRQ_STACK_NEEDED__



##
## Scheduling choice
##

ERIKAOPT += __ARM7GNU__
#ERIKAOPT += __ARM7ADS__

ERIKAOPT += __EVALUATOR7T__
ERIKAOPT += __MULTI__ __EDF__
ERIKAOPT +=  __TIME_SUPPORT__

ERIKAOPT += __ENABLE_THREAD__


##
## Peripheral usage
##

#ERIKAOPT += __EXT0_USED__	# button
ERIKAOPT += __LCD_USED__
ERIKAOPT += __LEDS_USED__
ERIKAOPT += __TIMER_0_USED__
ERIKAOPT += __TIMER_1_USED__
ERIKAOPT += __DIP_SWITCH_USED__

APP_SRCS = code.c initdrvs.c inithal.c initkern.c timer.c 
THUMB_SRCS = thumb.c

include $(ERIKABASE)/config/config.mak
