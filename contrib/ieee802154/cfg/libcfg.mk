#########################################################################
#
# Project: ERIKA Enterprise and Open-ZB 
#          ZigBee compliant network stack for ERIKA Enterprise
#
# Coordinators:
#   Giuseppe Lipari    	<lipari@sssup.it>
#   Eduardo Tovar       <emt@dei.isep.ipp.pt>
#   Mario Alves	        <mjs@isep.ipp.pt>
#
# Authors:
#   Andre Cunha            <andreribeirocunha@gmail.com>
#   Mangesh Chitnis        <m.chitnis@sssup.it>
#   Antonio Romano         <a.romano@sssup.it>
#   Ricardo Severino       <rars@isep.ipp.pt>
#   Paolo Pagano           <p.pagano@sssup.it>
#   Christian Nastasi      <nastasichr@gmail.com>
#
# ReTiS Lab (CEIIC, Scuola Superiore S.Anna - Pisa - Italy)
# IPP-Hurray (Polytechnique Institute of Porto - Portugal)
#
# http://retis.sssup.it
# http://www.hurray.isep.ipp.pt
#
#########################################################################
#
# Copyright (C) 2008 Andre Cunha, Mangesh Chitnis 
#                    Antonio Romano, Ricardo Severino
#                    Paolo Pagano, Christian Nastasi
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#########################################################################
#
# CVS: 
#
# $Id: libcfg.mk,v 1.8 2008/07/14 10:48:34 chris Exp $
# $Log: libcfg.mk,v $
# Revision 1.8  2008/07/14 10:48:34  chris
# Adapting to the new common files moved into the ieee802154 library tree
#
# Revision 1.7  2008/07/04 09:47:25  chris
# INFO: Add commented header (project description, licence, people) to files.
#
#
#########################################################################
ifeq ($(findstring __LIB_IEEE802154__,$(LIB_OPT)) , __LIB_IEEE802154__)
INCLUDE_IEEE802154 = YES
endif

ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_IEEE802154 = YES
endif

##
## If the IEEE802154lib is required
##
ifeq ($(INCLUDE_IEEE802154), YES)

##
## Library code
##

EE_SRCS_IEEE802154:= contrib/ieee802154/libsrc/phy/PD_DATA.c \
					contrib/ieee802154/libsrc/phy/PLME_CCA.c \
					contrib/ieee802154/libsrc/phy/PLME_ED.c \
					contrib/ieee802154/libsrc/phy/PLME_GET.c \
					contrib/ieee802154/libsrc/phy/PLME_SET.c \
					contrib/ieee802154/libsrc/phy/PLME_SET_TRX_STATE.c \
					contrib/ieee802154/libsrc/phy/Phy.c \
					contrib/ieee802154/libsrc/mac/Mac.c \
					contrib/ieee802154/libsrc/mac/MLME_START.c \
					contrib/ieee802154/libsrc/mac/MLME_GET.c \
					contrib/ieee802154/libsrc/mac/MLME_SET.c \
					contrib/ieee802154/libsrc/mac/MLME_ASSOCIATE.c \
					contrib/ieee802154/libsrc/mac/MCPS_DATA.c \
					contrib/ieee802154/libsrc/mac/mac_func.c \
					contrib/ieee802154/libsrc/nwl/Nwl.c \
					contrib/ieee802154/libsrc/ieee802154alarms/ieee802154alarms.c \
					contrib/ieee802154/libsrc/hal/hal_cc2420.c \
					contrib/ieee802154/libsrc/hal/hal_interrupts.c \
					contrib/ieee802154/libsrc/common/cc2420.c \
					contrib/ieee802154/libsrc/common/console.c \
					contrib/ieee802154/libsrc/common/ee_radio_spi.c \
					contrib/ieee802154/libsrc/common/eeuart.c \
					contrib/ieee802154/libsrc/common/netbuff.c \
					contrib/ieee802154/libsrc/common/queue.c 
					

EE_OBJS_IEEE802154:= $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(patsubst %.S,%.o, $(EE_SRCS_IEEE802154))))


LIBSRCS += $(EE_SRCS_IEEE802154)
		
libieee802154.a: $(EE_OBJS_IEEE802154)
	@printf "AR  libieee802154.a\n" ;
	$(QUIET)$(EE_AR) rs libieee802154.a $(EE_OBJS_IEEE802154)
	
ALL_LIBS += libieee802154.a



endif
