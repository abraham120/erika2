/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2015  Evidence Srl
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

#include <stdio.h>
#include "ee.h"

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4_discovery_sdio_sd.h"
#include "ff.h"

/* Private variables ---------------------------------------------------------*/
SD_Error Status = SD_OK;

FATFS filesystem;		/* volume lable */

FRESULT ret;			  /* Result code */

FIL file;				    /* File object */

DIR dir;				    /* Directory object */

FILINFO fno;			  /* File information object */

UINT bw, br;

uint8_t buff[128];

uint8_t test_ok = 0;

/*
 * SysTick ISR2
 */
ISR2(systick_handler)
{
	/* counconsole_init()t the interrupts, waking up expired alarms */
	CounterTick(myCounter);
}

/**
 * @brief  This function handles SDIO global interrupt request.
 * @param  None
 * @retval None
 */
ISR1(SDIO_IRQHandler) {
	/* Process All SDIO Interrupt Sources */
	SD_ProcessIRQSrc();
}

/**
 * @brief  This function handles DMA2 Stream3 or DMA2 Stream6 global interrupts
 *         requests.
 * @param  None
 * @retval None
 */
ISR1(SD_SDIO_DMA_IRQHANDLER) {
	/* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
	SD_ProcessDMAIRQ();
}
/* Private function prototypes -----------------------------------------------*/
/**
 * @brief   FatFs err dispose
 * @param  None
 * @retval None
*/
static void fault_err (FRESULT rc)
{
	const char *str =
			"OK\0" "DISK_ERR\0" "INT_ERR\0" "NOT_READY\0" "NO_FILE\0" "NO_PATH\0"
			"INVALID_NAME\0" "DENIED\0" "EXIST\0" "INVALID_OBJECT\0" "WRITE_PROTECTED\0"
			"INVALID_DRIVE\0" "NOT_ENABLED\0" "NO_FILE_SYSTEM\0" "MKFS_ABORTED\0" "TIMEOUT\0"
			"LOCKED\0" "NOT_ENOUGH_CORE\0" "TOO_MANY_OPEN_FILES\0";
	FRESULT i;

	for (i = (FRESULT)0; i != rc && *str; i++) {
		while (*str++) ;
	}
	printf("rc=%u FR_%s\r\n", (UINT)rc, str);
	STM_EVAL_LEDOn(LED6);
	while(1);
}

/**
  * @brief  Delay
  * @param  None
  * @retval None
  */
static void Delay(volatile uint32_t nCount)
{
  volatile uint32_t index = 0;
  for (index = (100000 * nCount); index != 0; index--);
}

TASK(TaskSDTest)
{
	/* mount the filesystem */
	//if (f_mount(0, &filesystem) != FR_OK) {
	if (f_mount(&filesystem, "", 0) != FR_OK) {
		printf("could not open filesystem \n\r");
	}

	Delay(10);
	printf("Open a test file (message.txt) \r\n");
	ret = f_open(&file, "MESSAGE.TXT", FA_READ);
	printf("ret = %d\r\n",ret);
	if (ret) {
		printf("not exist the test file (message.txt)\r\n");
	} else {
		printf("Type the file content\r\n");
		for (;;) {
			ret = f_read(&file, buff, sizeof(buff), &br);	/* Read a chunk of file */
			if (ret || !br) {
				break;			/* Error or end of file */
			}
			buff[br] = 0;
			printf("%s",buff);
			printf("\r\n");
		}
	    if (ret) {
	    	printf("Read the file error\r\n");
	    	fault_err(ret);
	    }

	    printf("Close the file\r\n");
	    ret = f_close(&file);
	    if (ret) {
	    	printf("Close the file error\r\n");
	    }
	}

	/*  hello.txt write test*/
	Delay(50);
	printf("Create a new file (hello.txt)\r\n");
	ret = f_open(&file, "HELLO.TXT", FA_WRITE | FA_CREATE_ALWAYS);
	if (ret) {
		printf("Create a new file error\r\n");
		fault_err(ret);
	} else {
		printf("Write a text data. (hello.txt)\r\n");
		ret = f_write(&file, "Hello world!", 14, &bw);
		if (ret) {
			printf("Write a text data to file error\r\n");
		} else {
			printf("%u bytes written\r\n", bw);
		}
	    Delay(50);
	    printf("Close the file\r\n");
	    ret = f_close(&file);
	    if (ret) {
	    	printf("Close the hello.txt file error\r\n");
	    }
	}

	/*  hello.txt read test*/
	Delay(50);
	printf("read the file (hello.txt)\r\n");
	ret = f_open(&file, "HELLO.TXT", FA_READ);
	if (ret) {
		printf("open hello.txt file error\r\n");
	} else {
		printf("Type the file content(hello.txt)\r\n");
		for (;;) {
			ret = f_read(&file, buff, sizeof(buff), &br);	/* Read a chunk of file */
			if (ret || !br) {
				break;			/* Error or end of file */
			}
			buff[br] = 0;
			printf("%s",buff);
			printf("\r\n");
		}
	    if (ret) {
	    	printf("Read file (hello.txt) error\r\n");
	    	fault_err(ret);
	    }

	    printf("Close the file (hello.txt)\r\n");
	    ret = f_close(&file);
	    if (ret) {
	    	printf("Close the file (hello.txt) error\r\n");
	    }
	}

	/*  directory display test*/
	Delay(50);
	printf("Open root directory\r\n");
	ret = f_opendir(&dir, "");
	if (ret) {
		printf("Open root directory error\r\n");
	} else {
		printf("Directory listing...\r\n");
		for (;;) {
			ret = f_readdir(&dir, &fno);		/* Read a directory item */
			if (ret || !fno.fname[0]) {
				break;	/* Error or end of dir */
			}
			if (fno.fattrib & AM_DIR) {
				printf("  <dir>  %s\r\n", fno.fname);
			} else {
				printf("%8lu  %s\r\n", fno.fsize, fno.fname);
			}
		}
		if (ret) {
			printf("Read a directory error\r\n");
			fault_err(ret);
	    }
	}

	Delay(50);
	printf("Test completed\r\n");


	SetRelAlarm(AlarmTaskTestOk, 10, 500);
}

TASK(TaskTestOk)
{
	STM_EVAL_LEDToggle(LED3);
}

int main(void)
{

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

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED6);

	uart_init();

	ActivateTask(TaskSDTest);

	/* Forever loop: background activities (if any) should go here */
	for (;;) {

	}

}
