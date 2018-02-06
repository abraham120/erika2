# Author: 2002 Paolo Gai
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 


EEOPT =

ifeq ($(thearch),e7t_manual)
EEOPT += DEBUG __ASSERT__

EEOPT += __ARM7GNU__ __EVALUATOR7T__

EEOPT += __OO_HAS_STARTUPHOOK__ \
            __OO_NO_RESOURCES__

# we use only the application-defined counters...
EEOPT += __PRIVATE_COUNTERS_INIT__

##
## Error Handling
##

EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __OO_HAS_ERRORHOOK__

##
## Pre and Post Task Hooks
##

#EEOPT += __OO_HAS_PRETASKHOOK__
#EEOPT += __OO_HAS_POSTTASKHOOK__


##
## Peripheral usage
##

#EEOPT += __TIME_SUPPORT__
#EEOPT += __BUTTON_USED__	# button
EEOPT += __LCD_USED__
EEOPT += __LEDS_USED__
#EEOPT += __TIMER_0_USED__
#EEOPT += __TIMER_1_USED__
#EEOPT += __DIP_SWITCH_USED__


# BCC1
# --------------------------------------------
ifeq ($(CONF),e7tB1multi)
EEOPT += __OO_BCC1__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),e7tB1multi2)
EEOPT += __OO_BCC1__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif
ifeq ($(CONF),e7tB1mono)
EEOPT += __OO_BCC1__ __MONO__ __ALLOW_NESTED_IRQ__
endif

# BCC2
# --------------------------------------------
ifeq ($(CONF),e7tB2multi)
EEOPT += __OO_BCC2__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),e7tB2multi2)
EEOPT += __OO_BCC2__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif
ifeq ($(CONF),e7tB2mono)
EEOPT += __OO_BCC2__ __MONO__ __ALLOW_NESTED_IRQ__
endif

# ECC1
# --------------------------------------------
ifeq ($(CONF),e7tE1multi)
EEOPT += __OO_ECC1__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),e7tE1multi2)
EEOPT += __OO_ECC1__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif

# ECC2
# --------------------------------------------
ifeq ($(CONF),e7tE2multi)
EEOPT += __OO_ECC2__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),e7tE2multi2)
EEOPT += __OO_ECC2__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif


APP_SRCS = initkern.c code.c threads.c inithal.c
THUMB_SRCS =

endif

include $(EEBASE)/pkg/cfg/rules.mk


##
## HAL choice
##

#EEOPT += __ARM7ADS__
#EEOPT += __JANUS__
#EEOPT += __ST10__ __ST10_OPTIMIZED__
#EEOPT += __ST10__
#EEOPT  += __H8__

##
## Peripheral usage
##

#ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
#EEOPT += __LCD_USED__
#EEOPT += __PLAY_NOTE_SUPPORT__
#endif

#ifeq ($(findstring __JANUS__,$(EEOPT)) , __JANUS__)
#APP_SRCS_ARM0 = $(APP_SRCS) inithal.c 
#THUMB_SRCS_ARM0 =
#endif

#ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
#APP_SRCS += initst10.c
#endif

#ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
#APP_SRCS += inith8hal.c set_hand.s
#endif
