#ifndef __EECFG_H__
#define __EECFG_H__


#define RTDRUID_CONFIGURATOR_NUMBER 1276



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
    #define Resource 0U

    // ALARM definition
    #define EE_MAX_ALARM 0

    // COUNTER definition
    #define EE_MAX_COUNTER 0

    // APPMODE definition
    #define EE_MAX_APPMODE 0U

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
#define __USE_TIMER__
#define __USE_SCI__


//////////////////////////////////////////////////////////////////////////////
//  
//   Automatic options
//  
/////////////////////////////////////////////////////////////////////////////
#define __RTD_CYGWIN__
#define __CODEWARRIOR__
#define __MC9S12__
#define __MC9S12G128__
#define __OO_BCC1__
#define __OO_EXTENDED_STATUS__
#define __MONO__
#define __OO_NO_ALARMS__
#define __OO_STARTOS_OLD__
#define __ALLOW_NESTED_IRQ__

#endif

#endif

