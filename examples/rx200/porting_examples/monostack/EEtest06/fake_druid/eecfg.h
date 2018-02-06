#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1275



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
    #define EE_MAX_ALARM 0

    /* COUNTER definition */
    #define EE_MAX_COUNTER 0

    /* APPMODE definition */
    #define EE_MAX_APPMODE 1U

    /* CPUs */
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0


#ifndef __DISABLE_EEOPT_DEFINES__


/***************************************************************************
 *
 * User options
 *
 **************************************************************************/
#define __ASSERT__
#define __RSKRX210__
#define __USE_RSKRX120_USER_LED__
#define __USE_RSKRX210_OP_FREQ_SETUP__

/***************************************************************************
 *
 * Automatic options
 *
 **************************************************************************/
#define __RTD_CYGWIN__
#define __RX200__
#define __R5F5210x__
#define __CCRX__
#define __OO_BCC1__
#define __OO_STARTOS_OLD__
#define __OO_EXTENDED_STATUS__
#define __MONO__
#define __OO_NO_ALARMS__
#define __OO_NO_RESOURCES__
#define __OO_AUTOSTART_TASK__

#endif

#endif

