#ifndef __EE_HV7131GP_CAMERA_BOARD_H__
#define __EE_HV7131GP_CAMERA_BOARD_H__


/* Specific Definitions	*/

#ifndef HV7131GP_OC_PORT
#define HV7131GP_OC_PORT 	EE_OC_4
#endif

#ifndef HV7131GP_I2C_PORT
#define HV7131GP_I2C_PORT 	EE_I2C_PORT_1A
#endif


/**
* @name Enable pin
* \brief Settings for D2 pin used like camera enable pin (see HV7131GP documentation)
*/
#define HV7131GP_PIN_ENABLE_INIT() 	TRISDbits.TRISD2=0	/* Init enable pin */
#define HV7131GP_PIN_ENABLE_HIGH() 	LATDbits.LATD2=1	/* Set pin to high value*/
#define HV7131GP_PIN_ENABLE_LOW() 	LATDbits.LATD2=0	/* Set pin to low value*/
/**  @} */

/**
* @name Reset pin
* \brief Settings for D1 pin used like camera reset pin (see HV7131GP documentation)
*/
#define HV7131GP_PIN_RESETB_INIT() 	TRISDbits.TRISD1=0	/* Init reset pin */
#define HV7131GP_PIN_RESETB_HIGH() 	LATDbits.LATD1=1	/* Set pin to high value*/
#define HV7131GP_PIN_RESETB_LOW() 	LATDbits.LATD1=0	/* Set pin to low value*/
/**  @} */




/**
* @name Vertical Sync
*
* INT2. Functions to set, reset, start, stop the vertical sync interrupt
*
* @{ */
#define HV7131GP_PIN_VSYNC_INIT_POSITIVE()					\
do { 										\
	INTCONbits.INT2EP = 1;	/*  Extern Interrupt on positive edge */	\
	IPC2bits.INT2IP  = 7;	/*  Set INT2 interrupt priority */		\
} while (0)									\

#define HV7131GP_PIN_VSYNC_INIT_NEGATIVE()					\
do { 										\
	INTCONbits.INT2EP = 0;	/*  Extern Interrupt on negative edge */	\
	IPC2bits.INT2IP  = 7;	/*  Set INT2 interrupt priority */		\
} while (0)									\

#define HV7131GP_PIN_VSYNC_START()						\
do { 										\
	IEC0bits.INT2IE = 1;	/*  Enable INT2 interrupt */			\
	IFS0bits.INT2IF = 0;	/*  Reset INT2 interrupt flag */	 	\
} while (0)									\

#define HV7131GP_PIN_VSYNC_STOP()						\
do { 										\
	IEC0bits.INT2IE = 0;	/*  Disable INT2 interrupt */			\
	IFS0bits.INT2IF = 0;	/*  Reset INT2 interrupt flag */ 		\
} while (0)									\

#define HV7131GP_VSYNC_RESET_IF()						\
do { 										\
	IFS0bits.INT2IF = 0;	/*  Reset INT2 interrupt flag */	 	\
} while (0)									\

#define HV7131GP_VSYNC_IF_VALUE	IFS0bits.INT2IF /*  Return INT2 interrupt flag value*/


#define HV7131GP_VSYNC_INTERRUPT()  ISR1(_EXTERNAL_2_VECTOR)


/**  @} */

/**
* @name Horizontal Sync
*
* CN2 (RB0). Functions to set, reset, start, stop the horizontal sync interrupt
*
* @{ */
#define HV7131GP_PIN_HSYNC_INIT()	EE_cn_init(7, 3)
#define HV7131GP_PIN_HSYNC_START()	EE_cn_enable(hv7131gp_cn2)
#define HV7131GP_PIN_HSYNC_STOP()	EE_cn_disable(hv7131gp_cn2)
#define HV7131GP_HSYNC_RESET_IF() 	
#define HV7131GP_HSYNC_INTERRUPT() 	EE_CN_HANDLER(hv7131gp_cn2) 
#define HV7131GP_HSYNC_VALUE() 		PORTBbits.RB0

#define HV7131GP_HSYNC_RISING		EE_CN_POLARITY_POS			
#define HV7131GP_HSYNC_FALLING		EE_CN_POLARITY_NEG	






/**  @} */

/**
* @name Video (Pixels) Clock
*
* INT1. It's the pixel interrupt: everytime this interrupt occurs a pixel is
* captured.
*
* @{ */
#define HV7131GP_PIN_VCLK_INIT()					\
do { 									\
	TRISEbits.TRISE8 = 1;	/* TODO: understand why with this  */	\
				/* the VCLK pin must be configured */	\
				/* as an output			   */	\
	INTCONbits.INT1EP = 0;	/* Extern Interrupt on negative edge */	\
	IPC1bits.INT1IP  = 6;	/* Set INT1 interrupt priority */	\
} while (0)							
	
#define HV7131GP_PIN_VCLK_START()				\
do { 								\
	IEC0bits.INT1IE = 1;	/*Enable INT1 interrupt */	\
	IFS0bits.INT1IF = 0;	/* Reset INT1 interrupt flag */	 \
} while (0)							

#define HV7131GP_PIN_VCLK_STOP()				\
do { 								\
	IEC0bits.INT1IE = 0;	/* Disable INT1 interrupt */	\
	IFS0bits.INT1IF = 0;	/* Reset INT1 interrupt flag */	 \
} while (0)							


/*Position of the interrupt associated with VCLK inside the interrupt table */
#define HV7131GP_VCLK_INT_TABLE_POSITION		_EXTERNAL_1_IRQ	



#define HV7131GP_VCLK_INTERRUPT()  ISR1(_EXTERNAL_1_VECTOR) 		

#define HV7131GP_VCLK_RESET_IF() IFS0bits.INT1IF = 0
#define HV7131GP_VCLK_IF_VALUE() IFS0bits.INT1IF

#define  HV7131GP_VCLK_PIN_VALUE()	PORTEbits.RE8



/**  @} */

/**
* @name Master Clock
*
* OC1 with Timer3. The output of this pin is the master clock for HV7131GP camera.
* The master clock is the time reference of the camera. It's set a master clock
* with a frequency of 10MHz
*
* @{ */

#define HV7131GP_PIN_MCLK_INIT(freq)	hv7131gp_oc_hal_init(freq)	/* Init master clock */
#define HV7131GP_PIN_MCLK_START()	hv7131gp_oc_hal_start()	/* Start master clock */
#define HV7131GP_PIN_MCLK_STOP()	hv7131gp_oc_hal_stop()	/* Stop master clock */
/**  @} */

/**
* @name Pixel pins. In this set of 8 pins are received the 8 bits of each pixel.
* The pixel reception is regulated by the pixel clock
* @{ */
#define HV7131GP_PIN_Y_INIT()	TRISESET = 0x00FF 	/* Init PORT_E */
#define HV7131GP_PIN_Y_ADDRESS	(&PORTE)		/* Address PORT_E */
/**  @} */



/**
* @name Software interrupt: end of frame acquisition
*
* PMP ISR. This interrupt is generated when an entire frame is captured. This
* interrupt call inside his ISR the callback function passed on the capture
* function
* \see hv7131gp_capture
*
* @{ */


#define HV7131GP_PIN_EOF_INIT()						\
do { 									\
	IPC7bits.PMPIP  = 5;	/* Set interrupt priority */	\
	IPC7bits.PMPIS  = 0;	/* Set interrupt sub-priority */	\
	IEC1bits.PMPIE = 1;	/* Enable interrupt */		\
	IFS1bits.PMPIF = 0;	/* Reset interrupt flag */	 	\
} while (0)								

#define HV7131GP_PIN_EOF_STOP()						\
do { 									\
	IEC1bits.PMPIE = 0;	/* Disable INT0 interrupt */		\
	IFS1bits.PMPIF = 0;	/* Reset INT0 interrupt flag */	 	\
} while (0)								


#define HV7131GP_EOF_INTERRUPT() ISR2(_PMP_VECTOR)
#define HV7131GP_EOF_RESET_IF() IFS1bits.PMPIF = 0
#define HV7131GP_EOF_ACTIVATE_IF() IFS1bits.PMPIF = 1

#endif //__EE_HV7131GP_CAMERA_BOARD_H__
