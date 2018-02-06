;;; H8 asm file

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


	
