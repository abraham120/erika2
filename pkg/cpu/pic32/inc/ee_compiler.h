/*
 * Compiler dependent interface
 */

#ifdef __NO_INLINE__
#define __INLINE__ static
#else
#define __INLINE__ static inline
#endif

#define __ALWAYS_INLINE__ 

#define NORETURN  __attribute__ ((noreturn))
