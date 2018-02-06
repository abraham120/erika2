# makemodel.mk - elaborate, compile and link a CAL network/model
#                Assumed to be used in sub-make from main Makefile
# Modified for integration on Erika toolchain
# Author: Antonio Marcello Catinella
# Date:	  2011

# delete the built-in suffixes to avoid surprises
.SUFFIXES:   

ifeq "$(strip $(MODEL))" ""
  $(error MODEL not set)
endif

srcdir?=.

MODEL_PATH=$(SRCDIR_ABS):$(CAL_BASE)/share/sysactors/cal:$(EEBASE)/contrib/cal/src

# Dependences of MODEL (re-generated if necessary)
ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
-include $(OUTPUT_DIR)/$(MODEL).depend
endif


# Default definitions of tools and directories
include $(EEBASE)/contrib/cal/cfg/definitions.mk

# Include path needed in Erika toolchain
INCLUDE_PATH += $(ACTORS_INCLUDE)

ifdef MERGE
override MODEL_DEPEND = $(OUTPUT_DIR)/$(MODEL)_new.xdf
else
override MODEL_DEPEND = $(OUTPUT_DIR)/$(MODEL).xdf
endif

#
# We get the actor instances from the CALML-files 
# (we have to do elaboration first, to get *.calml).
#

ACTOR_C_FILES=$(addprefix $(OUTPUT_DIR)/, $(XLIM_FILES:.xlim=.c))
PAR_FILES=$(XLIM_FILES:.xlim=.par)
EXTRA_OBJECTS=$(notdir $(C_FILES:.c=.o))
OBJECTS=$(ACTOR_C_FILES:.c=.o) $(EXTRA_OBJECTS) $(SYS_OBJECTS)
CAL_OBJS_FILES=$(addprefix $(OBJDIR)/, $(OBJECTS))
OBJS+=$(CAL_OBJS_FILES)

#
# Construction of libactors.a library based on the $(SYS_ACTORS_OBJS) which have to be added to the compiling chain
#
LIBACTORS=$(OUTPUT_DIR)/libactors.a
LIBDEP+=$(LIBACTORS)
LDFLAGS+=-lactors -lee

$(LIBACTORS): $(SYS_ACTORS_OBJS)
	@echo "AR    $(notdir $@)"
	$(QUIET)$(AR) $(ARFLAGS) $@ $^ $(VERBOSE_DEVNULL)

# Preserve generated C files (make otherwise considers them temporary files)
.SECONDARY: $(ACTOR_C_FILES)

$(OUTPUT_DIR)/%.c : %.xlim
	$(QUIET) $(XLIM2C) $< $@ $(VERBOSE_DEVNULL)

SRCS +=$(addprefix $(OUTPUT_DIR)/, $(MODEL).c) $(ACTOR_C_FILES)

#
# Generate network configuration from .xdf
#
$(OUTPUT_DIR)/$(MODEL).c: $(MODEL_DEPEND)
	@echo "CAL2C $(addsuffix .nl, $(MODEL))"
	$(QUIET) $(SAXON8) -o $@.tmp $< $(GENERATECONFIG_XSL) $(VERBOSE_DEVNULL)
	$(QUIET) gawk '{$$0=gensub(/int main/,"void main_cal", "g");print $$0}' <$@.tmp > $@ && rm $@.tmp

#
# If enabled, run model compiler
#
$(OUTPUT_DIR)/$(MODEL)_new.xdf: $(OUTPUT_DIR)/$(MODEL).xdf $(XLIM_FILES)
	$(MODELCOMPILER) $(OUTPUT_DIR)/$(MODEL).xdf
	@cp $(OUTPUT_DIR)/$(MODEL)_new.xdf $(OUTPUT_DIR)/$(MODEL).xdf
	@touch$ $(OUTPUT_DIR)/$(MODEL).timestamp

#
# Generate .xlim from .cal and .par
# (dependence of .xlim on .cal and .par is given by $(OUTPUT_DIR)/$(MODEL).depend)
#
$(XLIM_FILES): %.xlim :
	@echo "CAL2C $(*F)"
	@if ! [ -r $(OUTPUT_DIR)/$(MODEL).depend ]; then echo >&2 "Missing "; false; fi
	$(QUIET) $(SSAGENERATOR) -mp "$(srcdir)" `cat $(basename $(@F)).par` $(<F) $(VERBOSE_DEVNULL)
	$(QUIET) mv $(basename $(<F)).xlim $@


#
# Generate parameter (.par) files from $(OUTPUT_DIR)/$(MODEL).xdf
# (dependence of .par files on $(OUTPUT_DIR)/$(MODEL).xdf via $(OUTPUT_DIR)/$(MODEL).timestamp)
#

$(PAR_FILES): $(OUTPUT_DIR)/$(MODEL).timestamp

$(OUTPUT_DIR)/$(MODEL).timestamp: $(OUTPUT_DIR)/$(MODEL).xdf
	$(QUIET) $(XDF2PAR) $< $(VERBOSE_DEVNULL)
	@touch $@

#
# Generate dependences from .xdf
#
$(OUTPUT_DIR)/$(MODEL).depend: $(OUTPUT_DIR)/$(MODEL).xdf
	$(QUIET) $(SAXON8) -o $@ $< $(XDF2DEPEND_XSL) $(VERBOSE_DEVNULL)


#
# Generate xdf from network (nl) files
# (dependence of $(OUTPUT_DIR)/$(MODEL).xdf on network (.nl) files is
#  given in $(OUTPUT_DIR)/$(MODEL).depend).
#
$(OUTPUT_DIR)/$(MODEL).xdf: $(srcdir)/$(MODEL).nl $(SUB_NETWORKS)
	$(QUIET) $(ELABORATOR) -mp $(MODEL_PATH) $(MODEL) $(VERBOSE_DEVNULL)
	$(QUIET) mv $(MODEL).xdf $(OUTPUT_DIR)
