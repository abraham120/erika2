#ifndef __mem_compiler_h__
#define __mem_compiler_h__

/**
* Start Compiler Selection section
* \todo What is the global symbol for Erika Enterprise Kernel?
*/
#ifdef __ERIKA__		/* Erika Abstract Compiler */
#include <arch/mem_compiler_ee.h>
#ifdef __C30__ 
#ifndef COMPILER_ATTRIBUTE_FAR 
#define COMPILER_ATTRIBUTE_FAR __attribute__((far))
#endif
#elif defined (__PIC32__)
#define COMPILER_ATTRIBUTE_FAR
#elif defined __AVR5__
#ifndef COMPILER_ATTRIBUTE_FAR 
//#define COMPILER_ATTRIBUTE_FAR __attribute__((far))
#define COMPILER_ATTRIBUTE_FAR 
#endif 
#endif/* _AVR5_ */

#elif defined __C30__ 	/* Microchip C30 */
#include <arch/mem_compiler_c30.h>
#ifndef COMPILER_ATTRIBUTE_FAR 
#define COMPILER_ATTRIBUTE_FAR __attribute__((far))
#endif

#else			/* No compiler */
#error "MEMORY LIBRARY ERROR: compiler type not specified"

#endif	/* End Compiler Selection */

#endif /* Header Protection */
