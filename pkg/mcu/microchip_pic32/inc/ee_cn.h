/** 
* @file ee_cn.h
* @brief Change Notify driver
* @author Daniele Alessandrelli
* @author Christian Nastasi
* @version 0.1
* @date 2009-04-26
*
* This file is the driver for the Change Notify units
*
*/

 

#ifndef __INCLUDE_EE_CN_H__
#define __INCLUDE_EE_CN_H__

#ifdef __USE_CN__

#include "ee.h"
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif

//// portC
#define BIT_CN0 PORTCbits.RC14
#define BIT_CN1 PORTCbits.RC13
//// portB
#define BIT_CN2 PORTBbits.RB0
#define BIT_CN3 PORTBbits.RB1
#define BIT_CN4 PORTBbits.RB2
#define BIT_CN5 PORTBbits.RB3
#define BIT_CN6 PORTBbits.RB4
#define BIT_CN7 PORTBbits.RB5
//// portG
#define BIT_CN8 PORTGbits.RG6
#define BIT_CN9 PORTGbits.RG7
#define BIT_CN10 PORTGbits.RG8
#define BIT_CN11 PORTGbits.RG9
//// portB (again)
#define BIT_CN12 PORTBbits.RB15
//// portD
#define BIT_CN13 PORTDbits.RD4
#define BIT_CN14 PORTDbits.RD5
#define BIT_CN15 PORTDbits.RD6
#define BIT_CN16 PORTDbits.RD7
//// portF
#define BIT_CN17 PORTFbits.RF4
#define BIT_CN18 PORTFbits.RF5
//// portD (again)
#define BIT_CN19 PORTDbits.RD13
#define BIT_CN20 PORTDbits.RD14
#define BIT_CN21 PORTDbits.RD15
//// port used: B C D G F

union EE_cn_status_bits_t {
	struct {
		unsigned CN0:1;
		unsigned CN1:1;
		unsigned CN2:1;
		unsigned CN3:1;
		unsigned CN4:1;
		unsigned CN5:1;
		unsigned CN6:1;
		unsigned CN7:1;
		unsigned CN8:1;
		unsigned CN9:1;
		unsigned CN10:1;
		unsigned CN11:1;
		unsigned CN12:1;
		unsigned CN13:1;
		unsigned CN14:1;
		unsigned CN15:1;
		unsigned CN16:1;
		unsigned CN17:1;
		unsigned CN18:1;
		unsigned CN19:1;
		unsigned CN20:1;
		unsigned CN21:1;
	};
	struct {
		unsigned w:32;
	};
};

extern union EE_cn_status_bits_t EE_cn_status_bits;

#define EE_CN_POLARITY_NEG 0
#define EE_CN_POLARITY_POS 1

#define EE_CN_HANDLER(id) void EE_cn_handler_##id(void)
#define EE_cn_enable(id) EE_cn_enable_##id()
#define EE_cn_disable(id) EE_cn_disable_##id()
#define EE_cn_status(id) EE_cn_status_##id()
#define EE_cn_value(id) EE_cn_value_##id()

#include "ee_cn_config.h" /*TODO: temp solution while waiting for RT-Druid */

#ifdef EE_CN0
#define EE_CN0_enable 		EE_CN0(EE_cn_enable_)
#define EE_CN0_disable 		EE_CN0(EE_cn_disable_)
#define EE_CN0_status 		EE_CN0(EE_cn_status_)
#define EE_CN0_value 		EE_CN0(EE_cn_value_)
#define EE_CN0_handler 		EE_CN0(EE_cn_handler_)
#define EE_CN0_PORTBIT		PORTCbits.RC14
#define EE_CN0_SET_TRIS()			\
do {						\
	TRISCSET = _TRISC_TRISC14_MASK;		\
	/* TODO: set the AD1PCFG if Required!*/	\
} while (0)

__INLINE__ void EE_CN0_enable(void)
{
	#ifdef EE_CN0_PULLUP
	CNPUESET = _CNPUE_CNPUE0_MASK;
	#endif
	EE_cn_status_bits.CN0 = EE_CN0_PORTBIT;
	CNENSET = _CNEN_CNEN0_MASK;
}
__INLINE__ void EE_CN0_disable(void)
{
	CNENCLR = _CNEN_CNEN0_MASK;
	#ifdef EE_CN0_PULLUP
	CNPUECLR = _CNPUE_CNPUE0_MASK;
	#endif
}
__INLINE__ EE_UINT8 EE_CN0_status(void)
{
	return (CNEN & _CNEN_CNEN0_MASK);
}
__INLINE__ EE_UINT8 EE_CN0_value(void)
{
	return EE_cn_status_bits.CN0;
}
#else
#define EE_CN0_SET_TRIS()
#endif /* EE_CN0 */

#ifdef EE_CN1
#else
#define EE_CN1_SET_TRIS()
#endif /* EE_CN1 */

#ifdef EE_CN2

#define EE_CN2_enable 		EE_CN2(EE_cn_enable_)
#define EE_CN2_disable 		EE_CN2(EE_cn_disable_)
#define EE_CN2_status 		EE_CN2(EE_cn_status_)
#define EE_CN2_value 		EE_CN2(EE_cn_value_)
#define EE_CN2_handler 		EE_CN2(EE_cn_handler_)
#define EE_CN2_PORTBIT		PORTBbits.RB0
#define EE_CN2_SET_TRIS()			\
do {						\
	TRISBSET = _TRISB_TRISB0_MASK;		\
	AD1PCFGSET = _AD1PCFG_PCFG0_MASK;	\
} while (0)

__INLINE__ void EE_CN2_enable(void)
{
	#ifdef EE_CN2_PULLUP
	CNPUESET = _CNPUE_CNPUE2_MASK;
	#endif
	EE_cn_status_bits.CN2 = EE_CN2_PORTBIT;
	CNENSET = _CNEN_CNEN2_MASK;
}
__INLINE__ void EE_CN2_disable(void)
{
	CNENCLR = _CNEN_CNEN2_MASK;
	#ifdef EE_CN2_PULLUP
	CNPUECLR = _CNPUE_CNPUE2_MASK;
	#endif
}
__INLINE__ EE_UINT8 EE_CN2_status(void)
{
	return (CNEN & _CNEN_CNEN2_MASK);
}
__INLINE__ EE_UINT8 EE_CN2_value(void)
{
	return EE_cn_status_bits.CN2;
}


#else
#define EE_CN2_SET_TRIS()
#endif /* EE_CN2 */

#ifdef EE_CN3
#else
#define EE_CN3_SET_TRIS()
#endif /* EE_CN3 */

#ifdef EE_CN4

#define EE_CN4_enable 		EE_CN4(EE_cn_enable_)
#define EE_CN4_disable 		EE_CN4(EE_cn_disable_)
#define EE_CN4_status 		EE_CN4(EE_cn_status_)
#define EE_CN4_value 		EE_CN4(EE_cn_value_)
#define EE_CN4_handler 		EE_CN4(EE_cn_handler_)
#define EE_CN4_PORTBIT		PORTBbits.RB2
#define EE_CN4_SET_TRIS()			\
do {						\
	TRISBSET = _TRISB_TRISB2_MASK;		\
	/* TODO: set the AD1PCFG if Required!*/	\
} while (0)

__INLINE__ void EE_CN4_enable(void)
{
	#ifdef EE_CN4_PULLUP
	CNPUESET = _CNPUE_CNPUE4_MASK;
	#endif
	EE_cn_status_bits.CN4 = EE_CN4_PORTBIT;
	CNENSET = _CNEN_CNEN4_MASK;
}
__INLINE__ void EE_CN4_disable(void)
{
	CNENCLR = _CNEN_CNEN4_MASK;
	#ifdef EE_CN4_PULLUP
	CNPUECLR = _CNPUE_CNPUE4_MASK;
	#endif
}
__INLINE__ EE_UINT8 EE_CN4_status(void)
{
	return (CNEN & _CNEN_CNEN4_MASK);
}
__INLINE__ EE_UINT8 EE_CN4_value(void)
{
	return EE_cn_status_bits.CN4;
}

#else
#define EE_CN4_SET_TRIS()
#endif /* EE_CN4 */

#ifdef EE_CN5
#else
#define EE_CN5_SET_TRIS()
#endif /* EE_CN5 */

#ifdef EE_CN6
#else
#define EE_CN6_SET_TRIS()
#endif /* EE_CN6 */

#ifdef EE_CN7
#else
#define EE_CN7_SET_TRIS()
#endif /* EE_CN7 */

#ifdef EE_CN8
#else
#define EE_CN8_SET_TRIS()
#endif /* EE_CN8 */

#ifdef EE_CN9
#else
#define EE_CN9_SET_TRIS()
#endif /* EE_CN9 */

#ifdef EE_CN10
#else
#define EE_CN10_SET_TRIS()
#endif /* EE_CN10 */

#ifdef EE_CN11
#else
#define EE_CN11_SET_TRIS()
#endif /* EE_CN11 */

#ifdef EE_CN12
#else
#define EE_CN12_SET_TRIS()
#endif /* EE_CN12 */

#ifdef EE_CN13

#define EE_CN13_enable 		EE_CN13(EE_cn_enable_)
#define EE_CN13_disable 	EE_CN13(EE_cn_disable_)
#define EE_CN13_status 		EE_CN13(EE_cn_status_)
#define EE_CN13_value 		EE_CN13(EE_cn_value_)
#define EE_CN13_handler 	EE_CN13(EE_cn_handler_)
#define EE_CN13_PORTBIT		PORTDbits.RD4
#define EE_CN13_SET_TRIS()			\
do {						\
	TRISDSET = _TRISD_TRISD4_MASK;		\
	/* TODO: set the AD1PCFG if Required!*/	\
} while (0)

__INLINE__ void EE_CN13_enable(void)
{
	#ifdef EE_CN13_PULLUP 
	CNPUESET = _CNPUE_CNPUE13_MASK;
	#endif

	EE_cn_status_bits.CN13 = EE_CN13_PORTBIT;
	CNENSET = _CNEN_CNEN13_MASK;
}
__INLINE__ void EE_CN13_disable(void)
{
	CNENCLR = _CNEN_CNEN13_MASK;
	#ifdef EE_CN13_PULLUP
	CNPUECLR = _CNPUE_CNPUE13_MASK;
	#endif
}
__INLINE__ EE_UINT8 EE_CN13_status(void)
{
	return (CNEN & _CNEN_CNEN13_MASK);
}
__INLINE__ EE_UINT8 EE_CN13_value(void)
{
	return EE_cn_status_bits.CN13;
}
#else
#define EE_CN13_SET_TRIS()
#endif /* EE_CN13 */

#ifdef EE_CN14
#else
#define EE_CN14_SET_TRIS()
#endif /* EE_CN14 */

#ifdef EE_CN15
#define EE_CN15_enable 		EE_CN15(EE_cn_enable_)
#define EE_CN15_disable 	EE_CN15(EE_cn_disable_)
#define EE_CN15_status 		EE_CN15(EE_cn_status_)
#define EE_CN15_value 		EE_CN15(EE_cn_value_)
#define EE_CN15_handler 	EE_CN15(EE_cn_handler_)
#define EE_CN15_PORTBIT		PORTDbits.RD6
#define EE_CN15_SET_TRIS()			\
do {						\
	TRISDSET = _TRISD_TRISD6_MASK;		\
	/* TODO: set the AD1PCFG if Required!*/	\
} while (0)

__INLINE__ void EE_CN15_enable(void)
{
	#ifdef EE_CN15_PULLUP
	CNPUESET = _CNPUE_CNPUE15_MASK;
	#endif
	EE_cn_status_bits.CN15 = EE_CN15_PORTBIT;
	CNENSET = _CNEN_CNEN15_MASK;
}
__INLINE__ void EE_CN15_disable(void)
{
	CNENCLR = _CNEN_CNEN15_MASK;
	#ifdef EE_CN15_PULLUP
	CNPUECLR = _CNPUE_CNPUE15_MASK;
	#endif
}
__INLINE__ EE_UINT8 EE_CN15_status(void)
{
	return (CNEN & _CNEN_CNEN15_MASK);
}
__INLINE__ EE_UINT8 EE_CN15_value(void)
{
	return EE_cn_status_bits.CN15;
}
#else
#define EE_CN15_SET_TRIS()
#endif /* EE_CN15 */

#ifdef EE_CN16
#else
#define EE_CN16_SET_TRIS()
#endif /* EE_CN16 */

#ifdef EE_CN17
#else
#define EE_CN17_SET_TRIS()
#endif /* EE_CN17 */

#ifdef EE_CN18
#else
#define EE_CN18_SET_TRIS()
#endif /* EE_CN18 */

#ifdef EE_CN19
#else
#define EE_CN19_SET_TRIS()
#endif /* EE_CN19 */

#ifdef EE_CN20
#else
#define EE_CN20_SET_TRIS()
#endif /* EE_CN20 */

#ifdef EE_CN21
#else
#define EE_CN21_SET_TRIS()
#endif /* EE_CN21 */

/*TODO:
	- What happens on multiple calls to this function?
	  The main proble is what is going to be the resultiong prio and subrio?
	  With the current solution the last call will overwrite.
	  Do we want to have a policy that take the maximum valus?
*/
__INLINE__ void EE_cn_init(EE_UINT8 irq_prio, EE_UINT8 irq_subprio) 
{
	asm("di");
	/* Set the Tri-State (Digital Input) */
	EE_CN0_SET_TRIS();
	EE_CN1_SET_TRIS();
	EE_CN2_SET_TRIS();
	EE_CN3_SET_TRIS();
	EE_CN4_SET_TRIS();
	EE_CN5_SET_TRIS();
	EE_CN6_SET_TRIS();
	EE_CN7_SET_TRIS();
	EE_CN8_SET_TRIS();
	EE_CN9_SET_TRIS();
	EE_CN10_SET_TRIS();
	EE_CN11_SET_TRIS();
	EE_CN12_SET_TRIS();
	EE_CN13_SET_TRIS();
	EE_CN14_SET_TRIS();
	EE_CN15_SET_TRIS();
	EE_CN16_SET_TRIS();
	EE_CN17_SET_TRIS();
	EE_CN18_SET_TRIS();
	EE_CN19_SET_TRIS();
	EE_CN20_SET_TRIS();
	EE_CN21_SET_TRIS();
	/* Enable CN Module ON */
	CNCONSET = _CNCON_ON_MASK;
	/* Configure the CN interrupt priority and subpriority */
	IPC6CLR = _IPC6_CNIP_MASK;
	IPC6SET = ((EE_UREG)(irq_prio & ((1 << _IPC6_CNIP_LENGTH) - 1)) << 
		  					   _IPC6_CNIP_POSITION);
	IPC6CLR = _IPC6_CNIS_MASK;
	IPC6SET = ((EE_UREG)(irq_subprio & ((1 << _IPC6_CNIS_LENGTH) - 1)) << 
		  					   _IPC6_CNIS_POSITION);
	/* Clear CN interrupt flag */
	IFS1CLR = _IFS1_CNIF_MASK;
	/* Enable CN interrupt */
	IEC1SET =_IEC1_CNIE_MASK;
	asm("ei");
}

__INLINE__ void EE_cn_close(void)
{
	/* Disable CN interrupt */
	IEC1CLR =_IEC1_CNIE_MASK;
	/* Clear CN interrupt flag */
	IFS1CLR = _IFS1_CNIF_MASK;
}

#endif /* __USE_CN__ */

#endif /* __INCLUDE_EE_CN_H__ */
