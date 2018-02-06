# MONO Makefile
# 
# by Paolo Gai 2001
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 

# Compiling options

EEOPT = __FP__

EEOPT += __ST10__ __MONO__
#EEOPT += __ST10__ __MULTI__
#EEOPT += __ST10SEGM__ __MULTI__

APP_SRCS= irq_hand.asm irq_tim.c code.c inithal.c initkern.c

#
# --------------------------------------------------------------------------
#

include $(EEBASE)/config/config.mak
