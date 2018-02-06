/**************************************************************************//**
 * $Id: lpc12xx_iocon.c 7535 2011-06-09 09:13:16Z cnh20509 $
 *
 * @file     lpc12xx_iocon.c
 * @brief    Contains all functions support for IOCON firmware library on LPC12xx.
 * @version  1.0
 * @date     26. Sep. 2010
 * @author   NXP MCU Team
 *
 * @note
 * Copyright (C) 2010 NXP Semiconductors(NXP). All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
 ******************************************************************************/


/* Peripheral group ----------------------------------------------------------- */
/** @addtogroup IOCON
 * @{
 */

/* Includes ------------------------------------------------------------------- */

/* If this source file built with example, the LPC12xx FW library configuration
 * file in each example directory ("lpc12xx_libcfg.h") must be included,
 * otherwise the default FW library configuration file must be included instead
 */
#ifdef __BUILD_WITH_EXAMPLE__
#include "lpc12xx_libcfg.h"
#else
#include "lpc12xx_libcfg_default.h"
#endif /* __BUILD_WITH_EXAMPLE__ */


/* Public Functions ----------------------------------------------------------- */
/** @addtogroup IOCON_Private_Functions
  * @{
  */

/**
  * @brief    Setup the PIO port selection function
  * @param mode    Pointer to a IOCON_PIO_CFG_Type structure
  *
  * @return  None
  */
void IOCON_SetFunc ( IOCON_PIO_CFG_Type *mode)
{
    uint32_t offset;
    uint32_t func;  
    uint32_t tmp;
    uint32_t *p = (uint32_t *)LPC_IOCON;

    CHECK_PARAM( PARAM_IOCON_PIO_TYPE(mode->type) );
    CHECK_PARAM( PARAM_IOCON_PIO_MODE(mode->pinmode)); 
    CHECK_PARAM( PARAM_IOCON_PIO_DRV(mode->drive) );
    CHECK_PARAM( PARAM_IOCON_PIO_AD(mode->ad) );
    CHECK_PARAM( PARAM_IOCON_PIO_OD(mode->od));   
    CHECK_PARAM( PARAM_IOCON_PIO_INV(mode->invert) );
    CHECK_PARAM( PARAM_IOCON_PIO_SMODE(mode->sm));
    CHECK_PARAM( PARAM_IOCON_PIO_CLKDIV(mode->cd));

    offset = (mode->type >> 6);
    func = (mode->type & 0xf);

    if(offset == 0x24 || offset == 0x25){ //0x90, 0x94 right shift 2 bit
       tmp = (uint32_t)(func|(mode->pmode)|(mode->od)|(mode->invert)|(mode->sm)|(mode->cd));

    }else{
       tmp = (uint32_t)(func|(mode->pinmode)|(mode->drive)|(mode->ad)|(mode->od)|(mode->invert)|(mode->sm)|(mode->cd));
    }
    *(uint32_t *)(p + offset) = tmp;
}

/**
  * @brief     Fills each IOCON_PIO_CFG_Type member with its default value.
  *
  * @param  mode  pointer to a IOCON_PIO_CFG_Type structure which will be initialized.
  * @retval   None
  */

void IOCON_StructInit ( IOCON_PIO_CFG_Type *mode)
{
   mode->type = 0x0;
   mode->pinmode = IOCON_PIO_MODE_PULLUP;
   mode->invert = IOCON_PIO_INV_NOT;
   mode->pmode = IOCON_PIO_PMODE_DISABLE;
   mode->od = IOCON_PIO_OD_DISABLE;
   mode->drive = IOCON_PIO_DRV_LOW;
   mode->ad = IOCON_PIO_AD_DIGITAL;
   mode->sm = IOCON_PIO_SMODE_BYPASS;
   mode->cd = IOCON_PIO_CLKDIV_0;
}
/**
  * @}
  */
	
/**
  * @}
  */

/* --------------------------------- End Of File ------------------------------ */
