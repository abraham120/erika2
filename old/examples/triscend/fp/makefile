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
## Scheduling choice
##

EEOPT += __ARM7GNU__ __TRISCENDA7S__
EEOPT += __MULTI__ __FP__
#EEOPT += __MONO__ __FP__
EEOPT +=  __TIME_SUPPORT__ __TIMER_0_USED__

EEOPT += __ENABLE_THREAD__


##
## Peripheral usage
##

EEOPT += __WATCHDOG_USED__	
EEOPT += __LED_USED__
EEOPT += __TIMER_0_USED__
EEOPT += __TIMER_1_USED__
EEOPT += __DIP_SWITCH_USED__


##
## Make memory target
##

EEOPT += __FLASH__
#EEOPT += __FLASH_EXEC__

#EEOPT += __FLASH_EXEC_INTERNAL__
#EEOPT += __FLASH_INTERNAL__
#EEOPT += __INTERNAL__
#EEOPT += __CSL__
#EEOPT += __SDRAM__

#
# Definitions for FDL
# Pay attention with clock rate greater then 40MHz-->pipeline and DMA buffers enabled by sdram_init()!!

FLASH_DEVICE	= AM29LV116DT-90
CSOC_NAME		= TA7S20-60Q
SDRAM				= MT8LSDT864HG-662
CLOCK				= xtal32K:30M
MIU				= 2M:8
SDMIU				= 32M:32:1
CSL_NAME			= A7CAN.csl


# Fastchip project name and location (NB:use "C:", not "/cygdrive/c")
FCP_PROJECT = A7EE
FCP_PROJECT_DIR = C:/Triscend/Projects/$(FCP_PROJECT)

APP_SRCS = code.c initdrvs.c inithal.c initkern.c
THUMB_SRCS = thumb.c

include $(EEBASE)/config/config.mak
