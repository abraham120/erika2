ifeq ($(call iseeopt, __IPERMOB_BOARD_V2__), yes)

#ifeq ($(call iseeopt, __USE_BUTTONS__), yes)
#EE_SRCS += pkg/board/ipermob_mb_pic32/src/ee_board.c
#endif



#ifeq ($(call iseeopt, USE_HV7131GP), yes)
#EE_SRCS += pkg/board/ipermob_mb_pic32/src/ee_ethernet_enc28j60.c
#endif


endif # __IPERMOB_BOARD_V2__
