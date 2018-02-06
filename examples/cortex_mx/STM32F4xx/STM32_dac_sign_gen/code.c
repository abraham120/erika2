/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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

#include "ee.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


#define DAC_DHR12R2_ADDRESS    0x40007414
#define DAC_DHR8R1_ADDRESS     0x40007410

DAC_InitTypeDef  DAC_InitStructure;

const uint16_t Sine12bit[32] = {
                      2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909,
                      599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647};
const uint8_t Escalator8bit[6] = {0x0, 0x33, 0x66, 0x99, 0xCC, 0xFF};

__IO uint8_t SelectedWavesForm = 0;
__IO uint8_t KeyPressed = SET;

/**
  * @brief  TIM6 Configuration
  * @note   TIM6 configuration is based on CPU @168MHz and APB1 @42MHz
  * @note   TIM6 Update event occurs each 37.5MHz/256 = 16.406 KHz
  * @param  None
  * @retval None
  */
void TIM6_Config(void)
{
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure;
	/* TIM6 Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	/* Time base configuration */
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = 0xFF;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	/* TIM6 TRGO selection */
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

	/* TIM6 enable counter */
	TIM_Cmd(TIM6, ENABLE);
}

/**
  * @brief  DAC  Channel2 SineWave Configuration
  * @param  None
  * @retval None
  */
void DAC_Ch2_SineWaveConfig(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* DAC channel2 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

	/* DMA1_Stream5 channel7 configuration **************************************/
	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)DAC_DHR12R2_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&Sine12bit;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = 32;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);

	/* Enable DMA1_Stream5 */
	DMA_Cmd(DMA1_Stream5, ENABLE);

	/* Enable DAC Channel2 */
	DAC_Cmd(DAC_Channel_2, ENABLE);

	/* Enable DMA for DAC Channel2 */
	DAC_DMACmd(DAC_Channel_2, ENABLE);
}

/**
  * @brief  DAC Channel1 Escalator Configuration
  * @param  None
  * @retval None
  */
void DAC_Ch1_EscalatorConfig(void)
{
	DMA_InitTypeDef DMA_InitStructure;

	/* DAC channel1 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	/* DMA1_Stream6 channel7 configuration **************************************/
	DMA_DeInit(DMA1_Stream6);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR8R1_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&Escalator8bit;
	DMA_InitStructure.DMA_BufferSize = 6;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream6, &DMA_InitStructure);

	/* Enable DMA1_Stream6 */
	DMA_Cmd(DMA1_Stream6, ENABLE);

	/* Enable DAC Channel1 */
	DAC_Cmd(DAC_Channel_1, ENABLE);

	/* Enable DMA for DAC Channel1 */
	DAC_DMACmd(DAC_Channel_1, ENABLE);
}

/**
  * @brief  DAC Channel2 Triangle Configuration
  * @param  None
  * @retval None
  */
void DAC_Ch2_TriangleConfig(void)
{
	/* DAC channel2 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_1023;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_2, &DAC_InitStructure);

	/* Enable DAC Channel2 */
	DAC_Cmd(DAC_Channel_2, ENABLE);

	/* Set DAC channel2 DHR12RD register */
	DAC_SetChannel2Data(DAC_Align_12b_R, 0x100);
}

/**
  * @brief  DAC  Channel1 Noise Configuration
  * @param  None
  * @retval None
  */
void DAC_Ch1_NoiseConfig(void)
{
	/* DAC channel1 Configuration */
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Noise;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits10_0;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	/* Enable DAC Channel1 */
	DAC_Cmd(DAC_Channel_1, ENABLE);

	/* Set DAC Channel1 DHR12L register */
	DAC_SetChannel1Data(DAC_Align_12b_L, 0x7FF0);
}

/*
 * SysTick ISR1
 */
ISR1(exti0_irq_handler)
{
	/* Change the wave */
	KeyPressed = 0;
	/* Change the selected waves forms */
	SelectedWavesForm = !SelectedWavesForm;
	/* Clear the Right Button EXTI line pending bit */
	EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
}

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* count the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

TASK(TaskDAC)
{
	/* If the User Button is pressed */
	if (KeyPressed == RESET) {
		DAC_DeInit();

		/* select waves forms according to the Key Button status */
		if (SelectedWavesForm == 1) {
        /* The sine wave and the escalator wave has been selected */

        /* Escalator Wave generator ------------------------------------------*/
        DAC_Ch1_EscalatorConfig();

        /* Sine Wave generator -----------------------------------------------*/
        DAC_Ch2_SineWaveConfig();

      } else {
        /* The triangle wave and the noise wave has been selected */

        /* Noise Wave generator ----------------------------------------------*/
        DAC_Ch1_NoiseConfig();

        /* Triangle Wave generator -------------------------------------------*/
        DAC_Ch2_TriangleConfig();
      }

      KeyPressed = SET;
    }


}

TASK(TaskLedBlink)
{
	STM_EVAL_LEDToggle(LED4);
}

int main(void)
{

	/* Preconfiguration before using DAC----------------------------------------*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	SystemInit();

	/*Initialize Erika related stuffs*/
	EE_system_init();

	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();

	STM_EVAL_LEDInit(LED4);


	/* DMA1 clock and GPIOA clock enable (to be used with DAC) */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);

	/* DAC Periph clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	/* DAC channel 1 & 2 (DAC_OUT1 = PA.4)(DAC_OUT2 = PA.5) configuration */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* TIM6 Configuration ------------------------------------------------------*/
	TIM6_Config();

	/* Configures User Button */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

	/* Program cyclic alarms which will fire after an initial offset,
	 * and after that periodically
	 * */
	SetRelAlarm(AlarmDAC, 10, 10);
	SetRelAlarm(AlarmLedBlink, 10, 500);

	/* Forever loop: background activities (if any) should go here */
	for (;;);

}

