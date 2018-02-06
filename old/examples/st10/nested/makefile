# Makefile
# 
# by Paolo Gai 2002
#
# Rules Usage: all (build into the out dir), clean (remove the out dir) 

# Compiling options
EEOPT = __ST10__
#EEOPT = __ST10SEGM__

EEOPT += __EDF__ __ALLOW_NESTED_IRQ__

#EEOPT += __MONO__ 
EEOPT += __MULTI__ 


APP_SRCS= irq_tim.c code.c inithal.c initkern.c irq_hand.asm

#
# --------------------------------------------------------------------------
#

# the st10cfg.mak relies on these environment variables, that on my PC have
# the following values:
#
# C166BASE=/cygdrive/d/programmi/c166
# EEBASE=/cygdrive/d/madess/erika

include $(EEBASE)/config/config.mak
