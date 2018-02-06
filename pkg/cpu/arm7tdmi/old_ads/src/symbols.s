;;; Author: 2001-2002 Alessandro Colantonio
;;; CVS: $Id: symbols.s,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
	
;;
;; CPSR and SPSR control bits
;;
Mode_USR	EQU	0x10
Mode_FIQ	EQU	0x11
Mode_IRQ	EQU	0x12
Mode_SVC	EQU	0x13
Mode_ABT	EQU	0x17
Mode_UNDEF	EQU	0x1B
Mode_SYS	EQU	0x1F

I_bit		EQU	0x80	; when I-bit is _set_, IRQ is _disabled_
F_bit		EQU	0x40	; when F-bit is _set_, FIQ is _disabled_


	
		END
