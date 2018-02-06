/*
Copyright (C) 2009 -  Claudio Salvadori
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
 *
 *  \file hv7131gp_reg.h
 *
 *  \date Created on: 9-feb-2009
 *  \author Author: Claudio Salvadori
 *  \brief Enumeration of the register addresses for HV7131GP and definition of
 *  the most common values for some of them
 */

#ifndef HV7131GP_REG_H_
#define HV7131GP_REG_H_

/**
* @brief Definition of the maximum size of the buffer for different Micro
*/


#ifndef HV7131GP_TIME_OUT_DEF_H_
#define HV7131GP_TIME_OUT_DEF_H_
/**
* @brief Time constant symbolic name for init function
* @{ */
typedef enum {
	HV7131GP_TIME_MORE_THAN_1ms,		/**< More than 1ms */
	HV7131GP_TIME_MORE_THAN_4_MCLK,		/**< 4 T_MCLK */
	HV7131GP_TIME_2086000_MCLK,		/**< 2086000 T_MCLK */
} hv7131gp_time_t;
/**  @} */

#endif /* HV7131GP_TIME_OUT_DEF_H_ */






/**
* @brief Register addresses for HV7131GP
*
* Addresses for the register of the HV7131GP CMOS camera to be
* accessed via the I2C interface.
* See sensor reference manual for details.
*/
typedef enum {
	HV7131GP_REG_DEVID 		= 0x00,	/**< Device ID: product id, revision no. */

	HV7131GP_REG_SCTRA 		= 0x01,	/**< Sensor control A: operation mode, x/y flip, image size */
	HV7131GP_REG_SCTRB 		= 0x02,	/**< Sensor control B: power down, clock division */
	HV7131GP_REG_SCTRC 		= 0x03,	/**< Sensor control C: sensor interbal register */

	HV7131GP_REG_RSAH 		= 0x08,	/**< Row start address (high byte) */
	HV7131GP_REG_RSAL 		= 0x09,	/**< Row start address (low byte) */
	HV7131GP_REG_CSAH 		= 0x0A,	/**< Column start address (high byte) */
	HV7131GP_REG_CSAL 		= 0x0B,	/**< Column start address (low byte) */

	HV7131GP_REG_WIHH 		= 0x0C,	/**< Window Height (high byte) */
	HV7131GP_REG_WIHL 		= 0x0D,	/**< Window Height (low byte) */
	HV7131GP_REG_WIWH 		= 0x0E,	/**< Window Width (high byte) */
	HV7131GP_REG_WIWL 		= 0x0F,	/**< Window Width (low byte) */

	HV7131GP_REG_HBLANKH 		= 0x10,	/**< HBLANK (high byte) */
	HV7131GP_REG_HBLANKL 		= 0x11,	/**< HBLANK (low byte) */
	HV7131GP_REG_VBLANKH 		= 0x12,	/**< VBLANK (high byte) */
	HV7131GP_REG_VBLANKL 		= 0x13,	/**< VBLANK (low byte) */

	HV7131GP_REG_RCG 		= 0x14,	/**< Red color gain */
	HV7131GP_REG_GCG 		= 0x15,	/**< Green color gain */
	HV7131GP_REG_BCG 		= 0x16,	/**< Blue color gain */

	HV7131GP_REG_PREAMP		= 0x17,	/**< Preamp. gain */
	HV7131GP_REG_PREMIN		= 0x18,	/**< Preamp. gain min. */
	HV7131GP_REG_PREMAX		= 0x19,	/**< Preamp. gain max. */
	HV7131GP_REG_PRENOM		= 0x1A,	/**< Preamp. gain nominal */

	HV7131GP_REG_ASPBIAS		= 0x1B,	/**< Asp bias: amp bias, pixel bias */

	HV7131GP_REG_RSTCLMP		= 0x1C,	/**< Reset clamp */

	HV7131GP_REG_ADCBIAS		= 0x20,	/**< ADC bias */

	HV7131GP_REG_OREDI 		= 0x21,	/**< Red pixel black offset*/
	HV7131GP_REG_OGRNI 		= 0x22,	/**< Green pixel black offset */
	HV7131GP_REG_OBLUI 		= 0x23,	/**< Blue pixel black offset */

	HV7131GP_REG_OREDU 		= 0x24,	/**< Red pixel active offset (read only) */
	HV7131GP_REG_OGRNU 		= 0x25,	/**< Green pixel active offset (read only) */
	HV7131GP_REG_OBLUU 		= 0x26,	/**< Blue pixel active offset (read only) */

	HV7131GP_REG_BLCTH 		= 0x27,	/**< Black level threshold */

	HV7131GP_REG_ISPFEN		= 0x30,	/**< ISP function enabled */

	HV7131GP_REG_OUTFMT 		= 0x31,	/**< Output Format */

	HV7131GP_REG_OUTINV		= 0x32,	/**< Output polarity */

	HV7131GP_REG_EDGETH		= 0x33,	/**< Green edge threshold */

	HV7131GP_REG_CMA11 		= 0x34,	/**< Color matrix coefficient 11 */
	HV7131GP_REG_CMA12 		= 0x35,	/**< Color matrix coefficient 12 */
	HV7131GP_REG_CMA13 		= 0x36,	/**< Color matrix coefficient 13 */
	HV7131GP_REG_CMA21 		= 0x37,	/**< Color matrix coefficient 21 */
	HV7131GP_REG_CMA22 		= 0x38,	/**< Color matrix coefficient 22 */
	HV7131GP_REG_CMA23 		= 0x39,	/**< Color matrix coefficient 23 */
	HV7131GP_REG_CMA31 		= 0x3A,	/**< Color matrix coefficient 31 */
	HV7131GP_REG_CMA32 		= 0x3B,	/**< Color matrix coefficient 32 */
	HV7131GP_REG_CMA33 		= 0x3C,	/**< Color matrix coefficient 33 */

	HV7131GP_REG_GMAP0 		= 0x40,	/**< Gamma segment point 0 */
	HV7131GP_REG_GMAP1 		= 0x41,	/**< Gamma segment point 1 */
	HV7131GP_REG_GMAP2 		= 0x42,	/**< Gamma segment point 2 */
	HV7131GP_REG_GMAP3		= 0x43,	/**< Gamma segment point 3 */
	HV7131GP_REG_GMAP4 		= 0x44,	/**< Gamma segment point 4 */
	HV7131GP_REG_GMAP5 		= 0x45,	/**< Gamma segment point 5 */
	HV7131GP_REG_GMAP6 		= 0x46,	/**< Gamma segment point 6 */
	HV7131GP_REG_GMAP7		= 0x47,	/**< Gamma segment point 7 */
	HV7131GP_REG_GMAP8 		= 0x48,	/**< Gamma segment point 8 */
	HV7131GP_REG_GMAP9 		= 0x49,	/**< Gamma segment point 9 */

	HV7131GP_REG_GMAS0 		= 0x50,	/**< Gamma segment slope 0 */
	HV7131GP_REG_GMAS1 		= 0x51,	/**< Gamma segment slope 1 */
	HV7131GP_REG_GMAS2 		= 0x52,	/**< Gamma segment slope 2 */
	HV7131GP_REG_GMAS3		= 0x53,	/**< Gamma segment slope 3 */
	HV7131GP_REG_GMAS4 		= 0x54,	/**< Gamma segment slope 4 */
	HV7131GP_REG_GMAS5 		= 0x55,	/**< Gamma segment slope 5 */
	HV7131GP_REG_GMAS6 		= 0x56,	/**< Gamma segment slope 6 */
	HV7131GP_REG_GMAS7		= 0x57,	/**< Gamma segment slope 7 */
	HV7131GP_REG_GMAS8 		= 0x58,	/**< Gamma segment slope 8 */
	HV7131GP_REG_GMAS9 		= 0x59,	/**< Gamma segment slope 9 */

	HV7131GP_REG_AEM1 		= 0x60,	/**< AE mode 1 */
	HV7131GP_REG_AEM2 		= 0x61,	/**< AE mode 2 */

	HV7131GP_REG_INTH 		= 0x63,	/**< Integration time (high byte) */
	HV7131GP_REG_INTM 		= 0x64,	/**< Integration time (middle byte) */
	HV7131GP_REG_INTL 		= 0x65,	/**< Integration time (low byte) */

	HV7131GP_REG_AETGT 		= 0x66,	/**< AE target: frame luminance target value */

	HV7131GP_REG_AELBND		= 0x67,	/**< AE lock & fine tune boundary */
	HV7131GP_REG_AEUNLCK		= 0x68,	/**< AE unlock boundary */

	HV7131GP_REG_AEINCH		= 0x6A,	/**< AE integration step (high byte) */
	HV7131GP_REG_AEINCM		= 0x6B,	/**< AE integration step (middle byte) */
	HV7131GP_REG_AEINCL		= 0x6C,	/**< AE integration step (low byte) */

	HV7131GP_REG_AELMH		= 0x6D,	/**< AE integration limit (high byte) */
	HV7131GP_REG_AELMM		= 0x6E,	/**< AE integration limit (middle byte) */
	HV7131GP_REG_AELML		= 0x6F,	/**< AE integration limit (low byte) */

	HV7131GP_REG_AWBM1 		= 0x70,	/**< AWB mode 1 */
	HV7131GP_REG_AWBM2 		= 0x71,	/**< AWB mode 2 */

	HV7131GP_REG_CBTGT 		= 0x73,	/**< Cb target */
	HV7131GP_REG_CRTGT 		= 0x74,	/**< Cr target */

	HV7131GP_REG_AWBLB 		= 0x75,	/**< AWB lock boundary */
	HV7131GP_REG_AWBULB		= 0x76,	/**< AWB unlock boundary */
	HV7131GP_REG_AWBWPB		= 0x77,	/**< AWB white pixel boundary */

	HV7131GP_REG_YGAIN 		= 0x78,	/**< Y digital gain */
	HV7131GP_REG_CBGAIN		= 0x79,	/**< Cb digital gain */
	HV7131GP_REG_CRGAIN		= 0x7A,	/**< Cr digital gain */

	HV7131GP_REG_AEST		= 0x7B,	/**< AE status (read only) */
	HV7131GP_REG_AWBST		= 0x7C,	/**< AWB status (read only) */
	HV7131GP_REG_YFMEAN		= 0x7D,	/**< Y frame mean (read only) */
	HV7131GP_REG_CBFMEAN		= 0x7E,	/**< Cb frame mean (read only) */
	HV7131GP_REG_CRFMEAN		= 0x7F,	/**< Cr frame mean (read only) */

	HV7131GP_REG_BNDGMIN		= 0x80,	/**< Minimum anti-banding gain */
	HV7131GP_REG_BNDGMAX		= 0x81,	/**< Maximum anti-banding gain */

	HV7131GP_REG_ISOFSH		= 0x82,	/**< Integration-scan plane offset (high byte) */
	HV7131GP_REG_ISOFSM		= 0x83,	/**< Integration-scan plane offset (middle byte) */
	HV7131GP_REG_ISOFSL		= 0x84,	/**< Integration-scan plane offset (low byte) */

	HV7131GP_REG_AWBLUHI		= 0x8A,	/**< AWB luminance high boundary */
	HV7131GP_REG_AWBLULO 		= 0x8B,	/**< AWB luminance low boundary */
	HV7131GP_REG_AWBNO	 	= 0x8C,	/**< AWB valid number */

	HV7131GP_REG_DPCMODE		= 0x90,	/**< Dark bad pixel concelament mode */
	HV7131GP_REG_DPCINTH		= 0x91,	/**< Dark bad integration time (high byte) */
	HV7131GP_REG_DPCINTM		= 0x92,	/**< Dark bad integration time (middle byte) */
	HV7131GP_REG_DPCINTL		= 0x93,	/**< Dark bad integration time (low byte) */

	HV7131GP_REG_DPCGTH		= 0x94,	/**< Dark bad G threshold */
	HV7131GP_REG_DPCCTH		= 0x95,	/**< Dark bad R/B threshold */

} hv7131gp_reg_t;
/**  @} */

/******************************************************************************/
/*                           Macro Definitions                                */
/******************************************************************************/

/* DEVID register */

#define HV7131GP_DEVICE_ID 		0x22	/**< The I2C slave device ID */

#define HV7131GP_PROD_ID_MASK		0xf0    /**< Mask for ID in DEVID */
#define HV7131GP_PROD_ID_VALUE		0x40    /**< Product ID in DEVID */
#define HV7131GP_REV_NUM_MASK		0x0f    /**< Revision number mask in
                                                 * DEVID */
#define HV7131GP_REV_NUM_VALUE		0x00    /**< Revision number in DEVID */

/* SCTRA register */

#define HV7131GP_SCTRA_DEFAULT		0x0b	/**< SCTRA default value */
#define HV7131GP_X_FLIP 		0x08	/**< Perform horizontal flip */
#define HV7131GP_Y_FLIP 		0x04	/**< Perform vertical flip */

#define	HV7131GP_VIDEO_MASK 		0x03 	/**< Video mode mask in SCTRA */
#define	HV7131GP_VIDEO_NORMAL 		0x03 	/**< 3x3 color interpolation */
#define	HV7131GP_VIDEO_SUB_4 		0x02 	/**< 1/4 subsampling */
#define	HV7131GP_VIDEO_SUB_16 		0x01 	/**< 1/16 subsampling */
#define	HV7131GP_VIDEO_BAYER  		0x00 	/**< Bayer output format */

#define	HV7131GP_OPMODE_MASK		0xf0 /**< Operation mode mask in SCTRA */
#define	HV7131GP_OPMODE_NORMAL		0x00 /**< Normal operation mode */
#define	HV7131GP_OPMODE_TEST_A0 	0x80 /**< Test A all-0 operation mode */
#define	HV7131GP_OPMODE_TEST_A1		0x90 /**< Test A all-1 operation mode */
#define	HV7131GP_OPMODE_TEST_C0		0xe0 /**< Test C all-0 operation mode */
#define	HV7131GP_OPMODE_TEST_C1		0xd0 /**< Test C all-1 operation mode */

/* SCTRB register */

#define HV7131GP_SCTRB_DEFAULT		0x00	/**< SCTRB default value */

#define HV7131GP_DCF_1			0x00	/**< Divided clock freq. DFC=MCF */
#define HV7131GP_DCF_2			0x01	/**< Divided clock freq. DFC=MCF/2 */
#define HV7131GP_DCF_4			0x02	/**< Divided clock freq. DFC=MCF/4 */
#define HV7131GP_DCF_8			0x03	/**< Divided clock freq. DFC=MCF/8 */
#define HV7131GP_DCF_16			0x04	/**< Divided clock freq. DFC=MCF/16 */
#define HV7131GP_DCF_32			0x05	/**< Divided clock freq. DFC=MCF/32 */
#define HV7131GP_DCF_64			0x06	/**< Divided clock freq. DFC=MCF/64 */
#define HV7131GP_DCF_128		0x07	/**< Divided clock freq. DFC=MCF/128 */

#define	HV7131GP_AEAWB_SLEEP  		0x80 	/**< AE/AWB block disabled */
#define HV7131GP_SLEEP_MODE		0x10	/**< Sleep mode or not */

/* OUTFMT register */

#define HV7131GP_OUTFMT_DEFAULT		0x39	/**< Default value for OUTFMT register*/
#define HV7131GP_8BIT_OUTPUT		0x08	/**< Select 8 or 16 output mode */
#define HV7131GP_OUTFMT_BAYER_8BIT	0x40	/**< 8 or 10 bit for Bayer data */

#endif /* HV7131GP_REG_H_ */
