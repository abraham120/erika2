ifeq ($(call iseeopt, __IPERMOB_DB_PIC32__), yes)

ifeq ($(call iseeopt, __USE_BUTTONS__), yes)
#EE_SRCS += pkg/board/ipermob_db_pic32/src/ee_board.c
endif

endif # __IPERMOB_DB_PIC32__
