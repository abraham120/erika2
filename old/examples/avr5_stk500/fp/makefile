# Author: 2001-2002 Antonio Romano, 2005/2006 - Paolo Gai
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 


EEOPT =
EEBASE=  /cygdrive/c/ee_AVR
AVRBASE= /cygdrive/c/Programmi/AVRGCC\ 3.4.4/avrgcc
APPBASE= /cygdrive/c/ee_AVR/example/avr5_stk500/fp


# use this if you need gdb symbols
EEOPT += DEBUG


##
## Interrupt handlers config
##

# interrupt handlers can be nested
EEOPT += __ALLOW_NESTED_IRQ__

# stack used only by IRQ handlers. It is incompatible with __MONO__!!!
EEOPT += __IRQ_STACK_NEEDED__



##
## Scheduling choice
##

EEOPT += __AVR5GNU__

EEOPT += __STK500501__

EEOPT += __MULTI__ __FP__
#EEOPT += __MONO__ __FP__
#EEOPT +=  __TIME_SUPPORT__ __TIMER_0_USED__

#EEOPT += __ENABLE_THREAD__


##
## Peripheral usage
##


#EEOPT += __TIMER0_CLK_DIV1__           ##Timer clocked at F_CPU
#EEOPT += __TIMER0_CLK_DIV8__          ##Timer clocked at F_CPU/8
#EEOPT += __TIMER0_CLK_DIV32__         ##Timer clocked at F_CPU/32
#EEOPT += __TIMER0_CLK_DIV64__         ##Timer clocked at F_CPU/64
#EEOPT += __TIMER0_CLK_DIV256__        ##Timer clocked at F_CPU/256
EEOPT += __TIMER0_CLK_DIV1024__       ##Timer clocked at F_CPU/1024

#EEOPT += __TIMER2_CLK_DIV1__           ##Timer clocked at F_CPU
#EEOPT += __TIMER2_CLK_DIV8__           ##Timer clocked at F_CPU/8
#EEOPT += __TIMER2_CLK_DIV64__          ##Timer clocked at F_CPU/64
EEOPT += __TIMER2_CLK_DIV256__         ##Timer clocked at F_CPU/256
#EEOPT += __TIMER2_CLK_DIV1024__        ##Timer clocked at F_CPU/1024

#EEOPT += __TIMER1_CLK_DIV1__           ##Timer clocked at F_CPU
#EEOPT += __TIMER1_CLK_DIV8__           ##Timer clocked at F_CPU/8
EEOPT += __TIMER1_CLK_DIV64__          ##Timer clocked at F_CPU/64
#EEOPT += __TIMER1_CLK_DIV256__         ##Timer clocked at F_CPU/256
#EEOPT += __TIMER1_CLK_DIV1024__        ##Timer clocked at F_CPU/1024

#EEOPT += __TIMER3_CLK_DIV1__           ##Timer clocked at F_CPU
EEOPT += __TIMER3_CLK_DIV8__           ##Timer clocked at F_CPU/8
#EEOPT += __TIMER3_CLK_DIV64__          ##Timer clocked at F_CPU/64
#EEOPT += __TIMER3_CLK_DIV256__         ##Timer clocked at F_CPU/256
#EEOPT += __TIMER3_CLK_DIV1024__        ##Timer clocked at F_CPU/1024

EEOPT += __TIMER_USED__
EEOPT += __LEDS_USED__
EEOPT += __TIMER_0_USED__
EEOPT += __TIMER_1_USED__
EEOPT += __TIMER_2_USED__
EEOPT += __TIMER_3_USED__
#EEOPT += __SWITCH_USED__
##EEOPT += __IRQ_PRIORITY_MASKS__ __IRQ_PRIORITY_MASKS_NOCONST__
APP_SRCS = code.c inithal.c initkern.c threads.c handlerinstall.S handler.c


include $(EEBASE)/pkg/cfg/rules.mk
