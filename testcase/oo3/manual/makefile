# Author: 2002 Paolo Gai
# Rules Usage: all (build into the out dir), clean (remove the out dir) 


EEOPT =

EEOPT += __ASSERT__

EEOPT += __OO_HAS_STARTUPHOOK__ \
            __OO_NO_ALARMS__

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


# BCC1
# --------------------------------------------
ifeq ($(CONF),B1multi)
EEOPT += __OO_BCC1__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),B1multi2)
EEOPT += __OO_BCC1__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif
ifeq ($(CONF),B1mono)
EEOPT += __OO_BCC1__ __MONO__ __ALLOW_NESTED_IRQ__
endif

# BCC2
# --------------------------------------------
ifeq ($(CONF),B2multi)
EEOPT += __OO_BCC2__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),B2multi2)
EEOPT += __OO_BCC2__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif
ifeq ($(CONF),B2mono)
EEOPT += __OO_BCC2__ __MONO__ __ALLOW_NESTED_IRQ__
endif

# ECC1
# --------------------------------------------
ifeq ($(CONF),E1multi)
EEOPT += __OO_ECC1__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),E1multi2)
EEOPT += __OO_ECC1__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif

# ECC2
# --------------------------------------------
ifeq ($(CONF),E2multi)
EEOPT += __OO_ECC2__ __MULTI__ __ALLOW_NESTED_IRQ__
endif
ifeq ($(CONF),E2multi2)
EEOPT += __OO_ECC2__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
endif


ifeq ($(thearch),e7t_manual)
EEOPT += DEBUG

EEOPT += __ARM7GNU__ __EVALUATOR7T__

##
## Peripheral usage
##

#EEOPT += __TIME_SUPPORT__

#EEOPT += __BUTTON_USED__	# button
EEOPT += __LCD_USED__
EEOPT += __LEDS_USED__
#EEOPT += __TIMER_0_USED__
EEOPT += __TIMER_1_USED__
EEOPT += __DIP_SWITCH_USED__

APP_SRCS = initkern.c code.c threads.c inithal.c
THUMB_SRCS =
endif





ifeq ($(thearch),triscend)

EEOPT += DEBUG

EEOPT += __ARM7GNU__ __TRISCENDA7S__

##
## Peripheral usage
##

EEOPT += __LED_USED__ __TIMER_1_USED__ __DIP_SWITCH_USED__ __FLASH__
#EEOPT += __WATCHDOG_USED__ __TIME_SUPPORT__ __TIMER_1_USED__

# Definitions for FDL
# Pay attention with clock rate greater then 40MHz-->pipeline and DMA buffers enabled by sdram_init()!!

FLASH_DEVICE	= AM29LV116DT-90
CSOC_NAME		= TA7S20-60Q
SDRAM				= MT8LSDT864HG-662
CLOCK				= xtal32K:30M
MIU				= 2M:8
SDMIU				= 32M:32:1
CSL_NAME			= A7CAN.csl

# -rh to reset and halt cpu after download for the debugging
CSOC_DWL_OPTS += -rh

# Fastchip project name and location (NB:use "C:", not "/cygdrive/c")
FCP_PROJECT = A7EE
FCP_PROJECT_DIR = C:/Triscend/Projects/$(FCP_PROJECT)

APP_SRCS = code.c initdrvs.c inithal.c initkern.c threads.c 
THUMB_SRCS =

endif




include $(EEBASE)/pkg/cfg/rules.mk

#EEOPT += __ARM7ADS__
#EEOPT += __JANUS__
#EEOPT += __ST10SEGM__ __ST10_OPTIMIZED__
#EEOPT += __ST10SEGM__
#EEOPT += __H8__

#ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
#EEOPT += __LCD_USED__
#EEOPT += __PLAY_NOTE_SUPPORT__
#EEOPT += __TIMER_A_USER_FUNCTION_USED__
#endif

#ifeq ($(findstring __JANUS__,$(EEOPT)) , __JANUS__)
#APP_SRCS_ARM0 = $(APP_SRCS) inithal.c 
#THUMB_SRCS_ARM0 =
#endif

#ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
#APP_SRCS += initst10.c irq_st10.asm
#endif

#ifeq ($(findstring __ST10SEGM__,$(EEOPT)) , __ST10SEGM__)
#APP_SRCS += initst10.c irq_st10.asm
#endif

#ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
#APP_SRCS += inith8hal.c set_hand.s
#endif
