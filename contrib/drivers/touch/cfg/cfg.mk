## Author: 2009 Francesco Prosperi
## Check the Touch library selection
ifeq ($(findstring __LIB_TOUCH__,$(LIB_OPT)),__LIB_TOUCH__)

##
## Application files
##

EE_SRCS += contrib/drivers/touch/src/touch_1.c
EE_SRCS += contrib/drivers/touch/src/touch_1_timer_dspic30.c
EE_SRCS += contrib/drivers/touch/src/touch_1_kal_erika.c
EE_SRCS += contrib/drivers/touch/src/touch_2.c
EE_SRCS += contrib/drivers/touch/src/touch_2_timer_dspic30.c
EE_SRCS += contrib/drivers/touch/src/touch_2_kal_erika.c

endif
