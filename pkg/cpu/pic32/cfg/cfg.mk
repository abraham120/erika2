ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += pkg/cpu/pic32/src/ee_hal.S
EE_SRCS += pkg/cpu/pic32/src/ee_hal_c.c
EE_SRCS += pkg/cpu/pic32/src/ee_utils.c

ifeq ($(call iseeopt, __OO_BCC1__), yes)
CPU_OO=YES
endif
ifeq ($(call iseeopt, __OO_BCC2__), yes)
CPU_OO=YES
endif
ifeq ($(call iseeopt, __OO_ECC1__), yes)
CPU_OO=YES
endif
ifeq ($(call iseeopt, __OO_ECC2__), yes)
CPU_OO=YES
endif

ifeq ($(CPU_OO), YES)
EE_SRCS += pkg/cpu/pic32/src/ee_oo.S
endif

endif
