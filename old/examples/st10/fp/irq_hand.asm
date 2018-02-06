;;; Author: 2000 Paolo Gai
;;; CVS: $Id: irq_hand.asm,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $


; A Timer Handler

@IF( @__ST10SEGM__ )
$SEGMENTED
$CASE
REGDEF	R0-R15

ASSUME DPP3:SYSTEM

EXTERN _EE_st10_user_stack : WORD

@ELSE

$CASE
$EXTEND	    

REGDEF	R0-R15
@ENDI

$INCLUDE(sethand.asm)

@EE_hal_set_handler(38, _my_timer_handler, 0FC20h)
	

END
