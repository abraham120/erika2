;;; Author: 2000 Paolo Gai
;;; CVS: $Id: irq_st10.asm,v 1.1 2005/07/17 13:10:52 pj Exp $


; A Timer Handler

@IF( @__ST10SEGM__ )
$SEGMENTED
$CASE
REGDEF	R0-R15

ASSUME DPP3:SYSTEM

EXTERN _ERE_st10_user_stack : WORD

@ELSE

$CASE
$EXTEND	    

REGDEF	R0-R15
@ENDI

$INCLUDE(sethand.asm)

@ERE_hal_set_handler(38, _timer_and_button_handler, 0FC20h)
	

END
