/**
 * @brief Definitions of C99 boolean types
 *
 * @author  Bernardo  Dal Seno
 *
 * Copyright (C) 2010 Evidence srl
 *
 */

#ifndef __INCLUDE_CONTRIB_MISC_EE_STDBOOL_H__
#define __INCLUDE_CONTRIB_MISC_EE_STDBOOL_H__

/* When C99 stdbool is supported by the compiler library, just include
   the built-in stdbool.h */
#if defined(__LM32__) && defined(__GNUC__)
#include <stdbool.h>

#else /* No built-in stdboo.h */

#ifndef __bool_true_false_are_defined

#define __bool_true_false_are_defined 1
#define bool _Bool
#define true 1
#define false 0

#if defined(__GNUC__)
/* In recent GNU compilers _Bool is a built-in type (as per C99) */
#else
typedef unsigned char _Bool;
#endif

#endif /* ifndef __bool_true_false_are_defined */

#endif /* Compilers with direct support of stdbool.h */


#endif /* __INCLUDE_CONTRIB_MISC_EE_STDBOOL_H__ */
