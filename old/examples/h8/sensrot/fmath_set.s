;;; Author: 2002 Davide Cantini
;;; CVS: $Id: fmath_set.s,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $

;; 
;;  Set number of bit used for fractional part of 16bit fixed point number
;;
	
#ifdef __UNSIGNED_FIXED_USED__			
	.equ	EE_UF_NUM_BIT_FRAC, 9	;; 0 < UF_NUM_BIT_FRAC < 16
#endif


#ifdef __SIGNED_FIXED_USED__

	.equ	EE_SF_NUM_BIT_FRAC, 7	;; 0 < SF_NUM_BIT_FRAC < 16
#endif
