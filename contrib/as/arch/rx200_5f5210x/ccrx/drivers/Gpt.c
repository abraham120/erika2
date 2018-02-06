/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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
 * GPT367:	Gpt.c Module source file.
 *
 * AUTOSAR-"like" GPT Driver Source File.
 *
 * Author:  2012,  Gianluca Franchino
 */

/*
 * GPT293:	Gpt.c shall include Gpt.h.
 *
 * Comment: Gpt.c has implicit access to the Gpt_Cfg.h through the Gpt.h file.
 */
#include "Gpt.h"

/* 
 * GPT256:	The GPT module shall perform Inter Module Checks to avoid
 * 		integration of incompatible files. The imported included files
 * 		shall be checked by preprocessing directives. (BSW004)
 *
 * The following version numbers shall be verified:
 * - <MODULENAME>_AR_RELEASE_MAJOR_VERSION
 * - <MODULENAME>_AR_RELEASE_MINOR_VERSION
 * Where <MODULENAME> is the module abbreviation of the other (external) modules
 * which provide header files included by the GPT module.
 *
 * If the values are not identical to the expected values, an error shall be
 * reported.
 */
#define	GPT_AR_RELEASE_MAJOR_VERSION	4
#define	GPT_AR_RELEASE_MINOR_VERSION	0

#if !defined( GPT_AR_MAJOR_VERSION ) || \
    ( GPT_AR_MAJOR_VERSION != GPT_AR_RELEASE_MAJOR_VERSION )
#error	Gpt: version mismatch.
#endif

#include "ee.h"

/* Development error macros. */
#if ( GPT_DEV_ERROR_DETECT == STD_ON )

#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    Det_ReportError(GPT_MODULE_ID,0,_api,_err); \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#else	/* GPT_DEV_ERROR_DETECT */

#define VALIDATE(_exp,_api,_err) \
  if( !(_exp) ) { \
    return; \
  }

#define VALIDATE_IRQ(_exp,_api,_err,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return; \
  }

#define VALIDATE_W_RV(_exp,_api,_err,_rv) \
  if( !(_exp) ) { \
    return (_rv); \
  }

#define VALIDATE_IRQ_W_RV(_exp,_api,_err,_rv,_flags) \
  if( !(_exp) ) { \
    EE_hal_resumeIRQ(_flags); \
    return (_rv); \
  }

#endif	/* !GPT_DEV_ERROR_DETECT */

#include "Gpt_Internal.h"

/*
 * Type that holds all global data for Gpt Driver
 */
typedef struct
{

	boolean			Init;				/* GPT Driver Initialized?    */

	const Gpt_ConfigType *	ConfigPtr;	/* Actual Configuration	      */

	uint16			Status;				/* Channel Status	      */

	uint32			Notifications;		/* Channel Notifications      */

} Gpt_GlobalType;


/*
 * Global config
 */
Gpt_GlobalType Gpt_Global =
{
		FALSE,							/* Init		*/
		NULL_PTR,						/* ConfigPtr	*/
		0x00000000						/* Status	*/
};


/*
 * TCNT value of module TMR module after calling stop routine.  
 */
uint8 Gpt_tmr_tcnt_val[] = {0, 0, 0, 0};


/*
 * Channel expired flags. 
 */
uint32 exp_flag = 0;

/*
 * Channel stop flags. 
 */
uint32 stop_flag = 0;

/*
 * Channel start flags for TMR module. 
 */
uint8 start_flag = 0;

#if ( GPT_DEINIT_API == STD_ON )


/*
 * Gpt Reset Channel
 *
 * param	ch	Numeric ID of a GPT Channel.
 */
static void Gpt_ResetChannel(Gpt_ChannelType ch)
{
	/* if ch is between TMR0 and TMR23. */
	if (ch < GPT_INTERNAL_CHANNEL_CMT0) {
		GPT_CLEAR_TMR_TCNT(ch);
		GPT_SET_TMR_TCR(ch, 0x0);
		GPT_SET_TMR_TCCR(ch, 0x0);
		Gpt_tmr_dis_icu_int(ch);
	} else if (ch < GPT_INTERNAL_CHANNEL_MTU0) {
		GPT_CLEAR_CMT_TCNT(ch);
		GPT_DIS_ICU_IER(HW_ICU_IER_CMT_CMI, HW_ICU_CMT0_IER_CMI_MASK | 
				HW_ICU_CMT1_IER_CMI_MASK | HW_ICU_CMT2_IER_CMI_MASK | 
				HW_ICU_CMT3_IER_CMI_MASK);
	} else if (ch < GPT_INTERNAL_CHANNEL_MTU5U){
		GPT_CLEAR_MTU2A_TCNT(ch);
		Gpt_mtu2a_set_tgra(ch, 0xFFFF);
		Gpt_mtu2a_set_tgrb(ch, 0xFFFF);
		Gpt_mtu2a_set_tgrc(ch, 0xFFFF);
		Gpt_mtu2a_set_tgrd(ch, 0xFFFF);
		Gpt_mtu0_4_int_dis(ch, Gpt_get_mtu2a_tcr(ch));
	} else {
		Gpt_mtu5_set_cmp(ch, 0xFFFF);
		Gpt_mtu5_int_dis(ch);
	}
		
	switch (ch) {
	case GPT_INTERNAL_CHANNEL_TMR0:
	case GPT_INTERNAL_CHANNEL_TMR1:
	case GPT_INTERNAL_CHANNEL_TMR2:
	case GPT_INTERNAL_CHANNEL_TMR3:
		GPT_SET_TMR_TCORA(ch, 0xFF);
		GPT_SET_TMR_TCORB(ch, 0xFF);
		break;
	case GPT_INTERNAL_CHANNEL_TMR01:
		GPT_SET_TMR_TCORA16(GPT_INTERNAL_CHANNEL_TMR0, 0xFFFF);
		GPT_SET_TMR_TCORB16(GPT_INTERNAL_CHANNEL_TMR0, 0xFFFF);
		break;
	case GPT_INTERNAL_CHANNEL_TMR23:
		GPT_SET_TMR_TCORA16(GPT_INTERNAL_CHANNEL_TMR2, 0xFFFF);
		GPT_SET_TMR_TCORB16(GPT_INTERNAL_CHANNEL_TMR2, 0xFFFF);
		break;	
	case GPT_INTERNAL_CHANNEL_CMT0:
	case GPT_INTERNAL_CHANNEL_CMT1:	
		GPT_SET_CMT_CMSTR(GPT_INTERNAL_CHANNEL_CMT0, 0x0);
		GPT_SET_CMT_CMCR(ch, 0x0000);
		GPT_SET_CMT_CMCOR(ch, 0xFFFF);
		break;
	case GPT_INTERNAL_CHANNEL_CMT2:		
	case GPT_INTERNAL_CHANNEL_CMT3:
		GPT_SET_CMT_CMSTR(GPT_INTERNAL_CHANNEL_CMT2, 0x0);
		GPT_SET_CMT_CMCR(ch, GPT_CMTx_CMCR_RESET_VAL);
		GPT_SET_CMT_CMCOR(ch, 0xFFFF);
		break;	
	case GPT_INTERNAL_CHANNEL_MTU0:
	case GPT_INTERNAL_CHANNEL_MTU1:
	case GPT_INTERNAL_CHANNEL_MTU2:
	case GPT_INTERNAL_CHANNEL_MTU3:
	case GPT_INTERNAL_CHANNEL_MTU4:
		Gpt_set_mtu2a_tcr(ch, 0x0);
		Gpt_set_mtu2a_tmdr(ch, 0x0);
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		Gpt_set_mtu2a_tcr(GPT_INTERNAL_CHANNEL_MTU1, 0x0);
		Gpt_set_mtu2a_tmdr(GPT_INTERNAL_CHANNEL_MTU1, 0x0);
		Gpt_set_mtu2a_tcr(GPT_INTERNAL_CHANNEL_MTU2, 0x0);
		Gpt_set_mtu2a_tmdr(GPT_INTERNAL_CHANNEL_MTU2, 0x0);
		break;
	case GPT_INTERNAL_CHANNEL_MTU5U:
	case GPT_INTERNAL_CHANNEL_MTU5V:
	case GPT_INTERNAL_CHANNEL_MTU5W:
		Gpt_set_mtu2a_tcr(ch, 0x0);
		GPT_SET_MTU5_CMP_CLR(0x0);
		break;		
	}
}
#endif

/** @brief	Configure and initialize MTU2A module.
 *	@param ConfigPtr Address of channel configuration structure.
 */
static void Gpt_mtu2a_init(const Gpt_ChannelConfigType *ConfigPtr) 
{

	switch (ConfigPtr->GptChannelId) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU0_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Set timer in normal mode.*/
		GPT_SET_REG8(HW_MTU0_TMDR_ADDR, 
				GPT_GET_MTU2A_REG8(HW_MTU0_TMDR_ADDR) & 
				GPT_MTU2A_TMDR_N_MODE_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU1:
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU1_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Set timer in normal mode.*/
		GPT_SET_REG8(HW_MTU1_TMDR_ADDR, GPT_GET_MTU2A_REG8(HW_MTU1_TMDR_ADDR) & 
				GPT_MTU2A_TMDR_N_MODE_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU2:
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU2_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Set timer in normal mode.*/
		GPT_SET_REG8(HW_MTU2_TMDR_ADDR, GPT_GET_MTU2A_REG8(HW_MTU2_TMDR_ADDR) & 
				GPT_MTU2A_TMDR_N_MODE_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU1_TCR_ADDR, ConfigPtr->GptChannelHWConfig | 
				GPT_MTUA2_CASCADE_MODE);
		GPT_SET_REG8(HW_MTU2_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Set timer in normal mode.*/
		GPT_SET_REG8(HW_MTU1_TMDR_ADDR, GPT_GET_MTU2A_REG8(HW_MTU1_TMDR_ADDR) & 
				GPT_MTU2A_TMDR_N_MODE_MASK);
		GPT_SET_REG8(HW_MTU2_TMDR_ADDR, GPT_GET_MTU2A_REG8(HW_MTU2_TMDR_ADDR) & 
				GPT_MTU2A_TMDR_N_MODE_MASK);
		/* Enable Synchronous operation for MTU1 and MTU2. */
		GPT_SET_REG8(HW_MTU2A_TSYR_ADDR, GPT_GET_MTU2A_REG8(HW_MTU2A_TSYR_ADDR) | 
				GPT_TSYR_MTU12_ENABLE);
		break;
	
	case GPT_INTERNAL_CHANNEL_MTU3:
		/*Enable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_EN_MASK);
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU3_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Set timer in normal mode.*/
		GPT_SET_REG8(HW_MTU3_TMDR_ADDR, GPT_GET_MTU2A_REG8(HW_MTU3_TMDR_ADDR) & 
				GPT_MTU2A_TMDR_N_MODE_MASK);
		/*Disable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_DIS_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		/*Enable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_EN_MASK);
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU4_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Set timer in normal mode.*/
		GPT_SET_REG8(HW_MTU4_TMDR_ADDR, GPT_GET_MTU2A_REG8(HW_MTU4_TMDR_ADDR) & 
				GPT_MTU2A_TMDR_N_MODE_MASK);
		/*Disable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_DIS_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU5U:
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU5U_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Enable counter clear on match with TGRU. */ 
		if (ConfigPtr->GptChannelHWConfig & GPT_MTU5_CLR_BIT_MASK) {
			GPT_SET_REG8(HW_MTU5_TCNTCMPCLR_ADDR, 
					(GPT_GET_MTU2A_REG8(HW_MTU5_TCNTCMPCLR_ADDR) | 
							GPT_MTU5U_TCNTCMPCLR_EN_MASK));
		}
		break;
	case GPT_INTERNAL_CHANNEL_MTU5V:
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU5V_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Enable counter clear on match with TGRV. */
		if (ConfigPtr->GptChannelHWConfig & GPT_MTU5_CLR_BIT_MASK) {
			GPT_SET_REG8(HW_MTU5_TCNTCMPCLR_ADDR, 
					(GPT_GET_MTU2A_REG8(HW_MTU5_TCNTCMPCLR_ADDR) | 
							GPT_MTU5V_TCNTCMPCLR_EN_MASK));
		}
		break;
	case GPT_INTERNAL_CHANNEL_MTU5W:
		/*Set timer prescaler/clock and counter clear match.*/
		GPT_SET_REG8(HW_MTU5W_TCR_ADDR, ConfigPtr->GptChannelHWConfig);
		/*Enable counter clear on match with TGRW. */
		if ((ConfigPtr->GptChannelHWConfig & GPT_MTU5_CLR_BIT_MASK) == 
				GPT_MTU5_CLR_BIT_MASK) {
			GPT_SET_REG8(HW_MTU5_TCNTCMPCLR_ADDR, 
					(GPT_GET_MTU2A_REG8(HW_MTU5_TCNTCMPCLR_ADDR) | 
							GPT_MTU5W_TCNTCMPCLR_EN_MASK));
		}
		break;
	}
	
}

/** @brief	Enable MTU2A interrupts to handle one-shot mode.
 *	@param ConfigPtr Address of channel configuration structure.
 */
static void Gpt_mtu2a_en_oneshot(const Gpt_ChannelConfigType *ConfigPtr) 
{

	switch (ConfigPtr->GptChannelId) {
	case GPT_INTERNAL_CHANNEL_MTU0:
		if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_A_MASK) == 
				GPT_MTU2A_CMP_A_MASK) {
			GPT_SET_MTU2A_BIT_REG8(HW_MTU0_TIER_ADDR, GPT_MTU2A_TGIEA_POS);
			GPT_EN_ICU_IER(HW_ICU_IER_MTU0_TGIA, HW_ICU_MTU0_IER_TGIA_MASK);

			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_B_MASK) == 
					GPT_MTU2A_CMP_B_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU0_TIER_ADDR, GPT_MTU2A_TGIEB_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU0_TGIB, HW_ICU_MTU0_IER_TGIB_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_C_MASK) == 
					GPT_MTU2A_CMP_C_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU0_TIER_ADDR, GPT_MTU2A_TGIEC_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU0_TGIB, HW_ICU_MTU0_IER_TGIC_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_D_MASK) == 
					GPT_MTU2A_CMP_D_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU0_TIER_ADDR, GPT_MTU2A_TGIED_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU0_TGIB, HW_ICU_MTU0_IER_TGID_MASK);
			}
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU0_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU1:
		if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_A_MASK) == 
				GPT_MTU2A_CMP_A_MASK) {
			GPT_SET_MTU2A_BIT_REG8(HW_MTU1_TIER_ADDR, GPT_MTU2A_TGIEA_POS);
			GPT_EN_ICU_IER(HW_ICU_IER_MTU1_TGIA, HW_ICU_MTU1_IER_TGIA_MASK);
			
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_B_MASK) == 
					GPT_MTU2A_CMP_B_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU1_TIER_ADDR, GPT_MTU2A_TGIEB_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU1_TGIB, HW_ICU_MTU1_IER_TGIB_MASK);
			}
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU1_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU2:
		if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_A_MASK) == 
				GPT_MTU2A_CMP_A_MASK) {
			GPT_SET_MTU2A_BIT_REG8(HW_MTU2_TIER_ADDR, GPT_MTU2A_TGIEA_POS);
			GPT_EN_ICU_IER(HW_ICU_IER_MTU2_TGIA, HW_ICU_MTU2_IER_TGIA_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_B_MASK) == 
					GPT_MTU2A_CMP_B_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU2_TIER_ADDR, GPT_MTU2A_TGIEB_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU2_TGIB, HW_ICU_MTU2_IER_TGIB_MASK);
			} 
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU2_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU12:
		/*TODO*/
		break;
	case GPT_INTERNAL_CHANNEL_MTU3:
		/*Enable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_EN_MASK);
		if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_A_MASK) & 
				GPT_MTU2A_CMP_A_MASK) {
			GPT_SET_MTU2A_BIT_REG8(HW_MTU3_TIER_ADDR, GPT_MTU2A_TGIEA_POS);
			GPT_EN_ICU_IER(HW_ICU_IER_MTU3_TGIA, HW_ICU_MTU3_IER_TGIA_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_B_MASK) == 
					GPT_MTU2A_CMP_B_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU3_TIER_ADDR, GPT_MTU2A_TGIEB_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU3_TGIB, HW_ICU_MTU3_IER_TGIB_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_C_MASK) == 
					GPT_MTU2A_CMP_C_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU3_TIER_ADDR, GPT_MTU2A_TGIEC_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU3_TGIC, HW_ICU_MTU3_IER_TGIC_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_D_MASK) ==
					 GPT_MTU2A_CMP_D_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU3_TIER_ADDR, GPT_MTU2A_TGIED_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU3_TGID, HW_ICU_MTU3_IER_TGID_MASK);
			}
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU3_TGI_REG, HW_IPR_PRI_LEVEL_1);
		/*Disable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_DIS_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU4:
		/*Enable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_EN_MASK);
		if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_A_MASK) == 
				GPT_MTU2A_CMP_A_MASK) {
			GPT_SET_MTU2A_BIT_REG8(HW_MTU4_TIER_ADDR, GPT_MTU2A_TGIEA_POS);
			GPT_EN_ICU_IER(HW_ICU_IER_MTU4_TGIA, HW_ICU_MTU4_IER_TGIA_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_B_MASK) == 
					GPT_MTU2A_CMP_B_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU4_TIER_ADDR, GPT_MTU2A_TGIEB_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU4_TGIB, HW_ICU_MTU4_IER_TGIB_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_C_MASK) == 
					GPT_MTU2A_CMP_C_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU4_TIER_ADDR, GPT_MTU2A_TGIEC_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU4_TGIC, HW_ICU_MTU4_IER_TGIC_MASK);
			} else if ((ConfigPtr->GptChannelHWConfig & GPT_MTU2A_CMP_D_MASK) == 
					GPT_MTU2A_CMP_D_MASK) {
				GPT_SET_MTU2A_BIT_REG8(HW_MTU4_TIER_ADDR, GPT_MTU2A_TGIED_POS);
				GPT_EN_ICU_IER(HW_ICU_IER_MTU4_TGID, HW_ICU_MTU4_IER_TGID_MASK);
			}
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU4_TGI_REG, HW_IPR_PRI_LEVEL_1);
		/*Disable writing to MTU3 and MTU4 protected registers. */
		GPT_SET_REG8(HW_MTU34_TRWER_ADDR, GPT_MTU34_TRWER_DIS_MASK);
		break;
	case GPT_INTERNAL_CHANNEL_MTU5U:
		GPT_SET_MTU2A_BIT_REG8(HW_MTU5_TIER_ADDR, GPT_MTU2A_TGIE5U_POS);
		GPT_EN_ICU_IER(HW_ICU_IER_MTU5_TGI, HW_ICU_MTU5_IER_TGIU_MASK);
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU5_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU5V:
		GPT_SET_MTU2A_BIT_REG8(HW_MTU5_TIER_ADDR, GPT_MTU2A_TGIE5V_POS);
		GPT_EN_ICU_IER(HW_ICU_IER_MTU5_TGI, HW_ICU_MTU5_IER_TGIV_MASK);
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU5_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	case GPT_INTERNAL_CHANNEL_MTU5W:
		GPT_SET_MTU2A_BIT_REG8(HW_MTU5_TIER_ADDR, GPT_MTU2A_TGIE5W_POS);
		GPT_EN_ICU_IER(HW_ICU_IER_MTU5_TGI, HW_ICU_MTU5_IER_TGIW_MASK);
		GPT_SET_ICU_IPR(HW_ICU_IPR_MTU5_TGI_REG, HW_IPR_PRI_LEVEL_1);
		break;
	}
	
}


/*
 * Gpt Channel Initialization.
 */
static void Gpt_InitGptChannel(const Gpt_ChannelConfigType *ConfigPtr)
{

	/* Gpt Module Disabled? */
	if (!(Gpt_Global.Status & Gpt_ch_2_mod_stat(ConfigPtr->GptChannelId))){
		/* Enables Gpt Module in Run-Mode */
		Gpt_EnableChannel(ConfigPtr->GptChannelId);
	}
	/* Set Gpt Unit Status.*/
	Gpt_Global.Status |= Gpt_ch_2_mod_stat(ConfigPtr->GptChannelId);

	/* Stop Timer. */
	Gpt_tmr_stop(ConfigPtr->GptChannelId);
	
	/* Set clock source, prescaler and initialize the timer. */
	if (ConfigPtr->GptChannelId < GPT_INTERNAL_CHANNEL_CMT0) {
		Gpt_tmr_init(ConfigPtr);
	} else if (ConfigPtr->GptChannelId < GPT_INTERNAL_CHANNEL_MTU0) {
		Gpt_cmt_init(ConfigPtr);
	} else {
		Gpt_mtu2a_init(ConfigPtr);
	}
	
	/* One-shot mode is not supported by the hardware, hence, if one-shot mode 
	 * is selected then we use the compare math interrupt to stop the timer. 
	 */
	
	if (ConfigPtr->GptChannelMode == GPT_CH_MODE_ONESHOT) {
		if (ConfigPtr->GptChannelId < GPT_INTERNAL_CHANNEL_CMT0) {
			Gpt_tmr_en_oneshot(ConfigPtr);
		} else if (ConfigPtr->GptChannelId < GPT_INTERNAL_CHANNEL_MTU0) {
			Gpt_cmt_en_oneshot(ConfigPtr->GptChannelId);
		} else {
			Gpt_mtu2a_en_oneshot(ConfigPtr);
		}
	}

}

/*
 * Gpt Channel De-Initialization.
 */
#if ( GPT_DEINIT_API == STD_ON )
static void Gpt_DeInitGptChannel(const Gpt_ChannelConfigType *ConfigPtr)
{
	/* Gpt Module Disabled? */
	if (!(Gpt_Global.Status & Gpt_ch_2_mod_stat(ConfigPtr->GptChannelId))) {
		/* Enables Gpt Module in Run-Mode */
		Gpt_EnableChannel(ConfigPtr->GptChannelId);
	}

	/* Disable Gpt Module in Run-Mode */
	Gpt_ResetChannel(ConfigPtr->GptChannelId);
	
	GPT_CLEAR_FLAG(stop_flag, ConfigPtr->GptChannelId);
	GPT_CLEAR_FLAG(exp_flag, ConfigPtr->GptChannelId);
	
	/* Turn-off Gpt Unit */
	Gpt_Global.Status &= ~Gpt_ch_2_mod_stat(ConfigPtr->GptChannelId);

	/* Gpt Module Disabled? */
	if ( !(Gpt_Global.Status & Gpt_ch_2_mod_stat(ConfigPtr->GptChannelId)) ){
		/* Disable Gpt Module in Run-Mode */
		Gpt_DisableChannel(ConfigPtr->GptChannelId);
	}
}
#endif

/*
 * Gpt_Init implementation.
 */
void Gpt_Init( const Gpt_ConfigType *ConfigPtr)
{
	
	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE( ( ConfigPtr != NULL), GPT_INIT_SERVICE_ID, GPT_E_PARAM_CONFIG );

	//VALIDATE( ( Hw_CheckCore() == E_OK), GPT_INIT_SERVICE_ID, GPT_E_UNINIT );

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(!Gpt_Global.Init, GPT_INIT_SERVICE_ID, 
			GPT_E_ALREADY_INITIALIZED, flags);

	for (channel = 0; channel < ConfigPtr->GptNumberOfGptChannels; channel++) {
		/* Initializes Gpt Channel. */
		Gpt_InitGptChannel(&(ConfigPtr->GptChannels[channel]));
	}

	Gpt_Global.ConfigPtr = ConfigPtr;
	Gpt_Global.Init = TRUE;

	EE_hal_resumeIRQ(flags);

}

#if ( GPT_DEINIT_API == STD_ON )
/*
 * Gpt_DeInit implementation.
 */
void Gpt_DeInit(void)
{

	register EE_FREG	flags;
	register uint32	channel;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_DEINIT_SERVICE_ID, GPT_E_UNINIT, flags);

	for (channel = 0; channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels; 
		  channel++) {
		/* De-Initializes Gpt Channel. */
		Gpt_DeInitGptChannel(&(Gpt_Global.ConfigPtr->GptChannels[channel]));
	}

	Gpt_Global.Init = FALSE;
	Gpt_Global.ConfigPtr = NULL_PTR;

	GPT_CLEAR_FLAG(exp_flag, 
			Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId);
	GPT_CLEAR_FLAG(stop_flag, 
			Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId);
	
	EE_hal_resumeIRQ(flags);
}
#endif

#if ( (GPT_TIME_ELAPSED_API == STD_ON) || (GPT_TIME_REMAINING_API == STD_ON))
/*
 * Gpt_GetHWTarget implementation.
 */
static Gpt_ValueType Gpt_GetHWTarget(Gpt_ChannelType Channel)
{
	if (Channel < GPT_INTERNAL_CHANNEL_CMT0) {
		if ((GPT_GET_TMR_TCR(Channel) & GPT_TMR_CMP_A_MASK) == 
				GPT_TMR_CMP_A_MASK)
			return (GPT_GET_TMR_TCORA(Channel));
		else
			return (GPT_GET_TMR_TCORB(Channel));
	} else if (Channel < GPT_INTERNAL_CHANNEL_MTU0){
		return (GPT_GET_CMT_CMCOR(Channel));
	} else {
		return (Gpt_get_mtu2a_tgr(Channel));
	}
}

/*
 * Gpt_GetHWHWCnt implementation.
 */
static Gpt_ValueType Gpt_GetHWCnt(Gpt_ChannelType Channel)
{	
	if (Channel < GPT_INTERNAL_CHANNEL_CMT0) {
		/*If the channel is stopped, than use the value stored in 
		 * Gpt_tmr_tcnt_val[].*/
		if (GPT_GET_FLAG(stop_flag, Channel)) {
			if (Channel < GPT_INTERNAL_CHANNEL_TMR01) {
				return Gpt_tmr_tcnt_val[Channel];
			} else if (Channel == GPT_INTERNAL_CHANNEL_TMR01) {
				return (((uint16)(Gpt_tmr_tcnt_val[0]) << 8) | 
						Gpt_tmr_tcnt_val[1]);
			} else {
				return (((uint16)(Gpt_tmr_tcnt_val[2]) << 8) | 
						Gpt_tmr_tcnt_val[3]);
			}	
		}
		return (Gpt_get_tmr_tcnt(Channel));
	} else if (Channel < GPT_INTERNAL_CHANNEL_MTU0){
		return (GPT_GET_CMT_TCNT(Channel));
	} else {
		return (Gpt_get_mtu2a_tcnt(Channel));
	}
}

#endif	/* 
	 * ( GPT_TIME_ELAPSED_API == STD_ON ) ||
	 * ( GPT_TIME_REMAINING_API == STD_ON )
	 */

#if ( GPT_TIME_ELAPSED_API == STD_ON )


/*
 * Gpt_GetTimeElapsed implementation.
 */
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType	Channel)
{

	register EE_FREG		flags;
	register uint32		channel;
	
	register Gpt_ValueType	rv;

	VALIDATE_W_RV(GPT_CH_IS_VALID(Channel),	GPT_GETTIMEELAPSED_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, GPT_HW_TMR_EMPTY_VALUE);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Gpt_Global.Init, GPT_GETTIMEELAPSED_SERVICE_ID, 
			GPT_E_UNINIT, GPT_HW_TMR_EMPTY_VALUE, flags);

	for (channel = 0; ((channel < 
			Gpt_Global.ConfigPtr->GptNumberOfGptChannels) && 
			(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
					Channel)); channel++);

	VALIDATE_IRQ_W_RV((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels), 
			GPT_GETTIMEELAPSED_SERVICE_ID, GPT_E_PARAM_CHANNEL, 
			GPT_HW_TMR_EMPTY_VALUE, flags);

	VALIDATE_IRQ_W_RV((Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel)), 
			GPT_GETTIMEELAPSED_SERVICE_ID, GPT_E_STATE_TRANSITION, 
			GPT_HW_TMR_EMPTY_VALUE, flags);


	/* Note, we assume that the timer counts up and the starting time is 0x0.*/
	rv = Gpt_GetHWCnt(Channel);
	
	EE_hal_resumeIRQ(flags);
	
	return rv;
}
#endif

#if (GPT_TIME_REMAINING_API == STD_ON)
/*
 * Gpt_GetTimeRemainig implementation.
 */
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType	Channel)
{

	register EE_FREG		flags;
	register uint32		channel;
	
	register Gpt_ValueType	rv;
	

	VALIDATE_W_RV(GPT_CH_IS_VALID(Channel), GPT_GETTIMEREMAINING_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, GPT_HW_TMR_EMPTY_VALUE);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Gpt_Global.Init, GPT_GETTIMEREMAINING_SERVICE_ID, 
			GPT_E_UNINIT, GPT_HW_TMR_EMPTY_VALUE, flags);

	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel)); channel++);

	VALIDATE_IRQ_W_RV((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels), 
			GPT_GETTIMEREMAINING_SERVICE_ID, GPT_E_PARAM_CHANNEL, 
			GPT_HW_TMR_EMPTY_VALUE, flags);


	VALIDATE_IRQ_W_RV((Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel)), 
			GPT_GETTIMEREMAINING_SERVICE_ID, GPT_E_STATE_TRANSITION, 
			GPT_HW_TMR_EMPTY_VALUE, flags);

	
	/* Note, we assume that the timer counts up and is cleared when reaches 
	 * the target time, thus, we assume that:
	 * 	Gpt_GetHWTarget(Channel) > Gpt_GetHWCnt(Channel).
	 */
	rv = Gpt_GetHWTarget(Channel) - Gpt_GetHWCnt(Channel);
	
	EE_hal_resumeIRQ(flags);
	
	return rv;
}
#endif

/*
 * Gpt_StartTimer implementation.
 */
void Gpt_StartTimer(Gpt_ChannelType	Channel, Gpt_ValueType	Value)
{

	register EE_FREG	flags;
	register uint32	channel;
	register uint8	tcr_reg;

	VALIDATE(GPT_CH_IS_VALID(Channel), GPT_STARTTIMER_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL);


	VALIDATE((Value > 0), GPT_STARTTIMER_SERVICE_ID, GPT_E_PARAM_VALUE);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_STARTTIMER_SERVICE_ID, GPT_E_UNINIT, 
			flags);

	for (channel = 0; (
			(channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel));
			channel++);

	VALIDATE_IRQ((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ), 
			GPT_STARTTIMER_SERVICE_ID, GPT_E_PARAM_CHANNEL, flags);

	VALIDATE_IRQ((Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel)), 
			GPT_STARTTIMER_SERVICE_ID, GPT_E_STATE_TRANSITION, flags);
	
	if (Channel < GPT_INTERNAL_CHANNEL_CMT0) {
		tcr_reg = GPT_GET_TMR_TCR(Channel);
		/*If compare match A is anabled. */
		if ((tcr_reg & GPT_TMR_CMP_A_MASK) == GPT_TMR_CMP_A_MASK) {
			if (Channel == GPT_INTERNAL_CHANNEL_TMR01 || 
					Channel == GPT_INTERNAL_CHANNEL_TMR23) {
				GPT_SET_TMR_TCORA16(Channel, Value);
			} else {
				GPT_SET_TMR_TCORA(Channel, Value);
			}
			GPT_CLEAR_TMR_TCNT(Channel);
			/*Set interrupt bit. Note, the relative interrupt will fire iff 
			 * one-shot mode or a notification function is enabled.*/
			GPT_SET_TMR_CMIEA(Channel);
		} else {
			if (Channel == GPT_INTERNAL_CHANNEL_TMR01 || 
					Channel == GPT_INTERNAL_CHANNEL_TMR23) {
				GPT_SET_TMR_TCORB16(Channel, Value);
			} else {
				GPT_SET_TMR_TCORB(Channel, Value);
			}
			GPT_CLEAR_TMR_TCNT(Channel);
			/*Set interrupt bit. Note, the relative interrupt will fire iff 
			 * one-shot mode or a notification function is enabled.*/
			GPT_SET_TMR_CMIEB(Channel);

		}
		/*start_flag is only for TMR module.*/
		GPT_SET_FLAG(start_flag, Channel);
		GPT_CLEAR_TMR_TCNT(Channel);
	} else if (Channel < GPT_INTERNAL_CHANNEL_MTU0){
		GPT_CLEAR_CMT_TCNT(Channel);
		GPT_SET_CMT_CMCOR(Channel, Value);
		GPT_START_CMT(Channel);
	} else {
		GPT_CLEAR_MTU2A_TCNT(Channel);
		if (Channel < GPT_INTERNAL_CHANNEL_MTU5U) {
			Gpt_mtu0_4_set_cmp(Channel, Value, Gpt_get_mtu2a_tcr(Channel));
			
		} else {
			Gpt_mtu5_set_cmp(Channel, Value);
		}
		GPT_START_MTU2A(Channel);
	}
	
	GPT_CLEAR_FLAG(exp_flag, Channel);
	GPT_CLEAR_FLAG(stop_flag, Channel);
	
	EE_hal_resumeIRQ(flags);
}

/*
 * Gpt_StopTimer implementation.
 */
void Gpt_StopTimer(Gpt_ChannelType	Channel)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE(GPT_CH_IS_VALID(Channel), GPT_STOPTIMER_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_STOPTIMER_SERVICE_ID, GPT_E_UNINIT, 
			flags);

	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) &&
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel));
			channel++);

	VALIDATE_IRQ((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels),
			GPT_STOPTIMER_SERVICE_ID, GPT_E_PARAM_CHANNEL, flags);

	VALIDATE_IRQ((Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel)), 
			GPT_STARTTIMER_SERVICE_ID, GPT_E_STATE_TRANSITION, flags);

	
	if (Channel < GPT_INTERNAL_CHANNEL_CMT0) {
		/*We reutilize channel variable to get current TCNT. */
		channel = Gpt_get_tmr_tcnt(Channel);
		GPT_CLEAR_TMR_CMIEA(Channel);
		GPT_CLEAR_TMR_CMIEB(Channel);
		//Gpt_tmr_dis_icu_int(Channel);
		
		if (Channel < GPT_INTERNAL_CHANNEL_TMR01) {
			Gpt_tmr_tcnt_val[Channel] = (uint8) (channel);
		} else if (Channel == GPT_INTERNAL_CHANNEL_TMR01) {
			Gpt_tmr_tcnt_val[0] = (uint8) (channel >> 8);
			Gpt_tmr_tcnt_val[1] = (uint8) (channel);
		} else {
			Gpt_tmr_tcnt_val[2] = (uint8) (channel >> 8);
			Gpt_tmr_tcnt_val[3] = (uint8) (channel);
		}
		
		GPT_CLEAR_FLAG(start_flag, Channel);
		
	} else if (Channel < GPT_INTERNAL_CHANNEL_MTU0){
		GPT_STOP_CMT(Channel);
	} else {
		GPT_STOP_MTU2A(Channel);
	}
	
	GPT_SET_FLAG(stop_flag, Channel);
	
	EE_hal_resumeIRQ(flags);

}

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/*
 * Gpt_EnableNotification implementation.
 */
void Gpt_EnableNotification(Gpt_ChannelType	Channel)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE(GPT_CH_IS_VALID(Channel), GPT_ENABLENOTIFICATION_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_ENABLENOTIFICATION_SERVICE_ID, 
			GPT_E_UNINIT, flags);
	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel)); channel++);
	VALIDATE_IRQ(((channel <= Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
			(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != 
					NULL_PTR)), GPT_ENABLENOTIFICATION_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, flags);

	/* Gpt Unit Enabled? */
	if ( (Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel))) {
		/* Enable Time-out Interrupt */
		Gpt_timeout_int_en(Channel);
	}
		


	/* Turn-on Gpt Unit Notifications*/
	Gpt_Global.Notifications |= GPT_CH_2_NOTIF_MASK(Channel);

	EE_hal_resumeIRQ(flags);
}


/*
 * Gpt_DisableNotification implementation.
 */
void Gpt_DisableNotification(Gpt_ChannelType Channel)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE(GPT_CH_IS_VALID(Channel), GPT_DISABLENOTIFICATIONS_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_DISABLENOTIFICATIONS_SERVICE_ID, 
			GPT_E_UNINIT, flags);

	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel)); channel++);

	VALIDATE_IRQ(((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
			(Gpt_Global.ConfigPtr->GptChannels[channel].GptNotificationPtr != 
					NULL_PTR)), GPT_DISABLENOTIFICATION_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, flags);

	/* Gpt Unit Enabled? */
	if ((Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel))){
		/* Disable Time-out Interrupt */
		Gpt_timeout_int_dis(Channel);
	}

	/* Turn-off Gpt Unit Notifications */
	Gpt_Global.Notifications &= ~GPT_CH_2_NOTIF_MASK(Channel);

	EE_hal_resumeIRQ(flags);
}
#endif

#if ((GPT_REPORT_WAKEUP_SOURCE == STD_ON ) && \
		(GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/*
 * Gpt_SetMode implementation.
 */
void Gpt_SetMode(Gpt_ModeType	Mode)
{
	register EE_FREG	flags;

	VALIDATE(((Mode == GPT_MODE_NORMAL) || (Mode == GPT_MODE_SLEEP)), 
			GPT_SETMODE_SERVICE_ID, GPT_E_PARAM_MODE);

	flags = EE_hal_suspendIRQ();

	VALIDATE(Gpt_Global.Init, GPT_SETMODE_SERVICE_ID, GPT_E_UNINIT, flags);

	/* NOT IMPLEMENTED. */
	EE_hal_resumeIRQ(flags);
}

/*
 * Gpt_DisableWakeup implementation.
 */
void Gpt_DisableWakeup(Gpt_ChannelType	Channel)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE(GPT_CH_IS_VALID(Channel), GPT_DISABLEWAKEUP_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_DISABLEWAKEUP_SERVICE_ID, GPT_E_UNINIT, 
			flags);

	for (channel = 0; ((channel < ConfigPtr->GptNumberOfGptChannels) && 
			(ConfigPtr->GptChannels[channel].GptChannelId != Channel)); 
	channel++);

	VALIDATE_IRQ(((channel < ConfigPtr->GptNumberOfGptChannels ) && 
			ConfigPtr->GptChannels[channel].GptEnableWakeup), 
			GPT_DISABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL, flags);

	/* NOT IMPLEMENTED. */

	EE_hal_resumeIRQ(flags);
}

/*
 * Gpt_EnableWakeup implementation.
 */
void Gpt_EnableWakeup(Gpt_ChannelType Channel)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE(GPT_CH_IS_VALID(Channel), GPT_ENABLEWAKEUP_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_UNINIT);

	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel)); channel++);

	VALIDATE_IRQ(((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) && 
			Gpt_Global.ConfigPtr->GptChannels[channel].GptEnableWakeup), 
			GPT_ENABLEWAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL);

	/* NOT IMPLEMENTED. */
	EE_hal_resumeIRQ(flags);
}

/*
 * Gpt_CheckWakeup implementation.
 */
void Gpt_CheckWakeup(EcuM_WakeupSourceType	WakeupSource)
{

	register EE_FREG	flags;

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ(Gpt_Global.Init, GPT_CHECKWAKEUP_SERVICE_ID, GPT_E_UNINIT, 
			flags);

	/* NOT IMPLEMENTED. */

	EE_hal_resumeIRQ(flags);
}
#endif

#if (GPT_CHANNEL_WAKEUP_FUNCTIONALITY_API == STD_ON)
/*
 * Gpt_GoToSleep implementation.
 */
Std_ReturnType Gpt_GoToSleep(Gpt_ChannelType Channel)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE_W_RV(GPT_CH_IS_VALID(Channel), GPT_GOTOSLEEP_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Gpt_Global.Init, GPT_GOTOSLEEP_SERVICE_ID, GPT_E_UNINIT, 
			E_NOT_OK, flags);

	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel)); channel++);

	VALIDATE_IRQ_W_RV(
		  ((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
			Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport),
			GPT_GOTOSLEEP_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, 
			E_NOT_OK, flags);


	if (Channel >  GPT_CHANNEL_TMR23) {
		VALIDATE_IRQ_W_RV((Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel)),
				GPT_GOTOSLEEP_SERVICE_ID, GPT_E_STATE_TRANSITION, E_NOT_OK, flags);
	} else {
		VALIDATE_IRQ_W_RV((Gpt_Global.Status & GPT_HW_TMR_TMR_ON),
				GPT_GOTOSLEEP_SERVICE_ID, GPT_E_STATE_TRANSITION, E_NOT_OK, flags);
	}

	/* Stop Timer. */
	Gpt_DisableChannel(Channel);
	
	/* Turn-off Gpt Unit */
	Gpt_Global.Status &= ~Gpt_ch_2_mod_stat(Channel);
	
	/* Gpt Module Disabled? */
	if (!(Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel))) {
		/* Disable Gpt Module in Run-Mode */
		Gpt_DisableChannel(Channel);
	}

	EE_hal_resumeIRQ(flags);

	return E_OK;

}

/*
 * Gpt_Wakeup implementation.
 */
Std_ReturnType Gpt_Wakeup(Gpt_ChannelType Channel)
{

	register EE_FREG	flags;
	register uint32	channel;

	VALIDATE_W_RV(GPT_CH_IS_VALID(Channel), GPT_WAKEUP_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, E_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Gpt_Global.Init, GPT_WAKEUP_SERVICE_ID, GPT_E_UNINIT, 
			E_NOT_OK, flags);

	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel)); channel++);

	VALIDATE_IRQ_W_RV((
			(channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) || 
			Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport),
			GPT_WAKEUP_SERVICE_ID, GPT_E_PARAM_CHANNEL, E_NOT_OK, flags);


	if (Channel >  GPT_CHANNEL_TMR23) {
		VALIDATE_IRQ_W_RV(!(Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel)), 
				GPT_WAKEUP_SERVICE_ID, GPT_E_STATE_TRANSITION, E_NOT_OK, flags);
	} else {
		VALIDATE_IRQ_W_RV(!(Gpt_Global.Status & GPT_HW_TMR_TMR_ON), 
				GPT_WAKEUP_SERVICE_ID, GPT_E_STATE_TRANSITION, E_NOT_OK, flags);
	}
	

	/* Gpt Module Disabled? */
	if (!( Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel))) {
		/* Enables Gpt Module in Run-Mode */
		Gpt_EnableChannel(Channel);
	}

	/* Gpt Notifications Enabled? */
	if ((Gpt_Global.Notifications & GPT_CH_2_NOTIF_MASK(Channel))) {
		/* Enable Time-out Interrupt */
		Gpt_timeout_int_en(Channel);
	}

	/* Turn-on Gpt Unit */
	Gpt_Global.Status |= Gpt_ch_2_mod_stat(Channel);

	EE_hal_resumeIRQ(flags);

	return E_OK;
}

/*
 * Gpt_GetStatus implementation.
 */
Gpt_StatusType Gpt_GetStatus(Gpt_ChannelType Channel)
{

	register EE_FREG		flags;
	register Gpt_StatusType	rv;
	register uint32		channel;


	VALIDATE_W_RV(GPT_CH_IS_VALID(Channel), GPT_GETSTATUS_SERVICE_ID, 
			GPT_E_PARAM_CHANNEL, GPT_NOT_OK);

	flags = EE_hal_suspendIRQ();

	VALIDATE_IRQ_W_RV(Gpt_Global.Init, GPT_GETSTATUS_SERVICE_ID, GPT_E_UNINIT, 
			GPT_NOT_OK, flags);

	for (channel = 0; 
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels ) && 
					(Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelId != 
							Channel)); channel++);

	VALIDATE_IRQ_W_RV(
			((channel < Gpt_Global.ConfigPtr->GptNumberOfGptChannels) && 
					Gpt_Global.ConfigPtr->GptChannels[channel].GptChannelWakeupSupport), 
					GPT_GETSTATUS_SERVICE_ID, GPT_E_PARAM_CHANNEL, GPT_NOT_OK, 
					flags);

	if (!(Gpt_Global.Status & Gpt_ch_2_mod_stat(Channel)) ) {
		rv = GPT_CH_SLEEP;
	} else if (Gpt_is_running(Channel)) {
		rv = GPT_CH_RUNNING;
	} else if ( GPT_GET_FLAG(exp_flag, Channel) ) {
		rv = GPT_CH_EXPIRED;
	} else if (GPT_GET_FLAG(stop_flag, Channel)) {	
		rv = GPT_CH_STOPPED;
	} else {
		rv = GPT_OPERATIONAL;
	}
		
	EE_hal_resumeIRQ(flags);

	return rv;
	
}
#endif
