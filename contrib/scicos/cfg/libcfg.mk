# ###*B*###
# Copyright (C) Roberto Bucher (SUPSI- Lugano)
#               Simone Mannori (Scilab / INRIA / DIGITEO)
#
# Copyright (C) METALAU Project (INRIA)
# ###*E*###
 
 
## Author: 2007 Mauro Marinoni
## CVS: $Id: libcfg.mk,v 1.5 2008/02/04 14:43:37 pj Exp $

ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_SCICOS = YES
endif

ifeq ($(findstring __LIB_SCICOS__,$(LIB_OPT)) , __LIB_SCICOS__)
INCLUDE_SCICOS = YES
endif

##
## If the Scicos library is required
##

ifeq ($(INCLUDE_SCICOS), YES)

## If the blocks list is empty, create the console lib
ifeq ($(EE_SRCS_SCICOS),)

EE_SRCS_SCICOS := $(addprefix contrib/scicos/libsrc/core/, $(notdir $(shell ls -1 $(EEBASE)/contrib/scicos/libsrc/core/*.c))) \
		  $(addprefix contrib/scicos/libsrc/rt/,   $(notdir $(shell ls -1 $(EEBASE)/contrib/scicos/libsrc/rt/*.c)))

EE_OBJS_SCICOS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_SCICOS))))

LIBSRCS += $(EE_SRCS_SCICOS)

libscicos.a: $(EE_OBJS_SCICOS)
	@printf "AR  libscicos.a\n" ;
	$(QUIET)$(EE_AR) rs libscicos.a $(EE_OBJS_SCICOS)

ALL_LIBS += libscicos.a
		  
endif

##
## Library code
##

endif
