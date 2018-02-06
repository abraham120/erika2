## Author: 2011 Gianluca Franchino

##Check if is the stack that we're asking for
ifeq ($(call iseeopt, __USE_LPC12XX_CMSIS_V2__), yes)
## Check the CMSIS library selection
ifeq ($(findstring __LIB_CMSIS__,$(LIB_OPT)) , __LIB_CMSIS__)
INCLUDE_LPC12XX_CMSIS_V2 = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_LPC12XX_CMSIS_V2 = YES
endif

endif

##
## If the library is required
##
ifeq ($(INCLUDE_LPC12XX_CMSIS_V2), YES)

##
## Library code
##
## Add the inc path to the include pathlist
##New include mechanism
INCLUDE_PATH += $(call short_native_path, $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/inc/CM0/CoreSupport)
INCLUDE_PATH += $(call short_native_path, $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/inc/CM0/DeviceSupport/NXP/LPC12xx)
INCLUDE_PATH += $(call short_native_path, $(EEBASE)/contrib/nxp/lpc12xx_cmsis_v2_0/inc/Drivers/include)
## Add each file individually
EE_SRCS_CMSIS :=

## If the file list is not empty, create the tcpip lib
ifneq ($(EE_SRCS_CMSIS),)
EE_OBJS_CMSIS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.s,%.o, $(EE_SRCS_CMSIS))))
LIBSRCS += $(EE_SRCS_CMSIS)

ifeq ($(call iseeopt, __IAR__), yes) 
libcmsis.a: $(EE_OBJS_CMSIS)
	@echo $(EE_SRC_CMSIS)
	@printf "AR  libcmsis.a\n" ;
	$(QUIET)$(EE_AR) --create $@ $^
OPT_LIBS += -ltcpip
ALL_LIBS += libtcpip.a
else
$(error Compiler not supported! Currently the only supported compiler is IAR.)
endif

endif

endif

