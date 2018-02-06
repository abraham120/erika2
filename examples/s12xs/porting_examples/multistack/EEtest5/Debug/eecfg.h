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
    #define Producer 0
    #define Consumer 1

    // MUTEX definition
    #define EE_MAX_RESOURCE 0U

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
#define __SEM__
#define __ASSERT__
#define __S12XS_INCLUDE_REGS__


//////////////////////////////////////////////////////////////////////////////
//  
//   Automatic options
//  
/////////////////////////////////////////////////////////////////////////////
#define __RTD_CYGWIN__
#define __COSMIC__
#define __HCS12XS__
#define __USE_PIT__
#define __MC9S12XS128__
#define __DEMO9S12XSFAME__
#define __USE_POTENTIOMETER__
#define __USE_ADC__
#define __USE_BUTTONS__
#define __USE_LEDS__
#define __USE_LIGHT_SENSOR__
#define __FP__
#define __IRQ_STACK_NEEDED__
#define __MULTI__
#define __FP_NO_RESOURCES__
#define __ALLOW_NESTED_IRQ__

#endif

#endif

