#include "mcu/microchip_pic32/inc/ee_cn.h"

union EE_cn_status_bits_t EE_cn_status_bits;

#ifdef EE_CN0
extern void EE_CN0_handler(void);
#endif
#ifdef EE_CN1
extern void EE_CN1_handler(void);
#endif
#ifdef EE_CN2
extern void EE_CN2_handler(void);
#endif
#ifdef EE_CN3
extern void EE_CN3_handler(void);
#endif
#ifdef EE_CN4
extern void EE_CN4_handler(void);
#endif
#ifdef EE_CN5
extern void EE_CN5_handler(void);
#endif
#ifdef EE_CN6
extern void EE_CN6_handler(void);
#endif
#ifdef EE_CN7
extern void EE_CN7_handler(void);
#endif
#ifdef EE_CN8
extern void EE_CN8_handler(void);
#endif
#ifdef EE_CN9
extern void EE_CN9_handler(void);
#endif
#ifdef EE_CN10
extern void EE_CN10_handler(void);
#endif
#ifdef EE_CN11
extern void EE_CN11_handler(void);
#endif
#ifdef EE_CN12
extern void EE_CN12_handler(void);
#endif
#ifdef EE_CN13
extern void EE_CN13_handler(void);
#endif
#ifdef EE_CN14
extern void EE_CN14_handler(void);
#endif
#ifdef EE_CN15
extern void EE_CN15_handler(void);
#endif
#ifdef EE_CN16
extern void EE_CN16_handler(void);
#endif
#ifdef EE_CN17
extern void EE_CN17_handler(void);
#endif
#ifdef EE_CN18
extern void EE_CN18_handler(void);
#endif
#ifdef EE_CN19
extern void EE_CN19_handler(void);
#endif
#ifdef EE_CN20
extern void EE_CN20_handler(void);
#endif
#ifdef EE_CN21
extern void EE_CN21_handler(void);
#endif

#ifdef EE_CN_ISR1
ISR1(_CHANGE_NOTICE_VECTOR) 
#else
ISR2(_CHANGE_NOTICE_VECTOR) 
#endif
{
	/* NOTE: the order of the EE_CNx if-statements is the priority */

	#ifdef EE_CN15
	#ifdef EE_CN15_DEDICATED
	EE_CN15_handler();
	#else
	if (EE_cn_status_bits.CN15 != EE_CN15_PORTBIT) { 
		EE_cn_status_bits.CN15 ^= 1;
		#ifdef EE_CN15_POLARITY
		if (EE_cn_status_bits.CN15 == EE_CN15_POLARITY) 
		#endif
			EE_CN15_handler();
	}
	#endif /* EE_CN15_DEDICATED */

	#elif (defined EE_CN2)
	#ifdef EE_CN2_DEDICATED
	EE_CN2_handler();
	#else
	if (EE_cn_status_bits.CN2 != EE_CN2_PORTBIT) { 
		EE_cn_status_bits.CN2 ^= 1;
		#ifdef EE_CN2_POLARITY
		if (EE_cn_status_bits.CN2 == EE_CN2_POLARITY) 
		#endif
			EE_CN2_handler();
	}
	#endif /* EE_CN2_DEDICATED */
	#endif /* EE_CN2 */


	IFS1CLR = _IFS1_CNIF_MASK;
}
