## Author: 2007 Antonio Romano
## CVS: $Id: 

##
## Only for AVR5 and AVR8 cpu
##
ifneq (($or ($(call iseeopt, __AVR5__), yes), ($(call iseeopt, __AVR8__), yes)),)

ifeq ($(findstring __LIB_ATMEL802154__,$(LIB_OPT)) , __LIB_ATMEL802154__)
INCLUDE_ATMEL802154 = YES
endif

ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_ATMEL802154 = YES
endif

endif

##
## If the Atmel lib is required
##
ifeq ($(INCLUDE_ATMEL802154), YES)

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/atmel802_15_4/inc)"
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/atmel802_15_4/libsrc/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/atmel802_15_4/inc
ALLINCPATH += -I$(EEBASE)/contrib/atmel802_15_4/libsrc/inc
endif
## New include mechanism
INCLUDE_PATH += $(EEBASE)/contrib/atmel802_15_4/inc
INCLUDE_PATH += $(EEBASE)/contrib/atmel802_15_4/libsrc/inc

##
## Library code
##

EE_SRCS_ATMEL802154 := contrib/atmel802_15_4/libsrc/bios/bios.c \
		contrib/atmel802_15_4/libsrc/bios/board_rdk230.c \
		contrib/atmel802_15_4/libsrc/bios/crc16.c \
		contrib/atmel802_15_4/libsrc/bios/hif_rf230.c \
		contrib/atmel802_15_4/libsrc/bios/queue.c \
		contrib/atmel802_15_4/libsrc/bios/timer.c \
		contrib/atmel802_15_4/libsrc/bios/timer_m128.c \
		contrib/atmel802_15_4/libsrc/mac/associate.c \
		contrib/atmel802_15_4/libsrc/mac/beacon.c \
		contrib/atmel802_15_4/libsrc/mac/buffer.c \
		contrib/atmel802_15_4/libsrc/mac/csma_ca.c \
		contrib/atmel802_15_4/libsrc/mac/data_ind.c \
		contrib/atmel802_15_4/libsrc/mac/data_req.c \
		contrib/atmel802_15_4/libsrc/mac/disassociate.c \
		contrib/atmel802_15_4/libsrc/mac/mcps_data.c \
		contrib/atmel802_15_4/libsrc/mac/misc.c \
		contrib/atmel802_15_4/libsrc/mac/orphan.c \
		contrib/atmel802_15_4/libsrc/mac/pib.c \
		contrib/atmel802_15_4/libsrc/mac/plme_conf.c \
		contrib/atmel802_15_4/libsrc/mac/poll.c \
		contrib/atmel802_15_4/libsrc/mac/process_ack_frame.c \
		contrib/atmel802_15_4/libsrc/mac/process_beacon_frame.c \
		contrib/atmel802_15_4/libsrc/mac/rx_enable.c \
		contrib/atmel802_15_4/libsrc/mac/scan.c \
		contrib/atmel802_15_4/libsrc/mac/start.c \
		contrib/atmel802_15_4/libsrc/mac/sync.c \
		contrib/atmel802_15_4/libsrc/mac/tx_coord_realignment_command.c \
		contrib/atmel802_15_4/libsrc/phy/phy230.c \
		contrib/atmel802_15_4/libsrc/misc/api_mac.c \
		contrib/atmel802_15_4/libsrc/misc/dispatcher.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mcps_data_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_associate_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_disassociate_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_gts_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_poll_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_scan_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_sync_loss_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_plme_cca_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_plme_set_conf.c \
		contrib/atmel802_15_4/libsrc/misc/callback_wrapper.c \
		contrib/atmel802_15_4/libsrc/misc/usr_hal_radio_irq.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mcps_purge_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_beacon_notify_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_disassociate_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_gts_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_reset_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_set_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_pd_data_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_plme_ed_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_plme_set_trx_state_conf.c \
		contrib/atmel802_15_4/libsrc/misc/cmdif.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mcps_data_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_associate_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_comm_status_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_get_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_orphan_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_rx_enable_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_mlme_start_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_pd_data_ind.c \
		contrib/atmel802_15_4/libsrc/misc/usr_plme_get_conf.c \
		contrib/atmel802_15_4/libsrc/misc/usr_timer_trigger.c 


EE_OBJS_ATMEL802154 := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_ATMEL802154))))

ALLINCPATH += -I"$(EEBASE)/contrib/atmel802_15_4/inc" -I"$(EEBASE)/contrib/atmel802_15_4/libsrc/inc"  -I.

LIBSRCS += $(EE_SRCS_ATMEL802154)
		
libZigbEE.a: $(EE_OBJS_ATMEL802154)
	@printf "AR    libZigbEE.a\n" ;
	$(QUIET)$(EE_AR) crs libZigbEE.a $(EE_OBJS_ATMEL802154)
	
ALL_LIBS += libZigbEE.a

endif
