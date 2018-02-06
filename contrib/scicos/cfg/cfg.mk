# ###*B*###
# Copyright (C) Roberto Bucher (SUPSI- Lugano)
#               Simone Mannori (Scilab / INRIA / DIGITEO)
#
# Copyright (C) METALAU Project (INRIA)
# ###*E*###
 
 
## Author: 2007 Mauro Marinoni
## CVS: $Id: cfg.mk,v 1.5 2008/07/18 11:24:24 pj Exp $

ifeq ($(findstring __LIB_SCICOS__,$(LIB_OPT)),__LIB_SCICOS__)

EE_VPATH += $(EEBASE)/contrib/scicos/src/pic30
EE_VPATH += $(EEBASE)/contrib/scicos/src/pic30/communication
EE_VPATH += $(EEBASE)/contrib/scicos/src/pic30/communication/udp
EE_VPATH += $(EEBASE)/contrib/scicos/libsrc/rt
EE_VPATH += $(EEBASE)/contrib/scicos/libsrc/core

ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/scicos/inc/core)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/scicos/inc)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/scicos/inc/pic30/communication/udp)"
else
ALLINCPATH += -I$(EEBASE)/contrib/scicos/inc/core
ALLINCPATH += -I$(EEBASE)/contrib/scicos/inc
ALLINCPATH += -I$(EEBASE)/contrib/scicos/inc/pic30/communication/udp
endif
## New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/scicos/inc/core
INCLUDE_PATH += $(EEBASE)/contrib/scicos/inc
INCLUDE_PATH += $(EEBASE)/contrib/scicos/inc/pic30/communication/udp


##
## Application files
##

ifeq ($(call iseeopt, __NIOS2__), yes)

EE_SRCS +=      contrib/scicos/src/nios2/led.c \
        contrib/scicos/src/nios2/button.c \
        contrib/scicos/src/nios2/sevenseg.c 

endif

ifeq ($(call iseeopt, __EE_FLEX__), yes)

#If the  blocks list (from Scicos Code Generation) is empty, compile all the pic30 block sources
ifeq ($(EE_SRCS_SCICOS),)

EE_SRCS_SCICOS_DSPIC := $(addprefix contrib/scicos/src/pic30/, $(notdir $(shell ls -1 $(EEBASE)/contrib/scicos/src/pic30/*.c)))
EE_SRCS += $(EE_SRCS_SCICOS_DSPIC)

ifeq ($(findstring __LIB_IEEE802154__,$(LIB_OPT)),__LIB_IEEE802154__)
EE_SRCS_SCICOS_DSPIC_OPENZB := $(addprefix contrib/scicos/src/pic30/openzb/, $(notdir $(shell ls -1 $(EEBASE)/contrib/scicos/src/pic30/openzb/*.c)))
EE_SRCS += $(EE_SRCS_SCICOS_DSPIC_OPENZB)
endif

##
## Add Scicos to the linker list of libs
##
OPT_LIBS += -lscicos

else 

EE_SRCS += $(EE_SRCS_SCICOS)

ifeq ($(call iseeopt, __USE_DEMOBOARD__), yes)
EE_SRCS += contrib/scicos/src/pic30/flex_daughter.c
endif

ifeq ($(call iseeopt, __USE_MOTIONBOARD__), yes)
EE_SRCS += contrib/scicos/src/pic30/flex_daughter.c
endif

ifeq ($(call iseeopt, __USE_UDP__), yes)
EE_SRCS += contrib/scicos/src/pic30/communication/flex_udp.c
endif

ifeq ($(call iseeopt, __USE_CAN1__), yes)
EE_SRCS += contrib/scicos/src/pic30/communication/flex_can.c
endif

ifeq ($(call iseeopt, __USE_UART__), yes)
  ifeq ($(call iseeopt, __EE_UART_PORT1_CBUFFER__), yes)
    EE_SRCS += contrib/scicos/src/pic30/communication/easylab_serial.c
  endif #__EE_UART_PORT1_CBUFFER__
  ifeq ($(call iseeopt, __EE_UART_PORT2_CBUFFER__), yes)
    EE_SRCS += contrib/scicos/src/pic30/communication/easylab_serial.c
  endif #__EE_UART_PORT2_CBUFFER__
endif #__USE_UART__

ifeq ($(call iseeopt, __SCICOS_SMCUBE__), yes)
  EE_SRCS += $(shell ls -1 .. --ignore='*block.c' --ignore='*.h' | grep smcube_)
endif

endif

endif

#Add support for Easylab
ifeq ($(call iseeopt, __EE_EASYLAB__), yes)

EE_SRCS += $(EE_SRCS_SCICOS)

ifeq ($(call iseeopt, __USE_UART__), yes)
  ifeq ($(call iseeopt, __EE_UART_PORT1_CBUFFER__), yes)
    EE_SRCS += contrib/scicos/src/pic30/communication/easylab_serial.c
  endif #__EE_UART_PORT1_CBUFFER__
endif #__USE_UART__

ifeq ($(call iseeopt, __SCICOS_SMCUBE__), yes)
  EE_SRCS += $(shell ls -1 .. --ignore='*block.c' --ignore='*.h' | grep smcube_)
endif

endif #__EE_EASYLAB__

endif




