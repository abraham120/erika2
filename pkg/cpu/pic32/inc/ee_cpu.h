#ifndef __INCLUDE_PIC32_EE_CPU_H__
#define __INCLUDE_PIC32_EE_CPU_H__

#include "eecfg.h"
#include "cpu/pic32/inc/ee_compiler.h"
#include "ee_pic32regs.h"

#define ASM_DIS_INT      	\
do {				\
	asm volatile("di");	\
} while (0)
  
#define ASM_EN_INT      	\
do {				\
	asm volatile("ei");	\
} while (0)
  
/*************************************************************************
 HAL Constants
 *************************************************************************/

/* invalid pointer */
#ifndef NULL
#define NULL 0
#endif

/*************************************************************************
 HAL Types
 *************************************************************************/

/* Primitive data types */
typedef unsigned char EE_BIT; 
typedef unsigned char EE_UINT8;
typedef unsigned short int EE_UINT16;
typedef unsigned int EE_UINT32;
typedef signed char EE_INT8;
typedef signed short int EE_INT16;
typedef signed int EE_INT32;
typedef EE_UINT32 EE_UREG;
#define EE_UREG_SIZE 4
typedef EE_INT32  EE_SREG;
typedef EE_UINT32 EE_FREG;

/* boolean type */
#ifndef EE_TYPEBOOL
typedef EE_UREG EE_TYPEBOOL;
#endif

/* boolean true define */
#ifndef EE_TRUE
#define EE_TRUE ((EE_TYPEBOOL)1U)
#endif

/* boolean false define */
#ifndef EE_FALSE
#define EE_FALSE ((EE_TYPEBOOL)0U)
#endif


/* Thread IDs */
typedef EE_UINT32 EE_TID;
typedef EE_UINT32 EE_UTID;

/* Addresses (that have the same size of a pointer) */
typedef void *EE_ADDR;

/* Callbacks with no parameters nor return value */
typedef void (*EE_VOID_CALLBACK)(void);

/* Code addresses (same size of function pointers) */
/* For an easy upgrade path, we use a define instead of the typedef:
   typedef void (*EE_FADDR)(void); */
#define EE_FADDR EE_ADDR

/* Thread body pointer (same size of function pointers) */
#define EE_THREAD_PTR EE_ADDR

/*************************************************************************
 Application dependent data types
 *************************************************************************/
#ifdef __HAS_TYPES_H__
#include "types.h"
#endif

/*************************************************************************
 HAL Variables
 *************************************************************************/

/* Thread function body pointer */
extern const EE_ADDR EE_hal_thread_body[];

#ifdef __MULTI__
struct EE_TOS {
    EE_ADDR SYS_tos;
};
/* each task use a system (IRQ) stack and a user (SYS) stack */
extern struct EE_TOS EE_pic32_system_tos[];

/* pic32_system_tos[] index that point to the thread tos (one for each thread)*/
extern EE_UREG EE_pic32_thread_tos[];

/* pic32_system_tos[] index that point to the active thread tos */
extern EE_UREG EE_pic32_active_tos;

#ifdef __ALLOW_NESTED_IRQ__
#ifdef __IRQ_STACK_NEEDED__
/* stack used by IRQ handlers */
extern EE_UREG EE_pic32_stack_IRQ[EE_PIC32_STACK_IRQ_SIZE];
#define EE_PIC32_IRQ_TOS (EE_pic32_stack_IRQ + EE_PIC32_STACK_IRQ_SIZE)
#endif /* __IRQ_STACK_NEEDED__ */
#endif /* __ALLOW_NESTED_IRQ__ */
#endif /* __MULTI__ */

#if defined(__OO_BCC1__) || defined(__OO_BCC2__) || defined(__OO_ECC1__) || defined(__OO_ECC2__)
/* this is a safe place to put sp_sys when EE_hal_terminate_savestk
   is called into EE_oo_thread_stub */
extern EE_UINT32 EE_terminate_data[];

/* this is the real thread body that is called if the thread use the
   TerminateTask function */
extern const EE_ADDR EE_terminate_real_th_body[];

/* this is the stub that have to be put into the EE_th_body array */
extern void EE_oo_thread_stub(void);

#endif



/*********************************************************************
 PIC32 interrupt disabling/enabling
 *********************************************************************/

/*
 * Enable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_pic32_enableIRQ(void)
{
	ASM_EN_INT;
}

/*
 * Disable interrupts
 */
__INLINE__ void __ALWAYS_INLINE__ EE_pic32_disableIRQ(void)
{
	ASM_DIS_INT;
}


/*************************************************************************
 HAL Interrupt handling
 *************************************************************************/

/* Disable/Enable Interrupts */
__INLINE__ void __ALWAYS_INLINE__ EE_hal_enableIRQ(void)
{
	EE_pic32_enableIRQ();
}

__INLINE__ void __ALWAYS_INLINE__ EE_hal_disableIRQ(void)
{
	EE_pic32_disableIRQ();
}

/* This architecture doesn't support new HAL APIs for interrupt handling
   look at pic30, e200zx, cortex_mx or hs12xs ee_cpu.h to look new APIs
   signature and semantic.
 */
#define EE_OLD_HAL

/*************************************************************************
 Include the IRQ stub: ISR2
 *************************************************************************/
#include "cpu/pic32/inc/ee_irqstub.h"

/*************************************************************************
 Include the Utils 
 *************************************************************************/
#include "cpu/pic32/inc/ee_utils.h"

#endif /* __INCLUDE_PIC32_ARCH_H__ */
