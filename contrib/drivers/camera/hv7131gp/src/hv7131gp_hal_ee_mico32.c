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
Copyright (C) 2009 -  Claudio Salvadori and Christian Nastasi
Copyright (C) 2010 -  Evidence srl
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
* @file 	hv7131gp_hal_ee_mico32.c
* @brief 	HV7131GP camera driver HAL for Lattice Mico32 
			(derived from hv7131gp_hal_ee_pic32.c)
* @author 	Bernardo  Dal Seno
* @author	Dario Di Stefano 
* @date 	2010 
*/

#include <ee.h>
#include <hv7131gp_hal.h>
#include <hv7131gp.h>


/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/




/* ---------------------- Driver functions --------------------------------- */

/* This function configures I2C */
hv7131gp_status_t hv7131gp_i2c_hal_init(void)
{   
    if( EE_hv7131gp_i2c_config(100000,0) < 0)
        return -HV7131GP_ERR_I2C_INIT;
    
    return HV7131GP_SUCCESS;
}

/* This function writes on a camera register */
hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t val)
{
    if (EE_hv7131gp_i2c_write_byte(reg, val) !=  EE_I2C_OK)
        return -HV7131GP_ERR_I2C_WRITE;
    return HV7131GP_SUCCESS;
}

/* This function reads a camera register */
hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val)
{
    int ret = EE_hv7131gp_i2c_read_byte(reg);
    if (ret < 0)
        return -HV7131GP_ERR_I2C_READ;
    else
        *val = ret;
    return HV7131GP_SUCCESS; 
}

/* This function initializes i2c and camera mico32 controllers */
hv7131gp_status_t hv7131gp_hal_init_mico32(void)
{
    EE_hv7131gp_init(1);
    if (hv7131gp_i2c_hal_init() != HV7131GP_SUCCESS)
        return -HV7131GP_ERR_I2C_INIT;
    return HV7131GP_SUCCESS;
}

/* ---------------------- Global variables --------------------------------- */
hv7131gp_cback_t *ee_hv7131gp_cbk;  // ISR camera callback function

/* ---------------------- CAMERA interrupt handler ------------------------- */

/* This function is the camera interrupt handler */
void EE_hv7131gp_handler(int level)
{
    hv7131gp_status_t status;

    if (! EE_camera_read_ERR_flag()) {
	status = HV7131GP_SUCCESS;
    } else if (EE_camera_read_size_err_flag()) {
	status = HV7131GP_ERR_DMA_SIZE;
    } else {
	status = HV7131GP_FAILURE;
    }
    EE_camera_clear_IRQ_flag();
    
    if(ee_hv7131gp_cbk != (hv7131gp_cback_t *)0)
        ee_hv7131gp_cbk(status);

    return;
}

/* ---------------------- Other CAMERA Library functions ------------------------- */

/* This function sets the ISR operating mode */
void EE_hv7131gp_ISR_init(MicoCamera_t* cam, int irqf)
{
    /* reset camera controller FSM */
    Mico_camera_reset(cam);
    
    /* Interrupt configuration */
    EE_hal_hv7131gp_handler_setup(irqf);
    EE_camera_enable_IRQ();
}

/* This function sets the polling operating mode */
void EE_hv7131gp_polling_init(MicoCamera_t* cam)
{
    /* Disable IRQ */
    EE_camera_disable_IRQ();
    
    /* reset camera controller FSM */
    Mico_camera_reset(cam);
}


/* This function starts iamge capture and sets the callback */
int EE_hv7131gp_capture(void *image, hv7131gp_cback_t *cam_cbk)
{
    EE_camera_write_address(image);     // image buffer
    ee_hv7131gp_cbk = cam_cbk;              // set the callback function
    EE_camera_write_size(hv7131gp_get_size());
    EE_camera_start();                  // activate frame acquisition
    
    return HV7131GP_SUCCESS;
}


/* This function waits for ack */
hv7131gp_status_t hv7131gp_hal_init_ack(void)
{
    while(EE_camera_read_status_register() != MICO_CAMERA_IDLE)
        ;
    /* TODO: add a timeout */
    return HV7131GP_SUCCESS;
}
