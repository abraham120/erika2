/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2014  Evidence Srl
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
 * Author: 2014  Gianluca Franchino.
 *
 */

#include "qp_port.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "bsp.h"
#include "dpp.h"

Q_DEFINE_THIS_FILE

/* Local-scope objects -----------------------------------------------------*/
static unsigned  l_rnd;                                      /* random seed */

#define LED_RED     (LED5)
#define LED_GREEN   (LED4)
#define LED_BLUE    (LED6)

#include <stdio.h>

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int _write(int fd, char *ptr, int len)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{

#ifdef __GNUC__
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here. */
	EE_INT32 i;
   
	for (i = 0; i < len; i++) {
   	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
		USART_SendData(EVAL_COM1, (uint8_t) ptr[i]);
	/* Loop until the end of transmission */
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	}
	
	return len;
#else

	USART_SendData(EVAL_COM1, (uint8_t) ch);
	while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
	
	return ch;
	
#endif
}


/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
    static uint8_t  debounce_state = 0U;
    uint32_t btn;

    QF_TICK_X(0U, (void *)0);     /* process all armed time events */

                                              /* debounce the SW1 button... */
    btn = STM_EVAL_PBGetState(BUTTON_USER);   /* read the push btn */
	
    switch (debounce_state) {
        case 0:
			debounce_state = 1U;        /* transition to the next state */
            break;
        case 1:
			debounce_state = 2U;        /* transition to the next state */
            break;
        case 2:
			debounce_state = 3U;        /* transition to the next state */
            break;
        case 3:
            if (btn == 1U) {                /* is the button depressed? */
				static QEvt const pauseEvt = { PAUSE_SIG, 0U, 0U};
                QF_PUBLISH(&pauseEvt, (void *)0); //, &systick_handler);
            } 
            debounce_state = 0U;              /* transition back to state 0 */
            break;
    }
}

/*..........................................................................*/
void BSP_init(void) 
{
	USART_InitTypeDef USART_InitStructure;
	volatile uint32_t delay = 0;
	
	/*
	 * Setup the microcontroller system.
	 * Initialize the Embedded Flash Interface, the PLL and update the
	 * SystemFrequency variable.
	 * For default settings look at:
	 * pkg/mcu/st_stm32_stm32f4xx/src/system_stm32f4xx.c
	 */
	SystemInit();

	/* configure the LEDs*/
 	STM_EVAL_LEDInit(LED_RED);
	STM_EVAL_LEDInit(LED_GREEN);
	STM_EVAL_LEDInit(LED_BLUE);

	STM_EVAL_LEDOff(LED_RED);
	STM_EVAL_LEDOff(LED_GREEN);
	STM_EVAL_LEDOff(LED_BLUE);

	/* Initialize the user button. */
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_GPIO);
	
	/* USARTx configured as follow:
	 - BaudRate = 115200 baud
	 - Word Length = 8 Bits
	 - One Stop Bit
	 - No parity
	 - Hardware flow control disabled (RTS and CTS signals)
	 - Receive and transmit enabled
	 */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM_EVAL_COMInit(COM1, &USART_InitStructure);

    printf("\r\nDining Philosopher Problem example");
    printf("\r\nErika is the underlying RTOS");
    printf("\r\nQEP %s", QEP_getVersion());
    printf("\r\nQF  %s\r\n", QF_getVersion());


	while (delay++ < 20000000);
    
    if (QS_INIT((void *)0) == 0) {    /* initialize the QS software tracing */
        Q_ERROR();
    }

}

void BSP_displayPhilStat(uint8_t n, char const *stat) {
 	
	printf("\r\nPhilosopher %2d is %s", (int)n, stat);
	(stat[0] == 'e') ? STM_EVAL_LEDOn(LED_BLUE) : STM_EVAL_LEDOff(LED_BLUE);
	
    QS_BEGIN(PHILO_STAT, AO_Philo[n])  /* application-specific record begin */
        QS_U8(1, n);                                  /* Philosopher number */
        QS_STR(stat);                                 /* Philosopher status */
    QS_END()
}

void BSP_displayPaused(uint8_t paused) {
	printf("\r\nPaused is %s", paused ? "ON" : "OFF");
	(paused != 0U) ? STM_EVAL_LEDOn(LED_RED) : STM_EVAL_LEDOff(LED_RED);
	
}
/*..........................................................................*/
uint32_t BSP_random(void) {  /* a very cheap pseudo-random-number generator */
    float volatile x = 3.1415926F;
    x = x + 2.7182818F;

    /* "Super-Duper" Linear Congruential Generator (LCG)
    * LCG(2^32, 3*7*11*13*23, 0, seed)
    */
    l_rnd = l_rnd * (3U*7U*11U*13U*23U);

    return l_rnd >> 8;
}
/*..........................................................................*/
void BSP_randomSeed(uint32_t seed) {
    l_rnd = seed;
}
/*..........................................................................*/
void BSP_terminate(int16_t result) {
    (void)result;
}


/*..........................................................................*/
void QF_onStartup(void) {

	/*Initialize Erika related stuffs*/
	EE_system_init();
	
	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(BSP_TICKS_ms, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();
}
/*..........................................................................*/
void QF_onCleanup(void) {
	printf("\r\nBye! Bye!\r\n");
	
	QS_EXIT();
}
/*..........................................................................*/

/*..........................................................................*/
void QF_onIdle(void) {       /* called with interrupts disabled, see NOTE01 */
    float volatile x;
	
	STM_EVAL_LEDToggle(LED_GREEN);

    
	x = 3.1415926F;
    x = x + 2.7182818F;
	
#ifdef NDEBUG
    /* Put the CPU and peripherals to the low-power mode.
    * you might need to customize the clock management for your application,
    * see the datasheet for your particular Cortex-M MCU.
    */
    QF_CPU_SLEEP();         /* atomically go to sleep and enable interrupts */
#else
    QF_INT_ENABLE();                              /* just enable interrupts */
#endif
}

/*..........................................................................*/
void Q_onAssert(char const Q_ROM * const file, int line) {
    
	DisableAllInterrupts();
	
	for(;;);
}


/*
 * Philo0Task handles the l_philo[0] active object created in philo.c
 */
TASK(Philo0Task)
{

	task_function(pdata[Philo0Task]);
	
	TerminateTask();
}

/*
 * Philo1Task handles the l_philo[1] active object created in philo.c
 */
TASK(Philo1Task)
{

	task_function(pdata[Philo1Task]);
	
	TerminateTask();
}

/*
 * Philo2Task handles the l_philo[2] active object created in philo.c
 */
TASK(Philo2Task)
{

	task_function(pdata[Philo2Task]);
	
	TerminateTask();
}

/*
 * Philo3Task handles the l_philo[3] active object created in philo.c
 */
TASK(Philo3Task)
{

	task_function(pdata[Philo3Task]);
	
	TerminateTask();
}

/*
 * Philo4Task handles the l_philo[4] active object created in philo.c
 */
TASK(Philo4Task)
{

	task_function(pdata[Philo4Task]);
	
	TerminateTask();
}

/*
 * TableTask handles the Table active object created in table.c
 */
TASK(TableTask)
{

	task_function(pdata[TableTask]);
	
	TerminateTask();
}