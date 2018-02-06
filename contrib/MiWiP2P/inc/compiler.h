/*
 * compiler.h
 *
 * Author: Gianluca Franchino (Abbreviation GF).
 * Affiliation: Retis Lab. Scuola Superiore Sant'Anna. Pisa (Italy).
 * Contacts: g.franchino@sssup.it; gianluca@evidence.eu.com
 * Date: 02/16/2009.
 */

#ifndef _COMPILER_H_
#define _COMPILER_H_

//#include "ee_pic30regs.h"


#if defined(__33FJ256MC710__) && !defined(C30)
#define __dsPIC33F__
#endif

#ifndef NULL
#define NULL 0
#endif

#ifdef __33FJ256MC710__
#define ROM						const
#define memcmppgm2ram(a,b,c)	memcmp(a,b,c)
#define memcpypgm2ram(a,b,c)	memcpy(a,b,c)
#define strcpypgm2ram(a, b)		strcpy(a,b)
#define	strlenpgm(a)			strlen(a)
#define strstrrampgm(a,b)		strstr(a,b)
#define Reset()					asm("reset")
#endif

#endif /* _COMPILER_H_ */
