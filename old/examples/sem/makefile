# Semaphore Test
# 
# by Paolo Gai 2001-2002
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 

# Compiling options
#EEOPT = __ST10__ __MULTI__ __FP__ __SEM__
#EEOPT = __ST10__ __MULTI__ __FP__ __ST10_OPTIMIZED__ __SEM__
#EEOPT = __ST10SEGM__ __MULTI__ __FP__ __SEM__
#EEOPT = __ST10SEGM__ __MULTI__ __FP__ __ST10_OPTIMIZED__ __SEM__
EEOPT = __ARM7GNU__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__ \
           __FP__ __TIMER_1_USED__ __SEM__ DEBUG __EVALUATOR7T__
#EEOPT = __ARM7ADS__ __MULTI__ __ALLOW_NESTED_IRQ__ __IRQ_STACK_NEEDED__ \
#           __FP__ __TIMER_1_USED__ __SEM__ DEBUG

#EEOPT = __H8__ __MULTI__ __FP__ __SEM__ __TIMER_A_USER_FUNCTION_USED__ \
	    __LCD_USED__

# architecture independent part
APP_SRCS= irq_tim.c    \
          code.c       \
          initkern.c


ifeq ($(findstring __ST10__,$(EEOPT)) , __ST10__)
APP_SRCS+= initst10.c irq_hand.asm
endif

ifeq ($(findstring __ST10SEGM__,$(EEOPT)) , __ST10SEGM__)
APP_SRCS+= initst10.c irq_hand.asm
endif

ifeq ($(findstring __ARM7GNU__,$(EEOPT)) , __ARM7GNU__)
APP_SRCS += initarm7.c
THUMB_SRCS=
endif

ifeq ($(findstring __ARM7ADS__,$(EEOPT)) , __ARM7ADS__)
APP_SRCS += initarm7.c
THUMB_SRCS=
endif

ifeq ($(findstring __H8__,$(EEOPT)) , __H8__)
APP_SRCS+= inith8hal.c set_hand.s
endif

#
# --------------------------------------------------------------------------
#

include $(EEBASE)/config/config.mak









