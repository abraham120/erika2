/*
Copyright (C) 2011 -  Salvatore Marrapese, Riccardo Pelliccia, 
Christian Nastasi and Marco Ghibaudi.
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

/*
 * ee_ov9659_camera_board.h
 *
 * Created on: 11-July-2012
 * Author: Salvatore Marrapese, Riccardo Pelliccia, 
 *         Christian Nastasi, Marco Ghibaudi
 */

#ifndef OV9650_HAL_EE_BOARD_SINGLE_128K_H
#define OV9650_HAL_EE_BOARD_SINGLE_128K_H


/* Specific Definitions	*/

#ifndef OV9650_OC_PORT
#define OV9650_OC_PORT 		EE_OC_4
#endif

#ifndef OV9650_I2C_PORT
#define OV9650_I2C_PORT 	EE_I2C_PORT_1A
#endif

/**
* @name Enable pin
* \brief Settings for D2 pin used like camera power down pin (see OV9650 documentation).
*        Note carefully
*/
#define OV9650_PIN_PWDN_INIT() 	TRISDbits.TRISD2=0	/* Init enable pin */
#define OV9650_PIN_PWDN_ON() 	LATDbits.LATD2=0	/* Set pin to low value (normal mode)*/
#define OV9650_PIN_PWDN_OFF() 	LATDbits.LATD2=1	/* Set pin to high value (power down mode)*/
/**  @} */

/**
* @name Reset pin
* \brief Settings for D1 pin used like camera reset pin (see OV9650 documentation)
*/
#define OV9650_PIN_RESET_INIT() 	TRISDbits.TRISD1=0	/* Init reset pin */
#define OV9650_PIN_RESET_ON() 		LATDbits.LATD1=1	/* Set pin to high value (reset on)*/
#define OV9650_PIN_RESET_OFF() 		LATDbits.LATD1=0	/* Set pin to low value (reset off)*/
/**  @} */

/**
* @name Vertical Sync
*
* INT0. Functions to set, reset, start, stop the vertical sync interrupt
*
* @{ */
#define OV9650_PIN_VSYNC_INIT_POSITIVE()\
do {\
	INTCONbits.INT2EP = 1;	/*  Extern Interrupt on positive edge */	\
} while (0)\

#define OV9650_PIN_VSYNC_INIT_NEGATIVE()\
do {\
	INTCONbits.INT2EP = 0;	/*  Extern Interrupt on negative edge */	\
} while (0)\

#define OV9650_PIN_VSYNC_START()\
do {\
	IPC2bits.INT2IP = 7;\
	IEC0bits.INT2IE = 1;\
	IFS0bits.INT2IF = 0;\
} while (0)\

#define OV9650_PIN_VSYNC_STOP()\
do {\
	IEC0bits.INT2IE = 0;	/*  Disable INT2 interrupt */\
	IFS0bits.INT2IF = 0;	/*  Reset INT2 interrupt flag */\
} while (0)\

#define OV9650_VSYNC_RESET_IF()\
do {\
	IFS0bits.INT2IF = 0;	/*  Reset INT2 interrupt flag */\
} while (0)\

#define OV9650_VSYNC_IF_VALUE	IFS0bits.INT2IF /*  Return INT2 interrupt flag value*/


#define OV9650_VSYNC_INTERRUPT()  ISR1(_EXTERNAL_2_VECTOR)

/**  @} */

/**
* @name Horizontal Sync
*
* CN2 (RB0). Functions to set, reset, start, stop the horizontal sync interrupt
*
* @{ */
#define OV9650_PIN_HSYNC_INIT()		EE_cn_init(7, 3)
#define OV9650_PIN_HSYNC_START()	EE_cn_enable(ov9650_cn2)
#define OV9650_PIN_HSYNC_STOP()		EE_cn_disable(ov9650_cn2)
#define OV9650_HSYNC_RESET_IF() 	
#define OV9650_HSYNC_INTERRUPT() 	EE_CN_HANDLER(ov9650_cn2)
#define OV9650_HSYNC_VALUE() 		PORTBbits.RB0

#define OV9650_HSYNC_RISING			EE_CN_POLARITY_POS
#define OV9650_HSYNC_FALLING		EE_CN_POLARITY_NEG

/**  @} */

/**
* @name Video (Pixels) Clock
*
* INT1. It's the pixel interrupt: everytime this interrupt occurs a pixel is
* captured.
*
* @{ */
#define OV9650_PIN_VCLK_INIT()\
do {\
	TRISEbits.TRISE8 = 1;	\
	INTCONbits.INT1EP = 0;	/* Extern Interrupt on negative edge */\
	IPC1bits.INT1IP  = 6;	/* Set INT1 interrupt priority */\
} while (0)
	
#define OV9650_PIN_VCLK_START()\
do {\
	IEC0bits.INT1IE = 1;	/*Enable INT1 interrupt */	\
	IFS0bits.INT1IF = 0;	/* Reset INT1 interrupt flag */	 \
} while (0)

#define OV9650_PIN_VCLK_STOP()\
do {\
	IEC0bits.INT1IE = 0;	/* Disable INT1 interrupt */\
	IFS0bits.INT1IF = 0;	/* Reset INT1 interrupt flag */	\
} while (0)

/*Position of the interrupt associated with VCLK inside the interrupt table */
#define OV9650_PCLK_INT_TABLE_POSITION		_EXTERNAL_1_IRQ

#define OV9650_PCLK_INTERRUPT()  	ISR1(_EXTERNAL_1_VECTOR)

#define OV9650_PCLK_RESET_IF() 		IFS0bits.INT1IF = 0
#define OV9650_PCLK_IF_VALUE() 		IFS0bits.INT1IF

#define OV9650_PCLK_PIN_VALUE()	PORTEbits.RE8

/**  @} */

/**
* @name Master Clock
*
* OC1 with Timer3. The output of this pin is the master clock for OV9650 camera.
* The master clock is the time reference of the camera. It's set a master clock
* with a frequency of 10MHz
*
* @{ */

#define OV9650_PIN_MCLK_INIT(freq)	ov9650_oc_hal_init(freq)	/* Init master clock */
#define OV9650_PIN_MCLK_START()		ov9650_oc_hal_start()		/* Start master clock */
#define OV9650_PIN_MCLK_STOP()		ov9650_oc_hal_stop()		/* Stop master clock */
/**  @} */

/**
* @name Pixel pins. In this set of 8 pins are received the 8 bits of each pixel.
* The pixel reception is regulated by the pixel clock
* @{ */
#define OV9650_PIN_Y_INIT()		ODCESET = 0x00FF 	/* Init PORT_E */
#define OV9650_PIN_Y_ADDRESS	(&PORTE)			/* Address PORT_E */
/**  @} */

/**
* @name Software interrupt: end of frame acquisition
*
* PMP ISR. This interrupt is generated when an entire frame is captured. This
* interrupt call inside his ISR the callback function passed on the capture
* function
* \see ov9650_capture
*
* @{ */

#define OV9650_PIN_EOF_INIT()\
do {\
	IPC7bits.PMPIP  = 5;	/* Set interrupt priority */\
	IPC7bits.PMPIS  = 0;	/* Set interrupt sub-priority */\
	IEC1bits.PMPIE = 1;	/* Enable interrupt */\
	IFS1bits.PMPIF = 0;	/* Reset interrupt flag */\
} while (0)

#define OV9650_PIN_EOF_STOP()\
do {\
	IEC1bits.PMPIE = 0;	/* Disable INT0 interrupt */\
	IFS1bits.PMPIF = 0;	/* Reset INT0 interrupt flag */\
} while (0)


#define OV9650_EOF_INTERRUPT() ISR2(_PMP_VECTOR)
#define OV9650_EOF_RESET_IF() IFS1bits.PMPIF = 0
#define OV9650_EOF_ACTIVATE_IF() IFS1bits.PMPIF = 1


#endif // OV9650_HAL_EE_BOARD_SINGLE_128K_H
