/** @file notification.c 
*   @brief User Notification Definition File
*   @date 9.Sep.2014
*   @version 04.01.00
*
*   This file  defines  empty  notification  routines to avoid
*   linker errors, Driver expects user to define the notification. 
*   The user needs to either remove this file and use their custom 
*   notification function or place their code sequence in this file 
*   between the provided USER CODE BEGIN and USER CODE END.
*
*/

/* Include Files */

#include "esm.h"
#include "adc.h"
#include "can.h"
#include "gio.h"
#include "sci.h"
#include "spi.h"
#include "het.h"
#include "rti.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */
#pragma WEAK(esmGroup1Notification)
void esmGroup1Notification(uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (1) */
/* USER CODE END */
}

/* USER CODE BEGIN (2) */
/* USER CODE END */

#pragma WEAK(esmGroup2Notification)
void esmGroup2Notification(uint32 channel)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (3) */
/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */

#pragma WEAK(rtiNotification)
void rtiNotification(uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (5) */

/* USER CODE END */
}

/* USER CODE BEGIN (6) */
/* USER CODE END */
#pragma WEAK(adcNotification)
void adcNotification(adcBASE_t *adc, uint32 group)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (7) */
/* USER CODE END */
}

/* USER CODE BEGIN (8) */
/* USER CODE END */
#pragma WEAK(canErrorNotification)
void canErrorNotification(canBASE_t *node, uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (9) */
/* USER CODE END */
}

/* USER CODE BEGIN (10) */
/* USER CODE END */

#pragma WEAK(canMessageNotification)
void canMessageNotification(canBASE_t *node, uint32 messageBox)  
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (11) */
/* USER CODE END */
}

/* USER CODE BEGIN (12) */
/* USER CODE END */
#pragma WEAK(gioNotification)
void gioNotification(sint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (13) */

/* USER CODE END */
}

/* USER CODE BEGIN (14) */
/* USER CODE END */
#pragma WEAK(sciNotification)
void sciNotification(sciBASE_t *sci, uint32 flags)     
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (17) */
/* USER CODE END */
}

/* USER CODE BEGIN (18) */
/* USER CODE END */
#pragma WEAK(spiNotification)
void spiNotification(spiBASE_t *spi, uint32 flags)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (19) */
/* USER CODE END */
}

/* USER CODE BEGIN (20) */
/* USER CODE END */

#pragma WEAK(spiGroupNotification)
void spiGroupNotification(spiBASE_t *spi, uint32 group)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (21) */
/* USER CODE END */
}

/* USER CODE BEGIN (22) */
/* USER CODE END */
#pragma WEAK(pwmNotification)
void pwmNotification(uint32 pwm, uint32 notification)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (23) */
/* USER CODE END */
}

/* USER CODE BEGIN (24) */
/* USER CODE END */

#pragma WEAK(edgeNotification)
void edgeNotification(uint32 edge)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (25) */
/* USER CODE END */
}

/* USER CODE BEGIN (26) */
/* USER CODE END */

#pragma WEAK(hetNotification)
void hetNotification(hetBASE_t *het, uint32 offset)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (27) */
/* USER CODE END */
}

/* USER CODE BEGIN (28) */
/* USER CODE END */

/* USER CODE BEGIN (29) */
/* USER CODE END */

#pragma WEAK(canStatusChangeNotification)
void canStatusChangeNotification(canBASE_t *node, uint32 notification)  
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (30) */
/* USER CODE END */
}

/* USER CODE BEGIN (31) */
/* USER CODE END */
