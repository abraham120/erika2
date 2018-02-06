## Author: 2011 Riccardo Schiavi

##Check if is the stack that we're asking for
ifeq ($(call iseeopt, __USE_MCHP_TCPIP_531__), yes)
## Check the Console library selection
ifeq ($(findstring __LIB_TCPIP__,$(LIB_OPT)) , __LIB_TCPIP__)
INCLUDE_TCPIP_531 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_TCPIP_531 = YES
endif
endif

##
## If the library is required
##
ifeq ($(INCLUDE_TCPIP_531), YES)

##
## Library code
##
## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/microchip/tcpip_531/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/microchip/tcpip_531/inc
endif
##New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/microchip/tcpip_531/inc

## Add each file individually
#EE_SRCS_TCPIP_TMP = $(shell ls $(EEBASE)/contrib/microchip/tcpip_531/libsrc/*.c)
#EE_SRCS_TCPIP_TMP += $(shell ls $(EEBASE)/contrib/microchip/tcpip_531/libsrc/WiFi/*.c)
EE_SRCS_TCPIP :=

## If the file list is not empty, create the tcpip lib
ifneq ($(EE_SRCS_TCPIP),)
EE_OBJS_TCPIP := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_TCPIP))))
LIBSRCS += $(EE_SRCS_TCPIP)
libtcpip.a: $(EE_OBJS_TCPIP)
	@echo $(EE_SRC_TCPIP)
	@printf "AR  libtcpip.a\n" ;
	$(QUIET)$(EE_AR) rs libtcpip.a $(EE_OBJS_TCPIP)
OPT_LIBS += -ltcpip
ALL_LIBS += libtcpip.a
endif

endif

$(RS: info ALLINCPATH: $(ALLINCPATH))