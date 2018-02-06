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

#EEOPT += __H8__ __LCD_USED__ 
#   EEOPT += __PLAY_NOTE_SUPPORT__

#EEOPT += __ARM7GNU__ __EVALUATOR7T__
#EEOPT += __ARM7ADS__
EEOPT += __ARM7GNU__ __JANUS__ __JANUS_EIC_DOUBLE_BRANCH__
#EEOPT += __ST10__ __ST10_OPTIMIZED__
#EEOPT += __ST10__
#EEOPT += __ST10SEGM__ __ST10_OPTIMIZED__
#EEOPT += __ST10SEGM__

##
## HAL choice
##

#EEOPT += __MONO__
EEOPT += __MULTI__

##
## OSEK Configuration
##

#EEOPT += __OSEKOS_BCC1__
#EEOPT += __OSEKOS_BCC2__
#EEOPT += __OSEKOS_ECC1__
EEOPT += __OSEKOS_ECC2__

EEOPT += __OSEKOS_HAS_STARTUPHOOK__ \
            __OSEKOS_NO_ALARMS__

EEOPT += __OSEKOS_ORTI_LASTERROR__ __OSEKOS_ORTI_SERVICETRACE__ __OSEKOS_ORTI_RUNNINGISR2__ __OSEKOS_ORTI_PRIORITY__ __OSEK_ORTI_STACK__

##
## Error Handling
##

EEOPT += __OSEKOS_EXTENDED_STATUS__

EEOPT += __OSEKOS_HAS_ERRORHOOK__

##
## Pre and Post Task Hooks
##

EEOPT += __OSEKOS_HAS_PRETASKHOOK__
EEOPT += __OSEKOS_HAS_POSTTASKHOOK__


##
## Peripheral usage
##

ifeq ($(findstring __ARM7GNU__,$(EEOPT)) , __ARM7GNU__)
ifeq ($(findstring __EVALUATOR7T__,$(EEOPT)) , __EVALUATOR7T__)

#EEOPT += __TIME_SUPPORT__

#EEOPT += __EXT0_USED__	# button
EEOPT += __LCD_USED__
EEOPT += __LEDS_USED__
EEOPT += __TIMER_0_USED__
#EEOPT += __TIMER_1_USED__
EEOPT += __DIP_SWITCH_USED__

endif
endif


APP_SRCS = initkern.c code.c threads.c

ifeq ($(findstring __ARM7GNU__,$(EEOPT)) , __ARM7GNU__)

ifeq ($(findstring __EVALUATOR7T__,$(EEOPT)) , __EVALUATOR7T__)
APP_SRCS += inithal.c
THUMB_SRCS =
endif

ifeq ($(findstring __JANUS__,$(EEOPT)) , __JANUS__)
APP_SRCS_ARM0 += $(APP_SRCS) inithal.c
THUMB_SRCS_ARM0 +=
endif

endif

ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
APP_SRCS += initst10.c
endif

ifeq ($(findstring __ST10SEGM__,$(EEOPT)) , __ST10SEGM__)
APP_SRCS += initst10.c
endif

ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
APP_SRCS += inith8hal.c set_hand.s
endif

include $(EEBASE)/config/config.mak
