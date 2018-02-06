#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1275



//////////////////////////////////////////////////////////////////////////////
//  
//   Common defines ( CPU 0 )
//  
/////////////////////////////////////////////////////////////////////////////

    // TASK definition
    #define EE_MAX_TASK 2
    #define Task1 0
    #define Task2 1

    // MUTEX definition
    #define EE_MAX_RESOURCE 1U
    #define RES_SCHEDULER 0U

    // EVENT definition
    #define TimerEvent 0x1U
    #define ButtonEvent 0x2U

    // ALARM definition
    #define EE_MAX_ALARM 2
    #define AlarmTask1 0
    #define AlarmTask2 1

    // COUNTER definition
    #define EE_MAX_COUNTER 1
    #define Counter1 0

    // APPMODE definition
    #define EE_MAX_APPMODE 1U

    // CPUs
    #define EE_MAX_CPU 1
    #define EE_CURRENTCPU 0

#ifndef __DISABLE_EEOPT_DEFINES__


//////////////////////////////////////////////////////////////////////////////
//  
//   User options
//  
/////////////////////////////////////////////////////////////////////////////
#define __ASSERT__
#define __CODEWARRIOR__
#define CW_EVAL_VERSION
#define OO_CPU_HAS_STARTOS_ROUTINE


//////////////////////////////////////////////////////////////////////////////
//  
//   Automatic options
//  
/////////////////////////////////////////////////////////////////////////////
#define __RTD_CYGWIN__
#define __CODEWARRIOR__
#define __HCS12XS__
#define __MC9S12XS128__
#define __DEMO9S12XSFAME__
#define __USE_POTENTIOMETER__
#define __USE_ADC__
#define __USE_BUTTONS__
#define __USE_LEDS__
#define __USE_LIGHT_SENSOR__
#define __OO_ECC2__
#define __OO_EXTENDED_STATUS__
#define __OO_HAS_STARTUPHOOK__
#define __OO_HAS_ERRORHOOK__
#define __IRQ_STACK_NEEDED__
#define __MULTI__
#define __OO_HAS_USERESSCHEDULER__
#define __OO_AUTOSTART_TASK__
#define __OO_AUTOSTART_ALARM__
#define __ALLOW_NESTED_IRQ__
#define __OO_STARTOS_OLD__

#endif

#endif

