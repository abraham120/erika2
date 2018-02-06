### Setting Erika's variables:
# EEBASE = ../../..
# APPBASE = .
# 
# EEOPT =



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __ADD_LIBS__
EEOPT += __USE_PHY_SMSC8720__
EEOPT += __IPERMOB_BOARD_V2__
EEOPT += __USE_IPERMOB_BOARD_V2__
EEOPT += __USE_LEDS__
EEOPT += __USE_TIMER__
EEOPT += __USE_EE_TIMER_1__
EEOPT += __USE_EE_TIMER_2__
EEOPT += __USE_EE_TIMER_3__
EEOPT += __USE_UART__
EEOPT += __USE_UART_PORT1B__
EEOPT += USE_CONSOLE
EEOPT += USE_CONSOLE_SERIAL
EEOPT += CONSOLE_SERIAL_NUMBER=6
EEOPT += __LWIP_IPV4__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __PIC32__
EEOPT += __MICROCHIP_PIC32__
EEOPT += __PIC32_ICD2__
EEOPT += __32MX795F512L__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __ALARMS__


############################################################################
#
# PIC 32
#
############################################################################
ifndef EEBASE
    EEBASE  := $(shell cygpath `cygpath -ms "C:\Evidence\eclipse_160\plugins\com.eu.evidence.ee_1.6.0.201106072202\ee_base"`)
endif
APPBASE := 
OUTBASE := Debug_demo

PIC32_ASMDIR := $(shell cygpath `cygpath -ms "c:\Programmi\Microchip\MPLAB ASM32 Suite"`)
PIC32_GCCDIR := $(shell cygpath `cygpath -ms "c:\Programmi\Microchip\MPLAB C32"`)


############################################################################
#
# Init MCU for PIC32 (PIC32MX795F512L)
#
############################################################################
PIC32_MODEL           := 32MX795F512L
PIC32_DEV_LIB         := libmchp_peripheral_32MX795F512L.a
PIC32_INCLUDE_C       := p32xxxx.h


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += -DPBUF_POOL_SIZE=2 -DMEM_SIZE=1024*8 -DLWIP_UDP=1
ASFLAGS += 
LDFLAGS += -Wl,--defsym=_min_heap_size=16000,--defsym=_min_stack_size=2048
LDDEPS  += 
LIBS    += 

LIB_OPT  += __LIB_MAC_EXTPHY__
LIB_OPT  += __LIB_CONSOLE__
LIB_OPT  += __LIB_LWIP__


############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c main.c util.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
