### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1277



############################################################################
#
# User options
#
############################################################################
EEOPT += DEBUG
EEOPT += __ASSERT__
EEOPT += __AUTOSAR_R4_0__
EEOPT += __AS_MCU_DRIVER__
EEOPT += __AS_PORT_DRIVER__
EEOPT += __AS_DIO_DRIVER__
EEOPT += __AS_SPI_DRIVER__
EEOPT += __AS_CFG_SPI_SYNCHRONOUS__
EEOPT += __AS_CFG_SPI_EXTERNAL_BUFFERS__
EEOPT += __ADD_LIBS__


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += __R5F5210x__
EEOPT += __RX200__
EEOPT += __CCRX__
EEOPT += __FP__
EEOPT += __MONO__
EEOPT += __FP_NO_RESOURCE__
EEOPT += __DISABLE_EEOPT_DEFINES__


############################################################################
#
# Erika base directory
#
############################################################################
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse\plugins\com.eu.evidence.ee_2.1.0.20130613_2011\ee_files'`)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))


############################################################################
#
# Renesas RX200
#
############################################################################
include $(EEBASE)/pkg/cfg/path_helper.mk
APPBASE := ..
OUTBASE := Debug

$(eval $(call check_and_set_cygwin_compiler_path,CCRX_ROOT,C:\Programmi\Renesas\Hew\Tools\Renesas\RX\1_2_0))


############################################################################
#
# Flags
#
############################################################################
CFLAGS  += 
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 

LIB_OPT  += __LIB_AUTOSAR__


############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c main.c Mcu_Cfg.c Port_Cfg.c Dio_Cfg.c Spi_Cfg.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
