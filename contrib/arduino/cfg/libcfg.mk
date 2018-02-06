# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2016  Evidence Srl
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

###
### Author: 2016,  Giuseppe Serano
##

##Check if is the stack that we're asking for
ifeq ($(call iseeopt, __ARDUINO_SDK__), yes)

## Check the Arduino library selection
ifeq ($(findstring __LIB_ARDUINO_SDK__,$(LIB_OPT)) , __LIB_ARDUINO_SDK__)
INCLUDE_ARDUINO_SDK = YES
endif

## Check if it's selected all libs inclusion
ifeq ($(call iseeopt, __BUILD_ALL_LIBS__), yes)
INCLUDE_ARDUINO_SDK = YES
endif

##
## If the library is required
##
ifeq ($(INCLUDE_ARDUINO_SDK), YES)

ifndef	ARDUINO_SDK_FILES
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC_1_6_10__), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.6.10
else	# __ARDUINO_SDK_CC_1_6_10__
ifeq ($(call iseeopt, __ARDUINO_SDK_CC_1_6_9__), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.6.9
else	# __ARDUINO_SDK_CC_1_6_9__
export	ARDUINO_SDK_FILES = C:/arduino-1.6.8
endif	# __ARDUINO_SDK_CC_1_6_9__
endif	# __ARDUINO_SDK_CC_1_6_10__
else	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.7.10
else	# __ARDUINO_SDK_ORG_1_7_10__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_9__), yes)
export	ARDUINO_SDK_FILES = C:/arduino-1.7.9
else	# __ARDUINO_SDK_ORG_1_7_9__
export	ARDUINO_SDK_FILES = C:/arduino-1.7.8
endif	# __ARDUINO_SDK_ORG_1_7_9__
endif	# __ARDUINO_SDK_ORG_1_7_10__
else	# __ARDUINO_SDK_ORG__
export	ARDUINO_SDK_FILES = C:/arduino-1.0.5-r2
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_CC__
endif	# ARDUINO_SDK_FILES

ifeq ($(call iseeopt, __RTD_LINUX__), yes)
ARDUINO_SDK_ROOT := \
		$(call short_native_path, $(ARDUINO_SDK_FILES))
else
#ARDUINO_SDK_ROOT := \
#		$(shell cygpath $(call short_native_path, $(ARDUINO_SDK_FILES)))
ARDUINO_SDK_ROOT := \
		$(call short_native_path, $(ARDUINO_SDK_FILES))
endif

EE_VPATH += $(ARDUINO_SDK_ROOT)

ifeq ($(or	\
		$(call iseeopt, __ARDUINO_SDK_CC__),	\
		$(call iseeopt, __ARDUINO_SDK_ORG__)	\
	), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC_1_6_10__), yes)
EEOPT += ARDUINO=10610
else	# __ARDUINO_SDK_CC_1_6_10__
ifeq ($(call iseeopt, __ARDUINO_SDK_CC_1_6_9__), yes)
EEOPT += ARDUINO=10609
else	# __ARDUINO_SDK_CC_1_6_9__
EEOPT += ARDUINO=10608
endif	# __ARDUINO_SDK_CC_1_6_9__
endif	# __ARDUINO_SDK_CC_1_6_10__
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
EEOPT += ARDUINO=10710
else	# __ARDUINO_SDK_ORG_1_7_10__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_9__), yes)
EEOPT += ARDUINO=10709
else	# __ARDUINO_SDK_ORG_1_7_9__
EEOPT += ARDUINO=10708
endif	# __ARDUINO_SDK_ORG_1_7_9__
endif	# __ARDUINO_SDK_ORG_1_7_10__
endif	# __ARDUINO_SDK_ORG__
ifeq	($(call iseeopt, __ARDUINO_UNO_328__),yes)
EEOPT += ARDUINO_AVR_UNO
endif	# __ARDUINO_UNO_328__
ifeq	($(call iseeopt, __ARDUINO_NANO_328__),yes)
EEOPT += ARDUINO_AVR_NANO
endif	# __ARDUINO_NANO_328__
EEOPT += ARDUINO_ARCH_AVR
else	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
EEOPT += ARDUINO=105
endif	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__

##
## Library code
##
## Add the inc path to the include pathlist
## New include mechanism

ifeq ($(or	\
		$(call iseeopt, __ARDUINO_SDK_CC__),	\
		$(call iseeopt, __ARDUINO_SDK_ORG__)	\
	), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/cores/arduino	\
		$(INCLUDE_PATH)
else	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/cores/arduino	\
		$(INCLUDE_PATH)
endif	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__

ifeq	($(call iseeopt, __ARDUINO_UNO_328__), yes)
ifeq ($(or	\
		$(call iseeopt, __ARDUINO_SDK_CC__),	\
		$(call iseeopt, __ARDUINO_SDK_ORG__)	\
	), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/variants/standard	\
		$(INCLUDE_PATH)
else	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/variants/standard	\
		$(INCLUDE_PATH)
endif	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
endif	# __ARDUINO_UNO_328__

ifeq	($(call iseeopt, __ARDUINO_NANO_328__), yes)
ifeq ($(or	\
		$(call iseeopt, __ARDUINO_SDK_CC__),	\
		$(call iseeopt, __ARDUINO_SDK_ORG__)	\
	), yes)
INCLUDE_PATH :=	\
	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/variants/eightanaloginputs	\
	$(INCLUDE_PATH)
else	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
INCLUDE_PATH :=	\
	$(ARDUINO_SDK_ROOT)/hardware/arduino/variants/eightanaloginputs	\
	$(INCLUDE_PATH)
endif	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__
endif	# __ARDUINO_NANO_328__

ifeq	($(call iseeopt, __ARDUINO_SDK_SIMUL__), yes)
EEOPT += F_CPU=1000000UL
else
EEOPT += F_CPU=16000000UL
endif

ifeq	($(call iseeopt, __ATMEGA__), yes)

ifeq	($(call iseeopt, __AVR8__), yes)

ifeq ($(or	\
		$(call iseeopt, __ARDUINO_SDK_CC__),	\
		$(call iseeopt, __ARDUINO_SDK_ORG__)	\
	), yes)

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/hooks.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_digital.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_analog.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_pulse.c

ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_pulse.S
endif	# __ARDUINO_SDK_CC__

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/wiring_shift.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/WInterrupts.c

ifeq	($(call iseeopt, __ARDUINO_SDK_PCINT__), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/WPCInterrupts.c
endif	# __ARDUINO_SDK_PCINT__

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/abi.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/CDC.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial0.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial1.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial2.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HardwareSerial3.cpp

ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/HID.cpp
endif	# __ARDUINO_SDK_ORG__

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/IPAddress.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/new.cpp

ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/PluggableUSB.cpp
endif	# __ARDUINO_SDK_CC__

EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/Print.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/Stream.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/Tone.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/USBCore.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/WMath.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/cores/arduino/WString.cpp

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ARDUINO_WIFI__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/ArduinoWiFi/src		\
		$(ARDUINO_SDK_ROOT)/libraries/ArduinoWiFi/src/lib	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/ArduinoWiFi.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/crc16.c
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/espduino.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/FP.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/rest.cpp
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/ringbuf.c
EE_SRCS_ARDUINO_SDK += libraries/ArduinoWiFi/src/lib/SC16IS750.cpp
endif	# __ARDUINO_SDK_ORG_1_7_10__
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_ARDUINO_WIFI__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_BRACCIO__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_9__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Braccio/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/Braccio.cpp
endif	# __ARDUINO_SDK_ORG_1_7_9__
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_BRACCIO__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_BRIDGE__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Bridge/src \
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/Bridge.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/Console.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/FileIO.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/HttpClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/MailBox.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/Process.cpp
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeUdp.cpp
ifeq ($(call iseeopt, __ARDUINO_SDK_CC_1_6_9__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/BridgeSSLClient.cpp
endif	# __ARDUINO_SDK_CC_1_6_9__
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/YunClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Bridge/src/YunServer.cpp
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_BRIDGE__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_CIAO__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ciao/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ciao/src/lib	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/Ciao.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/crc16.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/espduino.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/FP.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/rest.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/ringbuf.c
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/SC16IS750.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/wifi.cpp
else	# __ARDUINO_SDK_ORG_1_7_10__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_9__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ciao/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ciao/src/lib	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/Ciao.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/crc16.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/espduino.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/FP.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/rest.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/ringbuf.c
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/SC16IS750.cpp
EE_SRCS_ARDUINO_SDK += libraries/Braccio/src/lib/UnowifiCiao.cpp
else	# __ARDUINO_SDK_ORG_1_7_9__
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ciao/src		\
		$(INCLUDE_PATH)
EE_SRCS += libraries/Braccio/src/Ciao.cpp
endif	# __ARDUINO_SDK_ORG_1_7_9__
endif	# __ARDUINO_SDK_ORG_1_7_10__
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_CIAO__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_EEPROM__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/EEPROM/src \
		$(INCLUDE_PATH)
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/EEPROM \
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/EEPROM/EEPROM.cpp
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_EEPROM__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ESPLORA__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Esplora/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Esplora/src/Esplora.cpp
endif	# __ARDUINO_SDK_LIB_ESPLORA__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ETHERNET__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ethernet/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ethernet/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/Dhcp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/Dns.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/Ethernet.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/EthernetClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/EthernetServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/EthernetUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/utility/socket.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/src/utility/w5100.cpp
endif	# __ARDUINO_SDK_LIB_ETHERNET__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ETHERNET2__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ethernet2/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Ethernet2/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Dhcp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Dns.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Ethernet2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/EthernetClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/EthernetServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/EthernetUdp2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/Twitter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/utility/socket.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet2/src/utility/w5500.cpp
endif	# __ARDUINO_SDK_LIB_ETHERNET2__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_FIRMATA__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Firmata		\
		$(ARDUINO_SDK_ROOT)/libraries/Firmata/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Firmata/Firmata.cpp
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/EthernetClientStream.cpp
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/SerialFirmata.cpp
ifeq ($(call iseeopt, __ARDUINO_SDK_CC_1_6_10__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/BLEStream.cpp
else	# __ARDUINO_SDK_CC_1_6_10__
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/WiFi101Stream.cpp
endif	# __ARDUINO_SDK_CC_1_6_10__
EE_SRCS_ARDUINO_SDK += libraries/Firmata/utility/WiFiStream.cpp
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Firmata		\
		$(ARDUINO_SDK_ROOT)/libraries/Firmata/utility	\
		$(INCLUDE_PATH)
EE_SRCS += libraries/Firmata/utility/BLEStream.cpp
EE_SRCS += libraries/Firmata/utility/EthernetClientStream.cpp
EE_SRCS += libraries/Firmata/utility/SerialFirmata.cpp
EE_SRCS += libraries/Firmata/utility/WiFi101Stream.cpp
EE_SRCS += libraries/Firmata/utility/WiFiStream.cpp
EE_SRCS += libraries/Firmata/Firmata.cpp
else	# __ARDUINO_SDK_ORG_1_7_10__
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Firmata/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Firmata/src/Firmata.cpp
endif	# __ARDUINO_SDK_ORG_1_7_10__
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_FIRMATA__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_GSM__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/GSM/src		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3CircularBuffer.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileAccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileCellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileDataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileMockupProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkRegistry.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileSMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileVoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1AccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BandManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BaseProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1CellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DirectModemProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemCore.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemVerification.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1PinManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ScanNetworks.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1SMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1VoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SMSService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SoftSerial.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3VoiceCallService.cpp
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_9__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/GSM/src \
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3CircularBuffer.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileAccessProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileCellManagement.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileClientProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileClientService.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileDataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileMockupProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileNetworkRegistry.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileServerProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileServerService.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileSMSProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3MobileVoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1AccessProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1BandManagement.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1BaseProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1CellManagement.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ClientProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1DataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1DirectModemProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ModemCore.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ModemVerification.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1MultiClientProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1MultiServerProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1PinManagement.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ScanNetworks.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1ServerProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1SMSProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV1VoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3ShieldV2.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3SMSService.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3SoftSerial.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/GSM/src/GSM3VoiceCallService.cpp
else	# __ARDUINO_SDK_ORG_1_7_9__
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/GSM/src \
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3CircularBuffer.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileAccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileCellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileClientService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileDataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileMockupProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileNetworkRegistry.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileServerService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileSMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3MobileVoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1AccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BandManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1BaseProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1CellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1DirectModemProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemCore.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ModemVerification.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1MultiServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1PinManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ScanNetworks.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1ServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1SMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV1VoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3ShieldV2.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SMSService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3SoftSerial.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/src/GSM3VoiceCallService.cpp
endif	# __ARDUINO_SDK_ORG_1_7_9__
endif	# __ARDUINO_SDK_ORG__
endif	#__ARDUINO_SDK_LIB_GSM__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_HID__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/HID/src \
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/HID/src/HID.cpp
endif	# __ARDUINO_SDK_CC__
endif	# __ARDUINO_SDK_LIB_HID__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_KEYBOARD__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Keyboard/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Keyboard/src/Keyboard.cpp
endif	# __ARDUINO_SDK_CC__
endif	# __ARDUINO_SDK_LIB_KEYBOARD__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_LIQUID_CRYSTAL__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/LiquidCrystal/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/LiquidCrystal/src/LiquidCrystal.cpp
endif	# __ARDUINO_SDK_LIB_LIQUID_CRYSTAL__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_LUCKY_SHIELD__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_9__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/LuckyShield/src		\
		$(ARDUINO_SDK_ROOT)/libraries/LuckyShield/src/lib	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/Adafruit_SSD1306.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/BME280.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/CAT9555.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/glcdfont.cpp
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/MAG3110.c
EE_SRCS_ARDUINO_SDK += libraries/LuckyShield/src/lib/MMA8491Q.cpp
endif	# __ARDUINO_SDK_ORG_1_7_9__
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_LUCKY_SHIELD__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_MOUSE__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Mouse/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Keyboard/src/Mouse.cpp
endif	# __ARDUINO_SDK_CC__
endif	# __ARDUINO_SDK_LIB_MOUSE__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_N_AXES_MOTION__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/NAxesMotion/		\
		$(ARDUINO_SDK_ROOT)/libraries/NAxesMotion/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/NAxesMotion/NAxesMotion.cpp
EE_SRCS_ARDUINO_SDK += libraries/NAxesMotion/utility/BNO055.c
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_N_AXES_MOTION__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_REST__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
ifneq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Rest/src		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Rest/src/rest.cpp
endif	# !__ARDUINO_SDK_ORG_1_7_10__
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_REST__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ROBOT_CONTROL__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Robot_Control/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Robot_Control/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Arduino_LCD.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/ArduinoRobot.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/communication.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Compass.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/EasyTransfer2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/EEPROM_I2C.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Fat16.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/glcdfont.c
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/helper.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/information.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/keyboard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/lcd.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Melody.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Motors.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Multiplexer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/RobotSdCard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/SdCard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Sensors.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/Squawk.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/SquawkSD.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/utility/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/utility/RobotTextManager.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/src/utility/VirtualKeyboard.cpp
endif	# __ARDUINO_SDK_LIB_ROBOT_CONTROL__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ROBOT_MOTOR__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Robot_Motor/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/ArduinoRobotMotorBoard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/EasyTransfer2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/lineFellow.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/src/Multiplexer.cpp
endif	# __ARDUINO_SDK_LIB_ROBOT_MOTOR__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ROBOT_IREMOTE__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/RobotIRemote/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/RobotIRemote/src/IRemote.cpp
EE_SRCS_ARDUINO_SDK += libraries/RobotIRemote/src/IRemoteTools.cpp
endif	# __ARDUINO_SDK_LIB_ROBOT_IREMOTE__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_RTC__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/RTC/src		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/RTC/src/RTCInt.cpp
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_RTC__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SCHEDULER__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Scheduler/src		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Scheduler/src/Scheduler.cpp
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_SCHEDULER__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SD__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/SD/src		\
		$(ARDUINO_SDK_ROOT)/libraries/SD/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/SD/src/File.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/SD.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/utility/Sd2Card.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/utility/SdFile.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/src/utility/SdVolume.cpp
endif	#__ARDUINO_SDK_LIB_SD__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SERVO__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Servo/src \
		$(ARDUINO_SDK_ROOT)/libraries/Servo/src/avr \
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Servo/src/avr/Servo.cpp
endif	#__ARDUINO_SDK_LIB_SERVO__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SOFTWARE_SERIAL__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SoftwareSerial/src	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SoftwareSerial/src/SoftwareSerial.cpp
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SoftwareSerial	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SoftwareSerial/SoftwareSerial.cpp
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_SOFTWARE_SERIAL__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SPI__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SPI/src	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SPI/src/SPI.cpp
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/SPI	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/SPI/SPI.cpp
endif	# __ARDUINO_SDK_ORG__
endif	#__ARDUINO_SDK_LIB_SPI__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SPACEBREW_YUN__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/SpacebrewYun/src	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/SpacebrewYun/src/SpacebrewYun.cpp
endif	# __ARDUINO_SDK_LIB_SPACEBREW_YUN__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_STEPPER__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Stepper/src	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Stepper/src/Stepper.cpp
endif	#__ARDUINO_SDK_LIB_STEPPER__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_TEMBOO__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Temboo/src		\
		$(ARDUINO_SDK_ROOT)/libraries/Temboo/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/Temboo.cpp
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/TembooCoAPEdgeDevice.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/TembooMQTTEdgeDevice.cpp
endif	# __ARDUINO_SDK_CC__
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/BaseFormatter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoInput.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoInputFormatter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoInputSet.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoOutput.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoOutputFormatter.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoOutputSet.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoPreset.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/ChoreoPresetFormatter.cpp
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/CoapMessageLayer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/CoapMsg.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/CoapRRLayer.cpp
endif	# __ARDUINO_SDK_CC__
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/DataFormatter.cpp
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTConnectClient.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTConnectServer.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTDeserializePublish.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTFormat.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTPacket.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTSerializePublish.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTSubscribeClient.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTSubscribeServer.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTUnsubscribeClient.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/MQTTUnsubscribeServer.c
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooCoAPSession.cpp
endif	# __ARDUINO_SDK_CC__
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooGlobal.c
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooMQTTSession.cpp
endif	# __ARDUINO_SDK_CC__
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/TembooSession.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/tmbhmac.cpp
EE_SRCS_ARDUINO_SDK += libraries/Temboo/src/utility/tmbmd5.cpp
endif	#__ARDUINO_SDK_LIB_TEMBOO__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_TFT__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/TFT/src		\
		$(ARDUINO_SDK_ROOT)/libraries/TFT/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/TFT.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/utility/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/utility/ST7735.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/src/utility/glcdfont.c
endif	#__ARDUINO_SDK_LIB_TFT__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_TIMER1__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Timer1 \
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Timer1/Timer1.cpp
endif	#__ARDUINO_SDK_LIB_TIMER1__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_TIMER1_CTC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Timer1CTC \
		$(INCLUDE_PATH)
#EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Timer1CTC/Timer1CTC.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Timer1CTC/Timer1CTC.c
endif	#__ARDUINO_SDK_LIB_TIMER1_CTC__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_USB_HOST__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/USBHost/src	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/adk.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/hid2.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/KeyboardController.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/MouseController.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/parsetools.cpp
EE_SRCS_ARDUINO_SDK += libraries/USBHost/src/Usb.cpp
endif	# __ARDUINO_SDK_ORG__
endif	#__ARDUINO_SDK_LIB_USB_HOST__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_WIFI__), yes)
ifneq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/WiFi/src		\
		$(ARDUINO_SDK_ROOT)/libraries/WiFi/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFi.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFiClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFiServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/WiFiUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/utility/server_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/utility/spi_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/src/utility/wifi_drv.cpp
endif	# !__ARDUINO_SDK_ORG_1_7_10__
endif	# __ARDUINO_SDK_LIB_WIFI__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_WIFI_SHIELD__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG_1_7_10__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/WiFiShield/src		\
		$(ARDUINO_SDK_ROOT)/libraries/WiFiShiled/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFi.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFiClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFiServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/WiFiUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/utility/server_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/utility/spi_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFiShield/src/utility/wifi_drv.cpp
endif	# __ARDUINO_SDK_ORG_1_7_10__
endif	# __ARDUINO_SDK_LIB_WIFI_SHIELD__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_WIRE__), yes)
ifeq ($(call iseeopt, __ARDUINO_SDK_CC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire/src		\
		$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire/src/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/src/Wire.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/src/utility/twi.c
endif	# __ARDUINO_SDK_CC__
ifeq ($(call iseeopt, __ARDUINO_SDK_ORG__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire		\
		$(ARDUINO_SDK_ROOT)/hardware/arduino/avr/libraries/Wire/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/Wire.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/avr/libraries/Wire/utility/twi.c
endif	# __ARDUINO_SDK_ORG__
endif	# __ARDUINO_SDK_LIB_WIRE__

else	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__

EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/avr-libc/malloc.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/avr-libc/realloc.c

EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/wiring.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/wiring_digital.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/wiring_analog.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/wiring_pulse.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/wiring_shift.c
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/WInterrupts.c

ifeq	($(call iseeopt, __ARDUINO_SDK_PCINT__), yes)
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/WPCInterrupts.c
endif	# __ARDUINO_SDK_PCINT__

EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/CDC.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/HardwareSerial.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/HID.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/IPAddress.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/new.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/Print.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/Stream.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/Tone.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/USBCore.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/WMath.cpp
EE_SRCS_ARDUINO_SDK += hardware/arduino/cores/arduino/WString.cpp

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_EEPROM__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/EEPROM		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/EEPROM/EEPROM.cpp
endif	# __ARDUINO_SDK_LIB_EEPROM__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ESPLORA__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Esplora		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Esplora/Esplora.cpp
endif	# __ARDUINO_SDK_LIB_ESPLORA__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ETHERNET__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Ethernet		\
		$(ARDUINO_SDK_ROOT)/libraries/Ethernet/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/Dhcp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/Dns.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/Ethernet.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/EthernetClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/EthernetServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/EthernetUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/utility/socket.cpp
EE_SRCS_ARDUINO_SDK += libraries/Ethernet/utility/w5100.cpp
endif	# __ARDUINO_SDK_LIB_ETHERNET__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_FIRMATA__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Firmata		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Firmata/Firmata.cpp
endif	# __ARDUINO_SDK_LIB_FIRMATA__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_GSM__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/GSM		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3CircularBuffer.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileAccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileCellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileClientService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileDataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileMockupProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileNetworkRegistry.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileServerService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileSMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3MobileVoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1AccessProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1BandManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1BaseProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1CellManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1ClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1DataNetworkProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1DirectModemProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1ModemCore.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1ModemVerification.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1MultiClientProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1MultiServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1PinManagement.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1ScanNetworks.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1ServerProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1SMSProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3ShieldV1VoiceProvider.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3SMSService.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3SoftSerial.cpp
EE_SRCS_ARDUINO_SDK += libraries/GSM/GSM3VoiceCallService.cpp
endif	# __ARDUINO_SDK_LIB_GSM__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_LIQUID_CRYSTAL__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/LiquidCrystal	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/LiquidCrystal/LiquidCrystal.cpp
endif	# __ARDUINO_SDK_LIB_LIQUID_CRYSTAL__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ROBOT_CONTROL__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Robot_Control		\
		$(ARDUINO_SDK_ROOT)/libraries/Robot_Control/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Arduino_LCD.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/ArduinoRobot.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/communication.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Compass.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/EasyTransfer2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/EEPROM_I2C.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Fat16.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/glcdfont.c
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/helper.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/information.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/keyboard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/lcd.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Melody.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Motors.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Multiplexer.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/RobotSdCard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/SdCard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Sensors.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/SPI.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Squawk.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/SquawkSD.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/Wire.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/utility/RobotTextManager.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/utility/twi.c
EE_SRCS_ARDUINO_SDK += libraries/Robot_Control/utility/VirtualKeyboard.cpp
endif	# __ARDUINO_SDK_LIB_ROBOT_CONTROL__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_ROBOT_MOTOR__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Robot_Motor	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/ArduinoRobotMotorBoard.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/EasyTransfer2.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/lineFellow.cpp
EE_SRCS_ARDUINO_SDK += libraries/Robot_Motor/Multiplexer.cpp
endif	# __ARDUINO_SDK_LIB_ROBOT_MOTOR__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SD__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/SD		\
		$(ARDUINO_SDK_ROOT)/libraries/SD/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/SD/File.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/SD.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/utility/Sd2Card.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/utility/SdFile.cpp
EE_SRCS_ARDUINO_SDK += libraries/SD/utility/SdVolume.cpp
endif	# __ARDUINO_SDK_LIB_SD__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SERVO__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Servo		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Servo/Servo.cpp
endif	#__ARDUINO_SDK_LIB_SERVO__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SOFTWARE_SERIAL__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/SoftwareSerial	$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/SoftwareSerial/SoftwareSerial.cpp
endif	# __ARDUINO_SDK_LIB_SOFTWARE_SERIAL__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_SPI__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/SPI $(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/SPI/SPI.cpp
endif	#__ARDUINO_SDK_LIB_SPI__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_STEPPER__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Stepper		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Stepper/Stepper.cpp
endif	#__ARDUINO_SDK_LIB_STEPPER__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_TFT__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/TFT		\
		$(ARDUINO_SDK_ROOT)/libraries/TFT/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/TFT/TFT.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/utility/Adafruit_GFX.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/utility/ST7735.cpp
EE_SRCS_ARDUINO_SDK += libraries/TFT/utility/glcdfont.c
endif	#__ARDUINO_SDK_LIB_TFT__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_TIMER1__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Timer1		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Timer1/Timer1.cpp
endif	# __ARDUINO_SDK_LIB_TIMER1__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_TIMER1_CTC__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Timer1CTC		$(INCLUDE_PATH)
#EE_SRCS_ARDUINO_SDK += libraries/Timer1CTC/Timer1CTC.cpp
EE_SRCS_ARDUINO_SDK += libraries/Timer1CTC/Timer1CTC.c
endif	# __ARDUINO_SDK_LIB_TIMER1_CTC__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_WIFI__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/WiFi		\
		$(ARDUINO_SDK_ROOT)/libraries/WiFi/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/WiFi/WiFi.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/WiFiClient.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/WiFiServer.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/WiFiUdp.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/utility/server_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/utility/spi_drv.cpp
EE_SRCS_ARDUINO_SDK += libraries/WiFi/utility/wifi_drv.cpp
endif	# __ARDUINO_SDK_LIB_WIFI__

ifeq	($(call iseeopt, __ARDUINO_SDK_LIB_WIRE__), yes)
INCLUDE_PATH :=	$(ARDUINO_SDK_ROOT)/libraries/Wire		\
		$(ARDUINO_SDK_ROOT)/libraries/Wire/utility	\
		$(INCLUDE_PATH)
EE_SRCS_ARDUINO_SDK += libraries/Wire/Wire.cpp
EE_SRCS_ARDUINO_SDK += libraries/Wire/utility/twi.c
endif	# __ARDUINO_SDK_LIB_WIRE__

endif	# __ARDUINO_SDK_CC__ && __ARDUINO_SDK_ORG__

EE_OBJS_ARDUINO_SDK := 							       \
	$(addprefix $(OBJDIR)/,						       \
		$(patsubst %.cpp,%.cpp.o,				       \
			$(patsubst %.c,%.c.o,				       \
				$(patsubst %.S,%.S.o,$(EE_SRCS_ARDUINO_SDK))   \
			)						       \
		)							       \
	)

LIBSRCS += $(EE_SRCS_ARDUINO_SDK)

ARDUINO_SDK_LIB := libarduinosdk.a

$(LIBDIR)/$(ARDUINO_SDK_LIB): $(EE_OBJS_ARDUINO_SDK)
	$(VERBOSE_PRINTAR) $(EE_AR) $(COMPUTED_OPT_AR) $@ $^

OPT_LIBS += $(LIBDIR)/$(ARDUINO_SDK_LIB)
ALL_LIBS += $(LIBDIR)/$(ARDUINO_SDK_LIB)

endif	# __AVR8__

endif	# __ATMEGA__

endif	# INCLUDE_ARDUINO_SDK

endif	# __ARDUINO_SDK__
