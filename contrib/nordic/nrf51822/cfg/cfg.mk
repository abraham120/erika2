# ###*B*###
# ERIKA Enterprise - a tiny RTOS for small microcontrollers
# 
# Copyright (C) 2002-2013  Evidence Srl
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

## Author: 2013 Alessandro Biondi

ifeq ($(call iseeopt, __USE_NRF51822_SYSLIB__), yes)

INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/app_common
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/ble
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/ble/softdevice
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/ble/ble_services
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/boards
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/esb
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/ext_sensors
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/gzll
INCLUDE_PATH += $(EEBASE)/contrib/nordic/nrf51822/inc/gzp

# Common files
EE_SRCS += contrib/nordic/nrf51822/src/templates/system_nrf51.c

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_BUTTON__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/app_common/app_button.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_FIFO__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/app_common/app_fifo.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_GPIOTE__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/app_common/app_gpiote.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_SCHEDULER__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/app_common/app_scheduler.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_TIMER__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/app_common/app_timer.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_UART__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/app_common/app_uart.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_BLE__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_advdata.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_conn_params.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_dtm.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_flash.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_radio_notification.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_bondmngr.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_debug_assert_handler.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_error_log.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_racp.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_sensorsim.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_stack_handler.c

EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_ans_c.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_bps.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_dis.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_gls_db.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_hrs.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_ias.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_lls.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_srv_common.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_bas.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_cscs.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_gls.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_hids.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_hts.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_ias_c.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_rscs.c
EE_SRCS += contrib/nordic/nrf51822/src/ble/ble_services/ble_tps.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_CONSOLE__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/console/console.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_ADNS2080__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ext_sensors/adns2080/adns2080.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_CHERRY8X16__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ext_sensors/cherry8x16/cherry8x16.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_DS1624__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ext_sensors/ds1624/ds1624.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_MPU6050__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ext_sensors/mpu6050/mpu6050.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_NRF6350__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ext_sensors/nRF6350/nRF6350.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_SDIO__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ext_sensors/sdio/sdio.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_SYNAPTICS_TOUCHPAD__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/ext_sensors/synaptics_touchpad/synaptics_touchpad.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_GZP__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/gzp/nrf_gzp.c
EE_SRCS += contrib/nordic/nrf51822/src/gzp/nrf_gzp_device.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_ASSERT__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/nrf_assert/nrf_assert.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_DELAY__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/nrf_delay/nrf_delay.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_ECB__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/nrf_ecb/nrf_ecb.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_NVMC__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/nrf_nvmc/nrf_nvmc.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_SIMPLE_UART__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/simple_uart/simple_uart.c
endif

ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_SPI_MASTER__)), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/spi_master/spi_master.c
endif


ifeq ($(or $(call iseeopt, __USE_NRF51822_SYSLIB_ALL__), $(call iseeopt, __USE_NRF51822_SYSLIB_TWI_MASTER__)), yes) 
ifeq ($(call iseeopt, __USE_NRF51822_SYSLIB_FIXED__), yes) 
EE_SRCS += contrib/nordic/nrf51822/src/fixed/twi_hw_master.c
else
EE_SRCS += contrib/nordic/nrf51822/src/twi_master/twi_hw_master.c
endif
EE_SRCS += contrib/nordic/nrf51822/src/twi_master/twi_sw_master.c
endif


endif #__USE_NRF51822_SYSLIB__