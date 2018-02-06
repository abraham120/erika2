# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2012  Evidence Srl
# 
# This file is part of ERIKA Enterprise.
# 
# ERIKA Enterprise is free software; you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation, 
# (with a special exception described below).
# 
# Linking this code statically or dynamically with other modules is
# making a combined work based on this code.  Thus, the terms and
# conditions of the GNU General Public License cover the whole
# combination.
# 
# As a special exception, the copyright holders of this library give you
# permission to link this code with independent modules to produce an
# executable, regardless of the license terms of these independent
# modules, and to copy and distribute the resulting executable under
# terms of your choice, provided that you also meet, for each linked
# independent module, the terms and conditions of the license of that
# module.  An independent module is a module which is not derived from
# or based on this library.  If you modify this code, you may extend
# this exception to your version of the code, but you are not
# obligated to do so.  If you do not wish to do so, delete this
# exception statement from your version.
# 
# ERIKA Enterprise is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License version 2 for more details.
# 
# You should have received a copy of the GNU General Public License
# version 2 along with ERIKA Enterprise; if not, write to the
# Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA.
# ###*E*###

##
## Author: 2010 Dario Di Stefano 
##         2012 Giuseppe Serano
##

ifeq ($(call iseeopt, __CORTEX_MX__), yes)

ifneq ($(ENABLE_LIBS), TRUE)

ifeq ( \
  $(or $(call iseeopt, __LWIP_IPV4__), $(call iseeopt, __LWIP_IPV6__)), yes \
)

## Add the inc path to the include pathlist
ifeq ($(call iseeopt, __RTD_CYGWIN__), yes) 
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include)"
ifeq ($(call iseeopt, __LWIP_IPV4__), yes)
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv4)"
endif
ifeq ($(call iseeopt, __LWIP_IPV6__), yes)
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv6)"
endif
ALLINCPATH += -I"$(shell cygpath -w $(EEBASE)/contrib/lwip/lwip_1_3_2/abstraction/inc)"
else
ALLINCPATH += -I$(EEBASE)/contrib/lwip/lwip_1_3_2/src/include
ifeq ($(call iseeopt, __LWIP_IPV4__), yes)
ALLINCPATH += -I$(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv4
endif
ifeq ($(call iseeopt, __LWIP_IPV6__), yes)
ALLINCPATH += -I$(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv6
endif
ALLINCPATH += -I$(EEBASE)/contrib/lwip/lwip_1_3_2/abstraction/inc
endif
INCLUDE_PATH += $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include
ifeq ($(call iseeopt, __LWIP_IPV4__), yes)
INCLUDE_PATH += $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv4
endif
ifeq ($(call iseeopt, __LWIP_IPV6__), yes)
INCLUDE_PATH += $(EEBASE)/contrib/lwip/lwip_1_3_2/src/include/ipv6
endif
INCLUDE_PATH += $(EEBASE)/contrib/lwip/lwip_1_3_2/abstraction/inc

##
## Application files
##

# core ipv4
ifeq ($(call iseeopt, __LWIP_IPV4__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/autoip.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/icmp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/igmp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/inet.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/inet_chksum.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip_addr.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip_frag.c
endif

# core ipv6
ifeq ($(call iseeopt, __LWIP_IPV6__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/icmp6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/inet6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/ip6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/ip6_addr.c
endif

# core snmp
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/asn1_dec.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/asn1_enc.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/mib2.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/mib_structs.c 
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/msg_in.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/msg_out.c

# ARP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/etharp.c  

# LOOP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/loopif.c  

# SLIP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/slipif.c

# api
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/api_lib.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/api_msg.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/err.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netbuf.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netdb.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netifapi.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/sockets.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/tcpip.c

# core
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/dhcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/dns.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/init.c   
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/mem.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/memp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/netif.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/pbuf.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/raw.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/stats.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/sys.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp_in.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp_out.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/udp.c

# ppp
ifeq ($(call iseeopt, __LWIP_PPP_SUPPORT__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/auth.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/chap.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/chpms.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/fsm.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ipcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/lcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/magic.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/md5.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/pap.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ppp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ppp_oe.c    
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/randm.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/vj.c 
endif

# LWIP manager
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/ee_lwip.c
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/util/lwip_debug.c

# Ethernet interface
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_ethernet.c
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer.c

# enc28j60
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_enc28j60.c

EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer_cortex_mx.c

endif

endif

else	# __CORTEX_MX__

## Check the Console library selection
ifeq ($(findstring __LIB_LWIP__,$(LIB_OPT)),__LIB_LWIP__)

##
## Application files
##

# core ipv4
ifeq ($(call iseeopt, __LWIP_IPV4__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/autoip.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/icmp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/igmp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/inet.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/inet_chksum.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip_addr.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv4/ip_frag.c
endif

# core ipv6
ifeq ($(call iseeopt, __LWIP_IPV6__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/icmp6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/inet6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/ip6.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/ipv6/ip6_addr.c
endif

# core snmp
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/asn1_dec.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/asn1_enc.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/mib2.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/mib_structs.c 
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/msg_in.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/snmp/msg_out.c

# ARP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/etharp.c  

# LOOP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/loopif.c  

# SLIP
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/slipif.c

# api
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/api_lib.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/api_msg.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/err.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netbuf.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netdb.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/netifapi.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/sockets.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/api/tcpip.c

# core
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/dhcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/dns.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/init.c   
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/mem.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/memp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/netif.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/pbuf.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/raw.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/stats.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/sys.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp_in.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/tcp_out.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/core/udp.c

# ppp
ifeq ($(call iseeopt, __LWIP_PPP_SUPPORT__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/auth.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/chap.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/chpms.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/fsm.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ipcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/lcp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/magic.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/md5.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/pap.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ppp.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/ppp_oe.c    
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/randm.c  
EE_SRCS += contrib/lwip/lwip_1_3_2/src/netif/ppp/vj.c 
endif

# LWIP manager
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/ee_lwip.c
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/util/lwip_debug.c

# Ethernet interface
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_ethernet.c
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer.c

# enc28j60
ifeq ($(findstring __LIB_ENC28J60__,$(LIB_OPT)),__LIB_ENC28J60__)
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_enc28j60.c
endif

# smsc8720
ifeq ($(findstring __LIB_MAC_EXTPHY__,$(LIB_OPT)),__LIB_MAC_EXTPHY__)
ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_pic32mac.c
endif
endif

# lm32
ifeq ($(call iseeopt, __LM32__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer_mico32.c
endif

ifeq ($(call iseeopt, __PIC32__), yes)
EE_SRCS += contrib/lwip/lwip_1_3_2/abstraction/src/hal/lwip_timer_pic32.c
endif

endif

endif	# !__CORTEX_MX__