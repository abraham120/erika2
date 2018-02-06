;;; Author: 2002 Davide Cantini
;;; CVS: $Id: set_hand.s,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $

.include "handstub.s"
	
;;;  handlers installed by system
.ifdef __TIMER_A_SUPPORT__
	M_set_handler EE_timerA_handler    
.endif

.ifdef __TIMER_B_SUPPORT__
	M_set_handler EE_timerB_handler
.endif

.ifdef __MOTOR_A_PWM_USED__
	M_set_handler CMI1A_handler
.endif

.ifdef __MOTOR_C_PWM_USED__
	M_set_handler CMI1B_handler	
.endif

.ifdef __MOTOR_PWM_SUPPORT__
	M_set_handler OVI1_handler	
.endif
	

;;;  handlers installed by user application 

	M_set_handler ONOFF_handler

	
