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

/*
 * Author: 2013  Gianluca Franchino.
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

#ifdef Q_SPY

    QSTimeCtr QS_tickTime_;
    QSTimeCtr QS_tickPeriod_;
    static uint8_t l_SysTick_Handler;
    static uint8_t l_GPIOPortA_IRQHandler;
    static uint8_t l_EXTI0_IRQHandler;

    #define UART_BAUD_RATE      115200U
    #define UART_TXFIFO_DEPTH   16U

    enum AppRecords {                 /* application-specific trace records */
        PHILO_STAT = QS_USER
    };

#endif

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
    static uint8_t  debounce_state = 0U;
    uint32_t btn;

#ifdef Q_SPY
    {
        uint32_t dummy = SysTick->CTRL;     /* clear SysTick_CTRL_COUNTFLAG */
        QS_tickTime_ += QS_tickPeriod_;   /* account for the clock rollover */
    }
#endif

    QF_TICK_X(0U, &l_SysTick_Handler);     /* process all armed time events */

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
                QF_PUBLISH(&pauseEvt, &l_SysTick_Handler);
            } 
            debounce_state = 0U;              /* transition back to state 0 */
            break;
    }
}

ISR2(button_usr_isr)
{
    QACTIVE_POST(AO_Table, Q_NEW(QEvt, MAX_PUB_SIG),      /* for testing... */
                 &l_GPIOPortA_IRQHandler);
	/* Clear the EXTI line pending bit */
	EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
}


void BSP_init(void) 
{
	
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
	STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
	
    if (QS_INIT((void *)0) == 0) {    /* initialize the QS software tracing */
        Q_ERROR();
    }
    
	QS_OBJ_DICTIONARY(&l_SysTick_Handler);
    QS_OBJ_DICTIONARY(&l_EXTI0_IRQHandler);
}

void BSP_displayPhilStat(uint8_t n, char const *stat) {
 	
	(stat[0] == 'e') ? STM_EVAL_LEDOn(LED_BLUE) : STM_EVAL_LEDOff(LED_BLUE);
	
    QS_BEGIN(PHILO_STAT, AO_Philo[n])  /* application-specific record begin */
        QS_U8(1, n);                                  /* Philosopher number */
        QS_STR(stat);                                 /* Philosopher status */
    QS_END()
}

void BSP_displayPaused(uint8_t paused) {
	(paused != 0U) ? STM_EVAL_LEDOn(LED_RED) : STM_EVAL_LEDOff(LED_RED);
	
}

uint32_t BSP_random(void) {  /* a very cheap pseudo-random-number generator */
    float volatile x = 3.1415926F;
    x = x + 2.7182818F;

    /* "Super-Duper" Linear Congruential Generator (LCG)
    * LCG(2^32, 3*7*11*13*23, 0, seed)
    */
    l_rnd = l_rnd * (3U*7U*11U*13U*23U);

    return l_rnd >> 8;
}


void BSP_randomSeed(uint32_t seed) {
    l_rnd = seed;
}

void BSP_terminate(int16_t result) {
    (void)result;
}


void QF_onStartup(void) {

	/*Initialize Erika related stuffs*/
	EE_system_init();
	
	/*Initialize systick */
	EE_systick_set_period(MILLISECONDS_TO_TICKS(BSP_TICKS_ms, SystemCoreClock));
	EE_systick_enable_int();
	EE_systick_start();
}

/*void QF_onCleanup(void) {
}*/

void QF_onIdle(void) {      
	
    float volatile x;
	
	STM_EVAL_LEDToggle(LED_GREEN);

    
	x = 3.1415926F;
    x = x + 2.7182818F;

#ifdef Q_SPY
    QF_INT_ENABLE();
    /* TX done? */
	if (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) != RESET) {
        uint16_t fifo = UART_TXFIFO_DEPTH;       /* max bytes we can accept */
        uint8_t const *block;

        QF_INT_DISABLE();
        block = QS_getBlock(&fifo);    /* try to get next block to transmit */
        QF_INT_ENABLE();

        while (fifo-- != 0) {                    /* any bytes in the block? */
            /* put into the FIFO */
			USART_SendData(EVAL_COM1, *block++);
			while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
        }
    }
	
#elif defined NDEBUG
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

#ifdef Q_SPY
/*..........................................................................*/
uint8_t QS_onStartup(void const *arg) {
    static uint8_t qsBuf[2*1024];                 /* buffer for Quantum Spy */
    uint32_t tmp;
    USART_InitTypeDef USART_InitStructure;
    QS_initBuf(qsBuf, sizeof(qsBuf));

	/* configure the UART for the desired baud rate, 8-N-1 operation */
	USART_InitStructure.USART_BaudRate = UART_BAUD_RATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	STM_EVAL_COMInit(COM1, &USART_InitStructure);



    QS_tickPeriod_ = SystemCoreClock / BSP_TICKS_PER_SEC;
    QS_tickTime_ = QS_tickPeriod_;        /* to start the timestamp at zero */

                                                 /* setup the QS filters... */
    QS_FILTER_ON(QS_ALL_RECORDS);

//    QS_FILTER_OFF(QS_QEP_STATE_EMPTY);
//    QS_FILTER_OFF(QS_QEP_STATE_ENTRY);
//    QS_FILTER_OFF(QS_QEP_STATE_EXIT);
//    QS_FILTER_OFF(QS_QEP_STATE_INIT);
//    QS_FILTER_OFF(QS_QEP_INIT_TRAN);
//    QS_FILTER_OFF(QS_QEP_INTERN_TRAN);
//    QS_FILTER_OFF(QS_QEP_TRAN);
//    QS_FILTER_OFF(QS_QEP_IGNORED);

//    QS_FILTER_OFF(QS_QF_ACTIVE_ADD);
//    QS_FILTER_OFF(QS_QF_ACTIVE_REMOVE);
//    QS_FILTER_OFF(QS_QF_ACTIVE_SUBSCRIBE);
//    QS_FILTER_OFF(QS_QF_ACTIVE_UNSUBSCRIBE);
//    QS_FILTER_OFF(QS_QF_ACTIVE_POST_FIFO);
//    QS_FILTER_OFF(QS_QF_ACTIVE_POST_LIFO);
//    QS_FILTER_OFF(QS_QF_ACTIVE_GET);
//    QS_FILTER_OFF(QS_QF_ACTIVE_GET_LAST);
//    QS_FILTER_OFF(QS_QF_EQUEUE_INIT);
//    QS_FILTER_OFF(QS_QF_EQUEUE_POST_FIFO);
//    QS_FILTER_OFF(QS_QF_EQUEUE_POST_LIFO);
//    QS_FILTER_OFF(QS_QF_EQUEUE_GET);
//    QS_FILTER_OFF(QS_QF_EQUEUE_GET_LAST);
//    QS_FILTER_OFF(QS_QF_MPOOL_INIT);
//    QS_FILTER_OFF(QS_QF_MPOOL_GET);
//    QS_FILTER_OFF(QS_QF_MPOOL_PUT);
//    QS_FILTER_OFF(QS_QF_PUBLISH);
//    QS_FILTER_OFF(QS_QF_NEW);
//    QS_FILTER_OFF(QS_QF_GC_ATTEMPT);
//    QS_FILTER_OFF(QS_QF_GC);
//    QS_FILTER_OFF(QS_QF_TICK);
//    QS_FILTER_OFF(QS_QF_TIMEEVT_ARM);
//    QS_FILTER_OFF(QS_QF_TIMEEVT_AUTO_DISARM);
//    QS_FILTER_OFF(QS_QF_TIMEEVT_DISARM_ATTEMPT);
//    QS_FILTER_OFF(QS_QF_TIMEEVT_DISARM);
//    QS_FILTER_OFF(QS_QF_TIMEEVT_REARM);
//    QS_FILTER_OFF(QS_QF_TIMEEVT_POST);
    QS_FILTER_OFF(QS_QF_CRIT_ENTRY);
    QS_FILTER_OFF(QS_QF_CRIT_EXIT);
    QS_FILTER_OFF(QS_QF_ISR_ENTRY);
    QS_FILTER_OFF(QS_QF_ISR_EXIT);

    return (uint8_t)1;                                    /* return success */
}
/*..........................................................................*/
void QS_onCleanup(void) {
}
/*..........................................................................*/
QSTimeCtr QS_onGetTime(void) {            /* invoked with interrupts locked */
    if ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0) {    /* not set? */
        return QS_tickTime_ - (QSTimeCtr)SysTick->VAL;
    }
    else {     /* the rollover occured, but the SysTick_ISR did not run yet */
        return QS_tickTime_ + QS_tickPeriod_ - (QSTimeCtr)SysTick->VAL;
    }
}
/*..........................................................................*/
void QS_onFlush(void) {
    uint16_t fifo = UART_TXFIFO_DEPTH;                     /* Tx FIFO depth */
    uint8_t const *block;
    QF_INT_DISABLE();
    while ((block = QS_getBlock(&fifo)) != (uint8_t *)0) {
        QF_INT_ENABLE();
                                           /* busy-wait until TX FIFO empty */
      /*  while ((UART0->FR & UART_FR_TXFE) == 0) {
        }*/
		while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
		
        while (fifo-- != 0) {                    /* any bytes in the block? */
            USART_SendData(EVAL_COM1, *block++);
			while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET);
        }
        fifo = UART_TXFIFO_DEPTH;              /* re-load the Tx FIFO depth */
        QF_INT_DISABLE();
    }
    QF_INT_ENABLE();
}
#endif                                                             
/* Q_SPY */

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
