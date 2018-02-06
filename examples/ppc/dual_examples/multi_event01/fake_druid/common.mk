

############################################################################
#
# Makefile created by RT-Druid
# 
# Common file
#
############################################################################

# Erika base directory
ifneq ($(__ERIKA_INNER_MAKEFILE_CALL__), yes)
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := ${ERIKA_FILES}

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := /home/francesco/Evidence/eclipse/plugins/com.eu.evidence.ee_1.6.0.20111215_1046/ee_files
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=

endif # __ERIKA_INNER_MAKEFILE_CALL__


RTDRUID_CONFIGURATOR_NUMBER:=1276



############################################################################
#
# Common EE options
#
############################################################################
EEOPT += 
EEOPT += __ASSERT__
EEOPT += __E200ZX_EXECUTE_FROM_RAM__
EEOPT += DEBUG
EEOPT += USE_PRAGMAS
EEOPT += __RTD_LINUX__
EEOPT += __MSRP__
EEOPT += __PPCE200ZX__
EEOPT += __MPC5668G__
EEOPT += __OO_ECC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MULTI__
EEOPT += __OO_HAS_USERESSCHEDULER__
EEOPT += __DISABLE_EEOPT_DEFINES__



############################################################################
#
# Flags
#
############################################################################
CFLAGS   = 

ASFLAGS  = 

LDFLAGS := 

LDDEPS  += 

LIBS    := 

