/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2002 Davide Cantini
 * CVS: $Id: ee_fmath.h,v 1.2 2006/04/08 21:07:06 pj Exp $
 */


/*****************************
 ****  FIXED POINT MATH   ****
 *****************************/

/* Three types of fixed point are available:						*
 * Unsigned Fixed: 16 bit, where N bit of which are for fractional part.		*
 *		   RANGE      : from  0.0  to  (2^(16-N))-1.(((2^N)-1)/(2^N))		*
 *		   GRANULARITY: 1/(2^N)							*
 *		   Example: N=10 => from 0.0 to 63.999023   (Granularity= 0.00097656)  	*			*
 *		   N=UF_NUM_BIT_FRAC is application dependent: see 'fmath_set.s' file.  *
 *											*
 * Signed Fixed:   16 bit, where N bit of which are for fractional part.		*
 *		   RANGE      : from -2^(16-N-1).0 to (2^(16-N-1))-1.(((2^N)-1)/(2^N))	*
 *		   GRANULARITY: 1/(2^N)							* 
 *		   Example: N=10 => from -32.0 to 31.999023				*
 *		   N=SF_NUM_BIT_FRAC is application dependent: see 'fmath_set.s' file. 	*
 *											*
 * Double Fixed:   32 bit, where 16 bit of which are for fractional part.		*
 *		   RANGE: from -32768.0 to 32767.999984					*
 *		   GRANULARITY: 1/(2^16)=0.00001526					*
 *											*
 * NOTES:										*
 * - You can think unsigned fixed and signed fixed just like as natural and integer	*
 *   numbers. So for example you can freely compare them with standard operators.	*
 * - Double fixed are slower than signed and unsigned; in particular division is slow   *
 *   I hope to find out some faster alghoritm,... Any idea about it?		  	*/
 
#include "erikahal.h"
	
#ifdef __UNSIGNED_FIXED_USED__
    /***********************
     *** UNSIGNED  FIXED ***
     ***********************/

    typedef EE_UINT16  EE_UF_TYPE;
    
    /* converts unsigned to fixed */
    EE_UF_TYPE EE_uint2uf(EE_UINT16 u);

    /* converts fixed to unsigned */
    EE_UINT16 EE_uf2uint(EE_UF_TYPE uf);

    /* returns a+b */    
//    __INLINE__ EE_UF_TYPE __ALWAYS_INLINE__ EE_uf_add(EE_UF_TYPE a, EE_UF_TYPE b)
//    {
//	return a+b;
//    }

    /* returns a-b */    
//    __INLINE__ EE_UF_TYPE __ALWAYS_INLINE__ EE_uf_sub(EE_UF_TYPE a, EE_UF_TYPE b)
//    {
//	return a-b;
//    }

    /* returns a*b */
    EE_UF_TYPE EE_uf_mul(EE_UF_TYPE a, EE_UF_TYPE b);

    /* returns a/b (quozient) */
    EE_UF_TYPE EE_uf_div(EE_UF_TYPE a, EE_UF_TYPE b);
#endif 


#ifdef __SIGNED_FIXED_USED__
    /***********************
     **** SIGNED  FIXED ****
     ***********************/
     
    typedef EE_INT16   EE_SF_TYPE;
    
#ifdef __SF_TRIG_USED__
    extern EE_INT16 EE_sf_table_cos[];

    /* calculate cos(theta) */    
    EE_SF_TYPE EE_sf_cos (EE_UINT16 theta); 

    /* calculate sin(theta) */
    EE_SF_TYPE EE_sf_sin (EE_UINT16 theta); 
        
#endif
    
    /* converts integer to fixed */
    EE_SF_TYPE EE_int2sf(EE_INT16 i);

    /* converts fixed to integer */
    EE_INT16 EE_sf2int(EE_SF_TYPE f);

    /* returns a+b */
//    __INLINE__ EE_SF_TYPE __ALWAYS_INLINE__ EE_sf_add(EE_SF_TYPE a, EE_SF_TYPE b)
//    {
//	return a+b;
//    }
    
    /* returns -a */
    EE_SF_TYPE EE_sf_negate(EE_SF_TYPE a);	
    

    /* returns a-b */
//    __INLINE__ EE_SF_TYPE __ALWAYS_INLINE__ EE_sf_sub(EE_SF_TYPE a, EE_SF_TYPE b)
//    {
//	return a-b;
//    }

    /* returns a*b */
    EE_SF_TYPE EE_sf_mul(EE_SF_TYPE a, EE_SF_TYPE b);

    /* returns a/b (quozient) */
    EE_SF_TYPE EE_sf_div(EE_SF_TYPE a, EE_SF_TYPE b);
#endif

#ifdef __DOUBLE_FIXED_USED__
    /********************************
     **** DOUBLE  FIXED (signed) ****
     ********************************/

    typedef struct DF_STRUCT {        
	EE_INT16 ip;    
	EE_UINT16 fp;        	
    } EE_DF_TYPE;

#ifdef __DF_TRIG_USED__
    extern EE_UINT16 EE_table_cos[];
    
    /* internally used (called by EE_cos and EE_sin) */
    void _df_trigon (EE_DF_TYPE * dfs, EE_DF_TYPE * theta, EE_UINT16 ph); 
    
    /* calculate cos(theta) and store it into dfs */
    __INLINE__ void __ALWAYS_INLINE__ EE_df_cos(EE_DF_TYPE * dfs, EE_DF_TYPE * theta)
    {
	_df_trigon(dfs, theta, 0);
    }
    /* calculate sin(theta) and store it into dfs */
    __INLINE__ void __ALWAYS_INLINE__ EE_df_sin(EE_DF_TYPE * dfs, EE_DF_TYPE * theta)
    {
	_df_trigon(dfs, theta, 90);
    }
#endif

    /* converts integer to fixed and store it into res*/
    void EE_int2df(EE_DF_TYPE * res, EE_INT16 i);

    /* converts fixed to integer and return it */
    EE_INT16 EE_df2int(EE_DF_TYPE * dfa);
    
    /* return -1, 0, 1 if dfa<dfb, dfa==dfb, dfa>dfb respectively */
    EE_INT16 EE_df_cmp(EE_DF_TYPE * dfa, EE_DF_TYPE * dfb);
    
    /* negate dfa and store it into res */    
    void EE_df_negate(EE_DF_TYPE * res, EE_DF_TYPE * dfa);
    
    /* calculate (dfa+dfb) and store it into res */    
    void EE_df_add(EE_DF_TYPE * res, EE_DF_TYPE * dfa, EE_DF_TYPE * dfb);
    
    /* calculate (dfa-dfb) and store it into res */        
    void EE_df_sub(EE_DF_TYPE * res, EE_DF_TYPE * dfa, EE_DF_TYPE * dfb);
    
    /* calculate (dfa*dfb) and store it into res */        
    void EE_df_mul(EE_DF_TYPE * res, EE_DF_TYPE * dfa, EE_DF_TYPE * dfb);
    
    /* calculate (dfa/dfb) and store it into res */        
    void EE_df_div(EE_DF_TYPE * res, EE_DF_TYPE * dfa, EE_DF_TYPE * dfb);        
#endif
