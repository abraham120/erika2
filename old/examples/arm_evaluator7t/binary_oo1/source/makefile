# Author: 2002 Paolo Gai
# Rules Usage: all (build into the out dir), clean (remove the out dir)


EEOPT =



# debugging or embedded version
EEOPT += DEBUG


##
## Interrupt handlers config
##

# interrupt handlers can be nested
EEOPT += __ALLOW_NESTED_IRQ__

# stack used only by IRQ handlers. It is incompatible with __MONO__!!!
#EEOPT += __IRQ_STACK_NEEDED__



##
## Architecture choice
##

EEOPT += __ARM7GNU__ __EVALUATOR7T__


##
## HAL choice
##

#EEOPT += __MONO__
EEOPT += __MULTI__

##
## OO Configuration
##

#EEOPT += __OO_BCC1__
#EEOPT += __OO_BCC2__
#EEOPT += __OO_ECC1__
EEOPT += __OO_ECC2__

EEOPT += __OO_HAS_STARTUPHOOK__ \
            __OO_NO_ALARMS__

EEOPT += __OO_ORTI_LASTERROR__ __OO_ORTI_SERVICETRACE__ __OO_ORTI_RUNNINGISR2__ __OO_ORTI_PRIORITY__ __OO_ORTI_STACK__

##
## Error Handling
##

EEOPT += __OO_EXTENDED_STATUS__

EEOPT += __OO_HAS_ERRORHOOK__

##
## Pre and Post Task Hooks
##

EEOPT += __OO_HAS_PRETASKHOOK__
EEOPT += __OO_HAS_POSTTASKHOOK__


##
## Peripheral usage
##

#EEOPT += __TIME_SUPPORT__

#EEOPT += __BUTTON_USED__	# button
EEOPT += __LCD_USED__
EEOPT += __LEDS_USED__
EEOPT += __TIMER_0_USED__
#EEOPT += __TIMER_1_USED__
EEOPT += __DIP_SWITCH_USED__


APP_SRCS = initkern.c code.c threads.c inithal.c
THUMB_SRCS =



include $(EEBASE)/pkg/cfg/rules.mk
