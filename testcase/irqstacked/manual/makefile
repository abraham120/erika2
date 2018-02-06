EEOPT =

# use this if you need gdb symbols
EEOPT += DEBUG __ASSERT__

EEOPT += __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__
EEOPT += __MULTI__ __FP__
EEOPT += __SEM__



ifeq ($(thearch),e7t_manual)

EEOPT += __ARM7GNU__ __EVALUATOR7T__ __TIMER_1_USED__

APP_SRCS = code.c inithal.c initkern.c
THUMB_SRCS =

endif



ifeq ($(thearch),triscend)

EEOPT += __ARM7GNU__ __TRISCENDA7S__ __FLASH__ __TIMER_1_USED__
#EEOPT += __WATCHDOG_USED__ __LED_USED__ __TIME_SUPPORT__ __TIMER_0_USED__ __DIP_SWITCH_USED__

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

APP_SRCS = code.c initdrvs.c inithal.c initkern.c
THUMB_SRCS =

endif

include $(EEBASE)/pkg/cfg/rules.mk
