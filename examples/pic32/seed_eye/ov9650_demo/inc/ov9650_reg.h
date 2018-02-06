/*
Copyright (C) 2012 -  Salvatore Marrapese
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
 *  \file ov9650_reg.h
 *
 *  \date Created on: 21-jun-2012
 *  \author Author: Salvatore Marrapese
 *  \brief Enumeration of the register addresses for OV9650 and definition of
 *  the most common values for some of them
 */

#ifndef OV9650_REG_H_
#define OV9650_REG_H_

/**
* @brief Definition of the maximum size of the buffer for different Micro
*/

#ifndef OV9650_TIME_OUT_DEF_H_
#define OV9650_TIME_OUT_DEF_H_

//@@@
/**
* @brief Time constant symbolic name for init function
* @{ */
typedef enum {
	OV9650_TIME_MORE_THAN_1ms,			/**< More than 1ms */
	OV9650_TIME_MORE_THAN_4_MCLK,		/**< 4 T_MCLK */
	OV9650_TIME_2086000_MCLK,		    /**< 2086000 T_MCLK */
} ov9650_time_t;
/**  @} */

#endif /* OV9650_TIME_OUT_DEF_H_ */

/**
* @brief Register addresses for OV9650
*
* Addresses for the register of the OV9650 CMOS camera to be
* accessed via the I2C interface.
* See OV9650 Color Cmos sxga OmniVision datasheet.
*/
typedef enum {
	OV9650_REG_GAIN 	= 0x00, /**< AGC[7:0] – Gain control gain setting
											Range: [00] to [FF]
											
											Def: 0x00
									*/
	OV9650_REG_BLUE 	= 0x01,	/**< AWB – Blue channel gain setting
											Range: [00] to [FF]
											
											Def: 0x80
									*/
	OV9650_REG_RED 		= 0x02,	/**< AWB – Red channel gain setting
											Range: [00] to [FF]
											
											Def: 0x80
									*/
	OV9650_REG_VREF 	= 0x03,	/**< Vertical Frame Control
											Bit[7:6]: AGC[9:8] (see register
												GAIN for AGC[7:0])
											Bit[5:3]: VREF end low 3 bits 
												(high 8 bits at VSTOP[7:0]
											Bit[2:0]: VREF start low 3 bits 
												(high 8 bits at VSTRT[7:0]
											
											Def: 0x12
									*/
	OV9650_REG_COM1 	= 0x04,	/**< Common Control 1
										Bit[7]: Reserved
										Bit[6]: CCIR656 format
										Bit[5]: QQVGA or QQCIF format. 
											Effective only when QVGA
											(register bit COM7[4]) or QCIF 
											(register bit COM7[3])
											output is selected and related 
											HREF skip option based on
											format is selected 
											(register COM1[3:2])
										Bit[4]: Reserved
										Bit[3:2]: HREF skip option
											00: No skip
											01: YUV/RGB skip every other row
												for YUV/RGB, skip 2
												rows for every 4 rows for 
												Raw data
											1x: Skip 3 rows for every 4 rows
												for YUV/RGB, skip 6 rows
												for every 8 rows for Raw data
										Bit[1:0]: AEC low 2 LSB (see registers 
													AECHM for AEC[15:10] and
													AECH for AEC[9:2])
													
										Def: 0x00
									*/
	OV9650_REG_BAVE 		= 0x05,	/**< U/B Average Level Automatically 
											updated based on chip 
											output format.
											
										 Def: 0x00
									*/
	OV9650_REG_GEAVE 		= 0x06,	/**< Y/Ge Average Level
										 Automatically updated based on 
										 chip output format 
										 
										 Def: 0x00
									*/
	OV9650_REG_RSVD 		= 0x07,	/**< Reserved */

	OV9650_REG_RAVE 		= 0x08,	/**< V/R Average Level
										 Automatically updated based on 
										 chip output format
										 
										 Def: 0x00
									*/
	OV9650_REG_COM2 		= 0x09,	/**< Common Control 2
											Bit[7:5]: Reserved
											Bit[4]: Soft sleep mode
											Bit[3:2]: Reserved
											Bit[1:0]: Output drive capability
												00: 1x
												01: 2x
												10: 2x
												11: 4x
												
										Def: 0x01
									*/
	OV9650_REG_PID 			= 0x0A,	/**< Product ID Number MSB (Read only) */
	OV9650_REG_VER 			= 0x0B,	/**< Product ID Number LSB (Read only) */

	OV9650_REG_COM3 		= 0x0C,	/**< Common Control 3
										 Bit[7]: Reserved
										 Bit[6]: Output data MSB and LSB swap
										 Bit[5:4]: Reserved
										 Bit[3]: Pin selection
											1: Change RESET pin to EXPST_B 
												(frame exposure mode timing)
												and change PWDN pin to FREX
												(frame exposure enable)
										 Bit[2]: VarioPixel for VGA, CIF, 
												 QVGA, QCIF, QQVGA, and QQCIF
										 Bit[1]: Reserved
										 Bit[0]: Single frame output (used for
												 Frame Exposure mode only)
												 
										 Dfe: 0x00
									*/
	OV9650_REG_COM4 		= 0x0D,	/**< Common Control 4
										 Bit[7]: VarioPixel for QVGA, QCIF,
												 QQVGA, and QQCIF
										 Bit[6:3]: Reserved
										 Bit[2]: Tri-state option for output
												 clock at power-down period
											0: Tri-state at this period
											1: No tri-state at this period
										 Bit[1]: Tri-state option for output
												 data at power-down period
											0: Tri-state at this period
											1: No tri-state at this period
										 Bit[0]: Reserved
										 Def: 0x00
									*/
	OV9650_REG_COM5 		= 0x0E,	/**< Common Control 5
										 Bit[7]: System clock selection.
												 If the system clock is
												 48 MHz, this bit should 
												 be set to high to get 
												 15 fps for YUV or RGB
										 Bit[6:5]: Reserved
										 Bit[4]: Slam mode enable
											0: Master mode
											1: Slam mode (used for slave mode)
										 Bit[3:0]: Reserved
										 
										 Def: 0x01
									*/
	OV9650_REG_COM6 		= 0x0F,	/**< Common Control 6
										 Bit[7]: Output of optical 
												 black line option
											0: Disable HREF at optical black
											1: Enable HREF at optical black
										 Bit[6:4]: Reserved
										 Bit[3]: Enable bias for ADBLC
										 Bit[2]: ADBLC offset
											0: Use 4-channel ADBLC
											1: Use 2-channel ADBLC
										 Bit[1]: Reset all timing when 
												 format changes
										 Bit[0]: Enable ADBLC option
										 
										 Def: 0x43
									*/
	OV9650_REG_AECH 		= 0x10,	/**< Exposure Value
										 Bit[7:0]: AEC[9:2] (see registers 
												   AECHM for AEC[15:10]
												   and COM1
													for AEC[1:0])
										 
										 Def: 0x40
									*/
	OV9650_REG_CLKRC 		= 0x11,	/**< Data Format and Internal Clock
										 Bit[7]: Digital PLL option
											0:  Disable double clock option,
												meaning the maximum
											    PCLK can be as high as 
												half input clock
											1: Enable double clock option,
												meaning the maximum
											    PCLK can be as high 
												as input clock
										 Bit[6]: Use input clock directly 
												(no clock pre-scale available)
										 Bit[5:0]: Internal clock pre-scalar
												   F(internal clock) = 
												   F(input clock)/(Bit[5:0]+1)
												   Range: [0 0000] to [1 1111]
											
										 Def: 0x00
									*/
	OV9650_REG_COM7			= 0x12,	/**< Common Control 7
											Bit[7]: SCCB Register Reset
												0: No change
												1: Resets all registers to 
												   default values
											Bit[6]: Output format - 
											        VGA selection
											Bit[5]: Output format - 
											        CIF selection
											Bit[4]: Output format - 
											        QVGA selection
											Bit[3]: Output format - 
											        QCIF selection
											Bit[2]: Output format - 
											        RGB selection
											Bit[1]: Reserved
											Bit[0]: Output format - 
											        Raw RGB (COM7[2] must
 													be set high)
											
											Def: 0x00
									*/
	OV9650_REG_COM8			= 0x13,	/**< Common Control 8
											Bit[7]: Enable fast AGC/AEC
         											algorithm
											Bit[6]: AEC - Step size limit
												0: Fast condition change 
												   maximum step is VSYNC
												1: Unlimited step size
											Bit[5]: Banding filter ON/OFF
											Bit[4:3]: Reserved
											Bit[2]: AGC Enable
											Bit[1]: AWB Enable
											Bit[0]: AEC Enable
											
											Def: 0x8F
									*/
	OV9650_REG_COM9			= 0x14,	/**< Common Control 9
											Bit[7]: Reserved
											Bit[6:4]: Automatic Gain Ceiling-
											          maximum AGC value
												000: 2x
												001: 4x
												010: 8x
												011: 16x
												100: 32x
												101: 64x
												110: 128x
											Bit[3]: Exposure timing can be
											        less than limit of banding
													filter when light is too 
													strong
											Bit[2]: Data format - VSYNC drop 
											        option
												0: VSYNC always exists
												1: VSYNC will drop when frame 
												   data drops
											Bit[1]: Enable drop frame when 
											        AEC step is larger than
													the Exposure Gap
											Bit[0]: Freeze AGC/AEC 
											
											Def: 0x4A
									*/
	OV9650_REG_COM10		= 0x15,	/**< Common Control 10
											Bit[7]: Set pin definition
												1: Set RESET to SLHS (slave
 												   mode horizontal sync) and
												   set PWDN to SLVS (slave 
												   mode vertical sync)
											Bit[6]: HREF changes to HSYNC
											Bit[5]: PCLK output option
												0: PCLK always output
												1: No PCLK output when HREF is
     												low
											Bit[4]: PCLK reverse
											Bit[3]: HREF reverse
											Bit[2]: Reset signal end point 
											        option
											Bit[1]: VSYNC negative
											Bit[0]: HSYNC negative 
											
											Def: 0x00
									*/
	OV9650_REG_RSVD0		= 0x16,	/**< Reserved */

	OV9650_REG_HSTART		= 0x17,	/**< Output Format - Horizontal Frame 
	                                     (HREF column) start high 8-bit (low
											3 bits are at HREF[2:0]) 
											
											Def: 0x1A
									*/

	OV9650_REG_HSTOP		= 0x18,	/**< Output Format - Horizontal Frame 
	                                     (HREF column) end high 8-bit (low
										  3 bits are at HREF[5:3]) 
										  
										 Def: 0xBA
									*/

	OV9650_REG_VSTRT		= 0x19,	/**< Output Format - Vertical Frame (row)
                                     	  start high 8-bit (low 3 bits are at
										  VREF[2:0]) 
										  
										  Def: 0x01
									*/

	OV9650_REG_VSTOP 		= 0x1A,	/**< Output Format - Vertical Frame 
	                                     (row) end high 8-bit (low 3 bits 
										  are at VREF[5:3])
										 
										 Def: 0x81
									*/
	OV9650_REG_PSHFT 		= 0x1B,	/**< Data Format - Pixel Delay Select 
	                                    (delays timing of the D[9:0] data 
										relative to HREF in pixel units)
											Range: [00] (no delay) to [FF]
											(256 pixel delay which accounts
											for whole array)
										
										Def: 0x00
									*/
	OV9650_REG_MIDH 		= 0x1C,	/**< Manufacturer ID Byte – 
	                                     High (Read only = 0x7F) 
									*/

	OV9650_REG_MIDL 		= 0x1D,	/**< Manufacturer ID Byte – 
	                                     Low (Read only = 0xA2) 
									*/
	OV9650_REG_MVFP 		= 0x1E,	/**< Mirror/VFlip Enable
											Bit[7:6]: Reserved
											Bit[5]: Mirror
												0: Normal image
												1: Mirror image
											Bit[4]: VFlip enable
												0: VFlip disable
												1: VFlip enable
											Bit[3:0]: Reserved 
											
											Def: 0x00
									*/
	OV9650_REG_LAEC 		= 0x1F,	/**< Reserved */

	OV9650_REG_BOS 			= 0x20,	/**< B Channel ADBLC Result
											Bit[7]: Offset adjustment sign
												0: Add offset	
												1: Subtract offset
											Bit[6:0]: Offset value of 10-bit
													  range (high 7 bits)
													  
											Def: 0x80
									*/

	OV9650_REG_GBOS			= 0x21,	/**< Gb channel ADBLC result
											Bit[7]: Offset adjustment sign
												0: Add offset
												1: Subtract offset
											Bit[6:0]: Offset value of 10-bit
													  range 
											
											Def: 0x80
									*/

	OV9650_REG_GROS 		= 0x22,	/**< Gr channel ADBLC result
											Bit[7]: Offset adjustment sign
												0: Add offset
												1: Subtract offset
											Bit[6:0]: Offset value of 10-bit
													  range 
											
											Def: 0x80
									*/

	OV9650_REG_ROS			= 0x23,	/**< R channel ADBLC result
											Bit[7]: Offset adjustment sign
												0: Add offset
												1: Subtract offset
											Bit[6:0]: Offset value of 10-bit 
													  range 
											
											Def: 0x80
									*/

	OV9650_REG_AEW			= 0x24,	/**< AGC/AEC - Stable Operating Region 
										(Upper Limit)
										
										Def: 0x78
									*/

	OV9650_REG_AEB	 		= 0x25,	/**< AGC/AEC - Stable Operating Region 
										(Lower Limit)
										
										Def: 0x68
									*/
	OV9650_REG_VPT	 		= 0x26,	/**< AGC/AEC Fast Mode Operating Region
											Bit[7:4]: High nibble of 
													  upper limit
											Bit[3:0]: High nibble of 
													  lower limit 
										
										Def: 0xD4
									*/
	OV9650_REG_BBIAS 		= 0x27,	/**< B Channel Signal Output Bias 
										(effective only when COM6[0] = 1)
											Bit[7]: Bias adjustment sign
												0: Add bias
												1: Subtract bias
											Bit[6:0]: Bias value of 10-bit
												range
											
											Def: 0x80
									*/
	OV9650_REG_GbBIAS 		= 0x28,	/**< Gb Channel Signal Output Bias 
										(effective only when COM6[0] = 1)
											Bit[7]: Bias adjustment sign
												0: Add bias
												1: Subtract bias
											Bit[6:0]: Bias value of 10-bit
													range
											
										Def: 0x80
									*/
	OV9650_REG_Gr_COM 		= 0x29,	/**< Analog BLC and Regulator Control
											Bit[7:6]: Reserved
											Bit[5]: Bypass Analog BLC
											Bit[4]: Bypass regulator
											Bit[3:0]: Reserved
											
										Def: 0x00
									*/
	OV9650_REG_EXHCH 		= 0x2A,	/**< Dummy Pixel Insert MSB
											Bit[7]: Reserved
											Bit[6:4]: 3 MSB for dummy pixel
													  insert in horizontal
													  direction
											Bit[3:2]: HSYNC falling edge
													  delay 2 MSB
											Bit[1:0]: HSYNC rising edge
											          delay 2 MSB
											
											Def: 0x00
									*/
	OV9650_REG_EXHCL 		= 0x2B,	/**< Dummy Pixel Insert LSB
										 8 LSB for dummy pixel insert 
										 in horizontal direction
										 
										 Def: 0x00
									*/
	OV9650_REG_RBIAS 		= 0x2C,	/**< R Channel Signal Output Bias 
										(effective only when COM6[0] = 1)
											Bit[7]: Bias adjustment sign
												0: Add bias
												1: Subtract bias
											Bit[6:0]: Bias value of 10-bit
												range2
											
											Def: 0x80
									*/
	OV9650_REG_ADVFL 		= 0x2D,	/**< LSB of insert dummy lines in vertical
										 direction (1 bit equals 1 line)*/

	OV9650_REG_ADVFH 		= 0x2E,	/**< MSB of insert dummy lines in vertical
										 direction*/
	OV9650_REG_YAVE 		= 0x2F,	/**< Y/G Channel Average Value
										
										Def: 0x00
									*/
	OV9650_REG_HSYST 		= 0x30,	/**< HSYNC Rising Edge Delay (low 8 bits)
										
										Def: 0x08
									*/
	OV9650_REG_HSYEN		= 0x31,	/**< HSYNC Falling Edge Delay (low 8 bits)
										
										Def: 0x30
									*/
	OV9650_REG_HREF 		= 0x32,	/**< HREF Control
											Bit[7:6]: HREF edge offset to data
													  output
											Bit[5:3]: HREF end 3 LSB (high
											          8 MSB at register HSTOP)
											Bit[2:0]: HREF start 3 LSB (high
													  8 MSB at register HSTART) 
											
											Def: 0xA4
									*/
	OV9650_REG_CHLF 		= 0x33,	/**< Bit[7:0]: Reserved
											
											Def: 0x00
									*/
	OV9650_REG_ARBLM 		= 0x34,	/**< Bit[7:0]: Reserved
											
											Def: 0x03
									*/
	OV9650_REG_RSVD1		= 0x35,	/**< Reserved */
	OV9650_REG_RSVD2 		= 0x36,	/**< Reserved */
	OV9650_REG_ADC	 		= 0x37,	/**< Bit[7:0]: Reserved
											
											Def: 0x04
									*/

	OV9650_REG_ACOM 		= 0x38,	/**< Bit[7:0]: Reserved
											
											Def: 0x12
									*/
	OV9650_REG_OFON 		= 0x39,	/**< Bit[7:4]: Reserved
										 Bit[3]: Line buffer power down
										 - must be set to "1" before chip
										 power down
										 Bit[2:0]: Reserved
										 
										 Def: 0x00
									*/
	OV9650_REG_TSLB 		= 0x3A,	/**< Line Buffer Test Option
											Bit[7:6]: Reserved
											Bit[5]: Bit-wise reverse
											Bit[4]: UV output value
												0: Use normal UV output
												1: Use fixed UV value set
													in registers MANU and
													MANV as UV output 
													instead of chip output
											Bit[3:2]: Output sequence is 
													Y U Y V instead of U Y V Y
												00: Y U Y V
												01: Y V Y U
												10: V Y U Y
												11: U Y V Y
											Bit[1]: Reserved
											Bit[0]: Digital BLC enable
												0: Disable
												1: Enable
											
											Def: 0x0C
									*/
	OV9650_REG_COM11		= 0x3B,	/**< Common Control 11
											Bit[7]: Night mode
												0: Night mode disable
												1: Night mode enable -
												   If the AGC gain goes
												   over 2, then AGC gain
												   drops to 0 and frame rate
												   changes by half.
											       COM11[6:5] limits the
												   minimum frame rate. Also,
												   ADVFH and ADVFL will be 
												   automatically updated.
											Bit[6:5]: Night mode insert frame
													option
												00: Normal frame rate
												01: 1/2 frame rate
												10: 1/4 frame rate
												11: 1/8 frame rate
											Bit[4:3]: Average calculation 
													 window option
												00: Use full frame
												01: Use half frame
												10: Use quarter frame
												11: Not allowed
											Bit[2:1]: Reserved
											Bit[0]: Manual banding filter mode
											
											Def: 0x00
									*/
	OV9650_REG_COM12 		= 0x3C,	/**< Common Control 12
											Bit[7]: HREF option
												0: No HREF when VREF is low
												1: Always has HREF
											Bit[6:3]: Reserved
											Bit[2]: Enable UV average
											Bit[1:0]: Reserved
											
											Def: 0x40
									*/
	OV9650_REG_COM13 		= 0x3D,	/**< Common Control 13
											Bit[7:6]: Gamma selection 
													  for signal
												00: No gamma function
												01: Gamma used for Y channel
													only
												10: Gamma used for Raw data
													before interpolation
												11: Not allowed
											Bit[5]: Reserved
											Bit[4]: Enable color matrix for
													RGB or YUV
											Bit[3]: Enable Y channel delay
													option
												0: Delay UV channel
												1: Delay Y channel
											Bit[2:0]: Output Y/UV delay
											
											Def: 0x99
									*/
	OV9650_REG_COM14 		= 0x3E,	/**< Common Control 14
											Bit[7:2]: Reserved
											Bit[1]: Enable edge enhancement
													for YUV output (effective
													only for YUV/RGB, no use
													for Raw data)
											Bit[0]: Edge enhancement option
												0: Edge enhancement
												   factor = EDGE[3:0]
												1: Edge enhancement
												   factor = 2 x EDGE[3:0]
											
											Def: 0x0E
									*/
	OV9650_REG_EDGE			= 0x3F,	/**< Edge Enhancement Adjustment
											Bit[7:4]: Edge enhancement
													  threshold[3:0]
													  (see register COM22[7:6}
													  for Edge threshold[5:4])
											Bit[3:0]: Edge enhancement factor
											
											Def: 0x88
									*/
	OV9650_REG_COM15 		= 0x40,	/**< Common Control 15
											Bit[7:6]: Data format - output
											full range enable
												0x: Output range: [10] to [F0]
												10: Output range: [01] to [FE]
												11: Output range: [00] to [FF]
											Bit[5:4]: RGB 555/565 option
													 (must set COM7[2] high)
												x0: Normal RGB output
												01: RGB 565
												11: RGB 555
											Bit[3]: Swap R/B in RGB565/RGB555
													format
											Bit[2:0]: Reserved
											
											Def: 0xC0
									*/
	OV9650_REG_COM16 		= 0x41,	/**< Common Control 16
											Bit[7:2]: Reserved
												Bit[1]: Color matrix 
												coefficient double option
												Bit[0]: Reserved
											
											Def: 0x10
									*/

	OV9650_REG_COM17 		= 0x42,	/**< Common Control 17
											Bit[7:5]: Reserved
											Bit[4]: Edge enhancement option
											Bit[3]: Reserved
											Bit[2]: Select single frame out
											Bit[1]: Tri-state output after single
													frame out
											Bit[0]: Reserved
											
											Def: 0x08
									*/
	OV9650_REG_RSVD3 		= 0x43,	/**< Reserved */
	OV9650_REG_RSVD4 		= 0x44,	/**< Reserved */
	OV9650_REG_RSVD5 		= 0x45,	/**< Reserved */
	OV9650_REG_RSVD6 		= 0x46,	/**< Reserved */
	OV9650_REG_RSVD7 		= 0x47,	/**< Reserved */
	OV9650_REG_RSVD8 		= 0x48,	/**< Reserved */
	OV9650_REG_RSVD9 		= 0x49,	/**< Reserved */
	OV9650_REG_RSVD10 		= 0x4A,	/**< Reserved */
	OV9650_REG_RSVD11 		= 0x4B,	/**< Reserved */
	OV9650_REG_RSVD12 		= 0x4C,	/**< Reserved */
	OV9650_REG_RSVD13 		= 0x4D,	/**< Reserved */
	OV9650_REG_RSVD14 		= 0x4E,	/**< Reserved */

	OV9650_REG_MTX1 		= 0x4F,	/**< Matrix Coefficient 1 */
	OV9650_REG_MTX2 		= 0x50,	/**< Matrix Coefficient 2 */
	OV9650_REG_MTX3 		= 0x51,	/**< Matrix Coefficient 3 */
	OV9650_REG_MTX4 		= 0x52,	/**< Matrix Coefficient 4 */
	OV9650_REG_MTX5 		= 0x53,	/**< Matrix Coefficient 5 */
	OV9650_REG_MTX6 		= 0x54,	/**< Matrix Coefficient 6 */
	OV9650_REG_MTX7 		= 0x55,	/**< Matrix Coefficient 7 */
	OV9650_REG_MTX8 		= 0x56,	/**< Matrix Coefficient 8 */
	OV9650_REG_MTX9 		= 0x57,	/**< Matrix Coefficient 9 */

	OV9650_REG_MTXS			= 0x58,	/**< Matrix Coefficient Sign for
										 coefficient 9 to 2
											0: Plus
											1: Minus
										
										Def: 0x0F
									*/
	OV9650_REG_RSVD15			= 0x59,	/**< Reserved */
	OV9650_REG_RSVD16		= 0x5A,	/**< Reserved */
	OV9650_REG_RSVD17		= 0x5B,	/**< Reserved */
	OV9650_REG_RSVD18		= 0x5C,	/**< Reserved */
	OV9650_REG_RSVD19		= 0x5D,	/**< Reserved */
	OV9650_REG_RSVD20		= 0x5E,	/**< Reserved */
	OV9650_REG_RSVD21		= 0x5F,	/**< Reserved */
	OV9650_REG_RSVD22		= 0x60,	/**< Reserved */
	OV9650_REG_RSVD23		= 0x61,	/**< Reserved */
	OV9650_REG_LCC1			= 0x62,	/**< Lens Correction Option 1 */
	OV9650_REG_LCC2			= 0x63,	/**< Lens Correction Option 2 */
	OV9650_REG_LCC3			= 0x64,	/**< Lens Correction Option 3 */
	OV9650_REG_LCC4			= 0x65,	/**< Lens Correction Option 4 */
	OV9650_REG_LCC5			= 0x66,	/**< Lens Correction Option */

	OV9650_REG_MANU			= 0x67,	/**< Manual U Value (effective 
										 only when register TSLB[4]
										 is high)
										 
										 Def: 0x80
									*/
	OV9650_REG_MANV			= 0x68,	/**< Manual V Value (effective
										 only when register TSLB[4]
										 is high)
										 
										 Def: 0x80
									*/
	OV9650_REG_HV			= 0x69,	/**< Manual Banding Filter MSB
											Bit[7:1]: Reserved
											Bit[0]: Matrix coefficient
													1 sign
											
											Def: 0x00
									*/

	OV9650_REG_MBD	 		= 0x6A,	/**< Manual Banding Filter Value
										(effective only when COM11[0]
										is high).
										
										Def: 0x00
									*/
	OV9650_REG_DBLV 		= 0x6B,	/**< Reserved */

	OV9650_REG_GSP	 		= 0x6C,	/**< Gamma curve */
	OV9650_REG_GSP1	 		= 0x6D,	/**< Gamma curve */
	OV9650_REG_GSP2	 		= 0x6E,	/**< Gamma curve */
	OV9650_REG_GSP3	 		= 0x6F,	/**< Gamma curve */
	OV9650_REG_GSP4	 		= 0x70,	/**< Gamma curve */
	OV9650_REG_GSP5	 		= 0x71,	/**< Gamma curve */
	OV9650_REG_GSP6	 		= 0x72,	/**< Gamma curve */
	OV9650_REG_GSP7	 		= 0x73,	/**< Gamma curve */
	OV9650_REG_GSP8	 		= 0x74,	/**< Gamma curve */
	OV9650_REG_GSP9	 		= 0x75,	/**< Gamma curve */
	OV9650_REG_GSPA	 		= 0x76,	/**< Gamma curve */
	OV9650_REG_GSPB	 		= 0x77,	/**< Gamma curve */
	OV9650_REG_GSPC	 		= 0x78,	/**< Gamma curve */
	OV9650_REG_GSPD	 		= 0x79,	/**< Gamma curve */
	OV9650_REG_GSPE	 		= 0x7A,	/**< Gamma curve */
	OV9650_REG_GSPF	 		= 0x7B,	/**< Gamma curve */

	OV9650_REG_GST	 		= 0x7C,	/**< Gamma curve */
	OV9650_REG_GST1	 		= 0x7D,	/**< Gamma curve */
	OV9650_REG_GST2	 		= 0x7E,	/**< Gamma curve */
	OV9650_REG_GST3	 		= 0x7F,	/**< Gamma curve */
	OV9650_REG_GST4	 		= 0x80,	/**< Gamma curve */
	OV9650_REG_GST5	 		= 0x81,	/**< Gamma curve */
	OV9650_REG_GST6	 		= 0x82,	/**< Gamma curve */
	OV9650_REG_GST7	 		= 0x83,	/**< Gamma curve */
	OV9650_REG_GST8	 		= 0x84,	/**< Gamma curve */
	OV9650_REG_GST9	 		= 0x85,	/**< Gamma curve */
	OV9650_REG_GSTA	 		= 0x86,	/**< Gamma curve */
	OV9650_REG_GSTB	 		= 0x87,	/**< Gamma curve */
	OV9650_REG_GSTC	 		= 0x88,	/**< Gamma curve */
	OV9650_REG_GSTD	 		= 0x89,	/**< Gamma curve */
	OV9650_REG_GSTE	 		= 0x8A,	/**< Gamma curve */
	OV9650_REG_GSTF	 		= 0x8B,	/**< Gamma curve */ 

	OV9650_REG_COM21	 	= 0x8B,	/**< Common Control 21
											Bit[7:0]: Reserved
											
											Def: 0x04
									*/
	OV9650_REG_COM22	 	= 0x8C,	/**< Common Control 22
											Bit[7:6]: Edge enhancement
													  threshold[5:4]
                                                      (see register EDGE[7:4}
													  for Edge threshold[3:0])
											Bit[5]: De-noise enable
											Bit[4:2]: Reserved
											Bit[1]: White-pixel erase enable
											Bit[0]: White-pixel erase option
											
											Def: 0x00
									*/
	OV9650_REG_COM23 		= 0x8D,	/**< Common Control 23
											Bit[7:5]: Reserved
											Bit[4]: Color bar test mode
											Bit[3:2]: Reserved
											Bit[1]: Color gain option
												0: Analog
												1: Digital
											Bit[0]: Reserved
											
											Def: 0x00
									*/

	OV9650_REG_COM24 		= 0x8E,	/**< Common Control 24
											Bit[7:0]: Reserved 
										
										Def: 0x00
									*/
	OV9650_REG_DBLC1		= 0x8F,	/**< Digital BLC Offset Sign
											Bit[7:4]: Reserved
											Bit[3]: Digital BLC B offset sign
											Bit[2]: Digital BLC R offset sign
											Bit[1]: Digital BLC Gb offset sign
											Bit[0]: Digital BLC Gr offset sign
										
										Def: 0x0F
									*/
	OV9650_REG_DBLC_B		= 0x90,	/**< Digital BLC B Channel Offset Value
											Bit[7:0]: Digital BLC B channel
											offset value
										
										Def: 0x00
									*/

	OV9650_REG_DBLC_R 		= 0x91,	/**< Digital BLC R Channel Offset Value
											Bit[7:0]: Digital BLC R channel
											offset value
										
										Def: 0x00
									*/
	OV9650_REG_DM_LNL		= 0x92,	/**< Dummy Line low 8 bits
											Bit[7:0]: Control insert Dummy
											line[7:0]
										
										Def: 0x00
									*/
	OV9650_REG_DM_LNH		= 0x93,	/**< Dummy Line high 8 bits
											Bit[7:0]: Control insert Dummy
											line[15:8]
										
										Def: 0x00
									*/

	OV9650_REG_RSVD24		= 0x94,	/**< Reserved */
	OV9650_REG_RSVD25		= 0x95,	/**< Reserved */
	OV9650_REG_RSVD26		= 0x96,	/**< Reserved */
	OV9650_REG_RSVD27		= 0x97,	/**< Reserved */
	OV9650_REG_RSVD28		= 0x98,	/**< Reserved */
	OV9650_REG_RSVD29		= 0x99,	/**< Reserved */
	OV9650_REG_RSVD30		= 0x9A,	/**< Reserved */
	OV9650_REG_RSVD31		= 0x9B,	/**< Reserved */
	OV9650_REG_RSVD32		= 0x9C,	/**< Reserved */

	OV9650_REG_LCCFB		= 0x9D,	/**< Lens Correction B Channel Control */
	OV9650_REG_LCCFR		= 0x9E,	/**< Lens Correction R Channel Control */
	OV9650_REG_DBLC_Gb		= 0x9F,	/**< Digital BLC Gb Channel Offset Value
											Bit[7:0]: Digital BLC Gb channel
											offset value
										
										Def: 0x00
									*/
	OV9650_REG_DBLC_Gr		= 0xA0,	/**< Digital BLC Gr Channel Offset Value
											Bit[7:0]: Digital BLC Gr channel
											offset value
										
										Def: 0x00
									*/
	OV9650_REG_AECHM		= 0xA1,	/**< Exposure Value - AEC MSB 5 bits
											Bit[7:6]: Reserved
											Bit[5:0]: AEC[15:10] (see
											registers AECH for AEC[9:2] and
											COM1 for AEC[1:0])
										
										Def: 0x40
									*/

	OV9650_REG_RSVD33		= 0xA2,	/**< Reserved */
	OV9650_REG_RSVD34		= 0xA3,	/**< Reserved */

	OV9650_REG_COM25		= 0xA4,	/**< Common Control 25
											Bit[7:0]: Reserved
										
										Def: 0x00
									*/
	OV9650_REG_COM26		= 0xA5,	/**< Common Control 26
											Bit[7:0]: Reserved
										
										Def: 0x00
									*/

	OV9650_REG_G_GAIN		= 0xA6, /**< Reserved */
	OV9650_REG_VGS_ST		= 0xA7, /**< Reserved */

	OV9650_REG_ACOM1		= 0xA8, /**< Reserved */
	OV9650_REG_ACOM2		= 0xA9, /**< Reserved */
	OV9650_REG_ACOM3		= 0xAA, /**< Reserved */
	OV9650_REG_ACOM4		= 0xAB, /**< Reserved */

} ov9650_reg_t;
/**  @} */

/******************************************************************************/
/*                           Macro Definitions                                */
/******************************************************************************/

/* 
 * Bit Register Def. 
 */
 
/* Bit Resolution. */
#define OV9650_COM7_VGA      (1 << 6)
#define OV9650_COM7_CIF      (1 << 5)
#define OV9650_COM7_QVGA     (1 << 4)
#define OV9650_COM7_QCIF     (1 << 3)
#define OV9650_COM7_RGB      (1 << 2)
#define OV9650_COM7_RAW_RGB  (1 << 0)

/* QQVGA or QQCIF resolution */
#define OV9650_COM1_QQVGA    (1 << 5)
#define OV9650_COM1_QQCIF    (1 << 5)

/* Enable color matrix for RGB or YUV */
#define OV9650_COM13_COLOR	(1 << 4)

/* Bit flip x register. */
#define OV9650_MVFP_X_FLIP   (1 << 5)
/* Bit flip y register. */
#define OV9650_MVFP_Y_FLIP   (1 << 4)

/* Sleep mode bit. */
#define OV9650_SLEEP_MODE    (1 << 4)

 /* Reset bit. */
#define OV9650_BIT_RESET		(1 << 7)    /** Reset Software 
                                                of the camera chip. */

/* Exsternal clock. */
#define OV9650_BIT_EXT_CLK		(1 << 6)	/** Use input clock directly. */

/* Fast AGC_AEC */
#define OV9650_BIT_FAST_AGC_AEC	(1 << 7)	/** Fast AGC_AEC */

/* Unlimited step size */
#define OV9650_BIT_AEC_UNLIM_STEP_SIZE	(1 << 6)	/** Unlimited step size */

/* QVGA MODE */
#define OV9650_BIT_QVGA					(1 << 4)	/** QVGA mode */

/* Bit Sleep mode */
#define OV9650_BIT_SOFT_SLEEP		(1 << 4) /** Setting this bit the camera goes
										         in sleep mode. */
/* DEVID register */
#define OV9650_DEVICE_ID 				0x60	/**< The I2C slave device ID */

#define OV9650_PROD_IDH					0x7F    /**< Product ID (Hight byte)*/
#define OV9650_PROD_IDL					0xA2    /**< Product ID (Low byte) */

#define OV9650_PROD_PID					0x96    /**< Product PID */

#endif /* OV9650_REG_H_ */
