/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
 
/*
Copyright (C) 2009, 2010 -  Claudio Salvadori and Christian Nastasi, Evidence Srl
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/** 
* @file 	hv7131gp_hal_ee_mico32.h
* @brief 	HV7131GP camera driver HAL for Lattice Mico32
* @author 	Bernardo  Dal Seno
* @author	Dario Di Stefano 
* @date 	2010
*/

#ifndef HV7131GP_HAL_EE_MICO32_H_
#define HV7131GP_HAL_EE_MICO32_H_

/* Required header files */
#include "hv7131gp_types.h"
#include "hv7131gp_reg.h"
#include <cpu/mico32/inc/ee_irq.h>
#include <MicoCamera.h>
/* Other used libraries: */
#include <mcu/mico32/inc/ee_i2c.h>
/* Include board dependent header file */
#ifdef __FPG_EYE__
#include <board/fpg-eye/inc/ee_camera_hv7131gp.h>
#endif


/******************************************************************************/
/*                        Symbols and macros                                  */
/******************************************************************************/

/* Symbols and macros */
#define EE_HV7131GP_DEVICE_ID               (HV7131GP_DEVICE_ID)
#define EE_HV7131GP_ISR_MODE                (0x01)
#define EE_HV7131GP_POLLING_MODE            (0x00)
#define EE_hv7131gp_need_enable_int(mode)   (mode)

/* Default configuration */
#define EE_HV7131GP_DEFAULT_FORMAT          (HV7131GP_OUTFMT_DEFAULT & (~HV7131GP_8BIT_OUTPUT))
#define EE_HV7131GP_DEFAULT_DIVISOR         (HV7131GP_T_1)
#define EE_HV7131GP_DEFAULT_RESOLUTION      (HV7131GP_1_16_SUB)
#define EE_HV7131GP_DEFAULT_WIDTH           (640)
#define EE_HV7131GP_DEFAULT_HEIGTH          (480)
#define EE_HV7131GP_DEFAULT_COLUMN          (0x2)
#define EE_HV7131GP_DEFAULT_ROW             (0x2)
#define EE_HV7131GP_DEFAULT_VBLANK          (8)
#define EE_HV7131GP_DEFAULT_HBLANK          (208)
#define EE_HV7131GP_DEFAULT_FRAME_WIDTH     (160)
#define EE_HV7131GP_DEFAULT_FRAME_HEIGHT    (120)


/******************************************************************************/
/*                         Functions Prototypes                               */
/******************************************************************************/

/* Callback function called by camera driver handler  */
extern hv7131gp_cback_t *ee_hv7131gp_cbk;

/**
	@brief This function initializes Mico32 i2c and camera controllers
*/
hv7131gp_status_t hv7131gp_hal_init_mico32(void);
#define hv7131gp_hal_init(x) hv7131gp_hal_init_mico32()

/**
	@brief This function waits for ack
*/
hv7131gp_status_t hv7131gp_hal_init_ack(void);

/**
	@brief This function initializes Mico32 i2c controller
*/
hv7131gp_status_t hv7131gp_i2c_hal_init(void);

/**
	@brief This function writes on a camera register
*/
hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t  val);

/**
	@brief This function reads a camera register
*/
hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val);

/* I2C-based Camera API */  
#define DECLARE_FUNC_I2C_HV7131GP(uc, lc) \
__INLINE__ int __ALWAYS_INLINE__ EE_hv7131gp_i2c_config(int baudrate,int settings){ \
    return cat3(EE_, lc, _config)(baudrate, settings); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_write_byte(EE_UINT8 address, EE_UINT8 data){ \
    return cat3(EE_, lc, _send_byte)(EE_HV7131GP_DEVICE_ID, address, data); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_write_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
    return cat3(EE_, lc, _send_buffer)(EE_HV7131GP_DEVICE_ID, address, data, len); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_read_byte(EE_UINT8 address){ \
    return cat3(EE_, lc, _receive_byte)(EE_HV7131GP_DEVICE_ID, address); } \
__INLINE__ int __ALWAYS_INLINE__  EE_hv7131gp_i2c_read_buffer(EE_UINT8 address, EE_UINT8 *data, int len){ \
    return cat3(EE_, lc, _receive_buffer)(EE_HV7131GP_DEVICE_ID, address, data, len); }

/**
	@brief 	This function sets the Mico32 camera controller 
			in ISR operating mode
*/
void EE_hv7131gp_ISR_init(MicoCamera_t* cam, int irqf);

/**
	@brief 	This function sets the Mico32 camera controller 
			in polling operating mode
*/
void EE_hv7131gp_polling_init(MicoCamera_t* cam);

/**
	@brief 	This function sets camera configuration
*/
int EE_hv7131gp_set_configuration(int div, int fmt, int res, int w, int h, int x, int y, int hb, int vb);

/**
	@brief 	This function sets camera default configuration
*/
int EE_hv7131gp_set_default_configuration(void);

/**
	@brief 	This function sets camera window width
*/
int EE_hv7131gp_set_width(int width);

/**
	@brief 	This function reads camera window width
*/
int EE_hv7131gp_get_width(void);

/**
	@brief 	This function sets camera window height
*/
int EE_hv7131gp_set_height(int height);

/**
	@brief 	This function reads camera window height
*/
int EE_hv7131gp_get_height(void);

/**
	@brief 	This function reads camera window size
*/
int EE_hv7131gp_get_size(void);

/**
	@brief 	This function sets camera window X position
*/
int EE_hv7131gp_set_xpos(int x);

/**
	@brief 	This function reads camera window X position
*/
int EE_hv7131gp_get_xpos(void);

/**
	@brief 	This function sets camera window Y position
*/
int EE_hv7131gp_set_ypos(int y);

/**
	@brief 	This function reads camera window Y position
*/
int EE_hv7131gp_get_ypos(void);

/**
	@brief 	This function sets camera hblank
*/
int EE_hv7131gp_set_hblank(int hb);

/**
	@brief 	This function gets camera hblank
*/
int EE_hv7131gp_get_hblank(void);

/**
	@brief 	This function sets camera vblank
*/
int EE_hv7131gp_set_vblank(int vb);

/**
	@brief 	This function gets camera vblank
*/
int EE_hv7131gp_get_vblank(void);

/**
	@brief 	This function sets camera window
*/
int EE_hv7131gp_set_window(int width, int height, int x, int y);

/**
	@brief 	This function sens capture image signal to the camera and
			sets the callback to call at the end of the capture
*/
int EE_hv7131gp_capture(void *image, hv7131gp_cback_t *cam_cbk);
#define hv7131gp_hal_capture(image, func) EE_hv7131gp_capture(image, func)

/**
	@brief 	This function sets camera sleep mode
*/
int EE_hv7131gp_set_sleep_status(void);

/**
	@brief 	This function sets camera active mode
*/
int EE_hv7131gp_set_active_status(void);

DECLARE_FUNC_I2C_HV7131GP(CAMERA_I2C, camera_i2c)


/* Mico32 HV7131GP Camera controller API */

static MicoCamera_t * const camera_base = (MicoCamera_t*)EE_BASE_ADD(CAMERA);

__INLINE__ void __ALWAYS_INLINE__ EE_hv7131gp_init(int irqmode)
{
    if(irqmode)
        EE_hv7131gp_ISR_init(camera_base, EE_IRQ_NAME(CAMERA));
    else
        EE_hv7131gp_polling_init(camera_base);
}

__INLINE__ void * __ALWAYS_INLINE__ EE_camera_read_address(void)
{
    return Mico_camera_read_address(camera_base);
}

__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_address(void *addr)
{
    Mico_camera_write_address(camera_base,addr);
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_status_register(void)
{
    return Mico_camera_read_status_register(camera_base);
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_IF_flag(void)
{
    return Mico_camera_read_IF_flag(camera_base);
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_ERR_flag(void)
{
    return Mico_camera_read_ERR_flag(camera_base);
}

__INLINE__ void __ALWAYS_INLINE__ EE_camera_start(void)
{
    Mico_camera_start(camera_base);
}

__INLINE__ void __ALWAYS_INLINE__ EE_camera_clear_IRQ_flag(void)
{
    Mico_camera_clear_IRQ_flag(camera_base);
}

__INLINE__ void __ALWAYS_INLINE__ EE_camera_reset(void)
{
    Mico_camera_reset(camera_base);
}

__INLINE__ void __ALWAYS_INLINE__ EE_camera_enable_IRQ(void)
{
    Mico_camera_enable_IRQ(camera_base);
}

__INLINE__ void __ALWAYS_INLINE__ EE_camera_disable_IRQ(void)
{
    Mico_camera_disable_IRQ(camera_base);
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_IRQ_enabled(void)
{
    return Mico_camera_IRQ_enabled(camera_base);
}

__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_divisor(unsigned int div)
{
    Mico_camera_write_divisor(camera_base, div);
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_divisor(void)
{
    return Mico_camera_read_divisor(camera_base);
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_frame_terminated(void)
{
    return Mico_camera_frame_terminated(camera_base);
}

#if defined MICO_CAMERA_VER && MICO_CAMERA_VER >= 1
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_size(unsigned int size)
{
    Mico_camera_write_size(camera_base, MICO_CAMERA_SIZE_WORDS(size));
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_size_err_flag(void)
{
    return Mico_camera_read_size_err_flag(camera_base);
}

#else /* #if defined MICO_CAMERA_VER && MICO_CAMERA_VER >= 1 */
__INLINE__ void __ALWAYS_INLINE__ EE_camera_write_size(unsigned int size)
{
}

__INLINE__ int __ALWAYS_INLINE__ EE_camera_read_size_err_flag(void)
{
    return 0;
}

#endif /* else #if defined MICO_CAMERA_VER && MICO_CAMERA_VER >= 1 */



/* INLINE functions */

/**
	@brief 	This function is the interrupt handler
*/
void EE_hv7131gp_handler(int level);

#ifndef __STATIC_ISR_TABLE__
/**
	@brief 	This function sets (registers) the interrupt handler
*/
__INLINE__ void __ALWAYS_INLINE__ EE_hal_hv7131gp_handler_setup(int irqf)
{
    EE_mico32_register_ISR(irqf, EE_hv7131gp_handler);
}
#else // __STATIC_ISR_TABLE__
/* This function just enable (unmask) camera controller IRQ */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_hv7131gp_handler_setup(int irqf)
{
    mico32_enable_irq(irqf);
}
#endif // __STATIC_ISR_TABLE__

/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/
#define HV7131GP_HAL_DRIVING_PINS           0

/* Effectively disable hv7131gp_configure_safe(), which is not safe enough to
 * do check the actual buffer size */
#define HV7131GP_MAX_SIZE   0


/*  For compatibility with other HALs that deal with low-level details */

#define HV7131GP_PIN_ENABLE_INIT()
#define HV7131GP_PIN_ENABLE_HIGH()
#define HV7131GP_PIN_EOF_INIT() 
#define HV7131GP_PIN_MCLK_INIT(p)
#define HV7131GP_PIN_MCLK_START()
#define HV7131GP_PIN_RESETB_INIT()
#define HV7131GP_PIN_RESETB_HIGH()
#define HV7131GP_PIN_RESETB_LOW()
#define HV7131GP_PIN_HSYNC_INIT()
#define HV7131GP_PIN_VCLK_INIT()
#define HV7131GP_PIN_VSYNC_INIT_POSITIVE()
#define HV7131GP_PIN_Y_INIT()   
#define HV7131GP_VSYNC_RESET_IF()
#define HV7131GP_VSYNC_IF_VALUE 1
#define HV7131GP_MORE_THAN_1_MS                 0
#define HV7131GP_MORE_THAN_4_MCLK_CYCLES        0
#define HV7131GP_MORE_THAN_2086000_MCLK_CYCLES  0
#define hv7131gp_hal_delay_us(x)  INVALID_ASM_INSTR



#endif /* HV7131GP_HAL_EE_MICO32_H_ */
