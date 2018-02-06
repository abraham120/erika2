#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1278



/***************************************************************************
 *
 * Common defines ( CPU 0 )
 *
 **************************************************************************/

    /* TASK definition */
    #define EE_MAX_TASK 2
    #define Task1 0
    #define Task2 1

    /* MUTEX definition */
    #define EE_MAX_RESOURCE 0U

    /* ALARM definition */
    #define EE_MAX_ALARM 0U

    /* SCHEDULING TABLE definition */
    #define EE_MAX_SCHEDULETABLE 0U

    /* COUNTER OBJECTS definition */
    #define EE_MAX_COUNTER_OBJECTS (EE_MAX_ALARM + EE_MAX_SCHEDULETABLE)

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0U

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

    /* Number of isr 2 */
    #define EE_MAX_ISR2   1
    #define EE_MAX_ISR_ID 1

/***************************************************************************
 *
 * ISR
 *
 **************************************************************************/
#define EE_AVR8_TIMER0_COMPA_ISR	timer_handler
/* #define EE_AVR8_TIMER0_COMPA_ISR_PRI	EE_ISR_PRI_LOW */
#define EE_AVR8_TIMER0_COMPA_ISR_CAT	2

#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__
#define __OO_STARTOS_OLD__


/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
//#define __RTD_CYGWIN__
//#define __RTD_LINUX__
#define __AVR8__
#define __ATTINY__
#define __TIMER_USED__
#define __TIMER_0_USED__
#define __TIMER0_CLK_DIV256__
#define __OO_BCC1__
#define __OO_EXTENDED_STATUS__
#define __MONO__
#define __OO_NO_ALARMS__
#define __OO_NO_RESOURCES__
#define __OO_AUTOSTART_TASK__
#define __ALLOW_NESTED_IRQ__

#endif

/***************************************************************************
 *
 * Vector size defines
 *
 **************************************************************************/
    #define EE_OO_AUTOSTART_TASK_MODE_OSDEFAULTAPPMODE_SIZE 1


#endif

